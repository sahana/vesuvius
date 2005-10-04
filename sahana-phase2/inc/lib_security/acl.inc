<?php
/**
* This library helps in authorization
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/



include_once("3rdparty/phpgacl/gacl.class.php");
require_once("3rdparty/phpgacl/gacl_api.class.php");

class SahanaAcl extends gacl_api {

/**
*constructor
*@param array options for the database
*/
function SahanaAcl($gacl_options){
  // for the moment $gacl_options is hard coded
    if (! is_array($gacl_options)){
        $gacl_options=array();
        $gacl_options = array(
                                                                'debug' => 'TRUE',
                                                                'items_per_page' => 100,
                                                                'max_select_box_items' => 100,
                                                                'max_search_return_items' => 200,
                                                                'db_type' => 'mysql',
                                                                'db_host' => 'localhost',
                                                                'db_user' => 'sahana',
                                                                'db_password' => 'sahanapwd',
                                                                'db_name' => 'sahanaACL',
                                                                'db_table_prefix' => 'gacl_',
                                                                'caching' => FALSE,
                                                                'force_cache_expire' => TRUE,
                                                                'cache_dir' => '/tmp/phpgacl_cache',
                                                                'cache_expire_time' => 600
                                                        );
    }
    parent::gacl_api($gacl_options);
   }
   
/*----------------------------------------------------------------------------------------*/
//API functions
/*****************************************************************************************/
//additions
/** 
*adds a User
*this is a ARO
*@param string user
*@param string description
*/
function shn_add_user($user,$desc){
    _shn_add_aco("users",$user,$desc);
}
/**
*adds a role
*e.g "admin" 
*this is a ARO group
*@param string role
*/
function shn_add_role($role,$desc){
    _shn_add_aco("groups",$role,$desc);
}
/**
adds an action under the "module"->"action_group"
e.g "shn_or_register"
this is an AXO
this will be added to the group "modules"->"or"->"actions"->"create"
*/
function shn_add_action($module,$action_group=NULL,$action,$desc){
    _shn_add_axo("actions",$action,$desc);
    if(_shn_exists($module,'AXO')){
        if(_shn_exists($action_group,'AXO'){
            _shn_add_to_axo_group();
        }
    }
}
/**
adds an action group under the module
e.g "create"
this is an AXO group under the module AXO group.
actully it will be added under the actions sub group of 
the module.
e.g  it will be added under "modules"->"or"->"actions" 
*/
function shn_add_action_group($module,$action_group,$desc){
}
/**
adds permission type
e.g "execute"
this is an ACO
we could have gone without AXO's.
but in the future we may provide ACL for database table rows.
therefore AXO's are required.
to specify permissions users to actions no need for AXO's.
but since we are having AXO's are actions ,and an ACO
named "execute" is specified for all those.
*/
function shn_add_perm_type($perm_type,$desc){
}

/**
adds a module
e.g "OR"
this is an AXO group
*/
function shn_add_module($module,$desc){
}

/*
adds ACL for a user for one action
e.g for action shn_or_register
note : each action name is unique
and front controller passes this action name
*/

function shn_add_perms_action_user($user,$action){

}
/*
adds ACL for a user for a group of actions
e.g for "create" action group
each action_group is stored uniquely
e.g or_create
*/
function shn_add_perms_action_group_user($user,$action_group){

}
/*
adds ACL for a role for an action
e.g : Allow admin to execute "shn_or_register"
*/
function shn_add_perms_action_role($role,$action){

}
/**
adds ACL for a role for a group of actions
e.g Allow admin to execute "or_create" actions
*/
function shn_add_perms_action_group_role($role,$action_group){

}

//end of additions
/*********************************************************/
// deletes 

/** 
removes  a User and from all the groups its under
this is a ARO
*/
function shn_rem_user($user){
}
/**
removes a role
e.g "admin" 
this is a ARO group
*/
function shn_rem_role($role){
}
/**
removes the action and removes it from all the action groups
it was under.
*/
function shn_rem_action($action){
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
}
/**
*removes permission type
e.g "execute"
this is an ACO
*/
function shn_rem_perm_type($perm_type){
}

/**
removes a module
e.g "OR"
this is an AXO group
*/
function shn_rem_module($module){
}

/*
removes ACL for a user for one action
e.g for action shn_or_register
note : each action name is unique
and front controller passes this action name
*/

function shn_rem_perms_action_user($user,$action){

}
/*
removes ACL for a user for a group of actions
e.g for "create" action group
each action_group is stored uniquely
e.g or_create
*/
function shn_rem_perms_action_group_user($user,$action_group){

}
/*
removes ACL for a role for an action
e.g : Allow admin to execute "shn_or_register"
*/
function shn_rem_perms_action_role($role,$action){

}
/**
removes ACL for a role for a group of actions
e.g Allow admin to execute "or_create" actions
*/
function shn_rem_perms_action_group_role($role,$action_group){

}


//end of deletes
/******************************************************************/
//permission checks

/*
checks whether the user can execute a particular action
there is no point in asking whether a role has permissions.
as user A with a particular role may be denied a certian 
resource.
so its not a boolean answer for the role
user is ARO ,action is AXO
*/
function shn_check_perms_action($user,$action){
//AXO= excute , ACO section actions,ARO section is users
    _shn_check_permission('perm_type','execute',"users",$user,"actions",$action);
}

//end of checks
/******************************************************************************/
//gets

/**
* gets roles assigned to an user
*@param string user
*/
function shn_get_roles_of_user($user){
    $this->acl_get_groups ("users",$user,NULL, 'ARO')
}

function shn_get_users_of_role($role){
    $group_id=$this->get_group_id ($role, NULL,'ARO');
    $users=$this->get_group_objects ($group_id,'ARO','NO_RECURSE');
    return $users;
}
/**
returns an array of modules
*/
function shn_get_modules(){
}
/**
returns action groups of that module
*/
function shn_get_module_action_groups($module){

}
/**
returns an array of actions , for each action there is an array
which specifies the action_groups it is in
*/
function shn_get_actions_of_module($module)
}
//end of gets

