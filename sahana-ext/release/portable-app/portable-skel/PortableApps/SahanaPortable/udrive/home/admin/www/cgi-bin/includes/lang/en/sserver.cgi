#!/usr/bin/perl

require header;
require secure;

print <<ENDDD;
<div id="main">
<h2>&#187; Shutdown Server</h2>
<h3>Shutting Down Server</h3>
<p>
The server is shutting down.
<br />
<br />
Thank you for using <a href="http://www.uniformserver.com/">The Uniform Server</a>.<br />
<br />
</p>
</div>
ENDDD

$res = system "\\home\\admin\\program\\pskill.exe", "mysqld-opt.exe";

if ($res == 0){
  	open (PASS,"../../../../mysql_password");
  	$password=<PASS>;
  	close (PASS);
  	system "/home/admin/program/uniserv.exe \"\\usr\\local\\mysql\\bin\\mysqladmin.exe --user=root --password=$password shutdown\"";
}

exec "\\home\\admin\\program\\pskill Apache.exe c";

require footer;
exit;
