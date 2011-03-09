<?
/**
 * @name         Login Handler
 * @version      1.0
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



global $conf;
global $global;

if ($_SESSION['logged_in'] != true ) {
	echo "
		<div id=\"loginform\">
			<form method=\"post\" action=\"index.php?act=login\">
				<fieldset>
					<legend>Login</legend>
					<label>Username</label><input type=\"text\"     name=\"user_name\" id=\"userName\" autocomplete=\"off\" />
					<label>Password</label><input type=\"password\" name=\"password\"  id=\"pswd\"     autocomplete=\"off\" />
					<label>&nbsp;</label><input   type=\"submit\"   id=\"loginButton\" value=\"Sign In\" class=\"styleTehButton\" /><br>
				";
				$acl = shn_acl_is_signup_enabled();
				if($acl == true) {
					echo "<span id=\"signUp\"><a href=\"index.php?act=signup\">Register for an Account</a></span>";
					echo "<span id=\"forgotPassword\"><a href=\"index.php?act=forgotPassword\">Forgot My Password</a></span>";
				}
				echo "
				</fieldset>
			</form>
			<div id=\"switchOpenId\">
				<a href=\"#\" onclick=\"switchLogin('loginform','openid_loginform');\">Login with an OpenID></a>
			</div>
		</div>
		<div id=\"openid_loginform\">
			<form action=\"\" method=\"get\">
				<fieldset id=\"openIdFieldset\">
					<label>OpenID</label>
					<input type=\"text\" name=\"identity_url\" id=\"openid_login\" />
					<input id=\"submitButtonOpen\" type=\"submit\" value=\"Sign In\" autocomplete=\"off\"/>
				</fieldset>
			</form>
			<div id=\"switchNormalLogin\">
				<a href=\"#\" onclick=\"switchLogin('openid_loginform','loginform');\">Go back to the Normal Login</a>
			</div>
		</div>
		<script type=\"text/javascript\">
			switchLogin('openid_loginform','loginform');
		</script>
	";
} else {
	echo "
		<div id=\"loginform\">
			<div id=\"loggedIn\">
				<b>Currently logged in as :</b><br>
				".$_SESSION['group_name']." / ".$_SESSION['user_name']."<br><br>
				<span id=\"logoutLink\" class=\"styleTehButton\"><a href=\"index.php?act=logout\">Logout</a></span>
			</div>

		</div>
	";
}


