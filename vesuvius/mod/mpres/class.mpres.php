<?php
/**
 * @name         MPR Email Service
 * @version      2.0
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0908
 */


global $global;
require_once($global['approot']."/mod/lpf/lib_lpf.inc");

class mpres {
	private $host;
	private $port;
	private $popimap;
	private $ssl;
	private $username;
	private $password;
	private $attachments;
	private $incident_id;
	private $delete_messages;
	private $serverString;
	private $mailbox;
	private $mailboxHeader;
	private $mailboxOpen;
	private $messageCount;
	private $currentMessage;
	private $currentAttachments;
	private $currentMessageHasXML;
	private $currentRandomValue;
	private $currentSubject;
	private $currentFrom;
	private $currentDate;
	private $senderAddress;
	private $person;
	private $email;
	private $XMLversion;
	private $ecode;

	public  $messages; // execution message queue
	public  $startTime; // timestamp of when an object of this type is instantiated
	public  $stopTime; // filled by the spit() method when called


	// constructor
	public function	__construct() {
		// get configuration settings
		$this->host                 = shn_db_get_config("mpres","host");
		$this->port                 = shn_db_get_config("mpres","port");
		$this->popimap              = shn_db_get_config("mpres","popimap");
		$this->ssl                  = shn_db_get_config("mpres","ssl");
		$this->username             = shn_db_get_config("mpres","username");
		$this->password             = shn_db_get_config("mpres","password");
		$this->attachments          = shn_db_get_config("mpres","attachments");
		$this->incident_id          = shn_db_get_config("mpres","incident_id");
		$this->delete_messages      = shn_db_get_config("mpres","delete_messages");
		$this->serverString         = null;
		$this->mailbox              = null;
		$this->mailboxHeader        = null;
		$this->mailboxOpen          = null;
		$this->messageCount         = 0;
		$this->messages             = "\n----------------------------------------------\nscriptExecutedAtTime >> ".date("Ymd:Gis.u")."\n";
		$this->currentMessage       = null;
		$this->currentAttachments   = null;
		$this->currentMessageHasXML = null;
		$this->currentRandomValue   = null;
		$this->currentSubject       = null;
		$this->currentFrom          = null;
		$this->currentDate          = null;
		$this->startTime            = microtime(true);
		$this->stopTime             = null;
		$this->senderAddress        = null;
		$this->person               = null;
		$this->email                = null;
		$this->XMLversion           = null;
		$this->ecode                = null;
		$this->openMailbox();
	}



	// destructor
	public function __destruct() {
		if ($this->mailboxOpen) {
			// purge and close inbox
			if ($this->delete_messages) {
				imap_expunge($this->mailbox);
			}
			imap_close($this->mailbox);
		}
		$this->host                 = null;
		$this->port                 = null;
		$this->popimap              = null;
		$this->ssl                  = null;
		$this->username             = null;
		$this->password             = null;
		$this->attachments          = null;
		$this->incident_id          = null;
		$this->delete_messages      = null;
		$this->serverString         = null;
		$this->mailbox              = null;
		$this->mailboxHeader        = null;
		$this->mailboxOpen          = null;
		$this->messageCount         = null;
		$this->messages             = null;
		$this->currentMessage       = null;
		$this->currentAttachments   = null;
		$this->currentMessageHasXML = null;
		$this->currentRandomValue   = null;
		$this->currentSubject       = null;
		$this->currentFrom          = null;
		$this->currentDate          = null;
		$this->startTime            = null;
		$this->stopTime             = null;
		$this->senderAddress        = null;
		$this->person               = null;
		$this->email                = null;
		$this->XMLversion           = null;
		$this->ecode                = null;
	}


	// as function name implies :)
	public function openMailbox() {
		// build pop/imap settings string
		$sslOption = "";
		if ($this->ssl=="1") {
			$sslOption = "/ssl/novalidate-cert";
		}
		$protocol = "imap";
		if ($this->popimap == "POP") {
			$protocol = "pop3";
		}
		// example server string = "{mail.nih.gov:995/pop3/ssl/novalidate-cert}";
		$this->serverString = "{". $this->host .":". $this->port ."/". $protocol . $sslOption ."}";
		$this->mailbox = imap_open($this->serverString, $this->username, $this->password);
		if ($this->mailboxHeader = imap_check($this->mailbox)) {
			$this->mailboxOpen = TRUE;
			$this->messages .= "Mailbox opened successfully.\n";
		} else {
			$this->mailboxOpen = FALSE;
			$this->messages .= "Mailbox failed to open.\n";
		}
	}


