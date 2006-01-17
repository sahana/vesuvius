<?php  
/**
* Displays the login box 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @author     ravindra@opensource.lk
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $conf;

if ($_SESSION['logged_in'] != true ) {
?>
    <div id="loginform">
	<form method="POST" action="index.php?act=login">
        <fieldset><legend><?=_('Login')?></legend>
        <label><?=_('User Name')?></label><input type="text" name="user_name" id="userName" />
        <label><?=_('Password')?></label><input type="password" name="password" id="pswd" />
		<input type="submit" value="Login" />
		<br />
        <!-- <a href="#">Forgot your password?</a> -->
        </fieldset>
    </form>
    </div><!-- /loginform -->

<?php
} else {
?>
    <div id="loginform">
        <fieldset><legend><?=_('Logged In')?></legend>
        <label><?=_('User: ')?><?=$_SESSION['user']?> </label>
        <br />
        <center><a href="index.php?act=logout"><?=_('Logout')?></a></center>
    </div>
<?php
}

?>
