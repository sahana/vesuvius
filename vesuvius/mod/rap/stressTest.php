<?php
/**
 * @name         Report a Person
 * @version      1.2
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0325
 */

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

require("../../conf/sahana.conf");
require("../../3rd/adodb/adodb.inc.php");
require("../../inc/handler_db.inc");
require("../../inc/lib_uuid.inc");
require("../../inc/lib_image.inc");


for($i = 0; $i < 10000000; $i++) {
	go();
}



function go() {
	global $global;

	$status      = "'unk'";
	$given_name  = "'unknown'";
	$family_name = "'unknown'";
	$gender      = "'unk'";
	$age         = "'0'";
	$minAge      = "'0'";
	$maxAge      = "'150'";
	$religion    = "'UNK'";
	$race        = "'U'";
	$address     = "'unknown'";
	$zip         = "'unknown'";
	$phone       = "'unknown'";
	$mobile      = "'unknown'";
	$email       = "'unknown'";
	$eye         = "'UNK'";
	$skin        = "'UNK'";
	$hair        = "'UNK'";
	$height      = "'unknown'";
	$weight      = "'unknown'";
	$physical    = "'unknown'";
	$seen        = "'unknown'";
	$clothing    = "'unknown'";
	$comments    = "'unknown'";

	$q0  = "
		SELECT *
		FROM incident
		WHERE shortname = 'stress';
	";
	$r0  = $global['db']->Execute($q0);
	$row = $r0->FetchRow();
	$id = $row['incident_id'];

	$uuid = shn_create_uuid();

	// insert person
	$q1 = "
		INSERT INTO person_uuid (p_uuid, full_name, family_name, given_name, incident_id, hospital_uuid)
		VALUES (
			'".$uuid."',
			'".mysql_real_escape_string($given_name)." ".mysql_real_escape_string($family_name)."',
			'".mysql_real_escape_string($family_name)."',
			'".mysql_real_escape_string($given_name)."',
			'".$id."',
			'-1'
		);
	";
	$res = $global['db']->Execute($q1);


	// insert person's missing information if missing
	if($status == "'mis'") {
		$q2 = "
			INSERT INTO person_missing (p_uuid, last_seen, last_clothing, comments)
			VALUES ('".$uuid."', ".$seen.", ".$clothing.", ".$comments.");
		";
		$res = $global['db']->Execute($q2);
	}

	// insert person's status
	$q5 = "
		INSERT INTO person_status (p_uuid, opt_status, last_updated, isvictim, creation_time)
		VALUES ( '".$uuid."', ".$status.", CURRENT_TIMESTAMP, TRUE, CURRENT_TIMESTAMP);
	";
	$res = $global['db']->Execute($q5);


	// insert into rap_log
	$q7 = "
		INSERT INTO rap_log (p_uuid)
		VALUES ('".$uuid."');
	";
	$res = $global['db']->Execute($q7);


	// insert person's details
	$q8 = "
		INSERT INTO person_details (p_uuid, opt_race, opt_religion, opt_gender, years_old, minAge, maxAge)
		VALUES ('".$uuid."', ".$race.", ".$religion.", ".$gender.", ".$age.", ".$minAge.", ".$maxAge.");
	";
	$res = $global['db']->Execute($q8);


	// insert person to report !! ROOT
	$q11 = "
		INSERT INTO person_to_report (p_uuid, rep_uuid)
		VALUES ('".$uuid."','1');
	";
	$res = $global['db']->Execute($q11);


	// insert personal physical
	$q11 = "
		INSERT INTO person_physical (p_uuid, height, weight, opt_eye_color, opt_skin_color, opt_hair_color, comments)
		VALUES ('".$uuid."', ".$height.", ".$weight.", ".$eye.", ".$skin.", ".$hair.", ".$physical.");";
	$res = $global['db']->Execute($q11);


	// insert phone
	$q13 = "
		INSERT INTO contact (pgoc_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'curr', ".$phone.");";
	$res = $global['db']->Execute($q13);


	// insert phone mobile
	$q14 = "
		INSERT INTO contact (pgoc_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'cmob', ".$mobile.");";
	$res = $global['db']->Execute($q14);


	// insert address
	$q15 = "
		INSERT INTO contact (pgoc_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'home', ".$address.");";
	$res = $global['db']->Execute($q15);


	// insert zip
	$q16 = "
		INSERT INTO contact (pgoc_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'zip', ".$zip.");";
	$res = $global['db']->Execute($q16);


	// insert email
	$q17 = "
		INSERT INTO contact (pgoc_uuid, opt_contact_type, contact_value)
		VALUES ('".$uuid."', 'email', ".$phone.");";
	$res = $global['db']->Execute($q17);


	// insert image
	$q18 = "
		INSERT INTO image (x_uuid, image_type, image_height, image_width, url, url_thumb, crop_x, crop_y, crop_w, crop_h, full_path)
		VALUES ('".$uuid."', 'jpg', '0', '0', 'url', 'url', '0', '0', '0', '0', 'path');
	";
	$res = $global['db']->Execute($q18);
}





