<?php

/**
* Main home page of the GPS Module
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sriganeshan <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @author     Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
include_once $global['approot']."/mod/gps/main_fns.inc";
include_once $global['approot']."/mod/gps/handler_marker.inc";
include_once $global['approot']."/mod/gps/handler_route.inc";
include_once $global['approot']."/mod/gps/handler_upload_waypoint.inc";
include_once $global['approot']."/mod/gps/handler_download_waypoint.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";

function shn_gps_mainmenu()
{
    global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen($conf['mod_gps_name']);
    shn_mod_menuitem("default",_("Home"),$module);
    shn_mod_menuitem("upload_seq",_("Upload Waypoints"),$module);
    shn_mod_menuitem("download_seq",_("Download Waypoints"),$module);
    shn_mod_menuitem("publish_seq",_("Publish Features"), $module);
    //shn_mod_menuitem("marker",_("Create new Waypoints to Download"),$module);
    shn_mod_menuitem("dynamic_download",_("Download Route"),$module);
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}

/**
 * Sequence of actions that leads to download of features.
 * 
 * sub functions can be found in:
 * - /inc/lib_gis/gis_fns.inc
 * - handler_download_waypoint.inc
 */
function shn_gps_download_seq()
{
    global $global;
    global $conf;
    if($conf['gis']){
        require_once $global['approot'] . "/inc/lib_gis/lib_gis_forms.inc";                    
        if(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                // Displays page showing features from existing searches.
                case '2_choose_features':
                    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
                    $keys = array('f_uuid'=>'1','f_class'=>'1','f_type'=>'1','f_projection'=>'1',
                        'f_coords'=>'1','f_module_item'=>'1','f_name'=>'1','f_description'=>'1',
                        'f_author'=>'1','f_url'=>'1','f_address'=>'1','f_event_date'=>'1','f_extended_data'=>'1');
                    // Add features from new search.
                    $new_features = shn_gis_get_features_other($keys, $_POST['l_uuid'], $_POST['c_uuid'], trim($_POST['f_author']), trim($_POST['f_event_date_from']), trim($_POST['f_event_date_to']), trim($_POST['f_name']));
                    // Add pre-searched features.
                    if(isset($_SESSION['gis']['feature_uuids'])){
                        $uuids = $_SESSION['gis']['feature_uuids'];
                        foreach($uuids as $uuid){
                            $keys2 = array('f_class'=>'0','f_type'=>'0','f_coords'=>'0','f_name'=>'0','f_description'=>'0','f_author'=>'0','f_event_date'=>'0');
                            $feature = shn_gis_get_features_uuid($uuid, $keys);
                            // set existing features to extended data to 'selected_' to set them already checked. 
                            $feature[0]['f_extended_data'] = 'selected_';
                            $new_features = array_merge($new_features, $feature);
                        }
                    }
                    // Display all featues.  TODO May want to have already selected features already selected...
                    shn_gps_form_feature_display_download($new_features, $keys);
                    break;
                // Displays fresh search, new search with previous search results saved, or download options
                case '3_save_and_options':
                    // Catch uuids
                    $uuids = array();
                    $limit = $_REQUEST['count'];
                    for($i = 1; $i <= $limit; $i++){
                        if(isset($_POST[$i])){
                            array_push($uuids, $_POST[$i]);
                        }
                    }
                    $_SESSION['gis']['feature_uuids'] = $uuids;
                    switch(trim($_POST['step3'])){
                        case "Search For More Features":
                            shn_gis_form_feature_search(false);
                            break;
                        case "Fresh Search":
                            shn_gis_form_feature_search();
                            break;
                        case "Continue To Download":
                            shn_gps_download_and_extra();
                            break;
                        default:
                            add_error(_t("Something went wrong"));
                            shn_gps_default();
                        break;
                    }
                    break;
                case '4_confirm':
                    $feed = false;
                    $delete = false;
                    if(isset($_POST['gis_publish'])){
                        $feed = $_POST['gis_feed_name'];
                        if('' == $feed){
                            add_warning(_t("Please enter a name for the feed"));
                            shn_gps_download_and_extra();
                            return;
                        }
                    }
                    if(isset($_POST['gis_delete'])){
                        $delete = true;
                    }
                    $uuids = $_SESSION['gis']['feature_uuids'];
                    shn_gps_download_confirm($feed, $delete, $uuids);
                    break;
                case '5_home':
                    shn_gps_default();
                    break;
                default:
                    add_error(_("Something went wrong"));
                    shn_gps_default();
                    break;
            }
        } else {
            // Displays search for features form
            $button_set = array('cancel' => true, 'back' => true, 'next' => true);
            $form_opts = array('seq' => '2_choose_features');
            shn_gis_form_feature_search($act = 'download_seq', $button_set, $form_opts);
        }
    } else {
        add_error(_t("GIS Disabled"));
    }
}

