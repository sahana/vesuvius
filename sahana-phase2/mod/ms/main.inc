<?php

/**Admin Module for MapServer
*
* PHP version 5
* 
* @author       Hasitha Anjana <hasianjana@gmail.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/    	
* @module       MapServer
* @version      $Id: main.inc,v 1.4 2009-08-22 17:17:25 ravithb Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_ajax.inc";
include_once $global['approot']."/mod/ms/main_fns.inc";
include_once $global['approot']."/mod/ms/common_fns.inc"; 
include_once $global['approot']."/mod/ms/map_fns.inc";
include_once $global['approot']."/mod/ms/layer_fns.inc";

function shn_ms_mainmenu()
{
    global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen($conf['mod_ms_name']);
    shn_mod_menuitem("default",_("Home"),$module);
    shn_mod_menuitem("create_map",_("Create New Map"),$module);
    shn_mod_menuitem("add_layer",_("Add Layer to Map"),$module); 
    shn_mod_menuitem("edit_layer",_("Edit Layer"),$module);
    shn_mod_menuitem("list_maps",_("Manage Maps"),$module);
    /**
     * Better moved to bottom of 'Manage Maps' section.
     *
     * shn_mod_menuitem("search_map",_("Search Maps"),$module);
     **/
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


