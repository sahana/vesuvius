<?php
/**
 * @name         LPF Library
 * @version      0.6
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0714
 */


/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personEdxlOne
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class personEdxlOne {

	public $de_id;
	public $co_id;
	public $content_descr;
	public $incident_id;
	public $incident_descr;
	public $confidentiality;

	public $tag_id;   // tag_id


	// Constructor
	public function __construct($image_id) {
		$this->tag_id   = null;
		$this->image_id = "'".$image_id."'";
		$this->tag_x    = "NULL";
		$this->tag_y    = "NULL";
		$this->tag_w    = "NULL";
		$this->tag_h    = "NULL";
		$this->tag_text = "NULL";
	}


	// Destructor
	public function __destruct() {
	}


	// save the image tag
	public function save() {
		global $global;
		$q = "
			INSERT INTO image_tag (
				image_id,
				tag_x,
				tag_y,
				tag_w,
				tag_h,
				tag_text )
			VALUES (
				".$this->image_id.",
				".$this->tag_x.",
				".$this->tag_y.",
				".$this->tag_w.",
				".$this->tag_h.",
				".$this->tag_text." );
		";
		$res = $global['db']->Execute($q);
	}
}



/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personImageTag
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class personImageTag {

	public $tag_id;   // tag_id
	public $image_id; // image_id
	public $tag_x;    // tag_x
	public $tag_y;    // tag_y
	public $tag_w;    // tag_w
	public $tag_h;    // tag_h
	public $tag_text; // tag_text

	// Constructor
	public function __construct($image_id) {
		$this->tag_id   = null;
		$this->image_id = "'".$image_id."'";
		$this->tag_x    = "NULL";
		$this->tag_y    = "NULL";
		$this->tag_w    = "NULL";
		$this->tag_h    = "NULL";
		$this->tag_text = "NULL";

	}


	// Destructor
	public function __destruct() {
		$this->tag_id   = null;
		$this->image_id = null;
		$this->tag_x    = null;
		$this->tag_y    = null;
		$this->tag_w    = null;
		$this->tag_h    = null;
		$this->tag_text = null;
	}


	// save the image tag
	public function save() {
		global $global;
		$q = "
			INSERT INTO image_tag (
				image_id,
				tag_x,
				tag_y,
				tag_w,
				tag_h,
				tag_text )
			VALUES (
				".$this->image_id.",
				".$this->tag_x.",
				".$this->tag_y.",
				".$this->tag_w.",
				".$this->tag_h.",
				".$this->tag_text." );
		";
		$res = $global['db']->Execute($q);
		$this->tag_id = $global['db']->Insert_ID('image_tag', 'tag_id');
	}
}


