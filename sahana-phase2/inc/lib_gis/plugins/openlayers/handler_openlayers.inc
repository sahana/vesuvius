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
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show basic map
 * + provide way of saving the current viewport in form fields (for GIS Defaults)
 * called by shn_gis_map_select in GIS API
 */
function show_map_select($lat,$lon,$zoom)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_viewport_save_button();
    ol_js_loaders();
    ol_layers();
    ol_functions();
    ol_viewport_save($lat,$lon,$zoom);
    _shn_print_end_of_map();
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
    ol_functions();
    _shn_print_end_of_map();
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
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show map with wiki markers
 * called by shn_gis_map_with_wiki_markers in GIS API
 */
function show_map_with_wiki_marker($array)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_js_loaders();
    ol_layers();
    ol_show_wiki_markers($array);
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show map with wiki markers
 * + allow updating of form fields by selection of marker
 * called by shn_gis_map_with_wiki_markers_select in GIS API
 */
function show_map_with_wiki_markers_select($array,$lat,$lon)
{
    global $global;
    global $conf;
    include_once('openlayers_fns.php');

    ol_js_loaders();
    ol_layers();
    ol_show_wiki_markers_select($array,$lat,$lon);
    ol_functions();
    _shn_print_end_of_map();
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
    ol_functions();
    _shn_print_end_of_map();
}

function _shn_print_end_of_map()
{
    global $global;
    global $conf;
?>	
</script>
	<div id="map" style="width: <?=$conf['gis_width']?>px; height: <?=$conf['gis_height']?>px"></div>
    <table><tr><td valign='top' style="border: 0px;">
<?php
    // Somewhere to report details of OSM File Features via on_feature_hover()
    print "<div id='status_osm'></div>\n";
    print "</td><td valign='top' style=\"border: 0px;\">\n";
    // Somewhere to report whether GeoRSS feed is using cached copy or completely inaccessible
    print "<div id='status_georss'></div>\n";
    // Somewhere to report whether KML feed is using cached copy or completely inaccessible
    print "<div id='status_kml'></div>\n";
    // Somewhere to report if Files are not found
    print "<div id='status_files'></div>\n";
    print "</td></tr></table>\n";
}

// Provides enhanced strstr function for versions of PHP <5.3.0
function strstrbi($haystack, $needle, $before_needle=FALSE, $include_needle=TRUE, $case_sensitive=FALSE)
{
    //Find the position of $needle
    if($case_sensitive) {
        $pos=strpos($haystack,$needle);
    } else {
        $pos=strpos(strtolower($haystack),strtolower($needle));
    }
    //If $needle not found, abort
    if(FALSE==$pos) return FALSE;
    //Adjust $pos to include/exclude the needle
    if($before_needle==$include_needle) $pos+=strlen($needle);
    //get everything from 0 to $pos?
    if($before_needle) return substr($haystack,0,$pos);
    //otherwise, go from $pos to end
    return substr($haystack,$pos);
}

?>
