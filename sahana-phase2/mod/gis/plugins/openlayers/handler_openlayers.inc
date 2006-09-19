<?php
/**
 * $id$
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


/**
 * show basic map
 * called by shn_gis_map in gis api
 */
function show_map($opt=null)
{
	global $global;
	global $conf;
?>
	<!--<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>-->
	<script src='http://dev.virtualearth.net/mapcontrol/v3/mapcontrol.js'></script>
	<script src="../3rd/openlayers-2.0/lib/OpenLayers.js"></script>
	<script type="text/javascript">
	  
	window.onload=function show_map_ol()
	{	
		
		var lon = <?=$conf['mod_gis_center_x']?>;
        var lat = <?=$conf['mod_gis_center_y']?>;
        //var lat=5;
        //var lon=40;
        var zoom = 5;
        var map, velayer, layer;
        
		map = new OpenLayers.Map($('map'));
		
		//map = new OpenLayers.Map( $('map') ,{controls:[new OpenLayers.Control.MouseDefaults()]});
		//var google = new OpenLayers.Layer.Google( "Google Hybrid" , {type: G_HYBRID_MAP });
	       var wms = new OpenLayers.Layer.WMS( "OpenLayers WMS", 
	                      "http://labs.metacarta.com/wms/vmap0", 
	                      {layers: 'basic'} );
	       
	       velayer = new OpenLayers.Layer.VirtualEarth( "VE",
            { minZoomLevel: 4, maxZoomLevel: 6 }); 
            
            map.addLayers([wms,velayer]);
            
            markers = new OpenLayers.Layer.Markers("markers");
            map.addLayer(markers);

            map.setCenter(new OpenLayers.LonLat(lon, lat), zoom);
            map.addControl( new OpenLayers.Control.LayerSwitcher() );
            map.addControl( new OpenLayers.Control.PanZoomBar() );
            
	}		

</script>
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?
}



/**
 * show map with marker addition event
 * ability to enter markers on map
 * called by shn_gis_add_marker_map_form in gis api
 */
function show_add_marker_map($name)
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
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
	
<?php
}


/**
 * show map with markers
 * called by shn_gis_map_with_markers in gis api
 * 
 */
function show_map_with_markers($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['mod_gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_markers_js()
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
					$url=$array[$i]["id"];
					$pre_url="index.php?mod=cr&act=ecmp&seq=view&cmp_id=";
					$url=$pre_url.$name;
?>	
					var point = new GLatLng(<?=$lon?>,<?=$lat?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?=_($name)?></strong><br><a href="<?=$url?>">View</a></div>');
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
<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}


/**
 * show map with wiki style markers
 * called by shn_gis_map_with_wiki_markers in gis api
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
					$url=_('Link: ').$array[$i]["url"];
					$date=_('Date: ').date('l dS \of F Y',$array[$i]["date"]);
					$author=($array[$i]["author"]!="")?$array[$i]["author"]:_("anonymous");
					$edit=$array[$i]["edit"];
					if($array[$i]["image"]!=null){
						$image = $array[$i]["image"];
					}
					$image=($image?"<img src=$image width=100 height=100 ><br>":'');
					//$edit="help";
?>	
					var point = new GLatLng(<?=$lon?>,<?=$lat?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?=_($name)?></strong><br><?=_($desc)?><br><?=$image?><a href="<?=$url?>">Link</a><br><?=$date?><br><strong>Author:</strong><?=$author?><br><?=$edit?></div>');
      				map.addOverlay(marker);
<?php
				}
				$image=null;
?>
      		}
      		else{
      			alert("Incompatible");
      			}      			
		
	}		
	//]]>	
	
	</script>
<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}




/**
 * Map with custom markers
 * called by shn_gis_density_map in gis api

/**
 * map with custom markers
 * called by shn_gis_density_map in gis api
 */
function show_map_with_custom_markers($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['mod_gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
	window.onload=function show_map_markers_js()
	{
			if(GBrowserIsCompatible())
			{
				var icon = new GIcon();
				//icon.image = <?=$global['approot'].$conf['mod_gis_marker_folder']."marker_r1.png"?>;
				//icon.shadow = "http://labs.google.com/ridefinder/images/mm_20_shadow.png";
				icon.iconSize = new GSize(20, 34);
				//icon.shadowSize = new GSize(22, 20);
				icon.iconAnchor = new GPoint(5, 34);
				icon.infoWindowAnchor = new GPoint(5, 2);
				
				
				
				function createMarker(point,html,markerName) {
        			var myicon=new GIcon(icon);
        			myicon.image = "<?=$conf['mod_gis_marker_folder']?>"+markerName+".png";
        			//myicon.image="http://localhost/~nazgul/sahana-main/sahana-phase2-pan/www/theme/default/img/"+markerName+".png";
        			//myicon.image="http://www.google.com/mapfiles/marker.png";
        			var marker = new GMarker(point,myicon);
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
					$url=$array[$i]["id"];
					$pre_url="index.php?mod=cr&act=ecmp&seq=view&cmp_id=";
					$url=$pre_url.$name;
					$desc=(isset($array[$i]["desc"]))?$array[$i]["desc"]:"";
					$marker_name=(isset($array[$i]["marker"]))?$array[$i]["marker"]:"marker";
?>	
					var point = new GLatLng(<?=$lon?>,<?=$lat?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?=_($name)?></strong><br><?=$desc?><br><a href="<?=$url?>">View</a></div>',"<?=$marker_name?>");
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
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}
?>
