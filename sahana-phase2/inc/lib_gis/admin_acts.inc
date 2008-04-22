<?php

/**
* Sahana GIS admin menu functionality
* Keeping separate from the main admin file to avoid tampering 
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	GIS
* @version	$id$
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

// Menu Actions
/**
 * Main GIS admin functionality
 */
function shn_admin_gis_main()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_main_settings();
}

/**
 * Google Maps plugin admin functionality
 */
function shn_admin_gis_google()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_google_settings();
}

/**
 * GIS Layers Management Functionality
 */
function shn_admin_gis_layer()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/layer.inc';
    _shn_gis_layer_main_form();
}
 
 
//Form Actions -----------------------

function shn_admin_gis_main_defaults()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_commit_main();
    add_confirmation(_t("Changes were saved"));
    shn_admin_gis_main_settings();
}

function shn_admin_gis_google_commit()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/admin_fns.inc';
    shn_admin_gis_commit_google();
    add_confirmation(_t("Changes were saved"));
    shn_admin_gis_google_settings();
}

function shn_admin_gis_layer_commit()
{
    global $global;
    include_once $global['approot'].'/inc/lib_gis/layer.inc';
    shn_admin_gis_commit_layer();
    add_confirmation(_t("Changes were saved"));
    _shn_gis_layer_main_form();
}

?>

