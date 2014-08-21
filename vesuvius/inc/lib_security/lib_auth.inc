<?
/**
 * @name         Authentication Library
 * @version      11
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


require_once("constants.inc");
require_once("errors.inc");
require_once("lib_acl.inc");

function shn_auth_get_openid_user($openid) {

	global $global;

	$db=$global['db'];
	$q = "
		select users.user_name
		from users, alt_logins
		where users.p_uuid = alt_logins.p_uuid
		and alt_logins.user_name='{$openid}';
	";
	$res = $db->Execute($q);
	if(($res == null) || ($res->EOF)){
		return null;
	} else {
		return $res->fields["user_name"];
	}
}



function shn_auth_user_list_and_status() {

	global $global;

	$db = $global['db'];
	$q = "
		select users.p_uuid, full_name, user_name, status
		from person_uuid,users
		where users.p_uuid = person_uuid.p_uuid
		and users.p_uuid <> 1
		order by full_name;
	";
	$res=$db->Execute($q);
	$users=array();

	while(!$res->EOF){
		$name = $res->fields["full_name"].":".$res->fields["user_name"];
		$users[$res->fields["p_uuid"]] = array($name,$res->fields["status"]);
		$res->MoveNext();
	}
	return $users;
}



function shn_auth_locked_user_list() {

	global $global;

	$db=$global['db'];

	$q = "
		select users.p_uuid,full_name,user_name,status
		from person_uuid,users
		where status='locked'
		and users.p_uuid=person_uuid.p_uuid
		and users.p_uuid <> 1
		order by full_name;
	";
	$res = $db->Execute($q);
	$users = array();

	while(!$res->EOF){
		$name = $res->fields["full_name"].":".$res->fields["user_name"];
		$users[$res->fields["p_uuid"]] = array($name,$res->fields["status"]);
		$res->MoveNext();
	}
	return $users;
}




function shn_auth_activate_user($pid=null,$uname=null) {

	global $global;

	$db=$global['db'];

	if($pid==null){
		if($uname==null) {
			return false;
		} else {
			$sql = "
				update users
				set status='active'
				where user_name='{$uname}';
			";
		}
	} else {
		$sql = "
			update users
			set status='active'
			where p_uuid='{$pid}';
		";
	}
	$res = $db->Execute($sql);
	return $res;
}



/**
 *check the existence of an user
 *@return bool
 *@param string user name
 *@access public
 */
function shn_current_user(){
	global $global;
	$q = "select p_uuid from  users where  user_name = '{$_SESSION['user']}'";
	$db=$global['db'];
	$res=$db->Execute($q);
	if(($res==null) or ($res->EOF)){
		return null;
	}else {
		return $res->fields["p_uuid"];
	}
}



function shn_get_user_details($user){

	$q = "select full_name from person_uuid where  p_uuid = '{$user}'";
	global $global;
	$db=$global['db'];
	$res=$db->Execute($q);
	if(($res==null) or ($res->EOF)){
		return false;
	}else {
		return $res->fields["full_name"];
	}
}



/**
 *Add a new user to the users table
 *@param string account name(nice name for the user)
 *@param string user namee
 *@param string user password
 *@param string role
 *@param p_uuid p_id ( user id , if not present the value is generated)
 *@param extra_opts
 *@param email_address
 *@access public
 *@return bool
 */