/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personImage
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class personImage {

	public $image_id;          // image_id
	public $p_uuid;            // p_uuid
	public $mimeType;          // image_type
	public $height;            // image_height
	public $width;             // image_width
	public $created;           // created (timestamp)
	public $category;          // category (person)
	public $url;               // url
	public $url_thumb;         // url_thumb
	public $filename;          //
	public $filenameOriginal;  // original_filename
	public $fileContentBase64; //
	public $fileContent;       //
	public $cropX;             // crop_x
	public $cropY;             // crop_y
	public $cropW;             // crop_w
	public $cropH;             // crop_h
	public $fullSizePath;      // full_path
	public $thumbnailPath;     //
	public $tags;              //

	// Constructor
	public function __construct($p_uuid, $mimeType, $fileContentBase64) {
		if($mimeType == "image/png") {
			$fileExtension = ".png";
		} else if($mimeType == "image/gif") {
			$fileExtension = ".gif";
		} else {
			$fileExtension = ".jpg";
		}
		$this->image_id          = null;
		$this->p_uuid            = "'".$p_uuid."'";
		$this->mimeType          = "'".$mimeType."'";
		$this->height            = 0;
		$this->width             = 0;
		$this->created           = "'".date("Y-m-d : H:i:s", time())."'"; // 2037-12-31 23:59:59
		$this->category          = "'person'";
		$this->filenameOriginal  = "NULL";
		$this->cropX             = "NULL";
		$this->cropY             = "NULL";
		$this->cropW             = "NULL";
		$this->cropH             = "NULL";

		$this->filename          = str_replace("/", "_", $this->p_uuid)."__".(string)rand(1000000, 9999999);
		$this->fileContentBase64 = $fileContentBase64;
		$this->fileContent       = base64_decode($this->fileContentBase64);
		$this->fullSizePath      = $global['approot']."www/tmp/plus_cache/".$this->filename.$fileExtension;
		$this->thumbnailPath     = $global['approot']."www/tmp/plus_cache/".$this->filename."__thumb".$fileExtension;
		$this->url               = "tmp/plus_cache/".$this->filename.$fileExtension;
		$this->url_thumb         = "tmp/plus_cache/".$this->filename."__thumb".$fileExtension;
		$this->tags              = array();
	}


	// Destructor
	public function __destruct() {
		$this->image_id          = null;
		$this->p_uuid            = null;
		$this->mimeType          = null;
		$this->height            = null;
		$this->width             = null;
		$this->created           = null;
		$this->category          = null;
		$this->url               = null;
		$this->url_thumb         = null;
		$this->filename          = null;
		$this->filenameOriginal  = null;
		$this->fileContentBase64 = null;
		$this->fileContent       = null;
		$this->cropX             = null;
		$this->cropY             = null;
		$this->cropW             = null;
		$this->cropH             = null;
		$this->fullSizePath      = null;
		$this->thumbnailPath     = null;
	}

	// save the current image
	public function save() {
		global $global;
		require_once($global['approot']."inc/lib_image.inc");

		file_put_contents($this->fullSizePath, $this->fileContent);
		shn_image_resize_height($fullSizePath, $this->thumbnailPath, 320); // save a 320px wide thumbnail

		// make the files world writeable for other applications
		chmod($fullSizePath,  0777);
		chmod($thumbnailPath, 0777);

		$info = getimagesize($fullSizePath);
		$this->width  = $info[0];
		$this->height = $info[1];

		$q = "
			INSERT INTO image (
				p_uuid,
				image_type,
				image_height,
				image_width,
				created,
				category,
				url,
				url_thumb,
				original_filename,
				cropX,
				cropY,
				cropW,
				cropH,
				full_path )
			VALUES (
				".$this->p_uuid.",
				".$this->mimeType.",
				".$this->height.",
				".$this->width.",
				".$this->created.",
				".$this->category.",
				".$this->url.",
				".$this->url_thumb.",
				".$this->original_filename."
				".$this->cropX.",
				".$this->cropY.",
				".$this->cropW.",
				".$this->cropH.",
				".$this->fullPath." );
		";
		$res = $global['db']->Execute($q);
		$this->image_id = $global['db']->Insert_ID('image', 'image_id');
	}

	// Debug
	public function debug() {
		echo "\nimage_id >>>>>>>>>>> ".$this->image_id." <<";
		echo "\np_uuid >>>>>>>>>>>>> ".$this->p_uuid." <<";
		echo "\nmimeType >>>>>>>>>>> ".$this->mimeType." <<";
		echo "\nheight >>>>>>>>>>>>> ".$this->height." <<";
		echo "\nwidth >>>>>>>>>>>>>> ".$this->width." <<";
		echo "\ncreated >>>>>>>>>>>> ".$this->created." <<";
		echo "\ncategory >>>>>>>>>>> ".$this->category." <<";
		echo "\nurl >>>>>>>>>>>>>>>> ".$this->url." <<";
		echo "\nurl_thumb >>>>>>>>>> ".$this->url_thumb." <<";
		echo "\nfilename >>>>>>>>>>> ".$this->filename." <<";
		echo "\nfilenameOriginal >>> ".$this->filenameOriginal." <<";
		echo "\ncropX >>>>>>>>>>>>>> ".$this->cropX." <<";
		echo "\ncropY >>>>>>>>>>>>>> ".$this->cropY." <<";
		echo "\ncropW >>>>>>>>>>>>>> ".$this->cropW." <<";
		echo "\ncropH >>>>>>>>>>>>>> ".$this->cropH." <<";
		echo "\nfullSizePath >>>>>>> ".$this->fullSizePath." <<";
		echo "\nthumbnailPath >>>>>> ".$this->thumbnailPath." <<\n";
	}
}


