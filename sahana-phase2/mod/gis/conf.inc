<?php
/* $id$ */

/** Configuration File for GIS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    module
* @subpackage gis
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 *provide a  nice display name for the GIS module
 */
$conf['mod_gis_name'] = _("GIS Mapping");
$conf['mod_gis_menuorder'] = 18;


/**
 * Default GIS plugin to use as GIS.
 * Can be changed via the admin interface for GIS
 * Should be the directory name of the GIS plugin
 */
$conf['mod_gis_dflt'] = 'google_maps';

 # if google maps, map api key
 # key should be registered to hosted url
 $conf['gmap_key'] = 'ABQIAAAAb-bE-ljr4-6Hsb4x92lWhRT2yXp_ZAY8_ufC3CFXhHIE1NvwkxQTjccCsxIjr0poUEEARUZJgolNfw';

/**
 * Default center coordinates of displayed maps
 * Currently set to display Sri Lanka
 * Can be changed via the admin interface for GIS
 */
$conf['mod_gis_center_x'] = '79.5';
$conf['mod_gis_center_y'] = '8.5338';
	 
?>
