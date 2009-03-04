<?php
/**
 * Main Controller of the Social Network
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] .'inc/lib_menu.inc';
include_once $global['approot'].'inc/lib_form.inc';
include_once $global['approot'].'inc/lib_validate.inc';
include_once $global['approot'].'inc/lib_errors.inc';
include_once $global['approot'].'inc/lib_log.inc';
include_once $global['approot'].'mod/sn/lib_notification.inc';
include_once $global['approot'].'mod/sn/lib_sn.inc';
include_once $global['approot'].'mod/sn/sn_functs.inc';
include_once $global['approot'].'mod/sn/admin_functs.inc';

function shn_sn_mainmenu(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	shn_mod_menuopen(_t('Social Network Module'));

	shn_mod_menuitem('default',_t('Home'));
	if(isset($_SESSION['user_id'])){
		shn_sub_mod_menuopen(_t('My Profile'));
		shn_sub_mod_menuitem('view_profile',_t('View Profile'));
		shn_sub_mod_menuitem('edit_my_prof',_t('Edit Profile'));
		shn_sub_mod_menuclose();

		$q="SELECT role_id FROM sn_module_role WHERE user_id=?";
		$rs = $db->Execute($q,array($_SESSION['user_id']));
		$role_id_module=$rs->fields['role_id'];

		$q1="SELECT role_id FROM sn_group_role WHERE user_id=?";
		$rs1 = $db->Execute($q1,array($_SESSION['user_id']));
		$role_id_group=$rs1->fields['role_id'];

		$q2="SELECT role_id FROM sn_forum_role WHERE user_id=?";
		$rs2 = $db->Execute($q2,array($_SESSION['user_id']));
		$role_id_furum=$rs2->fields['role_id'];

		if(isset($_SESSION['user_id']) OR $role_id_module=="sn1" OR $role_id_module=="sn2" OR $role_id_group=="g1" OR $role_id_furum=="f1"){
			shn_sub_mod_menuopen(_t('Administration'));
			shn_sub_mod_menuitem("ad_default", _t("Admin Home"));
			shn_sub_mod_menuitem("ad_manage_groups", _t("Groups"));
			shn_sub_mod_menuitem("ad_manage_roles", _t("Roles"));
			//shn_sub_mod_menuitem("ad_manage_users", _t("User Management"));
			shn_sub_mod_menuitem("ad_manage_forums", _t("Forums"));
			shn_sub_mod_menuclose();
		}
	}

	if(isset($_SESSION['user_id'])==false){
		shn_sub_mod_menuitem('signup',_t('Sign Up Now'));
	}
	shn_mod_menuclose();

	//include the main menu so that the user can navigate outside the module
	include_once($global['approot'] . '/inc/handler_mainmenu.inc');
}

function shn_sn_default()
{
	global $global;
	//var_dump($_SESSION);
	//$db->debug=true;
	/*$notifications = shn_sn_get_notifications_for_user($_SESSION['user_id']);
	foreach($notifications as $n){
	echo $n;
	}*/

	include_once $global['approot'] . '/mod/sn/home.inc';
}

function shn_sn_signup(){
	if(isset($_SESSION['user_id'])==false || $_SESSION['user_id']<0){
		if(isset($_POST['save'])){
			_shn_sn_signup_cr();
		}else{
			_shn_sn_signup_form();
		}
	}
}

function shn_sn_signup_group(){
	echo "<h2>"._t("Slect Group")."</h2>";
	shn_form_fopen('signup_cr','sn');

	shn_form_fsopen(_t('Slect Group'));

	shn_form_fsclose();

	shn_form_submit(_t('Cancel'),"name='cancel'");
	shn_form_submit(_t('Submit'),"name='save'");
	shn_form_fclose();

}

function shn_sn_view_profile(){

	_shn_sn_view_profile();
}

function shn_sn_edit_my_prof(){

	_shn_sn_edit_my_prof();
}

function shn_sn_change_name(){

	_shn_sn_change_name();
}

function shn_sn_change_personal_details(){

	_shn_sn_change_personal_details();
}

function shn_sn_change_medical_information(){

	_shn_sn_change_medical_information();
}

