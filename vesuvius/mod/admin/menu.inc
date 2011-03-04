<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Ravindra De Silva
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */



require_once $global['approot']."/inc/lib_menu.inc";

function _shn_admin_mainmenu() {
	global $global;
	global $conf;
	$module_list = shn_get_modules_with_admin();
	shn_mod_menuopen(shn_get_module_name());
	shn_sub_mod_menuitem("default", _t("Admin Home"), 'admin');

	// added by gmiernicki ~ menu item for snapshot module
	_shn_admin_snap_menu();

	shn_sub_mod_menuopen("Location Hierarchy");
	shn_sub_mod_menuitem("loc_lvl", _t("Location Terminology"), 'admin');
	shn_sub_mod_menuitem("add_loc", _t("Add New Location"), 'admin');
	shn_sub_mod_menuitem("view_loc", _t("Modify Location"), 'admin');
	shn_sub_mod_menuitem("loc_range", _t("Location Range"), 'admin');
	shn_sub_mod_menuitem("loc_start", _t("Default Location"), 'admin');
	shn_sub_mod_menuclose();

	// Messaging Admin menu inclusion: Mifan Careem <mifan@respere.com>
	_shn_admin_msg_menu();

	shn_sub_mod_menuopen(_t("Module Configuration"));
	foreach($module_list as $i) {
		shn_sub_mod_menuitem("adm_default", $conf['mod_'.$i.'_name'], $i);
	}
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_t("System Security"));
		shn_sub_mod_menuitem("add_user", _t("User Management"), 'admin');
		shn_sub_mod_menuitem("acl_enable_mods", _t("Module Access Control"), 'admin');
		shn_sub_mod_menuitem("acl_privacy", _t("Data Classification"), 'admin');
		shn_sub_mod_menuitem("acl_enable_signup", _t("Self Signup"), 'admin');
		shn_sub_mod_menuitem("acl_event_log", _t("Event Log"), 'admin');
		shn_sub_mod_menuitem("acl_enable_locking", _t("User Locking"), 'admin');
		shn_sub_mod_menuitem("acl_enable_acl", _t("Disable Security"), 'admin');
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_t("Language / Locale"));
	shn_sub_mod_menuitem("lc_set", _t("Default Language"), 'admin');
	shn_sub_mod_menuitem("lc_add_new_lang", _t("Add/Remove Language"), 'admin');
	shn_sub_mod_menuitem("lc_trns", _t("Language Translation"), 'admin');
	shn_sub_mod_menuitem("lc_db", _t("Database Translation"), 'admin');
	shn_sub_mod_menuitem("lc_ui_trns", _t("Interactive Translation"), 'admin');
	shn_sub_mod_menuitem("lc_ui_trns_update", _t("Update Translation"), 'admin');
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_t("Config Utils"));
	shn_sub_mod_menuitem("conf_list", _t("Config Values"), 'admin');
	shn_sub_mod_menuitem("check_sec_policies", _t("Check Security Policy validity"), 'admin');
	shn_mod_menuitem("field_option_config", _t("Edit Field Options"), 'admin');
	shn_sub_mod_menuclose();
	shn_mod_menuclose();
	include $global['approot']."/inc/handler_mainmenu.inc";
}


function _shn_admin_acl_user_roles_menu($user_home=false) {
	shn_tabmenu_open();
	shn_tabmenu_item("add_user", _t("Add Users"), "admin");
	shn_tabmenu_item("del_user", _t("Remove Users"), "admin");
	shn_tabmenu_item("acl_user_edit_roles", _t("Edit Roles of a User"), "admin");
	shn_tabmenu_item("reset_pwd", _t("Reset Password of a User"), "admin");
	shn_tabmenu_item("acl_change_user_status", _t("Change User Status"), 'admin');
	shn_tabmenu_close();
}



function _shn_admin_acl_privacy_menu($privacy_home=false) {
	shn_tabmenu_open();
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
		<li>If you need to modify which roles have permissions to create/read/modify which data, click on the <strong>'Data Classifications & Role Permissions'</strong> tab on the top of the page.</li>
		<li>If you need to modify data sensitivity classifications of the data in the system, click on the <strong>'Data Classifications & System Data'</strong> tab on the top of the page.</li>
		</ul>
		</div>
		<?php
	}
}



function _shn_admin_acl_user_menu() {
	_shn_admin_acl_user_roles_menu();
}



function _shn_admin_acl_role_menu($module=null) {
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
