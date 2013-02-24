<?php
/**
 * @name         MPR Email Service
 * @version      21
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */


global $tabid;
$tabid = isset($_GET['tabid']) ? $_GET['tabid'] : 0;
$tabid = "&tabid=".$tabid;


/** for mainmenu to figure out which status color to show */
function shn_mpres_statusGood() {

	global $global;
	$q = "
		SELECT Unix_Timestamp(last_executed)
		FROM mpres_seq ;
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres status good"); }
	$row = $res->FetchRow();
	$lastExecutedU = $row['Unix_Timestamp(last_executed)'];

	$delta = date("U") - $lastExecutedU;
	if($delta < 120) {
		return true;
	} else {
		return false;
	}
}


function shn_mpres_default() {

	global $global;

	$control = "";

	shn_tabmenu_open();
	shn_tabmenu_item("stat",          _t("Mpres-Text|Service Status"),  "inbound");
	shn_tabmenu_item("log",           _t("Mpres-Text|People Reported"), "inbound");
	shn_tabmenu_item("configuration", _t("Mpres-Text|Configuration"),   "inbound");
	shn_tabmenu_close();

	if(isset($_GET['log'])) {
		$control = "shn_mpres_log";

	} elseif(isset($_GET['configuration'])) {
		$control = "shn_mpres_configuration";

	} elseif(isset($_GET['purgeEvents'])) {
		$control = "shn_mpres_purgeEvents";

	} elseif(isset($_GET['purgeReports'])) {
		$control = "shn_mpres_purgeReports";

	} else {
		$control = "shn_mpres_status";
	}
	$control();
}



