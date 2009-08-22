<?php

/** Configuration File for GIS
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author   	Mifan Careem <mifan@opensource.lk>
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @package    	Sahana - http://sahana.sourceforge.net
* @subpackage 	sm
* @version		$id$
* @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * Provide a  nice display name for the Situation Mapping module
 */
global $conf;

$conf['mod_sm_name'] = _t("Situation Awareness");
$conf['mod_sm_menuorder'] = 2;

/**
 * folder to store wiki images
 * given from sahana root
 */
$conf['mod_sm_image_folder'] = 'www/tmp/';

