<?php
/* $Id: gis_fns.inc,v 1.3 2006-03-21 08:55:03 mifanc Exp $ */

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


/**
 * Insert gis entry
*/
function shn_gis_dbinsert($uuid,$loc_id,$gis,$xcoord,$ycoord,$projection){
	global $global;
	$db = $global['db'];
	
	//@todo  generate id for gis entries
	$gis_id=time();
	
	$q = "INSERT INTO gis_location ( poc_uuid , location_id , opt_gis_mod , map_northing , map_easting , map_projection , opt_gis_marker , gis_uid )
	VALUES (
	'{$uuid}', '{$loc_id}', '{$gis}', '{$xcoord}', '{$ycoord}', '{$projection}', NULL , '{$gis_id}'
	)";
	
	$res = $db->Execute($q);	
	
}

/**
 * Check for GIS availability from config file
 */
function _shn_gis_check_gis()
{
	global $global;
	include $global['approot']."/conf/config.inc";
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
 */
function shn_gis_init_plugin($name_of_map="Area Map")
{
	global $global;
	global $conf;
	$db=$global['db'];
	if($conf['gis'])
	{
		echo "<h2>".$name_of_map."</h2>";
		//include $global['approot']."/mod/gis/conf.inc";
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		initialize_map();
		
	}
	else{
		//gis not enabled in config file
	}
}

/**
 * Show plain GIS map for viewing purposes
 * Centers at default center
 * @access public
 * @param mixed  $name_of_map Custom Map Name
 */
function shn_gis_show_map($name_of_map="Area Map")
{
	global $global;
	global $conf;
	shn_gis_init_plugin($name_of_map);
	load_map($conf['mod_gis_center_x'],$conf['mod_gis_center_y']);
}

?>
