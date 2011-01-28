<?php
/**
 * This is the conf file for the PLS module.
 *
 * This module provides "Person Locator Services" and is a web services only module.
 *
 * PHP version 5.2+ (compiled with imap support)
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Greg Miernicki
 * @package	module
 * @subpackage	pls
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 *


/**
 * Default function
 *
 * @access public
 * @return void
 */
function shn_pls_default() {
	shn_pls_configuration();
}




function shn_pls_submissionLog() {
	global $global;
	echo "
			<h2>
			<a href=\"index.php?mod=pls&act=rawLog\">View the Access Log</a> ::
			<i>View the Submission Log</i> ::
			<a href=\"index.php?mod=pls&act=configuration\">Change Settings</a>
			</h2>
	";
	echo "
		TODO<br>
	";
}




function shn_pls_rawLog() {
	global $global;
	echo "<div id=\"home\">";
	echo "
			<h2>
			<i>View the Access Log</i> ::
			<a href=\"index.php?mod=pls&act=submissionLog\">View the Submission Log</a> ::
			<a href=\"index.php?mod=pls&act=configuration\">Change Settings</a>
			</h2>
	";
	$query  = "
		SELECT *
		FROM pls_access_log
		ORDER BY access_time DESC
		LIMIT 100;
	";
	$result = $global['db']->Execute($query);
	$count = 0;
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Accesses:</legend>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>Time</b></td>
		<td class=\"evener\"><b>Application</b></td>
		<td class=\"evener\"><b>Version</b></td>
		<td class=\"evener\"><b>IP</b></td>
		<td class=\"evener\" style=\"text-align: left;\"><b>Call</b></td>
	</tr>";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd.">".$row['access_time']."</td>
				<td ".$odd.">".$row['application']."</td>
				<td ".$odd.">".$row['version']."</td>
				<td ".$odd.">".$row['ip']."</td>
				<td ".$odd." style=\"text-align: left;\">".$row['call']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Service Calls Yet!</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}


function shn_pls_configuration() {
	global $global;
	include_once $global['approot'].'/inc/lib_xajax.inc';

	echo "
			<h2>
			<a href=\"index.php?mod=pls&act=rawLog\">View the Access Log</a> ::
			<a href=\"index.php?mod=pls&act=submissionLog\">View the Submission Log</a> ::
			<i>Change Settings</i>
			</h2>
	";

	$posted = 0;
	// if its a post ~ save configuration after we validate
	if(isset($_POST['timeout'])) {
		$posted = 1;
		$errorCount = 0;
		$t = (int)$_POST['timeout'];
		if(($t < 600) || ($t > 315360000)) {
			$errorCount++;
			add_error("Please use a positive integer value for the timeout in seconds (between 600 and 315,360,000 ~10 minutes to 10 years).");
		}
		if($errorCount == 0 ) {
			add_confirmation('Configuration Saved!');
			shn_db_config_update("pls","timeout",  $_POST['timeout']);
		} else {
			add_warning('Errors were encountered, configuration not saved.');
		}
	}
	$timeout = "";
	if ( $posted ) {
		$timeout = $_POST['timeout'];
	} else {
		$timeout = shn_db_get_config("pls","timeout");
	}

	// newly visited... option not yet set, so set and save
	if($timeout == "") {
		$timeout = 864000; // 100 days default
		shn_db_config_update("pls","timeout",  $timeout);
	}

	shn_form_fopen("configuration", null,array('req_message'=>true));
		shn_form_fsopen("Settings for PLS");
		?>
		<table id="popSettings">
		<tr>
			<td class="odd">Session Timeout (in seconds)</td>
			<td class="odd"><input type="text" name="timeout" id="timeout" value="<?php echo $timeout; ?>" tabindex="1"  /><span class='req'>*</span></td>
		</tr>
		</table>
		<?php
		shn_form_fsclose();
		shn_form_submit("Save Settings", $submit_opts = "class=\"styleTehButton\"");
	shn_form_fclose();
}



