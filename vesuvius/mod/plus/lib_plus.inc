<?
/**
 * @name         PL User Services
 * @version      24
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0221
 */


global $global;
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');


/** Registers one service from the API to the nusoap server */
function shn_plus_registerOne($server, $methodname, $params, $ns, $rtfm) {

	global $ns;

	$server->register(
		$methodname,
		$params["in"],
		$params["out"],
		$ns,
		$server->wsdl->endpoint.'#'.$methodname, // soapaction
		'document',
		'literal',
		$rtfm
	);
	/* REFERENCE ~ DONT DELETE!
	$server->register(
		$function,  // $name the name of the PHP function, class.method or class..method
		$in,        // $in assoc array of input values: key = param name, value = param type
		$out,       // $out assoc array of output values: key = param name, value = param type
		$ns,        // $namespace the element namespace for the method or false
		$action,    // $soapaction the soapaction for the method or false
		"document", // $style optional (rpc|document) or false Note: when 'document' is specified, parameter and return wrappers are created for you automatically
		"literal",  // $use optional (encoded|literal) or false
		$doc,       // $documentation optional Description to include in WSDL
		null        // $encodingStyle optional (usually 'http://schemas.xmlsoap.org/soap/encoding/' for encoded)
	);
	*/
}



/** Log access to PLUS services */
function shn_plus_logAccess($call="", $username=null) {

	global $global;

	// if not anonymous, check for invalid username and change it to null for logging purposes
	if($username !== null) {
		$q = "
			SELECT count(*)
			FROM `users`
			WHERE user_name = '".mysql_real_escape_string($username)."';
		";
		$res = $global['db']->Execute($q);
		if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus log access 1 ((".$q."))"); }
		if(($res == null) || ($res->EOF)) {
			$username = null;
		} else {
			if((int)$res->fields["count(*)"] != 1) {
				$username = null;
			}
		}
	}
	if($username === null) {
		$user_name = "null";
	} else {
		$user_name = "'".$username."'";
	}

	if(isset($_SERVER['HTTP_USER_AGENT'])) {

		$agent  = explode(" ", $_SERVER['HTTP_USER_AGENT']);
		$appver = explode("/", $agent[0]);
		$app    = $appver[0];
		$ver    = $appver[1];

	} else {
		$app = "";
		$ver = "";
	}

	$ip = $_SERVER['REMOTE_ADDR'];

	// see if this ip accessed plus in the last 10 minutes (for rate throttling ip lookups)
	$q = "
		SELECT *
		FROM plus_access_log
		WHERE ip = '".mysql_real_escape_string($ip)."'
		AND access_time BETWEEN DATE_SUB(NOW(), INTERVAL 10 MINUTE) AND NOW();
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus log access 2 ((".$q."))"); }
	if(($res == null) || ($res->EOF)) {

		// use a web service to lookup the lat/long of the ip address
		$resp = json_decode(file_get_contents('http://freegeoip.net/json/'.urlencode($ip)));
		if (!$resp->latitude) {
			// lookup failed
			$lat = 'null';
			$lon = 'null';
		} else {
			$lat = "'".(float)$resp->latitude."'";
			$lon = "'".(float)$resp->longitude."'";
		}

	// we already looked this use up in the last 10 minutes, so use the last reported value
	} else {
		$lat = $res->fields["latitude"];
		$lon = $res->fields["longitude"];
	}

	$q = "
		INSERT INTO plus_access_log (`access_time`, `application`, `version`, `ip`, `call`, `api_version`, `latitude`, `longitude`, `user_name`)
		VALUES (CURRENT_TIMESTAMP, '".$app."', '".$ver."', '".$ip."', '".$call."', '".mysql_real_escape_string($global['apiVersion'])."', ".$lat.", ".$lon.", ".$user_name.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus log access 3 ((".$q."))"); }
}



