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
	
	$user=$_SESSION["user_id"];
	$user=0;
	$roles=_shn_acl_get_roles($user);
	$q="select level_id from sys_tablefields_to_data_classification where table_field='{$table}' ";
    $res_acl=$db->Execute($q);
    if(($res_acl!=null) &&(!$res_acl->EOF)){
    	$level_id=$res_acl->fields["level_id"];
    	foreach ($roles as $role){
			$q="select crud from sys_group_to_data_classification where group_id={$role} and level_id={$level_id}";
    		$res=$db->Execute($q);
    		if(($res!=null) &&(!$res->EOF)){
    			
    			if($res->fields["crud"]>=$crud){
    				return ALLOWED;
    			}else{
    				shn_error_display_restricted_access();
    				return DENIED;
    			}
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
    if($user==null){
    	$q="select * from sys_user_groups";
    }else{
    	$q="select group_id,group_name from sys_user_to_group,sys_user_groups where p_uuid='{$user}' and sys_user_groups.group_id= sys_user_to_group.group_id ";
    }
    $res=$db->Execute($q);
    if(($res==null) ||($res->EOF)){
    	$roles[ANONYMOUS]="Anonymous User";
    	return;
    }
    //	array_push(
    	//	$roles,
    while(($res!=null) &&(!$res->EOF)){
    	$roles[$res->fields["group_id"]]=$res->fields["group_name"];
    	$res->MoveNext();
    }
   
    return $roles;
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

function shn_acl_install(){
	global $global;
    global $conf;
   	$status=true;
   	

   	include_once $global['approot'].'inc/lib_security/lib_auth.inc';
    include_once($global['approot']."/inc/lib_uuid.inc");
    $db=$global["db"];
   
   
    $conf['user_id']=2;
    $guest=shn_auth_add_user("Sahana Registered User",$_POST['user_name'],$_POST['user_pwd'],REGISTERED,$conf['user_id']); 
    //add a"guest" user to ACL users and add to 'guest' role

    $conf['root_id']=1;
    $root=shn_auth_add_user("Admin User",$_POST['admin_name'],$_POST['root_pwd'],ADMIN,$conf['root_id']); 
    //add a "root" user to ACL users and add to 'admin' role


    $q="insert into config(module_id,confkey,value) values('admin','acl_base','installed')";	
    $res=$db->Execute($q);

    if($_POST["acl"]=='enable'){
    	$q="insert into config(module_id,confkey,value) values('admin','acl_enabled',true)";
	}else{
		$q="insert into config(module_id,confkey,value) values('admin','acl_enabled',false)";
	}
	$db->Execute($q);
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
	$crud_arr= array(
			"delete_arr"=>array(1,3,5,7,9,11,13,15),
			"update_arr"=>array(2,3,6,7,10,11,14,15),
			"read_arr"=>array(4,5,6,7,12,13,14,15),
			"create_arr"=>array(8,9,10,11,12,13,14,15)	
			);
	$array=$crud."_arr";
	$res=array_search($crud_value,$crud_arr[$array],false);
	if(FALSE !== $res){
		
		return true;
	}else{
		
		return false;
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

function shn_acl_update_role_perms($role,$level,$total){
	global $global;
    $db=$global['db'];
  
   $q="update sys_group_to_data_classification set crud=$total where group_id=$role and level_id=$level";
 
   $res=$db->Execute($q);
 	if($res==false){
				add_error($db->ErrorMsg());
		 		return $res;
	}	
	return $res;
}
?>
