<?php
/**
 * @name         LPF Library
 * @version      0.5
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */


/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class   pop
* @version 2.0
* @author  Greg Miernicki <g@miernicki.com>
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
	private $smtp_reply_name;

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
	public  $stopTime;  // filled by the spit() method when called

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
			$this->smtp_reply_name    = shn_db_get_config("pop","smtp_reply_name1");
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
			$this->smtp_reply_name    = shn_db_get_config("pop","smtp_reply_name2");
		}
		$this->messages          = "scriptExecutedAtTime >> ".date("Ymd:Gis.u")."\n";
		$this->startTime         = microtime(true);
		$this->stopTime          = null;
		$this->messageCount      = 0;
		$this->currentAttachment = NULL;
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
		$this->smtp_reply_name    = shn_db_get_config("pop","smtp_reply_name2");
	}



	/**
	* Sends an Email to a recipient.
	*/
	public function sendMessage($toEmail, $toName, $subject, $bodyHTML, $bodyAlt) {
		global $global;
		//$messageLog = "";
		$messageLog = "";
		$sendStatus = "";
		require_once($global['approot']."3rd/phpmailer/class.phpmailer.php");
		require_once($global['approot']."3rd/phpmailer/class.smtp.php");
		$mail = new PHPMailer(true);  // the true param means it will throw exceptions on errors, which we need to catch
		$mail->IsSMTP();              // telling the class to use SMTP
		try {
			$mail->SMTPDebug  = 0;                                       // enables SMTP debug information (for testing)
			$mail->SMTPAuth   = ($this->smtp_auth == 1) ? true  : false; // enable SMTP authentication
			$mail->SMTPSecure = ($this->smtp_ssl  == 1) ? "ssl" : "";    // sets the prefix to the servier
			$mail->Host       = $this->smtp_host;                        // sets SMTP server
			$mail->Port       = $this->smtp_port;                        // set the SMTP port
			$mail->Username   = $this->pop_username;                     // username
			$mail->Password   = $this->pop_password;                     // password

			$mail->AddReplyTo($this->smtp_reply_address, $this->smtp_reply_name);
			$mail->SetFrom(   $this->smtp_reply_address, $this->smtp_reply_name);

			$mail->AddAddress($toEmail, $toName);
			$mail->Subject = $subject;
			$mail->AltBody = $bodyAlt;
			$mail->MsgHTML($bodyHTML);

			//$mail->AddAttachment('example/file.gif');
			$mail->Send();
			$sendStatus = "SUCCESS";
			$this->messages .= "Successfully sent the message.\n";
			$this->sentStatus = TRUE;
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

		$q = "INSERT INTO pop_outlog
			(`mod_accessed`, `time_sent`, `send_status`, `error_message`, `email_subject`, `email_from`, `email_recipients`)
			VALUES
			('".$mod."', CURRENT_TIMESTAMP, '".$sendStatus."', '".$messageLog."', '".$subject."', '".$this->smtp_reply_address."', '".$toEmail."');";

		$result = $global['db']->Execute($q);
		//$this->messages .= "\n\n".$q."\n\n";
	}



	/**
	* Prints the message log
	*/
	public function spit() {
		$this->stopTime = microtime(true);
		$totalTime = $this->stopTime - $this->startTime;
		$this->messages .= "scriptExecutedIn >> ".$totalTime." seconds.\n\n";
		echo $this->messages;
	}



	public function openMailbox() {
		// build pop/imap settings string
		$sslOption = "";
		if ($this->pop_ssl=="1") {
			$sslOption = "/ssl/novalidate-cert";
		}
		$protocol = "imap";
		if ($this->pop_popimap == "POP") {
			$protocol = "pop3";
		}
		// example server string = "{mail.nih.gov:995/pop3/ssl/novalidate-cert}";
		$this->serverString = "{". $this->pop_host .":". $this->pop_port ."/". $protocol . $sslOption ."}";
		$this->mailbox = imap_open($this->serverString, $this->pop_username, $this->pop_password);
		if ($this->mailboxHeader = imap_check($this->mailbox)) {
			$this->mailboxOpen = TRUE;
			$this->messages .= "Mailbox opened successfully.\n";
		} else {
			$this->mailboxOpen = FALSE;
			$this->messages .= "Mailbox failed to open.\n";
		}
	}


	public function loopInbox() {
		if ( $this->mailboxOpen == FALSE ) {
			$this->messages .= "Can't loop inbox as it's not open!\n";
		} else {
			$this->messageCount = $this->mailboxHeader->Nmsgs;
			$this->messages .= "Number of messages in inbox: ". $this->messageCount ."\n";

			// download all message information from inbox
			$overview = imap_fetch_overview($this->mailbox,"1:".$this->messageCount,0);
			$size = sizeof($overview);

			// loop through each message
			for ( $i = $size-1; $i >= 0; $i-- ) {
				// retrieve current message's data
				$this->currentMessage = $overview[$i];
				$this->fixDate(); // reformat the date for our purposes
				$this->fixFrom(); // strip extra characters from the from field

				// "New Disaster Patient #911-33455 Arrived at Suburban" ~ example email subject for TriagePic
				$emailType = stripos($this->currentMessage->subject, "New Disaster Patient");

				// if this is a TriagePic email, we will use the .lpf and image attachments
				if ( $emailType !== FALSE ) {
					$this->messages .= "TriagePic email found>> message(#".$i.") date(".$this->currentMessage->date.") subject(".$this->currentMessage->subject.")\n";
					$this->person = new lpfPatient($this->currentMessage->subject,$this->currentMessage->date,$this->currentMessage->from,$this->incident_id);
					if ($this->findLpfAttachment($i)) {
						$this->person->parseXML($this->currentAttachment);
						if (!$this->person->dupeCheck()) {
							$this->addImagesToPerson($i);
							$this->person->insertPatient();
							$this->messages .= "inserted!\n";
						} else {
							$this->messages .= "duplicate!\n";
						}
					} else {
						$this->messages .= "Error. No LPF attachment in LPF formatted email, person not added.\n";
					}

				// this is not a TriagePic email, so we will treat is as containing a victim's name in the subject an possibly having image attachments
				} else {
					$this->messages .= "Normal email found>> message(#".$i.") date(".$this->currentMessage->date.") subject(".$this->currentMessage->subject.")\n";
					$this->person = new lpfPatient($this->currentMessage->subject,$this->currentMessage->date,$this->currentMessage->from,$this->incident_id);
					$name = new nameParser( $this->currentMessage->subject );
					$this->person->lastName = $name->getLastName();
					$this->person->firstName = $name->getFirstName();
					if (!$this->person->dupeCheck()) {
						$this->addImagesToPerson($i);
						$this->person->insertPatient();
						$this->messages .= "inserted!\n";
					} else {
						$this->messages .= "duplicate!\n";
					}
				}

				// delete the message from the inbox if so configured
				if ($this->delete_messages=="1") {
					imap_delete($this->mailbox, $i+1);
					$this->messages .= "Message #".$i." deleted.\n";
				}

				// reset person for next round
				$this->person = NULL;
			}
		}
	}



	private function findLpfAttachment($i) {
		// loop through attachments (up to the maximum number specified) and find XML .lpf attachments
		for ( $j = 1; $j <= $this->attachments; $j++ ) {
			// here we are assuming that the attachments are body segments (this may not be always correct but it works in most cases)
			$fileContent = imap_base64(imap_fetchbody($this->mailbox,$i+1,$j+1));
			$foundHeader = stripos($fileContent, "<EDXLDistribution");
			if ( $foundHeader !== FALSE ) {
				$this->currentAttachment = $fileContent;
				return TRUE;
			}
		}
		$this->currentAttachment = NULL;
		return FALSE;
	}



	private function addImagesToPerson($i) {
		// loop through attachments finding images and add them to the current person
		for ( $j = 1; $j <= $this->attachments; $j++ ) {

			// here we are assuming that the attachments are body segments (this may not be always correct but it works in most cases)
			$fileContent = imap_base64( imap_fetchbody($this->mailbox,$i+1,$j+1) );
			if ( $fileContent != NULL ) {

				// save the image to the tmp folder so we can work on it
				$saveFile = "/tmp/popFile_". rand(1000000,9999999); // random filenames are good :)
				$handle = fopen( $saveFile, "w" );
				fwrite( $handle, $fileContent );
				fclose( $handle );

				// check the image type
				$info = getimagesize($saveFile);
				if ( !$info ) {
					// something wrong with attachment
					$type = "";
				} else {
					$mime = $info['mime'];
					$width = $info[0];
					$height = $info[1];
					if ( $mime == "image/jpeg" ) {
						$type = "jpeg";
					} elseif ( $mime == "image/gif" ) {
						$type = "gif";
					} elseif ( $mime == "image/png" ) {
						$type = "png";
					} else {
						// unsupported image type
						$type = "";
					}
				}
				if ( $type != "" ) {
					$this->person->images[] = new imageAttachment($fileContent,$height,$width,$type);
				}
				// done with file, so delete it
				unlink($saveFile);
			}
		}
	}



	private function fixDate() {
		// split into elements and reformat the date to our preferred format YYYYMMDD_HHMMSS (php ~ Ymd_Gis)
		list($dayName,$day,$month,$year,$time,$zone) = explode(" ",$this->currentMessage->date);
		list($hour,$minute,$second) = explode(":",$time);
		$month = $this->fixMonth($month);
		$day = str_pad($day, 2, "0", STR_PAD_LEFT);
		$hour = str_pad($hour, 2, "0", STR_PAD_LEFT);
		$minute = str_pad($minute, 2, "0", STR_PAD_LEFT);
		$second = str_pad($second, 2, "0", STR_PAD_LEFT);
		$this->currentMessage->date = $year.$month.$day."_".$hour.$minute.$second;
	}



	private function fixMonth($month) {
		// change 3 letter month abbreviation into decimal month
		switch ($month) {
			case "Jan": $month = "01"; break;
			case "Feb": $month = "02"; break;
			case "Mar": $month = "03"; break;
			case "Apr": $month = "04"; break;
			case "May": $month = "05"; break;
			case "Jun": $month = "06"; break;
			case "Jul": $month = "07"; break;
			case "Aug": $month = "08"; break;
			case "Sep": $month = "09"; break;
			case "Oct": $month = "10"; break;
			case "Nov": $month = "11"; break;
			case "Dec": $month = "12"; break;
		}
		return $month;
	}



	private function fixFrom() {
		$this->currentMessage->from = ereg_replace('/"/','',$this->currentMessage->from);
	}
}






