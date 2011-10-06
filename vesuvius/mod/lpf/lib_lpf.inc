<?php
/**
 * @name         LPF Library
 * @version      24
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0909
 */


// Enumerated Types...
global $global;
$global['enumTriageStatusTags']  = array('Green', 'BH Green', 'Yellow', 'Red', 'Gray', 'Black');
$global['enumGenders']           = array('M', 'F', 'U', 'C');
$global['enumDistrStatus']       = array('Actual', 'Exercise', 'System', 'Test');
$global['enumDistrType']         = array('Ack', 'Cancel', 'Dispatch', 'Error', 'Report', 'Request', 'Response', 'Update');
$global['enumXmlFormats']        = array('REUNITE3', 'TRIAGEPIC1', 'TRIAGEPIC0', 'REUNITE2');

// whether to save the xml attachments for debug purposes
$global['debugAndSaveXmlToFile'] = true;


/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        voiceNote
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class voiceNote {

	public $voice_id;
	public $p_uuid;
	public $length;
	public $format;
	public $sample_rate;
	public $channels;
	public $speaker;
	public $url_original;
	public $url_resampled_mp3;
	public $url_resampled_ogg;

	private $sql_voice_id;
	private $sql_p_uuid;
	private $sql_length;
	private $sql_format;
	private $sql_sample_rate;
	private $sql_channels;
	private $sql_speaker;
	private $sql_url_original;
	private $sql_url_resampled_mp3;
	private $sql_url_resampled_ogg;

	public $dataBase64;
	public $data;


	// Constructor
	public function __construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		// init values
		$this->voice_note_id     = null;
		$this->p_uuid            = null;
		$this->length            = null;
		$this->format            = null;
		$this->sample_rate       = null;
		$this->channels          = null;
		$this->speaker           = null;
		$this->url_original      = null;
		$this->url_resampled_mp3 = null;
		$this->url_resampled_ogg = null;

		$this->sql_voice_note_id     = null;
		$this->sql_p_uuid            = null;
		$this->sql_length            = null;
		$this->sql_format            = null;
		$this->sql_sample_rate       = null;
		$this->sql_channels          = null;
		$this->sql_speaker           = null;
		$this->sql_url_original      = null;
		$this->sql_url_resampled_mp3 = null;
		$this->sql_url_resampled_ogg = null;

		$this->dataBase64 = null;
		$this->data       = null;
	}


	// Destructor
	public function __destruct() {
		$this->voice_note_id     = null;
		$this->p_uuid            = null;
		$this->length            = null;
		$this->format            = null;
		$this->sample_rate       = null;
		$this->channels          = null;
		$this->speaker           = null;
		$this->url_original      = null;
		$this->url_resampled_mp3 = null;
		$this->url_resampled_ogg = null;

		$this->sql_voice_note_id     = null;
		$this->sql_p_uuid            = null;
		$this->sql_length            = null;
		$this->sql_format            = null;
		$this->sql_sample_rate       = null;
		$this->sql_channels          = null;
		$this->sql_speaker           = null;
		$this->sql_url_original      = null;
		$this->sql_url_resampled_mp3 = null;
		$this->sql_url_resampled_ogg = null;

		$this->dataBase64 = null;
		$this->data       = null;

		// make sure tables are safe :)
		$q = "UNLOCK TABLES;";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "voiceNote unlock tables"); }
	}


	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		// update sequence
		$q = "
			DELETE FROM `voice_note_seq`
			WHERE `id` like '%';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "voiceNote delete old sequence"); }

		$q = "
			INSERT INTO  `voice_note_seq` (`id`)
			VALUES (NULL);
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "voiceNote insert new sequence"); }

		// get new index value
		$q = "
			SELECT *
			FROM  `voice_note_seq`
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "voiceNote get sequence"); }

		$this->voice_note_id = $result->fields['id'];
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// build SQL value strings

		$this->sql_voice_note_id     = ($this->voice_note_id == null) ? "NULL" : (int)$this->voice_note_id;
		$this->sql_p_uuid            = ($this->p_uuid        == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_length            = ($this->length        == null) ? "NULL" : (int)$this->length;
		$this->sql_format            = ($this->format        == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->format)."'";
		$this->sql_sample_rate       = ($this->sample_rate   == null) ? "NULL" : (int)$this->sample_rate;
		$this->sql_channels          = ($this->channels      == null) ? "NULL" : (int)$this->channels;
		$this->sql_speaker           = ($this->speaker       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->speaker)."'";
		$this->sql_url_original      = ($this->url_original  == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url_original)."'";
		$this->sql_url_resampled_mp3 = ($this->url_resampled_mp3 == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url_resampled_mp3)."'";
		$this->sql_url_resampled_ogg = ($this->url_resampled_ogg == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url_resampled_ogg)."'";
	}


	private function decode() {
		$this->data = base64_decode($this->dataBase64);
	}


	private function write() {
		global $global;

		// base64 to hex
		$this->decode();

		// generate path and filename portion
		$a = explode("/", $this->p_uuid);
		$filename = $a[0]."_".$a[1]; // make pl.nlm.nih.gov/person.123456 into pl.nlm.nih.gov_person.123456
		$filename = $filename."_vn".$this->voice_note_id."_"; // filename now like pl.nlm.nih.gov_person.123456_vn112233_
		$path = $global['approot']."www/tmp/plus_cache/".$filename; // path is now like /opt/pl/www/tmp/plus_cache/pl.nlm.nih.gov_person.123456_vn112233_

		// save original like /opt/pl/www/tmp/plus_cache/pl.nlm.nih.gov_person.123456_vn112233_original
		file_put_contents($path."original", $this->data);
		chmod($path."original", 0777);
		$this->url_original  = "tmp/plus_cache/".$filename."original";

		// use ffmpeg to resample the file to wav for html5 audio (supported in all browsers)
		shell_exec("ffmpeg -i ".$path."original ".$path."resampled.mp3 ;");
		shell_exec("ffmpeg -i ".$path."original ".$path."resampled.ogg ;");
		chmod($path."resampled.mp3", 0777);
		chmod($path."resampled.ogg", 0777);
		$this->url_resampled_mp3 = "tmp/plus_cache/".$filename."resampled.mp3";
		$this->url_resampled_ogg = "tmp/plus_cache/".$filename."resampled.ogg";
	}


	// save the voice note
	public function insert() {
		$this->write();
		$this->sync();
		$q = "
			INSERT INTO voice_note (
				voice_note_id,
				p_uuid,
				length,
				format,
				sample_rate,
				channels,
				speaker,
				url_original,
				url_resampled_mp3,
				url_resampled_ogg )
			VALUES (
				".$this->sql_voice_note_id.",
				".$this->sql_p_uuid.",
				".$this->sql_length.",
				".$this->sql_format.",
				".$this->sql_sample_rate.",
				".$this->sql_channels.",
				".$this->sql_speaker.",
				".$this->sql_url_original.",
				".$this->sql_url_resampled_mp3.",
				".$this->sql_url_resampled_ogg." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "voiceNote insert()"); }
	}
}



