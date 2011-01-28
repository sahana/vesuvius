<?php
/**
 * LPF Library Configuration
 *
 * PHP version 5.3+
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Greg Miernicki <g@miernicki.com>
 * @package	lpf
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

$conf['mod_lpf_name']         = _t("LPF Library");  // Defines the name of the module
$conf['mod_lpf_menuorder']    = 3;                  // Defines this module's main menu priority 
$conf['mod_lpf_dependencies'] = "";                 // Doesnt depend on other modules (but is depending on by others)
$conf['mod_lpf_version']      = 0.3;