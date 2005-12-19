<?php
/* $Id; */

/**
* Functions page of the GIS Module
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
global $global;
include_once $global['approot']."/inc/lib_modules.inc";

function shn_gis_default()
{
	global $global;
?>
	<h1><?php echo _("GIS Mapping");?></h1>
	<br>
	<div id="home">
		<ul>
			<li>The GIS Mapping Module provides Spatial and Mapping Functionality to Sahana</li>
			<li>It is used by various modules to display maps, specify locations and coordinates, tracking etc.</li>
		</ul>
	</div>
<?php											
}

function shn_gis_show()
{
	global $global;
	include $global['approot']."/conf/config.inc";
	echo "<h2>"._("Area Map")."</h2>";
	if($conf['gis']){
		include $global['approot']."/mod/gis/conf.inc";
		if($conf['mod_gis']=='gmap'){
			/*
			 * google maps
			 * check for online connectivity
			*/
			include_once $global['approot']."/mod/gis/handler_gmap.inc";
			//echo "GIS: Google Map";
			init_map($conf['gmap_key']);
			load_map();
		}
	}
	else{
?>
		<p>No Currently Selected GIS</p>
<?php
	}

}
?>
