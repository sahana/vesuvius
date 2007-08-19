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
 
define('SALT_LENGTH', 9);
define('LOCK', 900);
define(LOGGEDIN,"logged in");
define(LOGGEDOUT,"logged out");

define(DENIED,1);
define(ALLOWED,2);

define(ANONYMOUS_USER,-2);

define(ADMIN,1);
define(OEMADMIN,2);
define(STSUSER,3);
define(SRSUSER,4);
define(ANONYMOUS,5);
$crud_arr= array(
			"delete_arr"=>array(1,3,5,7,9,11,13,15),
			"update_arr"=>array(2,3,6,7,10,11,14,15),
			"read_arr"=>array(4,5,6,7,12,13,14,15),
			"create_arr"=>array(8,9,10,11,12,13,14,15)	
			);
define    ($PWDPOLICY,"	<h4>Password must adhere to following rules:</h4>
    1. Only numbers and letters.<br />
    2. Minimum length is 8.<br />
    3. At least one number and one letter in the expression.<br />
    4. At least one uppercase letter and one lowercase letter.<br />"); 