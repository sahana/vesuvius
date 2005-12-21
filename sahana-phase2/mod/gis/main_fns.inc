<?php
/* $Id: main_fns.inc,v 1.3 2005-12-21 11:29:31 mifanc Exp $ */

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
	$db=$global['db'];
	include $global['approot']."/conf/config.inc";
	echo "<h2>"._("Area Map")."</h2>";
	if($conf['gis']){
		include $global['approot']."/mod/gis/conf.inc";
		if($conf['mod_gis']=='google_maps'){
			/*
			 * google maps
			 * check for online connectivity
			*/
			include_once $global['approot']."/mod/gis/plugins/google_maps/handler_google_maps.inc";
			//echo "GIS: Google Map";
			$q="select value from config where module_id='gis' and confkey='google_key'";
			$res=$db->Execute($q);
			$key=$res->fields[0];
			init_map($key);
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
