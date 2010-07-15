<?php
/**
 * REG Module ~ This module allows devices to register for web service authentication credentials and user accounts.
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

// We can never show errors or else device registration will fail
ini_set( "display_errors", 0);
error_reporting(0);

// define app root since we are outside the main execution thread~index.php
$global['approot'] = getcwd()."/../";

// required libraries
require($global['approot']."/conf/sysconf.inc.php");
require($global['approot']."/3rd/adodb/adodb.inc.php");
require($global['approot']."/inc/handler_db.inc");
require($global['approot']."/inc/lib_uuid.inc");
require($global['approot']."/inc/lib_security/lib_auth.inc");


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
else if(!validEmail($email)) {
	error("invalid email address.");
}
else if(isActive()) {
	error("API_KEY already active.");
}
else if(!hasRegistered()) {
	reg();
}
else if(isGreaterThanOneDay()) {
	del();
	reg();
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
	global $api;
	global $confirmation_code;
	global $global;
	$query  = "SELECT * FROM reg WHERE API_KEY = '".mysql_real_escape_string($api)."';";
	$result = $global['db']->Execute($query);
	if($row = $result->FetchRow()) {
		if($row['is_active'] == 1) {
			confirmationAlreadyActive();
		} else if($confirmation_code == $row['confirmation_code']) {
			addUser($row['EMAIL_ADDRESS'], $row['PASSWORD'], $row['FULL_NAME']);
			addDevice($row['p_uuid'], $row['API_KEY'], $row['PASSWORD'], $row['SECRET_CODE']);
			changeStatus($row['API_KEY']);
			$old_uuid = $row['p_uuid'];
			$q2   = "SELECT * FROM users WHERE user_name = '".$row['EMAIL_ADDRESS']."';";
			$r2   = $global['db']->Execute($q2);
			$row2 = $r2->FetchRow();
			$new_uuid = $row2['p_uuid'];
			updateUuids($old_uuid, $new_uuid);
			confirmationPassed();
		} else {
			confirmationFailedBadCode();
		}
	} else {
		confirmationFailedBadKey();
	}
	die(); // we are done :)
}



/**
 * Add newly confimred user to Sahana.
 */
function addUser($email, $password, $name) {
	// $ret = shn_auth_add_user($_POST['account_name'],$_POST['user_name'],$_POST['password'],$role=REGISTERED,null);
	$ret = shn_auth_add_user($name, $email, $password, $role=REGISTERED, null);
}



/**
 * Add newly confimred user to Sahana.
 */
function addDevice($uuid, $api, $password, $secret) {
	global $global;
	// $sql="insert into ws_keys(p_uuid,domain,api_key,password,secret) values('{$user}','{$domain}','{$key}','{$pwd}','{$secret}')";
	$query = "insert into ws_keys(
		`p_uuid`,
		`domain`,
		`api_key`,
		`password`,
		`secret`
	) values(
		'".$uuid."',
		'DEVICE',
		'".$api."',
		'".$password."',
		'".$secret."'
	)";
	$result = $global['db']->Execute($query);
}



/**
 * change reg status to active
 */
function changeStatus($api) {
	global $global;
	$query = "UPDATE reg SET is_active = 1 WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
}



/**
 * Updated uuid's of activated user
 */
function updateUuids($old_uuid, $new_uuid) {
	global $global;
	$q1 = "UPDATE ws_keys SET p_uuid = '".$new_uuid."' WHERE p_uuid = '".$old_uuid."';";
	$r1 = $global['db']->Execute($q1);
	$q2 = "UPDATE reg SET p_uuid = '".$new_uuid."' WHERE p_uuid = '".$old_uuid."';";
	$r2 = $global['db']->Execute($q2);
}



/**
 * Make the base url of the links we use
 */
function makeBaseUrl() {
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace("register.php", "", $link);
	return $link;
}



/**
 * Passed the user along to a page in the module reporting confirmation success.
 */
function confirmationPassed() {
	header("Location: ".makeBaseUrl()."index.php?mod=rez&act=default&page_id=-1");
}



/**
 * Passed the user along to a page in the module reporting confirmation failure for a bad confirmation code.
 */
function confirmationFailedBadCode() {
	header("Location: ".makeBaseUrl()."index.php?mod=rez&act=default&page_id=-2");
}



/**
 * Passed the user along to a page in the module reporting confirmation failure for a bad API_KEY.
 */
function confirmationFailedBadKey() {
	header("Location: ".makeBaseUrl()."index.php?mod=rez&act=default&page_id=-3");
}



/**
 * Passed the user along to a page showing that they already confirmed this registration
 */
