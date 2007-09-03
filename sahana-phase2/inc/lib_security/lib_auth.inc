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


function shn_auth_user_list_and_status(){
  	global $global;
    $db=$global['db'];
  
    $q="select users.p_uuid,full_name,user_name,status from person_uuid,users where users.p_uuid=person_uuid.p_uuid and users.p_uuid <> 1  order by full_name";
	$res=$db->Execute($q);
    $users=array();
        
    while(!$res->EOF){
    	//$name=$res->fields[2].".".$res->fields["full_name"];
    	$name=$res->fields["full_name"].":".$res->fields["user_name"];
       	$users[$res->fields["p_uuid"]]=array($name,$res->fields["status"]);
        $res->MoveNext();
    }
	return $users;

}

function shn_auth_locked_user_list(){
  	global $global;
    $db=$global['db'];
  
    $q="select users.p_uuid,full_name,user_name,status from person_uuid,users where status='locked' and users.p_uuid=person_uuid.p_uuid and users.p_uuid <> 1  order by full_name";
	$res=$db->Execute($q);
    $users=array();
    
    while(!$res->EOF){
    	//$name=$res->fields[2].".".$res->fields["full_name"];
    	$name=$res->fields["full_name"].":".$res->fields["user_name"];
       	$users[$res->fields["p_uuid"]]=array($name,$res->fields["status"]);
        $res->MoveNext();
    }
	return $users;

}
function shn_auth_activate_user($pid=null,$uname=null){
	if($pid==null){
			if($uname==null){
				return false;
			}else{
				$sql="update users set status='active'  where user_name='{$uname}'";
			}
	}else{
			$sql="update users set status='active' where p_uuid='{$pid}'";
		
	}

	//echo $sql;
	global $global;
    $db=$global['db'];
	$res=$db->Execute($sql);
	return $res;
	
}
/**
*check the existence of an user
*@return bool
*@param string user name
*@access public
*/
function shn_current_user(){
	global $global;
    $q = "select p_uuid from  users where  user_name = '{$_SESSION['user']}'";
    $db=$global['db'];
	$res=$db->Execute($q);
    if(($res==null) or ($res->EOF)){
        return null;
    }else {
        return $res->fields["p_uuid"];
    }
}

