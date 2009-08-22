<?php
/**
 *
 * This library helps in authentication ,but not authorization. A vital component of the framework.
 * Developers are required to use this library for security.
 *
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

require_once "constants.inc";

function shn_acl_check_valid_policy(){
	global $global;
	global $conf;
	$approot = $global['approot'];
	$xdoc = new DomDocument;
	$xmlschema = $global['approot']."/inc/lib_security/sec_policy.xsd";
	$d = dir($approot."/mod");
	while (false !== ($f = $d->read())) {
		$xmlfile=$approot."mod/".$f."/sec_policy.xml";
		//   if (file_exists($xmlfile)&& ($f=='or')) {
		if (file_exists($xmlfile)) {
			$nice_name=$conf['mod_'.$f.'_name'];
			print _t("Validating the security policy file in ")."<span style='color: blue;font-weight:bolder'>".$nice_name."</span>"._t(" module ... ")."<br />";
			$xdoc->Load($xmlfile);
			//Validate the XML file against the schema
			if ($xdoc->schemaValidate($xmlschema)) {
				print "&nbsp;&nbsp;&nbsp;&nbsp;".$xmlfile."<span style='color: green;font-weight:bolder'>"._t(" is valid")."</span> <br /><br />";
			} else {
				print "&nbsp;&nbsp;&nbsp;&nbsp;".$xmlfile."<span style='color: red;font-weight:bolder'>"._t(" is In valid")."</span> <br /><br />";;
			}

		}
	}

}
function shn_acl_log_msg($comment,$p_uuid=null,$user_name=null,$event_type=1){
	global $global;
	$db=$global["db"];
	$timestamp=time();
	if($p_uuid==null){
		$p_uuid=$_SESSION['user_id'];
	}
	if($user_name==null){
		$user_name=$_SESSION['user'];
	}
	$sql="insert into password_event_log(changed_timestamp,p_uuid,user_name,comment,event_type) values($timestamp,'{$p_uuid}','{$user_name}','{$comment}',{$event_type})";
	$res=$db->Execute($sql);
}

function shn_get_allowed_mods_current_user(){
	if(shn_acl_is_enabled()==true){
		$user=shn_current_user();
		if($user==null){
			$roles[ANONYMOUS]="Anonymous User";
		}else{
			$roles=_shn_acl_get_roles($user);
		}

		$mods=array();
		/*
		 array_push($mods,'home');
		 if ($_SESSION['logged_in'] == true ){
		 array_push($mods,'pref');
		 }
		 */
		foreach($roles as $role=>$name){
			$mods_role= _shn_acl_modules_for_role($role);

			if($mods_role!=null){
				foreach($mods_role as $mod){
					array_push($mods,$mod);
				}
			}



		}
	}else{
		$mods=shn_get_all_modules(false);
	}
	$mods=array_unique($mods);
	return $mods;

}

function shn_get_enabled_mods_current_user(){

	$user=shn_current_user();
	if($user==null){
		$roles[ANONYMOUS]="Anonymous User";
	}else{
		$roles=_shn_acl_get_roles($user);
	}

	$mods=array();
	/*
	 array_push($mods,'home');
	 if ($_SESSION['logged_in'] == true ){
	 array_push($mods,'pref');
	 }
	 */
	foreach($roles as $role=>$name){
		$mods_role= _shn_acl_modules_for_role($role);

		if($mods_role!=null){
			foreach($mods_role as $mod){
				array_push($mods,$mod);
			}
		}



	}

	$mods=array_unique($mods);
	return $mods;

}
function shn_acl_check_perms($mod,$module_function){
	if(shn_acl_is_enabled()==false){
		return ALLOWED;
	}
	global $global;
	include_once $global['approot']."/inc/lib_xml.inc";
	$xml_file=$global['approot']."/mod/".$mod."/sec_policy.xml";
	if (file_exists($xml_file)){
		//read the XML file describing the security policy for that module.
		$xml =simplexml_load_file($xml_file);

		foreach ($xml->usercase as $case) {
			//$name= trim($case->name);//name of the service
			foreach ($case->functions->function as $function) {
				//if(findAttribute($case->funct, "id")==$module_function){
				if($function==$module_function){
					$tables=array();
					foreach ($case->tables->table as $table){
						$tables["$table"]=findAttribute($table, "perm");
					}
				}
			}
		}

		if($tables!=null){
			return shn_acl_check_table_only_perms($tables);
		}else{
			return ALLOWED;
		}
			
	}else{
		return ALLOWED;
	}
}

