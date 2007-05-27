<?php
/**
 * Sahana security library constants
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

define(LOGGEDIN,"logged in");
define(LOGGEDOUT,"logged out");

define(DENIED,1);
define(ALLOWED,2);

define(ADMIN,1);
define(MAINOPS,2);
define(ORGHEAD,3);
define(TRUSTED,4);
define(REGISTERED,5);
define(ANONYMOUS,6);
$crud_arr= array(
			"delete_arr"=>array(1,3,5,7,9,11,13,15),
			"update_arr"=>array(2,3,6,7,10,11,14,15),
			"read_arr"=>array(4,5,6,7,12,13,14,15),
			"create_arr"=>array(8,9,10,11,12,13,14,15)	
			);
