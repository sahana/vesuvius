<?php
 # site@config.php - Side wide configuration info.
 # Author: Buddhika Siddhisena [Bud@babytux.org]
 # Created: 31/12/2004
 # Updated: 17/01/2005

$webroot = '/var/www/mambo/sahana';

$docroot = '/mambo/sahana';
#$docroot = '';

#-- print debug info --
$db=1; $xdb=1;
function db($msg){global $db;if($db) echo("<br><font color=\"#EE0000\">$msg</font>");}
function xdb($msg){global $xdb;if($xdb) echo("<br><font color=\"#1100BB\">$msg</font>");}


#-- database config --
$host = "localhost";
$dbuser="dbuser"; $dbpassword="dbpassword";

$database="mambo";

$attrtable = 'sahana_attributes';
$attrtable_fields = 'id,name,caption,data_type,publicity,search';
$attrvaltable = 'sahana_attribute_values';
$attrvaltable_fields = 'entity,report_id,attribute_id,value_int,value_string';
$attroptiontable = 'sahana_attribute_options';
$attroptiontable_fields = 'id,attribute_id,name,caption';
$entitytable = 'sahana_entities';
$entitytable_fields = 'id';
$dailyreporttable='sahana_daily_report';
$dailyreporttable_fields='report_id,created,title,field_heading';
$dailyreportdatatable='sahana_dailyreport_data';
$dailyreportdatatable_fields='report_id,field_data';


$resperpage=10; #results per page

#-- Application Config
$rowaltcolor='#EEEEEE';
$maxstatsize = 5; # Maximum number of statics labels to show

?>
