<?php
/**
 * Module >> Edit a Person :: Main Controller
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module
 * @subpackage eap
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


include_once($global['approot']."/inc/lib_uuid.inc");
include_once($global['approot']."/inc/lib_location.inc");
$revisionQ = array();


/**
 * Begin following a person.....
 *
 * @access public
 * @return void
 */
function shn_eap_follow() {
	global $global;
	shn_eap_findRights();

	$q0  = "
		SELECT COUNT(*)
		FROM person_followers
		WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
		AND p_uuid = '".$global['uuid']."';
	";
	$r0  = $global['db']->Execute($q0);
	$row0 = $r0->FetchRow();
	$alreadyFollowing = (bool)$row0['COUNT(*)']; // true if logged in user is already following the person

	if($global['startFollow']) {
		add_confirmation("You successfully began following this person.");
		if(!$alreadyFollowing) {
			$q = "INSERT INTO person_followers (p_uuid, follower_p_uuid) VALUES ('".$global['uuid']."','".$_SESSION['user_p_uuid']."');";
			$r = $global['db']->Execute($q);
		}
	} else {
		add_error("You are not allowed to follow this person... you must first login.");
	}
	shn_eap_edit();
}



/**
 * Stop following a person.....
 *
 * @access public
 * @return void
 */
function shn_eap_unFollow() {
	global $global;
	shn_eap_findRights();

	if($global['startFollow']) {
		add_confirmation("You are no longer following this person.");
		$q = "
			DELETE FROM person_followers
			WHERE `p_uuid` = '".$global['uuid']."'
			AND `follower_p_uuid` = '".$_SESSION['user_p_uuid']."';";
		$r = $global['db']->Execute($q);

	} else {
		add_error("You are not allowed to unfollow this person.");
	}
	shn_eap_edit();
}




/**
 * Adds a note to a person.....
 *
 * @access public
 * @return void
 */
function shn_eap_addNote() {
	global $global;
	shn_eap_findRights();

	if($global['addNote']) {
		$note = trim($_POST['addNote']);
		if(strlen($note)>1000) {
			$note = substr($note, 0, 999);
		}
		$note = trim(strip_tags($note));
		$note = mysql_real_escape_string($note);

		if(strlen($note) > 0) {
			$q  = "
				INSERT INTO person_notes (note_about_p_uuid, note_written_by_p_uuid, note)
				VALUES ('".$global['uuid']."', '".$_SESSION['user_p_uuid']."', '".$note."');
			";
			$r  = $global['db']->Execute($q);
			$row = $r->FetchRow();
			add_confirmation("Your note has been added.");
		} else {
			add_warning("Your note was not added because it was blank.");
		}
	} else {
		add_warning("You cannot add notes without being logged in, please login first.");
	}
	shn_eap_edit();
}




/**
 * Deletes a note from a person.....
 *
 * @access public
 * @return void
 */
function shn_eap_deleteNote() {
	global $global;
	shn_eap_findRights();

	if($global['privateEdit']) {
		$id = mysql_real_escape_string($_GET['noteId']);
		$q  = "
			DELETE FROM person_notes
			WHERE note_id = '".$id."'
			AND note_about_p_uuid = '".$global['uuid']."';
		";
		$r  = $global['db']->Execute($q);
		$row = $r->FetchRow();
		add_confirmation("Note <b>#".$id."</b> has been deleted.");
	} else {
		add_warning("You do not have permission to delete notes.");
	}
	shn_eap_edit();
}



/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_eap_mainmenu() {
	global $global;
	$module = $global['module'];
	include $global['approot']."/inc/handler_mainmenu.inc";
	// no menu... this module is only one page :)
}



/**
 * Make the url to the current page
 */
function makePageUrl() {
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	return $link;
}



/**
 * Make the base url of the links we use
 */
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



/**
 * findRights
 *
 * @access public
 * @return void
 */
function shn_eap_findRights() {
	global $global;

	$global['uuid'] = base64_decode($_GET['uuid']);

	// anonymous user ~ not logged in
	if(($_SESSION['logged_in'] != 1) || ($_SESSION['user'] == 'Anonymous')) {
		$global['publicView']  = true;
		$global['publicEdit']  = false;
		$global['privateView'] = false;
		$global['privateEdit'] = false;
		$global['addNote']     = false;
		$global['startFollow'] = false;
		$global['role']        = "anonymous";

	} else {
		$q  = "
			SELECT COUNT(*)
			FROM users u
			LEFT JOIN person_to_report r ON u.p_uuid = r.rep_uuid
			WHERE u.user_id = '".$_SESSION['user_id']."'
			AND r.p_uuid = '".$global['uuid']."';
		";
		$r  = $global['db']->Execute($q);
		$row = $r->FetchRow();
		$global['isReporter'] = (bool)$row['COUNT(*)'];

		// reporter ~ logged in
		if($global['isReporter']) {
			$global['publicView']  = true;
			$global['publicEdit']  = true;
			$global['privateView'] = true;
			$global['privateEdit'] = true;
			$global['addNote']     = true;
			$global['startFollow'] = false;
			$global['role']        = "reporter";

		// registered user ~ logged in
		} else if(($_SESSION['group_name'] == "Registered User") && ($_SESSION['logged_in'] == 1)) {
			$global['publicView']  = true;
			$global['publicEdit']  = false;
			$global['privateView'] = false;
			$global['privateEdit'] = false;
			$global['addNote']     = true;
			$global['startFollow'] = true;
			$global['role']        = "registered";

		// Hospital Staff / Hospital Staff Admin ~ logged in
		} else if(($_SESSION['group_id'] == "5" || $_SESSION['group_id'] == "6") && ($_SESSION['logged_in'] == 1)) {
			$global['publicView']  = true;
			$global['publicEdit']  = true;
			$global['privateView'] = true;
			$global['privateEdit'] = true;
			$global['addNote']     = true;
			$global['startFollow'] = true;
			$global['role']        = "staff";

		// Admin ~ logged in
		} else if(($_SESSION['group_id'] == "1") && ($_SESSION['logged_in'] == 1)) {
			$global['publicView']  = true;
			$global['publicEdit']  = true;
			$global['privateView'] = true;
			$global['privateEdit'] = true;
			$global['addNote']     = true;
			$global['startFollow'] = true;
			$global['role']        = "admin";
		}

		// hack to turn off notes on ChrustChurch and Columbia
		if(($_GET['shortname'] == "christchurch") || ($_GET['shortname'] == "columbia2011")) {
			$global['addNote'] = false;
		}
	}
}



/**
 * addEmailUpdates ~ Queues all updates
 *
 * @access public
 * @return void
 */