function shn_auth_add_user($given_name, $family_name, $user_name, $user_password, $role, $pid=null, $extra_opts=null, $email=null) {

	global $global;

	$db = $global['db'];
	include_once($global['approot']."/inc/lib_uuid.inc");
	$error = false;

	if($user_name == null) {
		return false;
	}

	if($role == null) {
		$role = REGISTERED;
	}

	if(shn_is_user($user_name)) {
		add_error(SHN_AUTH_ERR_USER_EXISTS);
		return false;
	}

	if(isset($_POST["email_address"]) && $_POST["email_address"] != null) {
		$q = "
			SELECT *
			FROM contact c, users u
			WHERE c.opt_contact_type = 'email'
			AND c.contact_value = '".mysql_real_escape_string(trim($_POST['email_address']))."'
			AND c.p_uuid = u.p_uuid;
		";
		$res = $db->Execute($q);
		if(($res == null) || ($res->EOF)) {
			// email address not used for any of the users in the system
		} else {
			add_error(SHN_AUTH_ERR_EMAIL_EXISTS);
			$error=true;
			return false;
		}
	}

	if(isset($_POST["openid"]) && $_POST["openid"] != null) {
		$q = "
			select alt_logins.p_uuid
			from alt_logins
			where user_name='{$_POST["openid"]}'
			and type='openid';
		";
		$res = $db->Execute($q);
		if(($res == null) || ($res->EOF)) {
			// openid not used
		} else {
			add_error(SHN_AUTH_ERR_OPENID_EXISTS);
			$error=true;
			return false;
		}
	}

	if($pid == null) {
		$pid = shn_create_uuid($type='person');
	} else {
		$q = "
			select p_uuid
			from person_uuid
			where p_uuid='{$pid}''
		";
		$res = $db->Execute($q);

		if(($res == null) || ($res->EOF)) {
			//
		} else {
			$error=true;
			add_error(SHN_AUTH_ERR_PERSON_EXISTS);
			return false;
		}
	}

	$q = "
		insert into person_uuid(p_uuid, full_name, family_name, given_name)
		values(
			'".$pid."',
			'".mysql_real_escape_string($given_name)." ".mysql_real_escape_string($family_name)."',
			'".mysql_real_escape_string($family_name)."',
			'".mysql_real_escape_string($given_name)."'
		);
	";
	$res = $db->Execute($q);

	if($res == false) {
		add_error($db->ErrorMsg());
		$error = true;
	}

	if(!$error) {
		// Create the encrypted password
		$salt1           = _shn_generateSalt();
		$salt2           = _shn_generateSalt();
		$salt            = $salt1.$salt2;
		$user_password   = substr($user_password, 0, 4).$salt.substr($user_password, 4);
		$stored_password = md5(trim($user_password));
		$time            = time();
		$confirmation    = md5(uniqid(rand(), true)); // code used to activate account

		if($extra_opts['pending'] == true) {
			$status = 'pending';
		} else {
			// Insert a new user into the users table
			$status = 'active';
		}

		$q = "
			INSERT INTO users(p_uuid, password, changed_timestamp, user_name, salt, status, confirmation)
			values('".$pid."','".$stored_password."', ".$time." ,'".mysql_real_escape_string($user_name)."', '".$salt."', '".$status."', '".$confirmation."');
		";
		$res = $db->Execute($q);

		if($res == false) {
			add_error($db->ErrorMsg());
		}

		if($res) {
			$res = shn_acl_adduser_to_role_uuid($pid, $role);
			shn_acl_log_msg("New user added : ", $pid, $user_name);

			$q = "
				SELECT *
				FROM users
				WHERE p_uuid = '".mysql_real_escape_string($pid)."' ;
			";
			$result = $global['db']->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "add user find new user_id ((".$q."))"); }

			if($row = $result->FetchRow()) {
				$res = $row['user_id'];
			}
		}

		if(isset($_POST["openid"]) && $_POST["openid"] != null) {
			$q2 = "
				INSERT INTO alt_logins(p_uuid, user_name, type)
				values('".$pid."', '".$_POST["openid"]."', 'openid');
			";
			$res2 = $db->Execute($q2);
		}

		$q9 = "
			INSERT INTO contact(p_uuid, opt_contact_type, contact_value)
			values('".$pid."', 'email', '".mysql_real_escape_string($email)."');
		";
		$res9 = $db->Execute($q9);
	}
	return $res;
}




// check the existence of an user
function shn_is_user($user_name) {

	global $global;

	$db = $global['db'];
	$q = "
		SELECT p_uuid
		FROM users
		WHERE user_name = '".mysql_real_escape_string($user_name)."';
	";
	$res = $db->Execute($q);
	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		return true;
	}
}



// check the existence of an user with the email address
function shn_is_user_with_email($email) {

	global $global;

	$db = $global['db'];
	$q = "
		SELECT *
		FROM contact c, users u
		where c.contact_value = '".mysql_real_escape_string($email)."'
		and c.p_uuid = u.p_uuid;
	";
	$res = $db->Execute($q);
	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		return true;
	}
}



function shn_auth_user_list($fullname = false, $admin = true) {

	global $global;

	$db = $global['db'];

	$q = "
		select users.p_uuid, full_name, user_name
		from person_uuid, users
		where users.p_uuid = person_uuid.p_uuid
		order by user_name;
	";
	$res = $db->Execute($q);
	$users = array();

	while(!$res->EOF){
		if($res->fields["full_name"]==null){
			$name="Full Name not avaliable - ".$name=$res->fields["user_name"];
		} else{
			$name=$res->fields["full_name"]." - ".$name=$res->fields["user_name"];
		}
		if(($res->fields["p_uuid"]!="1") or($admin==true)){
			$users[$res->fields["p_uuid"]]=$name;
		}
		$res->MoveNext();
	}
	return $users;
}



// added to allow the usage of user_id instead of p_uuid for user managerment (its more logical) ~ G
function shn_auth_user_list2() {

	global $global;

	$db=$global['db'];

	$q = "
		select p.p_uuid, p.full_name, u.user_id, u.user_name, g.group_id
		from person_uuid p
		left join users u on u.p_uuid = p.p_uuid
		left join sys_user_to_group g on p.p_uuid = g.p_uuid
		where u.user_id is not null
		order by u.user_id ;
	";

	$res   = $db->Execute($q);
	$users = array();

	while(!$res->EOF) {
		$users[$res->fields["user_id"]] = array(
			"user_id" => $res->fields["user_id"],
			"user_name" => $res->fields["user_name"],
			"full_name" => $res->fields["full_name"],
			"group_id" => $res->fields['group_id'],
			"p_uuid" => $res->fields['p_uuid']
		);
		$res->MoveNext();
	}
	return $users;
}



/**
 *Check if a user has an account that matches the user name and password
 *therefore this is the function you need to call for authentication
 *since authentication is called by the front controller
 *and all the POST variables avaliable to the front controller
 *are avaliable to this function as well,user name and password
 *are not sent as parameters. Instead they are read from the POST
 *array.
 *remember this function will be called with every request to the front
 *controller. But we need to authenticate only when its a login attempt
 *if its not a login request return -1
 *@return int the user id , if the user exists ,else 0 or -1
 *@access public
 */
