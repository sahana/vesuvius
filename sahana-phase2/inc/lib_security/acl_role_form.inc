<?php
/**
 * This library generates all the forms required to add,modify and remove
 * role ACL settings.
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
 * Generates a grid view form of role permissions
 * @access public
 * @return void
 */
function shn_acl_form_role_perms_grid($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
?>

<h3 align="center">Role Permissions</h3>
<div>

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
    $role_arr=$acl->_shn_get_roles();

    $j=0;
     while($j<count($role_arr)){
       $role=$role_arr[$j]['id'];
       
     ?>
    <tr>
        <td>
        <?php echo $role_arr[$j]['name']?>
        </td>
<?php
$k=0;
        while($k<count($act_arr)){
 $act=$act_arr[$k]["id"];
       if (shn_acl_check_role_perms_action_group($role,$act)) {
	 $active="Yes";
		echo "<td><b><font color=#2E8B57>".$active."</font></b></td>";
}else{
                $active="No";
		echo "<td><b><font color=#FF0000>".$active."</font></b></td>";
            }
     
       $k=$k+1;
    
        }
$j=$j+1;
       
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
 * Generates a form to edit permissions of a role
 * @access public
 * @return void
 */

function shn_acl_form_role_edit_perms($module,$error=false)
{
    global $global;
    $db=$global['db'];
    $acl=new SahanaACL(NULL);
?>

<h3 align="center">Add & Remove Role Permissions</h3>
<div>

<br />
</div>
<div id="note">
Rows are Action Groups ,Columns are Roles ,Intersection shows whether the action group is permitted or not
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>"index.php?mod=admin&act=acl_role_edit_perms_cr&sel=$module",'id'=>'formset');
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
    $role_arr=$acl->_shn_get_roles();

    $j=0;
     while($j<count($role_arr)){
       $role_id=$role_arr[$j]['id'];
       $role=$role_arr[$j]['value'];
     ?>
    <tr>
        <td>
        <?php echo $role_arr[$j]['name']?>
        </td>
<?php
$k=0;
        while($k<count($act_arr)){
        $act_id=$act_arr[$k]["id"];
	$act=$act_arr[$k]["value"];
       	$perms=trim($perms).trim($role_id).":".trim($act_id).";";
	$name=trim($role_id.$act_id);
       if (shn_acl_check_role_perms_action_group($role_id,$act_id)) {
	$allow=true;
}else{
                $allow=false;
            }
      	?><td><input type="checkbox" name="<?php echo $name?>" <?php if ($allow) echo "checked='checked'";?>" algin="right" select=1 </td>
<?php
       $k=$k+1;
    
        }
$j=$j+1;
       
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
}


?>
