<?php
/**Main home page of the wm
* $Id: main.inc,v 1.1 2006-06-22 09:44:55 mifanc Exp $
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/wm/wm_fns.php";
include_once $global['approot']."/inc/lib_menu.inc";


function shn_wm_mainmenu()
{
	global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen(_($conf['mod_wm_name']));
    shn_mod_menuitem("default",_("Home"),$module);
    //shn_mod_menuitem("srch",_("Search"),$module);
    //shn_mod_menuitem("acmp",_("Add Camp"),$module);
    //shn_mod_menuitem("ecmp",_("Edit Camp"),$module);
    //shn_sub_mod_menuopen(_("Reports"));
    //shn_sub_mod_menuitem("arpt",_("View All Camps"),$module);
    //shn_mod_menuitem("lrpt",_("View By Location"),$module);
    //shn_mod_menuitem("contact",_("View Admin Details"),$module);
    //if($conf['gis'])
    	//shn_mod_menuitem("gis_show",_("Location Map"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}

function shn_wm_default()
{
	show_wiki_map();
}


?>
