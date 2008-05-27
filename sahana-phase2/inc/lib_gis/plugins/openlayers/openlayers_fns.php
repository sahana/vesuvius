<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: openlayers_fns.php,v 1.45 2008-05-27 21:05:15 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Load Javascript files for the different layers
 * called by show_map in openlayers plugin handler
 * @access public
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
      echo "<link rel='stylesheet' href='res/OpenLayers/theme/default/framedCloud.css' type='text/css' />\n";
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
 * @access public
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
        echo "map.addLayer(mapnik);\n";
    }

    if ((1 == $conf['gis_ol_osm']) && (1 == $conf['gis_ol_osm_tiles'])) {
        echo "var osmarender = new OpenLayers.Layer.TMS( \"OpenStreetMap (Osmarender)\", \"http://tah.openstreetmap.org/Tiles/tile.php/\", {type: 'png', getURL: osm_getTileURL, displayOutsideMaxExtent: true } );\n";
        echo "map.addLayer(osmarender);\n";
    }

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_hybrid'])) {
        echo "var googlehybrid = new OpenLayers.Layer.Google( \"Google Hybrid\" , {type: G_HYBRID_MAP, 'sphericalMercator': true } );\n";
        echo "map.addLayer(googlehybrid);\n";
    }

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_sat'])) {
        echo "var googlesat = new OpenLayers.Layer.Google( \"Google Satellite\" , {type: G_SATELLITE_MAP, 'sphericalMercator': true } );\n";
        echo "map.addLayer(googlesat);\n";
    }

    if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_maps'])) {
        echo "var googlemaps = new OpenLayers.Layer.Google( \"Google Map\" , {type: G_NORMAL_MAP, 'sphericalMercator': true } );\n";
        echo "map.addLayer(googlemaps);\n";
    }

    if (1 == $conf['gis_ol_multimap']) {
        echo "var multimap = new OpenLayers.Layer.MultiMap( \"MultiMap\");\n";
        echo "map.addLayer(multimap);\n";
    }

    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_hybrid'])) {
        echo "var vehybrid = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Hybrid\" , {type: VEMapStyle.Hybrid, 'sphericalMercator': true } );\n";
        //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
        echo "map.addLayer(vehybrid);\n";
    }
       
    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_aerial'])) {
        echo "var veaerial = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Aerial\" , {type: VEMapStyle.Aerial, 'sphericalMercator': true } );\n";
        //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
        echo "map.addLayer(veaerial);\n";
    }
    
    if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_maps'])) {
        echo "var veroad = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Road\" , {type: VEMapStyle.Road, 'sphericalMercator': true } );\n";
        //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
        echo "map.addLayer(veroad);\n";
    }
    
    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_hybrid'])) {
        echo "var yahoohybrid = new OpenLayers.Layer.Yahoo( \"Yahoo Hybrid\", {'type': YAHOO_MAP_HYB, 'sphericalMercator': true } );\n";
        echo "map.addLayer(yahoohybrid);\n";
    }

    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_sat'])) {
        echo "var yahoosat = new OpenLayers.Layer.Yahoo( \"Yahoo Satellite\", {'type': YAHOO_MAP_SAT, 'sphericalMercator': true } );\n";
        echo "map.addLayer(yahoosat);\n";
    }
 
    if ((1 == $conf['gis_ol_yahoo']) && (1 == $conf['gis_ol_yahoo_maps'])) {
        echo "var yahoomaps = new OpenLayers.Layer.Yahoo( \"Yahoo Map\", {'sphericalMercator': true } );\n";
        echo "map.addLayer(yahoomaps);\n";
    }
  }
    // WMS
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
    
    // GeoRSS
    if (1 == $conf['gis_ol_georss_enable']) {
        $folder=$conf['gis_marker_folder'];
        $errors_georss="";
        if(function_exists(curl_init)){
            $dir = $global['approot'].'www/tmp/georss_cache';
            mkdir($dir);
            for ($i = 1; $i <= $conf['gis_ol_georss']; $i++) {
                if (1==$conf["gis_ol_georss_".$i."_enabled"]) {
                    $name = $conf["gis_ol_georss_".$i."_name"];
                    $url = $conf["gis_ol_georss_".$i."_url"];
                    $file=end(explode('/',$url));
                    $path = $dir."/".$file;
                    $ch = curl_init();
                    curl_setopt($ch, CURLOPT_URL,$url);
                    curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);  
                    curl_setopt($ch, CURLOPT_FAILONERROR,1);
                    $xmlResponse = curl_exec($ch);
                    $errnum=curl_errno($ch);
                    curl_close($ch);
                    // if errors
                    if (!0==$errnum) {
                        if (!file_exists($path)) {
                            $errors_georss.='<b>'._t("Warning")."</b>: \"$url\" "._t("inaccessible & no cached copy available").". \"$name\" "._t("layer not loaded").'.<br />';
                            $display=0;
                        } else {
                            // mtime() better on Win32
                            $timestamp=filemtime($path);
                            $stale=date("d M Y", $timestamp);
                            $errors_georss.='<b>'._t("Warning")."</b>: \"$url\" "._t("inaccessible").". \"$name\" "._t("layer loaded from cache. Last downloaded")." $stale.<br />";
                            $display=1;
                        }
                    } else {
                        // write out file
                        // ToDo: Catch for folder/file not being writable
                        $handle = fopen($path, 'w');
                        fwrite($handle, $xmlResponse);
                        fclose($handle);
                        $display=1;
                    }
                    if (1==$display) {
                        $path='tmp/georss_cache/'.$file;
                        $icon = $conf["gis_ol_georss_".$i."_icon"];
                        $iconsize = $conf["gis_ol_georss_".$i."_icon_size"];
                        $projection = $conf["gis_ol_georss_".$i."_projection"];
                        echo "var icongeorss$i = new OpenLayers.Icon(\"$folder$icon\", new OpenLayers.Size($iconsize));\n";
                        echo "var projgeorss$i = new OpenLayers.Projection(\"$projection\");\n";
                        echo "var georsslayer$i = new OpenLayers.Layer.GeoRSS( \"$name\", \"$path\", {projection: projgeorss$i, icon: icongeorss$i});\n"; 
                        echo "map.addLayer(georsslayer$i);\n";
                        if ("0" == $conf["gis_ol_georss_".$i."_visibility"]) {
                            echo "georsslayer$i.setVisibility(false);\n";
                        }
                    }
                }
            }
        } else {
            $errors_georss='<b>'._t("Warning").'</b>: '._t("PHP has no libcurl support. GeoRSS layers not being cached").'.<br />';
            for ($i = 1; $i <= $conf['gis_ol_georss']; $i++) {
                if (1==$conf["gis_ol_georss_".$i."_enabled"]) {
                    $name = $conf["gis_ol_georss_".$i."_name"];
                    $url = $conf["gis_ol_georss_".$i."_url"];
                    $icon = $conf["gis_ol_georss_".$i."_icon"];
                    $iconsize = $conf["gis_ol_georss_".$i."_icon_size"];
                    $projection = $conf["gis_ol_georss_".$i."_projection"];
                    echo "var icongeorss$i = new OpenLayers.Icon(\"$folder$icon\", new OpenLayers.Size($iconsize));\n";
                    echo "var projgeorss$i = new OpenLayers.Projection(\"$projection\");\n";
                    echo "var georsslayer$i = new OpenLayers.Layer.GeoRSS( \"$name\", \"$url\", {projection: projgeorss$i, icon: icongeorss$i});\n"; 
                    echo "map.addLayer(georsslayer$i);\n";
                    if ("0" == $conf["gis_ol_georss_".$i."_visibility"]) {
                        echo "georsslayer$i.setVisibility(false);\n";
                    }
                }
            }
        }
        echo "errors_georss='$errors_georss';\n";
        echo "ReportErrors('status_georss',errors_georss);\n";
    }

    // KML URL feeds
    if (1 == $conf['gis_ol_kml_enable']) {
        $errors_kml="";
        if(function_exists(curl_init)){
            $dir = $global['approot'].'www/tmp/kml_cache';
            mkdir($dir);
            // Download KML/KMZ files & cache before display
            for ($i = 1; $i <= $conf['gis_ol_kml']; $i++) {
                if (1==$conf["gis_ol_kml_".$i."_enabled"]) {
                    $name = $conf["gis_ol_kml_".$i."_name"];
                    $url = $conf["gis_ol_kml_".$i."_url"];
                    $file=end(explode('/',$url));
                    $ext=end(explode('.',$url));
                    $path = $dir."/".$file;
                    $ch = curl_init();
                    curl_setopt($ch, CURLOPT_URL,$url);
                    curl_setopt($ch, CURLOPT_RETURNTRANSFER,1); 
                    curl_setopt($ch, CURLOPT_FAILONERROR,1);
                    $xmlResponse = curl_exec($ch);
                    $errnum=curl_errno($ch);
                    curl_close($ch);
                    // if errors
                    if (!0==$errnum) {
                        if ("kmz"==$ext) {
                            // Provide Unzipped version to check for in cache
                            $basename=reset(explode('.',$file));
                            $file = $basename.".kml";
                            $path = $dir."/".$file;
                        }
                        if (!file_exists($path)) {
                            $errors_kml.='<b>'._t("Warning")."</b>: \"$url\" "._t("inaccessible & no cached copy available").". \"$name\" "._t("layer not loaded").'.<br />';
                            $display=0;
                        } else {
                            // mtime() better on Win32
                            $timestamp=filemtime($path);
                            $stale=date("d M Y", $timestamp);
                            $errors_kml.='<b>'._t("Warning")."</b>: \"$url\" "._t("inaccessible").". \"$name\" "._t("layer loaded from cache. Last downloaded")." $stale.<br />";
                            $display=1;
                        }
                    } else {
                        // write out file
                        // ToDo: Catch for folder/file not being writable
                        $handle = fopen($path, 'w');
                        fwrite($handle, $xmlResponse);
                        fclose($handle);
                        $display=1;
                        if ("kmz"==$ext) {
                            //Unzip
                            // PHP 5.2.0+ or PECL:
                            if(function_exists("zip_open")) {
                                //Can't report status as PHP still processing - page not yet rendered
                                //echo "ReportErrors('status_kml','Decompressing KMZ....');\n";
                                $dir = $global['approot'].'www/tmp/kml_cache/';
                                $zipped = $path;
                                $zip = zip_open($zipped);
                                while($zip_entry = zip_read($zip)) {
                                    $entry = zip_entry_open($zip,$zip_entry);
                                    $filename = zip_entry_name($zip_entry);
                                    $target_dir = $dir.substr($filename,0,strrpos($filename,'/'));
                                    $filesize = zip_entry_filesize($zip_entry);
                                    if (is_dir($target_dir) || mkdir($target_dir)) {
                                        if ($filesize > 0) {
                                            $contents = zip_entry_read($zip_entry, $filesize);
                                            file_put_contents($dir.$filename,$contents);
                                            $ext_contents=end(explode('.',$filename));
                                            if ("kml"==$ext_contents) {
                                                $input=$dir.$filename;
                                                $output=$dir.$filename.".w";
                                                $lines=file($input);
                                                $handle = fopen($output, 'w');
                                                foreach ($lines as $line_num => $line) {
                                                    //ToDo: Catch Network Links
                                                    if ("<NetworkLink>"==trim($line)) {
                                                        foreach ($lines as $line_num => $line) {
                                                            if (strpos($line,"<href>")) {
                                                                $url = strstrbi($line,"<href>",false,false);
                                                                $url = strstrbi($url,"</href>",true,false);
                                                                $errors_kml.="$url <br />";
                                                    //            $ch = curl_init();
                                                    //            curl_setopt($ch, CURLOPT_URL,$url);
                                                    //            curl_setopt($ch, CURLOPT_RETURNTRANSFER,1); 
                                                    //            curl_setopt($ch, CURLOPT_FAILONERROR,1);
                                                    //            $xmlResponse = curl_exec($ch);
                                                    //            $errnum=curl_errno($ch);
                                                    //            curl_close($ch);
                                                                // if errors
                                                    //            if (!0==$errnum) {
                                                    //                $errors_kml.='<b>'._t("Warning")."</b>: "._t("Network Link")." \"$url\" "._t("inaccessible")."<br />";
                                                    //                $display=0;
                                                    //                continue 12;
                                                    //            }
                                                            }
                                                        }
                                                        continue 2;
                                                    }
                                                    // Rewrite file to use correct path
                                                    $search="<img src='";
                                                    $replace="<img src='tmp/kml_cache/";
                                                    $line_out=str_replace($search,$replace,$line);
                                                    $search="<href>";
                                                    $replace="<href>tmp/kml_cache/";
                                                    $line=str_replace($search,$replace,$line_out);
                                                    // If the URL was remote not local, then put it back!
                                                    $search="<href>tmp/kml_cache/http://";
                                                    $replace="<href>http://";
                                                    $line_out=str_replace($search,$replace,$line);
                                                    fwrite($handle, $line_out);
                                                }
                                                fclose($handle);
                                                // All KMZ files seem to have just 'doc.kml' inside so make them more identifable & support multiple simultaneous feeds
                                                // (Multiple files in the normal 'files' folder are less likely to collide, but could be fixed by more rewriting)
                                                $basename=reset(explode('.',$file));
                                                $newname = $dir.$basename.".kml";
                                                rename($output, $newname);
                                                // remove non-rewritten file:
                                                unlink ($input);
                                            }
                                        }
                                    }
                                }
                            // remove zipped file:
                            unlink ($zipped);
                            // Provide Unzipped version to display in OL
                            $file = $basename.".kml";
                            }
                        }
                    }
                    if (1==$display) {
                        $path='tmp/kml_cache/'.$file;
                        echo "var kmllayer$i = new OpenLayers.Layer.GML( \"$name\", \"$path\", { projection: proj4326"; 
                        echo ", format: OpenLayers.Format.KML, formatOptions: { extractStyles: true, extractAttributes: true }});\n";
                        echo "map.addLayer(kmllayer$i);\n";
                        if ("0" == $conf["gis_ol_kml_".$i."_visibility"]) {
                            echo "kmllayer$i.setVisibility(false);\n";
                        }
                        echo "selectControlkml$i = new OpenLayers.Control.SelectFeature(map.layers[map.getLayerIndex(kmllayer$i)],\n";
                        echo "{onSelect: onFeatureSelectkml$i, onUnselect: onFeatureUnselect});\n";
                        echo "map.addControl(selectControlkml$i);\n";
                        echo "selectControlkml$i.activate();\n";
                        echo "function onPopupClosekml$i(evt) {\n";
                        echo "    selectControlkml$i.unselect(selectedFeaturekml$i);\n";
                        echo "}\n";
                        echo "function onFeatureSelectkml$i(feature) {\n";
                        echo "    selectedFeaturekml$i = feature;\n";
                        echo "    popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                        echo "        feature.geometry.getBounds().getCenterLonLat(),\n";
                        echo "        new OpenLayers.Size(100,100),\n";
                        echo "        \"<h2>\"+feature.attributes.name + \"</h2>\" + feature.attributes.description,\n";
                        echo "        null, true, onPopupClosekml$i);\n";
                        echo "    feature.popup = popup;\n";
                        echo "    map.addPopup(popup);\n";
                        echo     "}\n";
                    }   
                }
            }
         } else {
            $errors_kml='<b>'._t("Warning").'</b>: '._t("PHP has no libcurl support. KML layers not being cached & no support possible for KMZ files").'.<br />';
            // Load KML files direct via URL
            for ($i = 1; $i <= $conf['gis_ol_kml']; $i++) {
                if (1==$conf["gis_ol_kml_".$i."_enabled"]) {
                    $name = $conf["gis_ol_kml_".$i."_name"];
                    $url = $conf["gis_ol_kml_".$i."_url"];
                    echo "var kmllayer$i = new OpenLayers.Layer.GML( \"$name\", \"$url\", { projection: proj4326"; 
                    echo ", format: OpenLayers.Format.KML, formatOptions: { extractStyles: true, extractAttributes: true }});\n";
                    echo "map.addLayer(kmllayer$i);\n";
                    if ("0" == $conf["gis_ol_kml_".$i."_visibility"]) {
                        echo "kmllayer$i.setVisibility(false);\n";
                    }
                    echo "selectControlkml$i = new OpenLayers.Control.SelectFeature(map.layers[map.getLayerIndex(kmllayer$i)],\n";
                    echo "{onSelect: onFeatureSelectkml$i, onUnselect: onFeatureUnselect});\n";
                    echo "map.addControl(selectControlkml$i);\n";
                    echo "selectControlkml$i.activate();\n";
                    echo "function onPopupClosekml$i(evt) {\n";
                    echo "    selectControlkml$i.unselect(selectedFeaturekml$i);\n";
                    echo "}\n";
                    echo "function onFeatureSelectkml$i(feature) {\n";
                    echo "    selectedFeaturekml$i = feature;\n";
                    echo "    popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                    echo "        feature.geometry.getBounds().getCenterLonLat(),\n";
                    echo "        new OpenLayers.Size(100,100),\n";
                    echo "        \"<h2>\"+feature.attributes.name + \"</h2>\" + feature.attributes.description,\n";
                    echo "        null, true, onPopupClosekml$i);\n";
                    echo "    feature.popup = popup;\n";
                    echo "    map.addPopup(popup);\n";
                    echo "}\n";
                }
            }
        }
        echo "errors_kml='$errors_kml';\n";
        echo "ReportErrors('status_kml',errors_kml);\n";
    }
 
    // Files
    if (1 == $conf['gis_ol_files_enable']) {
        $errors_files="";
        for ($i = 1; $i <= $conf['gis_ol_files']; $i++) {
            if (1==$conf["gis_ol_files_".$i."_enabled"]) {
                $name = $conf["gis_ol_files_".$i."_name"];
                $filename = $conf["gis_ol_files_".$i."_filename"];
                $path='res/OpenLayers/files/'.$filename;
                if(file_exists($path)){
                    $ext=end(explode('.',$filename));
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
                    if ("KML"==strtoupper($ext)) {
                        echo "selectControl$i = new OpenLayers.Control.SelectFeature(map.layers[map.getLayerIndex(fileslayer$i)],\n";
                        echo "{onSelect: onFeatureSelect$i, onUnselect: onFeatureUnselect});\n";
                        echo "map.addControl(selectControl$i);\n";
                        echo "selectControl$i.activate();\n";
                        echo "function onPopupClose$i(evt) {\n";
                        echo "    selectControl$i.unselect(selectedFeature$i);\n";
                        echo "}\n";
                        echo "function onFeatureSelect$i(feature) {\n";
                        echo "    selectedFeature$i = feature;\n";
                        echo "    popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                        echo "        feature.geometry.getBounds().getCenterLonLat(),\n";
                        echo "        new OpenLayers.Size(100,100),\n";
                        echo "        \"<h2>\"+feature.attributes.name + \"</h2>\" + feature.attributes.description,\n";
                        echo "        null, true, onPopupClose$i);\n";
                        echo "    feature.popup = popup;\n";
                        echo "    map.addPopup(popup);\n";
                        echo "}\n";
                    }
                } else {
                    $errors_files.='<b>'._t("Warning")."</b>: \"$filename\" "._t("not found").". \"$name\" "._t("layer not loaded").'.<br />';
                }
            }
        }
        echo "errors_files='$errors_files';\n";
        echo "ReportErrors('status_files',errors_files);\n";
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
 * @access public
 */
 function ol_add_marker($name)
 {
    global $conf;
    global $global;
    $db = $global['db'];
    $folder = $conf['gis_marker_folder'];
    $marker = $conf['gis_marker'];
    $markersize = $conf['gis_marker_size'];
?>

    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);
    var size = new OpenLayers.Size(<?=$markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?=$folder?><?=$marker?>',size,offset);
	
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
 * @access public
 */
 function ol_show_markers($array)
 {
    global $conf;
    global $global;
    $db = $global['db'];
    $folder = $conf['gis_marker_folder'];
    $marker = $conf['gis_marker'];
    $markersize = $conf['gis_marker_size'];
?>
	var markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);
	var size = new OpenLayers.Size(<?=$markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?=$folder?><?=$marker?>',size,offset);
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
 * @access public
 */
 function ol_show_wiki_markers($array)
 {
    global $conf;
    global $global;
    $folder = $conf['gis_marker_folder'];
    $marker = $conf['gis_marker'];
    $markersize = $conf['gis_marker_size'];
?>
    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);
    var size = new OpenLayers.Size(<?=$markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?=$folder?><?=$marker?>',size,offset);
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
 * @access public
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
        //$markersize = (isset($array[$i]["markersize"]))?$array[$i]["markersize"]:"20,34";
        //var size = new OpenLayers.Size($markersize); // icon size
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
 * + function to support KML popups unselect
 * called by all show functions in openlayers plugin handler
 * @access public
 */
function ol_functions()
{
    global $conf;
    // close init()
    echo "}\n";
    ?>
    // For KML layers
    function onFeatureUnselect(feature) {
        map.removePopup(feature.popup);
        feature.popup.destroy();
        feature.popup = null;
    }
    function ReportErrors(div,text) {
         $(div).innerHTML = text;
    }
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
            $("status_osm").innerHTML = text;
    }
    <?php
    if ((1 == $conf['gis_ol_osm']) && (1 == $conf['gis_ol_osm_mapnik'] || 1 == $conf['gis_ol_osm_tiles'])) {
    ?>
        function osm_getTileURL(bounds) {
            var res = this.map.getResolution();
            var x = Math.round((bounds.left - this.maxExtent.left) / (res * this.tileSize.w));
            var y = Math.round((this.maxExtent.top - bounds.top) / (res * this.tileSize.h));
            var z = this.map.getZoom();
            var limit = Math.pow(2, z);
            if (y < 0 || y >= limit) {
                return OpenLayers.Util.getImagesLocation() + "404.png";
            } else {
                x = ((x % limit) + limit) % limit;
                return this.url + z + "/" + x + "/" + y + "." + this.type;
            }
        }
    <?php
    }
}
    
?>
