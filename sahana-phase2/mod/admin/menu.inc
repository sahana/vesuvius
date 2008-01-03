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
    shn_sub_mod_menuitem("default", _("Admin Home"), 'admin');

    shn_sub_mod_menuopen(_("Location Hierarchy"));
    shn_sub_mod_menuitem("loc_lvl", _("Location Terminology"), 'admin');
    shn_sub_mod_menuitem("add_loc", _("Add New Location"), 'admin');
    shn_sub_mod_menuitem("view_loc", _("Modify Location"), 'admin');
    shn_sub_mod_menuitem("loc_range", _("Location Range"), 'admin');
    shn_sub_mod_menuitem("loc_start", _("Default Location"), 'admin');
    // shn_sub_mod_menuitem("loc_range", _("Set Location Range"), $module);
    // shn_sub_mod_menuitem("start_loc", _("Set Starting Location"), $module);
    shn_sub_mod_menuclose();

    //shn_sub_mod_menuopen(_("Mapping / GIS"));
    shn_sub_mod_menuitem("gis_form", _("Mapping / GIS"), 'admin');
    //shn_sub_mod_menuitem("gis_mapserver", _("Mapserver Management"), 'admin');
    //shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Module Configuration"));
    foreach($module_list as $i) {
        shn_sub_mod_menuitem("adm_default", $conf['mod_'.$i.'_name'], $i);
    }
    shn_sub_mod_menuclose();

    //shn_sub_mod_menuopen(_("Module Management Console"));
    //include $global['approot']."/mod/admin/mmc_menus.inc";
    //shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("System Security"));

    if ($conf['acl_enabled']) {
	    shn_sub_mod_menuitem("acl_user_roles", _("User Management"), 'admin');
	    shn_sub_mod_menuitem("acl_enable_mods", _("Module Access Control"), 'admin');
		shn_sub_mod_menuitem("acl_privacy", _("Data Classification"), 'admin');
		shn_sub_mod_menuitem("acl_enable_signup", _("Self Signup"), 'admin');
	    shn_sub_mod_menuitem("acl_event_log", _("Event Log"), 'admin');
	    shn_sub_mod_menuitem("acl_enable_locking", _("User Locking"), 'admin');
	    shn_sub_mod_menuitem("acl_enable_acl", _("Disable Security"), 'admin');
    } else {
		shn_sub_mod_menuitem("acl_enable_acl", _("Enable Security"), 'admin');
    }

    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Language / Locale"));
    shn_sub_mod_menuitem("lc_set", _("Default Language"), 'admin');
    shn_sub_mod_menuitem("lc_add_new_lang", _("Add/Remove Language"), 'admin');
    shn_sub_mod_menuitem("lc_trns", _("Language Translation"), 'admin');
    shn_sub_mod_menuitem("lc_db", _("Database Translation"), 'admin');
    shn_sub_mod_menuitem("lc_ui_trns", _("Interactive Translation"), 'admin');
    shn_sub_mod_menuitem("lc_ui_trns_update", _("Update Translation"), 'admin');
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Disaster Levels"));
	shn_sub_mod_menuitem("ims_level1",_('Registered ')._lc($conf['mod_admin_ims_level1']), 'admin');
	shn_sub_mod_menuitem("ims_level2",_('Registered ')._lc($conf['mod_admin_ims_level2']), 'admin');
	shn_sub_mod_menuitem("ims_level3",_('Registered ')._lc($conf['mod_admin_ims_level3']), 'admin');
	shn_sub_mod_menuitem("ims_config",_('Levels Terminology'), 'admin');
    //include $global['approot']."/mod/admin/ims_menus.inc";
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Config Utils"));
    shn_sub_mod_menuitem("conf_list", _("Config Values"), 'admin');
    shn_sub_mod_menuitem("check_sec_policies", _("Check Security Policy validity"), 'admin');
    shn_sub_mod_menuitem("lc_upload_file", _("Upload sahana.po/.mo file"), 'admin');
    shn_sub_mod_menuclose();

    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


function _shn_admin_acl_user_roles_menu($user_home=false)
{
	shn_tabmenu_open();
	shn_tabmenu_item("add_user", _("Add Users"), "admin");
	shn_tabmenu_item("del_user", _("Remove Users"), "admin");
	shn_tabmenu_item("acl_user_edit_roles", _("Edit Roles of an User"), "admin");
	shn_tabmenu_item("reset_pwd", _("Reset Password of an User"), "admin");
	shn_tabmenu_item("acl_change_user_status", _("Change User Status"), 'admin');
    shn_tabmenu_item("acl_unlock_user", _("Unlock User"), 'admin');
	shn_tabmenu_close();
	if($user_home){
?>

	<br>
	<div id="home">
	<h2><?php echo _('Welcome to Users section'); ?></h2>
	<h3><?php echo _("As Administrator , use this section for the following")?></h3>
	<ul>
    <li><?=_('Add Users')?></li>
    <li><?=_('Remove Users')?></li>
    <li><?=_('Change User Roles')?></li>
    <li><?=_('Change User Status')?></li>
    <li><?=_('Unlock Users')?></li>
	</ul>
	</div>
<?php
	}
}

function _shn_admin_acl_privacy_menu($privacy_home=false)
{
	shn_tabmenu_open();
	//shn_tabmenu_item("acl_data_classifications", _("Data Classifications"), 'admin');
    shn_tabmenu_item("acl_data_privacy", _("Data Classifications & Role Permissions"), 'admin');
    shn_tabmenu_item("acl_data_classifications_tables", _("Data Classifications & System Data "), 'admin');
	shn_tabmenu_close();
	if($privacy_home==true){
 ?>

	<br>
	<div id="home">
	<h2><?php echo  _('Welcome to Privacy section'); ?></h2>

	<ul>
    <li><strong><?php echo _('You can set Privacy settings for Data and Roles')?></strong></li>

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
	<a href="index.php?mod=admin&amp;act=add_role"><?=_("Add Role")?></a>
	<a href="index.php?mod=admin&amp;act=del_role"><?=_("Remove Role")?></a>
	<a href="index.php?mod=admin&amp;act=acl_role_perms"><?=_("Existing Role Permissions")?></a>
	<a href="index.php?mod=admin&amp;act=acl_role_edit_perms"><?=_("Modify Role Permissions")?></a>
	</div>
	<br>
<?php
}
?>
