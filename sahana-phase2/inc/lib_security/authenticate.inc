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
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

// Add a new user to the users table
function shn_add_user($user_name, $user_password)
{
   // Create the encrypted password
   $stored_password = md5(trim($user_password));

   // Insert a new user into the users table
   $query = "INSERT INTO users SET 
             password = '{$stored_password}',
             user_name = '{$user_name}'";
	echo $query;
//   $result = $connection->query($query);
	if (!$connection =@mysql_connect("localhost", "sahana", "sahanapwd"))
  		die("Cannot connect");

  	if (!mysql_selectdb("sahanadb", $connection))
    	showerror();
	if (!$result = @ mysql_query ($query, $connection))
		echo "error";
	return $result;

}

// Check if a user has an account that matches the user name and password
function shn_authenticate_user()
{
	/*need to modify the function to work with the sahana database scheme
	and adodb code 
	*/
	return true;
	global $global;

	$user_data=array("user_id"=>0,"user"=>"anonymous");
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
        $connection =@mysql_connect("localhost", "sahana", "sahanapwd");
        //    die("Cannot connect");
        mysql_selectdb("sahanadb", $connection);
        //    showerror();
       // Formulate the SQL to find the user
        $query = "  SELECT user_id  FROM users
                    WHERE user_name = '$user'
                    AND password = '$password_digest'";
        $result = @ mysql_query ($query, $connection);
       /* no result ,so return 0 ,which is  not a valid user_id , the calling
       application can identify authentication was attempted,but failed
       */	   
       if (mysql_num_rows($result) != 1){
     		$user_data["user_id"]=0;
            return false;
        }
         else {
   			$myresult=mysql_fetch_row($result);
     		$user_data["user_id"]=$myresult[0];
     		$user_data["user"]=$user;
			return $user_data;
		}
   }
}
?>