function confirmationAlreadyActive() {
	header("Location: ".makeBaseUrl()."index.php?mod=rez&act=default&page_id=-4");
}



/**
 * Deletes a registration.
 */
function del() {
	global $api;
	global $global;
	$query  = "DELETE FROM reg WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
}



/**
 * Creates a new registration.
 */
function reg() {
/*
	how mod/ws generates the codes:

	$key  = md5(uniqid(rand(), true));
	$pwd  = md5(uniqid(rand(), true));
	$code = md5(uniqid(rand(), true));
*/
	global $api;
	global $password;
	global $email;
	global $name;
	global $global;
	$uuid         = shn_create_uuid();
	$secret       = md5(uniqid(rand(), true));
	$confirmation = md5(uniqid(rand(), true));
	$query  = "
		INSERT INTO reg (
			`p_uuid`, 
			`domain`, 
			`API_KEY`, 
			`PASSWORD`, 
			`SECRET_CODE`, 
			`EMAIL_ADDRESS`, 
			`FULL_NAME`, 
			`last_attempt`, 
			`is_active`, 
			`confirmation_code`
		)
		VALUES (
			'".mysql_real_escape_string($uuid)."',
			'DEVICE', 
			'".mysql_real_escape_string($api)."', 
			'".mysql_real_escape_string($password)."',
			'".$secret."',
			'".mysql_real_escape_string($email)."', 
			'".mysql_real_escape_string($name)."', 
			CURRENT_TIMESTAMP, 
			'0', 
			'".mysql_real_escape_string($confirmation)."'
		);";
	$result = $global['db']->Execute($query);
	$arr = array("SECRET_CODE"=>$secret);
	echo json_encode($arr);

	// Email the newly registered user a confirmation link.

	$link = makeBaseUrl()."register.php?action=confirm&API_KEY=".$api."&CONFIRM_CODE=".$confirmation;

	require($global['approot']."/mod/pop/class.pop.php");
	$p = new pop();
	$subject  = "Please confirm the registration of your device. #".$api;
	$bodyHTML = 
		"Thank you for registering your device, <b>".$name."</b>.<br><br>"
		."You <b>must</b> click on this link in order for the registration process to be completed:<br><a href=\"".$link."\">".$link."</a><br><br>"
		."Once completed, your device will be activated and allowed to send/recieve data with the Person Locator web site.<br><br>"
		."Afterwards, you will also be able to login to the Person Locator web site here by going here and logging in with the following credentials: <br><br>"
		."<a href=\"".makeBaseUrl()."\">".makeBaseUrl()."</a><br>"
		."<b>Username:</b> ".$email."<br><b>Password:</b> ".$password."<br><br>"
		."Once logged in, you can visit the site's <b>User Preferences</b> section to change your password.<br><br>";
	$bodyAlt = 
		"Thank you for registering your device, ".$name."\n\n"
		."You must visit the following link in your browser in order for the registration process to be completed:\n".$link."\n\n"
		."Once completed, your device will be activated and allowed to send/recieve data with the Person Locator web site.\n\n"
		."Afterwards, you will also be able to login to the Person Locator web site here by going here and logging in with the following credentials:\n\n"
		.makeBaseUrl()."\n"
		."Username: ".$email."\nPassword: ".$password."\n\n"
		."Once logged in, you can visit the site's \nUser Preferences\n section to change your password.\n\n";
	$p->sendMessage($email, $name, $subject, $bodyHTML, $bodyAlt);
}




/**
 * Report error message.
 */
function error($msg) {
	$arr = array("ERROR"=>$msg);
	echo json_encode($arr);
}



/**
 * Are the API_KEY and PASSWORD legal?
 */
function isValidKeyPassword() {
	global $api;
	global $password;
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
	global $api;
	global $global;
	$query  = "SELECT * FROM reg WHERE API_KEY = '".mysql_real_escape_string($api)."';";
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
	global $api;
	global $global;
	$query  = "SELECT UNIX_TIMESTAMP(`last_attempt`) FROM reg WHERE API_KEY = '".mysql_real_escape_string($api)."';";
	$result = $global['db']->Execute($query);
	$row    = $result->FetchRow();
	$last   = $row['last_attempt'];
	$time   = time();
	if(($last+(24*60*60)) > $time) {
		return true;
	} else {
		return false;
	}
}



/**
 * Check if an API_KEY is active (confirmed)
 */
function isActive() {
	global $api;
	global $global;
	$query  = "SELECT * FROM reg WHERE API_KEY = '".mysql_real_escape_string($api)."';";
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
		echo "shitttttttttttttttttttttttttttttttttttttttttttttttttttttttttt({$email})";
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