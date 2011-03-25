<?
/**
 * @name         ACL Form Library
 * @version      1.0
 * @package      framework
 * @author       Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


require_once "constants.inc";

function shn_acl_log_msg($comment,$p_uuid=null,$user_name=null,$event_type=1) {
	global $global;
	$db = $global["db"];
	$timestamp = time();
	if($p_uuid==null) {
		$p_uuid=$_SESSION['user_id'];
	}
	if($user_name==null){
		$user_name=$_SESSION['user'];
	}
	$sql = "insert into password_event_log(changed_timestamp,p_uuid,user_name,comment,event_type) values($timestamp,'{$p_uuid}','{$user_name}','{$comment}',{$event_type})";
	$res = $db->Execute($sql);
}



function shn_get_allowed_mods_current_user() {
	$user = shn_current_user();
	if($user==null) {
		$roles[ANONYMOUS]="Anonymous User";
	} else {
		$roles=_shn_acl_get_roles($user);
	}

	$mods = array();
	foreach($roles as $role=>$name) {
		$mods_role= _shn_acl_modules_for_role($role);
		if($mods_role!=null) {
			foreach($mods_role as $mod) {
				array_push($mods,$mod);
			}
		}
	}
	$mods=array_unique($mods);
	return $mods;
}



function shn_get_enabled_mods_current_user() {
	$user=shn_current_user();
	if($user==null){
		$roles[ANONYMOUS]="Anonymous User";
	} else {
		$roles=_shn_acl_get_roles($user);
	}
	$mods=array();
	foreach($roles as $role=>$name) {
		$mods_role= _shn_acl_modules_for_role($role);

		if($mods_role!=null) {
			foreach($mods_role as $mod){
				array_push($mods,$mod);
			}
		}
	}
	$mods=array_unique($mods);
	return $mods;
}



function shn_acl_check_perms($mod, $module_function) {
	// ACL IS ALWAYS ON NOW :)
	return ALLOWED;
}




function shn_acl_deluser_roles($users){
	global $global;
	$db = $global['db'];

	// Insert a new user,group mapping into the sys_user_to_group table
	if($users == null) {
		// nothing
	} else {
		foreach ($users as $user) {

			// find p_uuid for the given use
			$q = "
				SELECT *
				FROM users
				WHERE `user_id` = '".$user."';
			";
			$res = $db->Execute($q);

			if($res != null) {
				$p_uuid = $res->fields['p_uuid'];

				$q2 = "
					delete from sys_user_to_group
					where p_uuid = '".$p_uuid."';
				";
				$res2 = $db->Execute($q2);

				if($res2 == false) {
					add_error($db->ErrorMsg());
					return $res;
				}
			}
		}
	}
	return $res;
}



/**
 *adds a role to user
 *@return bool
 *@param string user
 *@param string role
 *@access public
 */
function shn_acl_adduser_to_role($user, $role) {
	global $global;
	$db = $global['db'];

	// find p_uuid for the given user_id
	$q = "
		SELECT *
		FROM users
		WHERE `user_id` = '".$user."';
	";
	$res = $db->Execute($q);

	if($res != null) {
		$p_uuid = $res->fields['p_uuid'];

		// Insert a new user,group mapping into the sys_user_to_group table
		$q2 = "
			INSERT INTO sys_user_to_group(group_id, p_uuid) values('".$role."', '".$p_uuid."');
		";
		$res2 = $db->Execute($q2);

		if($res2 == false) {
			add_error($db->ErrorMsg());
		} else {
			//add_confirmation("user(".$user.") added to group(".$role.")");
		}
	}
}


/**
 *adds a role to user using uuid
 *@return bool
 *@param string user
 *@param string role
 *@access public
 */
function shn_acl_adduser_to_role_uuid($user, $role) {
	global $global;
	$db = $global['db'];
	$okay = true;

	// Insert a new user,group mapping into the sys_user_to_group table
	$q2 = "
		INSERT INTO sys_user_to_group(group_id, p_uuid) values('".$role."', '".$user."');
	";
	$res2 = $db->Execute($q2);

	if($res2 == false) {
		add_error($db->ErrorMsg());
		$okay = false;
	} else {
		//add_confirmation("user(".$user.") added to group(".$role.")");
	}
	return $okay;
}



