<?PHP

/*
*
* Sahana Admin & ACL section
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @author     Chamindra <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
/*
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl_form.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot']."/inc/lib_errors.inc";
    include_once "user.inc";
*/
    include_once $global['approot']."/inc/lib_validate.inc";

function shn_admin_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];

     // display the list of modules on the menu bar
    $module_list = shn_get_modules_with_admin();
?>
    <div id="modmenuwrap">
        <h2>Administration</h2>
            <ul id="modmenu">
                <li><a href="#">Module Config </a></li>
                    <ul id="modsubmenu">

<?php foreach ($module_list as $i) {  ?>

                        <li><a href="index.php?mod=<?=$i?>&act=adm_default"><?=$conf['mod_'.$i.'_name']?></a></li><?php } ?> 
                    </ul>
<!--
                <li><a href="#">Security </a></li>
                    <ul id="modsubmenu">
                        <li><a href="index.php?mod=admin&act=acl_default">Add an User</a></li>
                        <li><a href="index.php?mod=admin&act=acl_default">ChangePassword</a></li>
                        <li><a href="index.php?mod=admin&act=acl_default">Delete User</a></li>
                    </ul>
                <li><a href="#">ACL Config </a></li>
                    <ul id="modsubmenu">

<?php foreach ($module_list as $i) {  ?>

                        <li><a href="index.php?mod=admin&act=acl_default&sel=<?=$i?>"><?=$conf['mod_'.$i.'_name']?></a></li><?php } ?> 
                    </ul>
         -->
         </ul>
        </dd>
        </dt>
    </div> <!-- /modmenuwrap -->    
<?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
	
function shn_admin_view()
{ 
    global $global;
?>

        <p><b>You called the admin view </b></p>
        <p> on module </p>
<?php
        
}

function shn_admin_default()
{ ?>
        <p><b>Welcome to the Sahana admin page</b></p>
        <p> This is the default  of admin</p>

<?php
}

function shn_admin_modadmin() 
{
    global $global;

    include $global['approot']."/mod/".$global['module']."/admin.inc";
    
    // compose and call the relevant module function 
    $module_function = "shn_".$global['module']."_".$global['action'];
    if (!function_exists($module_function)) {
        $module_function="shn_".$module."_default";
    } 

    $module_function(); 
 

}


function shn_admin_acl_default()
{
    global $conf;
    $module=$_GET['sel'];    
?>

        <h2>Welcome to the Sahana ACL page</h2>
        <h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>

<?php
	_shn_admin_acl_sub_menu($module);
     shn_acl_form_existing_perms($module,false);
}

function _shn_admin_acl_sub_menu($module)
{

?>
<div id="submenu_v">
<a href="index.php?mod=admin&act=acl_default&sel=<?php echo $module?>">Existing Permissions</a>
<a href="index.php?mod=admin&act=acl_usr_role&sel=<?php echo $module?>">Add User to Role</a>
<a href="index.php?mod=admin&act=acl_role&sel=<?php echo $module?>">Role Permissions</a>
<a href="index.php?mod=admin&act=acl_user&sel=<?php echo $module?>">User Permissions</a>
<a href="index.php?mod=admin&act=acl_adv&sel=<?php echo $module?>">Advanced Permissions</a>
</div>
<br>
<?php
}



function shn_admin_acl_usr_role($module=NULL,$error=false)
{

if(is_null($module)){
$module=$_GET['sel'];   
}

global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php
    _shn_admin_acl_sub_menu($module);

    shn_acl_form_user_role($module,$error);
}

function shn_admin_acl_usr_role_cr()
{
    global $global;
$module=$_GET['sel'];  
//$acl=new SahanaACL(NULL);

 if (is_null($_POST{"users"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $user=$_POST{"users"};
    }

if (is_null($_POST{"roles"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $role=$_POST{"roles"};
    }
$i=0;
    while($i<count($user)){
	$j=0;
    	while($j<count($role)){
		$res=shn_acl_add_to_role($user[$i],$role[$j]);
		$j=$j+1;
	}
	$i=$i+1;
}
if ($res){
?>
<div id="save">
Users were succesfully added to Roles
</div>
<?php
}
shn_admin_acl_usr_role($module,false);
}

function shn_admin_acl_role()
{
     $module=$_GET['sel'];  
global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php
    _shn_admin_acl_sub_menu($module);
    shn_acl_form_role_perms($module,false);
}

function shn_admin_acl_role_cr()
{
    global $global;
    $module=$_GET['sel'];  

    if (is_null($_POST{"action_groups"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $action_group=$_POST{"action_groups"};
    }

if (is_null($_POST{"roles"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $role=$_POST{"roles"};
    }
$i=0;
    while($i<count($role)){
	$j=0;
    	while($j<count($action_group)){
            $res=shn_acl_add_perms_action_group_role($role[$i],$module,$action_group[$j]);
              
		$j=$j+1;
	}
	$i=$i+1;
}
if ($res){
?>
<div id="save">
Roles were succesfully given permission to action groups
</div>
<?php
}
shn_admin_acl_role($module,false);
}



function shn_admin_acl_user()
{
    $module=$_GET['sel']; 
global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php 
    _shn_admin_acl_sub_menu($module);
    shn_acl_form_user_perms($module,false);
}

function shn_admin_acl_user_cr()
{
    global $global;
    $module=$_GET['sel'];  

    if (is_null($_POST{"action_groups"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $action_group=$_POST{"action_groups"};
    }

if (is_null($_POST{"users"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $user=$_POST{"users"};
    }
$i=0;
    while($i<count($user)){
	$j=0;
    	while($j<count($action_group)){
            $res=shn_acl_add_perms_action_group_user($user[$i],$module,$action_group[$j]);
              
		$j=$j+1;
	}
	$i=$i+1;
}
if ($res){
?>
<div id="save">
Roles were succesfully given permission to action groups
</div>
<?php
}


shn_admin_acl_user($module,false);
}

function shn_admin_acl_adv()
{
     $module=$_GET['sel']; 
global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php 
    _shn_admin_acl_sub_menu($module);;
    shn_acl_form_advanced_perms($module,false);
}

function shn_admin_acl_adv_cr()
{
    global $global;
    $module=$_GET['sel'];  

    if (is_null($_POST{"action_groups"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $action_group=$_POST{"action_groups"};
    }

if (is_null($_POST{"users"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $user=$_POST{"users"};
    }
$i=0;
    while($i<count($user)){
	$j=0;
    	while($j<count($action_group)){
            $res=shn_acl_add_perms_action_group_user($user[$i],$module,$action_group[$j]);
              
		$j=$j+1;
	}
	$i=$i+1;
}
if ($res){
?>
<div id="save">
Roles were succesfully given permission to action groups
</div>
<?php
}
}

function shn_admin_add_user(){
    shn_admin_form_user_add(false);
}

function shn_admin_add_user_cr(){
   
   

   list($error,$user_name)=(shn_validate_user_name($_POST{"user_name"}))?array($error,$_POST{"user_name"}):array(true,NULL);
    
    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
    if (is_null($_POST{"re_password"})){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_INCOMPLETE);
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_WRONG);
    }
}
?>
