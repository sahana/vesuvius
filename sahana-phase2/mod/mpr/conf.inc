<?php


/**
 * Main Configuration of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Gives the nice name of the module
 * @global string $conf['mod_mpr_name']
 */
$conf['mod_mpr_name'] = _t("Missing Person Registry");
$conf['mod_mpr_menuorder'] = 3;


/**
 * Sets the number of results shown in search query
 * @global string $conf['mod_mpr']['search']['limit']
 */
$conf['mod_mpr_search_limit'] = 5;
$conf['mod_mpr_search_limit'] = 5;
$conf['mod_mpr_pictures_per_page'] = 6;


/**
 * Sets the upper limit of the location handler
 * @global string $conf['mod_mpr']['location']['upper_limit']
 */
$conf['mod_mpr_location_upper_limit'] = 1;


/**
 * Sets the lower limit of the location handler
 * @global string $conf['mod_mpr']['location']['lower_limit']
 */
$conf['mod_mpr_location_lower_limit'] = 4;
//Missing Person Picture Upload
#$conf['mod_mpr']['upload_picture']['savehandler'] = 'database';
$conf['mod_mpr_upload_picture_savehandler'] = 'database';
$conf['mod_mpr_upload_pic_handler'] = 'database';
#$conf['mod_mpr_upload_pic_handler'] = 'file';
$conf['mod_mpr_dependencies'] = "";
