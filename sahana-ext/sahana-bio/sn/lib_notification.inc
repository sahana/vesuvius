<?php
/*
 * Social Networking Module Notification Library.
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue.
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage sn
 */

/**
 * Get all notifications for the given user
 *
 * @param String $p_uuid The user id
 * @param String $status Status of the notifications, defaults to NEW
 * @param boolean $order Whether to order the results (latest first) by date.
 * @return Array All notifications matching the criteria ordered by date (latest first) if order param is set
 */
function shn_sn_get_notifications_for_user($p_uuid,$status='NEW',$order=true){
	global $global;
	$db = $global['db'];
	//$db->debug = true;
	$query = "SELECT * FROM sn_notification WHERE target_p_uuid=? and notification_status=?";
	if($order){
		$query .= " ORDER BY added_date DESC";
	}
	$res = $db->Execute($query,array($p_uuid,strtoupper($status)));
	return $res->GetAssoc();
}

/**
 * Get all notifications for the given group
 *
 * @param String $group_id The group id
 * @param String $status Status of the notifications, defaults to NEW
 * @param boolean $order Whether to order the results (latest first) by date.
 * @return Array All notifications matching the criteria ordered by date (latest first) if order param is set
 */
function shn_sn_get_notifications_for_group($group_id,$status='NEW',$order=true){
	global $global;
	$db = $global['db'];

	$query = "SELECT * FROM sn_notification WHERE target_group_id=? and status=?";
	if($order){
		$query .= " ORDER BY added_date DESC";
	}
	$res = $db->Execute($query,array($group_id,strtoupper($status)));
	return $res->GetAssoc();
}
/**
 * Add a notification for a user in the SN module
 *
 * @param String $target_p_uuid The p_uuid of the user from the USERS table
 * @param String $subject Notification subject
 * @param String $message Notification message
 * @param String $target_action Target action to be executed when attending to this notification
 * @param String $target_module The module of the target action. Defaults to 'sn'
 * @param Array $target_funct_params An associative array of parameters to be passed as HTTP parameters for the target action
 * @return boolean Wheter the notification was successfully added
 */
function shn_sn_add_notifications_for_user($target_p_uuid,$subject='',$message='',$target_action='default',$target_module='sn',$target_funct_params=array(),$expiry_date=null,$related_to=null){
	global $global;
	$db = $global['db'];

	$query = "INSERT INTO sn_notification(notification_id,
	                                      target_p_uuid,
	                                      subject,
	                                      message,
	                                      target_action,
	                                      target_module,
	                                      target_func_params,
	                                      added_date,
	                                      expiry_date,
	                                      notification_status,
	                                      related_to) 
	                              VALUES(?,?,?,?,?,?,?,?,?,?,?)";
	$db->StartTrans();
	$added_date = date('Y-m-d H:i:s');
	$expiry_date = ($expiry_date==null)?null:$expiry_date;
	$s_tfparams = serialize($target_funct_params);
	$notificaiton_id = $db->GenID('sn_notification_seq');
	if($related_to==null){
		$related_to=$notificaiton_id;
	}
	$db->Execute($query,array($notificaiton_id,$target_p_uuid,$subject,$message,$target_action,$target_module,$s_tfparams,$added_date,$expiry_date,'NEW',$related_to));
	$failed = $db->HasFailedTrans();
	$db->CompleteTrans();
	return !$failed;
}

/**
 * Add a notification for a group of people in SN module
 *
 * @param String $target_group_id The group ID in SN_GROUPS table
 * @param String $subject Notification subject
 * @param String $message Notification message
 * @param String $target_action Target action to be executed when attending to this notification
 * @param String $target_module The module of the target action. Defaults to 'sn'
 * @param Array $target_funct_params An associative array of parameters to be passed as HTTP parameters for the target action
 * @return boolean Wheter the notification was successfully added
 */
function shn_sn_add_notifications_for_group($target_group_id,$subject,$message,$target_action,$target_module='sn',$target_funct_params,$related_to=null){
	global $global;
	$db = $global['db'];

	$query = "INSERT INTO sn_notification(notification_id,
	                                      target_group_id,
                                          subject,
                                          messaage,
                                          target_action,
                                          target_module,
                                          target_func_params,
                                          added_date,
                                          expiry_date,
                                          notification_status,
                                          related_to) 
                                  VALUES(?,?,?,?,?,?,?,?,?,?,?)";
	$db->StartTrans();
	$added_date = date('Y-m-d H:i:s');
	$expiry_date = ($expiry_date==null)?null:$expiry_date;
	$s_tfparams = serialize($target_funct_params);
	$notification_id = $db->GenID('sn_notification_seq');
	if($related_to==null){
		$related_to=$notificaiton_id;
	}
	$db->Execute($query,array($target_group_id,$subject,$message,$target_action,$target_module,$s_tfparams,$added_date,$expiry_date,'NEW',$related_to));
	$failed = $db->HasFailedTrans();
	$db->CompleteTrans();
	return $failed;

}

/**
 * Mark a notification after it is attended.
 *
 * @param String $notification_idj The notification id.
 * @return unknown
 */
function shn_sn_void_notification($notification_id){
	global $global;
	$db = $global['db'];
	$db->StartTrans();
	$related_no = $db->GetCol("SELECT related_to FROM sn_notification WHERE notification_id=?",array($notification_id));
	$query = "UPDATE sn_notification SET notification_status='ATTENDED' WHERE notification_id=?";
	$db->Execute($query,array($notification_id));
	if(count($related_no)>0){
		$query = "UPDATE sn_notification SET notificaiton_status='ATTENDED WHERE related_to=?";
		$db->Execute($query,array($related_no[0]));
	}
	$failed = $db->HasFailedTrans();
	$db->CompleteTrans();
	return !$failed;
}