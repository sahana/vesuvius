<?php

/** Configuration File for GIS
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* 
* @author       Mifan Careem <mifan@opensource.lk>
* @author       Fran Boon <flavour@partyvibe.com>
* @version      $id$;
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.sourceforge.net    	
* @subpackage   gis
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $conf;

/**
 * Default GIS plugin to use as GIS.
 * Should be the directory name of the GIS plugin
 */
$conf['gis_dflt'] = 'openlayers';

/**
 * Default center coordinates of displayed maps
 * Currently set to display Sri Lanka as default
 */
$conf['gis_center_x'] = '79.4'; // Longitude
$conf['gis_center_y'] = '6';    // Latitude
$conf['gis_zoom'] = '6';

/**
 * Folder that contains gis data files
 */
$conf['gis_data_folder'] = 'data';

/**
 * Map dimensions
 */
$conf['gis_height']=600;
$conf['gis_width']=760;

/**
 * Folder to store custom markers
 * given from sahana root
 */
$conf['gis_marker_folder'] = 'theme/default/img/';

/**
 * Folder to store wiki images
 * given from sahana root
 */
$conf['gis_image_folder'] = 'www/tmp/';

/**
 * Folder to store temp images of maps
 * given from sahana root
 */
$conf['gis_tmp_image_folder'] = 'theme/default/img/';

/**
 * if using Google maps, either as Plugin or within OpenLayers 
 * map API key (should be registered to hosted url. Default is localhost)
 */
$conf['gis_google_key']='ABQIAAAAb-bE-ljr4-6Hsb4x92lWhRT2yXp_ZAY8_ufC3CFXhHIE1NvwkxQTjccCsxIjr0poUEEARUZJgolNfw';

/**
 * Configuration for GIS Catalogue
 */
  
/**
 * Switches for OpenStreetMap
 * 0 for off; 1 for on
 */
$conf['gis_ol_osm']='0';
$conf['gis_ol_osm_mapnik']='1';
$conf['gis_ol_osm_tiles']='0';
 
/**
 * Switches for Googlemaps
 * 0 for off; 1 for on
 */
$conf['gis_ol_google']='0';
$conf['gis_ol_google_hybrid']='1';
$conf['gis_ol_google_maps']='0';
$conf['gis_ol_google_sat']='0';
 
/**
 * Switches for MS Virtual Earth
 * 0 for off; 1 for on
 */
$conf['gis_ol_virtualearth']='0';
$conf['gis_ol_virtualearth_hybrid']='1';
$conf['gis_ol_virtualearth_maps']='0';
$conf['gis_ol_virtualearth_aerial']='0';

/**
 * Switch for MultiMap
 * 0 for off; 1 for on
 */
$conf['gis_ol_multimap']='0';
$conf['gis_multimap_key']='metacarta_04';
 
/**
 * Switches for Yahoo! maps
 * 0 for off; 1 for on
 */
$conf['gis_ol_yahoo']='0';
$conf['gis_ol_yahoo_hybrid']='1';
$conf['gis_ol_yahoo_maps']='0';
$conf['gis_ol_yahoo_sat']='0';
$conf['gis_yahoo_key']='euzuro-openlayers';
  
/**
 * Counter for OpenLayers WMS layers
 * 0 for off; positive integer for how many layers are on
 */
$conf['gis_ol_wms']='1';
 
$conf['gis_ol_wms_1_description'] = 'A Free low-resolution Vector Map of the whole world';
$conf['gis_ol_wms_1_name'] = 'VMap0';
$conf['gis_ol_wms_1_type'] = 'base';
$conf['gis_ol_wms_1_url'] = 'http://labs.metacarta.com/wms/vmap0';
$conf['gis_ol_wms_1_layers'] = 'basic';
$conf['gis_ol_wms_1_img'] = '';
$conf['gis_ol_wms_1_transparency'] = '0';
$conf['gis_ol_wms_1_min'] = '';
$conf['gis_ol_wms_1_max'] = '';
 
/**
 * Counter for OpenLayers GeoRSS layers
 * 0 for off; positive integer for how many layers are on
 */
$conf['gis_ol_georss'] ='0';

$conf['gis_ol_georss_1_description'] = '';
$conf['gis_ol_georss_1_name'] = 'Earthquakes';
$conf['gis_ol_georss_1_url'] = 'http://earthquake.usgs.gov/eqcenter/catalogs/eqs7day-M2.5.xml';

$conf['mod_gis_dependencies'] = "";

?>
