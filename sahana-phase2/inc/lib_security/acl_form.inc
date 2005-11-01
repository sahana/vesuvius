<?php
/*
*
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
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']. 'inc/lib_security/acl_api.inc';
include_once $global['approot']. 'inc/lib_security/acl.inc';

function shn_acl_form_existing_perms($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
	
    ?>
<center><h2>Add User to Role</h2></center>
<h3>User can be assigned to Multiple Roles</h3>
 
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
	shn_form_open($header,false);
?>
    </br>
        <hr>
            <div id ="result">
                <h2>User Permissions</h2>
                <table>
                    <thead>
                        <td>User</td>
	                    <td>User Description</td>
                        <td>Permitted Actions</td>
	                    <td>Action Description</td>
                    </thead>
                    <tbody>
<?php 
   // $roles=array();
  //  $role_arr=$acl->_shn_get_roles();
    $q = "select user_id,full_name,name,user_name from org_users,person_uuid,org_main,users where org_users.user_id=person_uuid.p_uuid and org_users.org_id=org_main.o_uuid and users.p_uuid=person_uuid.p_uuid order by name";
    $res=$db->Execute($q);
 
    $i=0;
//	while($i<=count($role_arr)){
    while((!$res->EOF) && (!$res==NULL)){
        $user=$res->fields[0];
?>
    <tr>
        <td><b><?php echo $res->fields[2]?></b></td>
        <td><b><?php echo $res->fields[1]?></b></td>
        <td></td>
        <td></td>
    </tr>
<?php   
        $act_arr=$acl->_shn_get_module_actions($module);
        $i=0;
        while($i<count($act_arr)){
            $act=$act_arr[$i]["value"];
            $act_desc=$act_arr[$i]["name"];
            if (shn_acl_check_perms_action($user,$act)) {
?>
    <tr>
        <td></td>
        <td></td>
        <td><?php echo $act?></td>
        <td><?php echo $act_desc?></td>
  	</tr>  
<?php       }
        	$i=$i+1;
            }
        $res->MoveNext();
    }
   
?>
        </tbody>
    </table>
</div>

</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
}



function shn_acl_form_user_role($error=false)
{
    
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

?>
<center><h2>Add User to Role</h2></center>
<h3>User can be assigned to Multiple Roles</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
	shn_form_open($header,false);

$acl_users = array(
                        
                        array('desc'=>_("Users : "),'type'=>"multiselect",'size'=>4,'name'=>"users[]",'options'=>$users,
                        'br'=>'1'
                        ),// end of list form

			array('desc'=>_("Roles : "),'type'=>"multiselect",'size'=>4,'name'=>"roles[]",'options'=>$roles,
                        'br'=>'1'
                        ) // end of list form

                     );
    shn_form_add_component_list($acl_users,$section=true,$legend='',$return=false,$default_val_req=true);
?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
}


function shn_acl_form_role_perms($module,$error=false)
{
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


?>
<center><h2>Role Permissions</h2></center>
<h3>Assign Permissions to Action Groups</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
	shn_form_open($header,false);

$acl_users = array(
                        
                        array('desc'=>_("Roles : "),'type'=>"multiselect",'size'=>4,'name'=>"roles[]",'options'=>$roles,
                        'br'=>'1'
                        ),// end of list form

			array('desc'=>_("Action Groups : "),'type'=>"multiselect",'size'=>4,'name'=>"action_groups[]",'options'=>$action_groups,
                        'br'=>'1'
                        ) // end of list form

                     );
    shn_form_add_component_list($acl_users,$section=true,$legend='',$return=false,$default_val_req=true);

?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
    //$advanced= array('type'=>'button', 'value'=>'Advanced','href'=>'www.google.com');
	//shn_form_add_component($advanced,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
shn_acl_form_existing_perms($module,false);		
}


function shn_acl_form_user_perms($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
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


?>
<center><h2>User Permissions</h2></center>
<h3>Assign Permissions to Action Groups</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
	shn_form_open($header,false);

$acl_users = array(
                        
                        array('desc'=>_("User : "),'type'=>"multiselect",'size'=>4,'name'=>"roles[]",'options'=>$users,
                        'br'=>'1'
                        ),// end of list form

			array('desc'=>_("Action Groups : "),'type'=>"multiselect",'size'=>4,'name'=>"action_groups[]",'options'=>$action_groups,
                        'br'=>'1'
                        ) // end of list form

                     );
    shn_form_add_component_list($acl_users,$section=true,$legend='',$return=false,$default_val_req=true);

?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
    //$advanced= array('type'=>'button', 'value'=>'Advanced','href'=>'www.google.com');
	//shn_form_add_component($advanced,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
}

function shn_acl_form_advanced_perms($module,$error=false)
{
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

    $act_arr=$acl->_shn_get_module_actions($module);

    $actions=array();
    $i=0;
	while($i<=count($act_arr)){
        array_push(
            $actions,
            array(  'drop_desc'=>$act_arr[$i]["value"],
                    'value'=>$act_arr[$i]["id"]
            )       
        );
        
        $i=$i+1;
    }


?>
<center><h2>Advanced Permissions</h2></center>
<h3>Assign Permissions to Actions</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
	shn_form_open($header,false);

$acl_roles = array(
                        
                        array('desc'=>_("Roles : "),'type'=>"multiselect",'size'=>4,'name'=>"roles[]",'options'=>$roles,
                        'br'=>'1'
                        ),// end of list form

			array('desc'=>_("Actions : "),'type'=>"multiselect",'size'=>4,'name'=>"actions[]",'options'=>$actions,
                        'br'=>'1'
                        ) // end of list form

                     );
    shn_form_add_component_list($acl_roles,$section=true,$legend='',$return=false,$default_val_req=true);

$acl_users = array(
                        
                        array('desc'=>_("User : "),'type'=>"multiselect",'size'=>4,'name'=>"roles[]",'options'=>$users,
                        'br'=>'1'
                        ),// end of list form

			array('desc'=>_("Actions : "),'type'=>"multiselect",'size'=>4,'name'=>"actions[]",'options'=>$actions,
                        'br'=>'1'
                        ) // end of list form

                     );
    shn_form_add_component_list($acl_users,$section=true,$legend='',$return=false,$default_val_req=true);

?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
    //$advanced= array('type'=>'button', 'value'=>'Advanced','href'=>'www.google.com');
	//shn_form_add_component($advanced,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
}


?>
