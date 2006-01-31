<?php
/**
 * This library provides an API for authorization 
 * ,using the SahanaACL class of acl.inc
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

/**
*acl.inc includes functions directly interacting with
*phpgacl library.
*/

include_once("acl.inc");

/*****************************************************************************************/
/**
* ACO,AXO,ARO additions
*/

/**
* add  AXOs ,Resources to protect
*/

/**
*adds a module ,e.g "OR"
*this is an AXO group under "shn"
* @return bool true if succesfull ,else false
* @param string module name
* @param string description
* @access public
*/

function shn_acl_add_module($module,$desc){
    $acl=new SahanaACL(NULL);
    $parent = $acl->get_group_id("sahana",NULL,"AXO");
    $acl->_shn_add_axo_group($module,$desc,$parent);
}

/**
*adds an action group under the module
*e.g "create"
*this is an AXO group under the module AXO group.
*e.g  it will be added under "shn"->"or" 
*@return bool 
*@param string module name
*@param string action group
*@param string description
*@access public
*/
function shn_acl_add_action_group($module,$action_group,$desc){
    $acl=new SahanaACL(NULL);
    $axo_parent = $acl->get_group_id($module,NULL,"AXO");
    $acl->_shn_add_axo_group($module."_".$action_group,$desc,$axo_parent);
}

/**
*adds an action under the "shn"->"module"->"action_group"
*e.g "shn_or_register"
*this is an AXO
*this will be added to the group "shn"->"or"->"create"
*@return bool
*@param string module name
*@param string action group
*@param string action
*@param string  description
*@access public
*/

function shn_acl_add_action($module,$action_group=NULL,$action,$desc){
    $acl=new SahanaACL(NULL);
    $acl->_shn_add_section("actions","module actions","AXO");
    $acl->_shn_add_axo("actions",$action,$desc);
    if (is_null($action_group)){
        $axo_parent=$acl->get_group_id($module,NULL,"AXO");
    } else {
        $axo_parent=$acl->get_group_id($module."_".$action_group,NULL,"AXO");
    }
  //  $sub_groups=$acl->_shn_get_sub_groups($mod_id,"AXO");
  //  foreach ($sub_groups as $sub_group){
    //    if(trim($sub_group['value'])==trim($action_group)){
    //        $axo_parent=$sub_group['id'];
    //    }
    //}
    $acl->_shn_add_to_axo_group(trim($axo_parent),"actions",$action);
    
}
/**
*adds an action under the given parent
*this is an AXO
*@return bool
*@param string $axo_parent
*@param string $action an id 
*@param string  description
*@access public
*/
function shn_acl_add_action_id($axo_parent,$action,$desc){
    $acl=new SahanaACL(NULL);
    $acl->_shn_add_section("actions","module actions","AXO");
    $acl->_shn_add_axo("actions",$action,$desc);
    $acl->_shn_add_to_axo_group(trim($axo_parent),"actions",$action);
}
/**
*add a case under "shn"-> "module"->"action_group"->"action"
*e.g "shn_or_org_view" case "all" ,"one"
*this is an AXO
*this will be added to the group "shn"->"or"->"create"
*->"shn_or_org_view" as "shn_or_org_view_all"
*@return bool
*@param string module
*@param string action group
*@param string action
*@param string case
*@param string description
*@access public
*/
function shn_acl_add_action_case($module,$action_group=NULL,$action,$case,$desc){
    $acl=new SahanaACL(NULL);
    $axo=$action."_".$case;
    $acl->_shn_add_section("actions","module actions","AXO");
    $acl->_shn_add_axo("actions",$axo,$desc);
    if (is_null($action_group)){
    $axo_parent=$acl->get_group_id($module,NULL,"AXO");
    } else {
    $axo_parent=$acl->get_group_id($module."_".$action_group,NULL,"AXO");
    }
/*
    $mod_id=$acl->get_group_id($module,NULL,"AXO");
    $sub_groups=$acl->_shn_get_sub_groups($mod_id,"AXO");
    foreach ($sub_groups as $sub_group){
        if(trim($sub_group['value'])==trim($action_group)){
            $axo_parent=$sub_group['id'];
        }
    }
*/
    $acl->_shn_add_to_axo_group(trim($axo_parent),"actions",$axo);
}

      
/**
*add AROS ,requestors
*/

