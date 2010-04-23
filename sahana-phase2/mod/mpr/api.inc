<?php
/**
 * MPR Web Services
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @author     Greg Miernicki <miernickig@mail.nih.gov>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


/**
 * This returns a list of uuid's of current missing people.
 * @param
 * @access public
 * @return array
 */
function shn_mpr_list_missing_person_uuids() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT a.p_uuid
		FROM person_uuid a
		LEFT OUTER JOIN person_physical b USING (p_uuid)
		INNER JOIN person_missing c USING (p_uuid)
		INNER JOIN person_status d USING (p_uuid)
		INNER JOIN resource_to_incident e ON a.p_uuid = e.x_uuid
		WHERE d.opt_status = 'mis'
		ORDER BY d.updated DESC ;";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = $result->fields["p_uuid"];
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns a list of uuid's of current people who are not missing.
 * @param
 * @access public
 * @return array
 */
function shn_mpr_list_found_person_uuids() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT a.p_uuid
		FROM person_uuid a
		LEFT OUTER JOIN person_physical b USING (p_uuid)
		INNER JOIN person_status d USING (p_uuid)
		INNER JOIN resource_to_incident e ON a.p_uuid = e.x_uuid
		WHERE d.opt_status != 'mis'
		ORDER BY d.updated DESC ;";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = $result->fields["p_uuid"];
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns an array of (uuid, peron status, triage status) of all persons
 * @param
 * @access public
 * @return array
 */
function shn_mpr_list_all() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT a.p_uuid, b.opt_status, c.triageCategory
		FROM person_uuid a
		LEFT OUTER JOIN person_status b USING (p_uuid)
		LEFT OUTER JOIN mpres_patient c USING (p_uuid);";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('p_uuid'=>$result->fields["p_uuid"], 'opt_status'=>$result->fields["opt_status"], 'triageCategory'=>$result->fields["triageCategory"]);
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns an array of (uuid, peron status, triage status) of all persons matching a search term across full name
 * @param
 * @access public
 * @return array
 */
function shn_mpr_get_uuids_matching_search($uuid) {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT a.p_uuid, b.opt_status, c.triageCategory
		FROM person_uuid a
		LEFT OUTER JOIN person_status b USING (p_uuid)
		LEFT OUTER JOIN mpres_patient c USING (p_uuid)
		WHERE a.full_name LIKE '%".$uuid."%';";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('p_uuid'=>$result->fields["p_uuid"], 'opt_status'=>$result->fields["opt_status"], 'triageCategory'=>$result->fields["triageCategory"]);
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns an array of (uuid, peron status) of all persons matching a search term across full name
 * @param uuid ~ a misnomber, as there is a bug in sahana when renaming this field to something else, it actually contains the search term
 * @access public
 * @return array
 */
function shn_mpr_get_uuids_matching_search2($term) {
	global $global;
	$db = $global['db'];
	$termCount = 0;
	$qqq = "";

	$expload = explode("GGGdelimiterKKK", $term);
	$term     = $expload[0];
	$missing  = $expload[1];
	$alive    = $expload[2];
	$injured  = $expload[3];
	$deceased = $expload[4];
	$unknown  = $expload[5];

	if ($missing  == "true") { $missing  = true; }else{ $missing  = false; }
	if ($alive    == "true") { $alive    = true; }else{ $alive    = false; }
	if ($injured  == "true") { $injured  = true; }else{ $injured  = false; }
	if ($deceased == "true") { $deceased = true; }else{ $deceased = false; }
	if ($unknown  == "true") { $unknown  = true; }else{ $unknown  = false; }

	$term = str_replace(";", " ", $term);
	$term = str_replace(",", " ", $term);
	$term = str_replace(".", " ", $term);
	$term = str_replace("<", " ", $term);
	$term = str_replace(">", " ", $term);
	$term = str_replace("?", " ", $term);
	$term = str_replace(":", " ", $term);
	$term = str_replace("'", " ", $term);
	$term = str_replace("\"", " ", $term);
	$term = str_replace("`", " ", $term);
	$term = str_replace("~", " ", $term);
	$term = str_replace("!", " ", $term);
	$term = str_replace("@", " ", $term);
	$term = str_replace("#", " ", $term);
	$term = str_replace("$", " ", $term);
	$term = str_replace("%", " ", $term);
	$term = str_replace(":", " ", $term);

	$terms = explode(" ", $term);

	for ($i = 0; $i < count($terms); $i++) {
		$term = $terms[$i];
		if (strlen($term) >= 2) {
			if ($termCount == 0) {
				$qqq .= "(a.full_name like '".$term."%' or a.full_name like '% ".$term."%' or a.full_name like '%,".$term."' or a.full_name like '%.".$term."')";
				$termCount++;
			} else  {
				$qqq .= " OR (a.full_name like '".$term."%' or a.full_name like '% ".$term."%' or a.full_name like '%,".$term."' or a.full_name like '%.".$term."')";
				$termCount++;
			}
		}
	}

	$oneTwo = false;
	$mmm = "AND (";
	if ($missing) { $mmm .= "b.opt_status = 'mis'"; $oneTwo = true;}
	if ($alive) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'ali'"; 
	}
	if ($injured) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'inj'"; 
	}
	if ($deceased) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'dec'"; 
	}
	if ($unknown) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'unk' OR b.opt_status is null"; 
	}

	$mmm .= ")";
	$q = "SELECT a.p_uuid, a.full_name, b.opt_status FROM person_uuid a LEFT OUTER JOIN person_status b USING (p_uuid) WHERE ".$qqq." ".$mmm." ORDER BY opt_status DESC;";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$o = str_replace("\"", "", $result->fields["opt_status"]);
		$list[] = array('p_uuid'=>$result->fields["p_uuid"], 'full_name'=>$result->fields["full_name"], 'opt_status'=>$o);
		$result->MoveNext();
	}

	return $list;
}




