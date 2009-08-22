<?php
/**
* Functions Page of the GIS API and Library
* Controller functions that dynamically uses selected plugin
* This file contains the GIS API which provides an abstract view 
* to GIS functions implemented as plugins
* 
* PHP version 5
* 
* @package		Sahana - http://sahana.sourceforge.net 		
* @author   	Mifan Careem <mifan@opensource.lk>
* @author       Fran Boon <flavour@partyvibe.com>
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
* @version		$Id: gis_fns.inc,v 1.14 2009-08-22 17:17:25 ravithb Exp $
* @library		GIS
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* 
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

/**
 * Error Message for disabled GIS
 * @access public
 * @return void
 */
function shn_gis_print_msg()
{
	add_warning(_t('GIS Functionality has been disabled. Please contact your administrator to enable it'));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAP VIEW FUNCS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Show basic GIS map without further functionalities
 * @access public
 * @return void
 */
function shn_gis_map($opt_array=null)
{
	global $global;
	global $conf;
	$db = $global['db'];
	if($conf['gis'])
	{
		$plugin_name = $conf['gis_dflt'];
		include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map($opt_array);
	}
	else
		shn_gis_print_msg();
}

/**
 * Show basic GIS map with the ability to save current viewport settings
 * for GIS Defaults
 * @access public
 * @return void
 */
function shn_gis_map_select($lat,$lon,$zoom)
{
	global $global;
	global $conf;
	$db = $global['db'];
	if($conf['gis'])
	{
		// ToDo: Implement in GoogleMaps plugin
        if("openlayers"==$conf['gis_dflt']) {
            echo '<p>'._t("You can set the viewport to your desired settings & then click 'Update Viewport Settings' to update fields ready for saving").'.</p>';
            $plugin_name = $conf['gis_dflt'];
            include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
            show_map_select($lat,$lon,$zoom);
        } else {
            return;
        }
	}
	else
		shn_gis_print_msg();
}
/**
 * Show basic GIS map with all features taken from database.
 * Input an array of feature uuids.
 * 
 * @param <type> $uuids_
 */
function shn_gis_map_uuid($uuids_)
{
    global $global;
    global $conf;
    $db = $global['db'];
    if($conf['gis']) {
        $plugin_name = $conf['gis_dflt'];
        include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
        // "lon", "lat", "name", "desc", "date", "author", "image", "url", "edit"
        show_map_with_wiki_marker($array);
    } else {
        shn_gis_print_msg();
    }
}

/**
 * Show GIS map for marker addition
 * Centers at default center
 * Allows addition of a single marker to plot location
 * Without form element or gps boxes
 * @access public
 * @param mixed  $name_of_map Custom Map Name
 * @param $nameOfPoint Assign name to point
 */
function shn_gis_add_marker_map($name_of_map="Area Map",$name=null)
{
    global $global;
    global $conf;
    if($conf['gis']) {
        $plugin_name = $conf['gis_dflt'];
        include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
        show_add_marker_map($name);
    } else{
        shn_gis_print_msg();
    }
}

/**
 * Add marker map with form elements
 * Outputs Map within form elements which listen for click events
 * include_onces additional GPS boxes
 * @param string $name_of_map	Value over map
 * @param string $nameOfPoint	Name of point to be stored
 * @access public
 * @return void
 */
function shn_gis_add_marker_map_form($name_of_map="Area Map",$nameOfPoint="",$button_submit_opts=null,$extra_opts=null)
{
    global $global;    
    require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";
    shn_gis_form_map_single_geometry();
}

/**
 * Add map with simple markers from database
 *
 * Array values:
 * "lon", "lat", "name", "url"
 *
 * @param mixed $array 2d array of marker info to be shown
 * @access public
 * @return void
 */
function shn_gis_map_with_markers($array)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['gis_dflt'];
		include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map_with_markers($array);
	}	
	else{
		shn_gis_print_msg();
	}
}

/**
 * Add map with markers with wiki like info
 * DEPRECATED
 * @param mixed $array 2d array of info to be added
 * @access public
 * @return void
 */
function shn_gis_map_with_wiki_markers($array)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['gis_dflt'];
		include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map_with_wiki_marker($array);
	}
	else{
		shn_gis_print_msg();
	}	
}

/**
 * Add map with markers with wiki like info
 * + allows  selection of a Marker to fill-in a pair of Lat/Lon fields
 * @param mixed $array 2d array of marker info to be shown
 * @param strings of field labels to be updated 
 * @access public
 * @return void
 */
function shn_gis_map_with_wiki_markers_select($array,$lat,$lon)
{
	global $global;
	global $conf;
	if($conf['gis'])
    {
        // ToDo: Implement in GoogleMaps plugin
        if("openlayers"==$conf['gis_dflt']) {
            echo '<p>'._t("Click on a Marker to make that the selection").'</p>';
            $plugin_name = $conf['gis_dflt'];
            include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
            show_map_with_wiki_markers_select($array,$lat,$lon);
        } else {
            return;
        }
	}	
	else{
		shn_gis_print_msg();
	}
}

/**
 * GIS reporting function
 * shows density based markers in different colors
 * statistical info and markers are specified in array
 * @param mixed $array 2d associative array of information
 * @access public
 * @return void
 */
function shn_gis_density_map($array)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['gis_dflt'];
		include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map_with_custom_markers($array);
	}
	else{
		shn_gis_print_msg();
	}	
}

/**
 * Retrieve GPS coords from REST url
 * store in db with entity id
 * Can be used to modify coordinates of existing entities
 * @param string $uuid uuid of entity to store
 * @param numeric $lat latitude
 * @param numeric $lon longitude
 * @access public
 * @return void
 * @todo enhance capabilities. Do edit of existing entities.Add speed and direction info
 */
function shn_gis_gps_from_rest($uuid,$lat,$lon)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	include_once $global['approot']."/inc/lib_uuid.inc";
	$gis_id=shn_create_uuid('gis');
	$query="INSERT INTO gis_location (poc_uuid,map_northing,map_easting,gis_uid) " .
			" VALUES ('{$uuid}','{$lat}','{$lon}','{$gis_id}') ";
	$db->Execute($query);
	echo _t("Coordinates Added");
}

/**
 * GeoRSS Feed Display
 * @access private
 * @return void
 * @todo get rss feed from aggregator or registered source
 *       currently gets it from conf value
 */
