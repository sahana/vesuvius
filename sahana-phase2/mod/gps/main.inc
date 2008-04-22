<?php

/**
* Main home page of the GPS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Sriganeshan <sri@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
include_once $global['approot']."/mod/gps/main_fns.inc";
include_once $global['approot']."/mod/gps/handler_marker.inc";
include_once $global['approot']."/mod/gps/handler_route.inc";
include_once $global['approot']."/mod/gps/handler_upload_waypoint.inc";
include_once $global['approot']."/mod/gps/handler_download_waypoint.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";

function shn_gps_mainmenu(){
    global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen($conf['mod_gps_name']);
    shn_mod_menuitem("default",_("Home"),$module);
    shn_sub_mod_menuopen(_("Download Data"));
    shn_sub_mod_menuitem("dynamic_download",_("Dynamic Routes"),$module);
    shn_sub_mod_menuitem("waypoint",_("Waypoints/Markers"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuitem("upload",_("Upload Waypoints"),$module);
    shn_mod_menuitem("marker",_("Download Markers"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


function shn_gps_waypoint()
{
       	if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'map':
			shn_gps_display_points();
			break;
			
			case 'add':
			shn_gps_sort_download();
			break;
		}
	}else
	shn_gps_find_waypoint();
	
}


function shn_gps_dynamic_download()
{
	//if(isset($_REQUEST['seq'])){
		//switch($_REQUEST['seq']){
			//case 'map':
				//shn_gps_display_routes();
				//break;
			//case 'add':
				
				//shn_gps_sort_route();
				//break;

			//}
	//}else

       shn_gps_display_routes();

}

function shn_gps_marker()
{
	if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'map':
				if($_POST['marker_name']==""){
					shn_marker_add_detail(true);
				}
				else{
					shn_marker_add_map();
				}
				break;
			case 'img':
	             		 if((shn_valid_x_coordinate($_POST['loc_x']))&&(shn_valid_y_coordinate($_POST['loc_y']))){
                     		  shn_marker_add_file();
				
              		 }
              	 else{
                       shn_marker_add_map(true);                           
		   }
               		 break;
				
			case 'com':
				
				shn_marker_sort();
				break;
				
			case 'default':
				show_wiki_add_detail();
				break;
			
		}
	}
	else
		shn_marker_add_detail();
}



function shn_gps_upload()
{
	
	include_once('handler_upload.inc');

}


function shn_gps_classify()
{
	shn_gps_save_points();

}

function shn_gps_classifyxxxx()
{	
if(isset($_REQUEST['seq']))
{
	if(($_REQUEST['seq'])=='map')
		 shn_gps_save_points();
	else
	  shn_gps_upload();
}
else
shn_gps_point_sort();


}//end of function shn_gps_classify()

function shn_gps_sort_download()
{

	switch(trim($_POST['button1'])){
		case "New Search":
			shn_gps_find_waypoint();
			break;	

		case "Download Markers":
			shn_gps_add_creator();
			break;
		default:
			break;

	}

}

/*function shn_gps_sort_route()
{

switch(trim($_POST['button1'])){
		case "New Search":
			shn_gps_find_route();
			break;	

		case "Download Route":
			shn_gps_route_creator();
			break;
		default:
			break;

	}


}*/

?>