function shn_authenticate_user() {

	global $global;
	global $conf;

	$db = $global['db'];
	$user_data = array("user_id" => ANONYMOUS_USER, "user" => "Anonymous");
	$user_data["result"] = null;

	if(isset($_GET['act']) && $_GET['act'] == "logout") {
		$user_data["user_id"] = ANONYMOUS_USER;
		$user_data["user"]    = "Anonymous";
		$user_data["result"]  = LOGGEDOUT;
		return $user_data ;
	}

	// only authenticate if requested
	if(!isset($_GET['doLogin'])) {
		$user_data["user_id"] = -1;
		return $user_data ;





	// handle Google OAuth login
	} elseif($_GET['doLogin'] == "2") {

		require_once($global['approot']."/3rd/google-api-php-client/src/apiClient.php");
		require_once($global['approot']."/3rd/google-api-php-client/src/contrib/apiOauth2Service.php");

		$user_id = null;
		$username = null;

		$client = new apiClient();
		$client->setApplicationName($conf['site_name']);
		$client->setClientId($conf['oauth_google_clientId']);
		$client->setClientSecret($conf['oauth_google_clientSecret']);
		$client->setRedirectUri($conf['oauth_google_redirectUri']);
		$client->setDeveloperKey($conf['oauth_google_developerKey']);
		$client->setAccessType('online');

		$oauth2 = new apiOauth2Service($client);
		$authenticated = false;

		if(isset($_GET['code'])) {

			$client->authenticate();
			$_SESSION['token'] = $client->getAccessToken();

			//$redirect = 'http://' . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'];
			//header('Location: ' . filter_var($redirect, FILTER_SANITIZE_URL));

			if(isset($_SESSION['token'])) {
				$client->setAccessToken($_SESSION['token']);

				if($client->getAccessToken()) {

					// try { $client->verifyIdToken(); }
					// catch(apiAuthException $e) { echo '<br>Unable to verify id_token. Error: '.$e->getMessage().'<br>'; }

					$user = $oauth2->userinfo->get();

					$oauth_id       = isset($user['id'])             ? filter_var($user['id'],             FILTER_SANITIZE_NUMBER_INT) : null;
					$email          = isset($user['email'])          ? filter_var($user['email'],          FILTER_VALIDATE_EMAIL)      : null;
					$verified_email = isset($user['verified_email']) ? filter_var($user['verified_email'], FILTER_VALIDATE_BOOLEAN)    : null;
					$given_name     = isset($user['given_name'])     ? filter_var($user['given_name'],     FILTER_SANITIZE_STRING)     : null;
					$family_name    = isset($user['family_name'])    ? filter_var($user['family_name'],    FILTER_SANITIZE_STRING)     : null;
					$profile_link   = isset($user['link'])           ? filter_var($user['link'],           FILTER_VALIDATE_URL)        : null;
					$profile_pic    = isset($user['picture'])        ? filter_var($user['picture'],        FILTER_VALIDATE_URL)        : null;
					$gender         = isset($user['gender'])         ? filter_var($user['gender'],         FILTER_SANITIZE_STRING)     : null;
					$locale         = isset($user['locale'])         ? filter_var($user['locale'],         FILTER_SANITIZE_STRING)     : null;

					// The access token may have been updated lazily.
					$_SESSION['token'] = $client->getAccessToken();

					if($_SESSION['token'] != null) {
						$authenticated = true;
					}

				} else {
					$authenticated = false;
				}
			} else {
				$authenticated = false;
			}
		} else {
			$authenticated = false;
		}

		if(!$authenticated || (isset($_GET['error']) && $_GET['error'] == "access_denied")) {
			$user_data["user_id"] = ANONYMOUS_USER;
			$user_data["user"] = "Anonymous";
			$user_data["result"] = LOGINFAILED;
			add_error("Login via Google failed.");
			return $user_data;
		}

		/*
		echo '<pre>_SESSION('.print_r(var_export($_SESSION, true), true).')</pre>';
		echo '<pre>_SERVER('.print_r(var_export($_SERVER, true), true).')</pre>';
		echo '<pre>_COOKIE('.print_r(var_export($_COOKIE, true), true).')</pre>';
		echo '<pre>_REQUEST('.print_r(var_export($_REQUEST, true), true).')</pre>';
		die();
		*/

		// logged in successfully

		// find the local user with the corresponding oauth id (if it already exists)
		$q = "
			SELECT *
			FROM `users`
			WHERE oauth_id = '".mysql_real_escape_string($oauth_id)."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "oauth query 1 ((".$q."))"); }

		// if we already have an oauth user with a matching id on our system, log them in
		if($result != null && !$result->EOF) {
			$row = $result->FetchRow();
			$user_id = $row['user_id'];
			$username = $row['user_name'];

		// the oauth user is not already present in our system
		} else {

			// find the local user with a username that matches the google email address
			$q = "
				SELECT *
				FROM `users`
				WHERE user_name = '".mysql_real_escape_string($email)."';
			";
			$result = $global['db']->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "oauth query 2 ((".$q."))"); }

			// we have a user with a username that matches the google email address
			if($result != null && !$result->EOF) {
				$row = $result->FetchRow();
				$user_id = $row['user_id'];
				$username = $row['user_name'];

			// check if a user in the system is using a contact email address the same as the google email
			} else {

				$q = "
					SELECT *
					FROM contact c, users u
					WHERE c.contact_value = '".mysql_real_escape_string($email)."'
					AND c.p_uuid = u.p_uuid;
				";
				$result = $global['db']->Execute($q);
				if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "oauth query 3 ((".$q."))"); }

				// we have a user that is using this google email address
				if($result != null && !$result->EOF) {
					$row = $result->FetchRow();
					$user_id = $row['user_id'];
					$username = $row['user_name'];
				}
			}
		}

		// if not set, we have a new user, so add the new user...
		if($user_id == null && $username == null) {

			// generate a strong random password for the local account...
			$time = time();
			$p1a = rand(10e16, 10e20);
			$p1b = base_convert($p1a, 10, 36);
			$p1c = strtoupper($p1b);
			$part1 = substr($p1c, 0, 8);
			$p2a = rand(10e16, 10e20);
			$p2b = base_convert($p2a, 10, 36);
			$part2 = substr($p2b, 0, 8);
			$password = $part1.$part2;

			$user_id = shn_auth_add_user($given_name, $family_name, $email, $password, REGISTERED, null, null, $email);
			$username = $email;
		}

		// finally, update the user profile information with the current profile data...
		$q = "
			UPDATE users
			SET
				oauth_id        = '".mysql_real_escape_string($oauth_id)."',
				profile_link    = '".mysql_real_escape_string($profile_link)."',
				profile_picture = '".mysql_real_escape_string($profile_pic)."',
				locale          = '".mysql_real_escape_string($locale)."',
				verified_email  = '".mysql_real_escape_string($verified_email)."'

			WHERE user_id = '".mysql_real_escape_string($user_id)."' ;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "oauth query 4 ((".$q."))"); }

		// log the user in...
		$user_data["user_id"]  = $user_id;
		$user_data["user"]     = $username;
		$user_data["result"]   = LOGGEDIN;
		$user_data["doHeader"] = true;
		$user_data["headerLocation"] = "settings";
		return $user_data;

	// handle a normal login
	} elseif($_GET['doLogin'] == "1") {

		//authentication is done only as the user requested to login
		$user = addslashes(strip_tags(trim($_POST{"user_name"})));
		$pwd = addslashes(strip_tags(trim($_POST{"password"})));
		$q = "
			SELECT salt, p_uuid, status
			FROM users
			WHERE user_name = '$user';
		";
		$res = $db->Execute($q);
		if(($res == null) || ($res->EOF)) {
			add_error("Login Failed : Invalid user name or password.");
			shn_acl_log_msg("Login Failed : Invalid user name or password.", "anonymous", "Anonymous User");
			$user_data["user_id"] = ANONYMOUS_USER;
			$user_data["user"] = "Anonymous";
			$user_data["result"] = LOGINFAILED;
			return $user_data;
		} else {
			$status = $res->fields["status"];
			$salt = $res->fields["salt"];
			$uid = $res->fields["p_uuid"];
		}
		if($status == 'pending') {
			add_error("Your account is not yet active. Please refer to the registration email you have recieved to activate it.");
			shn_acl_log_msg("Login Failed : Account Pending", "anonymous", "Anonymous User");
			$user_data["user_id"] = ANONYMOUS_USER;
			$user_data["user"] = "Anonymous";
			$user_data["result"] = LOGINFAILED;
			return $user_data;
		}
		if($status == 'locked') {
			add_error("This account has been locked due to many failed login attempts. Please contact <a href=\"mailto:".$conf['audit_email']."\">".$conf['audit_email']."</a> to have your account unlocked. Remember to provide your username in the email to expedite the process.");
			shn_acl_log_msg("Login Failed : Password lock still valid.",$uid,$user);
			$user_data["user_id"] = ANONYMOUS_USER;
			$user_data["user"] = "Anonymous";
			$user_data["result"] = LOGINFAILED;
			return $user_data;
		}
		// banned user
		if($status == 'banned') {
			add_error("Login Failed : You have been banned by an administrator of the system.");
			shn_acl_log_msg("Login Failed : Banned user login atttempt.",$uid,$user,1);
			$user_data["user_id"] = ANONYMOUS_USER;
			$user_data["user"] = "Anonymous";
			$user_data["result"] = LOGINFAILED;
			return $user_data;
		}

		$pwd = substr($pwd, 0, 4).$salt.substr($pwd, 4);
		$user_data["result"] = LOGGEDOUT;

		// Create a digest of the password collected from the challenge
		$password_digest = md5(trim($pwd));

		// Formulate the SQL to find the user
		$q = "
			SELECT p_uuid  FROM users
			WHERE user_name = '$user'
			AND password = '$password_digest' and salt='{$salt}';
		";

		$res = $db->Execute($q);
		if(($res == null) || ($res->EOF)) {

			// no result ,so return 1 ,which is  not a valid user_id , the calling application can identify authentication was attempted,but failed
			shn_acl_log_msg("Login Failed : Invalid Password.", $uid, $user, 1);
			$user_data["user_id"] = ANONYMOUS_USER;
			$user_data["user"] = "Anonymous";
			$user_data["result"] = LOGINFAILED;
			_shn_auth_lock_user($uid, $status);
			return $user_data;

		} else {
			if($status == 'try1' || $status == 'try2' || $status == 'try3' || $status == 'active') {
				shn_auth_activate_user($uid);
			}

			$e = explode("/", $_POST['return']);
			$f = $e[sizeof($e)-1];
			$user_data["user_id"] = $res->fields["p_uuid"];
			$user_data["user"] = $user;
			$user_data["result"] = LOGGEDIN;
			$user_data["doHeader"] = true;
			$user_data["headerLocation"] = $f;
			return $user_data;
		}
	}
}