/**
 * This returns an array of (uuid, peron status) of all persons matching a search term across full name
 * @param uuid ~ a misnomber, as there is a bug in sahana when renaming this field to something else, it actually contains the search term
 * @access public
 * @return array
 */
function shn_mpr_get_uuids_matching_search3($term) {
	global $global;
	$db = $global['db'];
	$termCount = 0;
	$qqq = "";

	$expload = explode("GGGdelimiterKKK", $term);
	$term     = $expload[0];
	$missing  = $expload[1];
	$alive    = $expload[2];
	$injured  = $expload[3];
	$deceased = $expload[4];
	$unknown  = $expload[5];

	if ($missing  == "true") { $missing  = true; }else{ $missing  = false; }
	if ($alive    == "true") { $alive    = true; }else{ $alive    = false; }
	if ($injured  == "true") { $injured  = true; }else{ $injured  = false; }
	if ($deceased == "true") { $deceased = true; }else{ $deceased = false; }
	if ($unknown  == "true") { $unknown  = true; }else{ $unknown  = false; }

	$term = str_replace(";", " ", $term);
	$term = str_replace(",", " ", $term);
	$term = str_replace(".", " ", $term);
	$term = str_replace("<", " ", $term);
	$term = str_replace(">", " ", $term);
	$term = str_replace("?", " ", $term);
	$term = str_replace(":", " ", $term);
	$term = str_replace("'", " ", $term);
	$term = str_replace("\"", " ", $term);
	$term = str_replace("`", " ", $term);
	$term = str_replace("~", " ", $term);
	$term = str_replace("!", " ", $term);
	$term = str_replace("@", " ", $term);
	$term = str_replace("#", " ", $term);
	$term = str_replace("$", " ", $term);
	$term = str_replace("%", " ", $term);
	$term = str_replace(":", " ", $term);

	$terms = explode(" ", $term);

	for ($i = 0; $i < count($terms); $i++) {
		$term = $terms[$i];
		if (strlen($term) >= 2) {
			if ($termCount == 0) {
				$qqq .= "(a.full_name like '".$term."%' or a.full_name like '% ".$term."%' or a.full_name like '%,".$term."' or a.full_name like '%.".$term."')";
				$termCount++;
			} else  {
				$qqq .= " OR (a.full_name like '".$term."%' or a.full_name like '% ".$term."%' or a.full_name like '%,".$term."' or a.full_name like '%.".$term."')";
				$termCount++;
			}
		}
	}

	$oneTwo = false;
	$mmm = "AND (";
	if ($missing) { $mmm .= "b.opt_status = 'mis'"; $oneTwo = true;}
	if ($alive) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'ali'"; 
	}
	if ($injured) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'inj'"; 
	}
	if ($deceased) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'dec'"; 
	}
	if ($unknown) { 
		if ($oneTwo) { $mmm .= " OR "; }else{ $oneTwo = true; }
		$mmm .= "b.opt_status = 'unk' OR b.opt_status is null"; 
	}

	$mmm .= ")";
	$q = "SELECT a.p_uuid, a.full_name, b.opt_status FROM person_uuid a LEFT OUTER JOIN person_status b USING (p_uuid) WHERE ".$qqq." ".$mmm." AND b.isVictim = '1' ORDER BY opt_status DESC;";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$o = str_replace("\"", "", $result->fields["opt_status"]);
		$list[] = array('p_uuid'=>$result->fields["p_uuid"], 'full_name'=>$result->fields["full_name"], 'opt_status'=>$o);
		$result->MoveNext();
	}

	return $list;
}

