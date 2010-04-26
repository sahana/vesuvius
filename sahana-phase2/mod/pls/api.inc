<?php
/**
 * PL Web Services
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <miernickig@mail.nih.gov>
 * @copyright  NIH - http://www.nih.gov
 * @package    module
 * @subpackage pls
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */



/**
 * This is the test function to get SOAP working
 * @access public
 * @param y
 * @param x
 * @return array
 */
function shn_pls_test($x, $y) {
	$list = array();
	$list[] = array('x'=>$x, 'y'=>$y);
	return $list;
}



/**
 * This returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
 * @access public
 * @return array
 */
function shn_pls_get_incident_list() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT incident_id, parent_id, name, shortname, date, type, latitude, longitude FROM `incident` ;";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'incident_id' => $result->fields["incident_id"], 
			'parent_id'   => $result->fields["parent_id"], 
			'name'        => $result->fields["name"],
			'shortname'   => $result->fields["shortname"],
			'date'        => $result->fields["date"],
			'type'        => $result->fields["type"],
			'latitude'    => $result->fields["latitude"],
			'longitude'   => $result->fields["longitude"]
		);
		$result->MoveNext();
	}
	return $list;
}



/**
 * This returns a single new sahana uuid
 * @access public
 * @param params
 * @return string
 */
function shn_pls_create_uuid($incidentId) {
	global $global;
	$db = $global['db'];
	$list = array();
	$count = 0;
	$q = "SELECT incident_id FROM incident WHERE incident_id = '".$incidentId."';";
	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		// incident exists
		$count = 1;
		$result->MoveNext();
	}
	// if its a valid incident create a uuid and assign it to a incident otherwise error
	if ($count>0) {
		include_once $global['approot'].'/inc/lib_uuid.inc';
		$uuid = shn_create_uuid();
		$list[] = array('uuid'=>$uuid);
		$q = "INSERT into resource_to_incident (incident_id, x_uuid) VALUES ('".$incidentId."', '".$uuid."');";
		$result = $db->Execute($q);
	} else {
		$list[] = "error: invalid incident id";
	}
	return $list;
}



/**
 * This returns a batch of new sahana uuids
 * @access public
 * @param int incident
 * @param int num
 * @return string
 */
function shn_pls_create_uuid_batch($incidentId, $num) {
	global $global;
	$db = $global['db'];
	$list = array();
	$count = 0;
	$q = "SELECT incident_id FROM incident WHERE incident_id = '".$incidentId."';";
	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		// incident exists
		$count = 1;
		$result->MoveNext();
	}
	// if its a valid incident create a uuid and assign it to a incident otherwise error
	if ($count>0) {
		if ($num > 0 && $num <= 100) {
			include_once $global['approot'].'/inc/lib_uuid.inc';
			for ($i = 0; $i < $num; $i++) {
				$uuid = shn_create_uuid();
				$list[] = array('uuid'=>$uuid);
				$q = "INSERT into resource_to_incident (incident_id, x_uuid) VALUES ('".$incidentId."', '".$uuid."');";
				$result = $db->Execute($q);
			}
		} else {
			$list[] = "error: can only request 1-100 uuid's at a time";
		}
	} else {
		$list[] = "error: invalid incident id";
	}
	return $list;
}



/**
 * This returns an array of information about a person.
 * @param
 * @access public
 * @return array
 */
function shn_pls_get_person_data($uuid) {
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
 * This a basic array of person data matching a search (status-less).
 * @param  search_term
 * @access public
 * @return array
 */

function shn_pls_basic_search($searchString) {
	global $global;
	$db = $global['db'];
	$termCount = 0;
	$qqq = "";

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

	$terms = explode(" ", $searchString);

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

	$q = "
		SELECT a.p_uuid, a.full_name, 
			b.opt_status, DATE_FORMAT(b.updated, '%M %e %Y') as updated, 
			c.opt_gender, c.years_old,
			i.image_height, i.image_width, i.url,
			e.comments, e.last_seen
	      	FROM person_uuid a 
	        JOIN person_status b USING (p_uuid)
	        JOIN image i ON a.p_uuid = i.x_uuid
	        JOIN person_details c USING (p_uuid)
		JOIN person_missing e USING (p_uuid)
		WHERE ".$qqq." 
		AND b.isVictim = '1' 
		ORDER BY i.url DESC, b.opt_status DESC;";

	$result = $db->Execute($q);
	
	while (!$result == NULL && !$result->EOF) {
		$o = str_replace("\"", "", $result->fields["opt_status"]);
		$list[] = array(
			'p_uuid'        => $result->fields["p_uuid"], 
			'full_name'     => $result->fields["full_name"], 
			'years_old'     => $result->fields["years_old"], 
			'gender'        => $result->fields["opt_gender"],
			'status'        => $o,
			'statusUpdated' => $result->fields["updated"], 
			'last_seen'     => $result->fields["last_seen"], 
			'comments'      => strip_tags($result->fields["comments"]),
			'imageUrl'      => $result->fields["url"], 
			'imageWidth'    => $result->fields["image_width"], 
			'imageHeight'   => $result->fields["image_height"],
		);
		$result->MoveNext();
	}
	return $list;
}
