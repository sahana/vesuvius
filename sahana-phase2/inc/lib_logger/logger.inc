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

//include(actions.inc);

/**
 * shn_log_event 
 * 
 * @param mixed $message 
 * @access public
 * @return void
 */
function shn_log_event($message)
{
     
     global $conf, $global;
		 
		 $logdate= date("jS F Y");
		 $logtime= date("G:i:s");
		
     $entry['userid']= $_SESSION['userid']; 
     $entry['userlogid']=$_SESSION['userlogid'];
     $entry['action']=$global['action'];
     $entry['modulename']=$global['module'];


	 	 // switch to relevent log level based on sahana config file.
     switch($conf['loglevel']) {
	 	
        case 1 : // normal level auditing
    				_shn_db_insert_array($entry['userid'],$entry['userlogid'],$message,$conf['loglevel'],$logdate,$logtime,$entry['modulename']);
            break;
		
				case 2 : // security level auditing
    				_shn_db_insert_array($entry['userid'],$entry['userlogid'],$message,$conf['loglevel'],$logdate,$logtime,$entry['modulename']);
            break;
						
		
				default :
						break;
	  } // end of level_catch
}

/**
 * insert log entry into database
 * connection is already open
 * values entered via adodb
 * 
 * @param mixed $userid 
 * @param mixed $userlogid 
 * @param mixed $message_text 
 * @param mixed $loglevel 
 * @param mixed $date 
 * @param mixed $time 
 * @param mixed $module 
 * @access protected
 * @return void
 */
function _shn_db_insert_array($userid,$userlogid,$message_text,$loglevel,$date,$time,$module){
		global $conf, $global;
		$table='cre_actionlog';
		$id=$global['db']->GenId();
		$query="insert into $table values($id,$userid,$userlogid,$message_text,$loglevel,$module)";
		@$result=$global['db']->Execute($query) or die ("Error in query: $query".$global['db']->ErrorMsg());
}
	
?>