/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class   person
* @version 2.0
* @author  Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class person {

	// class Members
	public $personId;            // mapped to person_uuid.p_uuid
	public $eventId;             // mapped to resource_to_incident.incident_id
	public $eventShortName;      // mapped to incident.shortname
	public $dateTimeSent;        // mapped to person_status.updated
	public $firstName;           // mapped to person_uuid.fullname - person_uuid.family_name
	public $familyName;          // mapped to person_uuid.family_name
	public $gender;              // mapped to person_details.opt_gender
	public $minAge;              // mapped to person_details.minAge
	public $maxAge;              // mapped to person_details.maxAge
	public $estimatedAgeInYears; // mapped to person_details.years_old
	public $healthStatus;        // mapped to person_status.opt_status ~ overloaded
	public $locationStatus;      // mapped to person_status.opt_status ~ overloaded



	public $status;
	public $comments;
	public $images;
	public $incident_id;
	public $shortName;

	public $emailSubject;
	public $emailDate;
	public $emailFrom;

	public $lpfXmlFile;


	/**
	* New Constructor: Creates a new person
	*/
	public function __construct() {
		$this->uuid        = null;
		$this->shortName   = null;
		$this->firstName   = null;
		$this->familyName  = null;
		$this->gender      = null;
		$this->age         = null;
		$this->status      = null;
		$this->comments    = null;
		$this->images      = null;
		$this->incident_id = null;
		$this->shortName   = null;

		$this->emailSubject = null;
		$this->emailDate    = null;
		$this->emailFrom    = null;
	}



	/**
	* Destructor
	*/
	public function __destruct() {}



	/**
	* New Constructor: Creates a new person
	*/
	public function create() {
		$this->uuid = shn_create_uuid();
	}



	/**
	* Load Constructor: Loads the details of a previously saved person
	*/
	public function load($uuid) {
	}




	public function insertPersonXML() {
		global $global;
		$this->figureOutIncidentId();
		$this->insertImages();

		// insert person
		$q1 = " INSERT INTO person_uuid (p_uuid, full_name, family_name, l10n_name)
			VALUES ('".$this->uuid."', '".$this->firstName." ".$this->familyName."', '".$this->familyName."', NULL);";
		$res = $global['db']->Execute($q1);

		// insert person missing info
		$q2 = " INSERT INTO person_missing (p_uuid, last_seen, last_clothing, comments)
			VALUES ('".$this->uuid."', NULL, NULL, '".$this->comments."');";
		$res = $global['db']->Execute($q2);

		// insert an assignment of this person to the correct incident
		$q3 = " INSERT INTO resource_to_incident (x_uuid, incident_id)
			VALUES ('".$this->uuid."', '".$this->incident_id."');";
		$res = $global['db']->Execute($q3);

		// insert person's status
		$q4 = " INSERT INTO person_status (p_uuid, opt_status, updated, isvictim)
			VALUES ('".$this->uuid."', '".$this->sahanaStatus."', CURRENT_TIMESTAMP, TRUE);";
		$res = $global['db']->Execute($q4);

		// insert person's details
		$q5 = " INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old)
			VALUES ('".$this->uuid."', NULL, '".$this->gender."', '".$this->age."');";
		$res = $global['db']->Execute($q5);
/*
		// insert person who reported them
		$q6 = " INSERT INTO person_uuid (p_uuid)
			VALUES ('".$this->personId."');";
		$res = $global['db']->Execute($q6);
*/
		// insert into mpres_log
		$q7 = " INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);

		//echo "\n---------------------------------------------------------------------\n";
		//echo $q1."\n\n".$q2."\n\n".$q3."\n\n".$q4."\n\n".$q5."\n\n".$q6."\n\n".$q7;
		//echo "\n---------------------------------------------------------------------\n";
	}



	public function insertPerson() {
		global $global;
		$this->extractSahanaStatus();
		$this->insertImages();

		// insert person
		$q1 = " INSERT INTO person_uuid (p_uuid, full_name, family_name, l10n_name)
			VALUES ('".$this->uuid."','".$this->emailSubject."',NULL,NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = " INSERT INTO person_missing (p_uuid, last_seen, last_clothing, comments)
			VALUES ('".$this->uuid."', NULL, NULL, NULL);";
		$res = $global['db']->Execute($q2);

		// insert an assignment of this person to the correct incident
		$q3 = " INSERT INTO resource_to_incident (x_uuid, incident_id)
			VALUES ('".$this->uuid."','".$this->incident_id."');";
		$res = $global['db']->Execute($q3);

		// insert person's status
		$q4 = " INSERT INTO person_status (p_uuid, opt_status, updated, isvictim)
			VALUES ( '".$this->uuid."', '".$this->sahanaStatus."', CURRENT_TIMESTAMP, TRUE);";
		$res = $global['db']->Execute($q4);

		// insert into mpres_log
		$q5 = " INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q5);

		// insert person's details
		$q6 = " INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old)
			VALUES ('".$this->uuid."', NULL, NULL, NULL);";
		$res = $global['db']->Execute($q6);

		// insert person who reported link to root cuz we dont really know who reported them
		$q7 = " INSERT INTO person_to_report (p_uuid, rep_uuid)
			VALUES ('".$this->uuid."', '1');";
		$res = $global['db']->Execute($q7);

		//echo "\n---------------------------------------------------------------------\n";
		//echo $q1."\n\n".$q2."\n\n".$q3."\n\n".$q4."\n\n".$q5."\n\n".$q6."\n\n".$q7;
		//echo "\n---------------------------------------------------------------------\n";
	}



	public function insertImages() {
		global $global;
		// insert a person's images
		for ($i=0; $i < sizeof($this->images); $i++) {
			$q = " INSERT INTO image (x_uuid, image, image_type, image_height, image_width, created, category, url, url_thumb, original_filename)
				VALUES ('".$this->uuid."', NULL, '".$this->images[$i]->type."', '".$this->images[$i]->height."', '".$this->images[$i]->width."', CURRENT_TIMESTAMP, ".
				"'person', '".$this->images[$i]->url."', '".$this->images[$i]->url_thumb."', '".$this->images[$i]->original_filename."');";
			$res = $global['db']->Execute($q);
		}
	}



	public function figureOutIncidentId() {
		global $global;
		$query  = "SELECT * FROM incident WHERE shortname = '".$this->shortName."';";
		$result = $global['db']->Execute($query);
		$row    = $result->FetchRow();
		$this->incident_id = $row['incident_id'];
	}



	public function extractSahanaStatus() {
		$s = strtolower($this->emailSubject);
		$needle   = array();
		$status   = array();

		// clean extraneous characters
		$s = str_replace("`", " ", $s);
		$s = str_replace("~", " ", $s);
		$s = str_replace("!", " ", $s);
		$s = str_replace("@", " ", $s);
		$s = str_replace("#", " ", $s);
		$s = str_replace("$", " ", $s);
		$s = str_replace("%", " ", $s);
		$s = str_replace("^", " ", $s);
		$s = str_replace("&", " ", $s);
		$s = str_replace("*", " ", $s);
		$s = str_replace("(", " ", $s);
		$s = str_replace(")", " ", $s);
		$s = str_replace("-", " ", $s);
		$s = str_replace("_", " ", $s);
		$s = str_replace("+", " ", $s);
		$s = str_replace("=", " ", $s);
		$s = str_replace("{", " ", $s);
		$s = str_replace("}", " ", $s);
		$s = str_replace("[", " ", $s);
		$s = str_replace("]", " ", $s);
		$s = str_replace("|", " ", $s);
		$s = str_replace("\\"," ", $s);
		$s = str_replace(":", " ", $s);
		$s = str_replace(";", " ", $s);
		$s = str_replace("'", " ", $s);
		$s = str_replace("\""," ", $s);
		$s = str_replace(",", " ", $s);
		$s = str_replace(".", " ", $s);
		$s = str_replace("<", " ", $s);
		$s = str_replace(">", " ", $s);
		$s = str_replace("?", " ", $s);
		$s = str_replace("/", " ", $s);

		// vocabulary of english/french/spanish status words and their corresponding sahana status code
		$needle[] = '/missing/';
		$status[] = 'mis';
		$needle[] = '/lost/';
		$status[] = 'mis';
		$needle[] = '/looking for/';
		$status[] = 'mis';
		$needle[] = '/find/';
		$status[] = 'mis';
		$needle[] = '/disparu/';
		$status[] = 'mis';
		$needle[] = '/perdu/';
		$status[] = 'mis';
		$needle[] = '/a la recherche de/';
		$status[] = 'mis';
		$needle[] = '/trouver/';
		$status[] = 'mis';
		$needle[] = '/moun yap chache/';
		$status[] = 'mis';
		$needle[] = '/injured/';
		$status[] = 'inj';
		$needle[] = '/hurt/';
		$status[] = 'inj';
		$needle[] = '/wounded/';
		$status[] = 'inj';
		$needle[] = '/sick/';
		$status[] = 'inj';
		$needle[] = '/treated/';
		$status[] = 'inj';
		$needle[] = '/recovering/';
		$status[] = 'inj';
		$needle[] = '/blesse/';
		$status[] = 'inj';
		$needle[] = '/mal en point/';
		$status[] = 'inj';
		$needle[] = '/malade/';
		$status[] = 'inj';
		$needle[] = '/soigne/';
		$status[] = 'inj';
		$needle[] = '/convalecent/';
		$status[] = 'inj';
		$needle[] = '/deceased/';
		$status[] = 'dec';
		$needle[] = '/dead/';
	}












/*










////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////
/////////////////////
/////////////////////
//
//

	public $uuid;

	public $distributionId;
	public $sendId;
	public $dateTimeSent;
	public $distributionStatus;
	public $distributionType;
	public $combinedConfidentiality;
	public $keyword; // array
	public $targetArea;
	public $contentDescription;
	public $version;
	public $login;
	public $personId;
	public $eventName;
	public $orgName;
	public $orgId;
	public $lastName;
	public $firstName;
	public $gender;
	public $genderEnum;
	public $genderEnumDesc;
	public $peds;
	public $pedsEnum;
	public $pedsEnumDesc;
	public $triageCategory;
	public $triageCategoryEnum;
	public $triageCategoryEnumDesc;

	public $sahanaStatus;
	public $sahanaAgeGroup;
	public $sahanaAge;
	public $sahanaNotes;
	public $sahanaLastLocation;
	public $sahanaGPS;

	public $images;
	public $incident_id;

	public $emailSubject;
	public $emailDate;
	public $emailFrom;

	public $lpfFile;
	public $lpfArray;
	public $lpfFileXmlString;


	public function	__construct($subject, $date, $from, $incident_id) {
		$this->emailSubject = $subject;
		$this->emailDate    = $date;
		$this->emailFrom    = $from;
		$this->incident_id  = $incident_id;
		$this->lpfFile      = NULL;
		$this->lpfArray     = NULL;
		$this->images       = NULL;
		$this->imageCount   = 0;
		$this->uuid         = 0;
	}



	public function __destruct() {}



	public function parseXML($xmlString) {
		$converted = new xml2array();
		$converted->setXML($xmlString);
		$a = $converted->getArray();
		$this->distributionId          = $a['EDXLDistribution']['distributionID']['#text'];
		$this->sendId                  = $a['EDXLDistribution']['senderID']['#text'];
		$this->dateTimeSent            = $a['EDXLDistribution']['dateTimeSent']['#text'];
		$this->distributionStatus      = $a['EDXLDistribution']['distributionStatus']['#text'];
		$this->distributionType        = $a['EDXLDistribution']['distributionType']['#text'];
		$this->combinedConfidentiality = $a['EDXLDistribution']['combinedConfidentiality']['#text'];
		$this->keyword                 = $a['EDXLDistribution']['keyword']['value']; // array, index starting at 0, containing subarrays of keywords (#text)
		$this->targetArea              = $a['EDXLDistribution']['targetArea']['circle']['#text'];
		$this->contentDescription      = $a['EDXLDistribution']['contentObject']['contentDescription']['#text'];
		$this->version                 = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['version']['#text'];
		$this->login                   = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['login']['username']['#text'];
		$this->personId                = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['personId']['#text'];
		$this->eventName               = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventName']['#text'];
		$this->orgName                 = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgName']['#text'];
		$this->orgId                   = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgId']['#text'];
		$this->lastName                = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName']['#text'];
		$this->firstName               = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName']['#text'];
		$this->gender                  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['gender']['#text'];
		$this->genderEnum              = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['genderEnum']['#text'];
		$this->genderEnumDesc          = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['genderEnumDesc']['#text'];
		$this->peds                    = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['peds']['#text'];
		$this->pedsEnum                = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['pedsEnum']['#text'];
		$this->pedsEnumDesc            = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['pedsEnumDesc']['#text'];
		$this->triageCategory          = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategory']['#text'];
		$this->triageCategoryEnum      = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategoryEnum']['#text'];
		$this->triageCategoryEnumDesc  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategoryEnumDesc']['#text'];
		$this->lpfFileXmlString        = $xmlString;
		$this->lpfArray                = $a;
	}


	public function dupeCheck() {
		global $global;

		// find out if we have seen this email before
		$q = "SELECT * FROM mpres_log WHERE email_subject = '".$this->emailSubject."' AND email_from = '".$this->emailFrom."' AND email_date = '".$this->emailDate."';";
		$res = $global['db']->Execute($q);
		if ($res && $res->RecordCount() > 0) {
			return TRUE;
		} else {
			$this->create_uuid();
			return FALSE;
		}
	}



	public function insertPatient() {
		global $global;

		// insert person
		$q1 = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name) VALUES ('".$this->uuid."','".$this->firstName." ".$this->lastName."','".$this->lastName."',NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = "INSERT INTO person_missing (p_uuid,last_seen,last_clothing,comments) VALUES ('".$this->uuid."', '".$this->orgName         ."', NULL, NULL);";
		$res = $global['db']->Execute($q2);

		// insert a person's images
		for ($i = 0; $i < sizeof($this->images); $i++) {
			$q3 = "INSERT INTO image (x_uuid,image,image_type,image_height,image_width,created,category) VALUES ('".$this->uuid."','".addslashes($this->images[$i]->data)."','".$this->images[$i]->type."','".$this->images[$i]->height."','".$this->images[$i]->width."',CURRENT_TIMESTAMP, 'person');";
			$res = $global['db']->Execute($q3);
		}

		// insert an assignment of this person to the correct incident
		$q4 = "INSERT INTO resource_to_incident (x_uuid,incident_id) VALUES ('".$this->uuid."','".$this->incident_id."');";
		$res = $global['db']->Execute($q4);

		// figure out the person's status
		switch($this->triageCategory) {
			case "Black" :
				$opt_status = "dec";
				break;
			case "Yellow" :
			case "Red" :
			case "Gray" :
				$opt_status = "inj";
				break;
			case "Green" :
			case "BH Green" :
			default :
				$opt_status = "ali";
				break;
		}
		// insert person's status
		$q5 = "INSERT INTO person_status (p_uuid, opt_status, isvictim) VALUES ( '".$this->uuid."', '".$opt_status."', TRUE);";
		$res = $global['db']->Execute($q5);
/*
		// insert person's physical appearance
		$q6 = "INSERT INTO person_physical (p_uuid, comments) VALUES ('".$this->uuid."', '".$this->triageCategoryEnumDesc."');";
		$res = $global['db']->Execute($q6);
//
		// insert into mpres_log
		$q7 = "INSERT INTO mpres_log (p_uuid,email_subject,email_from,email_date,update_time) VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);


		// figure out the person's sex
		switch($this->gender) {
			case "M" :
				$opt_sex = "mal";
				break;
			case "F" :
				$opt_sex = "fml";
				break;
			default :
				$opt_sex = $this->gender;
				break;
		}


		// insert person's details
		$q8 = "INSERT INTO person_details (p_uuid, opt_gender) VALUES ('".$this->uuid."', '".$opt_sex."');";
		$res = $global['db']->Execute($q8);

		// save all fields to the mpres_patient table
		// temporary until EDXL classes and tables are implemented -- this is where we will save this data in the future
		$q9 = "INSERT INTO mpres_patient (p_uuid, distributionId, sendId, dateTimeSent, distributionStatus, distributionType, combinedConfidentiality, keyword, targetArea, contentDescription, 	version, login, personId, eventName, orgName, orgId, lastName, firstName, gender, genderEnum, genderEnumDesc, peds, pedsEnum, pedsEnumDesc, triageCategory, triageCategoryEnum, triageCategoryEnumDesc, lpfFileXmlString, lpfArray) VALUES ('".$this->uuid."', '".$this->distributionId."', '".$this->sendId."', '".$this->dateTimeSent."', '".$this->distributionStatus."', '".$this->distributionType."', '".$this->combinedConfidentiality."', '".$this->keyword."', '".$this->targetArea."', '".$this->contentDescription."', '".$this->version."', '".$this->login."', '".$this->personId."', '".$this->eventName."', '".$this->orgName."', '".$this->orgId."', '".$this->lastName."', '".$this->firstName."', '".$this->gender."', '".$this->genderEnum."', '".$this->genderEnumDesc."', '".$this->peds."', '".$this->pedsEnum."', '".$this->pedsEnumDesc."', '".$this->triageCategory."', '".$this->triageCategoryEnum."', '".$this->triageCategoryEnumDesc."', '".$this->lpfFileXmlString."', '".serialize($this->lpfArray)."');";
		$res = $global['db']->Execute($q9);

	}




	public function iPhoneParse($body) {
		$b = explode("\r", $body);

		$this->distributionId          = "";
		$this->sendId                  = trim($b[16]);
		$this->dateTimeSent            = trim($b[10]);
		$this->distributionStatus      = "";
		$this->distributionType        = "";
		$this->combinedConfidentiality = "";
		$this->keyword                 = "";
		$this->targetArea              = "";
		$this->contentDescription      = "";
		$this->version                 = "";
		$this->login                   = "";
		$this->personId                = trim($b[0])."-".substr(md5($this->sendId), 0, 5);
		$this->eventName               = "";
		$this->orgName                 = "";
		$this->orgId                   = "";
		$this->lastName                = trim($b[2]);
		$this->firstName               = trim($b[1]);
		$this->gender                  = trim($b[4]);
		$this->genderEnum              = "";
		$this->genderEnumDesc          = "";
		$this->peds                    = "";
		$this->pedsEnum                = "";
		$this->pedsEnumDesc            = "";
		$this->triageCategory          = "";
		$this->triageCategoryEnum      = "";
		$this->triageCategoryEnumDesc  = "";
		$this->lpfFileXmlString        = $body;
		$this->lpfArray                = $b;
		$this->sahanaStatus            = trim($b[3]);
		$this->sahanaAgeGroup          = trim($b[5]);
		$this->sahanaAge               = ""; //trim($b[6]);
		$this->sahanaNotes             = trim($b[11]);
		$this->sahanaLocationStatus    = trim($b[6]);
		$this->sahanaLastLocation      = trim($b[7]);
		$this->sahanaGPS               = trim($b[9]);
		$appName                       = trim($b[17]);
		$appVersion                    = trim($b[18]);

		/*
			[0] => ID: HAITI-20100127-0002
			[1] => Given Name: Mickey
			[2] => Family Name: Mouse
			[3] => Health Status: Alive & Well
			[4] => Gender: Male
			[5] => Age Group: 0-17
			[6] => Estimated Age: 16
			[7] => Location Status: Known
			[8] => Current Location: Walt Disney World, Kissimmee FL
			[9] => GPS: 39.1812N, 77.1788W
			[10] => Event Creation Timestamp: 2010-01-27 01:33:10 -0500
			[11] => Notes: test image
			[12] => UDID: ec3842f4f41b563790c82e394d4e6ec40ba86b68
			[13] => App Name: Found in Haiti
			[14] => Version: 0.3.1


			[0] => ID: HAITI-20100409-0001
			[1] => Given Name: Jane
			[2] => Family Name: Doe
			[3] => Health Status: Alive and Well
			[4] => Gender: Female
			[5] => Age: 20 to 25
			[6] => Location Status: Known
			[7] => Last Seen At: Pentagon Access Rd, Virginia, Arlington, Arlington,
			[8] => 22202, United States
			[9] => GPS: 38.8686N, 77.0543W
			[10] => Event Creation Timestamp: 2010-04-09 14:25:48 -0400
			[11] => Notes: this is a sample note
			[12] => Crop x: 207
			[13] => Crop y: 44
			[14] => Crop width: 221
			[15] => Crop height: 221
			[16] => UDID: 17132cc6679f115644254df38e3ec20f85522abe
			[17] => App Name: Reunite
			[18] => Version: 1.1
		//

		$appName                    = mysql_real_escape_string(str_ireplace("App Name: ",                 "", $appName));
		$appVersion                 = mysql_real_escape_string(str_ireplace("Version: ",                  "", $appVersion));
		$this->sendId               = mysql_real_escape_string(str_ireplace("UDID: ",                     "", $this->sendId));
		$this->dateTimeSent         = mysql_real_escape_string(str_ireplace("Event Creation Timestamp: ", "", $this->dateTimeSent));
		$this->personId             = mysql_real_escape_string(str_ireplace("ID: ",                       "", $this->personId));
		$this->lastName             = mysql_real_escape_string(str_ireplace("Family Name: ",              "", $this->lastName));
		$this->firstName            = mysql_real_escape_string(str_ireplace("Given Name: ",               "", $this->firstName));
		$this->sahanaAgeGroup       = mysql_real_escape_string(str_ireplace("Age: ",                      "", $this->sahanaAgeGroup));
		$this->sahanaAge            = mysql_real_escape_string(str_ireplace("Estimated Age: ",            "", $this->sahanaAge));
		$this->sahanaNotes          = mysql_real_escape_string(str_ireplace("Notes: ",                    "", $this->sahanaNotes));
		$this->sahanaLocationStatus = mysql_real_escape_string(str_ireplace("Location Status: ",          "", $this->sahanaLocationStatus));
		$this->sahanaLastLocation   = mysql_real_escape_string(str_ireplace("Current Location: ",         "", $this->sahanaLastLocation));
		$this->sahanaGPS            = mysql_real_escape_string(str_ireplace("GPS: ",                      "", $this->sahanaGPS));
		$this->sahanaStatus         = mysql_real_escape_string(str_ireplace("Health Status: ",            "", $this->sahanaStatus));

		// Alive & Well / Injured / Deceased / Unknown
		if ($this->sahanaStatus == "Alive & Well") {
			$this->sahanaStatus = "ali";
		} else if ($this->sahanaStatus == "Injured") {
			$this->sahanaStatus = "inj";
		} else if ($this->sahanaStatus == "Deceased") {
			$this->sahanaStatus = "dec";
		} else if ($this->sahanaLocationStatus == "Missing") {
			$this->sahanaStatus = "mis";
		} else {
			$this->sahanaStatus = "unk";
		}

		// Male / Female / Unknown
		if ($this->gender == "Male") {
			$this->gender = "mal";
		} else if ($this->gender == "Female") {
			$this->gender = "fml";
		} else {
			$this->gender = "unk";
		}
	}



	public function insertPerson2() {
		global $global;

		// insert person
		$q1 = "INSERT INTO person_uuid (p_uuid, full_name, family_name, l10n_name) VALUES ('".$this->personId."','".$this->firstName." ".$this->lastName."','".$this->lastName."',NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = "INSERT INTO person_missing (p_uuid, last_seen, last_clothing, comments) VALUES ('".$this->personId."', '".$this->sahanaLastLocation." (".$this->sahanaGPS.")', NULL, '".$this->sahanaNotes."');";
		$res = $global['db']->Execute($q2);

		// insert a person's images
		for ($i = 0; $i < sizeof($this->images); $i++) {

			// we are now stroing images in a cache on the web server vs. the database to reduce cpu usage when the server is being raped
			$newFileName = str_replace("/", "SLASH", $this->uuid).$i.".".$this->images[$i]->type;
			$newFilePath = "../../www/tmp/mpres_cache/";
			shell_exec("mv ".$this->images[$i]->file." ".$newFilePath.$newFileName);

			shn_image_resize_height($newFilePath.$newFileName, $newFilePath."thumb_".$newFileName, 320);

			$q3 = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width, created, category, url) VALUES (
				'".$this->personId."',
				NULL,
				'".$this->images[$i]->type."',
				'".$this->images[$i]->height."',
				'".$this->images[$i]->width."',
				CURRENT_TIMESTAMP,
				'person',
				'/tmp/mpres_cache/".$newFileName."');";

			$res = $global['db']->Execute($q3);
		}

		// insert an assignment of this person to the correct incident
		$q4 = "INSERT INTO resource_to_incident (x_uuid, incident_id) VALUES ('".$this->personId."','".$this->incident_id."');";
		$res = $global['db']->Execute($q4);

		// insert person's status
		$q5 = "INSERT INTO person_status (p_uuid, opt_status, isvictim) VALUES ( '".$this->personId."', '".$this->sahanaStatus."', TRUE);"; // current timestamp
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = "INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time) VALUES ('".$this->personId."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);

		// insert person's details
		$q8 = "INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old) VALUES ('".$this->personId."', '".$this->sahanaAgeGroup."', '".$this->gender."', '".$this->sahanaAge."');";
		$res = $global['db']->Execute($q8);

		// insert person who reported them
		$q10 = "INSERT INTO person_uuid (p_uuid) VALUES ('".$this->personId."');";
		$res = $global['db']->Execute($q10);

		// insert person
		$q11 = "INSERT INTO person_to_report (p_uuid, rep_uuid) VALUES ('".$this->sendId."','".$this->personId."');";
		$res = $global['db']->Execute($q11);

//echo $q1."\n".$q2."\n".$q3."\n".$q4."\n".$q5."\n".$q7."\n".$q8."\n".$q9."\n".$q10."\n".$q11."\n";

	}




public function findSahanaStatus() {
               $l = strtolower($this->emailSubject);

               // English missing:
               if (stripos($l, "missing", 0)) {
                       //$this->emailSubject = str_ireplace("missing", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "lost", 0)) {
                       //$this->emailSubject = str_ireplace("lost", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "looking for", 0)) {
                       //$this->emailSubject = str_ireplace("looking for", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "find", 0)) {  // typically "to find"
                       //$this->emailSubject = str_ireplace("find", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               // French missing:
               } else if (stripos($l, "disparu", 0)) {
                       //$this->emailSubject = str_ireplace("disparu", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "perdu", 0)) {
                       //$this->emailSubject = str_ireplace("perdu", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "a la recherche de", 0)) {  // TO DO: &#224; la recherche de
                       //$this->emailSubject = str_ireplace("a la recherche de", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "trouver", 0)) {
                       //$this->emailSubject = str_ireplace("trouver", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               // Creole missing:
               } else if (stripos($l, "moun yap chache", 0)) {  // TO DO: moun yap chaché
                       //$this->emailSubject = str_ireplace("moun yap chache", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               // English injured:
               } else if (stripos($l, "injured", 0)) {
                       //$this->emailSubject = str_ireplace("injured", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "hurt", 0)) {
                       //$this->emailSubject = str_ireplace("hurt", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "wounded", 0)) {
                       //$this->emailSubject = str_ireplace("wounded", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "sick", 0)) {
                       //$this->emailSubject = str_ireplace("sick", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "treated", 0)) {
                       //$this->emailSubject = str_ireplace("treated", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "recovering", 0)) {
                       //$this->emailSubject = str_ireplace("recovering", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               // French injured:
               } else if (stripos($l, "blesse", 0)) { // TO DO: bless&#233;
                       //$this->emailSubject = str_ireplace("blesse", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "mal en point", 0)) {
                       //$this->emailSubject = str_ireplace("mal en point", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "malade", 0)) {
                       //$this->emailSubject = str_ireplace("malade", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "soigne", 0)) { // TO DO: soign&#233;
                       //$this->emailSubject = str_ireplace("soigne", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "convalescent", 0)) {
                       //$this->emailSubject = str_ireplace("convalescent", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               // Creole injured:
               // blesse [and TO DO blessé] - Already covered by French

               // English dead:
               } else if (stripos($l, "deceased", 0)) {
                       //$this->emailSubject = str_ireplace("deceased", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "dead", 0)) {
                       //$this->emailSubject = str_ireplace("dead", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "died", 0)) {
                       //$this->emailSubject = str_ireplace("died", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "buried", 0)) {
                       //$this->emailSubject = str_ireplace("buried", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // English deceased:
               } else if (stripos($l, "deceased", 0)) {
                       //$this->emailSubject = str_ireplace("deceased", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "dead", 0)) {
                       //$this->emailSubject = str_ireplace("dead", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "died", 0)) {
                       //$this->emailSubject = str_ireplace("died", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "buried", 0)) {
                       //$this->emailSubject = str_ireplace("buried", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // French deceased:
               } else if (stripos($l, "decede", 0)) {  // TO DO:  D&#233;c&#233;d&#233;
                       //$this->emailSubject = str_ireplace("decede", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "mort", 0)) {
                       //$this->emailSubject = str_ireplace("mort", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "inhume", 0)) {  // TO DO:  inhum&#233;
                       //$this->emailSubject = str_ireplace("inhume", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // Creole deceased:
               } else if (stripos($l, "mouri", 0)) {
                       //$this->emailSubject = str_ireplace("mouri", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // English alive:
               } else if (stripos($l, "alive & well", 0)) {
                       //$this->emailSubject = str_ireplace("alive & well", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "alive and well", 0)) {
                       //$this->emailSubject = str_ireplace("alive and well", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "alive", 0)) { // do separate "alive", "well" words *after* phrase forms of "alive & well"
                       //$this->emailSubject = str_ireplace("alive", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "well", 0)) {
                       //$this->emailSubject = str_ireplace("well", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "okay", 0)) {
                       //$this->emailSubject = str_ireplace("okay", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "ok", 0)) { // do *after* okay
                       //$this->emailSubject = str_ireplace("ok", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "good", 0)) {
                       //$this->emailSubject = str_ireplace("good", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "recovered", 0)) {
                       //$this->emailSubject = str_ireplace("recovered", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "fine", 0)) {
                       //$this->emailSubject = str_ireplace("fine", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               // French alive:  // Note: "ok", "OK" handled under English
               } else if (stripos($l, "en vie", 0)) {
                       //$this->emailSubject = str_ireplace("en vie", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "vivant", 0)) {
                       //$this->emailSubject = str_ireplace("vivant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "bien portant", 0)) {
                       //$this->emailSubject = str_ireplace("bien portant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "en bonne sante", 0)) {  // TO DO: en bonne sant&#233;
                       //$this->emailSubject = str_ireplace("en bonne sante", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "gueri", 0)) {  // TO DO: gu&#233;ri
                       //$this->emailSubject = str_ireplace("gueri", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "bien portant", 0)) {
                       //$this->emailSubject = str_ireplace("bien portant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               // Creole alive & well
               } else if (stripos($l, "vivant ak anfom", 0)) {
                       //$this->emailSubject = str_ireplace("vivant ak anfom", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "vivant", 0)) { // Should be *after* compound form "vivant ak anfom"
                       //$this->emailSubject = str_ireplace("vivant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "anfom", 0)) { // Should be *after* compound form "vivant ak anfom"
                       //$this->emailSubject = str_ireplace("anfom", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else {
                       $this->sahanaStatus = "unk";
               }
       }



	public function insertPerson() {
		global $global;

		// insert person
		$q1 = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name) VALUES ('".$this->uuid."','".$this->emailSubject."',NULL,NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = "INSERT INTO person_missing (p_uuid,last_seen,last_clothing,comments) VALUES ('".$this->uuid."', NULL, NULL, NULL);";
		$res = $global['db']->Execute($q2);

		// insert a person's images
		for ($i = 0; $i < sizeof($this->images); $i++) {

			// we are now stroing images in a cache on the web server vs. the database to reduce cpu usage when the server is being raped
			$newFileName = str_replace("/", "SLASH", $this->uuid).$i.".".$this->images[$i]->type;
			$newFilePath = "../../www/tmp/mpres_cache/";
			shell_exec("mv ".$this->images[$i]->file." ".$newFilePath.$newFileName);

			shn_image_resize_height($newFilePath.$newFileName, $newFilePath."thumb_".$newFileName, 320);

			$q3 = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width, created, category, url) VALUES (
				'".$this->uuid."',
				NULL,
				'".$this->images[$i]->type."',
				'".$this->images[$i]->height."',
				'".$this->images[$i]->width."',
				CURRENT_TIMESTAMP,
				'person',
				'/tmp/mpres_cache/thumb_".$newFileName."');";

			$res = $global['db']->Execute($q3);
		}

		// insert an assignment of this person to the correct incident
		$q4 = "INSERT INTO resource_to_incident (x_uuid,incident_id) VALUES ('".$this->uuid."','".$this->incident_id."');";
		$res = $global['db']->Execute($q4);

		// insert person's status
		$q5 = "INSERT INTO person_status (p_uuid, opt_status, isvictim) VALUES ( '".$this->uuid."', '".$this->sahanaStatus."', TRUE);";
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = "INSERT INTO mpres_log (p_uuid,email_subject,email_from,email_date,update_time) VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);

/*
		// figure out the person's sex
		switch($this->gender) {
			case "M" :
				$opt_sex = "mal";
				break;
			case "F" :
				$opt_sex = "fml";
				break;
			default :
				$opt_sex = $this->gender;
				break;
		}


		// insert person's details
		$q8 = "INSERT INTO person_details (p_uuid, opt_gender) VALUES ('".$this->uuid."', '".$opt_sex."');";
		$res = $global['db']->Execute($q8);


		// save all fields to the mpres_patient table
		// temporary until EDXL classes and tables are implemented -- this is where we will save this data in the future
		$q9 = "INSERT INTO mpres_patient (p_uuid, distributionId, sendId, dateTimeSent, distributionStatus, distributionType, combinedConfidentiality, keyword, targetArea, contentDescription, 	version, login, personId, eventName, orgName, orgId, lastName, firstName, gender, genderEnum, genderEnumDesc, peds, pedsEnum, pedsEnumDesc, triageCategory, triageCategoryEnum, triageCategoryEnumDesc, lpfFileXmlString, lpfArray) VALUES ('".$this->uuid."', '".$this->distributionId."', '".$this->sendId."', '".$this->dateTimeSent."', '".$this->distributionStatus."', '".$this->distributionType."', '".$this->combinedConfidentiality."', '".$this->keyword."', '".$this->targetArea."', '".$this->contentDescription."', '".$this->version."', '".$this->login."', '".$this->personId."', '".$this->eventName."', '".$this->orgName."', '".$this->orgId."', '".$this->lastName."', '".$this->firstName."', '".$this->gender."', '".$this->genderEnum."', '".$this->genderEnumDesc."', '".$this->peds."', '".$this->pedsEnum."', '".$this->pedsEnumDesc."', '".$this->triageCategory."', '".$this->triageCategoryEnum."', '".$this->triageCategoryEnumDesc."', '".$this->lpfFileXmlString."', '".serialize($this->lpfArray)."');";
		$res = $global['db']->Execute($q9);
	}




	private function create_uuid() {
		$this->uuid = shn_create_uuid();
	}

	/*
	INSERT INTO person_uuid ( p_uuid , full_name , family_name , l10n_name ) VALUES ( '8y2fp-27', 'Mujestica', 'Allahary', 'Mua' )
	INSERT INTO person_to_report ( p_uuid , rep_uuid , relation ) VALUES ( '8y2fp-27', '8y2fp-3', 'Not Specified' )
	INSERT INTO identity_to_person ( p_uuid , serial , opt_id_type ) VALUES ( '8y2fp-27', 'M-652-299-399-499', 'nic' )
	INSERT INTO identity_to_person ( p_uuid , serial , opt_id_type ) VALUES ( '8y2fp-27', 'DJ-617-9999-420-000002', 'pas' )
	INSERT INTO identity_to_person ( p_uuid , serial , opt_id_type ) VALUES ( '8y2fp-27', 'DL-9999-8888-7777', 'dln' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '1234 Street St.', 'hom' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '911-911-9111', 'curr' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '911-911-9112', 'cmob' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '21999', 'zip' )
	INSERT INTO phonetic_word ( encode1 , encode2 , pgl_uuid ) VALUES ( 'M223', 'MJSTK', '8y2fp-27' )
	INSERT INTO phonetic_word ( encode1 , encode2 , pgl_uuid ) VALUES ( 'A460', 'ALHR', '8y2fp-27' )
	INSERT INTO phonetic_word ( encode1 , encode2 , pgl_uuid ) VALUES ( 'M000', 'M', '8y2fp-27' )
	INSERT INTO location_details ( pgoc_uuid , contact_value , opt_contact_type , postcode ) VALUES ( '8y2fp-27', '911-911-9112', 'cmob', '21999' )
	INSERT INTO person_physical ( p_uuid , opt_eye_color , opt_skin_color , opt_hair_color , height , weight , opt_blood_type , comments ) VALUES ( '8y2fp-27', 'blu', 'whi', 'bro', '135', '125', 'a+', 'smile' )
	INSERT INTO person_missing ( p_uuid , last_seen , last_clothing , comments ) VALUES ( '8y2fp-27', 'The mall', 'jeans, shirt', 'shes a flirt' )
	INSERT INTO person_details ( p_uuid , birth_date , opt_age_group , opt_gender , opt_marital_status , opt_religion , opt_race ) VALUES ( '8y2fp-27', '1990-05-01', 'adu', 'fml', 'sin', 'bud', 'filip' )
	INSERT INTO person_status ( p_uuid , opt_status , isvictim ) VALUES ( '8y2fp-27', 'mis', TRUE )
	INSERT INTO resource_to_incident ( x_uuid , incident_id ) VALUES ( '8y2fp-27', '1' )
	*/


}






/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class   imageAttachment
* @version 2.0
* @author  Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class imageAttachment {

	public $filename;          // new name of file
	public $fileContent;       // binary content of the file
	public $height;            // pixel height of image
	public $width;             // pixel width of image
	public $type;              // mime type of image
	public $url;               // associated url for image once its stored
	public $url_thumb;         // associated url for image thumbnail once its stored
	public $original_filename; // original filename of image when it was an email attachment

	/**
	* Constructor:
	*/
	public function __construct($filename, $fileContent, $height, $width, $type, $url, $url_thumb, $original_filename) {
		$this->filename          = $filename;
		$this->fileContent       = $fileContent;
		$this->height            = $height;
		$this->width             = $width;
		$this->type              = $type;
		$this->url               = $url;
		$this->url_thumb         = $url_thumb;
		$this->original_filename = $original_filename;
	}


	/**
	* Destructor
	*/
	public function __destruct() {
		$this->filename          = NULL;
		$this->fileContent       = NULL;
		$this->height            = NULL;
		$this->width             = NULL;
		$this->type              = NULL;
		$this->url               = NULL;
		$this->url_thumb         = NULL;
		$this->original_filename = NULL;
	}


	/**
	* Debug
	*/
	public function debug() {
		echo "\nfilename>>".$this->filename."<<";
		echo "\nheight>>".$this->height."<<";
		echo "\nwidth>>".$this->width."<<";
		echo "\ntype>>".$this->type."<<";
		echo "\nurl>>".$this->url."<<";
		echo "\nurl_thumb>>".$this->url_thumb."<<";
		echo "\noriginal_filename>>".$this->original_filename."<<\n";
	}
}






/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        lpfPatient
* @version      1.2
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class lpfPatient {

	/**
	* todo descriptions
	* @var	string
	* var boolean,array
	*/

	public $uuid;

	public $distributionId;
	public $sendId;
	public $dateTimeSent;
	public $distributionStatus;
	public $distributionType;
	public $combinedConfidentiality;
	public $keyword; // array
	public $targetArea;
	public $contentDescription;
	public $version;
	public $login;
	public $personId;
	public $eventName;
	public $orgName;
	public $orgId;
	public $lastName;
	public $firstName;
	public $gender;
	public $genderEnum;
	public $genderEnumDesc;
	public $peds;
	public $pedsEnum;
	public $pedsEnumDesc;
	public $triageCategory;
	public $triageCategoryEnum;
	public $triageCategoryEnumDesc;

	public $sahanaStatus;
	public $sahanaAgeGroup;
	public $sahanaAge;
	public $sahanaNotes;
	public $sahanaLastLocation;
	public $sahanaGPS;

	public $images;
	public $incident_id;

	public $emailSubject;
	public $emailDate;
	public $emailFrom;

	public $lpfFile;
	public $lpfArray;
	public $lpfFileXmlString;


	/**
	* Constructor:
	*/
	public function	__construct($subject, $date, $from, $incident_id) {
		$this->emailSubject = $subject;
		$this->emailDate    = $date;
		$this->emailFrom    = $from;
		$this->incident_id  = $incident_id;
		$this->lpfFile      = NULL;
		$this->lpfArray     = NULL;
		$this->images       = NULL;
		$this->imageCount   = 0;
		$this->uuid         = 0;
	}



	/**
	* Destructor
	*/
	public function __destruct() {}



	public function parseXML($xmlString) {
		$converted = new xml2array();
		$converted->setXML($xmlString);
		$a = $converted->getArray();
		$this->distributionId          = $a['EDXLDistribution']['distributionID']['#text'];
		$this->sendId                  = $a['EDXLDistribution']['senderID']['#text'];
		$this->dateTimeSent            = $a['EDXLDistribution']['dateTimeSent']['#text'];
		$this->distributionStatus      = $a['EDXLDistribution']['distributionStatus']['#text'];
		$this->distributionType        = $a['EDXLDistribution']['distributionType']['#text'];
		$this->combinedConfidentiality = $a['EDXLDistribution']['combinedConfidentiality']['#text'];
		$this->keyword                 = $a['EDXLDistribution']['keyword']['value']; // array, index starting at 0, containing subarrays of keywords (#text)
		$this->targetArea              = $a['EDXLDistribution']['targetArea']['circle']['#text'];
		$this->contentDescription      = $a['EDXLDistribution']['contentObject']['contentDescription']['#text'];
		$this->version                 = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['version']['#text'];
		$this->login                   = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['login']['username']['#text'];
		$this->personId                = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['personId']['#text'];
		$this->eventName               = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventName']['#text'];
		$this->orgName                 = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgName']['#text'];
		$this->orgId                   = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgId']['#text'];
		$this->lastName                = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName']['#text'];
		$this->firstName               = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName']['#text'];
		$this->gender                  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['gender']['#text'];
		$this->genderEnum              = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['genderEnum']['#text'];
		$this->genderEnumDesc          = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['genderEnumDesc']['#text'];
		$this->peds                    = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['peds']['#text'];
		$this->pedsEnum                = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['pedsEnum']['#text'];
		$this->pedsEnumDesc            = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['pedsEnumDesc']['#text'];
		$this->triageCategory          = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategory']['#text'];
		$this->triageCategoryEnum      = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategoryEnum']['#text'];
		$this->triageCategoryEnumDesc  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategoryEnumDesc']['#text'];
		$this->lpfFileXmlString        = $xmlString;
		$this->lpfArray                = $a;
	}


	public function dupeCheck() {
		global $global;

		// find out if we have seen this email before
		$q = "SELECT * FROM mpres_log WHERE email_subject = '".$this->emailSubject."' AND email_from = '".$this->emailFrom."' AND email_date = '".$this->emailDate."';";
		$res = $global['db']->Execute($q);
		if ($res && $res->RecordCount() > 0) {
			return TRUE;
		} else {
			$this->create_uuid();
			return FALSE;
		}
	}



	/* The patient is inserted as a person (non-missing) then status set to correspond to the Triage Status
		Alive:    Green, BH Green
		Injured:  Yellow, Red, Gray
		Deceased: Black
	*/
	public function insertPatient() {
		global $global;

		// insert person
		$q1 = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name) VALUES ('".$this->uuid."','".$this->firstName." ".$this->lastName."','".$this->lastName."',NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = "INSERT INTO person_missing (p_uuid,last_seen,last_clothing,comments) VALUES ('".$this->uuid."', '".$this->orgName         ."', NULL, NULL);";
		$res = $global['db']->Execute($q2);

		// insert a person's images
		for ($i = 0; $i < sizeof($this->images); $i++) {
			$q3 = "INSERT INTO image (x_uuid,image,image_type,image_height,image_width,created,category) VALUES ('".$this->uuid."','".addslashes($this->images[$i]->data)."','".$this->images[$i]->type."','".$this->images[$i]->height."','".$this->images[$i]->width."',CURRENT_TIMESTAMP, 'person');";
			$res = $global['db']->Execute($q3);
		}

		// insert an assignment of this person to the correct incident
		$q4 = "INSERT INTO resource_to_incident (x_uuid,incident_id) VALUES ('".$this->uuid."','".$this->incident_id."');";
		$res = $global['db']->Execute($q4);

		// figure out the person's status
		switch($this->triageCategory) {
			case "Black" :
				$opt_status = "dec";
				break;
			case "Yellow" :
			case "Red" :
			case "Gray" :
				$opt_status = "inj";
				break;
			case "Green" :
			case "BH Green" :
			default :
				$opt_status = "ali";
				break;
		}
		// insert person's status
		$q5 = "INSERT INTO person_status (p_uuid, opt_status, isvictim) VALUES ( '".$this->uuid."', '".$opt_status."', TRUE);";
		$res = $global['db']->Execute($q5);
/*
		// insert person's physical appearance
		$q6 = "INSERT INTO person_physical (p_uuid, comments) VALUES ('".$this->uuid."', '".$this->triageCategoryEnumDesc."');";
		$res = $global['db']->Execute($q6);
*/
		// insert into mpres_log
		$q7 = "INSERT INTO mpres_log (p_uuid,email_subject,email_from,email_date,update_time) VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);


		// figure out the person's sex
		switch($this->gender) {
			case "M" :
				$opt_sex = "mal";
				break;
			case "F" :
				$opt_sex = "fml";
				break;
			default :
				$opt_sex = $this->gender;
				break;
		}


		// insert person's details
		$q8 = "INSERT INTO person_details (p_uuid, opt_gender) VALUES ('".$this->uuid."', '".$opt_sex."');";
		$res = $global['db']->Execute($q8);

		// save all fields to the mpres_patient table
		// temporary until EDXL classes and tables are implemented -- this is where we will save this data in the future
		$q9 = "INSERT INTO mpres_patient (p_uuid, distributionId, sendId, dateTimeSent, distributionStatus, distributionType, combinedConfidentiality, keyword, targetArea, contentDescription, 	version, login, personId, eventName, orgName, orgId, lastName, firstName, gender, genderEnum, genderEnumDesc, peds, pedsEnum, pedsEnumDesc, triageCategory, triageCategoryEnum, triageCategoryEnumDesc, lpfFileXmlString, lpfArray) VALUES ('".$this->uuid."', '".$this->distributionId."', '".$this->sendId."', '".$this->dateTimeSent."', '".$this->distributionStatus."', '".$this->distributionType."', '".$this->combinedConfidentiality."', '".$this->keyword."', '".$this->targetArea."', '".$this->contentDescription."', '".$this->version."', '".$this->login."', '".$this->personId."', '".$this->eventName."', '".$this->orgName."', '".$this->orgId."', '".$this->lastName."', '".$this->firstName."', '".$this->gender."', '".$this->genderEnum."', '".$this->genderEnumDesc."', '".$this->peds."', '".$this->pedsEnum."', '".$this->pedsEnumDesc."', '".$this->triageCategory."', '".$this->triageCategoryEnum."', '".$this->triageCategoryEnumDesc."', '".$this->lpfFileXmlString."', '".serialize($this->lpfArray)."');";
		$res = $global['db']->Execute($q9);

	}




	public function iPhoneParse($body) {
		$b = explode("\r", $body);

		$this->distributionId          = "";
		$this->sendId                  = trim($b[16]);
		$this->dateTimeSent            = trim($b[10]);
		$this->distributionStatus      = "";
		$this->distributionType        = "";
		$this->combinedConfidentiality = "";
		$this->keyword                 = "";
		$this->targetArea              = "";
		$this->contentDescription      = "";
		$this->version                 = "";
		$this->login                   = "";
		$this->personId                = trim($b[0])."-".substr(md5($this->sendId), 0, 5);
		$this->eventName               = "";
		$this->orgName                 = "";
		$this->orgId                   = "";
		$this->lastName                = trim($b[2]);
		$this->firstName               = trim($b[1]);
		$this->gender                  = trim($b[4]);
		$this->genderEnum              = "";
		$this->genderEnumDesc          = "";
		$this->peds                    = "";
		$this->pedsEnum                = "";
		$this->pedsEnumDesc            = "";
		$this->triageCategory          = "";
		$this->triageCategoryEnum      = "";
		$this->triageCategoryEnumDesc  = "";
		$this->lpfFileXmlString        = $body;
		$this->lpfArray                = $b;
		$this->sahanaStatus            = trim($b[3]);
		$this->sahanaAgeGroup          = trim($b[5]);
		$this->sahanaAge               = ""; //trim($b[6]);
		$this->sahanaNotes             = trim($b[11]);
		$this->sahanaLocationStatus    = trim($b[6]);
		$this->sahanaLastLocation      = trim($b[7]);
		$this->sahanaGPS               = trim($b[9]);
		$appName                       = trim($b[17]);
		$appVersion                    = trim($b[18]);

		/*
			[0] => ID: HAITI-20100127-0002
			[1] => Given Name: Mickey
			[2] => Family Name: Mouse
			[3] => Health Status: Alive & Well
			[4] => Gender: Male
			[5] => Age Group: 0-17
			[6] => Estimated Age: 16
			[7] => Location Status: Known
			[8] => Current Location: Walt Disney World, Kissimmee FL
			[9] => GPS: 39.1812N, 77.1788W
			[10] => Event Creation Timestamp: 2010-01-27 01:33:10 -0500
			[11] => Notes: test image
			[12] => UDID: ec3842f4f41b563790c82e394d4e6ec40ba86b68
			[13] => App Name: Found in Haiti
			[14] => Version: 0.3.1


			[0] => ID: HAITI-20100409-0001
			[1] => Given Name: Jane
			[2] => Family Name: Doe
			[3] => Health Status: Alive and Well
			[4] => Gender: Female
			[5] => Age: 20 to 25
			[6] => Location Status: Known
			[7] => Last Seen At: Pentagon Access Rd, Virginia, Arlington, Arlington,
			[8] => 22202, United States
			[9] => GPS: 38.8686N, 77.0543W
			[10] => Event Creation Timestamp: 2010-04-09 14:25:48 -0400
			[11] => Notes: this is a sample note
			[12] => Crop x: 207
			[13] => Crop y: 44
			[14] => Crop width: 221
			[15] => Crop height: 221
			[16] => UDID: 17132cc6679f115644254df38e3ec20f85522abe
			[17] => App Name: Reunite
			[18] => Version: 1.1
		*/

		$appName                    = mysql_real_escape_string(str_ireplace("App Name: ",                 "", $appName));
		$appVersion                 = mysql_real_escape_string(str_ireplace("Version: ",                  "", $appVersion));
		$this->sendId               = mysql_real_escape_string(str_ireplace("UDID: ",                     "", $this->sendId));
		$this->dateTimeSent         = mysql_real_escape_string(str_ireplace("Event Creation Timestamp: ", "", $this->dateTimeSent));
		$this->personId             = mysql_real_escape_string(str_ireplace("ID: ",                       "", $this->personId));
		$this->lastName             = mysql_real_escape_string(str_ireplace("Family Name: ",              "", $this->lastName));
		$this->firstName            = mysql_real_escape_string(str_ireplace("Given Name: ",               "", $this->firstName));
		$this->sahanaAgeGroup       = mysql_real_escape_string(str_ireplace("Age: ",                      "", $this->sahanaAgeGroup));
		$this->sahanaAge            = mysql_real_escape_string(str_ireplace("Estimated Age: ",            "", $this->sahanaAge));
		$this->sahanaNotes          = mysql_real_escape_string(str_ireplace("Notes: ",                    "", $this->sahanaNotes));
		$this->sahanaLocationStatus = mysql_real_escape_string(str_ireplace("Location Status: ",          "", $this->sahanaLocationStatus));
		$this->sahanaLastLocation   = mysql_real_escape_string(str_ireplace("Current Location: ",         "", $this->sahanaLastLocation));
		$this->sahanaGPS            = mysql_real_escape_string(str_ireplace("GPS: ",                      "", $this->sahanaGPS));
		$this->sahanaStatus         = mysql_real_escape_string(str_ireplace("Health Status: ",            "", $this->sahanaStatus));

		// Alive & Well / Injured / Deceased / Unknown
		if ($this->sahanaStatus == "Alive & Well") {
			$this->sahanaStatus = "ali";
		} else if ($this->sahanaStatus == "Injured") {
			$this->sahanaStatus = "inj";
		} else if ($this->sahanaStatus == "Deceased") {
			$this->sahanaStatus = "dec";
		} else if ($this->sahanaLocationStatus == "Missing") {
			$this->sahanaStatus = "mis";
		} else {
			$this->sahanaStatus = "unk";
		}

		// Male / Female / Unknown
		if ($this->gender == "Male") {
			$this->gender = "mal";
		} else if ($this->gender == "Female") {
			$this->gender = "fml";
		} else {
			$this->gender = "unk";
		}
	}



	public function insertPerson2() {
		global $global;

		// insert person
		$q1 = "INSERT INTO person_uuid (p_uuid, full_name, family_name, l10n_name) VALUES ('".$this->personId."','".$this->firstName." ".$this->lastName."','".$this->lastName."',NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = "INSERT INTO person_missing (p_uuid, last_seen, last_clothing, comments) VALUES ('".$this->personId."', '".$this->sahanaLastLocation." (".$this->sahanaGPS.")', NULL, '".$this->sahanaNotes."');";
		$res = $global['db']->Execute($q2);

		// insert a person's images
		for ($i = 0; $i < sizeof($this->images); $i++) {

			// we are now stroing images in a cache on the web server vs. the database to reduce cpu usage when the server is being raped
			$newFileName = str_replace("/", "SLASH", $this->uuid).$i.".".$this->images[$i]->type;
			$newFilePath = "../../www/tmp/mpres_cache/";
			shell_exec("mv ".$this->images[$i]->file." ".$newFilePath.$newFileName);

			shn_image_resize_height($newFilePath.$newFileName, $newFilePath."thumb_".$newFileName, 320);

			$q3 = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width, created, category, url) VALUES (
				'".$this->personId."',
				NULL,
				'".$this->images[$i]->type."',
				'".$this->images[$i]->height."',
				'".$this->images[$i]->width."',
				CURRENT_TIMESTAMP,
				'person',
				'/tmp/mpres_cache/".$newFileName."');";

			$res = $global['db']->Execute($q3);
		}

		// insert an assignment of this person to the correct incident
		$q4 = "INSERT INTO resource_to_incident (x_uuid, incident_id) VALUES ('".$this->personId."','".$this->incident_id."');";
		$res = $global['db']->Execute($q4);

		// insert person's status
		$q5 = "INSERT INTO person_status (p_uuid, opt_status, isvictim) VALUES ( '".$this->personId."', '".$this->sahanaStatus."', TRUE);"; // current timestamp
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = "INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time) VALUES ('".$this->personId."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);

		// insert person's details
		$q8 = "INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old) VALUES ('".$this->personId."', '".$this->sahanaAgeGroup."', '".$this->gender."', '".$this->sahanaAge."');";
		$res = $global['db']->Execute($q8);

		// insert person who reported them
		$q10 = "INSERT INTO person_uuid (p_uuid) VALUES ('".$this->personId."');";
		$res = $global['db']->Execute($q10);

		// insert person
		$q11 = "INSERT INTO person_to_report (p_uuid, rep_uuid) VALUES ('".$this->sendId."','".$this->personId."');";
		$res = $global['db']->Execute($q11);

//echo $q1."\n".$q2."\n".$q3."\n".$q4."\n".$q5."\n".$q7."\n".$q8."\n".$q9."\n".$q10."\n".$q11."\n";

	}




public function findSahanaStatus() {
               $l = strtolower($this->emailSubject);

               // English missing:
               if (stripos($l, "missing", 0)) {
                       //$this->emailSubject = str_ireplace("missing", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "lost", 0)) {
                       //$this->emailSubject = str_ireplace("lost", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "looking for", 0)) {
                       //$this->emailSubject = str_ireplace("looking for", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "find", 0)) {  // typically "to find"
                       //$this->emailSubject = str_ireplace("find", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               // French missing:
               } else if (stripos($l, "disparu", 0)) {
                       //$this->emailSubject = str_ireplace("disparu", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "perdu", 0)) {
                       //$this->emailSubject = str_ireplace("perdu", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "a la recherche de", 0)) {  // TO DO: &#224; la recherche de
                       //$this->emailSubject = str_ireplace("a la recherche de", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               } else if (stripos($l, "trouver", 0)) {
                       //$this->emailSubject = str_ireplace("trouver", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               // Creole missing:
               } else if (stripos($l, "moun yap chache", 0)) {  // TO DO: moun yap chaché
                       //$this->emailSubject = str_ireplace("moun yap chache", "", $this->emailSubject);
                       $this->sahanaStatus = "mis";

               // English injured:
               } else if (stripos($l, "injured", 0)) {
                       //$this->emailSubject = str_ireplace("injured", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "hurt", 0)) {
                       //$this->emailSubject = str_ireplace("hurt", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "wounded", 0)) {
                       //$this->emailSubject = str_ireplace("wounded", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "sick", 0)) {
                       //$this->emailSubject = str_ireplace("sick", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "treated", 0)) {
                       //$this->emailSubject = str_ireplace("treated", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "recovering", 0)) {
                       //$this->emailSubject = str_ireplace("recovering", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               // French injured:
               } else if (stripos($l, "blesse", 0)) { // TO DO: bless&#233;
                       //$this->emailSubject = str_ireplace("blesse", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "mal en point", 0)) {
                       //$this->emailSubject = str_ireplace("mal en point", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "malade", 0)) {
                       //$this->emailSubject = str_ireplace("malade", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "soigne", 0)) { // TO DO: soign&#233;
                       //$this->emailSubject = str_ireplace("soigne", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               } else if (stripos($l, "convalescent", 0)) {
                       //$this->emailSubject = str_ireplace("convalescent", "", $this->emailSubject);
                       $this->sahanaStatus = "inj";

               // Creole injured:
               // blesse [and TO DO blessé] - Already covered by French

               // English dead:
               } else if (stripos($l, "deceased", 0)) {
                       //$this->emailSubject = str_ireplace("deceased", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "dead", 0)) {
                       //$this->emailSubject = str_ireplace("dead", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "died", 0)) {
                       //$this->emailSubject = str_ireplace("died", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "buried", 0)) {
                       //$this->emailSubject = str_ireplace("buried", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // English deceased:
               } else if (stripos($l, "deceased", 0)) {
                       //$this->emailSubject = str_ireplace("deceased", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "dead", 0)) {
                       //$this->emailSubject = str_ireplace("dead", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "died", 0)) {
                       //$this->emailSubject = str_ireplace("died", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "buried", 0)) {
                       //$this->emailSubject = str_ireplace("buried", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // French deceased:
               } else if (stripos($l, "decede", 0)) {  // TO DO:  D&#233;c&#233;d&#233;
                       //$this->emailSubject = str_ireplace("decede", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "mort", 0)) {
                       //$this->emailSubject = str_ireplace("mort", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               } else if (stripos($l, "inhume", 0)) {  // TO DO:  inhum&#233;
                       //$this->emailSubject = str_ireplace("inhume", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // Creole deceased:
               } else if (stripos($l, "mouri", 0)) {
                       //$this->emailSubject = str_ireplace("mouri", "", $this->emailSubject);
                       $this->sahanaStatus = "dec";

               // English alive:
               } else if (stripos($l, "alive & well", 0)) {
                       //$this->emailSubject = str_ireplace("alive & well", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "alive and well", 0)) {
                       //$this->emailSubject = str_ireplace("alive and well", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "alive", 0)) { // do separate "alive", "well" words *after* phrase forms of "alive & well"
                       //$this->emailSubject = str_ireplace("alive", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "well", 0)) {
                       //$this->emailSubject = str_ireplace("well", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "okay", 0)) {
                       //$this->emailSubject = str_ireplace("okay", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "ok", 0)) { // do *after* okay
                       //$this->emailSubject = str_ireplace("ok", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "good", 0)) {
                       //$this->emailSubject = str_ireplace("good", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "recovered", 0)) {
                       //$this->emailSubject = str_ireplace("recovered", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "fine", 0)) {
                       //$this->emailSubject = str_ireplace("fine", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               // French alive:  // Note: "ok", "OK" handled under English
               } else if (stripos($l, "en vie", 0)) {
                       //$this->emailSubject = str_ireplace("en vie", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "vivant", 0)) {
                       //$this->emailSubject = str_ireplace("vivant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "bien portant", 0)) {
                       //$this->emailSubject = str_ireplace("bien portant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "en bonne sante", 0)) {  // TO DO: en bonne sant&#233;
                       //$this->emailSubject = str_ireplace("en bonne sante", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "gueri", 0)) {  // TO DO: gu&#233;ri
                       //$this->emailSubject = str_ireplace("gueri", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "bien portant", 0)) {
                       //$this->emailSubject = str_ireplace("bien portant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               // Creole alive & well
               } else if (stripos($l, "vivant ak anfom", 0)) {
                       //$this->emailSubject = str_ireplace("vivant ak anfom", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "vivant", 0)) { // Should be *after* compound form "vivant ak anfom"
                       //$this->emailSubject = str_ireplace("vivant", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else if (stripos($l, "anfom", 0)) { // Should be *after* compound form "vivant ak anfom"
                       //$this->emailSubject = str_ireplace("anfom", "", $this->emailSubject);
                       $this->sahanaStatus = "ali";

               } else {
                       $this->sahanaStatus = "unk";
               }
       }



	/* inserting a person
		~~~~~~~
	*/
	public function insertPerson() {
		global $global;

		// insert person
		$q1 = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name) VALUES ('".$this->uuid."','".$this->emailSubject."',NULL,NULL);";
		$res = $global['db']->Execute($q1);

		// insert person's missing status
		$q2 = "INSERT INTO person_missing (p_uuid,last_seen,last_clothing,comments) VALUES ('".$this->uuid."', NULL, NULL, NULL);";
		$res = $global['db']->Execute($q2);

		// insert a person's images
		for ($i = 0; $i < sizeof($this->images); $i++) {

			// we are now stroing images in a cache on the web server vs. the database to reduce cpu usage when the server is being raped
			$newFileName = str_replace("/", "SLASH", $this->uuid).$i.".".$this->images[$i]->type;
			$newFilePath = "../../www/tmp/mpres_cache/";
			shell_exec("mv ".$this->images[$i]->file." ".$newFilePath.$newFileName);

			shn_image_resize_height($newFilePath.$newFileName, $newFilePath."thumb_".$newFileName, 320);

			$q3 = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width, created, category, url) VALUES (
				'".$this->uuid."',
				NULL,
				'".$this->images[$i]->type."',
				'".$this->images[$i]->height."',
				'".$this->images[$i]->width."',
				CURRENT_TIMESTAMP,
				'person',
				'/tmp/mpres_cache/thumb_".$newFileName."');";

			$res = $global['db']->Execute($q3);
		}

		// insert an assignment of this person to the correct incident
		$q4 = "INSERT INTO resource_to_incident (x_uuid,incident_id) VALUES ('".$this->uuid."','".$this->incident_id."');";
		$res = $global['db']->Execute($q4);

		// insert person's status
		$q5 = "INSERT INTO person_status (p_uuid, opt_status, isvictim) VALUES ( '".$this->uuid."', '".$this->sahanaStatus."', TRUE);";
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = "INSERT INTO mpres_log (p_uuid,email_subject,email_from,email_date,update_time) VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);

/*
		// figure out the person's sex
		switch($this->gender) {
			case "M" :
				$opt_sex = "mal";
				break;
			case "F" :
				$opt_sex = "fml";
				break;
			default :
				$opt_sex = $this->gender;
				break;
		}


		// insert person's details
		$q8 = "INSERT INTO person_details (p_uuid, opt_gender) VALUES ('".$this->uuid."', '".$opt_sex."');";
		$res = $global['db']->Execute($q8);
*/

		// save all fields to the mpres_patient table
		// temporary until EDXL classes and tables are implemented -- this is where we will save this data in the future
		$q9 = "INSERT INTO mpres_patient (p_uuid, distributionId, sendId, dateTimeSent, distributionStatus, distributionType, combinedConfidentiality, keyword, targetArea, contentDescription, 	version, login, personId, eventName, orgName, orgId, lastName, firstName, gender, genderEnum, genderEnumDesc, peds, pedsEnum, pedsEnumDesc, triageCategory, triageCategoryEnum, triageCategoryEnumDesc, lpfFileXmlString, lpfArray) VALUES ('".$this->uuid."', '".$this->distributionId."', '".$this->sendId."', '".$this->dateTimeSent."', '".$this->distributionStatus."', '".$this->distributionType."', '".$this->combinedConfidentiality."', '".$this->keyword."', '".$this->targetArea."', '".$this->contentDescription."', '".$this->version."', '".$this->login."', '".$this->personId."', '".$this->eventName."', '".$this->orgName."', '".$this->orgId."', '".$this->lastName."', '".$this->firstName."', '".$this->gender."', '".$this->genderEnum."', '".$this->genderEnumDesc."', '".$this->peds."', '".$this->pedsEnum."', '".$this->pedsEnumDesc."', '".$this->triageCategory."', '".$this->triageCategoryEnum."', '".$this->triageCategoryEnumDesc."', '".$this->lpfFileXmlString."', '".serialize($this->lpfArray)."');";
		$res = $global['db']->Execute($q9);
	}




	private function create_uuid() {
		$this->uuid = shn_create_uuid();
	}

	/*
	INSERT INTO person_uuid ( p_uuid , full_name , family_name , l10n_name ) VALUES ( '8y2fp-27', 'Mujestica', 'Allahary', 'Mua' )
	INSERT INTO person_to_report ( p_uuid , rep_uuid , relation ) VALUES ( '8y2fp-27', '8y2fp-3', 'Not Specified' )
	INSERT INTO identity_to_person ( p_uuid , serial , opt_id_type ) VALUES ( '8y2fp-27', 'M-652-299-399-499', 'nic' )
	INSERT INTO identity_to_person ( p_uuid , serial , opt_id_type ) VALUES ( '8y2fp-27', 'DJ-617-9999-420-000002', 'pas' )
	INSERT INTO identity_to_person ( p_uuid , serial , opt_id_type ) VALUES ( '8y2fp-27', 'DL-9999-8888-7777', 'dln' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '1234 Street St.', 'hom' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '911-911-9111', 'curr' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '911-911-9112', 'cmob' )
	INSERT INTO contact ( pgoc_uuid , contact_value , opt_contact_type ) VALUES ( '8y2fp-27', '21999', 'zip' )
	INSERT INTO phonetic_word ( encode1 , encode2 , pgl_uuid ) VALUES ( 'M223', 'MJSTK', '8y2fp-27' )
	INSERT INTO phonetic_word ( encode1 , encode2 , pgl_uuid ) VALUES ( 'A460', 'ALHR', '8y2fp-27' )
	INSERT INTO phonetic_word ( encode1 , encode2 , pgl_uuid ) VALUES ( 'M000', 'M', '8y2fp-27' )
	INSERT INTO location_details ( pgoc_uuid , contact_value , opt_contact_type , postcode ) VALUES ( '8y2fp-27', '911-911-9112', 'cmob', '21999' )
	INSERT INTO person_physical ( p_uuid , opt_eye_color , opt_skin_color , opt_hair_color , height , weight , opt_blood_type , comments ) VALUES ( '8y2fp-27', 'blu', 'whi', 'bro', '135', '125', 'a+', 'smile' )
	INSERT INTO person_missing ( p_uuid , last_seen , last_clothing , comments ) VALUES ( '8y2fp-27', 'The mall', 'jeans, shirt', 'shes a flirt' )
	INSERT INTO person_details ( p_uuid , birth_date , opt_age_group , opt_gender , opt_marital_status , opt_religion , opt_race ) VALUES ( '8y2fp-27', '1990-05-01', 'adu', 'fml', 'sin', 'bud', 'filip' )
	INSERT INTO person_status ( p_uuid , opt_status , isvictim ) VALUES ( '8y2fp-27', 'mis', TRUE )
	INSERT INTO resource_to_incident ( x_uuid , incident_id ) VALUES ( '8y2fp-27', '1' )
	*/
}






