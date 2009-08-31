<?php

/** 
 * Wikimaps functionality for Sitaution Awareness module
 * PHP version 5
 *
 * @author   	Mifan Careem <mifan@opensource.lk>
 * @author   	Fran Boon <flavour@partyvibe.com>
 * @author      Richard Smith <s0459387@sms.ed.ac.uk>
 * @copyright  	Lanka Software Foundation - http://www.opensource.lk
 * @module      sm
 * @version     $id$;
 * @copyright  	Lanka Software Foundation - http://www.opensource.lk
 * @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

// ==============================
// Sequences
// ==============================

/**
* Shows map of all catalogues and internal features.
* @global <type> $global
*/
function shn_sm_show_map_home()
{
    global $global;
    require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";

    // set values for db to return.
    $keys_ = array('all' => '1');
    // Find and show all features in system. If more than 250, OpenLayers will bail and DIE !!!
    $features = shn_gis_get_features_all($keys_);
    shn_gis_form_map_with_features($features);
}

function shn_sm_show_features_map()
{
    global $global;
    require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";

    // set values for db to return.
    $keys_ = array('all' => '1');
    // Find and show all features in system. If more than 250, OpenLayers will bail and DIE !!!
    $features = shn_gis_get_features_all($keys_);
    _shn_sm_form_catalogue_shortcuts();
    shn_gis_form_map_with_features($features);
}
  
/**
* Sequence to Add a Feature to the internal GIS database.
* 
* This function can be called anywhere within Sahana.
* (if $return_action and $return_module are set it should return to 
* the correct same place after exe) 
* 
* @global <type> $steps
* @param <type> $return_action_
* @param <type> $return_module_
*/
function shn_sm_feature_add_seq($return_action_ = NULL, $return_module_ = NULL)
{
    global $steps;
    $steps = array('Feature Details', 'Map', 'Layers', 'Confirm');

    // If a user wishes to return to a page other than admin home on cancel or finish
    if(return_module_ != NULL && $return_action_ != NULL){
        $_SESSION['sm']['feature_add']['return_action'] = $return_action_;
        $_SESSION['sm']['=feature_add']['return_module'] = $return_module_;
    }

    // If user cancels sequence
    if(isset($_REQUEST['cancel'])){
        add_warning(_t('Operation Cancelled'));
        _shn_sm_feature_add_return();
    // If user is in sequence
    } elseif(isset($_REQUEST['seq'])){
        switch($_REQUEST['seq']){
            case 'seq_2':   
                _shn_sm_feature_add_seq_2();
                break;
            case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_sm_feature_add_seq_1();
                } else {
                    _shn_sm_feature_add_seq_3();
                }
                break;
            case 'seq_4':
                if(isset($_REQUEST['back'])){
                    _shn_sm_feature_add_seq_2();
                } else {
                    _shn_sm_feature_add_seq_4();
                }
                break;
            case 'seq_5':
                if(isset($_REQUEST['back'])){
                    _shn_sm_feature_add_seq_3();
                } else {
                    _shn_sm_feature_add_seq_5();
                }
                break;
            default:
                add_error(_t('Something went wrong'));
                _shn_sm_feature_add_return();
                break;
        }
    // if user is starting sequence
    } else {
        // enter detail page
        unset($_SESSION['sm']['feature_add']);

        // Set layer array (for later on)
        _shn_sm_feature_add_seq_1();
    }
}
    
