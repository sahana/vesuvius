#!/usr/bin/perl

require header;
require secure;

print "
<div id=\"main\">
<h2>&#187; Restart Server</h2>
<h3>Restarting...</h3>
<p>";

if ($ENV{'QUERY_STRING'}eq"M"){
  	$res=`net top mysql`;
  	$res=`net start mysql`;

  	print "<h2>The MySQL service was restarted.</h2>";
}

if ($ENV{'QUERY_STRING'}ne""){
  	print <<ENDDD;
  	<script language="JavaScript">
	<!--
  	window.location = '../../../../start.php';
  	// -->
  	</script>
  	</p>
  	</div>
ENDDD
}

if  ($ENV{'QUERY_STRING'}eq"A"){
  	print "<h2>The Apache service was restarted.</h2>";

  	$res=`net stop Apache2`;
  	exec "net start Apache2";
  	exit;
}

print <<ENDDD;
This script will restart the services.
<br />
It may take some time.
<br />
<br />
I am sure: <a href="$ENV{SCRIPT_NAME}?A">Restart Apache2 Service</a>
<br />
I am sure: <a href="$ENV{SCRIPT_NAME}?M">Restart MySQL Service</a>
</p>
</div>
ENDDD

require footer;

exit;