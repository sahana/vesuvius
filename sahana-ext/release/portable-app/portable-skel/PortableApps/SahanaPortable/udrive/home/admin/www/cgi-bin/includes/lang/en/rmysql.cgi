#!/usr/bin/perl

require header;
require secure;

print "
<div id=\"main\">
<h2>&#187; Start MySQL</h2>
<h3>Starting MySQL</h3>
<p>";

&check_mysql;
if ($run) {
  	if ($ENV{'QUERY_STRING'}eq"F"){
		&start_mysql;
		print "MySQL server was forced to start.";
		print "<br />";
  	}

  	else {
		print <<ENDDD;
		MySQL server already running.
		<br />
		But if you think that it is mistake click on this <a href="$ENV{SCRIPT_NAME}?F">link</a>
		<br />
		</p>
 		</div>
ENDDD
  	}
} 

else {
  	print <<ENDDD;
  	MySQL server started.
  	</p>
  	</div>
ENDDD
  	require footer;
  	&start_mysql;
}

require footer;

exit;

sub check_mysql(){
 	$res = system "\\home\\admin\\program\\pskill.exe", "mysqld-opt.exe";
 	if ($res == 0){$run=1} 
	else {$run=0}
}

sub start_mysql(){
 	exec "/usr/local/mysql/bin/mysqld-opt.exe --defaults-file=/usr/local/mysql/bin/my-small.cnf\"";
}