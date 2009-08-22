<?php
/**
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	Mifan Careem <mifan@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: handler_smstools.inc,v 1.3 2009-08-22 17:17:27 ravithb Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @plugin		SMSTools - http://smstools.meinemullemaus.de/
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_errors.inc');

/**
 * Send short message via SMSTools
 * @todo get SMSTools values from conf file
 * @todo check SMSTools status
 * 
 */
function shn_msg_plugin_send_sm($recipients,$message)
{
	global $global;
	global $conf;
	include_once($global['approot'].'/mod/msg/plugins/smstools/conf.inc');
  
    foreach($recipients as $to){
    	//Let system handle tmp directory: change to absolute dir if needed
    	$filename = tempnam("","");
    	$msg_file = fopen($filename,"w");
    	
    	fwrite($msg_file,"To: ".$to."\n");
    	fwrite($msg_file,"\n");
    	fwrite($msg_file,"$message"."\n");
    	fclose($msg_file);
	$copyto=$conf['msg_outgoing']."/".basename($filename);
    	if(!copy($filename,$copyto)){
    		//Copy failed
    		print "Copy failed. Probably a write error";
		echo "|$copyto|";
    		add_error(_t("Copy Failed"));
    		unlink($filename);
    	}
	if(!chmod($copyto  , 0777  ))
		echo "Faild to change the file owner";
	unlink($filename);
    	
    }//end of loop
}


/**
 * Receive short message via SMSTools :
 * This function will process the GET & POST variables send by the smsfwd (daemon)
 * And return a array consisting with message details.
 * @author J P Fonseka
 */
function shn_msg_plugin_receive_sm(){
    //Check if this request is from smstools
    if(isset($_REQUEST['plugin'])&& $_REQUEST['plugin']=='smstools'){
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
        echo "Sahana server Error : Request is generated from a wrong gateway, server is expecting the request from smstools.";
        return null;
    }
}

/**
 * Check Status of gateway plugin
 * @author Mifan Careem <mifan@respere.com>
 * @return 0: Failed, 1: Success
 */
function shn_msg_plugin_check_status(){
	return 1;
}

function shn_msg_plugin_store_received_msg()
{
	global $db;
	$sender = $_REQUEST['sender'];
	$message = $_REQUEST['msg'];
	
	$sql = "INSERT INTO msg_received_messages (sender,status,message) " .
			" VALUES('{$sender}','1','{$message}')";
}

