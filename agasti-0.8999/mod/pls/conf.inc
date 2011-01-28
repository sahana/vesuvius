<?php
/**
 * This is the conf file for the PLS module.
 *
 * This module provides "Person Locator Services" and is a web services only module.
 *
 * PHP version 5.2+ (compiled with imap support)
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Greg Miernicki
 * @package	module
 * @subpackage	pls
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

$conf['mod_pls_name']         = _t("Person Locator Services");   // Defines the name of the module
$conf['mod_pls_menuorder']    = 99;                              // Defines this module's main menu priority 
$conf['mod_pls_dependencies'] = "pop(0.1):lpf(0.1)";
$conf['mod_pls_version']      = 1.0;