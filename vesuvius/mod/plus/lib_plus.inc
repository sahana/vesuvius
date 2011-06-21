<?
/**
 * @name         PL User Services
 * @version      1.9.2
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0606
 */



/**
* Registers one service from the API to the nusoap server
*/
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
	/*
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



/**
 * Log access to PLUS services
 */
function shn_plus_logAccess($call="") {
	global $global;
	$agent  = explode(" ", $_SERVER['HTTP_USER_AGENT']);
	$appver = explode("/", $agent[0]);
	$app    = $appver[0];
	$ver    = $appver[1];
	$ip     = $_SERVER['REMOTE_ADDR'];
	$q1 = "
		INSERT INTO plus_access_log (`access_time`, `application`, `version`, `ip`, `call`, `api_version`)
		VALUES (CURRENT_TIMESTAMP, '".$app."', '".$ver."', '".$ip."', '".$call."', '".mysql_real_escape_string($global['apiVersion'])."');
	";
	$res = $global['db']->Execute($q1);
}






/**
* Checks the credentials of a user
* @return int ~ error code
* error code: 0 for user/password valid and user is active
* error code: 1 invalid username or password
* error code: 2 user account is not active
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
	if(($res == null) || ($res->EOF)) {
		return 1;
	} else {
		if($res->fields["status"] != "active") {
			return 2;
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
		if(($res2 == null) || ($res2->EOF)) {
			return 1;
		} else {
			return 0; // successfull auth'd
		}
	}
}



/**
 * Creates a new registration.
 */
function shn_plus_emailNewUser($username) {
	global $global;
	$q = "
		SELECT *
		FROM users u, contact c
		WHERE u.p_uuid = c.p_uuid
		AND u.user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
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
			."<b>- People Locator</b>";
		$bodyAlt =
			"Thank you for registering.\n\n"
			."You must click on this link in order for the registration process to be completed:\n".$link."\n"
			."Once completed, your account will be active allowing you to login the Person Locator web site and other devices which utilize its web services.\n\n\n"
			."- People Locator";
		$p->sendMessage($res->fields["contact_value"], $username, $subject, $bodyHTML, $bodyAlt);
	}
}



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
}



/**
 * Updates confirmation code and sends email with link to reset password.
 */
function shn_plus_resetEmail($username, $email) {
	global $global;
	$confirmation = md5(uniqid(rand(), true));

	$q = "
		UPDATE users
		SET confirmation =  '".$confirmation."'
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);

	// Email the link with confirmation to reset a password
	$link = makeBaseUrl()."index.php?register&reset=".$confirmation."&username=".$username;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$p = new pop();
	$subject  = "Request to reset the password of your PL user account";
	$bodyHTML =
		"Dear User,<br><br>Someone (possibly not you) has initiated a request to reset the password for your PL user account. If you feel this was in error or you did not initiate this request yourself, you may safely ignore this email as nothing will change. However, if you did initiate this request and would like to reset your password, you must visit the following link to have it reset:<br><br><a href=\"".$link."\">".$link."</a><br><br>Once this has been done, another email will be sent to you with a temporary password. From there, you can login and change your password to someting of your choosing.<br><br><b>- People Locator</b>";
	$bodyAlt =
		"Dear User,\n\nSomeone (possibly not you) has initiated a request to reset the password for your PL user account. If you feel this was in error or you did not initiate this request yourself, you may safely ignore this email as nothing will change. However, if you did initiate this request and would like to reset your password, you must visit the following link to have it reset:\n\n".$link."\n\nOnce this has been done, another email will be sent to you with a temporary password. From there, you can login and change your password to someting of your choosing.\n\n- People Locator";
	$p->sendMessage($email, $username, $subject, $bodyHTML, $bodyAlt);
}




function shn_plus_resetPasswordAndEmail($username) {
	global $global;
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
	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		// Email the new password to the user
		$link1 = makeBaseUrl()."login";
		$link2 = makeBaseUrl()."index.php?mod=pref&act=ch_passwd";
		require_once($global['approot']."/mod/lpf/lib_lpf.inc");
		$p = new pop();
		$subject  = "New password for your PL user account.";
		$bodyHTML =
			"Dear User,<br><br>Your password has successfully been updated and is now set to:<br><b>".$newPassword."</b><br><br>You may now login with it here:<br><a href=\"".$link1."\">".$link1."</a><br><br>Also, you may change your password by visiting this link (after logging in):<br><a href=\"".$link2."\">".$link2."</a><br><br><b>- People Locator</b>";
		$bodyAlt =
			"Dear User,\n\nYour password has successfully been updated and is now set to:\n".$newPassword."\n\nYou may now login with it here:\n".$link1."\n\nAlso, you may change your password by visiting this link (after logging in):\n".$link2."\n\n- People Locator";
		$p->sendMessage($res->fields["contact_value"], $username, $subject, $bodyHTML, $bodyAlt);
	}
}



function shn_plus_forgotUsernameEmail($email, $username) {
	global $global;

	// Email the username to the user
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$p = new pop();
	$subject  = "Email Reminder of your username for your PL account";
	$bodyHTML =
		"Dear User,<br><br>Someone (possibly not you) has requested to be reminded of the username associated with their account on PL.<br><br>The username assoicated with this email address is:<br><b>".$username."</b><br><br>This should help you to login to the site if you had forgotten your username. If you did not request this email, please disregard it.<br><br><b>- People Locator</b><br>";
	$bodyAlt =
		"Dear User,\n\nSomeone (possibly not you) has requested to be reminded of the username associated with their account on PL.\n\nThe username assoicated with this email address is:\n".$username."\n\nThis should help you to login to the site if you had forgotten your username. If you did not request this email, please disregard it.\n\n- People Locator\n";
	$p->sendMessage($email, $username, $subject, $bodyHTML, $bodyAlt);
}








