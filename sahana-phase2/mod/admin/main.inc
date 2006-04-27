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

// Incident Management Module
include_once $global['approot']."mod/admin/ims_main.inc";

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
{ ?>
    <div id="home">
    <h2><?=_("Sahana System Administration")?></h2>
        <p><?=_("The System Adminisitration section allows you to configure and customize Sahana based on your requirements")?></p>
	<ul>
	<li><b><?=_("System Config")?></b> <br/><?=_("Contains all the configuration sections that apply across the Sahana application such as localization to location")?></li>
	<li><b><?=_("Module Config")?></b> <br/><?=_("Contains specific configuration pages for each module that has been installed in the system allowing them to be customized individually and seperately.")?> </li>
	<li><b><?=_("Security Config")?></b> <br/><?=_("Allows the system administrator to configure who gets access to what modules and to what degree to high degree of granularity if required.")?></li>
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


function shn_admin_acl_default()
{
    _shn_admin_acl_default();
}

function shn_admin_acl_system()
{
    _shn_admin_acl_system();
}
function shn_admin_acl_module()
{
    _shn_admin_acl_module();
}
function shn_admin_acl_module_cr()
{
    _shn_admin_acl_module_cr();
}
function shn_admin_acl_install()
{
    _shn_admin_acl_install();
}
function shn_admin_acl_mod_install()
{
    _shn_admin_acl_mod_install();
}
function shn_admin_acl_state()
{
    _shn_admin_acl_state();
}

/************************************/
function shn_admin_add_loc()
{
    shn_admin_location_form();
}

function shn_admin_add_loc_cr()
{
    shn_location_add();
    shn_admin_location_form();
}

function shn_admin_view_loc()
{
    shn_admin_location_view_form();
}

function shn_admin_view_loc_cr()
{
	if (isset($_POST{"chk_start"})){
        $loc=0;
    }else {
        $level=$_POST{"opt_location_type"};
        $loc=$_POST{$level};
    }
	shn_admin_location_edit_form($loc);
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
            shn_admin_location_view_form();
            break;
        case "del":
            shn_location_del($loc);
            shn_admin_location_view_form();
            break;
        default:
             shn_admin_location_view_form();
            break;
    }

}

/************************************/
function shn_admin_acl_action_group()
{
    _shn_admin_acl_action_group();
}

function shn_admin_acl_action_group_cr()
{
    _shn_admin_acl_action_group_cr();
}

function shn_admin_acl_action()
{
    _shn_admin_acl_action();
}

function shn_admin_acl_action_cr()
{
    _shn_admin_acl_action_cr();
}

/************************************/
function shn_admin_acl_existing_perms_tab()
{
    _shn_admin_acl_existing_perms_tab();
}

function shn_admin_acl_user_cr()
{
    _shn_admin_acl_user_cr();
}

function shn_admin_acl_user()
{
    _shn_admin_acl_user();
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

/**************************************/
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

/******************************************/

function shn_admin_add_user($error=false)
{
    _shn_admin_acl_user_menu($module);
    shn_auth_form_user_add($error);
}

function shn_admin_add_user_cr()
{
    _shn_admin_add_user_cr();
}

function shn_admin_del_user($error=false)
{
    _shn_admin_acl_user_menu($module);
    shn_auth_form_user_del();
}

function shn_admin_del_user_cr()
{
    _shn_admin_del_user_cr();
}

function shn_admin_ch_pwd($error=false)
{
    _shn_admin_acl_user_menu($module);
    shn_auth_form_ch_pwd($error);
}

function shn_admin_ch_pwd_cr()
{
    _shn_admin_ch_pwd_cr();
}

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
?>
