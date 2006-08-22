<?php
/**
 * This library generates all the forms required to add,modify and remove
 * user ACL settings.
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
include_once "acl_form_lib.inc";

/**
 * Generates a form to edit roles of an user
 * @access public
 * @return void
 */

function shn_acl_form_user_edit_roles($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
?>

<h3 align="center">Add & Remove Roles for Users</h3>

<div id="note">
Rows are User ,Columns are Roles ,Intersection shows whether the User is a member of the Role or not
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=admin&act=acl_user_edit_roles_cr','id'=>'formset');
shn_form_open($header,false);
?>
<div id ="result">
    <table>
        <thead>
        <td>
<?php
    $role_arr=$acl->_shn_get_roles();
    $k=0;
     while($k<count($role_arr)){
       echo "<td>".$role_arr[$k]['name']."</td>";
       $k=$k+1;
    }
?>       
    </thead>
     <tbody>
<?php    
    $q = "select user_id,full_name,name,user_name from org_users,person_uuid,org_main,users where org_users.user_id=person_uuid.p_uuid and org_users.o_uuid=org_main.o_uuid and users.p_uuid=person_uuid.p_uuid order by name";
    $res=$db->Execute($q);
    
    while((!$res->EOF) && (!$res==NULL)){
        $user=$res->fields[0];
        $org=$res->fields[2];
        $user_name=$res->fields[3];
   ?>
    <tr>
        <td>
        <?php echo $org."->".$user_name?>
        </td>
<?php
$k=0;
        while($k<count($role_arr)){
 			$role_id=$role_arr[$k]["id"];
 			$role=$role_arr[$k]["value"];
       		$perms=$perms.$user.":".$role.";";
			$name=trim($user.$role);
 	
	if ($acl->_shn_is_user_role($user,$role_id)) {
	 	$allow=true;
	}else{
         $allow=false;
    }
   
      	?><td><input type="checkbox" name="<?php echo $name?>"<?php if ($user=='0') echo "disabled=true";?> <?php if ($allow==true) echo "checked=true";?> algin="right" /></td>
<?php

       $k=$k+1;
    
        }
$res->MoveNext();
       
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>
<br />
<center>
<?php
$tmp=array('type'=>"hidden",'name'=>'perms','value'=>$perms); 
shn_form_add_component($tmp,$return=false,$default_val_req=false);
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Save');
	shn_form_add_component($submit,false,false);
?>
</center>
<?php
    //close the form
    shn_form_close(false);
?>
</div>
<?php	
}

/**
 * Generates a form to edit permissions of an user
 * @access public
 * @return void
 */

function shn_acl_form_user_edit_perms($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
?>

<h3 align="center">Edit User Permissions</h3>

<div id="note">
Rows are Actions ,Columns are Users ,Intersection shows whether the action is permitted or not
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=admin&act=acl_user_edit_perms_cr','id'=>'formset');
shn_form_open($header,false);
?>
<div id ="result">
    <table>
        <thead>
        <td>
<?php
    $act_arr=$acl->_shn_get_module_action_groups($module);
    $k=0;
     while($k<count($act_arr)){
       echo "<td>".$act_arr[$k]['name']."</td>";
       $k=$k+1;
    }
?>       
    </thead>
     <tbody>
<?php    
    $q = "select user_id,full_name,name,user_name from org_users,person_uuid,org_main,users where org_users.user_id=person_uuid.p_uuid and org_users.org_id=org_main.o_uuid and users.p_uuid=person_uuid.p_uuid order by name";

    $res=$db->Execute($q);
    
    while((!$res->EOF) && (!$res==NULL)){
        $user=$res->fields[0];
        $org=$res->fields[2];
        $user_name=$res->fields[3];
   ?>
    <tr>
        <td>
        <?php echo $org."->".$user_name?>
        </td>
<?php
$k=0;
        while($k<count($act_arr)){
 	$act_id=$act_arr[$k]["id"];
       	$perms=$perms.$user.":".$act_id.";";
	$name=$user.$act_id;
 	
	if (shn_acl_check_perms_action_group($user,$act_id)) {
	 	$allow=true;
}else{
                $allow=false;
            }
      	?><td><input type="checkbox" name="<?php echo $name?>" <?php if ($allow) echo "checked='checked'";?>" algin="right" select=1 </td>
<?php

       $k=$k+1;
    
        }
$res->MoveNext();
       
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>
<br />
<center>
<?php
$tmp=array('type'=>"hidden",'name'=>'perms','value'=>$perms); 
shn_form_add_component($tmp,$return=false,$default_val_req=false);
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Save');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
    //close the form
    shn_form_close(false);
?>
</div>
<?php	
}

/**
 * Generates a grid view form of user permissions
 * @access public
 * @return void
 */

function shn_acl_form_user_perms_grid($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
?>

<h3 align="center">Grid view of User Permissions</h3>
<div>
<center>
<a href="index.php?mod=admin&act=acl_existing_perms_tab&sel=or">Click here for Tabular view of User Permissions</a>
</center>
<br />
</div>
<div id="note">
Rows are Actions ,Columns are Users ,Intersection shows whether the action is permitted or not
</div>
<div id ="result">
    <table>
        <thead>
        <td>
<?php
    $act_arr=$acl->_shn_get_module_action_groups($module);
    $k=0;
     while($k<count($act_arr)){
       echo "<td>".$act_arr[$k]['name']."</td>";
       $k=$k+1;
    }
?>       
    </thead>
     <tbody>
<?php    
    $q = "select user_id,full_name,name,user_name from org_users,person_uuid,org_main,users where org_users.user_id=person_uuid.p_uuid and org_users.org_id=org_main.o_uuid and users.p_uuid=person_uuid.p_uuid order by name";

    $res=$db->Execute($q);

    while((!$res->EOF) && (!$res==NULL)){
        $user=$res->fields[0];
        $org=$res->fields[2];
        $user_name=$res->fields[3];
   ?>
    <tr>
        <td>
        <?php echo $org."->".$user_name?>
        </td>
<?php
$k=0;
        while($k<count($act_arr)){
 $act=$act_arr[$k]["id"];
       if (shn_acl_check_perms_action_group($user,$act)) {
	 $active="Yes";
		echo "<td><b><font color=#2E8B57>".$active."</font></b></td>";
}else{
                $active="No";
		echo "<td><b><font color=#FF0000>".$active."</font></b></td>";
            }
     
       $k=$k+1;
    
        }
$res->MoveNext();
       
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>

<?php
}

/**
 * Generates a table view form of user permissions
 * @access public
 * @return void
 */

function shn_acl_form_existing_perms_tabular($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
	
    ?>
<center><h2>Existing User Permissions</h2></center>
<!--<h3>User can be assigned to Multiple Roles</h3>-->
 
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=acl_default&sel='.$module,'id'=>'formset');
	shn_form_open($header,false);
?>
   <!-- </br>
        <hr>-->
            <div id ="result">
              <!--  <h2>User Permissions</h2>-->
                <table>
                    <thead>
                        <td>Organization</td>
                        <td>User Name</td>
	                    <td>User Description</td>
                        <td>Member of Roles</td>
                        <td>Permitted Actions</td>
	                    <td>Action Description</td>
                    </thead>
                    <tbody>
<?php 
  
$q = "select user_id,full_name,name,user_name from org_users,person_uuid,org_main,users where org_users.user_id=person_uuid.p_uuid and org_users.org_id=org_main.o_uuid and users.p_uuid=person_uuid.p_uuid order by name";

    $res=$db->Execute($q);
 
    $i=0;

    while((!$res->EOF) && (!$res==NULL)){
        $user=$res->fields[0];
        $user_name=$res->fields[3];
?>
    <tr>
        <td><b><?php echo $res->fields[2]?></b></td>
        <td><b><?php echo $res->fields[3]?></b></td>
        <td><b><?php echo $res->fields[1]?></b></td>
<?php
        $role_arr=$acl->_shn_get_roles_of_user($user);
        $act_arr=$acl->_shn_get_module_actions($module);
?>
        <td>
<?php
            $k=0;
            while($k<=count($role_arr)){
                echo $role_arr[$k]['name']."</br>";
                $k=$k+1;
            }
?>
        </td>
        <td>
        <td>
        </tr>
<?php
        $i=0;
        while($i<count($act_arr)){
            $act=$act_arr[$i]["value"];
            $act_desc=$act_arr[$i]["name"];
            if (shn_acl_check_perms_action($user,$act)) {
?>
    <tr>
    <td></td>
    <td></td>
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
    $submit= array('type'=>'submit', 'value'=>'Reload');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
}

/**
 * Generates a form to add roles for an user
 * @access public
 * @return void
 */

function shn_acl_form_user_add_roles($module,$error=false)
{
   
?>
<center><h2>Add User to Role</h2></center>
<h3>User can be assigned to Multiple Roles</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=acl_user_add_roles_cr&sel='.$module,'id'=>'formset');
	shn_form_open($header,false);
$user=shn_acl_form_users();
$acl_users = array();
array_push(
		$acl_users,
		$user
	  );
$roles=shn_acl_form_roles();
array_push(
		$acl_users,
		$roles
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

/**
 * Generates a form to add permissions for an user
 * @access public
 * @return void
 */

function shn_acl_form_user_add_perms($module,$error=false)
{
?>
<center><h2>User Permissions</h2></center>
<h3>Assign Permissions to Action Groups</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=acl_user_cr&sel='.$module,'id'=>'formset');
	shn_form_open($header,false);

$acl_users = array();

$user=shn_acl_form_users();
array_push(
		$acl_users,
		$user
	  );
$groups=shn_acl_form_action_groups($module);
array_push(
		$acl_users,
		$groups
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
