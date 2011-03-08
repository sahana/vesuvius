<?
/**
 * @name         User Preferences
 * @version      1.0
 * @package      pref
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once "tracker.inc";


/**
 * Forgot Password Controller
 * @return void
 * @access public
 */
function shn_pref_forgotPassword() {
	global $global;

	// step 0 ~ email + captcha form
	if(!isset($_REQUEST['zz']) || trim($_REQUEST['zz']) == "") {
		shn_pref_emailCaptchaForm();

	// step 1 ~ verify captcha/email and send 1st email with confirmation link
	} else if($_REQUEST['zz'] == "1") {
		if($_SESSION['security_captcha_key'] != md5($_POST["captcha"])) {
			add_error(_t("Please provide the text in the image correctly to prove you are human."));
			shn_pref_emailCaptchaForm();
		} else {
			// check if the email address is associated with a sahana account
			$email = trim($_POST['email']);

			$q = "
				SELECT *
				FROM `users` u, `contact` c
				WHERE c.pgoc_uuid = u.p_uuid
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

				$url = shn_pref_makeBaseUrl() ."index.php?mod=pref&act=forgotPassword&zz=2&c=".base64_encode($confirmation)."&u=".base64_encode($user_id);

				$q = "
					UPDATE  `users`
					SET  `confirmation` =  '".$confirmation."'
					WHERE  `users`.`user_id` = '".$user_id."';
				";
				$result = $global['db']->Execute($q);

				// send out the password reset link in an email
				require($global['approot']."mod/lpf/lib_lpf.inc");
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
				AND c.pgoc_uuid = u.p_uuid
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
			$new_pass = mt_rand(123456789, 1234567890);
			$new_pwd = substr($new_pass, 0, 4).$salt.substr($new_pass, 4);
			$password_digest = md5(trim($new_pwd));
			$q3 = "
				update users
				set password = '{$password_digest}', changed_timestamp = {$time}, confirmation = NULL
				WHERE p_uuid = '$p_uuid' ;
			";
			$result = $global['db']->Execute($q3);

			// send out the new password in an email
			require($global['approot']."mod/lpf/lib_lpf.inc");
			$p = new pop();
			$subject  = "Your login details...";
			$url = shn_pref_makeBaseUrl()."index.php";

			$bodyHTML = "
				Dear ".$user_name.",<br>
				<br>
				As you requested, your password has now been reset. Your new details are as follows:<br>
				<br>
				Username: <b>".$user_name."</b><br>
				Password: <b>".$new_pass."</b><br>
				<br>
				To change your password, please visit our site: <br>
				<a href=\"".$url."\">".$url."</a><br>
				then login, and navigate to My Settings where you will see a link to change your password.<br>
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
				To change your password, please visit our site: \n
				".$url."\n
				then login, and navigate to My Settings where you will see a link to change your password.\n
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



/**
 * Make the base url of the links we use
 */
function shn_pref_makeBaseUrl() {
	global $global;

	$q = "
		SELECT *
		FROM `incident`
		WHERE `default` = '1'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($row = $result->FetchRow()) {
		$shortname = $row['shortname'] ."/";
	} else {
		$shortname = "";
	}

	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace("index.php", "", $link);
	$link = $link.$shortname;
	return $link;
}



/**
 * Generates a form to rest a forgotten password
 * @return void
 * @access public
 */
function shn_pref_emailCaptchaForm() {
	global $global;
	echo "
		<h2>Forgot My Password</h2>
		<div id=\"formcontainer\">
		<br>
		If you have forgotten your username or password, you can request to have your username emailed to you and to reset your password.
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
		shn_form_submit(_t("Submit"), "class=\"styleTehButton\"");
		echo "</br>";
	shn_form_fclose();
	echo "</div>";
}



/**
 * Generates a form to add an user
 * @return void
 * @access public
 */
function shn_pref_signup($title="Create Your Account", $mod="pref", $act="signup_cr", $error=false) {
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
	shn_form_fopen($act, $mod);
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
 	shn_form_submit(_t("Submit"), "class=\"styleTehButton\"");
	echo "</br><br/><br/>";
	shn_form_fclose();
	echo "</div>";
}



function shn_pref_signup_cr() {
	if(shn_auth_self_signup_cr() == true){
		shn_pref_signup();
		if($_SESSION['security_captcha_key'] != md5($_POST["captcha"])) {
			add_error(_t("Please provide the text in the image correctly to prove you are human."));
			return;
		}
		shn_pref_signup();

	} else {
		if($_SESSION['security_captcha_key'] != md5($_POST["captcha"])) {
			add_error(_t("Please provide the text in the image correctly to prove you are human."));
			shn_pref_signup();
			return;
		}
		$ret = shn_auth_add_user($_POST['given_name'], $_POST['family_name'], $_POST['user_name'], $_POST['password'], $role=REGISTERED, null, null, $_POST['email_address']);
		if($ret) {
			$msg = "Your new user account has been created and is now active. You may now use your credentials to login to the site.";
			add_confirmation($msg);
		} else {
			shn_pref_signup();
		}
	}
}



function shn_image_pref_captcha() {
	shn_auth_gen_captcha();
}



/*
 * include all xxx_main.inc
 */
$d = dir($global['approot'].'mod/pref/');
while (false !== ($f = $d->read())) {
	if (preg_match('/.*_main.inc$/',$f)){
		if (file_exists($global['approot'].'mod/pref/'.$f)){
			include ($global['approot'].'mod/pref/'.$f);
		}
	}
}



/**
 *
 * This function displays the home page of the User Preferences
 *
 * @access public
 * @return void
 */
function shn_pref_default() {
	echo "<div id=\"home\">";
	echo "
		<ul>".
			"<li><b><a href=\"index.php?mod=pref&act=ch_passwd\">Change My Password</a></b></li><br>".
			"<li><b><a href=\"index.php?mod=pref&act=personal\">Edit My Personal Details</a></b></li>".
		"</ul>";
	echo "</div>";

}



/**
 * Generates a form to enable/disable XForm
 * @access public
 * @return void
 */

function shn_pref_enable_ocr_xform() {
	include_once('xform_config.inc');
	echo "<h2>"._t("Enable/Disable OCR XForm")."</h2>";
	shn_form_fopen("enable_xform","pref",array("req"=>false));
		shn_form_fsopen(_t("Enable or disable the OCR friendly form generation."));
			$_value = _shn_xform_conf_value();
			$val_xform = ($_value==true?'enabled':'disabled');
			shn_form_radio(array("enabled"=>_t("Enabled"),"disabled"=>_t("Disabled")),_t("OCR friendly XForm : "),"ocr_xform_status","",array('value'=>$val_xform));
		shn_form_fsclose();
		shn_form_submit(_("Cancel"),"name='disable'");
		shn_form_submit(_("Save"));
	shn_form_fclose();
}



function shn_pref_enable_xform() {
	include('xform_config.inc');
	if(!$_POST['disable']){
		$val_xform = $_POST['ocr_xform_status'];
		if($val_xform =='enabled'){
			$ret_xform = _shn_xform_set_config_value('false');
			if($ret_xform == true){
				add_confirmation(_t("Your preference was successfully saved."));
			}
			else{
				add_error(_t("An error occured while saving your preference."));
			}
		}
		else{
			$ret_xform = _shn_xform_set_config_value('true');
			if($ret_xform == false){
				add_confirmation(_t("Your preference was successfully saved."));
			}
			else{
				add_error(_t("An error occured while saving your preference."));
			}
		}
		shn_pref_enable_ocr_xform();
	}
	else {
		shn_pref_enable_ocr_xform();
	}
}




/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post) {
	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}
}


