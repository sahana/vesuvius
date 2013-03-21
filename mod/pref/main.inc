<?
/**
 * @name         User Preferences
 * @version      13
 * @package      pref
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


global $tabid;
$tabid = isset($_GET['tabid']) ? $_GET['tabid'] : 0;
$tabid = "&tabid=".$tabid;

require_once($global['approot']."/inc/lib_modules.inc");
require_once($global['approot']."/inc/lib_menu.inc");
require_once($global['approot']."/inc/lib_form.inc");
require_once($global['approot']."/inc/lib_validate.inc");
require_once($global['approot']."/inc/lib_errors.inc");
require_once($global['approot']."/mod/lpf/lib_lpf.inc");
require_once($global['approot']."/inc/lib_security/lib_auth.inc");



function shn_pref_default() {

	global $global;

	shn_tabmenu_open();
	shn_tabmenu_item("session",  _t("Pref-TableHeader|Session Information"), "pref");
	shn_tabmenu_item("password", _t("Pref-TableHeader|Change My Password"),  "pref");
	shn_tabmenu_close();

	$control = "";

	if(isset($_GET['forgot'])) {
		$control = "shn_pref_forgotPassword";

	} elseif(isset($_GET['password'])) {
		$control = "shn_pref_ch_passwd";

	} elseif(isset($_GET['passwdp'])) {
		$control = "shn_pref_ch_passwd_p";

	} elseif(isset($_GET['signup2'])) {
		$control = "shn_pref_signup2";

	} elseif(isset($_GET['login'])) {
		$control = "shn_pref_loginForm";
	}

	if($control == "") {
		$control = "shn_pref_session";
	}

	$control();
}



/** This function displays the home page of the User Preferences */
function shn_pref_session() {

	global $global;

	echo "<br><div id=\"home\">";
	echo '
		<div id="rezMain" class="mainArea" style="opacity: 1; width: 300px;">
			<table class="emTable">
				<tbody>
				<tr>
					<td style="padding-left: 8px; text-align: left; font-weight: bold;" colspan=2 class="mainRowOdd">Currently Logged in as...</td>
				</tr>
				<tr>
					<td style="padding-left: 8px; text-align: right;" class="mainRowEven">Username</td>
					<td style="padding-left: 8px; text-align: left; font-weight: bold;" class="mainRowEven">'.$_SESSION['user'].'</td>
				</tr>
				<tr>
					<td style="padding-left: 8px; text-align: right;" class="mainRowOdd">Full Name</td>
					<td style="padding-left: 8px; text-align: left; font-weight: bold;" class="mainRowOdd">'.$_SESSION['full_name'].'</td>
				</tr>
				<tr>
					<td style="padding-left: 8px; text-align: right;" class="mainRowEven">User Group</td>
					<td style="padding-left: 8px; text-align: left; font-weight: bold;" class="mainRowEven">'.$_SESSION['group_name'].'</td>
				</tr>
				<tr>
					<td style="padding-left: 8px; text-align: right;" class="mainRowOdd">Locale</td>
					<td style="padding-left: 8px; text-align: left; font-weight: bold;" class="mainRowOdd">'.$_SESSION['locale'].'</td>
				</tr>
				</tbody>
			</table>
		</div>
	';
	echo "</div>";
}



function shn_pref_makeGoogleLoginLink() {

	global $global;
	global $conf;

	require_once($global['approot']."/3rd/google-api-php-client/src/apiClient.php");
	require_once($global['approot']."/3rd/google-api-php-client/src/contrib/apiOauth2Service.php");

	$client = new apiClient();
	$client->setApplicationName($conf['site_name']);
	$client->setClientId($conf['oauth_google_clientId']);
	$client->setClientSecret($conf['oauth_google_clientSecret']);
	$client->setRedirectUri($conf['oauth_google_redirectUri']);
	$client->setDeveloperKey($conf['oauth_google_developerKey']);
	$client->setAccessType('online');

	$oauth2 = new apiOauth2Service($client);

	$authUrl = $client->createAuthUrl();

	echo '
		<div class="form-container" style="padding: auto;">
			<form>
				<fieldset style="width: 500px;">
				<legend>Login with</legend>
				<a class="styleTehButton googleButton" href="'.$authUrl.'"><img height=23 src="theme/lpf3/img/google34px.png"></a>
				<hr class="loginHr">
				<span class="loginText">You may login with a 3rd party service instead of registering for a new user account.</span>
				</fieldset>
			</form>
		</div>
	';
	//	<pre>('.print_r(get_defined_vars(), true).')</pre>
}


