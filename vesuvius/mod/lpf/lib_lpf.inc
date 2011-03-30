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


/**
* @class   pop
* @author  Greg Miernicki <g@miernicki.com>
*/
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







///////////////////////////////////////////////////
// HELPER FUNCTIONS
///////////////////////////////////////////////////


function makeBaseUrlMinusEvent() {
	isset($_GET['shortname']) ? $short = $_GET['shortname'] : $short = "";
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace($short."/index.php", "/index.php", $link);
	return $link;
}



function makeBaseUrlMinusEventForHome() {
	isset($_GET['shortname']) ? $short = $_GET['shortname'] : $short = "";
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace($short."/index.php", "", $link);
	return $link;
}