/**
* Checks the credentials of a user
* @return int ~ error code
* error code: 0 for user/password valid and user is active
* error code: 1 invalid username or password
* error code: 2 user account is not active
* error code: 3 user account is banned
*/
function shn_plus_checkCredz($username, $password) {

	global $global;
	require_once($global['approot']."/conf/sahana.conf");
	require_once($global['approot']."/3rd/adodb/adodb.inc.php");
	require_once($global['approot']."/inc/handler_db.inc");
	require_once($global['approot']."/inc/lib_uuid.inc");
	require_once($global['approot']."/inc/lib_security/lib_auth.inc");

	$q = "
		SELECT salt, p_uuid, status
		FROM users
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check credz ((".$q."))"); }
	if(($res == null) || ($res->EOF)) {
		return 1;
	} else {
		if($res->fields["status"] == "pending") {
			return 2;

		} elseif($res->fields["status"] == "banned") {
			return 3;

		} elseif($res->fields["status"] == "locked") {
			return 4;
		}

		$salt = $res->fields["salt"];
		$pwd  = substr($password, 0, 4) .$salt. substr($password, 4);

		// Create a digest of the password collected from the challenge
		$password_digest = md5(trim($pwd));
		$q2 = "
			SELECT *
			FROM users
			WHERE user_name = '".mysql_real_escape_string($username)."'
			AND password = '".$password_digest."'
			AND salt = '".$salt."';
		";
		$res2 = $global['db']->Execute($q2);
		if($res2 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check credz 2 ((".$q2."))"); }
		if(($res2 == null) || ($res2->EOF)) {
			return 1;
		} else {
			return 0; // successfull auth'd
		}
	}
}



/**
* Checks the credentials of a user to perform an expiration on a record (must be record owner, hsa, or admin)
* @return boolean (true if allowed to expire record)
*/
function shn_plus_checkCredzExpiry($username, $uuid) {

	global $global;

	// check if the user is admin or hsa member...
	$q = "
		SELECT *
		FROM users u, sys_user_groups g, sys_user_to_group x
		WHERE u.user_name = '".mysql_real_escape_string($username)."'
		AND x.p_uuid = u.p_uuid
		AND g.group_id = x.group_id
		AND (
			g.group_id = 1
			OR g.group_id = 6
		);
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check credz expiry 1 ((".$q."))"); }

	if(($result == null) || ($result->EOF)) {

		// if not admin or hsa, check they are at least the record owner...
		$q2 = "
			SELECT *
			FROM users u, person_to_report p
			WHERE u.user_name = '".mysql_real_escape_string($username)."'
			AND p.rep_uuid = u.p_uuid
			AND p.p_uuid = '".mysql_real_escape_string($uuid)."';
		";
		$res2 = $global['db']->Execute($q2);
		if($res2 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check credz expiry 2 ((".$q2."))"); }

		if(($res2 == null) || ($res2->EOF)) {
			return false;
		} else {
			return true; // they must have reported this person
		}

	} else {
		// at least one row... they are an admin or hsa
		return true;
	}
}




/**
* Checks the credentials of a user to perform a revision on a record (must be record owner, hsa, hs, or admin)
* @return boolean (true if allowed to revise the record)
*/
function shn_plus_checkCredzTriage($username, $uuid) {

	global $global;

	// check if the user is admin or hsa member...
	$q = "
		SELECT *
		FROM users u, sys_user_groups g, sys_user_to_group x
		WHERE u.user_name = '".mysql_real_escape_string($username)."'
		AND x.p_uuid = u.p_uuid
		AND g.group_id = x.group_id
		AND (
			g.group_id = 1
			OR g.group_id = 5
			OR g.group_id = 6
		);
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check credz triage 1 ((".$q."))"); }

	if(($result == null) || ($result->EOF)) {

		// if not admin, hsa, or hs, check they are at least the record owner...
		$q2 = "
			SELECT *
			FROM users u, person_to_report p
			WHERE u.user_name = '".mysql_real_escape_string($username)."'
			AND p.rep_uuid = u.p_uuid
			AND p.p_uuid = '".mysql_real_escape_string($uuid)."';
		";
		$res2 = $global['db']->Execute($q2);
		if($res2 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check credz triage 2 ((".$q2."))"); }

		if(($res2 == null) || ($res2->EOF)) {
			return false;
		} else {
			return true; // they must have reported this person
		}

	} else {
		// at least one row... they are an admin or hsa
		return true;
	}
}



/**
* Finds the uuid a a prticular user
* @return string (false if not found)
*/
function shn_plus_getUserUuid($username) {

	global $global;

	$q = "
		SELECT *
		FROM users
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus get user uuid ((".$q."))"); }

	if(($result == null) || ($result->EOF)) {
		return false;
	} else {
		return $result->fields["p_uuid"];
	}
}



/**
* Finds out if a particulr uuid was reported via web services
* @return boolean
*/
function shn_plus_wasRecordReportedViaPLUS($p_uuid) {

	global $global;

	$q = "
		SELECT *
		FROM plus_report_log
		WHERE p_uuid = '".mysql_real_escape_string($p_uuid)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check was record reported via PLUS ((".$q."))"); }

	if(($result == null) || ($result->EOF)) {
		return false;
	} else {
		return true;
	}
}



/**
* Checks if a person exists (has an entry in person_uuid)
* @return boolean
*/
function shn_plus_doesPersonExist($uuid) {

	global $global;

	$q = "
		SELECT count(*)
		FROM person_uuid
		WHERE p_uuid = '".mysql_real_escape_string($uuid)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus check person exists ((".$q."))"); }

	if((int)$result->fields["count(*)"] == 1) {
		return true;
	} else {
		return false;
	}
}



/**
* Finds the user_id of a prticular user
* @return string (false if not found)
*/
function shn_plus_getUserId($username) {

	global $global;

	$q = "
		SELECT *
		FROM users
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus get user uuid ((".$q."))"); }

	if(($result == null) || ($result->EOF)) {
		return false;
	} else {
		return $result->fields["user_id"];
	}
}



/** Creates a new registration. */
function shn_plus_emailNewUser($username) {

	global $global;
	global $conf;

	$q = "
		SELECT *
		FROM users u, contact c
		WHERE u.p_uuid = c.p_uuid
		AND u.user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus email new user ((".$q."))"); }

	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		// Email the newly registered user a confirmation link.
		$link = makeBaseUrl()."index.php?register&confirm=".$res->fields["confirmation"]."&username=".$username;
		require_once($global['approot']."/mod/lpf/lib_lpf.inc");
		$p = new pop();
		$subject  = "Please confirm the registration of your new PL user account";
		$bodyHTML =
			"Thank you for registering.<br><br>"
			."You <b>must</b> click on this link in order for the registration process to be completed:<br><a href=\"".$link."\">".$link."</a><br><br>"
			."Once completed, your account will be active allowing you to login the Person Locator web site and other devices which utilize its web services.<br><br><br>"
			."<b>- ".$conf['site_name']."</b>";
		$bodyAlt =
			"Thank you for registering.\n\n"
			."You must click on this link in order for the registration process to be completed:\n".$link."\n"
			."Once completed, your account will be active allowing you to login the Person Locator web site and other devices which utilize its web services.\n\n\n"
			."- ".$conf['site_name'];
		$p->sendMessage($res->fields["contact_value"], $username, $subject, $bodyHTML, $bodyAlt);
	}
}



/** Changes a user's account status to active */
function shn_plus_activateUser($username) {

	global $global;

	$q = "
		UPDATE  users
		SET
			status =  'active',
			confirmation = NULL
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$r = $global['db']->Execute($q);
	if($r === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus activate user ((".$q."))"); }
}



/** Updates confirmation code and sends email with link to reset password. */
function shn_plus_resetEmail($username, $email) {

	global $global;
	global $conf;

	$confirmation = md5(uniqid(rand(), true));

	$q = "
		UPDATE users
		SET confirmation =  '".$confirmation."'
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus reset email ((".$q."))"); }

	// Email the link with confirmation to reset a password
	$link = makeBaseUrl()."index.php?register&reset=".$confirmation."&username=".$username;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$p = new pop();
	$subject  = "Request to reset the password of your account on ".$conf['site_name'];
	$bodyHTML =
		"Dear User,<br><br>Someone (possibly not you) has initiated a request to reset the password for your account on ".$conf['site_name'].". If you feel this was in error or you did not initiate this request yourself, you may safely ignore this email as nothing will change. However, if you did initiate this request and would like to reset your password, you must visit the following link to have it reset:<br><br><a href=\"".$link."\">".$link."</a><br><br>Once this has been done, another email will be sent to you with a temporary password. From there, you can login and change your password to something of your own choosing.<br><br>Your username on ".$conf['site_name']." is: <b>".$username."</b><br><br><b>- ".$conf['site_name']."</b>";
	$bodyAlt =
		"Dear User,\n\nSomeone (possibly not you) has initiated a request to reset the password for your account on ".$conf['site_name'].". If you feel this was in error or you did not initiate this request yourself, you may safely ignore this email as nothing will change. However, if you did initiate this request and would like to reset your password, you must visit the following link to have it reset:\n\n".$link."\n\nOnce this has been done, another email will be sent to you with a temporary password. From there, you can login and change your password to something of your own choosing.\n\nYour username on ".$conf['site_name']." is: ".$username."\n\n- ".$conf['site_name'];
	$p->sendMessage($email, $username, $subject, $bodyHTML, $bodyAlt);
}



/** Reset a user's password to a random value and email it to the user */
function shn_plus_resetPasswordAndEmail($username) {

	global $global;
	global $conf;

	require_once($global['approot']."/inc/lib_security/lib_auth.inc");
	$newPassword = md5(uniqid(rand(), true));
	$newPassword = substr($newPassword, rand(0,7), 12)."Z";
	shn_change_password_simple($username, $newPassword);

	$q = "
		SELECT *
		FROM users u, contact c
		WHERE u.p_uuid = c.p_uuid
		AND u.user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "plus reset password and email ((".$q."))"); }

	if(($res == null) || ($res->EOF)) {
		return false;

	// Email the new password to the user
	} else {
		$link1 = makeBaseUrl()."login";
		$link2 = makeBaseUrl()."index.php?mod=pref&act=ch_passwd";
		require_once($global['approot']."/mod/lpf/lib_lpf.inc");
		$p = new pop();
		$subject  = "New password for your account on ".$conf['site_name'];
		$bodyHTML =
			"Dear User,<br><br>Your password has successfully been updated and is now set to:<br><b>".$newPassword."</b><br><br>You may now login with it here:<br><a href=\"".$link1."\">".$link1."</a><br><br>Also, you may change your password by visiting this link (after logging in):<br><a href=\"".$link2."\">".$link2."</a><br><br><b>- ".$conf['site_name']."</b>";
		$bodyAlt =
			"Dear User,\n\nYour password has successfully been updated and is now set to:\n".$newPassword."\n\nYou may now login with it here:\n".$link1."\n\nAlso, you may change your password by visiting this link (after logging in):\n".$link2."\n\n- ".$conf['site_name'];
		$p->sendMessage($res->fields["contact_value"], $username, $subject, $bodyHTML, $bodyAlt);
	}
}



/** Emails username to a user who forgot it */
function shn_plus_forgotUsernameEmail($email, $username) {

	global $global;
	global $conf;

	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$p = new pop();
	$subject  = "Email Reminder of your username account on ".$conf['site_name'];
	$bodyHTML =
		"Dear User,<br><br>Someone (possibly not you) has requested to be reminded of the username associated with their account on ".$conf['site_name'].".<br><br>The username assoicated with this email address is:<br><b>".$username."</b><br><br>This should help you to login to the site if you had forgotten your username. If you did not request this email, please disregard it.<br><br><b>- ".$conf['site_name']."</b><br>";
	$bodyAlt =
		"Dear User,\n\nSomeone (possibly not you) has requested to be reminded of the username associated with their account on ".$conf['site_name'].".\n\nThe username assoicated with this email address is:\n".$username."\n\nThis should help you to login to the site if you had forgotten your username. If you did not request this email, please disregard it.\n\n- ".$conf['site_name'];
	$p->sendMessage($email, $username, $subject, $bodyHTML, $bodyAlt);
}