function addEmailUpdates($table, $column, $name, $oldValue, $newValue) {
	global $revisionQ;
	$revisionQ[] = "The value for ".$name." has changed from <b>".$oldValue."</b> to <b>".$newValue."</b>";
}



/**
 * emailUpdates
 *
 * @access public
 * @return void
 */
function emailUpdates() {
	global $global;
	global $revisionQ;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	// only email if revisions...
	if(count($revisionQ) > 0) {

		$p = new pop();
		$subject  = "People Locator update for ".$global['full_name'];
		$bodyHTML = "
			Changes have been made to the Person Record of <b>".$global['full_name']."</b>.<br>
			<br>
		";
		$bodyAlt = "
			A change was made to the Person Record of ".$global['full_name'].".\n
			\n
		";

		$i = 0;
		while($i < count($revisionQ)) {
			$bodyHTML .= $revisionQ[$i]."<br>";

			// remove bold chars for alt email body
			$revisionQ[$i] = str_replace("<b>", "", $revisionQ[$i]);
			$revisionQ[$i] = str_replace("</b>", "", $revisionQ[$i]);

			$bodyAlt .= $revisionQ[$i]."\n";
			$i++;
		}

		$bodyHTML .= "
			<br>
			<br>
			You can view the full record for this person here: <a href=\"".$global['googl']."\">".$global['googl']."</a><br>
			<br>
			<br>
			<br>
			<i>If you would like to unsubscribe from these email alerts, click the button to un-follow this person from the above mentioned link.</i><br>
			<br>
			<br>
		";
		$bodyAlt .= "
			\n
			\n
			You can view the full record for this person here: ".$global['googl']."\n
			\n
			\n
			\n
			If you would like to unsubscribe from these email alerts, click the button to un-follow this person from the above mentioned link.\n
			\n
			\n
		";

		// email followers......
		$q = "
			SELECT *
			FROM person_followers f, person_uuid p, contact c
			WHERE f.p_uuid = '".$global['uuid']."'
			AND p.p_uuid = f.follower_p_uuid
			AND c.pgoc_uuid = f.follower_p_uuid
			AND c.opt_contact_type = 'email';
		";

		$r = $global['db']->Execute($q);
		while($row = $r->FetchRow()) {
			$p->sendMessage($row['contact_value'], $row['full_name'], $subject, $bodyHTML, $bodyAlt);
		}

		// email reporter........
		$q = "
			SELECT *
			FROM person_to_report p, contact c, person_uuid pp
			WHERE p.p_uuid = '".$global['uuid']."'
			AND p.rep_uuid = c.pgoc_uuid
			AND c.opt_contact_type = 'email'
			AND pp.p_uuid = p.rep_uuid;
		";
		$r = $global['db']->Execute($q);
		while($row = $r->FetchRow()) {
			$p->sendMessage($row['contact_value'], $row['full_name'], $subject, $bodyHTML, $bodyAlt);
		}
	}
}



/**
 * saveRevision
 *
 * @access public
 * @return void
 */
function saveRevision($table, $column, $name, $oldValue, $newValue) {
	global $global;

	// save the revision
	$q = "
		UPDATE ".$table."
		SET ".$column." = '".mysql_real_escape_string($newValue)."'
		WHERE p_uuid    = '".$global['uuid']."';
	";
	$r = $global['db']->Execute($q);

	// note the revision
	$q = "
		INSERT into person_updates (`p_uuid`, `updated_table`, `updated_column`, `old_value`, `new_value`, `updated_by_p_uuid`)
		VALUES ('".$global['uuid']."', '".$table."', '".$column."', '".mysql_real_escape_string($oldValue)."', '".mysql_real_escape_string($newValue)."', '".$_SESSION['user_p_uuid']."');
	";
	$r = $global['db']->Execute($q);

	// update timestamp
	$q = "
		UPDATE person_status
		SET updated = CURRENT_TIMESTAMP
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r = $global['db']->Execute($q);

	add_confirmation("Updated ".$name." from \"".$oldValue."\" to \"".$newValue."\"");

	addEmailUpdates($table, $column, $name, $oldValue, $newValue);
}



/**
 * saveContactRevision
 *
 * @access public
 * @return void
 */
function saveContactRevision($type, $name, $oldValue, $newValue) {
	global $global;

	// we delete and then insert here because sometimes the contact value is not yet set, so an update would fail~!

	// delete the old value
	$q = "
		DELETE FROM contact
		WHERE pgoc_uuid = '".$global['uuid']."'
		AND opt_contact_type = '".$type."';
	";
	$r = $global['db']->Execute($q);


	// insert the new value
	$q = "
		INSERT INTO contact (`pgoc_uuid`, `opt_contact_type`, `contact_value`)
		VALUE ('".$global['uuid']."', '".$type."', '".mysql_real_escape_string($newValue)."');
	";
	$r = $global['db']->Execute($q);


	// note the revision
	$q = "
		INSERT INTO person_updates (`p_uuid`, `updated_table`, `updated_column`, `old_value`, `new_value`, `updated_by_p_uuid`)
		VALUES ('".$global['uuid']."', 'contact', 'contact_value', '".$type."<::>".$oldValue."', '".$type."<::>".$newValue."', '".$_SESSION['user_p_uuid']."');
	";
	$r = $global['db']->Execute($q);

	// update timestamp
	$q = "
		UPDATE person_status
		SET updated = CURRENT_TIMESTAMP
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r = $global['db']->Execute($q);

	add_confirmation("Updated ".$name." from \"".$oldValue."\" to \"".$newValue."\"");

	addEmailUpdates("contact", $type, $name, $oldValue, $newValue);
}



/**
 * saveHospitalRevision
 *
 * @access public
 * @return void
 */
function saveHospitalRevision($name, $oldValue, $newValue) {
	global $global;

	// we delete and then insert here because sometimes the contact value is not yet set, so an update would fail~!

	// delete the old value
	$q = "
		DELETE FROM person_to_hospital
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r = $global['db']->Execute($q);


	// insert the new value
	$q = "
		INSERT INTO person_to_hospital (`p_uuid`, `hospital_uuid`)
		VALUE ('".$global['uuid']."', '".mysql_real_escape_string($newValue)."');
	";
	$r = $global['db']->Execute($q);


	// note the revision
	$q = "
		INSERT INTO person_updates (`p_uuid`, `updated_table`, `updated_column`, `old_value`, `new_value`, `updated_by_p_uuid`)
		VALUES ('".$global['uuid']."', 'person_to_hospital', 'hospital_uuid', '".$oldValue."', '".$newValue."', '".$_SESSION['user_p_uuid']."');
	";
	$r = $global['db']->Execute($q);

	// update timestamp
	$q = "
		UPDATE person_status
		SET updated = CURRENT_TIMESTAMP
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r = $global['db']->Execute($q);

	add_confirmation("Updated ".$name." from \"".$oldValue."\" to \"".$newValue."\"");

	addEmailUpdates("person_to_hospital", "hospital_uuid", $name, $oldValue, $newValue);
}



