<?php
 # qreports.php - Quick report generation flat table dump scipt.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 17/01/2005
 # Updated: 16/02/2005

# Dont allow directcall. Uses mambo variable
#defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("../common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");


$db=0;$xdb=1; #local debug options

$peopletable='people_person2';

function get_option_name_by_attr($attr_id,$value_int){
  global $conn,$xdb;
  
  #$sql="select name from sahana_attribute_options  where attribute_id=$attr_id and id=$value_int"; xdb($sql);
  $sql="select name from sahana_attribute_options  where  id=$value_int"; xdb($sql);
  $rs=mysql_query($sql);
  if (mysql_num_rows($rs)>0){
    $row=mysql_fetch_row($rs);
    return $row[0];
  }
  return $value_int;
}

function create_temp_table(){
  global $conn,$xdb,$peopletable;
  
  $sql="select distinct a.name as attribute from sahana_attributes a, sahana_attribute_values v where v.attribute_id=a.id order by a.name"; xdb($sql);
  $rs=mysql_query($sql);
  
  #$sql='create temporary table t,mp (id int(10) not null,';
  $sql='create table $peopletable (report_id int(10) not null,entity_id int(10) not null,family_entity_id int(10),';
  for ($i=0;$i<mysql_num_rows($rs);$i++){
    $row=mysql_fetch_array($rs);
    $sql.=$row[0].' varchar(250),';
  }
  $sql=preg_replace("/\,$/",'',$sql);
  $sql.=")"; xdb($sql);
  mysql_query($sql);
  
}

create_temp_table();

# select v.report_id as report_id, e.id as entity_id, a.id as attributeid, a.name as attribute, v.value_int, v.value_string from sahana_entities e, sahana_attributes a, sahana_attribute_values v where v.attribute_id=a.id and v.entity=e.id order by v.report_id;

#$sql="select e.id, a.id as attributeid, a.name as attribute, v.value_int, v.value_string from sahana_entities e, sahana_attributes a, sahana_attribute_values v where v.attribute_id=a.id and v.entity=e.id order by e.id"; xdb($sql);
$sql="select max(entity_id) from $peopletable";
$rs=mysql_query($sql);
$row=mysql_fetch_row($rs);
$max_entity_id=($row[0]=='')?0:$row[0];

$sql="select v.report_id as report_id, e.id as entity_id, a.id as attributeid, a.name as attribute, v.value_int, v.value_string from sahana_entities e, sahana_attributes a, sahana_attribute_values v where e.entity_type=1 and v.attribute_id=a.id and v.entity=e.id and e.id>$max_entity_id order by e.id"; xdb($sql);

$rs=mysql_query($sql);

$sql='';

$cont="<table border=1>
<tr><td>reportid</td><td> entityid</td><td>attributeid</td><td>attribute</td><td>attr_value</td></tr>";

$entity_id=0; $report_id=0;
for ($i=0;$i<mysql_num_rows($rs);$i++){
  $row=mysql_fetch_array($rs);
  
  if($entity_id!=$row['entity_id']){
     $entity_id=$row['entity_id'];
     
     # Get family_entity_id
     $sql="select er.related_id as family_entity_id from sahana_entities e, sahana_entity_relationships er where er.relation_type=3 and er.entity_id=e.id and e.id=$entity_id"; xdb($sql); 
     $rs2=mysql_query($sql);
     $row2=mysql_fetch_row($rs2);
     
     $row2[0]=($row2[0]>0)?$row2[0]:'NULL';
     $sql="insert into $peopletable(entity_id,family_entity_id) values ($row[entity_id],$row2[0])"; xdb($sql); 
     mysql_query($sql);
  }
  
  $attr_value=($row['value_int'])?get_option_name_by_attr($row['attributeid'],$row['value_int']):$row['value_string'];
  
  $sql="update $peopletable set report_id=$row[report_id],$row[attribute]='$attr_value' where entity_id=$row[entity_id]"; xdb($sql); mysql_query($sql);
     
  
  $cont.="<tr><td> $row[report_id]</td><td> $row[entity_id]</td><td> $row[attributeid]</td><td> $row[attribute]</td><td>&nbsp; $attr_value</td></tr>";
}
$cont.="</table>";

#print $cont;

?>

