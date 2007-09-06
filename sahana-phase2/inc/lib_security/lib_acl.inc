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

function shn_acl_log_error($comment,$p_uuid=null,$user_name=null,$event_type=1){
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

function shn_acl_check_perms($tables_only, $tables_with_fields=null){
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
			return DENIED;
		}
	}
	return ALLOWED;
}

function _shn_acl_check_table_only_perms($table,$crud){
	global $global;
    $db=$global['db'];
  
	$length=strlen($crud);
	for ($i=0;$i<$length;$i++){
		$crud_pattern=$crud_pattern."%".substr($crud, $i, 1)."%";
	}
	
	$user=$_SESSION["user_id"];

	$roles=_shn_acl_get_roles($user);
	
	$q="select level_id from sys_tablefields_to_data_classification where table_field='{$table}' ";
    
    $res_acl=$db->Execute($q);
    if(($res_acl!=null) &&(!$res_acl->EOF)){
    	$level_id=$res_acl->fields["level_id"];
    	foreach ($roles as $role=>$role_name){
		
			$q="select crud from sys_group_to_data_classification where group_id={$role} and level_id={$level_id}  and crud LIKE '$crud_pattern'";

     		$res=$db->Execute($q);
    		if(($res!=null) &&(!$res->EOF)){
    
    			return ALLOWED;
    			
    		}else{
    			shn_error_display_restricted_access();
    			return DENIED;
    		}
    	}
    	shn_error_display_restricted_access();
    	return DENIED;
   
    }
    
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

function _shn_acl_get_roles($user=null){
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
    	$roles[ANONYMOUS]="Anonymous User";
    	return $roles;
    }
    //	array_push(
    	//	$roles,
    while(($res!=null) &&(!$res->EOF)){
    	$roles[$res->fields["group_id"]]=$res->fields["group_name"];
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

function shn_acl_install(){
	global $global;
    global $conf;
   	$status=true;
   	

   	include_once $global['approot'].'inc/lib_security/lib_auth.inc';
    include_once($global['approot']."/inc/lib_uuid.inc");
    $db=$global["db"];
 
    $root=shn_auth_add_user("Admin User",$_POST['admin_name'],$_POST['root_pwd'],ADMIN,null); 
 	 //add a "root" user to ACL users and add to 'admin' role
 	 //add a "registered" user to ACL users and add to 'registered' role
 	$reg_user=shn_auth_add_user("Sahana Registered User",$_POST['user_name'],$_POST['user_pwd'],REGISTERED,null);
    $roles=array(ADMIN,REGISTERED,ANONYMOUS);
	//$mods=array("home","pref");
	$mods=shn_get_all_modules(false);
	foreach($roles as $role){
		foreach ($mods as $mod){
			$sql="insert into sys_group_to_module values({$role},'{$mod}','enabled')";
			$res=$db->Execute($sql);
		}
	}

    $q="insert into config(module_id,confkey,value) values('admin','acl_base','installed')";	
    $res=$db->Execute($q);
    $q="insert into config(module_id,confkey,value) values('ws','authentication',true)";	
    $res=$db->Execute($q);
    
    if($_POST["acl"]=='enable'){
    	$q="insert into config(module_id,confkey,value) values('admin','acl_enabled',true)";
	}else{
		$q="insert into config(module_id,confkey,value) values('admin','acl_enabled',false)";
	}

	$db->Execute($q);
	$q="insert into config(module_id,confkey,value) values('admin','acl_locking',false)";	
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
		 		return $res;
	}	
	return $res;
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
?>