function _shn_auth_lock_user($uid, $status) {

	global $global;

	// Do not lock the default administrator.
	if($uid != 1) {
		$next_status = 'locked';
		switch($status) {
			case 'active' :
				$next_status = 'try1';
				add_error("Login Failure #1 : Invalid user name or password.");
				break;
			case 'try1' :
				$next_status = 'try2';
				add_error("Login Failure #2 : Invalid user name or password.");
				break;
			case 'try2' :
				$next_status = 'try3';
				add_error("Login Failure #3 : Invalid user name or password.");
				break;
			case 'try3' :
				add_error('Login Failure #4 : You have failed to successfully login 4 successive times. If you fail one more time your account will become disabled. You may wish to try the "Forgot my password" button below to reset your password to avoid being locked out of your account.');
				$next_status = 'locked';
				break;
			case 'locked' :
				add_warning('your fucked');
				$next_status = 'locked';
				break;
		}
		$q = "
			update users
			set status = '".$next_status."'
			where p_uuid = '".$uid."';
		";
		$res = $global["db"]->Execute($q);
		if($res == false) {
			add_error($global["db"]->ErrorMsg());
		}
	}
}



/**
 * Changes the password
 * @param string user name
 * @param string old password
 * @param string new password
 * @access public
 */
function shn_change_password($user, $old_pwd, $new_pwd) {

	date_default_timezone_set('America/New_York');
	global $global;
	$db = $global['db'];
	$q = "
		SELECT p_uuid, salt
		FROM users
		WHERE user_id = '$user';
	";
	// AND password = '$password_digest'";

	$res = $db->Execute($q);
	if($res->EOF){
		return false;
	} else {
		$salt = $res->fields["salt"];
	}

	$pwd = substr($old_pwd, 0, 4).$salt.substr($old_pwd, 4);

	// Create a digest of the password collected from the challenge
	$password_digest = md5(trim($pwd));

	// Formulate the SQL to find the user
	$q = "
		SELECT p_uuid  FROM users
		WHERE user_id = '$user'
		AND password = '$password_digest' and salt='{$salt}';
	";

	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		$time = time();
		$new_pwd = substr($new_pwd, 0, 4).$salt.substr($new_pwd, 4);
		$password_digest = md5(trim($new_pwd));

		// Formulate the SQL to find the user
		$q = "
			update users
			set password = '{$password_digest}', changed_timestamp={$time}
			WHERE user_id = '$user'";

		$res=$db->Execute($q);
		return $res;
	}
}



