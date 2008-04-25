<?php
/**
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  Sahana	
* @subpackage Messaging
* @version 	  $id$
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Action for store message form
 */
function shn_msg_create_store()
{
	
	$_SESSION['msg_head']=$_POST['msg_head'];
	$_SESSION['message']=$_POST['message'];
	$_SESSION['media_type']=$_POST['media_type'];
	
	
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_uuid.inc');
	
	$db = $global['db'];
	
	$m_uid = shn_create_uuid('msg');
	
	$query = "INSERT INTO msg_stored_messages (m_uuid,message_header,message_content,message_creation_user_id) " .
			" VALUES ('{$m_uid}','{$_SESSION['msg_head']}','{$_SESSION['message']}','{$_SESSION['user']}')";
	$db->Execute($query);
	
	//Enter message mapping to medium
	foreach ($_SESSION['media_type'] as $key=>$val){
		$query_map = "INSERT INTO msg_message_to_medium (m_uuid,opt_msg_message_medium) VALUES ('{$m_uid}','{$val}')";
		$db->Execute($query_map);
	}
	
	add_confirmation(_('Your message has been stored in the system'));
}


/**
 * Action for template  message form
 */
function shn_msg_create_tpl()
{
	
	$_SESSION['msg_head']=$_POST['msg_head'];
	$_SESSION['message']=$_POST['message'];
	$_SESSION['media_type']=$_POST['media_type'];
	
	
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_uuid.inc');
	
	$db = $global['db'];
	
	$m_uid = shn_create_uuid('msg');
	
	$query = "INSERT INTO msg_tpl_messages (m_uuid,message_header,message_content,message_creation_user_id) " .
			" VALUES ('{$m_uid}','{$_SESSION['msg_head']}','{$_SESSION['message']}','{$_SESSION['user']}')";
	$db->Execute($query);
	
	//Enter message mapping to medium
	foreach ($_SESSION['media_type'] as $key=>$val){
		$query_map = "INSERT INTO msg_message_to_medium (m_uuid,opt_msg_message_medium) VALUES ('{$m_uid}','{$val}')";
		$db->Execute($query_map);
	}
	
	add_confirmation(_('Your message has been stored in the system'));
}


/**
 * Send message main call
 * @todo add group information to the message strings
 */
function shn_msg_send_message(){
	global $global;
	include_once $global['approot']."/mod/msg/lib_msg.inc";
	
	$db = $global['db'];
	$message="";
	$email_array = array();
	$sms_array = array();
	$group_array = array();

	
	//Handle message
	if($_POST['stmsg']!=""){
		//Stored Message
		$sql = "SELECT message_content FROM msg_stored_messages WHERE m_uuid='{$_POST['stmsg']}'";
		$result = $db->Execute($sql);
		if(!$result->EOF){
			$message = $result->fields['message_content'];
		}
	}
	else{
		//Template or custom message
		$message = $_POST['message'];
	}
	
	//Handle contacts
	list($email_array,$sms_array) = shn_msg_get_categories_from_contact(_shn_msg_message_filter($_POST['to']));
	
	
	//Call library methods
	//Send text messages
	$status_sms = shn_msg_send_short_message($sms_array,$message);
	
	//Send email messages
	$status_email = shn_msg_send_email($email_array,$message);
	if($status_email){
		//print email status
		foreach($status_email as $key=>$value){
			echo $key."->".$value;
			if($value)
				add_confirmation(_('Sent mail to ').$key);
			else if(!$value)
				add_error(_('Send mail failure: The mail to ').$key._(' was not sent'));
		}
	}
	
}

/**
 * Filter message contacts into email/sms
 * @return mixed_array array of contacts
 */
function _shn_msg_message_filter($contacts)
{
	global $global;
	$contacts = trim($contacts);
	$contacts_array = split(',',$contacts);
	return $contacts_array;		
}
?>
