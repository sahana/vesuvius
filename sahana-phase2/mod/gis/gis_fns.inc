<?php
/* $Id: gis_fns.inc,v 1.11 2006-06-12 11:08:17 mifanc Exp $ */

/**
* Functions Page of the GIS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @package module
* @subpackage gis    
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/gis/main_fns.inc";


function shn_gis_map($opt_array=null)
{
	global $global;
	global $conf;
	$db = $global['db'];
	if($conf['gis'])
	{
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map($opt_array);
	}
	else
	  	echo "GIS not enabled";
?>
	
<?php
}
/**
 * Insert gis entry
*/
function shn_gis_dbinsert($uuid,$loc_id,$gis,$xcoord,$ycoord,$projection){
	global $global;
	$db = $global['db'];
	
	//@todo  generate id for gis entries
	$gis_id=shn_create_uuid('g');
	
	$q = "INSERT INTO gis_location ( poc_uuid , location_id , opt_gis_mod , map_northing , map_easting , map_projection , opt_gis_marker , gis_uid )
	VALUES (
	'{$uuid}', '{$loc_id}', '{$gis}', '{$xcoord}', '{$ycoord}', '{$projection}', NULL , '{$gis_id}'
	)";
	
	$res = $db->Execute($q);	
	
}

function shn_gis_map_with_markers_from_db()
{
	
}

/**
 * Check for GIS availability from config file
 * $deprecated
 */
function _shn_gis_check_gis()
{
	global $global;
	global $conf;
	//only if gis is enabled
	if($conf['gis' == 'true'])
	{
		
	}
	
}

/**
 * Initialize GIS plugin
 * Detects selected GIS plugin and calls functionalities from specified plugin
 * @access public
 * @param mixed  $name_of_map Custom Map Name
 * @todo: nicer error messages
 */
function shn_gis_init_plugin($name_of_map="Area Map")
{
	global $global;
	global $conf;
	$db=$global['db'];
	echo $conf['mod_gis_name'];
	if($conf['gis'])
	{
		echo "<h2>".$name_of_map."</h2>";
		//include $global['approot']."/mod/gis/conf.inc";
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		initialize_map();
		
	}
	else{
		//@TODO: nicer message
		echo "gis not enabled in config file";
	}
}

/**
* @deprecated
*/
function shn_gis_load_map()
{
	
}

/**
 * Show plain GIS map for viewing purposes
 * Centers at default center
 * @access public
 * @param mixed  $name_of_map Custom Map Name
 * $deprecated
 */
function shn_gis_show_map($name_of_map="Area Map")
{
	global $global;
	global $conf;
	shn_gis_init_plugin($name_of_map);
	load_map($conf['mod_gis_center_x'],$conf['mod_gis_center_y']);
	
	//below if statement is to handle GoogleMaps-IE inconsistencies
	if($conf['mod_gis_dflt'] == 'google_maps')
		end_page();
}

/**
 * Show GIS map for marker addition
 * Centers at default center
 * Allows addition of a single marker to plot location
 * @access public
 * @param mixed  $name_of_map Custom Map Name
 * @param $nameOfPoint Assign name to point
 */
function shn_gis_add_marker_map($name_of_map="Area Map",$name=null)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_add_marker_map($name);
	}

}

/**
 * Add marker map with form elements
 * Outputs Map within form elements which listen for click events
 * Includes additional GPS boxes
 * @param string $name_of_map	Value over map
 * @param string $nameOfPoint	Name of point to be stored
 * used
 */
function shn_gis_add_marker_map_form($name_of_map="Area Map",$nameOfPoint="")
{
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_form.inc');
	
	if($conf['gis'])
	{
		shn_form_fsopen($name_of_map);
		shn_form_hidden(array('loc_x'=>''));
		shn_form_hidden(array('loc_y'=>''));
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_add_marker_map_v2($nameOfPoint);
		shn_form_fsclose();
	}
	else
	{
		//no gis
	}
	shn_form_fsopen(_("GPS Coordinates"));
	shn_form_text(_("Northing / Latitude"),"gps_x",'size="60"');
	shn_form_text(_("Easting / Longitude"),"gps_y",'size="60"');
	shn_form_fsclose();
}

?>
