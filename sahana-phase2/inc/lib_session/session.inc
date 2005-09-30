<?php
/**
* This library helps in session management
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/




/* following code decides the session management approach
e.g write sessions to the database or files 
*/

switch ($conf["session_writer"]){

case "database":

	switch ($conf["session_database"]){
	
	case "adodb":
	//	shn_db_session();
		break;
		
	case "phpdb":
        if($session_encrypt){
            include "php_session_db_encrypt.inc";
        } else {
		    include "php_session_db.inc";
        }
		break;
	
	default:
        break;
    }

case "files":
	break;

default:
	break;
}

function shn_session_start(){
	//retrieves or starts a session
   session_start();
   /* since the anonymous user cant do much , no one would
   try to fix or hijack their session, so let the attackers
    hijack this useless session
  */
  if ('anonymous'==$_SESSION['user']){
   		return true;
   }
   /*If user is anonymous then he has privileges ,so we have to protect the    
      session ,lets  try to make it hard for session hijacking
    the use of IPADDRESS to prevent session hijacking has
   been rejected by many many PHP experts, what they say
   is its relatively easy to spoof an IP ,on the other hand
   many networks change the IP for every request
   e.g AOL with millions of users
	*/
   
   if (isset($_SESSION['initiated'])){
   	/* user agent maybe not present in every request, so check only if its set ,
	so users with user agent are more secure against their session being hijacked
	*/
        if (isset($_SESSION['HTTP_USER_AGENT'])){
            if ($_SESSION['HTTP_USER_AGENT'] != md5($_SERVER['HTTP_USER_AGENT'])) {
            	return false;
            }
        }else {
			return true;
		}
		
    }else {
	 	$ip=$_SERVER['REMOTE_ADDR'];
		//create an entry in the user log and obtain the automatically generated id
	   	// $log_id=shn_db_insert("cre_userlog",array("userid"=>$user_id,"ip"=>$ip));
        $_SESSION['user_agent'] = md5($_SERVER['HTTP_USER_AGENT']);
        $_SESSION['initiated'] = true;
        $_SESSION['logged_in'] = false;
   		$_SESSION["user"]="anonymous";
		$_SESSION["user_id"]=0;// anonymous user id is 0
		$_SESSION["user_log_id"]=$log_id;
		return true;
    }
}


function shn_session_change($user_data){
	/*regenerate the session id and send to the client, this  is essential
	as user obtained different privileges
	*/ 
	session_regenerate_id();
    	$_SESSION['logged_in'] = true;
    	$_SESSION['user'] = $user_data["user"];
    	$_SESSION['user_id'] =$user_data["user_id"];
		return ;
}

// function which checks whether a Session variable is already registered
function shn_session_register($sess_var){
    if(!isset($_SESSION[$sess_var])){
        return true;
    } else {
        return false;
    }
}
?>
