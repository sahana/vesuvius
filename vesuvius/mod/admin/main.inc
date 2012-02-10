<?php
/**
 * @name         Administration
 * @version      11
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0208
 */


global $global;

require_once($global['approot']."/inc/lib_errors.inc");
require_once($global['approot']."/inc/lib_validate.inc");
require_once($global['approot']."inc/lib_security/acl_form.inc");
require_once($global['approot']."inc/lib_security/auth_form.inc");
require_once($global['approot']."inc/lib_security/lib_auth.inc");
require_once($global['approot']."inc/lib_xajax.inc");


function shn_admin_field_option_config() {
	require_once('lib_fo_config.inc');
	_shn_admin_field_option_config();
}


/** the controller for admin modole */
function shn_admin_default() {

	global $global;

	$control = "";

	shn_tabmenu_open();
	shn_tabmenu_item("version", _t("Version"),        "admin");
	shn_tabmenu_item("rez",     _t("Resource Pages"), "admin");
	shn_tabmenu_item("adduser", _t("Add User"),       "admin");
	shn_tabmenu_item("deluser", _t("Remove User"),    "admin");
	shn_tabmenu_item("roles",   _t("User Roles"),     "admin");
	shn_tabmenu_item("passwd",  _t("Password Reset"), "admin");
	shn_tabmenu_item("status",  _t("User Status"),    'admin');
	shn_tabmenu_item("mods",    _t("Module ACL"),     'admin');
	shn_tabmenu_item("log",     _t("Event Log"),      'admin');
	shn_tabmenu_close();


	if(isset($_GET['rez'])) {
		$control = "shn_rez_adm_default";
		require_once($global['approot']."mod/rez/admin.inc");

	} elseif(isset($_GET['adduser'])) {
		$control = "shn_admin_add_user";

	} elseif(isset($_GET['adduserp'])) {
		$control = "shn_admin_add_user_p";

	} elseif(isset($_GET['deluser'])) {
		$control = "shn_admin_del_user";

	} elseif(isset($_GET['deluserp'])) {
		$control = "shn_admin_del_user_p";

	} elseif(isset($_GET['roles'])) {
		$control = "shn_admin_acl_user_edit_roles";

	} elseif(isset($_GET['class'])) {
		$control = "shn_admin_changeClass";

	} elseif(isset($_GET['passwd'])) {
		$control = "shn_admin_reset_pwd";

	} elseif(isset($_GET['status'])) {
		$control = "shn_admin_acl_change_user_status";

	} elseif(isset($_GET['log'])) {
		$control = "shn_admin_acl_event_log";

	} elseif(isset($_GET['mods'])) {
		$control = "shn_admin_acl_enable_mods";
	}

	if($control == "") {
		$control = "shn_admin_build";
	}

	$control();
}



function shn_admin_build() {

	global $global;

	// show build & version
	$revision_file = $global['approot']."/version";
	$time_file     = $global['approot']."/time";

	// only show the rev/build info on stage/production ~ not dev as version/time dont exist there or in svn
	if(file_exists($revision_file) && file_exists($time_file)) {
		// open file with the revision number in the first line
		$handle = fopen($revision_file, "r");

		// read first line. TODO: check if it's not empty, etc.
		$version = fgets($handle);

		// open file to read timestamp
		$handle2 = fopen($time_file, "r");

		// extract time
		$time = fgets($handle2);

		// print generated link
		echo "
			<br>Build Time: <b>".$time."</b><br>
			Bazaar revision: <b><a href=\"http://bazaar.launchpad.net/~triune/vesuvius/trunk/revision/".$version."\" target=\"_blank\">r".$version."</a></b><br>
			Codebase: <b><a href=\"https://code.launchpad.net/vesuvius\" target=\"_blank\">https://code.launchpad.net/vesuvius</a></b>
		";
	}

}


