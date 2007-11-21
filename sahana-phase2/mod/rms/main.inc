<?php
/**
* The Sahana Resquest Management System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_uuid.inc";

//include_once $global['approot']."/inc/lib_modules.inc";
//include_once $global['approot']."/inc/lib_validate.inc";
//include_once $global['approot']."/inc/lib_form.inc";
//include_once $global['approot']."/inc/lib_table.inc";
//require_once $global['approot']."/inc/lib_menu.inc";
//include_once($global['approot']."/inc/lib_uuid.inc");
include_once($global['approot']."/inc/lib_dependency.inc");
//include_once $global['approot']."/inc/lib_location.inc";
require_once 'lib_rms.inc';
require_once 'lib_rms_db.inc';
require_once 'lib_rms_js.inc';
require_once 'lib_rms_rss.inc';

include_once $global['approot']."/mod/gis/gis_fns.inc";
include_once $global['approot']."/mod/ims/lib_ims.inc";

function shn_rms_default()
{
    include_once ('handler_home.inc');
}

function shn_rms_mainmenu()
{
	global $global;
    $module = $global['modlue'];
    
    shn_mod_menuopen(shn_get_module_name());
    shn_mod_menuitem("default", _("Home"), $module);
    shn_sub_mod_menuopen(_("Requests"));
    shn_sub_mod_menuitem("req_new", _("Make Request"), $module);
    shn_sub_mod_menuitem("req_ls", _("List Requests"), $module);
    shn_sub_mod_menuitem("req_sch", _("Search Requests"), $module);
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_("Pledges"));
    shn_sub_mod_menuitem("plg_new", _("New Pledge"), $module);
    shn_sub_mod_menuitem("plg_ls", _("List Pledges"), $module);
    shn_sub_mod_menuitem("plg_sch", _("Search Pledges"), $module);
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_("Manage"));
    shn_sub_mod_menuitem("req_ls", _("Fulfill Request"), $module);
//    shn_sub_mod_menuitem("mng_stat", _("View Statistics"), $module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose() ;
    
    include $global['approot']."/inc/handler_mainmenu.inc";
}

function shn_rms_req_new()
{
    include_once ('handler_req_new.inc');
}

function shn_rms_req_ls()
{
    include_once ('handler_req_ls.inc');
}

function shn_rms_req_sch()
{
    include_once ('handler_req_sch.inc');
}

function shn_rms_plg_new()
{
    include_once ('handler_plg_new.inc');
}

function shn_rms_plg_ls()
{
    include_once ('handler_plg_ls.inc');
}

function shn_rms_plg_sch()
{
    include_once ('handler_plg_sch.inc');
}

function shn_rms_mng_ff()
{
    //global $global;
    include_once ('handler_mng_ff.inc');
    //include_once ('handler_req_ls.inc');
}

function shn_rms_mng_stat()
{
    include_once ('handler_mng_stat.inc');
}

function shn_rms_fullfill_from_inventory()
{
    include_once('handler_mng_ff.inc');
}
?>