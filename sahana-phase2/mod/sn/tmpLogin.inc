<?php
/**
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Harsha Halgaswatta(harsha.halgaswatta@gmail.com)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage s
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $conf;

if ($_SESSION['logged_in'] != true ) {
?>
    <div id="loginform">
	<form method="post" action="index.php?act=login">
        <fieldset><legend><?php echo _t('Login')?></legend>
        <label><?php echo _t('User Name')?></label><input type="text" name="user_name" id="userName" />
        <label><?php echo _t('Password')?></label><input type="password" name="password" id="pswd" />
		<input type="submit" value="Sign In" />
		<br />
        <!-- <a href="#">Forgot your password?</a> -->
        </fieldset>
        <?php
         	$acl=shn_acl_is_signup_enabled();
 			if($acl==true){
 				?>
        <div>
        <?php echo _t("No account? "); ?> <a href="index.php?act=signup"><?php echo _t("Sign Up");?></a>
        </div>
        <?php }?>
    </form>
    <hr />
    <center> <a href="#" onclick="switchLogin('loginform','openid_loginform');"><?php echo _t("Login with an OpenID"); ?></a></center>
    </div><!-- /loginform -->

    <div id="openid_loginform">
    	<form action="" method="get">
    		<fieldset><legend><?php echo _t('OpenId Login')?></legend>
    			<label><?php echo _t('OpenID')?></label><input type="text" name="identity_url" id="openid_login" />
				<input type="submit" value="Sign In" />
				<br />
				<i><?php echo _t("For example: "); ?> <tt>you.someblog.com</tt></i>
			</fieldset>
		</form>
	<center><a href="#" onclick="switchLogin('openid_loginform','loginform');"><?php echo _t("go back to the Normal Login"); ?></a></center>
    </div>
    <script type="text/javascript">
    	switchLogin('openid_loginform','loginform');
    </script>
<?php
} else {
?>
    <div id="loginform">
        <fieldset><legend><?php echo _t('Logged In')?></legend>
        <label><?php echo _t('User: ')?><?php echo $_SESSION['user'];?> </label>
        <br />
        <center><a href="index.php?act=logout"><?php echo _t('Logout')?></a></center>
    </div>

<?php
}


