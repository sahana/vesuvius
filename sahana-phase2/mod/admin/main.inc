<?PHP
/**
*
* Sahana Admin & ACL section
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @author     Chamindra <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;

include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once "menu.inc";
include_once "acl.inc";
include_once "location.inc";
include_once $global['approot']."inc/lib_security/auth_form.inc";
include_once $global['approot']."inc/lib_security/lib_auth.inc";
// Incident Management Module
include_once $global['approot']."mod/admin/ims_main.inc";
include_once $global['approot']."mod/admin/conf_admin.inc";

// Module Management Console
include_once $global['approot']."mod/admin/mmc_main.inc";

// GIS Management Console
// @todo: move as library
//include_once $global['approot']."mod/gis/gis_admin.inc";


function shn_admin_mainmenu()
{
    _shn_admin_mainmenu() ;
}

function shn_admin_view()
{
    global $global;
?>

        <p><b><?=_("You called the admin view")?> </b></p>
        <p><?=_(" on module") ?> </p>
<?php

}

function shn_admin_default()
{ 
    global $global;
    $db = $global['db'];

    $result = $db->Execute("select * from incident");
    $isDisasterNamed = ($result->RecordCount() > 0);

    $result = $db->Execute("select * from location");
    $isLocationsEntered = ($result->RecordCount() > 0);

    $result = $db->Execute("select * from gacl_acl");
    $isSecurityInstalled = ($result->RecordCount() > 0);

    $result = $db->Execute("select * from ct_catalogue");
    $isCatalogCreated = ($result->RecordCount() > 0);

    $result = $db->Execute("select value from config where module_id='gis'
                                 and confkey='mod_gis_google_key'");
    $isGoogleSetup = ($result->fields['value']  != "");

    echo '<div id="home">';
  
    if (!$isLocationsEntered || !$isGoogleSetup || !$isCatalogCreated 
        || !$isSecurityInstalled || !$isDisasterNamed) {
        echo '<h2>'._('Finalize Your Sahana Installation')."</h2>\n";
        echo _("<p>There are still a few steps to be performed before you 
                can start using your Sahana installation effectively. 
                These items are given in priority order below:</p>")."\n";
    }
    echo "<ol>\n";
    if (!$isDisasterNamed) {
        echo '<li>'._('<b>Add Disaster Name</b> - As this system can handle 
                multiple disasters in the same system you need to 
                first add the name of the first disaster you are using 
                Sahana for. To do this in the navigation bar click on '). 
                '&#34;'._('Multiple Incidents').'&#34;'.
                _(' followed by ').'<a href="?mod=admin&act=ims_level1">'
                .'&#34;'._('Manage Disaster').'&#34;'.'</a> '.
        		_('and add the disaster name.').'</li><br/>'; 
    }
       
    if (!$isLocationsEntered) {
        echo '<li>'._('<b>Add Locations</b> - Please enter some of the 
                regions affected in the disaster by clicking the 
                navigation bar on ').
                '&#34;'._('Locations').'&#34;'.
                _(' followed by ').'<a href="?mod=admin&act=add_loc">'.
                '&#34;'._('Add Location').'&#34;'.'</a></li><br/>'; 
    }
    if (!$isCatalogCreated) {
        echo '<li>'._('<b>Create the Aid Catalog</b> - The catalog 
                of aid items has to be defined to use 
                the Pledge/Request Management System and Inventory Management,
                you need to define the type of aid items available. To do this 
                click on the').'<a href="?mod=cs&act=default">'.
                '&#34;'._('Catalog System').'&#34;'.'</a> '._('in the navigation bar and start adding 
                aid items for the disaster').'</li><br/>'; 
    }
   if (!$isGoogleSetup) {
        echo '<li>'._('<b>Setup Google Maps</b> - To get mapping to 
                work you need to enter a Google Map key in the ') 
                .'&#34;'._('Module Config').'&#34;'.'->' .
                		'<a href="?mod=gis&act=admin&submod=google_maps">'.
                '&#34;'._('GIS Mapping').'&#34; '.'</a>'._('section').'</li><br/>'; 
    }
    
    if (!$isSecurityInstalled) {
        echo '<li>'._('<b>Configure Security (optional)</b> - To prevent 
                unauthorized access to the system configure security by
                 clicking ').
                 '&#34;'._('Security Config').'&#34; '._('and then selecting ').  
                '<a href="?mod=admin&act=acl_user_roles">'.
                '&#34;'._('System &amp User').'&#34;'.'</a>'.'</li><br/>';
    }


    echo "</ol>\n";
?>
    <h2><?=_("Sahana System Administration")?></h2>
        <p><?=_("The System Adminisitration section allows you to configure and customize Sahana based on your requirements. Each section on the Administration menu is grouped by the section. These sections are described below:")?></p>
	<ul>
	<li><b><?=_("Disaster Incidents")?></b> <br/><?=_("Define multiple disasters, sub incidents and events that this instance of Sahana will handle")?></li>
	<li><b><?=_("Locations")?></b> <br/><?=_("Add, modify and customized the affected locations and hierachies in the disaster")?></li>
	<li><b><?=_("GIS Config")?></b> <br/><?=_("Specify your mapping configuration and prefered mapping/GIS system to be used in Sahana")?></li>
	<li><b><?=_("Localization")?></b> <br/><?=_("Translate the Sahana interface and terminology to a local language and that relevant for the disaster")?></li>
	<li><b><?=_("Module Config")?></b> <br/><?=_("Contains specific configuration pages for each module that has been installed in the system allowing them to be customized individually and seperately.")?> </li>
	<li><b><?=_("Security Config")?></b> <br/><?=_("Allows the system administrator to configure who gets access to what modules and actions available in Sahana")?></li>
	<li><b><?=_("Config Value")?></b> <br/><?=_("This section give you access to all the raw configuration values that can be changed in the system")?></li>
	</ul>
    </div>

<?php
}

function shn_admin_modadmin()
{
    global $global;

    // include original module admin section
    include $global['approot']."/mod/".$global['module']."/admin.inc";

    // compose and call the relevant module function
    $module_function = "shn_".$global['module']."_".$global['action'];
    
    if (!function_exists($module_function)) {
        $module_function="shn_".$global['module']."_adm_default";
    } 

    // @TODO remove. call the admin menu shn_<mod>_adminmenu if it exists
    /*$admin_menu = "shn_".$global['module']."_adminmenu";

    if(function_exists($admin_menu))
        $admin_menu();    */

    $module_function();
}


