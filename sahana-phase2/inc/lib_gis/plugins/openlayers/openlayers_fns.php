<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: openlayers_fns.php,v 1.34 2008-05-13 21:34:05 franboon Exp $
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

  //Disable other base layers if using a non-sphericalMercator WMS projection
  if (0==$conf['gis_ol_wms_enable'] || "EPSG:900913"==$conf["gis_ol_wms_projection"]) {
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

  }
  if (1 == $conf['gis_ol_files_enable']) {
      echo "<script src='res/OpenLayers/osm_styles.js'></script>\n";
  }
?>
    <script src="res/OpenLayers/OpenLayers.js"></script>
    <script src="res/OpenLayers/proj4js.js"></script>
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
    // http://crschmidt.net/~crschmidt/spherical_mercator.html#reprojecting-points
    var proj4326 = new OpenLayers.Projection("EPSG:4326");
    var projection_current = new OpenLayers.Projection("<?=$conf['gis_ol_wms_projection']?>");
    var point = new OpenLayers.LonLat(lon, lat);
    var options = {
        displayProjection: proj4326,
        projection: projection_current,
        units: "<?=$conf['gis_ol_wms_units']?>",
        maxResolution: <?=$conf['gis_ol_wms_maxResolution']?>,
        maxExtent: new OpenLayers.Bounds(<?=$conf['gis_ol_wms_maxExtent']?>)
    };
    map = new OpenLayers.Map('map',options);
    OpenLayers.ProxyHost='<?=$conf['proxy_path']?>';
	       
<?php
  //Disable other base layers if using a non-sphericalMercator WMS projection
  if (0==$conf['gis_ol_wms_enable'] || "EPSG:900913"==$conf["gis_ol_wms_projection"]) {
    //OSM layer(s) listed 1st - promote OpenData!
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
  }
    if (1 == $conf['gis_ol_wms_enable']) {
        $projection = $conf["gis_ol_wms_projection"];
        $maxResolution = $conf["gis_ol_wms_maxResolution"];
        $maxExtent = $conf["gis_ol_wms_maxExtent"];
        $units = $conf["gis_ol_wms_units"];
        $wms = $conf["gis_ol_wms"];
        for ($i = 1; $i <= $wms; $i++) {
            if (1==$conf["gis_ol_wms_".$i."_enabled"]) {
                $name = $conf["gis_ol_wms_".$i."_name"];
                $url = $conf["gis_ol_wms_".$i."_url"];
                $map = $conf["gis_ol_wms_".$i."_map"];
                $layers = $conf["gis_ol_wms_".$i."_layers"];
                $format = $conf["gis_ol_wms_".$i."_format"];
                echo "var wmslayer$i = new OpenLayers.Layer.WMS( \"$name\",\n"; 
                echo "\"$url\",\n"; 
                echo "{";
                if (!null==$map) {
                    echo "map:'$map', ";
                }
                echo "layers:'$layers', ";
                if (!null==$format) {
                    echo "format:'$format', ";
                }
                $base = "true";
                if ("1" == $conf["gis_ol_wms_".$i."_type"]) {
                    $base = "false";
                }
                echo "isBaseLayer:'$base', wrapDateLine:'true'";
                if ("1" == $conf["gis_ol_wms_".$i."_transparency"]) {
                    echo ", transparent: true";
                }
                echo "});\n";
                echo "map.addLayer(wmslayer$i);\n";
                if ("0" == $conf["gis_ol_wms_".$i."_visibility"]) {
                    echo "wmslayer$i.setVisibility(false);\n";
                }
            }
        }
    }

    if (1 == $conf['gis_ol_georss_enable']) {
        for ($i = 1; $i <= $conf['gis_ol_georss']; $i++) {
            if (1==$conf["gis_ol_georss_".$i."_enabled"]) {
                $name = $conf["gis_ol_georss_".$i."_name"];
                $url = $conf["gis_ol_georss_".$i."_url"];
                $projection = $conf["gis_ol_georss_".$i."_projection"];
                echo "var projgeorss$i = new OpenLayers.Projection(\"$projection\");\n";
                echo "var georsslayer$i = new OpenLayers.Layer.GeoRSS( \"$name\", \"$url\", {projection: projgeorss$i});\n"; 
                echo "map.addLayer(georsslayer$i);\n";
                if ("0" == $conf["gis_ol_georss_".$i."_visibility"]) {
                    echo "georsslayer$i.setVisibility(false);\n";
                }
            }
        }
    }

    if (1 == $conf['gis_ol_files_enable']) {
        for ($i = 1; $i <= $conf['gis_ol_files']; $i++) {
            if (1==$conf["gis_ol_files_".$i."_enabled"]) {
                $name = $conf["gis_ol_files_".$i."_name"];
                $filename = $conf["gis_ol_files_".$i."_filename"];
                $ext=end(explode('.',$filename));
                $path='res/OpenLayers/files/'.$filename;
                echo "var fileslayer$i = new OpenLayers.Layer.GML( \"$name\", \"$path\", { projection: proj4326"; 
                if ("KML"==strtoupper($ext)) {
                    echo ", format: OpenLayers.Format.KML, formatOptions: { extractStyles: true, extractAttributes: true }});\n";
                }
                else if ("OSM"==strtoupper($ext)) {
                    echo ", format: OpenLayers.Format.OSM});\n";
                }
                else {
                //GML
                    echo "});\n";
                }
                echo "map.addLayer(fileslayer$i);\n";
                if ("0" == $conf["gis_ol_files_".$i."_visibility"]) {
                    echo "fileslayer$i.setVisibility(false);\n";
                }
                if ("OSM"==strtoupper($ext)) {
                    echo "fileslayer$i.preFeatureInsert = style_osm_feature;\n";
                    echo "var sf$i = new OpenLayers.Control.SelectFeature(fileslayer$i, {'onSelect': on_feature_hover});\n";
                    echo "map.addControl(sf$i);\n";
                    echo "sf$i.activate();\n";
                }
            }
        }
    }