function shn_gis_show_georss()
{
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_gis/lib_georss.inc');
	
	// Create lastRSS object
	$rss = new lastRSS;
	// Set cache dir and cache time limit (1200 seconds)
	// (don't forget to chmod cache dir to 777 to allow writing)
	$rss->cache_dir = '';
	$rss->cache_time = 0;
	$rss->cp = 'US-ASCII';
	$rss->date_format = 'l';
	
	// Try to load and parse RSS file as stated in conf
	$rssurl = $conf['gis_georss_feed'];
	
	if ($rs = $rss->get($rssurl)) {
	    echo '<pre>';
	    print_r($rs);
	    echo '</pre>';
	    }
	else {
	    echo "Error: It's not possible to get $rssurl...";
	} 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ANALYSIS FUNCS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Returns Features within a Radius of a Position
 * Calling function has the job of filtering features by the type they are interested in
 * Formula from: http://blog.peoplesdns.com/archives/24
 * Spherical Law of Cosines (accurate down to around 1m & computationally quick): http://www.movable-type.co.uk/scripts/latlong.html
 * @ToDo: Do a Square query 1st & then run this query over subset (to improve performance)
 *
 * IF PROJECTION CHANGES THIS WILL NOT WORK
 * 
 * @global <type> $global
 * @param <type> $keys_
 * @param <type> $lat_
 * @param <type> $lon_
 * @param <type> $radius_
 * @return <type>
 */
function shn_gis_get_features_in_radius($keys_, $lat_, $lon_, $radius_)
{
    global $global;
    $db = $global['db'];

    // get all values to search for
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $fld = array_merge($fld_val_key_feature[0], $fld_val_key_metadata[0]);
    $val = array_merge($fld_val_key_feature[1], $fld_val_key_metadata[1]);
    $key = array_merge($fld_val_key_feature[2], $fld_val_key_metadata[2]);
    $avk_all = array($fld, $val, $key);
    // in case someone has added a new value and not added an appropriate fld, val, key for each
    if(!(count($fld) == count($val) &&  count($val) == count($key))){
        return false;
    }

    // km
    $radius_earth = 6378.137;
    //MySQL's PI() isn't accurate enough - rounds to: 3.141593
    $PI = 3.141592653589793;

    $calc = "$radius_earth * ACOS((SIN($PI * $lat_ /180) * SIN($PI * gis_features.coord_y /180)) + (COS($PI * $lat_ /180) * cos($PI*gis_features.coord_y/180) * COS($PI * gis_features.coord_x/180-$PI* $lon_ /180)))";

    // create query string
    $s_fields = implode(', '  , $avk_all[0]);
    $query1 = "SELECT DISTINCT gis_features.coord_x, gis_features.coord_y, {$s_fields}, $calc AS distance FROM gis_features, gis_feature_metadata WHERE 1 = 1 AND gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid AND $calc <= $radius_ ORDER BY $calc";
    $result1 = $db->Execute($query1);
    if(!$result1){
        return false;
    }
    
    //create arrays
    $output = array();
    while(!$result1->EOF){
        $items = array();
        for($i = 0; $i < count($avk_all[0]); $i++){
            // get rid of table ref before '.'
            $field = substr ($avk_all[0][$i], (strpos($avk_all[0][$i], '.') + 1), strlen($avk_all[0][$i]));
            $items[$avk_all[2][$i]] = $result1->fields[$field];
        }
        array_push($output, $items);
        $result1->MoveNext();
    }
    return $output;
}

/**
 * Given a Start (1) & End (2) set of Coordinates, return a Bearing
 * Formula from: http://www.movable-type.co.uk/scripts/latlong.html
 * 
 * @param <type> $lat1
 * @param <type> $lon1
 * @param <type> $lat2
 * @param <type> $lon2
 * @return <type>
 */
function shn_gis_bearing($lat1, $lon1, $lat2, $lon2)
{
    $delta_lon = $lon1 - $lon2;
    $bearing = ATAN2( SIN($delta_lon)*COS($lat2) , (COS($lat1)*SIN($lat2)) - (SIN($lat1)*COS($lat2)*COS($delta_lon)) );
    // Convert to a compass bearing
    $bearing = ($bearing + 360) % 360;
    return $bearing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Takes the coord string stored in the db and decodes it into an array of:
 *
 * [0 => center of obj][0 => x, 1 => y, 2 => z]
 * [1 => plot 1][0 => x, 1 => y, 2 => z]
 * [2 => plot 2][0 => x, 1 => y, 2 => z]
 * [3 => plot 3][0 => x, 1 => y, 2 => z]
 *
 * In the case of a single point (eg 33.54,64.32,0,wkt{POINT Z (33.54 64.32 0)} ) the call would result in
 * [0][0 => 33.54, 1 => 64.32, 2 => 0]
 * [1][0 => 33.54, 1 => 64.32, 2 => 0]
 *
 * In a line or poly type (eg 2,3,0,wkt{POLYGON Z ((1 4 0,5 1 0,5 5 1))} )
 * [0][0 => 2, 1 => 3, 2 => 0]
 * [1][0 => 1, 1 => 4, 2 => 0]
 * [2][0 => 5, 1 => 1, 2 => 0]
 * [3][0 => 5, 1 => 5, 2 => 1]
 *
 *
 * @param <type> $coords
 * @return <type>
 */
function shn_gis_coord_decode($coords)
{
    $output = array();
    $subcoords = explode(",", $coords, 4);
    //2,3,0,wkt{POLYGON Z ((1 4 0,5 1 0,5 5 1))}
    array_push($output, array($subcoords[0], $subcoords[1], $subcoords[2]));
    // [0][0 => 2, 1 => 3, 2 => 0]
    $wkt = $subcoords[3];
    // wkt{POLYGON Z ((1 4 0,5 1 0,5 5 1))}
    $wkt = ereg_replace("(wkt{|})", "", $wkt);
    // POLYGON Z ((1 4 0,5 1 0,5 5 1))
    $wkt = explode('(' , $wkt, 2);
    // 0 => POLYGON Z   1 => ((1 4 0,5 1 0,5 5 1))
    // if polygons start haveing inner circles this will need to change
    $wkt = ereg_replace("(\(|\))", "", $wkt[1]);
    // 1 4 0,5 1 0,5 5 1
    $wkt = explode(',' , $wkt);
    // 0 => 1 4 0   1 => 5 1 0   2 => 5 5 1
    foreach($wkt as $point){
        array_push($output, explode(' ' , $point, 3) );
    }
    return $output;
}

/**
 * Takes a coord array and encodes it into an array of:
 *
 * [0 => center of obj][0 => x, 1 => y, 2 => z]
 * [1 => plot 1][0 => x, 1 => y, 2 => z]
 * [2 => plot 2][0 => x, 1 => y, 2 => z]
 * [3 => plot 3][0 => x, 1 => y, 2 => z]
 *
 * @param <type> $coords
 * @param <type> $type
 * @return <type>
 */
function shn_gis_coord_encode($coords, $type)
{
    if(count($coords[0]) == 2){
        $coords[0][2] = '0';
    }
    $output = "{$coords[0][0]},{$coords[0][1]},{$coords[0][2]},wkt{";
    switch ($type){
        case 'point':
        $wkt = 'POINT Z (';
        break;
        case 'line':
        $wkt = 'LINESTRING Z (';
        break;
        case 'poly';
        $wkt = 'POLYGON Z ((';
        break;
        case 'polygon';
        $wkt = 'POLYGON Z ((';
        break;
        default:
        return false;
        break;
    }
    if(!($coords == 1 && $type == 'point')){
        for($i = 1; $i < (count($coords) - 1); $i++){
            $wkt = $wkt . implode(' ', $coords[$i]) . ',';
        }
        if(count($coords) > 0){
            $wkt = $wkt . implode(' ', $coords[count($coords) - 1]);
        }
    } else{ // If using a point and haven't bothered to put in 2nd line
        $wkt = "{$coords[0][0]} {$coords[0][1]} {$coords[0][2]}";
    }
    if($type != 'poly'){
        return $output . $wkt . ')}';
    } else {
        return $output . $wkt . '))}';
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FEATURE GETS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Returns selected fields of all features.
 * Required field(strings) are passed in an associative array $keys_ and
 * returned in a multidimensional array:
 *
 * An example of $keys_ might be
 * �array = array('f_type' = 1, 'f_coords' = '!!!doesnt matter what this value is!!!')
 * This will return all entry fields 'f_type' 'f_coords' in form as seen below
 *
 * [0]['f_type' => 'point', 'f_coords' => 'x,y,z,wkt{POINT(x y z)}']
 * [1]['f_type' => 'line',  'f_coords' => 'x,y,z,wkt{LINESTRING(x y z,x y z)}']
 * [2]['f_type' => 'poly',  'f_coords' => 'x,y,z,wkt{POLYGON(x y z,x y z,x y z)}']
 *
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_get_features_all($keys_)
{
    global $global;
    $db = $global['db'];

    // get all value to search for
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $fld = array_merge($fld_val_key_feature[0], $fld_val_key_metadata[0]);
    $val = array_merge($fld_val_key_feature[1], $fld_val_key_metadata[1]);
    $key = array_merge($fld_val_key_feature[2], $fld_val_key_metadata[2]);
    $avk_all = array($fld, $val, $key);
    // incase someone has added a new value and not added an aproprate fld, val, key for each
    if(!(count($fld) == count($val) &&  count($val) == count($key))){
        return false;
    }

    // create query string
    $s_fields = implode(', '  , $avk_all[0]);
    $query1 = "SELECT DISTINCT {$s_fields} FROM gis_features, gis_feature_metadata WHERE gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid";
    $result1 = $db->Execute($query1);
    if(!$result1){
        return false;
    }

    //create arrays
    $output = array();
    while(!$result1->EOF){
        $items = array();
        for($i = 0; $i < count($avk_all[0]); $i++){
            // get rid of table ref before '.'
            $field = substr ($avk_all[0][$i], (strpos($avk_all[0][$i], '.') + 1), strlen($avk_all[0][$i]));
            $items[$avk_all[2][$i]] = $result1->fields[$field];
        }
        array_push($output, $items);
        $result1->MoveNext();
    }
    return $output;
}

/**
 * Returns selected fields of all features belonging to a feature class
 * required fields are passed in an associative array $keys_ and
 * returned in a multidimensional array:
 * [item_1][key1, key2... ]
 * [item_2][key1, key2... ]
 *
 * @global <type> $global
 * @param <type> $class_uuid_
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_get_features_feature_class($class_uuid_, $keys_)
{
    global $global;
    $db = $global['db'];

    // get all value to search for
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $fld = array_merge($fld_val_key_feature[0], $fld_val_key_metadata[0]);
    $val = array_merge($fld_val_key_feature[1], $fld_val_key_metadata[1]);
    $key = array_merge($fld_val_key_feature[2], $fld_val_key_metadata[2]);
    $avk_all = array($fld, $val, $key);
    // incase someone has added a new value and not added an aproprate fld, val, key for each
    if(!(count($fld) == count($val) &&  count($val) == count($key))){
        return false;
    }

    // create query string
    $s_fields = implode(', '  , $avk_all[0]);
    $where = "gis_features.feature_class_uuid_ref = '{$class_uuid_}'";
    $query1 = "SELECT DISTINCT {$s_fields} FROM gis_features, gis_feature_metadata WHERE gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid AND {$where}";
    $result1 = $db->Execute($query1);
    if(!$result1){
        return false;
    }

    //create arrays
    $output = array();
    while(!$result1->EOF){
        $items = array();
        for($i = 0; $i < count($avk_all[0]); $i++){
            // get rid of table ref before '.'
            $field = substr ($avk_all[0][$i], (strpos($avk_all[0][$i], '.') + 1), strlen($avk_all[0][$i]));
            $items[$avk_all[2][$i]] = $result1->fields[$field];
        }
        array_push($output, $items);
        $result1->MoveNext();
    }
    return $output;
}

/**
 * Returns selected fields of all features belonging to a layer
 * required fields are passed in an associative array $keys_ and
 * returned in a multidimensional array:
 * [item_1][key1, key2... ]
 * [item_2][key1, key2... ]
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_get_features_layer($layer_uuid_, $keys_)
{
    global $global;
    $db = $global['db'];

    // get all value to search for
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $fld = array_merge($fld_val_key_feature[0], $fld_val_key_metadata[0]);
    $val = array_merge($fld_val_key_feature[1], $fld_val_key_metadata[1]);
    $key = array_merge($fld_val_key_feature[2], $fld_val_key_metadata[2]);
    $avk_all = array($fld, $val, $key);
    // incase someone has added a new value and not added an aproprate fld, val, key for each
    if(!(count($fld) == count($val) &&  count($val) == count($key))){
        return false;
    }

    // create query string
    $s_fields = implode(', '  , $avk_all[0]);
    $from = "gis_features " .
              "INNER JOIN gis_feature_metadata ON gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid " .
              "INNER JOIN gis_feature_class ON gis_features.feature_class_uuid_ref = gis_feature_class.feature_class_uuid " .
              "LEFT OUTER JOIN gis_feature_class_to_layer ON gis_feature_class.feature_class_uuid = gis_feature_class_to_layer.feature_class_uuid_ref " .
              "LEFT OUTER JOIN gis_feature_to_layer ON gis_features.feature_uuid = gis_feature_to_layer.feature_uuid_ref " .
              "INNER JOIN gis_layers ON (gis_layers.layer_uuid = gis_feature_class_to_layer.layer_uuid_ref OR gis_layers.layer_uuid = gis_feature_to_layer.layer_uuid_ref)";
    $where = "gis_layers.layer_uuid = '{$layer_uuid_}'";
    $query1 = "SELECT DISTINCT {$s_fields} FROM {$from} WHERE {$where}";
    $result1 = $db->Execute($query1);
    if(!$result1){
        return false;
    }
    
    //create arrays
    $output = array();
    
    // Add all features from feature classes within layer
    $feature_classes = shn_gis_get_feature_class_layer($layer_uuid_);
    foreach($feature_classes as $feature_class){
        array_merge($output, shn_gis_get_features_feature_class($feature_class->fields['c_uuid'], $keys_));
    }
     
    // Add all features within layer(not in a feature class)
    while(!$result1->EOF){
        $items = array();
        for($i = 0; $i < count($avk_all[0]); $i++){
            // get rid of table ref before '.'
            $field = substr ($avk_all[0][$i], (strpos($avk_all[0][$i], '.') + 1), strlen($avk_all[0][$i]));
            $items[$avk_all[2][$i]] = $result1->fields[$field];
        }
        array_push($output, $items);
        $result1->MoveNext();
    }
    return $output;
}

/**
 * Returns selected fields of all features belonging to uid ref
 * required fields are passed in an associative array $keys_ and
 * returned in a multidimensional array:
 * [item_1][key1, key2... ]
 * [item_2][key1, key2... ]
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_get_features_uuid($uuid_, $keys_)
{
    global $global;
    $db = $global['db'];

    // get all value to search for
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $fld = array_merge($fld_val_key_feature[0], $fld_val_key_metadata[0]);
    $val = array_merge($fld_val_key_feature[1], $fld_val_key_metadata[1]);
    $key = array_merge($fld_val_key_feature[2], $fld_val_key_metadata[2]);
    $avk_all = array($fld, $val, $key);
    // incase someone has added a new value and not added an aproprate fld, val, key for each
    if(!(count($fld) == count($val) &&  count($val) == count($key))){
        return false;
    }

    // create query string
    $s_fields = implode(', '  , $avk_all[0]);
    $where = "gis_features.feature_uuid = '{$uuid_}' ";
    $query1 = "SELECT DISTINCT {$s_fields} FROM gis_features, gis_feature_metadata WHERE gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid AND {$where}";
    $result1 = $db->Execute($query1);
    if(!$result1){
        return false;
    }

    //create arrays
    $output = array();
    while(!$result1->EOF){
        $items = array();
        for($i = 0; $i < count($avk_all[0]); $i++){
            // get rid of table ref before '.'
            $field = substr ($avk_all[0][$i], (strpos($avk_all[0][$i], '.') + 1), strlen($avk_all[0][$i]));
            $items[$avk_all[2][$i]] = $result1->fields[$field];
        }
        array_push($output, $items);
        $result1->MoveNext();
    }
    return $output;
}

/**
 * Returns selected fields of all features belonging to an external tables uid ref
 * required fields are passed in an associative array $keys_ and
 * returned in a multidimensional array:
 * [item_1][key1, key2... ]
 * [item_2][key1, key2... ]
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_get_features_item_ref($item_uuid_, $keys_)
{
    global $global;
    $db = $global['db'];

    // get all value to search for
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $fld = array_merge($fld_val_key_feature[0], $fld_val_key_metadata[0]);
    $val = array_merge($fld_val_key_feature[1], $fld_val_key_metadata[1]);
    $key = array_merge($fld_val_key_feature[2], $fld_val_key_metadata[2]);
    $avk_all = array($fld, $val, $key);
    // incase someone has added a new value and not added an aproprate fld, val, key for each
    if(!(count($fld) == count($val) &&  count($val) == count($key))){
        return false;
    }

    // create query string
    $s_fields = implode(', '  , $avk_all[0]);
    $where = "gis_feature_metadata.module_item_ref = '{$item_uuid_}' ";
    $query1 = "SELECT DISTINCT {$s_fields} FROM gis_features, gis_feature_metadata WHERE gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid AND {$where}";
    $result1 = $db->Execute($query1);
    if(!$result1){
        return false;
    }

    //create arrays
    $output = array();
    while(!$result1->EOF){
        $items = array();
        for($i = 0; $i < count($avk_all[0]); $i++){
            // get rid of table ref before '.'
            $field = substr ($avk_all[0][$i], (strpos($avk_all[0][$i], '.') + 1), strlen($avk_all[0][$i]));
            $items[$avk_all[2][$i]] = $result1->fields[$field];
        }
        array_push($output, $items);
        $result1->MoveNext();
    }
    return $output;
}

/**
 * Returns features corresponding to search values.
 * To ignore any of the values, set input at $att = ''
 * 
 * @global <type> $global
 * @param <type> $keys_
 * @param <type> $layer_
 * @param <type> $class_
 * @param <type> $author_name_
 * @param <type> $date_from_
 * @param <type> $date_to_
 * @param <type> $feature_name_
 * @return <type>
 */
function shn_gis_get_features_other($keys_, $layer_, $class_, $author_name_, $date_from_, $date_to_, $feature_name_)
{
    global $global;
    $db = $global['db'];
    
    $from = "gis_features " .
              "LEFT OUTER JOIN gis_feature_metadata ON gis_features.metadata_uuid_ref = gis_feature_metadata.metadata_uuid " .
              "LEFT OUTER JOIN gis_feature_class ON gis_features.feature_class_uuid_ref = gis_feature_class.feature_class_uuid " .
              "LEFT OUTER JOIN gis_feature_class_to_layer ON gis_feature_class.feature_class_uuid = gis_feature_class_to_layer.feature_class_uuid_ref " .
              "LEFT OUTER JOIN gis_feature_to_layer ON gis_features.feature_uuid = gis_feature_to_layer.feature_uuid_ref " .
              "LEFT OUTER JOIN gis_layers ON (gis_layers.layer_uuid = gis_feature_class_to_layer.layer_uuid_ref OR gis_layers.layer_uuid = gis_feature_to_layer.layer_uuid_ref)";

    $where = '';
    if($layer_ != "" && $layer_ != "all"){
        $where = $where . "gis_layers.layer_uuid = '{$layer_}' AND "; 
    }
    if($class_ != "" && $class_ != "all"){
        $where = $where . "gis_feature_class.feature_class_uuid = '{$class_}' AND ";
    }
    if($author_name_ != ""){
        $where = $where . "gis_feature_metadata.author = '{$author_name_}' AND ";
    }
    if($date_from_ != ""){
        $where = $where . "gis_feature_metadata.event_date >= '{$date_from_}' AND ";
    } 
    if($date_to_ != ""){  
        $where = $where . "gis_feature_metadata.event_date <= '{$date_to_}' AND ";;
    }            
    if($feature_name_ != ""){
        $where = $where . "gis_feature_metadata.name = '{$feature_name_ }' AND ";
    }
    $where = $where . '1 = 1';
    $query = "SELECT DISTINCT gis_features.feature_uuid FROM {$from} WHERE {$where}";
    $result = $db->Execute($query);
    
    $output = array();
    while(!$result->EOF){
        $items = shn_gis_get_features_uuid($result->fields['feature_uuid'], $keys_);
        $output = array_merge($items, $output);
        $result->MoveNext(); 
    }
    return $output;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FEATURE & FEATURE METADATA TABLE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Function takes an assosative array containing keys below. It then
 * inserts the values into the aproprate areas of the database.
 * This add a layer of abstraction to the GIS db allowing future changes
 * to structure and additional fields to be added.
 *
 * Returns id of created feature or false if creation fails.
 *
 * If a new feild is added define the key value below and add to this function
 * below. see http://www.sahana.lk/wiki/doku.php?id=dev:gisapi for more details [!!! UPDATE !!!]
 *
 * GIS key values
 *
 *   KEY                 TYPE   EXAMPLE VALUE               DESCRIPTION
 * == Required
 * 'f_type'           => [str] ['point']                    [Feature type use one of ('point', 'line' 'poly')]
 * 'f_coords'         => [str] ['x,y,z,wkt(POINT(x y z))']  [Coordinates center point then coords in wkt(x y z) format ]
 *
 * == Optional
 * 'f_uuid'           => [str] ['ql5yg-1']                  [Feature unique ID !!! IT IS RECOMENDED THAT YOU LET THIS FUNCTION GEN A UUID FOR YOU]
 * 'f_class'          => [str] ['ql5yg-2']                  [uuid of feature class]
 * 'f_projection'     => [str] ['EPSG:900913']              [Mapping projection default EPSG:900913 ]
 *
 * 'f_module_item'    => [str] ['ql5yg-2']                  [Module item refrance uuid NOTE: This should be the UID of the item the feature is representing in the modules table]
 * 'f_name'           => [str] ['Toms house']               [Name of feature]
 * 'f_description'    => [str] ['Big blue house, blk door'] [Description of feature(can be html)]
 * 'f_author'         => [str] ['Tom']                      [Name of author]
 * 'f_url'            => [str] ['http://www.thouse.com']    [url realated to node]
 * 'f_address'        => [str] ['10 big hill']              [Address at which node resides]
 * 'f_event_date'     => [date]['2008-06-15 15:05:20']      [Date of event which marker represents]
 * 'f_extended_data'  => [str] ['blaa blaa']                [Any extended data assosated with point (sahana specifc)]
 *
 * Add new keys as database expands
 *
 * @global <type> $global
 * @global <type> $conf
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_create_feature($keys_)
{
    global $global;
    global $conf;
    include_once $global['approot']."/inc/lib_uuid.inc";
    $db = $global['db'];

    $feature_uuid   = shn_create_uuid('g');
    $metadata_uuid  = shn_create_uuid('g');
    $fail = false;

    /* feature checks
     *
     * All fields must be filled in.
     * Feature table as such will use default if possible
     * if not flag fail.
     */

    // uuid
    if(array_key_exists('f_uuid', $keys_)){
        // May want to check the new uuid they are useing doesnt allready exist!!!
        // This is very dangous may remove ability to set uuid in future
        $feature_uuid = $keys_['f_class'];
    }
    // feature class
    if(!array_key_exists('f_class', $keys_) || '' == $keys_['f_class']){
        $keys_['f_class'] = $conf['gis_feature_type_default'];
    }
    // feature type
    if(array_key_exists('f_type', $keys_)){
        $type = 'unknown';
        switch ($keys_['f_type']){
            case 'point':
            $type = 'point';
            break;
            case 'line':
            $type = 'line';
            break;
            case 'track':
            $type = 'line';
            break;
            case 'poly';
            $type = 'poly';
            break;
            case 'polygon':
            $type = 'poly';
            break;
            default:
            $fail = true; // fail
            break;
        }
        $keys_['f_type'] = $type;
    } else { // flag fail
        $fail = true;
    }
    // feature projection
    if(!array_key_exists('f_projection', $keys_) || '' == $keys_['f_projection']){
        $keys_['f_projection'] = $conf['gis_feature_projection_default'];
    }
    // feature coordinates
    if(!array_key_exists('f_coords', $keys_) || '' == $keys_['f_coords']){
        $fail = true;
    }
    
    $xyz = explode(',', $keys_['f_coords'], 3);
    $coord_x = $xyz[0];
    $coord_y = $xyz[1];
    $coord_z = $xyz[2];

    if( '' == $coord_x){
        $fail = true;
    }
    if( '' == $coord_y){
        $fail = true;
    }
    if( '' == $coord_z){
        $coord_z = 0;
    }

    /*
     * metadata checks
     *
     * Not all fields need filling - at the authors discretion.
     */

    // use feature type insted !!!
    if(!array_key_exists('f_name', $keys_)){
        $keys_['f_name'] = $keys_['f_type'];
    }
    
    // fail check
    if(!$fail){
        // Make feature query
        $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
        // string containing key values to be queryed
        $query_feature_keys = 'INSERT INTO gis_features (feature_uuid, metadata_uuid_ref, coord_x, coord_y, coord_z, ' . implode(', '  , $fld_val_key_feature[0]) . ') ';
        // string containing values of keys to be queryed
        $query_feature_vals = "VALUES ('$feature_uuid', '$metadata_uuid', '$coord_x', '$coord_y', '$coord_z', '" . implode("', '"  , $fld_val_key_feature[1]) . "')";
        $query_feature  = $query_feature_keys . $query_feature_vals;

        // Make metadata query
        $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
        // string containing keys values to be queryed
        $query_metadata_keys = 'INSERT INTO gis_feature_metadata (metadata_uuid, ' . implode(', '  , $fld_val_key_metadata[0]) . ') ';
        // string containing values of keys to be queryed
        $query_metadata_vals = "VALUES ('{$metadata_uuid}', '" . implode("', '"  , $fld_val_key_metadata[1]) . "')";
        $query_metadata = $query_metadata_keys . $query_metadata_vals;

        // Make Query
        $db->BeginTrans();
        $ok = $db->Execute($query_feature);
        if ($ok){
            $ok = $db->Execute($query_metadata);
        }
        if ($ok){
            $db->CommitTrans();
            return $feature_uuid;
        }
        $db->RollbackTrans(); 
    }
    return false;
}

/**
 * Removes a feature, associated metadata and feature_to_layer refs.
 *
 * NOTE: If in future feature-to-metadata relationships become one-to-many
 * this function will need recoding to check if a metadata entry is used more
 * than once before it is deleted.
 *
 * @global <type> $global
 * @param <type> $feature_uuid_
 * @return <type>
 */
function shn_gis_remove_feature($feature_uuid_)
{
    global $global;
    $db = $global['db'];

    // Delete feature_to_layer refs
    $query1 = "DELETE FROM gis_feature_to_layer " .
              "WHERE feature_uuid_ref  = '{$feature_uuid_}'";
    // delete metadata
    $query2 = "DELETE FROM gis_feature_metadata " .
              "WHERE metadata_uuid = " .
    // find metadata id to delete
              "(SELECT DISTINCT metadata_uuid_ref " .
              "FROM gis_features " .
              "WHERE feature_uuid = '{$feature_uuid_}')";
    // delete feature
    $query3 = "DELETE FROM gis_features " .
               "WHERE feature_uuid = '{$feature_uuid_}'";

    // Make Query
    $db->BeginTrans();
    $ok = $db->Execute($query1);
    if ($ok){
        $ok = $db->Execute($query2);
    }
    if ($ok){
        $ok = $db->Execute($query3);
    }
    if ($ok){
        $db->CommitTrans();
        return true;
    }
    $db->RollbackTrans(); 
    return false;
}

/**
 * Removes a feature, associated metadata and feature_to_layer refs.
 * Uses external item ref to delete MOST MODULES will use this function.
 *
 * NOTE: If in future feature-to-metadata relationships become one-to-many
 * this function will need recoding to check if a metadata entry is used more
 * than once before it is deleted.
 *
 * @global <type> $global
 * @param <type> $f_module_item_
 * @return <type>
 */
function shn_gis_remove_feature_module_item($f_module_item_)
{
    global $global;
    $db = $global['db'];

    // Delete feature_to_layer refs
    $query1 = "DELETE FROM gis_feature_to_layer " .
              "WHERE feature_uuid_ref  = " .
    // find feature id to delete
              "(SELECT DISTINCT feature_uuid " .
              "FROM gis_features, gis_feature_metadata " .
              "WHERE metadata_uuid_ref = metadata_uuid AND module_item_ref = '{$f_module_item_}')";
    // delete feature
    $query2 = "DELETE FROM gis_features " .
              "WHERE feature_uuid = " .
    // find feature id to delete
              "(SELECT DISTINCT feature_uuid " .
              "FROM gis_feature_metadata " .
              "WHERE metadata_uuid_ref = metadata_uuid AND module_item_ref = '{$f_module_item_}')";
    // delete metadata
    $query3 = "DELETE FROM gis_feature_metadata " .
              "WHERE module_item_ref = '{$f_module_item_}'";

    // Make Query
    $db->BeginTrans();
    $ok = $db->Execute($query1);
    if ($ok){
        $ok = $db->Execute($query2);
    }
    if ($ok){
        $ok = $db->Execute($query3);
    }
    if ($ok){
        $db->CommitTrans();
        return true;
    }
    $db->RollbackTrans(); 
    return false;
}

/**
 * Modifies any keys value of feature with uuid
 *
 * @global <type> $global
 * @param <type> $uuid
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_modify_feature($uuid_, $keys_)
{
    global $global;
    $db = $global['db'];

    // Generate gis_features Query
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $count = count($fld_val_key_feature[1]);
    if($count > 0){
        $set = '';
        for($i = 0; $i < $count - 1; $i++){
            $set = $set . " {$fld_val_key_feature[0][$i]} = '{$fld_val_key_feature[1][$i]}',";
        }
        $set = $set . " {$fld_val_key_feature[0][$count - 1]} = '{$fld_val_key_feature[1][$count - 1]}'";
        $query1 = "UPDATE gis_features " .
                  "SET {$set} " .
                  "WHERE feature_uuid = '{$uuid_}'";
    }

    // Generate gis_feature_metadata Query
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $count2 = count($fld_val_key_metadata[1]);
    if($count2 > 0){
        $set2 = '';
        for($i = 0; $i < $count2 - 1; $i++){
            $set2 = $set2 . " {$fld_val_key_metadata[0][$i]} = '{$fld_val_key_metadata[1][$i]}',";
        }
        $set2 = $set2 . " {$fld_val_key_metadata[0][$count2 - 1]} = '{$fld_val_key_metadata[1][$count2 - 1]}'";
        $query2 = "UPDATE gis_feature_metadata " .
                  "SET {$set2} " .
                  "WHERE metadata_uuid = " .
                  "(SELECT DISTINCT metadata_uuid_ref  " .
                  "FROM gis_features " .
                  "WHERE feature_uuid = '{$uuid_}')";
    }

    //echo '<br />Q: ' . $query1 . '<br />Q2: ' . $query2;
    // Make Query
    $db->BeginTrans();
    if($count > 0 ){
        $ok = $db->Execute($query1);
    } else {
        $ok = true;
    }
    if ($ok && $count2 > 0 ){
        $ok = $db->Execute($query2);
    }
    if ($ok){
        $db->CommitTrans();
        return true;
    }
    $db->RollbackTrans(); 
    return false;
}

/**
 * Modifies any keys value of feature with f_module_item uuid
 *
 * @global <type> $global
 * @param <type> $uuid
 * @param <type> $keys_
 * @return <type>
 */
function shn_gis_modify_feature_module_item($f_module_item_, $keys_)
{
    global $global;
    $db = $global['db'];
    $query1 = '';
    $query2 = '';

    // Generate gis_features Query
    $fld_val_key_feature = _shn_gis_querygen_feature($keys_);
    $count = count($fld_val_key_feature[1]);
    if($count > 0){
        $set = '';
        for($i = 0; $i < $count - 1; $i++){
            $set = $set . " {$fld_val_key_feature[0][$i]} = '{$fld_val_key_feature[1][$i]}',";
        }
        $set = $set . " {$fld_val_key_feature[0][$count - 1]} = '{$fld_val_key_feature[1][$count - 1]}'";
        $query1 = "UPDATE gis_features " .
                  "SET {$set} " .
                  "WHERE metadata_uuid_ref = " .
                  "(SELECT DISTINCT metadata_uuid " .
                  "FROM gis_feature_metadata " .
                  "WHERE module_item_ref = '{$f_module_item_}')";
    }

    // Generate gis_feature_metadata Query
    $fld_val_key_metadata = _shn_gis_querygen_metadata($keys_);
    $count2 = count($fld_val_key_metadata[1]);
    if($count2 > 0){
        $set = '';
        for($i = 0; $i < $count2 - 1; $i++){
            $set2 = $set2 . " {$fld_val_key_metadata[0][$i]} = '{$fld_val_key_metadata[1][$i]}',";
        }
        $set2 = $set2 . " {$fld_val_key_metadata[0][$count2 - 1]} = '{$fld_val_key_metadata[1][$count2 - 1]}'";
        $query2 = "UPDATE gis_feature_metadata " .
                  "SET {$set2} " .
                  "WHERE module_item_ref = '{$f_module_item_}'";
    }

    //echo '<br />Q: ' . $query1 . '<br />Q2: ' . $query2;
    // Make Query
    $db->BeginTrans();
    if($count > 0 ){
        $ok = $db->Execute($query1);
    } else {
        $ok = true;
    }
    if ($ok && $count2 > 0 ){
        $ok = $db->Execute($query2);
    }
    if ($ok){
        $db->CommitTrans();
        return true;
    }
    $db->RollbackTrans(); 
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// FEATURE_CLASS TABLE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Creates a new feature_class
 *
 * notes: should names be unique?
 *
 * @global <type> $global
 * @param <type> $uuid_
 * @param <type> $name_
 * @param <type> $description_
 * @param <type> $icon_
 * @param <type> $color_
 */
function shn_gis_create_feature_class($module_ref_, $name_, $description_, $icon_, $color_)
{
    global $global;
    include $global['approot']."/inc/lib_uuid.inc";
    $db = $global['db'];

    $feature_class_uuid = shn_create_uuid('g');

    $query = "INSERT INTO gis_feature_class (feature_class_uuid, module_ref, name, description, icon, color) " .
             "VALUES ('{$feature_class_uuid}', '{$module_ref_}', '{$name_}', '{$description_}', '{$icon_}', '{$color_}')";
    $result = $db->Execute($query);
    if($result){
        return $feature_class_uuid;
    }
    return false;
}

/**
 * Removes feature_class from database.
 *
 * Options used to Decide what action to take with features that use this class.
 * 1 - Fail if features exist with this feature class, otherwise remove.
 * 2 - Remove feature class and set existing features with feature_class_uuid to default class.
 * 3 - Remove existing feature with this class then remove class.
 * default - fail if features exist with this feature class.
 *
 * Returns true or false depending on success of query.
 * 
 * @global <type> $global
 * @param <type> $uuid_
 * @param <type> $options_
 * @return <type>
 */
function shn_gis_remove_feature_class($feature_class_uuid_, $options_)
{
    global $global;
    global $conf;
    $db = $global['db'];

    // Should not be able to delete default class
    if($feature_class_uuid_ != $conf['gis_feature_type_default']){
        switch($options_){
            case 1: // fail if features exist with this feature type.
            // Search for existing features
            $query1 = "SELECT DISTINCT feature_uuid " .
                      "FROM gis_features " .
                      "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
            $result1 = $db->Execute($query1);
            if('' == $result1->fields['feature_uuid']){
                // Delete refrences to layers
                $query2 = "DELETE FROM gis_feature_class_to_layer " .
                          "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
                // Delete old feature_class.
                $query3 = "DELETE FROM gis_feature_class " .
                          "WHERE feature_class_uuid = '{$feature_class_uuid_}'";
                $db->BeginTrans();
                $ok = $db->Execute($query2);
                if ($ok){
                    $ok = $db->Execute($query3);
                }
                if ($ok){
                    $db->CommitTrans();
                    return true;
                }
                $db->RollbackTrans(); 
            }
            break;

            case 2: // set existing features to default type then delete.
            // Update feature types which contain feature_class.
            $query1 = "UPDATE gis_features " .
                      "SET feature_class_uuid_ref  = '{$conf['gis_feature_type_default']}' " .
                      "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
            // Delete refrences to layers
            $query2 = "DELETE FROM gis_feature_class_to_layer " .
                      "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
            // Delete old feature_class.
            $query3 = "DELETE FROM gis_feature_class " .
                      "WHERE feature_class_uuid = '{$feature_class_uuid_}'";

            // Make Query
            $db->BeginTrans();
            $ok = $db->Execute($query1);
            if ($ok){
                $ok = $db->Execute($query2);
            }
            if ($ok){
                $ok = $db->Execute($query3);
            }
            if ($ok){
                $db->CommitTrans();
                return true;
            }
            $db->RollbackTrans(); 
            break;

            case 3: // Delete existing features with this feature_class then delete.
            // Select features with useing feature_class
            $query1 = "SELECT DISTINCT feature_uuid " .
                      "FROM gis_features " .
                      "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
            $result1 = $db->Execute($query1);
            if($result1){
                // Delete refrences to layers
                $query2 = "DELETE FROM gis_feature_class_to_layer " .
                          "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
                // Delete old feature_class.
                $query3 = "DELETE FROM gis_feature_class " .
                          "WHERE feature_class_uuid = '{$feature_class_uuid_}'";
                $ok = true;
                $db->BeginTrans();
                while (!$result1->EOF && $ok) {
                    // Delete feature types which contain feature_class.
                    $uuid = $result1->fields['feature_uuid'];
                    $ok = shn_gis_remove_feature($uuid); 
                    $result1->MoveNext();
                }
                if($ok){
                    $ok = $db->Execute($query2);
                }
                if($ok){
                    $ok = $db->Execute($query3);
                }
                if($ok){
                    $db->CommitTrans();
                    return true;
                }
                $db->RollbackTrans();
            }
            break;

            default: // default fail if features exist with this feature type (seems safest).
            shn_gis_remove_feature_class($feature_class_uuid_, 1);
            break;
        }
    }
    return false;
}

function shn_gis_modify_feature_class($uuid_, $keys_)
{
    global $global;
    $db = $global['db'];
    $fc_val_key_feature = _shn_gis_querygen_feature_class($keys_);
    $count = count($fc_val_key_feature[1]);
    if($count > 0){
        $set = '';
        for($i = 0; $i < $count - 1; $i++){
            $set = $set . " {$fc_val_key_feature[0][$i]} = '{$fc_val_key_feature[1][$i]}',";
        }
        $set = $set . " {$fc_val_key_feature[0][$count - 1]} = '{$fc_val_key_feature[1][$count - 1]}'";
        $query = "UPDATE gis_feature_class " .
                 "SET {$set} " .
                 "WHERE feature_class_uuid = '{$uuid_}'";
        $db->Execute($query);
        if($db){
            return true;
        } 
    }
    return false;
}

function shn_gis_get_feature_class_all()
{
    global $global;
    $db = $global['db'];
    $query = "SELECT DISTINCT * " .
             "FROM gis_feature_class";
    $result = $db->Execute($query);
        
    // create output array
    $output = array();
    while(!$result->EOF){
        $feature_class = array(
        'c_uuid' => $result->fields['feature_class_uuid'], 
        'c_module_ref' => $result->fields['module_ref'], 
        'c_name' => $result->fields['name'], 
        'c_description' => $result->fields['description'], 
        'c_icon' => $result->fields['icon'], 
        'c_color' => $result->fields['color']
        );
        array_push($output, $feature_class);
        $result->MoveNext();
    }
    return $output;     
}

/**
 * Returns infomation about a feature class in the form of an associative array
 * values can be seen in function below.
 * 
 * @param <type> $feature_class_uuid_
 * @return <type>
 */
function shn_gis_get_feature_class_uuid($feature_class_uuid_)
{
    global $global;
    $db = $global['db']; 
    $query = "SELECT DISTINCT * " .
              "FROM gis_feature_class " .
              "WHERE feature_class_uuid = '{$feature_class_uuid_}'";
    $result = $db->Execute($query);

    //create arrays
    $output = array(
        'c_uuid' => $result->fields['feature_class_uuid'], 
        'c_module_ref' => $result->fields['module_ref'], 
        'c_name' => $result->fields['name'], 
        'c_description' => $result->fields['description'], 
        'c_icon' => $result->fields['icon'], 
        'c_color' => $result->fields['color']);
    return $output;
}

///////////////////////
// LAYER FUNCTIONS
///////////////////////

/*
 * The gis_layers and gis_feature_to_layer tables store data for creating extra layers
 * in OL. Each entry in gis_layers represents a layer that can be displayed in OL.
 * The mappings of features to layers are stored in gis_feature_layer.
 * mappings can be many-to-many for features-to-layers
 */

/**
 * Creates a new layer
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $name_
 * @param <type> $description_
 */
function shn_gis_create_layer($name_, $description_)
{
    global $global;
    include $global['approot']."/inc/lib_uuid.inc";
    $db = $global['db'];

    $layer_uuid = shn_create_uuid('g');

    //create new layer
    $query = "INSERT INTO gis_layers (layer_uuid, name, description) " .
             "VALUES ('{$layer_uuid}', '{$name_}', '{$description_}')";
    $ok = $db->Execute($query);
    if($ok){
        return $layer_uuid;
    }
    return false;
}

/**
 * Removes layer from database.
 *
 * Options used to Decide what action to take with features that use this layer.
 *
 * 1 - Fail if features exist within this layer otherwise remove.
 * 2 - Remove layer and refrances only.
 * 3 - Remove layer, layer references and all feature_classes and features that are in this layer.
 * default - Fail if features exist with this layer, otherwise remove.
 * 
 * @todo Add in feature class options.
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $options_
 */
function shn_gis_remove_layer($layer_uuid_, $options_)
{
    global $global;
    $db = $global['db'];

    switch($options_){
        case 1: // Fail if features exist with this layer otherwise delete.
        // Search for existing features
        $query1 = "SELECT DISTINCT feature_uuid_ref, feature_class_uuid_ref " .
                  "FROM gis_feature_to_layer, gis_feature_class_to_layer " .
                  "WHERE gis_feature_to_layer.layer_uuid_ref = '{$layer_uuid_}' " .
                  "OR gis_feature_class_to_layer.layer_uuid_ref = '{$layer_uuid_}'";
        $result1 = $db->Execute($query1);
        if('' == $result1->fields['feature_uuid_ref']){
            // Delete layer
            $query2 = "DELETE FROM gis_layers " .
                      "WHERE layer_uuid = '{$layer_uuid_}'";
            $result2 = $db->Execute($query2);
            if($result2){
                return true;
            }
        }
        break;

        case 2: // Delete layer and refrances only.
        // Delete feature layer refrences
        $query1 = "DELETE FROM gis_feature_to_layer " .
                  "WHERE layer_uuid_ref = '{$layer_uuid_}'";
        // Delete refrences to layers
        $query2 = "DELETE FROM gis_feature_class_to_layer " .
                  "WHERE layer_uuid_ref = '{$layer_uuid_}'";
        // Delete layer
        $query3 = "DELETE FROM gis_layers " .
                  "WHERE layer_uuid = '{$layer_uuid_}'";
        
        // Make Query
        $db->BeginTrans();
        $ok = $db->Execute($query1);
        if ($ok){
            $ok = $db->Execute($query2);
        }
        if ($ok){
            $ok = $db->Execute($query3);
        }
        if ($ok){
            $db->CommitTrans();
            return true;
        }
        $db->RollbackTrans(); 
        break;

        case 3: // Delete layer, layer refrances and all feature_classes and features that are in this layer.
        // Find all features in this layer
        $query1 = "SELECT DISTINCT feature_uuid_ref " .
                  "FROM gis_feature_to_layer " .
                  "WHERE layer_uuid_ref = '{$layer_uuid_}'";
        // Find all feature_classes in this layer
        $query2 = "SELECT DISTINCT feature_class_uuid_ref " .
                  "FROM  gis_feature_class_to_layer " .
                  "WHERE layer_uuid_ref = '{$layer_uuid_}'";
        $result1 = $db->Execute($query1);
        $result2 = $db->Execute($query2);
        if($result1 && $result2){
            // Delete refrences to layers
            $query3 = "DELETE FROM gis_feature_class_to_layer " .
                      "WHERE layer_uuid_ref = '{$layer_uuid_}'";
            // Delete feature layer refrences
            $query4 = "DELETE FROM gis_feature_to_layer " .
                      "WHERE layer_uuid_ref = '{$layer_uuid_}'";
            // Delete layer
            $query5 = "DELETE FROM gis_layers " .
                      "WHERE layer_uuid = '{$layer_uuid_}'";
            $ok = true;                
            $db->BeginTrans();
            while (!$result1->EOF && $ok) {
                // Delete all features in this layer
                $uuid = $result1->fields['feature_uuid_ref'];
                $ok = shn_gis_remove_feature($uuid);
                $result1->MoveNext();
            }
            while (!$result2->EOF && $ok) {
                // Delete all feature_classes in this class
                $uuid = $result1->fields['feature_class_uuid_ref'];
                $ok = shn_gis_remove_feature_class($uuid, 3);
                $result1->MoveNext();
            }
            // should not need to do this...
            $ok = $db->Execute($query3);
            if($ok){
                // should not need to do this...
                $ok = $db->Execute($query4);
            }
            if($ok){    
                $ok = $db->Execute($query5);
            }
            if($ok){
                $db->CommitTrans();
                return true;
            }
        }
        $db->RollbackTrans();
        break;

        default: // Fail if features exist with this layer otherwise delete.
        shn_gis_delet_layer($layer_uuid_, 1);
        break;
    }
    return false;
}

/**
 * Add tie between a number of features and a layer.
 *
 * Features passed as an array of feature uuids.
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $features_uuids_
 */
function shn_gis_insert_layer_features($layer_uuid_, $features_uuid_)
{
    global $global;
    $db = $global['db'];
    foreach($features_uuid_ as $feature_uuid){
        $query = "INSERT INTO gis_feature_to_layer (layer_uuid_ref, feature_uuid_ref) " .
                 "VALUES ('{$layer_uuid_}', '{$feature_uuid}')";
        $result = $db->Execute($query);
    }
}

/**
 * Removes tie between a number of features and a layer.
 *
 * Features passed as an array of feature uuids.
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $feature_uuid_
 */
function shn_gis_remove_layer_features($layer_uuid_, $features_uuid_)
{
    global $global;
    $db = $global['db'];
    foreach($features_uuid_ as $feature_uuid){
        $query = "DELETE FROM gis_feature_to_layer " .
                 "WHERE layer_uuid_ref = '{$layer_uuid_}' AND feature_uuid_ref = '{$feature_uuid}'";
        $result = $db->Execute($query);
    }
}

/**
 * Add tie between a number of feature_class and a layer.
 *
 * Feature classes passed as an array of feature_class uuids.
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $features_uuids_
 */
function shn_gis_insert_layer_feature_class($layer_uuid_, $feature_classes_uuid_)
{
    global $global;
    $db = $global['db'];
    foreach($feature_classes_uuid_ as $feature_class_uuid_){
        $query = "INSERT INTO gis_feature_class_to_layer (layer_uuid_ref, feature_class_uuid_ref) " .
                 "VALUES ('{$layer_uuid_}', '{$feature_class_uuid_}')";
        $result = $db->Execute($query);
    }
}

/**
 * Removes tie between a number of feature_class and a layer.
 *
 * Feature classes passed as an array of feature_class uuids.
 *
 * @global <type> $global
 * @param <type> $layer_uuid_
 * @param <type> $feature_uuid_
 */
function shn_gis_remove_layer_feature_class($layer_uuid_, $feature_classes_uuid_)
{
    global $global;
    $db = $global['db'];
    foreach($feature_classes_uuid_ as $feature_class_uuid_){
        $query = "DELETE FROM gis_feature_class_to_layer " .
                 "WHERE layer_uuid_ref = '{$layer_uuid_}' AND feature_class_uuid_ref = '{$feature_class_uuid_}'";
        $result = $db->Execute($query);
    }
}

function shn_gis_get_layers_all()
{
    global $global;
    $db = $global['db'];
    $query = "SELECT DISTINCT * " .
             "FROM gis_layers";
    $result = $db->Execute($query);

    // create output array
    $output = array();
    while(!$result->EOF){
        $layer = array(
            'l_uuid' => $result->fields['layer_uuid'], 
            'l_name' => $result->fields['name'], 
            'l_description' => $result->fields['description']
        );
        array_push($output, $layer);
        $result->MoveNext();
    }
    return $output;     
}

function shn_gis_get_layers_uuid($layer_uuid_)
{
    global $global;
    $db = $global['db'];
    $query = "SELECT DISTINCT * " .
             "FROM gis_layers where layer_uuid = '$layer_uuid_'";
    $result = $db->Execute($query);
        
    // create output array
    $output = array();
    while(!$result->EOF){
        $output = array(
            'l_uuid' => $result->fields['layer_uuid'], 
            'l_name' => $result->fields['name'], 
            'l_description' => $result->fields['description']
        );
        $result->MoveNext();
    }
    return $output;     
}

/**
 * Returns layers uuids that a feature class is registered to
 * 
 * @global <type> $global
 * @param <type> $feature_class_uuid_
 */
function shn_gis_get_layers_feature_class($feature_class_uuid_)
{
    global $global;
    $db = $global['db'];
    // Find all feature_classes in this layer
    $query = "SELECT DISTINCT layer_uuid_ref " .
              "FROM gis_feature_class_to_layer " .
              "WHERE feature_class_uuid_ref = '{$feature_class_uuid_}'";
    $result = $db->Execute($query);
    
    // create output array
    $output = array();
    while(!$result->EOF){      
        array_push($output, shn_gis_get_layers_uuid($result->fields['layer_uuid_ref']));
        $result->MoveNext();
    }
    return $output;  
}

/**
 * Returns classes in layer
 * 
 * Option 1 returns all class uuids registered to layer.
 * Option 2 returns all classes uuids registered to layer as well as classes of features in that layer
 * not all ready registered.
 * 
 * array(array('c_uuid', c_name,.. ), array('c_uuid', c_name,.. ) ...)
 * @param <type> $layer_uuid_
 */
function shn_gis_get_feature_classes_layer($layer_uuid_, $options)
{
    global $global;
    $db = $global['db'];

    switch($options){
        case 1:
            $query = "SELECT DISTINCT feature_class_uuid FROM gis_feature_class, gis_feature_class_to_layer WHERE layer_uuid_ref = '{$layer_uuid_}' AND gis_feature_class_to_layer.feature_class_uuid_ref = gis_feature_class.feature_class_uuid";
            break;
        
        case 2;
            $from = "gis_feature_class, gis_features, gis_feature_class_to_layer, gis_feature_to_layer, gis_layers";
            $where = "gis_layers.layer_uuid = '{$layer_uuid_}' " .
                 "AND ".
                 "((gis_layers.layer_uuid = gis_feature_class_to_layer.layer_uuid_ref AND gis_feature_class_to_layer.feature_class_uuid_ref = gis_feature_class.feature_class_uuid) " .
                 "OR " .
                 "(gis_layers.layer_uuid = gis_feature_to_layer.layer_uuid_ref AND gis_feature_to_layer.feature_uuid_ref = gis_features.feature_uuid AND gis_features.feature_class_uuid_ref = gis_feature_class.feature_class_uuid))";
            $query = "SELECT DISTINCT feature_class_uuid FROM {$from} WHERE {$where}";
            break;
        
        default:
            shn_gis_get_feature_class_layer($layer_uuid_, 1);
            return;
            break; 
    }
    
    $result = $db->Execute($query);
    $output = array();
    while(!$result->EOF){
        $items = shn_gis_get_feature_class_uuid($result->fields['feature_class_uuid']);
        array_push($output, $items);
        $result->MoveNext(); 
    }
    return $output;
}

////////////////////////
// QUERY STRING GENS
///////////////////////

/*
 * Functions generate strings to use in queries
 * All return a length 3 array containing fields, values in fields and shorthand search names (keys)
 *
 * Note: Remember these functions do not check if what is being entered is correct...
 * This is the job of the parent function !!!
 */

/**
 *   KEY                 TYPE   EXAMPLE VALUE               DESCRIPTION
 * 'f_uuid'           => [str] ['ql5yg-1']                  [Feature unique ID]
 * 'f_type'           => [str] ['point']                    [Feature type use one of ('point', 'line' 'poly')]
 * 'f_coords'         => [str] ['x,y,z,wkt(POINT(x y z))']  [Coordinates center point then coords in wkt(x y z) format ]
 * 'f_class'          => [str] ['ql5yg-1']                  [uuid of feature class]
 * 'f_projection'     => [str] ['EPSG:900913']              [Mapping projection default EPSG:900913 ]
 *
 * @param <type> $keys_
 * @return <type>
 */
function _shn_gis_querygen_feature($keys_)
{
    // arrays containing fields values and keys to be queryed
    $query_feature_fields = array();
    $query_feature_vals = array();
    $query_feature_key = array();

    // feature class
    if(array_key_exists('f_uuid', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_fields, 'gis_features.feature_uuid');
        array_push($query_feature_vals, $keys_['f_uuid']);
        array_push($query_feature_key, 'f_uuid');
    }

    // feature class
    if(array_key_exists('f_class', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_fields, 'gis_features.feature_class_uuid_ref');
        array_push($query_feature_vals, $keys_['f_class']);
        array_push($query_feature_key, 'f_class');
    }
    // feature type
    if(array_key_exists('f_type', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_fields, 'gis_features.feature_type');
        array_push($query_feature_vals, $keys_['f_type']);
        array_push($query_feature_key, 'f_type');
    }
    // feature projection
    if(array_key_exists('f_projection', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_fields, 'gis_features.map_projection');
        array_push($query_feature_vals, $keys_['f_projection']);
        array_push($query_feature_key, 'f_projection');
    }
    // feature coordinates
    if(array_key_exists('f_coords', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_fields, 'gis_features.coords');
        array_push($query_feature_vals, $keys_['f_coords']);
        array_push($query_feature_key, 'f_coords');
    }

    return array($query_feature_fields, $query_feature_vals, $query_feature_key);

}

/**
 *   KEY                 TYPE   EXAMPLE VALUE               DESCRIPTION
 * 'f_class'          => [str] ['ql5yg-1']                  [uuid of feature class]
 * 'f_projection'     => [str] ['EPSG:900913']              [Mapping projection default EPSG:900913 ]
 * 'f_module_item'    => [str] ['ql5yg-2']                  [Module item refrance]
 * 'f_name'           => [str] ['Toms house']               [Name of feature]
 * 'f_description'    => [str] ['Big blue house, blk door'] [Description of feature(can be html)]
 * 'f_author'         => [str] ['Tom']                      [Name of author]
 * 'f_url'            => [str] ['http://www.thouse.com']    [url realated to node]
 * 'f_address'        => [str] ['10 big hill']              [Address at which node resides]
 * 'f_event_date'     => [date]['2008-06-15 15:05:20']      [Date of event which marker represents]
 * 'f_extended_data'  => [str] ['blaa blaa']                [Any extended data assosated with point (sahana specifc)]
 *
 * @param <type> $keys_
 * @return <type>
 */
function _shn_gis_querygen_metadata($keys_)
{
    // arrays containing field, values and keys to be queryed
    $query_metadata_fields = array();
    $query_metadata_vals = array();
    $query_metadata_key = array();

    if(array_key_exists('f_module_item', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.module_item_ref');
        array_push($query_metadata_vals, $keys_['f_module_item']);
        array_push($query_metadata_key, 'f_module_item');
    }
    if(array_key_exists('f_name', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.name');
        array_push($query_metadata_vals, $keys_['f_name']);
        array_push($query_metadata_key, 'f_name');
    }
    if(array_key_exists('f_description', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.description');
        array_push($query_metadata_vals, $keys_['f_description']);
        array_push($query_metadata_key, 'f_description');
    }
    if(array_key_exists('f_author', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.author');
        array_push($query_metadata_vals, $keys_['f_author']);
        array_push($query_metadata_key, 'f_author');
    }
    if(array_key_exists('f_url', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.url');
        array_push($query_metadata_vals, $keys_['f_url']);
        array_push($query_metadata_key, 'f_url');
    }
    if(array_key_exists('f_address', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.address');
        array_push($query_metadata_vals, $keys_['f_address']);
        array_push($query_metadata_key, 'f_address');
    }
    if(array_key_exists('f_event_date', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.event_date');
        array_push($query_metadata_vals, $keys_['f_event_date']);
        array_push($query_metadata_key, 'f_event_date');
    }
    if(array_key_exists('f_extended_data', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.extended_data');
        array_push($query_metadata_vals, $keys_['f_extended_data']);
        array_push($query_metadata_key, 'f_extended_data');
    }
    if(array_key_exists('f_url_view', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.url_view');
        array_push($query_metadata_vals, $keys_['f_url_view']);
        array_push($query_metadata_key, 'f_url_view');
    }
    if(array_key_exists('f_url_edit', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.url_edit');
        array_push($query_metadata_vals, $keys_['f_url_edit']);
        array_push($query_metadata_key, 'f_url_edit');
    }
    if(array_key_exists('f_url_delete', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_metadata_fields, 'gis_feature_metadata.url_del');
        array_push($query_metadata_vals, $keys_['f_url_delete']);
        array_push($query_metadata_key, 'f_url_delete');
    }
    return array($query_metadata_fields, $query_metadata_vals, $query_metadata_key);
}

/**
 *   KEY                 TYPE   EXAMPLE VALUE               DESCRIPTION
 * 'c_uuid'           => [str] ['ql5yg-1']                  [uuid of feature class]
 * 'c_module_ref'     => [str] ['cr']                       [Module name refrance]
 * 'c_name'           => [str] ['Camp']                     [Name of feature class]
 * 'c_description'    => [str] ['A camp']                   [Description of feature class]
 * 'c_icon'           => [str] ['http://sahanahost/www/res/img/markers/marker.png'] [Link to icon representing feature class]
 * 'c_color'          => [str] ['000000']                   [Color of icon for feature class (not currently used)]
 * 
 * @param <type> $keys_
 * @return <type>
 */
function _shn_gis_querygen_feature_class($keys_)
{
    // arrays containing field, values and keys to be queryed
    $query_feature_class_fields = array();
    $query_feature_class_vals = array();
    $query_feature_class_key = array();
    
    if(array_key_exists('c_uuid', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_class_fields, 'gis_feature_class.feature_class_uuid');
        array_push($query_feature_class_vals, $keys_['c_uuid']);
        array_push($query_feature_class_key, 'c_uuid');
    }
    if(array_key_exists('c_module_ref', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_class_fields, 'gis_feature_class.module_ref');
        array_push($query_feature_class_vals, $keys_['c_module_ref']);
        array_push($query_feature_class_key, 'c_module_ref');
    }
    if(array_key_exists('c_name', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_class_fields, 'gis_feature_class.name');
        array_push($query_feature_class_vals, $keys_['c_name']);
        array_push($query_feature_class_key, 'c_name');
    }
    if(array_key_exists('c_description', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_class_fields, 'gis_feature_class.description');
        array_push($query_feature_class_vals, $keys_['c_description']);
        array_push($query_feature_class_key, 'c_description');
    }
    if(array_key_exists('c_icon', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_class_fields, 'gis_feature_class.icon');
        array_push($query_feature_class_vals, $keys_['c_icon']);
        array_push($query_feature_class_key, 'c_icon');
    }
    if(array_key_exists('c_color', $keys_) || array_key_exists('all', $keys_)){
        array_push($query_feature_class_fields, 'gis_feature_class.color');
        array_push($query_feature_class_vals, $keys_['c_color']);
        array_push($query_feature_class_key, 'c_color');
    }
    return array($query_feature_class_fields, $query_feature_class_vals, $query_feature_class_key);
}

/////////////////////////////////////////////////////////////////
//// TODO
////////////////////////////////////////////////////////////////

/*
function shn_gis_get_features_boundingbox($north, $south, $east, $west, $rotation, $fields_)
{

}

*/

/////////////////////////////////////////////////////////////////
//// IMPORT/EXPORT FUNCS
////////////////////////////////////////////////////////////////

/**
 * Prints features as xml in the format given in $file_type_
 * Use in conjuction with shn_text function to offer a file for download
 * 
 * @global <type> $global
 * @global <type> $config
 * @param <type> $file_type_
 * @param <type> $feature_uuids_
 * @return <type>
 */
function shn_gis_create_file($file_name_, $file_type_, $feature_uuids_, $echo = false)
{
    global $global;
    global $config;
    $db = $global['db'];
    require_once $global['approot'] . "/inc/lib_gis/lib_gis_file_factory_download.inc";

    // discover and create aproprate file factory
    if ('gpx' == $file_type_){
        $GeoFactory = new GPXFactory();
    } elseif('gml' == $file_type_){
        $GeoFactory = new GMLFactory();
    } elseif('kml' === $file_type_){
        $GeoFactory = new KMLFactory();
    } elseif('georss' == $file_type_){
        $file_type_ = 'xml';
        $GeoFactory = new GeoRSSFactory();
    } else {
        return false;
    }

    foreach($feature_uuids_ as $feature_uuid){
        $keys = array(
            'f_uuid'          => '1',
            'f_class'         => '1',
            'f_type'          => '1',
            'f_projection'    => '1',
            'f_coords'        => '1',
            'f_module_item'   => '1',
            'f_name'          => '1',
            'f_description'   => '1',
            'f_author'        => '1',
            'f_url'           => '1',
            'f_address'       => '1',
            'f_event_date'    => '1',
            'f_extended_data' => '1'
        );
        $results = shn_gis_get_features_uuid($feature_uuid, $keys);
        if($results){
            $f_uuid           = $results[0]['f_uuid'];
            $f_class          = $results[0]['f_class'];
            $f_type           = $results[0]['f_type'];
            $f_projection     = $results[0]['f_projection'];
            $f_coords         = $results[0]['f_coords'];
            $f_module_item    = $results[0]['f_module_item'];
            $f_name           = $results[0]['f_name'];
            $f_description    = $results[0]['f_description'];
            $f_author         = $results[0]['f_author'];
            $f_url            = $results[0]['f_url'];
            $f_address        = $results[0]['f_address'];
            $f_event_date     = $results[0]['f_event_date'];
            $f_extended_data  = $results[0]['f_extended_data'];
            // Decode coords string
            $coords = shn_gis_coord_decode($f_coords);
            // Get icon from class
            $class = shn_gis_get_feature_class_uuid($f_class);
            $icon = $class['c_icon'];
            switch($f_type){
                case 'point':
                    $GeoFactory->shn_sm_Geo_Add_Point($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $icon, $extendedData, $coords);
                    break;

                case 'line':
                    $GeoFactory->shn_sm_Geo_Add_Path($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                    break;

                case 'poly':
                    $GeoFactory->shn_sm_Geo_Add_Polygon($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                    break;

                default:
                    // miss out feature...
                    break;
            }
        }
    }
    header("Content-type: text/" . $file_type);
    header("Content-Disposition: attachment; filename=" . $file_name_ . "." . $file_type);
    header("Cache-Control: no-cache, must-revalidate");
    if($echo){
        echo $GeoFactory->shn_sm_geo_print();
    } else {
        return $GeoFactory->shn_sm_geo_print();
    }
}

/**
 * Creates a feed using features uuids from database
 * Saves to "www/export/georss/$name_.xml"
 * 
 * @global <type> $global
 * @global <type> $config
 * @param <type> $name_
 * @param <type> $feature_uuids_
 * @return <type>
 */
function shn_gis_create_feed($name_, $feature_uuids_, $feed_type_ = 'georss', $overwrite_ = true)
{
    global $global;
    global $config;
    require_once $global['approot'] . "/inc/lib_gis/lib_gis_file_factory_download.inc";
    
    // discover and create appropriate file factory
    if ('gpx' == $feed_type_){
        $GeoFactory = new GPXFactory();
    } elseif('gml' == $feed_type_){
        $GeoFactory = new GMLFactory();
    } elseif('kml' === $feed_type_){
        $GeoFactory = new KMLFactory();
    } elseif('georss' == $feed_type_){
        $GeoFactory = new GeoRSSFactory();
    } else {
        return false;
    }
    
    foreach($feature_uuids_ as $feature_uuid){
        $keys = array(
            'f_uuid'          => '1',
            'f_class'         => '1',
            'f_type'          => '1',
            'f_projection'    => '1',
            'f_coords'        => '1',
            'f_module_item'   => '1',
            'f_name'          => '1',
            'f_description'   => '1',
            'f_author'        => '1',
            'f_url'           => '1',
            'f_address'       => '1',
            'f_event_date'    => '1',
            'f_extended_data' => '1'
        );
        $results = shn_gis_get_features_uuid($feature_uuid, $keys);
        if($results){
            $f_uuid           = $results[0]['f_uuid'];
            $f_class          = $results[0]['f_class'];
            $f_type           = $results[0]['f_type'];
            $f_projection     = $results[0]['f_projection'];
            $f_coords         = $results[0]['f_coords'];
            $f_module_item    = $results[0]['f_module_item'];
            $f_name           = $results[0]['f_name'];
            $f_description    = $results[0]['f_description'];
            $f_author         = $results[0]['f_author'];
            $f_url            = $results[0]['f_url'];
            $f_address        = $results[0]['f_address'];
            $f_event_date     = $results[0]['f_event_date'];
            $f_extended_data  = $results[0]['f_extended_data'];
            // Decode coords string
            $coords = shn_gis_coord_decode($f_coords);
            // Get icon from class
            $class = shn_gis_get_feature_class_uuid($f_class);
            $icon = $class['c_icon'];
            switch($f_type){
                case 'point':
                $GeoFactory->shn_sm_Geo_Add_Point($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $icon, $extendedData, $coords);
                break;
                case 'line':
                $GeoFactory->shn_sm_Geo_Add_Path($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                break;
                case 'poly':
                $GeoFactory->shn_sm_Geo_Add_Polygon($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                break;
                default:
                // miss out feature...
                break;
            }
        }
    }
    
    // Saves to "www/export/georss/$name_.xml"
    return $GeoFactory->shn_sm_geo_publish($name_, $overwrite_);       
}

function shn_sm_check_file_upload()
{
    global $global;
    global $conf;
    global $file;
    $extension_str = ' .' . implode(', .', $conf['gis_file_extensions']);
    
    //get the extension and the tmp name of the file
    unset($_SESSION['gis']['files']['filetype']);
    $_SESSION['gis']['files']['filetype'] = end(explode('.',$_FILES['load']['name']));
    unset($_SESSION['gis']['files']['file']);
    $_SESSION['gis']['files']['file'] ="./tmp/".basename($_FILES['load']['name']);
    //check for tmp file permision
    if(!is_writable('./tmp')){
        add_error(_('Make sure the tmp folder is writable'));
    }
    //check whether an error occurred
    else if($file['error']!= 0){
        //give error information
        switch ($file['error']){
            case 1:
            case 2:
                add_error(_('The uploaded file exceeds the Max upload size'));
                break;
            case 3:
                add_error(_('The uploaded file was only partially uploaded.'));
                break;
            case 4:
                add_error(_('No file was uploaded :  Please press the browse button and select a file to upload before you press the next button'));
                break;
        }
    }
    //check for correct extension
    else if(!in_array($_SESSION['gis']['files']['filetype'], $conf['gis_file_extensions'])){
        add_error(_t("Please upload a file with one of these extensions: ") . $extension_str );
    }
    //move the uploaded file to the tmp directory
    else if (move_uploaded_file($_FILES['load']['tmp_name'], $_SESSION['gis']['files']['file'])) {
        // Check file types
        if(!(FALSE === array_search($_SESSION['gis']['files']['filetype'], $conf['gis_file_extensions'])) && !shn_sm_xml_validator()) {
            return true;
        } else {
            add_error(_('Possible file upload attack!'));
            return false;
        }
    }
}

function shn_sm_xml_validator()
{
    $error_flag=false;
    
    class SchemaDOMDocument extends DOMDocument
    {
        public function validateXMLSchemas()
        {
            global $ext;
            // Do we want to validate against old schema versions of filetype ???
            $schemaLocation = $conf['schema_location_' . $ext];

            $pairs = preg_split('/\s+/', $schemaLocation);
            $pairCount = count($pairs);
            $valid = true;
            for($x = 1; $x < $pairCount; $x+=2) {
                $valid = $this->schemaValidate($pairs[$x]) && $valid;
            }
            if(!$valid) {
                return false;
            }
            return true;
        }
    }//end of class SchemaDOMDocument

    $file = $_SESSION['gis']['files']['file'];

    if (!($fp = fopen($file, "r"))) {
        add_error(_("Can not open file."));
        unlink($file);
        return $error_flag=true;;
    }

    $xml = fread($fp,filesize($file));
    // close the file
    fclose($fp);

    $parser = xml_parser_create ();
    if (!xml_parse ($parser, $xml, true)) {
        xml_parser_free ($parser);
        unlink($file);
        add_error(_("Your File is not well-formed. Please upload a well-formed file"));
        return $error_flag=true;;
    }
    $library = new SchemaDOMDocument("1.0");
    $library->validateOnParse = true;
    $library->load($file);
    
    if($library->validateXMLSchemas()) {
        return $error_flag=false;;
    } else {
        unlink($file);
        add_error(_("Your File is not valid. Please upload a valid file"));
        return $error_flag=true;
    }
}

function shn_gis_draw_polylines($cords,$title=null){
	
	global $global;
	global $conf;
	$db = $global['db'];
	if($conf['gis'])
	{
		
        if("openlayers"==$conf['gis_dflt']) {
            
            $plugin_name = $conf['gis_dflt'];
            include $global['approot']."/inc/lib_gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
            show_map_polylines($cords,$title);
        } else {
            return;
        }
	}
	else
		shn_gis_print_msg();
	
	
}


