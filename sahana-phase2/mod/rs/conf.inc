<?php


/**
 * Main Configuration of the Catalogue System. 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Gives the nice name of the module
 * @global string $conf['mod_cs_name']
 */
#global $conf;

$conf['mod_rs_name'] = _t("Reporting System");
$conf['mod_rs_menuorder'] = 19;
$conf['mod_rs_dependencies'] = "";
$conf['mod_rs_chart_update_interval'] = 30;

