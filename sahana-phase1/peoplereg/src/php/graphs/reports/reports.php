<?php
 # reports.php - Daily reports page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 17/01/2005
 # Updated: 20/01/2005

# Dont allow directcall. Uses mambo variable
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");


$db=0;$xdb=0; #local debug options

function getReport($created=''){ # gets a daily report
  global $conn,$cont,$content_template,$dailyreporttable,$dailyreporttable_fields,$dailyreportdatatable,$dailyreportdatatable_fields;
  
  $cont=''; $report_id='';
  $created=($created)?$created:"CURDATE()";
  
  # Replace template TAGS with values
  $page_cont=get_page($content_template);
  $page_cont=preg_replace("/{SELF}/",$_SERVER['PHP_SELF'],$page_cont);

  $table=$dailyreporttable; $fldset=$dailyreporttable_fields; $crit="created=$created";
  if(get_data($table,$fldset,'x',$crit)){
    $page_cont=preg_replace("/{REPORT_TITLE}/",$GLOBALS{'xtitle'},$page_cont);
    $page_cont=preg_replace("/{REPORT_DATE}/",$GLOBALS{'xcreated'},$page_cont);
  
    $table=$dailyreportdatatable; $fldset=$dailyreportdatatable_fields; $crit="report_id=".$GLOBALS{'xreport_id'};
    $sort="field_data asc";
    
    $cont="<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"540\">
    <tr bgcolor=\"#CCCCCC\"><td>District</td><td>&nbsp;</td><td>Deaths</td><td>&nbsp;</td><td>Injured</td><td>&nbsp;</td><td>Missing</td><td>&nbsp;</td><td>Unknown</td><td>&nbsp;</td></tr>";
    get_data($table,$fldset,'',$crit,$sort,'report_row');
    $cont.="</table>";
     
  }
  
   # Replace content
   $page_cont=preg_replace("/{REPORT_CONT}/",$cont,$page_cont);
  
   # Remove any remaining TAGS
   $page_cont=preg_replace("/{[^\}]+}/",'',$page_cont);

  return $page_cont;
}

function report_row($row){
 global $cont,$altcolor,$rowaltcolor;

 $altcolor=($altcolor=='#FFFFFF')?$rowaltcolor:'#FFFFFF';
 #$orderdate=date("d-M-y h:i a",$row['created']);

  list($district,$deaths,$injured,$missing,$unknown)=preg_split("/\|/",$row['field_data']);
  $deaths=($deaths)?$deaths:0;
  $injured=($injured)?$injured:0;
  $missing=($missing)?$missing:0;
  $unknown=($unknown)?$missing:0;
  
  $cont.="<tr bgcolor=\"$altcolor\"><td>$district</td><td>&nbsp;</td><td>$deaths</td><td>&nbsp;</td><td>$injured</td><td>&nbsp;</td><td>$missing</td><td>&nbsp;</td><td>$unknown</td><td>&nbsp;</td></tr>\n";
}


#$page_cont=preg_replace("/{HIDDEN_FIELDS}/","<input type=hidden name=mode value='$nextmode'><input type=hidden name=nextpg value='$nextpg'>",$page_cont);

print getReport();
?>

