<?php
/**
 * @name         MPR Email Service
 * @version      1.6
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


require("class.imageAttachment.php");

class lpfPatient {

	/**
	* todo descriptions
	* @var	string
	* var boolean,array
	*/

	public $uuid;

	public $firstName;
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
		$this->figureOutIncidentIdv12();
		$this->insertImages();

		// insert person
		$q1 = " INSERT INTO person_uuid (p_uuid, full_name, family_name, l10n_name, given_name)
			VALUES ('".$this->uuid."', '".$this->firstName." ".$this->familyName."', '".$this->familyName."', NULL, '".$this->firstName."');";
		$res = $global['db']->Execute($q1);
/*
		// insert person missing info if missing
		if($this->sahanaStatus == "mis") {
			$q2 = " INSERT INTO person_missing (p_uuid, last_seen, last_clothing, comments)
				VALUES ('".$this->uuid."', NULL, NULL, '".$this->comments."');";
			$res = $global['db']->Execute($q2);
		}
*/
		// insert an assignment of this person to the correct incident
		$q3 = " INSERT INTO resource_to_incident (x_uuid, incident_id)
			VALUES ('".$this->uuid."', '".$this->incident_id."');";
		$res = $global['db']->Execute($q3);

		// insert person's status
		$q4 = " INSERT INTO person_status (p_uuid, opt_status, updated, isvictim, updated_server)
			VALUES ('".$this->uuid."', '".$this->sahanaStatus."', '".$this->clientDate."', TRUE, CURRENT_TIMESTAMP);";
		$res = $global['db']->Execute($q4);

		// insert person's details
		$q5 = " INSERT INTO person_details (p_uuid, opt_age_group, opt_gender, years_old, minAge, maxAge)
			VALUES ('".$this->uuid."', NULL, '".$this->gender."', ".$this->age.", ".$this->minAge.", ".$this->maxAge.");";
		$res = $global['db']->Execute($q5);

		// insert into mpres_log
		$q7 = " INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);

		// insert into mpres_log
		$q8 = " INSERT INTO person_to_hospital (hospital_uuid, p_uuid)
			VALUES ('".$this->hospitalId."', '".$this->uuid."');";
		$res = $global['db']->Execute($q8);

/*
		echo "\n---------------------------------------------------------------------\n";
		echo $q1."\n\n".$q3."\n\n".$q4."\n\n".$q5."\n\n".$q7;
		echo "\n---------------------------------------------------------------------\n";
*/
	}


	public function insertPersonXMLv16() {
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

		// insert into mpres_log
		$q7 = " INSERT INTO mpres_log (p_uuid, email_subject, email_from, email_date, update_time)
			VALUES ('".$this->uuid."','".$this->emailSubject."','".$this->emailFrom."','".$this->emailDate."',NOW());";
		$res = $global['db']->Execute($q7);
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

	public function figureOutIncidentIdv12() {
		global $global;
		if($this->longName == "Unnamed TEST or DEMO") {
			$this->incident_id = 1;
		} else if($this->longName == "CMAX 2009 - DRILL") {
			$this->incident_id = 2;
		} else if($this->longName == "CMAX 2010 - DRILL") {
			$this->incident_id = 3;
		}
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
			if(preg_match($needle[$i], $s)>0) {
				$this->sahanaStatus = $status[$i];
			}
		}
		if($this->sahanaStatus == "") {
			$this->sahanaStatus = "unk";
		}
	}



	// end class
}

