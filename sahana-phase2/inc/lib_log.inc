<?php
/**
* Sahana logging and cronology library
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage logging 
* @author     Chamindra de Silva <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


/**
 * shn_log_event 
 * 
 * @param string UUID 
 * @param string action
 * @param string message
 * @param string details
 * @return void
 */
function shn_log_event($UUID,$action,$message,$details=null)
{
 
    global $conf, $global;

    include_once($global['approot'].'inc/lib_uuid.inc');

    $datetime = date("Y-m-d H:i:s");

    $sql['user_uuid'] = 'sdsd'; //"$_SESSION['userid']"; 
    //$userlogid=$_SESSION['userlogid'];
    $sql['module'] = $global['module'];
    $sql['log_uuid'] = shn_create_uuid('log');
    $sql['opt_cron_type'] = 'cron';
    $sql['pgoc_uuid'] = $UUID;
    $sql['comments'] = $message;
    $sql['action'] = $action;
    $sql['details'] = $details;
    $sql['event_date'] = $datetime;

    shn_db_insert($sql,'chronology'); 
}
