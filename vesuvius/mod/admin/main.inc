<?php
/**
 * @name         Administration
 * @version      11
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0612
 */


global $global;

require_once($global['approot']."/inc/lib_errors.inc");
require_once($global['approot']."/inc/lib_validate.inc");
require_once($global['approot']."inc/lib_security/acl_form.inc");
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
	shn_tabmenu_item("version", _t("Admin-Menu|Version"),        "admin");
	shn_tabmenu_item("rez",     _t("Admin-Menu|Resource Pages"), "admin");
	shn_tabmenu_item("adduser", _t("Admin-Menu|Add User"),       "admin");
	shn_tabmenu_item("deluser", _t("Admin-Menu|Remove User"),    "admin");
	shn_tabmenu_item("roles",   _t("Admin-Menu|User Roles"),     "admin");
	shn_tabmenu_item("passwd",  _t("Admin-Menu|Password Reset"), "admin");
	shn_tabmenu_item("status",  _t("Admin-Menu|User Status"),    'admin');
	shn_tabmenu_item("mods",    _t("Admin-Menu|Module ACL"),     'admin');
	shn_tabmenu_item("log",     _t("Admin-Menu|Event Log"),      'admin');
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

	} elseif(isset($_GET['passwdp'])) {
		$control = "shn_admin_reset_pwd_p";

	} elseif(isset($_GET['status'])) {
		$control = "shn_admin_acl_change_user_status";

	} elseif(isset($_GET['statusp'])) {
		$control = "shn_admin_acl_change_user_status_p";

	} elseif(isset($_GET['log'])) {
		$control = "shn_admin_acl_event_log";

	} elseif(isset($_GET['mods'])) {
		$control = "shn_admin_acl_enable_mods";

	} elseif(isset($_GET['modsp'])) {
		$control = "shn_admin_acl_enable_mods_p";
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
			Codebase: <b><a href=\"https://code.launchpad.net/vesuvius\" target=\"_blank\">https://code.launchpad.net/vesuvius</a></b><br>
			CHANGELOG: <b><a href=\"http://bazaar.launchpad.net/~triune/vesuvius/trunk/view/head:/vesuvius/CHANGELOG\" target=\"_blank\">http://bazaar.launchpad.net/~triune/vesuvius/trunk/view/head:/vesuvius/CHANGELOG</a></b>
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



function shn_admin_acl_change_user_status($error = false) {

	global $global;

	$db = $global['db'];
	$perms = "";
	?>
	<br>
	<div id="home"><?php echo _t("Rows are Users ,Columns are the possible status values"); ?>
	<br><br>
	<ul>
	<li><?php echo _t("Admin-UserPermission-Text|<strong>Active</strong> - The user can login and perform operations."); ?></li>
	<li><?php echo _t("Admin-UserPermission-Text|<strong>Locked</strong> - The user is withheld from performing operations on the system temporarily."); ?></li>
	<li><?php echo _t("Admin-UserPermission-Text|<strong>Banned</strong> - The user is not allowed to perform any operation on the system permanently."); ?></li>
	</ul>
	</div>

	<div id="formcontainer"><?php
	shn_form_fopen2("admin?statusp&tabid=6", null, array('req_message'=>false));
	?>
	<div id="result">
	<table>
	<thead>
		<td><strong><?php echo _t("Admin-UserStatus-Heading|User"); ?></strong></td>
		<td><?php echo _t("Admin-UserStatus-Text|Active") ?></td>
		<td><?php echo _t("Admin-UserStatus-Text|Locked") ?></td>
		<td><?php echo _t("Admin-UserStatus-Text|Banned") ?></td>
	</thead>
	<tbody>
	<?php

	$users = shn_auth_user_list_and_status();
	$locked = shn_auth_locked_user_list();

	foreach ($users as $user=>$uarray){
		//this will be used in a hidden field to identify all the checkboxes
		$user=$user;

		$uname=$uarray[0];
		?>
		<tr>
			<td><?php echo $uname;?></td>
			<td><?php
			$options=array("active"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
			<td><?php
			$options=array("locked"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
			<td><?php
			$options=array("banned"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
		</tr>
		<?php
	}
	?>
		</tbody>
	</table>
	</div>
	<br />

	<center><?php
	shn_form_hidden(array("perms"=>$perms));
	shn_form_hidden(array("users"=>$users));
	shn_form_submit(_t("Admin-UserPermission-Button|Save"), "class=\"styleTehButton\"");
	?></center><br><br>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}
function shn_admin_acl_change_user_status_p($error = false) {

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
	add_confirmation(_t("Admin-UserStatus-Message|Status of user accounts saved!"));

	shn_admin_acl_change_user_status();
}



function shn_admin_acl_event_log($error=false) {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$count = 0;

	$db=$global['db'];
	?>
	<div id="result">
	<table>
	<thead>
		<td><strong><?php echo _t("Admin-UserEventLog-TableHeader|Date/Time") ?></strong></td>
		<td><strong><?php echo _t("Admin-UserEventLog-TableHeader|User Name") ?></strong></td>
		<td><strong><?php echo _t("Admin-UserEventLog-TableHeader|Full Name") ?></strong></td>
		<td><strong><?php echo _t("Admin-UserEventLog-TableHeader|Event Type") ?></strong></td>
		<td><strong><?php echo _t("Admin-UserEventLog-TableHeader|Event") ?></strong></td>
	</thead>
	<tbody>
	<?php

	$sql =
		"SELECT *
		FROM password_event_log
		ORDER BY changed_timestamp DESC ;
	";
	$res = $db->Execute($sql);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "acl event log display (".$sql.")"); }

	while(($res != null) && (!$res->EOF)) {
		$timestamp = $res->fields["changed_timestamp"];
		$full_name = shn_get_user_details($res->fields["p_uuid"]);
		$type = ($res->fields["event_type"] == null) ? "" : $res->fields["event_type"];
		?>
		<tr>
			<td><?php echo $timestamp;?></td>
			<td><?php echo $res->fields["user_name"];?></td>
			<td><?php echo $full_name;?></td>
			<td style="color: red; font-weight: bold;"><?php echo $type;?></td>
			<td><?php echo $res->fields["comment"];?></td>
		</tr>
		<?php
		$res->MoveNext();
		$count++;
	}
	if($count == 0) {
		echo "<tr><td colspan=5><center>."._t("Admin-UserEventLog-Message|No log entries thus far.")."</center></td></tr>";
	}
	?>
		</tbody>
	</table>
	</div>
	<br />
	<?php
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
	shn_form_fsopen(_t("Admin-AddUser-Form|Account Details"));
	$extra_opts['req'] = true;
	shn_form_text(_t("Admin-AddUser-TextField|First Name "),    'given_name',    'size="30" autocomplete="off"', $extra_opts);
	shn_form_text(_t("Admin-AddUser-TextField|Last Name "),     'family_name',   'size="30" autocomplete="off"', $extra_opts);
	shn_form_text(_t("Admin-AddUser-TextField|User Name "),     'user_name',     'size="30" autocomplete="oo"', $extra_opts);
	shn_form_text(_t("Admin-AddUser-TextField|Email Address "), 'email_address', 'size="30" autocomplete="off"', $extra_opts);
	shn_form_password(_t("Admin-AddUser-Password|Password for Login"), "password", 'autocomplete="off"', $extra_opts);
	shn_form_password(_t("Admin-AddUser-Password|Confirm Password"), "re_password", 'autocomplete="off"', $extra_opts);
	shn_form_fsclose();
	$roles=_shn_acl_get_roles(null, false);
	shn_form_fsopen(_t("Admin-AddUser-Text|Select Role"));
	shn_form_select($roles,_t("Admin-AddUser-Select|Roles"), 'roles', null, $extra_opts);
	shn_form_fsclose();
	$extra_opts['req'] = true;
	shn_form_fsopen(_t("Admin-AddUser-TextField|OpenId Login Details"), "openIdSignup");
	echo "<div class=\"info\">"._t("Admin-AddUser-Message|Option to use an OpenID instead of a username/password if you'd like.")."</div><br />";
	shn_form_text(_t("Admin-AddUser-Text|OpenID "), 'openid', 'size="30"', null);
	shn_form_fsclose();
	echo "</br>";
 	shn_form_submit(_t("Admin-AddUser-Form|Submit"), "class=\"styleTehButton\"");
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
		shn_form_fsopen(_t("Admin-RemoveUser-Text|Select User(s) to Delete"));
			$users = shn_auth_user_list(true, false);
			shn_form_multi_select('users', $users, "Users", null, null);
		shn_form_fsclose();
		echo "<br>";
		shn_form_submit(_t("Admin-RemoveUser-Button|Remove user"), "class=\"styleTehButton\"");
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
		add_error(_t("Admin-RemoveUser-Error|User does not exist"));
	} else {
		add_confirmation(_t("Admin-RemoveUser-Message|User was successfully removed"));
	}
	shn_admin_del_user($error);
}



function shn_admin_reset_pwd($error = false) {

	echo "
		<br>
		<div id=\"formcontainer\">
	";
	$policy = shn_get_password_policy();
	if(count($policy) > 0) {
		echo _t("Admin-ChangeUserPassword-Message|<h4>Password must adhere to following rules:</h4>");
		for($i=0; $i<count($policy); $i++) {
			echo ($i+1).". ".$policy[$i]."<br/>";
		}
	}
	echo "<br>";
	shn_form_fopen2("admin?passwdp&tabid=5");
	$extra_opts['req'] = true;
	$users = shn_auth_user_list(true);
	shn_form_fsopen(_t("Admin-ChangeUserPassword-Select|Select User"));
	shn_form_select($users,"Users", 'user', null, $extra_opts);
	shn_form_fsclose();
	shn_form_fsopen(_t("Admin-ChangeUserPassword-Text|New Password"));
	$extra_opts['req'] = true;
	shn_form_password(_t("Admin-ChangeUserPassword-Password|New Password"), "password", null, $extra_opts);
	shn_form_password(_t("Admin-ChangeUserPassword-Password|Confirm New Password"), "re_password", null, $extra_opts);
	shn_form_fsclose();
	echo "<br>";
	shn_form_submit(_t("Admin-ChangeUserPassword-Button|Reset Password"), "class=\"styleTehButton\"");
	echo "<br>";
	shn_form_fclose();
	echo "<br><br>";

	if($error) {
		display_errors();
	}
}
function shn_admin_reset_pwd_p() {

	global $global;

	require_once("errors.inc");

	$db = $global["db"];
	$VARCHAR = 100;
	$error = false;

	if(!isset($_POST["password"]) || $_POST["password"] == null) {
		$error = true;
		add_error(_t("Admin-ChangeUserPassword-Error|New password cannot be blank."));
	} else {
		$password = trim($_POST["password"]);
	}

	if(!isset($_POST["re_password"]) || $_POST["re_password"] == null) {
		$error = true;
		add_error(_t("Admin-ChangeUserPassword-Error|You failed to re-enter the password."));
	} else {
		$re_password = trim($_POST["re_password"]);
	}

	if(!$error && !($password == $re_password)) {
		$error = true;
		add_error(_t("Admin-ChangeUserPassword-Error|The two passwords you entered did not match."));
	}

	if($error == true) {
		return $error;
	}
	$user_id = trim($_POST["user"]);
	if(shn_force_change_password($user_id, $password) == true) {
		return;
	}

	add_confirmation(_t("Admin-ChangeUserPassword-Message|The password was succesfully reset."));

	shn_admin_reset_pwd();
}



function shn_admin_ch_pwd($error=false) {
	shn_auth_form_ch_pwd($error);
}



function shn_admin_ch_pwd_cr() {

	require_once("errors.inc");
	$error=_shn_admin_ch_pwd_cr();
	echo "<div id=\"result_msg\">";
	if($error) {
		$msg=_t("Admin-ChangeUserPassword-Message|An error ocurred");
	} else {
		$msg=_t("Admin-ChangeUserPassword-Message|The password was succesfully updated.");
	}
	if($error) {
		display_errors();
	}
	echo "</div>";
	_shn_admin_acl_system_menu();
}



/** Generates a form to enable/disable modules */
function shn_admin_acl_enable_mods() {

	global $global;

	$db = $global['db'];
	$perms = "";

	echo _t('Admin-EnableModules-Help|
		<br><b>Enable/Disable Modules</b> ~ rows are modules, columns are groups, intersection shows whether the module is enabled not<br><br>
		<div id="formcontainer">
	');
	shn_form_fopen2("admin?modsp&tabid=7", null, array('req_message'=>false));
	echo '
		<div id="result">
			<table>
			<thead>
			<td>&nbsp;</td>
	';

	$roles = _shn_acl_get_roles();
	foreach ($roles as $role=>$role_name) {
		echo "<td>".$role_name."</td>";
	}
	echo '
			</thead>
			<tbody>
	';

	$mods=shn_get_all_modules();

	foreach($mods as $mod=>$mod_arr) {

		echo '
			<tr>
			<td>'.$mod_arr[1].'</td>
		';

		foreach($roles as $role=>$role_name) {

			$perms = $perms.$mod_arr[0].":".$role.";";
			$name = trim($mod_arr[0].$role);
			$allow = false;
			if( _shn_acl_is_module_role( $mod_arr[0],$role)==true) {
				$allow=true;
			} else {
				$allow=false;
			}
			echo '<td><input type="checkbox" name="'.$name.'"';
			if($role == ADMIN && $mod_arr[0] == "admin") { echo "checked=true disabled=true"; }
			if($role != ADMIN && $mod_arr[0] == "admin") { echo "disabled=true"; }
			if($allow == true) { echo "checked=true"; }
			echo 'align="right" /></td>';
		}
		echo '</tr>';
	}
	echo '
		</tbody>
		</table>
		</div>
	';
	shn_form_hidden(array("perms" => $perms));
	shn_form_submit(_t("Admin-Modules-Button|Save ACL"), "class=\"styleTehButton\"");
	shn_form_fclose();
	echo '</div>';
}
function shn_admin_acl_enable_mods_p() {

	global $global;

	$error_flag = false;

	$db = $global["db"];
	$perm_string=$_POST{"perms"};
	$perms = explode(";",$perm_string);
	$sql = "DELETE FROM sys_group_to_module";
	$res = $db->Execute($sql);
	if(!$res && !$error_flag) {
		$error_flag = true;
	}

	// give admin module to admin role.
	$admin_role = 1;
	$sql = "INSERT INTO sys_group_to_module VALUES({$admin_role},'admin','enabled')";
	$res = $db->Execute($sql);
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
		add_error(_t("Admin-Modules-Message|The selection was not saved due to one or more errors."));
	}else{
		add_confirmation(_t("Admin-Modules-Message|The ACL changes were saved successfully."));
	}

	shn_admin_acl_enable_mods();
}


function shn_admin_changeClass() {

	global $global;
	$db = $global['db'];

	$q = "
		DELETE FROM sys_user_to_group
		WHERE p_uuid = '".mysql_real_escape_string(urldecode($_GET['p']))."';
	";
	$res = $db->Execute($q);
	$q2 = "
		INSERT INTO sys_user_to_group (`group_id`, `p_uuid`)
		VALUES ('".$_GET['g']."', '".mysql_real_escape_string(urldecode($_GET['p']))."');
	";
	$res2 = $db->Execute($q2);
	shn_admin_acl_user_edit_roles();
	add_confirmation(_t("Admin-User-Message|User's class updated successfully."));
}



/** Generates a form to edit roles of a user */
function shn_admin_acl_user_edit_roles($error=false) {

	global $global;
	$db = $global['db'];

	echo "
		<br>
		<div id=\"home\">"
		._t("Admin-ChangeUserRole-Message|Designate which group each use is apart of by clicking assign to change it to the desired group. The box colored <span style=\"color: orange; font-weight: bold;\">orange</span> denotes which group the user is currently apart of.")
		."</div><br><div id=\"formcontainer\">";

	shn_form_fopen2("rolesp", "admin", array('req_message' => false));

	echo "
		<div id=\"result\">
		<table>
		<thead>
		<td><strong><center>"._t("Admin-ChangeUserRole-TextField|UserID")."</center></strong></td>
		<td><strong>"._t("Admin-ChangeUserRole-TextField|Username")."</strong></td>
		<td><strong>"._t("Admin-ChangeUserRole-TextField|Real Name")."</strong></td>
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

	foreach($users as $user) {

		echo "<td>".$user['user_id']."</td><td>".$user['user_name']."</td><td>".$user['full_name']."</td>";
		foreach($roles as $role => $role_name) {
			if($user['group_id'] == $role) {
				echo "<td style=\"background-color: orange;\"><center>".$role_name."</center></td>";
			} else if($user['user_id'] == 1) {
				echo "<td>&nbsp;</td>";
			} else {
				echo "<td><center><a href=\"admin?class&tabid=4&p=".urlencode($user['p_uuid'])."&g=".$role."\">"._t("Admin-ChangeUserRole-Link|assign")."</a></center></td>";
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



