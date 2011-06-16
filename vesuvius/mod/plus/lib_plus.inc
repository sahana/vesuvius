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









