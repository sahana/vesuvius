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
require_once ($global['approot'].'inc/lib_security/authenticate.inc');

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

//start the session
shn_session_start();

// authenticate user
	$user_data = shn_authenticate_user();

 	if($user_data["user_id"]>1){
		shn_session_change($user_data);
    }

var_dump($user_data);     

var_dump($_SESSION);     
/**
*this function is a wrapper around session_start()
*it includes checks to reduce session hijacking
*therefore this function will also start or
*retreive a session like session_start() ,but
*with better security
*/
function shn_session_start(){
	//retrieves or starts a session
   session_start();
   /* since the guest user cant do much , no one would
   try to fix or hijack their session, so let the attackers
    hijack this useless session
  */
  if ('guest'==$_SESSION['user']){
   		return true;
   }
   /*If user is guest then he has privileges ,so we have to protect the    
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
   		$_SESSION["user"]="guest";
		$_SESSION["user_id"]=1;// guest user id is 0
		$_SESSION["user_log_id"]=$log_id;
		return true;
    }
}
/**
* when the user changes privilege levels (e.g login)
*its recommended to regenerate the session id
*this function does that and in addition registers
*,changes several session variables to reflect
*change of privileges
*/

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

/**
*function which checks whether a Session variable is already registered
*since there are many modules ,there is the possibility of one module
*overiding a session varibale of another.
*proper naming convention should reduce that, in addition its recommended
*to call this function to see if the variable is already registered
*/
function shn_session_is_registered($sess_var){
    if(!isset($_SESSION[$sess_var])){
        return true;
    } else {
        return false;
    }
}
?>
