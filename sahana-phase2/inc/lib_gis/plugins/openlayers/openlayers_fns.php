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
* @author	Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * Load Javascript files for the different layers
 * called by show_map in openlayers plugin handler
 * @access private
 * @todo get layers from catalogue module instead of conf.inc
 */
 function ol_js_loaders()
 {
 	global $conf;
 	global $global;

	if (1 == $conf['ol_google_sat'] || 1 == $conf['ol_google_maps'] || 1 == $conf['ol_google_hybrid']) {
	$key = $conf['mod_gis_google_key'];
	echo "<script src='http://maps.google.com/maps?file=api&v=2&key=$key' type=\"text/javascript\"></script>\n";
	}

	if (1 == $conf['ol_multimap']) {
	$key = $conf['mod_gis_multimap_key'];
	echo "<script src='http://clients.multimap.com/API/maps/1.1/$key' type=\"text/javascript\"></script>\n";
	}

	if (1 == $conf['ol_virtualearth']) {
	echo '<script src="http://dev.virtualearth.net/mapcontrol/v3/mapcontrol.js"></script>';
	echo "\n";
	}

	if (1 == $conf['ol_yahoo_maps']) {
	$key = $conf['mod_gis_yahoo_key'];
	echo "<script src='http://api.maps.yahoo.com/ajaxymap?v=3.0&appid=$key'></script>\n";
	}

?>
	<script src="res/OpenLayers/OpenLayers.js"></script>
	<script type="text/javascript">

        var onloadfunc = window.onload;
	window.onload=function show_map_ol()
	{
	   onloadfunc();
<?php
}



/**
 * Load Layers onto the Map
 * called by show_map in openlayers plugin handler
 * @access private
 * @todo get layers from catalogue module instead of conf.inc
 */
 function ol_layers()
 {
 	global $conf;
 	global $global;
?>
	var lon = <?=$conf['mod_gis_center_x']?>;
  	var lat = <?=$conf['mod_gis_center_y']?>;
  	var zoom = 5;
	var map = new OpenLayers.Map($('map'));
	OpenLayers.ProxyHost='<?=$conf['proxy_path']?>';
	       
<?php
	if (1 == $conf['ol_google_hybrid']) {
	echo "var googlehybrid = new OpenLayers.Layer.Google( \"Google Hybrid\" , {type: G_HYBRID_MAP } );\n";
	echo 'map.addLayer(googlehybrid);';
	echo "\n";
	}

	if (1 == $conf['ol_google_sat']) {
	echo "var googlesat = new OpenLayers.Layer.Google( \"Google Satellite\" , {type: G_SATELLITE_MAP } );\n";
	echo 'map.addLayer(googlesat);';
	echo "\n";
	}

	if (1 == $conf['ol_google_maps']) {
	echo "var googlemaps = new OpenLayers.Layer.Google( \"Google Maps\" , {type: G_NORMAL_MAP } );\n";
	echo 'map.addLayer(googlemaps);';
	echo "\n";
	}

	if (1 == $conf['ol_multimap']) {
	echo "var multimap = new OpenLayers.Layer.MultiMap( \"MultiMap\");\n";
	echo 'map.addLayer(multimap);';
	echo "\n";
	}

	if (1 == $conf['ol_virtualearth']) {
	echo "var velayer = new OpenLayers.Layer.VirtualEarth( \"MS VirtualEarth\",\n";
	echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
	echo 'map.addLayer(velayer);';
	echo "\n";
	}
        
	if (1 == $conf['ol_yahoo_maps']) {
	echo "var yahoo = new OpenLayers.Layer.Yahoo( \"Yahoo\");\n";
	echo 'map.addLayer(yahoo);';
	echo "\n";
	}

	for ($i = 1; $i <= $conf['ol_wms']; $i++) {
	$name = $conf["ol_wms_".$i."_name"];
	$url = $conf["ol_wms_".$i."_url"];
	$layers = $conf["ol_wms_".$i."_layers"];
	echo "var wmslayer$i = new OpenLayers.Layer.WMS( \"$name\",\n"; 
		echo "\"$url\",\n"; 
		echo "{layers: '$layers'} );\n";
	echo "map.addLayer(wmslayer$i);\n";
	}

	for ($i = 1; $i <= $conf['ol_georss']; $i++) {
	$name = $conf["ol_georss_".$i."_name"];
	$url = $conf["ol_georss_".$i."_url"];
	echo "var georsslayer$i = new OpenLayers.Layer.GeoRSS( \"$name\", \"$url\");\n"; 
	echo "map.addLayer(georsslayer$i);\n";
	}
?>
            
	map.setCenter( new OpenLayers.LonLat(lon, lat), zoom);
	map.addControl( new OpenLayers.Control.LayerSwitcher() );
	map.addControl( new OpenLayers.Control.PanZoomBar() );

<?php
}



/**
 * Show the Markers layer with Wiki information
 * called by show_map in openlayers plugin handler
 * @access private
 * @todo get layers from catalogue module instead of conf.inc
 */
 function ol_show_wiki_markers($array)
 {
 	global $conf;
 	global $global;
  $db=$global['db'];
?>

	var markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);
	var size = new OpenLayers.Size(21,25); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('res/OpenLayers/img/marker.png',size,offset);
	var popup;

<?php
	for($i=0;$i< sizeof($array);$i++){
	$lon=$array[$i]["lat"];
	$lat=$array[$i]["lon"];
	$name=$array[$i]["name"];
  $desc=$array[$i]["desc"];
  $url=$array[$i]["url"];
	if(!(($array[$i]["date"])=="0000-00-00 00:00:00")){
		$date=_('Date: ').date('l dS \of F Y',strtotime($array[$i]["date"]));
	} else {
		$date="";
	}
	$author=($array[$i]["author"]!="")?$array[$i]["author"]:_("anonymous");
  $edit=$array[$i]["edit"];
	$id=$array[$i]["wiki_uuid"];
	echo "var feature$i = new OpenLayers.Feature(markers, new OpenLayers.LonLat($lon,$lat),{'icon': icon.clone()});\n";
	echo "var marker$i = feature$i.createMarker();\n";
	echo "markers.addMarker(marker$i);\n";
	echo "marker$i.events.register(\"mousedown\", marker$i, mousedown$i);\n";
	echo "function mousedown$i(evt) {\n";
		// check to see if the popup was hidden by the close box
		// if so, then destroy it before continuing
		echo "if (popup != null) {\n";
			echo "if (!popup.visible()) {\n";
				echo "markers.map.removePopup(popup);\n";
				echo "popup.destroy();\n";
				echo "popup = null;\n";
			echo "}\n";
		echo "}\n";
		echo "if (popup == null) {\n";
			echo "popup = feature$i.createPopup(true);\n";
			echo "popup.setContentHTML(\"<b>$name</b><br>$desc<br><a href='$url' target='_blank'>Link</a><br>$date<br><b>Author</b>: $author</p>";
			if (1 == $edit) {
				echo "<br><a href='$url' target='_blank'>Edit</a>\");\n";
			} else {
				echo "\");\n";
			}
			echo "popup.setBackgroundColor(\"yellow\");\n";
			echo "popup.setOpacity(0.7);\n";
			echo "markers.map.addPopup(popup);\n";
		echo "} else {\n";
			echo "markers.map.removePopup(popup);\n";
			echo "popup.destroy();\n";
			echo "popup = null;\n";
		echo "}\n";
		echo "Event.stop(evt);\n";
	echo "}\n";
	}
}