function shn_force_change_password($user = null, $new_pwd, $p_uuid = null) {

	/*
	if(shn_validate_password($user,$new_pwd)==false){
		return true;
	}
	*/
	date_default_timezone_set('America/New_York');
	global $global;
	$db=$global['db'];
	if($p_uuid=null){
		$q = "
			SELECT p_uuid,salt
			FROM users
			WHERE user_name = '$user';
		";
	} else {
		$q = "
			SELECT p_uuid,salt
			FROM users
			WHERE p_uuid = '$user';
		";
	}
	$res = $db->Execute($q);

	if($res->EOF) {
		return true;
	} else {
		$salt = $res->fields["salt"];
	}
	$time = time();
	$new_pwd = substr($new_pwd, 0, 4).$salt.substr($new_pwd, 4);
	$password_digest = md5(trim($new_pwd));

	// update the password
	if($p_uuid = null) {
		$q = "
			update users
			set password = '{$password_digest}', changed_timestamp={$time}
			WHERE user_name = '$user';
		";
	} else {
		$q = "
			update users
			set password = '{$password_digest}', changed_timestamp={$time}
			WHERE p_uuid = '$user';
		";
	}
	$res = $db->Execute($q);
	return false;
}



function shn_change_password_simple($username = null, $newPassword) {

	global $global;
	date_default_timezone_set('America/New_York');
	$q = "
		SELECT *
		FROM users
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
	if($res->EOF) {
		return false;
	} else {
		$salt = $res->fields["salt"];
	}
	$time = time();
	$newPwd = substr($newPassword, 0, 4) . $salt . substr($newPassword, 4);
	$passwordDigest = md5(trim($newPwd));

	$q = "
		UPDATE users
		SET password = '".$passwordDigest."', changed_timestamp = ".$time."
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$res = $global['db']->Execute($q);
	return true;
}



