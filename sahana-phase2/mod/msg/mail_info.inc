<?php
/**SMTP settings for sending mail 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sri Ganeshan <sri@opensource.lk>
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage msg
*/
// Configuration settings for My sit
global $sit;
// Email Settings
$sit['from_name'] = "sri"; // from email name
$sit['from_email'] = "sri@opensource.lk"; // from email address
//$sit['reply_tol']('kushi223344@yahoo.com', 'sri')
// Just in case we need to relay to a different server, 
// provide an option to use external mail server.

$sit['smtp_mode'] = "enabled"; 
$sit['smtp_host'] = "";
$sit['smtp_port'] = 25;
$sit['smtp_username'] ="";
$sit['smtp_password'] ="";