function shn_sm_analysis_radius_seq()
{
    global $steps;
    $steps = array('Enter Details', 'Results');

    // If a user wishes to return to a page other than admin home on cancel or finish
    if(return_module_ != NULL && $return_action_ != NULL){
        $_SESSION['sm']['analysis_radius']['return_action'] = $return_action_;
        $_SESSION['sm']['analysis_radius']['return_module'] = $return_module_;
    }

    // If user cancels sequence
    if(isset($_REQUEST['cancel'])){
        add_warning(_t('Operation Cancelled'));
        _shn_sm_analysis_radius_return();
    // If user is in sequence
    } elseif(isset($_REQUEST['seq'])){
        switch($_REQUEST['seq']){
            case 'seq_2':   
                _shn_sm_analysis_radius_seq_2();
                break;
            case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_sm_analysis_radius_seq_1();
                } else {
                    _shn_sm_analysis_radius_seq_3();
                }
                break;
            default:
                add_error(_t('Something went wrong'));
                _shn_sm_analysis_radius_return();
                break;
        }
    // if user is starting sequence
    } else {
        // enter detail page
        unset($_SESSION['sm']['analysis_radius']);
        // Set layer array (for later on)
        _shn_sm_analysis_radius_seq_1();
    }
}

// ==============================
// Sequences Actions
// ==============================

function _shn_sm_analysis_radius_seq_1()
{
    $button_set = array('cancel' => true, 'custom' => array(array('value' => 'Analyse', 'submit_opts' => 'name = "next"')));
    _shn_sm_form_analysis_radius('analysis_radius', 'seq_2', $button_set);
}
    
function _shn_sm_analysis_radius_seq_2()
{      
    global $global;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

    $lat = trim($_REQUEST['sm_radius_lat']);
    $lon = trim($_REQUEST['sm_radius_lon']);

    // validate coords....
    $radius = trim($_REQUEST['sm_radius_distance']);
    if('' != $lat && '' != $lon && '' != $radius){
        // set values for db to return.
        $keys_ = array('all' => '1');
        // Find and show all features in system. If more than 250, OpenLayers will bail and DIE !!!
        $features = shn_gis_get_features_in_radius($keys_, $lat, $lon, $radius);
        if($features === false){
            add_error(_t('Search Failed'));
            return;
        }
        if(count($features) > 0){
            // Show all feature on map
            shn_gis_form_map_with_features($features);
            $bearing = shn_gis_bearing($latitude, $longitude, $lat, $lon);  
        } else{
            add_confirmation(_t('No Situations found within this Radius'));
            _shn_sm_analysis_radius_seq_1();
            return;
        }
    } else{
        add_warning(_t('Not all fields have data. Not possible to run analysis'));
        _shn_sm_analysis_radius_seq_1();
        return;
    }
}

function _shn_sm_analysis_radius_seq_3()
{
}

/**
* Report on Situations within a Radius of a Position
*/
function shn_sm_radius_analyse_process()
{
    global $global;
    global $conf;
    $db = $global['db'];
    if(!null==$_POST['sm_radius_lat'] && !null==$_POST['sm_radius_lon'] && !null==$_POST['sm_radius_distance']){
        // ToDo: http://wiki.sahana.lk/doku.php?id=dev:form_validation
        $latitude = floatval($_POST['sm_radius_lat']);
        $longitude = floatval($_POST['sm_radius_lon']);
        $radius = $_POST['sm_radius_distance'];
        // call GIS API
        include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        $array = shn_gis_features_in_radius($latitude,$longitude,$radius);
        if(!0==sizeof($array)){
            print '<h2>'._t("Radius Report").'</h2>';
            if ($latitude > 0) {
                $northing = "N";
                $lat = $latitude;
            } else {
                $northing = "S";
                $lat = ltrim($latitude,"-");
            }
            if ($longitude > 0) {
                $easting = "E";
                $lon = $longitude;
            } else {
                $easting = "W";
                $lon = ltrim($longitude,"-");
            }
            print '<p>'._t("These are the Situations within a")." $radius km "._t("radius of")." $lat $northing, $lon $easting:</p>";
            print '<table><thead><td>'._t("Situation").'</td><td>'._t("Description").'</td><td>'._t("Distance").' (km)</td><td>'._t("Bearing").'</td><td>'._t("Date").'</td></thead><tbody>';
            for($i=0;$i< sizeof($array);$i++){
                $poc_uuid=$array[$i]["poc_uuid"];
                // Filter for only Situations
                $identifier="wm-";
                if (!FALSE==strpos($poc_uuid,$identifier)) {
                    $distance=round($array[$i]["distance"],1);
                    // Keep precise if using in calculations instead of displaying to users
                    $lat=$array[$i]["lat"];
                    $lon=$array[$i]["lon"];
                    // Lookup extra details in Situations table
                    $query = "SELECT name,description,event_date FROM gis_wiki WHERE wiki_uuid = '$poc_uuid'";
                    $res = $db->Execute($query);
                    $name=$res->fields['name'];
                    $description=$res->fields['description'];
                    $date=$res->fields['event_date'];
                    // Show Bearing, not Lat/Lon in table
                    $bearing=shn_gis_bearing($latitude,$longitude,$lat,$lon);
                    // ToDo: Make entries into clickable links to view on Map
                    print "<tr><td>$name</td><td>$description</td><td align=center>$distance</td><td>$bearing</td><td>$date</td></tr>";
                }
            }
            print "</tbody></table>";
        } else {
            add_confirmation(_t('No Situations found within this Radius'));
            shn_sm_analysis_radius_form();
        }
    } else {
        add_warning(_t('Not all fields have data. Not possible to run analysis'));
        shn_sm_analysis_radius_form();
    }
}

