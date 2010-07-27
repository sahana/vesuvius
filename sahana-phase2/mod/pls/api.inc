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
 * @author     Greg Miernicki <g@miernicki.com>
 * @copyright  http://sahanafoundation.org
 * @package    module
 * @version    1.0
 * @subpackage pls
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */




/**
 * This function is called by the Document/Literal SOAP server upon initalization to register all the api services from this module's api.
 * 
 * As you can see in this function, each of the API functions must be essentially declared(registered) here manually.
 * This approach is different from other Sahana modules that used the RPC/encoded SOAP server.
 *
 * @access public
 * @param string namespace
 */
function shn_pls_register_all($namespace) {
	global $server;
	/*
		$server->register(
			$function,  // $name the name of the PHP function, class.method or class..method
			$in,        // $in assoc array of input values: key = param name, value = param type
			$out,       // $out assoc array of output values: key = param name, value = param type
			$ns,        // $namespace the element namespace for the method or false
			$action,    // $soapaction the soapaction for the method or false
			"document", // $style optional (rpc|document) or false Note: when 'document' is specified, parameter and return wrappers are created for you automatically
			"literal",  // $use optional (encoded|literal) or false
			$doc,       // $documentation optional Description to include in WSDL
			null        // $encodingStyle optional (usually 'http://schemas.xmlsoap.org/soap/encoding/' for encoded)
		);
	*/

	shn_pls_register_one($server, 'shn_pls_basicSearch', 
		array(
			'in' => array(
				'searchString'      => 'xsd:string',
				'incidentShortName' => 'xsd:string'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"This a basic search for a person matching a string and assigned to a particular incident."
	);

	shn_pls_register_one($server, 'shn_pls_test', 
		array(
			'in' => array(
				'x' => 'xsd:integer'
			),
			'out' => array(
				'results' => 'xsd:integer'
			)
		),
		$namespace,
		"This is the test function to get SOAP working. It returns the integer value that is passed in."
	);

	shn_pls_register_one($server, 'shn_pls_basicSearchAll', 
		array(
			'in' => array(
				'searchString' => 'xsd:string'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"This a basic search for a person matching a string across all incidents."
	);

	shn_pls_register_one($server, 'shn_pls_getIncidentList', 
		array(
			'in' => array(null),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"This returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents."
	);

	shn_pls_register_one($server, 'shn_pls_createUuid', 
		array(
			'in' => array(
				'incidentId' => 'xsd:integer'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"This returns a single new uuid associated to a specific incident."
	);

	shn_pls_register_one($server, 'shn_pls_createUuidBatch', 
		array(
			'in' => array(
				'incidentId' => 'xsd:integer',
				'num'        => 'xsd:integer'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"This returns a batch of new uuids associated to a specific incident."
	);

	shn_pls_register_one($server, 'shn_pls_getPersonData', 
		array(
			'in' => array(
				'uuid' => 'xsd:integer'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"This returns an array of information about a person."
	);
}



function shn_pls_register_one($server, $methodname, $params, $ns, $rtfm) {
	global $ns;
	$server->register(
		$methodname, 
		$params["in"], 
		$params["out"],
		$ns,
		$server->wsdl->endpoint.'#'.$methodname, // soapaction
		'document',
		'literal',
		$rtfm
	);
}



/**
 * This a basic search for a person matching a string and assigned to a particular incident.
 * @param  string search_term
 * @param  string incidentShortName
 * @return array search_results
 */

function shn_pls_basicSearch($searchString, $incidentShortName) {
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
			i.image_height, i.image_width, i.url, i.url_thumb,
			e.comments, e.last_seen
		FROM person_uuid a
		JOIN person_status b USING (p_uuid)
		JOIN image i ON a.p_uuid = i.x_uuid
		JOIN person_details c USING (p_uuid)
		JOIN person_missing e USING (p_uuid)
		JOIN resource_to_incident r ON a.p_uuid = r.x_uuid
		JOIN incident z ON z.incident_id = r.incident_id
		WHERE ".$qqq." 
		AND b.isVictim = '1'
		AND r.x_uuid = a.p_uuid
		AND z.shortname = '".$incidentShortName."'
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
			'imageUrlThumb' => $result->fields["url_thumb"],
		);
		$result->MoveNext();
	}

	return array('results'=>json_encode($list));
}



/**
 * This is the test function to get SOAP working. It returns the integer value that is passed in.
 * @access public
 * @param int y
 * @return array
 */
function shn_pls_test($x) {
	$list = array();
	$list[] = array('x'=>$x);
	return array('results'=>json_encode($list));
}



/**
* This a basic search for a person matching a string across all incidents.
 * @param  string search_term
 * @return array
 */

function shn_pls_basicSearchAll($searchString) {
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
			i.image_height, i.image_width, i.url, i.url_thumb,
			e.comments, e.last_seen, z.shortname, z.name
	      	FROM person_uuid a 
	        JOIN person_status b USING (p_uuid)
	        JOIN image i ON a.p_uuid = i.x_uuid
	        JOIN person_details c USING (p_uuid)
		JOIN person_missing e USING (p_uuid)
		JOIN resource_to_incident r ON a.p_uuid = r.x_uuid
		JOIN incident z ON z.incident_id = r.incident_id
		WHERE ".$qqq." 
		AND b.isVictim = '1' 
		ORDER BY i.url DESC, b.opt_status DESC;";

	$result = $db->Execute($q);
	
	while (!$result == NULL && !$result->EOF) {
		$o = str_replace("\"", "", $result->fields["opt_status"]);
		$list[] = array(
			'p_uuid'            => $result->fields["p_uuid"], 
			'full_name'         => $result->fields["full_name"], 
			'years_old'         => $result->fields["years_old"], 
			'gender'            => $result->fields["opt_gender"],
			'status'            => $o,
			'statusUpdated'     => $result->fields["updated"], 
			'last_seen'         => $result->fields["last_seen"], 
			'comments'          => strip_tags($result->fields["comments"]),
			'imageUrl'          => $result->fields["url"], 
			'imageWidth'        => $result->fields["image_width"], 
			'imageHeight'       => $result->fields["image_height"],
			'imageUrlThumb'     => $result->fields["url_thumb"],
			'incidentName'      => $result->fields["name"], 
			'incidentShortName' => $result->fields["shortname"],
		);
		$result->MoveNext();
	}
	return array('results'=>json_encode($list));
}



/**
 * This returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
 * @return array
 */
function shn_pls_getIncidentList() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "SELECT incident_id, parent_id, name, shortname, date, type, latitude, longitude 
	      FROM `incident` 
	      ORDER BY `default` DESC, `name` ASC;";

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
	return array('results'=>json_encode($list));
}



/**
 * This returns a single new uuid associated to a specific incident.
 * @param int incidentId
 * @return string ~ uuid
 */
function shn_pls_createUuid($incidentId) {
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
	return array('results'=>json_encode($list));
}



/**
 * This returns a batch of new uuids associated to a specific incident.
 * @access public
 * @param int incident
 * @param int num ~ number of id's to create
 * @return array ~ list of new uuid's
 */
function shn_pls_createUuidBatch($incidentId, $num) {
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
			$list[] = "error: can only request 1-100 uuid's at a time or you did not match parameter names correctly.";
		}
	} else {
		$list[] = "error: invalid incident id";
	}
	return array('results'=>json_encode($list));
}



/**
 * This returns an array of information about a person: uuid. full_name, gender, years_old, age_group, statusSahana, statusSahanaUpdated, statusTriage, triageCategory, id, peds, orgName, imageWidth, imageHeight, imageUrl, last_seen, comments
 * @param string uuid
 * @return array
 * 
 * STATUS: DEPRECATED ~ going away in v2.0 ~ legacy from DNW
 */
function shn_pls_getPersonData($uuid) {
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
	return array('results'=>json_encode($list));
}



/**
 * Accepts LPF XML v1.5 person reports.
 * @access public
 * @param int lpfXml
 * @return array
 */
function shn_pls_submitLpf($lpfXml) {
	return array('results'=>json_encode($list));
}






