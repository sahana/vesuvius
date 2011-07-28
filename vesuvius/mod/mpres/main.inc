<?php
/**
 * @name         MPR Email Service
 * @version      1.9
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0728
 */


function shn_mpres_statusGood() {
	global $global;
	$q = "
		SELECT Unix_Timestamp(last_executed)
		FROM mpres_seq ;
	";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$lastExecutedU = $row['Unix_Timestamp(last_executed)'];

	$delta = date("U") - $lastExecutedU;
	if($delta < 120) {
		return true;
	} else {
		return false;
	}
}


function shn_mpres_header2() {
	global $global;

	echo "<ul>";

	if(($_GET['act'] == "status") || ($_GET['act'] == "default")){
		echo "<li>Service Status</li>";
	} else {
		echo "<li><a style=\"font-size: 13px;\" class=\"rezLink\" href=\"index.php?mod=mpres&act=status\">Service Status</a></li>";
	}

	if($_GET['act'] == "configuration") {
		echo "<li>Configuration Options</li>";
	} else {
		echo "<li><a style=\"font-size: 13px;\" class=\"rezLink\" href=\"index.php?mod=mpres&act=configuration\">Configuration Options</a></li>";
	}

	echo "</ul><hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">";
}


/**
 * @access public
 * @return void
 */
function shn_mpres_default() {
	 shn_mpres_status();
}


/**
 * Shows Cron Status as well as the last 100 emails entered...
 * @access public
 * @return void
 */
