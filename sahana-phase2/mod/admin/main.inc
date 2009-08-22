<?php
/**
 *
 * Sahana Admin & ACL section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available throughacl_user_roles the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Ravindra <ravindra@opensource.lk>
 * @author     Chamindra <chamindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */

global $global;

include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once "menu.inc";
include_once "acl.inc";
include_once "location.inc";
include_once $global['approot']."inc/lib_security/auth_form.inc";
include_once $global['approot']."inc/lib_security/lib_auth.inc";
// Incident Management Module
include_once $global['approot']."mod/admin/ims_main.inc";
include_once $global['approot']."mod/admin/conf_admin.inc";

// Module Management Console
include_once $global['approot']."mod/admin/mmc_main.inc";
include_once $global['approot'] . '/inc/lib_xajax.inc';



function shn_admin_mainmenu()
{
	_shn_admin_mainmenu();
}

function shn_admin_view()
{
	global $global;
	?>
<p><b><?php echo _t("You called the admin view")?> </b></p>
<p><?php echo _t(" on module") ?></p>
	<?php
}

function shn_admin_field_option_config(){
	include_once 'lib_fo_config.inc';
	_shn_admin_field_option_config();
}

function shn_admin_default()
{
	global $global;
	global $conf;
	$db = $global['db'];
	include_once $global['approot']. 'inc/lib_security/lib_acl.inc';

	$result = $db->Execute("SELECT * FROM incident");
	$isDisasterNamed = ((isset($result) && $result)?($result->RecordCount() > 0):false);

	$result = $db->Execute("SELECT * FROM location");
	$isLocationsEntered = ((isset($result) && $result)?($result->RecordCount() > 0):false);

	$isSecurityEnabled = $conf['acl_enabled'];

	$result = $db->Execute("SELECT * FROM ct_catalogue");
	$isCatalogCreated = ((isset($result) && $result)?($result->RecordCount() > 0):false);

	$result = $db->Execute("SELECT value FROM config WHERE module_id='admin' AND confkey='gis_dflt'");
	$isGISSetup = ((isset($result) && $result)?($result->fields['value'] != ""):false);

	echo '<div id="home">';

	if(!$isLocationsEntered || !$isGISSetup || !$isCatalogCreated
	|| !$isDisasterNamed) {
		echo '<h2>'._t('Finalize Your Sahana Installation')."</h2>\n";
		echo "<p>"._t("There are still a few steps to be performed before you
                can start using your Sahana installation effectively.
                These items are given in priority order below:")."</p>\n";
	}
	echo "<ol>\n";
	if(!$isDisasterNamed) {
		echo '<li><b>'._t('Add Disaster Name').'</b>'._t(' - As this system can handle
                multiple disasters in the same system you need to
                first add the name of the first disaster you are using
                Sahana for. To do this in the navigation bar click on ').
                '&#34;'._t('Disaster Incidents').'&#34;'.
		_t(' followed by ').'<a href="?mod=admin&act=ims_level1">'
		.'&#34;'._t('Manage Disaster').'&#34;'.'</a> '.
		_t('and add the disaster name.').'</li><br/>';
	}

	if(!$isLocationsEntered) {
		echo '<li><b>'._t('Add Locations').'</b>'._t(' - Please enter some of the
                regions affected in the disaster by clicking the
                navigation bar on ').
                '&#34;'._t('Location Hierarchy').'&#34;'.
		_t(' followed by ').'<a href="?mod=admin&act=add_loc">'.
                '&#34;'._t('Add New Location').'&#34;'.'</a></li><br/>';
	}
	if(!$isCatalogCreated) {
		echo '<li><b>'._t('Create the Aid Catalog').'</b>'._t(' - The catalog
                of aid items has to be defined to use
                the Pledge/Request Management System and Inventory Management,
                you need to define the type of aid items available. To do this
                click on the').'<a href="?mod=cs&act=default">'.
                '&#34;'._t('Catalog System').'&#34;'.'</a> '._t('in the navigation bar and start adding
                aid items for the disaster').'</li><br/>';
	}
	if(!$isGISSetup) {
		echo '<li><b>'._t('Configure Geographical Information System (GIS) | Mapping').'</b>'._t(' - To configure GIS/Mapping in Sahana ').
		_t('visit the ')
		.'<a href="?mod=admin&act=gis_main">'.
                '&#34;'._t('GIS Configuration').'&#34; '.'</a>'._t('section.').'</li><br/>';
	}

	if(!$isSecurityEnabled) {
		?>
<font color="red"><?php echo _t("Current Security state: Disabled")?></font>
		<?php

		echo '<li><b>'. _t('Configure Default Security').'</b>'._t(' - By default Sahana is installed with open access. To prevent unauthorized access to the system enable logins and security by clicking ').'&#34;'.'<a href="?mod=admin&act=acl_enable_acl">'._t('Enable Security.').'</a>&#34;</li>';
	}

	echo "</ol>\n";
	?>
<h2><?php echo _t("Sahana System Administration")?></h2>
<p><?php echo _t("The System Administration section allows you to configure and customize Sahana based on your requirements. Each section on the Administration menu is grouped by the section. These sections are described below:")?></p>
<ul>
	<li><b><?php echo _t("Locations Hierarchy")?></b> <br />
	<?php echo _t("Add, modify and customized the affected locations and hierachies in the disaster")?></li>
	<li><b><?php echo _t("GIS Configuration")?></b> <br />
	<?php echo _t("Specify your mapping configuration and preferred mapping/GIS system to be used in Sahana")?></li>
	<li><b><?php echo _t("Module Configuration")?></b> <br />
	<?php echo _t("Contains specific configuration pages for each module that has been installed in the system allowing them to be customized individually and seperately.")?>
	</li>
	<li><b><?php echo _t("System Security")?></b> <br />
	<?php echo _t("Allows the system administrator to configure who gets access to what modules and actions available in Sahana")?></li>
	<li><b><?php echo _t("Language / Locale")?></b> <br />
	<?php echo _t("Translate the Sahana interface and terminology to a local language and that relevant for the disaster")?></li>
	<li><b><?php echo _t("Disaster Levels")?></b> <br />
	<?php echo _t("Define multiple disasters, sub incidents and events that this instance of Sahana will handle")?></li>
	<li><b><?php echo _t("Config Utils")?></b> <br />
	<?php echo _t("This section give you access to all technical configuration details and tools that can be changed in the system")?></li>
</ul>
</div>
	<?php
}

function shn_admin_modadmin()
{
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

function shn_admin_check_sec_policies()
{
	shn_acl_check_valid_policy();
}

function shn_admin_acl_change_user_status($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_acl_form_change_user_status();
}

function shn_admin_acl_change_user_status_cr($error=false)
{
	_shn_admin_acl_change_user_status_cr();
	_shn_admin_acl_enable_locking_on_lock_user();
	shn_admin_acl_change_user_status();
}

function shn_admin_acl_unlock_user($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_acl_form_unlock_user();
}
function shn_admin_acl_unlock_user_cr($error=false)
{
	_shn_admin_acl_unlock_user_cr();
	_shn_admin_acl_enable_locking_on_lock_user();
	shn_admin_acl_unlock_user();
}

function shn_admin_acl_event_log($error=false)
{
	shn_acl_form_event_log();
}

function shn_admin_add_user($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_auth_form_user_add($error);
}

function shn_admin_add_user_cr()
{
	include_once "errors.inc";
	if(shn_auth_add_user_cr()==true) {
		shn_admin_add_user();
		return;
	}

	_shn_admin_acl_user_menu();
	shn_auth_form_user_add($error);
}

function shn_admin_del_user($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_auth_form_user_del();
}

function shn_admin_del_user_cr()
{
	_shn_auth_del_user_cr();
	_shn_admin_acl_user_menu();
}

function shn_admin_reset_pwd($error=false)
{
	_shn_admin_acl_user_menu();
	shn_auth_form_reset_pwd($error);
}

function shn_admin_reset_pwd_cr()
{
	include_once "errors.inc";
	$done=_shn_admin_reset_pwd_cr();


	_shn_admin_acl_user_menu();

}

function shn_admin_ch_pwd($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_auth_form_ch_pwd($error);
}

function shn_admin_ch_pwd_cr()
{
	include_once "errors.inc";
	$error=_shn_admin_ch_pwd_cr();
	?>
<div id="result_msg"><?php
if($error){
	$msg="An error ocurred";
}else{
	$msg="The Password was succesfully updated ";
}

if($error)
display_errors();
?></div>
<?php
_shn_admin_acl_system_menu();
}




function shn_admin_acl_user_roles()
{

	_shn_admin_acl_user_roles();
}


function shn_admin_acl_privacy()
{

	_shn_admin_acl_privacy_menu(true);
}

function shn_admin_acl_enable_mods()
{

	_shn_admin_acl_enable_mods();
}
function shn_admin_acl_enable_mods_cr()
{

	_shn_admin_acl_enable_mods_cr();
}
function shn_admin_acl_enable_acl()
{

	_shn_admin_acl_enable_acl();
}

function shn_admin_acl_enable_acl_cr()
{

	_shn_admin_acl_enable_acl_cr();
}
function shn_admin_acl_enable_signup()
{

	_shn_admin_acl_enable_signup();
}

function shn_admin_acl_enable_signup_cr()
{

	_shn_admin_acl_enable_signup_cr();
}


function shn_admin_acl_enable_locking()
{

	_shn_admin_acl_enable_locking();
}
function shn_admin_acl_enable_locking_cr()
{
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

function shn_admin_acl_state()
{
	_shn_admin_acl_state();
}




function shn_admin_add_loc()
{
	_shn_admin_location_form();
}

function shn_admin_add_loc_cr()
{
	shn_location_add();
	_shn_admin_location_form();
}

function shn_admin_add_loc_crb()
{
	shn_location_addb();
	_shn_admin_location_form();
}

function shn_admin_view_loc()
{
	_shn_admin_location_view_form();
}

function shn_admin_view_loc_cr()
{
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

function shn_admin_edit_loc_cr()
{
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

function shn_admin_loc_range()
{
	_shn_admin_location_range_form();
}

function shn_admin_loc_range_cr()
{
	_shn_admin_loc_range_cr();
}


function shn_admin_loc_start()
{
	_shn_admin_location_start_form();
}

function shn_admin_loc_start_cr()
{
	_shn_admin_loc_start_cr();
}

function shn_admin_loc_lvl()
{
	_shn_admin_levels_form();
}
function shn_admin_loc_lvl_cr()
{
	_shn_adm_loc_lvl_cr();
}
function shn_admin_start_loc()
{
	_shn_admin_location_view_form();
}


/************************************/
function shn_admin_acl_user()
{
	_shn_admin_acl_user();
}
function shn_admin_acl_user_edit_roles($error=false)
{
	_shn_admin_acl_user_edit_roles();
}
function shn_admin_acl_user_edit_roles_cr($error=false)
{
	_shn_admin_acl_user_edit_roles_cr();
}

function shn_admin_acl_data_privacy()
{
	_shn_admin_acl_privacy_menu();
	_shn_admin_acl_data_privacy();
}
function shn_admin_acl_role_edit_perms()
{
	_shn_admin_acl_role_edit_perms();
}

function  shn_admin_acl_role_edit_perms_cr()
{
	_shn_admin_acl_role_edit_perms_cr();
}

function shn_admin_acl_data_classifications_tables()
{
	_shn_admin_acl_privacy_menu();
	_shn_admin_acl_data_classifications_tables();
}

function shn_admin_acl_data_classifications_tables_cr()
{
	_shn_admin_acl_data_classifications_tables_cr();
}
/*
 function shn_admin_acl_existing_perms_tab()
 {
 _shn_admin_acl_existing_perms_tab();
 }

 function shn_admin_acl_user_cr()
 {
 _shn_admin_acl_user_cr();
 }



 function shn_admin_acl_user_perms()
 {
 _shn_admin_acl_user_perms();
 }

 function shn_admin_acl_user_add_roles($module=NULL,$error=false)
 {
 _shn_admin_acl_user_add_roles();
 }

 function shn_admin_acl_user_add_roles_cr($module=NULL,$error=false)
 {
 _shn_admin_acl_user_add_roles_cr();
 }

 function shn_admin_acl_user_edit_roles($error=false)
 {
 _shn_admin_acl_user_edit_roles();
 }

 function shn_admin_acl_user_edit_roles_cr($error=false)
 {
 _shn_admin_acl_user_edit_roles_cr();
 }
 */

/**************************************/
/*
 function shn_admin_acl_role_perms()
 {
 _shn_admin_acl_role_perms();
 }

 function shn_admin_acl_role_edit_perms()
 {
 _shn_admin_acl_role_edit_perms();
 }

 function shn_admin_acl_role_edit_perms_cr()
 {
 $module=$_GET{"sel"};
 _shn_admin_acl_role_edit_perms_cr($module);
 }

 function shn_admin_acl_role()
 {
 _shn_admin_acl_role();
 }

 function shn_admin_acl_role_cr()
 {
 _shn_admin_acl_role_cr();
 }
 */

/***
 * Localization interface for language translation
 */
function shn_admin_lc_trns()
{
	print ("<h1><center>"._t("Language Translation")."</center></h1>");
	require_once('lc_translate.inc');
}

function shn_admin_lc_set()
{
	print ("<h1><center>"._t("Set Locale")."</center></h1>");
	require_once('lc_setlocale.inc');
}

function shn_admin_lc_db()
{
	print ("<h1><center>"._t("Database Translation")."</center></h1>");
	require_once('lc_db.inc');
}

//User interface language translation

function shn_admin_lc_ui_trns()
{
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

function shn_admin_lc_ui_trns_enable()
{
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

function shn_admin_lc_ui_trns_update()
{
	require_once('lc_ui_translate_update.inc');
	print ("<h1><center>"._t("Update Translation")."</center></h1>");

	if($_GET['update']=="Update") {
		_shn_admin_lc_translate_compile();

	}else {
		_shn_admin_lc_translate_update();
	}

}

function shn_admin_lc_add_new_lang()
{
	require_once('lc_add_new_language.inc');
	print ("<h1><center>"._t("Add/Remove language")."</center></h1>");
	_shn_admin_lc_add_new_language_form();
}

function shn_admin_lc_add_new_language_post()
{
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

function shn_admin_lc_add_new_module()
{
	require_once('lc_add_new_module.inc');
	print ("<h1><center>"._t("Add New Module")."</center></h1>");
	_shn_admin_lc_add_new_module();
}

function shn_admin_lc_add_new_module_post()
{
	require_once('lc_add_new_module.inc');

	if(isset($_POST['merge']))
	_shn_admin_lc_add_new_module_update();
}


function shn_admin_lc_file_browser()
{
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

function shn_admin_lc_javascript()
{
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
 * Module manager funciton
 */
function shn_admin_module_mgr(){
	global $global,$conf;
	$db = $global['db'];
	echo "<h2>"._t("Module Manager")."</h2>";
	echo "<table><tr>";
	echo "<th>"._('Module')."</th>";
	echo "<th>"._('Status')."</th>";
	echo "<th>"._('Actions')."</th>";
	echo "</tr>";
	$mod_dir = $global['approot']."mod";
	$mod_query = "SELECT module,status FROM modules";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();

	include_once $global['approot'].'inst/setup_utils.inc';
	$essencial_modules = _shn_setup_get_essencial_modules();

	if($dh = opendir($mod_dir)) {

		while (($file = readdir($dh)) !== false) {
			echo "<tr>";
			if(is_dir($mod_dir.'/'.$file)){
				//echo "<td>$file</td>";
				if($file!='..' && $file!='.' && $file!='CVS' && preg_match('/^\.w+$/i',$file)==false){
					echo "<td>".$conf['mod_'.$file.'_name']."</td>";
					echo "<td>".((trim($result_array[$file])=='installed')?_t('Installed'):_t('Not Installed'))."</td>";
					echo "<td>".((trim($result_array[$file])=='installed')?((array_search($file,$essencial_modules)==false)?_t('Uninstall Now'):''):_t('Install Now'))."</td>";
				}
			}

			//echo "filename: $file : filetype: " . filetype($dir . $file) . "\n";
			echo "</tr>";
		}
		closedir($dh);

	}
	echo "</table>";
}

/**
 * Inclusion of GIS admin menu functionality/actions
 */
include_once $global['approot'].'/inc/lib_gis/admin_acts.inc';

/**
 * Inclusion of Messaging admin menu
 * @edit: Mifan Careem <mifan@respere.com>
 * @todo check availability of messaing module
 */
include_once $global['approot']."/mod/msg/adm_menu_actions.inc";

/**
 * Inclusion of Snapshot admin module
 * notes: code to include the snapshot menu item actions
 * @edit: Greg Miernicki <miernickig@mail.nih.gov>
 */
include_once $global['approot']."/mod/snap/admin_menu_actions.inc";