/** Shows Cron Status as well as the last 100 emails entered... */
function shn_mpres_status() {

	global $global;

	$count = 0;

	$q = "
		SELECT *
		FROM mpres_seq ;
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres status 1"); }
	$row = $res->FetchRow();

	$lastExecuted = $row['last_executed'];
	$lastMessage  = $row['last_message'];

	$q = "
		SELECT Unix_Timestamp(last_executed)
		FROM mpres_seq ;
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres status 2"); }
	$row = $res->FetchRow();

	$lastExecutedU = $row['Unix_Timestamp(last_executed)'];

	$delta = date("U") - $lastExecutedU;

	if($delta < 120) {
		$statusMsg = "Cron Status: <span style=\"color: green;\"><b>Nominal</b></span>";
	} else {
		$statusMsg = "Cron Status: <span style=\"color: red;\"><b>FAILURE</b></span>";
	}

	echo '
		<br>
		<div class="form-container">
			<form>
				<fieldset>
					<legend>Daemon Status</legend>
					Cron Job last executed @ <b>'.$lastExecuted.'</b> or <b>'.$delta.' seconds</b> ago.<br>
					'.$statusMsg.'<br>
					<hr>
					<b>Last Message:</b><br>
					'.$lastMessage.'
				</fieldset>
			</form>
		</div>
	';

	// figure out log traversal navigation....

	if(isset($_GET['pagenum'])) {

		$startPoint = (int)$_GET['pagenum']*100;
		$endPoint = $startPoint + 100;
		$msg = "showing executions ".($startPoint+1)." to ".$endPoint;

	} else {
		$startPoint = 0;
		$endPoint = $startPoint + 100;
		$msg = "showing last 100";
	}

	if(isset($_GET['pagenum']) && (int)$_GET['pagenum'] > 0) {
		$previous = "<a href=\"inbound?status&pagenum=".((int)$_GET['pagenum']-1)."\">◄</a>";

	} else {
		$previous = "◄";
		$_GET['pagenum'] = 0;
	}

	$q = "
		SELECT count(*)
		FROM `mpres_messages`;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres status 3"); }
	$row = $result->FetchRow();

	$totalCount = $row['count(*)'];

	if($endPoint < $totalCount) {
		$next = "<a href=\"inbound?status&pagenum=".($_GET['pagenum']+1)."\">►</a>";
	} else {
		$next = "►";
		$msg = "showing ".($startPoint+1)." to ".$totalCount;
	}

	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Email Event Log (".$msg." of ".$totalCount." total) ".$previous." ".$next."</legend>";
	echo "<a href=\"inbound?purgeEvents\"><span class=\"styleTehButton\">Purge the Event Log</span></a> (<i>this action is audited</i>)<br><br>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener left\"><b>Time</b></td>
		<td class=\"evener left\"><b>Messages</b></td>
	</tr>";
	$q = "
		SELECT *
		FROM  `mpres_messages`
		ORDER BY  `when` DESC
		LIMIT ".$startPoint.", 100;
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres status 4"); }

	while($row = $res->FetchRow()) {

		if(($count%2)==0) {
			$odd = "class=\"odder left\"";
		} else {
			$odd = "class=\"evener left\"";
		}
		echo "  <tr>
				<td ".$odd."> &nbsp; &nbsp; ".$row['when']."</td>
				<td ".$odd.">".$row['messages']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=2 class=\"odder\">No emails so far!</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
}



/** Truncates the Event Log */
function shn_mpres_purgeEvents() {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$db = $global["db"];

	shn_acl_log_msg("Purged the MPRES Email Event Log", $_SESSION['user_p_uuid'], $_SESSION['user_name'], "LOG PURGE");

	$q = "
		TRUNCATE mpres_messages ;
	";
	$res = $db->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres event log purge (".$q.")"); }

	add_confirmation("Email Event Log purged.");

	shn_mpres_status();
}


/** Truncates the Report Log */
function shn_mpres_purgeReports() {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");
	$db = $global["db"];

	shn_acl_log_msg("Purged the MPRES Emails Received Log", $_SESSION['user_p_uuid'], $_SESSION['user_name'], "LOG PURGE");

	$q = "
		TRUNCATE mpres_log ;
	";
	$res = $db->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres emails recieved log purge (".$q.")"); }

	add_confirmation("Emails Recieved Log purged.");

	shn_mpres_log();
}



/** Shows Cron Status as well as the last 100 emails entered... */
function shn_mpres_log() {

	global $conf;
	global $global;

	$count = 0;

	// figure out log traversal navigation....

	if(isset($_GET['pagenum'])) {
		$startPoint = (int)$_GET['pagenum']*100;
		$endPoint = $startPoint + 100;
		$msg = "showing emails ".($startPoint+1)." to ".$endPoint;
	} else {
		$startPoint = 0;
		$endPoint = $startPoint + 100;
		$msg = "showing last 100";
	}

	if(isset($_GET['pagenum']) && (int)$_GET['pagenum'] > 0) {
		$previous = "<a href=\"inbound?log&pagenum=".((int)$_GET['pagenum']-1)."\">◄</a>";
	} else {
		$previous = "◄";
	}

	$q = "
		SELECT count(*)
		FROM `mpres_log`;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres log 1"); }
	$row = $result->FetchRow();
	$totalCount = $row['count(*)'];

	if($endPoint < $totalCount) {
		$next = "<a href=\"inbound?log&pagenum=".($_GET['pagenum']+1)."\">►</a>";
	} else {
		$next = "►";
		$msg = "showing emails ".($startPoint+1)." to ".$totalCount;
	}

	echo "<br><div class=\"form-container\"><form><fieldset>";
	echo "<legend>Emails Received (".$msg." of ".$totalCount." total) ".$previous." ".$next."</legend>";
	echo "<a href=\"inbound?purgeReports&tabid=1\"><span class=\"styleTehButton\">Purge the Emails Received Log</span></a> (<i>this action is audited</i>)<br><br>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>Record Identifier / p_uuid</b></td>
		<td class=\"evener\"><b>Email From</b></td>
		<td class=\"evener\"><b>Email Subject</b></td>
		<td class=\"evener\"><b>Time</b></td>
	</tr>";
	$q = "
		SELECT *
		FROM  `mpres_log`
		ORDER BY  `mpres_log`.`update_time` DESC
		LIMIT ".$startPoint.", 100;
	";
	$res = $global['db']->Execute($q);
	if($res === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres log 2"); }
	while($row = $res->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd."><a href=\"".$conf['https'].$row['p_uuid']."\">".$row['p_uuid']."</a></td>
				<td ".$odd.">".$row['email_from']."</td>
				<td ".$odd.">".$row['email_subject']."</td>
				<td ".$odd.">".$row['update_time']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=4 class=\"odder\">No emails received so far!</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
}




/** Generates the Configuration Page and provides the load/save functions for configuration data. */
function shn_mpres_configuration() {

	global $global;
	global $tabid;

	$posted = 0;
	// if its a post ~ save configuration after we validate
	if(isset($_POST['mpres_port'])) {
		$posted = 1;
		$errorCount = 0;

		if ( ($_POST['mpres_password'] == null) || ($_POST['mpres_password'] == "") ) {
			$errorCount++;
			add_error('Please fill in the password for the email address, it cannot be left blank.');
		}
		if ( $errorCount == 0 ) {
			add_confirmation('Configuration Saved!');
			if (isset($_POST['mpres_ssl'])) {
				$ssl = 1;
			} else {
				$ssl = 0;
			}
			if ( isset($_POST['mpres_popimap']) && $_POST['mpres_popimap'] == "POP") {
				$popimap = "POP";
			} else {
				$popimap = "IMAP";
			}
			// save module configuration
			shn_db_config_update("mpres","host",           $_POST['mpres_host']);
			shn_db_config_update("mpres","port",           $_POST['mpres_port']);
			shn_db_config_update("mpres","popimap",        $popimap);
			shn_db_config_update("mpres","ssl",            $ssl);
			shn_db_config_update("mpres","username",       htmlspecialchars_decode($_POST['mpres_username']));
			shn_db_config_update("mpres","password",       htmlspecialchars_decode($_POST['mpres_password']));
			shn_db_config_update("mpres","incident_id",    $_POST['mpres_incident_id']);
		} else {
			add_warning('Errors were encountered, configuration not saved.');
		}
	}
	// generate data for form fields
	if ( $posted ) {
		$host        = $_POST['mpres_host'];
		$port        = $_POST['mpres_port'];
		$username    = $_POST['mpres_username'];
		$password    = $_POST['mpres_password'];
		$incident_id = $_POST['mpres_incident_id'];
		if (isset($_POST['mpres_ssl'])) {
			$sslText = "CHECKED";
		} else {
			$sslText = "";
		}
		if (isset($_POST['mpres_popimap']) && $_POST['mpres_popimap'] == "POP") {
			$popimapOption = "POP";
		} else {
			$popimapOption = "IMAP";
		}
	} else {
		// function shn_db_get_config($module,$conf_key)
		$host            = shn_db_get_config("mpres","host");
		$popimap         = shn_db_get_config("mpres","popimap");
		$port            = shn_db_get_config("mpres","port");
		$ssl             = shn_db_get_config("mpres","ssl");
		$username        = htmlspecialchars(shn_db_get_config("mpres","username"));
		$password        = htmlspecialchars(shn_db_get_config("mpres","password"));
		$incident_id     = shn_db_get_config("mpres","incident_id");
		if ($ssl=="1") {
			$sslText = "CHECKED";
		} else {
			$sslText = "";
		}
		if ( $popimap == "POP") {
			$popimapOption = "POP";
		} else {
			$popimapOption = "IMAP";
		}
	}
	shn_form_fopen2("inbound?configuration".$tabid, null, array('req_message'=>true));
		shn_form_fsopen("POP / IMAP Settings");
			shn_form_text("Host or IP (ie. mail.google.com)", "mpres_host", null, array("req"=>true, "value"=>$host));
			shn_form_text("Port (ie. 110 or 993,995 for SSL)", "mpres_port",null, array("req"=>true, "value"=>$port));
			shn_form_radio(array("POP"=>"POP", "IMAP"=>"IMAP"), "Use POP or IMAP protocol", "mpres_popimap", null, array("value"=>$popimapOption));
			shn_form_checkbox("Use SSL", "mpres_ssl", $text_opts = $sslText, $extra_opts = null);
		shn_form_fsclose();

		shn_form_fsopen("Email Account Credentials");
			shn_form_text("Username", "mpres_username", 'size=40', array("req"=>true, "value"=>$username));
			shn_form_text("Password", "mpres_password", 'size=40', array("req"=>true, "value"=>$password));
		shn_form_fsclose();

		shn_form_fsopen("Default Event");
			shn_mpres_incident_select($incident_id);
		shn_form_fsclose();
		echo "<br>";
		shn_form_submit("Save Configuration Settings", "class=\"styleTehButton\"");
	shn_form_fclose();
	echo "<br><br>";
}



/** generates the incident select box */
function shn_mpres_incident_select($incident_id) {

	global $global;

	echo '
		<label for="mpres_incident">The event selected here will be used for persons reported using unstructured emails.</label><select name="mpres_incident_id">
	';

	$q1 = "
		SELECT incident_id, name
		FROM incident
		WHERE parent_id IS NULL ;
	";
	$r1 = $global['db']->Execute($q1);
	if($r1 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres incident select 1"); }
	while($row1 = $r1->FetchRow()) {

		echo '
			<option value="'.$row1['incident_id'].'"  '.($incident_id == $row1['incident_id'] ? 'selected="selected"' : '').'>&nbsp;&nbsp;&nbsp;'.$row1['name'].'</option>
		';
		$q2 = "
			SELECT incident_id, name
			FROM incident
			WHERE parent_id = '".$row1['incident_id']."';
		";
		$r2 = $global['db']->Execute($q2);
		if($r2 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres incident select 2"); }
		while($row2 = $r2->FetchRow()) {

			echo '
				<option value="'.$row2['incident_id'].'" '.($incident_id == $row2['incident_id'] ? 'selected="selected"' : '').'>&nbsp;&nbsp;&#8211;&nbsp;'.$row2['name'].'</option>
			';
			$q3 = "
				SELECT incident_id, name
				FROM incident
				WHERE parent_id = '".$row2['incident_id']."' ;
			";
			$r3 = $global['db']->Execute($q3);
			if($r3 === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "mpres incident select 3"); }
			while($row3 = $r3->FetchRow()) {

				echo '
					<option value="'.$row3['incident_id'].'" '.($incident_id == $row3['incident_id'] ? 'selected="selected"' : '').'>&nbsp;&nbsp;&nbsp;&nbsp;&#8211;&nbsp;'.$row3['name'].'</option>
				';
			}
		}
	}
	echo '
		</select>
	';
}