	// traverse the inbox for appropriate messages
	public function loopInbox() {
		global $global;

		// update sequence
		$q = "
			DELETE FROM `mpres_seq`
			WHERE `id` like '%';
		";
		$res = $global['db']->Execute($q);

		$q = "
			INSERT INTO  `mpres_seq` (`id`, `last_executed`)
			VALUES (NULL, CURRENT_TIMESTAMP);
		";
		$res = $global['db']->Execute($q);


		// check mailbox status
		if($this->mailboxOpen == false) {
			$this->messages .= "Can't loop inbox as it's not open!\n";
		} else {
			$this->messageCount = $this->mailboxHeader->Nmsgs;
		}
		if($this->messageCount == 0) {
			$this->messages .= "Not looping inbox, its empty!\n";
		} else {
			$this->messages .= "Number of messages in inbox: ". $this->messageCount ."\n";

			// download all message information from inbox
			$overview = imap_fetch_overview($this->mailbox,"1:".$this->messageCount,0);
			$size = sizeof($overview);

			// loop through each message
			for($i = $size-1; $i >= 0; $i--) {

				$this->person = null; // reset from last person/email...
				$this->person = new person();
				$this->person->init();
				$this->ecode = 0;

				// retrieve current message's data
				$this->currentMessage       = $overview[$i];
				$this->currentSubject       = $this->currentMessage->subject;
				$this->currentDate          = $this->currentMessage->date;
				$this->currentFrom          = $this->currentMessage->from;
				$this->currentAttachments   = null; // reset from last person
				$this->currentAttachments   = array();
				$this->currentMessageHasXML = false;
				$this->senderAddress        = $overview[$i]->from;
				$this->fixDate();           // reformat the date for our purposes
				$this->fixFrom();           // strip extra characters from the from field
				$this->fixAddress();        // fix email address of excess characters
				$this->getAttachmentsAndParseXML($i);  // grab all attachments

				// email has XML attachment....
				if ($this->currentMessageHasXML) {

					// catch all parsing errors...
					if($this->ecode != 0) {
						$this->messages .= "LPF XML email found but failed during parsing with error code: ".$this->ecode.".\n";

					// event is closed... error
					} elseif(!$this->person->isEventOpen()) {
						$this->messages .= "LPF XML email found however, the event being reported to is closed, so the person was not inserted.\n";
						$this->replyError($this->person->shortName);

					// insert!
					} else {
						$this->person->insert();
						$this->messages .= "LPF XML email found and person(".$this->person->p_uuid.") inserted.\n";
						$this->replySuccess($this->person->p_uuid, ""); // FIX event name...
					}

				// unstructured email... attempt to parse subject
				} else {
					$this->person->incident_id = $this->incident_id;
					if(!$this->person->isEventOpen()) {
						$this->messages .= "Unstructured email found, however the event being reported to is closed, so the person was not inserted.\n";
						$this->replyError($this->person->shortName);
					} else {
						$this->person->insert();
						$this->messages .= "Normal email found and person(".$this->person->p_uuid.") inserted.\n";
						$this->replySuccess($this->person->p_uuid, ""); // FIX event name...
					}
				}

				// delete the message from the inbox
				imap_delete($this->mailbox, $i+1);
				$this->messages .= "Message #".$i." deleted.\n";
			}
		}
	}


	// algorithmically find the attachments in this email...
	private function getAttachmentsAndParseXML($messageNumber) {
		$structure = imap_fetchstructure($this->mailbox, $messageNumber+1);
		if (isset($structure->parts) && count($structure->parts)) {
			for ($i=0; $i < count($structure->parts); $i++) {
				$this->currentAttachments[$i] = array(
					'is_attachment' => false,
					'is_image'      => false,
					'is_xml'        => false,
					'type'          => '',
					'filename'      => '',
					'attachment'    => ''
				);
				if ($structure->parts[$i]->ifparameters) {
					foreach($structure->parts[$i]->parameters as $object) {
						if(strtolower($object->attribute) == 'name') {
							$this->currentAttachments[$i]['is_attachment'] = true;
							$this->currentAttachments[$i]['filename'] = strtolower($object->value);
						}
					}
				}
				if ($structure->parts[$i]->ifdparameters) {
					foreach ($structure->parts[$i]->dparameters as $object) {
						if (strtolower($object->attribute) == 'filename') {
							$this->currentAttachments[$i]['is_attachment'] = true;
							$this->currentAttachments[$i]['filename'] = strtolower($object->value);
						}
					}
				}
				if ($this->currentAttachments[$i]['is_attachment']) {
					$this->currentAttachments[$i]['attachment'] = imap_fetchbody($this->mailbox, $messageNumber+1, $i+1);
					if ($structure->parts[$i]->encoding == 3) { // 3 = BASE64
						$this->currentAttachments[$i]['attachment'] = base64_decode($this->currentAttachments[$i]['attachment']);
					}
					elseif ($structure->parts[$i]->encoding == 4) { // 4 = QUOTED-PRINTABLE
						$this->currentAttachments[$i]['attachment'] = quoted_printable_decode($this->currentAttachments[$i]['attachment']);
					}
				}
			}
		}
		for ($i=0; $i < count($this->currentAttachments); $i++) {
			if ($this->currentAttachments[$i]['is_attachment'] == true) {

				$f = $this->currentAttachments[$i]['filename'];
				if(strtolower(substr($f, -4)) == ".jpg" || strtolower(substr($f, -5)) == ".jpeg") {
					$this->currentAttachments[$i]['is_image'] = true;
					$this->currentAttachments[$i]['type']     = "jpg";

				} else if(strtolower(substr($f, -4)) == ".gif") {
					$this->currentAttachments[$i]['is_image'] = true;
					$this->currentAttachments[$i]['type']     = "gif";

				} else if(strtolower(substr($f, -4)) == ".png") {
					$this->currentAttachments[$i]['is_image'] = true;
					$this->currentAttachments[$i]['type']     = "png";

				} else if(strtolower(substr($f, -4)) == ".xml" || strtolower(substr($f, -4)) == ".lpf") {
					$this->currentAttachments[$i]['is_xml']   = true;
					$this->currentAttachments[$i]['type']     = "xml";
					$this->currentMessageHasXML               = true;
				}

				// add the image to our current person...
				if ($this->currentAttachments[$i]['is_image']) {
					$this->person->addImage(base64_encode($this->currentAttachments[$i]['attachment']), $f);
				}

				// handle the XML LPF attachment
				if ($this->currentAttachments[$i]['is_xml']) {
					$this->messages .= "found XML attachment>>(".$f.")\n";
					$a = xml2array($this->currentAttachments[$i]['attachment']);

					// LPF v1.5/1.6 XML from Re-Unite
					if(isset($a['lpfContent'])) {
						$this->person->theString = $this->currentAttachments[$i]['attachment'];
						$this->person->xmlFormat = "REUNITE2";
						$this->ecode = $p->parseXml();

					// LPF v1.2 XML from TriagePic
					} else if(isset($a['EDXLDistribution'])) {
						$this->person->theString = $this->currentAttachments[$i]['attachment'];
						$this->person->xmlFormat = "MPRES1";
						$this->ecode = $p->parseXml();
					}
				}
			}
		}
	}


