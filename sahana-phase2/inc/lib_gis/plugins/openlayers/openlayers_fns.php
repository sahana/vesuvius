<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: openlayers_fns.php,v 1.69 2009-08-22 17:17:26 ravithb Exp $
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
    if (0==$conf['gis_ol_wms_enable'] || "EPSG:900913"==$conf["gis_ol_projection"]) {
        if ((1 == $conf['gis_ol_google']) && (1 == $conf['gis_ol_google_sat'] || 1 == $conf['gis_ol_google_maps'] || 1 == $conf['gis_ol_google_hybrid'])) {
            $key = $conf['gis_google_key'];
            echo "<script src='http://maps.google.com/maps?file=api&v=2&key=$key' type=\"text/javascript\"></script>\n";
        }

        if (1 == $conf['gis_ol_multimap']) {
            $key = $conf['gis_multimap_key'];
            echo "<script src='http://clients.multimap.com/API/maps/1.1/$key' type=\"text/javascript\"></script>\n";
        }

        if ((1 == $conf['gis_ol_virtualearth']) && (1 == $conf['gis_ol_virtualearth_aerial'] || 1 == $conf['gis_ol_virtualearth_maps'] || 1 == $conf['gis_ol_virtualearth_hybrid'])) {
            echo "<script src='http://dev.virtualearth.net/mapcontrol/mapcontrol.ashx?v=6.1'></script>\n";
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
<?php
}

/**
 * OpenLayers loader
 * called by show_map in openlayers plugin handler
 * @access public
 */
function ol_onload_start()
{
    global $conf;
?>
    <script type="text/javascript">
    
    // make map available for easy debugging
    var map;

    // make feature and popup available
    var currentFeature;
    var currentPopup;

    // make markers layer available
    var markersLayer;
    var featuresLayer;

    // Make Controls Available
    var selectControl;
    var dragControl;
    //var modifyControl;
    var pointControl;
    var lineControl;
    var polygonControl;
    
    // avoid pink tiles
    OpenLayers.IMAGE_RELOAD_ATTEMPTS = 3;
    OpenLayers.Util.onImageLoadErrorColor = "transparent";

    // Set Proxy Host
    OpenLayers.ProxyHost = '<?php echo $conf['proxy_path']?>';

    var lon = <?php echo $conf['gis_center_x']?>;
    var lat = <?php echo $conf['gis_center_y']?>;
    var zoom = <?php echo $conf['gis_zoom']?>;

    // See - http://crschmidt.net/~crschmidt/spherical_mercator.html#reprojecting-points
    var proj4326 = new OpenLayers.Projection("EPSG:4326");
    var projection_current = new OpenLayers.Projection('<?php echo $conf['gis_ol_projection']?>');
    var point = new OpenLayers.LonLat(lon, lat);

    // Map Options
    var options = {
        displayProjection: proj4326,
        projection: projection_current,
        units: "<?php echo $conf['gis_ol_units']?>",
        <?php
        if($conf['gis_ol_maxResolution'] != ''){
            ?>
            maxResolution: <?php echo  $conf['gis_ol_maxResolution'] ?>,
            <?php
        }
        if($conf['gis_ol_maxExtent'] != ''){
            ?>
            maxExtent: new OpenLayers.Bounds(<?php echo  $conf['gis_ol_maxExtent'] ?>),
            <?php
        }
        //if($conf['gis_ol_restrictExtent'] != ''){
            ?>
            //restrictedExtent: new OpenLayers.Bounds(<?php echo  $conf['gis_ol_restrictExtent'] ?>)
            <?php
        //}
        ?>
    };

    // Start Map
    function initMap()
    {
    map = new OpenLayers.Map('map', options);
<?php
}

// Add controls to the map
function ol_onload_controls($options)
{
    // Always have standard base set.
    ol_controls_standard();
    switch($options){
        case 1:
            ol_controls_add();
            // Start with navigate activated.
            echo 'shn_gis_map_control_navigate();';
            break;
        case 2:
            ol_controls_add_edit();
            // Start with select activated.
            echo 'shn_gis_map_control_select();';
            break;
        default:
            break;
    }
}

function ol_controls_standard()
{
?>
    map.addControl(new OpenLayers.Control.LayerSwitcher());
    map.addControl(new OpenLayers.Control.PanZoomBar());
    map.addControl(new OpenLayers.Control.ScaleLine());
    map.addControl(new OpenLayers.Control.MousePosition());
    map.addControl(new OpenLayers.Control.OverviewMap({mapOptions: options}));
<?php
}

function ol_controls_add()
{
?>   
    // Add control to add new Points to the map.
    pointControl = new OpenLayers.Control.DrawFeature(featuresLayer, OpenLayers.Handler.Point);
    pointControl.featureAdded = shn_gis_map_add_geometry;
    map.addControl(pointControl);
    // Add control to add new Lines to the map.
    lineControl = new OpenLayers.Control.DrawFeature(featuresLayer, OpenLayers.Handler.Path);
    lineControl.featureAdded = shn_gis_map_add_geometry;
    map.addControl(lineControl);
    // Add control to add new Polygons to the map.
    polygonControl = new OpenLayers.Control.DrawFeature(featuresLayer, OpenLayers.Handler.Polygon);
    polygonControl.featureAdded = shn_gis_map_add_geometry;
    map.addControl(polygonControl);
<?php
}

function ol_controls_add_edit()
{ 
?>
    // Add control to select features (showing info popup).
    selectControl = new OpenLayers.Control.SelectFeature(featuresLayer, {
        onSelect: onFeatureSelect_1,
        onUnselect: onFeatureUnselect_1,
        multiple: false,
        clickout: true,
        toggle: true
    });
    map.addControl(selectControl);

    // Add control to drag internal features around the map.
    dragControl = new OpenLayers.Control.DragFeature(featuresLayer, {
        onComplete: shn_gis_popup_edit_position
    });
    map.addControl(dragControl);

    // Add control to modify the shape of internal features on the map.
    // WARNING this seems to cause select feature to behaviour strangely 
    //(eg being able to drag a selected feature even if modify is disabled)
    //modifyControl = new OpenLayers.Control.ModifyFeature(featuresLayer);
    //map.addControl(modifyControl);
    //modifyControl.mode = OpenLayers.Control.ModifyFeature.RESHAPE;
    //modifyControl.mode &= ~OpenLayers.Control.ModifyFeature.DRAG;

    // Add control to add new points to the map.
    pointControl = new OpenLayers.Control.DrawFeature(featuresLayer, OpenLayers.Handler.Point);
    pointControl.featureAdded = shn_gis_map_create_feature;
    map.addControl(pointControl);

    // Add control to add new lines to the map.
    lineControl = new OpenLayers.Control.DrawFeature(featuresLayer, OpenLayers.Handler.Path);
    lineControl.featureAdded = shn_gis_map_create_feature;
    map.addControl(lineControl);

    // Add control to add new polygons to the map.
    polygonControl = new OpenLayers.Control.DrawFeature(featuresLayer, OpenLayers.Handler.Polygon);
    polygonControl.featureAdded = shn_gis_map_create_feature;
    map.addControl(polygonControl);
<?php
}

/**
 * Called to end the onload function
 */
function ol_onload_fin()
{
?>
    // Center the map.
    map.setCenter(point.transform(proj4326, map.getProjectionObject()), zoom);
    }
    window.onload(initMap());
<?php
}

/**
 * Load Layers onto the Map
 * called by show_map in openlayers plugin handler
 * @access public
 */
 function ol_layers_all()
 {
    global $conf;
    // Disable other base layers if using a non-sphericalMercator WMS projection
    if (0==$conf['gis_ol_wms_enable'] || "EPSG:900913"==$conf["gis_ol_projection"]) {
        ol_layers_base();
    }
    if (1 == $conf['gis_ol_wms_enable']) {
        ol_layers_WMS();
    }
    if (1 == $conf['gis_ol_tms_enable']) {
        ol_layers_TMS();
    }
    if (1 == $conf['gis_ol_georss_enable']) {
        ol_layers_georss();
    }
    if (1 == $conf['gis_ol_kml_enable']) {
        ol_layers_kml();
    }
    if (1 == $conf['gis_ol_files_enable']) {
        ol_layers_files();
    }
}

function ol_layers_features()
{
    echo 'featuresLayer = new OpenLayers.Layer.Vector("Feature");';
    echo "map.addLayer(featuresLayer);\n";
}
 
/**
  * Load External Base layers such as:
  * - OpenStreetMap
  * - Google Maps
  * - Multimap
  * - Virtual Earth
  * - Yahoo Maps
  */
function ol_layers_base()
{
    global $conf;
    global $global;
    // OpenStreetMap (listed 1st - promote Open Data!)
    if (1 == $conf['gis_ol_osm']) {
        if (1 == $conf['gis_ol_osm_mapnik']) {
            echo "var mapnik = new OpenLayers.Layer.TMS( \"OpenStreetMap (Mapnik)\", \"http://tile.openstreetmap.org/\", {type: 'png', getURL: osm_getTileURL, displayOutsideMaxExtent: true } );\n";
            echo "map.addLayer(mapnik);\n";
        }
        if (1 == $conf['gis_ol_osm_tiles']) {
            echo "var osmarender = new OpenLayers.Layer.TMS( \"OpenStreetMap (Osmarender)\", \"http://tah.openstreetmap.org/Tiles/tile/\", {type: 'png', getURL: osm_getTileURL, displayOutsideMaxExtent: true } );\n";
            echo "map.addLayer(osmarender);\n";
        }
    }
    // Google
    if (1 == $conf['gis_ol_google']) {
        if(1 == $conf['gis_ol_google_hybrid']) {
            echo "var googlehybrid = new OpenLayers.Layer.Google( \"Google Hybrid\" , {type: G_HYBRID_MAP, 'sphericalMercator': true } );\n";
            echo "map.addLayer(googlehybrid);\n";
        }
        if (1 == $conf['gis_ol_google_sat']) {
            echo "var googlesat = new OpenLayers.Layer.Google( \"Google Satellite\" , {type: G_SATELLITE_MAP, 'sphericalMercator': true } );\n";
            echo "map.addLayer(googlesat);\n";
        }
        if (1 == $conf['gis_ol_google_maps']) {
            echo "var googlemaps = new OpenLayers.Layer.Google( \"Google Map\" , {type: G_NORMAL_MAP, 'sphericalMercator': true } );\n";
            echo "map.addLayer(googlemaps);\n";
        }
        if (1 == $conf['gis_ol_google_terrain']) {
            echo "var googleterrain = new OpenLayers.Layer.Google( \"Google Terrain\" , {type: G_PHYSICAL_MAP, 'sphericalMercator': true } );\n";
            echo "map.addLayer(googleterrain);\n";
        }
    }
    // MultiMap
    if (1 == $conf['gis_ol_multimap']) {
        echo "var multimap = new OpenLayers.Layer.MultiMap( \"MultiMap\");\n";
        echo "map.addLayer(multimap);\n";
    }
    // MS VirtualEarth
    if (1 == $conf['gis_ol_virtualearth']) {
        if (1 == $conf['gis_ol_virtualearth_hybrid']) {
            echo "var vehybrid = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Hybrid\" , {type: VEMapStyle.Hybrid, 'sphericalMercator': true } );\n";
            //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
            echo "map.addLayer(vehybrid);\n";
        }
        if (1 == $conf['gis_ol_virtualearth_aerial']) {
            echo "var veaerial = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Aerial\" , {type: VEMapStyle.Aerial, 'sphericalMercator': true } );\n";
            //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
            echo "map.addLayer(veaerial);\n";
        }
        if (1 == $conf['gis_ol_virtualearth_maps']) {
            echo "var veroad = new OpenLayers.Layer.VirtualEarth( \"Virtual Earth Road\" , {type: VEMapStyle.Road, 'sphericalMercator': true } );\n";
            //echo "{ minZoomLevel: 4, maxZoomLevel: 6 });\n";
            echo "map.addLayer(veroad);\n";
        }
    }
    // Yahoo
    if (1 == $conf['gis_ol_yahoo']) {
        if (1 == $conf['gis_ol_yahoo_hybrid']) {
            echo "var yahoohybrid = new OpenLayers.Layer.Yahoo( \"Yahoo Hybrid\", {'type': YAHOO_MAP_HYB, 'sphericalMercator': true } );\n";
            echo "map.addLayer(yahoohybrid);\n";
        }
        if (1 == $conf['gis_ol_yahoo_sat']) {
            echo "var yahoosat = new OpenLayers.Layer.Yahoo( \"Yahoo Satellite\", {'type': YAHOO_MAP_SAT, 'sphericalMercator': true } );\n";
            echo "map.addLayer(yahoosat);\n";
        }
        if (1 == $conf['gis_ol_yahoo_maps']) {
            echo "var yahoomaps = new OpenLayers.Layer.Yahoo( \"Yahoo Map\", {'sphericalMercator': true } );\n";
            echo "map.addLayer(yahoomaps);\n";
        }
    }
}

function ol_layers_WMS()
{
    global $conf;
    global $global;
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
    
// TMS : support available from OL 2.5 onwards
function ol_layers_TMS()
{
    global $conf;
    global $global;
    $tms = $conf["gis_ol_tms"];
    for ($i = 1; $i <= $tms; $i++) {
        if (1==$conf["gis_ol_tms_".$i."_enabled"]) {
            $name = $conf["gis_ol_tms_".$i."_name"];
            $url = $conf["gis_ol_tms_".$i."_url"];
            
            $layers = $conf["gis_ol_tms_".$i."_layers"];
            $format = $conf["gis_ol_tms_".$i."_format"];
            echo "var tmslayer$i = new OpenLayers.Layer.TMS( \"$name\",\n"; 
            echo "\"$url\",\n"; 
            echo "{";
            echo "layername: '$layers', ";
            if (!null==$format) {
                echo "type:'$format', ";
            }
            echo "});\n";
            echo "map.addLayer(tmslayer$i);\n";
            if ("0" == $conf["gis_ol_tms_".$i."_visibility"]) {
                echo "tmslayer$i.setVisibility(false);\n";
            }
        }
    }
}

// GeoRSS feeds
function ol_layers_georss()
{
    global $conf;
    global $global;
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
    if (!""==$errors_georss){
        echo "errors_georss='$errors_georss';\n";
        echo "ReportErrors('status_georss',errors_georss);\n";
    }
}

// KML URL feeds
function ol_layers_kml()
{
    global $conf;
    global $global;
    $errors_kml="";
    if(function_exists(curl_init)){
        $dir = $global['approot'].'www/tmp/kml_cache';
        mkdir($dir);
        // Download KML/KMZ files & cache before display
        // ToDo Make this an async call to a separate PHP script
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
                                                // Catch Network Links
                                                if ("<NetworkLink>"==trim($line)) {
                                                    foreach ($lines as $line_num => $line) {
                                                        if (strpos($line,"<href>")) {
                                                            $url = strstrbi($line,"<href>",false,false);
                                                            $url = strstrbi($url,"</href>",true,false);
                                                            $ch = curl_init();
                                                            curl_setopt($ch, CURLOPT_URL,$url);
                                                            curl_setopt($ch, CURLOPT_RETURNTRANSFER,1); 
                                                            curl_setopt($ch, CURLOPT_FAILONERROR,1);
                                                            $xmlResponse = curl_exec($ch);
                                                            $errnum=curl_errno($ch);
                                                            curl_close($ch);
                                                            // if errors
                                                            if (!0==$errnum) {
                                                                $errors_kml.='<b>'._t("Warning")."</b>: "._t("Network Link")." \"$url\" "._t("inaccessible")."<br />";
                                                                $display=0;
                                                                continue 12;
                                                            } else {
                                                                // write out file
                                                                // ToDo: Catch for folder/file not being writable
                                                                $handle = fopen($path, 'w');
                                                                fwrite($handle, $xmlResponse);
                                                                fclose($handle);
                                                                if ("kmz"==$ext) {
                                                                    //Unzip
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
                                                                                        if (strpos($line,"<GroundOverlay>")) {
                                                                                            $errors_kml.='<b>'._t("Warning").'</b>: "GroundOverlay" '._t("not supported in")." OpenLayers yet. \"$name\" "._t("layer may not work properly").'.<br />';
                                                                                            continue 1;
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
                                                    }
                                                    continue 2;
                                                }
                                                if (strpos($line,"<GroundOverlay>")) {
                                                    $errors_kml.='<b>'._t("Warning").'</b>: "GroundOverlay" '._t("not supported in")." OpenLayers yet. \"$name\" "._t("layer may not work properly").'.<br />';
                                                    continue 1;
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
                    echo "    if (\"undefined\" === feature.attributes.description)\n{\n";
                    echo "        popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                    echo "            feature.geometry.getBounds().getCenterLonLat(),\n";
                    echo "            new OpenLayers.Size(100,100),\n";
                    echo "            \"<h2>\" + feature.attributes.name + \"</h2>\" + feature.attributes.description,\n";
                    echo "            null, true, onPopupClose$i);\n";
                    echo "    }\nelse\n{";
                    echo "        popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                    echo "            feature.geometry.getBounds().getCenterLonLat(),\n";
                    echo "            new OpenLayers.Size(100,100),\n";
                    echo "            \"<h2>\" + feature.attributes.name + \"</h2>\",\n";
                    echo "            null, true, onPopupClose$i);\n";
                    echo "    }\n";
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
                echo "    if (\"undefined\" === feature.attributes.description)\n{\n";
                echo "        popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                echo "            feature.geometry.getBounds().getCenterLonLat(),\n";
                echo "            new OpenLayers.Size(100,100),\n";
                echo "            \"<h2>\" + feature.attributes.name + \"</h2>\" + feature.attributes.description,\n";
                echo "            null, true, onPopupClose$i);\n";
                echo "    }\nelse\n{";
                echo "        popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                echo "            feature.geometry.getBounds().getCenterLonLat(),\n";
                echo "            new OpenLayers.Size(100,100),\n";
                echo "            \"<h2>\" + feature.attributes.name + \"</h2>\",\n";
                echo "            null, true, onPopupClose$i);\n";
                echo "    }\n";
                echo "    feature.popup = popup;\n";
                echo "    map.addPopup(popup);\n";
                echo "}\n";
            }
        }
    }
    if (!""==$errors_kml){
        echo "errors_kml='$errors_kml';\n";
        echo "ReportErrors('status_kml',errors_kml);\n";
    }
}
 
// Files: OSM, KML, GML
function ol_layers_files()
{
    global $conf;
    global $global;
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
                    echo "    if (\"undefined\" === feature.attributes.description)\n{\n";
                    echo "        popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                    echo "            feature.geometry.getBounds().getCenterLonLat(),\n";
                    echo "            new OpenLayers.Size(100,100),\n";
                    echo "            \"<h2>\" + feature.attributes.name + \"</h2>\" + feature.attributes.description,\n";
                    echo "            null, true, onPopupClose$i);\n";
                    echo "    }\nelse\n{";
                    echo "        popup = new OpenLayers.Popup.FramedCloud(\"chicken\",\n";
                    echo "            feature.geometry.getBounds().getCenterLonLat(),\n";
                    echo "            new OpenLayers.Size(100,100),\n";
                    echo "            \"<h2>\" + feature.attributes.name + \"</h2>\",\n";
                    echo "            null, true, onPopupClose$i);\n";
                    echo "    }\n";
                    echo "    feature.popup = popup;\n";
                    echo "    map.addPopup(popup);\n";
                    echo "}\n";
                }
            } else {
                $errors_files.='<b>'._t("Warning")."</b>: \"$filename\" "._t("not found").". \"$name\" "._t("layer not loaded").'.<br />';
            }
        }
    }
    if (!""==$errors_files){
        echo "errors_files='$errors_files';\n";
        echo "ReportErrors('status_files',errors_files);\n";
    }
}

/**
 * Allow addition of a Marker
 * called by show_add_marker_map in openlayers plugin handler
 * @access public
 */
 function ol_add_marker($name,$icon)
 {
    global $conf;
    global $global;
    $markersize = $conf['gis_marker_size'];
    if(isset($icon) && $icon != ''){
        $marker = $icon;
    } else{
        $marker = $conf['gis_marker_folder'] . $conf['gis_marker'];
    }
?>

    var markers = new OpenLayers.Layer.Markers("Markers");
    map.addLayer(markers);
    var size = new OpenLayers.Size(<?php echo $markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?php echo $marker?>',size,offset);
	
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
        // Update form fields
        document.getElementById("gps_x").value = lon_new;
        document.getElementById("gps_y").value = lat_new;
        // store x,y coords in hidden variables named loc_x, loc_y
        // must be set via calling page
        var x_point=document.getElementsByName("loc_x");
        var y_point=document.getElementsByName("loc_y");
        x_point[0].value=lon_new;
        y_point[0].value=lat_new;
});
<?php
}

