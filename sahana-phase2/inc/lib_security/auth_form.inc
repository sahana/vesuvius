<?PHP
/**
 *
 * Sahana authentication form generator library.
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


	global $global;
    include_once $global['approot']. 'inc/lib_security/lib_auth.inc';
    include_once $global['approot']."/inc/lib_errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    
   
/**
 * Generates a form to delete a user
 * @return void
 * @access public
 */
function shn_auth_form_user_del($title="Delete Usert",$mod="admin",$act="del_user_cr",$error=false)
{
   
?>
<?php
    if($error)
    display_errors();
?> 
<h3>Remove Users</h3>              
<div id="formcontainer">
<?php
    shn_form_fopen($act,$mod);
    shn_form_fsopen(_("Select User"));
	$extra_opts['req']=true;
	$users=shn_auth_user_list(true,false);
	shn_form_multi_select('users',$users,"Users",null,$extra_opts);
	//$extra_opts['value']=$_SESSION['user'];
	shn_form_fsclose();
?>
</br>

<?php
//create the submit button
 	shn_form_submit(_("Remove user"));
?>

</br>
<?php
        //close the form
   shn_form_fclose();
?>				     
</div>
<?php

}


/**
 * Generates a form to add an user
 * @return void
 * @access public
 */

function shn_auth_form_signup($title="Create Your Account",$mod="pref",$act="signup_cr",$error=false)
{
	global $global;

    if($error)
    display_errors();
?>               
<h3>SignUp for a SAHANA account</h3> 
<div id="formcontainer">
<?php
    shn_form_fopen($act,$mod);
    
	shn_form_fsopen(_("Account Details"));
	$extra_opts['req']=true;
	//$extra_opts['value']=$_SESSION['user'];
	shn_form_text(_("Full Name "),'account_name','size="30"',null);
	shn_form_text(_("User Name "),'user_name','size="30"',$extra_opts);
	shn_form_password("Password for Login", "password", null, $extra_opts);
	shn_form_password("Confirm Password", "re_password", null, $extra_opts);
	shn_form_fsclose();

    
    $extra_opts['req']=true;
	shn_form_fsopen(_("OpenId Login Details"));
	?><div class="info"><?= _("You can use an OpenID instead of a username/password for login if you like.");?> </div><br /><?
	shn_form_text(_("OpenID "),'openid','size="30"',null);
	shn_form_fsclose();
	
	shn_form_fsopen(_("Just a couple of more Details to verify that you are not a bot"));
	
?>
</br>
<img src="index.php?stream=image&mod=pref&act=captcha" />
<br />
<?php
//create the submit button
	shn_form_text(_("Enter the text in the above image "),'captcha','size="30"',null);
	shn_form_fsclose();
 	shn_form_submit(_("Submit"));
?>

</br>
<?php
        //close the form
   shn_form_fclose();
?>				     
</div>
<?php
    // end of form 
} 

/**
 * Generates a form to add an user
 * @return void
 * @access public
 */

function shn_auth_form_user_add($title="Create Your Account",$mod="admin",$act="add_user_cr",$error=false)
{
	global $global;

    if($error)
    display_errors();
?>               
<h3>Add Users</h3> 
<div id="formcontainer">
<?php
    shn_form_fopen($act,$mod);
    
	shn_form_fsopen(_("Account Details"));
	$extra_opts['req']=true;
	//$extra_opts['value']=$_SESSION['user'];
	shn_form_text(_("Full Name "),'account_name','size="30"',null);
	shn_form_text(_("User Name "),'user_name','size="30"',$extra_opts);
	shn_form_password("Password for Login", "password", null, $extra_opts);
	shn_form_password("Confirm Password", "re_password", null, $extra_opts);
	shn_form_fsclose();
	$roles=_shn_acl_get_roles(null,false);
    shn_form_fsopen(_("Select Role"));
	shn_form_select($roles,"Roles",'roles',null,$extra_opts);
    shn_form_fsclose();
    
    $extra_opts['req']=true;
	shn_form_fsopen(_("OpenId Login Details"));
	?><div class="info"><?= _("Option to use an OpenID instead of a username/password if you'd like.");?> </div><br /><?
	shn_form_text(_("OpenID "),'openid','size="30"',null);
	shn_form_fsclose();
	
?>
</br>

<?php
//create the submit button
 	shn_form_submit(_("Submit"));
?>

</br>
<?php
        //close the form
   shn_form_fclose();
?>				     
</div>
<?php
    // end of form 
} 




/**
 * Generates a form to change the password
 * @return void
 * @access public
 */
 
