<?php
/**
 *Sahana Admin & ACL section
 *PHP version 4 and 5
 *LICENSE: This source file is subject to LGPL license that is available through
 *the world-wide-web at the following URI: http://www.gnu.org/copyleft/lesser.
 *html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Ravindra <ravindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */

require_once $global['approot']."/inc/lib_menu.inc";

function _shn_admin_mainmenu()
{
    global $global;
    global $conf;
    $module_list = shn_get_modules_with_admin();
    shn_mod_menuopen(shn_get_module_name());
    shn_sub_mod_menuitem("default", _t("Admin Home"), 'admin');
    shn_sub_mod_menuitem("module_mgr",_t("Module Manager"),'admin');
    shn_sub_mod_menuopen(_t("Location Hierarchy"));
    shn_sub_mod_menuitem("loc_lvl", _t("Location Terminology"), 'admin');
    shn_sub_mod_menuitem("add_loc", _t("Add New Location"), 'admin');
    shn_sub_mod_menuitem("view_loc", _t("Modify Location"), 'admin');
    shn_sub_mod_menuitem("loc_range", _t("Location Range"), 'admin');
    shn_sub_mod_menuitem("loc_start", _t("Default Location"), 'admin');
    // shn_sub_mod_menuitem("loc_range", _t("Set Location Range"), $module);
    // shn_sub_mod_menuitem("start_loc", _t("Set Starting Location"), $module);
    shn_sub_mod_menuclose();

    //GIS Admin menu inclusion:
    //@edit: Mifan Careem <mifan@respere.com>
    include_once $global['approot'].'/inc/lib_gis/admin_menu.inc';
    
    //Messaging Admin menu inclusion:
    //@edit: Mifan Careem <mifan@respere.com>
    _shn_admin_msg_menu();

    // added by gmiernicki ~ menu item for snapshot module
    _shn_admin_snap_menu();

    shn_sub_mod_menuopen(_t("Module Configuration"));
    foreach($module_list as $i) {
        shn_sub_mod_menuitem("adm_default", $conf['mod_'.$i.'_name'], $i);
    }
    shn_sub_mod_menuclose();

    //shn_sub_mod_menuopen(_t("Module Management Console"));
    //include $global['approot']."/mod/admin/mmc_menus.inc";
    //shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_t("System Security"));

    if ($conf['acl_enabled']) {
	    shn_sub_mod_menuitem("acl_user_roles", _t("User Management"), 'admin');
	    shn_sub_mod_menuitem("acl_enable_mods", _t("Module Access Control"), 'admin');
            shn_sub_mod_menuitem("acl_privacy", _t("Data Classification"), 'admin');
            shn_sub_mod_menuitem("acl_enable_signup", _t("Self Signup"), 'admin');
	    shn_sub_mod_menuitem("acl_event_log", _t("Event Log"), 'admin');
	    shn_sub_mod_menuitem("acl_enable_locking", _t("User Locking"), 'admin');
	    shn_sub_mod_menuitem("acl_enable_acl", _t("Disable Security"), 'admin');
    } else {
		shn_sub_mod_menuitem("acl_enable_acl", _t("Enable Security"), 'admin');
    }

    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_t("Language / Locale"));
    shn_sub_mod_menuitem("lc_set", _t("Default Language"), 'admin');
    shn_sub_mod_menuitem("lc_add_new_lang", _t("Add/Remove Language"), 'admin');
    shn_sub_mod_menuitem("lc_trns", _t("Language Translation"), 'admin');
    shn_sub_mod_menuitem("lc_db", _t("Database Translation"), 'admin');
    shn_sub_mod_menuitem("lc_ui_trns", _t("Interactive Translation"), 'admin');
    shn_sub_mod_menuitem("lc_ui_trns_update", _t("Update Translation"), 'admin');
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_t("Disaster Levels"));
    shn_sub_mod_menuitem("ims_level1",_t('Registered ')._lc($conf['mod_admin_ims_level1']), 'admin');
    shn_sub_mod_menuitem("ims_level2",_t('Registered ')._lc($conf['mod_admin_ims_level2']), 'admin');
    shn_sub_mod_menuitem("ims_level3",_t('Registered ')._lc($conf['mod_admin_ims_level3']), 'admin');
    shn_sub_mod_menuitem("ims_config",_t('Levels Terminology'), 'admin');
    //include $global['approot']."/mod/admin/ims_menus.inc";
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_t("Config Utils"));
    shn_sub_mod_menuitem("conf_list", _t("Config Values"), 'admin');
    shn_sub_mod_menuitem("check_sec_policies", _t("Check Security Policy validity"), 'admin');
    shn_mod_menuitem("field_option_config", _t("Edit Field Options"), 'admin');
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


