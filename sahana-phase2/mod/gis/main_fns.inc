<?php
/* $Id: main_fns.inc,v 1.6 2006-01-17 09:37:58 chamindra Exp $ */

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
	<div id="home">
	<h2><?php echo _("GIS Mapping");?></h2>
			<p>The GIS (Geographic Information System) Mapping Module provides Spatial and Mapping Functionality to Sahana. It is used by various modules to display maps, specify locations and coordinates of camps, victims and relief efforts. Currently it support Google Maps</p>
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

			$w="select value from config where module_id='gis' and confkey='center_x'";
			$wres=$db->Execute($w);
			$wkey=$wres->fields[0];
						
			$e="select value from config where module_id='gis' and confkey='center_y'";
			$eres=$db->Execute($e);
			$ekey=$eres->fields[0];

			
			init_map($key);
			load_map($wkey,$ekey);
		}
	}
	else{
?>
		<p>No Currently Selected GIS</p>
<?php
	}

}
?>