// ==============
// Add a Feature
// ==============

/**
* Displays Form in which to enter features details.
*
* @global <type> $global
* @global <type> $steps
*/
function _shn_sm_feature_add_seq_1()
{
    global $global;
    global $steps;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    // Display progress bar.
    shn_form_progress_bar($steps, 1);
    if(isset($_REQUEST['back'])){
        $class    = $_SESSION['sm']['feature_add']['class'];
        $name     = $_SESSION['sm']['feature_add']['name'];
        $desc     = $_SESSION['sm']['feature_add']['description'];
        $date     = $_SESSION['sm']['feature_add']['event_date'];
        $author   = $_SESSION['sm']['feature_add']['author'];
        $url      = $_SESSION['sm']['feature_add']['url'];
        $address  = $_SESSION['sm']['feature_add']['address'];
    }
    // Add in js so that if a feature is selected that cannot be created in this module a link is provided...
    $button_set = array('cancel' => true, 'next' => true);
    _shn_sm_form_input_feature_details('awik', 'seq_2', $button_set, $class, $name, $desc, $date, $author, $url, $address);
}
/**
* Displays map to locate the position of the feature
* 
* @global <type> $global
* @global <type> $steps
* @return <type>
*/
function _shn_sm_feature_add_seq_2()
{
    global $global;
    global $steps;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    if(isset($_REQUEST['next'])){
        // Run checks in case user tries to create a feature of a class that is registered to an existing module.
        if(isset($_REQUEST['c_uuid']) && trim($_REQUEST['c_uuid']) != ''){
            $full_class = shn_gis_get_feature_class_uuid(trim($_REQUEST['c_uuid']));
            if(!(isset($full_class['c_module_ref']) && $full_class['c_module_ref'] != '')){
                $_SESSION['sm']['feature_add']['class'] = trim($_REQUEST['c_uuid']);
            } else{
                add_error(_t('A Feature of this Class can only be created inside its own module') . ' <a href="index.php?mod=' . $full_class['c_module_ref'] .'&act=default">' . _t('HERE') . '</a>');
                _shn_sm_feature_add_seq_1();
                return;
            } 
        } else{
            add_error(_t('Select A Feature Class'));
            _shn_sm_feature_add_seq_1();
            return;
        }

        if(isset($_REQUEST['f_name']) && trim($_REQUEST['f_name']) != ''){
            $_SESSION['sm']['feature_add']['name'] = trim($_REQUEST['f_name']);
        } else{
            add_error(_t('Enter Feature Name'));
            _shn_sm_feature_add_seq_1();
            return;
        }

        $_SESSION['sm']['feature_add']['description'] = trim($_REQUEST['f_description']);
        $_SESSION['sm']['feature_add']['event_date'] = trim($_REQUEST['f_event_date']);
        $_SESSION['sm']['feature_add']['author'] = trim($_REQUEST['f_author']);
        $_SESSION['sm']['feature_add']['url'] = trim($_REQUEST['f_url']);
        $_SESSION['sm']['feature_add']['address'] = trim($_REQUEST['f_address']);
    }
    // Display progress bar.
    shn_form_progress_bar($steps, 2);
    // Show map
    $button_set = array('cancel' => true, 'back' => true, 'next' => true);
    echo 
    _shn_sm_form_input_feature_location('awik', 'seq_3', $button_set, $_SESSION['sm']['feature_add']['class']);
}

