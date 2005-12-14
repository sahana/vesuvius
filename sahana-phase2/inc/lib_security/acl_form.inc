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
include_once "acl_form_lib.inc";


function shn_acl_form_user_add($error=false)
{


?>
<center><h2>Add an User</h2></center>
<h3>Fields marked with * are required (entry is compulsory)</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=add_user_cr','id'=>'formset');
	shn_form_open($header,false);
$org=shn_user_orgs();
$or_arr=array();
array_push(
	$or_arr,
	$org
	);
shn_form_add_component_list($or_arr,$section=true,$legend='Add a User for the Organization',$return=false,$default_val_req=false);

$login_info = array(    
			array('desc'=>_("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1),
                    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    shn_form_add_component_list($login_info,$section=true,$legend='Create an Account for Login',$return=false,$default_val_req=false);
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
?>				     
</div>
<?php
    // end of form

    
} 

function shn_acl_form_ch_pwd($error=false)
{


?>
<center><h2>Change Password</h2></center>
<h3>Fields marked with * are required (entry is compulsory)</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=ch_pwd_cr','id'=>'formset');
	shn_form_open($header,false);
$login_info = array(    
			
                //    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
array('desc'=>_("* Old Password: "),'type'=>"password",'size'=>20,'name'=>'old_password','br'=>1),
                    array('desc'=>_("* New Password: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("* Confirm New Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    shn_form_add_component_list($login_info,$section=true,$legend='Create an Account for Login',$return=false,$default_val_req=false);
$user_id=$_SESSION["user_id"];
$user=array('type'=>"hidden",'name'=>'user','value'=>$user_id); 
shn_form_add_component($user,$return=false,$default_val_req=false);
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
?>				     
</div>
<?php
    // end of form

    
} 


function shn_acl_form_existing_perms_grid($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
?>

<h1 align="center">Grid view of User Permissions</h1>
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
    $act_arr=$acl->_shn_get_module_actions($module);
    $k=0;
     while($k<count($act_arr)){
       echo "<td>".$act_arr[$k]['value']."</td>";
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
        $user_name=$res->fields[3];
   ?>
    <tr>
        <td>
        <?php echo $user_name?>
        </td>
<?php
$k=0;
        while($k<count($act_arr)){
 $act=$act_arr[$k]["value"];
       if (shn_acl_check_perms_action($user,$act)) {
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

function shn_acl_form_user_role($module,$error=false)
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
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=acl_usr_role_cr&sel='.$module,'id'=>'formset');
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


function shn_acl_form_role_perms($module,$error=false)
{
?>
<center><h2>Role Permissions</h2></center>
<h3>Assign Permissions to Action Groups</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=acl_role_cr&sel='.$module,'id'=>'formset');
	shn_form_open($header,false);


$acl_users = array();

$roles=shn_acl_form_roles();
array_push(
		$acl_users,
		$roles
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


function shn_acl_form_user_perms($module,$error=false)
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
    $header=array('method'=>'POST','action'=>'index.php?mod=admin&act=acl_adv_cr&sel='.$module,'id'=>'formset');
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