function shn_sn_change_contact_information(){

	_shn_sn_change_contact_information();
}

function shn_sn_change_profile_visibility(){

	_shn_sn_change_profile_visibility();
}

function shn_sn_change_name_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	$full_name = $_REQUEST["full_name"];

	if(isset($_REQUEST['edit_full_name'])){

		$errors = array();
		if($_REQUEST["full_name"]==null){
			add_error(_t("Please fill the name"));
			shn_sn_change_name();
		}
		else{
			$sql = "UPDATE person_uuid SET full_name=? WHERE p_uuid=? ";
			$res = $db->Execute($sql,array($full_name,$_SESSION["user_id"]));
			shn_sn_edit_my_prof();
		}
	}
	else{
		shn_sn_edit_my_prof();
	}
}

function shn_sn_change_personal_details_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	$image_id = $_REQUEST["image_id"];

	if(isset($_REQUEST['edit_personal_details'])){

		$sql = "UPDATE person_details SET birth_date=?, opt_country=?, opt_race=?,opt_religion=?, opt_marital_status=?, opt_gender=?, occupation=? WHERE p_uuid=? ";
		$res = $db->Execute($sql,array($_POST['dob'],$_POST['opt_country'],$_POST['opt_race'],$_POST['opt_religion'],$_POST['opt_marital_status'],$_POST['gender'],$_POST['occupation'],$_SESSION["user_id"]));

			include_once $global['approot'].'inc/lib_image.inc';
			if($_FILES['picture']['error']!=null && $_FILES['picture']['error']!=UPLOAD_ERR_NO_FILE){
				// errors in image upload
				//$db->FailTrans();
				add_error(shn_file_upload_error_msg($_FILES['picture']['error']));
	
			}else{
	
				shn_image_to_db($_FILES['picture'],$_SESSION["user_id"],$image_id);
			}
	
		shn_sn_edit_my_prof();
	}

	else{
		shn_sn_edit_my_prof();
	}

}

function shn_sn_change_medical_information_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	if(isset($_REQUEST['edit_medical_information'])){

		$sql = "UPDATE person_physical SET opt_blood_type=?, height=?, weight=?,opt_eye_color=?, opt_skin_color=?, opt_hair_color=? WHERE p_uuid=? ";
		$res = $db->Execute($sql,array($_POST['opt_blood_type'],$_POST['height'],$_POST['weight'],$_POST['opt_eye_color'],$_POST['opt_skin_color'],$_POST['opt_hair_color'],$_SESSION["user_id"]));
		shn_sn_edit_my_prof();

	}else{
		shn_sn_edit_my_prof();
	}

}

function shn_sn_change_contact_information_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	$pgoc_uuid = $_POST["pgoc_uuid"];
    //var_dump($_REQUEST);

	if(isset($_REQUEST['edit_contact_information'])){
		//$db->debug=true;

		$query4 = "SELECT * FROM field_options WHERE field_name='opt_contact_type'";
		$res4 = $db->Execute($query4);
        //var_dump($_POST);
		while($row = $res4->FetchRow()){
			//echo "old_".$row['option_code'].'_value'."<br/>";
			$old_value = $_POST["old_".$row['option_code'].'_value'];
			$option_code = $row['option_code'];
			
			$query = "DELETE FROM contact WHERE pgoc_uuid=? AND opt_contact_type=? AND contact_value=?";
			$db->Execute($query,array($pgoc_uuid,$option_code,$old_value));
			
			$query5 = "INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES (?,?,?)";
			$db->Execute($query5,array($pgoc_uuid,$row['option_code'],$_POST['contact_'.$row['option_code']]));
            //var_dump($_POST['contact_'.$row['option_code']]);
		}
		shn_sn_edit_my_prof();

	}else{
		shn_sn_edit_my_prof();
	}

}
 
