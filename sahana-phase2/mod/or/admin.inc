<?php
/*
*
* Sahana HTML form handler
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
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl_form.inc';
	include_once $global['approot'].'inc/lib_security/acl.inc';

function _shn_or_acl_sub_menu()
{
?>
<div id="submenu_v">
<a href="index.php?mod=or&act=adm_default">Add User to Role</a>
<a href="index.php?mod=or&act=adm_acl_role">Role Permissions</a>
<a href="index.php?mod=or&act=adm_acl_user">User Permissions</a>
<a href="index.php?mod=or&act=adm_acl_adv">Advanced Permissions</a>
</div>
<br>
<?php
}

function shn_or_adm_default()
{
    _shn_or_acl_sub_menu();
    shn_acl_form_user_role(false);
}

function shn_or_adm_acl_role()
{
    _shn_or_acl_sub_menu();
    shn_acl_form_role_perms("or",false);
}

function shn_or_adm_acl_user()
{
    _shn_or_acl_sub_menu();
    shn_acl_form_user_perms("or",false);
}

function shn_or_adm_acl_adv()
{
    _shn_or_acl_sub_menu();
    shn_acl_form_advanced_perms("or",false);
}

?>