/******************************************/

function shn_admin_add_user($error=false)
{
    _shn_admin_acl_user_menu($module);
    shn_auth_form_user_add($error);
}

function shn_admin_add_user_cr()
{
   include_once "errors.inc";
    shn_auth_add_user_cr();
 
    _shn_admin_acl_user_menu();
   
}

function shn_admin_del_user($error=false)
{
    _shn_admin_acl_user_menu($module);
    shn_auth_form_user_del();
}

function shn_admin_del_user_cr()
{
    _shn_auth_del_user_cr();
    _shn_admin_acl_user_menu();
}

function shn_admin_ch_pwd($error=false)
{
    _shn_admin_acl_user_menu($module);
    shn_auth_form_ch_pwd($error);
}

function shn_admin_ch_pwd_cr()
{
   include_once "errors.inc";
   $error=_shn_admin_ch_pwd_cr();
   ?><div id="result_msg"><?
   if($error){
   	   $msg="An error ocurred";
   }else{ 
   		$msg="The Password was succesfully updated ";
   }
   
    echo $msg;
    if($error)
    		display_errors();
    ?>
   </div><?
   _shn_admin_acl_system_menu();
}




function shn_admin_acl_user_roles()
{
    _shn_admin_acl_user_roles();
}

function shn_admin_acl_state()
{
    _shn_admin_acl_state();
}



/************************************/
function shn_admin_add_loc()
{
    _shn_admin_location_form();
}

function shn_admin_add_loc_cr()
{
    shn_location_add();
    _shn_admin_location_form();
}

function shn_admin_view_loc()
{
    _shn_admin_location_view_form();
}

function shn_admin_view_loc_cr()
{
	if (isset($_POST{"chk_start"})){
        $loc=0;
    }else {
        $level=$_POST{"opt_location_type"};
        $loc=$_POST{$level};
    }
	_shn_admin_location_edit_form($loc);
}

