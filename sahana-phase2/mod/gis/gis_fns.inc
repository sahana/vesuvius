<?php
/* $Id: gis_fns.inc,v 1.2 2006-03-15 12:21:52 mifanc Exp $ */

/**
* Functions Page of the GIS Module
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

?>
