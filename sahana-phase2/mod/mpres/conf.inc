<?php
/**
 * This is the conf file for the MPRES module.
 *
 * The MPRES module add 2 functions to the MPR module:
 * 1) the ability to import MPR data from email submissions where name and image(s) are sent
 * 2) the ability to import MPR data from email submitted from other applications in the XML/PFIF format (this task must be cronned)
 *
 * PHP version 5.2+
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @package	module
 * @subpackage	mpres
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Gives the nice name of the module
 */
$conf['mod_mpres_name'] = _t("MPR Email Service");

/**
 * Gives the priority order in the main menu when listed
 */
$conf['mod_mpres_menuorder'] = 3;
$conf['mod_mpres_dependencies'] = "mpr";