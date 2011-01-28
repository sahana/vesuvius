<?php
/**
 * Module >> CAM
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module
 * @subpackage cam
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

$conf['mod_cam_name']         = _t("Cam Test");  // Defines the name of the module
$conf['mod_cam_menuorder']    = 2;               // Defines this module's main menu priority
$conf['mod_cam_dependencies'] = "cam";           // Requires POP module for email and REZ for displaying some page content
//$conf['mod_cam_hide_in_menu'] = true;
$conf['mod_cam_version']      = 0.0;
