<?
/**
 * @name         PL User Services
 * @version      1.9.3
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0621
 */


function shn_plus_default() {
	shn_plus_rawLog();
}



function shn_plus_header2() {
	global $global;
	echo "<ul>";

	if($global['action'] == "configuration") {
		echo "<li>Change Settings</li>";
	} else {
		echo "<li><a href=\"index.php?mod=plus&act=configuration\">Change Settings</a></li>";
	}
	if($global['action'] == "rawLog" || $global['action'] == "default") {
		echo "<li>View the Access Log</li>";
	} else {
		echo "<li><a href=\"index.php?mod=plus&act=rawLog\">View the Access Log</a></li>";
	}
	echo "</ul>";
}




function shn_plus_submissionLog() {
	shn_plus_header2();
	echo "
		TODO<br>
	";
}




function shn_plus_rawLog() {
	global $global;
	shn_plus_header2();

	echo "<div id=\"home\">";
	$query  = "
		SELECT *
		FROM plus_access_log
		ORDER BY access_time DESC
		LIMIT 100;
	";
	$result = $global['db']->Execute($query);
	$count = 0;
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Raw Access Log</legend>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>Time</b></td>
		<td class=\"evener\"><b>Application</b></td>
		<td class=\"evener\"><b>Version</b></td>
		<td class=\"evener\"><b>IP</b></td>
		<td class=\"evener\" style=\"text-align: left;\"><b>Call</b></td>
		<td class=\"evener\"><b>apiVersion</b></td>
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
				<td ".$odd.">".$row['api_version']."</td>
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


function shn_plus_configuration() {
	global $global;
	require_once($global['approot'].'/inc/lib_xajax.inc');
	shn_plus_header2();

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
			shn_db_config_update("plus","timeout",  $_POST['timeout']);
		} else {
			add_warning('Errors were encountered, configuration not saved.');
		}
	}
	$timeout = "";
	if ( $posted ) {
		$timeout = $_POST['timeout'];
	} else {
		$timeout = shn_db_get_config("plus","timeout");
	}

	// newly visited... option not yet set, so set and save
	if($timeout == "") {
		$timeout = 864000; // 100 days default
		shn_db_config_update("plus","timeout",  $timeout);
	}

	shn_form_fopen("configuration", null,array('req_message'=>true));
		shn_form_fsopen("Settings for PLUS");
		?>
		<table id="popSettings">
		<tr>
			<td class="odd">Session Timeout (in seconds)</td>
			<td class="odd"><input type="text" name="timeout" id="timeout" value="<?php echo $timeout; ?>" tabindex="1"  /><span class='req'>*</span></td>
		</tr>
		</table>
		<br><br>
		<?php
		shn_form_submit("Save Settings", $submit_opts = "class=\"styleTehButton\"");
		shn_form_fsclose();
	shn_form_fclose();
}



