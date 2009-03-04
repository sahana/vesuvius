<?php
/**
 * Social Network Administrative Section Home Page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    shana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


function shn_sn_datacreate(){
	global $global;
	$db = $global['db'];
	
	$tres = $db->Execute("SELECT MAX(group_id) FROM sys_user_groups");
	$next_gid = ($tres->fields[0]+1);
	
	/* 
 * Create the User Role for the Module
 */
    $db->Execute("INSERT INTO sys_user_groups VALUES ( '$next_gid', 'Social Networking User')");
    
    shn_acl_refresh('sn');
	
	$query = "SELECT act_id FROM sys_actions WHERE module='sn'";
	$res = $db->GetCol($query);
	$query2 = $db->Prepare("INSERT INTO sys_group_to_action (act_id,group_id) VALUES (?,?)");
	
	foreach($res as $v){
		$db->Execute($query2,array($next_gid,$v));
	}
}