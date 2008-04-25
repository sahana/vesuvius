<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: openlayers_fns.php,v 1.10 2008-04-25 00:00:26 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Load Javascript files for the different layers
 * called by show_map in openlayers plugin handler
 * @access private
 */
 function ol_js_loaders()
 {
    global $conf;
    global $global;

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_sat'] || 1 == $conf['gis_ol_google_maps'] || 1 == $conf['gis_ol_google_hybrid'])) {
        $key = $conf['gis_google_key'];
        echo "<script src='http://maps.google.com/maps?file=api&v=2&key=$key' type=\"text/javascript\"></script>\n";
    }

    if (1 == $conf['gis_ol_multimap']) {
        $key = $conf['gis_multimap_key'];
        echo "<script src='http://clients.multimap.com/API/maps/1.1/$key' type=\"text/javascript\"></script>\n";
    }

    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_aerial'] || 1 == $conf['gis_ol_virtualearth_maps'] || 1 == $conf['gis_ol_virtualearth_hybrid'])) {
        echo '<script src="http://dev.virtualearth.net/mapcontrol/v3/mapcontrol.js"></script>';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_sat'] || 1 == $conf['gis_ol_yahoo_maps'] || 1 == $conf['gis_ol_yahoo_hybrid'])) {
        $key = $conf['gis_yahoo_key'];
        echo "<script src='http://api.maps.yahoo.com/ajaxymap?v=3.8&appid=$key'></script>\n";
    }

