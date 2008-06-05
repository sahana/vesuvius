#!/usr/bin/perl

require header;
require secure;

print "
<div id=\"main\">
<h2>&#187; Stop MySQL</h2>
<h3>Stopping MySQL</h3>
<p>";

&check_mysql;
if ($run) {
  	&stop_mysql;
  	print "MySQL server stopped.<br>";
} 

else {
  	if ($ENV{'QUERY_STRING'}eq"F"){
		&stop_mysql;
		print "MySQL server was forced to stop.";
		print "<br>";
  	} 

  	else {
		print <<ENDDD;
		MySQL server was not running.
		<br />
		But if you think that it is a mistake click on this <a href="$ENV{SCRIPT_NAME}?F">link</a>
		<br />
ENDDD
  	}
}

print <<ENDDD;
</p>
</div>
ENDDD

require footer;

exit;

sub check_mysql(){
 	$res = system "\\home\\admin\\program\\pskill.exe", "mysqld-opt.exe";
 	if ($res == 0){$run=1} 
	else {$run=0}
}
sub stop_mysql(){
  	open (PASS,"../../../../mysql_password");
  	$password=<PASS>;
  	close (PASS);
  	system "/home/admin/program/uniserv.exe \"\\usr\\local\\mysql\\bin\\mysqladmin.exe --user=root --password=$password shutdown\"";
}