/**
 * Sequence of actions that leads to upload of features.
 * 
 * sub functions can be found in:
 * - /inc/lib_gis/gis_fns.inc
 * - handler_upload.inc
 * - handler_upload_waypoint.inc
 */
function shn_gps_upload_seq()
{
    global $global;
    global $conf;
    global $file;
    require_once('handler_upload.inc');
    if($conf['gis']){ 
        if(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                case '2_choose_features':
                    $file = $_FILES['load'];
                    //Print the error message if an error occurred with the Upload File
                    display_errors($return=false, $clean_errors=true, $exit=false);
                    //check whether a file was uploaded
                    if(isset($file) &&  _shn_sm_check_file_upload()){
                        // If all good start sorting points
                        shn_gps_feature_temp_save();
                        shn_gps_form_feature_display_upload();
                    } 
                    break;
                case '3_save_and_options':
                    $ids = array();
                    $limit = $_REQUEST['count'];
                    for($i = 1; $i <= $limit; $i++){
                        if(isset($_POST[$i])){
                            array_push($ids, $_POST[$i]);
                        }
                    }
                    $_SESSION['gis']['feature_ids_upload'] = $ids;
                    $_SESSION['gis']['feature_uuids_upload']  = shn_gps_save_points($ids);
                    shn_gps_upload_and_extra();
                    break;
                case '4_confirm':
                    $feed = false;
                    if(isset($_POST['gis_publish'])){
                        $feed = $_POST['gis_feed_name'];
                        if('' == $feed){
                            add_warning(_t("Please enter a name for the feed"));
                            shn_gps_upload_and_extra();
                        } else {
                            shn_gps_upload_confirm($feed, $_SESSION['gis']['feature_uuids_upload']);
                        } 
                    }
                    break;
                case '5_home':
                    shn_gps_default();
                    break;
                default:
                    add_error(_t("Something went wrong"));
                    shn_gps_default();
                    break;
            }
        } else {
            _shn_sm_form_upload();
        }
    } else{
        add_error(_t("GIS Disabled"));
    }
}