/**
*adds a role
*e.g "admin" 
*this is a ARO group
*@return bool
*@param string role
*@param string description
*@access public
*/
function shn_acl_add_role($role,$desc){
    $acl=new SahanaACL(NULL);
    $parent = $acl->get_group_id("sahana",NULL,"ARO");
    $acl->_shn_add_aro_group($role,$desc,$parent);
}


/** 
*adds a User
*this is a ARO
*@return bool
*@param string user
*@param string description
*@access public
*/
function shn_acl_add_user($user,$desc){
    $acl=new SahanaACL(NULL);
    return $acl->_shn_add_aro("users",$user,$desc);
}

/** 
*adds a role to user
*@return bool
*@param string user
*@param string role
*@access public
*/
function shn_acl_add_to_role($user,$role){
    $acl=new SahanaACL(NULL);
    $group_id=$acl->get_group_id($role,NULL,'ARO');
    $res=$acl->_shn_add_to_aro_group($group_id,"users",$user);
    return res;
}


/**
*add ACOs  
*/

/**
*adds permission type,e.g "execute",this is an ACO
*we could have gone without AXO's.
*but in the future we may provide ACL for database table rows.
*therefore AXO's are required.
*To specify permissions users to actions no need for AXO's.
*but since we are having AXO's as actions ,and an ACO
*named "execute" is specified for all those.
*@return bool
*@param string permission type
*@param string description
*@access public
*/
function shn_acl_add_perm_type($perm_type,$desc){
    $acl=new SahanaACL(NULL);
    $acl->_shn_add_section(trim("permissions"),"permission types","ACO");
    $acl->_shn_add_aco(trim("permissions"),$perm_type,$desc);
}


/**
*add ACLs
*/

/**
*add an ACL for a role to a module
*therefore the module is permitted for the role
*permissions for the module are inherited by "action groups"
*and "actions" under the module, unless overridden.
*@return bool
*@param string role
*@param string module
*@access public
*/

function shn_acl_add_perms_module_role($role,$module){
    $acl=new SahanaACL(NULL);
    $axo_group =$acl->get_group_id(trim($module),NULL,"AXO");
    $axo_groups=array($axo_group);
    $aro_group= $acl->get_group_id(trim($role),NULL,'ARO');
    $aro_groups=array($aro_group);
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),NULL,NULL,$aro_groups,NULL,NULL,$axo_groups,true,true,NULL,"first acl");
}


/**
*add an ACL for a role to an action group with in the module
*therefore the action group is permitted for the role
*permissions for the action group are inherited by 
*actions under the module, unless overridden.
*@return bool
*@param string role
*@param string module
*@param string action group
*@access public
*/

function shn_acl_add_perms_action_group_role($role,$module,$action_group){
    $acl=new SahanaACL(NULL);
    $aro_group= $acl->get_group_id(trim($role),NULL,'ARO');
    $aro_groups=array($aro_group);
/**
    $mod_id=$acl->get_group_id($module,NULL,"AXO");
    $sub_groups=$acl->_shn_get_sub_groups($mod_id,"AXO");
    foreach ($sub_groups as $sub_group){
        if(trim($sub_group['value'])==trim($module."_".$action_group)){
            $axo_group=$sub_group['id'];
        }
    }
**/
    if (is_null($action_group)){
        $axo_group=$acl->get_group_id($module,NULL,"AXO");
    } else {
        $axo_group=$acl->get_group_id($module."_".$action_group,NULL,"AXO");
    }

    $axo_groups=array($axo_group);
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),NULL,NULL,$aro_groups,NULL,NULL,$axo_groups,true,true,NULL,"first acl"); 

}

/**
*add an ACL for a role to an action group(given the id) with in the module
*therefore the action group is permitted for the role
*@return bool
*@param string role
*@param string module
*@param string action group
*@access public
*/

