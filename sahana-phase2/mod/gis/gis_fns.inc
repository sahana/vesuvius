<?php
/* $Id: gis_fns.inc,v 1.26 2007-12-03 09:10:47 isurunishan Exp $ */

/**
* Functions Page of the GIS Module and API
* Controller functions that dynamically uses selected plugin
* 
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
include_once $global['approot']."/inc/lib_errors.inc";

/**
 * Error Message for disabled GIS
 * @access public
 * @return void
 */
function shn_gis_print_msg()
{
	add_warning(_('GIS Functionality has been disabled. Please contact your administrator to enable it'));
}

/**
 * Retrieve GPS coords from REST url
 * store in db with entity id
 * Can be used to modify coordinates of existing entities
 * @param string $uuid uuid of entity to store
 * @param numeric $lat latitude
 * @param numeric $lon longitude
 * @access public
 * @return void
 * @todo enhance capabilities. Do edit of existing entities.Add speed and direction info
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
 * GeoRSS Feed Display
 * @access private
 * @return void
 * @todo get rss feed from aggregator or registered source
 *       currently gets it from conf value
 */
function shn_gis_show_georss()
{
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_gis/lib_georss.inc');
	
	// Create lastRSS object
	$rss = new lastRSS;
	// Set cache dir and cache time limit (1200 seconds)
	// (don't forget to chmod cache dir to 777 to allow writing)
	$rss->cache_dir = '';
	$rss->cache_time = 0;
	$rss->cp = 'US-ASCII';
	$rss->date_format = 'l';
	
	// Try to load and parse RSS file as stated in conf
	$rssurl = $conf['mod_gis_georss_feed'];
	
	if ($rs = $rss->get($rssurl)) {
	    echo '<pre>';
	    print_r($rs);
	    echo '</pre>';
	    }
	else {
	    echo "Error: It's not possible to get $rssurl...";
	} 
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
 * Use to enter GIS coords into database
 * @param char $uuid uuid of entity
 * @param char $loc_id uuid of location
 * @param char gis gis module name
 * @param numeric xcoord x coordinate value
 * @param numeric ycoord y coordinate value
 * @param char projection projection type
 * @access public
 * @return void
 * @todo change coordinate data type to standard format
 * @todo handle projection information and module specific functions
*/
function shn_gis_dbinsert($uuid,$loc_id,$gis,$ycoord,$xcoord,$projection){
	global $global;
	include_once $global['approot']."/inc/lib_uuid.inc";
	$db = $global['db'];
	
	//@todo  generate id for gis entries
	$gis_id=shn_create_uuid('g');
	
	$q = "INSERT INTO gis_location ( poc_uuid , location_id , opt_gis_mod , map_northing , map_easting , map_projection , opt_gis_marker , gis_uid )
	VALUES (
	'{$uuid}', '{$loc_id}', '{$gis}', '{$ycoord}', '{$xcoord}', '{$projection}', NULL , '{$gis_id}'
	)";
	
	$res = $db->Execute($q);		
}

/**
 * Database entry api for gis data
 * Use to enter GIS coords into database
 * Used with OGC compliant Databases
 * @param char $uuid uuid of matching entity
 * @param numeric $latcoord lat (y) coordinate value
 * @param numeric $loncoord lon (x) coordinate value
 * @param timestamp $time time value
 * @access public
 * @return void
*/
function shn_gis_dbinsert_feature($uuid,$latcoord,$loncoord,$time=null){
	global $global;
	include_once $global['approot']."/inc/lib_uuid.inc";
	$db = $global['db'];
	
	$gis_id=shn_create_uuid('g');
	
	// @TODO: Check for type of insertion. POINT assumed.
	
	$query = "INSERT INTO gis_feature (feature_uuid,poc_uuid,feature_coords) " .
			 " VALUES ('{$gis_id}', '{$uuid}', GeomFromText('POINT($latcoord $loncoord)'))";
	
	$res = $db->Execute($query);		
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
 * @access public
 * @return void 
 */
function shn_gis_add_marker_map_form($name_of_map="Area Map",$nameOfPoint="",$button_submit_opts=null)
{
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_form.inc');
	
	shn_form_fsopen(_("GPS Coordinates"));
	shn_form_text(_("Northing / Latitude"),"gps_y",'size="60"');
	shn_form_text(_("Easting / Longitude"),"gps_x",'size="60"');
	shn_form_submit(_("Next"),$button_submit_opts);
	shn_form_fsclose();
	
	if($conf['gis'])
	{
		shn_form_fsopen($name_of_map);
		shn_form_hidden(array('loc_x'=>''));
		shn_form_hidden(array('loc_y'=>''));
		$plugin_name = $conf['mod_gis_dflt'];
		include $global['approot']."/mod/gis/plugins/"."$plugin_name"."/handler_"."$plugin_name".".inc";
		echo "<div class='msg info'>";
		echo _("You can move around and enlarge/reduce the size of the area you want using
the scale on upper left corner of the map. By clicking on a map you can
mark your location with a pointer. If you want to remove the pointer,
simply click on the center of the pointer.");
		echo "</div>";
		show_add_marker_map($nameOfPoint);
		shn_form_fsclose();
	}
	else
	{
		shn_gis_print_msg();
	}
	
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