/******** form processing ****/
function shn_auth_add_user_cr(){

	global $global;

	$db      = $global["db"];
	$VARCHAR = 100;
	$error   = false;

	// check for the given name
	if(isset($_POST['given_name']) && strlen(shn_clean($_POST['given_name'])) > 0) {
		list($error, $given_name) = (shn_validate_field($_POST['given_name'], "First Name", $VARCHAR, true)) ? array($error, $_POST["given_name"]) : array(true, NULL);
	} else {
		add_error(_t("Security-Name-Prompt|First name is a required field. Please enter a value."));
		$error = true;
	}

	// check for the family name
	if(isset($_POST['family_name']) && strlen(shn_clean($_POST['family_name'])) > 0) {
		list($error, $family_name) = (shn_validate_field($_POST['family_name'], "Last Name", $VARCHAR, true)) ? array($error, $_POST["family_name"]) : array(true,NULL);
	} else {
		add_error(_t("Security-Name-Prompt|Last name is a required field. Please enter a value."));
		$error = true;
	}

	list($error, $user_name) = (shn_validate_user_name($_POST{"user_name"})) ? array($error, $_POST{"user_name"}) : array(true, NULL);

	//for the moment return true
	list($error, $password) = (shn_validate_password($_POST{"user_name"}, $_POST{"password"})) ? array($error, $_POST{"password"}) : array(true, $_POST{"password"});

	if(is_null($_POST{"re_password"})) {
		$error=true;
		add_error(SHN_ERR_ADMIN_REPWD_INCOMPLETE);
	} else {
		$re_password=trim($_POST{"re_password"});
	}

	if(is_null($_POST{"email_address"}) || !validEmail($_POST{"email_address"})) {
		$error|=true;
		add_error("Enter a valid Email Address.");
	} else {
		$email = trim($_POST{"email_address"});
	}

	if(!($password == $re_password)) {
		$error = true;
		add_error(SHN_ERR_ADMIN_REPWD_WRONG);
	}

	if(trim(strlen($_POST{"given_name"})) > $VARCHAR){
		$error = true;
		add_error(SHN_ERR_ADMIN_REG_MAX);
	} else {
		$given_name = $_POST{"given_name"};
	}

	if(trim(strlen($_POST{"family_name"})) > $VARCHAR){
		$error = true;
		add_error(SHN_ERR_ADMIN_REG_MAX);
	} else {
		$family_name = $_POST{"family_name"};
	}

	if($error == true) {
		return $error;
	} else {
		$role = $_POST["roles"];
		if(shn_auth_add_user($given_name, $family_name, $user_name, $password, $role, null, null, $email) == false) {
			// ok!
		} else {
			$msg = $given_name." ".$family_name." was successfully registered as a User ";
			add_confirmation($msg);
			unset($_POST);
		}
	}
	return $error;
}



function shn_auth_self_signup_cr() {

	global $global;

	$db = $global["db"];
	$VARCHAR = 100;
	$error = null;

	list($error, $user_name) = (shn_validate_user_name($_POST{"user_name"})) ? array($error, $_POST{"user_name"}) : array(true, NULL);

	// for the moment return true
	list($error, $password) = (shn_validate_password($_POST{"user_name"}, $_POST{"password"})) ? array($error || false,$_POST{"password"}) : array($error || true, $_POST{"password"});

	if (is_null($_POST{"re_password"})){
		$error|=true;
		add_error(SHN_AUTH_ERR_REPWD_INCOMPLETE);
	}else {
		$re_password=trim($_POST{"re_password"});
	}

	if (is_null($_POST{"email_address"}) || !validEmail($_POST{"email_address"})){
		$error|=true;
		add_error("Enter a valid Email Address.");
	}else {
		$email=trim($_POST{"email_address"});
	}

	if (!($password==$re_password)){
		$error|=true;
		add_error(SHN_AUTH_ERR_REPWD_WRONG);
	}

	if (trim(strlen($_POST{"given_name"})) > $VARCHAR) {
		$error|= true;
		add_error(SHN_AUTH_ERR_REG_MAX);
	} else {
		$given_name = $_POST{"given_name"};
	}

	if (trim(strlen($_POST{"family_name"})) > $VARCHAR) {
		$error|=true;
		add_error(SHN_AUTH_ERR_REG_MAX);
	} else {
		$family_name=$_POST{"family_name"};
	}

	if($error==true){
		return $error;
	}
	$role = REGISTERED;

	return $error;
}


function _shn_generateSalt($salt = null) {

	if ($salt === null)
	{
		$salt = substr(md5(uniqid(rand(), true)), 0, SALT_LENGTH);
	}
	else
	{
		$salt = substr($salt, 0, SALT_LENGTH);
	}
	//$salt=$salt.
	return $salt;
}