function ol_add_feature($name, $icon = 'null')
{
?>
    function shn_gis_map_add_geometry(feature){
    
        var fcopy = feature.clone();
        // need for later.
        var fcopygeom = fcopy.geometry.clone();
        var lonlat = fcopy.geometry.getBounds().getCenterLonLat();
        var proj_current = map.getProjectionObject();
        lonlat.transform(proj_current, proj4326);
        var lon_new = lonlat.lon;
        var lat_new = lonlat.lat;
        var wkt_new = fcopy.geometry.transform(proj_current, proj4326).toString();
        var type_new = featureTypeStr(fcopy);
        
        // Update form fields
        var x_gps = document.getElementById("gps_x");
        var y_gps = document.getElementById("gps_y");
        if( x_gps != null && y_gps != null){
            x_gps.value = lon_new;
            y_gps.value = lat_new;
        }

        // store x,y coords in hidden variables named loc_x, loc_y
        // must be set via calling page
        var x_point = document.getElementsByName("loc_x");
        var y_point = document.getElementsByName("loc_y");
        if(x_point != null && y_point != null){
            x_point[0].value = lon_new;
            y_point[0].value = lat_new;
        }
        // store type
        var loc_type = document.getElementsByName("loc_type");
        if(loc_type != null){
            loc_type[0].value = type_new;
        }
        // store wkt value
        var wkt_point = document.getElementsByName("loc_wkt");
        if(wkt_point != null){
            wkt_point[0].value = wkt_new;
        }
        
        // Remove last plot from layer
        featuresLayer.destroyFeatures(featuresLayer.features);
        
        // Add icon.  
        add_Feature(featuresLayer, 'newFeature', fcopygeom, '<?php echo  $icon ?>');
    }
<?php
}

