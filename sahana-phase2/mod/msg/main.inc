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
* ----------
* HISTORY	
* 	@desc		The original version of this file was created by:	
* 	@author		Sudheera R. Fernando <sudheera@opensource.lk>
* 	@author		Sriganeshan<sri@opensource.lk>
* ----------
* @author		Mifan Careem <mifan@respere.com>
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage   msg
* @tutorial
* @version		$Id: main.inc,v 1.33 2009-08-22 17:17:22 ravithb Exp $
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";
include_once $global['approot']."/inc/lib_uuid.inc";
include_once $global['approot']."/mod/msg/errors.inc";
include_once($global['approot'].'/mod/msg/handler_contacts.inc');
include_once($global['approot'].'/mod/msg/lib_group.inc');
include_once($global['approot'].'/mod/msg/lib_contact.inc');
include_once($global['approot'].'/mod/msg/lib_survey.inc');
require_once $global['approot']."/inc/lib_misc.inc";

//Additional form actions are here:
include_once $global['approot']."/mod/msg/form_actions.inc";

include_once 'lib_msg_rss.inc';



/**
 * Messaging main menu
 * @author Sudheera <sudheera@opensource.lk>
 */
function shn_msg_mainmenu()
{
    global $global;
    global $conf;
    $module = $global['module'];

    shn_mod_menuopen($conf['mod_msg_name']);
    shn_mod_menuitem("default", "Home", $module) ;
    
    shn_sub_mod_menuopen("Consoles");
    shn_sub_mod_menuitem("send_console",_("Send Message Console"));
//     shn_sub_mod_menuitem("customized_messaging", _("Quick Messaging"), $module);
//     shn_sub_mod_menuitem("send_group",_("Quick Group Messaging"),$module);
    shn_sub_mod_menuitem("receive_console",_("Receive Message Console"));
    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuopen("Manage Contacts");
//     shn_sub_mod_menuitem("contacts",_("Contacts"),$module);
    shn_sub_mod_menuitem("contact_individual",_("Add Contact"),$module);
    //shn_sub_mod_menuitem("edit_contact_individual",_("Edit Contact"),$module);
    shn_sub_mod_menuitem("contact_group",_("Contact List"),$module);
    shn_sub_mod_menuitem("add_contact_group",_("Add Group"),$module);
    shn_sub_mod_menuitem("add_group",_("Add Adhoc Group"),$module);
    shn_sub_mod_menuitem("edit_group",_("Edit Adhoc Group"),$module);
    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuopen("Messaging Reports");
    shn_sub_mod_menuitem("sent_rpt",_("Sent Messages"),$module);
    shn_sub_mod_menuitem("rcvd_rpt",_("Received Messages"),$module);
//     shn_sub_mod_menuitem("contact_rpt",_("Contact List"),$module);
//     shn_sub_mod_menuitem("list_group",_("List Adhoc Group"),$module);
    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuopen("Survey Messages");
    shn_sub_mod_menuitem("send_survey", _("Send Survey Message"), $module);
    shn_sub_mod_menuitem("survey_rpt",_("Survey Reports"),$module);
    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuopen("Stored Messages");
    shn_sub_mod_menuitem("add_store_msg",_("Create Stored Message"),$module);
    shn_sub_mod_menuitem("add_temp_msg",_("Create Template Message"),$module);
    shn_sub_mod_menuclose();
    
    shn_sub_mod_menuopen("Common Alerting Protocol");
    shn_sub_mod_menuitem("cap_new", _("New Alert"), $module);
    shn_sub_mod_menuitem("cap_view", _("View Alert"), $module);
    shn_sub_mod_menuitem("cap_edit", _("Edit Alert"), $module);
    shn_sub_mod_menuitem("cap_upload", _("Upload CAP File"), $module);
    shn_sub_mod_menuclose();
      
/*
 *  Rearranged below menu items to fall in above categories  
    shn_sub_mod_menuopen("--Messages");
    shn_sub_mod_menuitem("customized_messaging", _("Customized Messaging"), $module);
    shn_sub_mod_menuitem("send_group",_("Group Messaging"),$module);
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen("--Manage Groups");
    shn_sub_mod_menuitem("add_group",_("Add Group"),$module);
    shn_sub_mod_menuitem("edit_group",_("Edit Group"),$module);
    shn_sub_mod_menuitem("list_group",_("List Group"),$module);
    shn_sub_mod_menuclose();
*/    

    
    shn_mod_menuclose() ;
    
    include $global['approot']."/inc/handler_mainmenu.inc";
}


