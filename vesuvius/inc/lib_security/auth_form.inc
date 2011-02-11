<?php
/**
 *
 * Sahana authentication form generator library.
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


global $global;
include_once $global['approot']. 'inc/lib_security/lib_auth.inc';
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";


/**
 * Generates a form to delete a user
 * @return void
 * @access public
 */
function shn_auth_form_user_del($title="Delete Usert", $mod="admin" ,$act="del_user_cr", $error=false) {
	if($error) {
		display_errors();
	}
	echo "
		<br>
		<div id=\"formcontainer\">
	";
	shn_form_fopen($act, $mod, null);
		shn_form_fsopen(_t("Select User"));
			$users = shn_auth_user_list(true, false);
			shn_form_multi_select('users', $users, "Users", null, null);
		shn_form_fsclose();
		echo "<br>";
		shn_form_submit(_t("Remove user"), "class=\"styleTehButton\"");
		echo "<br>";
	shn_form_fclose();
	echo "</div>";
}



/**
 * Generates a form to add an user
 * @return void
 * @access public
 */

function shn_auth_form_user_add($title="Create Your Account", $mod="admin", $act="add_user_cr", $error=false) {
	global $global;
	if($error) {
		display_errors();
	}
	echo "
		<br>
		<div id=\"formcontainer\">
	";
	shn_form_fopen($act,$mod);
	shn_form_fsopen(_t("Account Details"));
	$extra_opts['req'] = true;
	shn_form_text("First Name ",    'given_name',    'size="30" autocomplete="off"', $extra_opts);
	shn_form_text("Last Name ",     'family_name',   'size="30" autocomplete="off"', $extra_opts);
	shn_form_text("User Name ",     'user_name',     'size="30" autocomplete="oo"', $extra_opts);
	shn_form_text("Email Address ", 'email_address', 'size="30" autocomplete="off"', $extra_opts);
	shn_form_password("Password for Login", "password", 'autocomplete="off"', $extra_opts);
	shn_form_password("Confirm Password", "re_password", 'autocomplete="off"', $extra_opts);
	shn_form_fsclose();
	$roles=_shn_acl_get_roles(null, false);
	shn_form_fsopen(_t("Select Role"));
	shn_form_select($roles,"Roles", 'roles', null, $extra_opts);
	shn_form_fsclose();
	$extra_opts['req'] = true;
	shn_form_fsopen("OpenId Login Details", "openIdSignup");
	echo "<div class=\"info\">Option to use an OpenID instead of a username/password if you'd like.</div><br />";
	shn_form_text(_t("OpenID "), 'openid', 'size="30"', null);
	shn_form_fsclose();
	echo "</br>";
 	shn_form_submit(_t("Submit"), "class=\"styleTehButton\"");
	echo "</br>";
	shn_form_fclose();
	echo "</div>";
}



/**
 * Generates a form to change the password
 * @return void
 * @access public
 */

function shn_auth_form_ch_pwd($error=false) {
	echo "
		<h2>Change My Password</h2>
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
		?><h4><?php echo _t("You new password must adhere to following rules:") ?></h4><?php
		for($i=0; $i < count($policy); $i++) {
			echo ($i+1).". ".$policy[$i]."<br/>";
		}
	}
	?><br><?php
	shn_form_fopen($act,$mod);
	shn_form_fsopen(_t("Fill in these required fields to change your password"));
	$extra_opts['req']=true;
	shn_form_password("Old Password", "old_password", null, $extra_opts);
	shn_form_password("New Password", "password", null, $extra_opts);
	shn_form_password("Confirm New Password", "re_password", null, $extra_opts);
	$user_id=$_SESSION["user_id"];
	shn_form_hidden(array('user'=>$user_id));
	shn_form_fsclose();
	echo "<br>";
 	shn_form_submit(_t("Change Password"), "class=\"styleTehButton\"");
	echo "<br>";
	shn_form_fclose();
	echo "</div>";
}



function _shn_admin_ch_pwd_cr()	{
	global $global;
	$db=$global["db"];
	$VARCHAR=100;

	//for the moment return true
	//  list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
	if ((null==$_POST["old_password"])or(is_null($_POST["old_password"]))){
		$error=true;
		add_error(_t("Old password cannot be empty"));
	} else {
		$old_password=trim($_POST{"old_password"});
	}
	if ((null==$_POST["password"])or(is_null($_POST["password"]))){
		$error=true;
		add_error(_t("New password cannot be empty"));
	} else {
		$password=trim($_POST{"password"});
	}
	if ((null==$_POST["re_password"])or(is_null($_POST["re_password"]))){
		$error=true;
		add_error(_t("Confirm password cannot be empty"));
	} else {
		$re_password=trim($_POST{"re_password"});
	}
	if (!($password==$re_password)){
		$error=true;
		add_error(_t("Password and Confirm Password should match"));
	}
	if($error==true){
		return $error;
	}
	$user_id=trim($_POST{"user"});
	$error=shn_change_password($user_id,$old_password,$password);
	if($error==true){
		return $error;
	}
	shn_admin_ch_pwd($error);
}



/**
 * Generates a form to change the password
 * @return void
 * @access public
 */

function shn_auth_form_reset_pwd($error=false) {
	echo "
		<br>
		<div id=\"formcontainer\">
	";
	$act = "reset_pwd_cr";
	$mod = "admin";
	$policy = shn_get_password_policy();
	if(count($policy) > 0) {
		echo "<h4>Password must adhere to following rules:</h4>";
		for($i=0; $i<count($policy); $i++) {
			echo ($i+1).". ".$policy[$i]."<br/>";
		}
	}
	echo "<br>";
	shn_form_fopen($act,$mod);
	$extra_opts['req'] = true;
	$users=shn_auth_user_list(true);
	shn_form_fsopen(_t("Select User"));
	shn_form_select($users,"Users", 'user', null, $extra_opts);
	shn_form_fsclose();
	shn_form_fsopen(_t("New Password"));
	$extra_opts['req'] = true;
	shn_form_password("New Password", "password", null, $extra_opts);
	shn_form_password("Confirm New Password", "re_password", null, $extra_opts);
	shn_form_fsclose();
	echo "<br>";
	shn_form_submit(_t("Reset Password"), "class=\"styleTehButton\"");
	echo "<br>";
	shn_form_fclose();
	echo "<br><br>";

	if($error) {
		display_errors();
	}
}



function _shn_admin_reset_pwd_cr(){
	global $global;
	$db = $global["db"];
	$VARCHAR = 100;
	$error = false;

	if(!isset($_POST["password"]) || $_POST["password"] == null) {
		$error = true;
		add_error(_t("New password cannot be empty"));
	} else {
		$password = trim($_POST["password"]);
	}

	if(!isset($_POST["re_password"]) || $_POST["re_password"] == null) {
		$error = true;
		add_error(_t("Confirm password cannot be empty"));
	} else {
		$re_password = trim($_POST["re_password"]);
	}

	if(!$error && !($password == $re_password)) {
		$error = true;
		add_error(_t("Password and Confirm Password should match"));
	}

	if($error == true) {
		return $error;
	}
	$user_id = trim($_POST["user"]);
	if(shn_force_change_password($user_id, $password) == true) {
		return;
	}

	add_confirmation(_t("The Password was succesfully updated"));
}