/**
 * Show the Markers layer
 * called by show_map_with_markers in openlayers plugin handler
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
	var markers = new OpenLayers.Layer.Markers("Markers");
	map.addLayer(markers);
	var size = new OpenLayers.Size(<?php echo $markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?php echo $folder?><?php echo $marker?>',size,offset);
    var currentPopup;
<?php
	for($i=0;$i< sizeof($array);$i++){
        $lon=$array[$i]["lon"];
        $lat=$array[$i]["lat"];
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
    _ol_generate_add_marker();
}

/**
 * Show the Markers layer
 * called by show_map_polylines in openlayers plugin handler
 * @access public
 */
 function ol_show_cap_markers($cords,$title)
 {?>    
 	document.getElementById("outer_map").style.width="100%";
    var amap = document.getElementById("map");
    amap.style.width = "90%";
  	amap.style.height = "400px";
  	
        
        
  	<?php
  	global $conf;
    global $global;
    $db = $global['db'];
    $folder = $conf['gis_marker_folder'];
    $marker = $conf['gis_marker'];
    $markersize = $conf['gis_marker_size'];
    
    echo "var proj_current = map.getProjectionObject();\n";
        
?>
	var markers = new OpenLayers.Layer.Markers("CAP Alerts");
	map.addLayer(markers);
	var size = new OpenLayers.Size(<?php echo $markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?php echo $folder?><?php echo $marker?>',size,offset);
    var currentPopup;
    var result_style = OpenLayers.Util.applyDefaults({
             strokeWidth: 7,
             strokeColor: "#ff0000",
             fillOpacity: 0
         }, OpenLayers.Feature.Vector.style['default']);
	var highlight = new OpenLayers.Layer.Vector("Lines", {style:result_style});
    //map.addLayer(highlight);
    var parser = new OpenLayers.Format.WKT();
   
    
<?php
	
	
    
  	for($i=0;$i< sizeof($cords);$i++){
        $lon=$cords[$i]["right"][1];
        $lat=$cords[$i]["right"][0];
        $lon1=$cords[$i]["right"][1];
        $lat1=$cords[$i]["right"][0];
        $name=$title[$i]["title"];
	$name=substr($name,0,20);
        $url=$title[$i]["link"];
        $days=$title[$i]["days"];
        $hours=$title[$i]["hours"];
        $pre_url="index.php?mod=cap&act=alert&stream=text&url=";
        if(preg_match("/.cap|.xml/", $url))
		$url=$pre_url.$url;
        echo "popupContentHTML = \"<b>$name</b><br />Alert arrived $days days $hours hours ago. <br /><a href='$url'>View</a><br /></p>\"\n";
        echo "var lonlat = new OpenLayers.LonLat($lon,$lat);\n";
        echo "var proj_current = map.getProjectionObject();\n";
        echo "lonlat.transform(proj4326, proj_current);\n";
        echo "addMarker(lonlat,popupContentHTML);\n";
        echo "var wkt = 'LINESTRING($lon $lat, $lon1 $lat1)';\n";
        echo "var feature = parser.read(wkt);\n";
        echo "highlight.addFeatures([feature]);\n";
        echo "map.zoomToExtent(new OpenLayers.Bounds($lon,$lat,$lon1,$lat1));\n";
        
           
       
	}
        _ol_generate_add_marker();
             
    
  ?>
   
                        
        
    <?php

}
		
/**
 * !!! DEPRECATED !!!
 *
 * Show the Markers layer with Wiki information
 * called by show_map_with_wiki_marker in openlayers plugin handler
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
    var markers = new OpenLayers.Layer.Markers("Markers");
    map.addLayer(markers);
    var size = new OpenLayers.Size(<?php echo $markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?php echo $folder?><?php echo $marker?>',size,offset);
    var currentPopup;
<?php
    for($i=0;$i< sizeof($array);$i++){
        $lon=$array[$i]["lon"];
        $lat=$array[$i]["lat"];
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
    _ol_generate_add_marker();   
}

/**
 * Show the Markers layer with Wiki information
 * + fill-in a pair of Lat/Lon fields based on which Marker is selected
 * called by show_map_with_wiki_marker in openlayers plugin handler
 * @access public
 */
function ol_show_wiki_markers_select($array,$lat_field,$lon_field)
 {
    global $conf;
    global $global;
    $folder = $conf['gis_marker_folder'];
    $marker = $conf['gis_marker'];
    $markersize = $conf['gis_marker_size'];
?>
    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);
    var size = new OpenLayers.Size(<?php echo $markersize?>); // icon size
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon('<?php echo $folder?><?php echo $marker?>',size,offset);
    var currentPopup;
<?php
    for($i=0;$i< sizeof($array);$i++){
        $lon=$array[$i]["lon"];
        $lat=$array[$i]["lat"];
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
            // Convert back to LonLat for form fields
            var lonlat2 = new OpenLayers.LonLat(lonlat.lon,lonlat.lat);
            lonlat2.transform(proj_current, proj4326);
            // Update form fields
            document.getElementById('<?php echo $lon_field?>').value = lonlat2.lon;
            document.getElementById('<?php echo $lat_field?>').value = lonlat2.lat;
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
        $lon=$array[$i]["lon"];
        $lat=$array[$i]["lat"];
        $name=$array[$i]["name"];
        $url=$array[$i]["url"];
        $pre_url="index.php?";
        $url=$pre_url.$url;
        $marker_name=(isset($array[$i]["marker"]))?$array[$i]["marker"]:"marker";
        //$markersize = (isset($array[$i]["markersize"]))?$array[$i]["markersize"]:"20,34";
        //var size = new OpenLayers.Size($markersize); // icon size
?>
        var icon = new OpenLayers.Icon('<?php echo $folder?><?php echo $marker_name?>.png',size,offset);
<?php
	    echo "popupContentHTML = \"<b>$name</b><br /><a href='$url'>View</a><br /></p>\"\n";
        echo "var lonlat = new OpenLayers.LonLat($lon,$lat);\n";
        echo "var proj_current = map.getProjectionObject();\n";
        echo "lonlat.transform(proj4326, proj_current);\n";
        echo "addMarker(lonlat,popupContentHTML);\n";
    }
    _ol_generate_add_marker();
}
 
