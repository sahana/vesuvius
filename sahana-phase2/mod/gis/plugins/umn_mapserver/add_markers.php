<?php
/** 
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
session_start();
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
    <html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
    <head>
        <title><?=_($title)?></title>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <link rel="stylesheet" media="screen, projection" type="text/css" href="theme/<?=$theme?>/sahana.css" />
	<link rel="stylesheet" media="print" type="text/css" href="theme/<?=$theme?>/print.css" />
	<link rel="stylesheet" media="handheld" type="text/css" href="theme/<?=$theme?>/mobile.css" />
    <script type="text/javascript" src="theme/<?=$theme?>/sahana.js"></script> 
    <script type="text/javascript" src="res/js/popup.js"></script> 
    <script type="text/javascript" src="index.php?stream=text&amp;mod=xst&amp;act=help"></script>
  	</head>
  	<body>
<?php

	$approot = $_REQUEST['approot'];
	$mapfile = $_REQUEST['mapfile'];
	
	//Load the dynamic library.
	dl('php_mapscript.so');
	//dl('php_mapscript_42.dll'); //For WinDoS Users
	
	$map_path="$approot"."mod/gis/plugins/umn_mapserver/map/";
	
	global $map;
	$map= ms_newMapObj($map_path.$mapfile);
	
	if ( isset($_POST["mapa_x"]) && isset($_POST["mapa_y"])) {
      $extent_to_set = explode(" ",$_POST["extent"]); 
      $map->setextent($extent_to_set[0],$extent_to_set[1],
                      $extent_to_set[2],$extent_to_set[3]);
      $my_point = ms_newpointObj();
      $my_point->setXY($_POST["mapa_x"],$_POST["mapa_y"]);
      $my_extent = ms_newrectObj();
      $my_extent->setextent($extent_to_set[0],$extent_to_set[1],
                              $extent_to_set[2],$extent_to_set[3]);

      switch($_POST['map_control']){
      	case 'zo':
      			$map->zoompoint(-2,$my_point,$map->width,$map->height,$my_extent);
      			break;
      	case 'zi':
      			$map->zoompoint(2,$my_point,$map->width,$map->height,$my_extent);
      			break;
      	case 'pan':
      			break;
      	default:
      			//Convert pixels to map units
				$map_pt = click2map($_POST["mapa_x"],$_POST["mapa_y"],$map->extent);
				//Create the point
				$pt = ms_newPointObj();
				$pt-> setXY($map_pt[0],$map_pt[1]);
				
				$_SESSION['loc_x']=$map_pt[0];
				$_SESSION['loc_y']=$map_pt[1];
				
				$click=true;
      			break;
      }
	  
    }
    $image=$map->draw();
    
    if($click){
		$layer = $map->getLayerByName('INLINE');
		$pt->draw($map, $layer, $image, 0 ,'yuhuu');
		$click=false;
		//print_r($pt);
		//print_r($_POST);
	}
	$image_url=$image->saveWebImage();
	
	$extent_to_html = $map->extent->minx." ".$map->extent->miny." "
		.$map->extent->maxx." ".$map->extent->maxy;
	
?>
	<div id="formcontainer">
		<form method="post" action="" id="formset" name="">
		<fieldset>
		<legend>Map Controls</legend>
		<label>Control</label>
		<input type="radio" name="map_control" value="zi" />Zoom In
		<input type="radio" name="map_control" value="zo" />Zoom Out
		<input type="radio" name="map_control" value="zo" />Pan
		<br />
		</fieldset>
		<fieldset>
		<input type="image" name="mapa" src="<?=$image_url?>">
		<input type="hidden" name="approot" value="<?=$approot?>">
		<input type="hidden" name="map" value="<?=$mapfile?>">
		<input type="hidden" name="extent" value="<?=$extent_to_html?>">
		</fieldset>
		<input type="button" name="map_done" value="Finish">
	</div>
< pre>
<!-- Debug Lines -->
<?php
echo "GET\n";
print_r($_GET);
echo "Point:\n";
print_r($pt); 
//var_dump($_SESSION);
?>
  </body>
 </html>
 
<?php
/**
 *Convert pixels to map units (got from PHPMapscriptSnippet1)
 */
function click2map ($click_x, $click_y,$map) {
    global $map;
    $e= &$map->extent; //for saving writing
    $x_pct = ($click_x / $map->width);
    $y_pct = 1 - ($click_y / $map->height);
    $x_map = $e->minx + ( ($e->maxx - $e->minx) * $x_pct);
    $y_map = $e->miny + ( ($e->maxy - $e->miny) * $y_pct);

    return array($x_map, $y_map);
}
?>
