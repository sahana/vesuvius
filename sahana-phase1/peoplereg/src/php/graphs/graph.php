<?php
# graph.php - Graph Statistics page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 31/12/2004
 # Updated: 05/01/2005

 // Site configuration
require_once("common/site@config.php");

// Database support
require_once ("$webroot/common/db@connect.php");

//Include plot code
include("$webroot/stats/phplot.php");

// Include commin Stats functions 
require_once ("$webroot/stats/inc_stats.php");

$db=0;$xdb=0; #local debug options


function draw_graph($attr_id,$width,$height,$graph_type='pie',$disp_unknown=1){ # Draw a graph
global $maxstatsize;

$cont='';
$statattrdata=array(); # Store the stats in an array
$statattrvaldata=array();
$statoptiondata=array(); 
list($num_rows,$total_entities)=get_statdata($attr_id,$statattrdata,$statattrvaldata,$statoptiondata); 

# Build graph data array
$graph_data=array();
$graph_data[0]=array();
$graph_data[0][0]=' ';
$graph_legend=array();

$attr_count=0; $other_count=0; # Used to track the frequency of other options once we pass $maxstatsize
 
for ($i=0;$i<count($statattrdata);$i++){
   #$row[0] = $statattrdata[$i]; $row[1]=$statattrvaldata[$i];
   if($statattrdata[$i] && $i<$maxstatsize){
      if (preg_match("/other/i",$statattrdata[$i])){
       $other_count+=$statattrvaldata[$i];
      }else{ 
        $graph_data[0][$i+1]=$statattrvaldata[$i];
        $graph_legend[$i]=(isset($statoptiondata[$statattrdata[$i]])?$statoptiondata[$statattrdata[$i]]:$statattrdata[$i]); 
      }
   } else{ $other_count+=$statattrvaldata[$i]; }
   $attr_count+=$statattrvaldata[$i];
 }
  
 if($other_count>0){
   array_push($graph_data[0],$other_count);  
   $graph_legend[$i]='Other'; 
 }
 if($num_rows>1 && $total_entities>0 && $disp_unknown){
   array_push($graph_data[0],$total_entities-$attr_count);  
   $graph_legend[$i+1]='Unknown'; 
 }
 
 // See if we didnt get any data
 if(count($graph_data[0])>2){ # We did get any records
    //Define the graph object
   
   if($width>0 && $height>0){ 
     $graph =& new PHPlot($width,$height);
   }else{
    $graph =& new PHPlot($width,$height);
   }

  $graph_type=($graph_type=='bars')?'bars':'pie';
  $graph->SetPlotType($graph_type);
  ##911 $graph->SetTitle("$attr_name Distribution");
  $graph->SetLegend($graph_legend);
  
  if($graph_type=='bars'){
    $graph->SetXGridLabelType("title");
    $graph->SetNumHorizTicks(1);
    $graph->SetYLabel("Frequency");
  }
  #$graph->SetLegendPixels($width-70,1);
    
  $graph->SetDataValues($graph_data);
  
  //Draw it
  $graph->DrawGraph();
 }else{
  $handle = fopen ("images/empty.png", "rb");
  $cont = fread ($handle, filesize ("images/empty.png"));
  fclose ($handle);
  print $cont;
 }
 
}

if ($_REQUEST['attribute']) {draw_graph($_REQUEST['attribute'],$_REQUEST['width'],$_REQUEST['height'],$_REQUEST['graph_type'],$_REQUEST['disp_unknown']); }
?>