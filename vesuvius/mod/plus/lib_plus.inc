<?
/**
 * @name         PL User Services
 * @version      2.0.0
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0411
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
* @return boolean
*/
function shn_plus_checkCredz($user, $pass) {
	global $global;
	require($global['approot']."/conf/sahana.conf");
	require($global['approot']."/3rd/adodb/adodb.inc.php");
	require($global['approot']."/inc/handler_db.inc");
	require($global['approot']."/inc/lib_uuid.inc");
	require($global['approot']."/inc/lib_security/lib_auth.inc");

	$q = "
		SELECT salt, p_uuid, status
		FROM users
		WHERE user_name = '$user';
	";
	$res = $db->Execute($q);
	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		$status = $res->fields["status"];
		$salt   = $res->fields["salt"];
		$uid    = $res->fields["p_uuid"];
		$pwd    = substr($password, 0, 4).$salt.substr($pwd, 4);

		// Create a digest of the password collected from the challenge
		$password_digest = md5(trim($pwd));
		$q2 = "
			SELECT p_uuid
			FROM users
			WHERE user_name = '$email'
			AND password = '$password_digest'
			AND salt='{$salt}';
		";
		$res2 = $db->Execute($q2);

		if(($res2 == null) || ($res2->EOF)) {
			return false;
		} else {
			return true;
		}
	}
}


