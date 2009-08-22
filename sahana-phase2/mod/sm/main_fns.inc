<?php
/**
* Main Functionality actions of the SM Module
* 
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
* @package      module
* @subpackage   sm
* @version      $id$
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/inc/lib_validate.inc";
require_once $global['approot']."/mod/sm/wm_fns.inc";

//Include home description
include_once $global['approot']."/mod/sm/home.inc";


/**
* Feature Map
*/
function shn_sm_swik()
{
    shn_sm_show_features_map();
}

/**
* Add Feature Sequence
*/
function shn_sm_awik()
{
    shn_sm_feature_add_seq();
}

/**
* Analysis map: Radius
*/
function shn_sm_analysis_radius()
{
    shn_sm_analysis_radius_seq();
}

/**
* Analysis map: Feature Class
*/
function shn_sm_analysis_feature_class()
{
    shn_sm_analysis_feature_class_seq();
}

// TO GO
function shn_sm_radius_analyse()
{
    shn_sm_radius_analyse_process();
}


