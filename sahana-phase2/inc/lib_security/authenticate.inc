<?php
/**
* This library helps in authentication ,but not authorization
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva(ravindra@opensource.lk)
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
*Add a new user to the users table
*@return bool 
*@param string user name
*@param string user password
*/
include "acl_api.inc";

function shn_add_user($p_uuid,$user_name, $user_password)
{
    global $global;
    $db=$global['db'];

    if (shn_is_user($user_name)){
        add_error(SHN_ERR_OR_USER_EXISTS);
   		return false;
	}
   // Create the encrypted password
   $stored_password = md5(trim($user_password));

   // Insert a new user into the users table
   $q = "INSERT INTO users SET 
             p_uuid='{$p_uuid}',
		password = '{$stored_password}',
             user_name = '{$user_name}'";
	echo $query;
	$res=$db->Execute($q);
	if ($res){
    	$res=shn_acl_add_user($p_uuid,$user_name);
    	$res=shn_acl_add_to_role($p_uuid,"user");
	}
	return $res;
}

/**
*check the existence of an user
*@return bool
*@param string user name
*/
function shn_is_user($user_name){
	
    $q = "select p_uuid from  users where  user_name = '{$user_name}'";

    global $global;
    $db=$global['db'];
	$res=$db->Execute($q);
    if(!$res->EOF){
       if(($res->fields[0])>0){
           return true;
        }
    }
}

/**
*Check if a user has an account that matches the user name and password
*therefore this is the function you need to call for authentication
*since authentication is called by the front controller
*and all the POST variables avaliable to the front controller
*are avaliable to this function as well,user name and password
*are not sent as parameters. Instead they are read from the POST
*array.
*remember this function will be called with every request to the front
*controller. But we need to authenticate only when its a login attempt
*if its not a login request return -1
*@return int the user id , if the user exists ,else 0 or -1
*/

function shn_authenticate_user()
{
	/*need to modify the function to work with the sahana database scheme
	and adodb code, till then return true. 
	*/
	return true;
    global $global;
    $db=$global['db'];
	$user_data=array("user_id"=>0,"user"=>"guest");
 	/* if user has not requested login no need to authenticate, simply
	return -1 , so the calling application can identify that 			
	authentication was not attempted
	*/
	if("login_submit"!=$global['action']){
     	$user_data["user_id"]=-1;
	 	return $user_data ;
    } else {
    //authentication is done only as the user requested to login
        $user = $_POST{"user"};
        $pwd =$_POST{"pwd"};
         // Create a digest of the password collected from the challenge
        $password_digest = md5(trim($pwd));
        // Formulate the SQL to find the user
        $query = "  SELECT user_id  FROM users
                    WHERE user_name = '$user'
                    AND password = '$password_digest'";
    	$res=$this->db->Execute($q);
        if(!$res->EOF){
            $user_id=$res->fields[0];
            if($user_id>0){
     		    $user_data["user_id"]=$user_id;
     		    $user_data["user"]=$user;
			    return $user_data;
            }
            else{
                /* no result ,so return 0 ,which is  not a valid user_id , the calling
                application can identify authentication was attempted,but failed
                */	
        	    $user_data["user_id"]=0;
                return $user_data;
            }
        }
        else{
            /* no result ,so return 0 ,which is  not a valid user_id , the calling
            application can identify authentication was attempted,but failed
            */	
        	$user_data["user_id"]=0;
            return $user_data;
        }
    }
}
?>