/**
 * Show the Markers layer
 * called by show_map in openlayers plugin handler
 * @access private
 * @todo get layers from catalogue module instead of conf.inc
 */
 function ol_show_markers($array)
 {
 	global $conf;
 	global $global;
  	$db=$global['db'];
?>

	var markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);
	var size = new OpenLayers.Size(21,25); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('res/OpenLayers/img/marker.png',size,offset);
	var popup;

<?php
	for($i=0;$i< sizeof($array);$i++){
	$lon=$array[$i]["lat"];
	$lat=$array[$i]["lon"];
	$name=$array[$i]["name"];
  	$url=$array[$i]["url"];
  	$pre_url="index.php?";
	$url=$pre_url.$url;
	
	echo "var feature$i = new OpenLayers.Feature(markers, new OpenLayers.LonLat($lon,$lat),{'icon': icon.clone()});\n";
	echo "var marker$i = feature$i.createMarker();\n";
	echo "markers.addMarker(marker$i);\n";
	echo "marker$i.events.register(\"mousedown\", marker$i, mousedown$i);\n";
	echo "function mousedown$i(evt) {\n";
		// check to see if the popup was hidden by the close box
		// if so, then destroy it before continuing
		echo "if (popup != null) {\n";
			echo "if (!popup.visible()) {\n";
				echo "markers.map.removePopup(popup);\n";
				echo "popup.destroy();\n";
				echo "popup = null;\n";
			echo "}\n";
		echo "}\n";
		echo "if (popup == null) {\n";
			echo "popup = feature$i.createPopup(true);\n";
			echo "popup.setContentHTML(\"<b>$name</b><br /><a href='$url' target='_blank'>Link</a><br /></p>";
			echo "\");\n";
			echo "popup.setBackgroundColor(\"yellow\");\n";
			echo "popup.setOpacity(0.7);\n";
			echo "markers.map.addPopup(popup);\n";
		echo "} else {\n";
			echo "markers.map.removePopup(popup);\n";
			echo "popup.destroy();\n";
			echo "popup = null;\n";
		echo "}\n";
		echo "Event.stop(evt);\n";
	echo "}\n";
	}
}
		
/**
 * Show the map & allow addition of a Marker
 * called by show_add_marker_map in openlayers plugin handler
 * @access private
 */
 function ol_add_marker($name)
 {
 	global $conf;
 	global $global;
  $db=$global['db'];
?>

	var markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);
	var size = new OpenLayers.Size(21,25); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('res/OpenLayers/img/marker.png',size,offset);
	
	map.events.register("click", map, function(e) { 
		var lonlat = map.getLonLatFromViewPortPx(e.xy);
		var lon_new = lonlat.lon;
		var lat_new = lonlat.lat;
		// store x,y coords in hidden variables named loc_x, loc_y
		// must be set via calling page
		var x_point=document.getElementsByName("loc_x");
		var y_point=document.getElementsByName("loc_y");
		x_point[0].value=lon_new;
		y_point[0].value=lat_new;
		// Provide visual feedback that marker was placed OK
		var marker = new OpenLayers.Marker(new OpenLayers.LonLat(lon_new,lat_new),icon);
		markers.addMarker(marker);
});
	
<?php
}

?>
