<?php
/**
 * REG Module
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module reg
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


$conf['mod_reg_name']         = _t("Device Manager");  // Defines the name of the module
$conf['mod_reg_menuorder']    = 90;                               // Defines this module's main menu priority 
$conf['mod_reg_dependencies'] = "pop(1.0):rez(1.0)";
$conf['mod_reg_version']      = 1.0;