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

    shn_sub_mod_menuopen(_("Disaster Incidents"));
    include $global['approot']."/mod/admin/ims_menus.inc"; 
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Location Config"));
    shn_sub_mod_menuitem("loc_lvl", _("Location Levels"), 'admin');
    shn_sub_mod_menuitem("add_loc", _("Add Location"), 'admin');
    shn_sub_mod_menuitem("view_loc", _("Edit & Delete Location"), 'admin');
    shn_sub_mod_menuitem("loc_range", _("Set Location Range"), 'admin');
    shn_sub_mod_menuitem("loc_start", _("Set Starting Location"), 'admin');
    // shn_sub_mod_menuitem("loc_range", _("Set Location Range"), $module);
    // shn_sub_mod_menuitem("start_loc", _("Set Starting Location"), $module);
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("GIS Config"));
    shn_sub_mod_menuitem("gis_form", _("Plugin Management"), 'admin');
    //shn_sub_mod_menuitem("gis_mapserver", _("Mapserver Management"), 'admin');
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Localization"));
    shn_sub_mod_menuitem("lc_set", _("Set Locale"), 'admin');
    shn_sub_mod_menuitem("lc_db", _("Database L10N"), 'admin');
    shn_sub_mod_menuitem("lc_trns", _("Language Translation"), 'admin');
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Module Config"));
    foreach ($module_list as $i) {  
        shn_sub_mod_menuitem("adm_default", $conf['mod_'.$i.'_name'], $i);
    }
    shn_sub_mod_menuclose();

    //shn_sub_mod_menuopen(_("Module Management Console"));
    //include $global['approot']."/mod/admin/mmc_menus.inc"; 
    //shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_("Security Config"));
    shn_sub_mod_menuitem("acl_user_roles", _("User Config"), 'admin');
    shn_sub_mod_menuitem("acl_change_user_status", _("Change User Status"), 'admin');
    shn_sub_mod_menuitem("acl_unlock_user", _("Unlock User"), 'admin');
    shn_sub_mod_menuitem("acl_data_classifications", _("Data Classifications"), 'admin');
    shn_sub_mod_menuitem("acl_data_privacy", _("Data Classifications & Role Permissions"), 'admin');
    shn_sub_mod_menuitem("acl_data_classifications_tables", _("Data Classifications & System Data "), 'admin');
    shn_sub_mod_menuitem("acl_event_log", _("Event Log"), 'admin');

    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuitem("conf_list", _("Config Values"), 'admin');
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


function _shn_admin_acl_user_roles_menu()
{
	
	shn_tabmenu_open();
	shn_tabmenu_item("add_user", "Add Users", "admin");
	shn_tabmenu_item("del_user", "Remove Users", "admin");
	shn_tabmenu_item("acl_user_edit_roles", "Edit Roles of an User", "admin");
	shn_tabmenu_item("reset_pwd", "Reset Password of an User", "admin");
	shn_tabmenu_close();
 ?>

<br>
<div id="home">
<h2><?= _('Welcome to Users section'); ?></h2>

<ul>
    <li><?=_('Click <strong>Users</strong> to add,remove Users or edit User Roles')?></li>
    
</ul>
</div>
<?php


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
