<?php
/** Main home page of the Camp Registry a.k.a Shelter Registry a.k.a ...
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package  Sahana - http://sahana.sourceforge.net
* @subpackage cr
* @author   Mifan Careem <mifan@opensource.lk>
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @version $Id: main.inc,v 1.19 2008-01-03 04:40:56 isurunishan Exp $
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/cr/main_fns.inc";
include_once $global['approot']."/inc/lib_menu.inc";


/**
 * Display main side menu for CR
 */
function shn_cr_mainmenu()
{
	global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen(_($conf['mod_cr_name']));
    shn_mod_menuitem("default",_("Home"),$module);
    shn_sub_mod_menuopen(_("Search"));
    shn_mod_menuitem("srch",_("Search by name"),$module);
    shn_mod_menuitem("srch_address",_("Search by address"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuitem("acmp",_("Add Shelter"),$module);
    shn_mod_menuitem("ecmp",_("Edit Shelter"),$module);
    shn_sub_mod_menuopen(_("Reports"));
    shn_sub_mod_menuitem("arpt",_("View All Shelters"),$module);
    shn_mod_menuitem("lrpt",_("View By Location"),$module);
    shn_mod_menuitem("contact",_("View Admin Details"),$module);
    if($conf['gis']){
    	shn_mod_menuitem("gis_show",_("Map by Location"),$module);
    	shn_mod_menuitem("gis_infect",_("Map by Infection"),$module);
    	shn_mod_menuitem("gis_population",_("Map by Population"),$module);
    }
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    
    // Display Sahana main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