/*
@author		Pradeeper <pradeeper@respere.com>
@function	catch all form submits and reroute to relavent functions to process
*/
function shn_msg_contact_submit()
{
$target=$_POST['target'];
	$person_id=$_POST['person_id'];
	$group_id=$_POST['group_id'];
	$option=$_POST['option'];
	
	switch ($target){
		
		case add_contact:
			// catch the post data and store it in the DB
			_shn_msg_add_contact();
			break;
			
		case edit_contact:
			// pass edit values to the db 
			_shn_msg_add_contact($person_id);			
			break;
		
		case delete_contact:
			// delete the contact from the db
			_shn_msg_delete_contact($person_id,$option);
			break;
			
		case delete_group:
			// delete the group from the db
			shn_msg_delete_group($group_id);
			break;	
			
		case list_contact:
			print "list contact";
			break;
			
		case send_survey:
			//print "send survey";
			_shn_msg_send_survey_submistion();
			break;	
			
		case add_contact_group:
			_shn_msg_add_contact_group();
			break;
			
		case update_contact_group:
			$group_name=$_POST['grp_name'];
			$description=$_POST['desc'];
			$type=$_POST['opt_msg_group_category'];
			
			//check whether cacel has been pressed
			if(isset($_POST['cancel'])){
				shn_msg_select_group($group_id);
			} else {
				// submit the data to store in the db
				shn_msg_update_group($store="yes",$group_id, $group_name, $description, $type);
			}
			
			break;		
	}
}



/**
 * The Default Messaging homepage
 */
function shn_msg_default()
{
    include_once ('handler_main.inc');
}

/**
 * This function print send console
 *
 * @author		Pradeeper <pradeeper@respere.com>
 * @function	Send surveys	
 */
function shn_msg_send_survey()
{
	shn_msg_send_survey_form();
}


/**
 * This function print survey report
 *
 * @author		Pradeeper <pradeeper@respere.com>
 * @function	Send surveys	
 */
function shn_msg_survey_rpt()
{
	_shn_msg_survey_reports();
}


/**
 * This function print send console
 *
 * @author J P Fonseka <hevayo@gmail.com>
 * @access public
 * @return void
 */
function shn_msg_send_console()
{
    include_once ('handler_send_console.inc');
}

/**
 * This function print receive console
 *
 * @author J P Fonseka <hevayo@gmail.com>
 * @access public
 * @return void
 */
function shn_msg_receive_console()
{
    include_once ('handler_receive_console.inc');
}

/**
 * This function print receive console
 *
 * @author J P Fonseka <hevayo@gmail.com>
 * @access public
 * @return void
 */