function ol_show_features_markers($features)
{
    global $conf;
    global $global;
    global $id;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    require_once $global['approot'] . '/inc/lib_gis/lib_gis_forms.inc';
    // Add Features Layer
    echo 'featuresLayer = new OpenLayers.Layer.Vector("Internal Features");';
    echo "var proj_current = map.getProjectionObject();\n";
    // Set id in case any features do not have uuids...
    $id = 0;
    // Place each feature
    foreach($features as $feature){
        // Set Feature uuid
        if(isset($feature['f_uuid'])){
            $feature_uuid = 'outer_' . $feature['f_uuid'];
        } else{
            $uuid = 'outer_popup_' . $id++; // :(
        }
        // Set Feautre Type
        if(isset($feature['f_type'])){
            $type = $feature['f_type'];
        } else{
            $type = 'point';
        }
        // Generate vars for html popup HTML content
        if(isset($feature['f_class'])){
            $feature_class = shn_gis_get_feature_class_uuid($feature['f_class']);
        } else{
            $feature_class = shn_gis_get_feature_class_uuid($conf['gis_feature_type_default']);
        }
        // Set icon
        if(isset($feature['icon'])){
            $icon = $feature['icon'];
        } else {
            $icon = $feature_class['c_icon'];
        }
        if($icon == ''){
            $fc = shn_gis_get_feature_class_uuid($conf['gis_feature_type_default']);
            $icon = $fc['c_icon'];
        }
        // Bit of a hacky way to do it. Especially the transform...
        $coordinates = shn_gis_coord_decode($feature['f_coords']);
        $coords = '';
        if(count($coordinates) == 1){
             $coords = $coords . "var coords = new Array(new OpenLayers.Geometry.Point((new OpenLayers.LonLat({$coordinates[$i][0]}, {$coordinates[$i][1]}).transform(proj4326, proj_current)).lon, (new OpenLayers.LonLat({$coordinates[$i][0]}, {$coordinates[$i][1]}).transform(proj4326, proj_current)).lat));\n"; 
        } else {
             $coords = $coords . "var coords = new Array(";
             $ctot = count($coordinates) - 1;
             for($i = 1; $i < $ctot; $i++){
                 $coords = $coords . "new OpenLayers.Geometry.Point((new OpenLayers.LonLat({$coordinates[$i][0]}, " .
                 		"{$coordinates[$i][1]}).transform(proj4326, proj_current)).lon, " .
                 		"(new OpenLayers.LonLat({$coordinates[$i][0]}, " .
                 		"{$coordinates[$i][1]}).transform(proj4326, proj_current)).lat), ";
             }
             if($ctot > 0){
             $coords = $coords . "new OpenLayers.Geometry.Point((new OpenLayers.LonLat({$coordinates[$i][0]}, {$coordinates[$i][1]}).transform(proj4326, proj_current)).lon, (new OpenLayers.LonLat({$coordinates[$i][0]}, {$coordinates[$i][1]}).transform(proj4326, proj_current)).lat)";   
             }
             $coords = $coords . ");\n";             
        }
        echo $coords;
        // Popup
        $html =  "var popupContentHTML = \"";
        $html = $html . shn_gis_form_popupHTML_view($feature);
        $html = $html . "\";\n";
        echo $html;
        // Create geometry of feature (point, line, polygon)
        echo "var geom = coordToGeom(coords, \"$type\");\n";
        echo "add_Feature_with_popup(featuresLayer, '$feature_uuid', geom, popupContentHTML, '$icon');\n";
    }
    // Add Feature layer
    echo "map.addLayer(featuresLayer);\n";
}
/**
 * Addtional Functions to support OSM & KML layers
 * called by all show functions in openlayers plugin handler
 * @access public
 */
