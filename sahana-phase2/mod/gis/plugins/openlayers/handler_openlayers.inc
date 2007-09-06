<?php
/**
* $id$;
* 
* Openlayers Plugin for GIS 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @author	Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    module
* @subpackage openlayers
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * show basic map
 * called by shn_gis_map in gis api
 * @todo get layers from catalogue module instead of conf.inc
 */
function show_map($opt=null)
{
	global $global;
	global $conf;
	include_once('openlayers_fns.php');
	
	ol_js_loaders();
	ol_layers();
?>            
	}		

</script>
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}




/**
 * show map with markers
 * called by shn_gis_map_with_markers in gis api
 * 
 */
function show_map_with_markers($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	include_once('openlayers_fns.php');
	
  	ol_js_loaders();
	ol_layers();
	ol_show_markers($array);
?>            
	}		

</script>
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}


/**
 * show map with wiki markers
 * called by shn_gis_map_with_markers in gis api
 * 
 */
function show_map_with_wiki_marker($array)
{
	global $global;
	global $conf;
	include_once('openlayers_fns.php');
	
  	ol_js_loaders();
	ol_layers();
	ol_show_wiki_markers($array);
?>            
	}		

</script>
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}

/**
 * show map with marker addition event
 * ability to enter markers on map
 * called by shn_gis_add_marker_map_form in gis api
 */
function show_add_marker_map($name)
{
	global $global;
	global $conf;
	include_once('openlayers_fns.php');
	
	ol_js_loaders();
	ol_layers();
	ol_add_marker($name);
?>		
	}			
	
</script>
	<div id="map" style="width: <?=$conf['mod_gis_width']?>px; height: <?=$conf['mod_gis_height']?>px"></div>
<?php
}
		
?>