function shn_mpr_get_uuids_matching_search4($term) {
	global $global;
	$db = $global['db'];
	$termCount = 0;
	$qqq = "";

	$expload = explode("GGGdelimiterKKK", $term);
	$term     = $expload[0];
	$missing  = $expload[1];
	$alive    = $expload[2];
	$injured  = $expload[3];
	$deceased = $expload[4];
	$unknown  = $expload[5];

	if ($missing  == "true") { $missing  = true; }else{ $missing  = false; }
	if ($alive    == "true") { $alive    = true; }else{ $alive    = false; }
	if ($injured  == "true") { $injured  = true; }else{ $injured  = false; }
	if ($deceased == "true") { $deceased = true; }else{ $deceased = false; }
	if ($unknown  == "true") { $unknown  = true; }else{ $unknown  = false; }

	$term = str_replace(";", " ", $term);
	$term = str_replace(",", " ", $term);
	$term = str_replace(".", " ", $term);
	$term = str_replace("<", " ", $term);
	$term = str_replace(">", " ", $term);
	$term = str_replace("?", " ", $term);
	$term = str_replace(":", " ", $term);
	$term = str_replace("'", " ", $term);
	$term = str_replace("\"", " ", $term);
	$term = str_replace("`", " ", $term);
	$term = str_replace("~", " ", $term);
	$term = str_replace("!", " ", $term);
	$term = str_replace("@", " ", $term);
	$term = str_replace("#", " ", $term);
	$term = str_replace("$", " ", $term);
	$term = str_replace("%", " ", $term);
	$term = str_replace(":", " ", $term);

	$terms = explode(" ", $term);

	for ($i = 0; $i < count($terms); $i++) {
		$term = $terms[$i];
		if (strlen($term) >= 2) {
			if ($termCount == 0) {
				$qqq .= "(a.full_name like '".$term."%' or a.full_name like '% ".$term."%' or a.full_name like '%,".$term."' or a.full_name like '%.".$term."')";
				$termCount++;
			} else  {
				$qqq .= " OR (a.full_name like '".$term."%' or a.full_name like '% ".$term."%' or a.full_name like '%,".$term."' or a.full_name like '%.".$term."')";
				$termCount++;
			}
		}
	}

	$oneTwo = false;
	$mmm = "AND ( 1 = 1 ";
	if ($missing) { 
		$mmm .= " OR b.opt_status = 'mis'";
	}
	if ($alive) { 
		$mmm .= " OR b.opt_status = 'ali'"; 
	}
	if ($injured) { 
		$mmm .= " OR b.opt_status = 'inj'"; 
	}
	if ($deceased) { 
		$mmm .= " OR b.opt_status = 'dec'"; 
	}
	if ($unknown) { 
		$mmm .= " OR b.opt_status = 'unk' OR b.opt_status is null"; 
	}

	$mmm .= ")";
	$q = "
	      SELECT a.p_uuid, a.full_name, 
	             b.opt_status, DATE_FORMAT(b.updated, '%M %e %Y') as updated, 
	             c.opt_gender, c.years_old, c.opt_age_group, 
	             i.image_height, i.image_width, i.url,
				 e.comments, e.last_seen
	      	FROM person_uuid a 
	        JOIN person_status b USING (p_uuid)
	        JOIN image i ON a.p_uuid = i.x_uuid
	        JOIN person_details c USING (p_uuid)
			JOIN person_missing e USING (p_uuid)
	       WHERE "
	      . $qqq . " " . $mmm ." AND b.isVictim = '1' ORDER BY i.url DESC, b.opt_status DESC;";

	$result = $db->Execute($q);
	
	while (!$result == NULL && !$result->EOF) {
		$o = str_replace("\"", "", $result->fields["opt_status"]);
		$list[] = array('p_uuid'=>$result->fields["p_uuid"], 'full_name'=>$result->fields["full_name"], 'opt_status'=>$o,
				'imageUrl'=>$result->fields["url"], 'imageWidth'=>$result->fields["image_width"], 'imageHeight'=>$result->fields["image_height"], 'years_old'=>$result->fields["years_old"], 'age'=>$result->fields["opt_age_group"], 'id'=>$result->fields["personId"], 'statusSahanaUpdated'=>$result->fields["updated"], 'statusTriage'=>$result->fields["triageCategory"], 'peds'=>$result->fields["peds"], 'orgName'=>$result->fields["orgName"], 'last_seen'=>$result->fields["last_seen"], 'comments'=>strip_tags($result->fields["comments"]));
		$result->MoveNext();
	}
	//return array($q);
	return $list;
}



