<?php
 # genreport.php - Generate a daily report.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 17/01/2005
 # Updated: 19/01/2005

# Dont allow directcall. Uses mambo variable
#defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("../common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");


$db=0;$xdb=1; #local debug options

function get_filterstat($attr,$attrfilter,$attrfilter_val){ # get filter statistic
 global $conn,$db,$xdb;
 global $attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields,$entitytable,$entitytable_fields;

 $filter_data=array();
 
 # First create a temporary table to store valid entities
 $sql="create temporary table entity(id int (11) not null, primary key (id))"; xdb($sql); mysql_query($sql,$conn);
 $sql="delete from entity"; xdb($sql); mysql_query($sql,$conn);
 
 # Get data according to filter and place in temporary table
 $sql="insert into entity (select distinct e.id from $entitytable e, $attrtable a, $attrvaltable v, $attroptiontable o where v.attribute_id=a.id and v.entity=e.id and o.attribute_id=a.id and a.name='$attrfilter' and v.value_int=o.id and o.name='$attrfilter_val')"; xdb($sql);
 mysql_query($sql,$conn);
 
 $sql="select o.caption as x, count(*) as y from $entitytable e, $attrtable a, $attrvaltable v, $attroptiontable o, entity t where v.attribute_id=a.id and v.entity=e.id and o.attribute_id=a.id and a.name='$attr' and v.value_int=o.id and e.id=t.id group by o.name"; xdb($sql);
 $rs=mysql_query($sql,$conn);
 
 $num_rows=mysql_num_rows($rs);
 for ($i=0;$i<$num_rows;$i++){
   $row=mysql_fetch_row($rs);
   #print "<br>$row[0] | $row[1]";
   $filter_data[$row[0]].=$row[1];
 }
 return $filter_data;
}

function gen_report(){ # generate report

 global $attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields,$entitytable,$entitytable_fields;
 global $dailyreporttable,$dailyreporttable_fields,$dailyreportdatatable,$dailyreportdatatable_fields;
 global $conn,$db,$xdb;
 
 # Define data arrays
 $death_arr=array();
 $injured_arr=array();
 $missing_arr=array();
 $unknown_arr=array();
 #$displaced_arr=array();
 
 
 $created="CURDATE()"; # created date
 $title="Impact of Tsunami 9.0";
 $fldlist="District|Deaths|Injured|Missing|Unknown";
 
  # First check if there are alreay a report for the day
 $sql="select * from $dailyreporttable where created=$created";
 $rs=mysql_query($sql);
 if (mysql_num_rows($rs)>0){print "Data already exists for $created so exiting";return;} # for now we dont do anything
 
 # Create a report entry 
 $sql="insert into $dailyreporttable($dailyreporttable_fields) values ('',$created,'$title','$fldlist')"; xdb($sql);
 $rs=mysql_query($sql);
 $report_id=mysql_insert_id();
 
 $death_arr=get_filterstat('district','status','missing');
 $injured_arr=get_filterstat('district','status','deceased');
 $missing_arr=get_filterstat('district','status','injured');
 $unknown_arr=get_filterstat('district','status','unknown');
 #$displaced_arr=get_filterstat('district','location','unknown');
 
 # get a list of districts
 $sql="select distinct o.name, o.caption from $attrtable a, $attrvaltable v, $attroptiontable o where v.attribute_id=a.id and o.id=v.value_int and a.name='district'";
 $rs=mysql_query($sql);
 
 print "<br>$fldlist";
 
 for ($i=0;$i<mysql_num_rows($rs);$i++){
   $row=mysql_fetch_row ($rs);
   $district=$row[1];
   $field_data="$district|$death_arr[$district]|$injured_arr[$district]|$missing_arr[$district]|$unknown_arr[$district]";
   $sql="insert into $dailyreportdatatable($dailyreportdatatable_fields) values ($report_id,'$field_data')"; xdb($sql);
   mysql_query($sql);
 }
   
  #  foreach($filter_data2 as $key2 => $value2){
  #    echo "<br>Key: $key2; Value: $value2";
  #  }
  
   
 
 
 
}

gen_report();
?>

