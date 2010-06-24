<?php
/**
 * This is the main file for the Sahana module. Once the module is selected in the
 * post all actions are passed to this file for processing.
 * <Description of file>
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Ishan Liyanage <ishanul@gmail.com>
 * @author     Richard Smith <s0459387@sms.ed.ac.uk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage xst (Extensible Streaming)
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Place all your dependant libraries below. Given are some typical ones
 * required for the module
 */
include_once "handler_gis.inc";
include_once "handler_location.inc";
include_once "handler_catalog.inc";
include_once "handler_ims.inc";
include_once ($global['approot']."inc/user_feedback.inc");

function shn_text_xst_get_loc(){
	shn_location_get_loc();
}
function shn_text_xst_get_loc_val(){
	_shn_get_locations();
}
function shn_text_xst_sub_cat(){
	shn_text_catalog_sub_cat();
}
function shn_text_xst_unit_cat(){
	shn_text_catalog_unit_cat();
}
function shn_text_xst_help()
{
	if(empty($_GET['help_id'])){
		echo "var help_arr = new Array(".count($_SESSION['form_help']).");\n";
		if(isset($_SESSION['form_help']))
		foreach($_SESSION['form_help'] as $help_id => $value){
			$clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
			echo "help_arr[".$help_id."] = \"$clean_value\";\n";
		}
	}else{
		echo $_SESSION['form_help'][$_GET['help_id']];
	}
}

function shn_text_xst_victims(){
	_shn_get_victims();
}

function shn_text_xst_user_feedback(){
	global $global,$conf;
	require_once($global['approot']."/3rd/xajax/xajax.inc.php");
	require_once($global['approot'].'/3rd/xajax/xajaxResponse.inc.php');

	$xajax = new xajax($conf['base_url'].'index.php?mod=xst&act=user_feedback&stream=text');//$conf['base_url'].'index.php?mod=admin&act=conf_list'
	$xajax->registerFunction("_shn_send_feedback");
	$xajax->registerFunction("_shn_search_answer");
	$xajax->registerFunction("_shn_dont_show_fbform");
	$xajax->processRequests();
	
}

//This is a small hack
function shn_xst_help(){
	global $global;
	include_once ($global['approot']."mod/home/main.inc");
	shn_home_default();
	
}

function shn_xst_online_cam_upload_img(){
	global $global;  
    if($_SESSION['online_cam']['seckey']==$_POST['seckey']){    	
    	$target = $global['approot']."www/tmp/online_cam_".$_SESSION['online_cam']['image_id'].".png";
        move_uploaded_file($_FILES['Filedata']['tmp_name'],$target);
        chmod($target,0444);
    }else{
        //shn_log_event(null,"upload_img","Image upload attempt without security key in the session.","An attempt was made to upload an image without a valid security key in the sesion.");
    }
}

/**
 * Dummy function for ajax calls
 */
function shn_ajax_xst_xajax(){

}

/**
 * Call for GIS feature search form
 */
function shn_text_xst_gis_search_layer()
{
    _shn_gis_form_select_layer_callback();
}
/**
 * Calls for GIS popups
 */
function shn_text_xst_gis_popup_refresh()
{
    _shn_gis_form_gis_popup_refresh_callback();
}
function shn_text_xst_gis_popup_new_ok()
{
    _shn_gis_form_gis_popup_new_callback();
}
function shn_text_xst_gis_popup_edit_position()
{
    _shn_gis_form_gis_popup_edit_position_callback();
}
function shn_text_xst_gis_popup_edit_details()
{
    _shn_gis_form_gis_popup_edit_callback();
}
function shn_text_xst_gis_popup_edit_details_ok()
{
    _shn_gis_form_gis_popup_edit_ok_callback();
}
function shn_text_xst_gis_popup_delete()
{
    _shn_gis_form_gis_popup_delete_callback();
}

