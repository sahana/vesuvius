<?php
 # inc_stats.php - Statistics include functionality
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 05/01/2005
 # Updated: 05/01/2005


function attrclass(&$statattrdata,&$statattrvaldata,$num_classes=1){ # generate a group of class data
  $max=max($statattrdata);
  $min=min($statattrdata);
  
  $classwidth=(int)(($max-$min)/$num_classes);
  
  $aggr_data=array();
  
  for ($i=$min;$i<$max;$i+=$classwidth){
      $tag="$i - ".($i+$classwidth-1);
      $aggr_data[($i+$classwidth-1)]=0;
  }
  
  for ($i=0;$i<count($statattrdata);$i++){
    $aproxclass = ceil($statattrdata[$i]/$classwidth);
    $indx=$aproxclass*$classwidth;
    $aggr_data[$indx]+=$statattrvaldata[$i];
  }
  
  $i=0;
  $statattrdata=array(); $statattrvaldata=array();  # Reset the array index to 0
  foreach ($aggr_data as $key => $value){
   $tag=($key-$classwidth+1)." - ".$key;
   $statattrdata[$i]=$tag;
   $statattrvaldata[$i]=$value; $i++;
  }
  
}

function get_statdata($attr_id,&$statattrdata,&$statattrvaldata,&$statoptiondata){
 global $conn,$db,$xdb;
 global $attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields,$entitytable,$maxstatsize;
 
 $num_rows=0;
 
 $attr_type=0;$attr_name='';
 if(get_data($attrtable,"data_type,caption",'x',"id=$attr_id")){$attr_type=$GLOBALS{'xdata_type'};$attr_name=$GLOBALS{'xcaption'};}
 
 # Get a list of options
 $sql = "SELECT $attroptiontable_fields FROM $attroptiontable WHERE attribute_id=$attr_id"; xdb($sql);
 $rs=mysql_query($sql);
 $num_rows=mysql_num_rows($rs);
 
 for ($i=0;$i<$num_rows;$i++){
   $row=mysql_fetch_array($rs);
   $statoptiondata[$row['id']]=$row['caption'];
 } 
 
 # Get total number of records
 $sql = "SELECT COUNT(*) FROM $entitytable"; xdb($sql);
 $rs = mysql_query($sql);
 
 $total_entities=0;
 if(mysql_num_rows($rs)==1){$row=mysql_fetch_row($rs); $total_entities=$row[0];}
 
 # Attr frequency
 $value_tag=($attr_type==1)?'value_string':'value_int';
 $sql = "SELECT  $value_tag,count($value_tag) AS freq FROM $attrvaltable WHERE attribute_id=$attr_id GROUP BY $value_tag ORDER BY freq DESC"; xdb($sql);
 $rs=mysql_query($sql);
 $num_rows=mysql_num_rows($rs);
 
 
 for ($i=0;$i<$num_rows;$i++){
   $row=mysql_fetch_row($rs);
   $statattrdata[$i]=$row[0];
   $statattrvaldata[$i]=$row[1];      
 }
 
 # If we need to convert data in to classes (ranges)
 if($attr_type==0 && count($statoptiondata)==0){
   $attrclass_arr=array();
   $attrclass_arr=attrclass($statattrdata,$statattrvaldata,$maxstatsize);
   $maxstatsize++;  # increase the maxstatsize since we have already controlled the output by grouping
 }
 
 return array($num_rows,$total_entities);
 
}
?>