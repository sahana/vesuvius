<?
/**
 * @name         User Preferences
 * @version      1.0
 * @package      pref
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


include_once $global['approot']."/mod/pref/ims_config.inc";


function shn_pref_ims_config() {
	switch ($_POST['seq']) {
		case 'entry':
			if(_shn_pref_config_validate()){
				_shn_pref_config_form(false,true);
			} else {
				_shn_pref_config_form(true,false);
			}
			break;
		default:
			_shn_pref_config_form();
			break;
	}
}



function shn_XST_pref_ims_set_incident() {
	global $global;
	$incident_id = addslashes(strip_tags(trim($_REQUEST['incident_id'])));
	$value=shn_user_pref_update ('ims', 'incident_id',$incident_id);
	$res_sql="SELECT name FROM incident WHERE incident_id='".$value."'";
	$res=$global['db']->Execute($res_sql);
	echo $res->fields['name'];
}


function shn_pref_ch_passwd() {
	global $global;
	include_once $global['approot']."/inc/lib_security/auth_form.inc";
	shn_auth_form_ch_pwd();
}



function shn_pref_ch_passwd_cr() {
	$error = false;
	$user = $_POST["user"];
	if($user != $_SESSION["user_id"]){
		add_error("Session Hijacked");
		return false;
	}

	global $global;
	include_once $global['approot']."/inc/lib_security/auth_form.inc";
	$db = $global['db'];

	if (shn_validate_password($_SESSION['user'], $_POST["password"]) == false) {
		shn_pref_ch_passwd();
		return false;
	}

	if((null == $_POST["old_password"]) or (is_null($_POST["old_password"]))) {
		$error=true;
		add_error(_t("Old password cannot be empty!"));
		shn_acl_log_msg("Password Change error: Old password cannot be empty");
	} else {
		$old_password=trim($_POST{"old_password"});
	}

	if((null == $_POST["password"]) or (is_null($_POST["password"]))) {
		$error = true;
		add_error(_t("New password cannot be empty!"));
		shn_acl_log_msg("Password Change error: User password cannot be empty");
	} else {
		$new_password=trim($_POST{"password"});
	}

	if((null==$_POST["re_password"])or(is_null($_POST["re_password"]))) {
		$error=true;
		add_error(_t("You left the confirm password field blank."));
		shn_acl_log_msg("Password Change error: User Confirm password cannot be empty");
	} else {
		$re_password=trim($_POST{"re_password"});
	}

	if(!($new_password==$re_password)) {
		$error=true;
		add_error(_t("Your new password did not match when you retyped it."));
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
    		add_error(_t("You cannot change the password more than once in one day"));
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
			add_error(_t("You cannot choose one of the recent four passwords"));
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
		$msg = _t(" Succesfully changed Password ");
		add_confirmation($msg);
	}
}

