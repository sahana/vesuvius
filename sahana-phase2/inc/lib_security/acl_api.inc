<?php
/**
* This library provides an API for authorization ,using the SahanaACL class of acl.inc
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva(ravindra@opensource.lk)
* @copyright  Lanka Software Foundation - http://www.opensource.lk
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
*/
function shn_acl_add_user($user,$desc){
    $acl=new SahanaACL(NULL);
echo "here".$user ."and".$desc;
    return $acl->_shn_add_aro("users",$user,$desc);
}

/** 
*adds a role to user
*@return bool
*@param string user
*@param string role
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
*add an ACL for a role to an action in the action group with in the module
*therefore the action is permitted for the role
*e.g : Allow admin to execute "shn_or_register"
*@return bool
*@param string role
*@param string action ,since actions are unique ,no need for the module
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
removes  a User and from all the groups its under
this is a ARO
*/
function shn_rem_user($user){
    $acl=new SahanaACL;
}
/**
removes a role
e.g "admin" 
this is a ARO group
*/
function shn_rem_role($role){
    $acl=new SahanaACL;
}
/**
removes the action and removes it from all the action groups
it was under.
*/
function shn_rem_action($action){
    $acl=new SahanaACL;
}
/**
removes an action group under the module
e.g "create"
this is an AXO group under the module AXO group.
actually it will be removed from the actions sub group of 
the module.
e.g  it will be removed from "modules"->"or"->"actions" 
*/
function shn_rem_action_group($module,$action_group){
    $acl=new SahanaACL;
}
/**
*removes permission type
e.g "execute"
this is an ACO
*/
function shn_rem_perm_type($perm_type){
    $acl=new SahanaACL;
}

/**
removes a module
e.g "OR"
this is an AXO group
*/
function shn_rem_module($module){
    $acl=new SahanaACL;
}

/*
removes ACL for a user for one action
e.g for action shn_or_register
note : each action name is unique
and front controller passes this action name
*/

function shn_rem_perms_action_user($user,$action){
    $acl=new SahanaACL;

}
/*
removes ACL for a user for a group of actions
e.g for "create" action group
each action_group is stored uniquely
e.g or_create
*/
function shn_rem_perms_action_group_user($user,$action_group){
    $acl=new SahanaACL;

}
/*
removes ACL for a role for an action
e.g : Allow admin to execute "shn_or_register"
*/
function shn_rem_perms_action_role($role,$action){
    $acl=new SahanaACL;

}
/**
removes ACL for a role for a group of actions
e.g Allow admin to execute "or_create" actions
*/
function shn_rem_perms_action_group_role($role,$action_group){
    $acl=new SahanaACL;

}


/**
*end of deletes
*/
/******************************************************************/
/**
*permission checks
*/

/*
checks whether the user can execute a particular action
there is no point in asking whether a role has permissions.
as user A with a particular role may be denied a certian 
resource.
so its not a boolean answer for the role
user is ARO ,action is AXO
@return bool ,true if allowed
@param string user
@param string action
*/

function shn_acl_check_perms_action($user,$action){
    $acl=new SahanaACL(NULL);
    $res=$acl->_shn_check_permission('permissions','execute','users',$user,'actions',$action);
    return $res;
}

function shn_check_perms_action_case($user,$action,$case){
}

function shn_check_perms_table($user,$table,$perm_type){
}

function shn_check_perms_table_field($user,$table,$field,$perm_type){
}
/**
*end of checks
*/

/******************************************************************************/
/**
*gets
*/

