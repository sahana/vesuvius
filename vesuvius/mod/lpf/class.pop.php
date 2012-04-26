<?php
/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        pop
* @version      11
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class pop {

	private $pop_host;
	private $pop_port;
	private $pop_popimap;
	private $pop_ssl;
	private $pop_cron;
	private $smtp_host;
	private $smtp_port;
	private $smtp_ssl;
	private $smtp_auth;
	private $smtp_backup2;
	private $pop_username;
	private $pop_password;
	private $smtp_reply_address;

	private $attachments;
	private $incident_id;
	private $delete_messages;

	private $serverString;
	private $mailbox;
	private $mailboxHeader;
	private $mailboxOpen;
	private $messageCount;
	private $currentMessage;
	private $currentAttachment;

	private $person;

	public  $messages;  // execution message queue
	public  $startTime; // timestamp of when an object of this type is instantiated

	public  $sentStatus;


	/**
	* Constructor:
	* Setup the object, initialise the variables
	* @access public
	*/
	public function __construct($use="PRIMARY") {

		if ($use == "PRIMARY") {
			// get configuration settings
			$this->pop_host           = shn_db_get_config("pop","pop_host1");
			$this->pop_port           = shn_db_get_config("pop","pop_port1");
			$this->pop_popimap        = shn_db_get_config("pop","pop_popimap1");
			$this->pop_ssl            = shn_db_get_config("pop","pop_ssl1");
			$this->pop_cron           = shn_db_get_config("pop","pop_cron1");
			$this->smtp_host          = shn_db_get_config("pop","smtp_host1");
			$this->smtp_port          = shn_db_get_config("pop","smtp_port1");
			$this->smtp_ssl           = shn_db_get_config("pop","smtp_ssl1");
			$this->smtp_auth          = shn_db_get_config("pop","smtp_auth1");
			$this->username           = shn_db_get_config("pop","pop_username1");
			$this->password           = shn_db_get_config("pop","pop_password1");
			$this->smtp_backup2       = shn_db_get_config("pop","smtp_backup2");
			$this->smtp_reply_address = shn_db_get_config("pop","smtp_reply_address1");
		} else {
			$this->pop_host           = shn_db_get_config("pop","pop_host2");
			$this->pop_port           = shn_db_get_config("pop","pop_port2");
			$this->pop_popimap        = shn_db_get_config("pop","pop_popimap2");
			$this->pop_ssl            = shn_db_get_config("pop","pop_ssl2");
			$this->pop_cron           = shn_db_get_config("pop","pop_cron2");
			$this->smtp_host          = shn_db_get_config("pop","smtp_host2");
			$this->smtp_port          = shn_db_get_config("pop","smtp_port2");
			$this->smtp_ssl           = shn_db_get_config("pop","smtp_ssl2");
			$this->smtp_auth          = shn_db_get_config("pop","smtp_auth2");
			$this->username           = shn_db_get_config("pop","pop_username2");
			$this->password           = shn_db_get_config("pop","pop_password2");
			$this->smtp_backup2       = shn_db_get_config("pop","smtp_backup2");
			$this->smtp_reply_address = shn_db_get_config("pop","smtp_reply_address2");
		}

		$this->messages          = "scriptExecutedAtTime >> ".date("Ymd:Gis.u")."\n";
		$this->startTime         = microtime(true);
		$this->stopTime          = null;
		$this->messageCount      = 0;
		$this->currentAttachment = null;
		$this->mailboxOpen       = FALSE;
		$this->delete_messages   = TRUE;
		$this->sentStatus        = FALSE;
	}



	/**
	* Destructor
	*/
	public function __destruct() {

		if ($this->mailboxOpen) {
			// purge and close inbox
			if ($this->delete_messages) {
				imap_expunge($this->mailbox);
			}
			imap_close($this->mailbox);
		}
	}



	/**
	* Reloads the config values from the backup server.
	* @access public
	*/
	public function reloadBackupConfig() {

		$this->pop_host           = shn_db_get_config("pop","pop_host2");
		$this->pop_port           = shn_db_get_config("pop","pop_port2");
		$this->pop_popimap        = shn_db_get_config("pop","pop_popimap2");
		$this->pop_ssl            = shn_db_get_config("pop","pop_ssl2");
		$this->pop_cron           = shn_db_get_config("pop","pop_cron2");
		$this->smtp_host          = shn_db_get_config("pop","smtp_host2");
		$this->smtp_port          = shn_db_get_config("pop","smtp_port2");
		$this->smtp_ssl           = shn_db_get_config("pop","smtp_ssl2");
		$this->smtp_auth          = shn_db_get_config("pop","smtp_auth2");
		$this->username           = shn_db_get_config("pop","pop_username2");
		$this->password           = shn_db_get_config("pop","pop_password2");
		$this->smtp_reply_address = shn_db_get_config("pop","smtp_reply_address2");
	}



	/**
	* Sends an Email to a recipient.
	*/
	public function sendMessage($toEmail, $toName, $subject, $bodyHTML, $bodyAlt) {

		global $global;
		global $conf;

		$messageLog = "";
		$sendStatus = "";
		require_once($global['approot']."3rd/phpmailer/class.phpmailer.php");

		try {
			$mail = new PHPMailer(true);  // true=enable exceptions

			$mail->IsSMTP();
			$mail->SMTPAuth   = ($this->smtp_auth == 1) ? true  : false; // enable SMTP authentication
			$mail->Port       = $this->smtp_port;                        // set the SMTP port
			$mail->Host       = $this->smtp_host;                        // sets SMTP server
			$mail->Username   = $this->pop_username;                     // username
			$mail->Password   = $this->pop_password;                     // password
			//$mail->IsSendmail();                                         // tell the class to use Sendmail
			$mail->SMTPDebug  = true;                                    // enables SMTP debug information (for testing)
			$mail->SMTPSecure = ($this->smtp_ssl  == 1) ? "ssl" : "";    // sets the prefix to the servier

			$mail->AddReplyTo($this->smtp_reply_address, $conf['site_name']);
			$mail->From       = $this->smtp_reply_address;
			$mail->FromName   = $conf['site_name'];

			$mail->AddAddress($toEmail, $toName);
			$mail->Subject = $subject;
			$mail->AltBody = $bodyAlt;
			$mail->MsgHTML($bodyHTML);
			$mail->WordWrap = 80;
			$mail->IsHTML(true); // send as HTML

			//$mail->AddAttachment('example/file.gif');
			$mail->Send();
			$sendStatus = "SUCCESS\n";
			$this->messages .= "Successfully sent the message.\n";
			$this->sentStatus = true;

		} catch (phpmailerException $e) {

			$sendStatus = "ERROR";
			$this->messages .= $e->errorMessage(); // pretty error messages from phpmailer
			$messageLog .= $e->errorMessage();

		} catch (Exception $e) {

			$sendStatus = "ERROR";
			$this->messages .= $e->getMessage();   // boring error messages from anything else!
			$messageLog .= $e->getMessage();
		}

		$this->messages .= $sendStatus;

		// log that we sent out an email ....
		$mod = isset($global['module']) ? $global['module'] : "cron";

		$q = "
			INSERT INTO pop_outlog (
				`mod_accessed`,
				`time_sent`,
				`send_status`,
				`error_message`,
				`email_subject`,
				`email_from`,
				`email_recipients` )
			VALUES (
				'".$mod."',
				CURRENT_TIMESTAMP,
				'".$sendStatus."',
				'".$messageLog."',
				'".$subject."',
				'".$this->smtp_reply_address."',
				'".$toEmail."' ) ;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "pop send message ((".$q."))"); }
	}


	/**
	* Prints the message log
	*/
	public function spit() {

		$this->stopTime = microtime(true);
		$totalTime = $this->stopTime - $this->startTime;
		$this->messages .= "scriptExecutedIn >> ".$totalTime." seconds.\n";
		echo $this->messages;
	}
}




