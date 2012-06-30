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


global $global;
require_once($global['approot']."/mod/lpf/lib_lpf.inc");


class mpres {
	private $host;
	private $port;
	private $popimap;
	private $ssl;
	private $username;
	private $password;
	private $incident_id;
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
	private $toggleActivity;
	private $overview;
	private $size;
	private $messages;  // execution message log
	private $startTime; // timestamp of when an object of this type is instantiated
	private $stopTime;  // filled by the spit() method when called... represents end time


	// constructor
	public function	__construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		// get configuration settings
		$this->host                 = shn_db_get_config("mpres","host");
		$this->port                 = shn_db_get_config("mpres","port");
		$this->popimap              = shn_db_get_config("mpres","popimap");
		$this->ssl                  = shn_db_get_config("mpres","ssl");
		$this->username             = shn_db_get_config("mpres","username");
		$this->password             = shn_db_get_config("mpres","password");
		$this->incident_id          = shn_db_get_config("mpres","incident_id");
		$this->serverString         = null;
		$this->mailbox              = null;
		$this->mailboxHeader        = null;
		$this->mailboxOpen          = null;
		$this->messageCount         = 0;
		$this->messages             = "";
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
		$this->toggleActivity       = false;
		$this->overview             = null;
		$this->size                 = null;
		$this->go();
	}


	// destructor
	public function __destruct() {
		$this->closeMailbox();
		$this->host                 = null;
		$this->port                 = null;
		$this->popimap              = null;
		$this->ssl                  = null;
		$this->username             = null;
		$this->password             = null;
		$this->incident_id          = null;
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
		$this->toggleActivity       = null;
		$this->overview             = null;
		$this->size                 = null;
	}


	private function go() {
		$this->openMailbox();
		if($this->mailboxOpen == true) {
			$this->messageCount = $this->mailboxHeader->Nmsgs;
			if($this->messageCount == 0) {
				$this->messages .= "Inbox is empty.<br>";
			} else {
				$this->messages .= "Number of messages in inbox: ". $this->messageCount ."<br>";
				$this->loopInbox();
			}
		}
		$this->updateSequence();
	}


	// traverse the inbox for appropriate messages
	private function loopInbox() {

		global $global;

		// download all message information from inbox
		$this->overview = imap_fetch_overview($this->mailbox,"1:".$this->messageCount,0);
		$this->size = sizeof($this->overview);

		// loop through each message
		for($i = $this->size-1; $i >= 0; $i--) {

			$raw = imap_fetchstructure($this->mailbox, $i);
			error_log("DUMPPPPPP::>>".var_export($raw)."<<::::");

			$this->person = null; // clear out the last person...
			$this->person = new person();
			$this->person->init();
			$this->person->rep_uuid = 2;
			$this->ecode = 0;
			$this->toggleActivity = true;

			// retrieve current message's data
			$this->currentMessage       = $this->overview[$i];
			$this->currentSubject       = $this->currentMessage->subject;
			$this->currentDate          = $this->currentMessage->date;
			$this->currentFrom          = $this->currentMessage->from;
			$this->currentAttachments   = null; // reset from last person
			$this->currentAttachments   = array();
			$this->currentMessageHasXML = false;
			$this->senderAddress        = $this->overview[$i]->from;
			$this->fixDate();           // reformat the date for our purposes
			$this->fixFrom();           // strip extra characters from the from field
			$this->fixAddress();        // fix email address of excess characters
			$this->getAttachmentsAndParseXML($i);  // grab all attachments

			$this->messages .= "From: ".$this->currentFrom."<br>";
			$this->messages .= "Subject: ".$this->currentSubject."<br>";

			// Time Sensitive Action Required: NIH Password Expires on 04/04/2012 19:07:11
			$needle[] = "/Time Sensitive Action Required/";
			if(preg_match($needle[$i], $this->currentSubject) > 0) {
				global $conf;

				$body = "Please update the password on this account before it expires: <b>".shn_db_get_config("mpres","username")."</b><br><br>Email Subject:<br>".$this->currentSubject;
				$p = new pop();
				$p->sendMessage($conf['audit_email'], "", "{ ".$conf['site_name']." Password Expiration Notice }", $body, $body);
				echo $p->spit();

			// email has XML attachment....
			} elseif($this->currentMessageHasXML) {

				// catch all parsing errors...
				if($this->ecode != 0) {
					$this->messages .= "LPF XML email found but failed during parsing with error code: ".$this->ecode.".<br>";
					$this->replyError("Your person record was successfully received, but we failed to parse the XML. Please report this to lpfsupport@mail.nih.gov");

				// event is closed... error
				} elseif(!$this->person->isEventOpen()) {
					$this->messages .= "LPF XML email found however, the event being reported to is closed, so the person was not inserted.<br>";
					$this->replyError("Your person record was successfully received, but the event you are reporting to is closed so the record was not inserted.");

				// insert!
				} else {
					$this->person->insert();
					$this->mpresLog();
					$this->messages .= "LPF XML email found and person <a href=\"https://".$this->person->p_uuid."\" target=\"_blank\">".$this->person->p_uuid."</a> inserted.<br>";
					$this->replySuccess($this->person->p_uuid, $this->person->incident_id);
				}

			// unstructured email... attempt to parse subject
			} else {
				$this->person->incident_id = $this->incident_id;
				if(!$this->person->isEventOpen()) {
					$this->messages .= "Unstructured email found, however the event being reported to is closed, so the person was not inserted.<br>";
					$this->replyError("We are not accepting email reports at this time. Sorry, but your person was not inserted into our system.");
				} else {
					$this->person->createUUID();
					$this->extractStatusFromSubject();
					$name = new nameParser($this->currentSubject);
					$this->person->given_name    = $name->getFirstName();
					$this->person->family_name   = $name->getLastName();
					$this->person->full_name     = $this->person->given_name." ".$this->person->family_name;
					$this->person->last_updated  = date('Y-m-d H:i:s');
					$this->person->creation_time = date('Y-m-d H:i:s');
					$this->person->author_name   = $this->currentFrom;
					$this->person->author_email  = $this->currentFrom;
					$this->person->xmlFormat     = "MPRES";
					$this->person->arrival_vanilla_email = true;
					$this->person->insert();
					$this->mpresLog();
					$this->messages .= "Unstructured email found and person <a href=\"https://".$this->person->p_uuid."\"  target=\"_blank\">".$this->person->p_uuid."</a> inserted.<br>";
					$this->replySuccess($this->person->p_uuid, $this->person->incident_id);
				}
			}

			// delete the message from the inbox
			imap_delete($this->mailbox, $i+1);
			$this->messages .= "Message #".$i." deleted.<br>";
		}
	}


	// open the mailbox
	private function openMailbox() {

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
			$this->mailboxOpen = true;
			$this->messages .= "Mailbox opened successfully.<br>";
		} else {
			$this->mailboxOpen = false;
			$this->messages .= "Mailbox failed to open.<br>";
		}
	}


	// purge and close inbox
	private function closeMailbox() {

		if ($this->mailboxOpen) {
			imap_expunge($this->mailbox);
			imap_close($this->mailbox);
		}
	}


	// update sequence
	private function updateSequence() {

		// figure out script execution time
		$this->stopTime = microtime(true);
		$totalTime = $this->stopTime - $this->startTime;
		$this->messages .= "Script executed in ".$totalTime." seconds.<br>";

		$q = "
			DELETE FROM `mpres_seq`
			WHERE `id` like '%';
		";
		$res = $this->db->Execute($q);

		$q = "
			INSERT INTO  `mpres_seq` (`id`, `last_executed`, `last_message`)
			VALUES (NULL, CURRENT_TIMESTAMP, '".mysql_real_escape_string($this->messages)."');
		";
		$res = $this->db->Execute($q);

		// only save messages if there is something going on, ie. there was at least one message in the inbox
		if($this->toggleActivity) {
			$q = "
				INSERT INTO  `mpres_messages` (`messages`, `error_code`)
				VALUES ('".mysql_real_escape_string($this->messages)."', '".$this->ecode."');
			";
			$res = $this->db->Execute($q);
		}
	}


	// save entry in the log
	private function mpresLog() {
		// insert into mpres_log
		$q = "
			INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time, xml_format)
			VALUES ('".$this->person->p_uuid."', '".$this->currentSubject."', '".$this->currentFrom."', '".$this->currentDate."', NOW(), '".$this->person->xmlFormat."');
		";
		$res = $this->db->Execute($q);
	}



	// algorithmically find the attachments in this email...
	private function getAttachmentsAndParseXML($messageNumber) {

		// we only accept one XML attachment per email, but allow multiple images...
		// so we will save a flag for once we found an XML and ignore all other attachments of this type afterwards
		$foundXml = false;

		// get attachments
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

		// process what attachments we found
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

				 // update to add tep support later......
				} else if(strtolower(substr($f, -4)) == ".lp2" || strtolower(substr($f, -4)) == ".lpf" || strtolower(substr($f, -4)) == ".xml") {
					$this->currentAttachments[$i]['is_xml']   = true;
					$this->currentAttachments[$i]['type']     = "xml";
					$this->currentMessageHasXML               = true;
				}

				// add the image to our current person...
				if($this->currentAttachments[$i]['is_image']) {
					$this->messages .= "found image attachment: ".$f."<br>";
					$this->person->createUUID(); // make sure we have a uuid already...
					$this->person->addImage(base64_encode($this->currentAttachments[$i]['attachment']), $f);
				}

				// handle the XML LPF attachment
				if(!$foundXml && ($this->currentAttachments[$i]['is_xml'])) {

					$foundXml = true; // that's it, we found an xml file, ignore any others...

					$this->messages .= "found XML attachment: ".$f."<br>";
					$a = xml2array($this->currentAttachments[$i]['attachment']);

					// New ReUnite XML Format (from ReUnite 2.5+)
					if(isset($a['person'])) {
						$this->person->theString = $this->currentAttachments[$i]['attachment'];
						$this->person->xmlFormat = "REUNITE3";
						$this->messages .= "attempting to parse XML attachment as REUNITE3 format<br>";
						$this->ecode = $this->person->parseXml();

					// Old ReUnite XML Format (Reunite 1.0-2.1)
					} elseif(isset($a['lpfContent'])) {
						$this->person->theString = $this->currentAttachments[$i]['attachment'];
						$this->person->xmlFormat = "REUNITE2";
						$this->messages .= "attempting to parse XML attachment as REUNITE2 format<br>";
						$this->ecode = $this->person->parseXml();

					// Old LPF v1.2 XML from TriagePic
					} elseif(isset($a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent'])) {
						$this->person->theString = $this->currentAttachments[$i]['attachment'];
						$this->person->xmlFormat = "TRIAGEPIC0";
						$this->messages .= "attempting to parse XML attachment as TRIAGEPIC0 format<br>";
						$this->ecode = $this->person->parseXml();

					// Try the new LPF 1.3 Format
					} else {
						$this->person->theString = $this->currentAttachments[$i]['attachment'];
						$this->person->xmlFormat = "TRIAGEPIC1";
						$this->messages .= "attempting to parse XML attachment as TRIAGEPIC1 format<br>";
						$this->ecode = $this->person->parseXml();
					}
				}
			}
		}
	}


	// starts out like: "triune@gmail.com" <triune@gmail.com>
	// so turn it into: triune@gmail.com
	private function fixAddress() {

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
	private function replyError($error) {

		$subject  = "[AUTO-REPLY]: People Locator Record Submission FAILURE";
		$bodyHTML = "
			".$error."<br>
			<br>
			<br>
			<b>- People Locator</b><br>
			<br>
		";
		$bodyAlt = "
			".$error."\n
			\n
			\n
			- People Locator\n
			\n
		";
		$p = new pop();
		$p->sendMessage($this->senderAddress, "", $subject, $bodyHTML, $bodyAlt);
	}


	// email sender with success message
	private function replySuccess($uuid, $id) {

		// figure out the event name
		$q = "
			SELECT *
			FROM incident
			WHERE incident_id = '".mysql_real_escape_string((int)$id)."';
		";
		$result = $this->db->Execute($q);
		$event = $result->fields['description'];

		$subject  = "[AUTO-REPLY]: People Locator Record Submission SUCCESS";
		$bodyHTML = "
			We received the person record you submitted ".$event.". It has been added to our registry and will show up in search results in a few minutes.<br>
			<br>
			You can always view the record for this person (and updates) at the following url:<br>
			<a href=\"https://".$uuid."\" target=\"_blank\">https://".$uuid."</a><br>
			<br>
			<br>
			<b>- People Locator</b><br>
			<br>
		";
		$bodyAlt = "
			We received the person record you submitted ".$event.". It has been added to our registry and will show up in search results in a few minutes.\n
			\n
			You can always view the record for this person (and updates) at the following url:\n
			https://".$uuid."</a>\n
			\n
			\n
			- People Locator\n
			\n
		";
		$p = new pop();
		$p->sendMessage($this->senderAddress, "", $subject, $bodyHTML, $bodyAlt);
	}


	// try to determine the status of the person by looking for certain strings in the subject
	private function extractStatusFromSubject() {

		$this->currentSubject = strtolower($this->currentSubject);
		$s = $this->currentSubject;
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

		$needle[] = '/found/';
		$status[] = 'fnd';

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
		$status[] = 'dec';

		$needle[] = '/died/';
		$status[] = 'dec';

		$needle[] = '/buried/';
		$status[] = 'dec';

		$needle[] = '/decede/';
		$status[] = 'dec';

		$needle[] = '/mort/';
		$status[] = 'dec';

		$needle[] = '/inhume/';
		$status[] = 'dec';

		$needle[] = '/mouri/';
		$status[] = 'dec';

		$needle[] = '/alive & well/';
		$status[] = 'ali';

		$needle[] = '/alive and well/';
		$status[] = 'ali';

		$needle[] = '/alive/';
		$status[] = 'ali';

		$needle[] = '/well/';
		$status[] = 'ali';

		$needle[] = '/okay/';
		$status[] = 'ali';

		$needle[] = '/recovered/';
		$status[] = 'ali';

		$needle[] = '/en vie/';
		$status[] = 'ali';

		$needle[] = '/en bonne sante/';
		$status[] = 'ali';

		$needle[] = '/gueri/';
		$status[] = 'ali';

		$needle[] = '/bien prtant/';
		$status[] = 'ali';

		$needle[] = '/vivant ak anfom/';
		$status[] = 'ali';

		$needle[] = '/vivant/';
		$status[] = 'ali';

		$needle[] = '/anfom/';
		$status[] = 'ali';

		for ($i=0; $i < count($needle); $i++) {
			if(preg_match($needle[$i], $s) > 0) {

				// assign status
				$this->person->opt_status = $status[$i];

				// remove the status from the email subject
				$this->currentSubject = preg_replace($needle[$i], "", $this->currentSubject);
			}
		}

		// if we haven't figured out the status yet, set it to unknown
		if($this->person->opt_status == null) {
			$this->person->opt_status = "unk";
		}
	}
	// end class
}

