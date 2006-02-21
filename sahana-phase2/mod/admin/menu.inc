<?php
/**
 *Sahana Admin & ACL section
 *PHP version 4 and 5
 *LICENSE: This source file is subject to LGPL license that is available through
 *the world-wide-web at the following URI: http://www.gnu.org/copyleft/lesser.
 *html
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
        <h2><?=_("Administration")?></h2>
            <ul id="modmenu">
                <li><a href="#"><?=_("System Config")?> </a></li>
                    <ul id="modsubmenu">
                    <li>
                        <a href="index.php?mod=admin&act=add_loc"><?=_("Add Location")?></a>
                    </li>
                    </ul>
                    <li><a href="#"><?=_("Localization")?></a></li>
                    <ul id="modsubmenu">
                    	<li>
                            <a href="index.php?mod=admin&amp;act=lc_set"><?=_("Set Locale")?></a>
                        </li>
                        <li>
                            <a href="index.php?mod=admin&amp;act=lc_db"><?=_("Database L10N")?></a>
                        </li>
						<li>
                            <a href="index.php?mod=admin&amp;act=lc_trns"><?=_("Language Translation")?></a>
                        </li>
                    </ul>

               <li><a href="#"><?=_("Module Config")?> </a></li>
                    <ul id="modsubmenu">
<?php foreach ($module_list as $i) {  ?>
                        <li><a href="index.php?mod=<?=$i?>&act=adm_default"><?=$conf['mod_'.$i.'_name']?></a></li><?php } ?>
                    </ul>


                <li><a href="#"><?=_("Security Config")?> </a></li>
                    <ul id="modsubmenu">
<li><a href="index.php?mod=admin&act=acl_system"><?=_("System &amp; User")?></a></li>
<li><a href="index.php?mod=admin&act=acl_module"><?=_("Modules")?></a></li>
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
	global $global;
	include_once $global['approot']."inc/lib_security/acl_module_form.inc";
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
 <h2 align="center"><?=_("Welcome to the Sahana ACL Module Configuration page")?></h2>
<br />
 <h2 align="center"><?=_("Current Status (Installed/Enabled)")?></h2>
 <br />
<?php
	shn_acl_module_status($module_list);
}else {
?>
<a href='index.php?mod=admin&act=acl_install'><?=_("ACL is not Installed! You need to Install ACL Base")?></a>
<?php
}
}

function _shn_admin_acl_system_menu()
{
    $visible=shn_acl_is_base_installed();
 ?>
<div id="submenu_v">
<?php

if($visible==true){
?>
<a href="index.php?mod=admin&act=acl_install"><?=_("<strong>A</strong>CL Base Install")?></a>
<a href="index.php?mod=admin&act=acl_user&sel=admin"><?=_("<strong>U</strong>sers")?></a>
<a href="index.php?mod=admin&act=acl_role&sel=admin"><?=_("<strong>R</strong>oles")?></a>
</div>
<br>
<!--<h2 align="center"><?=_("Welcome to the Sahana ACL System Configuration page")?></h2>-->
<?php
} else {
?>
<a href="index.php?mod=admin&act=acl_install"><?=_("<strong>A</strong>CL Base Install")?></a>
<?php
}
}

function _shn_admin_acl_module_sub_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=<?php echo $module?>&act=adm_acl_install"><strong><?=_("Install Default ACL")?></strong></a>
<a href="index.php?mod=admin&act=acl_user_perms&sel=<?php echo $module?>"><?=_("User  Permissions")?></a>
<a href="index.php?mod=admin&act=acl_role&sel=<?php echo $module?>"><?=_("Role Permissions")?></a>
<a href="index.php?mod=admin&act=acl_action&sel=<?php echo $module?>"><?=_("Add &amp; Remove Actions")?></a>
<a href="index.php?mod=admin&act=acl_action_group&sel=<?php echo $module?>"><?=_("Action Groups")?></a>
</div>
<br />
<?php
}

function _shn_admin_acl_user_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=admin&act=add_user"><?=_("Add User")?></a>
<a href="index.php?mod=admin&act=del_user"><?=_("Remove User")?></a>
<?php
if($_SESSION['logged_in']==true) {
?>
<a href="index.php?mod=admin&act=ch_pwd"><?=_("Change Password")?></a>
<?php
}
?>
<a href="index.php?mod=admin&act=acl_user_edit_roles&sel=<?php echo $module?>"><?=_("Edit Roles of an User")?></a>
<a href="index.php?mod=admin&act=acl_user_add_roles&sel=<?php echo $module?>"><?=_("Add Users to Role")?></a>
</div>
<br>
<?php
}

function _shn_admin_acl_role_menu($module)
{
?>
<div id="submenu_v">
<?php
if($module=='admin') {
?>
<a href="index.php?mod=admin&act=add_role"><?=_("Add Role")?></a>
<a href="index.php?mod=admin&act=del_role"><?=_("Remove Role")?></a>
<?php
} else {
?>
<a href="index.php?mod=admin&act=acl_role_perms&sel=<?php echo $module?>"><?=_("Existing Role Permissions")?></a>
<a href="index.php?mod=admin&act=acl_role_edit_perms&sel=<?php echo $module?>"><?=_("Add &amp; Remove Role Permissions")?></a>
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
<a href="index.php?mod=admin&act=acl_role_default&sel=<?php echo $module?>"><?=_("Add Action")?></a>
<a href="index.php?mod=admin&act=acl_user_edit_perms&sel=<?php echo $module?>"><?=_("Remove Action")?></a>
</div>
<br>
<?php
}

function _shn_admin_acl_action_group_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=admin&act=acl_role_default&sel=<?php echo $module?>"><?=_("Add Action Group")?></a>
<a href="index.php?mod=admin&act=acl_user_edit_perms&sel=<?php echo $module?>"><?=_("Remove Action Action Group")?></a>
</div>
<br>
<?php
}
?>
