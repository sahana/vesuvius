<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Ravindra De Silva
 * @author       Chamindra <chamindra@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */



global $global;

require_once($global['approot']."/inc/lib_errors.inc");
require_once($global['approot']."/inc/lib_validate.inc");
require_once($global['approot']."inc/lib_security/auth_form.inc");
require_once($global['approot']."inc/lib_security/lib_auth.inc");
require_once($global['approot']."inc/lib_xajax.inc");
require_once("acl.inc");


function shn_admin_field_option_config() {
	require_once('lib_fo_config.inc');
	_shn_admin_field_option_config();
}



function shn_admin_default() {
	echo '
		<ul>
		<li><a href="index.php?mod=rez&act=adm_default">Resource Pages</a></li>
		<li><a href="index.php?mod=admin&act=add_user&tabid=0">User Management</a></li>
		<li><a href="index.php?mod=admin&act=acl_event_log">User Event Log</a></li>
		<li><a href="index.php?mod=admin&act=acl_enable_mods">Module Access Control</a></li>
		<li><a href="index.php?mod=admin&act=acl_enable_signup">Enable / Disable User Self Signup</a></li>
		<li><a href="index.php?mod=admin&act=acl_enable_locking">Enable / Disable User Account Locking</a></li>
		</ul>
	';


	// show build & version
	$revision_file = $global['approot']."/www/theme/lpf3/version";
	$time_file     = $global['approot']."/www/theme/lpf3/time";

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
		echo "version: <b>r".$version."</b> &nbsp; Build Time: <b>".$time."</b>";
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
	_shn_admin_acl_user_menu();
	shn_acl_form_change_user_status();
}



function shn_admin_acl_change_user_status_cr($error=false) {
	_shn_admin_acl_change_user_status_cr();
	_shn_admin_acl_enable_locking_on_lock_user();
	shn_admin_acl_change_user_status();
}



function shn_admin_acl_unlock_user($error=false) {
	_shn_admin_acl_user_menu();
	shn_acl_form_unlock_user();
}



function shn_admin_acl_unlock_user_cr($error=false) {
	_shn_admin_acl_unlock_user_cr();
	_shn_admin_acl_enable_locking_on_lock_user();
	shn_admin_acl_unlock_user();
}


function shn_admin_acl_event_log($error=false) {
	shn_acl_form_event_log();
}



function shn_admin_add_user($error = false) {
	_shn_admin_acl_user_menu();
	shn_auth_form_user_add($error);
}



function shn_admin_add_user_cr() {
	$error = false; // i guess we should init this value here since its being used below?
	require_once("errors.inc");
	if(shn_auth_add_user_cr() == true) {
		shn_admin_add_user();
		return;
	}
	_shn_admin_acl_user_menu();
	shn_auth_form_user_add($error);
}



function shn_admin_del_user($error=false) {
	_shn_admin_acl_user_menu();
	shn_auth_form_user_del();
}



function shn_admin_del_user_cr() {
	_shn_auth_del_user_cr();
	_shn_admin_acl_user_menu();
}



function shn_admin_reset_pwd($error=false) {
	_shn_admin_acl_user_menu();
	shn_auth_form_reset_pwd($error);
}



function shn_admin_reset_pwd_cr() {
	require_once("errors.inc");
	$done = _shn_admin_reset_pwd_cr();
	_shn_admin_acl_user_menu();
	shn_auth_form_reset_pwd();
}



function shn_admin_ch_pwd($error=false) {
	_shn_admin_acl_user_menu();
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
function shn_admin_acl_enable_signup()    { _shn_admin_acl_enable_signup(); }
function shn_admin_acl_enable_signup_cr() { _shn_admin_acl_enable_signup_cr(); }
function shn_admin_acl_enable_locking()   { _shn_admin_acl_enable_locking(); }
function shn_admin_acl_state()            { _shn_admin_acl_state(); }
function shn_admin_acl_user()             { _shn_admin_acl_user(); }
function shn_admin_acl_user_edit_roles($error=false) { _shn_admin_acl_user_edit_roles(); }
function shn_admin_acl_user_edit_roles_cr($error=false) { _shn_admin_acl_user_edit_roles_cr(); }



function shn_admin_acl_enable_locking_cr() {
	// changed by Ravith.
	// enable the locking
	$act = $_POST['action'];
	if($act == 'enable'){
		_shn_admin_acl_enable_locking_cr(true);
		add_confirmation(_("User Locking is enabled now."));
	}else if($act=='disable'){
		_shn_admin_acl_enable_locking_cr(false);
		add_confirmation(_("User Locking is disabled now."));
	}
	// show the ui
	shn_acl_form_enable_locking();
}



function shn_admin_acl_role_edit_perms() {
	_shn_admin_acl_role_edit_perms();
}



function  shn_admin_acl_role_edit_perms_cr() {
	_shn_admin_acl_role_edit_perms_cr();
}




/**
 * Inclusion of Snapshot admin module
 * notes: code to include the snapshot menu item actions
 * @edit: Greg Miernicki <miernickig@mail.nih.gov>
 */
if(file_exists($global['approot']."/mod/snap/admin_menu_actions.inc")) {
	require_once($global['approot']."/mod/snap/admin_menu_actions.inc");
}




function shn_admin_changeClass() {
	global $global;
	$db = $global['db'];

	$q = "
		DELETE FROM sys_user_to_group
		WHERE p_uuid = '".mysql_real_escape_string(base64_decode($_GET['p_uuid']))."';
	";
	$res = $db->Execute($q);


	$q2 = "
		INSERT INTO sys_user_to_group (`group_id`, `p_uuid`)
		VALUES ('".$_GET['group_id']."', '".mysql_real_escape_string(base64_decode($_GET['p_uuid']))."');
	";
	$res2 = $db->Execute($q2);
	_shn_admin_acl_user_edit_roles();
}





