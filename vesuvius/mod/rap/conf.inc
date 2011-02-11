<?php
/**
 * Module >> Report a Person :: Main Controller 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module
 * @subpackage rap
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

$conf['mod_rap_name']         = _t("Report a Person");  // Defines the name of the module
$conf['mod_rap_menuorder']    = 10;                      // Defines this module's main menu priority
$conf['mod_rap_dependencies'] = "pop(1.0)";
$conf['mod_rap_version']      = 1.0;