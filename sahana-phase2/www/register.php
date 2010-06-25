<?php
/**
 * REG Module ~ This module allows devices to register users and for web service authentication credentials.
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module reg
 * @version    0.2
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


// required libraries
require("../conf/sysconf.inc.php");
require("../3rd/adodb/adodb.inc.php");
require("../inc/handler_db.inc");
require("../inc/lib_uuid.inc");



// figure out what to do and call the functions to do it
$action = isset($_GET['action']) ? $_GET['action'] : "register";

if($action == "confirm") {
	$api               = isset($_GET['API_KEY'])      ? $_GET['API_KEY']      : null;
	$confirmation_code = isset($_GET['CONFIRM_CODE']) ? $_GET['CONFIRM_CODE'] : null;
	confirm();
}
else if($action != "register") {
	error("Invalid action request.");
}
else {
	$api      = isset($_GET['API_KEY'])       ? $_GET['API_KEY']       : null;
	$password = isset($_GET['PASSWORD'])      ? $_GET['PASSWORD']      : null;
	$email    = isset($_GET['EMAIL_ADDRESS']) ? $_GET['EMAIL_ADDRESS'] : null;
	$name     = isset($_GET['FULL_NAME'])     ? $_GET['FULL_NAME']     : null;
}
if(!isValidKeyPassword()) {
	error("invalid API_KEY or PASSWORD string(s).");
} 
else if(!validEmail()) {
	error("invalid email address.");
}
else if(isActive()) {
	error("API_KEY already active.");
}
else if(!hasRegistered()) {
	reg();
	email();
}
else if(isGreaterThanOneDay()) {
	del();
	reg();
	email();
}
else {
	error("Registered this API_KEY less than 24 hours ago. Use the confirmation code to activate it.");
}



// END EXECUTION   ///////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * Check for valid conformation code
 */
function confirm() {
	global $global;
	$query  = "SELECT * FROM reg WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
	if($row = $result->FetchRow()) {
		if($confirmation_code == $row['confirmation_code']) {
			addUser();
			addDevice();
			confirmationPassed();
		} else {
			confirmationFailedBadCode();
		}
	} else {
		confirmationFailedBadKey();
	}
}



/**
 * Add newly confimred user to Sahana.
 */
function addUser() {
}



/**
 * Add newly confimred user to Sahana.
 */
function addDevice() {
}



/**
 * Passed the user along to a page in the module reporting confirmation success.
 */
function confirmationPassed() {
	header("Location: /index.php?mod=rez&act=default&page_id=-1");
}



/**
 * Passed the user along to a page in the module reporting confirmation failure for a bad confirmation code.
 */
function confirmationFailedBadCode() {
	header("Location: /index.php?mod=rez&act=default&page_id=-2");
}



/**
 * Passed the user along to a page in the module reporting confirmation failure for a bad API_KEY.
 */
function confirmationFailedBadKey() {
	header("Location: /index.php?mod=rez&act=default&page_id=-3");
}



/**
 * Deletes a registration.
 */
function del() {
	global $global;
	$query  = "DELETE FROM reg WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
}



/**
 * Creates a new registration.
 */
function reg() {
	global $global;
	$uuid   = shn_create_uuid();
	$code   = md5(uniqid(rand(), true));
	$query  = "INSERT INTO reg (`p_uuid`, `domain`, `API_KEY`, `PASSWORD`, `EMAIL_ADDRESS`, `FULL_NAME`, `last_attempt`, `is_active`, `confirmation_code`)
	           VALUES ('".$uuid."', 'DEVICE', '".$api."', '".$password."', '".$email."', '".$name."', CURRENT_TIMESTAMP, '0', '".$code."');";
	$result = $global['db']->Execute($query);
}



/**
 * Emails the newly registered user a confirmation link.
 */
function email() {
	require("../mod/pop/class.pop.php");
	$p = new pop();
	$body = "Here is a test message.";
	$p = new pop();
	$subject  = "Please confirm the registration of your device. #".$api;
	$bodyHTML = "Thank you for registering your device, ".$name.".<br><br> You must click on this link: <a href=\"\"></a> in order for the registration process to be completed. Afterwards, you will be able to login to the site with the following credentials.<br><br>username: ".$."";
	$p->sendMessage($email, $name, $subject, $body, $body);
}




/**
 * Report error message.
 */
function error($msg) {
	echo '{"ERROR":"'.$msg.'"}';
}



/**
 * Are the API_KEY and PASSWORD legal?
 */
function isValidKeyPassword() {
	if((strlen($api) > 60) || (strlen($password) > 60) || ($api == null) || ($password == null)) {
		return false;
	} else {
		return true;
	}
}




/**
 * Has this API_KEY attempted registration before?
 */
function hasRegistered() {
	global $global;
	$query  = "SELECT * FROM reg WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
	if($row = $result->FetchRow()) {
		return true;
	} else {
		return false;
	}
}



/**
 * Check if an API_KEY has attempted to register in the past 24 hours
 */
function isGreaterThanOneDay() {
	global $global;
	$query  = "SELECT UNIX_TIMESTAMP(`last_attempt`) FROM reg WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
	$row    = $result->FetchRow();
	$last   = $row['last_attempt'];
	$time   = time();
	if(($last+(24*60*60)) > $time) {
		return true
	} else {
		return false;
	}
}



/**
 * Check if an API_KEY is active (confirmed)
 */
function isActive($api) {
	global $global;
	$query  = "SELECT * FROM reg WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
	$row    = $result->FetchRow();
	$active = $row['is_active'];
	if($active == "1") {
		return true;
	} else {
		return false;
	}
}



/**
 * Validate an email address.
 * Provide email address (raw input)
 * Returns true if the email address has the email 
 * address format and the domain exists.
 * borrowed from: http://goo.gl/ufhg
 */
function validEmail($email) {
	$isValid = true;
	$atIndex = strrpos($email, "@");
	if(is_bool($atIndex) && !$atIndex) {
		$isValid = false;
	} else {
		$domain    = substr($email, $atIndex+1);
		$local     = substr($email, 0, $atIndex);
		$localLen  = strlen($local);
		$domainLen = strlen($domain);
		if($localLen < 1 || $localLen > 64) { 
			// local part length exceeded
			$isValid = false;
		} else if($domainLen < 1 || $domainLen > 255) {
			// domain part length exceeded
			$isValid = false;
		} else if($local[0] == '.' || $local[$localLen-1] == '.') {
			// local part starts or ends with '.'
			$isValid = false;
		} else if(preg_match('/\\.\\./', $local)) {
			// local part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain)) {
			// character not valid in domain part
			$isValid = false;
		} else if(preg_match('/\\.\\./', $domain)) {
			// domain part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local))) {
			// character not valid in local part unless 
			// local part is quoted
			if (!preg_match('/^"(\\\\"|[^"])+"$/', str_replace("\\\\","",$local))) {
				$isValid = false;
			}
		}
		if($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A"))) {
			// domain not found in DNS
			$isValid = false;
		}
	}
	return $isValid;
}