/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personEdxl
* @version      1.0
* @author       Greg Miernicki <g@miernicki.com>
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class personEdxl {

	// edxl_co_header
	public $de_id;
	public $co_id;          // co_id is for the person (onle and
	public $content_descr;  // content description
	public $incident_id;    // event id
	public $incident_descr; // incident description
	public $confidentiality;

	private $sql_de_id;
	private $sql_co_id;
	private $sql_content_descr;
	private $sql_incident_id;
	private $sql_incident_descr;
	private $sql_confidentiality;

	// edxl_co_lpf
	public $p_uuid;
	public $type;
	public $schema_version;
	public $login_machine;
	public $login_account;
	public $person_id;
	public $event_name;
	public $event_long_name;
	public $org_name;
	public $org_id;
	public $last_name;
	public $first_name;
	public $gender;
	public $peds;
	public $triage_category;

	private $sql_p_uuid;
	private $sql_type;
	private $sql_schema_version;
	private $sql_login_machine;
	private $sql_login_account;
	private $sql_person_id;
	private $sql_event_name;
	private $sql_event_long_name;
	private $sql_org_name;
	private $sql_org_id;
	private $sql_last_name;
	private $sql_first_name;
	private $sql_gender;
	private $sql_peds;
	private $sql_triage_category;

	// edxl_de_header
	public $when_sent;
	public $sender_id;     // Email, phone num, etc. Not always URI, URN, URL
	public $distr_id;      // Distribution ID. Sender may or may not choose to vary.
	public $distr_status;
	public $distr_type;    // Not included: types for sensor grids
	public $combined_conf; // Combined confidentiality of all content objects
	public $language;
	public $when_here;     // Received or sent from here. [local]
	public $inbound;        // BOOLEAN [local]

	private $sql_when_sent;
	private $sql_sender_id;
	private $sql_distr_id;
	private $sql_distr_status;
	private $sql_distr_type;
	private $sql_combined_conf;
	private $sql_language;
	private $sql_when_here;
	private $sql_inbound;

	// edxl_co_photos
	public $mimeTypes;
	public $uris;
	public $contentDatas;
	public $image_ids;
	public $image_co_ids;


	// Constructor
	public function __construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		$this->de_id           = null;
		$this->co_id           = null;
		$this->content_descr   = null;
		$this->incident_id     = null;
		$this->incident_descr  = null;
		$this->confidentiality = null;
		$this->p_uuid          = null;
		$this->type            = null;
		$this->schema_version  = null;
		$this->login_machine   = null;
		$this->login_account   = null;
		$this->person_id       = null;
		$this->event_name      = null;
		$this->event_long_name = null;
		$this->org_name        = null;
		$this->org_id          = null;
		$this->last_name       = null;
		$this->first_name      = null;
		$this->gender          = null;
		$this->peds            = null;
		$this->triage_category = null;
		$this->when_sent       = null;
		$this->sender_id       = null;
		$this->distr_id        = null;
		$this->distr_status    = null;
		$this->distr_type      = null;
		$this->combined_conf   = null;
		$this->language        = null;
		$this->when_here       = null;
		$this->inbound         = null;

		$this->mimeTypes    = array();
		$this->uris         = array();
		$this->contentDatas = array();
		$this->image_ids    = array();
		$this->image_co_ids = array();

		$this->sql_de_id           = null;
		$this->sql_co_id           = null;
		$this->sql_content_descr   = null;
		$this->sql_incident_id     = null;
		$this->sql_incident_descr  = null;
		$this->sql_confidentiality = null;
		$this->sql_p_uuid          = null;
		$this->sql_type            = null;
		$this->sql_schema_version  = null;
		$this->sql_login_machine   = null;
		$this->sql_login_account   = null;
		$this->sql_person_id       = null;
		$this->sql_event_name      = null;
		$this->sql_event_long_name = null;
		$this->sql_org_name        = null;
		$this->sql_org_id          = null;
		$this->sql_last_name       = null;
		$this->sql_first_name      = null;
		$this->sql_gender          = null;
		$this->sql_peds            = null;
		$this->sql_triage_category = null;
		$this->sql_when_sent       = null;
		$this->sql_sender_id       = null;
		$this->sql_distr_id        = null;
		$this->sql_distr_status    = null;
		$this->sql_distr_type      = null;
		$this->sql_combined_conf   = null;
		$this->sql_language        = null;
		$this->sql_when_here       = null;
		$this->sql_inbound         = null;
	}


	// Destructor
	public function __destruct() {
		$this->de_id           = null;
		$this->co_id           = null;
		$this->content_descr   = null;
		$this->incident_id     = null;
		$this->incident_descr  = null;
		$this->confidentiality = null;
		$this->p_uuid          = null;
		$this->type            = null;
		$this->schema_version  = null;
		$this->login_machine   = null;
		$this->login_account   = null;
		$this->person_id       = null;
		$this->event_name      = null;
		$this->event_long_name = null;
		$this->org_name        = null;
		$this->org_id          = null;
		$this->last_name       = null;
		$this->first_name      = null;
		$this->gender          = null;
		$this->peds            = null;
		$this->triage_category = null;
		$this->when_sent       = null;
		$this->sender_id       = null;
		$this->distr_id        = null;
		$this->distr_status    = null;
		$this->distr_type      = null;
		$this->combined_conf   = null;
		$this->language        = null;
		$this->when_here       = null;
		$this->inbound         = null;

		$this->mimeTypes    = null;
		$this->uris         = null;
		$this->contentDatas = null;
		$this->image_ids    = null;
		$this->image_co_ids = null;

		$this->sql_de_id           = null;
		$this->sql_co_id           = null;
		$this->sql_content_descr   = null;
		$this->sql_incident_id     = null;
		$this->sql_incident_descr  = null;
		$this->sql_confidentiality = null;
		$this->sql_p_uuid          = null;
		$this->sql_type            = null;
		$this->sql_schema_version  = null;
		$this->sql_login_machine   = null;
		$this->sql_login_account   = null;
		$this->sql_person_id       = null;
		$this->sql_event_name      = null;
		$this->sql_event_long_name = null;
		$this->sql_org_name        = null;
		$this->sql_org_id          = null;
		$this->sql_last_name       = null;
		$this->sql_first_name      = null;
		$this->sql_gender          = null;
		$this->sql_peds            = null;
		$this->sql_triage_category = null;
		$this->sql_when_sent       = null;
		$this->sql_sender_id       = null;
		$this->sql_distr_id        = null;
		$this->sql_distr_status    = null;
		$this->sql_distr_type      = null;
		$this->sql_combined_conf   = null;
		$this->sql_language        = null;
		$this->sql_when_here       = null;
		$this->sql_inbound         = null;

		// make sure tables are safe :)
		$q = "UNLOCK TABLES;";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl unlock tables"); }
	}

	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		/*
		// lock tables to hold new indexes for this session
		$q = "LOCK table edxl_de_header write;";
		$result = $this->db->Execute($q);

		$q = "LOCK table edxl_co_header write;";
		$result = $this->db->Execute($q);

		// get index values
		$q = "SHOW TABLE STATUS LIKE 'edxl_de_header'";
		$result = $this->db->Execute($q);
		$this->de_id = $result->fields['Auto_increment'];

		$q = "SHOW TABLE STATUS LIKE 'edxl_co_header'";
		$result = $this->db->Execute($q);
		$this->co_id = $result->fields['Auto_increment'];
		*/

		// update sequences

		$this->co_id = $this->getNew_co_id();
		$this->de_id = $this->getNew_de_id();
	}


	public function getNew_co_id() {
		$q = "
			DELETE FROM `edxl_co_header_seq`
			WHERE `id` like '%';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl delete co sequence"); }

		$q = "
			INSERT INTO  `edxl_co_header_seq` (`id`)
			VALUES (NULL);
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl insert co sequence"); }

		$q = "
			SELECT *
			FROM  `edxl_co_header_seq`
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl get co sequence"); }
		return $result->fields['id'];
	}


	public function getNew_de_id() {
		$q = "
			DELETE FROM `edxl_de_header_seq`
			WHERE `id` like '%';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl delete de sequence"); }

		$q = "
			INSERT INTO  `edxl_de_header_seq` (`id`)
			VALUES (NULL);
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl insert de sequence"); }

		$q = "
			SELECT *
			FROM  `edxl_de_header_seq`
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl get de sequence"); }
		return $result->fields['id'];
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// sanity checks

		// check gender
		if(!in_array($this->gender, $global['enumGenders'])) {
			$this->gender = null;
		}
		// check triage category
		if(!in_array($this->triage_category, $global['enumTriageStatusTags'])) {
			$this->triage_category = null;
		}
		// check distr status
		if(!in_array($this->distr_status, $global['enumDistrStatus'])) {
			$this->distr_status = null;
		}
		// check distr type
		if(!in_array($this->distr_type, $global['enumDistrType'])) {
			$this->distr_type = null;
		}

		// build SQL value strings

		$this->sql_de_id           = ($this->de_id           == null) ? "NULL" : (int)$this->de_id;
		$this->sql_co_id           = ($this->co_id           == null) ? "NULL" : (int)$this->co_id;
		$this->sql_content_descr   = ($this->content_descr   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->content_descr)."'";
		$this->sql_incident_id     = ($this->incident_id     == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->incident_id)."'";
		$this->sql_incident_descr  = ($this->content_descr   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->content_descr)."'";
		$this->sql_confidentiality = ($this->confidentiality == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->confidentiality)."'";
		$this->sql_p_uuid          = ($this->p_uuid          == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_type            = ($this->type            == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->type)."'";
		$this->sql_schema_version  = ($this->schema_version  == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->schema_version)."'";
		$this->sql_login_machine   = ($this->login_machine   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->login_machine)."'";
		$this->sql_login_account   = ($this->login_account   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->login_account)."'";
		$this->sql_person_id       = ($this->person_id       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->person_id)."'";
		$this->sql_event_name      = ($this->event_name      == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->event_name)."'";
		$this->sql_event_long_name = ($this->event_long_name == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->event_long_name)."'";
		$this->sql_org_name        = ($this->org_name        == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->org_name)."'";
		$this->sql_org_id          = ($this->org_id          == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->org_id)."'";
		$this->sql_last_name       = ($this->last_name       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->last_name)."'";
		$this->sql_first_name      = ($this->first_name      == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->first_name)."'";
		$this->sql_gender          = ($this->gender          == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->gender)."'";
		$this->sql_peds            = ($this->peds            == null) ? "NULL" : (int)$this->peds;
		$this->sql_triage_category = ($this->triage_category == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->triage_category)."'";
		$this->sql_when_sent       = ($this->when_sent       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->when_sent)."'";
		$this->sql_sender_id       = ($this->sender_id       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->sender_id)."'";
		$this->sql_distr_id        = ($this->distr_id        == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->distr_id)."'";
		$this->sql_distr_status    = ($this->distr_status    == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->distr_status)."'";
		$this->sql_distr_type      = ($this->distr_type      == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->distr_type)."'";
		$this->sql_combined_conf   = ($this->combined_conf   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->combined_conf)."'";
		$this->sql_language        = ($this->language        == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->language)."'";
		$this->sql_when_here       = ($this->when_here       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->when_here)."'";
		$this->sql_inbound         = ($this->inbound         == null) ? "NULL" : (int)$this->inbound;
	}


	// save the image tag
	public function insert() {
		$this->sync();
		$q = "
			INSERT INTO edxl_de_header (
				de_id,
				when_sent,
				sender_id,
				distr_id,
				distr_status,
				distr_type,
				combined_conf,
				language,
				when_here,
				inbound )
			VALUES (
				".$this->sql_de_id.",
				".$this->sql_when_sent.",
				".$this->sql_sender_id.",
				".$this->sql_distr_id.",
				".$this->sql_distr_status.",
				".$this->sql_distr_type.",
				".$this->sql_combined_conf.",
				".$this->sql_language.",
				".$this->sql_when_here.",
				".$this->sql_inbound." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl de header insert"); }

		$q = "
			INSERT INTO edxl_co_header (
				de_id,
				co_id,
				p_uuid,
				type,
				content_descr,
				incident_id,
				incident_descr,
				confidentiality )
			VALUES (
				".$this->sql_de_id.",
				".$this->sql_co_id.",
				".$this->sql_p_uuid.",
				".$this->sql_type.",
				".$this->sql_content_descr.",
				".$this->sql_incident_id.",
				".$this->sql_incident_descr.",
				".$this->sql_confidentiality." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co header insert"); }

		$q = "
			INSERT INTO edxl_co_lpf (
				co_id,
				p_uuid,
				schema_version,
				login_machine,
				login_account,
				person_id,
				event_name,
				event_long_name,
				org_name,
				org_id,
				last_name,
				first_name,
				gender,
				peds,
				triage_category )
			VALUES (
				".$this->sql_co_id.",
				".$this->sql_p_uuid.",
				".$this->sql_schema_version.",
				".$this->sql_login_machine.",
				".$this->sql_login_account.",
				".$this->sql_person_id.",
				".$this->sql_event_name.",
				".$this->sql_event_long_name.",
				".$this->sql_org_name.",
				".$this->sql_org_id.",
				".$this->sql_last_name.",
				".$this->sql_first_name.",
				".$this->sql_gender.",
				".$this->sql_peds.",
				".$this->sql_triage_category." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co lpf insert"); }


		for($i = 0; $i < sizeof($this->contentDatas); $i++) {
			$q = "
				INSERT INTO edxl_co_photos (
					co_id,
					p_uuid,
					mimeType,
					uri,
					contentData,
					image_id )
				VALUES (
					'".mysql_real_escape_string($this->image_co_ids[$i])."',
					".$this->sql_p_uuid.",
					'".mysql_real_escape_string($this->mimeTypes[$i])."',
					'".mysql_real_escape_string($this->uris[$i])."',
					'".mysql_real_escape_string($this->contentDatas[$i])."',
					'".mysql_real_escape_string($this->image_ids[$i])."' );
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co photos insert"); }

			$q = "
				INSERT INTO edxl_co_header (
					de_id,
					co_id,
					p_uuid,
					type,
					content_descr,
					incident_id,
					incident_descr,
					confidentiality )
				VALUES (
					".$this->sql_de_id.",
					'".mysql_real_escape_string($this->image_co_ids[$i])."',
					".$this->sql_p_uuid.",
					'pix',
					".$this->sql_content_descr.",
					".$this->sql_incident_id.",
					".$this->sql_incident_descr.",
					".$this->sql_confidentiality." );
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co header insert"); }
		}
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

	public $tag_id;
	public $image_id;
	public $tag_x;
	public $tag_y;
	public $tag_w;
	public $tag_h;
	public $tag_text;

	private $sql_tag_id;
	private $sql_image_id;
	private $sql_tag_x;
	private $sql_tag_y;
	private $sql_tag_w;
	private $sql_tag_h;
	private $sql_tag_text;

	// Constructor
	public function __construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		// init values
		$this->tag_id   = null;
		$this->image_id = null;
		$this->tag_x    = null;
		$this->tag_y    = null;
		$this->tag_w    = null;
		$this->tag_h    = null;
		$this->tag_text = null;

		$this->sql_tag_id   = null;
		$this->sql_image_id = null;
		$this->sql_tag_x    = null;
		$this->sql_tag_y    = null;
		$this->sql_tag_w    = null;
		$this->sql_tag_h    = null;
		$this->sql_tag_text = null;
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

		$this->sql_tag_id   = null;
		$this->sql_image_id = null;
		$this->sql_tag_x    = null;
		$this->sql_tag_y    = null;
		$this->sql_tag_w    = null;
		$this->sql_tag_h    = null;
		$this->sql_tag_text = null;

		// make sure tables are safe :)
		$q = "UNLOCK TABLES;";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag unlock tables"); }
	}


	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		// lock tables to hold new indexes for this session
		//$q = "LOCK table image_tag write;";
		//$result = $this->db->Execute($q);

		// get index value
		//$q = "SHOW TABLE STATUS LIKE 'image_tag'";
		//$result = $this->db->Execute($q);
		//$this->tag_id = $result->fields['Auto_increment'];

		// update sequence
		$q = "
			DELETE FROM `image_tag_seq`
			WHERE `id` like '%';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag delete sequence"); }

		$q = "
			INSERT INTO  `image_tag_seq` (`id`)
			VALUES (NULL);
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag insert sequence"); }

		// get new index value
		$q = "
			SELECT *
			FROM  `image_tag_seq`
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag get sequence"); }

		$this->tag_id = $result->fields['id'];
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// build SQL value strings

		$this->sql_tag_id   = ($this->tag_id   == null) ? "NULL" : (int)$this->tag_id;
		$this->sql_image_id = ($this->image_id == null) ? "NULL" : (int)$this->image_id;
		$this->sql_tag_x    = ($this->tag_x    == null) ? "NULL" : (int)$this->tag_x;
		$this->sql_tag_y    = ($this->tag_y    == null) ? "NULL" : (int)$this->tag_y;
		$this->sql_tag_w    = ($this->tag_w    == null) ? "NULL" : (int)$this->tag_w;
		$this->sql_tag_h    = ($this->tag_h    == null) ? "NULL" : (int)$this->tag_h;
		$this->sql_tag_text = ($this->tag_text == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->tag_text)."'";
	}


	// save the image tag
	public function insert() {
		$this->sync();
		$q = "
			INSERT INTO image_tag (
				tag_id,
				image_id,
				tag_x,
				tag_y,
				tag_w,
				tag_h,
				tag_text )
			VALUES (
				".$this->sql_tag_id.",
				".$this->sql_image_id.",
				".$this->sql_tag_x.",
				".$this->sql_tag_y.",
				".$this->sql_tag_w.",
				".$this->sql_tag_h.",
				".$this->sql_tag_text." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag insert"); }
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

	public $image_id;
	public $p_uuid;
	public $image_type;
	public $image_height;
	public $image_width;
	public $created;
	public $url;
	public $url_thumb;
	public $original_filename;

	private $sql_image_id;
	private $sql_p_uuid;
	private $sql_image_type;
	private $sql_image_height;
	private $sql_image_width;
	private $sql_created;
	private $sql_url;
	private $sql_url_thumb;
	private $sql_original_filename;

	// extra image info
	public $fileContentBase64;
	public $fileContent;
	public $tags;


	// Constructor
	public function __construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		$this->image_id              = null;
		$this->p_uuid                = null;
		$this->image_type            = null;
		$this->image_height          = null;
		$this->image_width           = null;
		$this->created               = null;
		$this->url                   = null;
		$this->url_thumb             = null;
		$this->original_filename     = null;
		$this->sql_image_id          = null;
		$this->sql_p_uuid            = null;
		$this->sql_image_type        = null;
		$this->sql_image_height      = null;
		$this->sql_image_width       = null;
		$this->sql_created           = null;
		$this->sql_url               = null;
		$this->sql_url_thumb         = null;
		$this->sql_original_filename = null;
		$this->fileContentBase64     = null;
		$this->fileContent           = null;
		$this->fullSizePath          = null;
		$this->thumbnailPath         = null;
		$this->tags                  = array();
	}


	// Destructor
	public function __destruct() {
		$this->image_id              = null;
		$this->p_uuid                = null;
		$this->image_type            = null;
		$this->image_height          = null;
		$this->image_width           = null;
		$this->created               = null;
		$this->url                   = null;
		$this->url_thumb             = null;
		$this->original_filename     = null;
		$this->sql_image_id          = null;
		$this->sql_p_uuid            = null;
		$this->sql_image_type        = null;
		$this->sql_image_height      = null;
		$this->sql_image_width       = null;
		$this->sql_created           = null;
		$this->sql_url               = null;
		$this->sql_url_thumb         = null;
		$this->sql_original_filename = null;
		$this->fileContentBase64     = null;
		$this->fileContent           = null;
		$this->fullSizePath          = null;
		$this->thumbnailPath         = null;
		$this->tags                  = null;

		// make sure tables are safe :)
		$q = "UNLOCK TABLES;";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage unlock"); }
	}

	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		/*
		// lock tables to hold new indexes for this session
		$q = "LOCK TABLE image write;";
		//$result = $this->db->Execute($q);

		// get index values
		$q = "SHOW TABLE STATUS LIKE 'image'";
		$result = $this->db->Execute($q);
		$this->image_id = $result->fields['Auto_increment'];
		*/

		// update sequence
		$q = "
			DELETE FROM `image_seq`
			WHERE `id` like '%';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage delete sequence"); }

		$q = "
			INSERT INTO  `image_seq` (`id`)
			VALUES (NULL);
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage insert sequence"); }

		// get new index value
		$q = "
			SELECT *
			FROM  `image_seq`;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage get sequence"); }

		$this->image_id = $result->fields['id'];
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// build SQL strings from values

		$this->sql_image_id          = ($this->image_id          == null) ? "NULL" : (int)$this->image_id;
		$this->sql_p_uuid            = ($this->p_uuid            == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_image_type        = ($this->image_type        == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->image_type)."'";
		$this->sql_image_height      = ($this->image_height      == null) ? "NULL" : (int)$this->image_height;
		$this->sql_image_width       = ($this->image_width       == null) ? "NULL" : (int)$this->image_width;
		$this->sql_created           = ($this->created           == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->created)."'";
		$this->sql_url               = ($this->url               == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url)."'";
		$this->sql_url_thumb         = ($this->url_thumb         == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->url_thumb)."'";
		$this->sql_original_filename = ($this->original_filename == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->original_filename)."'";
	}


	public function decode() {
		$this->fileContent = base64_decode($this->fileContentBase64);
	}


	private function write() {
		global $global;
		require_once($global['approot']."inc/lib_image.inc");

		// base64 to hex
		$this->decode();

		// generate path and filename portion
		$a = explode("/", $this->p_uuid);

		$filename = $a[0]."_".$a[1]; // make pl.nlm.nih.gov/person.123456 into pl.nlm.nih.gov_person.123456
		$filename = $filename."_".$this->image_id."_"; // filename now like person.123456_112233_
		$path = $global['approot']."www/tmp/plus_cache/".$filename; // path is now like /opt/pl/www/tmp/plus_cache/person.123456_112233_

		// save original like /opt/pl/www/tmp/plus_cache/person.123456_112233_original
		file_put_contents($path."original", $this->fileContent);

		// get information from original file
		$info = getimagesize($path."original");
		$this->image_width  = $info[0];
		$this->image_height = $info[1];
		list(,$mime) = explode("/",$info['mime']);
		$mime = strtolower($mime);
		$this->image_type = $mime;
		if(stripos($mime,"png") !== FALSE) {
			$ext = ".png";
		} elseif(stripos($mime,"gif") !== FALSE) {
			$ext = ".gif";
		} else {
			$ext = ".jpg";
		}

		// save full size resampled image like /opt/pl/www/tmp/plus_cache/person.123456_112233_full.ext
		shn_image_resize($path."original", $path."full".$ext, $this->image_width, $this->image_height);

		// save thumb resampled image (320px height) like /opt/pl/www/tmp/plus_cache/person.123456_112233_thumb.ext
		shn_image_resize_height($path."original", $path."thumb".$ext, 320);

		// update URLs
		$this->url       = "tmp/plus_cache/".$filename."full".$ext;
		$this->url_thumb = "tmp/plus_cache/".$filename."thumb".$ext;

		// make the files world writeable for other users/applications and to handle deletes
		chmod($path."original",   0777);
		chmod($path."full".$ext,  0777);
		chmod($path."thumb".$ext, 0777);
	}


	// save the image
	public function insert() {

		// save image to disk
		$this->write();

		// db insert
		$this->sync();
		$q = "
			INSERT INTO image (
				image_id,
				p_uuid,
				image_type,
				image_height,
				image_width,
				url,
				url_thumb,
				original_filename )
			VALUES (
				'".$this->sql_image_id."',
				".$this->sql_p_uuid.",
				".$this->sql_image_type.",
				'".$this->sql_image_height."',
				'".$this->sql_image_width."',
				".$this->sql_url.",
				".$this->sql_url_thumb.",
				".$this->sql_original_filename." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImage insert"); }

		$this->insertImageTags();
	}


	private function insertImageTags() {
		foreach($this->tags as $tag) {
			$tag->insert();
		}
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
	public $a; // holds the array of the parsed xml

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
	public $creation_time;

	// table person_details
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

	// person's images
	public $images;

	// person's edxl components
	public $edxl;

	// person's voice_note
	public $voice_note;

	// sql strings of the objetct's attributes
	private $sql_p_uuid;
	private $sql_full_name;
	private $sql_family_name;
	private $sql_given_name;
	private $sql_incident_id;
	private $sql_hospital_uuid;
	private $sql_expiry_date;
	private $sql_opt_status;
	private $sql_last_updated;
	private $sql_creation_time;
	private $sql_birth_date;
	private $sql_opt_race;
	private $sql_opt_religion;
	private $sql_opt_gender;
	private $sql_years_old;
	private $sql_minAge;
	private $sql_maxAge;
	private $sql_last_seen;
	private $sql_last_clothing;
	private $sql_other_comments;
	private $sql_rep_uuid;
	private $sql_relation;

	// used for when we recieve emails from mpres to make a pfif_note
	public $author_name;
	public $author_email;

	// whether to make a static PFIF not upon insertion
	public $makePfifNote;

	// Constructor:
	public function	__construct() {
		// init db
		global $global;
		$this->db = $global['db'];

		$this->theString      = null;
		$this->xmlFormat      = null;
		$this->a              = null;

		$this->p_uuid         = null;
		$this->full_name      = null;
		$this->family_name    = null;
		$this->given_name     = null;
		$this->incident_id    = null;
		$this->hospital_uuid  = null;
		$this->expiry_date    = null;
		$this->opt_status     = null;
		$this->last_updated   = null;
		$this->creation_time  = null;
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

		$this->images         = array();
		$this->edxl           = null;
		$this->voice_note     = null;

		$this->sql_p_uuid         = null;
		$this->sql_full_name      = null;
		$this->sql_family_name    = null;
		$this->sql_given_name     = null;
		$this->sql_incident_id    = null;
		$this->sql_hospital_uuid  = null;
		$this->sql_expiry_date    = null;
		$this->sql_opt_status     = null;
		$this->sql_last_updated   = null;
		$this->sql_creation_time  = null;
		$this->sql_birth_date     = null;
		$this->sql_opt_race       = null;
		$this->sql_opt_religion   = null;
		$this->sql_opt_gender     = null;
		$this->sql_years_old      = null;
		$this->sql_minAge         = null;
		$this->sql_maxAge         = null;
		$this->sql_last_seen      = null;
		$this->sql_last_clothing  = null;
		$this->sql_other_comments = null;
		$this->sql_rep_uuid       = null;
		$this->sql_relation       = null;

		$this->author_name        = null;
		$this->author_email       = null;

		$this->makePfifNote       = true;
	}



	// Destructor
	public function __destruct() {
		$this->theString      = null;
		$this->xmlFormat      = null;
		$this->a              = null;

		$this->p_uuid         = null;
		$this->full_name      = null;
		$this->family_name    = null;
		$this->given_name     = null;
		$this->incident_id    = null;
		$this->hospital_uuid  = null;
		$this->expiry_date    = null;
		$this->opt_status     = null;
		$this->last_updated   = null;
		$this->creation_time  = null;
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
		$this->edxl           = null;
		$this->voice_note     = null;

		$this->sql_p_uuid         = null;
		$this->sql_full_name      = null;
		$this->sql_family_name    = null;
		$this->sql_given_name     = null;
		$this->sql_incident_id    = null;
		$this->sql_hospital_uuid  = null;
		$this->sql_expiry_date    = null;
		$this->sql_opt_status     = null;
		$this->sql_last_updated   = null;
		$this->sql_creation_time  = null;
		$this->sql_birth_date     = null;
		$this->sql_opt_race       = null;
		$this->sql_opt_religion   = null;
		$this->sql_opt_gender     = null;
		$this->sql_years_old      = null;
		$this->sql_minAge         = null;
		$this->sql_maxAge         = null;
		$this->sql_last_seen      = null;
		$this->sql_last_clothing  = null;
		$this->sql_other_comments = null;
		$this->sql_rep_uuid       = null;
		$this->sql_relation       = null;

		$this->author_name        = null;
		$this->author_email       = null;

		$this->makePfifNote       = null;
	}


	// initializes some values for a new instance (instead of when we load a previous instance)
	public function init() {
		global $global;
		// not used yet...
	}


	// synchronize SQL value strings with public attributes
	private function sync() {
		global $global;

		// map enum types

		if($this->opt_gender == "M") {
			$this->opt_gender = "mal";
		} elseif($this->opt_gender == "F") {
			$this->opt_gender = "fml";
		} elseif($this->opt_gender == "C") {
			$this->opt_gender = "cpx";
		} elseif($this->opt_gender == "U") {
			$this->opt_gender = null;
		} else {
			$this->opt_gender = null;
		}

		// build SQL value strings

		$this->sql_p_uuid         = ($this->p_uuid         == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_full_name      = ($this->full_name      == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->full_name)."'";
		$this->sql_family_name    = ($this->family_name    == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->family_name)."'";
		$this->sql_given_name     = ($this->given_name     == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->given_name)."'";
		$this->sql_incident_id    = ($this->incident_id    == null) ? "NULL" : (int)$this->incident_id;
		$this->sql_hospital_uuid  = ($this->hospital_uuid  == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->hospital_uuid)."'";
		$this->sql_expiry_date    = ($this->expiry_date    == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->expiry_date)."'";

		$this->sql_opt_status     = ($this->opt_status     == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->opt_status)."'";
		$this->sql_last_updated   = ($this->last_updated   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->last_updated)."'";
		$this->sql_creation_time  = ($this->creation_time  == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->creation_time)."'";

		$this->sql_birth_date     = ($this->birth_date     == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->birth_date)."'";
		$this->sql_opt_race       = ($this->opt_race       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->opt_race)."'";
		$this->sql_opt_religion   = ($this->opt_religion   == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->opt_religion)."'";
		$this->sql_opt_gender     = ($this->opt_gender     == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->opt_gender)."'";
		$this->sql_years_old      = ($this->years_old      == null) ? "NULL" : (int)$this->years_old;
		$this->sql_minAge         = ($this->minAge         == null) ? "NULL" : (int)$this->minAge;
		$this->sql_maxAge         = ($this->maxAge         == null) ? "NULL" : (int)$this->maxAge;
		$this->sql_last_seen      = ($this->last_seen      == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->last_seen)."'";
		$this->sql_last_clothing  = ($this->last_clothing  == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->last_clothing)."'";
		$this->sql_other_comments = ($this->other_comments == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->other_comments)."'";

		$this->sql_rep_uuid       = ($this->rep_uuid       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->rep_uuid)."'";
		$this->sql_relation       = ($this->relation       == null) ? "NULL" : "'".mysql_real_escape_string((string)$this->relation)."'";
	}


	// save the person
	public function insert() {
		$this->sync();
		$q = "
			INSERT INTO person_uuid (
				p_uuid,
				full_name,
				family_name,
				given_name,
				incident_id,
				hospital_uuid,
				expiry_date )
			VALUES (
				".$this->sql_p_uuid.",
				".$this->sql_full_name.",
				".$this->sql_family_name.",
				".$this->sql_given_name.",
				".$this->sql_incident_id.",
				".$this->sql_hospital_uuid.",
				".$this->sql_expiry_date." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person person_uuid insert"); }

		$q = "
			INSERT INTO person_status (
				p_uuid,
				opt_status,
				last_updated,
				creation_time )
			VALUES (
				".$this->sql_p_uuid.",
				".$this->sql_opt_status.",
				".$this->sql_last_updated.",
				".$this->sql_creation_time." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person person_status insert"); }

		$q = "
			INSERT INTO person_details (
				p_uuid,
				birth_date,
				opt_race,
				opt_religion,
				opt_gender,
				years_old,
				minAge,
				maxAge,
				last_seen,
				last_clothing,
				other_comments )
			VALUES (
				".$this->sql_p_uuid.",
				".$this->sql_birth_date.",
				".$this->sql_opt_race.",
				".$this->sql_opt_religion.",
				".$this->sql_opt_gender.",
				".$this->sql_years_old.",
				".$this->sql_minAge.",
				".$this->sql_maxAge.",
				".$this->sql_last_seen.",
				".$this->sql_last_clothing.",
				".$this->sql_other_comments." );
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person person_details insert"); }

		$q = "
			INSERT INTO  `person_to_report` (`p_uuid`, `rep_uuid`)
			VALUES (".$this->sql_p_uuid.", ".$this->sql_rep_uuid.");
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person person_to_report insert"); }

		$this->insertImages();
		$this->insertEdxl();
		$this->makeStaticPfifNote();
		$this->insertVoiceNote();
	}


	// insert into plus_log
	public function plusReportLog() {
		$q = "
			INSERT INTO plus_report_log (p_uuid, enum)
			VALUES ('".$this->p_uuid."', '".$this->xmlFormat."');
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person plus_report insert"); }
	}


	// insert into rap_log
	public function rapReportLog() {
		$q = "
			INSERT INTO rap_log (p_uuid)
			VALUES ('".$this->p_uuid."');
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person rap_log insert"); }
	}


	private function insertVoiceNote() {
		if($this->voice_note != null) {
			$this->voice_note->insert();
		}
	}


	private function insertEdxl() {
		if($this->edxl != null) {
			$this->edxl->insert();
		}
	}


	private function insertImages() {
		foreach($this->images as $image) {
			$image->insert();
		}
	}


	public function makeStaticPfifNote() {
		// make the note unless we are explicitly asked not to...
		if(!$this->makePfifNote) {
			return;
		}

		global $global;
		require_once($global['approot']."inc/lib_uuid.inc");
		require_once($global['approot']."mod/pfif/pfif.inc");
		require_once($global['approot']."mod/pfif/util.inc");

		$p = new Pfif();

		$n = new Pfif_Note();
		$n->note_record_id          = shn_create_uuid('pfif_note');
		$n->person_record_id        = $this->p_uuid;
		$n->linked_person_record_id = null;
		$n->source_date             = $this->last_updated; // since we are now creating the note,
		$n->entry_date              = $this->last_updated; // we use the last_updated for both values
		$n->author_phone            = null;
		$n->email_of_found_person   = null;
		$n->phone_of_found_person   = null;
		$n->last_known_location     = $this->last_seen;
		$n->text                    = $this->other_comments;
		$n->found                   = null; // we have no way to know if the reporter had direct contact (hence we leave this null)

		// figure out the person's pfif status
		$n->status = shn_map_status_to_pfif($this->opt_status);

		// find author name and email...
		$q = "
			SELECT *
			FROM contact c, person_uuid p
			WHERE p.p_uuid = c.p_uuid
			AND c.opt_contact_type = 'email'
			AND p.p_uuid = '".$this->rep_uuid."';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get contact for pfif note"); }

		if($result != NULL && !$result->EOF) {
			$n->author_name  = $result->fields['full_name'];
			$n->author_email = $result->fields['contact_value'];
		} elseif($this->author_name != null) {
			$n->author_name  = $this->author_name;
			$n->author_email = $this->author_email;
		} else {
			$n->author_name  = null;
			$n->author_email = null;
		}

		$p->setNote($n);
		$p->setIncidentId($this->incident_id);
		$p->storeNotesInDatabase();
	}


	public function isEventOpen() {
		// find if this event is open/closed
		$q = "
			SELECT *
			FROM incident
			WHERE incident_id = '".$this->incident_id."';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person check event open"); }

		if($result != NULL && !$result->EOF) {
			$row = $result->FetchRow();
		} else {
			return false;
		}
		if($row['closed'] != 0) {
			return false;
		} else {
			return true;
		}
	}


	public function addImage($fileContentBase64, $filename) {
		// create sahana image
		if(trim($fileContentBase64) != "") {
			$i = new personImage();
			$i->init();
			$i->p_uuid = $this->p_uuid;
			$i->fileContentBase64 = $fileContentBase64;
			$i->original_filename = $filename;
			$this->images[] = $i;
		}
	}


	public function createUUID() {
		global $global;
		require_once($global['approot']."inc/lib_uuid.inc");
		if($this->p_uuid == null || $this->p_uuid == "") {
			$this->p_uuid = shn_create_uuid();
		}
	}


	// set the event id (which will be ignored by XML parser)
	public function setEvent($eventShortName) {
		$q = "
			SELECT *
			FROM `incident`
			WHERE shortname = '".mysql_real_escape_string($eventShortName)."';
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get incident"); }

		$this->incident_id = $result->fields['incident_id'];
	}


	public function parseXml() {
		global $global;
		require_once($global['approot']."inc/lib_uuid.inc");

		// save xml for debuggins?
		if($global['debugAndSaveXmlToFile'] == true) {
			$filename = "debugXML_".mt_rand();
			$path = $global['approot']."www/tmp/plus_cache/".$filename.".xml";
			file_put_contents($path, $this->theString);
		}

		// is this a supported XML type?
		if(!in_array((string)trim($this->xmlFormat), $global['enumXmlFormats'])) {
			return (int)400;
		}

		//$a = xml2array($this->theString);
		$aa = new XMLParser();
		$aa->rawXML = $this->theString;
		$aa->parse();

		if($aa->getError()) {
			return (int)403; // error code for failed to parse xml
		}

		$a = $aa->getArray();

		// parse REUNITE3 XML
		if($this->xmlFormat == "REUNITE3") {
			$this->p_uuid         = $a['person']['p_uuid'];
			$this->given_name     = $a['person']['givenName'];
			$this->family_name    = $a['person']['familyName'];
			$this->full_name      = $this->given_name." ".$this->family_name;
			$this->expiry_date    = $a['person']['expiryDate'];
			$this->opt_status     = $a['person']['status'];
			$this->last_updated   = date('Y-m-d H:i:s');
			$this->creation_time  = $a['person']['dateTimeSent'];
			$this->opt_gender     = $a['person']['gender'];
			$this->years_old      = $a['person']['estimatedAge'];
			$this->minAge         = $a['person']['minAge'];
			$this->maxAge         = $a['person']['maxAge'];
			$this->other_comments = $a['person']['note'];

			// only update the incident_id if not already set
			if($this->incident_id == null) {
				$this->incident_id = $a['person']['eventId'];
			}

			foreach($a['person']['photos'] as $photo) {
				if(trim($photo['data']) != "") {
					$i = new personImage();
					$i->init();
					$i->p_uuid = $this->p_uuid;
					$i->fileContentBase64 = $photo['data'];
					foreach($photo['tags'] as $tag) {
						$t = new personImageTag();
						$t->init();
						$t->image_id = $i->image_id;
						$t->tag_x    = $tag['x'];
						$t->tag_y    = $tag['y'];
						$t->tag_w    = $tag['w'];
						$t->tag_h    = $tag['h'];
						$t->tag_text = $tag['text'];
						$i->tags[] = $t;
					}
					$this->images[] = $i;
				}
			}

			// if there is actual voicenote data, save process it...
			if(trim($a['person']['voiceNote']['data']) != "") {
				$v = new voiceNote();
				$v->init();
				$v->p_uuid      = $this->p_uuid;
				$v->dataBase64  = $a['person']['voiceNote']['data'];
				$v->length      = $a['person']['voiceNote']['length'];
				$v->format      = $a['person']['voiceNote']['format'];
				$v->sample_rate = $a['person']['voiceNote']['sampleRate'];
				$v->channels    = $a['person']['voiceNote']['numberOfChannels'];
				$v->speaker     = $a['person']['voiceNote']['speaker'];
				$this->voice_note = $v;
			}

			// check for p_uuid collision with already present data, return 401 error if p_uuid already exists
			$q = "
				SELECT count(*)
				FROM person_uuid
				WHERE p_uuid = '".mysql_real_escape_string((string)$this->p_uuid)."';
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person check p_uuid collision"); }

			if((int)$result->fields['count(*)'] > 0 ) {
				return (int)401;
			}

			// check if reported p_uuid is valid (in range of sequence) ~ 402 error if not
			if(!shn_is_p_uuid_valid($this->p_uuid)) {
				return (int)402;
			}

			// check if the event is closed to reporting...
			if(!$this->isEventOpen()) {
				return (int)405;
			}

			// no errors
			return (int)0;


		// parse REUNITE2 XML
		} elseif($this->xmlFormat == "REUNITE2") {

			// figure out the incident_id
			$shortName = strtolower($a['lpfContent']['person']['eventShortName']);
			$q = "
				SELECT *
				FROM incident
				WHERE shortname = '".mysql_real_escape_string((string)$shortName)."';
			";

			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get incident"); }

			if($result != NULL && !$result->EOF) {
				$this->incident_id = $result->fields['incident_id'];
			} else {
				return (int)406;
			}

			// extract other xml data
			$this->createUUID();
			$this->given_name     = $a['lpfContent']['person']['firstName'];
			$this->family_name    = $a['lpfContent']['person']['familyName'];
			$this->full_name      = $this->given_name." ".$this->family_name;
			$this->opt_status     = substr(strtolower($a['lpfContent']['person']['status']['healthStatus']), 0, 3);
			$this->last_updated   = date('Y-m-d H:i:s');
			$this->creation_time  = $a['lpfContent']['person']['dateTimeSent'];
			$this->opt_gender     = substr(strtolower($a['lpfContent']['person']['gender']), 0, 3);
			$this->years_old      = $a['lpfContent']['person']['estimatedAgeInYears'];
			$this->minAge         = $a['lpfContent']['person']['ageGroup']['minAge'];
			$this->maxAge         = $a['lpfContent']['person']['ageGroup']['maxAge'];
			$this->other_comments = $a['lpfContent']['person']['notes'];

			// check if the event is closed to reporting...
			if(!$this->isEventOpen()) {
				return (int)405;
			}

			// no errors
			return (int)0;


		// parse TRIAGEPIC1 XML
		} elseif($this->xmlFormat == "TRIAGEPIC1") {

			$this->edxl = new personEdxl();
			$this->edxl->init();

			// when we have more than 1 contentObject, they are renamed to 0...x
			if(isset($a['EDXLDistribution'][0])) {
				$ix = 0;

			// when there is only 1 contentObject, we go by name
			} elseif(isset($a['EDXLDistribution']['contentObject'])) {
				$ix = "contentObject";

			// all else, we fail and quit
			} else {
				return (int)403; // error code for failed to parse xml
			}

			$this->createUUID();
			$this->family_name = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['lastName'];
			$this->given_name  = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['firstName'];
			$this->full_name   = $this->given_name." ".$this->family_name;


			$eventName = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['eventName'];
			$q = "
				SELECT *
				FROM incident
				WHERE shortname = '".mysql_real_escape_string((string)$eventName)."';
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get incident"); }

			$this->incident_id = $result->fields["incident_id"];


			$b = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['triageCategory'];
			if(($b == "Green") || ($b == "BH Green")) {
				$this->opt_status = "ali";
			} elseif(($b == "Yellow") || ($b == "Red") || ($b == "Gray")) {
				$this->opt_status = "inj";
			} elseif($b == "Black") {
				$this->opt_status = "dec";
			} else {
				$this->opt_status = "unk";
			}

			$this->last_updated = date('Y-m-d H:i:s');

			// <dateTimeSent>2011-03-28T07:52:17Z</dateTimeSent>
			$datetime      = $a['EDXLDistribution']['dateTimeSent'];
			$timezoneUTC   = new DateTimeZone("UTC");
			$timezoneLocal = new DateTimeZone(date_default_timezone_get());
			$datetime2     = new DateTime();
			$datetime2->setTimezone($timezoneUTC);
			$datetime2->setTimestamp(strtotime($datetime));
			$datetime2->setTimezone($timezoneLocal);
			$this->creation_time = $datetime2->format('Y-m-d H:i:s');

			$this->opt_gender = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['gender'];

			$peds = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['peds'];

			if($peds == "Y") {
				$this->minAge = 0;
				$this->maxAge = 17;
			} elseif($peds == "N") {
				$this->minAge = 18;
				$this->maxAge = 150;
			} elseif($peds == "Y,N") {
				$this->minAge = 0;
				$this->maxAge = 150;
			}

			$this->other_comments = $a['EDXLDistribution'][$ix]['contentDescription'];


			$orgId  = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['organization']['orgId'];
			$q = "
				SELECT *
				FROM hospital
				WHERE npi = '".mysql_real_escape_string((string)$orgId)."';
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get hospital"); }

			$this->hospital_uuid = $result->fields["hospital_uuid"];
			$this->last_seen     = $result->fields["name"]." Hospital";

			$this->edxl->content_descr   = $a['EDXLDistribution'][$ix]['contentDescription'];
			$this->edxl->p_uuid          = $this->p_uuid;
			$this->edxl->schema_version  = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['version'];
			$this->edxl->login_machine   = "n/a"; //null; HACK! cant be null
			$this->edxl->login_account   = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['login']['userName'];
			$this->edxl->person_id       = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['personId'];
			$this->edxl->event_name      = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['eventName'];
			$this->edxl->event_long_name = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['eventLongName'];
			$this->edxl->org_name        = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['organization']['orgName'];
			$this->edxl->org_id          = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['organization']['orgId'];
			$this->edxl->last_name       = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['lastName'];
			$this->edxl->first_name      = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['firstName'];
			$this->edxl->gender          = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['gender'];
			$this->edxl->peds            = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['peds'];
			$this->edxl->triage_category = $a['EDXLDistribution'][$ix]['xmlContent']['lpfContent']['person']['triageCategory'];
			$this->edxl->when_sent       = $this->last_updated;
			$this->edxl->sender_id       = $a['EDXLDistribution']['senderID'];
			$this->edxl->distr_id        = $a['EDXLDistribution']['distributionID'];
			$this->edxl->distr_status    = $a['EDXLDistribution']['distributionStatus'];
			$this->edxl->distr_type      = $a['EDXLDistribution']['distributionType'];
			$this->edxl->combined_conf   = $a['EDXLDistribution']['combinedConfidentiality'];
			$this->edxl->language        = null;
			$this->edxl->when_here       = $this->creation_time;
			$this->edxl->inbound         = 1; //null; HACK! cant be null
			$this->edxl->type            = "lpf";

			// parse all images
			for($n = 0; $n < sizeof($a['EDXLDistribution']); $n++) {
				if(isset($a['EDXLDistribution'][$n]['nonXMLContent']) && $a['EDXLDistribution'][$n]['nonXMLContent'] != null) {

					$imageNode = $a['EDXLDistribution'][$n]['nonXMLContent'];

					// create sahana image
					if(trim($imageNode['contentData']) != "") {
						$i = new personImage();
						$i->init();
						$i->p_uuid = $this->p_uuid;
						$i->fileContentBase64 = $imageNode['contentData'];
						$i->original_filename = $imageNode['uri'];
						$this->images[] = $i;
					}

					// create edxl image
					$this->edxl->mimeTypes[]    = $imageNode['mimeType'];
					$this->edxl->uris[]         = $imageNode['uri'];
					$this->edxl->contentDatas[] = $imageNode['contentData'];
					$this->edxl->image_ids[]    = $i->image_id;
					$this->edxl->image_co_ids[] = $this->edxl->getNew_co_id();
				}
			}

			// check if the event is closed to reporting...
			if(!$this->isEventOpen()) {
				return (int)405;
			}

			// exit with success
			return (int)0;

		// parse TRIAGEPIC0 XML
		} elseif($this->xmlFormat == "TRIAGEPIC0") {

			$this->edxl = new personEdxl();
			$this->edxl->init();

			$this->createUUID();
			$this->family_name = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName'];
			$this->given_name  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName'];
			$this->full_name   = $this->given_name." ".$this->family_name;


			$eventName = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventName'];
			$q = "
				SELECT *
				FROM incident
				WHERE shortname = '".mysql_real_escape_string((string)$eventName)."';
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get incident"); }

			$this->incident_id = $result->fields["incident_id"];


			$b = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategory'];
			if(($b == "Green") || ($b == "BH Green")) {
				$this->opt_status = "ali";
			} elseif(($b == "Yellow") || ($b == "Red") || ($b == "Gray")) {
				$this->opt_status = "inj";
			} elseif($b == "Black") {
				$this->opt_status = "dec";
			} else {
				$this->opt_status = "unk";
			}

			$this->last_updated = date('Y-m-d H:i:s');

			// <dateTimeSent>2011-03-28T07:52:17Z</dateTimeSent>
			$datetime      = $a['EDXLDistribution']['dateTimeSent'];
			$timezoneUTC   = new DateTimeZone("UTC");
			$timezoneLocal = new DateTimeZone(date_default_timezone_get());
			$datetime2     = new DateTime();
			$datetime2->setTimezone($timezoneUTC);
			$datetime2->setTimestamp(strtotime($datetime));
			$datetime2->setTimezone($timezoneLocal);
			$this->creation_time = $datetime2->format('Y-m-d H:i:s');

			$this->opt_gender = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['gender'];

			$peds = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['peds'];

			if($peds == "Y") {
				$this->minAge = 0;
				$this->maxAge = 17;
			} elseif($peds == "N") {
				$this->minAge = 18;
				$this->maxAge = 150;
			} elseif($peds == "Y,N") {
				$this->minAge = 0;
				$this->maxAge = 150;
			}

			$this->other_comments = $a['EDXLDistribution']['contentObject']['contentDescription'];


			$orgId  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgId'];
			$q = "
				SELECT *
				FROM hospital
				WHERE npi = '".mysql_real_escape_string((string)$orgId)."';
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person get hospital"); }

			$this->hospital_uuid = $result->fields["hospital_uuid"];
			$this->last_seen     = $result->fields["name"]." Hospital";

			$this->edxl->content_descr   = $a['EDXLDistribution']['contentObject']['contentDescription'];
			$this->edxl->p_uuid          = $this->p_uuid;
			$this->edxl->schema_version  = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['version'];
			$this->edxl->login_machine   = "n/a"; //null; HACK! cant be null
			$this->edxl->login_account   = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['login']['username'];
			$this->edxl->person_id       = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['personId'];
			$this->edxl->event_name      = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventName'];
			$this->edxl->event_long_name = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['eventLongName'];
			$this->edxl->org_name        = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgName'];
			$this->edxl->org_id          = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['organization']['orgId'];
			$this->edxl->last_name       = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['lastName'];
			$this->edxl->first_name      = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['firstName'];
			$this->edxl->gender          = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['gender'];
			$this->edxl->peds            = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['peds'];
			$this->edxl->triage_category = $a['EDXLDistribution']['contentObject']['xmlContent']['embeddedXMLContent']['lpfContent']['person']['triageCategory'];
			$this->edxl->when_sent       = $this->last_updated;
			$this->edxl->sender_id       = $a['EDXLDistribution']['senderID'];
			$this->edxl->distr_id        = $a['EDXLDistribution']['distributionID'];
			$this->edxl->distr_status    = $a['EDXLDistribution']['distributionStatus'];
			$this->edxl->distr_type      = $a['EDXLDistribution']['distributionType'];
			$this->edxl->combined_conf   = $a['EDXLDistribution']['combinedConfidentiality'];
			$this->edxl->language        = null;
			$this->edxl->when_here       = $this->creation_time;
			$this->edxl->inbound         = 1; //null; HACK! cant be null
			$this->edxl->type            = "lpf";

			// check if the event is closed to reporting...
			if(!$this->isEventOpen()) {
				return (int)405;
			}

			// exit with success
			return (int)0;

		// how did we get here?
		} else {
			return (int)9999;
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
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "pop send message"); }
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



/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        XMLparser
* @link         http://goo.gl/3vnSr
*
* $p = new XMLParser(file_get_contents('referenceXML_TP.xml'));
* echo print_r($p->getOutput(), true);
* echo $p->getStatus();
*
********************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************/

class XMLParser  {

	// raw xml
	public $rawXML;

	// xml parser
	private $parser = null;

	// array returned by the xml parser
	private $valueArray = array();
	private $keyArray = array();

	// arrays for dealing with duplicate keys
	private $duplicateKeys = array();

	// return data
	private $output = array();
	private $errorMessage;

	// true if an error was encountered
	private $error;


	public function __construct() {
		$this->error = false;
		$this->rawXML = null;
		$this->parser = xml_parser_create();
	}


	public function parse(){

		$parser = $this->parser;

		xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0); // Dont mess with my cAsE sEtTings
		xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);     // Dont bother with empty info
		if(!xml_parse_into_struct($parser, $this->rawXML, $this->valueArray, $this->keyArray)) {
			$this->errorMessage = 'error: '.xml_error_string(xml_get_error_code($parser)).' at line '.xml_get_current_line_number($parser);
			$this->error = true;
			return;
		}
		xml_parser_free($parser);

		$this->findDuplicateKeys();

		// tmp array used for stacking
		$stack = array();
		$increment = 0;

		foreach($this->valueArray as $val) {
			if($val['type'] == "open") {

				//if array key is duplicate then send in increment
				if(array_key_exists($val['tag'], $this->duplicateKeys)){
					array_push($stack, $this->duplicateKeys[$val['tag']]);
					$this->duplicateKeys[$val['tag']]++;
				} else {
					// else send in tag
					array_push($stack, $val['tag']);
				}

			} elseif($val['type'] == "close") {
				array_pop($stack);

				// reset the increment if they tag does not exists in the stack
				if(array_key_exists($val['tag'], $stack)){
					$this->duplicateKeys[$val['tag']] = 0;
				}

			} elseif($val['type'] == "complete") {

				//if array key is duplicate then send in increment
				if(array_key_exists($val['tag'], $this->duplicateKeys)){
					array_push($stack, $this->duplicateKeys[$val['tag']]);
					$this->duplicateKeys[$val['tag']]++;
				} else {
					// else send in tag
					array_push($stack,  $val['tag']);
				}
				if(!isset($val['value'])) {
					$val['value'] = null;
				}
				$this->setArrayValue($this->output, $stack, $val['value']);
				array_pop($stack);
			}
			$increment++;
		}
		$this->status = 'success: xml was parsed';
		return;
	}


	private function findDuplicateKeys() {
		for($i=0;$i < count($this->valueArray); $i++) {

			// duplicate keys are when two complete tags are side by side
			if($this->valueArray[$i]['type'] == "complete") {
				if( $i+1 < count($this->valueArray)) {
					if($this->valueArray[$i+1]['tag'] == $this->valueArray[$i]['tag'] && $this->valueArray[$i+1]['type'] == "complete") {
						$this->duplicateKeys[$this->valueArray[$i]['tag']] = 0;
					}
				}
			}

			// also when a close tag is before an open tag and the tags are the same
			if($this->valueArray[$i]['type'] == "close") {
				if( $i+1 < count($this->valueArray)) {
					if($this->valueArray[$i+1]['type'] == "open" && $this->valueArray[$i+1]['tag'] == $this->valueArray[$i]['tag']) {
						$this->duplicateKeys[$this->valueArray[$i]['tag']] = 0;
					}
				}
			}
		}
	}


	private function setArrayValue(&$array, $stack, $value) {
		if ($stack) {
			$key = array_shift($stack);
			$this->setArrayValue($array[$key], $stack, $value);
			return $array;
		} else {
			$array = $value;
		}
	}


	public function getArray(){
		return $this->output;
	}


	public function getError(){
		return $this->error;
	}


	public function getErrorMessage(){
		return $this->errorMessage;
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// logs all DAO errors to database...
function daoErrorLog($file, $line, $method, $class, $function, $errorMessage, $other) {
	// init db
	global $global;
	$db = $global['db'];
	$q = "
		INSERT INTO dao_error_log (
			file,
			line,
			method,
			class,
			function,
			error_message,
			other )
		VALUES (
			'".mysql_real_escape_string((string)$file)."',
			'".mysql_real_escape_string((string)$line)."',
			'".mysql_real_escape_string((string)$method)."',
			'".mysql_real_escape_string((string)$class)."',
			'".mysql_real_escape_string((string)$function)."',
			'".mysql_real_escape_string((string)$errorMessage)."',
			'".mysql_real_escape_string((string)$other)."' );
	";
	$result = $db->Execute($q);
}




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


