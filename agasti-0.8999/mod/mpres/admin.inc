<?php
/**
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @package      module
 * @subpackage   mpres
 * @version      1.6
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2010.1124
 */


/**
 * Default Admin function
 *
 * @access public
 * @return void
 */
function shn_mpres_adm_default() {
	global $global;
	?><h2>Missing Person Registry Email Service Settings</h2>
		<p><?= _t('The MPR (Missing Person Registry) Email Service is a tool to allow people to report missing persons via email.'); ?></p><br></br>
		<div>
			<h3><b><em><?= (_t("Features Include:")) ?></em></b></h3>
		</div>
		<br></br>
		<ul>
			<li><?= _t('Downloads Missing Person data that has been submitted to an email account via POP/IMAP'); ?></li>
			<li><?= _t('Extracts and parses the missing person\'s name from the subject line of an email (can be in various formats)'); ?></li>
			<li><?= _t('Parses the email body for image attachments and downloads them into a temporary location'); ?></li>
			<li><?= _t('Allows a user with sufficient priviledges the ability to import (or delete) downloaded email submissions into the MPR'); ?></li>
			<li><i><?= _t('Accepts MPR requests from other applications in an XML format (todo: future component)'); ?></i></li>
		</ul>
		<strong><? echo _t("Description of Actions:"); ?></strong><br/>
		<ul>
			<li><a href="index.php?mod=mpres&act=adm_configuration"><b><?= _t('Configuration Settings'); ?> </b></a><br/><?= _t('Configure the settings specific to the email account gathering MPR data.'); ?></li>
			<li><a href="index.php?mod=mpres&act=adm_log"><b><?= _t('Check Email Import Log'); ?> </b> </a><br/><?= _t('Check the log/remove entries that have been committed to the Missing Person Registry'); ?></li>
		</ul>
		<br/>
	<?
}


/**
 * Generates the Configuration Page and provides the load/save functions for configuration data.
 * @access public
 * @return void
 */
function shn_mpres_adm_configuration() {
	global $global;
	include_once $global['approot'].'/inc/lib_xajax.inc';

	echo "<h2>MPR Email Service Settings</h2>";
	$posted = 0;
	// if its a post ~ save configuration after we validate
	if(isset($_POST['mpres_port'])) {
		$posted = 1;
		$errorCount = 0;

		// ereg deprecated... so commented out below validation code until someone updates it with preg_match()
		/*
		$validIpAddressRegex = "^([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";
		$validHostnameRegex = "^([A-z0-9][-A-z0-9]+\.)+[A-z]{2,4}$";
		$validPortRegex = "^([1-9]|[1-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-5][0-9][0-9][0-9][0-9]|[6][0-5][0-4][0-9][0-9]|[6][5][5][0-3][0-5])$";
		$validUsernameRegex = "^[\x20-\x2D\x2F-\x7E]+(\.[\x20-\x2D\x2F-\x7E]+)*$"; // @(([a-z0-9]([-a-z0-9]*[a-z0-9]+)?){1,63}\.)+[a-z0-9]{2,6}$";
		$validAttachmentsRegex = "^([1-9]|1[0-9]|20)$";

		if ( !ereg($validIpAddressRegex, $_POST['mpres_host']) && !ereg($validHostnameRegex, $_POST['mpres_host']) ) {
			$errorCount++;
			add_error("Please fill in a valid hostname or ip address for the mail server, <b>".$_POST['mpres_host']."</b> is not valid.");
		}
		if ( !ereg($validPortRegex, $_POST['mpres_port']) ) {
			$errorCount++;
			add_error("Please fill in a valid port for the mail server, (ie. 110 or 995) because <b>".$_POST['mpres_port']."</b> is not valid.");
		}
		if ( !ereg($validUsernameRegex, $_POST['mpres_username']) ) {
			$errorCount++;
			add_error("Please fill in the username for the email address,  (ie. bob@aol.com would be: bob) because <b>".$_POST['mpres_username']."</b> is not valid.");
		}
		if ( !ereg($validAttachmentsRegex, $_POST['mpres_attachments']) ) {
			$errorCount++;
			add_error("Please fill in a digit corresponding the the number of image attachments to parse out of emails (1-20), <b>".$_POST['mpres_attachments']."</b> is not valid.");
		}
		*/
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
	shn_form_fopen("adm_configuration", null,array('req_message'=>true));
		shn_form_fsopen("POP/IMAP server");
			shn_form_text("Host or IP (ie. mail.google.com)","mpres_host",null,array("req"=>true,"value"=>$host)); // , "help"=>"testing help0"));
			shn_form_text("Port (ie. 110 or 993,995 for SSL)","mpres_port",null,array("req"=>true,"value"=>$port));
			shn_form_radio(array("POP"=>"POP","IMAP"=>"IMAP"),"Use POP or IMAP protocol","mpres_popimap", null, array("value"=>$popimapOption));
			shn_form_checkbox("Use SSL", "mpres_ssl", $text_opts = $sslText, $extra_opts = null);
		shn_form_fsclose();

		shn_form_fsopen("Email Account");
			shn_form_text("Username","mpres_username",null,array("req"=>true,"value"=>$username));
			shn_form_password("Password","mpres_password",null,array("req"=>true,"value"=>$password)); //, "help"=>"testing help"));
		shn_form_fsclose();

		shn_form_fsopen("Attachments");
			shn_form_text("Number of image attachments to allow in each email (1-20)","mpres_attachments",null,array("req"=>true,"value"=>$attachments));
		shn_form_fsclose();

		shn_form_fsopen("Incident");
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
 * This is the action we perform that will poll the email account and import data into MPR
 * @access public
 * @return void
 */
function shn_mpres_import_data(){
	echo "cool";
	//mpres_lib_import_data();
}



/**
 *
 */
function shn_mpres_incident_select($incident_id){
	global $global;
	?> <label for="mpres_incident">This is the incident new persons will be assigned to</label><select name="mpres_incident_id"><?php
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