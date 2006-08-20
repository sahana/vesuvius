<?php
/* $Id: gis_fns.inc,v 1.16 2006-08-20 19:40:01 mifanc Exp $ */

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
* 
* This file contains the GIS API which provides an abstract view to GIS functions implemented as plugins
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/gis/main_fns.inc";

/**
 * Error Message for disabled GIS
 * @access public
 * @return void
 */
function shn_gis_print_msg()
{
?>
	<h3><?=_("GIS Mapping has been disabled. Please contact the Administrator to enable it")?></h3>
<?php
}

/**
 * Retrieve GPS coords from REST url
 * store in db with id
 * @access public
 * @return void
 */
function shn_gis_gps_from_rest($uuid,$lat,$lon)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	include_once $global['approot']."/inc/lib_uuid.inc";
	$gis_id=shn_create_uuid('gis');
	$query="insert into gis_location (poc_uuid,map_northing,map_easting,gis_uid) " .
			" values ('{$uuid}','{$lat}','{$lon}','{$gis_id}') ";
	$db->Execute($query);
	echo _("Coordinates Added");
}

/**
 * Show basic GIS map without further functionalities
 * @access public
 * @return void
 */
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
		shn_gis_print_msg();
}

/**
 * Database entry api for gis data
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

/**
 * Show GIS map for marker addition
 * Centers at default center
 * Allows addition of a single marker to plot location
 * Without form element or gps boxes
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
	else{
		shn_gis_print_msg();
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
		show_add_marker_map($nameOfPoint);
		shn_form_fsclose();
	}
	else
	{
		shn_gis_print_msg();
	}
	shn_form_fsopen(_("GPS Coordinates"));
	shn_form_text(_("Northing / Latitude"),"gps_x",'size="60"');
	shn_form_text(_("Easting / Longitude"),"gps_y",'size="60"');
	shn_form_fsclose();
}

/**
 * Add map with simple markers from database
 * @param mixed $array 2d array of marker info to be shown
 * @access public
 * @return void
 */
function shn_gis_map_with_markers($array)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map_with_markers($array);
	}	
	else{
		shn_gis_print_msg();
	}
}

/**
 * Add map with markers with wiki like info
 * @param mixed $array 2d array of info to be added
 * @access public
 * @return void
 */
function shn_gis_map_with_wiki_markers($array)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map_with_wiki_marker($array);
	}
	else{
		shn_gis_print_msg();
	}	
}

/**
 * GIS reporting function
 * shows density based markers in different colors
 * statistical info and markers are specified in array
 * @param mixed $array 2d associative array of information
 * @access public
 * @return void
 */
function shn_gis_density_map($array)
{
	global $global;
	global $conf;
	if($conf['gis'])
	{
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		show_map_with_custom_markers($array);
	}
	else{
		shn_gis_print_msg();
	}	
}


?>