function shn_admin_edit_loc_cr()
{
	$act=$_POST{"action"};
	$loc=$_POST{"loc_id"};
	switch ($act) {
        case "edit":
        		$loc=array();
        		$loc["loc"]=$_POST{"loc_id"};
        		$loc["name"]=$_POST{"loc_name"};
        		$loc["desc"]=$_POST{"desc"};
        		$loc["iso"]=$_POST{"iso"};
        		
        		shn_location_edit($loc);
            _shn_admin_location_view_form();
            break;
        case "del":
            shn_location_del($loc);
            _shn_admin_location_view_form();
            break;
        default:
             _shn_admin_location_view_form();
            break;
    }

}

function shn_admin_loc_range(){
	 _shn_admin_location_range_form();
}

function shn_admin_loc_range_cr(){
	_shn_admin_loc_range_cr();
}


function shn_admin_loc_start(){
	_shn_admin_location_start_form();
}

function shn_admin_loc_start_cr(){
	_shn_admin_loc_start_cr();
}

function shn_admin_loc_lvl(){
	_shn_admin_levels_form();
}
function shn_admin_loc_lvl_cr(){
	_shn_adm_loc_lvl_cr();
}
function shn_admin_start_loc()
{
    _shn_admin_location_view_form();
}


/************************************/
function shn_admin_acl_user()
{
    _shn_admin_acl_user();
}
function shn_admin_acl_user_edit_roles($error=false)
{
    _shn_admin_acl_user_edit_roles();
}
function shn_admin_acl_user_edit_roles_cr($error=false)
{
    _shn_admin_acl_user_edit_roles_cr();
}

function shn_admin_acl_data_privacy(){
	_shn_admin_acl_data_privacy();
}
function shn_admin_acl_role_edit_perms(){
	
	_shn_admin_acl_role_edit_perms();
}

function  shn_admin_acl_role_edit_perms_cr(){
	_shn_admin_acl_role_edit_perms_cr();
}
/*
function shn_admin_acl_existing_perms_tab()
{
    _shn_admin_acl_existing_perms_tab();
}

function shn_admin_acl_user_cr()
{
    _shn_admin_acl_user_cr();
}



function shn_admin_acl_user_perms()
{
    _shn_admin_acl_user_perms();
}

function shn_admin_acl_user_add_roles($module=NULL,$error=false)
{
    _shn_admin_acl_user_add_roles();
}

function shn_admin_acl_user_add_roles_cr($module=NULL,$error=false)
{
    _shn_admin_acl_user_add_roles_cr();
}

function shn_admin_acl_user_edit_roles($error=false)
{
    _shn_admin_acl_user_edit_roles();
}

function shn_admin_acl_user_edit_roles_cr($error=false)
{
    _shn_admin_acl_user_edit_roles_cr();
}
*/

/**************************************/
/*
function shn_admin_acl_role_perms()
{
    _shn_admin_acl_role_perms();
}

function shn_admin_acl_role_edit_perms()
{
    _shn_admin_acl_role_edit_perms();
}

function shn_admin_acl_role_edit_perms_cr()
{
    $module=$_GET{"sel"};
    _shn_admin_acl_role_edit_perms_cr($module);
}

function shn_admin_acl_role()
{
    _shn_admin_acl_role();
}

function shn_admin_acl_role_cr()
{
    _shn_admin_acl_role_cr();
}
*/

/***
 * Localization interface for language translation
 */
function shn_admin_lc_trns()
{
    require_once('lc_translate.inc');
}

function shn_admin_lc_set()
{
    require_once('lc_setlocale.inc');
}

function shn_admin_lc_db()
{
    require_once('lc_db.inc');
}

// GIS admin page from gis module/lib
function shn_admin_gis_form()
{
	global $global;
	global $conf;
	require_once($global['approot'].'/mod/admin/gis_admin.inc');
	shn_gis_adm_default();
}

function shn_admin_gis_commit()
{
	global $global;
	global $conf;
	require_once($global['approot'].'/mod/admin/gis_admin.inc');
	shn_gis_adm_commit();
}
?>
