<?php
/**
* @package      mpres
* @version      1.5.1
* @author       Greg Miernicki <g@miernicki.com>
* LastModified: 2010:0525
* License:      LGPL
* @link         http://www.nlm.nih.gov/
*/


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
	private $person;

	public  $messages; // execution message queue
	public  $startTime; // timestamp of when an object of this type is instantiated
	public  $stopTime; // filled by the spit() method when called


	/**
	* Constructor:
	* Setup the object, initialise the variables
	* @access public
	*/
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
		$this->messages             = "\n----------------------------------------------\nscriptExecutedAtTime >> ".date("Ymd:Gis.u")."\n";
		$this->startTime            = microtime(true);
		$this->stopTime             = null;
		$this->messageCount         = 0;
		$this->currentMessage       = NULL;
		$this->currentAttachments   = NULL;
		$this->currentMessageHasXML = NULL;
		$this->person               = NULL;
		$this->openMailbox();
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
	* Prints the message log
	*/
	public function spit() {
		$this->stopTime = microtime(true);
		$totalTime = $this->stopTime - $this->startTime;
		$this->messages .= "scriptExecutedIn >> ".$totalTime." seconds.\n";
		echo $this->messages;
	}



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


	public function loopInbox() {
		if ( $this->mailboxOpen == FALSE ) {
			$this->messages .= "Can't loop inbox as it's not open!\n";
		} else {
			$this->messageCount = $this->mailboxHeader->Nmsgs;
		}
		if ($this->messageCount == 0) {
			$this->messages .= "Not looping inbox, its empty!\n";
		} else {
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

				$this->person = new lpfPatient();
				$this->person->emailSubject = $this->currentMessage->subject;
				$this->person->emailDate    = $this->currentMessage->date;
				$this->person->emailFrom    = $this->currentMessage->from;

				$this->currentAttachments = NULL;
				$this->currentAttachments = array();
				$this->currentMessageHasXML = FALSE;
				$this->getAttachments($i); // grab all attachments

				// if this is a LPF XML v1.5+ Email
				if ($this->currentMessageHasXML) {
					$this->person->insertPersonXML();
					$this->messages .= "LPF XML email found and person(".$this->person->uuid.") inserted.\n";

				// this is not a TriagePic or ReUnite email, so we will act that it contains a victim's name/status in the subject line
				} else {
					$this->person->incident_id = $this->incident_id;
					$this->person->insertPerson();
					$this->messages .= "Normal email found and person(".$this->person->uuid.") inserted.\n";
				}

				// delete the message from the inbox
				imap_delete($this->mailbox, $i+1);
				$this->messages .= "Message #".$i." deleted.\n";

				// reset person for next round
				$this->person = NULL;
			}
		}
	}



	private function getAttachments($messageNumber) {
		$structure = imap_fetchstructure($this->mailbox, $messageNumber+1);
		if (isset($structure->parts) && count($structure->parts)) {
			for ($i=0; $i < count($structure->parts); $i++) {
				$this->currentAttachments[$i] = array(
					'is_attachment' => FALSE,
					'is_image'      => FALSE,
					'is_xml'        => FALSE,
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
				if (substr($f, -4) == ".jpg" || substr($f, -5) == ".jpeg") {
					$this->currentAttachments[$i]['is_image'] = true;
					$this->currentAttachments[$i]['type']     = "jpg";
				} else if (substr($f, -4) == ".gif") {
					$this->currentAttachments[$i]['is_image'] = true;
					$this->currentAttachments[$i]['type']     = "gif";
				} else if (substr($f, -4) == ".png") {
					$this->currentAttachments[$i]['is_image'] = true;
					$this->currentAttachments[$i]['type']     = "png";
				} else if (substr($f, -4) == ".xml") {
					$this->currentAttachments[$i]['is_xml']   = true;
					$this->currentAttachments[$i]['type']     = "xml";
					$this->currentMessageHasXML = TRUE;
				}

				// save the image and thumbnail
				if ($this->currentAttachments[$i]['is_image']) {
					$newFilename   = "image".rand(1000000000, 1999999999).".".$this->currentAttachments[$i]['type'];
					$fullzizePath  = "../../www/tmp/mpres_cache/".$newFilename;
					$thumbnailPath = "../../www/tmp/mpres_cache/thumb_".$newFilename;
					$fullzizeUrl   = "/tmp/mpres_cache/".$newFilename;
					$thumbnailUrl  = "/tmp/mpres_cache/thumb_".$newFilename;

					file_put_contents($fullzizePath, $this->currentAttachments[$i]['attachment']);
					shn_image_resize_height($fullzizePath, $thumbnailPath, 320);
					// make the files world writeable for other applications
					chmod($fullzizePath,  0777);
					chmod($thumbnailPath, 0777);

					$info = getimagesize($fullzizePath);
					$width = $info[0];
					$height = $info[1];

					$this->person->images[] = new imageAttachment($newFilename, NULL, $height, $width, $this->currentAttachments[$i]['type'], $fullzizeUrl, $thumbnailUrl, $f);
					$this->messages .= "found image attachment>>(".$f.")\n";
					$this->messages .= "fullzize url>>>(".$fullzizeUrl.")\n";
					$this->messages .= "thumbnail url>>(".$thumbnailUrl.")\n";
				}

				// handle the XML LPF attachment
				if ($this->currentAttachments[$i]['is_xml']) {
					$newFilename  = "xml_".rand(1000000000, 1999999999).".".$this->currentAttachments[$i]['type'];
					$saveXmlPath  = "../../www/tmp/mpres_cache/".$newFilename;
					$saveXmlUrl   = "/tmp/mpres_cache/".$newFilename;
					//file_put_contents($saveXmlPath, $this->currentAttachments[$i]['attachment']);
					//chmod($saveXmlPath, 0777);

					$this->messages .= "found XML attachment>>(".$f.")\n";
					//$this->messages .= "xml url>>>(".$saveXmlUrl.")\n";

					$a = $this->xml2array($this->currentAttachments[$i]['attachment']);

					$this->person->shortName    = strtolower($a['lpfContent']['person']['eventShortName']);
					$this->person->firstName    = $a['lpfContent']['person']['firstName'];
					$this->person->familyName   = $a['lpfContent']['person']['familyName'];
					$this->person->gender       = substr(strtolower($a['lpfContent']['person']['gender']), 0, 3);
					$this->person->age          = $a['lpfContent']['person']['estimatedAgeInYears'];
					$this->person->sahanaStatus = substr(strtolower($a['lpfContent']['person']['status']['healthStatus']), 0, 3);
					$this->person->comments     = $a['lpfContent']['person']['notes'];
				}
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
		$this->currentMessage->from = preg_replace('/"/', '', $this->currentMessage->from);
	}



	/**
	* Function converts an XML string into an array
	* Original Author: lz_speedy@web.de
	* Original Source: http://goo.gl/7WRp
	*/
	private function xml2array($xml, $get_attributes = 1, $priority = 'tag') {
		$contents = "";
		if (!function_exists('xml_parser_create')) {
			return array ();
		}
		$parser = xml_parser_create('');
		$contents = $xml;

		xml_parser_set_option($parser, XML_OPTION_TARGET_ENCODING, "UTF-8");
		xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0);
		xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);
		xml_parse_into_struct($parser, trim($contents), $xml_values);
		xml_parser_free($parser);
		if (!$xml_values) {
			return; //Hmm...
		}
		$xml_array = array ();
		$parents = array ();
		$opened_tags = array ();
		$arr = array ();
		$current = & $xml_array;
		$repeated_tag_index = array (); 
		foreach ($xml_values as $data) {
			unset ($attributes, $value);
			extract($data);
			$result = array ();
			$attributes_data = array ();
			if (isset ($value)) {
				if ($priority == 'tag') {
					$result = $value;
				} else {
					$result['value'] = $value;
				}
			}
			if (isset($attributes) and $get_attributes) {
				foreach ($attributes as $attr => $val) {
					if ($priority == 'tag') {
						$attributes_data[$attr] = $val;
					} else {
						$result['attr'][$attr] = $val; //Set all the attributes in a array called 'attr'
					}
				}
			}
			if ($type == "open") { 
				$parent[$level -1] = & $current;
				if (!is_array($current) or (!in_array($tag, array_keys($current)))) {
					$current[$tag] = $result;
					if ($attributes_data) {
						$current[$tag . '_attr'] = $attributes_data;
					}
					$repeated_tag_index[$tag . '_' . $level] = 1;
					$current = & $current[$tag];
				} else {
					if (isset ($current[$tag][0])) {
						$current[$tag][$repeated_tag_index[$tag . '_' . $level]] = $result;
						$repeated_tag_index[$tag . '_' . $level]++;
					} else { 
						$current[$tag] = array (
							$current[$tag],
							$result
						); 
						$repeated_tag_index[$tag . '_' . $level] = 2;
						if (isset ($current[$tag . '_attr'])) {
							$current[$tag]['0_attr'] = $current[$tag . '_attr'];
							unset ($current[$tag . '_attr']);
						}
					}
					$last_item_index = $repeated_tag_index[$tag . '_' . $level] - 1;
					$current = & $current[$tag][$last_item_index];
				}
			} elseif ($type == "complete") {
				if (!isset ($current[$tag])) {
					$current[$tag] = $result;
					$repeated_tag_index[$tag . '_' . $level] = 1;
					if ($priority == 'tag' and $attributes_data) {
						$current[$tag . '_attr'] = $attributes_data;
					}
				} else {
					if (isset ($current[$tag][0]) and is_array($current[$tag])) {
						$current[$tag][$repeated_tag_index[$tag . '_' . $level]] = $result;
						if ($priority == 'tag' and $get_attributes and $attributes_data) {
							$current[$tag][$repeated_tag_index[$tag . '_' . $level] . '_attr'] = $attributes_data;
						}
						$repeated_tag_index[$tag . '_' . $level]++;
					} else {
						$current[$tag] = array (
							$current[$tag],
							$result
						); 
						$repeated_tag_index[$tag . '_' . $level] = 1;
						if ($priority == 'tag' and $get_attributes) {
							if (isset ($current[$tag . '_attr'])) { 
								$current[$tag]['0_attr'] = $current[$tag . '_attr'];
								unset ($current[$tag . '_attr']);
							}
							if ($attributes_data) {
								$current[$tag][$repeated_tag_index[$tag . '_' . $level] . '_attr'] = $attributes_data;
							}
						}
						$repeated_tag_index[$tag . '_' . $level]++; //0 and 1 index is already taken
					}
				}
			} elseif ($type == 'close') {
				$current = & $parent[$level -1];
			}
		}
		return ($xml_array);
	}



	// end class
}