/**
 * updateFullName ~ full_name is derived, so we update it when given or family names are updated
 *
 * @access public
 * @return void
 */
function updateFullName($editGivenName, $editFamilyName) {
	global $global;

	$q = "
		UPDATE person_uuid
		SET full_name = '".mysql_real_escape_string($editGivenName)." ".mysql_real_escape_string($editFamilyName)."'
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r = $global['db']->Execute($q);
	add_warning("
		Since you changed the person's name, the record will not reflect this until you revisit this page or
		<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($global['uuid'])."\">click here.</a>");
}



/**
 * Main Controller function
 *
 * @access public
 * @return void
 */
function shn_eap_edit() {
	global $global;
	global $shn_tabindex;

	shn_eap_findRights();
	$googl = new goo_gl(makePageUrl());
	$global['googl'] = $googl->result();

	$debug = false;
	$debugParam = "";
	if(isset($_GET['debug'])) {
		$debug = true;
		$debugParam = "&debug";
	}

	// HEADER ////////////////////////////////////////////////////////////////////////////////////
	$q  = "
		SELECT *
		FROM person_uuid
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r        = $global['db']->Execute($q);
	$row      = $r->FetchRow();
	$full_name = $row['full_name'];
	$global['full_name'] = $full_name;
	$person_uuid = $row;

	$q  = "
		SELECT *
		FROM person_details
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r        = $global['db']->Execute($q);
	$person_details = $r->FetchRow();

	echo "<h2>".$full_name." :: ".$global['uuid']."</h2>";
	// HEADER END ////////////////////////////////////////////////////////////////////////////////


	// IMAGES ////////////////////////////////////////////////////////////////////////////////////
	$boy     = "res/img/s0boy.png";
	$girl    = "res/img/s1girl.png";
	$man     = "res/img/s2man.png";
	$woman   = "res/img/s3woman.png";
	$unknown = "res/img/s4unknown.png";

	// figure out if the person has any images ...

	$q  = "
		SELECT COUNT(*)
		FROM image
		WHERE x_uuid = '".$global['uuid']."';
	";
	$r   = $global['db']->Execute($q);
	$row = $r->FetchRow();
	$num = $row['COUNT(*)'];

	// we has images
	if($num > 0) {
		$q  = "
			SELECT *
			FROM image
			WHERE x_uuid = '".$global['uuid']."'
			LIMIT 1;
		";
		$r        = $global['db']->Execute($q);
		$row      = $r->FetchRow();
		$imageUrl = $row['url'];
		$thumbUrl = $row['url_thumb'];

	// we doesnt has images
	} else {
		$sex = $person_details['opt_gender'];
		$old = $person_details['years_old'];
		$min = $person_details['minAge'];
		$max = $person_details['maxAge'];

		if(($sex != "mal") && ($sex != "fml")) {
			$imageUrl = $unknown;
			$thumbUrl = $unknown;
		} else if($sex == "mal") {
			if($old != null) {
				if($old > 17) {
					$imageUrl = $man;
					$thumbUrl = $man;
				} else {
					$imageUrl = $boy;
					$thumbUrl = $boy;
				}
			} else if($min != null) {
				if($min > 17) {
					$imageUrl = $man;
					$thumbUrl = $man;
				} else {
					$imageUrl = $boy;
					$thumbUrl = $boy;
				}
			} else {
				$imageUrl = $man;
				$thumbUrl = $man;
			}
		} else if($sex == "fml") {
			if($old != null) {
				if($old > 17) {
					$imageUrl = $woman;
					$thumbUrl = $woman;
				} else {
					$imageUrl = $girl;
					$thumbUrl = $girl;
				}
			} else if($min != null) {
				if($min > 17) {
					$imageUrl = $woman;
					$thumbUrl = $woman;
				} else {
					$imageUrl = $girl;
					$thumbUrl = $girl;
				}
			} else {
				$imageUrl = $man;
				$thumbUrl = $man;
			}
		} else {
			$imageUrl = $unknown;
			$thumbUrl = $unknown;
		}
	}
	$global['full_thumb_url'] = makeBaseUrl().$thumbUrl;

	echo "
		<div class=\"form-container\">
			<form>
				<fieldset id=\"editImages\">
					<legend>Images</legend>
					<a href=\"".$imageUrl."\" target=\"_blank\">
						<div style=\"background-color: #fff; padding: 5px; border: 1px solid #777; float: left; text-align: center;\">
							<img height=\"150\" src=\"".$thumbUrl."\">
							<div style=\"clear:both;\"></div>
							zoom
						</div>
					</a>
				</fieldset>
			</form>
		</div>
	";
	// IMAGES END /////////////////////////////////////////////////////////////////////////////////////


	// LOAD PUBLIC DATA ///////////////////////////////////////////////////////////////////////////////

	// load physical
	$q  = "
		SELECT *
		FROM person_physical
		WHERE p_uuid = '".$global['uuid']."';
	";
	$r               = $global['db']->Execute($q);
	$person_physical = $r->FetchRow();

	// load status
	$q  = "
		SELECT *
		FROM person_status s, field_options f
		WHERE s.p_uuid = '".$global['uuid']."'
		AND f.field_name = 'opt_status'
		AND s.opt_status = f.option_code;
	";
	$r              = $global['db']->Execute($q);
	$person_status  = $r->FetchRow();

	// we use updated time of the new updated_server time is not available
	if($person_status['updated_server'] == null) {
		$person_status['updated_server'] = $person_status['updated'];
	}

	// load missing data (if person is missing)
	if(isset($status['opt_status']) && $status['opt_status'] == "mis") {
		$missing = true;
		$q  = "
			SELECT *
			FROM person_missing
			WHERE p_uuid = '".$global['uuid']."';
		";
		$r               = $global['db']->Execute($q);
		$person_missing  = $r->FetchRow();
	} else {
		$missing = false;
	}

	// load hospital data
	$q  = "
		SELECT *
		FROM person_to_hospital p, hospital h
		WHERE p.hospital_uuid = h.hospital_uuid
		AND p.p_uuid = '".$global['uuid']."';
	";
	$r        = $global['db']->Execute($q);
	$hospital = $r->FetchRow();

	// set opt values to UNK if thats teh case
	$person_details['opt_gender']      == null ? $gender = "UNK" : $gender = $person_details['opt_gender'];
	$person_physical['opt_eye_color']  == null ? $eye    = "UNK" : $eye    = $person_physical['opt_eye_color'];
	$person_physical['opt_skin_color'] == null ? $skin   = "UNK" : $skin   = $person_physical['opt_skin_color'];
	$person_physical['opt_hair_color'] == null ? $hair   = "UNK" : $hair   = $person_physical['opt_hair_color'];

	// map field_options to real values
	// map gender
	$q  = "
		SELECT *
		FROM field_options
		WHERE option_code = '".$gender."'
		AND field_name = 'opt_gender';
	";
	$r   = $global['db']->Execute($q);
	$row = $r->FetchRow();
	$gender = $row['option_description'];

	// map eyes
	$q  = "
		SELECT *
		FROM field_options
		WHERE option_code = '".$eye."'
		AND field_name = 'opt_eye_color';
	";
	$r   = $global['db']->Execute($q);
	$row = $r->FetchRow();
	$eye = $row['option_description'];

	// map skin color
	$q  = "
		SELECT *
		FROM field_options
		WHERE option_code = '".$skin."'
		AND field_name = 'opt_skin_color';
	";
	$r   = $global['db']->Execute($q);
	$row = $r->FetchRow();
	$skin = $row['option_description'];

	// map hair color
	$q  = "
		SELECT *
		FROM field_options
		WHERE option_code = '".$hair."'
		AND field_name = 'opt_hair_color';
	";
	$r   = $global['db']->Execute($q);
	$row = $r->FetchRow();
	$hair = $row['option_description'];

	// hospital information
	$q = "
		SELECT *
		FROM person_to_hospital p, hospital h
		WHERE p.p_uuid = '".$global['uuid']."'
		AND h.hospital_uuid = p.hospital_uuid;
	";
	$r   = $global['db']->Execute($q);
	if($person_to_hospital = $r->FetchRow()) {
		// ok, good ;)
	} else {
		// person must not be at hospital or not assigned to one yet
		$person_to_hospital = array();
		$person_to_hospital['hospital_uuid'] = -1; // teh null hospital :)
		$person_to_hospital['name']          = "SELECT";
	}
	// LOAD PUBLIC DATA END ///////////////////////////////////////////////////////////////////////////


	// PUBLIC EDIT ////////////////////////////////////////////////////////////////////////////////////
	if($global['publicEdit']) {

		if((count($_POST) > 0) && isset($_POST['given_name'])) {
			$editGivenName  = trim($_POST['given_name']);
			$editFamilyName = trim($_POST['family_name']);
			$editAge        = trim($_POST['age']);
			$editMinAge     = trim($_POST['age_lower']);
			$editMaxAge     = trim($_POST['age_upper']);
			$editGender     = trim($_POST['opt_gender']);
			$editEye        = trim($_POST['opt_eye_color']);
			$editSkin       = trim($_POST['opt_skin_color']);
			$editHair       = trim($_POST['opt_hair_color']);
			$editHeight     = trim($_POST['height']);
			$editWeight     = trim($_POST['weight']);
			$editComments   = trim($_POST['comments']);
			$editStatus     = trim($_POST['opt_status']);
			$editHospital   = trim($_POST['hospital']);

			// check for revisions and save dem
			if($editGivenName  !== $person_uuid['given_name'])  {
				saveRevision("person_uuid", "given_name", "First Name", $person_uuid['given_name'],  $editGivenName);
				updateFullName($editGivenName, $editFamilyName);
			}
			if($editFamilyName !== $person_uuid['family_name']) {
				saveRevision("person_uuid", "family_name", "Last Name", $person_uuid['family_name'], $editFamilyName);
				updateFullName($editGivenName, $editFamilyName);
			}

			if($editAge        !== $person_details['years_old'])         { saveRevision("person_details",     "years_old",      "Age",         $person_details['years_old'],         $editAge);      }
			if($editMinAge     !== $person_details['minAge'])            { saveRevision("person_details",     "minAge",         "Minimum Age", $person_details['minAge'],            $editMinAge);   }
			if($editMaxAge     !== $person_details['maxAge'])            { saveRevision("person_details",     "maxAge",         "Maximum Age", $person_details['maxAge'],            $editMaxAge);   }
			if($editGender     !== $person_details['opt_gender'])        { saveRevision("person_details",     "opt_gender",     "Gender",      $person_details['opt_gender'],        $editGender);   }
			if($editEye        !== $person_physical['opt_eye_color'])    { saveRevision("person_physical",    "opt_eye_color",  "Eye Color",   $person_physical['opt_eye_color'],    $editEye);      }
			if($editSkin       !== $person_physical['opt_skin_color'])   { saveRevision("person_physical",    "opt_skin_color", "Skin Color",  $person_physical['opt_skin_color'],   $editSkin);     }
			if($editHair       !== $person_physical['opt_hair_color'])   { saveRevision("person_physical",    "opt_hair_color", "Hair Color",  $person_physical['opt_hair_color'],   $editHair);     }
			if($editHeight     !== $person_physical['height'])           { saveRevision("person_physical",    "height",         "Height",      $person_physical['height'],           $editHeight);   }
			if($editWeight     !== $person_physical['weight'])           { saveRevision("person_physical",    "weight",         "Weight",      $person_physical['weight'],           $editWeight);   }
			if($editComments   !== $person_physical['comments'])         { saveRevision("person_physical",    "comments",       "Comments",    $person_physical['comments'],         $editComments); }
			if($editStatus     !== $person_status['opt_status'])         { saveRevision("person_status",      "opt_status",     "Status",      $person_status['opt_status'],         $editStatus);   }

			if($editHospital   !== $person_to_hospital['hospital_uuid']) { saveHospitalRevision("Hospital", $person_to_hospital['hospital_uuid'], $editHospital); }

			// reload status since changes made......
			$q  = "
				SELECT *
				FROM person_status s, field_options f
				WHERE s.p_uuid = '".$global['uuid']."'
				AND f.field_name = 'opt_status'
				AND s.opt_status = f.option_code;
			";
			$r              = $global['db']->Execute($q);
			$person_status  = $r->FetchRow();

			// we use updated time of the new updated_server time is not available
			if($person_status['updated_server'] == null) {
				$person_status['updated_server'] = $person_status['updated'];
			}

		} else {
			$editGivenName  = $person_uuid['given_name'];
			$editFamilyName = $person_uuid['family_name'];
			$editAge        = $person_details['years_old'];
			$editMinAge     = $person_details['minAge'];
			$editMaxAge     = $person_details['maxAge'];
			$editGender     = $person_details['opt_gender'];
			$editEye        = $person_physical['opt_eye_color'];
			$editSkin       = $person_physical['opt_skin_color'];
			$editHair       = $person_physical['opt_hair_color'];
			$editHeight     = $person_physical['height'];
			$editWeight     = $person_physical['weight'];
			$editComments   = $person_physical['comments'];
			$editStatus     = $person_status['opt_status'];
			$editHospital   = $person_to_hospital['hospital_uuid'];
		}

		echo "
			<div class=\"form-container\">
			<form method=\"post\" id=\"editPublic\" name=\"editPublic\" action=\"index.php?mod=eap&act=edit".$debugParam."&uuid=".base64_encode($global['uuid'])."\">
			<fieldset id=\"editPublic\">
			<legend><span class=\"publicText\">View / Edit Public Information</span></legend>

			<label for=\"opt_status\"><b>Record Created</b> </label>
			<input type=\"text\" name=\"opt_status\" id=\"opt_status\" value=\"".$person_status['updated_server']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"opt_status\"><b>Last Updated</b> </label>
			<input type=\"text\" name=\"opt_status\" id=\"opt_status\" value=\"".$person_status['updated']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>
			<br>
		";


		// generate status dropdown
		$q = "
			SELECT *
			FROM field_options
			WHERE field_name = 'opt_status';
		";
		$r = $global['db']->Execute($q);
		$opt_status_array = array();
		while(!$r->EOF) {
			$opt_status_array[$r->fields['option_code']] = $r->fields['option_description'];
			$r->MoveNext();
		}
		shn_form_select($opt_status_array, "<b>Health / Locational Status</b>", "opt_status", "onchange=\"\"", array('value'=>$editStatus));


		// generate hospital dropdown
		$q = "
			SELECT *
			FROM hospital;
		";
		$r = $global['db']->Execute($q);
		$hospital_array = array();
		while(!$r->EOF) {
			$hospital_array[$r->fields['hospital_uuid']] = $r->fields['name'];
			$r->MoveNext();
		}
		shn_form_select($hospital_array, "<b>Located at Hospital</b>", "hospital", "onchange=\"\"", array('value'=>$editHospital));


		echo "
			<hr class=\"insideHrGreen\">

			<label for=\"given_name\">First Name </label>
			<input type=\"text\" name=\"given_name\" id=\"given_name\" value=\"".$editGivenName."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>

			<label for=\"given_name\">Last Name </label>
			<input type=\"text\" name=\"family_name\" id=\"family_name\" value=\"".$editFamilyName."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>

			<label for=\"age\">Age</label>
			<input type=\"text\" name=\"age\" id=\"age\" value=\"".$editAge."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>

			<label for=\"age_lower\">Lower Age Range</label>
			<input type=\"text\" name=\"age_lower\" id=\"age_upper\" value=\"".$editMinAge."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>

			<label for=\"age_upper\">Upper Age Range</label>
			<input type=\"text\" name=\"age_upper\" id=\"age_upper\" value=\"".$editMaxAge."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>
		";

		shn_form_opt_select("opt_gender",     "Gender",     null, array('sort'=>'display_order, option_description ASC', 'value'=>$editGender));
		shn_form_opt_select("opt_eye_color",  "Eye Color",  null, array('sort'=>'display_order, option_description ASC', 'value'=>$editEye   ));
		shn_form_opt_select("opt_skin_color", "Skin Color", null, array('sort'=>'display_order, option_description ASC', 'value'=>$editSkin  ));
		shn_form_opt_select("opt_hair_color", "Hair Color", null, array('sort'=>'display_order, option_description ASC', 'value'=>$editHair  ));


		echo "
			<label for=\"height\">Height</label>
			<input type=\"text\" name=\"height\" id=\"height\" value=\"".$editHeight."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>

			<label for=\"height\">Weight</label>
			<input type=\"text\" name=\"weight\" id=\"weight\" value=\"".$editWeight."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"public\">
			<br>

			<label for=\"height\">Distinctive Features</label>
			<textarea name=\"comments\" id=\"comments\" cols=\"43\" rows=\"4\" tabindex=\"".++$shn_tabindex."\" class=\"public\">".$editComments."</textarea>
			<br>
			<br>

			<label for=\"height\">&nbsp;</label>
			<input type=\"submit\" value=\"Save Changes to Public Information\" class=\"styleTehButton\" tabindex=\"".++$shn_tabindex."\">

			</fieldset>
			</form></div>
		";
	// PUBLIC EDIT END ////////////////////////////////////////////////////////////////////////////////


	// PUBLIC VIEW ////////////////////////////////////////////////////////////////////////////////////
	} else {
		echo "
			<div class=\"form-container\">
			<form>
			<fieldset id=\"editPublic\">
			<legend><span class=\"publicText\">Information</span></legend>

			<label for=\"opt_status\"><b>Record Created</b> </label>
			<input type=\"text\" name=\"opt_status\" id=\"opt_status\" value=\"".$person_status['updated_server']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"opt_status\"><b>Last Updated</b> </label>
			<input type=\"text\" name=\"opt_status\" id=\"opt_status\" value=\"".$person_status['updated']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"opt_status\"><b>Health / Locational Status</b> </label>
			<input type=\"text\" name=\"opt_status\" id=\"opt_status\" value=\"".$person_status['option_description']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>
		";

		if($person_to_hospital['hospital_uuid'] > 0) {
			if(strlen($hospital['icon_url']) > 5) {
				echo "<img style=\"float: left;\" src=\"".$hospital['icon_url']."\"><br>";
			}
			echo "
				<label style=\"position: relative; left: -53px;\" for=\"hospital\"><b>Located at Hospital</b> </label>
				<input style=\"position: relative; left: -53px;\" type=\"text\" name=\"hospital\" id=\"hospital\" value=\"".$person_to_hospital['name']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
				<br>
			";
		}

		echo "
			<hr class=\"insideHrGreen\">

			<label for=\"given_name\">First Name </label>
			<input type=\"text\" name=\"given_name\" id=\"given_name\" value=\"".$person_uuid['given_name']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"given_name\">Last Name </label>
			<input type=\"text\" name=\"family_name\" id=\"family_name\" value=\"".$person_uuid['family_name']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"age\">Age</label>
			<input type=\"text\" name=\"age\" id=\"age\" value=\"".$person_details['years_old']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>
		";

		$a = (int)$person_details['years_old'];
		(($a >= 0) && ($a <= 150)) ? $hide = true : $hide = false;

		if(!$hide) {
			echo "
				<label for=\"age_lower\">Lower Age Range</label>
				<input type=\"text\" name=\"age_lower\" id=\"age_upper\" value=\"".$person_details['minAge']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
				<br>

				<label for=\"age_upper\">Upper Age Range</label>
				<input type=\"text\" name=\"age_upper\" id=\"age_upper\" value=\"".$person_details['maxAge']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
				<br>
			";
		}

		echo "
			<label for=\"gender\">Gender</label>
			<input type=\"text\" name=\"gender\" id=\"gender\" value=\"".$gender."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"eye_color\">Eye Color</label>
			<input type=\"text\" name=\"eye_color\" id=\"eye_color\" value=\"".$eye."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"skin_color\">Skin Color</label>
			<input type=\"text\" name=\"skin_color\" id=\"skin_color\" value=\"".$skin."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"hair_color\">Hair Color</label>
			<input type=\"text\" name=\"hair_color\" id=\"hair_color\" value=\"".$hair."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"height\">Height</label>
			<input type=\"text\" name=\"height\" id=\"height\" value=\"".$person_physical['height']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"height\">Weight</label>
			<input type=\"text\" name=\"weight\" id=\"weight\" value=\"".$person_physical['weight']."\" size=\"30\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>
			<br>

			<label for=\"height\">Distinctive Features</label>
			<textarea name=\"comments\" id=\"comments\" cols=\"43\" rows=\"4\" tabindex=\"".++$shn_tabindex."\" class=\"nonedit public\" READONLY>".$person_physical['comments']."</textarea>
			<br>

			</fieldset></form></div>
		";
	}
	// PUBLIC VIEW END ////////////////////////////////////////////////////////////////////////////////////


	// LOAD PRIVATE DATA //////////////////////////////////////////////////////////////////////////////////
	if($global['privateEdit']) {

		$address = "";
		$zip     = "";
		$phone   = "";
		$mobile  = "";
		$email   = "";

		$q  = "
			SELECT *
			FROM contact
			WHERE pgoc_uuid = '".$global['uuid']."';
		";
		$r   = $global['db']->Execute($q);
		while ($row = $r->FetchRow()) {
			$type  = $row['opt_contact_type'];
			$value = $row['contact_value'];
			if($type == "home") {
				$address = $value;
			} else if($type == "zip") {
				$zip = $value;
			} else if($type == "curr") {
				$phone = $value;
			} else if($type == "cmob") {
				$mobile = $value;
			} else if($type == "email") {
				$email = $value;
			}
		}
	// LOAD PRIVATE DATA END ///////////////////////////////////////////////////////////////////////////


	// PRIVATE EDIT ////////////////////////////////////////////////////////////////////////////////////
		if((count($_POST) > 0) && isset($_POST['opt_race'])) {
			$editAddress    = trim($_POST['address']);
			$editZip        = trim($_POST['zip']);
			$editPhone      = trim($_POST['phone']);
			$editCell       = trim($_POST['mobile']);
			$editEmail      = trim($_POST['email']);
			$editReligion   = trim($_POST['opt_religion']);
			$editRace       = trim($_POST['opt_race']);

			if($editAddress   != $address)                        { saveContactRevision("home",  "Address",  $address, $editAddress); }
			if($editZip       != $zip)                            { saveContactRevision("zip",   "Zip Code", $zip,     $editZip);     }
			if($editPhone     != $phone)                          { saveContactRevision("curr",  "Phone",    $phone,   $editPhone);   }
			if($editCell      != $mobile)                         { saveContactRevision("cmob",  "Mobile",   $mobile,  $editCell);    }
			if($editEmail     != $email)                          { saveContactRevision("email", "Email",    $email,   $editEmail)  ; }
			if($editReligion  != $person_details['opt_religion']) { saveRevision("person_details", "opt_religion", "Religion",  $person_details['opt_religion'], $editReligion); }
			if($editRace      != $person_details['opt_race'])     { saveRevision("person_details", "opt_race",     "Race",      $person_details['opt_race'],     $editRace);     }

		} else {
			$editAddress    = $address;
			$editZip        = $zip;
			$editPhone      = $phone;
			$editCell       = $mobile;
			$editEmail      = $email;
			$editReligion   = $person_details['opt_religion'];
			$editRace       = $person_details['opt_race'];
		}

		echo "
			<div class=\"form-container\">
			<form method=\"post\" id=\"editPrivateForm\" name=\"editPrivateForm\" action=\"index.php?mod=eap&act=edit".$debugParam."&uuid=".base64_encode($global['uuid'])."\">
			<fieldset id=\"editPrivate\">
			<legend><span class=\"privateText\">View / Edit Private Information</span></legend>
		";

		shn_form_textarea("Address",                  "address", null,       array('value'=>$editAddress, 'cols'=>43));
		shn_form_text(    "Zip/Postal Code",          "zip",    'size="15"', array('value'=>$editZip  ));
		shn_form_text(    "Home Phone Number",        "phone",  'size="15"', array('value'=>$editPhone));
		shn_form_text(    "Cell/Mobile Phone Number", "mobile", 'size="15"', array('value'=>$editCell ));
		shn_form_text(    "Email Address",            "email",  'size="25"', array('value'=>$editEmail));

		shn_form_opt_select("opt_race", "Race ",         null, array('sort'=>'display_order, option_description ASC', 'value'=>$editRace    ));
		shn_form_opt_select("opt_religion", "Religion ", null, array('sort'=>'display_order, option_description ASC', 'value'=>$editReligion));

		echo "
			<br>
			<label for=\"height\">&nbsp;</label>
			<input type=\"submit\" value=\"Save Changes to Private Information\" class=\"styleTehButton\" tabindex=\"".++$shn_tabindex."\">

			</fieldset>
			</form></div>
		";
	}
	// PRIVATE EDIT END ////////////////////////////////////////////////////////////////////////////////


	// REVISIONS START//////////////////////////////////////////////////////////////////////////////////
	if($global['privateEdit']) {
		echo "
			<div class=\"form-container\">
			<form id=\"editRevisionsForm\" name=\"editRevisionsForm\">
			<fieldset id=\"editPrivate\">
			<legend><span class=\"revisionsText\">Revisions to this Record</span></legend>
		";

		$out = "<table>
			<tr>
				<td style=\"text-align: left; border: none; font-weight: bold;\" class=\"odder\">Field Changed</td>
				<td style=\"text-align: left; border: none; font-weight: bold;\" class=\"odder\">Old Value</td>
				<td style=\"text-align: left; border: none; font-weight: bold;\" class=\"odder\">New Value</td>
				<td style=\"text-align: left; border: none; font-weight: bold;\" class=\"odder\">Updated When</td>
				<td style=\"text-align: left; border: none; font-weight: bold;\" class=\"odder\">Updated By</td>
			</tr>
		";

		$q  = "
			SELECT *
			FROM person_updates u, person_uuid p
			WHERE u.p_uuid = '".$global['uuid']."'
			AND p.p_uuid = u.updated_by_p_uuid
			ORDER BY update_time ASC;
		";
		$r  = $global['db']->Execute($q);
		$count = 0;
		while($row = $r->FetchRow()) {
			if(($count % 2) == 0) {
				$class = "evener";
			} else {
				$class = "odder";
			}
			$out .= "
				<tr>
					<td style=\"text-align: left; border: none;\" class=\"".$class."\">".$row['updated_table']." :: ".$row['updated_column']."</td>
					<td style=\"text-align: left; border: none;\" class=\"".$class."\">".$row['old_value']."</td>
					<td style=\"text-align: left; border: none;\" class=\"".$class."\">".$row['new_value']."</td>
					<td style=\"text-align: left; border: none;\" class=\"".$class."\">".$row['update_time']."</td>
					<td style=\"text-align: left; border: none;\" class=\"".$class."\">".$row['full_name']."</td>
				</tr>
			";
			$count++;
		}
		$out .= "</table>";
		if($count == 0) {
			echo "<b>No revisions to this record.</b>";
		} else {
			echo $out;
		}
		echo "
			</fieldset>
			</form></div>
		";
	}
	// REVISIONS END ////////////////////////////////////////////////////////////////////////////////



	// FOLLOW //////////////////////////////////////////////////////////////////////////////////////////
	if($global['startFollow'] && $global['role'] != "reporter") {

		$q  = "
			SELECT COUNT(*)
			FROM person_followers
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p_uuid = '".$global['uuid']."';
		";
		$r  = $global['db']->Execute($q);
		$row = $r->FetchRow();
		$alreadyFollowing = (bool)$row['COUNT(*)']; // true if logged in user is already following the person

		if(!$alreadyFollowing) {
			echo "
				<script>
					function followPersonCall() {
						var fP = document.getElementById('followPerson');
						fP.submit();
					}
				</script>

				<div class=\"form-container\">
				<form method=\"post\" id=\"followPerson\" name=\"followPerson\" action=\"index.php?mod=eap&act=follow".$debugParam."&uuid=".base64_encode($global['uuid'])."\">
				<fieldset id=\"editFollow\">
				<legend><span class=\"followText\">Follow</span></legend>
				To receive email alerts when this record is updated with new information, you can elect to follow this person. You will only receive an email when the reporter or staff change any of the information in this person's record or when a user of the site leaves a note on this page.<br>
				<br>
				<input id=\"followButton\" class=\"styleTehButton\" type=\"button\" value=\"Click here to begin following this person's record via email\" onclick=\"followPersonCall();\"><br>
				<br>
				Be aware that at any time you may visit your <a href=\"index.php?mod=pref&act=default\">User Preferences</a> page to manage which people you are following.
				</fieldset>
				</form>
				</div>
			";
		} else {
			echo "
				<script>
					function unFollowPersonCall() {
						var ufP = document.getElementById('unFollowPerson');
						ufP.submit();
					}
				</script>
				<div class=\"form-container\">
				<form method=\"post\" id=\"unFollowPerson\" name=\"unFollowPerson\" action=\"index.php?mod=eap&act=unFollow".$debugParam."&uuid=".base64_encode($global['uuid'])."\">
				<fieldset id=\"editFollow\">
				<legend><span class=\"followText\">Follow</span></legend>
				To stop receiving email alerts when this record is updated with new information or notes, you can elect to unfollow this person.<br>
				<br>
				<input id=\"unFollowButton\" class=\"styleTehButton\" type=\"button\" value=\"Click here to STOP following this person's record via email\" onclick=\"unFollowPersonCall();\"><br>
				<br>
				</fieldset>
				</form>
				</div>
			";
		}
	}

	// if not allowed to follow, then we ask the user to first login/signup
	if(!$global['startFollow'] && $global['role'] != "reporter") {
		echo "
			<div class=\"form-container\">
			<form method=\"post\" id=\"followPerson\" name=\"followPerson\">
			<fieldset id=\"editFollow\">
			<legend><span class=\"followText\">Follow</span></legend>
			To receive email alerts when this record is updated with new information, you can elect to follow this person. You will only receive an email when the reporter or staff change any of the information in this person's record or when a user of the site leaves a note on this page.<br>
			<br>
			<b>If you would like to follow this person, you must first login. If you don't have an account, then first <a href=\"index.php?act=signup\">sign up for one.</a></b>
			</fieldset>
			</form>
			</div>
		";
	}
	// FOLLOW END ///////////////////////////////////////////////////////////////////////////////


	// SHARE ////////////////////////////////////////////////////////////////////////////////////
	echo "
		<div class=\"form-container\">
		<form>
		<fieldset id=\"editShare\">
		<legend>Share</legend>
		<b>Please use any of following methods to share this person's record with others:</b><br>


		<div class=\"shr-bookmarks shr-bookmarks-expand shr-bookmarks-center\">
			<ul class=\"socials\">
				<li class=\"shr-blogger\">
					<a href=\"http://www.blogger.com/blog_this.pyra?t&amp;u=".$global['googl']."&amp;n=".$global['full_name']."&amp;pli=1\" rel=\"nofollow\" class=\"external\" title=\"Blog this on Blogger\">&nbsp;</a>
				</li>
	";
	/* hiding RSS for now........
				<li class="shr-comfeed">
					<a href="http://g.miernicki.com/?p=115&amp;feed=comments-rss2" rel="nofollow" class="external" title="Subscribe to the comments for this post?">&nbsp;</a>
				</li>
	*/
	echo "
				<li class=\"shr-delicious\">
					<a href=\"http://delicious.com/post?url=".$global['googl']."&amp;title=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Share this on del.icio.us\">&nbsp;</a>
				</li>
				<li class=\"shr-digg\">
					<a href=\"http://digg.com/submit?phase=2&amp;url=".$global['googl']."&amp;title=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Digg this!\">&nbsp;</a>
				</li>
				<li class=\"shr-facebook\">
					<a href=\"http://www.facebook.com/share.php?v=4&amp;src=bm&amp;u=".$global['googl']."&amp;t=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Share this on Facebook\" onclick=\"window.open(this.href,'sharer','toolbar=0,status=0,width=626,height=436'); return false;\">&nbsp;</a>
				</li>
				<li class=\"shr-googlebookmarks\">
					<a href=\"http://www.google.com/bookmarks/mark?op=add&amp;bkmk=".$global['googl']."&amp;title=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Add this to Google Bookmarks\">&nbsp;</a>
				</li>
				<li class=\"shr-googlebuzz\">
					<a href=\"http://www.google.com/buzz/post?url=".$global['googl']."&amp;imageurl=".$global['full_thumb_url']."\" rel=\"nofollow\" class=\"external\" title=\"Post on Google Buzz\">&nbsp;</a>
				</li>
				<li class=\"shr-myspace\">
					<a href=\"http://www.myspace.com/Modules/PostTo/Pages/?u=".$global['googl']."&amp;t=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Post this to MySpace\">&nbsp;</a>
				</li>
				<li class=\"shr-reddit\">
					<a href=\"http://reddit.com/submit?url=".$global['googl']."&amp;title=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Share this on Reddit\">&nbsp;</a>
				</li>
				<li class=\"shr-stumbleupon\">
					<a href=\"http://www.stumbleupon.com/submit?url=".$global['googl']."&amp;title=".$global['full_name']."\" rel=\"nofollow\" class=\"external\" title=\"Share it on StumbleUpon\">&nbsp;</a>
				</li>
				<li class=\"shr-twitter\">
					<a href=\"http://twitter.com/home?status=".$global['full_name']."+-+".$global['googl']."&amp;source=PL\" rel=\"nofollow\" class=\"external\" title=\"Tweet This!\">&nbsp;</a>
				</li>
		</ul>
		<div style=\"clear:both;\"></div>
		</div>
		<br>
		Short URL to this page: <br>
		<b><input type=\"text\" value=\"".$global['googl']."\"></b></input><br>
		<br>
		<span>Send this page to a mobile device:</span><br>
		<img id=\"tehQRimage\" height=\"150\" class=\"qrImage\" src=\"https://www.google.com/chart?cht=qr&chs=150x150&choe=UTF-8&chld=H&chl=".$global['googl']."\">
		<script>
			function reloadQR() {
				var obj = document.getElementById('tehQRimage');
				obj.src = 'https://www.google.com/chart?cht=qr&chs=150x150&choe=UTF-8&chld=H&chl=".$global['googl']."';
			}
			setTimeout('reloadQR()', 1000);
		</script>
		<br>
		</fieldset>
		</form>
		</div>
	";
	// SHARE END ///////////////////////////////////////////////////////////////////////////////////////


	// NOTES BEGIN /////////////////////////////////////////////////////////////////////////////////////
	echo "
		<div class=\"form-container\">
		<form method=\"post\" id=\"notesPerson\" name=\"notesPerson\" action=\"index.php?mod=eap&act=addNote".$debugParam."&uuid=".base64_encode($global['uuid'])."\">
		<fieldset id=\"editNotes\">
		<legend><span class=\"notesText\">Notes</span></legend>
	";

	$q  = "
		SELECT *
		FROM person_notes n, person_uuid p
		WHERE n.note_written_by_p_uuid = p.p_uuid
		AND note_about_p_uuid = '".$global['uuid']."'
		ORDER BY n.when ASC;
	";

	$r  = $global['db']->Execute($q);

	while($row = $r->FetchRow()) {
		$delete = "";
		if($global['privateEdit'] || (isset($_SESSION['user_p_uuid']) && ($_SESSION['user_p_uuid'] == $row['note_written_by_p_uuid']))) {
			$delete = "&nbsp;&nbsp;&nbsp;<a style=\"color: red;\" href=\"index.php?mod=eap&act=deleteNote&noteId=".$row['note_id'].$debugParam."&uuid=".base64_encode($global['uuid'])."\">DELETE</a>";
		}
		echo "
			<i><b>".$row['full_name']." at ".$row['when']." commented...</b></i>".$delete."
			<div>".$row['note']."</div>
			<br>
			<br>
		";
	}

	// if user is allowed to add notes... show the tool for this
	if($global['addNote']) {
		echo "
			Add a note of your own...<br>
			<center>
				<textarea name=\"addNote\" id=\"addNote\" style=\"width: 80%; \" rows=\"5\" tabindex=\"".++$shn_tabindex."\" ></textarea><br>
				<input type=\"submit\" value=\"Save Note\" class=\"styleTehButton\" tabindex=\"".++$shn_tabindex."\">
			</center>
		";

	// if user is not allowed to add notes, tell them
	} else {
		echo "
			<br>
			<b>If you would like to leave a note, you must first login. If you don't have an account, then first <a href=\"index.php?act=signup\">sign up for one.</a>
		";
	}

	// close notes
	echo "
		<br>
		<label for=\"height\">&nbsp;</label>
		</fieldset>
		</form></div>
	";
	// NOTES END ///////////////////////////////////////////////////////////////////////////////////////


	// DEBUG ////////////////////////////////////////////////////////////////////////////////////

	// only allow debugging when enabled and only by the root user....
	if($debug && $_SESSION['user_p_uuid'] == "1") {
		echo "<div class=\"form-container\" style=\"overflow: hidden;\"><form><fieldset>";
		echo "<legend>debug</legend>";
		echo "<pre>";
		echo "user_id.....(".$_SESSION['user_id'].       ")<br>";
		echo "uuid........(".$global['uuid'].            ")<br>";
		echo "publicView..(".(int)$global['publicView']. ")<br>";
		echo "publicEdit..(".(int)$global['publicEdit']. ")<br>";
		echo "privateView.(".(int)$global['privateView'].")<br>";
		echo "privateEdit.(".(int)$global['privateEdit'].")<br>";
		echo "addNote.....(".(int)$global['addNote'].    ")<br>";
		echo "startFollow.(".(int)$global['startFollow'].")<br>";
		echo "role........(".$global['role']. ")<br>";
		echo "<br>";
		echo $googl->result()." --> ".makePageUrl()."<br><br>";
		echo "\$_SESSION[] = ".print_r($_SESSION, true)."\n\n";
		echo "\$_GET[] = ".print_r($_GET, true)."\n\n";
		echo "\$_POST[] = ".print_r($_POST, true)."\n\n";
		echo "\$global[] = ".print_r($global, true)."\n\n";
		echo "</pre>";
		echo "</fieldset></form></div>";
	}
	// DEBUG END //////////////////////////////////////////////////////////////////////////////////

	emailUpdates();
}



/*
API Google URL Shortner - goo.gl
Marcus Nunes - marcusnunes.com - 09/18/2010

eg:
$googl = new goo_gl('http://marcusnunes.com/api-goo.gl.php');
echo $googl->result();
*/

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


