<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

global $global;
$req_id = $_GET['req_id'];
$stat = $_GET['stat'];
$user_id = $global['person_id'];
$stat = $_GET['stat'];

if (is_requester($req_id,$user_id))
{
    $sql = "UPDATE rms_request SET status='$stat' WHERE req_id=$req_id";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
        print "DB error : $msg";
    }
    
    print "<h4>The Request Status was successfully changed. " .
            "Please click <a href='index.php?mod=rms'>here to go back to the main page</a>" .
            ", or click <a href='index.php?mod=rms&act=vw_req&seq=detail&req_id=$req_id'>here to view the request</a></h4>";
}
else
{
    print "Sorry, you are not the owner of this request";
}
?>