function _shn_acl_get_roles($user=null, $anonymous=true){
	global $global;
	$db=$global['db'];
	$roles=array();

	if(($user==NULL)){
		$q="select * from sys_user_groups";
	}else{
		$q="select sys_user_groups.group_id,group_name from sys_user_to_group,sys_user_groups where p_uuid='{$user}' and sys_user_groups.group_id= sys_user_to_group.group_id ";
	}

	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		if($anonymous==true){
			$roles[ANONYMOUS]="Anonymous User";
		}
		return $roles;
	}
	//	array_push(
	//	$roles,
	while(($res!=null) &&(!$res->EOF)){
		if(($res->fields["group_id"]!=ANONYMOUS) or($anonymous==true)){
			$roles[$res->fields["group_id"]]=$res->fields["group_name"];
		}
		$res->MoveNext();
	}

	return $roles;
}



function _shn_acl_modules_for_role($role) {
	$mods=array();


	global $global;
	$db=$global['db'];
	$q="select status,module from sys_group_to_module where group_id='{$role}' and status='enabled'";

	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return null;
	}else{
		while(!$res->EOF){
			array_push($mods,$res->fields["module"]);
			$res->MoveNext();
		}
		return $mods;
	}

}



function _shn_acl_is_module_role($mod,$role) {
	global $global;
	$db = $global['db'];
	$q = "select status from sys_group_to_module where group_id='{$role}' and module='{$mod}'";
	$res = $db->Execute($q);
	if(($res==null) ||($res->EOF)) {
		return false;
	} else {
		if($res->fields["status"]=="enabled") {
			return true;
		} else {
			return false;
		}
	}
}



function _shn_acl_is_user_role($user, $role) {
	global $global;
	$db = $global['db'];
	$q = "select group_id from sys_user_to_group where p_uuid='{$user}' and sys_user_to_group.group_id=$role ";
	$res = $db->Execute($q);
	if(($res==null) ||($res->EOF)) {
		return false;
	} else {
		return true;
	}
}



function _shn_acl_is_user_role2($user, $role) {
	global $global;
	$db = $global['db'];

	// find p_uuid for the given user_id
	$q = "
		SELECT *
		FROM users
		WHERE `user_id` = '".$user."';
	";
	$res = $db->Execute($q);

	if($res != null) {
		$p_uuid = $res->fields['p_uuid'];

		$q2 = "
			select group_id
			from sys_user_to_group
			where p_uuid = '".$p_uuid."'
			and sys_user_to_group.group_id = '".$role."';
		";

		$res2 = $db->Execute($q2);
		if(($res2 == null) ||($res2->EOF)) {
			return false;
		} else {
			return true;
		}
	}
}





function _shn_acl_is_user_role_only($user,$role) {
	global $global;
	$db = $global['db'];
	$q = "select group_id from sys_user_to_group where p_uuid='{$user}' and sys_user_to_group.group_id=$role";
	$res = $db->Execute($q);
	if(($res==null) ||($res->EOF)) {
		return false;
	} else {
		$q="select group_id from sys_user_to_group where p_uuid='{$user}' and sys_user_to_group.group_id <> $role ";
		$res=$db->Execute($q);
		if(($res==null) ||($res->EOF)) {
			return true;
		} else {
			return false;
		}
	}
}



function shn_acl_is_signup_enabled() {
	global $global;
	$db = $global["db"];
	$q = "select value from config where module_id='admin' and confkey='acl_signup_enabled'";
	$res = $db->Execute($q);
	if(($res==null) ||($res->EOF)) {
		return true; //by default we allow signup
	} else {
		if(($res->fields['value']==1)) {
			return true;
		} else {
			return false;
		}
	}
}