?>
            
	// http://crschmidt.net/~crschmidt/spherical_mercator.html#reprojecting-points
    map.setCenter(point.transform(proj4326, map.getProjectionObject()),zoom);
	map.addControl( new OpenLayers.Control.LayerSwitcher() );
	map.addControl( new OpenLayers.Control.PanZoomBar() );
<?php
}

/**
 * Allow addition of a Marker
 * called by show_add_marker_map in openlayers plugin handler
 * @access private
 */
 function ol_add_marker($name)
 {
    global $conf;
    global $global;
    $db = $global['db'];
    $folder = $conf['gis_marker_folder'];
?>

    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);
    var size = new OpenLayers.Size(20,34); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?=$folder?>marker.png',size,offset);
	
    map.events.register("click", map, function(e) { 
        var lonlat = map.getLonLatFromPixel(e.xy);
        // Provide visual feedback that marker was placed OK (pre-transform)
        var marker = new OpenLayers.Marker(lonlat,icon);
        markers.addMarker(marker);
        // Convert to Lon/Lat for DB storage
        var proj_current = map.getProjectionObject();
        lonlat.transform(proj_current, proj4326);
        var lon_new = lonlat.lon;
        var lat_new = lonlat.lat;
        // store x,y coords in hidden variables named loc_x, loc_y
        // must be set via calling page
        var x_point=document.getElementsByName("loc_x");
        var y_point=document.getElementsByName("loc_y");
        x_point[0].value=lon_new;
        y_point[0].value=lat_new;
});
<?php
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
    $folder = $conf['gis_marker_folder'];
?>
	var markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);
	var size = new OpenLayers.Size(20,34); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?=$folder?>marker.png',size,offset);
    var currentPopup;
<?php
	for($i=0;$i< sizeof($array);$i++){
        $lon=$array[$i]["lat"];
        $lat=$array[$i]["lon"];
        $name=$array[$i]["name"];
        $url=$array[$i]["url"];
        $pre_url="index.php?";
        $url=$pre_url.$url;
        echo "popupContentHTML = \"<b>$name</b><br /><a href='$url'>View</a><br /></p>\"\n";
        echo "var lonlat = new OpenLayers.LonLat($lon,$lat);\n";
        echo "var proj_current = map.getProjectionObject();\n";
        echo "lonlat.transform(proj4326, proj_current);\n";
        echo "addMarker(lonlat,popupContentHTML);\n";
    }
?>
    function addMarker(lonlat, popupContentHTML) {
        var feature = new OpenLayers.Feature(markers, lonlat,{'icon': icon.clone()}); 
        feature.closeBox = true;
        feature.popupClass = OpenLayers.Class(OpenLayers.Popup.AnchoredBubble,{'autoSize': true});
        feature.data.popupContentHTML = popupContentHTML;
        var marker = feature.createMarker();
        var markerClick = function (evt) {
            if (this.popup == null) {
                this.popup = this.createPopup(this.closeBox);
                //this.popup.setOpacity(0.9);
                map.addPopup(this.popup);
                this.popup.show();
            } else {
                this.popup.toggle();
            }
            currentPopup = this.popup;
            OpenLayers.Event.stop(evt);
        };
        marker.events.register("mousedown", feature, markerClick);
        markers.addMarker(marker);
    }
<?php   
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
    $folder = $conf['gis_marker_folder'];
?>
    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);
    var size = new OpenLayers.Size(20,34); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?=$folder?>marker.png',size,offset);
    var currentPopup;