function shn_admin_modadmin() {
	global $global;

	// include original module admin section
	include $global['approot']."/mod/".$global['module']."/admin.inc";

	// compose and call the relevant module function
	$module_function = "shn_".$global['module']."_".$global['action'];

	if(!function_exists($module_function)) {
		$module_function="shn_".$global['module']."_adm_default";
	}
	$module_function();
}



function shn_admin_acl_change_user_status($error=false) {
	shn_acl_form_change_user_status();
}



function shn_admin_acl_change_user_status_cr($error=false) {
	_shn_admin_acl_change_user_status_cr();
	shn_admin_acl_change_user_status();
}



function shn_admin_acl_unlock_user($error=false) {
	shn_acl_form_unlock_user();
}



function shn_admin_acl_unlock_user_cr($error=false) {
	_shn_admin_acl_unlock_user_cr();
	shn_admin_acl_unlock_user();
}


function shn_admin_acl_event_log($error=false) {
	shn_acl_form_event_log();
}



/** Generates a form to add an user */
function shn_admin_add_user($error = false) {

	global $global;

	if($error) {
		display_errors();
	}
	echo "
		<br>
		<div id=\"formcontainer\">
	";
	shn_form_fopen2("admin?adduserp&tabid=2");
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
function shn_admin_add_user_p() {

	$error = false;
	require_once("errors.inc");
	if(shn_auth_add_user_cr() == true) {
		shn_admin_add_user();
		return;
	}
	shn_admin_add_user($error);
}







function shn_admin_del_user($error=false) {

	if($error) {
		display_errors();
	}
	echo "
		<br>
		<div id=\"formcontainer\">
	";
	shn_form_fopen2("admin?deluserp&tabid=3");
		shn_form_fsopen(_t("Select User(s) to Delete"));
			$users = shn_auth_user_list(true, false);
			shn_form_multi_select('users', $users, "Users", null, null);
		shn_form_fsclose();
		echo "<br>";
		shn_form_submit(_t("Remove user"), "class=\"styleTehButton\"");
		echo "<br>";
	shn_form_fclose();
	echo "</div>";
}
function shn_admin_del_user_p() {

	global $global;

	$error = false;
	$user=$_POST{"users"};
	$db=$global["db"];
	$VARCHAR=100;
	for($i=0;$i<count($user);$i++) {
		if($user[$i]!=ADMINUSER) {
			$q="delete from users where p_uuid='{$user[$i]}'";
			$res=$db->Execute($q);
			if($res==false){
				add_error($db->ErrorMsg());
			}
		}
	}
	for($i=0;$i<count($user);$i++) {
		if($user[$i]!=ADMINUSER){
			$q="delete from alt_logins where p_uuid='{$user[$i]}'";
			$res=$db->Execute($q);
			if($res==false){
				add_error($db->ErrorMsg());
			}
		}
	}
	for($i=0;$i<count($user);$i++) {
		if($user[$i]!=ADMINUSER){
			$q="delete from contact where p_uuid='{$user[$i]}'";
			$res=$db->Execute($q);
			if($res==false){
				add_error($db->ErrorMsg());
			}
		}
	}
	if($res==false) {
		add_error(_t("User does not exist"));
	} else {
		add_confirmation(_t("User was successfully removed"));
	}
	shn_admin_del_user($error);
}

















function shn_admin_reset_pwd($error=false) {
	shn_auth_form_reset_pwd($error);
}



function shn_admin_reset_pwd_cr() {
	require_once("errors.inc");
	$done = _shn_admin_reset_pwd_cr();
	shn_auth_form_reset_pwd();
}



function shn_admin_ch_pwd($error=false) {
	shn_auth_form_ch_pwd($error);
}



function shn_admin_ch_pwd_cr() {
	require_once("errors.inc");
	$error=_shn_admin_ch_pwd_cr();
	echo "<div id=\"result_msg\">";
	if($error) {
		$msg="An error ocurred";
	} else {
		$msg="The Password was succesfully updated ";
	}
	if($error) {
		display_errors();
	}
	echo "</div>";
	_shn_admin_acl_system_menu();
}



function shn_admin_acl_user_roles()       { _shn_admin_acl_user_roles(); }
function shn_admin_acl_enable_mods()      { _shn_admin_acl_enable_mods(); }
function shn_admin_acl_enable_mods_cr()   { _shn_admin_acl_enable_mods_cr(); }
function shn_admin_acl_state()            { _shn_admin_acl_state(); }
function shn_admin_acl_user()             { _shn_admin_acl_user(); }


function shn_admin_acl_role_edit_perms() {
	_shn_admin_acl_role_edit_perms();
}



function  shn_admin_acl_role_edit_perms_cr() {
	_shn_admin_acl_role_edit_perms_cr();
}



function shn_admin_changeClass() {

	global $global;
	$db = $global['db'];

	$q = "
		DELETE FROM sys_user_to_group
		WHERE p_uuid = '".mysql_real_escape_string(urldecode($_GET['p']))."';
	";
	$res = $db->Execute($q);

error_log($q);

	$q2 = "
		INSERT INTO sys_user_to_group (`group_id`, `p_uuid`)
		VALUES ('".$_GET['g']."', '".mysql_real_escape_string(urldecode($_GET['p']))."');
	";
	$res2 = $db->Execute($q2);
	shn_admin_acl_user_edit_roles();
	add_confirmation(_t("User's class updated successfully."));
}



function _shn_admin_acl_enable_mods() {
	shn_acl_form_enable_mods();
}



function _shn_admin_acl_enable_mods_cr() {

	global $global;
	$error_flag = false;

	$db=$global["db"];
	$perm_string=$_POST{"perms"};
	$perms=explode(";",$perm_string);
	$sql="DELETE FROM sys_group_to_module";
	$res=$db->Execute($sql);
	if(!$res && !$error_flag){
		$error_flag = true;
	}

	// give admin module to admin role.
	$admin_role=1;
	$sql="INSERT INTO sys_group_to_module VALUES({$admin_role},'admin','enabled')";
	$res=$db->Execute($sql);
	if(!$res && !$error_flag){
		// set the error flag once only
		// no overwrite if set.
		$error_flag = true;
	}

	for($i=0;$i<count($perms)-1;$i++) {
		$rule=explode(":",$perms[$i]);
		$mod=$rule[0];
		$role=$rule[1];
		$name=$mod.$role;



		if(isset($_POST[trim($name)])) {
			// avoid the duplicate entry using the condition
			if($mod=='admin' && $role==$admin_role){
				// do nothing
			}else{
				$sql="INSERT INTO sys_group_to_module VALUES({$role},'{$mod}','enabled')";
				$res=$db->Execute($sql);
				if(!$res && !$error_flag){

					// set the error flag once only
					// no overwrite if set.
					$error_flag = true;
				}
			}
		}
	}

	if($error_flag){
		add_error(_t("The selection was not saved due to one or more errors."));
	}else{
		add_confirmation(_t("The changes were saved successfully."));
	}

	shn_acl_form_enable_mods();
}



function _shn_admin_acl_enable_acl() {
	shn_acl_form_enable_acl();
}



function _shn_admin_acl_enable_acl_cr($show=false) {

	global $global;
	//$db=$global["db"];

	if($_POST['action']=='enable') {
		shn_acl_enable(true);
	}else {
		shn_acl_enable(false);
	}
	if($show==true){
		shn_acl_form_enable_acl();
	}else{
		if(shn_acl_check_perms("admin","acl_enable_acl")==true){
			$global['action']="acl_enable_acl";
			$global['module']="admin";
		}else{
			$global['action']="default";
			$global['module']="home";
		}

	}
	header("Location: index.php?mod=home&act=default");
}



function _shn_admin_acl_user_roles() {
	_shn_admin_acl_user_roles_menu(true);
}



function _shn_admin_acl_role_edit_perms() {
	shn_acl_form_role_perms_grid($_POST["roles"]);
}



function _shn_admin_acl_existing_perms_tab() {
	$module=$_GET['sel'];
	shn_acl_form_existing_perms_tabular($module,false);
}



function _shn_admin_acl_user_perms() {
	$module=$_GET['sel'];
	_shn_admin_acl_module_sub_menu($module);
	shn_acl_form_user_perms_grid($module,false);
}





/** Generates a form to edit roles of a user */
function shn_admin_acl_user_edit_roles($error=false) {

	global $global;
	$db = $global['db'];

	echo "
		<br>
		<div id=\"home\">Designate which group each use is apart of by clicking assign to change it to the desired group. The box colored <span style=\"color: orange; font-weight: bold;\">orange</span> denotes which group the user is currently apart of.</div><br>
		<div id=\"formcontainer\">
	";

	shn_form_fopen2("rolesp", "admin", array('req_message' => false));

	echo "
		<div id=\"result\">
		<table>
		<thead>
		<td><strong><center>UserID</center></strong></td>
		<td><strong>Username</strong></td>
		<td><strong>Real Name</strong></td>
	";

	$roles = _shn_acl_get_roles();
	foreach($roles as $role=>$role_name){
		echo "<td>".$role_name."</td>";
	}


	echo "
		</thead>
		<tbody>
	";

	// switched this to list2 because it wasn't handling uuid's with /'s in them correctly,
	// to we use the user_id and then find the p_uuid of the user when adding the role to the user
	$users = shn_auth_user_list2();

	//echo "<pre>".print_r($users, true)."</pre>";
	//echo "---------------------------------------<br>";
	//echo "<pre>".print_r($roles, true)."</pre>";

	foreach($users as $user) {

		echo "<td>".$user['user_id']."</td><td>".$user['user_name']."</td><td>".$user['full_name']."</td>";



		foreach($roles as $role => $role_name) {
			if($user['group_id'] == $role) {
				echo "<td style=\"background-color: orange;\"><center>".$role_name."</center></td>";
			} else if($user['user_id'] == 1) {
				echo "<td>&nbsp;</td>";
			} else {
				echo "<td><center><a href=\"admin?class&tabid=4&p=".urlencode($user['p_uuid'])."&g=".$role."\">assign</a></center></td>";
			}
		}
		echo "</tr>";
	}
	echo "
		</tbody>
		</table>
		</div>
	";
	shn_form_fclose();
	echo "</div>";
}


function _shn_admin_acl_change_user_status_cr() {
	global $global;
	$db = $global["db"];

	$users = shn_auth_user_list();

	foreach($users as $user => $uname) {
		if($user != "1") { // we dont touch root :)
			$status = $_POST[str_replace(".", "_", $user)]; // $_POST will turn . into _, so we reverse this

			$sql = "
				UPDATE users
				SET status = '".$status."'
				WHERE p_uuid = '".$user."';
			";
			$res = $db->Execute($sql);
		}
	}
	add_confirmation("Status of Users Saved!");
}



function _shn_admin_acl_unlock_user_cr() {
	$users = shn_auth_locked_user_list();
	global $global;
	$db = $global["db"];
	foreach($users as $user=>$uname) {
		$status = $_POST[$user];
		$sql = "
			UPDATE users
			SET status = '{$status}'
			WHERE p_uuid = '{$user}';
		";
		$res=$db->Execute($sql);
	}
}



function _shn_admin_acl_user_add_roles($module=NULL,$error=false) {
	if(is_null($module)) {
		$module=$_GET['sel'];
	}


	global $conf;
	?><h2 align="center"><?php echo sprintf(_t("Configure ACL user permissions for %s"), $conf['mod_'.$module.'_name']); ?></h2><?php
	shn_acl_form_user_add_roles($module,$error);
}



function _shn_admin_acl_user_add_roles_cr() {
	global $global;
	$module=$_GET['sel'];

	if(is_null($_POST{"users"})) {
		$error=true;
		add_error(SHN_ERR_OR_NAME_INCOMPLETE);
	}else{
		$user=$_POST{"users"};
	}

	if(is_null($_POST{"roles"})) {
		$error=true;
		add_error(SHN_ERR_OR_NAME_INCOMPLETE);
	}else{
		$role=$_POST{"roles"};
	}

	$i=0;
	while($i<count($user)) {
		$j=0;
		while($j<count($role)) {
			$res=shn_acl_add_to_role($user[$i],$role[$j]);
			$j=$j+1;
		}
		$i=$i+1;
	}

	shn_admin_acl_user_add_roles($module,false);
	if($res) {
		?><div id="save"><?php echo _t("Users were succesfully added to Roles") ?></div><?php
	}
}



function _shn_admin_acl_role() {
	$module=$_GET['sel'];
	global $conf;
	_shn_admin_acl_role_menu($module);
	?><h2 align="center"><?php echo _t("Configure ACL Role permissions") ?></h2><?php
}



function _shn_admin_acl_role_cr() {
	global $global;
	$module=$_GET['sel'];

	if(is_null($_POST{"action_groups"})) {
		$error=true;
		add_error(SHN_ERR_OR_NAME_INCOMPLETE);
	}else{
		$action_group=$_POST{"action_groups"};
	}

	if(is_null($_POST{"roles"})) {
		$error=true;
		add_error(SHN_ERR_OR_NAME_INCOMPLETE);
	}else{
		$role=$_POST{"roles"};
	}
	$i=0;
	while($i<count($role)) {
		$j=0;
		while($j<count($action_group)) {
			$res=shn_acl_add_perms_action_group_role($role[$i],$module,$action_group[$j]);
			$j=$j+1;
		}
		$i=$i+1;
	}
	if($res) {
		?><div id="save"><?php echo _t("Roles were succesfully given permission to action groups") ?></div><?php
	}
	shn_admin_acl_role($module,false);
}



function _shn_admin_acl_user_add_perms() {
	$module=$_GET['sel'];
	global $conf;
	?><h3><?php echo sprintf(_("Configure ACL for "),$conf['mod_'.$module.'_name'])?></h3><?php
	shn_acl_form_user_add_perms($module,false);
}



function _shn_admin_acl_user_edit_perms_cr() {
	$perm_string=$_POST{"perms"};
	$perms=explode(";",$perm_string);
	var_dump($perms);
}



function _shn_admin_acl_user_edit_perms() {
	$module=$_GET['sel'];
	global $conf;
	?><h3><?php echo sprintf(_t("Configure ACL for "),$conf['mod_'.$module.'_name']) ?></h3><?php

	shn_acl_form_user_edit_perms($module,false);
}



function _shn_admin_acl_user_cr() {
	global $global;
	$module=$_GET['sel'];

	if(is_null($_POST{"action_groups"})) {
		$error=true;
		add_error(SHN_ERR_OR_NAME_INCOMPLETE);
	}else{
		$action_group=$_POST{"action_groups"};
	}

	if(is_null($_POST{"users"})) {
		$error=true;
		add_error(SHN_ERR_OR_NAME_INCOMPLETE);
	}else{
		$user=$_POST{"users"};
	}
	$i=0;
	while($i<count($user)) {
		$j=0;
		while($j<count($action_group)) {
			$res=shn_acl_add_perms_action_group_user($user[$i],$module,$action_group[$j]);

			$j=$j+1;
		}
		$i=$i+1;
	}
	if($res) {
		?><div id="save"><?php echo _t("Roles were succesfully given permission to action groups") ?></div>
		<?php
	}
	_shn_admin_acl_user($module,false);
}



