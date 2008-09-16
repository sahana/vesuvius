<?php

/**
* Sahana GIS admin menu functionality
* Keeping separate from the main admin file to avoid tampering 
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library		GIS
* @version		$Id: admin_acts.inc,v 1.24 2008-09-16 20:36:02 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

// Menu Actions
/**
 * Main GIS admin functionality
 */
function shn_admin_gis_main()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_main_settings();
}

/**
* GIS Feature Class functionality
*/
function shn_admin_gis_database_classes()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_feature_class.inc';
    shn_gis_internal_class_general_select();
}

function shn_admin_gis_database_classes_add()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_feature_class.inc';
    shn_gis_internal_class_add_seq();
}

function shn_admin_gis_database_classes_edit()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_feature_class.inc';
    shn_gis_internal_class_edit_seq();
}

function shn_admin_gis_database_classes_remove()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_feature_class.inc';
    shn_gis_internal_class_remove_seq();
}

/**
* GIS Internal Database Layer Functionality
*/
function shn_admin_gis_database_layers()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_internal_layer.inc';
    shn_gis_internal_layer_general_select();
}

function shn_admin_gis_database_layer_add()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_internal_layer.inc';
   shn_gis_internal_layer_add_seq(); 
}

function shn_admin_gis_database_layer_edit()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_internal_layer.inc';
    shn_gis_internal_layer_edit_seq(); 
}

function shn_admin_gis_database_layer_remove()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_internal_layer.inc';
    shn_gis_internal_layer_remove_seq(); 
}

/**
  * GIS Files Management Functionality
  */
function shn_admin_gis_files()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_files.inc';
    shn_gis_internal_class_general_select();
}

function shn_admin_gis_file_download()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_files.inc';
    shn_gis_file_download_seq();
}

function shn_admin_gis_file_upload()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_files.inc';
   shn_gis_file_upload_seq();

}

function shn_admin_gis_file_upload2()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_files.inc';
    shn_gis_file_upload_seq();

}

function shn_text_admin_gis_create_file()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_files.inc';
    shn_text_admin_gis_create_file2();   
}

/**
 * GIS Feeds Management Functionality
 */
function shn_admin_gis_feeds()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_feeds.inc';
    shn_gis_feed_general_select();
}

function shn_admin_gis_feed_general()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_feeds.inc';
    shn_gis_feed_general_seq();
}

function shn_admin_gis_feed_feature_class()
{
    global $global;
    include_once $global['approot'] . '/inc/lib_gis/admin_feeds.inc';
    shn_gis_feed_feature_class_seq();
}

/**
 * Google Maps plugin admin functionality
 */
function shn_admin_gis_google()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_google_settings();
}

/**
 * GIS Layers Management Functionality
 */
function shn_admin_gis_layers()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/layer.inc';
    _shn_gis_layer_main_form();
}
 
/**
 * GIS Markers Management Functionality
 */
function shn_admin_gis_markers()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/select_markers.inc';
    _shn_admin_gis_markers_form();
    include_once $global['approot'].'/inc/lib_gis/upload_markers.inc';
    _shn_gis_upload_markers();
    include_once $global['approot'].'/inc/lib_gis/list_markers.inc';
    _shn_gis_list_markers();
}

/**
 * GIS Projections Management Functionality
 */
function shn_admin_gis_projections()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/select_projection.inc';
    _shn_admin_gis_projection_form();
    include_once $global['approot'].'/inc/lib_gis/upload_defs.inc';
}
 
//Form Actions -----------------------

function shn_admin_gis_main_defaults()
{
    global $global;
    global $conf;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_commit_main();
    // Update conf from DB  so that view is refreshed
    shn_config_database_fetch(&$conf,'admin');
    shn_admin_gis_main_settings();
}

function shn_admin_gis_google_commit()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_commit_google();
    add_confirmation(_t("Changes were saved"));
    shn_admin_gis_google_settings();
}

function shn_admin_gis_layers_commit()
{
    global $global;
    global $conf;
    include_once $global['approot'].'/inc/lib_gis/layer.inc';
    _shn_admin_gis_commit_layers();
    add_confirmation(_t("Changes were saved"));
    // Update conf from DB  so that view is refreshed
    shn_config_database_fetch(&$conf,'admin');
    _shn_gis_layer_main_form();
}

function shn_admin_gis_markers_commit()
{
    global $global;
    global $conf;
    include_once $global['approot'].'/inc/lib_gis/select_markers.inc';
    _shn_admin_gis_commit_markers();
    add_confirmation(_t("Changes were saved"));
    // Update conf from DB  so that view is refreshed
    shn_config_database_fetch(&$conf,'admin');
    _shn_admin_gis_markers_form();
    include_once $global['approot'].'/inc/lib_gis/upload_markers.inc';
    _shn_gis_upload_markers();
    include_once $global['approot'].'/inc/lib_gis/list_markers.inc';
    _shn_gis_list_markers();
}
 
function shn_admin_gis_marker_folders_commit()
{
    global $global;
    global $conf;
    include_once $global['approot'].'/inc/lib_gis/upload_markers.inc';
    _shn_gis_create_markers_folder();
    if (false==is_errors()){
        add_confirmation(_t("Folder was created"));
    }
    // Update conf from DB  so that view is refreshed
    shn_config_database_fetch(&$conf,'admin');
    include_once $global['approot'].'/inc/lib_gis/select_markers.inc';
    _shn_admin_gis_markers_form();
    _shn_gis_upload_markers();
    include_once $global['approot'].'/inc/lib_gis/list_markers.inc';
    _shn_gis_list_markers();
}

function shn_admin_gis_projection_commit()
{
    global $global;
    global $conf;
    include_once $global['approot'].'/inc/lib_gis/select_projection.inc';
    _shn_admin_gis_commit_projection();
    add_confirmation(_t("Changes were saved"));
    // Update conf from DB  so that view is refreshed
    shn_config_database_fetch(&$conf,'admin');
    _shn_admin_gis_projection_form();
    include_once $global['approot'].'/inc/lib_gis/upload_defs.inc';
}
 
//Deprecated---------------------------------
 
/**
 * GIS plugin admin functionality
 * Deprecated
 */
function shn_admin_gis_plugin()
{
	global $global;
	include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
	shn_admin_gis_plugin_controller();
}

/*
 * Deprecated
 */ 
 function shn_admin_gis_plugin_default()
 {
 	global $global;
	include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
 	shn_admin_gis_plugin_default_commit();
 	add_confirmation(_t("Changes were saved"));
 	shn_admin_gis_plugin_controller();
 }
 
 function shn_admin_gis_layer_wms_add_tab()
 {
 	global $global;
	include_once $global['approot'].'/inc/lib_gis/wms_fns.inc';
	_shn_gis_mng_wms_form();
	_shn_gis_wms_add_tab();
	
 }
 
 function shn_admin_gis_layer_wms_list_tab()
 {
 	global $global;
	include_once $global['approot'].'/inc/lib_gis/wms_fns.inc';
	_shn_gis_mng_wms_form();
 }
 
 function shn_admin_gis_layer_wms_edit_tab()
 {
 	global $global;
	include_once $global['approot'].'/inc/lib_gis/wms_fns.inc';
	_shn_gis_mng_wms_form();
 }

?>