function shn_acl_check_table_perms($tables_only, $tables_with_fields=null){
	//$acl_enabled=shn_acl_get_state($module);
	if($tables_with_fields==null){
		return shn_acl_check_table_only_perms($tables_only);
	}
}
/*
 $tables= array(
 'field_options'=>'4',
 'org_main'=>'8'
 );


 */
function shn_acl_check_table_only_perms($tables){

	foreach ($tables as $table=>$crud){
		if(_shn_acl_check_table_only_perms($table,$crud)==DENIED){
			//echo $table." - > ".$crud." DENIED <br/>";
			return DENIED;
		}
	}
	return ALLOWED;
}

function _shn_acl_check_table_only_perms($table,$crud){
	global $global;
	$db=$global['db'];

	// Set $crud_pattern in CRUD order.
	$crud_pattern = _shn_acl_get_crud_str($crud);
	if($crud_pattern==null){
		return DENIED;
	}

	$user=$_SESSION["user_id"];

	$roles=_shn_acl_get_roles($user);

	$q="select level_id from sys_tablefields_to_data_classification where table_field='{$table}' ";

	$res_acl=$db->Execute($q);
	if(($res_acl!=null) && (!$res_acl->EOF)){
		$level_id=$res_acl->fields["level_id"];
		// array to hold all c, r , u and d 's.
		$crud_tmp_arr = array(null,null,null,null);

		foreach ($roles as $role=>$role_name){

			$q="select crud from sys_group_to_data_classification where group_id={$role} and level_id={$level_id} ";// and crud LIKE '$crud_pattern'

			$res=$db->Execute($q);
			//echo "RECORDS = ".$res->RecordCount()."<br/>";
			while(!$res->EOF){
				$str = $res->fields[0];
				$length=strlen($str);
				//echo "$str <br/>";
				for ($i=0;$i<$length;$i++){
					$crud_char=strtolower(substr($str,$i,1));
					switch ($crud_char){
						case "c":
							$crud_tmp_arr[0]="c";
							break;
						case "r":
							$crud_tmp_arr[1]="r";
							break;
						case "u":
							$crud_tmp_arr[2]="u";
							break;
						case "d":
							$crud_tmp_arr[3]="d";
							break;
					}
				}
				$res->MoveNext();
			}
		}
		$new_crud = "";
		// re create string
		for($i=0;$i<count($crud_tmp_arr);$i++){
			// append only if not null
			$new_crud=$new_crud.(($crud_tmp_arr[$i]!=null)?$crud_tmp_arr[$i]:"");
		}
		//var_dump($crud_pattern);
		//var_dump($new_crud);
		//var_dump(preg_match('/'.$crud_pattern.'/',$new_crud));

		if(preg_match('/'.$crud_pattern.'/',$new_crud)!=false){
			return ALLOWED;
		}else{
			$q = "SELECT level FROM sys_data_classifications WHERE level_id = '".$level_id."'";
			$result = $db->Execute($q);
			$sensitivity = $result->fields[0];
			$msg=_t("You don't have access to ")._lc($sensitivity)._t(" data, which is required for this functionality.");
			//shn_error_display_restricted_access($msg);
			add_error($msg);
			return DENIED;
		}

		/*	// check whether matches.
		 if(($res!=null) &&(!$res->EOF)){

			return ALLOWED;

			}else{
			//shn_error_display_restricted_access();
			return DENIED;
			}
			*/
		//shn_error_display_restricted_access();
		return DENIED;
			
	}

}

/**
 * Returns the crud string in the correct order,
 * no matter what order the crud letters are passed in.
 *
 * @param String $crud The string having the letters c,r,u,d in any order.
 * @return String The crud pattern having the letters in the correct order (crud).
 */
