<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @author		Sriganeshan<sri@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage  msg
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";
include_once $global['approot']."/inc/lib_uuid.inc";
include_once $global['approot']."/mod/msg/errors.inc";
require_once $global['approot']."/inc/lib_misc.inc";


/**
 * Messaging main menu
 */
function shn_msg_mainmenu()
{
    global $global;
    $module = $global['module'];

    shn_mod_menuopen("Messaging");
    shn_mod_menuitem("default", "Home", $module) ;
    shn_sub_mod_menuopen("Messages");
    shn_sub_mod_menuitem("customized_messaging", _("Customized Messaging"), $module);
    shn_sub_mod_menuitem("send_group",_("Group Messaging"),$module);
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen("Manage Groups");
    shn_sub_mod_menuitem("add_group",_("Add Group"),$module);
    shn_sub_mod_menuitem("edit_group",_("Edit Group"),$module);
    shn_sub_mod_menuitem("list_group",_("List Group"),$module);
    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuopen("CAP");
    shn_sub_mod_menuitem("cap_new", _("New Alert"), $module);
    shn_sub_mod_menuitem("cap_view", _("View Alert"), $module);
    shn_sub_mod_menuitem("cap_edit", _("Edit Alert"), $module);
    shn_sub_mod_menuitem("cap_upload", _("Upload CAP File"), $module);
    shn_sub_mod_menuclose();
    
    shn_mod_menuclose() ;
    
    include $global['approot']."/inc/handler_mainmenu.inc";
}

/**
 * The Default Messaging homepage
 */
function shn_msg_default()
{
    include_once ('handler_main.inc');
}

function shn_msg_cap_new()
{
    include_once ('handler_cap_new.inc');
}

function shn_msg_cap_view()
{
    include_once ('handler_cap_view.inc');
}

function shn_msg_cap_edit()
{
    include_once ('handler_cap_edit.inc');
}

function shn_msg_cap_upload()
{
    include_once ('handler_cap_upload.inc');
}

function shn_msg_cap_download()
{
    $file = $_POST['file'];
    header("Content-type: text/xml");
    header("Content-Disposition: attachment; filename=$file");
    $file_str = file_get_contents($file);
    print $file_str;
}


function shn_msg_add_group()
{
    include_once('message_forms.inc');
    _shn_msg_add_group();
    
}

function shn_msg_add_group_actions()
{
    include_once('message_forms.inc');
    $action=trim($_POST['action']);
    
    if($action=="clear")
    {
	$_POST['new_group_name']="";
	$_POST['email']="";
	$_POST['mobile_number']="";
	_shn_msg_add_group();
    }
    if($action=="save")
    {
	if(_shn_msg_validate_add_group())
	{
	    shn_msg_add_group();
	}
	else
	{
	    _shn_msg_add_group_actions();
	}
    }
}

function shn_msg_edit_group()
{
    include_once('message_forms.inc');
    _shn_msg_edit_group();
}

function shn_msg_view_edit_group_actions()
{
    global $global;
    $db=$global['db'];

    include_once('message_forms.inc');

    $action=trim($_POST['action']);
    $group_uuid=trim($_POST['group_uuid']);
    $group_name=trim($_POST['group_name']);
    $new_group_name=trim($_POST['new_group_name']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);

    
    if($action=="edit")
    {
	if(_shn_msg_validate_add_group($group_name))
	{
	    shn_msg_edit_group_item();
	}
	else
	{
	    $sql_edit="UPDATE messaging_group SET group_name='{$new_group_name}',address='{$email}',mobile='{$mobile_number}' WHERE group_uuid='$group_uuid';";
	    $msg_edit=$db->Execute($sql_edit);

	    $_POST['group_name']="";
            $_POST['email']="";
            $_POST['mobile_number']="";
            add_confirmation('Your changes have been saved successfully');
    	    shn_msg_edit_group();
	}
    }
    if($action=="delete")
    {
	$sql_delete="DELETE FROM messaging_group WHERE group_uuid='$group_uuid';";
	$msg_delete=$db->Execute($sql_delete);
	add_confirmation('The group you selected was successfully deleted from the database');
	shn_msg_edit_group();
    }
    if($action=="close")
    {
	shn_msg_edit_group();
    }
}

function shn_msg_edit_group_item()
{
    global $global;
    include_once('message_forms.inc');
    $group_uuid=trim($_REQUEST['group_uuid']);
    _shn_msg_edit_group_form($group_uuid);
}

function shn_msg_list_group()
{
    include_once('message_forms.inc');
    _shn_msg_list_group();
}

function shn_msg_send_group()
{
    include_once('message_forms.inc');
    _shn_msg_send_group();
}

function shn_msg_send_group_action()
{

   include_once('message_forms.inc');
    _shn_msg_send_group_action();
}

function shn_msg_customized_messaging()
{
    include_once('message_forms.inc');
    _shn_msg_customized_messaging();
}

function shn_msg_customized_messaging_actions()
{
    include_once('message_forms.inc');

    $action=$_POST['action'];
    
    if($action=="send")
    {
	if(_shn_msg_validate_customized_messaging())
	{
              
	     shn_msg_customized_messaging(); 
	}
	else
	{
            
	    _shn_msg_customized_messaging_actions();
            $_POST['message']="";
	    $_POST['email']="";
	    $_POST['mobile_number']="";
            shn_msg_customized_messaging();
	}
    }
    if($action=="clear")
    {
	$_POST['message']="";
	$_POST['email']="";
	$_POST['mobile_number']="";
	shn_msg_customized_messaging();
    }

}

?>