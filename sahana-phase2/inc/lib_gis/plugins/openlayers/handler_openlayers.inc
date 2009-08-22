<?php

/**
* $id$;
* Openlayers Plugin for GIS 
*
* PHP version 5
*
* Sahana - http://sahana.sourceforge.net
* @author     Mifan Careem <mifan@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
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
    //global $global;
    global $conf;
    require_once('openlayers_fns.php');

    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map();
    ol_onload_start();
    ol_layers_all();
    ol_onload_fin();
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
    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map();
    ol_onload_start();
    ol_layers_all();
    ol_onload_fin();
    ol_viewport_save($lat,$lon,$zoom);
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show map with marker addition event
 * ability to enter markers on map
 * called by shn_gis_add_marker_map_form in GIS API
 */
//function show_add_marker_map($name)
//{
//    global $global;
//    global $conf;
//    include_once('openlayers_fns.php');

//    ol_js_loaders();
//    ol_layers();
//    ol_add_marker($name);
//    ol_functions();
//    _shn_print_end_of_map();
//}

/**
 * Show map with markers
 * called by shn_gis_map_with_markers in GIS API
 */
function show_map_with_markers($array)
{
    //global $global;
    //global $conf;
    //$db=$global['db'];
    include_once('openlayers_fns.php');

    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map();
    ol_onload_start();
    ol_layers_all();
    ol_show_markers($array);
    ol_onload_fin();
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show map with wiki markers
 * called by shn_gis_map_with_wiki_markers in GIS API
 */
//function show_map_with_wiki_marker($array)
//{
//    global $global;
//    global $conf;
//    include_once('openlayers_fns.php');

//    ol_js_loaders();
//    ol_layers();
//    ol_show_wiki_markers($array);
//    ol_functions();
//    _shn_print_end_of_map();
//}

/**
 * Show map with wiki markers
 * + allow updating of form fields by selection of marker
 * called by shn_gis_map_with_wiki_markers_select in GIS API
 */
function show_map_with_wiki_markers_select($array,$lat,$lon)
{
    //global $global;
    //global $conf;
    include_once('openlayers_fns.php');

    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map();
    ol_onload_start();
    ol_layers_all();
    ol_show_wiki_markers_select($array,$lat,$lon);
    ol_onload_fin();
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show map with custom markers
 * called by shn_gis_density_map in GIS API
*/
function show_map_with_custom_markers($array)
{
    //global $global;
    //global $conf;
    include_once('openlayers_fns.php');

    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map();
    ol_onload_start();
    ol_layers_all();
    ol_show_custom_markers($array);
    ol_onload_fin();
    ol_functions();
    _shn_print_end_of_map();
}

/**
 * Show map with marker addition event
 * ability to add single geometry
 * called by shn_gis_add_marker_map_form in GIS API
 */
function show_map_add_single_geometry($icon, $types)
{
    require_once('openlayers_fns.php');
        
    $tool_options = 1;
        
    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map($tool_options);
    ol_onload_start();
    ol_layers_all();
    ol_layers_features();    
    ol_onload_controls($tool_options);
    ol_onload_fin();
    ol_add_feature('Feature', $icon);
    _ol_generate_add_feature();
    ol_functions();
    _shn_print_end_of_map();   
}

/**
 * Show map with features from internal GIS
 * (make sure features have most/all key values especially uuid
 * if you want them to be editable).
 * 
 * See wiki on GIS API for details of $feature attribute.
 * 
 * @global <type> $global
 * @param <type> $features
 */
 function show_map_with_features($features)
{
    global $global;
    require_once('openlayers_fns.php');

    $tool_options = 2;
     
    _shn_print_status();
    ol_js_loaders();     
    _shn_print_start_of_map($tool_options);
    ol_onload_start();
    ol_layers_all();
    ol_show_features_markers($features);
    ol_onload_controls($tool_options);
    ol_onload_fin();
    _ol_generate_add_feature_with_popup();
    ol_functions();
    _shn_print_end_of_map(); 
}

/**
 * Starts Openlayers and suporting functions script.
* 
 * $options:
 * 1 - controls to add (point/line/polygon) on map but not to create feature in db
 * 2 - controls to add select, move, add (point/line/polygon) and create feature in db
 * 
 * @global <type> $conf
 * @param <type> $options
 */
function _shn_print_start_of_map($options)
{
    global $conf;
?> 
    <fieldset>
    <div id="outer_map" style="width: 600px; height: 800px; background-color: #FFFFFF"> 
<?php 
        switch($options){
            
            case 1:
               _shn_print_map_toolbar1();
                break;
            
            case 2:
              _shn_print_map_toolbar2(); 
                break;
            
            default:
                // no toolbar
                break;
        }
?>
        <div style="float: left; width: 100%;"></div>
        <div id="map" style="border: 2px solid black;  background-color: #FFFFFF"></div> 
        </fieldset>
    </div>
<?php
}
 
/**
 * Show partial toolbar
 */
function _shn_print_map_toolbar1()
 {
 ?>
    <div id='gis_map_toolbar' >
        <fieldset id='gis_map_toolbar_fieldset' style="border: 1px solid ; padding: 5px; padding-bottom:2px;">

            <div id="gis_map_toolbar_default">
                <span title="<?php echo  _t('Expand Map') ?>"><a onclick="shn_gis_map_expand()" alt="<?php echo  _t('Full screen map')?>"><div id="gis_map_icon_expand" style="width: 24px; height: 22px;"></div></a></span>
            </div>
            <div id="gis_map_toolbar_manipulate">
                <span title="<?php echo  _t('Navigate') ?>"><a onclick="shn_gis_map_control_navigate()" alt="<?php echo  _t('Navigate')?>"><div id="gis_map_icon_select" style="width: 24px; height: 22px;"></div></a></span>
                <span title="<?php echo  _t('Add Point')?>"><a onclick="shn_gis_map_control_add_point()" alt="<?php echo  _t('Add Point')?>"><div id="gis_map_icon_addpoint" style="width: 24px; height: 22px;"></div></a></span>
                <span title="<?php echo  _t('Add Line')?>"><a onclick="shn_gis_map_control_add_line()" alt="<?php echo  _t('Add Line')?>"><div id="gis_map_icon_addline" style="width: 24px; height: 22px;"></div></a></span>
                <span title="<?php echo  _t('Add Area')?>"><a onclick="shn_gis_map_control_add_polygon()" alt="<?php echo  _t('Add Area')?>"><div id="gis_map_icon_addpolygon" style="width: 24px; height: 22px;"></div></a></span>
                <span title="<?php echo  _t('Toggle Freehand Draw')?>"><a onclick="shn_gis_map_control_freehand()" alt="<?php echo  _t('Toggle Freehand Draw')?>"><div id="gis_map_icon_freehand" style="width: 24px; height: 22px;"></div></a></span>
                <span title="<?php echo  _t('Mode Description')?>" id="gis_map_icon_descripion"></span>
            </div>
        </fieldset>
    </div>
<?php
}
 
/**
 * Show full toolbar
 */
function _shn_print_map_toolbar2()
 {
 ?>  
    <div id='gis_map_toolbar'>
        <fieldset id='gis_map_toolbar_fieldset' style="border: 1px solid ; padding: 5px; padding-bottom:2px;">
        
        <div id="gis_map_toolbar_default">
            <span title="<?php echo  _t('Expand Map') ?>"><a onclick="shn_gis_map_expand()" alt="<?php echo  _t('Full screen map')?>"><div id="gis_map_icon_expand" style="width: 24px; height: 22px;"></div></a></span>
        </div>
        <div id="gis_map_toolbar_manipulate">
            <span title="<?php echo  _t('Select Features') ?>"><a onclick="shn_gis_map_control_select()" alt="<?php echo  _t('Select Features')?>"><div id="gis_map_icon_select" style="width: 24px; height: 22px;"></div></a></span>
            <span title="<?php echo  _t('Move Features')?>"><a onclick="shn_gis_map_control_drag()" alt="<?php echo  _t('Move Features')?>"><div id="gis_map_icon_drag" style="width: 24px; height: 22px;"></div></a></span>
            <span title="<?php echo  _t('Add Point')?>"><a onclick="shn_gis_map_control_add_point()" alt="<?php echo  _t('Add Point')?>"><div id="gis_map_icon_addpoint" style="width: 24px; height: 22px;"></div></a></span>
            <span title="<?php echo  _t('Add Line')?>"><a onclick="shn_gis_map_control_add_line()" alt="<?php echo  _t('Add Line')?>"><div id="gis_map_icon_addline" style="width: 24px; height: 22px;"></div></a></span>
            <span title="<?php echo  _t('Add Area')?>"><a onclick="shn_gis_map_control_add_polygon()" alt="<?php echo  _t('Add Area')?>"><div id="gis_map_icon_addpolygon" style="width: 24px; height: 22px;"></div></a></span>
            <span title="<?php echo  _t('Toggle Freehand Draw')?>"><a onclick="shn_gis_map_control_freehand()" alt="<?php echo  _t('Toggle Freehand Draw')?>"><div id="gis_map_icon_freehand" style="width: 24px; height: 22px;"></div></a></span>
            <span title="<?php echo  _t('Mode Description')?>" id="gis_map_icon_descripion"></span>
        </div>
        </fieldset>
    </div>
<?php
}

/**
 * status_osm - Somewhere to report details of OSM File Features via on_feature_hover()
 * status_georss -  Somewhere to report whether GeoRSS feed is using cached copy or completely inaccessible
 * status_kml -  Somewhere to report whether KML feed is using cached copy or completely inaccessible
 * status_files - Somewhere to report if Files are not found
 * 
 */            
function _shn_print_status()
{
?>
    <table>
        <tr>
            <td valign='top' style="border: 0px;">
                <div id='status_osm'></div>
            </td>
            <td valign='top' style="border: 0px;">
                <div id='status_georss'></div>
                <div id='status_kml'></div>
                <div id='status_files'></div>
            </td>
        </tr>
    </table>
<?php
}

/**
 * Ends Openlayers
 */            
function _shn_print_end_of_map()
{
?>
    </script>
    <table>
        <tr>
            <td valign='top' style="border: 0px;">
                <div id='status_osm'></div>
            </td>
            <td valign='top' style="border: 0px;">
                <div id='status_georss'></div>
                <div id='status_kml'></div>
                <div id='status_files'></div>
            </td>
        </tr>
    </table>
<?php
}



// this funtion is to draw polyline
function show_map_polylines($cords,$title=null)
{
    //global $global;
    global $conf;
    require_once('openlayers_fns.php');

    _shn_print_status();
    ol_js_loaders();
    _shn_print_start_of_map();
    ol_onload_start();
    ol_layers_all();
    ol_show_cap_markers($cords, $title);
    ol_onload_controls(0);
    ol_onload_fin();
    ol_functions();
     _shn_print_end_of_map();
	
} 










