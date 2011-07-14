<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */


$conf['mod_mpr_name']         = _t("Missing Person Registry");
$conf['mod_mpr_menuorder']    = 3;
$conf['mod_mpr_version']      = 1.0;
$conf['mod_mpr_dependencies'] = "";


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


/**
 * Picutre Handling
 */
$conf['mod_mpr_upload_picture_savehandler'] = 'database';
$conf['mod_mpr_upload_pic_handler'] = 'database';


