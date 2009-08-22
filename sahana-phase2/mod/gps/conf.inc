<?php

/* $id$ */

/** Configuration File for GPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author     Sriganeshan <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    module
* @subpackage gis
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $conf;

/**
 * nice display name for the GPS module
 */
$conf['mod_gps_name'] = _("GPS Interface");
$conf['mod_gps_menuorder'] = 3;

/**
 * Nice name for admin module
 */
$conf['mod_gps_adm_name']=_("GPS");

/**
 * Folder that contains gps data files
 */
$conf['mod_gps_data_folder'] = 'data';

/**
 * Files for temporarily storing dynamic markers
 */
$conf['input']= "../www/tmp/input.txt";
$conf['output']= "../www/tmp/output.txt";
   
/**
 * GPX schema location
 */
$conf['schema_location']="./gpx_schema.xsd";


