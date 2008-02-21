<?php

/* $Id: main.inc,v 1.20 2008-02-21 08:42:50 mifanc Exp $; */
/* $Id: main.inc,v 1.20 2008-02-21 08:42:50 mifanc Exp $; */

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
//include_once $global['approot']."/mod/gis/conf.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/gis/wm_fns.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";


function shn_gis_mainmenu(){
	global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen($conf['mod_gis_name']);
    shn_mod_menuitem("default",_t("Home"),$module);
    shn_mod_menuitem("swik",_t("Situation Map"),$module);
    shn_mod_menuitem("awik",_t("Add New Situation"),$module);
    shn_mod_menuitem("mapc",_t("Map Client"),$module);
    
    // @todo: Confirm functionality
    /*
    shn_sub_mod_menuopen(_t("Landmark Feature"));
    shn_mod_menuitem("aloc",_t("Add Landmark"),$module);
    shn_mod_menuitem("vloc",_t("View Landmarks"),$module);
    shn_sub_mod_menuclose();
    */
    //shn_sub_mod_menuopen(_t("Situation Feature"));
    //shn_sub_mod_menuclose();
    // @todo: confirm functionality
    /*
    shn_sub_mod_menuopen(_t("Spatial Reports"));
    shn_sub_mod_menuclose();
    */
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}

//-----------------------------

function shn_gis_mapc()
{
	//earlier done by Mifan's shn_gis_show()
	//main.inc, wm_fns.php and main_fns.inc were changed
	
	//needs coding for validation etc
	
					map_client(true);
				
}

//-----------------------------



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
			case 'img':
				// Map used to enter location
				// Patch by Fran Boon
               if(!($_POST['loc_x']=="")){
                       show_wiki_add_image();
               }
               elseif ((shn_valid_x_coordinate($_POST['gps_x']))&&(shn_valid_y_coordinate($_POST['gps_y']))){
                       show_wiki_add_image();
               }
               else{
                       show_wiki_add_map(true);                              }
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

function shn_gis_wm_edit()
{
	
	if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'ewmp':
					//echo "{$_REQUEST['wmid']}";
					shn_wiki_edit($_REQUEST['wmid']);
				break;
			default:
		}
	}
}

function shn_gis_swik()
{
	show_wiki_map($_POST['opt_wikimap_type']);
}

function shn_gis_ewik()
{
	shn_wiki_edit_com($_REQUEST['wiki_id']);
}

//dynamic gps coordinate update via REST
function shn_gis_gps_rest()
{
	global $global;
  	include_once $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_gps_from_rest($_REQUEST['gps_id'],$_REQUEST['gps_lat'],$_REQUEST['gps_lon']);
}

?>