function shn_auth_form_ch_pwd($error=false)
{


?>
<center><h2>Change Password</h2></center>
<?php
    if($error)
    display_errors();
?>             
<h3>Change Passwords</h3>   
<div id="formcontainer">
<?php
	$act="ch_passwd_cr";
	$mod="pref";
	?>
	<h4>Password must adhere to following rules:</h4>
    1. Minimum length is 8.<br />
    2. At least one letter in the expression.<br />
    3. At least one character is numeric or special.<br />
    4. Cannot be any of the past four (4) passwords.<br />
    5. Passwords cannot be changed more frequently than once per day.<br />
	
	<br />
	<?php
    shn_form_fopen($act,$mod);
    shn_form_fsopen(_("Old and New Password"));
	$extra_opts['req']=true;
	//$extra_opts['value']=$_SESSION['user'];
	shn_form_password("Old Password", "old_password", null, $extra_opts);
	shn_form_password("New Password", "password", null, $extra_opts);
	shn_form_password("Confirm New Password", "re_password", null, $extra_opts);
	$user_id=$_SESSION["user_id"];
	shn_form_hidden(array('user'=>$user_id));
	shn_form_fsclose();
?>
</br>

<?php
//create the submit button
 	shn_form_submit(_("Change Password"));
?>

</br>
<?php
        //close the form
   shn_form_fclose();
?>				     
</div>
<?php      

  // end of form

    
} 

function _shn_admin_ch_pwd_cr(){
    global $global;
    $db=$global["db"];
    $VARCHAR=100;
    
    //for the moment return true
  //  list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
	if ((null==$_POST["old_password"])or(is_null($_POST["old_password"]))){
        $error=true;
        add_error(_("Old password cannot be empty"));
    }else {    
          $old_password=trim($_POST{"old_password"});
    }
	if ((null==$_POST["password"])or(is_null($_POST["password"]))){
        $error=true;
        add_error(_("New password cannot be empty"));
    }else {    
        $password=trim($_POST{"password"});
    }
	if ((null==$_POST["re_password"])or(is_null($_POST["re_password"]))){
        $error=true;
        add_error(_("Confirm password cannot be empty"));
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(_("Password and Confirm Password should match"));
    }
	if($error==true){
    		return $error;
    }
  
    $user_id=trim($_POST{"user"});
    $error=shn_change_password($user_id,$old_password,$password);
   	if($error==true){
    		return $error;
    }
    shn_admin_ch_pwd($error);
}

/**
 * Generates a form to change the password
 * @return void
 * @access public
 */
 
function shn_auth_form_reset_pwd($error=false)
{



    if($error)
    display_errors();
?>  
<h3>Reset Passwords</h3>              
<div id="formcontainer">
<?php
	$act="reset_pwd_cr";
	$mod="admin";
	?>
	<h4>Password must adhere to following rules:</h4>
    1. Minimum length is 8.<br />
    2. At least one letter in the expression.<br />
    3. At least one character is numeric or special.<br />
	
	<br />
	<?php
    shn_form_fopen($act,$mod);
    $extra_opts['req']=true;
	$users=shn_auth_user_list(true);
	shn_form_fsopen(_("Select User"));
    shn_form_select($users,"Users",'user',null,$extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Old and New Password"));
	$extra_opts['req']=true;

	shn_form_password("New Password", "password", null, $extra_opts);
	shn_form_password("Confirm New Password", "re_password", null, $extra_opts);

	shn_form_fsclose();
?>
</br>

<?php
//create the submit button
 	shn_form_submit(_("Reset Password"));
?>

</br>
<?php
        //close the form
   shn_form_fclose();
?>				     
</div>
<?php      

  // end of form

    
} 

function _shn_admin_reset_pwd_cr(){
    global $global;
    $db=$global["db"];
    $VARCHAR=100;

	if ((null==$_POST["password"])or(is_null($_POST["password"]))){
        $error=true;
        add_error(_("New password cannot be empty"));
    }else {    
        $password=trim($_POST{"password"});
    }
	if ((null==$_POST["re_password"])or(is_null($_POST["re_password"]))){
        $error=true;
        add_error(_("Confirm password cannot be empty"));
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(_("Password and Confirm Password should match"));
    }
	if($error==true){
    		return $error;
    }

    $user_id=trim($_POST{"user"});
    if(shn_force_change_password($user_id,$password)==true){
    	return;
    }
	add_confirmation(_("The Password was succesfully updated"));
   // shn_admin_reset_pwd($done);
}
