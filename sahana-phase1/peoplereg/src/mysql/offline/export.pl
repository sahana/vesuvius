#!/usr/bin/perl

use strict;

use XML::DOM;
use DBI;

my $verbose = 1;

my $parser = XML::DOM::Parser->new();
my $dump = $parser->parsefile('dump.xml');

my $database_nodes = $dump->getElementsByTagName('database');
my $n = $database_nodes->getLength();

for (my $i = 0; $i < $n; $i++) {
	my $database_node = $database_nodes->item($i);
	dump_database($database_node);
}

exit(0);


sub dump_database()
{
	my $database_node = shift;
	my $name = $database_node->getAttributeNode('name')->getValue();
	my $user = $database_node->getAttributeNode('user')->getValue();
	my $password = $database_node->getAttributeNode('password')->getValue();

	print "Opening database `$name' as `$user'...";
	my $dbh = DBI->connect("DBI:mysql:database=$name", $user, $password) or die "Can't open database '$name'.";
	print "done.\n\n";

	my $target_nodes = $database_node->getElementsByTagName('target');
	unless ($target_nodes->getLength()) {
		print "*** No target database ***\n";
		exit 1;
	}
	my $target_node = $target_nodes->item(0);
	my $target_name = $target_node->getAttributeNode('name')->getValue();
	my $target_user = $target_node->getAttributeNode('user')->getValue();
	my $target_password = $target_node->getAttributeNode('password')->getValue();

	print "Opening target database `$target_name' as `$target_user'...";
	my $dbh_target = DBI->connect("DBI:mysql:database=$target_name", $target_user, $target_password) or die "Can't open target database '$target_name'.";
	print "done.\n\n";

	my $table_nodes = $database_node->getElementsByTagName('table');
	my $n = $table_nodes->getLength();

	print "Reading table information.\n";
	my %table = ();
	for (my $i = 0; $i < $n; $i++) {
		my $table = read_table_info($dbh, $table_nodes->item($i));
		$table{$table->{name}} = $table;
	}
	print "Finished reading table information.\n\n";

	print "Setting up cross references and queries.\n";
	foreach my $table (sort keys %table) {
		if ($table{$table}{refers}) {
			print "References in $table:\n";
			foreach my $column (sort keys %{$table{$table}{refers}}) {
				my $ref_table = $table{$table}{refers}{$column}{table};
				my $ref_key = $table{$table}{refers}{$column}{key};
				unless ($table{$ref_table}{auto} eq $ref_key) {
					print "*** Can't find $ref_key as an auto_increment field in $ref_table ***\n";
				}
				print "  $column => $ref_table, $ref_key\n";
				$table{$ref_table}{refered}{$ref_key}{table} = $table;
				$table{$ref_table}{refered}{$ref_key}{column} = $column;
			}
		}
		$table{$table}{status} = 'ready';
	}
	print "Cross references and queries complete.\n\n";

	print "All set to go! :-)\n\n";

	print "Dumping database $name\n";
	my $not_done = 1;
	my %map = ();
	my $last_id = $dbh->prepare('select last_insert_id()');
	while ($not_done) {
		$not_done = 0;
		foreach my $table (sort keys %table) {
			if ($table{$table}{status} eq 'ready') {
				$not_done = 1;
				print "- Table $table is in ready state.\n" if ($verbose);
				my $have_all = 1;
				my @values = ();
				foreach my $column (sort keys %{$table{$table}{refers}}) {
					my $ref_table = $table{$table}{refers}{$column}{table};
					unless ($table{$ref_table}{status} eq 'done') {
						print "- Table $ref_table is not done yet, sleeping.\n";
						$have_all = 0;
						last;
					}
				}
				if ($have_all) {
					print "- All dependent tables (if any) are ready.\n" if ($verbose);
					print "- Fetching data.\n" if ($verbose);

					my $get = $dbh->prepare("select * from $table");
					$get->execute();

					my $insert_query = "insert into $table";
					my @columns = sort keys %{$table{$table}{column}};
					my $columns = join (',', @columns);
					if ($columns) {
						$insert_query .= " ($columns)";
					}
					$insert_query .= ' values (' . ($#columns ? '?' : '') . (',?' x $#columns) . ')';
					print "- Insert query: $insert_query\n" if ($verbose);

					my $insert = $dbh_target->prepare($insert_query);

					while (my $row = $get->fetchrow_hashref()) {
						@values = ();
						my $auto = undef;
						foreach my $column (@columns) {
							if ($table{$table}{column}{$column}{type} == 'normal') {
								push @values, $row->{$column};
							}
							elsif ($table{$table}{column}{$column}{type} == 'foreign') {
								push @values, $map{$table{$table}{refers}{$column}{table}}{$row->{$column}};
							}
							elsif ($table{$table}{column}{$column}{type} == 'auto') {
								$auto = $row->{$column}
							}
						}
						print "- Insert query: $insert_query\n" if ($verbose);
						print "- Values: " . join(',', @values) . "\n" if ($verbose);
						$insert->execute(@values);
						$map{$table}{$auto} = last_insert_id($last_id);
					}

					print "- Settign state of $table to done.\n" if ($verbose);
					$table{$table}{status} = 'done';
				}
			}
		}
	}
	print "Dumping database $name complete\n\n";

	print "Closing database `$name'...";
	$dbh->disconnect();
	print "done.\n";
}


sub read_table_info()
{
	my ($dbh, $table_node) = @_;
	my %table = ();

	$table{name} = $table_node->getAttributeNode('name')->getValue();
	print "Table: $table{name}\n";

	my $auto_nodes = $table_node->getElementsByTagName('auto');
	if ($auto_nodes->getLength()) {
		$table{auto} = $auto_nodes->item(0)->getAttributeNode('key')->getValue();
		print "  Auto increment column (given): $table{auto}\n";
	}
	else {
		$table{auto} = 0;
		print "  No auto increment columns\n";
	}

	print "  Reading column list.\n";
	my $q = $dbh->prepare("describe $table{name}");
	$q->execute();

	while (my $row = $q->fetchrow_hashref()) {
		if ($row->{Field} eq $table{auto}) {
			print "  Auto increment column (found): $row->{Field}\n";
			unless ($table{auto} eq $row->{Field}) {
				print "*** Auto increment column mismatch ***\n";
				exit 1
			}
		}
		else {
			print "  Normal column: $row->{Field}\n";
			$table{column}{$row->{Field}}{type} = 'normal';
		}
	}

	my $foreign_nodes = $table_node->getElementsByTagName('foreign');
	my $n = $foreign_nodes->getLength();

	for (my $i = 0; $i < $n; $i++) {
		my $foreign_node = $foreign_nodes->item($i);
		my $foreign_column = $foreign_node->getAttributeNode('column')->getValue();
		unless ($table{column}{$foreign_column}) {
			print "*** Foreign key column $foreign_column not found ***\n";
			exit 1;
		}
		$table{refers}{$foreign_column}{table} =
			$foreign_node->getAttributeNode('table')->getValue();
		unless ($table{refers}{$foreign_column}{table}) {
			print "*** Table for $foreign_column not found ***\n";
			exit 1;
		}
		$table{refers}{$foreign_column}{key} =
			$foreign_node->getAttributeNode('key')->getValue();
		unless ($table{refers}{$foreign_column}{key}) {
			print "*** Key for $foreign_column not found ***\n";
			exit 1;
		}
		$table{column}{$foreign_column}{type} = 'foreign';
		print "  Foreign key: $foreign_column => $table{column}{$foreign_column}{table}($table{column}{$foreign_column}{key})\n";
	}

	return \%table;
}

sub last_insert_id()
{
	my $last_id = shift;
	$last_id->execute();
	if (my @last_id = $last_id->fetchrow_array()) {
		return $last_id[0];
	}
	return undef;
}

