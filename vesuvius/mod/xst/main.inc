<?
/**
 * @name         Extensible Streaming
 * @version      1.0
 * @package      xst
 * @author       Ishan Liyanage <ishanul@gmail.com>
 * @author       Richard Smith <s0459387@sms.ed.ac.uk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


/**
 * Place all your dependant libraries below. Given are some typical ones
 * required for the module
 */
include_once "handler_gis.inc";
include_once "handler_location.inc";
include_once "handler_catalog.inc";
include_once "handler_ims.inc";

function shn_text_xst_get_loc() {
	shn_location_get_loc();
}



function shn_text_xst_get_loc_val() {
	_shn_get_locations();
}



function shn_text_xst_sub_cat() {
	shn_text_catalog_sub_cat();
}



function shn_text_xst_unit_cat() {
	shn_text_catalog_unit_cat();
}



function shn_text_xst_help() {
	if(empty($_GET['help_id'])) {

		echo "var help_arr = new Array(".count(isset($_SESSION['form_help']) ? $_SESSION['form_help'] : null).");\n";
		if(isset($_SESSION['form_help']))
		foreach($_SESSION['form_help'] as $help_id => $value){
			$clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
			echo "help_arr[".$help_id."] = \"$clean_value\";\n";
		}
	} else {
		echo $_SESSION['form_help'][$_GET['help_id']];
	}
}



function shn_text_xst_victims() {
	_shn_get_victims();
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