function shn_gps_publish_seq()
{
    if($conf['gis']){
        global $global;
        require_once $global['approot'] . "/inc/lib_gis/lib_gis_forms.inc";             
        if(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                // Displays page showing features from existing searches.
                case '2_choose_features':
                    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
                    $keys = array('f_uuid'=>'1','f_class'=>'1','f_type'=>'1','f_projection'=>'1',
                        'f_coords'=>'1','f_module_item'=>'1','f_name'=>'1','f_description'=>'1',
                        'f_author'=>'1','f_url'=>'1','f_address'=>'1','f_event_date'=>'1','f_extended_data'=>'1');
                    // Add features from new search.
                    $new_features = shn_gis_get_features_other($keys, $_POST['l_uuid'], $_POST['c_uuid'], trim($_POST['f_author']), trim($_POST['f_event_date_from']), trim($_POST['f_event_date_to']), trim($_POST['f_name']));
                    // Add pre-searched features.
                    if(isset($_SESSION['gis']['feature_uuids'])){
                        $uuids = $_SESSION['gis']['feature_uuids'];
                        foreach($uuids as $uuid){
                            $feature = shn_gis_get_features_uuid($uuid, $keys);
                            // set existing features to extended data to 'selected_' to set them already checked. 
                            $feature[0]['f_extended_data'] = 'selected_';
                            $new_features = array_merge($new_features, $feature);
                        }
                    }
                    // Display all featues.  TODO May want to have allready selected features allready selected...
                    shn_gps_form_feature_display_download($new_features, $keys);
                    break;
                // Displays fresh search, new search with previous search results saved, or download options
                case '3_save_and_options':
                    // Catch uuids
                    $uuids = array();
                    $limit = $_REQUEST['count'];
                    for($i = 1; $i <= $limit; $i++){
                        if(isset($_POST[$i])){
                            array_push($uuids, $_POST[$i]);
                        }
                    }
                    $_SESSION['gis']['feature_uuids'] = $uuids;
                    switch(trim($_POST['step3'])){
                        case "Search For More Features":
                            shn_gis_form_feature_search(false);
                            break;
                        case "Fresh Search":
                            shn_gis_form_feature_search();
                            break;
                        case "Continue To Download":
                            shn_gps_download_and_extra();
                            break;
                        default:
                            add_error(_t("Something went wrong"));
                            shn_gps_default();
                            break;
                    }
                    break;
                case '4_confirm':
                    $feed = false;
                    $delete = false;
                    if(isset($_POST['gis_publish'])){
                        $feed = $_POST['gis_feed_name'];
                        if('' == $feed){
                            add_warning(_t("Please enter a name for the feed"));
                            shn_gps_download_and_extra();
                            return;
                        }
                    }
                    if(isset($_POST['gis_delete'])){
                        $delete = true;
                    }
                    $uuids = $_SESSION['gis']['feature_uuids'];
                    shn_gps_download_confirm($feed, $delete, $uuids);
                    break;
                case '5_home':
                    shn_gps_default();
                    break;
                default:
                    add_error(_t("Something went wrong"));
                    shn_gps_default();
                    break;
            }
        } else{
            // Displays search for features form
            shn_gis_form_feature_search();
        }
    } else{
        add_error(_t("GIS Disabled"));
    }
}

function shn_gps_dynamic_download()
{
    shn_gps_display_routes();
}

function shn_gps_marker()
{
    if(isset($_REQUEST['seq'])){
        switch($_REQUEST['seq']){
            case 'map':
                if($_POST['marker_name']==""){
                    shn_marker_add_detail(true);
                } else {
                    shn_marker_add_map();
                }
                break;
            case 'img':
                if((shn_valid_x_coordinate($_POST['loc_x']))&&(shn_valid_y_coordinate($_POST['loc_y']))){
                    shn_marker_add_file();
                } else {
                    shn_marker_add_map(true);                           
                }
                break;
            case 'com':
                shn_marker_sort();
                break;
            case 'default':
                show_wiki_add_detail();
                break;
        }
    } else
        shn_marker_add_detail();
}

/*
 * Deprecated functions (GSoC 2008 rendered these 2007 functions redundant)
 */

//function shn_gps_waypoint()
//{
//    if(isset($_REQUEST['seq'])){
//        switch($_REQUEST['seq']){
//            case 'map':
//                shn_gps_display_points();
//                break;
//            case 'add':
//                shn_gps_sort_download();
//                break;
//        }
//    } else
//        shn_gps_find_waypoint();
//}

//function shn_gps_upload()
//{
//    include_once('handler_upload.inc');
//}

//function shn_gps_classify()
//{
//    shn_gps_save_points();
//}

//function shn_gps_classifyxxxx()
//{	
//    if(isset($_REQUEST['seq'])) {
//        if(($_REQUEST['seq'])=='map')
//            shn_gps_save_points();
//        else
//            shn_gps_upload();
//    } else
//        shn_gps_point_sort();
//}

//function shn_gps_sort_download()
//{
//    switch(trim($_POST['button1'])){
//        case "New Search":
//            shn_gps_find_waypoint();
//            break;	
//        case "Download Markers":/
//            shn_gps_add_creator();
//            break;
//        default:
//            break;
//    }
//}


