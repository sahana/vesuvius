	<?php
/**
 * $id$;
 * Google Maps plugin for Sahana GIS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    module
* @subpackage google_maps
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function initialize_map(){
	global $global;
	global $conf;
	$db=$global['db'];
	/*
	$q="select value from config where module_id='gis' and confkey='google_key'";
	$res=$db->Execute($q);
	$key=$res->fields[0];
	*/
	//$key=$conf['gmap_key'];
	$key = $conf['mod_gis_google_key'];
?>
		<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $key?>" type="text/javascript"></script>
		<div id="map" style="width: 500px; height: 400px"></div>

<?php
}

function init_map($gmap_key){
?>
		<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $gmap_key?>" type="text/javascript"></script>
		<div id="map" style="width: 500px; height: 400px"></div>

<?php
}
function init_gmap(){
?>
		<script src="http://maps.google.com/maps?file=api&v=1&key=ABQIAAAAb-bE-ljr4-6Hsb4x92lWhRT2yXp_ZAY8_ufC3CFXhHIE1NvwkxQTjccCsxIjr0poUEEARUZJgolNfw" type="text/javascript"></script>

<?php
}

function load_map($x='',$y=''){
?>
<script type="text/javascript">
	
		   //<![CDATA[
       var map = new GMap(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
       //map.addControl(new GSmallMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch
<?php
		if($x=='' || $y==''){
?>
       	map.centerAndZoom(new GPoint(79.5, 8.5338), 10);
<?php
		}
		else{
?>
				map.centerAndZoom(new GPoint(<?php echo $x?>,<?php echo $y?>), 10);
<?php
		}
?>
			 	//map.centerAndZoom(new GPoint(<?php echo $x?>,<?php echo $y?>), 4);<?php ;?>
       //map.centerAndZoom(new GPoint(79.8000, 7.4419),8);

			 //add marker test
			 //var point1 = new GPoint(-122.1419, 37.4419);
			 //var marker1 = new GMarker(point1);
			 //map.addOverlay(marker1);
       //]]>
	</script>
<?php
   //end_page();
}

function load_map_v2($x='',$y=''){
?>
<script type="text/javascript">
	
		   //<![CDATA[
       var map = new GMap2(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
       //map.addControl(new GSmallMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch
<?php
		if($x=='' || $y==''){
?>
       	map.setCenter(new GLatLng(79.5, 8.5338), 10);
<?php
		}
		else{
?>
				map.setCenter(new GLatLng(<?php echo $x?>,<?php echo $y?>), 10);
<?php
		}
?>
			 	//map.centerAndZoom(new GPoint(<?php echo $x?>,<?php echo $y?>), 4);<?php ;?>
       //map.centerAndZoom(new GPoint(79.8000, 7.4419),8);

			 //add marker test
			 //var point1 = new GPoint(-122.1419, 37.4419);
			 //var marker1 = new GMarker(point1);
			 //map.addOverlay(marker1);
       //]]>
	</script>
<?php
   //end_page();
}

/*
 * add existing markers from db
*/
function add_marker_db($x,$y,$name)
{
?>
  <script type="text/javascript">
		var point1 = new GPoint(<?php echo $x?>,<?php echo $y?>);
		var marker1 = new GMarker(point1);
		//marker1.openInfoWindowHtml(<?php echo $name?>);
		map.addOverlay(marker1);
	</script>
<?php
}

/*
 * add existing markers from db
*/
function add_marker_db_v2($x,$y,$name)
{
?>
  <script type="text/javascript">
		var point1 = new GLatLng(<?php echo $x?>,<?php echo $y?>);
		var marker1 = new GMarker(point1);
		//marker1.openInfoWindowHtml(<?php echo $name?>);
		map.addOverlay(marker1);
	</script>
<?php
}

/*
 * add wiki markers from db
 * used
*/
function add_wiki_marker_db($x,$y,$name)
{
}

/*
 * click and add markers
*/
function add_marker($name)
{

}

function add_marker_out($name)
{

}

/**
 * info on existing markers
*/
function info_event($query_results){
?>			 
<?php
}

/**
 * Show zoom and pan
 */
function toolbar()
{
	global $global;
	include_once $global['approot']."/inc/lib_form.inc";
	if(!isset($category))
		$category="all";
	
	//$type_help="Help Me";
	
	shn_form_fopen("show",null,array('req'=>false));
	shn_form_fsopen("Controls");
	
	$zoom_array=array();
	$zoom_array["1"]=_("Zoom In");
	$zoom_array["-1"]="Zoom Out";
	
	//shn_form_select($zoom_array,_("Zoom Level"),null);
	shn_form_radio($zoom_array,_("Control"),"map_control");
	shn_form_fsclose();
	shn_form_submit(_("Filter"));
	shn_form_fclose();
}

/**
 * Show Map
 * @TODO: handle windows dll
 * with zoom
 */
function show_map($opt=null)
{
	global $global;
	global $conf;
	//var_dump($_POST);
	dl("php_mapscript.so");
	//$map_file="./hello.map";
	$map_path="{$global['approot']}/mod/gis/plugins/umn_mapserver/map/";
	$map_file="usa1.map";
	
	global $map;
	$map = ms_newMapObj($map_path.$map_file);
	
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
				$click=true;
      			break;
      }
	  
    }
	$layer_array= $map->getAllLayerNames();
	//echo $val[1];
	//echo count($val);
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
	
	include_once $global['approot']."/inc/lib_form.inc";
	//shn_form_fopen("show",null,array('req'=>false));
?>
	<div id="formcontainer">
		<form method="post" action="" id="formset" name="">
<?php
	shn_form_fsopen(_("Map Controls"));
	
	$zoom_array=array();
	$zoom_array["zi"]=_("Zoom In");
	$zoom_array["zo"]=_("Zoom Out");
	$zoom_array["pan"]=_("Pan");
	
	//shn_form_select($zoom_array,_("Zoom Level"),"zoom");
	shn_form_radio($zoom_array,_("Control"),"map_control");
	shn_form_fsclose();
	shn_form_fsopen("Layers");
	for($i=0;$i<count($layer_array);$i++){
		shn_form_checkbox("$layer_array[$i]","$layer_array[$i]",null,array('br'=>true));
	}
	//shn_form_checkbox("name","valu");
	shn_form_fsclose();
	shn_form_fsopen("Map");
?>
	<input type="image" name="mapa" src="<?=$image_url?>">
	<input type="hidden" name="extent" value="<?=$extent_to_html?>">
<?php
	shn_form_fsclose();
	//shn_form_submit(_("Re-Draw"));
	shn_form_fclose();

}