/**
 * This returns an array of information about a person.
 * @param
 * @access public
 * @return array
 */
function shn_mpr_get_person_data($uuid) {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "
		SELECT a.p_uuid, a.full_name, b.opt_gender, b.birth_date, b.opt_age_group, c.opt_status, c.updated, d.triageCategory, d.personId, d.peds, d.orgName, i.image_height, i.image_width, i.url, e.last_seen, e.comments
		FROM person_uuid a
		LEFT OUTER JOIN person_details b USING (p_uuid)
		LEFT OUTER JOIN person_status c USING (p_uuid)
		LEFT OUTER JOIN mpres_patient d USING (p_uuid)
		LEFT OUTER JOIN image i ON a.p_uuid = i.x_uuid
		LEFT OUTER JOIN person_missing e USING (p_uuid)
		WHERE a.p_uuid = '".$uuid."';";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('uuid'=>$result->fields["p_uuid"], 'name'=>$result->fields["full_name"], 'gender'=>$result->fields["opt_gender"], 'birthdate'=>$result->fields["birth_date"], 'age'=>$result->fields["opt_age_group"], 'statusSahana'=>$result->fields["opt_status"], 'statusSahanaUpdated'=>$result->fields["updated"], 'statusTriage'=>$result->fields["triageCategory"], 'id'=>$result->fields["personId"], 'peds'=>$result->fields["peds"], 'orgName'=>$result->fields["orgName"], 'imageWidth'=>$result->fields["image_width"], 'imageHeight'=>$result->fields["image_height"], 'imageUrl'=>$result->fields["url"], 'last_seen'=>$result->fields["last_seen"], 'comments'=>$result->fields["comments"]);
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns an array of information about a person.
 * @param
 * @access public
 * @return array
 */
function shn_mpr_get_person_data2($uuid) {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "
		SELECT a.p_uuid, a.full_name, b.opt_gender, b.years_old, b.opt_age_group, c.opt_status, c.updated, i.image_height, i.image_width, i.url, e.last_seen, e.comments
		FROM person_uuid a
		LEFT OUTER JOIN person_details b USING (p_uuid)
		LEFT OUTER JOIN person_status c USING (p_uuid)
		LEFT OUTER JOIN image i ON a.p_uuid = i.x_uuid
		LEFT OUTER JOIN person_missing e USING (p_uuid)
		WHERE a.p_uuid = '".$uuid."';";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('uuid'=>$result->fields["p_uuid"], 'name'=>$result->fields["full_name"], 'gender'=>$result->fields["opt_gender"], 'years_old'=>$result->fields["years_old"], 'age'=>$result->fields["opt_age_group"], 'statusSahana'=>$result->fields["opt_status"], 'statusSahanaUpdated'=>$result->fields["updated"], 'statusTriage'=>$result->fields["triageCategory"], 'id'=>$result->fields["personId"], 'peds'=>$result->fields["peds"], 'orgName'=>$result->fields["orgName"], 'imageWidth'=>$result->fields["image_width"], 'imageHeight'=>$result->fields["image_height"], 'imageUrl'=>$result->fields["url"], 'last_seen'=>$result->fields["last_seen"], 'comments'=>strip_tags($result->fields["comments"]));
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns a list of uuid's of current missing people.
 * @param
 * @access public
 * @return array
 */
function shn_mpr_total_records2() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT COUNT(*) as count FROM person_uuid LEFT OUTER JOIN person_status b USING (p_uuid) WHERE b.isVictim = '1';";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('count'=>$result->fields["count"]);
		$result->MoveNext();
	}
	return $list;
}