/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        person
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class person {

	// holds the XML/format if used to instantiate in this manner
	public $theString; // object is initialized as a string first, then parsed into an array
	public $xmlFormat; // enumerated constant denoting type of the XML being loaded ~ REUNITE, TRIAGEPIC

	// table person_uuid
	public $p_uuid;
	public $full_name;
	public $family_name;
	public $given_name;
	public $incident_id;
	public $hospital_uuid;
	public $expiry_date;

	// table person_status
	public $opt_status;
	public $last_updated;
	public $isVictim;
	public $creation_time;

	// table person_details
	public $details_id;
	public $birth_date;
	public $opt_race;
	public $opt_religion;
	public $opt_gender;
	public $years_old;
	public $minAge;
	public $maxAge;
	public $last_seen;
	public $last_clothing;
	public $other_comments;

	// table person_to_report
	public $rep_uuid;
	public $relation;

	// table image
	public $images;



	// Constructor:
	public function	__construct() {
		$this->theString      = null;
		$this->xmlFormat      = null;
		$this->p_uuid         = null;
		$this->full_name      = null;
		$this->family_name    = null;
		$this->given_name     = null;
		$this->incident_id    = null;
		$this->hospital_uuid  = null;
		$this->expiry_date    = null;
		$this->opt_status     = null;
		$this->last_updated   = null;
		$this->isVictim       = null;
		$this->creation_time  = null;
		$this->details_id     = null;
		$this->birth_date     = null;
		$this->opt_race       = null;
		$this->opt_religion   = null;
		$this->opt_gender     = null;
		$this->years_old      = null;
		$this->minAge         = null;
		$this->maxAge         = null;
		$this->last_seen      = null;
		$this->last_clothing  = null;
		$this->other_comments = null;
		$this->rep_uuid       = null;
		$this->relation       = null;
		$this->images         = null;
	}



	// Destructor
	public function __destruct() {
		$this->theString      = null;
		$this->xmlFormat      = null;
		$this->p_uuid         = null;
		$this->full_name      = null;
		$this->family_name    = null;
		$this->given_name     = null;
		$this->incident_id    = null;
		$this->hospital_uuid  = null;
		$this->expiry_date    = null;
		$this->opt_status     = null;
		$this->last_updated   = null;
		$this->isVictim       = null;
		$this->creation_time  = null;
		$this->details_id     = null;
		$this->birth_date     = null;
		$this->opt_race       = null;
		$this->opt_religion   = null;
		$this->opt_gender     = null;
		$this->years_old      = null;
		$this->minAge         = null;
		$this->maxAge         = null;
		$this->last_seen      = null;
		$this->last_clothing  = null;
		$this->other_comments = null;
		$this->rep_uuid       = null;
		$this->relation       = null;
		$this->images         = null;
	}


	public function save() {
		global $global;
		// we use the pfif lib to create pfif notes in managing persons...
		require_once($global['approot']."mod/pfif/pfif.inc");








//////////////////////////

		global $global;

		$this->extractStatusFromSubject();

		$name = new nameParser($this->emailSubject);
		$this->givenName  = $name->getFirstName();
		$this->familyName = $name->getLastName();

		// insert person
		$q1 = "
			INSERT INTO person_uuid (p_uuid, full_name, family_name, given_name, incident_id, hospital_uuid)
			VALUES ('".$this->uuid."', '".$this->givenName." ".$this->familyName."', '".$this->familyName."', '".$this->givenName."', '".$this->incident_id."', NULL);
		";
		$res = $global['db']->Execute($q1);


		// insert person's status
		$q4 = "
			INSERT INTO person_status (p_uuid, opt_status, last_updated, isvictim, creation_time)
			VALUES ( '".$this->uuid."', '".$this->sahanaStatus."', CURRENT_TIMESTAMP, TRUE, CURRENT_TIMESTAMP);
		";
		$res = $global['db']->Execute($q4);


		// insert into mpres_log
		$q5 = "
			INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());
		";
		$res = $global['db']->Execute($q5);


		// insert person's details
		$q6 = "
			INSERT INTO person_details (p_uuid, opt_gender, years_old, last_seen, last_clothing, other_comments)
			VALUES ('".$this->uuid."', NULL, NULL, NULL, NULL, NULL);
		";
		$res = $global['db']->Execute($q6);


		// insert person who reported link to root cuz we dont really know who reported them
		$q7 = "
			INSERT INTO person_to_report (p_uuid, rep_uuid)
			VALUES ('".$this->uuid."', '1');
		";
		$res = $global['db']->Execute($q7);

		$this->insertImages();

////////////////////


		global $global;
		$this->figureOutIncidentId();

		// insert person
		$q1 = "
			INSERT INTO person_uuid (p_uuid, full_name, family_name, given_name, incident_id, hospital_uuid)
			VALUES ('".$this->uuid."', '".$this->givenName." ".$this->familyName."', '".$this->familyName."', '".$this->givenName."', '".$this->incident_id."', ".$this->hospitalId.");
		";
		$res = $global['db']->Execute($q1);


		// insert person's status
		$q4 = "
			INSERT INTO person_status (p_uuid, opt_status, last_updated, isvictim, creation_time)
			VALUES ('".$this->uuid."', '".$this->sahanaStatus."', CURRENT_TIMESTAMP, TRUE, CURRENT_TIMESTAMP);
		";
		$res = $global['db']->Execute($q4);


		// insert person's details
		$q5 = "
			INSERT INTO person_details (p_uuid, opt_gender, years_old, last_seen, last_clothing, other_comments)
			VALUES ('".$this->uuid."', ".$this->gender.", '".$this->age."', NULL, NULL, '".$this->comments."');
		";
		$res = $global['db']->Execute($q5);


		// insert into mpres_log
		$q7 = "
			INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());
		";
		$res = $global['db']->Execute($q7);

		$this->insertImages();