/**
 * Show Map
 * @TODO: handle windows dll
 */
function show_map_no_zoom($opt=null)
{
	global $global;
	global $conf;
	
	toolbar();
	dl("php_mapscript.so");
	//$map_file="./hello.map";
	$map_path="{$global['approot']}/mod/gis/plugins/umn_mapserver/map/";
	$map_file="usa1.map";
	
	$map = ms_newMapObj($map_path.$map_file);
	$image=$map->draw();
	$image_url=$image->saveWebImage();
?>

<div id="map" style="width: 500px; height: 400px">
	<img src="<?php echo $image_url?>">
</div>
<?
}

/**
 * Show map layers
 * get layer information dynamically
 */
function show_map_layers(){}

function show_map_with_markers($markers)
{

}

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

/**
 * show map with marker addition event
 * allows people to enter markers over google map
 * currently used
 */
function show_add_marker_map($name)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['mod_gis_google_key'];
	
	//Load the dynamic library.
	dl('php_mapscript.so');
	//dl('php_mapscript_42.dll'); //For WinDoS Users
	
	//$map_file="./hello.map";
	$map_path="{$global['approot']}/mod/gis/plugins/umn_mapserver/map/";
	$map_file="usa1.map";
	
	$map = ms_newMapObj($map_path.$map_file);
	

	//Convert pixels to map units
	$map_pt = click2map($_GET['mapa_x'],$_GET['mapa_y'],$map->extent);
	//Create the point
	$pt = ms_newPointObj();
	$pt-> setXY($map_pt[0],$map_pt[1]);

	//Draw the map and add the point
	$img = $map->draw();
	$layer = $map->getLayerByName('INLINE');
	$pt->draw($map, $layer, $img, 0 ,'yuhuu');
	$url = $img->saveWebImage();

	include_once $global['approot']."/inc/lib_form.inc";
	//shn_form_fopen("show",null,array('req'=>false));
?>
	<div id="formcontainer">
		<form method="get" action="" id="formset" name="">
		<input type="image" name="mapa" src="<?=$url?>">
	</div>
< pre>
<!-- Debug Lines -->
<?php
echo "GET\n";
print_r($_GET);
echo "Point:\n";
print_r($pt); ?>

	<div id="map" style="width: 500px; height: 400px"></div>
<?php
}

/**
 * show map with marker addition event
 * allows people to enter markers over google map
 * currently used
 * version 2
 */
function show_add_marker_map_v2($name)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['mod_gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_add_mkr_js()
	{
			var map = new GMap2(document.getElementById("map"));
			map.addControl(new GLargeMapControl());
	       //map.addControl(new GSmallMapControl());
			map.addControl(new GMapTypeControl());//satellite image switch
				 
			map.setCenter(new GLatLng(<?=$conf['mod_gis_center_x']?>,<?=$conf['mod_gis_center_y']?>), <?=$conf['mod_gis_zoom']?>);			
			GEvent.addListener(map, 'click', function(overlay, point) {
	  		if (overlay) {
				var html = "<?php echo $name?>";
				//overlay.openInfoWindowHtml(html);
				map.removeOverlay(overlay);
			} 
			else if (point) {
				map.addOverlay(new GMarker(point));
				// store x,y coords in hidden variables named loc_x, loc_y
				// must be set via calling page
				var x_point=document.getElementsByName("loc_x");
				var y_point=document.getElementsByName("loc_y");
				x_point[0].value=point.x;
				y_point[0].value=point.y;
				//alert(x_point[0].value);
			}	
		});		
		
	}		
	//]]>	
	
	</script>
	<div id="map" style="width: 500px; height: 400px"></div>
<?php
}

function shn_map_show(){
	global $global;
	global $conf;
	$key = $conf['mod_gis_google_key'];
?>
<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $key?>" type="text/javascript"></script>
<script type="text/javascript">
  
//<![CDATA[
window.onload = function show_map_js()
{
		
	//alert('map');

       var map = new GMap(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
       //map.addControl(new GSmallMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch
			 
			map.centerAndZoom(new GPoint(79.5, 8.5338), 10);
	
}		
//]]>	
</script>
	<div id="map" style="width: 500px; height: 400px"></div>


<?php
}
?>
