<?php

// Add a new user to the users table
function newUser($user_name, $user_password)
{
   // Create the encrypted password
   $stored_password = md5(trim($user_password));

   // Insert a new user into the users table
   $query = "INSERT INTO users SET 
              password = '{$stored_password}',
             user_name = '{$user_name}'";

//   $result = $connection->query($query);
if (!$connection =@mysql_connect("localhost", "sahana", "sahanapwd"))
  die("Cannot connect");

  if (!mysql_selectdb("sahanadb", $connection))
    showerror();

if (!$result = @ mysql_query ($query, $connection))
echo "error";


}

// Check if a user has an account that matches the username and password
function authenticateUser($user_name, $user_password)
{
   // Create a digest of the password collected from the challenge
   $password_digest = md5(trim($user_password));

if (!$connection =@mysql_connect("localhost", "sahana", "sahanapwd"))
  die("Cannot connect");

if (!mysql_selectdb("sahanadb", $connection))
  showerror();
  
  
   // Formulate the SQL to find the user
   $query = "SELECT password FROM users
             WHERE user_name = '$user_name'
             AND password = '$password_digest'";
//   $result = $connection->query($query);
 if (!$result = @ mysql_query ($query, $connection))
echo "error";
//echo $query;
   // exactly one row? then we have found the user
//   if ($result->numRows() != 1)
  if (mysql_num_rows($result) != 1){
//  echo mysql_num_rows($result);
  return false;
  }
   else{
   echo "successfullt authenticated";
      return true;
   }
}

// Register that user has logged in
function registerLogin($user_id)
{

   // Register the IP address that started this session
   $login_ip = $_SERVER["REMOTE_ADDR"];
   $time_stamp= time();
   
   $query = "select * from user_sessions where user_id = {$user_id}";
   $result = $connection->query($query);
   // exactly one row? then we have found the user
   if ($result->numRows() != 0)
      return true;
   else{
      
      // Insert the session into the user session table
   $query = "INSERT INTO user_sessions SET 
             user_id = {$user_id},
             login_ip = '{$login_ip}',
             session_start = '{$time_stamp}'";

   $result = $connection->query($query);
   if (DB::isError($result)){
      trigger_error($result->getMessage(), E_USER_ERROR);
    return false;
    }
    return true;  
   }
}

// Logout (unregister the login)
function unregisterLogin($user_id)
{
 $query = "delete * from user_sessions where user_id = {$user_id}";
 $result = $connection->query($query);
 if (DB::isError($result)){
      trigger_error($result->getMessage(), E_USER_ERROR);
    return false;
 }
    return true;  
}

// Connects to a session and checks that the user has 
// authenticated and that the remote IP address matches 
// the address used to create the session.
function sessionAuthenticate($user_id,$resource_id,$action)
{
   $login_ip = $_SERVER["REMOTE_ADDR"];
   $query = "select * from user_sessions where user_id = {$user_id} and login_ip = {$login_ip}";
   $result = $connection->query($query);
   // exactly one row? then we have found the user
   if ($result->numRows() != 1)
      return false;
   else{
   //check ACL
   //return (allow($user_id,$resource_id,$action));
   }
  

    $_SESSION["message"] = "You are not authorized to access the URL
                            {$_SERVER["REQUEST_URI"]} from the address
                            {$_SERVER["REMOTE_ADDR"]}";

    unregisterLogin();
    header("Location: {$destinationScript}");
    exit;
  }


?>
