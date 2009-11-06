<?php

/*
 *
 * Sahana Admin & ACL section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Ravindra <ravindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */

global $global;

include_once $global['approot']. 'inc/lib_security/lib_auth.inc';
include_once $global['approot'].'inc/lib_security/acl_form.inc';
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once "menu.inc";


function _shn_admin_acl_user()
{
	global $conf;
	$module=$_GET['sel'];
	_shn_admin_acl_user_menu();

	?>
<div id="home">
<h2><?php echo  _t('Welcome to Users= section'); ?></h2>

<ul>
	<li><?php echo _t('Add Users')?></li>
	<li><?php echo _t('Remove Users')?></li>
	<li><?php echo _t('Change your password if you are logged in')?></li>
	<li><?php echo _t('Edit Roles of User ')?></li>
</ul>
</div>

	<?php
}

function _shn_admin_acl_enable_mods()
{
	shn_acl_form_enable_mods();
}


function _shn_admin_acl_enable_mods_cr()
{
	global $global;
	$error_flag = false;

	$db=$global["db"];
	$perm_string=$_POST{"perms"};
	$perms=explode(";",$perm_string);
	$sql="DELETE FROM sys_group_to_module";
	$res=$db->Execute($sql);
	if(!$res && !$error_flag){
		// no overwrite if set.
		$error_flag = true;			// set the error flag once only
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

function _shn_admin_acl_enable_acl()
{
	shn_acl_form_enable_acl();
}
function _shn_admin_acl_enable_signup()
{
	shn_acl_form_enable_signup();
}
function _shn_admin_acl_enable_acl_cr($show=false)
{
	global $global;
	//$db=$global["db"];

	if($_POST['action']=='enable') {
		shn_acl_enable(true);
	}else {
		shn_acl_enable(false);
	}
	if($show==true){
		//if(($show==true)&&( shn_acl_check_perms("admin","acl_enable_acl_cr")==true)){
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
function  _shn_admin_acl_enable_signup_cr()
{
	global $global;
	//$db=$global["db"];

	if($_POST['action']=='enable') {
		shn_acl_enable_signup(true);
		add_confirmation(_t("Self-signup is enabled now"));
	}else if($_POST['action']=='disable'){
		shn_acl_enable_signup(false);
		add_confirmation(_t("Self-signup is disabled now"));
	}
	//if(($show==true)&&( shn_acl_check_perms("admin","acl_enable_acl_cr")==true)){
	shn_acl_form_enable_signup();


}

function _shn_admin_acl_enable_locking()
{
	shn_acl_form_enable_locking();
}

/**
 * Create the enable locking flag record.
 *
 * @param Boolean $enable The flag value
 *
 * Changed by Ravith.
 */
function _shn_admin_acl_enable_locking_cr($enable=false)
{
	global $global;
	$db=$global["db"];

	if($enable) {
		$q="UPDATE config SET value=true WHERE module_id='admin' AND confkey='acl_locking'";
	}else {
		$q="UPDATE config SET value=false WHERE module_id='admin' AND confkey='acl_locking'";
	}
	$res=$db->Execute($q);
}

function _shn_admin_acl_user_roles()
{
	_shn_admin_acl_user_roles_menu(true);
}



function _shn_admin_acl_data_privacy()
{
	shn_acl_form_role_select();
}

function _shn_admin_acl_role_edit_perms()
{
	shn_acl_form_role_perms_grid($_POST["roles"]);
}


function _shn_admin_acl_existing_perms_tab()
{
	$module=$_GET['sel'];
	shn_acl_form_existing_perms_tabular($module,false);
}


function _shn_admin_acl_user_perms()
{
	$module=$_GET['sel'];
	_shn_admin_acl_module_sub_menu($module);
	shn_acl_form_user_perms_grid($module,false);
}

function _shn_admin_acl_role_perms()
{
	$module=$_GET['sel'];
	_shn_admin_acl_role_menu($module);
	shn_acl_form_role_perms_grid($module,false);
}


function _shn_admin_acl_role_edit_perms_cr()
{
	$perm_string=$_POST{"perms"};
	$perms=explode(";",$perm_string);
	$role=$_POST{"role"};
	//	array_pop($perms);
    $success = true;
	for($i=1;$i<count($perms);$i++) {
		$save="";
		$rule=explode(":",$perms[$i]);
		$level=$rule[0];
		//if(!shn_acl_delrole_perms($level))
		//return false;
		$cruds=array(
     			"create"=>"c",
     			"read"=>"r",
     			"update"=>"u",
     			"delete"=>"d"
     			);
     	$total=0;
     	foreach($cruds as $crud=>$crud_value) {
			$name=$level.$crud;
			if(isset($_POST{trim($name)})) {
				$save=$save.$crud_value;
			}else{
				$save=$save."-";
			}
     	}
     	$success &= shn_acl_update_role_perms($role,$level,$save);
	}
	if($success == true){
	   add_confirmation(_t("Role permissions to access data were successfully updated."));
	}
	shn_acl_form_role_perms_grid($role);

}


function _shn_admin_acl_data_classifications_tables()
{
	shn_acl_form_classifications_to_data();
}

function _shn_admin_acl_data_classifications_tables_cr()
{
	global $global;
	$db=$global['db'];
	$tables=shn_acl_sys_data_tables();
	//var_dump($_POST);
	foreach($tables as $table=>$level_id) {

		$level_val=$_POST[$table];
		$q="UPDATE sys_tablefields_to_data_classification set level_id=$level_val where table_field='{$table}'";
			
		$res=$db->Execute($q);
		if($res==false) {
			add_error($db->ErrorMsg());
			return $res;
		}
	}
	// return $res;
	_shn_admin_acl_data_classifications_tables();
}



function  _shn_admin_acl_user_edit_roles()
{
	_shn_admin_acl_user_menu();
	shn_acl_form_user_edit_roles();
}


function _shn_admin_acl_user_edit_roles_cr($module=NULL,$error=false)
{
	$perm_string=$_POST{"perms"};
	$perms=explode(";",$perm_string);
	$users=explode(":",$_POST{"users"});
	$i=count($users)-1;

	/*
	 echo "i=".$i;
	 $tmp_users=array();
	 while($i>0) {
		array_push(
		$tmp_users,
		$users[$i]
		);
		$i=$i-1;
		}
		*/
	array_pop($users);


	if(!shn_acl_deluser_roles($users))
	return false;
	for ($i=0;$i<count($perms)-1;$i++) {
		$rule=explode(":",$perms[$i]);
		$user=$rule[0];
		$role=$rule[1];

		$name=$user.$role;

		if(isset($_POST{trim($name)})) {
			shn_acl_adduser_to_role($user,$role);
		}
	}
	$user=ADMINUSER;
	$role=ADMIN;
	shn_acl_adduser_to_role($user,$role);
	_shn_admin_acl_user_menu();
	add_confirmation(_t("User roles were updated successfully."));
	shn_acl_form_user_edit_roles();
}


function _shn_admin_acl_change_user_status_cr()
{
	$users=shn_auth_user_list();
	global $global;
	$db=$global["db"];
	foreach($users as $user=>$uname) {
		$status=$_POST[$user];
		$sql="UPDATE users SET status='{$status}' WHERE p_uuid='{$user}'";
		$res=$db->Execute($sql);
	}
}


function _shn_admin_acl_unlock_user_cr()
{
	$users=shn_auth_locked_user_list();
	global $global;
	$db=$global["db"];
	foreach($users as $user=>$uname) {
		$status=$_POST[$user];
		$sql="UPDATE users SET status='{$status}' WHERE p_uuid='{$user}'";
		$res=$db->Execute($sql);
	}
}


function _shn_admin_acl_user_add_roles($module=NULL,$error=false)
{
	if(is_null($module)) {
		$module=$_GET['sel'];
	}

	_shn_admin_acl_user_menu($module);
	global $conf;

	?>
<h2 align="center"><?php echo sprintf(_t("Configure ACL user permissions for %s"), $conf['mod_'.$module.'_name']); ?>
</h2>
	<?php

	shn_acl_form_user_add_roles($module,$error);
}


function _shn_admin_acl_user_add_roles_cr()
{
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
		?>
<div id="save"><?php echo _t("Users were succesfully added to Roles") ?></div>
		<?php
}
}

function _shn_admin_acl_role()
{
	$module=$_GET['sel'];
	global $conf;

	_shn_admin_acl_role_menu($module);
	?>
<h2 align="center"><?php echo _t("Configure ACL Role permissions") ?></h2>
	<?php
}

function _shn_admin_acl_role_cr()
{
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
		?>
<div id="save"><?php echo _t("Roles were succesfully given permission to action groups") ?>
</div>
		<?php
}
shn_admin_acl_role($module,false);
}

function _shn_admin_acl_user_add_perms()
{
	$module=$_GET['sel'];
	global $conf;
	?>
<h3><?php echo sprintf(_("Configure ACL for "),$conf['mod_'.$module.'_name'])?></h3>
	<?php
	_shn_admin_acl_user_menu($module);
	shn_acl_form_user_add_perms($module,false);
}


function _shn_admin_acl_user_edit_perms_cr()
{
	$perm_string=$_POST{"perms"};
	$perms=explode(";",$perm_string);
	var_dump($perms);
}

function _shn_admin_acl_user_edit_perms()
{
	$module=$_GET['sel'];
	global $conf;
	?>
<h3><?php echo sprintf(_t("Configure ACL for "),$conf['mod_'.$module.'_name']) ?></h3>
	<?php
	_shn_admin_acl_user_menu($module);
	shn_acl_form_user_edit_perms($module,false);
}

function _shn_admin_acl_user_cr()
{
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
		?>
<div id="save"><?php echo _t("Roles were succesfully given permission to action groups") ?>
</div>
		<?php
}

_shn_admin_acl_user($module,false);
}

/**
 * This will enable locking if system wide locking is disabled.
 * once a user is locked.
 *
 */
function _shn_admin_acl_enable_locking_on_lock_user(){
	$locked = shn_auth_locked_user_list();
	if(count($locked)>0 && shn_acl_is_locking_enabled()==false){
		_shn_admin_acl_enable_locking_cr(true);
		add_confirmation(_t("The selected user account(s) has been locked.")."<br/>"._t("System wide locking has been enabled too.").
		"<br/><a href='index.php?mod=admin&act=acl_enable_locking'>"._t("Click here if you need to disable locking")."</a>");
	}
}