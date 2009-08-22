<?php
/**
*
* Kannel handler file for the messaging controller architecture.
* 
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	  Sri <sri@opensource.lk>
* @author     Mifan Careem <mifan@respere.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  Sahana - http://sahana.lk/
* @subpackage msg
* @plugin	  kannel - http://kannel.org/
* @version 	  $Id: handler_kannel.inc,v 1.3 2009-08-22 17:17:22 ravithb Exp $
* @contrib	  Re-written by Respere for the Messaging/Alerting module - http://respere.com
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* 
*/

/**
 * Send short message via Kannel
 * @author Sri <sri@opensource.lk>
 * @author Mifan Careem <mifan@respere.com>
 * @todo get kannel values from conf file
 * 
 */
function shn_msg_plugin_send_sm($recipients,$message)
{
	global $global;
	global $conf;
	
	if(file_exists($global['approot']."3rd/snoopy/Snoopy.class.php")){
		require_once($global['approot']."3rd/snoopy/Snoopy.class.php");
	}
	else{
		add_error(_t("Snoopy Class Unavailable"));
		return 0;
	}
	
	$sms_box=0;
  	$bearer_box=0;
  	$status_sms=array();
  	$snoopy = new Snoopy;
  
    foreach($recipients as $to){
        $form_msg = urlencode($message);
        $snoopy->fetchtext("http://localhost:13014/cgi-bin/sendsms?username=tester&password=foobar&to=".$to."&text=".$form_msg);
        $server_response=$snoopy->results;
        if(strcmp($server_response[0],"Sent.")){
          	$status_sms[$to]=1;
        }
        else{
	  		$status_sms[$to]=0;
        }
       $server_response="";
    }//end of loop
    return $status_sms;
}

/**
 * Receive short message via kannel :
 * This function will process the GET & POST variables send by the kannel
 * And return a array consisting with message details.
 * @author J P Fonseka  <jo@respere.com>
 */
function shn_msg_plugin_receive_sm(){
    //Check if this request is from smstools
    if(isset($_REQUEST['plugin'])&& $_REQUEST['plugin']=='kannel'){
    //check if all the required GET & POST values are set
        if(isset($_REQUEST['From'])&&isset($_REQUEST['Received'])&&isset($_REQUEST['message'])){
            //create an array and return the content of this array will be added to receive table.
            $received_message=array();
            $received_message['sender']=$_REQUEST['From'];
            $received_message['received']=$_REQUEST['Received'];
            $received_message['message']=$_REQUEST['message'];
            return $received_message;
        }
        else{
            echo "Sahana server Error : Required fields are not set.";
            return null;
        }
    }
    else{
        echo "Sahana server Error : Request is generated from a wrong gateway, server is expecting the request from kannel.";
        return null;
    }
}

/**
 * Check Status of gateway plugin
 * @author Sriganeshan <sri@opensource.lk>
 * @author Mifan Careem <mifan@respere.com>
 * @return 0: Failed, 1: Success
 * @todo get kannel port and URI from conf file
 * @todo Check whether Kannel is started or not
 */
function shn_msg_plugin_check_status()
{
	  global $global;
	  if(file_exists($global['approot']."3rd/snoopy/Snoopy.class.php")){
		require_once($global['approot']."3rd/snoopy/Snoopy.class.php");
	  }
	  else{
		add_error(_t("Snoopy Class Unavailable"));
		return 0;
	  }
	  $kannel_status=0;
	  $sms_box=0;
	  $bearer_box=0;
	  $status_sms=array();
	  $snoopy = new Snoopy;
	  $snoopy->fetchtext("http://localhost:13014/cgi-bin/sendsms?");
	  $server_response=$snoopy->results;
	  $pieces = explode(" ",$server_response);
	  if((strcmp($pieces[0],"Authorization")==0) && (strcmp($pieces[1],"failed")==0)){
	    	$sms_box=1;
	  }
	  /*
	  $snoopy->fetchtext("http://localhost:13003/");
	  $server_response=$snoopy->results;
	  $pieces = explode(" ",$server_response);
	  if(!strcmp($pieces[0],"Unknown") && !strcmp($pieces[1],"command"))
	    $bearer_box=1;
	  else
	    $bearer_box=0;
	*/
	  if($sms_box){ 
	    $kannel_status= 1;
	  }
	
	return $kannel_status;
	//return true;
	
}
function shn_msg_plugin_store_received_msg()
{
	global $db;
	$sender = $_REQUEST['sender'];
	$message = $_REQUEST['msg'];
	
	$sql = "INSERT INTO msg_received_messages (sender,status,message) " .
			" VALUES('{$sender}','1','{$message}')";
}




