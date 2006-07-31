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
       	map.setCenter(new GLatLng(8.5338,79.5), 10);
<?php
		}
		else{
?>
				map.setCenter(new GLatLng(<?php echo $y?>,<?php echo $x?>), 10);
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
		var point1 = new GLatLng(<?php echo $y?>,<?php echo $x?>);
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
?>
  <script type="text/javascript">
		var point1 = new GPoint(<?php echo $x?>,<?php echo $y?>);
		var marker1 = new GMarker(point1);
		var html = "<?=$name?>";
  		GEvent.addListener(marker1, 'click', function() {
			marker1.openInfoWindowHtml(html);
  		});
		map.addOverlay(marker1);
	</script>
<?php
}

/*
 * add wiki markers from db
 * used
*/
function add_wiki_marker_db2($x,$y,$name)
{
?>
  <script type="text/javascript">
		var point1 = new GLatLng(<?php echo $y?>,<?php echo $x?>);
		var marker1 = new GMarker(point1);
		map.addOverlay(marker1);
	</script>
<?php
}

/*
 * click and add markers
*/
function add_marker($name)
{
?>
	<script type="text/javascript">
		GEvent.addListener(map, 'click', function(overlay, point) {
	  	if (overlay) {
			var html = "<?php echo $name?>";
			//var html = overlay;
				overlay.openInfoWindowHtml(html);
				//map.removeOverlay(overlay);
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
	</script>
<?php
}

function add_marker_out($name)
{
?>
	<script type="text/javascript">
	function add_marker()
	{
		GEvent.addListener(map, 'click', function(overlay, point) {
	  	if (overlay) {
			var html = "<?php echo $name?>";
			//var html = overlay;
				overlay.openInfoWindowHtml(html);
				//map.removeOverlay(overlay);
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
	</script>
<?php
}

/**
 * info on existing markers
*/
function info_event($query_results){
?>
 <script type="text/javascript">
 	GEvent.addListener(map, 'click', function(overlay, point) {
  	if (overlay) { 
			//display information on marker
			var html = "test";
			overlay.openInfoWindowHtml(html);
		}
		else if (point){
			map.addOverlay(new GMarker(point));
			
		}
	});
 </script>			 
<?php
}


/**
 *adding the footer
*/
function add_footer(){
?>
    </div> <!-- /content -->
<?php

    // include the footer provided there is not a module override
    shn_include_page_section('footer',$module);
?>
    </div> <!-- /wrapper -->
    </div> <!-- /container -->

<?php
}

/**
 *used to close the page
 */
function end_page(){
?>
    </body>
    </html>
<?php 
	exit(0);
}

/**
 * show map
 * used
 */
function show_map($opt=null)
{
	global $global;
	global $conf;
	$key = $conf['mod_gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_gms()
	{
			
		//alert('map');
	
	       var map = new GMap2(document.getElementById("map"));
				 map.addControl(new GLargeMapControl());
	       //map.addControl(new GSmallMapControl());
				 map.addControl(new GMapTypeControl());//satellite image switch
				 
				map.setCenter(new GLatLng(<?=$conf['mod_gis_center_y']!=''?$conf['mod_gis_center_y']:8.5?>,<?=$conf['mod_gis_center_x']!=''?$conf['mod_gis_center_x']:79.5?>), <?=$conf['mod_gis_zoom']?>,G_SATELLITE_MAP);
		
	}		
//]]>	
</script>
<div id="map" style="width: 500px; height: 400px"></div>
<?
}

function show_map_with_markers($markers)
{
	global $global;
	global $conf;
	$db=$global['db'];
	//$key=$conf['gmap_key'];
	$key = $conf['mod_gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_js()
	{
			
		//alert('map');
	
	       var map = new GMap(document.getElementById("map"));
				 map.addControl(new GLargeMapControl());
	       //map.addControl(new GSmallMapControl());
				 map.addControl(new GMapTypeControl());//satellite image switch
				 
				map.centerAndZoom(new GPoint(<?=$conf['mod_gis_center_y']?>,<?=$conf['mod_gis_center_x']?>), <?=$conf['mod_gis_zoom']?>);
				
				
		
	}		
	//]]>
		</script>
<div id="map" style="width: 500px; height: 400px"></div>
<?php
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
?>
	<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_add_mkr_js()
	{
			var map = new GMap(document.getElementById("map"));
			map.addControl(new GLargeMapControl());
	       //map.addControl(new GSmallMapControl());
			map.addControl(new GMapTypeControl());//satellite image switch
				 
			map.centerAndZoom(new GPoint(<?=$conf['mod_gis_center_x']?>,<?=$conf['mod_gis_center_y']?>), <?=$conf['mod_gis_zoom']?>);			
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
				 
			map.setCenter(new GLatLng(<?=$conf['mod_gis_center_y']?>,<?=$conf['mod_gis_center_x']?>), <?=$conf['mod_gis_zoom']?>,G_SATELLITE_MAP);			
			GEvent.addListener(map, 'click', function(overlay, point) {
	  		if (overlay) {
				var html = "<?php echo $name?>";
				//overlay.openInfoWindowHtml(html);
				map.removeOverlay(overlay);
			} 
			else {
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

/**
 * show map with markerst
 * currently used
 * version 2
 */
function show_map_with_marker($array)
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
				 
			map.setCenter(new GLatLng(<?=$conf['mod_gis_center_y']?>,<?=$conf['mod_gis_center_x']?>), <?=$conf['mod_gis_zoom']?>,G_SATELLITE_MAP);			
			GEvent.addListener(map, 'click', function(overlay, point) {
	  		if (overlay) {
				//var html = "<?php echo $name?>";
				overlay.openInfoWindowHtml(html);
				//map.removeOverlay(overlay);
			} 
			else {
				map.addOverlay(new GMarker(point));
			}	
		});		
<?php
?>
		
	}		
	//]]>	
	
	</script>
	<div id="map" style="width: 500px; height: 400px"></div>
<?php
}

/**
 * show map with markerst
 * currently used
 * version 2
 */
function show_map_with_wiki_marker($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['mod_gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_wiki_js()
	{
			if(GBrowserIsCompatible())
			{
				function createMarker(point,html) {
        			var marker = new GMarker(point);
        			GEvent.addListener(marker, "click", function() {
          				marker.openInfoWindowHtml(html);
        			});
        		return marker;
      			}
      			
      			var map = new GMap2(document.getElementById("map"));
      			map.addControl(new GLargeMapControl());
	       		//map.addControl(new GSmallMapControl());
				map.addControl(new GMapTypeControl());//satellite image switch
				
				map.setCenter(new GLatLng(<?=$conf['mod_gis_center_y']?>,<?=$conf['mod_gis_center_x']?>), <?=$conf['mod_gis_zoom']?>,G_SATELLITE_MAP);
<?php
				for($i=0;$i< sizeof($array);$i++){
					$lat=$array[$i]["lat"];
					$lon=$array[$i]["lon"];
					$name=$array[$i]["name"];
					$desc=$array[$i]["desc"];
					$url=$array[$i]["url"];
?>	
					var point = new GLatLng(<?=$lon?>,<?=$lat?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?=_($name)?></strong><br><?=_($desc)?><br><a href="<?=$url?>">Link</a></div>');
      				map.addOverlay(marker);
<?php
				}
?>
      		}
      		else{
      			alert("Incompatible");
      			}      			
		
	}		
	//]]>	
	
	</script>
	<div id="map" style="width: 500px; height: 400px"></div>
<?php
}


/**
 * deprecated
 */
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


<?
}
?>
