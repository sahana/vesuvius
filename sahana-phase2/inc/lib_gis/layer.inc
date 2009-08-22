<?php

/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: layer.inc,v 1.9 2009-08-22 17:17:25 ravithb Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Layer Catalog management
 * Tabbed functionality for separate layers
 */
function shn_gis_layer_main()
{
    _shn_gis_layer_main_form();
}

function _shn_gis_layer_main_form()
{
    global $global;
    global $conf;
    if($conf['gis_dflt']=='google_maps') {
        include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
        shn_admin_gis_google_settings();
    } else
 {
        shn_form_fopen('gis_layers_commit',null,array('tab'=>'float'));
        _shn_gis_layer_load_admin_forms();
        shn_form_drawtab();
        shn_form_submit(_t('Save Settings'));
        shn_form_fclose();
    }
}
        
/**
 * Load layer classes admin sections as tabs 
 */
function _shn_gis_layer_load_admin_forms()
{
    global $global;
    $gis_layer_dir=$global['approot'].'/inc/lib_gis/layers/';
    $dir = opendir($gis_layer_dir);

    while($file = readdir($dir)){
        if(!is_dir($file)){
            include_once $global['approot'].'/inc/lib_gis/layers/'.$file;
            $class = spliti('\.',$file);
            $classname = $class[0];
            $layer_obj = new $classname();
            $layer_obj->print_form();
        }
    }
}

/**
 * Commit Layers configuration
 */
function _shn_admin_gis_commit_layers()
{
    global $global;
    global $conf;
    $db = $global['db'];
    $gis_layer_dir=$global['approot'].'/inc/lib_gis/layers/';
    $dir = opendir($gis_layer_dir);
	
    while($file = readdir($dir)){
        if(!is_dir($file)){
            include_once ($global['approot'].'/inc/lib_gis/layers/'.$file);
            $class = spliti('\.',$file);
            $classname = $class[0];
            $layer_obj = new $classname();
            $layer_obj->commit_values();
        }
    }
}