function shn_pref_loginForm($return = null) {

	global $conf;
	global $global;

	if ($_SESSION['logged_in'] != true ) {

		if($return != null) {
			$returnVal = $return;
		} else {
			$returnVal = $_SERVER['REQUEST_URI'];
		}

		echo '
			<div class="form-container" style="padding: auto;">
				<form method="post" action="auth" id="form0" name="form0">
				<fieldset id="noIdDefined" style="width: 500px;">
				<legend>Login</legend>
				<label for="user_name">Username </label><input type="text" name="user_name" id="user_name" tabindex="1" autocomplete="off"><br>
				<div class="brake"></div>
				<label for="pswd">Password </label><input type="password" name="password" id="pswd" autocomplete="off" tabindex="2"><br>
				<div class="brake"></div>
				<br>
				<div style="text-align: center;">
					<input type="submit" value="Login" class="styleTehButton" tabindex="3">
				</div>
				</fieldset>
				<input type="hidden" name="return" value="'.$returnVal.'">
				</form>
			</div>
		';

		if($conf['oauth_google_enable']) {
			shn_pref_makeGoogleLoginLink();
		}

		echo '
			<div class="form-container" style="padding: auto;">
				<form>
					<fieldset style="width: 500px;">
					<legend>Register / Forgot Password</legend>
					<div style="text-align: center;">
						<input id="followButton" class="styleTehButton" type="button" value="Register as a new user" onclick="register();">
						&nbsp; &nbsp; &nbsp; &nbsp;
						<input id="followButton" class="styleTehButton" type="button" value="Forgot my password" onclick="forgot();">
					</div>
					<hr class="loginHr">
					<span class="loginText">You can register for a new user account or reset your password in the event it is lost.</span>
					</fieldset>
				</form>
			</div>
			<script>
				function register() {
					window.location = \'register\';
				}
				function forgot() {
					window.location = \'forgot\';
				}
			</script>
		';

		/*
				<div id=\"switchOpenId\">
					<a href=\"#\" onclick=\"switchLogin('loginform','openid_loginform');\">Login with an OpenID></a>
				</div>
			<div id=\"openid_loginform\">
				<form action=\"\" method=\"get\">
					<fieldset id=\"openIdFieldset\">
						<label>OpenID</label>
						<input type=\"text\" name=\"identity_url\" id=\"openid_login\" />
						<input id=\"submitButtonOpen\" type=\"submit\" value=\"Login\" autocomplete=\"off\"/>
					</fieldset>
				</form>
				<div id=\"switchNormalLogin\">
					<a href=\"#\" onclick=\"switchLogin('openid_loginform','loginform');\">Go back to the Normal Login</a>
				</div>
			</div>
			<script type=\"text/javascript\">
				switchLogin('openid_loginform','loginform');
			</script>
		*/


		// force focus to login box...
		echo "
			<script>
				window.onload = function() {
					document.getElementById(\"user_name\").focus();
				};
			</script>
		";

	} else {
		echo "
			<div id=\"loggedIn\">
					<b>Currently logged in as :</b><br>
					".$_SESSION['group_name']." / ".$_SESSION['user_name']."<br><br>
					<span id=\"logoutLink\" class=\"styleTehButton\"><a href=\"logout\">Logout</a></span>
			</div>
		";
	}
}




/** Forgot Password Controller */
function shn_pref_forgotPassword() {

	global $global;

	// step 0 ~ email + captcha form
	if(!isset($_REQUEST['zz']) || trim($_REQUEST['zz']) == "") {
		shn_pref_emailCaptchaForm();

	// step 1 ~ verify captcha/email and send 1st email with confirmation link
	} else if($_REQUEST['zz'] == "1") {
		if($_SESSION['security_captcha_key'] != md5($_POST["captcha"])) {
			add_error(_t("Pref-ForgetPassword-Error|Please provide the text in the image correctly to prove you are human."));
			shn_pref_emailCaptchaForm();
		} else {
			// check if the email address is associated with a sahana account
			$email = trim($_POST['email']);

			$q = "
				SELECT *
				FROM `users` u, `contact` c
				WHERE c.p_uuid = u.p_uuid
				AND c.contact_value = '".mysql_real_escape_string($email)."'
				AND u.status = 'active'
				LIMIT 1;
			";
			$result = $global['db']->Execute($q);
			if($row = $result->FetchRow()) {
				$email = $row['contact_value'];
				echo "
					<h2>Forgot My Password</h2>
					<div id=\"formcontainer\">
						<br>
						An email has been sent to the address you provided: <b>".$email."</b>, with your username and a link that you must click on to reset your password.
					</div>
				";

				$user_id = $row['user_id'];
				$user_name = $row['user_name'];
				$confirmation = md5(uniqid(rand(), true));
				// needed for users table to work from here on out......
				// ALTER TABLE  `users` ADD  `confirmation` VARCHAR( 255 ) NULL DEFAULT NULL

				$url = makeBaseUrl() ."pref?forgot&zz=2&c=".base64_encode($confirmation)."&u=".base64_encode($user_id);

				$q = "
					UPDATE  `users`
					SET  `confirmation` =  '".$confirmation."'
					WHERE  `users`.`user_id` = '".$user_id."';
				";
				$result = $global['db']->Execute($q);

				// send out the password reset link in an email
				$p = new pop();
				$subject  = "Your login details...";

				$bodyHTML = "
					Dear ".$user_name.",<br>
					<br>
					You have requested a new password for our site. If you did not request this, please ignore this email. It will expire and become useless in 24 hours time.<br>
					<br>
					To reset your password, please visit the following page:<br>
					<a href=\"".$url."\">".$url."</a><br>
					<br>
					When you visit that page, your password will be reset, and the new password will be emailed to you.<br>
					<br>
					Your username is: <b>".$user_name."</b><br>
					<br>
					All the best,<br>
					Admins<br>
				";

				$bodyAlt = "
					Dear ".$user_name.",\n
					\n
					You have requested a new password for our site. If you did not request this, please ignore this email. It will expire and become useless in 24 hours time.\n
					\n
					To reset your password, please visit the following page:\n
					".$url."\n
					\n
					When you visit that page, your password will be reset, and the new password will be emailed to you.\n
					\n
					Your username is: ".$user_name."\n
					\n
					All the best,\n
					Admins\n
				";
				$p->sendMessage($email, $email, $subject, $bodyHTML, $bodyAlt);

				// try and resend once if it fails
				if(!$p->sentStatus) {
					$p->sendMessage($email, $email, $subject, $bodyHTML, $bodyAlt);
				}

			// account is inactive or the user does not exist with the provided email
			} else {
				echo "
					<h2>Forgot My Password</h2>
					<div id=\"formcontainer\">
						<br>
						The email address you provided: <b>".$email."</b>, does not match any account in our system.
					</div>
				";
			}
		}

	// step 2 ~ confirmed email link clicked ~ create and email new password if confimration is correct
	} else if($_REQUEST['zz'] == "2") {
		$error = false;
		$zz = 2;
		if(!isset($_REQUEST['c']) || !isset($_REQUEST['u'])) {
			$error = true;
		} else {
			$user_id      = base64_decode($_REQUEST['u']);
			$confirmation = base64_decode($_REQUEST['c']);

			$q = "
				SELECT *
				FROM `users` u, contact c
				WHERE u.status = 'active'
				AND `user_id` = '".$user_id."'
				AND `confirmation` = '".mysql_real_escape_string($confirmation)."'
				AND c.p_uuid = u.p_uuid
				LIMIT 1;
			";

			$result = $global['db']->Execute($q);
			if($row = $result->FetchRow()) {
				$email     = $row['contact_value'];
				$user_name = $row['user_name'];
				$p_uuid    = $row['p_uuid'];
				$salt      = $row['salt'];
			} else {
				$error = true;
			}
		}

		// valid code ~ so reset password and send the email
		if(!$error) {

			// reset password
			$time = time();

			$p1a = rand(10e16, 10e20);
			$p1b = base_convert($p1a, 10, 36);
			$p1c = strtoupper($p1b);
			$part1 = substr($p1c, 0, 8);

			$p2a = rand(10e16, 10e20);
			$p2b = base_convert($p2a, 10, 36);
			$part2 = substr($p2b, 0, 8);

			$new_pass = $part1.$part2;

			// O, 0, i, l, 1 characters are removed ~ too hard for old people to read!
			$search = array('O', '0', 'i', '1', 'l');
			$replace = array('Z', 'Z', 'Z', 'Z', 'Z');
			$new_pass = str_replace($search, $replace, $new_pass);

			$new_pwd = substr($new_pass, 0, 4).$salt.substr($new_pass, 4);

			$password_digest = md5(trim($new_pwd));
			$q3 = "
				update users
				set password = '{$password_digest}', changed_timestamp = {$time}, confirmation = NULL
				WHERE p_uuid = '$p_uuid' ;
			";
			$result = $global['db']->Execute($q3);

			// send out the new password in an email
			$p = new pop();
			$subject  = "Your login details...";
			$url = makeBaseUrl()."password";

			$bodyHTML = "
				Dear ".$user_name.",<br>
				<br>
				As you requested, your password has now been reset. Your new details are as follows:<br>
				<br>
				Username: <b>".$user_name."</b><br>
				Password: <b>".$new_pass."</b><br>
				<br>
				To change your password please visit our site, login, and you will be offered the choice to create a new password: <br>
				<a href=\"".$url."\">".$url."</a><br>
				<br>
				All the best,<br>
				Admins<br>
			";

			$bodyAlt = "
				Dear ".$user_name.",\n
				\n
				As you requested, your password has now been reset. Your new details are as follows:\n
				\n
				Username: ".$user_name."\n
				Password: ".$new_pass."\n
				\n
				To change your password please visit our site, login, and you will be offered the choice to create a new password: \n
				".$url."\n
				\n
				All the best,\n
				Admins\n
			";
			$p->sendMessage($email, $email, $subject, $bodyHTML, $bodyAlt);
			// try and resend once if it fails
			if(!$p->sentStatus) {
				$p->sendMessage($email, $email, $subject, $bodyHTML, $bodyAlt);
			}

			echo "
				<h2>Forgot My Password</h2>
				<div id=\"formcontainer\">
					<br>
					Your password has been reset and the new password emailed to you.<br>
				</div>
			";

		// invalid code, so tell em!
		} else {
			echo "
				<h2>Forgot My Password</h2>
				<div id=\"formcontainer\">
					<br>
					Your confirmation code is either invalid or expired.
				</div>
			";
		}
	} else {
		echo "
			<h2>Forgot My Password</h2>
			<div id=\"formcontainer\">
				<br>
				Your confirmation code is either invalid or expired.
			</div>
		";
	}

}




/** Generates a form to rest a forgotten password */
function shn_pref_emailCaptchaForm() {

	global $global;

	echo "
		<h2>Forgot My Password</h2>
		<div id=\"formcontainer\">
		<br>
		If you have forgotten your username or password, you can request to have your username emailed to you and to reset your password.<br>
		When you fill in your registered email address, you will be sent instructions on how to reset your password.<br>
	";
	shn_form_fopen("forgotPassword&zz=1", "pref");
		shn_form_fsopen("Account Email");
			$extra_opts['req'] = true;
			shn_form_text("Email Address ", 'email', 'size="30"', $extra_opts);
		shn_form_fsclose();
		shn_form_fsopen("Verify that you are human");
			echo "<br><img src=\"index.php?stream=image&mod=pref&act=captcha\" /><br>";
			if(isset($_POST['captcha'])) {
				unset($_POST['captcha']);
			}
			shn_form_text("Enter the text in the above image ", 'captcha', 'size="30"', $extra_opts);
		shn_form_fsclose();
		shn_form_submit(_t("Pref-ForgetPassword-Button|Submit"), "class=\"styleTehButton\"");
		echo "</br>";
	shn_form_fclose();
	echo "</div>";
}



/** Generates a form to add an user */
function shn_pref_signup($title="Create Your Account", $mod="pref", $act="signup2", $error=false) {

	global $global;

	if($error) {
		display_errors();
	}
	echo "<h2>Sign up for a user account</h2>";

	$policy = shn_get_password_policy();

	if(count($policy) > 0){
		echo "<br><br><h4>Passwords must adhere to the following rules :</h4>";
		for($i=0; $i < count($policy); $i++) {
			echo ($i+1).". ".$policy[$i]."<br/>";
		}
	}

	echo "<div id=\"formcontainer\">";
	shn_form_fopen2("register2", null);
	shn_form_fsopen("Account Details");
	$extra_opts['req'] = true;

	shn_form_text("First Name ",    'given_name',    'size="30"', $extra_opts);
	shn_form_text("Last Name ",     'family_name',   'size="30"', $extra_opts);
	shn_form_text("User Name ",     'user_name',     'size="30"', $extra_opts);
	shn_form_text("Email Address ", 'email_address', 'size="30"', $extra_opts);

	if(isset($_POST['password']) || isset($_POST['re_password'])) {
		unset($_POST['password']);
		unset($_POST['re_password']);
	}
	shn_form_password("Password for Login", "password", null, $extra_opts);
	shn_form_password("Confirm Password", "re_password", null, $extra_opts);
	shn_form_fsclose();
	$extra_opts['req']=true;

	shn_form_fsopen("OpenId Login Details", "openIdSignup");
	echo "<div class=\"info\">You can use an OpenID to login if you prefer.</div><br />";
	shn_form_text("OpenID ", 'openid', 'size="30"', null);
	shn_form_fsclose();

	shn_form_fsopen("Verify that you are human");
	echo "<br><img src=\"index.php?stream=image&mod=pref&act=captcha\" /><br>";
	if(isset($_POST['captcha'])) {
		unset($_POST['captcha']);
	}
	shn_form_text("Enter the text in the above image ", 'captcha', 'size="30"', $extra_opts);
	shn_form_fsclose();
 	shn_form_submit(_t("Pref-adduser-Button|Submit"), "class=\"styleTehButton\"");
	echo "</br><br/><br/>";
	shn_form_fclose();
	echo "</div>";
}



function shn_pref_signup2() {

	if(shn_auth_self_signup_cr() == true){
		shn_pref_signup();
		if(!isset($_POST["captcha"]) || ($_SESSION['security_captcha_key'] != md5($_POST["captcha"]))) {
			add_error(_t("Pref-Signup-Error|Please provide the text in the image correctly to prove you are human."));
			return;
		}
		shn_pref_signup();

	} else {
		if($_SESSION['security_captcha_key'] != md5($_POST["captcha"])) {
			add_error(_t("Pref-Signup-Error|Please provide the text in the image correctly to prove you are human."));
			shn_pref_signup();
			return;
		}
		$ret = shn_auth_add_user($_POST['given_name'], $_POST['family_name'], $_POST['user_name'], $_POST['password'], $role=REGISTERED, null, null, $_POST['email_address']);
		if($ret) {
			$msg = "A new user account has been created for you and is now active. Please login below using your credentials.";
			add_confirmation($msg);
			shn_pref_loginForm('settings');
		} else {
			shn_pref_signup();
		}
	}
}



function shn_image_pref_captcha() { shn_auth_gen_captcha(); }



/** Generates a form to change the password */
function shn_pref_ch_passwd() {

	global $global;

	echo "
		<br>
	";
	if($error) {
		display_errors();
	}
	?><div id="formcontainer"><?php
	$act    = "ch_passwd_cr";
	$mod    = "pref";
	$policy = shn_get_password_policy();

	if(count($policy) > 0){
		?><h4><?php echo _t("Pref-ChangePassword-Text|You new password must adhere to following rules:") ?></h4><br><?php
		for($i=0; $i < count($policy); $i++) {
			echo ($i+1).". ".$policy[$i]."<br/>";
		}
	}
	?><br><br><?php
	shn_form_fopen2("pref?passwdp", null, null, null, "width: 600px;");
	shn_form_fsopen(_t("Pref-ChangePassword-TableHeader|Fill in these required fields to change your password"));
	$extra_opts['req']=true;
	shn_form_password("Old Password", "old_password", null, $extra_opts);
	shn_form_password("New Password", "password", null, $extra_opts);
	shn_form_password("Confirm New Password", "re_password", null, $extra_opts);
	$user_id=$_SESSION["user_id"];
	shn_form_hidden(array('user'=>$user_id));
	shn_form_fsclose();
	echo "<br>";
 	shn_form_submit(_t("Pref-ChangePassword-Button|Change Password"), "class=\"styleTehButton\"");
	echo "<br>";
	shn_form_fclose();
	echo "</div>";
}








function shn_pref_ch_passwd_p() {

	global $global;

	$error = false;
	$user = $_POST["user"];
	if($user != $_SESSION["user_id"]){
		add_error("Session Hijacked");
		return false;
	}

	$db = $global['db'];

	if (shn_validate_password($_SESSION['user'], $_POST["password"]) == false) {
		shn_pref_ch_passwd();
		return false;
	}

	if((null == $_POST["old_password"]) or (is_null($_POST["old_password"]))) {
		$error=true;
		add_error(_t("Pref-ChangePassword-Error|Old password cannot be empty!"));
		shn_acl_log_msg("Password Change error: Old password cannot be empty");
	} else {
		$old_password=trim($_POST{"old_password"});
	}

	if((null == $_POST["password"]) or (is_null($_POST["password"]))) {
		$error = true;
		add_error(_t("Pref-ChangePassword-Error|New password cannot be empty!"));
		shn_acl_log_msg("Password Change error: User password cannot be empty");
	} else {
		$new_password=trim($_POST{"password"});
	}

	if((null==$_POST["re_password"])or(is_null($_POST["re_password"]))) {
		$error=true;
		add_error(_t("Pref-ChangePassword-Error|You left the confirm password field blank."));
		shn_acl_log_msg("Password Change error: User Confirm password cannot be empty");
	} else {
		$re_password=trim($_POST{"re_password"});
	}

	if(!($new_password==$re_password)) {
		$error=true;
		add_error(_t("Pref-ChangePassword-Error|Your new password did not match when you retyped it."));
		shn_acl_log_msg("Password Change error: User password and confirm password should match");
	}

	if($error){
		return false;
	}

	date_default_timezone_set('America/New_York');

	$curr = time();
	$curr_date= date("Ymd",$curr);

	//echo gmdate();

	$sql="select password,changed_timestamp from users where user_name='{$_SESSION['user']}'";
	$res=$db->Execute($sql);
	$tmp=$res->fields["changed_timestamp"];
	$old_pwd=$res->fields["password"];
	$date= date("Ymd",$tmp);
	global $conf;

    	if(!isset($conf['pwd_no_change_limit']) && ($conf['pwd_no_change_limit'] == true) && ($date == $curr_date)){
		global $conf;
		echo "<pre>ok".print_r($conf, true)."</pre>";
    		add_error(_t("Pref-ChangePassword-Error|You cannot change the password more than once in one day"));
    		shn_acl_log_msg("Password Change error: tried to change the password more than once in one day");
    		shn_auth_form_ch_pwd();
    		return false;
    	}else{
		$pwd=md5(trim($_POST["password"]));
		$sql="select count(p_uuid) as count from old_passwords where p_uuid='{$user}'";
		$res=$db->Execute($sql);
		$count=$res->fields["count"];

		if(($res==null) or ($res->EOF) or ($count==0)){
			$insert=true;
		}else{

		// password the same as one of the last 4?
		if($count < 4){
			$insert=true;
		}else{
			$insert=false;
		}

		$sql="select password from old_passwords where p_uuid='{$user}' and password='{$pwd}' order by changed_timestamp";
		$res=$db->Execute($sql);

		if(($res==null) or ($res->EOF)){
			$sql="select password from old_passwords where p_uuid='{$user}' order by changed_timestamp DESC ";
			$res=$db->Execute($sql);
			$tmp=$res->fields["password"];
			$sql="update old_passwords set password='{$old_pwd}', changed_timestamp=$curr where p_uuid='{$user}' and password='{$tmp}'";
			$res=$db->Execute($sql);
		}else{
			add_error(_t("Pref-ChangePassword-Error|You cannot choose one of the recent four passwords"));
			shn_acl_log_msg("Password Change error: tried to choose one of the recent four passwords");
			shn_auth_form_ch_pwd();
			return false;
		}
		}
		if($insert==true) {
			$sql="INSERT INTO old_passwords (p_uuid,password,changed_timestamp) SELECT users.p_uuid,users.password,$curr FROM users WHERE users.p_uuid='{$user}'";
			$res=$db->Execute($sql);
		}
	}
	if(shn_change_password($user, $old_password, $new_password) == false) {
		shn_auth_form_ch_pwd();
	} else {
		$msg = _t("Pref-ChangePassword-Confirm| Succesfully changed Password");
		add_confirmation($msg);
	}
	shn_pref_session();
}



function _shn_admin_ch_pwd_cr() {

	global $global;

	$db = $global["db"];
	$VARCHAR = 100;

	if((null == $_POST["old_password"])  || (is_null($_POST["old_password"]))) {
		$error = true;
		add_error(_t("Pref-AdminChangePassword-Error|Old password cannot be empty"));
	} else {
		$old_password = trim($_POST{"old_password"});
	}
	if((null == $_POST["password"]) || (is_null($_POST["password"]))) {
		$error = true;
		add_error(_t("Pref-AdminChangePassword-Error|New password cannot be empty"));
	} else {
		$password = trim($_POST{"password"});
	}
	if((null == $_POST["re_password"]) || (is_null($_POST["re_password"]))) {
		$error = true;
		add_error(_t("Pref-AdminChangePassword-Error|Confirm password cannot be empty"));
	} else {
		$re_password = trim($_POST{"re_password"});
	}
	if(!($password == $re_password)){
		$error = true;
		add_error(_t("Pref-AdminChangePassword-Error|Password and Confirm Password should match"));
	}
	if($error == true) {
		return $error;
	}
	$user_id = trim($_POST{"user"});
	$error = shn_change_password($user_id,$old_password,$password);
	if($error == true){
		return $error;
	}
	shn_admin_ch_pwd($error);
}



function shn_pref_tracking() {

	global $conf;
	global $global;

	$showAll = true;

	// persons in the current event //////////////////////////////////////////////////////////
	if(isset($_GET['shortname']) && $_GET['shortname'] != "") {
		$showAll = false;

		// current event reported
		$q = "
			SELECT *
			FROM person_to_report u, person_uuid p, incident i
			WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = u.p_uuid
			AND p.incident_id = i.incident_id
			AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."';
		";
		$r  = $global['db']->Execute($q);
		$count = 0;
		while($row = $r->FetchRow()) {
			if($count == 0) {
				echo "
					<div class=\"form-container\"><form><fieldset>
					<legend>People that I'm following or Reported for the ".$row['name']."</legend>
					<table id=\"repLog\">
					<tr>
					<td class=\"noBorderLeft evener\" >Origin ID / Origin URL</td>
					<td class=\"noBorderLeft evener\" >Full Name</td>
					</tr>
				";

			}
			if($count%2 == 0) {
				$class = "odder";
			} else {
				$class = "evener";
			}
			echo "
				<tr>
				<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
				<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['p_uuid']."</b></a></td>
				<td class=\"noBorderLeft ".$class."\" >
				<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['full_name']."</b></a></td>
				</tr>
			";
			$count++;
		}

		if($count == 0) {
			echo "
				<div class=\"form-container\"><form><fieldset>
				<legend>People that I'm following or Reported for the current event.</legend>
				<table id=\"repLog\">
			";
		}

		// current event following
		$q  = "
			SELECT *
			FROM person_followers f, person_uuid p, incident i
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = f.p_uuid
			AND p.incident_id = i.incident_id
			AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."';
		";
		$r  = $global['db']->Execute($q);
		while($row = $r->FetchRow()) {
			if($count%2 == 0) {
				$class = "odder";
			} else {
				$class = "evener";
			}
			echo "
				<tr>
				<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
				<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['p_uuid']."</b></a></td>
				<td class=\"noBorderLeft ".$class."\" >
				<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['full_name']."</b></a></td>
				</tr>
			";
			$count++;
		}

		if($count == 0) {
			echo "<tr><td class=\"noBorderLeft\" colspan=2>No persons reported.</td></tr>";
		}
		echo "</table>";
		echo "</fieldset>";
		echo "</form></div><br>";
	}



	// Personally Reported ///////////////////////////////////////////////////////////////////
	if($showAll) {
		$other = "";
	} else {
		$other = "Other ";
	}
	echo "
		<div class=\"form-container\"><form><fieldset>
		<legend>".$other."People That I Have Reported</legend>
	";

	if($showAll) {
		$q  = "
			SELECT *
			FROM person_to_report u, person_uuid p, incident i
			WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = u.p_uuid
			AND p.incident_id = i.incident_id;
		";
	} else {
		$q  = "
			SELECT *
			FROM person_to_report u, person_uuid p, incident i
			WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = u.p_uuid
			AND p.incident_id = i.incident_id
			AND i.shortname <> '".mysql_real_escape_string($_GET['shortname'])."';
		";
	}
	$r  = $global['db']->Execute($q);

	$count = 0;
	while($row = $r->FetchRow()) {
		if($count == 0) {
			echo "
				<table id=\"repLog\">
				<tr>
				<td class=\"noBorderLeft evener\" >Origin ID / Origin URL</td>
				<td class=\"noBorderLeft evener\" >Full Name</td>
				<td class=\"noBorderLeft evener\" >Event</td>
				</tr>
			";

		}
		if($count%2 == 0) {
			$class = "odder";
		} else {
			$class = "evener";
		}
		echo "
			<tr>
			<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
			<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['p_uuid']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['full_name']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			".$row['name']."</b></td>
			</tr>
		";
		$count++;
	}
	if($count == 0) {
		echo "<tr><td class=\"noBorderLeft\" colspan=3>No persons reported.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset>";
	echo "</form></div><br>";



	// Persons Following ///////////////////////////////////////////////////////////////////////
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>".$other."People That I Am Following</legend>";

	if($showAll) {
		$q  = "
			SELECT *
			FROM person_followers f, person_uuid p, incident i
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = f.p_uuid
			AND p.incident_id = i.incident_id;
		";
	} else {
		$q  = "
			SELECT *
			FROM person_followers f, person_uuid p, incident i
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = f.p_uuid
			AND p.incident_id <> i.incident_id
			AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."';
		";
	}
	$r  = $global['db']->Execute($q);

	$count = 0;
	echo "<table id=\"followLog\">";
	while($row = $r->FetchRow()) {
		if($count == 0) {
			echo "
				<table id=\"repLog\">
				<tr>
				<td class=\"noBorderLeft evener\" >Origin ID / Origin URL</td>
				<td class=\"noBorderLeft evener\" >Full Name</td>
				<td class=\"noBorderLeft evener\" >Event</td>
				</tr>
			";

		}
		if($count%2 == 0) {
			$class = "odder";
		} else {
			$class = "evener";
		}
		echo "
			<tr>
			<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
			<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['p_uuid']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			<a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\"><b>".$row['full_name']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			".$row['name']."</b></td>
			</tr>
		";
		$count++;
	}
	if($count == 0) {
		echo "<tr><td class=\"noBorderLeft\" colspan=3>Not following any persons.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset>";
	echo "</form></div>";
}





