<?php
/** API of the Resquest Management System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ishan Liyanage <ishanul@gmail.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

/**
 * This function can be used to make requests
 * @param 
 * @access public
 */
global $global;
include_once $global['approot']."/inc/lib_uuid.inc";
function shn_rms_make_request($item,$amount,$priority,$unit){
		
	global $global;
	$db=$global['db'];
	$req_uuid = shn_create_uuid('r');
	$requester_uuid = shn_create_uuid('p');
    $status = 'open';
    $user_id = 'u-1';
    $q1="INSERT INTO rms_req_item (item_uuid,quantity,pri_uuid,req_uuid,unit) VALUES ('$item','$amount','$priority','$req_uuid','$unit')";
    $q2 = "INSERT INTO rms_request (req_uuid, reqstr_uuid, loc_uuid, status, user_id) " .
            "VALUES ('$req_uuid', '$requester_uuid', '', '$status', '$user_id')";
    $res1=$db->Execute($q1);
    $res2=$db->Execute($q2);
    if($res1==NULL || $res1==NULL)
    {
        return 'error';
    }
    else
    {
    	return 'success';
    }
		
}

/**
 * This function can be used to make new pledges
 * @param 
 * @access public
 */

function shn_rms_new_pledge($item,$amount,$unit){
	global $global;
	$db=$global['db'];
	$plg_uuid = shn_create_uuid('pl');
    $status = 'Not Delivered';
    $user_id = 'u-1';
    $donor_uuid = shn_create_uuid('p');
    $sql1 = "INSERT INTO rms_pledge (plg_uuid, donor_uuid, status, user_id) " .
            "VALUES ('$plg_uuid', '$donor_uuid', '$status', '$user_id')";
    
    $sql2 = "INSERT INTO rms_plg_item (item_uuid, quantity, plg_uuid, unit) " .
                "VALUES ('$item', '$amount', '$plg_uuid', '$unit')";
        
    $res1=$db->Execute($sql1);
    $res2=$db->Execute($sql2);
    if($res1==NULL || $res2==NULL)
    {
        return 'Error';
    }
    else
    {
    	return 'success';
    }
}

/**
 * This function can be used to get request list
 * @param 
 * @access public
 */

function shn_rms_request_list(){
    global $global;
	$db=$global['db'];
	$sql1="SELECT * FROM rms_req_item";
	$res = $db->Execute($sql1);
	$sql2="SELECT name from ct_catalogue WHERE ct_uuid='".$res->fields["item_uuid"]."'";
    $res2=$db->Execute($sql2);
    $request_list=array();
    while((!$res==NULL) && (!$res->EOF)) {
    	    $request_list[] = array('item' => $res2->fields["name"], 'quantity' => $res->fields["quantity"], 'priority' => $res->fields["pri_uuid"], 'req_id' => $res->fields["req_uuid"], 'unit' => $res->fields["unit"]);
    		$res->MoveNext();
    }
    return $request_list;
}
?>