function _shn_admin_acl_user_roles_menu($user_home=false)
{
	shn_tabmenu_open();
	shn_tabmenu_item("add_user", _t("Add Users"), "admin");
	shn_tabmenu_item("del_user", _t("Remove Users"), "admin");
	shn_tabmenu_item("acl_user_edit_roles", _t("Edit Roles of a User"), "admin");
	shn_tabmenu_item("reset_pwd", _t("Reset Password of a User"), "admin");
	shn_tabmenu_item("acl_change_user_status", _t("Change User Status"), 'admin');
  //  shn_tabmenu_item("acl_unlock_user", _t("Unlock User"), 'admin');
	shn_tabmenu_close();
	if($user_home){
?>

	<br>
	<div id="home">
	<h2><?php echo _t('Welcome to Users section'); ?></h2>
	<h3><?php echo _t("As Administrator, use this section for the following")?></h3>
	<ul>
    <li><?php echo _t('Add Users')?></li>
    <li><?php echo _t('Remove Users')?></li>
    <li><?php echo _t('Change User Roles')?></li>
    <li><?php echo _t('Change User Status')?></li>
    <li><?php echo _t('Unlock Users')?></li>
	</ul>
	</div>
<?php
	}
}

function _shn_admin_acl_privacy_menu($privacy_home=false)
{
    shn_tabmenu_open();
    //shn_tabmenu_item("acl_data_classifications", _t("Data Classifications"), 'admin');
    shn_tabmenu_item("acl_data_privacy", _t("Data Classifications & Role Permissions"), 'admin');
    shn_tabmenu_item("acl_data_classifications_tables", _t("Data Classifications & System Data "), 'admin');
    shn_tabmenu_close();
    if($privacy_home==true){
 ?>

	<br>
	<div id="home">
	<h2><?php echo  _t('Welcome to Privacy section'); ?></h2>
    <p><strong><?php echo _t('You can set Privacy settings for Data and Roles')?></strong></p>
	<ul>
    <li><?php echo _t("If you need to modify which roles have permissions to create/read/modify which data, click on the <strong>'Data Classifications & Role Permissions'</strong> tab on the top of the page.") ?></li>
    <li><?php echo _t("If you need to modify data sensitivity classifications of the data in the system, click on the <strong>'Data Classifications & System Data'</strong> tab on the top of the page.") ?></li>
	</ul>
	</div>
<?php
	}
}

function _shn_admin_acl_user_menu()
{
	_shn_admin_acl_user_roles_menu();
}

function _shn_admin_acl_role_menu($module=null)
{
?>
	<div id="submenu_v">
	<a href="index.php?mod=admin&amp;act=add_role"><?php echo _t("Add Role")?></a>
	<a href="index.php?mod=admin&amp;act=del_role"><?php echo _t("Remove Role")?></a>
	<a href="index.php?mod=admin&amp;act=acl_role_perms"><?php echo _t("Existing Role Permissions")?></a>
	<a href="index.php?mod=admin&amp;act=acl_role_edit_perms"><?php echo _t("Modify Role Permissions")?></a>
	</div>
	<br>
<?php


}
/**
 * Messaging/Alerting admin section
 * The admin section is moved outwards since it is a library/framework component
 * And it requires multiple menu items so not intended as a module-only admin
 * However, doing a module check here since it can be optional
 * @author      Mifan Careem <mifan@respere.com>
 */
 function _shn_admin_msg_menu(){
        global $global;
        include_once $global['approot']."/inc/lib_modules.inc";

	if(shn_module_exists('msg')){
		include_once $global['approot']."/mod/msg/adm_menu.inc";
		shn_msg_admin_menu();
	}
}


/**
 * Snapshot admin section
 * code stolen from function above, same deal here :)
 * @author	Greg Miernicki <miernickig@mail.nih.gov>
 */
function _shn_admin_snap_menu() {
	global $global;
	include_once $global['approot']."/inc/lib_modules.inc";

	if(shn_module_exists('snap')){
		include_once $global['approot']."/mod/snap/admin_menu.inc";
		shn_snap_admin_menu();
	}
}