function ol_functions()
{
    global $conf;
?>
    // General functions usable by all Layers
    
    // returns string type of a feature
    // return point if not line or poly ....danger....
    function featureTypeStr(feature){
        var type = 'point';
        var geotype = feature.geometry.CLASS_NAME;
        if(geotype == 'OpenLayers.Geometry.LineString'){
            type = 'line';
        } else if(geotype == 'OpenLayers.Geometry.Polygon'){
            type = 'poly';
        }
        return type;
    }
    // create geometries from point coords.
    function coordToGeom(coords, type){
        var geom = coords[0]
        if(type == 'point'){
            geom = coords[0]; // =  Array(new OpenLayers.Geometry.Point(lon, lat));
        } else if(type == 'line'){
            geom = new OpenLayers.Geometry.LineString(coords);
        } else if(type == 'poly'){
            geom = new OpenLayers.Geometry.Polygon(new Array(new OpenLayers.Geometry.LinearRing(coords)));
        } 
        return geom;
    }
    // Report Errors to a DIV
    function ReportErrors(div,text) {
         $(div).innerHTML = text;
    }
    // For KML layers
    function onFeatureUnselect(feature) {
        map.removePopup(feature.popup);
        feature.popup.destroy();
        feature.popup = null;
    }
    // For OSM File layers
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
    // For OSM Base layer
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
    // Add Control Functions
    _ol_generate_control_fns();
    // Add popup button_fns
    _ol_generate_popup_fns();
    // Generate ajax for popup boxes
    _ol_generate_popup_ajax();
}

function _ol_generate_popup_fns()
{ 
    ?>
    // On Creating a new feature Display a popup box to enter details.
    function shn_gis_map_create_feature(feature){
        // If adding a new popup before an old one is completed, kill old popup (current feature is set to null at end of process)
        if(currentFeature != null){
            currentFeature.popup.hide();
            featuresLayer.removeFeatures([currentFeature]);
            currentFeature.popup.destroy(currentFeature.popup);
            currentFeature.destroy();
        }
        // Generate Popup + Props
        var fc_id = null;
        var fc_lonlat = feature.geometry.getBounds().getCenterLonLat();
        var fc_size = null;
        var fc_contentHTML = "<?php echo  shn_gis_form_popupHTML_new(); ?>";
        var fc_anchor = null;
        var fc_closeBox = true; // Bad can close without create...
        var fc_closeBoxCallback = shn_gis_popup_new_cancel;
        var framedCloud = new OpenLayers.Popup.FramedCloud(fc_id, fc_lonlat, fc_size, fc_contentHTML, fc_anchor, fc_closeBox, fc_closeBoxCallback);
        framedCloud.autoSize = true;
        framedCloud.minSize = new OpenLayers.Size(460,270);
        // Add Popup
        feature.popup = framedCloud;
        map.addPopup(feature.popup);
        feature.popup.show();
        currentFeature = feature;
    }
    // Supports feature select control.
    function onFeatureSelect_1(feature){
        // Set global for back referencing
        currentFeature = feature;
        if (feature.popup.map == null) {
            map.addPopup(feature.popup);
            feature.popup.show();
        } else {
            feature.popup.toggle();
        }
    }
    // Supports feature select control.
    function onFeatureUnselect_1(feature) {
        feature.popup.hide();
    }
    // Supports feature select control.
    function onPopupClose(evt) {
        onFeatureUnselect_1(currentFeature);
    }
<?php
}

