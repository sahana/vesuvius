<?php
 # stats.php - Statistics page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 31/12/2004
 # Updated: 06/01/2005

# Dont allow directcall. Uses mambo variable
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

 // Site configuration
require_once("common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");


// Include commin Stats functions 
require_once ("$webroot/stats/inc_stats.php");

$db=0;$xdb=0; #local debug options


function get_attribute($publicity_level=1){ # Get a list of attributes
 global $attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields;
 
 $cont=''; $crit="publicity>=$publicity_level AND search=1";
 $val=$_REQUEST['attribute'];
 $fname='attribute'; $width='10'; $fldset="id,caption";
 
 $crit = "name IN ('age','gender','province','city','marital_status','country','race','religion')";
 $cont=dbsel($val,$fname,$width,$attrtable,$fldset,$crit); # commented since we dont need all atts

 
 return $cont; 
}

function get_filter($publicity_level=1){ # Get a list of filters
 global $attrtable,$attrtable_fields,$attrvaltable,$attrvaltable_fields;
 global $attroptiontable,$attroptiontable_fields;
 
 $cont=''; $crit="publicity>=$publicity_level AND search=1";
 $val=$_REQUEST['attribute'];
 $fname='attribute'; $width='10'; $fldset="id,caption";
 
 # $cont=dbsel($val,$fname,$width,$attrtable,$fldset); # commented since we dont need all atts
 $cont="<select name=\"filter\" width=\"10\">
 <option value=\"0\">Please select a filter</option>
 <option value=\"4\">Age</option>
 <option value=\"6\">Province/state</option>
 <option value=\"12\">Country</option>
 <option value=\"13\">Race</option>
 <option value=\"14\">Religion</option>
 </select>";
 
 $cont=preg_replace ("/<option[ ]+value\=\"$val\"/","<option value\=\"$val\" selected",$cont);
 return $cont; 
}

function graphtype_sel($val){ # Displays the graph type drop
  $cont="<select name=\"graph_type\" width=\"10\">
  <option value=\"pie\">Pie Graph</option>
  <option value=\"bars\">Bar Graph</option>
  </select>";

  $cont=preg_replace ("/<option[ ]+value\=\"$val\"/","<option value\=\"$val\" selected",$cont);
  return $cont; 

}

function dispunknown_chk($val){ # Displays the unknown tick
  $cont="<input type=\"checkbox\" name=\"disp_unknown\" value=\"1\" checked>Display Unknown";

  if(!($val>0)){$cont=preg_replace ("/checked/","",$cont);}
  return $cont; 

}

function print_statdata($attr_id){ # Prints stat data
 global $maxstatsize;
 
$cont='';
$statattrdata=array(); # Store the stats in an array
$statattrvaldata=array();
$statoptiondata=array(); 
list($num_rows,$total_entities)=get_statdata($attr_id,$statattrdata,$statattrvaldata,$statoptiondata); 

$cont="<table  width=200 class=\"stat_table\" cellspacing=0 cellpadding=0><tr><td colspan='2' align='center' class=\"bottomBorder\"><b>$attr_name</b></td></tr>
 <tr><td class=\"rightBorder bottomBorder\">Value</td><td class=\"bottomBorder\">Frequency</td></tr>";

 $attr_count=0; $other_count=0; # Used to track the frequency of other options once we pass $maxstatsize
 
for ($i=0;$i<count($statattrdata);$i++){
   #$row[0] = $statattrdata[$i]; $row[1]=$statattrvaldata[$i];
   if($statattrdata[$i] && $i<$maxstatsize){ 
     if (preg_match("/other/i",$statattrdata[$i])){
       $other_count+=$statattrvaldata[$i];
     }else{
       $cont.="<tr><td class=\"rightBorder\">".(isset($statoptiondata[$statattrdata[$i]])?$statoptiondata[$statattrdata[$i]]:$statattrdata[$i])."</td><td>$statattrvaldata[$i]</td>"; 
     }
   }else{ $other_count+=$statattrvaldata[$i]; }
   $attr_count+=$statattrvaldata[$i];
 }
 
 if($other_count>0){$cont.="<tr><td class=\"rightBorder\">Other</td><td>$other_count</td></tr>"; }
 if($total_entities>0 && $_REQUEST['disp_unknown']){$cont.="<tr><td class=\"rightBorder\">Unknown</td><td>".($total_entities-$attr_count)."</td></tr>"; }
 $cont.="</table>"; 

  if ($num_rows>1){return $cont;} # return rable only if there are records
  
}

# Replace template TAGS with values
$page_cont=get_page($content_template);
$page_cont=preg_replace("/{SELF}/",$_SERVER['PHP_SELF'],$page_cont);
$page_cont=preg_replace("/{ATTR_LIST}/",get_attribute(),$page_cont);

if($_REQUEST['attribute']){
  $page_cont=preg_replace("/{STAT_TABLE}/",print_statdata($_REQUEST['attribute']),$page_cont);
  $page_cont=preg_replace("/{PIE_GRAPH}/","<img src=\"$docroot/graph.php?attribute=$_REQUEST[attribute]&width=475&height=220&graph_type=$_REQUEST[graph_type]&disp_unknown=$_REQUEST[disp_unknown]\">",$page_cont);
  #### $page_cont=preg_replace("/{FILTER_LIST}/",get_filter(),$page_cont); ##working on it 
  $page_cont=preg_replace("/{FILTER_LIST}/",'',$page_cont);
  $page_cont=preg_replace("/{GRAPH_TYPE}/",graphtype_sel($_REQUEST['graph_type']),$page_cont);
  $page_cont=preg_replace("/{UNKNOWN_CHK}/",dispunknown_chk($_REQUEST['disp_unknown']),$page_cont);
}else{
 $page_cont=preg_replace("/{[^\}]+}/",'',$page_cont);
}

#$page_cont=preg_replace("/{HIDDEN_FIELDS}/","<input type=hidden name=mode value='$nextmode'><input type=hidden name=nextpg value='$nextpg'>",$page_cont);

print $page_cont;
?>