function shn_acl_add_perms_action_group_id_role_id($role,$module,$axo_group){
    $acl=new SahanaACL(NULL);
    $aro_groups=array($role);
/**
    $mod_id=$acl->get_group_id($module,NULL,"AXO");
    $sub_groups=$acl->_shn_get_sub_groups($mod_id,"AXO");
    foreach ($sub_groups as $sub_group){
        if(trim($sub_group['value'])==trim($module."_".$action_group)){
            $axo_group=$sub_group['id'];
        }
    }
**/
    $axo_groups=array($axo_group);
    echo $axo_group;
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),NULL,NULL,$aro_groups,NULL,NULL,$axo_groups,true,true,NULL,"first acl"); 

}


/**
*add an ACL for a role to an action in the action group with in the module
*therefore the action is permitted for the role
*e.g : Allow admin to execute "shn_or_register"
*@return bool
*@param string role
*@param string action ,since actions are unique ,no need for the module
*@access public
*/


function shn_acl_add_perms_action_role($role,$action){
    $acl=new SahanaACL(NULL);
    $aro_group= $acl->get_group_id(trim($role),NULL,'ARO');
    $aro_groups=array($aro_group);
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),NULL,NULL,$aro_groups,trim("actions"),trim($action),NULL,true,true,NULL,"first acl"); 
}

/**
*add an ACL for a role to an action case in the action group with in the module
*therefore the action case is permitted for the role
e.g : Allow admin to execute "shn_or_org_view_all"
*@return bool
*@param string role
*@param string action ,since actions are unique ,no need for the module
*@param string case
*@access public
*/


function shn_acl_add_perms_action_case_role($role,$action,$case){
    $acl=new SahanaACL(NULL);
    $action_case=$action."_".$case;
    $aro_group= $acl->get_group_id(trim($role),NULL,'ARO');
    $aro_groups=array($aro_group);
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),NULL,NULL,$aro_groups,trim("actions"),trim($action_case),NULL,true,true,NULL,"first acl");
}


/**
*user permissions
*/

/**
*add an ACL for a user to a module
*therefore the module is permitted for the user
*permissions for the module are inherited by "action groups"
*and "actions" under the module, unless overridden.
*@return bool
*@param string user
*@param string module
*@access public
*/

function shn_acl_add_perms_module_user($user,$module){
    $acl=new SahanaACL(NULL);
    $axo_group = $acl->get_group_id(trim($module),NULL,"AXO");
    $axo_groups=array($axo_group);
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),trim("users"),trim($user),NULL,NULL,NULL,$axo_groups,true,true,NULL,"first acl");
}


/**
*add an ACL for a user to an action group with in the module
*therefore the action group is permitted for the user
*permissions for the action group are inherited by 
*actions under the module, unless overridden.
*@return bool
*@param string user
*@param string module
*@param string action group
*@access public
*/

function shn_acl_add_perms_action_group_user($user,$module,$action_group){
        $acl=new SahanaACL(NULL);
/**
        $mod_id=$acl->get_group_id($module,NULL,"AXO");
        $sub_groups=$acl->_shn_get_sub_groups($mod_id,"AXO");
        foreach ($sub_groups as $sub_group){
        if(trim($sub_group['value'])==trim($module."_".$action_group)){
            $axo_group=$sub_group['id'];
        }
        }
**/
    if (is_null($action_group)){
        $axo_group=$acl->get_group_id($module,NULL,"AXO");
    } else {
        $axo_group=$acl->get_group_id($module."_".$action_group,NULL,"AXO");
    }
        $axo_groups=array($axo_group);
        $acl->_shn_add_permission(trim("permissions"),trim("execute"),trim("users"),trim($user),NULL,NULL,NULL,$axo_groups,true,true,NULL,"first acl");
}


/**
*add an ACL for a user to an action in the action group with in the module
*therefore the action is permitted for the user
*e.g : Allow admin to execute "shn_or_register"
*@return bool
*@param string user
*@param string action ,since actions are unique ,no need for the module
*@access public
*/

function shn_acl_add_perms_action_user($user,$action){
    $acl=new SahanaACL(NULL);
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),trim("users"),trim($user),NULL,trim("actions"),trim($action),NULL,true,true,NULL,"first acl");

}

/**
*add an ACL for a user to an action case in the action group with in the module
*therefore the action case is permitted for the user
e.g : Allow user to execute "shn_or_org_view_all"
*@return bool
*@param string user
*@param string action ,since actions are unique ,no need for the module
*@param string case
*@access public
*/