	// starts out like: "triune@gmail.com" <triune@gmail.com>
	// so turn it into: triune@gmail.com
	public function fixAddress() {
		$e = explode("<", (string)$this->senderAddress);
		$e = explode(">", $e[1]);
		$this->senderAddress = $e[0];
	}


	// split into elements and reformat the date to our preferred format YYYYMMDD_HHMMSS (php ~ Ymd_Gis)
	private function fixDate() {
		list($dayName,$day,$month,$year,$time,$zone) = explode(" ",$this->currentMessage->date);
		list($hour,$minute,$second) = explode(":",$time);
		$month = $this->fixMonth($month);
		$day = str_pad($day, 2, "0", STR_PAD_LEFT);
		$hour = str_pad($hour, 2, "0", STR_PAD_LEFT);
		$minute = str_pad($minute, 2, "0", STR_PAD_LEFT);
		$second = str_pad($second, 2, "0", STR_PAD_LEFT);
		$this->currentMessage->date = $year.$month.$day."_".$hour.$minute.$second;
	}


	// change 3 letter month abbreviation into decimal month
	private function fixMonth($month) {
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


	// fix from field...
	private function fixFrom() {
		$this->currentMessage->from = preg_replace('/"/', '', $this->currentMessage->from);
	}


	// send email with error message...
	private function replyError($name) {
		global $global;
		$p = new pop();

		$subject  = "[AUTO-REPLY]: People Locator Record Submission FAILURE";
		$bodyHTML = "
			Thank you for the person record you submitted for event(".$name."). However, the event you attempted to assign this person to is closed. Therefore your submission has been rejected.<br>
			<br>
			<br>
			<b>- People Locator</b><br>
			<br>
		";
		$bodyAlt = "
			Thank you for the person record you submitted for event(".$name."). However, the event you attempted to assign this person to is closed. Therefore your submission has been rejected.\n
			\n
			\n
			- People Locator\n
			\n
		";
		$p->sendMessage($this->senderAddress, "", $subject, $bodyHTML, $bodyAlt);
	}


	// email sender with success message
	private function replySuccess($uuid, $name="") {
		global $global;
		$p = new pop();

		if(trim($name) == "") {
			$event = "";
		} else {
			$event = " for event (".$name.")";
		}

		$subject  = "[AUTO-REPLY]: People Locator Record Submission SUCCESS";
		$bodyHTML = "
			Thank you for the person record you submitted".$event.". It has been added to our registry and will show up in search results in a few minutes.<br>
			<br>
			You can always view the record (and updates) of this person at the following url:<br>
			<a href=\"https://".$uuid."\">https://".$uuid."</a><br>
			<br>
			<br>
			<b>- People Locator</b><br>
			<br>
		";
		$bodyAlt = "
			Thank you for the person record you submitted".$event.". It has been added to our registry and will show up in search results in a few minutes.\n
			\n
			You can always view the record (and updates) of this person at the following url:\n
			https://".$uuid."</a>\n
			\n
			\n
			- People Locator\n
			\n
		";
		$p->sendMessage($this->senderAddress, "", $subject, $bodyHTML, $bodyAlt);
	}


	// prints the message log...
	public function spit() {
		$this->stopTime = microtime(true);
		$totalTime = $this->stopTime - $this->startTime;
		$this->messages .= "scriptExecutedIn >> ".$totalTime." seconds.\n";
		echo $this->messages;
	}
	// end class
}

