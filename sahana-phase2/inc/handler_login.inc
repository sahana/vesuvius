<?php  
/**
* Displays the login box 
* Sahana - http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage handler 
* @author     http://www.linux.lk/~chamindra
* @author     ravindra@opensource.lk
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $conf;

if ($_SESSION['logged_in'] != true ) {
?>
    <div id="loginform">
	<form method="post" action="index.php?act=login">
        <fieldset><legend><?=_('Login')?></legend>
        <label><?=_('User Name')?></label><input type="text" name="user_name" id="userName" />
        <label><?=_('Password')?></label><input type="password" name="password" id="pswd" />
		<input type="submit" value="Sign In" />
		<br />
        <!-- <a href="#">Forgot your password?</a> -->
        </fieldset>
        <?php
         	$acl=shn_acl_is_signup_enabled();
 			if($acl==true){
 				?>
        <div>
        <?php echo _("No account? "); ?> <a href="index.php?act=signup"><?php echo _("Sign Up");?></a>
        </div>
        <?php }?>
    </form>
    <hr />
    <center> <a href="#" onclick="switchLogin('loginform','openid_loginform');"><?php echo _("Login with an OpenID"); ?></a></center>
    </div><!-- /loginform -->
    
    <div id="openid_loginform">
    	<form action="" method="get">
    		<fieldset><legend><?=_('OpenId Login')?></legend>
    			<label><?=_('OpenID')?></label><input type="text" name="identity_url" id="openid_login" />
				<input type="submit" value="Sign In" />
				<br />
				<i><?php echo _("For example: "); ?> <tt>you.someblog.com</tt></i>
			</fieldset>
		</form>
	<center><a href="#" onclick="switchLogin('openid_loginform','loginform');"><?php echo _("go back to the Normal Login"); ?></a></center>
    </div>
    <script type="text/javascript">
    	switchLogin('openid_loginform','loginform');
    </script>
<?php
} else {
?>
    <div id="loginform">
        <fieldset><legend><?=_('Logged In')?></legend>
        <label><?=_('User: ')?><?php echo $_SESSION['user'];?> </label>
        <br />
        <center><a href="index.php?act=logout"><?=_('Logout')?></a></center>
    </div>

<?php
}

?>