function _shn_acl_get_crud_str($crud){
	$length=strlen($crud);

	// Set $crud_pattern in CRUD order.
	$crud_pattern="";

	if($length>0){
		$crud_arr = array('\w?','\w?','\w?','\w?');
	}else{
		return null;
	}

	for ($i=0;$i<$length;$i++){
		$crud_char=strtolower(substr($crud,$i,1));
		switch ($crud_char){
			case "c":
				$crud_arr[0]="c";
				break;
			case "r":
				$crud_arr[1]="r";
				break;
			case "u":
				$crud_arr[2]="u";
				break;
			case "d":
				$crud_arr[3]="d";
				break;
		}
	}

	// append chars in array to a string. with succeeding %;
	for ($i=0;$i<4;$i++){
		$char=$crud_arr[$i];
		if($char!=null){
			$crud_pattern=$crud_pattern.$char;
		}
	}
	return $crud_pattern;
}


function shn_acl_deluser_roles($users){
	global $global;
	$db=$global['db'];
	// Insert a new user,group mapping into the sys_user_to_group table
	if($users==null){
			
	}else{
		foreach ($users as $user){
			$q = "delete from sys_user_to_group where p_uuid='{$user}'";
			$res=$db->Execute($q);
			if($res==false){
				add_error($db->ErrorMsg());
				return $res;
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
function shn_acl_adduser_to_role($user,$role){
	global $global;
	$db=$global['db'];
	// Insert a new user,group mapping into the sys_user_to_group table
	$q = "INSERT INTO sys_user_to_group(group_id,p_uuid) values($role,'{$user}')";

	$res=$db->Execute($q);
	if($res==false){
		add_error($db->ErrorMsg());
	}
	return $res;
}

function _shn_acl_get_roles($user=null,$anonymous=true){
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

function _shn_acl_modules_for_role($role){
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

function _shn_acl_is_module_role($mod,$role){

	global $global;
	$db=$global['db'];
	$q="select status from sys_group_to_module where group_id='{$role}' and module='{$mod}'";

	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return false;
	}else{
		if($res->fields["status"]=="enabled"){

			return true;
		}else{
			return false;
		}
			
	}

}

function _shn_acl_is_user_role($user,$role){
	global $global;
	$db=$global['db'];
	$q="select group_id from sys_user_to_group where p_uuid='{$user}' and sys_user_to_group.group_id=$role ";

	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
			
		return false;
	}else{
		return true;
	}

}

function _shn_acl_is_user_role_only($user,$role){
	global $global;
	$db=$global['db'];
	$q="select group_id from sys_user_to_group where p_uuid='{$user}' and sys_user_to_group.group_id=$role";
	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return false;
	}else{
		$q="select group_id from sys_user_to_group where p_uuid='{$user}' and sys_user_to_group.group_id <> $role ";
		$res=$db->Execute($q);
		if(($res==null) ||($res->EOF)){
			return true;
		}else{
			return false;
		}
			
	}

}

function shn_acl_is_enabled(){
	global $global;
	$db=$global["db"];
	$q="select value from config where module_id='admin' and confkey='acl_enabled'";
	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return true; //by default we should have security
	}else{
		if(($res->fields['value']==1)){
			return true;
		}else{
			return false;
		}
			
	}
}

function shn_acl_is_signup_enabled(){
	global $global;
	$db=$global["db"];
	$q="select value from config where module_id='admin' and confkey='acl_signup_enabled'";
	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return true; //by default we allow signup
	}else{
		if(($res->fields['value']==1)){
			return true;
		}else{
			return false;
		}
			
	}
}


function shn_acl_is_locking_enabled(){
	global $global;
	$db=$global["db"];
	$q="select value from config where module_id='admin' and confkey='acl_locking'";
	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return true; //by default we should have security
	}else{
		if(($res->fields['value']==1)){
			return true;
		}else{
			return false;
		}
			
	}
}