/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        nameParser
* @version      1.1
* @author       Greg Miernicki <g@miernicki.com>
* @author       Keith Beckman
* @author       DLM
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class nameParser {

	/**
	* Array of possible name titles.
	* @var	array
	*/
	private $titles;

	/**
	* Array of possible last name prefixes.
	* @var	array
	*/
	private $prefices;

	/**
	* Array of possible name suffices.
	* @var	array;
	*/
	private $suffices;

	/**
	* The TITLE ie. Dr., Mr. Mrs., etc...
	* @var	string
	*/
	private $title;

	/**
	* The FIRST Name
	* @var	string
	*/
	private $first;

	/**
	* The MIDDLE Name
	* @var	string
	*/
	private $middle;

	/**
	* The LAST Name
	* @var	string
	*/
	private $last;

	/**
	* Name addendum ie. III, Sr., etc...
	* @var	string
	*/
	private $suffix;

	/**
	* Full name string passed to class
	* @var	string
	*/
	private $fullName;

	/**
	* Set to false by default, but set to true if parse() is executed on a name that is not parseable
	* @var	boolean
	*/
	private $notParseable;


	/**
	* Constructor:
	* Setup the object, initialise the variables, and if instantiated with a name - parse it automagically
	*
	* @param string The Name String
	* @access public
	*/
	public function	__construct( $initString = "" ) {
		$this->title 		= "";
		$this->first 		= "";
		$this->middle 		= "";
		$this->last 		= "";
		$this->suffix 		= "";

		// added Military Titles
		$this->titles		= array('dr','doctor','miss','misses','mr','mister','mrs','ms','judge','sir','madam','madame','AB','2ndLt','Amn','1stLt','A1C','Capt','SrA','Maj','SSgt','LtCol','TSgt','Col','BrigGen','1stSgt','MajGen','SMSgt','LtGen','1stSgt','Gen','CMSgt','1stSgt','CCMSgt','CMSAF','PVT','2LT','PV2','1LT','PFC','CPT','SPC','MAJ','CPL','LTC','SGT','COL','SSG','BG','SFC','MG','MSG','LTG','1SGT','GEN','SGM','CSM','SMA','WO1','WO2','WO3','WO4','WO5','ENS','SA','LTJG','SN','LT','PO3','LCDR','PO2','CDR','PO1','CAPT','CPO','RADM(LH)','SCPO','RADM(UH)','MCPO','VADM','MCPOC','ADM','MPCO-CG','CWO-2','CWO-3','CWO-4','Pvt','2ndLt','PFC','1stLt','LCpl','Capt','Cpl','Maj','Sgt','LtCol','SSgt','Col','GySgt','BGen','MSgt','MajGen','1stSgt','LtGen','MGySgt','Gen','SgtMaj','SgtMajMC','WO-1','CWO-2','CWO-3','CWO-4','CWO-5','ENS','SA','LTJG','SN','LT','PO3','LCDR','PO2','CDR','PO1','CAPT','CPO','RDML','SCPO','RADM','MCPO','VADM','MCPON','ADM','FADM','WO1','CWO2','CWO3','CWO4','CWO5');

		$this->prefices		= array('bon','ben','bin','da','dal','de','del','der','de','e','la','le','san','st','ste','van','vel','von');
		$this->suffices		= array('esq','esquire','jr','sr','2','i','ii','iii','iv','v','clu','chfc','cfp','md','phd');
		$this->fullName		= "";
		$this->notParseable 	= FALSE;

		// if initialized by value, set class variable and then parse
		if ( $initString != "" ) {
			$this->fullName = $initString;
			$this->parse();
		}
	}


	/**
	* Destructor
	* @access public
	*/
	public function __destruct() {}



	/**
	* Access Method
	* @access public
	*/
	public function	getFirstName() { return $this->first; }



	/**
	* Access Method
	* @access public
	*/
	public function	getMiddleName() { return $this->middle; }



	/**
	* Access Method
	* @access public
	*/
	public function	getLastName() { return $this->last; }



	/**
	* Access Method
	* @access public
	*/
	public function	getTitle() { return $this->title; }



	/**
	* Access Method
	* @access public
	*/
	public function	getSuffix() { return $this->suffix; }



	/**
	* Access Method
	* @access public
	*/
	public function	getNotParseable() { return $this->notParseable; }



	/**
	* Mutator Method
	* @access public
	* @param newFullName the new value to set fullName to
	*/
	public function	setFullName( $newFullName ) { $this->fullName = $newFullName; }



	/**
	* Determine if the needle is in the haystack.
	*
	* @param needle the needle to look for
	* @param haystack the haystack from which to look into
	* @access private
	*/
	private function inArrayNorm( $needle, $haystack ) {
		$needle = trim( strtolower( str_replace( '.', '', $needle ) ) );
		return	in_array( $needle, $haystack );
	}



	/**
	* Extract the elements of the full name into separate parts.
	*
	* @access public
	*/
	public function	parse() {
		// reset values
		$this->title 		= "";
		$this->first 		= "";
		$this->middle 		= "";
		$this->last 		= "";
		$this->suffix 		= "";
		$this->notParseable 	= FALSE;

		// break up name based on number of commas
		$pieces		= explode( ',', preg_replace('/\s+/', ' ', trim( $this->fullName ) ) );
		$numPieces 	= count( $pieces );

		switch ( $numPieces ) {

			// array(title first middle last suffix)
			case	1:
				$subPieces = explode(' ', trim( $pieces[0] ) );
				$numSubPieces = count( $subPieces );
				for ( $i = 0; $i < $numSubPieces; $i++ ) {
					$current = trim( $subPieces[$i] );
					if ( $i < ($numSubPieces-1) ) {
						$next = trim( $subPieces[$i+1] );
					} else {
						$next = "";
					}
					if ( $i == 0 && $this->inArrayNorm( $current, $this->titles ) ) {
						$this->title = $current;
						continue;
					}
					if ( $this->first == "" ) {
						$this->first = $current;
						continue;
					}
					if ( $i == $numSubPieces-2 && ($next != "") && $this->inArrayNorm( $next, $this->suffices ) ) {
						if ( $this->last != "") {
							$this->last	.=	" ".$current;
						} else {
							$this->last = $current;
						}
						$this->suffix = $next;
						break;
					}
					if ( $i == $numSubPieces-1 ) {
						if ( $this->last != "" ) {
							$this->last .= " ".$current;
						} else {
							$this->last = $current;
						}
						continue;
					}
					if ( $this->inArrayNorm( $current, $this->prefices ) ) {
						if ( $this->last != "" ) {
							$this->last .= " ".$current;
						} else {
							$this->last = $current;
						}
						continue;
					}
					if ( $next == 'y' || $next == 'Y' ) {
						if ( $this->last != "" ) {
							$this->last .= " ".$current;
						} else {
							$this->last = $current;
						}
						continue;
					}
					if ( $this->last != "" ) {
						$this->last .= " ".$current;
						continue;
					}
					if( $this->middle != "" ) {
						$this->middle .= " ".$current;
					} else {
						$this->middle =	$current;
					}
				}
				break;

			default:
				switch( $this->inArrayNorm( $pieces[1], $this->suffices ) ) {

					// array(title first middle last, suffix [, suffix])
					case	TRUE:
						$subPieces = explode(' ', trim( $pieces[0] ) );
						$numSubPieces =	count( $subPieces );
						for ( $i = 0; $i < $numSubPieces; $i++ ) {
							$current = trim( $subPieces[$i] );
							if ( $i < ($numSubPieces-1) ) {
								$next = trim( $subPieces[$i+1] );
							} else {
								$next = "";
							}
							if ( $i == 0 && $this->inArrayNorm( $current, $this->titles ) ) {
								$this->title = $current;
								continue;
							}
							if ( $this->first == "" ) {
								$this->first = $current;
								continue;
							}
							if ( $i == $numSubPieces-1 ) {
								if ( $this->last != "" ) {
									$this->last .=	" ".$current;
								} else {
									$this->last = $current;
								}
								continue;
							}
							if ( $this->inArrayNorm( $current, $this->prefices ) ) {
								if ( $this->last != "" ) {
									$this->last .= " ".$current;
								} else {
									$this->last = $current;
								}
								continue;
							}
							if ( $next == 'y' || $next == 'Y' ) {
								if ( $this->last != "" ) {
									$this->last .= " ".$current;
								} else {
									$this->last = $current;
								}
								continue;
							}
							if ( $this->last != "" ) {
								$this->last .= " ".$current;
								continue;
							}
							if ( $this->middle != "" ) {
								$this->middle .= " ".$current;
							} else {
								$this->middle = $current;
							}
						}
						$this->suffix =	trim($pieces[1]);
						for ( $i = 2; $i < $numPieces; $i++ ) {
							$this->suffix .= ", ". trim( $pieces[$i] );
						}
						break;

					// array(last, title first middles[,] suffix [,suffix])
					case	FALSE:
						$subPieces = explode( ' ', trim( $pieces[1] ) );
						$numSubPieces =	count( $subPieces );
						for ( $i = 0; $i < $numSubPieces; $i++ ) {
							$current = trim( $subPieces[$i] );
							if ( $i < ($numSubPieces-1) ) {
								$next = trim( $subPieces[$i+1] );
							} else {
								$next = "";
							}
							if ( $i == 0 && $this->inArrayNorm( $current, $this->titles ) ) {
								$this->title = $current;
								continue;
							}
							if ( $this->first == "" ) {
								$this->first = $current;
								continue;
							}
							if ( $i == $numSubPieces-2 && ($next != "") && $this->inArrayNorm( $next, $this->suffices ) ) {
								if ( $this->middle != "" ) {
									$this->middle .= " ".$current;
								} else {
									$this->middle = $current;
								}
								$this->suffix = $next;
								break;
							}
							if ( $i == $numSubPieces-1 && $this->inArrayNorm( $current, $this->suffices ) ) {
								$this->suffix = $current;
								continue;
							}
							if ( $this->middle != "" ) {
								$this->middle .= " ".$current;
							} else {
								$this->middle = $current;
							}
						}
						if( isset($pieces[2]) && $pieces[2] ) {
							if ( $this->last == "" ) {
								$this->suffix = trim( $pieces[2] );
								for ($s = 3; $s < $numPieces; $s++) {
									$this->suffix .= ", ". trim( $pieces[$s] );
								}
							} else {
								for ($s = 2; $s < $numPieces; $s++) {
									$this->suffix .= ", ". trim( $pieces[$s] );
								}
							}
						}
						$this->last = $pieces[0];
						break;
				}
				unset( $pieces );
				break;
		}
		if ( $this->first == "" && $this->middle == "" && $this->last == "" ) {
			$this->notParseable = TRUE;
		}
	}
}






