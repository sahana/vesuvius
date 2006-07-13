<?php
/* $Id: main.inc,v 1.6 2006-07-13 08:59:02 mifanc Exp $; */

/**
* Main home page of the GIS Module
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
//var_dump($global[db]);
include_once $global['approot']."/mod/gis/main_fns.inc";
include_once $global['approot']."/mod/gis/conf.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/wm/wm_fns.php";
include_once $global['approot']."/inc/lib_menu.inc";


function shn_gis_mainmenu(){
	global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen(_($conf['mod_wm_name']));
    shn_mod_menuitem("default",_("Home"),$module);
    shn_mod_menuitem("aloc",_("Add Landmark"),$module);
    shn_mod_menuitem("swik",_("View Situation Map"),$module);
    shn_mod_menuitem("awik",_("Add Situation"),$module);
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}

function shn_gis_awik()
{
	if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'map':
				if($_POST['wiki_name']==""){
					show_wiki_add_detail(true);
				}
				else{
					show_wiki_add_map();
				}
				break;
			case 'com':
				shn_wiki_map_commit();
				break;
				
			case 'default':
				show_wiki_add_detail();
				break;
			
		}
	}
	else
		show_wiki_add_detail();
}

function shn_wm_default()
{
	show_wiki_map();
}

function shn_gis_swik()
{
	show_wiki_map();
}

?>
