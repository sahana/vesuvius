<?php
/**Library of the Social Network
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_sn_execute($sql){


	global $global;

	$db = $global['db'];

	$res = $db->Execute($sql);
	if ($res) {
		return $res;
	} else {
		return false;
	}
}

function _shn_sn_get_username($user_id = null){

	$sql = "SELECT user_name FROM users where p_uuid='$user_id'";
	$res = _shn_sn_execute($sql)->fields['user_name'];

	return $res;

}


function _shn_sn_chk_user_in_sn($id = null){

	$sql = "SELECT sn_mem_interests FROM sn_members WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['sn_mem_interests'];
	return $res;
}

function _shn_sn_get_stored_group($option = true){

	$sql = "SELECT group_id, group_name FROM sn_groups";
	$res = _shn_sn_execute($sql);
	$result = array();
	foreach ($res as $r) {
		$result[$r['group_id']] = $r['group_name'];
	}
	return $result;
}

function _shn_sn_get_stored_diseases($option = true){

	$sql = "SELECT dis_id, dis_name FROM dsm_diseases";
	$res = _shn_sn_execute($sql);
	$result = array();
	foreach ($res as $r) {
		$result[$r['dis_id']] = $r['dis_name'];
	}
	return $result;
}

function _shn_sn_get_stored_category($option = true){

	$sql = "SELECT category_id, category_name FROM sn_category";
	$res = _shn_sn_execute($sql);
	$result = array();
	foreach ($res as $r) {
		$result[$r['category_id']] = $r['category_name'];
	}
	return $result;
}

function _shn_sn_get_stored_groups($option = true){

    $sql = "SELECT group_id, group_name FROM sn_groups";
    $res = _shn_sn_execute($sql);
    $result = array();
    foreach ($res as $r) {
        $result[$r['group_id']] = $r['group_name'];
    }
    return $result;
}

function _shn_sn_get_stored_module_role($option = true){

    $sql = "SELECT role_id, role_name FROM sn_roles WHERE role_category='sn'";
    $res = _shn_sn_execute($sql);
    $result = array();
    foreach ($res as $r) {
        $result[$r['role_id']] = $r['role_name'];
    }
    return $result;
}

function _shn_sn_get_stored_forum_role($option = true){

	$sql = "SELECT role_id, role_name FROM sn_roles WHERE role_category='forum'";
	$res = _shn_sn_execute($sql);
	$result = array();
	foreach ($res as $r) {
		$result[$r['role_id']] = $r['role_name'];
	}
	return $result;
}

function _shn_sn_get_stored_group_role($option = true){

    $sql = "SELECT role_id, role_name FROM sn_roles WHERE role_category='group'";
    $res = _shn_sn_execute($sql);
    $result = array();
    foreach ($res as $r) {
        $result[$r['role_id']] = $r['role_name'];
    }
    return $result;
}

function _shn_sn_get_stored_forums($option = true){

    $sql = "SELECT forum_id, forum_name FROM sn_forums";
    $res = _shn_sn_execute($sql);
    $result = array();
    foreach ($res as $r) {
        $result[$r['forum_id']] = $r['forum_name'];
    }
    return $result;
}

/**
 * Returns the unread message count in the inbox folder.
 *
 * @return Integer
 */
function _shn_sn_get_unread_message_count(){
	global $global;
	$db = $global['db'];

	$query = "SELECT COUNT(*) AS c FROM sn_messages WHERE to_p_uuid=? AND status='UNREAD' AND folder='Inbox'";
	$res = $db->Execute($query,array($_SESSION['user_id']));
	$inbox_count = 0;
	if($res && $res->RecordCount()>0){
		$inbox_count = $res->fields[0];
	}

	return $inbox_count;
}

function _shn_sn_get_option_description($opt_code){
	global $global;
	$db = $global['db'];
	$query = "SELECT option_description FROM field_options WHERE option_code=?";
	$res = $db->Execute($query,array($opt_code));
	return $res->fields["option_description"];
}