function shn_acl_add_perms_action_case_user($user,$action,$case){
    $acl=new SahanaACL(NULL);
    $action_case=$action."_".$case;
    $acl->_shn_add_permission(trim("permissions"),trim("execute"),trim("users"),trim($user),NULL,trim("actions"),trim($action_case),NULL,true,true,NULL,"first acl");
}




/**
*end of additions
*/
/*********************************************************/
/**
*deletes TODO
*/

/** 
 *removes  a User and from all the groups its under
 * this is a ARO
 * @todo function does not work right now 
 */
function shn_rem_user($user){
    $acl=new SahanaACL;
}
/**
 *removes a role
 * e.g "admin" 
 *this is a ARO group
 *@todo function does not work right now 
*/
function shn_rem_role($role){
    $acl=new SahanaACLg;
}
/**
 *removes the action and removes it from all the action groups
 *it was under.
 *@param $action
 *@return bool
 *
*/
function shn_rem_action($action){
    $acl=new SahanaACL(NULL);
    global $global;
    $q="delete from gacl_axo where value='{$action}'";
    $res=$global['db']->Execute($q);
    return $res;
}
/**
 *removes tthe action group and all the actions under it 
 *@param $action_group
 *@return bool
*/

function shn_rem_action_group($action_group){
    $acl=new SahanaACL(NULL);
    global $global;
    $act_arr=$acl->_shn_get_action_group_actions($action_group);
    for($i=0;i<count($act_arr);$i++){
       shn_rem_action($act_arr[$i]['value']); 
    }    
    $q="delete from gacl_axo_groups where id='{$action_group}'";
    $res=$global['db']->Execute($q);
    return $res;
}

/**
removes an action group under the module
e.g "create"
this is an AXO group under the module AXO group.
actually it will be removed from the actions sub group of 
the module.
e.g  it will be removed from "modules"->"or"->"actions" 

function shn_rem_action_group($module,$action_group){
  '  $acl=new SahanaACL;
}
*/
/**
*removes permission type
*e.g "execute"
*this is an ACO
*@todo function is not working
*/
function shn_rem_perm_type($perm_type){
    $acl=new SahanaACL;
}

/**
*removes a module
*e.g "OR"
*this is an AXO group
*@todo function is not working
*/
function shn_rem_module($module){
    $acl=new SahanaACL;
}

/*
*removes ACL for a user for one action
*e.g for action shn_or_register
*note : each action name is unique
*and front controller passes this action name
*@todo function is not workingS
*/

function shn_rem_perms_action_user($user,$action){
    $acl=new SahanaACL;

}
/*
*removes ACL for a user for a group of actions
*e.g for "create" action group
*each action_group is stored uniquely
*e.g or_create
*@todo function is not working
*/
function shn_rem_perms_action_group_user($user,$action_group){
    $acl=new SahanaACL;

}
/*
*removes ACL for a role for an action
*e.g : Allow admin to execute "shn_or_register"
*@todo function is not working
*/
function shn_rem_perms_action_role($role,$action){
    $acl=new SahanaACL;

}
/**
*removes ACL for a role for a group of actions
*e.g Allow admin to execute "or_create" actions
*@todo function is not working
*/
function shn_rem_perms_action_group_role($role,$action_group){
    $acl=new SahanaACL;

}
/**
 * Delete all the permissions related to a module
 * @param $module
 * @access public
 */
function shn_rem_perms_action_group($module){
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
    $act_arr=$acl->_shn_get_module_action_groups($module);
    $k=0;
     while($k<count($act_arr)){
        $q="delete gacl_aro_groups_map from gacl_aro_groups_map,gacl_axo_groups_map where gacl_aro_groups_map.acl_id=gacl_axo_groups_map.acl_id and gacl_axo_groups_map.group_id=".$act_arr[$k]['id'];
		$res=$db->Execute($q);
		$q="delete from gacl_axo_groups_map where group_id=".$act_arr[$k]['id'];
		$res=$db->Execute($q);
        $k=$k+1;
    }
	return $res;
}

function shn_acl_rem_user_role_map(){
	$q="delete from gacl_groups_aro_map";
	global $global;
	$res=$global['db']->Execute($q);
	return $res;
}

/**
*end of deletes
*/
/******************************************************************/
/**
*permission checks
*/