?>
    <script src="res/OpenLayers/OpenLayers.js"></script>
    <script type="text/javascript">

    // make map available for easy debugging
    var map;
        
    // avoid pink tiles
    OpenLayers.IMAGE_RELOAD_ATTEMPTS = 3;
    OpenLayers.Util.onImageLoadErrorColor = "transparent";

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
 */
 function ol_layers()
 {
    global $conf;
    global $global;
?>
    var lon = <?=$conf['gis_center_x']?>;
    var lat = <?=$conf['gis_center_y']?>;
    var zoom = <?=$conf['gis_zoom']?>;

    var options = {
        projection: new OpenLayers.Projection("EPSG:900913"),
        displayProjection: new OpenLayers.Projection("EPSG:4326"),
        units: "m",
        maxResolution: 156543.0339,
        maxExtent: new OpenLayers.Bounds(-20037508, -20037508, 20037508, 20037508.34)
    };

    map = new OpenLayers.Map('map',options);
    OpenLayers.ProxyHost='<?=$conf['proxy_path']?>';
	       
<?php
    if ((1 == $conf['gis_ol_osm']) && (1 == $conf['gis_ol_osm_mapnik'])) {
        echo "var mapnik = new OpenLayers.Layer.TMS( \"OpenStreetMap (Mapnik)\", \"http://tile.openstreetmap.org/\", {type: 'png', getURL: osm_getTileURL, displayOutsideMaxExtent: true } );\n";
        echo 'map.addLayer(mapnik);';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_osm']) && (1 == $conf['gis_ol_osm_tiles'])) {
        echo "var osmarender = new OpenLayers.Layer.TMS( \"OpenStreetMap (Osmarender)\", \"http://tah.openstreetmap.org/Tiles/tile.php/\", {type: 'png', getURL: osm_getTileURL, displayOutsideMaxExtent: true } );\n";
        echo 'map.addLayer(osmarender);';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_hybrid'])) {
        echo "var googlehybrid = new OpenLayers.Layer.Google( \"Google Hybrid\" , {type: G_HYBRID_MAP, 'sphericalMercator': true } );\n";
        echo 'map.addLayer(googlehybrid);';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_sat'])) {
        echo "var googlesat = new OpenLayers.Layer.Google( \"Google Satellite\" , {type: G_SATELLITE_MAP, 'sphericalMercator': true } );\n";
        echo 'map.addLayer(googlesat);';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_maps'])) {
        echo "var googlemaps = new OpenLayers.Layer.Google( \"Google Map\" , {type: G_NORMAL_MAP, 'sphericalMercator': true } );\n";
        echo 'map.addLayer(googlemaps);';
        echo "\n";
    }

    if (1 == $conf['gis_ol_multimap']) {
        echo "var multimap = new OpenLayers.Layer.MultiMap( \"MultiMap\");\n";
        echo 'map.addLayer(multimap);';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_hybrid'])) {
        echo "var vehybrid = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Hybrid\" , {type: VEMapStyle.Hybrid, 'sphericalMercator': true } );\n";
        //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
        echo 'map.addLayer(vehybrid);';
        echo "\n";
    }
       
    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_aerial'])) {
        echo "var veaerial = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Aerial\" , {type: VEMapStyle.Aerial, 'sphericalMercator': true } );\n";
        //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
        echo 'map.addLayer(veaerial);';
        echo "\n";
    }
    
    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_maps'])) {
        echo "var veroad = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Road\" , {type: VEMapStyle.Road, 'sphericalMercator': true } );\n";
        //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
        echo 'map.addLayer(veroad);';
        echo "\n";
    }
    
    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_hybrid'])) {
        echo "var yahoohybrid = new OpenLayers.Layer.Yahoo( \"Yahoo Hybrid\", {'type': YAHOO_MAP_HYB, 'sphericalMercator': true } );\n";
        echo 'map.addLayer(yahoohybrid);';
        echo "\n";
    }

    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_sat'])) {
        echo "var yahoosat = new OpenLayers.Layer.Yahoo( \"Yahoo Satellite\", {'type': YAHOO_MAP_SAT, 'sphericalMercator': true } );\n";
        echo 'map.addLayer(yahoosat);';
        echo "\n";
    }
 
    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_maps'])) {
        echo "var yahoomaps = new OpenLayers.Layer.Yahoo( \"Yahoo Map\", {'sphericalMercator': true } );\n";
        echo 'map.addLayer(yahoomaps);';
        echo "\n";
    }

    for ($i = 1; $i <= $conf['gis_ol_wms']; $i++) {
        $name = $conf["gis_ol_wms_".$i."_name"];
        $url = $conf["gis_ol_wms_".$i."_url"];
        $layers = $conf["gis_ol_wms_".$i."_layers"];
        echo "var wmslayer$i = new OpenLayers.Layer.WMS( \"$name\",\n"; 
        echo "\"$url\",\n"; 
        echo "{layers: '$layers'}, \n";
        echo "{'sphericalMercator': true, 'wrapDateLine': true} );\n";
        echo "map.addLayer(wmslayer$i);\n";
    }

    for ($i = 1; $i <= $conf['gis_ol_georss']; $i++) {
        $name = $conf["gis_ol_georss_".$i."_name"];
        $url = $conf["gis_ol_georss_".$i."_url"];
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
 * Function to support OSM layers
 * called by all show functions in openlayers plugin handler
 * @access private
 */
function ol_osm_getTileURL()
{
    global $conf;
    // close init()
    echo "}\n";
    if ((1 == $conf['gis_ol_osm']) && (1 == $conf['gis_ol_osm_mapnik'] || 1 == $conf['gis_ol_osm_tiles'])) {
        echo "function osm_getTileURL(bounds) {\n";
        echo "    var res = this.map.getResolution();\n";
        echo "    var x = Math.round((bounds.left - this.maxExtent.left) / (res * this.tileSize.w));\n";
        echo "    var y = Math.round((this.maxExtent.top - bounds.top) / (res * this.tileSize.h));\n";
        echo "    var z = this.map.getZoom();\n";
        echo "    var limit = Math.pow(2, z);\n";
        echo "    if (y < 0 || y >= limit) {\n";
        echo "        return OpenLayers.Util.getImagesLocation() + \"404.png\";\n";
        echo "    } else {\n";
        echo "        x = ((x % limit) + limit) % limit;\n";
        echo "        return this.url + z + \"/\" + x + \"/\" + y + \".\" + this.type;\n";
        echo "    }\n";
    }
}
    
/**
 * Show the Markers layer with Wiki information
 * called by show_map in openlayers plugin handler
 * @access private
 */
 function ol_show_wiki_markers($array)
 {
    global $conf;
    global $global;
    $db = $global['db'];
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
        echo "    if (!popup.visible()) {\n";
        echo "        markers.map.removePopup(popup);\n";
        echo "        popup.destroy();\n";
        echo "        popup = null;\n";
        echo "    }\n";
        echo "}\n";
        echo "if (popup == null) {\n";
        echo "    popup = feature$i.createPopup(true);\n";
        echo "    popup.setContentHTML(\"<b>$name</b><br>$desc<br><a href='$url' target='_blank'>Link</a><br>$date<br><b>Author</b>: $author</p>";
        if (1 == $edit) {
            echo "<br><a href='$url' target='_blank'>Edit</a>\");\n";
        } else {
            echo "\");\n";
        }
        echo "    popup.setBackgroundColor(\"yellow\");\n";
        echo "    popup.setOpacity(0.7);\n";
        echo "    markers.map.addPopup(popup);\n";
        echo "} else {\n";
        echo "    markers.map.removePopup(popup);\n";
        echo "    popup.destroy();\n";
        echo "    popup = null;\n";
        echo "}\n";
        echo "Event.stop(evt);\n";
        echo "}\n";
    }
}

/**
 * Show the Markers layer
 * called by show_map in openlayers plugin handler
 * @access private
 */
 function ol_show_markers($array)
 {
    global $conf;
    global $global;
    $db = $global['db'];
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
    $db = $global['db'];
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
