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
require_once($global['approot']."/inc/lib_location.inc");
require_once($global['approot']."/inc/lib_validate.inc");
require_once($global['approot']."inc/lib_security/auth_form.inc");
require_once($global['approot']."inc/lib_security/lib_auth.inc");
require_once($global['approot']."inc/lib_xajax.inc");
require_once("acl.inc");
require_once("location.inc");


function shn_admin_field_option_config() {
	require_once('lib_fo_config.inc');
	_shn_admin_field_option_config();
}



function shn_admin_default() {
	echo '
		<ul>
		<li><a href="index.php?mod=admin&amp;act=snap_show">Snapshot Module ~ Database Backup and Restore</a></li><br>
		<li><a href="index.php?mod=rez&act=adm_default">Resource Pages</a></li><br>
		<br>
		<li><a href="index.php?mod=admin&act=add_user&tabid=0">User Management</a></li><br>
		<li><a href="index.php?mod=admin&act=acl_event_log">User Event Log</a></li><br>
		<li><a href="index.php?mod=admin&act=acl_enable_mods">Module Access Control</a></li><br>
		<br>
		<li><a href="index.php?mod=admin&act=acl_enable_signup">Enable / Disable User Self Signup</a></li><br>
		<li><a href="index.php?mod=admin&act=acl_enable_locking">Enable / Disable User Account Locking</a></li><br>
		<br>
		</ul>



	';

	// unused location stuff
	//echo '<h2><a href="index.php?mod=admin&amp;act=loc_lvl">Location Terminology</a></h2>';
	//echo '<h2><a href="index.php?mod=admin&amp;act=add_loc">Add New Location</a></h2>';
	//echo '<h2><a href="index.php?mod=admin&amp;act=view_loc">Modify Location</a></h2>';
	//echo '<h2><a href="index.php?mod=admin&amp;act=loc_range">Location Range</a></h2>';
	//echo '<h2><a href="index.php?mod=admin&amp;act=loc_start">Default Location</a></h2>';

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

	// @TODO remove. call the admin menu shn_<mod>_adminmenu if it exists
	/*$admin_menu = "shn_".$global['module']."_adminmenu";

	if(function_exists($admin_menu))
	$admin_menu();
	*/

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
function shn_admin_add_loc()              { _shn_admin_location_form(); }
function shn_admin_view_loc()             { _shn_admin_location_view_form(); }
function shn_admin_loc_range()            { _shn_admin_location_range_form(); }
function shn_admin_loc_range_cr()         { _shn_admin_loc_range_cr(); }
function shn_admin_loc_start()            { _shn_admin_location_start_form(); }
function shn_admin_loc_start_cr()         { _shn_admin_loc_start_cr(); }
function shn_admin_loc_lvl()              { _shn_admin_levels_form(); }
function shn_admin_loc_lvl_cr()           { _shn_adm_loc_lvl_cr(); }
function shn_admin_start_loc()            { _shn_admin_location_view_form(); }
function shn_admin_acl_user()             { _shn_admin_acl_user(); }
function shn_admin_acl_user_edit_roles($error=false) { _shn_admin_acl_user_edit_roles(); }
function shn_admin_acl_user_edit_roles_cr($error=false) { _shn_admin_acl_user_edit_roles_cr(); }



function shn_admin_add_loc_cr() {
	shn_location_add();
	_shn_admin_location_form();
}



function shn_admin_add_loc_crb() {
	shn_location_addb();
	_shn_admin_location_form();
}



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


function shn_admin_view_loc_cr() {
	if(isset($_POST{"chk_start"})) {
		$loc=0;
	}else {
		$level="loc_select_".$_POST{"opt_location_type"};
		$loc=$_POST{$level};
	}
	if($loc=="0"){
		add_error("Select the \"Location\" first and then select the \"Location Level\"");
		_shn_admin_location_view_form();
	}
	else{
		_shn_admin_location_edit_form($loc);
	}
}



function shn_admin_edit_loc_cr() {
	$act=$_POST{"action"};
	$loc=$_POST{"loc_id"};
	switch($act) {
		case "edit":
			$loc=array();
			$loc["loc"]=$_POST{"loc_id"};
			$loc["name"]=$_POST{"loc_name"};
			$loc["desc"]=$_POST{"desc"};
			$loc["iso"]=$_POST{"iso"};

			shn_location_edit($loc);
			_shn_admin_location_view_form();
			break;
		case "del":
			shn_location_del($loc);
			_shn_admin_location_view_form();
			break;
		default:
			_shn_admin_location_view_form();
			break;
	}
}



function shn_admin_acl_role_edit_perms() {
	_shn_admin_acl_role_edit_perms();
}



function  shn_admin_acl_role_edit_perms_cr() {
	_shn_admin_acl_role_edit_perms_cr();
}



/***
 * Localization interface for language translation
 */
function shn_admin_lc_trns() {
	print ("<h1><center>"._t("Language Translation")."</center></h1>");
	require_once('lc_translate.inc');
}



function shn_admin_lc_set() {
	print ("<h1><center>"._t("Set Locale")."</center></h1>");
	require_once('lc_setlocale.inc');
}



function shn_admin_lc_db() {
	print ("<h1><center>"._t("Database Translation")."</center></h1>");
	require_once('lc_db.inc');
}



//User interface language translation
function shn_admin_lc_ui_trns() {
	global $global;
	require_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	require_once('lc_ui_translate.inc');

	print ("<h1><center>"._t("User Interface Language Translation")."</center></h1>");
	if($_POST['locale']==null){
		_shn_admin_set_locale();
	}else {
		_shn_admin_lc_set_ui_translate();
		$locale = $_POST['locale'];
		_shn_lc_setcookielc($locale);
		_shn_lc_setsessionlc($locale);
	}
}



function shn_admin_lc_ui_trns_enable() {
	require_once('lc_ui_translate.inc');
	if(isset($_POST['lc'])) {
		if (!is_writable('../res')){
			add_error(_('sahana/res folder is not writable!'));
			_shn_admin_lc_set_ui_translate();
		}
		else
		_shn_admin_lc_ui_trns_enable();
	}
	if(isset($_POST['lc_dis'])) {
		_shn_admin_lc_ui_trns_disable();
	}
	if(isset($_POST['lc_update'])) {
		_shn_admin_lc_ui_trns_update();
	}
}



function shn_admin_lc_ui_trns_update() {
	require_once('lc_ui_translate_update.inc');
	print ("<h1><center>"._t("Update Translation")."</center></h1>");

	if($_GET['update']=="Update") {
		_shn_admin_lc_translate_compile();

	}else {
		_shn_admin_lc_translate_update();
	}
}



function shn_admin_lc_add_new_lang() {
	require_once('lc_add_new_language.inc');
	print ("<h1><center>"._t("Add/Remove language")."</center></h1>");
	_shn_admin_lc_add_new_language_form();
}



function shn_admin_lc_add_new_language_post() {
	require_once('lc_add_new_language.inc');
	if(isset($_POST['add'])) {
		if($_POST['lang_name']!=null && $_POST['lang_folder_name']!=null)
		_shn_admin_lc_add_new_language();
		else {
			add_error(_t('Language Name and Folder Name cannot be blank'));
			print ("<h1><center>"._t("Add/Remove language")."</center></h1>");
			_shn_admin_lc_add_new_language_form();
		}
	}
	else if(isset($_POST['remove'])) {
		_shn_admin_lc_remove_language();
	}
}



function shn_admin_lc_add_new_module() {
	require_once('lc_add_new_module.inc');
	print ("<h1><center>"._t("Add New Module")."</center></h1>");
	_shn_admin_lc_add_new_module();
}



function shn_admin_lc_add_new_module_post() {
	require_once('lc_add_new_module.inc');
	if(isset($_POST['merge']))
	_shn_admin_lc_add_new_module_update();
}



function shn_admin_lc_file_browser() {
	global $global;
	$locale = $_POST['locale'];
	//$file_type=$_POST['file_type'];
	$uploaddir = "../res/locale/$locale/LC_MESSAGES/";
	//"../res/locale/$locale/LC_MESSAGES/";
	//echo $uploaddir;
	$uploadfile = $uploaddir . basename($_FILES['userfile']['name']);

	if(move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
		add_confirmation('File uploaded sucessfully');
	}else {
		add_error('File uploaded failed');
	}
}



function shn_admin_lc_javascript() {
	global $global;
	global $conf;
	$approot = $global['approot'];
	$request  = $_REQUEST['request'];
	if($request=='first') {
		require_once $approot."/mod/admin/lc_first_process_request.inc";
		_find_translated_str();
	}
	else if($request=='second') {
		require_once $approot."/mod/admin/lc_second_process_request.inc";
		_find_str();
	}
	else if($request=='third') {
		require_once $approot."/mod/admin/lc_third_process_request.inc";
		_find_str();
	}
	else if($request=='select') {
		require_once $approot."/mod/admin/lc_select_process_request.inc";
		shn_admin_lc_select_tag();
	}shn_sub_mod_menuopen(_t("Location Hierarchy"));
}



/**
 * Inclusion of GIS admin menu functionality/actions
 */
if(file_exists($global['approot'].'/inc/lib_gis/admin_acts.inc')) {
	require_once($global['approot'].'/inc/lib_gis/admin_acts.inc');
}



/**
 * Inclusion of Messaging admin menu
 * @edit: Mifan Careem <mifan@respere.com>
 * @todo check availability of messaing module
 */
if(file_exists($global['approot']."/mod/msg/adm_menu_actions.inc")) {
	require_once($global['approot']."/mod/msg/adm_menu_actions.inc");
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