/**
 * This returns a list of uuid's of current missing people.
 * @param
 * @access public
 * @return array
 */
function shn_mpr_total_records() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT COUNT(*) as count FROM person_uuid;";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('count'=>$result->fields["count"]);
		$result->MoveNext();
	}
	return $list;
}





// Below function commented out as no ws.xml was provided, this not fully implemented
/*
function shn_mpr_api_addmp($arrmpr) {
	global $global;

	$insert_array['p_uuid'] = $arrmpr['p_uuid'];

	//Basic Details : Table person_uuid and Phonetic Table
	if(isset($arrmpr['full_name'])){
		$insert_array['full_name'] = $arrmpr['full_name'];
		shn_db_insert_phonetic($insert_array['full_name'],$insert_array['p_uuid']);
	}
	if(isset($arrmpr['family_name'])){
		$insert_array['family_name'] = $arrmpr['family_name'];
		shn_db_insert_phonetic($insert_array['family_name'],$insert_array['p_uuid']);
	}
	if(isset($arrmpr['local_name'])){
		$insert_array['l10n_name'] = $arrmpr['local_name'];
		shn_db_insert_phonetic($insert_array['l10n_name'],$insert_array['p_uuid']);
	}

	shn_db_insert($insert_array,'person_uuid',true, 'p_uuid');
	$insert_array = null;


	$insert_array['p_uuid'] = $arrmpr['p_uuid'];
	//Identity
	if(isset($arrmpr['idcard'])) {
		$insert_array['serial'] = $arrmpr['idcard'];
		$insert_array['opt_id_type'] = 'nic';
		shn_db_insert($insert_array,'identity_to_person',true,'p_uuid');
	}
	if(isset($arrmpr['passport'])) {
		$insert_array['serial'] = $arrmpr['passport'];
		$insert_array['opt_id_type'] = 'pas';
		shn_db_insert($insert_array,'identity_to_person',true,'p_uuid');
	}
	if(isset($arrmpr['drv_license'])) {
		$insert_array['serial'] = $arrmpr['drv_license'];
		$insert_array['opt_id_type'] = 'dln';
		shn_db_insert($insert_array,'identity_to_person', true, 'p_uuid');
	}
	$insert_array = null;

	//Contacts
	$insert_array['poc_uuid'] = $arrmpr['p_uuid'];
	$insert_array['opt_person_loc_type'] = 'hom';
	if(isset($arrmpr['address'])){
		$insert_array['address'] = $arrmpr['address'];
	}

	// This hack should be integrated with the lib_location
	//Starts
	$i = $conf['mod_mpr_location_lower_limit'];
	while((! isset($arrmpr[$i])) &&
		$i > $conf['mod_mpr_location_upper_limit'] )
	$i--;
	//Ends

	if(isset($arrmpr[$i]))
		$insert_array['location_id'] = $arrmpr[$i];

	if(isset($arrmpr['zip']))
		$insert_array['postcode'] = $arrmpr['zip'];
	shn_db_insert($insert_array,'location_details', true, 'poc_uuid');
	$insert_array = null;

	//Contact : Phone
	$insert_array['pgoc_uuid'] = $arrmpr['p_uuid'];
	if(isset($arrmpr['phone'])){
		$insert_array['contact_value'] = $arrmpr['phone'];
		$insert_array['opt_contact_type'] = 'curr';

	}
	shn_db_insert($insert_array,'contact', true, 'pgoc_uuid');
	$insert_array = null;

	//Contact : Mobile
	$insert_array['pgoc_uuid'] = $arrmpr['p_uuid'];
	if(isset($arrmpr['mobile'])){
		$insert_array['contact_value'] = $arrmpr['mobile'];
		$insert_array['opt_contact_type'] = 'cmob';
	}
	shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
	$insert_array = null;

	//Physical Details : person_physical
	$insert_array['p_uuid'] = $arrmpr['p_uuid'];
	if(isset($arrmpr['opt_eye_color']))
		$insert_array['opt_eye_color'] = $arrmpr['opt_eye_color'];
	if(isset($arrmpr['opt_skin_color']))
		$insert_array['opt_skin_color'] = $arrmpr['opt_skin_color'];
	if(isset($arrmpr['opt_hair_color']))
		$insert_array['opt_hair_color'] = $arrmpr['opt_hair_color'];
	if(isset($arrmpr['height']))
		$insert_array['height'] = $arrmpr['height'];
	if(isset($arrmpr['weight']))
		$insert_array['weight'] = $arrmpr['weight'];
	if(isset($arrmpr['opt_blood_type']))
		$insert_array['opt_blood_type'] = $arrmpr['opt_blood_type'];
	if(isset($arrmpr['physical_comments']))
		$insert_array['comments'] = $arrmpr['physical_comments'];
	shn_db_insert($insert_array,'person_physical',true,'p_uuid');
	$insert_array = null;

	$insert_array['p_uuid'] = $arrmpr['p_uuid'];


	//Other Details
	if(isset($arrmpr['last_seen']))
		$insert_array['last_seen'] = $arrmpr['last_seen'];
	if(isset($arrmpr['last_clothing']))
		$insert_array['last_clothing'] = $arrmpr['last_clothing'];
	if(isset($arrmpr['comments']))
		$insert_array['comments'] = $arrmpr['comments'];

	shn_db_insert($insert_array,'person_missing',true,'p_uuid');
	//reset $insert_array
	$insert_array = null;

	$insert_array['p_uuid'] = $arrmpr['p_uuid'];
	//person_details
	if(isset($arrmpr['dob']))
		$insert_array['birth_date'] = $arrmpr['dob'];
	if(isset($arrmpr['opt_age_group']))
		$insert_array['opt_age_group'] = $arrmpr['opt_age_group'];
	if(isset($arrmpr['opt_gender']))
		$insert_array['opt_gender'] = $arrmpr['opt_gender'];
	if(isset($arrmpr['opt_marital_status']))
		$insert_array['opt_marital_status'] = $arrmpr['opt_marital_status'];
	if(isset($arrmpr['opt_religion']))
		$insert_array['opt_religion'] = $arrmpr['opt_religion'];
	if(isset($arrmpr['opt_race']))
		$insert_array['opt_race'] = $arrmpr['opt_race'];
	shn_db_insert($insert_array,'person_details',true,'p_uuid');
	//reset $insert_array
	$insert_array = null;

	$insert_array['p_uuid'] = $arrmpr['p_uuid'];
	//Insert Into person_status mis
	$insert_array['opt_status'] = $arrmpr['opt_status'];
	$insert_array['isvictim'] = 'TRUE';
	shn_db_insert($insert_array,'person_status',true,'p_uuid');
	//reset $insert_array
	$insert_array = null;

	//insert into mutiple incidents
	$insert_array['x_uuid'] = $arrmpr['p_uuid'];
	$insert_array['incident_id'] = $_SESSION['user_pref_ims_incident_id'];
	shn_db_insert($insert_array,'resource_to_incident',true,'x_uuid');
	//reset $insert_array
	$insert_array = null;

	/**
	* todo: Later for now using the person_to_report to group
	//Insert into pgroup
	/*
	* For Tracking purpose create a group around missing person
	* /
	$insert_array['p_uuid'] = $arrmpr['p_uuid'];
	$insert_array['opt_group_type'] = 'mpr_trk';
	shn_db_insert($insert_array,'pgroup');
	//reset $insert_array
	$insert_array = null;
	//

	//reset $insert_array

	if($arrmpr['tracker_id']){
		shn_add_person_to_report ($arrmpr['p_uuid'],
			$arrmpr['tracker_id'],
			$_SESSION['mpr_add']['report_person']['rep_relation']);
	}else
		shn_mpr_addmp_insert_reporter($arrmpr['p_uuid']);

	//Insert Image if image save handler is set to database
	if($conf['mod_mpr_upload_picture_savehandler'] == 'database'){
		shn_image_to_db_ex($arrmpr['p_uuid'],
				$_SESSION['mpr']['entry']['image'],
				$_SESSION['mpr']['entry']['image_type'],
				$_SESSION['mpr']['entry']['image_height'],
				$_SESSION['mpr']['entry']['image_width']);
	}
}
*/