<?php
/**
 * This library generates common parts for the forms in security library.
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

global $global;
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']. 'inc/lib_security/acl_api.inc';
include_once $global['approot']. 'inc/lib_security/acl.inc';

/**
 * generates a multi select box of users
 * @param $multi (whether to enable multi select or not)
 * @return void
 * @access public
 * 
 */

function shn_acl_form_users($multi=false){
  global $global;
    $db=$global['db'];
    
  $q = "select user_id,full_name,name,user_name from org_users,person_uuid,org_main,users where org_users.user_id=person_uuid.p_uuid and org_users.org_id=org_main.o_uuid and users.p_uuid=person_uuid.p_uuid order by name";
  
    $res=$db->Execute($q);
    $users=array();
        
    while(!$res->EOF){
        array_push(
            $users,
            array(  'drop_desc'=>$res->fields[2].".".$res->fields[3],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
$type=$multi?"select":"multiselect";
$user_arr=array('desc'=>_("Users : "),'type'=>$type,'size'=>4,'name'=>"users[]",'options'=>$users,
                        'br'=>'1'
                        );
return $user_arr;

}

/**
 * generates a multi select box of roles
 * @return void
 * @access public
 * 
 */

function shn_acl_form_roles(){
  global $global;
    $db=$global['db'];

    $acl=new SahanaACL(NULL);
    $roles=array();
    $role_arr=$acl->_shn_get_roles();
    $i=0;
	while($i<=count($role_arr)){
        array_push(
            $roles,
            array(  'drop_desc'=>$role_arr[$i]["name"],
                    'value'=>$role_arr[$i]["value"]
            )       
        );
        
        $i=$i+1;
    }
$role_arr=array('desc'=>_("Roles : "),'type'=>"multiselect",'size'=>4,'name'=>"roles[]",'options'=>$roles,
                        'br'=>'1'
                        ) ;
return $role_arr;

}
/**
 * generates a multi select box of actions in a module
 * @param $modules
 * @return void
 * @access public
 * 
 */

function shn_acl_form_actions($module){
global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
   
    $act_arr=$acl->_shn_get_module_actions($module);
    $actions=array();
    $i=0;
	while($i<=count($act_arr)){
        array_push(
            $actions,
            array(  'drop_desc'=>$act_arr[$i]["name"],
                    'value'=>$act_arr[$i]["value"]
            )       
        );
        
        $i=$i+1;
    }
$arr=array('desc'=>_("Actions : "),'type'=>"multiselect",'size'=>4,'name'=>"actions[]",'options'=>$actions,'br'=>'1'
                        );
return $arr;
}

/**
 * generates a multi select box of action groups in a module
 * @param $module 
 * @param $multi (whether to enable multi select or not)
 * @return void
 * @access public
 * 
 */

function shn_acl_form_action_groups($module,$multi=true){
global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
   
    $act_group_arr=$acl->_shn_get_module_action_groups($module);
    $action_groups=array();
    $i=0;
	while($i<=count($act_group_arr)){
        array_push(
            $action_groups,
            array(  'drop_desc'=>$act_group_arr[$i]["name"],
                    'value'=>$act_group_arr[$i]["value"]
            )       
        );
        
        $i=$i+1;
    }

	$arr=array('desc'=>_("Action Groups : "),'type'=>$select,'size'=>4,'name'=>"action_groups[]",'options'=>$action_groups,'br'=>'1'
                        );
	$arr=$multi?array('desc'=>_("* Action Groups:"),'type'=>"multiselect",'size'=>4,'name'=>'action_groups[]','options'=>$action_groups,'br'=>'1'):array('desc'=>_("* Action Groups:"),'type'=>"dropdown",'name'=>'action_groups[]','options'=>$action_groups,'br'=>'1');    
	return $arr;
}

/**
 * generates a multi select box of action groups in a module, the value
 * is the id of the action group
 * @param $module 
 * @param $multi (whether to enable multi select or not)
 * @return void
 * @access public
 * 
 */

function shn_acl_form_action_groups_id($module,$multi=true){
	global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
   
    $act_group_arr=$acl->_shn_get_module_action_groups($module);
    $action_groups=array();
        $i=0;
	while($i<=count($act_group_arr)){
        array_push(
            $action_groups,
            array(  'drop_desc'=>$act_group_arr[$i]["name"],
                    'value'=>$act_group_arr[$i]["id"]
            )       
        );
        
        $i=$i+1;
    }
//echo $multi;
	//$select=$multi?"multiselect":"select";
$arr=array('desc'=>_("Select the Action Group : "),'type'=>$select,'size'=>4,'name'=>"action_groups[]",'options'=>$action_groups,'br'=>'1'
                        );

$arr=$multi?array('desc'=>_("* Action Groups:"),'type'=>"multiselect",'size'=>4,'name'=>'action_groups[]','options'=>$action_groups,'br'=>'1'):array('desc'=>_("* Action Groups:"),'type'=>"dropdown",'name'=>'action_groups[]','options'=>$action_groups,'br'=>'1');    

return $arr;
}
/**
 * Generates a select box of user organizations
 * @return array organizations
 * @access public
 */

function shn_user_orgs(){

	global $global;
    $db=$global['db'];
    
    $q = "select o_uuid,name from org_main";
    $res=$db->Execute($q);
    $orgs=array();
        
    while(!res==NULL && !$res->EOF){
        array_push(
            $orgs,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
	$org_arr=array('desc'=>_("Organization :"),'type'=>"dropdown",'name'=>'org','options'=>$orgs,'br'=>'1');
	return $org_arr;
}