/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        googleGeocoder
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
* @author       Quentin Zervaas <x@phpriot.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class googleGeocoder {
	public static $url = 'http://maps.google.com/maps/geo';

	const G_GEO_SUCCESS             = 200;
	const G_GEO_BAD_REQUEST         = 400;
	const G_GEO_SERVER_ERROR        = 500;
	const G_GEO_MISSING_QUERY       = 601;
	const G_GEO_MISSING_ADDRESS     = 601;
	const G_GEO_UNKNOWN_ADDRESS     = 602;
	const G_GEO_UNAVAILABLE_ADDRESS = 603;
	const G_GEO_UNKNOWN_DIRECTIONS  = 604;
	const G_GEO_BAD_KEY             = 610;
	const G_GEO_TOO_MANY_QUERIES    = 620;

	protected $_apiKey;
	protected $_search;

	public function __construct($search, $key = "") {
		$this->_search = $search;
		$this->_apiKey = $key;
		$this->lookup();
	}


	// http://maps.google.com/maps/geo?q=location&output=json&oe=utf8&sensor=false
	public function performRequest($search, $output = "xml") {
		$url = sprintf("%s?q=%s&output=%s&key=%s&oe=utf-8", self::$url, urlencode($search), $output, $this->_apiKey);
		$ch = curl_init($url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		$response = curl_exec($ch);
		curl_close($ch);
		return $response;
	}


	public function lookup() {
		$response = $this->performRequest($this->_search, "xml");
		$xml      = new SimpleXMLElement($response);
		$status   = (int)$xml->Response->Status->code;
		echo "<pre>".print_r($xml,true)."</pre>\n";
		switch ($status) {
			case self::G_GEO_SUCCESS:
				$placemarks = array();
				foreach ($xml->Response->Placemark as $placemark) {
					$placemarks[] = googlePlacemark::FromSimpleXml($placemark);
				}
				//$placemarks[] = "one item";
				return $placemarks;

			case self::G_GEO_UNKNOWN_ADDRESS:
			case self::G_GEO_UNAVAILABLE_ADDRESS:
				//$placemarks[] = "messed up";
				return $placemarks;

			default:
				throw new Exception(sprintf('Google Geo error %d occurred', $status));
		}
	}
}



// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //



class googlePlacemark {
	const ACCURACY_UNKNOWN      = 0;
	const ACCURACY_COUNTRY      = 1;
	const ACCURACY_REGION       = 2;
	const ACCURACY_SUBREGION    = 3;
	const ACCURACY_TOWN         = 4;
	const ACCURACY_POSTCODE     = 5;
	const ACCURACY_STREET       = 6;
	const ACCURACY_INTERSECTION = 7;
	const ACCURACY_ADDRESS      = 8;

	protected $_point;
	protected $_address;
	protected $_accuracy;



	public function setAddress($address) {
		$this->_address = (string)$address;
	}



	public function getAddress() {
		return $this->_address;
	}



	public function __toString() {
		return $this->getAddress();
	}



	public function setPoint(googlePoint $point) {
		$this->_point = $point;
	}



	public function getPoint() {
		return $this->_point;
	}



	public function setAccuracy($accuracy) {
		$this->_accuracy = (int)$accuracy;
	}



	public function getAccuracy() {
		return $this->_accuracy;
	}



	public static function FromSimpleXml($xml) {
		$point = googlePoint::create($xml->Point->coordinates);
		$placemark = new self;
		$placemark->setPoint($point);
		$placemark->setAddress($xml->address);
		$placemark->setAccuracy($xml->AddressDetails['Accuracy']);
		return $placemark;
	}
}



class googlePoint {
	protected $_lat;
	protected $_lng;

	public function __construct($latitude, $longitude) {
		$this->_lat = $latitude;
		$this->_lng = $longitude;
	}

	public function getLatitude() {
		return $this->_lat;
	}

	public function getLongitude() {
		return $this->_lng;
	}


	public static function create($str) {
		list($longitude, $latitude, $elevation) = explode(',', $str, 3);
		return new self($latitude, $longitude);
	}
}


