<?php

/**
* Sahana GIS Admin Menu content
* Please refer to LIST before making major name changes!!!
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: admin_menu.inc,v 1.14 2009-08-22 17:17:25 ravithb Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

    global $conf;
    
    shn_sub_mod_menuopen(_t("GIS Configuration"));
    shn_sub_mod_menuitem("gis_main", _t("GIS Defaults Configuration"), 'admin');
    shn_sub_mod_menuitem("gis_database_classes", _t("GIS Feature Class Management"), 'admin');
    shn_sub_mod_menuitem("gis_database_layers", _t("GIS Layers (Internal) Management"), 'admin');
    shn_sub_mod_menuitem("gis_layers", _t("GIS Layers (External) Management"), 'admin');
    shn_sub_mod_menuitem("gis_feeds", _t("GIS Feeds Management"), 'admin');
    shn_sub_mod_menuitem("gis_files", _t("GIS Files Management"), 'admin');
    shn_sub_mod_menuitem("gis_markers", _t("GIS Markers Management"), 'admin');
    shn_sub_mod_menuitem("gis_projections", _t("GIS Projections Management"), 'admin');
    shn_sub_mod_menuclose();