/**
 * Ajax form for shn_gis_form_feature_search
 *
 */
function _ol_generate_popup_ajax()
{
    $del_confirm = '"' . _t('Are you sure you wish to Delete Feature from system') . '"';
    $create_fail = '"' . _t('Failed to create new Feature.') . '"';
    $ajax_error = '"' . _t('Your browser does not support AJAX!') . '"';
    $popup_unable = '"' . _t('The module that created this feature does not support this action here. Navigate to the module manually to perform this action.') . '"';

?>
    var xmlHttp
    function shn_gis_popup_unable()
    {
        alert (<?php echo $popup_unable ?>);
    }
    function shn_gis_popup_print()
    {
        if (xmlHttp.readyState == 4){
            var textDoc = xmlHttp.responseText;
            currentFeature.popup.setContentHTML(textDoc);
        }
    }
    function shn_gis_popup_refresh_print()
    {
        if (xmlHttp.readyState == 4){
            var textDoc = xmlHttp.responseText;
            if(textDoc == '<delete />'){
                currentFeature.popup.hide();
                featuresLayer.removeFeatures([currentFeature]);
                currentFeature.popup.destroy(currentFeature.popup);
                currentFeature.destroy();
                //featuresLayer.redraw();
            } else{
                currentFeature.popup.setContentHTML(textDoc);
            }
        }
    }
    function shn_gis_popup_new_print()
    {
        if (xmlHttp.readyState == 4){
            var textDoc = xmlHttp.responseText;
            
            var geom = currentFeature.geometry.clone();
                  
            currentFeature.popup.hide();
            featuresLayer.removeFeatures([currentFeature]);
            currentFeature.popup.destroy(currentFeature.popup);
            currentFeature.destroy();
            currentFeature = null;
            //featuresLayer.redraw();
            if(!(textDoc == 'fail' || textDoc == '')){ 
                var uuidpos = textDoc.search('<uuid />');
                var iconURLPos = textDoc.search('<icon />');
                
                var uuid = textDoc.substring(0, uuidpos);
                var iconURL = textDoc.substring((uuidpos + 8), iconURLPos);
                var html = textDoc.substring((iconURLPos + 8));

                add_Feature_with_popup(featuresLayer, uuid, geom, html, iconURL);
            } else{
                alert(<?php echo $create_fail ?>);   
            }
        }
    }
    // Called by link in popup box
    function shn_gis_popup_new_ok(id){
        xmlHttp = GetXmlHttpObject();
        if (xmlHttp==null){
            alert (<?php echo $ajax_error ?>);
            return;
        }
        // Clone to stop any effects on the current feature.
        var cfcopy = currentFeature.clone();
        // returns string type of a feature
        // return point if not line or poly ....danger....
        var type = featureTypeStr(cfcopy);
        // Transform for db.
        var lonlat = cfcopy.geometry.getBounds().getCenterLonLat().clone();
        var proj_current = map.getProjectionObject();
        lonlat.transform(proj_current, proj4326);
        var lat = lonlat.lat;
        var lon = lonlat.lon;
        var wkt = cfcopy.geometry.transform(proj_current, proj4326).toString();
        var name  = document.getElementById(id + '_popup_name').value;
        var desc  = document.getElementById(id + '_popup_desc').value;
        var auth  = document.getElementById(id + '_popup_auth').value;
        var furl  = document.getElementById(id + '_popup_url').value;
        var add   = document.getElementById(id + '_popup_add').value;
        var edate = document.getElementById(id + '_popup_edate').value;
        // Send to db
        var url = 'index.php?act=gis_popup_new_ok&mod=xst&stream=text';
        url = url + "&type=" + type + "&center_lat=" + lat + "&center_lon=" + lon + "&wkt=" + wkt + "&name=" + name + "&desc=" + desc + "&auth=" + auth + "&url=" + furl + "&add=" + add + "&date=" + edate;
        url = url + "&sid=" + Math.random();
        xmlHttp.onreadystatechange = shn_gis_popup_new_print;
        xmlHttp.open("GET", url, true);
        xmlHttp.send(null);
    }
    // Called by link in popup box
    function shn_gis_popup_new_cancel(){
        currentFeature.popup.hide();
        featuresLayer.removeFeatures([currentFeature]);
        currentFeature.popup.destroy(currentFeature.popup);
        currentFeature.destroy();
        currentFeature = null;
    }
    // Called by link in popup box
    function shn_gis_popup_refresh(id)
    {
        xmlHttp = GetXmlHttpObject();
        if (xmlHttp == null){
            alert (<?php echo $ajax_error ?>);
            return;
        }

        var url = 'index.php?act=gis_popup_refresh&mod=xst&stream=text&id=' + id;
        url = url +"&sid=" + Math.random();
        xmlHttp.onreadystatechange = shn_gis_popup_refresh_print;
        xmlHttp.open("GET", url, true);
        xmlHttp.send(null);
    }
    // Called by link in popup box
    function shn_gis_popup_delete(id)
    {
        xmlHttp = GetXmlHttpObject();
        if (xmlHttp == null){
            alert (<?php $ajax_error ?>);
            return;
        }
        ok = confirm(<?php echo $del_confirm?>);
        if(ok){
            var url = 'index.php?act=gis_popup_delete&mod=xst&stream=text&id=' + id;
            url = url +"&sid=" + Math.random();
            xmlHttp.onreadystatechange = shn_gis_popup_refresh_print;
            xmlHttp.open("GET", url, true);
            xmlHttp.send(null);
        }
    }
     // Called by dragControl after editing a Features position
    function shn_gis_popup_edit_position(feature, pixel)
    {
        xmlHttp = GetXmlHttpObject();
        if (xmlHttp==null){
            alert (<?php echo $ajax_error ?>);
            return;
        }
        currentFeature = feature;
        // Move features popup to new location
        feature.popup.lonlat = feature.geometry.getBounds().getCenterLonLat();
        // Need id before clone
        var id  = feature.fid.substring(6)
        // Clone to stop any effects on the current feature.
        var cfcopy = feature.clone();
        // Transform for db.
        var lonlat = cfcopy.geometry.getBounds().getCenterLonLat().clone();
        var proj_current = map.getProjectionObject();
        lonlat.transform(proj_current, proj4326);
        var lat = lonlat.lat;
        var lon = lonlat.lon;
        var wkt = cfcopy.geometry.transform(proj_current, proj4326).toString();
        // Send to db
        var url='index.php?act=gis_popup_edit_position&mod=xst&stream=text&id=' + id;
        url = url + "&center_lat=" + lat + "&center_lon=" + lon + "&wkt=" + wkt;
        url = url +"&sid=" + Math.random();
        //xmlHttp.onreadystatechange = shn_gis_popup_print;
        xmlHttp.open("GET", url, true);
        xmlHttp.send(null);
    }
    // Called by link in popup box
    function shn_gis_popup_edit_details(id)
    {
        xmlHttp = GetXmlHttpObject();
        if (xmlHttp==null){
            alert (<?php echo $ajax_error ?>);
            return;
        }
        var url='index.php?act=gis_popup_edit_details&mod=xst&stream=text&id=' + id;
        url = url +"&sid=" + Math.random();
        xmlHttp.onreadystatechange = shn_gis_popup_print;
        xmlHttp.open("GET", url, true);
        xmlHttp.send(null);
    }
    function shn_gis_popup_edit_details_ok(id)
    {
        xmlHttp = GetXmlHttpObject();
        if (xmlHttp==null){
            alert (<?php echo $ajax_error ?>);
            return;
        }
        var name  = document.getElementById(id + '_popup_name').value;
        var desc  = document.getElementById(id + '_popup_desc').value;
        var auth  = document.getElementById(id + '_popup_auth').value;
        var furl   = document.getElementById(id + '_popup_url').value;
        var add   = document.getElementById(id + '_popup_add').value;
        var edate  = document.getElementById(id + '_popup_edate').value;
        var url = 'index.php?act=gis_popup_edit_details_ok&mod=xst&stream=text&id=' + id;
        url = url + "&name=" + name + "&desc=" + desc + "&auth=" + auth + "&url=" + furl + "&add=" + add + "&date=" + edate;
        url = url +"&sid=" + Math.random();
        xmlHttp.onreadystatechange = shn_gis_popup_print;
        xmlHttp.open("GET", url, true);
        xmlHttp.send(null);
    }
    function GetXmlHttpObject(){
        var xmlHttp=null;
        try{
            // Firefox, Opera 8.0+, Safari
            xmlHttp=new XMLHttpRequest();
        }
        catch (e){
            // Internet Explorer
            try{
                xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
            }
            catch (e){
                xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
            }
        }
        return xmlHttp;
    }
<?php
}