function shn_mpres_status() {
	global $global;

	shn_mpres_header2();

	$q = "
		SELECT *
		FROM mpres_seq ;
	";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$lastExecuted = $row['last_executed'];

	$q = "
		SELECT Unix_Timestamp(last_executed)
		FROM mpres_seq ;
	";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$lastExecutedU = $row['Unix_Timestamp(last_executed)'];

	$delta = date("U") - $lastExecutedU;

	echo "Cron Job last executed @ <b>".$lastExecuted."</b> or <b>".$delta." seconds</b> ago.<br>";

	if($delta < 120) {
		echo "Cron Status: <span style=\"color: green;\"><b>Nominal</b></span><br><br>";
	} else {
		echo "Cron Status: <span style=\"color: red;\"><b>FAILURE</b></span><br><br>";
	}


	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Last 10 Emails Received...</legend>";
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
		LIMIT 0 , 10;
	";
	$res = $global['db']->Execute($q);
	while($row = $res->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd."><a href=\"https://".$row['p_uuid']."\">".$row['p_uuid']."</a></td>
				<td ".$odd.">".$row['email_from']."</td>
				<td ".$odd.">".$row['email_subject']."</td>
				<td ".$odd.">".$row['update_time']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=4 class=\"odder\">No MPRES Emails Received So Far!</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}


/**
 * Generates the Configuration Page and provides the load/save functions for configuration data.
 * @access public
 * @return void
 */
function shn_mpres_configuration() {
	global $global;

	shn_mpres_header2();

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
			if (isset($_POST['mpres_delete_messages'])) {
				$delete_messages = 1;
			} else {
				$delete_messages = 0;
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
			shn_db_config_update("mpres","username",       $_POST['mpres_username']);
			shn_db_config_update("mpres","password",       $_POST['mpres_password']);
			shn_db_config_update("mpres","attachments",    $_POST['mpres_attachments']);
			shn_db_config_update("mpres","incident_id",    $_POST['mpres_incident_id']);
			shn_db_config_update("mpres","delete_messages",$delete_messages);
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
		$attachments = $_POST['mpres_attachments'];
		$incident_id = $_POST['mpres_incident_id'];
		if (isset($_POST['mpres_ssl'])) {
			$sslText = "CHECKED";
		} else {
			$sslText = "";
		}
		if (isset($_POST['mpres_delete_messages'])) {
			$deleteMessagesText = "CHECKED";
		} else {
			$deleteMessagesText = "";
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
		$username        = shn_db_get_config("mpres","username");
		$password        = shn_db_get_config("mpres","password");
		$attachments     = shn_db_get_config("mpres","attachments");
		$incident_id     = shn_db_get_config("mpres","incident_id");
		$delete_messages = shn_db_get_config("mpres","delete_messages");
		if ($ssl=="1") {
			$sslText = "CHECKED";
		} else {
			$sslText = "";
		}
		if ($delete_messages=="1") {
			$deleteMessagesText = "CHECKED";
		} else {
			$deleteMessagesText = "";
		}
		if ( $popimap == "POP") {
			$popimapOption = "POP";
		} else {
			$popimapOption = "IMAP";
		}
	}
	shn_form_fopen("configuration", null,array('req_message'=>true));
		shn_form_fsopen("POP/IMAP server");
			shn_form_text("Host or IP (ie. mail.google.com)","mpres_host",null,array("req"=>true,"value"=>$host));
			shn_form_text("Port (ie. 110 or 993,995 for SSL)","mpres_port",null,array("req"=>true,"value"=>$port));
			shn_form_radio(array("POP"=>"POP","IMAP"=>"IMAP"),"Use POP or IMAP protocol","mpres_popimap", null, array("value"=>$popimapOption));
			shn_form_checkbox("Use SSL", "mpres_ssl", $text_opts = $sslText, $extra_opts = null);
		shn_form_fsclose();

		shn_form_fsopen("Email Account");
			shn_form_text("Username","mpres_username",null,array("req"=>true,"value"=>$username));
			shn_form_password("Password","mpres_password",null,array("req"=>true,"value"=>$password));
		shn_form_fsclose();

		shn_form_fsopen("Attachments");
			shn_form_text("Number of image attachments to allow in each email (1-20)","mpres_attachments",null,array("req"=>true,"value"=>$attachments));
		shn_form_fsclose();

		shn_form_fsopen("Event");
			shn_mpres_incident_select($incident_id);
		shn_form_fsclose();

		shn_form_fsopen("Inbox Options");
			shn_form_checkbox("Delete Emails After Download", "mpres_delete_messages", $text_opts = $deleteMessagesText, $extra_opts = null);
		shn_form_fsclose();

		shn_form_submit("Save Configuration Settings", "class=\"styleTehButton\"");
	shn_form_fclose();
	echo "<br><br>";
}



/**
 *
 */
function shn_mpres_incident_select($incident_id){
	global $global;
	?> <label for="mpres_incident">The event chosen here will be assigned to all persons reported using unstructured emails.</label><select name="mpres_incident_id"><?php
	$query1 = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
	$result1 = $global['db']->Execute($query1);
	while($row1 = $result1->FetchRow()){
		?><option value="<?php echo $row1['incident_id'];?>"  <?php echo ($incident_id==$row1['incident_id']?'selected="selected"':'');?> >&nbsp;&nbsp;&nbsp;<?php echo $row1['name'];?></option><?php
		$query2 = "SELECT incident_id, name FROM incident WHERE parent_id = '".$row1['incident_id']."';";
		$result2 = $global['db']->Execute($query2);
		while($row2 = $result2->FetchRow() ){
			?><option value="<?php echo $row2['incident_id'];?>"  <?php echo ($incident_id==$row2['incident_id']?'selected="selected"':'');?>  >&nbsp;&nbsp;&#8211;&nbsp;<?php echo $row2['name'];?></option><?php
			$query3 = "SELECT incident_id, name FROM incident WHERE parent_id = '".$row2['incident_id']."'";
			$result3 = $global['db']->Execute($query3);
			while($row3 = $result3->FetchRow() ){
				?><option value="<?php echo $row3['incident_id'];?>"  <?php echo ($incident_id==$row3['incident_id']?'selected="selected"':'');?>  >&nbsp;&nbsp;&nbsp;&nbsp;&#8211;&nbsp;<?php echo $row3['name'];?></option><?php
			}
		}
	}
	?></select><?php
}