function shn_auth_gen_captcha() {

	// Now lets use md5 to generate a totally random string
	$md5 = md5(microtime() * time());

	// We dont need a 32 character long string so we trim it down to 5
	$string = substr($md5,0,5);

	// Now for the GD stuff, for ease of use lets create the image from a background image.
	global $global;
	$width = 200;
	$height = 80;
	$captcha = imagecreatetruecolor($width, $height);
	imagefilledrectangle($captcha, 0, 0, $width, $height, imagecolorallocatealpha($captcha, 247, 247, 247, 0));

	// draw random rectangles
	$rectangles = 100;
	for($i=0; $i<$rectangles; $i++) {
		$x1    = rand(0, $width*0.9);
		$y1    = rand(0, $height*0.9);
		$x2    = rand($x1, $width);
		$y2    = rand($y1, $height);
		$red   = rand(0, 255);
		$green = rand(0, 255);
		$blue  = rand(0, 255);
		$alpha = rand(0, 127);
		$color = imagecolorallocatealpha($captcha, $red, $green, $blue, $alpha);
		imagefilledrectangle($captcha, $x1, $y1, $x2, $y2, $color);
	}
	for($i=0; $i<$rectangles; $i++) {
		$x1    = rand(0, $width*0.9);
		$y1    = rand(0, $height*0.9);
		$x2    = rand($x1, $width);
		$y2    = rand($y1, $height);
		$red   = rand(0, 255);
		$green = rand(0, 255);
		$blue  = rand(0, 255);
		$alpha = rand(0, 127);
		$color = imagecolorallocatealpha($captcha, $red, $green, $blue, $alpha);
		imagerectangle($captcha, $x1, $y1, $x2, $y2, $color);
	}

	// draw random lines on the string
	$lines = 50;
	for($i=0; $i<$lines; $i++) {
		imagesetthickness($captcha, rand(3,6));
		$red   = rand(0, 191);
		$green = rand(0, 191);
		$blue  = rand(0, 191);
		$alpha = rand(63, 127);
		$x1    = rand(0, $width);
		$y1    = rand(0, $height);
		$x2    = rand(0, $width);
		$y2    = rand(0, $height);
		$color = imagecolorallocatealpha($captcha, $red, $green, $blue, $alpha);
		imageline($captcha, $x1, $y1, $x2, $y2, $color);
	}

	// draw the string.
	for($i=0; $i<strlen($string); $i++) {
		$red   = rand(0, 63);
		$green = rand(0, 63);
		$blue  = rand(0, 63);
		$alpha = rand(16, 47);
		$color = imagecolorallocatealpha($captcha, $red, $green, $blue, $alpha);
		$path = realpath(getcwd()."/res/ttf/");
		$font  = $path."/arial.ttf";
		$angle = rand(-30, 30);
		$x     = (($width/5)*$i)+abs($angle)/2;
		$y     = rand(40,60);
		imagettftext($captcha, 32, $angle, $x, $y, $color, $font, $string[$i]);
	}

	$_SESSION['security_captcha_key'] = md5($string);
	// Output the image
	imagepng($captcha);
}



/**
 * The following constants are the error codes returned by the password policy
 * checking API function to notify the caller about the faliure.
 */
define("LESS_MIN_CHARS",2);
define("MORE_MAX_CHARS",3);
define("REQ_UPPERCASE",4);
define("REQ_LOWERCASE", 9);
define("REQ_NUMBERS",5);
define("REQ_SPECIAL_CHARS",6);
define("HAS_USERNAME",7);


/**
 * Check whether the given password matches the configured password policy.
 *
 * Added 30/10/2007 By Ravith Botejue.
 * Updated 2011.0205 By Greg Miernicki ~ Added Lowercase Checking
 *
 * @param String $password The password
 * @param String $username The username
 * @param Array $password Any extra options as key=>value
 * @return true if the password matches the policy, An Error code if the password doesnt match, stating which rule fails.
 */
function shn_check_password_matches_policy($password, $username, $extra_opts=null) {

	global $global, $conf;

	if(isset($extra_opts['rule_set'])) {
		// specify from where to get the rule set values.
		// this is used in setup because the values are in the session.
		$rule_array = $extra_opts['rule_set'];
	} else {
		// load the rules from conf.
		$rule_array = $conf;
	}
	if(isset($password)){
		if(isset($rule_array['pwd_min_chars']) && $rule_array['pwd_min_chars'] == true) {
			if(strlen($password) < $rule_array['pwd_min_chars']) {
				return LESS_MIN_CHARS;
			}
		}

		if(isset($rule_array['pwd_max_chars']) && $rule_array['pwd_max_chars'] == true) {
			if(strlen($password) > $rule_array['pwd_max_chars']) {
				return MORE_MAX_CHARS;
			}
		}

		if(isset($rule_array['pwd_has_uppercase']) && $rule_array['pwd_has_uppercase'] == true) {
			if(!preg_match('/[A-Z]/', $password)) {
				return REQ_UPPERCASE;
			}
		}

		if(isset($rule_array['pwd_has_lowercase']) && $rule_array['pwd_has_lowercase'] == true) {
			if(!preg_match('/[a-z]/', $password)) {
				return REQ_LOWERCASE;
			}
		}

		if(isset($rule_array['pwd_has_numbers']) && $rule_array['pwd_has_numbers'] == true) {
			if(!preg_match('/[0-9]/', $password)) {
				return REQ_NUMBERS;
			}
		}

		if(isset($rule_array['pwd_has_spchars']) && $rule_array['pwd_has_spchars'] == true) {
			$sp_chars_str = "!@,.#$%\^&\*/?`~+=|:;()-\"'[]{}<>";
			$has_sp_char = false;
			for($i=0; $i < strlen($sp_chars_str); $i++) {
				$sp_chr = substr($sp_chars_str,$i,1);
				if(stripos($password,$sp_chr) !== FALSE) {
					$has_sp_char = true;
					break;
				}
			}

			if($has_sp_char == false) {
				return REQ_SPECIAL_CHARS;
			}
		}

		if(isset($rule_array['pwd_has_username']) && $rule_array['pwd_has_username'] == true) {
			if(stripos($password,$username) !== FALSE){
				return HAS_USERNAME;
			}
		}

		// nothing wrong if control comes here.
		return true;
	} else {
		// no password to match.
		return false;
	}
}