/**
 * Generates a function to add new features to the map with an icon and popup
 * 
 * It is IMPORTANT to remember that the geom type must be translated to the map's
 * projection before it is passed to this function.
 * 
 * @global <type> $conf
 */
function _ol_generate_add_feature_with_popup()
{
    global $conf;
    $conf['gis_marker_size'];
?>
    // Add marker to map
    function add_Feature_with_popup(layer, feature_id, geom, popupContentHTML, iconURL) {
        // Set icon dims
        var icon_img = new Image();
        icon_img.src = iconURL;
        var max_w = 25;
        var max_h = 35;
        var width = icon_img.width;
        var height = icon_img.height;
        if(width > max_w){
            height = ((max_w / width) * height);
            width = max_w;
        }
        if(height > max_h){
            width = ((max_h / height) * width);
            height = max_h;
        }
        // http://www.nabble.com/Markers-vs-Features--td16497389.html
        var style_marker = OpenLayers.Util.extend({}, OpenLayers.Feature.Vector.style['default']);
        //style_mark.pointRadius = 12;
        style_marker.graphicWidth = width;
        style_marker.graphicHeight = height;
        style_marker.graphicXOffset = -(width / 2);
        style_marker.graphicYOffset = -height;
        style_marker.externalGraphic = iconURL;
        style_marker.graphicOpacity = 1;
        // Create Feature Vector + Props
        var featureVec = new OpenLayers.Feature.Vector(geom, null, style_marker);
        featureVec.fid = feature_id;
        // Generate Popup + Props
        var fc_id = null;
        var fc_lonlat = featureVec.geometry.getBounds().getCenterLonLat();
        var fc_size = null;
        var fc_contentHTML = popupContentHTML;
        var fc_anchor = null;
        var fc_closeBox = true;
        var fc_closeBoxCallback = onPopupClose;
        var framedCloud = new OpenLayers.Popup.FramedCloud(fc_id, fc_lonlat, fc_size, fc_contentHTML, fc_anchor, fc_closeBox, fc_closeBoxCallback);
        // framedCloud = OpenLayers.Class(new OpenLayers.Popup.FramedCloud, {'autoSize': true});
        framedCloud.autoSize = true;
        framedCloud.minSize = new OpenLayers.Size(460,270);
        // Add Popup
        featureVec.popup = framedCloud;
        // Add Feature.
        layer.addFeatures([featureVec]);
    }
<?php
}

 function _ol_generate_add_feature()
{
    global $conf;
    $conf['gis_marker_size'];
?>
    // Add marker to map
    function add_Feature(layer, feature_id, geom, iconURL){
        // Set icon dims
        var icon_img = new Image();
        icon_img.src = iconURL;
        var max_w = 25;
        var max_h = 35;
        var width = icon_img.width;
        var height = icon_img.height;
        if(width > max_w){
            height = ((max_w / width) * height);
            width = max_w;
        }
        if(height > max_h){
            width = ((max_h / height) * width);
            height = max_h;
        }
        // http://www.nabble.com/Markers-vs-Features--td16497389.html
        var style_marker = OpenLayers.Util.extend({}, OpenLayers.Feature.Vector.style['default']);
        //style_mark.pointRadius = 12;
        style_marker.graphicWidth = width;
        style_marker.graphicHeight = height;
        style_marker.graphicXOffset = -(width / 2);
        style_marker.graphicYOffset = -height;
        style_marker.externalGraphic = iconURL;
        style_marker.graphicOpacity = 1;
        // Create Feature Vector + Props
        var featureVec = new OpenLayers.Feature.Vector(geom, null, style_marker);
        featureVec.fid = feature_id;
        // Add Feature.
        layer.addFeatures([featureVec]);
    }
<?php
}

