<?php
/**
* This library helps uses phpgacl library to manage ACL
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

/**
make phpgacl work with the adodb installation rest of the system
uses
*/
define('ADODB_DIR', $global['approot']."3rd/adodb");
define ('TRUE','success');
define ('UEXIST','user already exists');
define ('UNEXIST','user does not exist');
define ('REXIST','Resource already exists');
define ('RNEXIST','Resource does not exist');
define ('AEXIST','ACL already exists');
define ('ANEXIST','ACL does not exist');
define ('NARG','NULL arguments');
global $global;
include_once($global['approot']."3rd/phpgacl/gacl.class.php");
require_once($global['approot']."3rd/phpgacl/gacl_api.class.php");

class SahanaAcl extends gacl_api {

/**
*constructor
*@param array options for the database
*/
function SahanaAcl($gacl_options){
    global $conf;
  // for the moment $gacl_options is hard coded
    if (! is_array($gacl_options)){
        $gacl_options = array(
                               'debug' => FALSE,
                               'items_per_page' => 100,
                               'max_select_box_items' => 100,
                               'max_search_return_items' => 200,
                               'db_type' => $conf['db_engine'],
                               'db_host' => $conf['db_host'],
                               'db_user' => $conf['db_user'],
                               'db_password' => $conf['db_pass'],
                               'db_name' => $conf['db_name'],
                               'db_table_prefix' => $conf['tbl_prefix'].'gacl_',
                               'caching' => FALSE,
                               'force_cache_expire' => TRUE,
                               'cache_dir' => '/tmp/phpgacl_cache',
                               'cache_expire_time' => 600
                              );
    }
    parent::gacl_api($gacl_options);
}
//}   
/*----------------------------------------------------------------------------------------*/
//Functions directly used by the API functions

function _shn_get_sub_group_id($group,$subgroup){

}

