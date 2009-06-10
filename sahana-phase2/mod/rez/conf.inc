<?php
/**
 * modRez conf
 *
 * @package	module
 * @subpackage	rez
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * Gives the nice name of the module
 */
$conf['mod_rez_name'] = _t("Resources");

/**
 * Gives the priority order in the main menu when listed
 */
$conf['mod_rez_menuorder'] = 4;
$conf['mod_rez_dependencies'] = "";

/**
 * Set to 1 (true) the main menu will be rendered before the module menu
 */
$conf['mod_rez_mainmenu_before_modmenu'] = 1;