function shn_text_msg_receive_popup()
{
    include_once ('lib_receive_console.inc');
    _shn_msg_popup_page();
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

function shn_text_msg_cap_download()
{
    $file = $_REQUEST['file'];
    switch($_REQUEST['type']){
        case 'messages':
        $type = 'messages';
        break;
        case 'templates':
        $type = 'templates';
    }

    header("Content-type: text/xml");
    header("Content-Disposition: attachment; filename=$file");
    $MSG_DIR = '../res/msg/cap/';
    $file = $MSG_DIR.$type.'/'.$file;
    $file_str = file_get_contents($file);
    print $file_str;
}


/*
@author		Pradeeper <pradeeper@respere.com>
@function	This function will add contact group/s to the database
*/
function shn_msg_add_contact_group()
{
	global $global;
    $module = $global['module'];
	include_once($global['approot'].'/mod/msg/handler_contacts.inc');
	shn_msg_contact_add_group();
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

function shn_msg_contact_individual()
{
	global $global;
    $module = $global['module'];
	
    //shn_msg_contact_add_individual();
    shn_msg_form_add_contact();
}

function shn_msg_contacts(){
    echo "<h2>"._('Contacts')."</h2>";
    shn_form_fopen('contacts','',array('req_message'=>false));
    shn_form_fclose();
}



/*
@author		Pradeeper <pradeeper@respere.com>
@function	this will lead to list all the groups
*/
function shn_msg_contact_group()
{
	global $global;
    $module = $global['module'];
	include_once($global['approot'].'/mod/msg/handler_contacts.inc');
	
	print "<h2>Contact Group List</h2>";
	shn_msg_list_groups();
	//shn_msg_list_all_groups();
}

/*
@author		Pradeeper <pradeeper@respere.com>
@function	this will shows the internals of the selected group
*/
function shn_msg_select_group($tmp_id)
{
	$id=$_GET['id'];
	
	if(!isset($id)){
		$id=$tmp_id;
	}
	
	print "<h2>Group Details</h2>";
	shn_msg_view_group($id);
	
	// display 'add','update' and 'delete' links
	echo "&nbsp;&nbsp;&nbsp;";
	echo "<a href='index.php?mod=msg&act=form_add_contact&id=$id'>Add</a>";
	echo "&nbsp;&nbsp;&nbsp;";
	echo "<a href='index.php?mod=msg&act=update_group&id=$id'>Update</a>";
	echo "&nbsp;&nbsp;&nbsp;";
	echo "<a href='index.php?mod=msg&act=delete_person_group&id=$id&type=group'>Delete</a>";
	echo "<br>";
	
	// for "back" button
	shn_form_fopen("index.php?mod=msg&act=contact_group",null,array('req_message'=>false));
		shn_form_submit("Back", $submit_opts = null);
	shn_form_fclose();
}

/*
@author		Pradeeper <pradeeper@respere.com>
@function	this will select a person from a selected group
*/
function shn_msg_select_person()
{
	$id=$_GET['id'];
	$grp_id=$_GET['grpid'];
	print "<h2>Member Information</h2>";
	
	// display 'update' and 'delete' links
	shn_msg_view_person($id);
		echo "&nbsp;&nbsp;&nbsp;";
		echo "<a href='index.php?mod=msg&act=edit_contact_individual&id=$id'>Update</a>";
		echo "&nbsp;&nbsp;&nbsp;";
		echo "<a href='index.php?mod=msg&act=delete_person&id=$id''>Delete</a>";
		echo "<br>";
		
	//for "back" button
	shn_form_fopen("index.php?mod=msg&act=select_group&id=$grp_id",null,array('req_message'=>false));
		shn_form_submit("Back", $submit_opts = null);
	shn_form_fclose();	
}


/*
@author		Pradeeper <pradeeper@respere.com>
@function	this will delete a person or a group
*/
function shn_msg_delete_person_group()
{
	$id=$_GET['id'];
	$type=$_GET['type'];
	
	
	
	if($type=="group"){
		$tmp="Group";	
	} else {
		$tmp="Member";
	}
	// title
	print "<h2>$tmp Delete</h2>";
	
	// display the detail of a person or group
	if($tmp=="Group"){
		shn_msg_view_group($id);	
	} else {
		shn_msg_view_person($id);
	}
	
	// yes/no 
	shn_form_fopen("contact_submit", null,array('req_message'=>false));
		shn_form_fsopen("");
			if($type=="group"){
				shn_form_hidden(array("target"=>"delete_group","group_id"=>"$id"));
			} else {
				shn_form_hidden(array("target"=>"delete_contact","person_id"=>"$id"));
			}
			shn_form_radio(array("yes"=>"Yes","no"=>"No"),"Are you sure you want to delete : ",'option','');
		shn_form_fsclose();
		shn_form_submit("Submit",$submit_opts = null);
	shn_form_fclose();	
	
}


function shn_msg_add_store_msg()
{
	global $global;
    $module = $global['module'];
	include_once($global['approot'].'/mod/msg/handler_stored_message.inc');
    shn_msg_create_stored_message_form();
}

function shn_msg_sent_rpt()
{
	global $global;
	include_once($global['approot'].'/mod/msg/msg_reports.inc');
	shn_msg_basic_sent_report();
}

function shn_msg_rcvd_rpt()
{
	global $global;
	include_once($global['approot'].'/mod/msg/msg_reports.inc');
	shn_msg_basic_rcvd_report();
}

function shn_msg_add_temp_msg()
{
	global $global;
    $module = $global['module'];
	include_once($global['approot'].'/mod/msg/handler_tpl_message.inc');
    shn_msg_create_template_message_form();
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

/*
@author		Pradeeper <pradeeper@respere.com>
@function	Allow edit individual information
*/
function shn_msg_edit_contact_individual()
{
	//print "<h2>Edit Contact</h2>";
	//print "<p>Please select a group from the list</p>";
	//shn_msg_list_groups();// list all the groups that are in the db
	$id=$_GET['id'];
	shn_msg_form_edit_contact($id);
}


function shn_text_msg_receive_message(){
    include_once "lib_msg.inc";
    shn_msg_receive_short_message();
}