//end of API functions

/*----------------------------------------------------------------------------------------*/
//Functions directly used by the API functions

function _shn_add_permission($aco_section,$aco,$aro_section,$aro,$aro_group,$axo_section,$axo,
$axo_group,$allow,$enabled,NULL,$acl_desc){

	$aco_array = array($aco_section => array($aco) );
	$aro_array = array($aro_section => array($aro) );
	$axo_array = array($axo_section => array($axo) );
    $allow = TRUE;
	$enabled = TRUE;
	$return_value = NULL;
	echo $aco_array;
	echo $aro_array;
	//The NULL values are for the more advanced options such as groups, and AXOs. Refer to the manual for more info.
	$result = $this->add_acl($aco_array, $aro_array, $aro_group,$axo_array, $axo_group, $allow, $enabled, $return_value, $note);
	if ($result !== FALSE) {
        echo "Created our first ACL sucessfully. Click <a href=admin/acl_test.php>here</a> to see it in action!<br>\n";
	} else {
        echo "Error creating ACL.<br>\n";
	}

}


function _shn_check_permission($aco_section,$aco,$aro_section,$aro,$axo_section,$axo){
	echo $aco;
	echo $aro;
    /*
    this phpgacl function is very smart.
    it retreives groups for the aro and checks
    permissions for those groups.
    final permission is the union of group permission
    plus individual permissions.
    */
	$res=$this->acl_check($aco_section,$aco,$aro_section,$aro,$axo_section,$axo);
	return $res;
}

function _shn_add_section($section,$desc,$type){
	$res = $this->add_object_section($desc,$section, 10, 0, $type); //Must specifiy Object Type.
	if ($res !== FALSE) {
        echo "Created section sucessfully. <br>\n";
	} else {
        echo "Error creating  section.<br>\n";
}
}

function _shn_add_aco($section,$aco,$aco_desc){
	$res = $this->add_object($section,$aco_desc,$aco, 10, 0, 'ACO'); //Must specifiy Object Type.
	if ($res !== FALSE) {
    	echo "Created ACO sucessfully. <br>\n";
	} else {
   		echo "Error creating ACO.<br>\n";
	}
	return $res;
}

function _shn_add_axo($section,$axo,$axo_desc){
	$res = $this->add_object($section,$axo_desc,$axo, 10, 0, 'AXO'); //Must specifiy Object Type.
	if ($res !== FALSE) {
    	echo "Created AXO sucessfully. <br>\n";
	} else {
   		echo "Error creating AXO.<br>\n";
	}
	return $res;
}

function _shn_add_aro($section,$aro,$aro_desc){
	$res = $this->add_object($section,$aro_desc,$aro, 10, 0, 'ARO');
	if ($res !== FALSE) {
        echo "Created $aro  sucessfully. <br>\n";
	} else {
   		echo "Error creating $aro  ARO.<br>\n";
	}
	return $res;
}

function _shn_add_aro_group($group,$desc,$parent){
	$this->add_group($group, $desc,$this->aro_group[$parent],'ARO');
	if ($res !== FALSE) {
    	echo "Created ARO group sucessfully. <br>\n";
	} else {
   		echo "Error creating ARO group.<br>\n";
	}
	return $res;
}
}

function _shn_add_aco_group($group,$desc,$parent){
	$this->add_group($group, $desc,$this->aco_group[$parent],'ACO');
	if ($res !== FALSE) {
    	echo "Created ACO group sucessfully. <br>\n";
	} else {
   		echo "Error creating ACO group.<br>\n";
	}
	return $res;
}

}
function _shn_add_axo_group($group,$desc,$parent){
	$this->add_group($group, $desc,$this->axo_group[$parent],'AXO');
	if ($res !== FALSE) {
    	echo "Created AXO group sucessfully. <br>\n";
	} else {
   		echo "Error creating AXO group.<br>\n";
	}
	return $res;
}

}

/**
adds the $aro of $section to $group
*/
function _shn_add_to_aro_group($group,$section,$aro){
	$this->add_group_object($this->aro_group[$group],$section,$aro,'ARO'); 
	if ($res !== FALSE) {
    	echo "added to ARO group sucessfully. <br>\n";
	} else {
   		echo "Error adding to ARO group.<br>\n";
	}
	return $res;
}
}



function _shn_add__to_aco_group($group,$section,$aco){
	$this->add_group_object($this->aco_group[$group],$section,$aco,'ACO');
	if ($res !== FALSE) {
    	echo "added to ACO group sucessfully. <br>\n";
	} else {
   		echo "Error adding to ACO group.<br>\n";
	}
	return $res;
} 

}
function _shn_add__to_axo_group($group,$section,$axo){
	$this->add_group_object($this->axo_group[$group],$section,$axo,'AXO');
	if ($res !== FALSE) {
    	echo "added to  AXO group sucessfully. <br>\n";
	} else {
   		echo "Error adding to  AXO group.<br>\n";
	}
	return $res;
} 

}

?>












