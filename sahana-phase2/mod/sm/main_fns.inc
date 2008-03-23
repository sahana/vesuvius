<?php
/**
* Main Functionality actions of the SM Module
* 
* PHP version 5
* 
* @author   	Mifan Careem <mifan@respere.com>
* @package 		module
* @subpackage 	sm
* @version 		$id$
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/mod/sm/wm_fns.inc";
include_once $global['approot']."/inc/lib_validate.inc";

//Include home description
include_once $global['approot']."/mod/sm/home.inc";




//not being used any more
//replaced by sha_gis_mapc()
/*
function shn_gis_show()
{
  //echo "showing";
  global $global;
  include_once $global['approot']."/mod/gis/gis_fns.inc";
  
  $options=array();
  if((isset($_POST['mapa_x'])) && isset($_POST['mapa_y'])){
  	//echo $_POST['mapa_x'];
  }
  //var_dump($_POST);
  shn_gis_map();
}
*/
function shn_sm_swik()
{
	shn_sm_show_wiki_map($_POST['opt_wikimap_type']);
}

function shn_sm_ewik()
{
	shn_sm_wiki_edit_com($_REQUEST['wiki_id']);
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


/**
 * Wikimap situation addition main controller function
 * @patch Fran Boon : Patch for coordinate validation
 */
function shn_sm_awik()
{
	if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'map':
				if($_POST['wiki_name']==""){
					shn_sm_show_wiki_add_detail(true);
				}
				else{
					shn_sm_show_wiki_add_map();
				}
				break;
			case 'img':
               	if(!($_POST['loc_x']=="")){
                       shn_sm_show_wiki_add_image();
               	}
               	elseif ((shn_valid_x_coordinate($_POST['gps_x']))&&(shn_valid_y_coordinate($_POST['gps_y']))){
                       shn_sm_show_wiki_add_image();
               	}
               	else{
                       shn_sm_show_wiki_add_map(true); 
               	}
               	break;
				
			case 'com':
				shn_sm_wiki_map_commit();
				break;
				
			default:
				shn_sm_show_wiki_add_detail();
				break;
			
		}
	}
	else
		shn_sm_show_wiki_add_detail();
}

function shn_sm_wm_default()
{
	shn_sm_show_wiki_map();
}

function shn_sm_wm_edit()
{
	
	if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'ewmp':
					shn_sm_wiki_edit($_REQUEST['wmid']);
					break;
			default:
		}
	}
}

						

?>
