#!/usr/bin/perl

##### ERROR LOG FILE LOCATION #####
# 
$logfile = "/usr/local/apache2/logs/error.log";
#
###################################

require header;
require secure;

print "
<div id=\"main\">
<h2>&#187; Error Log Viewer</h2>
<h3>Viewing Error Log File</h3>
<p>";

open (LOG, "$logfile")|| die "Can't open data file!\n";
@log = <LOG>;
close (LOG);

@log=reverse(@log);
splice @log, 4096;

foreach $logs (@log) {
  	print "- $logs <br />";
}

print "
</p>
</div>";

require footer;

exit;