/**
 * Displays form to select the layers the feature should belong to.
 *
 * @global <type> $global
 * @global <type> $steps
 * @return <type>
 */
function _shn_sm_feature_add_seq_3()
{
    global $global;
    global $steps;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    require_once $global['approot']."/inc/lib_validate.inc";
    if(isset($_REQUEST['next'])){
        // add in support for lines and areas.
        if(trim($_POST['loc_type']) == ''){
            $_SESSION['sm']['feature_add']['type'] = 'point';
        } else {
            $_SESSION['sm']['feature_add']['type'] = $_POST['loc_type'];
        }
        if(isset($_POST['loc_x']) && $_POST['loc_x'] != '' && (true === shn_valid_x_coordinate($_POST['gps_x']))  && isset($_POST['loc_y']) && $_POST['loc_y'] != '' && (true === shn_valid_y_coordinate($_POST['loc_y']))){
            $_SESSION['sm']['feature_add']['loc_x'] = $_POST['loc_x'];
            $_SESSION['sm']['feature_add']['loc_y'] = $_POST['loc_y'];
            $_SESSION['sm']['feature_add']['loc_wkt'] = $_POST['loc_wkt'];
        } elseif(isset($_POST['gps_x']) && $_POST['gps_x'] != '' && (true === shn_valid_x_coordinate($_POST['gps_x'])) && isset($_POST['gps_y']) && $_POST['gps_y'] != '' && (true === shn_valid_y_coordinate($_POST['gps_y']))){
            $_SESSION['sm']['feature_add']['loc_x'] = $_POST['gps_x'];
            $_SESSION['sm']['feature_add']['loc_y'] = $_POST['gps_y'];
            $_SESSION['sm']['feature_add']['loc_wkt'] = $_POST['loc_wkt'];
        } else {
            add_error(_t('Invalid Coordinates'));
            unset($_REQUEST['next']);
            _shn_sm_feature_add_seq_2();
            return;
        }
    }
    $_SESSION['sm']['feature_add']['class_layer_uuids'] = array();
    // Finds all layers, checks any that have already been checked.
    $layers = shn_gis_get_layers_all();
    $l_uuids_class = shn_gis_get_layers_feature_class($_SESSION['sm']['feature_add']['class']);
    $l_uuids_pre = $_SESSION['sm']['feature_add']['extra_layer_uuids'];
    for($i = 0; $i < count($layers); $i++){
        // Tick features that have already been selected.
        foreach($l_uuids_pre as $uuid_pre){
            if($layers[$i]['l_uuid'] == $uuid_pre){
                $layers[$i]['checked'] = '1';
            }
        }
        // Disable layers that feature already belongs to as a result of its feature class.
        foreach($l_uuids_class as $uuid_class){
            if($layers[$i]['l_uuid'] == $uuid_class['l_uuid']){
                $layers[$i]['disabled'] = '1';
                array_push($_SESSION['sm']['feature_add']['class_layer_uuids'], $uuid_class['l_uuid']);
            }
        }
    }
    // Show progress bar
    shn_form_progress_bar($steps, 3);
    $button_set = array('cancel' => true, 'back' => true, 'next' => true);
    _shn_sm_form_select_layers('awik', 'seq_4', $button_set, $layers);
}

