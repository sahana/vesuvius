<?
/**
 * @name         Authentication Form Library
 * @version      11
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0209
 */



global $global;

require_once($global['approot']. 'inc/lib_security/lib_auth.inc');
require_once($global['approot']."/inc/lib_errors.inc");
require_once($global['approot']."/inc/lib_validate.inc");



/** Generates a form to change the password */
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
	shn_form_fopen($act, $mod, null, null, "width: 600px;");
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



function _shn_admin_ch_pwd_cr() {

	global $global;

	$db = $global["db"];
	$VARCHAR = 100;

	if((null == $_POST["old_password"])  || (is_null($_POST["old_password"]))) {
		$error = true;
		add_error(_t("Old password cannot be empty"));
	} else {
		$old_password = trim($_POST{"old_password"});
	}
	if((null == $_POST["password"]) || (is_null($_POST["password"]))) {
		$error = true;
		add_error(_t("New password cannot be empty"));
	} else {
		$password = trim($_POST{"password"});
	}
	if((null == $_POST["re_password"]) || (is_null($_POST["re_password"]))) {
		$error = true;
		add_error(_t("Confirm password cannot be empty"));
	} else {
		$re_password = trim($_POST{"re_password"});
	}
	if(!($password == $re_password)){
		$error = true;
		add_error(_t("Password and Confirm Password should match"));
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



