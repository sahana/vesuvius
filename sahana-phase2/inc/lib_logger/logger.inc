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
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Mifan <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


// Sahana logging (auditing) engine.
// 20th Sep 2005
// by The A-Team :)

function shn_log_event()
{
     
     global $conf, $global;
     
     $entry['userid']= $_SESSION['userid']; 
     $entry['userlogid']=$_SESSION['userlogid'];
     $entry['action']=$global['action'];
     $entry['modulename']=$global['module'];

    echo $global['action'];
    echo $global['module'];

	 // switch to relavent log level based on sahana config file.
     switch($conf['loglevel']) {
	 	
        case 1 : // normal level auditing
    		shn_db_insert_array("core_actionlog_level1", $entry,true);
            break;
		
		case 2 : // security level auditing
    		$entry['data']=serialize($_POST);
            shn_db_insert_array("core_actionlog_level2", $entry, true);
            break;
		
		// case 3 : // debug level auditing
		 //   break;
		
		default :
	  } // end of level_catch
}

?>
