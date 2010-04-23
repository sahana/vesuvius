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

if ($_SESSION['logged_in'] != true ) { ?>

<div id="loginform">
	<form method="post" action="index.php?act=login">
		<fieldset>
			<legend><?php echo _t('Login')?></legend>
			<label><?php echo _t('Username')?></label>
				<input type="text" name="user_name" id="userName" autocomplete="off" />
			<label><?php echo _t('Password')?></label>
				<input type="password" name="password" id="pswd" autocomplete="off" />
				<input id="submitButton" type="submit" value="Sign In" />
		</fieldset>
	</form>
	<?php
	$acl=shn_acl_is_signup_enabled();
	if ($acl == true) { ?>
		<div id="signUp">
			<?php echo _t("No account? "); ?> <a href="index.php?act=signup"><?php echo _t("Sign Up");?></a>
		</div>
	<?php } ?>
	<div id="switchOpenId">
		<a href="#" onclick="switchLogin('loginform','openid_loginform');"><?php echo _t("Login with an OpenID"); ?></a>
	</div>
</div>
<div id="openid_loginform">
	<form action="" method="get">
		<fieldset id="openIdFieldset">
			<label><?php echo _t('OpenID')?> </label>
			<input type="text" name="identity_url" id="openid_login" />
			<input id="submitButtonOpen" type="submit" value="Sign In" />
		</fieldset>
	</form>
	<div id="switchNormalLogin">
		<a href="#" onclick="switchLogin('openid_loginform','loginform');"><?php echo _t("Go back to the Normal Login"); ?></a>
	</div>
</div>
<script type="text/javascript">
	switchLogin('openid_loginform','loginform');
</script>
<?php
} else {
?>
<div id="loginform">
	<div id="loggedIn">Logged in as: <?php echo $_SESSION['user'];?></div>
        <div id="userPreferencesLink"><a href="index.php?mod=pref"><?=_('User Preferences')?></a></div>
        <div id="logoutLink"><a href="index.php?act=logout"><?=_('Logout')?></a></div>
</div>
<?php
}