 // Copied from get_group_children in the parent class, this version returns
  // all of the fields, rather than just the group ids.  This makes it a bit
  // more efficient as it doesn't need the get_group_data call for each row.
function _shn_get_sub_groups($group_id, $group_type = 'AXO') {

    switch (strtolower(trim($group_type))) {
		case 'axo':
			$group_type = 'axo';
			$table = 'gacl_axo_groups';
			break;
		default:
			$group_type = 'aro';
			$table = 'gacl_aro_groups';
	}

	if (empty($group_id)) {
		return FALSE;
	}
    $q='select id,name,value from '.$table.' where parent_id='.$group_id;
	$res=$this->db->Execute($q);
    while(!$res->EOF){
       $sub_groups[]=array(
       'id' =>$res->fields[0].' ',
       'name'=>$res->fields[1].' ',
       'value'=>$res->fields[2].' ',
        );
       $res->MoveNext();
    }
	return $sub_groups;
}

function _shn_add_permission($aco_section,$aco,$aro_section,$aro,$aro_group,$axo_section,$axo,$axo_group,$allow,$enabled,$return_value,$acl_desc) {
    if(($aco_section==NULL)or($aco==NULL)){
        $aco_array=NULL;
    }else {
	    $aco_array = array($aco_section => array($aco) );
	}
    if(($aro_section==NULL)or($aro==NULL)){
        $aro_array=NULL;
    }else {
        $aro_array = array($aro_section => array($aro) );
    }                    
    if(($axo_section==NULL)or($axo==NULL)){
        $axo_array=NULL;
    }else {
        $axo_array = array($axo_section => array($axo) );
    }                  
    $allow = true;
	$enabled = true;
	$return_value = NULL;
    //The NULL values are for the more advanced options such as groups, and AXOs. Refer to the manual for more info.
	$result = $this->add_acl($aco_array, $aro_array, $aro_group,$axo_array, $axo_group, $allow, $enabled, $return_value, $acl_desc);
	if ($result == FALSE) {
	    return false;
    } else {
        return TRUE;
	}
}


function _shn_check_permission($aco_section,$aco,$aro_section,$aro,$axo_section,$axo){
    /*
    this phpgacl function is very smart.
    it retreives groups for the aro and checks
    permissions for those groups.
    final permission is the union of group permission
    plus individual permissions.
    */
	$res=$this->acl_check($aco_section,$aco,$aro_section,$aro,$axo_section,$axo);
	if ($res==FALSE){
        return false;
    } else {
    return TRUE;
    }
}

function _shn_add_section($section,$desc,$type){
	$res = $this->add_object_section($desc,$section, 10, 0, $type); //Must specifiy Object Type.
	if ($res == FALSE) {
        return false;
	} else {
        return TRUE;
    }
}

function _shn_add_aco($section,$aco,$aco_desc){
    
    if ((NULL==$section) or (NULL==$aco)) {
        return NARG;
    } else {
        $id = $this->get_object_id($section, $aco, "aco");
        if($id)
            return UEXIST;
        else {
	        $res = $this->add_object($section,$aco_desc,$aco, 10, 0, 'ACO'); //Must specifiy Object Type.
	        if ($res == FALSE) {
                return false;
	        } else {
	            return TRUE;
            }
	    }
    }
}

function _shn_add_axo($section,$axo,$axo_desc){
    if ((NULL==$section) or (NULL==$axo)) {
        return false;
    } else {
        $id=$this->get_object_id($section,$axo,"axo");
        if($id)
            return REXIST;
        else {
            $res = $this->add_object($section,$axo_desc,$axo, 10, 0, 'AXO'); //Must specifiy Object Type.
	        if ($res == FALSE) {
    	        return false;
	        } else {
   		        return TRUE;
	        }
	    }
    }
}

function _shn_add_aro($section,$aro,$aro_desc){
    if ((NULL==$section) or (NULL==$aro)) {
        return false;
    } else {
        $id=$this->get_object_id($section,$aro,"aro");
        if($id)
            return REXIST;
        else {
	        $res = $this->add_object($section,$aro_desc,$aro, 10, 0, 'ARO');
	        if ($res == FALSE) {
                return false;
	        } else {
   		        return TRUE;
	        }
	    }
    }
}

function _shn_add_aro_group($group,$desc,$parent){
	//$parent_id=$this->get_group_id($parent,NULL,"ARO");
    
   $this->add_group($group, $desc,$parent,'ARO');
    if ($res !== FALSE) {
    	//echo "Created ARO group sucessfully. <br>\n";
	} else {
   		//echo "Error creating ARO group.<br>\n";
	}
	return $res;
   // $this->add_group('fk2', 'foobar',10,'ARO');
    
}


function _shn_add_aco_group($group,$desc,$parent){
	$this->add_group($group, $desc,$parent,'ACO');
	if ($res !== FALSE) {
    	//echo "Created ACO group sucessfully. <br>\n";
	} else {
   		//echo "Error creating ACO group.<br>\n";
	}
	return $res;
}


function _shn_add_axo_group($group,$desc,$parent){
	$this->add_group($group, $desc,$parent,'AXO');
	if ($res !== FALSE) {
    	//echo "Created AXO group sucessfully. <br>\n";
	} else {
   		//echo "Error creating AXO group.<br>\n";
	}
	return $res;
}



/**
adds the $aro of $section to $group
*/
function _shn_add_to_aro_group($group,$section,$aro){
    $this->add_group_object($group,$section,$aro,'ARO'); 
	if ($res !== FALSE) {
    	//echo "added to ARO group sucessfully. <br>\n";
	} else {
   		//echo "Error adding to ARO group.<br>\n";
	}
	return $res;
}




function _shn_add_to_aco_group($group,$section,$aco){
	$this->add_group_object($group,$section,$aco,'ACO');
	if ($res !== FALSE) {
    	//echo "added to ACO group sucessfully. <br>\n";
	} else {
   		//echo "Error adding to ACO group.<br>\n";
	}
	return $res;
} 


function _shn_add_to_axo_group($group,$section,$axo){
	$this->add_group_object($group,$section,$axo,'AXO');
	if ($res !== FALSE) {
    	//echo "added to  AXO group sucessfully. <br>\n";
	} else {
   		//echo "Error adding to  AXO group.<br>\n";
	}
	return $res;
} 


/******************************************************************************/
/**
*gets
*/

/**
* gets roles assigned to an user
*@param string user
*/
function _shn_get_roles(){
	$q="select id from gacl_aro_groups where value='sahana'";
    $res=$this->db->Execute($q);
    $group_id=$res->fields[0];
    $q="select id,value,name from gacl_aro_groups where parent_id={$group_id}";
	$res=$this->db->Execute($q);
    while(!$res->EOF){
       $roles[]=array(
       'id' =>$res->fields[0].' ',
       'name'=>$res->fields[2].' ',
       'value'=>$res->fields[1].' ',
        );
       $res->MoveNext();
    }
	return $roles;
}

/**
* gets roles assigned to an user
*@param string user
*/
function _shn_get_roles_of_user($user){
    //$res=$this->acl_get_groups ("users",$user,NULL, 'ARO');
    $q="select id from gacl_aro_groups where value='sahana'";
    $res=$this->db->Execute($q);
    $group_id=$res->fields[0];
    $q="select gacl_aro_groups.id,gacl_aro_groups.value,gacl_aro_groups.name from gacl_aro_groups,gacl_groups_aro_map,gacl_aro where parent_id={$group_id} and gacl_aro.value='{$user}' and gacl_groups_aro_map.aro_id=gacl_aro.id and gacl_aro_groups.id=gacl_groups_aro_map.group_id";

    $res=$this->db->Execute($q);
    while(!$res->EOF){
       $roles[]=array(
       'id' =>$res->fields[0].' ',
       'name'=>$res->fields[2].' ',
       'value'=>$res->fields[1].' ',
        );
       $res->MoveNext();
    }
	return $roles;
}

function shn_get_users_of_role($role){
    $acl=new SahanaACL;
    $group_id=$this->get_group_id ($role, NULL,'ARO');
    $users=$this->get_group_objects ($group_id,'ARO','NO_RECURSE');
    return $users;
}
/**
returns an array of modules
*/
function _shn_get_modules(){
    $q="select id from gacl_axo_groups where value='sahana'";
$res=$this->db->Execute($q);
$group_id=$res->fields[0];
    $q="select id,value,name from gacl_axo_groups where parent_id={$group_id}";
	$res=$this->db->Execute($q);
    while(!$res->EOF){
       $modules[]=array(
       'id' =>$res->fields[0].' ',
       'name'=>$res->fields[2].' ',
       'value'=>$res->fields[1].' ',
        );
       $res->MoveNext();
    }
	return $modules;
}
/**
returns action groups of that module
*/
function _shn_get_module_action_groups($module){
    $q="select id from gacl_axo_groups where value='{$module}'";
    $res=$this->db->Execute($q);
    $group_id=$res->fields[0];
    $q="select id,value,name from gacl_axo_groups where parent_id={$group_id}";
    $res=$this->db->Execute($q);
    while(!$res->EOF){
       $act_groups[]=array(
       'id' =>$res->fields[0].' ',
       'name'=>$res->fields[2].' ',
       'value'=>$res->fields[1].' ',
        );
       $res->MoveNext();
    }
	return $act_groups;
}


/**
returns an array of actions , for each action there is an array
which specifies the action_groups it is in
*/
function _shn_get_module_actions($module){
    $act_groups=$this->_shn_get_module_action_groups($module);
    $i=0;
    while ($i<count($act_groups)){
        $group_id=$act_groups[$i]['id'];
        $q="select id,value,name from gacl_groups_axo_map,gacl_axo where group_id={$group_id} and gacl_axo.id=gacl_groups_axo_map.axo_id";
        $res=$this->db->Execute($q);
        while(!$res->EOF){
            $act[]=array(
            'id' =>$res->fields[0].' ',
            'name'=>$res->fields[2].' ',
            'value'=>$res->fields[1].' ',
             );
            $res->MoveNext();
        }
        $i=$i+1;
    }
    return $act;
    //return array_unique($act);
}
//end of gets
}
?>