function shn_sn_change_profile_visibility_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	if(isset($_REQUEST['edit_profile_visibility'])){

		if(isset($_POST['show_profile'])){

			$sql = "UPDATE sn_public_profile SET public_profile=? WHERE p_uuid=? ";
			$res = $db->Execute($sql,array(1,$_SESSION["user_id"]));
		}else{
			$sql = "UPDATE sn_public_profile SET public_profile=? WHERE p_uuid=? ";
			$res = $db->Execute($sql,array(0,$_SESSION["user_id"]));
		}
		shn_sn_edit_my_prof();

	}else{
		shn_sn_edit_my_prof();
	}
}

function shn_sn_add_interest(){
	if(isset($_POST['save']) || isset($_POST['search']) || isset($_POST['add_intr'])){
		_shn_sn_add_interest_cr();
	}else if(isset($_POST['cancel'])){
		shn_sn_default();
	}else{
		_shn_sn_add_interest_form();
	}
}

function shn_sn_friends(){
	_shn_sn_friends_page();
}

function shn_sn_search_people(){
	echo "<h2>"._t("Sahana Social Networking :: Find A Friend")."</h2>";
	shn_tabmenu_open();
	shn_tabmenu_item('friends',_t('My Friends'));
	shn_tabmenu_item('search_people',_t('Find A Friend'));
	shn_tabmenu_close();
	if(isset($_REQUEST['search'])){
		_shn_sn_search_people_cr();
	}else{
		_shn_sn_search_people_page();
	}
}

function shn_sn_groups(){
	_shn_sn_groups_page();
}

function shn_sn_mailbox(){
	_shn_sn_mailbox_page();
}

function shn_image_sn_view_img(){
	global $global;
	$db = $global['db'];
	$xuuid = $_REQUEST['x_uuid'];

	if(isset($xuuid)){
		$res = $db->Execute("SELECT image_type,image FROM image WHERE x_uuid=?",array($xuuid));
		if($res->RecordCount()>0){
			$row = $res->FetchRow();
			header('ContentType: image/'.$row['image_type']);
			echo $row['image'];
		}
		return;
	}
}


function shn_sn_add_as_friend(){
	_shn_sn_add_as_friend();
}

function shn_sn_req_access(){

	if(isset($_POST['req_forum'])){
		_shn_sn_req_access_cr();
	}else if(isset($_POST['cancel'])){
		_shn_sn_forum_index();
	}else{
		_shn_sn_req_access();
	}

}

function shn_sn_req_access_group(){

	if(isset($_POST['req_group'])){
		_shn_sn_req_access_group_cr();
	}else if(isset($_POST['cancel'])){
		shn_sn_groups();
	}else{
		_shn_sn_req_access_group();
	}

}

function shn_sn_view_group_members(){

	_shn_sn_view_group_members();
}

function shn_sn_req_forum(){

	if(isset($_POST['request'])){
		_shn_sn_notification();
	}else if(isset($_POST['cancel'])){
		shn_sn_default();
	}else{
		_shn_sn_req_forum();
	}

}

function shn_sn_forum_index(){

	if(isset($_POST['request'])){

	}else if(isset($_POST['cancel'])){
		shn_sn_default();
	}else{
		_shn_sn_forum_index();
	}

}

function shn_sn_view_forum(){

	if(isset($_POST['create_topic'])){
		_shn_sn_create_topic_cr();
	}else if(isset($_POST['cancel'])){
		_shn_sn_forum_index();
	}else{
		_shn_sn_view_forum();
	}
}
function shn_sn_add_post(){

	if(isset($_POST['post'])){
		_shn_sn_add_post_cr();
	}else if(isset($_POST['cancel'])){
		_shn_sn_view_forum();
	}else{
		_shn_sn_add_post();
	}

}

function shn_sn_view_post(){

	_shn_sn_view_post();
}

function shn_sn_edit_post(){

	if(isset($_POST['edit_post'])){
		_shn_sn_edit_post_cr();
	}else if(isset($_POST['cancel'])){
		_shn_sn_add_post();
	}else{
		_shn_sn_edit_post();
	}
}

function shn_sn_delete_post(){

	if(isset($_POST['delete_post'])){
		_shn_sn_delete_post_cr();
	}else if(isset($_POST['cancel'])){
		_shn_sn_add_post();
	}else{
		_shn_sn_delete_post();
	}
}

function shn_sn_view_notifications(){
	_shn_sn_view_notifications();
}