/**
 * Shows confirm page.
 *
 * @global <type> $global
 * @global <type> $steps
 */
function _shn_sm_feature_add_seq_4()
{
    global $global;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    if(isset($_REQUEST['next'])){
        // Catch layer uuids from previous form.
        $uuids = array();
        $limit = $_REQUEST['count'];
        for($i = 1; $i <= $limit; $i++){
            if(isset($_POST[$i])){
                array_push($uuids, $_POST[$i]);
            }
        }
        // Set new selected uuids session
        $_SESSION['sm']['feature_add']['extra_layer_uuids'] = $uuids;
        $uuids = array_merge($_SESSION['sm']['feature_add']['class_layer_uuids'], $uuids);
    } else {
        $uuids = array_merge($_SESSION['sm']['feature_add']['class_layer_uuids'], $_SESSION['sm']['feature_add']['extra_layer_uuids']);
    }
    // Get rid of dupes caused by back -> forward action.
    $uuids = array_unique($uuids);
    // Get layers from uuids to display
    $layers = array();
    foreach($uuids as $uuid){
        array_push($layers, shn_gis_get_layers_uuid($uuid));
    }
    $class    = shn_gis_get_feature_class_uuid($_SESSION['sm']['feature_add']['class']);
    $lat      = $_SESSION['sm']['feature_add']['loc_y'];
    $lon      = $_SESSION['sm']['feature_add']['loc_x'];
    $name     = $_SESSION['sm']['feature_add']['name'];
    $desc     = $_SESSION['sm']['feature_add']['description'];
    $date     = $_SESSION['sm']['feature_add']['event_date'];
    $author   = $_SESSION['sm']['feature_add']['author'];
    $url      = $_SESSION['sm']['feature_add']['url'];
    $address  = $_SESSION['sm']['feature_add']['address'];
    $type     = $_SESSION['sm']['feature_add']['type'];     
    // Show progress bar
    shn_form_progress_bar($steps, 4);
    echo '<h2>' . _t("Confirm New Feature") . '</h2>';
    $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
    _shn_sm_form_feature_confim('awik', 'seq_5', $button_set, $class, $name, $desc, $type, $lat, $lon, $date, $author, $url, $address, $layers);
}

/**
 * @global <type> $global
 */
function _shn_sm_feature_add_seq_5()
{
    // Make sure all end checks are completed
    global $global;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    if(isset($_REQUEST['finish'])){
        // set new feature class vars.
        $class    = $_SESSION['sm']['feature_add']['class'];
        $name     = $_SESSION['sm']['feature_add']['name'];
        $desc     = $_SESSION['sm']['feature_add']['description'];
        $date     = $_SESSION['sm']['feature_add']['event_date'];
        $author   = $_SESSION['sm']['feature_add']['author'];
        $url      = $_SESSION['sm']['feature_add']['url'];
        $address  = $_SESSION['sm']['feature_add']['address'];
        $proj     = '';
        $layers   = $_SESSION['sm']['feature_add']['extra_layer_uuids'];
        $type     = $_SESSION['sm']['feature_add']['type'];
        $lat      = $_SESSION['sm']['feature_add']['loc_y'];
        $lon      = $_SESSION['sm']['feature_add']['loc_x'];
        if(trim($_SESSION['sm']['feature_add']['loc_wkt']) != ''){
            $coords = $lon . ',' . $lat . ',' . 0 . ',wkt{' .  $_SESSION['sm']['feature_add']['loc_wkt'] . '}';
        } else{
            $coords = array(array($lon, $lat, 0), array($lon, $lat, 0));
            $coords = shn_gis_coord_encode($coords, $type);
        }
        // Check again feature class is allowed.
        $full_class = shn_gis_get_feature_class_uuid($class);
        if(!(isset($full_class['c_module_ref']) && $full_class['c_module_ref'] != '')){
            // Check vars are set
            if($class != NULL && $class != '' && $name != NULL && $name != '' && $type != NULL && $type != '' && (true === shn_valid_x_coordinate($lon))  && (true === shn_valid_y_coordinate($lat))){
                $keys = array(  
                    'f_class'         => $class,
                    'f_type'          => $type,
                    'f_projection'    => $proj,
                    'f_coords'        => $coords,  
                    'f_name'          => $name,
                    'f_description'   => $desc,
                    'f_author'        => $author,
                    'f_url'           => $url,
                    'f_address'       => $address,
                    'f_event_date'    => $date,
                );
                // Create new feature class.
                $uuid = shn_gis_create_feature($keys);
                // Show confimation if successful, or error if not.
                if($uuid){
                    add_confirmation(_t('Added New Feature.'));
                    foreach($layers as $layer_uuid){ 
                        shn_gis_insert_layer_features($layer_uuid, array($uuid));
                        add_confirmation(_t('Added Feature to Layer'));
                    }  
                } else {
                    add_error(_t('Feature could not be created.'));
                }
            } else {
                add_error(_t('Feature could not be created. Insufficient details'));  
            }
        } else {
            add_error(_t('Feature could not be created. A Feature of this Class can only be created inside its own module'). ' <a href="index.php?mod=' . $full_class['c_module_ref'] .'&act=default">' . _t('HERE') . '</a>');
        }
    } else {
        add_error(_t('Use Finish'));  
    }
    // Show return page.
    _shn_sm_feature_add_return();
}

