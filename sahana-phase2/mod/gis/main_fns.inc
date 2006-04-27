<?php
/* $Id: main_fns.inc,v 1.14 2006-04-27 12:57:11 mifanc Exp $ */

/**
* Functions page of the GIS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package module
* @subpackage gis    
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
global $global;
include_once $global['approot']."/inc/lib_modules.inc";

function shn_gis_default()
{
	global $global;
?>
	<div id="home">
	<h2><?php echo _("GIS Mapping");?></h2>
			<p><?echo _("The GIS (Geographic Information System) Mapping Module provides Spatial and Mapping " .
					"Functionality to Sahana. It is used by various modules to display maps, " .
					"specify locations and coordinates of camps, victims and relief efforts. Currently it supports Google Maps")?></p>
	</div>
<?php											
}

function shn_gis_show()
{
	//echo "showing";
	global $global;
	include_once $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_map();
	//shn_gis_show_map();
	//shn_gis_add_marker_map();
}





?>
