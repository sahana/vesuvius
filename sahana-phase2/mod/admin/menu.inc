<?php
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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

function _shn_admin_mainmenu() 
{
    global $global;
    global $conf;
$module_list = shn_get_modules_with_admin();
?>
    <div id="modmenuwrap">
        <h2>Administration</h2>
            <ul id="modmenu">
               
                <li><a href="#">System Config </a></li>
                    <ul id="modsubmenu">
<li><a href="index.php?mod=admin&act=add_loc">Add Location</a></li> 
                   </ul>

               <li><a href="#">Module Config </a></li>
                    <ul id="modsubmenu">
<?php foreach ($module_list as $i) {  ?>
                        <li><a href="index.php?mod=<?=$i?>&act=adm_default"><?=$conf['mod_'.$i.'_name']?></a></li><?php } ?> 
                    </ul>

                
                <li><a href="#">Security Config </a></li>
                    <ul id="modsubmenu">
<li><a href="index.php?mod=admin&act=acl_system">User</a></li> 
<li><a href="index.php?mod=admin&act=acl_module">Modules</a></li> 
                   </ul>
         </ul>
        </dd>
        </dt>
    </div> <!-- /modmenuwrap -->    
<?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 


function _shn_admin_acl_module_menu(){
global $conf;
$module_list = shn_get_modules_with_admin();
$visible=shn_acl_is_base_installed();
if($visible==true){
?>
<div id="submenu_v">
<?php
foreach ($module_list as $i) {
    ?>
    <a href="index.php?mod=admin&act=acl_default&sel=<?php echo $i ?>"><?php echo $conf['mod_'.$i.'_name']?></a>
    <?php
    } ?> 
</div>
<br />
 <h2 align="center">Welcome to the Sahana ACL Module Configuration page</h2>
<?php
}else {
?>
<a href='index.php?mod=admin&act=acl_install'>ACL is not Installed! You need to Install ACL Base</a>  
<?php
}
}

function _shn_admin_acl_system_menu()
{


        $visible=shn_acl_is_base_installed();

    $acl=shn_acl_get_state();
?>
<div id="submenu_v">
<?php

if($visible==true){
if ($acl==true){
	?>
    <a href="index.php?mod=admin&act=acl_state&do=disable"><b>D</b>isable ACL</a>
<?php
}else {
    ?>
	<a href="index.php?mod=admin&act=acl_state&do=enable"><b>E</b>nable ACL</a>
<?php
}
?>
<a href="index.php?mod=admin&act=acl_install"><b>A</b>CL Base Install</a>
<a href="index.php?mod=admin&act=acl_user&sel=admin"><b>U</b>sers</a>
<a href="index.php?mod=admin&act=acl_role&sel=admin"><b>R</b>oles</a>
</div>
<br>
 <h2 align="center">Welcome to the Sahana ACL System Configuration page</h2>
<?php
}else {
?>
<a href="index.php?mod=admin&act=acl_install"><b>A</b>CL Base Install</a>
<?php
}
}

function _shn_admin_acl_module_sub_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=<?php echo $module?>&act=adm_acl_install"><b>Install Default ACL</b></a>
<a href="index.php?mod=admin&act=acl_user_perms&sel=<?php echo $module?>">User  Permissions</a>
<a href="index.php?mod=admin&act=acl_role&sel=<?php echo $module?>">Role Permissions</a>
<a href="index.php?mod=admin&act=acl_action&sel=<?php echo $module?>">Add & Remove Actions</a>
<a href="index.php?mod=admin&act=acl_action_group&sel=<?php echo $module?>">Action Groups</a>
</div>
<br />
<?php
}

function _shn_admin_acl_user_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=admin&act=add_user">Add User</a>
<a href="index.php?mod=admin&act=del_user">Remove User</a>
<?php 
if($_SESSION['logged_in']==true){
?>
<a href="index.php?mod=admin&act=ch_pwd">Change Password</a>
<?php
}
?>
<a href="index.php?mod=admin&act=acl_user_edit_roles&sel=<?php echo $module?>">Edit Roles of an User</a>
<a href="index.php?mod=admin&act=acl_user_add_roles&sel=<?php echo $module?>">Add Users to Role</a>
</div>
<br>
<?php
}

function _shn_admin_acl_role_menu($module)
{
?>
<div id="submenu_v">
<?php
if($module=='admin'){
?>
<a href="index.php?mod=admin&act=add_role">Add Role</a>
<a href="index.php?mod=admin&act=del_role">Remove Role</a>
<?php
}else {
?>
<a href="index.php?mod=admin&act=acl_role_perms&sel=<?php echo $module?>">Existing Role Permissions</a>
<a href="index.php?mod=admin&act=acl_role_edit_perms&sel=<?php echo $module?>">Add & Remove Role Permissions</a>
<?php
}
?>
</div>
<br>
<?php
}

function _shn_admin_acl_action_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=admin&act=acl_role_default&sel=<?php echo $module?>">Add Action</a>
<a href="index.php?mod=admin&act=acl_user_edit_perms&sel=<?php echo $module?>">Remove Action</a>
</div>
<br>
<?php
}

function _shn_admin_acl_action_group_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=admin&act=acl_role_default&sel=<?php echo $module?>">Add Action Group</a>
<a href="index.php?mod=admin&act=acl_user_edit_perms&sel=<?php echo $module?>">Remove Action Action Group</a>
</div>
<br>
<?php
}

?>
