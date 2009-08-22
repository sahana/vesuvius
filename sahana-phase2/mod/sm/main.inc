<?php

/**
* Main home page of the Situation Mapping Module
* PHP version 5
*
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @author       Richard Smith <s0459387@sms.ed.ac.uk>
* @package  Sahana - http://sahana.sourceforge.net
* @module       sm
* @version      $id$
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/mod/sm/main_fns.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_security/lib_acl.inc";

/**
 * Main SM menu functionality
 */
function shn_sm_mainmenu(){
    global $global;
    global $conf;
    $module = $global['module'];
    
    shn_mod_menuopen($conf['mod_sm_name']);
    shn_mod_menuitem("default",_t("Home"),$module);
    shn_mod_menuitem("swik",_t("View Situation Map"),$module);
    shn_mod_menuitem("awik",_t("Add New Situation"),$module);
    //shn_mod_menuitem("ewik",_t("Edit Situation"),$module);
    shn_sub_mod_menuopen(_t("Situation Analysis"));
    shn_mod_menuitem("analysis_radius",_t("Radius"),$module);
    shn_mod_menuitem("analysis_class",_t("Feature Class"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