/**
*checks whether the user can execute a particular action
*there is no point in asking whether a role has permissions.
*as user A with a particular role may be denied a certian 
*resource.
*so its not a boolean answer for the role
*user is ARO ,action is AXO
*@return bool ,true if allowed
*@param string user
*@param string action
*access public
*/

function shn_acl_check_perms_action($user,$action){
    if($user==0){return true;}
    $acl=new SahanaACL(NULL);
    $res=$acl->_shn_check_permission('permissions','execute','users',$user,'actions',$action);
    return $res;
}
/**
*checks whether the user can execute a particular action group
*there is no point in asking whether a role has permissions.
*as user A with a particular role may be denied a certian 
*resource.
*so its not a boolean answer for the role
*user is ARO ,action is AXO
*@return bool ,true if allowed
*@param string user
*@param string action
*access public
*/

function shn_acl_check_perms_action_group($user,$action_group){
    if($user==0){return true;}
    $result=false;
    global $global;
    $acl=new SahanaACL(NULL);
    $db=$global['db'];
    $q="select gacl_aro_map.acl_id from gacl_aro_map,gacl_axo_groups_map where section_value='users' and value='{$user}' and gacl_aro_map.acl_id=gacl_axo_groups_map.acl_id and gacl_axo_groups_map.group_id={$action_group}";
    $res=$db->Execute($q);
    if(!$res->EOF)
        return true;
   $roles=$acl->_shn_get_roles_of_user($user);
    for($i=0;$i<count($roles);$i++){
        $q="select gacl_aro_groups_map.acl_id from gacl_aro_groups_map,gacl_axo_groups_map where gacl_aro_groups_map.group_id={$roles[$i]['id']} and gacl_aro_groups_map.acl_id=gacl_axo_groups_map.acl_id and gacl_axo_groups_map.group_id={$action_group}";
        $res=$db->Execute($q);
        if(!$res->EOF)
            return true;
    }    
   return $result;
}

/**
*checks whether the role has an entry for a particular action group
*user is ARO ,action is AXO
*@return bool ,true if allowed
*@param string user
*@param string action
*access public
*/

function shn_acl_check_role_perms_action_group($role,$action_group){
    $result=false;
    global $global;
    $db=$global['db'];
    $q="select gacl_aro_groups_map.acl_id from gacl_aro_groups_map,gacl_axo_groups_map where gacl_aro_groups_map.group_id={$role} and gacl_aro_groups_map.acl_id=gacl_axo_groups_map.acl_id and gacl_axo_groups_map.group_id={$action_group}";
    $res=$db->Execute($q);
    if(!$res->EOF)
            return true;
    return $result;
}

function shn_check_perms_action_case($user,$action,$case){
}

function shn_check_perms_table($user,$table,$perm_type){
}

function shn_check_perms_table_field($user,$table,$field,$perm_type){
}
/**
 * function to check whether the ACL BASE is installed
 * @return bool
 * @access public
 */
function shn_acl_is_base_installed(){
    global $global;
    $db=$global["db"];
    $q="select value from config where module_id='admin' and confkey='acl_base'";
    $res=$db->Execute($q);
    if(!$res->EOF && $res->fields[0]=='installed'){
        return true;
    }else {
        return false;
    }
}
/**
 * function to set the ACL state(enabled vs disabled), reads from the POST varaibles.
 * if enabled will disable and vice versa
 * @access public
 * 
 */
function shn_acl_set_state(){
	if('enable'==$_GET{"do"}){
		$q="update config set value='true' where module_id='admin' and confkey='acl'";
	}else{
		$q="update config set value='false' where module_id='admin' and confkey='acl'";
	}
	global $global;
	$global["db"]->Execute($q);
}
/**
 * function to read the ACL state
 * @access public
 * @return bool
 * 
 */
function shn_acl_get_state(){
    global $global;
    $q="select value from config where module_id='admin' and confkey='acl'";
    $db=$global["db"];
    $res=$db->Execute($q);
    if(!$res->EOF){
        //echo ($res->fields[0]);
        if($res->fields[0]=='true'){
          // echo "true it is";
           return true;
        }
	return false;
    }
    return false;
}
/**
*end of checks
*/

/******************************************************************************/
/**
*gets
*/