function shn_acl_is_web_service_auth_enabled(){
	global $global;
	$db=$global["db"];
	$q="select value from config where module_id='ws' and confkey='authentication'";
	$res=$db->Execute($q);
	if(($res==null) ||($res->EOF)){
		return true; //by default we should have security
	}else{
		if(($res->fields['value']==1)){
			return true;
		}else{
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
function shn_acl_install($root_username,$root_passwd,$sahana_username,$sahana_password,$enable_acl=false,$extra_opts=null){
	global $global;
	global $conf;
	$status=true;


	include_once $global['approot'].'inc/lib_security/lib_auth.inc';
	include_once($global['approot']."/inc/lib_uuid.inc");
	$db=$global["db"];

	$root=shn_auth_add_user("Admin User",$root_username,$root_passwd,ADMIN,ADMINUSER);
	//add a "root" user to ACL users and add to 'admin' role
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

	$q="insert into config(module_id,confkey,value) values('admin','acl_base','installed')";
	$res=$db->Execute($q);
	$q="insert into config(module_id,confkey,value) values('ws','authentication',true)";
	$res=$db->Execute($q);

	if($enable_acl){
		$q="insert into config(module_id,confkey,value) values('admin','acl_enabled',true)";
	}else{
		$q="insert into config(module_id,confkey,value) values('admin','acl_enabled',false)";
	}

	$db->Execute($q);
	$q="insert into config(module_id,confkey,value) values('admin','acl_locking',false)";
	$res=$db->Execute($q);
	$q="insert into config(module_id,confkey,value) values('admin','acl_signup_enabled',true)";
	$res=$db->Execute($q);
	return $status;


}

function shn_acl_sys_data_tables(){
	global $global;
	$db=$global['db'];

	$q="select table_field,level_id from sys_tablefields_to_data_classification order by table_field";
	$res=$db->Execute($q);
	$levels=array();

	while(!$res->EOF){
		//$name=$res->fields[2].".".$res->fields["full_name"];
		$name=$res->fields["level_id"];
		$levels[$res->fields["table_field"]]=$name;
		$res->MoveNext();
	}

	return $levels;
}

function shn_acl_data_classifications_list(){
	global $global;
	$db=$global['db'];

	$q="select * from sys_data_classifications order by level_id";
	$res=$db->Execute($q);
	$levels=array();

	while(!$res->EOF){
		//$name=$res->fields[2].".".$res->fields["full_name"];
		$name=$res->fields["level"];
		$levels[$res->fields["level_id"]]=$name;
		$res->MoveNext();
	}
	return $levels;

}

function _shn_acl_get_role_data_classification_crud($role,$data_level){
	global $global;
	$db=$global['db'];

	$q="select crud from sys_group_to_data_classification where group_id=$role and level_id=$data_level";
	$res=$db->Execute($q);
	if(($res==NULL)||($res->EOF)){
		return 0;
	}else{

		return($res->fields["crud"]);

	}


}
function _shn_acl_is_crud_group($crud,$crud_value){

	$chr= substr($crud, 0, 1);

	if(stristr($crud_value,$chr)==FALSE){
		return false;
	}else{
		return true;
	}

}

function shn_acl_delrole_perms($role){
	global $global;
	$db=$global['db'];

	$q="delete from sys_group_to_data_classification where group_id=$role";
	$res=$db->Execute($q);
	if($res==false){
		add_error($db->ErrorMsg());
		return $res;
	}
	return $res;
}

function shn_acl_update_role_perms($role,$level,$crud){
	global $global;
	$db=$global['db'];

	$q="update sys_group_to_data_classification set crud='{$crud}' where group_id=$role and level_id=$level";

	$res=$db->Execute($q);
	if($res==false){
		add_error($db->ErrorMsg());
		return false;
	}
	return true;
}

function shn_acl_hmac_sha1($data,$key) {
	if(($data==null)or($key==null)){
		return null;
	}
	$blocksize = 64;
	$hashfunc = 'sha1';

	if (strlen($key) > $blocksize) {
		$key = pack('H*', $hashfunc($key));
	}

	$key = str_pad($key, $blocksize, chr(0x00));
	$ipad = str_repeat(chr(0x36), $blocksize);
	$opad = str_repeat(chr(0x5c), $blocksize);
	$hmac = pack(
                    'H*', $hashfunc(
	($key^$opad).pack(
                                    'H*', $hashfunc(
	($key^$ipad).$data
	)
	)
	)
	);
	return $hmac;
}


/**
 * Enable Disable self signup
 *
 * @param boolean $flag true to enable, false to disable.
 */
function shn_acl_enable($flag=true){
	global $global;
	$db=$global["db"];
	$q="UPDATE config SET value='{$flag}' WHERE module_id='admin' AND confkey='acl_enabled'";
	$res=$db->Execute($q);

	// force logout if acl has been disabled.
	if($flag==false){
		shn_session_end();
	}
}

/**
 * Enable Disable ACL
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

