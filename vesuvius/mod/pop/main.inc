<?
/**
 * @name         Push Out Post
 * @version      1.0
 * @package      pop
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


/**
 * @access public
 * @return void
 */
function shn_pop_default() {
	shn_pop_configuration();
}



function shn_pop_first() {
	echo "
		<h2><a href=\"index.php?mod=pop&amp;act=configuration\">Configure Outbound Email Settings</a></h2>
		<h2><a href=\"index.php?mod=pop&amp;act=outlog\">View Outbound Email Log</a></h2><br>
	";
}



/**
 * Generates the Configuration Page and provides the load/save functions for configuration data.
 * @access public
 * @return void
 */
function shn_pop_outlog() {
	global $global;
	shn_pop_first();

	$query  = "
		SELECT *
		FROM pop_outlog
		ORDER BY time_sent DESC
		LIMIT 100;
	";
	$result = $global['db']->Execute($query);
	$count = 0;
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Last 100 Outbound Emails Sent</legend>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>Sent By Module</b></td>
		<td class=\"evener\"><b>Time Sent</b></td>
		<td class=\"evener\"><b>Send Status</b></td>
		<td class=\"evener\"><b>Error Message</b></td>
		<td class=\"evener\"><b>Subject</b></td>
		<td class=\"evener\"><b>Recipients</b></td>
	</tr>";
	while($row = $result->FetchRow()) {
		if(($count%2) == 0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
			<td ".$odd.">".$row['mod_accessed']."</td>
			<td ".$odd.">".$row['time_sent']."</td>
			<td ".$odd.">".$row['send_status']."</td>
			<td ".$odd.">".$row['error_message']."</td>
			<td ".$odd.">".$row['email_subject']."</td>
			<td ".$odd.">".$row['email_recipients']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No emails sent yet..</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
}



/**
 * Generates the Configuration Page and provides the load/save functions for configuration data.
 * @access public
 * @return void
 */
function shn_pop_configuration() {
	global $global;
	shn_pop_first();
	//include_once $global['approot'].'/inc/lib_xajax.inc';
	$posted = 0;
	// if its a post ~ save configuration after we validate
	if(isset($_POST['smtp_reply_address1'])) {
		$posted = 1;
		$errorCount = 0;

		if(!shn_pop_validEmail($_POST['smtp_reply_address1'])) {
			$errorCount++;
			add_error("Please fill in a valid email address for From/Reply-To Email Address.");
		}
		if(($_POST['pop_password1'] == null) || ($_POST['pop_password1'] == "") ) {
			$errorCount++;
			add_error('Please fill in the password for the email address, it cannot be left blank.');
		}
		if(($_POST['smtp_reply_name1'] == null) || ($_POST['smtp_reply_name1'] == "") ) {
			$errorCount++;
			add_error('Please fill in the From/Reply-To Name, it cannot be left blank.');
		}
		if($errorCount == 0 ) {
			add_confirmation('Configuration Saved!');

			if (isset($_POST['smtp_ssl1'])) {
				$smtp_ssl1 = 1;
			} else {
				$smtp_ssl1 = 0;
			}
			if (isset($_POST['smtp_ssl2'])) {
				$smtp_ssl2 = 1;
			} else {
				$smtp_ssl2 = 0;
			}

			if (isset($_POST['smtp_auth1'])) {
				$smtp_auth1 = 1;
			} else {
				$smtp_auth1 = 0;
			}
			if (isset($_POST['smtp_auth2'])) {
				$smtp_auth2 = 1;
			} else {
				$smtp_auth2 = 0;
			}

			if (isset($_POST['smtp_backup2'])) {
				$smtp_backup2 = 1;
			} else {
				$smtp_backup2 = 0;
			}

			// save module configuration
			shn_db_config_update("pop","smtp_reply_address1", $_POST['smtp_reply_address1']);
			shn_db_config_update("pop","smtp_reply_name1",    $_POST['smtp_reply_name1']);
			shn_db_config_update("pop","smtp_host1",          $_POST['smtp_host1']);
			shn_db_config_update("pop","smtp_port1",          $_POST['smtp_port1']);
			shn_db_config_update("pop","smtp_auth1",          $smtp_auth1);
			shn_db_config_update("pop","smtp_ssl1",           $smtp_ssl1);
			shn_db_config_update("pop","pop_username1",       $_POST['pop_username1']);
			shn_db_config_update("pop","pop_password1",       $_POST['pop_password1']);

			shn_db_config_update("pop","smtp_reply_address2", $_POST['smtp_reply_address2']);
			shn_db_config_update("pop","smtp_reply_name2",    $_POST['smtp_reply_name2']);
			shn_db_config_update("pop","smtp_host2",          $_POST['smtp_host2']);
			shn_db_config_update("pop","smtp_port2",          $_POST['smtp_port2']);
			shn_db_config_update("pop","smtp_auth2",          $smtp_auth2);
			shn_db_config_update("pop","smtp_ssl2",           $smtp_ssl2);
			shn_db_config_update("pop","smtp_backup2",        $smtp_backup2);
			shn_db_config_update("pop","pop_username2",       $_POST['pop_username2']);
			shn_db_config_update("pop","pop_password2",       $_POST['pop_password2']);
		} else {
			add_warning('Errors were encountered, configuration not saved.');
		}
	}
	// generate data for form fields
	if ( $posted ) {
		$smtp_host1          = $_POST['smtp_host1'];
		$smtp_port1          = $_POST['smtp_port1'];
		$pop_username1       = $_POST['pop_username1'];
		$pop_password1       = $_POST['pop_password1'];
		$smtp_reply_address1 = $_POST['smtp_reply_address1'];
		$smtp_reply_name1    = $_POST['smtp_reply_name1'];

		$smtp_host2          = $_POST['smtp_host2'];
		$smtp_port2          = $_POST['smtp_port2'];
		$pop_username2       = $_POST['pop_username2'];
		$pop_password2       = $_POST['pop_password2'];
		$smtp_reply_address2 = $_POST['smtp_reply_address2'];
		$smtp_reply_name2    = $_POST['smtp_reply_name2'];


		if (isset($_POST['smtp_ssl1'])) {
			$smtp_ssl1_text = "CHECKED";
		} else {
			$smtp_ssl1_text = "";
		}
		if (isset($_POST['smtp_ssl2'])) {
			$smtp_ssl2_text = "CHECKED";
		} else {
			$smtp_ssl2_text = "";
		}

		if (isset($_POST['smtp_auth1'])) {
			$smtp_auth1_text = "CHECKED";
		} else {
			$smtp_auth1_text = "";
		}
		if (isset($_POST['smtp_auth2'])) {
			$smtp_auth2_text = "CHECKED";
		} else {
			$smtp_auth2_text = "";
		}

		if (isset($_POST['smtp_backup2'])) {
			$smtp_backup2_text = "CHECKED";
		} else {
			$smtp_backup2_text = "";
		}

	} else {
		// function shn_db_get_config($module,$conf_key)
		$smtp_host1          = shn_db_get_config("pop","smtp_host1");
		$smtp_port1          = shn_db_get_config("pop","smtp_port1");
		$smtp_ssl1           = shn_db_get_config("pop","smtp_ssl1");
		$smtp_auth1          = shn_db_get_config("pop","smtp_auth1");
		$pop_username1       = shn_db_get_config("pop","pop_username1");
		$pop_password1       = shn_db_get_config("pop","pop_password1");
		$smtp_reply_address1 = shn_db_get_config("pop","smtp_reply_address1");
		$smtp_reply_name1    = shn_db_get_config("pop","smtp_reply_name1");

		$smtp_host2          = shn_db_get_config("pop","smtp_host2");
		$smtp_port2          = shn_db_get_config("pop","smtp_port2");
		$smtp_ssl2           = shn_db_get_config("pop","smtp_ssl2");
		$smtp_auth2          = shn_db_get_config("pop","smtp_auth2");
		$smtp_backup2        = shn_db_get_config("pop","smtp_backup2");
		$pop_username2       = shn_db_get_config("pop","pop_username2");
		$pop_password2       = shn_db_get_config("pop","pop_password2");
		$smtp_reply_address2 = shn_db_get_config("pop","smtp_reply_address2");
		$smtp_reply_name2    = shn_db_get_config("pop","smtp_reply_name2");

		if ($smtp_ssl1=="1") {
			$smtp_ssl1_text = "CHECKED";
		} else {
			$smtp_ssl1_text = "";
		}
		if ($smtp_ssl2=="1") {
			$smtp_ssl2_text = "CHECKED";
		} else {
			$smtp_ssl2_text = "";
		}

		if ($smtp_auth1=="1") {
			$smtp_auth1_text = "CHECKED";
		} else {
			$smtp_auth1_text = "";
		}
		if ($smtp_auth2=="1") {
			$smtp_auth2_text = "CHECKED";
		} else {
			$smtp_auth2_text = "";
		}

		if ($smtp_backup2=="1") {
			$smtp_backup2_text = "CHECKED";
		} else {
			$smtp_backup2_text = "";
		}
	}
	shn_form_fopen("configuration", null,array('req_message'=>false));
		shn_form_fsopen("Outbound Email Settings");
		?>
<table id="popSettings">
<tr>
	<td>&nbsp;</td>
	<td><b>Primary Email Account</b></td>
	<td><b>Secondary Email Account</b></td>
</tr>
<tr><td><b>Account Credentials</b></td><td colspan=2>&nbsp;</td></tr>
<tr>
	<td class="odd">Account Username</td>
	<td class="odd"><input type="text" name="pop_username1" id="pop_username1" value="<?php echo $pop_username1; ?>" tabindex="1"  /><span class='req'>*</span></td>
	<td class="odd"><input type="text" name="pop_username2" id="pop_username2" value="<?php echo $pop_username2; ?>" tabindex="41" /></td>
</tr>
<tr>
	<td>Account Password</td>
	<td><input type="text" name="pop_password1" id="pop_password1" value="<?php echo $pop_password1; ?>" tabindex="2"  /><span class='req'>*</span></td>
	<td><input type="text" name="pop_password2" id="pop_password2" value="<?php echo $pop_password2; ?>" tabindex="42" /></td>
</tr>
<tr><td colspan=3>&nbsp;</td></tr>
<tr><td><b>Outbound Email Settings</b></td><td colspan=2>&nbsp;</td></tr>
<tr>
	<td class="odd">From/Reply-To Email Address</td>
	<td class="odd"><input size=30 type="text" name="smtp_reply_address1" id="smtp_reply_address1" value="<?php echo $smtp_reply_address1; ?>" tabindex="8"  /><span class='req'>*</span></td>
	<td class="odd"><input size=30 type="text" name="smtp_reply_address2" id="smtp_reply_address2" value="<?php echo $smtp_reply_address2; ?>" tabindex="48" /></td>
</tr>
<tr>
	<td>From/Reply-To Name</td>
	<td><input type="text" name="smtp_reply_name1" id="smtp_reply_name1" value="<?php echo $smtp_reply_name1; ?>" tabindex="9"  /><span class='req'>*</span></td>
	<td><input type="text" name="smtp_reply_name2" id="smtp_reply_name2" value="<?php echo $smtp_reply_name2; ?>" tabindex="49" /></td>
</tr>
<tr>
	<td class="odd">SMTP Server Hostname/IP</td>
	<td class="odd"><input type="text" name="smtp_host1" id="smtp_host1" value="<?php echo $smtp_host1; ?>" tabindex="10"  /><span class='req'>*</span></td>
	<td class="odd"><input type="text" name="smtp_host2" id="smtp_host2" value="<?php echo $smtp_host2; ?>" tabindex="50" /></td>
</tr>
<tr>
	<td>SMTP Server Port</td>
	<td><input type="text" name="smtp_port1" id="smtp_port1" value="<?php echo $smtp_port1; ?>" tabindex="11"  /><span class='req'>*</span></td>
	<td><input type="text" name="smtp_port2" id="smtp_port2" value="<?php echo $smtp_port2; ?>" tabindex="51" /></td>
</tr>
<tr>
	<td class="odd">Use SSL for SMTP?</td>
	<td class="odd"><input type="checkbox" name="smtp_ssl1" id="smtp_ssl1" tabindex="12" <?php echo $smtp_ssl1_text; ?> /></td>
	<td class="odd"><input type="checkbox" name="smtp_ssl2" id="smtp_ssl2" tabindex="52" <?php echo $smtp_ssl2_text; ?> /></td>
</tr>
<tr>
	<td>AUTH before sending Emails via SMTP?</td>
	<td><input type="checkbox" name="smtp_auth1" id="smtp_auth1" tabindex="13" <?php echo $smtp_auth1_text; ?> /></td>
	<td><input type="checkbox" name="smtp_auth2" id="smpt_auth2" tabindex="53" <?php echo $smtp_auth2_text; ?> /></td>
</tr>
<tr>
	<td class="odd">Send emails with Secondary account if Primary fails?</td>
	<td class="odd">&nbsp;</td>
	<td class="odd"><input type="checkbox" name="smtp_backup2" id="smtp_backup2" tabindex="54" <?php echo $smtp_backup2_text; ?> /></td>
</tr>
<tr><td colspan=3>&nbsp;</td></tr>
</table>
		<?php
		shn_form_fsclose();
		shn_form_submit("Save Configuration Settings", $submit_opts = "class=\"styleTehButton\"");
	shn_form_fclose();
	echo "<br><br>";
}






/**
 * Validate an email address.
 * Provide email address (raw input)
 * Returns true if the email address has the email
 * address format and the domain exists.
 * borrowed from: http://goo.gl/ufhg
 */
function shn_pop_validEmail($email) {
	$isValid = true;
	$atIndex = strrpos($email, "@");
	if(is_bool($atIndex) && !$atIndex) {
		$isValid = false;
	} else {
		$domain    = substr($email, $atIndex+1);
		$local     = substr($email, 0, $atIndex);
		$localLen  = strlen($local);
		$domainLen = strlen($domain);
		if($localLen < 1 || $localLen > 64) {
			// local part length exceeded
			$isValid = false;
		} else if($domainLen < 1 || $domainLen > 255) {
			// domain part length exceeded
			$isValid = false;
		} else if($local[0] == '.' || $local[$localLen-1] == '.') {
			// local part starts or ends with '.'
			$isValid = false;
		} else if(preg_match('/\\.\\./', $local)) {
			// local part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain)) {
			// character not valid in domain part
			$isValid = false;
		} else if(preg_match('/\\.\\./', $domain)) {
			// domain part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local))) {
			// character not valid in local part unless
			// local part is quoted
			if (!preg_match('/^"(\\\\"|[^"])+"$/', str_replace("\\\\","",$local))) {
				$isValid = false;
			}
		}
		if($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A"))) {
			// domain not found in DNS
			$isValid = false;
		}
	}
	return $isValid;
}