////////////////

		global $global;
		$this->figureOutIncidentId();

		// insert person
		$q1 = "
			INSERT INTO person_uuid (p_uuid, full_name, family_name, given_name, incident_id, hospital_uuid)
			VALUES ('".$this->uuid."', '".$this->givenName." ".$this->familyName."', '".$this->familyName."', '".$this->givenName."', '".$this->incident_id."', ".$this->hospitalId.");
		";
		$res = $global['db']->Execute($q1);


		// insert person's status
		$q4 = "
			INSERT INTO person_status (p_uuid, opt_status, last_updated, isvictim, creation_time)
			VALUES ('".$this->uuid."', '".$this->sahanaStatus."', '".$this->clientDate."', TRUE, CURRENT_TIMESTAMP);
		";
		$res = $global['db']->Execute($q4);


		// insert person's details
		$q5 = "
			INSERT INTO person_details (p_uuid, opt_gender, years_old, minAge, maxAge)
			VALUES ('".$this->uuid."', ".$this->gender.", ".$this->age.", ".$this->minAge.", ".$this->maxAge.");
		";
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = "
			INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());
		";
		$res = $global['db']->Execute($q7);

		$this->insertImages();

///////////////





	}


	public function load() {
		global $global;
		// we use the pfif lib to create pfif notes in managing persons...
		require_once($global['approot']."mod/pfif/pfif.inc");

	}


	public function edit() {
		global $global;
		// we use the pfif lib to create pfif notes in managing persons...
		require_once($global['approot']."mod/pfif/pfif.inc");

	}



	public function parseXml() {
		$a = xml2array($this->theString);

		// Identify ReUnite XML's
		if(isset($a['lpfContent'])) {
			$this->person->shortName    = strtolower($a['lpfContent']['person']['eventShortName']);
			$this->person->givenName    = $a['lpfContent']['person']['firstName'];
			$this->person->familyName   = $a['lpfContent']['person']['familyName'];
			$this->person->gender       = substr(strtolower($a['lpfContent']['person']['gender']), 0, 3);
			$this->person->age          = $a['lpfContent']['person']['estimatedAgeInYears'];
			$this->person->sahanaStatus = substr(strtolower($a['lpfContent']['person']['status']['healthStatus']), 0, 3);
			$this->person->comments     = $a['lpfContent']['person']['notes'];
			$this->XMLversion           = 1.6;

		// LPF v1.2 XML from TriagePic
		} else if(isset($a['EDXLDistribution'])) {

			// old method from mpres 1.0
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
			$this->eventLongName           = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventLongName']['#text'];
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


			$this->person->shortName   = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventName'];
			$this->person->longName    = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventLongName'];

			// fix missing last name
			if(isset($a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName']) &&
				trim((string)$a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName']) != "") {
				$this->person->familyName = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName'];
			} else {
				$this->person->familyName = "unknown";
			}
			if(is_array($this->person->familyName)) {
				$this->person->familyName = "unknown";
			}

			// fix missing first name
			if(isset($a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName']) &&
				trim((string)$a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName']) != "") {
				$this->person->givenName  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName'];
			} else {
				$this->person->givenName  = "unknown";
			}
			if(is_array($this->person->givenName)) {
				$this->person->givenName = "unknown";
			}

			// <dateTimeSent>2011-03-28T07:52:17Z</dateTimeSent>
			$date = $a['EDXLDistribution']['dateTimeSent'];
			$date = str_replace("T", " ", $date);
			$date = str_replace("Z", "", $date);
			$this->person->clientDate = $date;

			// fix org
			if(trim($a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgName']) == "National Naval Medical Center") {
				$this->person->hospitalId = "'2'";
			} else if(trim($a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgName']) == "Suburban Hospital") {
				$this->person->hospitalId = "'1'";
			} else {
				$this->person->hospitalId = "NULL";
			}

			$this->person->age = null;

			$this->person->gender = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['gender'];

			if($this->person->gender == "M") {
				$this->person->gender = "'mal'";

			} elseif($this->person->gender == "'F'") {
				$this->person->gender = "'fml'";

			} elseif($this->person->gender == "C") {
				$this->person->gender = "'cpx'";

			} else {
				$this->person->gender = "NULL";
			}


			$this->person->peds = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['peds'];

			if($this->person->peds == "Y") {
				$this->person->age = "'17'";
				$this->person->minAge = "'0'";
				$this->person->maxAge = "'17'";
			} elseif($this->person->peds == "N") {
				$this->person->age = "'18'";
				$this->person->minAge = "'18'";
				$this->person->maxAge = "'150'";
			} elseif($this->person->peds == "Y,N") {
				$this->person->age = "'18'";
				$this->person->minAge = "'0'";
				$this->person->maxAge = "'150'";
			} else {
				$this->person->age = "null";
				$this->person->minAge = "'0'";
				$this->person->maxAge = "'17'";
			}


			$b = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategory'];
			if(($b == "Green") || ($b == "BH Green")) {
				$this->person->sahanaStatus = "ali";
			} elseif(($b == "Yellow") || ($b == "Red") || ($b == "Gray")) {
				$this->person->sahanaStatus = "inj";
			} elseif($b == "Black") {
				$this->person->sahanaStatus = "dec";
			} else {
				$this->person->sahanaStatus = "ali";
			}
			$this->XMLversion = 1.2;
		}
	}
}


/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        pop
* @version      1.0
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
			$sendStatus = "SUCCESS\n";
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
		$this->messages .= "scriptExecutedIn >> ".$totalTime." seconds.\n";
		echo $this->messages;
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

/* TEST CASE
$address = "301 Bayside Road, St. Leonard, MD";

require_once('class.googleGeocoder.php');
$geocoder = new googleGeocoder();
try {
	$placemarks = $geocoder->lookup($address);
} catch(Exception $ex) {
	echo $ex->getMessage();
	exit;
}
if (count($placemarks) > 0) {
	foreach ($placemarks as $placemark) {
		echo htmlSpecialChars($placemark)."(".$placemark->getPoint()->getLatitude().",".$placemark->getPoint()->getLongitude().")\n";
	}
} else {
	echo "no matches";
}
*/

/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        goo_gl
* @author       Marcus Nunes - marcusnunes.com - 09/18/2010
*
* eg:
* $googl = new goo_gl('http://marcusnunes.com/api-goo.gl.php');
* echo $googl->result();
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class goo_gl{

	var $url, $resul;

	//goo.gl construct method
	function goo_gl($url){

		$this->url = $url;

		$curl = curl_init();
		curl_setopt($curl, CURLOPT_URL, 'http://goo.gl/api/url');
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_POST, 1);
		curl_setopt($curl, CURLOPT_POSTFIELDS, 'user=toolbar@google.com&url='.urlencode($this->url).'&auth_token='.$this->googlToken($url));
		$saida = curl_exec($curl);
		curl_close($curl);
		if($saida){
			$json = json_decode($saida);
			$this->resul = $json->short_url;
		}
	}

	//show url shorted by goo.gl
	function result(){
		return $this->resul;
	}

	//token code
	function googlToken($b){
		$i = $this->tke($b);
		$i = $i >> 2 & 1073741823;
		$i = $i >> 4 & 67108800 | $i & 63;
		$i = $i >> 4 & 4193280 | $i & 1023;
		$i = $i >> 4 & 245760 | $i & 16383;
		$j = "7";
		$h = $this->tkf($b);
		$k = ($i >> 2 & 15) << 4 | $h & 15;
		$k |= ($i >> 6 & 15) << 12 | ($h >> 8 & 15) << 8;
		$k |= ($i >> 10 & 15) << 20 | ($h >> 16 & 15) << 16;
		$k |= ($i >> 14 & 15) << 28 | ($h >> 24 & 15) << 24;
		$j .= $this->tkd($k);
		return $j;
	}

	function tkc(){
		$l = 0;
		foreach(func_get_args() as $val){
			$val &= 4294967295;
			$val += $val > 2147483647 ? -4294967296 : ($val < -2147483647 ? 4294967296 : 0);
			$l   += $val;
			$l   += $l > 2147483647 ? -4294967296 : ($l < -2147483647 ? 4294967296 : 0);
		}
		return $l;
	}

	function tkd($l){
		$l = $l > 0 ? $l : $l + 4294967296;
		$m = "$l";  //deve ser uma string
		$o = 0;
		$n = false;
		for($p = strlen($m) - 1; $p >= 0; --$p){
			$q = $m[$p];
			if($n){
				$q *= 2;
				$o += floor($q / 10) + $q % 10;
			} else {
				$o += $q;
			}
			$n = !$n;
		}
		$m = $o % 10;
		$o = 0;
		if($m != 0){
			$o = 10 - $m;
			if(strlen($l) % 2 == 1){
				if ($o % 2 == 1){
					$o += 9;
				}
				$o /= 2;
			}
		}
		return "$o$l";
	}

	function tke($l){
		$m = 5381;
		for($o = 0; $o < strlen($l); $o++){
			$m = $this->tkc($m << 5, $m, ord($l[$o]));
		}
		return $m;
	}

	function tkf($l){
		$m = 0;
		for($o = 0; $o < strlen($l); $o++){
			$m = $this->tkc(ord($l[$o]), $m << 6, $m << 16, -$m);
		}
		return $m;
	}

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/**
 * Validate an email address.
 * Provide email address (raw input)
 * Returns true if the email address has the email
 * address format and the domain exists.
 * borrowed from: http://goo.gl/ufhg
 */
function isEmailValid($email) {
	$isValid = true;
	$atIndex = strrpos($email, "@");
	if(is_bool($atIndex) && !$atIndex) {
		$isValid = false;
	} else {
		$domain    = substr($email, $atIndex+1);
		$local     = substr($email, 0, $atIndex);
		$localLen  = strlen($local);
		$domainLen = strlen($domain);
		if($localLen < 1 || $localLen > 64) {
			// local part length exceeded
			$isValid = false;
		} else if($domainLen < 1 || $domainLen > 255) {
			// domain part length exceeded
			$isValid = false;
		} else if($local[0] == '.' || $local[$localLen-1] == '.') {
			// local part starts or ends with '.'
			$isValid = false;
		} else if(preg_match('/\\.\\./', $local)) {
			// local part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain)) {
			// character not valid in domain part
			$isValid = false;
		} else if(preg_match('/\\.\\./', $domain)) {
			// domain part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local))) {
			// character not valid in local part unless
			// local part is quoted
			if (!preg_match('/^"(\\\\"|[^"])+"$/', str_replace("\\\\","",$local))) {
				$isValid = false;
			}
		}
		if($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A"))) {
			// domain not found in DNS
			$isValid = false;
		}
	}
	return $isValid;
}



/**
* Function converts an XML string into an array
* Original Author: lz_speedy@web.de
* Original Source: http://goo.gl/7WRp
*/
function xml2array($xml, $get_attributes = 1, $priority = 'tag') {
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



/**
 * converts an array into xml
 */
class arr2xml {
	var $array = array();
	var $xml = '';

	function arr2xml($array) {
		$this->array = $array;

		if(is_array($array) && count($array) > 0) {
			$this->struct_xml($array);
		} else {
			$this->xml .= "no data";
		}
	}

	function struct_xml($array) {
		foreach($array as $k=>$v) {
			if(is_array($v)) {
				$tag = ereg_replace('^[0-9]{1,}','data',$k); // replace numeric key in array to 'data'
				$this->xml .= "<$tag>";
				$this->struct_xml($v);
				$this->xml .= "</$tag>";
			} else {
				$tag = ereg_replace('^[0-9]{1,}','data',$k); // replace numeric key in array to 'data'
				$this->xml .= "<$tag>$v</$tag>";
			}
		}
	}

	function get_xml() {
		$header = "<?xml version=\"1.0\" encoding=\"utf-8\"?><root>";
		$footer = "</root>";

		echo $header;
		echo $this->xml;
		echo $footer;
	}
}




function makePageUrl() {
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	return $link;
}



function makeBaseUrl() {
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace("index.php", "", $link);
	return $link;
}



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
	$link = str_replace("/index.php", "", $link);
	return $link;
}