function shn_acl_is_locking_enabled() {
	global $global;
	$db = $global["db"];
	$q = "select value from config where module_id='admin' and confkey='acl_locking'";
	$res = $db->Execute($q);
	if(($res==null) ||($res->EOF)) {
		return true; //by default we should have security
	} else {
		if(($res->fields['value']==1)) {
			return true;
		} else {
			return false;
		}
	}
}



/**
 * Installs the ACL to the database.
 *
 * @param String $root_username The sahana administrator username.
 * @param String $root_passwd The sahana administrator password.
 * @param String $sahana_username The sahana normal user's username.
 * @param String $sahana_password The sahana normal user's password.
 * @param boolean $enable_acl Whether to enable acl. true to enable, false to disable.Defaults to false.
 * @param String $extra_opts The extra options.
 * @return boolean Whether the operation succeeded.
 */
function shn_acl_install($root_username, $root_passwd, $sahana_username, $sahana_password, $enable_acl=true, $extra_opts=null) {
	global $global;
	global $conf;
	$status=true;

	include_once $global['approot'].'inc/lib_security/lib_auth.inc';
	include_once($global['approot']."/inc/lib_uuid.inc");
	$db=$global["db"];

	//add a "root" user to ACL users and add to 'admin' role
	$root=shn_auth_add_user("Admin User", $root_username, $root_passwd, ADMIN,ADMINUSER);

	//add a "registered" user to ACL users and add to 'registered' role
	$reg_user=shn_auth_add_user("Sahana Registered User",$sahana_username,$sahana_password,REGISTERED,null);

	//$roles=array(ADMIN,REGISTERED,ANONYMOUS,SUPERUSER,ORGADMIN,VOLCOORDINATOR,CAMPADMIN);
	$roles=array(ADMIN,SUPERUSER);

	//$mods=array("home","pref");
	$mods=shn_get_all_modules(false);
	foreach($roles as $role){
		foreach ($mods as $mod){
			if(($mod!="admin") or ($role==ADMIN)or ($role==SUPERUSER)){
				$sql="insert into sys_group_to_module values({$role},'{$mod}','enabled')";
				$res=$db->Execute($sql);
			}
		}
	}
	$roles=array(REGISTERED,ORGADMIN,VOLCOORDINATOR,CAMPADMIN);
	foreach($roles as $role){
		foreach ($mods as $mod){
			if(($mod=="home") or ($mod=="pref")){
				$sql="insert into sys_group_to_module values({$role},'{$mod}','enabled')";
				$res=$db->Execute($sql);
			}
		}
	}
	$role=ORGADMIN;
	$sql="insert into sys_group_to_module values({$role},'or','enabled')";
	$res=$db->Execute($sql);
	$role=CAMPADMIN;
	$sql="insert into sys_group_to_module values({$role},'cr','enabled')";
	$res=$db->Execute($sql);
	$role=VOLCOORDINATOR;
	$sql="insert into sys_group_to_module values({$role},'vm','enabled')";
	$res=$db->Execute($sql);
	$role=ANONYMOUS;
	$sql="insert into sys_group_to_module values({$role},'home','enabled')";
	$res=$db->Execute($sql);
	$sql="insert into sys_group_to_module values({$role},'pref','enabled')";
	$res=$db->Execute($sql);
}






/**
 * Enable Disable ACL Signup
 *
 * @param boolean $flag true to enable, false to disable.
 */
function shn_acl_enable_signup($flag=true){
	global $global;
	$db=$global["db"];
	$q="UPDATE config SET value='{$flag}' WHERE module_id='admin' AND confkey='acl_signup_enabled'";
	$res=$db->Execute($q);
}



/**
 * Get the name of a group by passing the group id.
 *
 * @param integer $role_id group id
 * @return String group name
 */
function shn_acl_get_group_name($role_id){
	global $global;
	$db = $global['db'];
	$query = "SELECT group_name FROM `sys_user_groups` where `group_id`=?";
	$res = $db->Execute($query,$role_id);

	return $res->fields[0];

}

