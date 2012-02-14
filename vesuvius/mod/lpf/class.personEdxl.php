<?php
/** ******************************************************************************************************************************************************************
*********************************************************************************************************************************************************************
********************************************************************************************************************************************************************
*
* @class        personEdxl
* @version      12
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

	public $Ode_id;
	public $Oco_id;
	public $Ocontent_descr;
	public $Oincident_id;
	public $Oincident_descr;
	public $Oconfidentiality;

	private $sql_de_id;
	private $sql_co_id;
	private $sql_content_descr;
	private $sql_incident_id;
	private $sql_incident_descr;
	private $sql_confidentiality;

	private $sql_Ode_id;
	private $sql_Oco_id;
	private $sql_Ocontent_descr;
	private $sql_Oincident_id;
	private $sql_Oincident_descr;
	private $sql_Oconfidentiality;

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

	public $Op_uuid;
	public $Otype;
	public $Oschema_version;
	public $Ologin_machine;
	public $Ologin_account;
	public $Operson_id;
	public $Oevent_name;
	public $Oevent_long_name;
	public $Oorg_name;
	public $Oorg_id;
	public $Olast_name;
	public $Ofirst_name;
	public $Ogender;
	public $Opeds;
	public $Otriage_category;

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

	private $sql_Op_uuid;
	private $sql_Otype;
	private $sql_Oschema_version;
	private $sql_Ologin_machine;
	private $sql_Ologin_account;
	private $sql_Operson_id;
	private $sql_Oevent_name;
	private $sql_Oevent_long_name;
	private $sql_Oorg_name;
	private $sql_Oorg_id;
	private $sql_Olast_name;
	private $sql_Ofirst_name;
	private $sql_Ogender;
	private $sql_Opeds;
	private $sql_Otriage_category;

	// edxl_de_header
	public $when_sent;
	public $sender_id;     // Email, phone num, etc. Not always URI, URN, URL
	public $distr_id;      // Distribution ID. Sender may or may not choose to vary.
	public $distr_status;
	public $distr_type;    // Not included: types for sensor grids
	public $combined_conf; // Combined confidentiality of all content objects
	public $language;
	public $when_here;     // Received or sent from here. [local]
	public $inbound;       // BOOLEAN [local]

	public $Owhen_sent;
	public $Osender_id;
	public $Odistr_id;
	public $Odistr_status;
	public $Odistr_type;
	public $Ocombined_conf;
	public $Olanguage;
	public $Owhen_here;
	public $Oinbound;

	private $sql_when_sent;
	private $sql_sender_id;
	private $sql_distr_id;
	private $sql_distr_status;
	private $sql_distr_type;
	private $sql_combined_conf;
	private $sql_language;
	private $sql_when_here;
	private $sql_inbound;

	private $sql_Owhen_sent;
	private $sql_Osender_id;
	private $sql_Odistr_id;
	private $sql_Odistr_status;
	private $sql_Odistr_type;
	private $sql_Ocombined_conf;
	private $sql_Olanguage;
	private $sql_Owhen_here;
	private $sql_Oinbound;

	// edxl_co_photos
	public $mimeTypes;
	public $uris;
	public $contentDatas;
	public $image_ids;
	public $image_co_ids;
	public $image_sha1;


	// Constructor
	public function __construct() {

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

		$this->Ode_id           = null;
		$this->Oco_id           = null;
		$this->Ocontent_descr   = null;
		$this->Oincident_id     = null;
		$this->Oincident_descr  = null;
		$this->Oconfidentiality = null;
		$this->Op_uuid          = null;
		$this->Otype            = null;
		$this->Oschema_version  = null;
		$this->Ologin_machine   = null;
		$this->Ologin_account   = null;
		$this->Operson_id       = null;
		$this->Oevent_name      = null;
		$this->Oevent_long_name = null;
		$this->Oorg_name        = null;
		$this->Oorg_id          = null;
		$this->Olast_name       = null;
		$this->Ofirst_name      = null;
		$this->Ogender          = null;
		$this->Opeds            = null;
		$this->Otriage_category = null;
		$this->Owhen_sent       = null;
		$this->Osender_id       = null;
		$this->Odistr_id        = null;
		$this->Odistr_status    = null;
		$this->Odistr_type      = null;
		$this->Ocombined_conf   = null;
		$this->Olanguage        = null;
		$this->Owhen_here       = null;
		$this->Oinbound         = null;

		$this->mimeTypes    = array();
		$this->uris         = array();
		$this->contentDatas = array();
		$this->image_ids    = array();
		$this->image_co_ids = array();
		$this->image_sha1   = array();

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

		$this->sql_Ode_id           = null;
		$this->sql_Oco_id           = null;
		$this->sql_Ocontent_descr   = null;
		$this->sql_Oincident_id     = null;
		$this->sql_Oincident_descr  = null;
		$this->sql_Oconfidentiality = null;
		$this->sql_Op_uuid          = null;
		$this->sql_Otype            = null;
		$this->sql_Oschema_version  = null;
		$this->sql_Ologin_machine   = null;
		$this->sql_Ologin_account   = null;
		$this->sql_Operson_id       = null;
		$this->sql_Oevent_name      = null;
		$this->sql_Oevent_long_name = null;
		$this->sql_Oorg_name        = null;
		$this->sql_Oorg_id          = null;
		$this->sql_Olast_name       = null;
		$this->sql_Ofirst_name      = null;
		$this->sql_Ogender          = null;
		$this->sql_Opeds            = null;
		$this->sql_Otriage_category = null;
		$this->sql_Owhen_sent       = null;
		$this->sql_Osender_id       = null;
		$this->sql_Odistr_id        = null;
		$this->sql_Odistr_status    = null;
		$this->sql_Odistr_type      = null;
		$this->sql_Ocombined_conf   = null;
		$this->sql_Olanguage        = null;
		$this->sql_Owhen_here       = null;
		$this->sql_Oinbound         = null;
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

		$this->Ode_id           = null;
		$this->Oco_id           = null;
		$this->Ocontent_descr   = null;
		$this->Oincident_id     = null;
		$this->Oincident_descr  = null;
		$this->Oconfidentiality = null;
		$this->Op_uuid          = null;
		$this->Otype            = null;
		$this->Oschema_version  = null;
		$this->Ologin_machine   = null;
		$this->Ologin_account   = null;
		$this->Operson_id       = null;
		$this->Oevent_name      = null;
		$this->Oevent_long_name = null;
		$this->Oorg_name        = null;
		$this->Oorg_id          = null;
		$this->Olast_name       = null;
		$this->Ofirst_name      = null;
		$this->Ogender          = null;
		$this->Opeds            = null;
		$this->Otriage_category = null;
		$this->Owhen_sent       = null;
		$this->Osender_id       = null;
		$this->Odistr_id        = null;
		$this->Odistr_status    = null;
		$this->Odistr_type      = null;
		$this->Ocombined_conf   = null;
		$this->Olanguage        = null;
		$this->Owhen_here       = null;
		$this->Oinbound         = null;

		$this->mimeTypes    = null;
		$this->uris         = null;
		$this->contentDatas = null;
		$this->image_ids    = null;
		$this->image_co_ids = null;
		$this->image_sha1   = null;

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

		$this->sql_Ode_id           = null;
		$this->sql_Oco_id           = null;
		$this->sql_Ocontent_descr   = null;
		$this->sql_Oincident_id     = null;
		$this->sql_Oincident_descr  = null;
		$this->sql_Oconfidentiality = null;
		$this->sql_Op_uuid          = null;
		$this->sql_Otype            = null;
		$this->sql_Oschema_version  = null;
		$this->sql_Ologin_machine   = null;
		$this->sql_Ologin_account   = null;
		$this->sql_Operson_id       = null;
		$this->sql_Oevent_name      = null;
		$this->sql_Oevent_long_name = null;
		$this->sql_Oorg_name        = null;
		$this->sql_Oorg_id          = null;
		$this->sql_Olast_name       = null;
		$this->sql_Ofirst_name      = null;
		$this->sql_Ogender          = null;
		$this->sql_Opeds            = null;
		$this->sql_Otriage_category = null;
		$this->sql_Owhen_sent       = null;
		$this->sql_Osender_id       = null;
		$this->sql_Odistr_id        = null;
		$this->sql_Odistr_status    = null;
		$this->sql_Odistr_type      = null;
		$this->sql_Ocombined_conf   = null;
		$this->sql_Olanguage        = null;
		$this->sql_Owhen_here       = null;
		$this->sql_Oinbound         = null;
	}

	/** initializes some values for a new instance (instead of when we load a previous instance) */
	public function init() {

		// update sequences
		$this->co_id = shn_create_uuid("edxl_co_header");
		$this->de_id = shn_create_uuid("edxl_de_header");
	}


	/** load data from db */
	public function load() {

		$q = "
			SELECT *
			FROM edxl_co_lpf
			WHERE p_uuid = '".mysql_real_escape_string((string)$this->p_uuid)."' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl load 1 ((".$q."))"); }

		if($result != NULL && !$result->EOF) {

			$this->co_id           = $result->fields['co_id'];
			$this->p_uuid          = $result->fields['p_uuid'];
			$this->schema_version  = $result->fields['schema_version'];
			$this->login_machine   = $result->fields['login_machine'];
			$this->login_account   = $result->fields['login_account'];
			$this->person_id       = $result->fields['person_id'];
			$this->event_name      = $result->fields['event_name'];
			$this->event_long_name = $result->fields['event_long_name'];
			$this->org_name        = $result->fields['org_name'];
			$this->org_id          = $result->fields['org_id'];
			$this->last_name       = $result->fields['last_name'];
			$this->first_name      = $result->fields['first_name'];
			$this->gender          = $result->fields['gender'];
			$this->peds            = $result->fields['peds'];
			$this->triage_category = $result->fields['triage_category'];

			// original values for updates...
			$this->Oco_id           = $result->fields['co_id'];
			$this->Op_uuid          = $result->fields['p_uuid'];
			$this->Oschema_version  = $result->fields['schema_version'];
			$this->Ologin_machine   = $result->fields['login_machine'];
			$this->Ologin_account   = $result->fields['login_account'];
			$this->Operson_id       = $result->fields['person_id'];
			$this->Oevent_name      = $result->fields['event_name'];
			$this->Oevent_long_name = $result->fields['event_long_name'];
			$this->Oorg_name        = $result->fields['org_name'];
			$this->Oorg_id          = $result->fields['org_id'];
			$this->Olast_name       = $result->fields['last_name'];
			$this->Ofirst_name      = $result->fields['first_name'];
			$this->Ogender          = $result->fields['gender'];
			$this->Opeds            = $result->fields['peds'];
			$this->Otriage_category = $result->fields['triage_category'];
		} else {
			// we failed to load a de object for this person, so fail the load (indicate to person class there is no edxl for this person)
			return false;
		}

		$q = "
			SELECT *
			FROM edxl_co_header
			WHERE p_uuid = '".mysql_real_escape_string((string)$this->p_uuid)."'
			AND type = 'lpf' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl load 2 ((".$q."))"); }

		if($result != NULL && !$result->EOF) {

			$this->de_id           = $result->fields['de_id'];
			$this->co_id           = $result->fields['co_id'];
			$this->p_uuid          = $result->fields['p_uuid'];
			$this->type            = $result->fields['type'];
			$this->content_descr   = $result->fields['content_descr'];
			$this->incident_id     = $result->fields['incident_id'];
			$this->incident_descr  = $result->fields['incident_descr'];
			$this->confidentiality = $result->fields['confidentiality'];

			// save original values for updates...
			$this->Ode_id           = $result->fields['de_id'];
			$this->Oco_id           = $result->fields['co_id'];
			$this->Op_uuid          = $result->fields['p_uuid'];
			$this->Otype            = $result->fields['type'];
			$this->Ocontent_descr   = $result->fields['content_descr'];
			$this->Oincident_id     = $result->fields['incident_id'];
			$this->Oincident_descr  = $result->fields['incident_descr'];
			$this->Oconfidentiality = $result->fields['confidentiality'];
		} else {
			// we failed to load a content object for this person, so fail the load (indicate to person class there is no edxl for this person)
			return false;
		}


		$q = "
			SELECT *
			FROM edxl_de_header
			WHERE de_id = '".mysql_real_escape_string((string)$this->de_id)."' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl load 3 ((".$q."))"); }

		if($result != NULL && !$result->EOF) {

			$this->de_id         = $result->fields['de_id'];
			$this->when_sent     = $result->fields['when_sent'];
			$this->sender_id     = $result->fields['sender_id'];
			$this->distr_id      = $result->fields['distr_id'];
			$this->distr_status  = $result->fields['distr_status'];
			$this->distr_type    = $result->fields['distr_type'];
			$this->combined_conf = $result->fields['combined_conf'];
			$this->language      = $result->fields['language'];
			$this->when_here     = $result->fields['when_here'];
			$this->inbound       = $result->fields['inbound'];

			// original values for updates...
			$this->Ode_id         = $result->fields['de_id'];
			$this->Owhen_sent     = $result->fields['when_sent'];
			$this->Osender_id     = $result->fields['sender_id'];
			$this->Odistr_id      = $result->fields['distr_id'];
			$this->Odistr_status  = $result->fields['distr_status'];
			$this->Odistr_type    = $result->fields['distr_type'];
			$this->Ocombined_conf = $result->fields['combined_conf'];
			$this->Olanguage      = $result->fields['language'];
			$this->Owhen_here     = $result->fields['when_here'];
			$this->Oinbound       = $result->fields['inbound'];
		} else {
			// we failed to load a de object for this person, so fail the load (indicate to person class there is no edxl for this person)
			return false;
		}

		// load image CO's if there are any....
		$q = "
			SELECT *
			FROM edxl_co_header h, edxl_co_photos p
			WHERE h.p_uuid = '".mysql_real_escape_string((string)$this->p_uuid)."'
			AND p.p_uuid = '".mysql_real_escape_string((string)$this->p_uuid)."'
			AND h.co_id = p.co_id
			AND h.type = 'pix' ;
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl load 4 ((".$q."))"); }
		while(!$result == NULL && !$result->EOF) {

			$this->image_co_ids[] = $result->fields['co_id'];
			$this->mimeTypes[]    = $result->fields['mimeType'];
			$this->uris[]         = $result->fields['uri'];
			$this->contentDatas[] = $result->fields['contentData'];
			$this->image_ids[]    = $result->fields['image_id'];
			$this->image_sha1[]   = $result->fields['sha1'];
			$result->MoveNext();
		}
		return true;
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

		$this->sql_de_id           = ($this->de_id           === null) ? "NULL" : (int)$this->de_id;
		$this->sql_co_id           = ($this->co_id           === null) ? "NULL" : (int)$this->co_id;
		$this->sql_content_descr   = ($this->content_descr   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->content_descr)."'";
		$this->sql_incident_id     = ($this->incident_id     === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->incident_id)."'";
		$this->sql_incident_descr  = ($this->content_descr   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->content_descr)."'";
		$this->sql_confidentiality = ($this->confidentiality === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->confidentiality)."'";
		$this->sql_p_uuid          = ($this->p_uuid          === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->p_uuid)."'";
		$this->sql_type            = ($this->type            === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->type)."'";
		$this->sql_schema_version  = ($this->schema_version  === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->schema_version)."'";
		$this->sql_login_machine   = ($this->login_machine   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->login_machine)."'";
		$this->sql_login_account   = ($this->login_account   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->login_account)."'";
		$this->sql_person_id       = ($this->person_id       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->person_id)."'";
		$this->sql_event_name      = ($this->event_name      === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->event_name)."'";
		$this->sql_event_long_name = ($this->event_long_name === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->event_long_name)."'";
		$this->sql_org_name        = ($this->org_name        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->org_name)."'";
		$this->sql_org_id          = ($this->org_id          === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->org_id)."'";
		$this->sql_last_name       = ($this->last_name       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->last_name)."'";
		$this->sql_first_name      = ($this->first_name      === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->first_name)."'";
		$this->sql_gender          = ($this->gender          === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->gender)."'";
		$this->sql_peds            = ($this->peds            === null) ? "NULL" : (int)$this->peds;
		$this->sql_triage_category = ($this->triage_category === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->triage_category)."'";
		$this->sql_when_sent       = ($this->when_sent       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->when_sent)."'";
		$this->sql_sender_id       = ($this->sender_id       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->sender_id)."'";
		$this->sql_distr_id        = ($this->distr_id        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->distr_id)."'";
		$this->sql_distr_status    = ($this->distr_status    === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->distr_status)."'";
		$this->sql_distr_type      = ($this->distr_type      === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->distr_type)."'";
		$this->sql_combined_conf   = ($this->combined_conf   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->combined_conf)."'";
		$this->sql_language        = ($this->language        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->language)."'";
		$this->sql_when_here       = ($this->when_here       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->when_here)."'";
		$this->sql_inbound         = ($this->inbound         === null) ? "NULL" : (int)$this->inbound;

		$this->sql_Ode_id           = ($this->Ode_id           === null) ? "NULL" : (int)$this->Ode_id;
		$this->sql_Oco_id           = ($this->Oco_id           === null) ? "NULL" : (int)$this->Oco_id;
		$this->sql_Ocontent_descr   = ($this->Ocontent_descr   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ocontent_descr)."'";
		$this->sql_Oincident_id     = ($this->Oincident_id     === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oincident_id)."'";
		$this->sql_Oincident_descr  = ($this->Ocontent_descr   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ocontent_descr)."'";
		$this->sql_Oconfidentiality = ($this->Oconfidentiality === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oconfidentiality)."'";
		$this->sql_Op_uuid          = ($this->Op_uuid          === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Op_uuid)."'";
		$this->sql_Otype            = ($this->Otype            === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Otype)."'";
		$this->sql_Oschema_version  = ($this->Oschema_version  === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oschema_version)."'";
		$this->sql_Ologin_machine   = ($this->Ologin_machine   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ologin_machine)."'";
		$this->sql_Ologin_account   = ($this->Ologin_account   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ologin_account)."'";
		$this->sql_Operson_id       = ($this->Operson_id       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Operson_id)."'";
		$this->sql_Oevent_name      = ($this->Oevent_name      === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oevent_name)."'";
		$this->sql_Oevent_long_name = ($this->Oevent_long_name === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oevent_long_name)."'";
		$this->sql_Oorg_name        = ($this->Oorg_name        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oorg_name)."'";
		$this->sql_Oorg_id          = ($this->Oorg_id          === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Oorg_id)."'";
		$this->sql_Olast_name       = ($this->Olast_name       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Olast_name)."'";
		$this->sql_Ofirst_name      = ($this->Ofirst_name      === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ofirst_name)."'";
		$this->sql_Ogender          = ($this->Ogender          === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ogender)."'";
		$this->sql_Opeds            = ($this->Opeds            === null) ? "NULL" : (int)$this->Opeds;
		$this->sql_Otriage_category = ($this->Otriage_category === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Otriage_category)."'";
		$this->sql_Owhen_sent       = ($this->Owhen_sent       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Owhen_sent)."'";
		$this->sql_Osender_id       = ($this->Osender_id       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Osender_id)."'";
		$this->sql_Odistr_id        = ($this->Odistr_id        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Odistr_id)."'";
		$this->sql_Odistr_status    = ($this->Odistr_status    === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Odistr_status)."'";
		$this->sql_Odistr_type      = ($this->Odistr_type      === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Odistr_type)."'";
		$this->sql_Ocombined_conf   = ($this->Ocombined_conf   === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Ocombined_conf)."'";
		$this->sql_Olanguage        = ($this->Olanguage        === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Olanguage)."'";
		$this->sql_Owhen_here       = ($this->Owhen_here       === null) ? "NULL" : "'".mysql_real_escape_string((string)$this->Owhen_here)."'";
		$this->sql_Oinbound         = ($this->Oinbound         === null) ? "NULL" : (int)$this->Oinbound;
	}


	// Delete Function
	public function delete() {

		// just to mysql-ready the data nodes...
		$this->sync();

		$q = "
			DELETE FROM edxl_co_photos
			WHERE p_uuid = ".$this->sql_p_uuid.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person delete edxl 1 ((".$q."))"); }

		$q = "
			DELETE FROM edxl_co_lpf
			WHERE p_uuid = ".$this->sql_p_uuid.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person delete edxl 2 ((".$q."))"); }

		$q = "
			DELETE FROM edxl_co_header
			WHERE p_uuid = ".$this->sql_p_uuid.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person delete edxl 3 ((".$q."))"); }

		$q = "
			DELETE FROM edxl_de_header
			WHERE de_id = ".$this->sql_de_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "person delete edxl 4 ((".$q."))"); }
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
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl de header insert ((".$q."))"); }

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
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co header insert ((".$q."))"); }

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
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co lpf insert ((".$q."))"); }


		for($i = 0; $i < sizeof($this->contentDatas); $i++) {

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
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co header insert ((".$q."))"); }

			$q = "
				INSERT INTO edxl_co_photos (
					co_id,
					p_uuid,
					mimeType,
					uri,
					contentData,
					image_id,
					sha1 )
				VALUES (
					'".mysql_real_escape_string($this->image_co_ids[$i])."',
					".$this->sql_p_uuid.",
					'".mysql_real_escape_string($this->mimeTypes[$i])."',
					'".mysql_real_escape_string($this->uris[$i])."',
					'".mysql_real_escape_string($this->contentDatas[$i])."',
					'".mysql_real_escape_string($this->image_ids[$i])."',
					'".mysql_real_escape_string($this->image_sha1[$i])."' );
			";
			$result = $this->db->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl co photos insert ((".$q."))"); }
		}
	}


/** Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Update / Save Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Update / Save Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


	// save the person (subsequent save = update)
	public function update() {
/*
		$this->sync();
		$this->saveRevisions();

		$q = "
			UPDATE edxl_de_header (
			SET
				de_id         = ".$this->sql_de_id.",
				when_sent     = ".$this->sql_when_sent.",
				sender_id     = ".$this->sql_sender_id.",
				distr_id      = ".$this->sql_distr_id.",
				distr_status  = ".$this->sql_distr_status.",
				distr_type    = ".$this->sql_distr_type.",
				combined_conf = ".$this->sql_combined_conf.",
				language      = ".$this->sql_language.",
				when_here     = ".$this->sql_when_here.",
				inbound       = ".$this->sql_inbound."
			WHERE de_id = ".$this->sql_de_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personEdxl de header insert ((".$q."))"); }





		$q = "
			UPDATE image_tag
			SET
				image_id = ".$this->sql_image_id.",
				tag_x    = ".$this->sql_tag_x.",
				tag_y    = ".$this->sql_tag_y.",
				tag_w    = ".$this->sql_tag_w.",
				tag_h    = ".$this->sql_tag_h.",
				tag_text = ".$this->sql_tag_text."

			WHERE tag_id = ".$this->sql_tag_id.";
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag update ((".$q."))"); }
*/

	}


	// save any changes since object was loaded as revisions
	function saveRevisions() {

		if($this->image_id != $this->Oimage_id) { $this->saveRevision($this->sql_image_id, $this->sql_Oimage_id, 'image_tag', 'image_id' ); }
		if($this->tag_x    != $this->Otag_x)    { $this->saveRevision($this->sql_tag_x,    $this->sql_Otag_x,    'image_tag', 'tag_x'    ); }
		if($this->tag_y    != $this->Otag_y)    { $this->saveRevision($this->sql_tag_y,    $this->sql_Otag_y,    'image_tag', 'tag_y'    ); }
		if($this->tag_w    != $this->Otag_w)    { $this->saveRevision($this->sql_tag_w,    $this->sql_Otag_w,    'image_tag', 'tag_w'    ); }
		if($this->tag_h    != $this->Otag_h)    { $this->saveRevision($this->sql_tag_h,    $this->sql_Otag_h,    'image_tag', 'tag_h'    ); }
		if($this->tag_text != $this->Otag_text) { $this->saveRevision($this->sql_tag_text, $this->sql_Otag_text, 'image_tag', 'tag_text' ); }
	}


	// save the revision
	function saveRevision($newValue, $oldValue, $table, $column) {

		// note the revision
		$q = "
			INSERT into person_updates (`p_uuid`, `updated_table`, `updated_column`, `old_value`, `new_value`, `updated_by_p_uuid`)
			VALUES (".$this->sql_p_uuid.", '".$table."', '".$column."', ".$oldValue.", ".$newValue.", '".$this->updated_by_p_uuid."');
		";
		$result = $this->db->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $this->db->ErrorMsg(), "personImageTag saveRevision ((".$q."))"); }
	}









}



