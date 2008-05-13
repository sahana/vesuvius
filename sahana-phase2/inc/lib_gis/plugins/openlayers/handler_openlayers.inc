<?php

/**
* $id$;
* Openlayers Plugin for GIS 
*
* PHP version 4 and 5
*
* Sahana - http://sahana.sourceforge.net
* @author     Mifan Careem <mifan@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    module
* @subpackage openlayers
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Show basic map
 * called by shn_gis_map in GIS API
 */
function show_map($opt=null)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_js_loaders();
    ol_layers();
    ol_osm_getTileURL();
?>            
</script>
	<div id="map" style="width: <?=$conf['gis_width']?>px; height: <?=$conf['gis_height']?>px"></div>
    <div id="status">Loading...</div>
<?php
}

/**
 * Show map with marker addition event
 * ability to enter markers on map
 * called by shn_gis_add_marker_map_form in GIS API
 */
function show_add_marker_map($name)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_js_loaders();
    ol_layers();
    ol_add_marker($name);
    ol_osm_getTileURL();
?>		
</script>
	<div id="map" style="width: <?=$conf['gis_width']?>px; height: <?=$conf['gis_height']?>px"></div>
    <div id="status">Loading...</div>
<?php
}

/**
 * Show map with markers
 * called by shn_gis_map_with_markers in gis api
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
    ol_osm_getTileURL();
?>            
</script>
	<div id="map" style="width: <?=$conf['gis_width']?>px; height: <?=$conf['gis_height']?>px"></div>
    <div id="status">Loading...</div>
<?php
}

/**
 * Show map with wiki markers
 * called by shn_gis_map_with_markers in GIS API
 */
function show_map_with_wiki_marker($array)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_js_loaders();
    ol_layers();
    ol_show_wiki_markers($array);
    ol_osm_getTileURL();
?>            
</script>
	<div id="map" style="width: <?=$conf['gis_width']?>px; height: <?=$conf['gis_height']?>px"></div>
    <div id="status">Loading...</div>
<?php
}

/**
 * Show map with custom markers
 * called by shn_gis_density_map in gis api
*/
function show_map_with_custom_markers($array)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_js_loaders();
    ol_layers();
    ol_show_custom_markers($array);
    ol_osm_getTileURL();
?>		
</script>
	<div id="map" style="width: <?=$conf['gis_width']?>px; height: <?=$conf['gis_height']?>px"></div>
    <div id="status">Loading...</div>
<?php
}

?>