function shn_get_password_policy_message($error_code, $extra_opts = null) {

	global $conf;

	$rule_array = null;
	if(isset($extra_opts['rule_set'])) {
		$rule_array = $extra_opts['rule_set'];
	} else {
		$rule_array = $conf;
	}
	$msg = "";
	switch($error_code) {
		case LESS_MIN_CHARS:
			$msg = sprintf(_t("Security-PWlength-Prompt|The minimum password length is %d"),$rule_array['pwd_min_chars']);
			break;
		case MORE_MAX_CHARS:
			$msg = sprintf(_t("Security-PWlength-Prompt|The maximum password length is %d."),$rule_array['pwd_max_chars']);
			break;
		case REQ_UPPERCASE:
			$msg = _t("Security-PWtype-Prompt|The password should have at least one uppercase character.");
			break;
		case REQ_LOWERCASE:
			$msg = _t("Security-PWtype-Prompt|The password should have at least one lowercase character.");
			break;
		case REQ_NUMBERS:
			$msg = _t("Security-PWtype-Prompt|The password should have at least one numeric character.")	;
			break;
		case REQ_SPECIAL_CHARS:
			$msg = _t("Security-PWtype-Prompt|The password should have at least one special character. eg. !,@.#$%\^&\*/?`~+=|:;-\"'");
			break;
		case HAS_USERNAME:
			$msg = _t("Security-PWtype-Prompt|The username cannot be a part of the password.");
			break;
	}
	return $msg;
}



/**
 * Get the password policy ruleset in an array of strings.
 *
 * @param unknown_type $extra_opts Any extra options.
 * @return Array The password policy ruleset.
 */
function shn_get_password_policy($extra_opts = null) {

	global $conf;

	$policy = array();
	$rule_array = null;
	if(isset($extra_opts['rule_set'])) {
		$rule_array = $extra_opts['rule_set'];
	} else {
		$rule_array = $conf;
	}

	if(isset($rule_array['pwd_min_chars']) && $rule_array['pwd_min_chars'] == true) {
		array_push($policy,sprintf(_t("Security-PWlength-Prompt|The minimum length of the password is %d characters."),$rule_array['pwd_min_chars']));
	}

	if(isset($rule_array['pwd_max_chars']) && $rule_array['pwd_max_chars'] == true) {
		array_push($policy,sprintf(_t("Security-PWlength-Prompt|The maximum length of the password is %d characters."),$rule_array['pwd_max_chars']));
	}

	if(isset($rule_array['pwd_has_uppercase']) && $rule_array['pwd_has_uppercase'] == true) {
		array_push($policy,_t("Security-PWtype-Prompt|Must have at least one uppercase character."));
	}

	if(isset($rule_array['pwd_has_lowercase']) && $rule_array['pwd_has_lowercase'] == true) {
		array_push($policy,_t("Security-PWtype-Prompt|Must have at least one lowercase character."));
	}

	if(isset($rule_array['pwd_has_numbers']) && $rule_array['pwd_has_numbers'] == true) {
		array_push($policy,_t("Security-PWtype-Prompt|Must have at least one numeral (0-9)."));
	}

	if(isset($rule_array['pwd_has_spchars']) && $rule_array['pwd_has_spchars'] == true) {
		array_push($policy,_t("Security-PWtype-Prompt|Should have one or more of the following characters: '!@,.#$%\^&\*/?`~+=|:;()-\"'[]{}<>' "));
	}

	if(isset($rule_array['pwd_has_username']) && $rule_array['pwd_has_username'] == true) {
		array_push($policy,_t("Security-PWtype-Prompt|The password cannot contain your username."));
	}

	return $policy;
}



function shn_auth_add_role_cr() {

	global $global;

	$db = $global['db'];

	if($_POST['role_name']==null || strlen(trim($_POST['role_name']))==0){
		add_error(_t("Security-role-Prompt|Please enter a valid Role name."));
	}else{
		$role_name = ucwords(trim($_POST['role_name']));
		$select_query = "SELECT COUNT(group_name) FROM sys_user_groups WHERE group_name=?";
		$res = $db->Execute($select_query,array($role_name));

		if($res!=false && (($res->fields[0]*1)==0)){

			$select_query = "SELECT MAX(group_id) FROM sys_user_groups";
			$res = $db->Execute($select_query);

			if($res){
				$max_id = ($res->fields[0])+1;
				$query = "INSERT INTO sys_user_groups(group_id,group_name) VALUES(?,?)";
				$global['db']->Execute($query,array($max_id,$role_name));

				add_confirmation(sprintf(_t("Security-role-Confirm|The role '%s' was successfully added."),$role_name));
				// clear the value so that the text box becomes empty.
				$_POST['role_name'] = "";
			}
		}else{
			add_error(_t("Security-role-Error|A role with the name you entered already exists. Please enter a different role name."));
		}
	}
	shn_admin_add_role();
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
		if(!$conf['mobile_server']) {
			// not mobile server
			if($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A"))) {
				// domain not found in DNS
				$isValid = false;
			}
		}
	}
	return $isValid;
}


