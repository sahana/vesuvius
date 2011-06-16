<?php
/**
 * @name         MPR Email Service
 * @version      1.8
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0404
 */

global $global;
require("class.imageAttachment.php");
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');

class lpfPatient {

	/**
	* todo descriptions
	* @var	string
	* var boolean,array
	*/

	public $uuid;

	public $givenName;
	public $familyName;
	public $gender;

	// sql strings w/ wrapped quotations
	public $age;
	public $maxAge;
	public $minAge;

	public $comments;
	public $sahanaStatus;
	public $hospitalId;
	public $peds;

	public $images;

	public $incident_id;
	public $shortName;
	public $longName;

	public $emailSubject;
	public $emailDate;
	public $emailFrom;

	public $clientDate;


	/**
	* Constructor:
	*/
	public function	__construct() {
		$this->uuid = shn_create_uuid();
		$this->incident_id = 0; // default
	}



	/**
	* Destructor
	*/
	public function __destruct() {}



	public function insertPersonXML($version) {
		if($version == 1.2) {
			$this->insertPersonXMLv12();
		} else if($version == 1.6) {
			$this->insertPersonXMLv16();
		}
	}



	public function insertPersonXMLv12() {
		global $global;
		$this->figureOutIncidentId();
		$this->insertImages();

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
			INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old, minAge, maxAge)
			VALUES ('".$this->uuid."', NULL, ".$this->gender.", ".$this->age.", ".$this->minAge.", ".$this->maxAge.");
		";
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = "
			INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());
		";
		$res = $global['db']->Execute($q7);
	}



	public function insertPersonXMLv16() {
		global $global;
		$this->figureOutIncidentId();
		$this->insertImages();

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
			INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old, last_seen, last_clothing, other_comments)
			VALUES ('".$this->uuid."', NULL, ".$this->gender.", '".$this->age."', NULL, NULL, '".$this->comments."');
		";
		$res = $global['db']->Execute($q5);


		// insert into mpres_log
		$q7 = "
			INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());
		";
		$res = $global['db']->Execute($q7);
	}



	public function insertPerson() {
		global $global;

		$this->extractStatusFromSubject();

		$name = new nameParser($this->emailSubject);
		$this->givenName  = $name->getFirstName();
		$this->familyName = $name->getLastName();


		$this->insertImages();

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
			INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old, last_seen, last_clothing, other_comments)
			VALUES ('".$this->uuid."', NULL, NULL, NULL, NULL, NULL, NULL);
		";
		$res = $global['db']->Execute($q6);


		// insert person who reported link to root cuz we dont really know who reported them
		$q7 = "
			INSERT INTO person_to_report (p_uuid, rep_uuid)
			VALUES ('".$this->uuid."', '1');
		";
		$res = $global['db']->Execute($q7);
	}



	public function insertImages() {
		global $global;
		// insert a person's images
		for ($i=0; $i < sizeof($this->images); $i++) {
			$q = "
				INSERT INTO image (p_uuid, image_type, image_height, image_width, created, category, url, url_thumb, original_filename)
				VALUES ('".$this->uuid."', '".$this->images[$i]->type."', '".$this->images[$i]->height."', '".$this->images[$i]->width."', CURRENT_TIMESTAMP, ".
				"'person', '".$this->images[$i]->url."', '".$this->images[$i]->url_thumb."', '".$this->images[$i]->original_filename."');
			";
			$res = $global['db']->Execute($q);
		}
	}



	public function figureOutIncidentId() {
		global $global;
		$q  = "
			SELECT *
			FROM incident WHERE shortname = '".$this->shortName."';
		";
		$result = $global['db']->Execute($q);
		if($row = $result->FetchRow()) {
			$this->incident_id = $row['incident_id'];

		// if we can't figure out what incident it is, default to the test incident (#1)
		} else {
			$this->incident_id = 1;
		}
	}


	public function extractStatusFromSubject() {
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

		$this->sahanaStatus = "";
		for ($i=0; $i < count($needle); $i++) {
			if(preg_match($needle[$i], $s) > 0) {
				$this->sahanaStatus = $status[$i];
				// remove the status from the email subject
				$this->emailSubject = preg_replace($needle[$i], " ", $this->emailSubject);
			}
		}
		if($this->sahanaStatus == "") {
			$this->sahanaStatus = "unk";
		}
	}



	// end class
}

