<?php
/**
* Sahana GIS Admin Menu content
* Please refer to LIST before making major name changes!!!
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$id$
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

	shn_sub_mod_menuopen(_t("GIS Configuration"));
	shn_sub_mod_menuitem("gis_main", _t("GIS General Configuration"), 'admin');
    shn_sub_mod_menuitem("gis_plugin", _t("GIS Plugin Management"), 'admin');
    shn_sub_mod_menuitem("gis_layer", _t("GIS Layer Management"), 'admin');
    shn_sub_mod_menuclose();

?>
