<?php
/**
 *
 * This library helps in authentication ,but not authorization. A vital component of the framework.
 * Developers are required to use this library for security.
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */


require_once "constants.inc";
require_once "errors.inc";
require_once "lib_acl.inc";

/**
*Add a new user to the users table
*@param string account name(nice name for the user)
*@param string user namee
*@param string user password
*@param string role 
*@param p_uuid p_id ( user id , if not present the value is generated)
*@access public
*@return bool
*/
function shn_auth_add_user($account_name,$user_name, $user_password,$role,$pid=NULL)
{
    global $global;
    $db=$global['db'];
    include_once($global['approot']."/inc/lib_uuid.inc");
   
    
    if (shn_is_user($user_name)){
        add_error(SHN_AUTH_ERR_USER_EXISTS);
   		return false;
    }

    if($pid==null){
       // $pid = $db->GenID('person_seq',10);
       $pid=shn_create_uuid($type='person');
    }
    
    $q="select p_uuid from person_uuid where p_uuid='{$pid}'";
    $res=$db->Execute($q);
    if(!$res->EOF){
        $error=true;
       	add_error(SHN_AUTH_ERR_PERSON_EXISTS);
        return false;
    }

 	if(!$error){
        $q="insert into person_uuid(p_uuid,full_name) values('{$pid}','{$account_name}')";
        $res=$db->Execute($q);
        	if($res==false){
				add_error($db->ErrorMsg());
			}
   		 // Create the encrypted password
   		$stored_password = md5(trim($user_password));

   		// Insert a new user into the users table
  		 $q = "INSERT INTO users SET 
             p_uuid='{$pid}',
		password = '{$stored_password}',
             user_name = '{$user_name}'";
    
		$res=$db->Execute($q);
        if($res==false){
				add_error($db->ErrorMsg());
		}
		//$role=REGISTERED;
		if ($res){
    		//$res=shn_acl_add_user($pid,$user_name);
    		$res=shn_acl_adduser_to_role($pid,$role);
    		
		}
    }
	return $res;
}

/**
*check the existence of an user
*@return bool
*@param string user name
*@access public
*/
function shn_is_user($user_name){
	
    $q = "select p_uuid from  users where  user_name = '{$user_name}'";
    global $global;
    $db=$global['db'];
	$res=$db->Execute($q);
    if(($res==null) or ($res->EOF)){
        return false;
    }else {
        return true;
    }
}

function shn_auth_user_list(){
  	global $global;
    $db=$global['db'];
  
    $q="select users.p_uuid,full_name,user_name from person_uuid,users where users.p_uuid=person_uuid.p_uuid and users.p_uuid <> 1  order by full_name";
	$res=$db->Execute($q);
    $users=array();
        
    while(!$res->EOF){
    	//$name=$res->fields[2].".".$res->fields["full_name"];
    	$name=$res->fields["full_name"];
       	$users[$res->fields["p_uuid"]]=$name;
        $res->MoveNext();
    }
	return $users;

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
*@access public
*/

function shn_authenticate_user()
{
	/*need to modify the function to work with the sahana database scheme
	and adodb code, till then return true. 
	*/

    global $global;
    $db=$global['db'];
	$user_data=array("user_id"=>ANONYMOUS_USER,"user"=>"Anonymous");
    if("logout"==$_GET['act']){
     	$user_data["user_id"]=ANONYMOUS_USER;
     	$user_data["user"]="Anonymous";
     	$user_data["result"]=LOGGEDOUT;
	 	return $user_data ;
    }
    /* if user has not requested login no need to authenticate, simply
	return -1 , so the calling application can identify that 			
	authentication was not attempted
	*/
	if("login"!=$_GET['act']){
     	$user_data["user_id"]=-1;
	 	return $user_data ;
    } else {
    //authentication is done only as the user requested to login
        $user= addslashes(strip_tags(trim($_POST{"user_name"})));
        $pwd= addslashes(strip_tags(trim($_POST{"password"})));
        $user_data["result"]=LOGGEDOUT;
         // Create a digest of the password collected from the challenge
        $password_digest = md5(trim($pwd));
        // Formulate the SQL to find the user
        $q = "  SELECT p_uuid  FROM users
                    WHERE user_name = '$user'
                    AND password = '$password_digest'";
       
        $res=$db->Execute($q);
        if(($res==null)||($res->EOF)){
            /* no result ,so return 1 ,which is  not a valid user_id , the calling
            application can identify authentication was attempted,but failed
            */	
        	$user_data["user_id"]=ANONYMOUS_USER;
        	$user_data["user"]="Anonymous";
            return $user_data;

        }else{

                $user_data["user_id"]=$res->fields["p_uuid"];
     		    $user_data["user"]=$user;
     	        $user_data["result"]=LOGGEDIN;
			    return $user_data;
        }
    }
}
/**
 * Changes the password
 * @param string user name
 * @param string old password
 * @param string new password
 * @access public
 */
function shn_change_password($user,$old_pwd,$new_pwd)
{
	global $global;
        $db=$global['db'];
	$password_digest = md5(trim($old_pwd));
       $q = "  SELECT p_uuid  FROM users
                    WHERE p_uuid = '$user'
                    AND password = '$password_digest'";
        $res=$db->Execute($q);
	if($res->EOF){
		return true;
	}
	$password_digest = md5(trim($new_pwd));
        // Formulate the SQL to find the user
        $q = "  update users set password = '$password_digest'
                    WHERE p_uuid = '$user'";
        $res=$db->Execute($q);
	return $res;
}

/******** form processing ****/

function shn_auth_add_user_cr(){
   global $global;
 	$db=$global["db"];
	$VARCHAR=100;

   list($error,$user_name)=(shn_validate_user_name($_POST{"user_name"}))?array($error,$_POST{"user_name"}):array(true,NULL);
    
    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
    if (is_null($_POST{"re_password"})){
        $error=true;
        add_error(SHN_ERR_ADMIN_REPWD_INCOMPLETE);
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(SHN_ERR_ADMIN_REPWD_WRONG);
    }
	 if (trim(strlen($_POST{"account_name"})) > $VARCHAR){
        $error=true;
        add_error(SHN_ERR_ADMIN_REG_MAX);
    }else {
        $account_name=$_POST{"account_name"};
    }

    if($error==true){
    		return $error;
    }
    
	if(shn_auth_add_user($account_name,$user_name,$password,"user",-1)==false){
		
	}else{
		$msg=$_POST{"account_name"}." was succesfully registered as a User ";
     	add_confirmation($msg);
	}
    return $error;
}


function _shn_auth_del_user_cr(){
   global $global;
	$user=$_POST{"users"};
 	$db=$global["db"];
	$VARCHAR=100;
	for($i=0;$i<count($user);$i++){

		$q="delete from users where p_uuid='{$user[$i]}'";
        $res=$db->Execute($q);
        if($res==false){
				add_error($db->ErrorMsg());
		}
       
	}
	if($res==false){
		add_error(_("User does not exist"));
	}else{
		add_confirmation(_("User was successfully removed"));
	}
}


?>