function shn_get_user_details($user){
	
    $q = "select full_name from person_uuid where  p_uuid = '{$user}'";
    global $global;
    $db=$global['db'];
	$res=$db->Execute($q);
    if(($res==null) or ($res->EOF)){
        return false;
    }else {
        return $res->fields["full_name"];
    }
}

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
function shn_auth_add_user($account_name,$user_name, $user_password,$role,$pid=NULL,$extra_opts=null)
{
    global $global;
    $db=$global['db'];
    include_once($global['approot']."/inc/lib_uuid.inc");
    
   	if($user_name==null){
   		return false;
   	}
    if($role==null){
    	$role=REGISTERED;
    }
    if (shn_is_user($user_name)){
        add_error(SHN_AUTH_ERR_USER_EXISTS);
   		return false;
    }

    if($pid==null){
       // $pid = $db->GenID('person_seq',10);
       $pid=shn_create_uuid($type='person');
       $q="insert into person_uuid(p_uuid,full_name) values('{$pid}','{$account_name}')";
       $res=$db->Execute($q);
       if($res==false){
				add_error($db->ErrorMsg());
				$error=true;
		}
    }else{
     	$q="select p_uuid from person_uuid where p_uuid='{$pid}'";
    	$res=$db->Execute($q);
    	if($res->EOF){
        	$error=true;
       		add_error(SHN_AUTH_ERR_PERSON_NOT_EXISTS);
        	return false;
    	}   	
    }
    


 	if(!$error){

   		 // Create the encrypted password
   		$salt1=_shn_generateSalt();
   		$salt2=_shn_generateSalt();
   		$salt=$salt1.$salt2;
   		$user_password=substr($user_password, 0, 4).$salt.substr($user_password, 4);
   		$stored_password = md5(trim($user_password));
		$time=time();
		if($extra_opts['pending']==true){
			$status='pending';


		}else{
				   			// Insert a new user into the users table
			$status='active';

		}
		$q = "INSERT INTO users(p_uuid,password,changed_timestamp,user_name,salt,status) values('{$pid}','{$stored_password}',{$time},'{$user_name}','{$salt}','{$status}')";
   
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

function shn_auth_user_list($fullname=false){
  	global $global;
    $db=$global['db'];
  
    $q="select users.p_uuid,full_name,user_name from person_uuid,users where users.p_uuid=person_uuid.p_uuid and users.p_uuid <> 1  order by user_name";
	$res=$db->Execute($q);
    $users=array();
        
    while(!$res->EOF){
    	//$name=$res->fields[2].".".$res->fields["full_name"];
    	if($res->fields["full_name"]==null){
    		$name="Full Name not avaliable - ".$name=$res->fields["user_name"];
    	}else{
    		$name=$res->fields["full_name"]." - ".$name=$res->fields["user_name"];
    	}
    	//$name=$res->fields["full_name"];
       	$users[$res->fields["p_uuid"]]=$name;
        $res->MoveNext();
    }
	return $users;

}

function shn_authenticate_ws_signature($secret,$sign,$digest){
	
	$cmp_sign=md5(shn_acl_hmac_sha1($digest,$secret));
	
	if($sign==$cmp_sign){
		
		return true;
	}else{
		return false;
	}
	
}


function shn_authenticate_ws_user($user,$pwd,$extra_opts=null)
{
	global $global;
    $db=$global['db'];
	$sql="select secret,domain from ws_keys where api_key='{$user}' and password='{$pwd}'";
	$res=$db->Execute($sql);
    if(($res==null) or ($res->EOF)){
        return null;
    }else {
        return $res->fields["secret"];
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
        $q = "SELECT salt,p_uuid,status  FROM users
                    WHERE user_name = '$user'";
        $res=$db->Execute($q);
        if(($res==null)||($res->EOF)){
        	add_error("Login Failed : Invalid user name or password.");
            shn_acl_log_error("Login Failed : Invalid user name or password.","aonymous","Aonymous User");
        	$user_data["user_id"]=ANONYMOUS_USER;
        	$user_data["user"]="Anonymous";
            return $user_data;
        }else{
        	$status=$res->fields["status"];
        	$salt=$res->fields["salt"];
        	$uid=$res->fields["p_uuid"];
        }
         if($status=='pending'){
                    $user_data["user_id"]=ANONYMOUS_USER;
        			$user_data["user"]="Anonymous";
        			return $user_data;
         }

        
        if($status=='locked'){
        	$sql="select changed_timestamp from password_event_log where p_uuid='{$uid}' and event_type=1 order by changed_timestamp desc ";
        	$res=$db->Execute($sql);
        	if(($res==null)||($res->EOF)){
        		add_error("Login Failed : Password log attacked.");
            	shn_acl_log_error("Login Failed : Password log attacked.",$uid,$user,1);
            	$user_data["user_id"]=ANONYMOUS_USER;
        		$user_data["user"]="Anonymous";
        		return $user_data;
        	}else{
        		$tstamp=$res->fields["changed_timestamp"];
        		$now=time();
        		$diff=$now-$tstamp;
        		if($diff < LOCK){
        			//add_error("Login Failed : Password lock still valid.");
        			add_error("This account has been locked.  Please contact OEM to unlock the account.");
            		shn_acl_log_error("Login Failed : Password lock still valid.",$uid,$user);
            		$user_data["user_id"]=ANONYMOUS_USER;
        			$user_data["user"]="Anonymous";
        			return $user_data;
        		}
        		
        	}
        	
        }
      
        $pwd=substr($pwd, 0, 4).$salt.substr($pwd, 4);
       
        $user_data["result"]=LOGGEDOUT;
         // Create a digest of the password collected from the challenge
        $password_digest = md5(trim($pwd));
        // Formulate the SQL to find the user
        $q = "  SELECT p_uuid  FROM users
                    WHERE user_name = '$user'
                    AND password = '$password_digest' and salt='{$salt}'";
       
        $res=$db->Execute($q);
        if(($res==null)||($res->EOF)){
            /* no result ,so return 1 ,which is  not a valid user_id , the calling
            application can identify authentication was attempted,but failed
            */
            add_error("Login Failed : Invalid user name or password.");
            shn_acl_log_error("Login Failed : Invalid Password.",$uid,$user,1);
        	$user_data["user_id"]=ANONYMOUS_USER;
        	$user_data["user"]="Anonymous";
        	_shn_auth_lock_user($uid,$status);
            return $user_data;

        }else{
				if(($status=='locked')||($status=='try1')||($status=='try2')){
					shn_auth_activate_user($uid);
				}
                $user_data["user_id"]=$res->fields["p_uuid"];
     		    $user_data["user"]=$user;
     	        $user_data["result"]=LOGGEDIN;
                $global['welcome']=true;
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
	date_default_timezone_set('America/New_York');
	global $global;
    $db=$global['db'];
	$q = "  SELECT p_uuid,salt  FROM users
                    WHERE p_uuid = '$user'";
                   // AND password = '$password_digest'";
    $res=$db->Execute($q);
	if($res->EOF){
		return true;
	}else{
		$salt=$res->fields["salt"];
	}
	
	$pwd=substr($old_pwd, 0, 4).$salt.substr($old_pwd, 4);
  
         // Create a digest of the password collected from the challenge
        $password_digest = md5(trim($pwd));
        // Formulate the SQL to find the user
        $q = "  SELECT p_uuid  FROM users
                    WHERE p_uuid = '$user'
                    AND password = '$password_digest' and salt='{$salt}'";
   		
	 if(($res==null) ||($res->EOF)){
	 	return true;
	 }else{
	 		$time=time();
			$new_pwd=substr($new_pwd, 0, 4).$salt.substr($new_pwd, 4);
			$password_digest = md5(trim($new_pwd));
       		// Formulate the SQL to find the user
        	$q = "  update users set password = '{$password_digest}',changed_timestamp={$time}
                    WHERE p_uuid = '$user'";
        	$res=$db->Execute($q);
			return $res;
	 }

}

function shn_force_change_password($user=null,$new_pwd,$p_uuid=null)
{
	if(shn_validate_password($user,$new_pwd)==false){
		return true;
	}
	date_default_timezone_set('America/New_York');
	global $global;
    $db=$global['db'];
    if($p_uuid=null){
		$q = "  SELECT p_uuid,salt  FROM users
                    WHERE user_name = '$user'";
                   // AND password = '$password_digest'";
    }else{
    	$q = "  SELECT p_uuid,salt  FROM users
                    WHERE p_uuid = '$user'";
    }
    $res=$db->Execute($q);
  
	if($res->EOF){
		return true;
	}else{
		$salt=$res->fields["salt"];
	}
	$time=time();
	$new_pwd=substr($new_pwd, 0, 4).$salt.substr($new_pwd, 4);
	$password_digest = md5(trim($new_pwd));
        // Formulate the SQL to find the user
    if($p_uuid=null){
        $q = "  update users set password = '{$password_digest}',changed_timestamp={$time}
                    WHERE user_name = '$user'";
    }else{
    	$q = "  update users set password = '{$password_digest}',changed_timestamp={$time}
                    WHERE p_uuid = '$user'";
    }
        
        $res=$db->Execute($q);

		return false;
}

/******** form processing ****/

function shn_auth_add_user_cr(){
   global $global;
 	$db=$global["db"];
	$VARCHAR=100;

   list($error,$user_name)=(shn_validate_user_name($_POST{"user_name"}))?array($error,$_POST{"user_name"}):array(true,NULL);

    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"user_name"},$_POST{"password"}))?array(false,$_POST{"password"}):array(true,$_POST{"password"});

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
    $role=$_POST["roles"];
    
	if(shn_auth_add_user($account_name,$user_name,$password,$role,null)==false){
		
	}else{
		$msg=$_POST{"account_name"}." was successfully registered as a User ";
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



function _shn_generateSalt($salt = null)
{
    if ($salt === null)
    {
        $salt = substr(md5(uniqid(rand(), true)), 0, SALT_LENGTH);
    }
    else
    {
        $salt = substr($salt, 0, SALT_LENGTH);
    }
	//$salt=$salt.
    return $salt;
}

function _shn_auth_lock_user($uid,$status)
{
	global $global;
	$role=STSUSER;
	if(_shn_acl_is_user_role_only($uid,$role)==true){
		return true;
	}
	$db=$global["db"];
	$next_status='locked';
	switch ($status){
		case 'active':
			$next_status='try1';
		break;
		case 'try1':
			$next_status='try2';
		break;
		case 'try2':
			$next_status='locked';
		break;

	}
	$sql="update users set status='{$next_status}' where p_uuid='{$uid}'";
    $res=$db->Execute($sql);
    if($res==false){
				add_error($db->ErrorMsg());
	}
	
}


?>