<?php
    for($i=0;$i< sizeof($array);$i++){
        $lon=$array[$i]["lat"];
        $lat=$array[$i]["lon"];
        $name=$array[$i]["name"];
        $desc=$array[$i]["desc"];
        if(!(($array[$i]["date"])=="0000-00-00 00:00:00")){
            $date=_('Date: ').date('l dS \of F Y',strtotime($array[$i]["date"]));
        } else {
            $date="";
        }
        $author=($array[$i]["author"]!="")?$array[$i]["author"]:_("anonymous");
        echo "popupContentHTML = \"<p><b>$name</b><br>$desc<br>";
        if (!null == $array[$i]["image"]) {
            $image = $array[$i]["image"];
            echo "<img src=$image width=100 height=100><br>";
        }
        if (!null == $array[$i]["url"]) {
            $url=$array[$i]["url"];
            echo "<a href='$url' target='_blank'>View</a><br>";
        }
        echo "$date<br><b>Author</b>: $author<br>";
        if (!null == $array[$i]["edit"]) {
            $edit=$array[$i]["edit"];
            echo "<a href='$edit'>Edit</a>";
        }
        echo "</p>\"\n";
        echo "var lonlat = new OpenLayers.LonLat($lon,$lat);\n";
        echo "var proj_current = map.getProjectionObject();\n";
        echo "lonlat.transform(proj4326, proj_current);\n";
        echo "addMarker(lonlat,popupContentHTML);\n";
    }
?>
    function addMarker(lonlat, popupContentHTML) {
        var feature = new OpenLayers.Feature(markers, lonlat,{'icon': icon.clone()}); 
        feature.closeBox = true;
        feature.popupClass = OpenLayers.Class(OpenLayers.Popup.AnchoredBubble,{'autoSize': true});
        feature.data.popupContentHTML = popupContentHTML;
        var marker = feature.createMarker();
        var markerClick = function (evt) {
            if (this.popup == null) {
                this.popup = this.createPopup(true);
                //this.popup.setOpacity(0.9);
                map.addPopup(this.popup);
                this.popup.show();
            } else {
                this.popup.toggle();
            }
            currentPopup = this.popup;
            OpenLayers.Event.stop(evt);
        };
        marker.events.register("mousedown", feature, markerClick);
        markers.addMarker(marker);
    }
<?php   
}

/**
 * Show the Markers layer with custom markers
 * called by show_map_with_custom_markers in openlayers plugin handler
 * @access private
 */
 function ol_show_custom_markers($array)
 {
    global $conf;
    global $global;
    $folder = $conf['gis_marker_folder'];
?>
	var markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);
	var size = new OpenLayers.Size(20,34); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
    var currentPopup;
<?php
	for($i=0;$i< sizeof($array);$i++){
        $lon=$array[$i]["lat"];
        $lat=$array[$i]["lon"];
        $name=$array[$i]["name"];
        $url=$array[$i]["url"];
        $pre_url="index.php?";
        $url=$pre_url.$url;
        $marker_name=(isset($array[$i]["marker"]))?$array[$i]["marker"]:"marker";
?>
        var icon = new OpenLayers.Icon('<?=$folder?><?=$marker_name?>.png',size,offset);
<?php
	    echo "popupContentHTML = \"<b>$name</b><br /><a href='$url'>View</a><br /></p>\"\n";
        echo "var lonlat = new OpenLayers.LonLat($lon,$lat);\n";
        echo "var proj_current = map.getProjectionObject();\n";
        echo "lonlat.transform(proj4326, proj_current);\n";
        echo "addMarker(lonlat,popupContentHTML);\n";
    }
?>
    function addMarker(lonlat, popupContentHTML) {
        var feature = new OpenLayers.Feature(markers, lonlat,{'icon': icon.clone()}); 
        feature.closeBox = true;
        feature.popupClass = OpenLayers.Class(OpenLayers.Popup.AnchoredBubble,{'autoSize': true});
        feature.data.popupContentHTML = popupContentHTML;
        var marker = feature.createMarker();
        var markerClick = function (evt) {
            if (this.popup == null) {
                this.popup = this.createPopup(this.closeBox);
                //this.popup.setOpacity(0.9);
                map.addPopup(this.popup);
                this.popup.show();
            } else {
                this.popup.toggle();
            }
            currentPopup = this.popup;
            OpenLayers.Event.stop(evt);
        };
        marker.events.register("mousedown", feature, markerClick);
        markers.addMarker(marker);
    }
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
    ?>
    function on_feature_hover(feature) {
            var text ="<ul>";
            var type ="way";
            if (feature.geometry.CLASS_NAME == "OpenLayers.Geometry.Point") {
                type = "node";
            }    
            text += "<li>" + feature.osm_id + ": <a href='http://www.openstreetmap.org/api/0.5/"+type + "/" + feature.osm_id + "'>API</a></li>";
            for (var key in feature.attributes) {
                text += "<li>" + key + ": " + feature.attributes[key] + "</li>";
            }
            text += "</ul>";
            $("status").innerHTML = text;
    }
    <?php
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
        echo "}\n";
    }
}
    
?>