function _ol_generate_add_marker()
{
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
 * Js Functions called by control buttons.
 */
function _ol_generate_control_fns()
{
    global $global;
    global $conf;
?>
   // Activate Control for navigating around the maps.
   function shn_gis_map_control_navigate(){
        shn_gis_map_control_deactivate_all();
        document.getElementById('gis_map_icon_select').style.backgroundImage = "url(res/OpenLayers/theme/default/img/move_feature_on.png)";
        document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Navigate') ?>';
    }
    // Activate Control for selecting features.
    function shn_gis_map_control_select(){
        shn_gis_map_control_deactivate_all();
        document.getElementById('gis_map_icon_select').style.backgroundImage = "url(res/OpenLayers/theme/default/img/move_feature_on.png)";
        document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Select') ?>';
        selectControl.activate();
    }
    // Activate Control for dragging features.
    function shn_gis_map_control_drag(){
        shn_gis_map_control_deactivate_all();
        document.getElementById('gis_map_icon_drag').style.backgroundImage = "url(res/OpenLayers/theme/default/img/pan_on.png)";
        document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Drag') ?>';
        dragControl.activate();
    }
    // Activate Control for modifying features.
    function shn_gis_map_control_modify(){
        shn_gis_map_control_deactivate_all();
        //document.getElementById('gis_map_icon_modify').style.backgroundImage = "url()";
        //document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Modify') ?>';
        //modifyControl.activate();
    }
    // Activate Control for adding point features.
    function shn_gis_map_control_add_point(){
        shn_gis_map_control_deactivate_all();
        document.getElementById('gis_map_icon_addpoint').style.backgroundImage = "url(res/OpenLayers/theme/default/img/draw_point_on.png)";
        document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Add Point') ?>';
        pointControl.activate();
    }
    // Activate Control for adding line features.
    function shn_gis_map_control_add_line(){
        shn_gis_map_control_deactivate_all();
        document.getElementById('gis_map_icon_addline').style.backgroundImage = "url(res/OpenLayers/theme/default/img/draw_line_on.png)";
        document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Add line') ?>';
        lineControl.activate();
    }
    // Activate Control for adding polygon features.
    function shn_gis_map_control_add_polygon(){
        shn_gis_map_control_deactivate_all();
        document.getElementById('gis_map_icon_addpolygon').style.backgroundImage = "url(res/OpenLayers/theme/default/img/draw_polygon_on.png)";
        document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Add Area') ?>';
        polygonControl.activate();
    }
    // Activate Control for drawing features freehand.
    function shn_gis_map_control_freehand(){
        if(lineControl.handler.freehand){
            document.getElementById('gis_map_icon_freehand').style.backgroundImage = "url(res/OpenLayers/theme/default/img/freehand_off.png)";
            document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Freehand OFF') ?>';
            lineControl.handler.freehand = false;
            polygonControl.handler.freehand = false;
        } else{
            document.getElementById('gis_map_icon_freehand').style.backgroundImage = "url(res/OpenLayers/theme/default/img/freehand_on.png)";
            document.getElementById('gis_map_icon_descripion').innerHTML = '<?php echo  _t('Mode: Freehand ON') ?>';
            lineControl.handler.freehand = true;
            polygonControl.handler.freehand = true;
        }
    }
    // Deactivate all other controls
    function shn_gis_map_control_deactivate_all(){
        // Turn off navigate
        var nav = document.getElementById('gis_map_icon_select')
        if(nav != null){
            nav.style.backgroundImage = "url(res/OpenLayers/theme/default/img/move_feature_off.png)";
        }
        // Turn off select
        if(selectControl != null){
            selectControl.unselectAll();
            selectControl.deactivate();
            document.getElementById('gis_map_icon_select').style.backgroundImage = "url(res/OpenLayers/theme/default/img/move_feature_off.png)";
        }
        // Turn off drag
        if(dragControl != null){
            dragControl.deactivate();
            document.getElementById('gis_map_icon_drag').style.backgroundImage = "url(res/OpenLayers/theme/default/img/pan_off.png)";
        }
        // Turn off modify
        //if(modifyControl != null){
        //modifyControl.deactivate();
        //}
        // Drop features/popups in progress from a create feature.
        if(currentFeature != null && ((pointControl != null && pointControl.active) || (lineControl != null && lineControl.active) || (polygonControl != null && polygonControl.active))){
            if(currentFeature.popup != null){
                currentFeature.popup.hide();
                currentFeature.popup.destroy(currentFeature.popup);
            }
            featuresLayer.removeFeatures([currentFeature]);
            currentFeature.destroy();
            currentFeature = null;
        }
        // Hide any popup showing and deactivate current feature.
        if(currentFeature != null){
            if(currentFeature.popup != null){
                currentFeature.popup.hide();
            }
            currentFeature = null;
        }
        // Turn off point add
        if(pointControl != null){
            pointControl.deactivate();
            document.getElementById('gis_map_icon_addpoint').style.backgroundImage = "url(res/OpenLayers/theme/default/img/draw_point_off.png)";
        }
        // Turn off line add
        if(lineControl != null){
            lineControl.deactivate();
            document.getElementById('gis_map_icon_addline').style.backgroundImage = "url(res/OpenLayers/theme/default/img/draw_line_off.png)";
        }
        // Turn off polygon add
        if(polygonControl != null){
            polygonControl.deactivate();
            document.getElementById('gis_map_icon_addpolygon').style.backgroundImage = "url(res/OpenLayers/theme/default/img/draw_polygon_off.png)";
        }
    }
    function shn_gis_map_expand()
    {
        var omap = document.getElementById("outer_map");
        var amap = document.getElementById("map");
        var tmap = document.getElementById("gis_map_toolbar");
        var fmap = document.getElementById("gis_map_toolbar_fieldset");
        var expd = document.getElementById("gis_map_icon_expand");
        // If currently small, make big
        if(omap.style.position != 'fixed'){
            expd.style.backgroundImage = "url(res/OpenLayers/theme/default/img/map_resize_in_c.png)";
            amap.style.width = '100%';
            amap.style.height = '100%';
            omap.style.position = 'fixed';
            omap.style.top = '0px';
            omap.style.left = '0px';
            omap.style.width = '100%';
            omap.style.height = '100%';
            omap.style.marginLeft = '0px';
            fmap.style.border = '0px none';
            tmap.style.margin = '0px';
        }
        // If currently big, make small
        else {
            expd.style.backgroundImage = "url(res/OpenLayers/theme/default/img/map_resize_out_c.png)";
            amap.style.width = '<?php echo  $conf['gis_width'] ?>px';
            amap.style.height = '<?php echo  $conf['gis_height'] ?>px';
            omap.style.position = 'relative';
            omap.style.top = 'auto';
            omap.style.left = 'auto';
            omap.style.width = 'auto';
            omap.style.height = 'auto';
            omap.style.marginLeft = '10px';
            fmap.style.border = '1px solid';
            tmap.style.margin = '10px 10px 10px 0px';
        }
    }
<?php
}

/**
 * Add Button to save current Viewport settings
 * called by show_map_select function in openlayers plugin handler
 * @access public
 */
function ol_viewport_save_button()
{
?>
    <form>
    <input type="button" value="Update Viewport Settings" OnClick="UpdateViewportFormFields();">
    </form>
<?php
}

/**
 * Add Function to save current Viewport settings
 * called by show_map_select function in openlayers plugin handler
 * @access public
 */
function ol_viewport_save($lat_field,$lon_field,$zoom_field)
{
?>
    function UpdateViewportFormFields() {
        // Read current settings from map
        var lonlat = map.getCenter();
        var zoom = map.getZoom();
        // Convert back to LonLat for form fields
        var proj4326 = new OpenLayers.Projection("EPSG:4326");
        var proj_current = map.getProjectionObject();
        lonlat.transform(proj_current, proj4326);
        // Update form fields
        document.getElementById('<?php echo $lon_field?>').value = lonlat.lon;
        document.getElementById('<?php echo $lat_field?>').value = lonlat.lat;
        document.getElementById('<?php echo $zoom_field?>').value = zoom;
    }
<?php
}
    
// Provides enhanced strstr function for versions of PHP <5.3.0
// Used by KML layer
function strstrbi($haystack, $needle, $before_needle=FALSE, $include_needle=TRUE, $case_sensitive=FALSE)
{
    //Find the position of $needle
    if($case_sensitive) {
        $pos=strpos($haystack,$needle);
    } else {
        $pos=strpos(strtolower($haystack),strtolower($needle));
    }
    //If $needle not found, abort
    if(FALSE==$pos) return FALSE;
    //Adjust $pos to include/exclude the needle
    if($before_needle==$include_needle) $pos+=strlen($needle);
    //get everything from 0 to $pos?
    if($before_needle) return substr($haystack,0,$pos);
    //otherwise, go from $pos to end
    return substr($haystack,$pos);
}