/**
 * Displays button to return to location prior to starting sequence
 */
function _shn_sm_feature_add_return()
{
    if(isset($_SESSION['sm']['feature_add']['return_action']) && isset($_SESSION['sm']['feature_add']['return_module'])){
        $return_action = $_SESSION['sm']['feature_add']['return_action'];
        $return_module = $_SESSION['sm']['feature_add']['return_module'];
    } else {
        $return_action = 'default';
        $return_module = 'sm';
    }
        
    // Unset all session values.
    unset($_SESSION['sm']['feature_add']);
    _shn_sm_form_return($return_action, $return_module);
}

// ==============================
// Sequences Action Forms
// ==============================

/**
 * Form for entering details of a new Feature.
 * 
 * @global <type> $global
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 */
function _shn_sm_form_input_feature_details($act, $seq, $button_set, $class = '', $name = '', $desc = '', $date = '', $author = '', $url = '', $address = '', $proj = '')
{
    global $global;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

    $help_name = _t('Enter a name for the Feature eg. Wishing well.');
    $help_description = _t('Enter a description of the feature eg. Well full on coins.');
    $help_event_date = _t('Enter the date that the event occurred on (if relevant).');
    $help_author = _t('Enter your name.');
    $help_url = _t('Enter a link relevant to the feature.');
    $help_address = _t('Enter the Address at which the feature resides (if relevant');

    echo '<h2>' . _t("Enter Situation Detail") . '</h2>';
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    shn_form_fsopen(_t("Main Details"));

    $f_classes = shn_gis_get_feature_class_all();
    foreach($f_classes as $f_class){
        $options_c[$f_class['c_uuid']] = $f_class['c_name'];
    }
    shn_form_select($options_c, "Feature Class", "c_uuid", $select_opts = "", $extra_opts = array('value' => $class));
    shn_form_text(_t("Name of Feature"),"f_name",'size="48" maxlength="60"', array('value' => $name, 'req' => true, 'help' => $help_name));
    shn_form_textarea(_t("Description"), "f_description", "rows='5' cols='70'", array('value' => $desc, 'req' => false, 'help' => $help_description));
    shn_form_fsclose();
    shn_form_fsopen(_t("Extra Details"));
    shn_form_date(_t("Date of Event"), "f_event_date", array('value' => $date, 'req' => false, 'help' => $help_event_date));
    shn_form_text(_t("Author"), "f_author", 'size="48" maxlength="60"', array('value' => $author, 'req' => false, 'help' => $help_author));
    shn_form_text(_t("URL"), "f_url", 'size="48"  maxlength="100"', array('value' => $url, 'req' => false, 'help' => $help_url));
    shn_form_textarea(_t("Address"), "f_address", "rows='5' cols='70'", array('value' => $address, 'req' => false, 'help' => $help_address));
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Show form with map for adding features location.
 * 
 * @global <type> $global
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 */
function _shn_sm_form_input_feature_location($act, $seq, $button_set, $feature_class)
{
    global $global;    
    require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";
    echo '<h2>' . _t("Location Feature Position") . '</h2>';
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    // call GIS API for a map
    shn_gis_form_map_single_geometry($button_set, $feature_class);
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Display form showing options for selecting layers to add features to.
 * 
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 * @param <type> $layers
 */
function _shn_sm_form_select_layers($act, $seq, $button_set, $layers)
{
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    echo '<h2>' . _t('Layer Options') . '</h2>';
                            echo "<div class='message information'>";
    echo _t('Gray (Disabled) Layers show Layers that the Feature belongs to as a result of its Feature Class.') . '<br /> <br />' . _t('These layers can only be changed by:');
    echo '<ul><li>' . _t('Changing the Feature\'s Feature Class') . '</li>';
    echo '<li>' . _t('Changing the Layers the Feature Class Belongs to (Administrator Settings)') . '</li></ul>';
    echo "</div>";
    shn_form_fsopen(_t('Layer Options'));

    shn_form_label(_t('Add Feature to Layers:'));
    $count = 0;
    foreach($layers as $layer){
        $count++;
        $extra_opts = '';
        if(isset($layer['checked'])){
            $extra_opts = 'checked = "checked"';
        }
        if(isset($layer['disabled'])){
            $extra_opts = 'checked = "checked" disabled="disabled"';
        }
        shn_form_checkbox($layer['l_name'], $count, $extra_opts, array('value' => $layer['l_uuid']));
    }
    shn_form_hidden(array('count' => $count));
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Confirm form for adding features.
 * 
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 * @param <type> $class
 * @param <type> $name
 * @param <type> $desc
 * @param <type> $type
 * @param <type> $lat
 * @param <type> $lon
 * @param <type> $date
 * @param <type> $author
 * @param <type> $url
 * @param <type> $address
 * @param <type> $layers_
 */
function _shn_sm_form_feature_confim($act, $seq, $button_set, $class = '', $name = '', $desc = '', $type = '', $lat = '', $lon = '', $date = '', $author = '', $url = '', $address = '', $layers_ = array())
{
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    shn_form_fsopen(_t('General Details'));
    shn_form_label(_t('Feature Class'), $class['c_name']);
    shn_form_label(_t('Feature Name'), $name);
    shn_form_label(_t('Feature Description'), $desc);
    shn_form_label(_t('Feature Type'), $type);
    shn_form_label(_t('Coordinates Latitude'), $lat);
    shn_form_label(_t('Coordinates Longitude'), $lon);
    shn_form_fsclose();
    shn_form_fsopen(_t('Extra Details'));
    shn_form_label(_t('Date'), $date);
    shn_form_label(_t('Author'), $author);
    shn_form_label(_t('Url'), $url);
    shn_form_label(_t('Address'), $address);
    shn_form_fsclose();
    shn_form_fsopen(_t('Layer Details'));
    shn_form_label(_t('Belongs to Layers:'));
    foreach($layers_ as $layer){
        shn_form_label('', $layer['l_name']);
    }
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Report on Situations within a Radius of a Position 
 */
function _shn_sm_form_analysis_radius($act, $seq, $button_set)
{
    $lat_help = _t("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
    $lon_help = _t("Longitude is West - East (Sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
    $radius_help = _t("Distance from the selected location to the search circle's edge - measured in kilometers.");
    
    shn_form_fopen($act, null, array('req_message'=>true));
    shn_form_hidden(array('seq' => $seq));
    shn_form_fsopen(_t('Situation Analysis'));
    shn_form_fsopen(_t('Radius'));
    echo '<p>'._t("Report on which situations are located within a specified radius of a selected location").'.</p>';
    shn_form_fsclose();
    $lat_help=_t("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
    $lon_help=_t("Longitude is West - East (sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
    $radius_help=_t("Distance from the selected location to the search circle's edge - measured in kilometers.");
    shn_form_text(_t('Latitude: '),"sm_radius_lat",'size=40',array('req'=>true,"help"=>$lat_help));
    shn_form_text(_t('Longitude: '),"sm_radius_lon",'size=40',array('req'=>true,"help"=>$lon_help));
    shn_form_text(_t('Radius (km): '),"sm_radius_distance",'size=40',array('req'=>true,"help"=>$radius_help));
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Image Upload Form as part of adding situations.
 * 
 * @access public
 * @global <type> $global
 */
function _shn_sm_form_add_image()
{        
    global $global;
    include_once ($global['approot'].'/inc/lib_form.inc');
    shn_form_fopen(awik,null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_hidden(array('seq'=>'com'));
    shn_form_fsopen(_t("Situation Image"));
    shn_form_upload(_t("Upload Image"),'image');
    shn_form_fsclose();
    shn_form_submit(_t('Next'));
    shn_form_fclose();
}

/**
 * Print form of links to catalogue admin options.
 */
function _shn_sm_form_catalogue_shortcuts()
{
    // Shortcuts to GIS Catalogue
    include_once $global['approot']."/inc/lib_gis/admin_acts.inc";
    print "<table><tr><td style=\"border: 0px;\">";
    print _t("GIS Administration:");
    print "</td><td style=\"border: 0px;\">";
    shn_form_fopen(gis_main,admin,array('req'=>false));
    shn_form_submit(_t("Defaults"));
    shn_form_fclose();
    print "</td><td style=\"border: 0px;\">";
    shn_form_fopen(gis_files,admin,array('req'=>false));
    shn_form_submit(_t("Files"));
    shn_form_fclose();
    print "</td><td style=\"border: 0px;\">";
    shn_form_fopen(gis_layers,admin,array('req'=>false));
    shn_form_submit(_t("Layers"));
    shn_form_fclose();
    print "</td><td style=\"border: 0px;\">";
    shn_form_fopen(gis_markers,admin,array('req'=>false));
    shn_form_submit(_t("Markers"));
    shn_form_fclose();
    print "</td><td style=\"border: 0px;\">";
    shn_form_fopen(gis_projections,admin,array('req'=>false));
    shn_form_submit(_t("Projections"));
    shn_form_fclose();
    print "</td></tr></table>";
}

/**
 * Displays return options.
 *
 * @param <type> $return_action_
 * @param <type> $return_module_
 */
function _shn_sm_form_return($return_action_, $return_module_)
{
    shn_form_fopen($return_action_, $return_module_, array());
    shn_form_fsopen(_t('Return to Original Menu'));
    shn_form_submit(_t('Return'), 'name="return"');
    shn_form_fsclose();
    shn_form_fclose();
}

// ==============================
// Extra functions
// ==============================
function shn_sm_image_handler()
{
    // Handle images
    //@todo: image type
    $image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.jpeg';
    $image_path="tmp/".$image_name;
    $image_file=$global['approot'].$conf['mod_sm_image_folder'].$image_name;
    // No image available and other format support
    if(!file_exists($image_file)){
        //check jpg
        $image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.jpg';
        $image_path="tmp/".$image_name;
        $image_file=$global['approot'].$conf['mod_sm_image_folder'].$image_name;
        if(!file_exists($image_file)){
            //check png
            $image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.png';
            $image_path="tmp/".$image_name;
            $image_file=$global['approot'].$conf['mod_sm_image_folder'].$image_name;
            if(!file_exists($image_file)){
                $image_path=null;
            }
        }
    }
}

