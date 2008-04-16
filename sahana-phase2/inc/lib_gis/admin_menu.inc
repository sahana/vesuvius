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
* @version	$id$
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

    global $conf;
	
    shn_sub_mod_menuopen(_t("GIS Configuration"));
    shn_sub_mod_menuitem("gis_main", _t("GIS Defaults Configuration"), 'admin');
  
    if($conf['gis_dflt']=='google_maps')
    	shn_sub_mod_menuitem("gis_google", _t("Google Maps Configuration"), 'admin');
   
    if($conf['gis_dflt']=='openlayers')
    	shn_sub_mod_menuitem("gis_layer", _t("GIS Layer Management"), 'admin');
    if($conf['gis_dflt']=='openlayers' && $conf['gis_ol_wms'])
    	shn_sub_mod_menuitem("gis_mng_wms", _t("Manage WMS Layers"), 'admin');
    if($conf['gis_dflt']=='openlayers' && $conf['gis_ol_georss'])
    	shn_sub_mod_menuitem("gis_mng_georss", _t("Manage GeoRSS Layers"), 'admin');

    shn_sub_mod_menuclose();

?>
