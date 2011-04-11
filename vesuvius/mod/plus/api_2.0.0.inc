<?
/**
 * @name         PL User Services
 * @version      2.0.0
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0411
 */


/**
 * This function is called by the Document/Literal SOAP server upon initalization to register all the api services from this module's api.
 * @access public
 * @param string namespace
 */
function shn_plus_registerAll($namespace) {
	global $server;
	shn_plus_registerOne($server, 'version',
		array(
			'in' => array(),
			'out' => array(
				'apiVersion' => 'xsd:string'
			)
		),
		$namespace,
		"Returns version info (2.0.0)"
	);

	shn_plus_registerOne($server, 'getIncidentList',
		array(
			'in' => array(),
			'out' => array(
				'incidentList' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude, street) listing disaster incidents' components."
	);

/*
	shn_plus_register_one($server, 'basicSearch',
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
		"Basic search matching a string and assigned to a particular incident."
	);

	shn_plus_register_one($server, 'basicSearchWithRange',
		array(
			'in' => array(
				'searchString'      => 'xsd:string',
				'incidentShortName' => 'xsd:string',
				'startFrom'         => 'xsd:int',
				'limit'             => 'xsd:int'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"Basic search matching a string and assigned to a particular incident passing back XML and with range restraints."
	);

	shn_plus_register_one($server, 'basicSearchAll',
		array(
			'in' => array(
				'searchString' => 'xsd:string'
			),
			'out' => array(
				'results' => 'xsd:string'
			)
		),
		$namespace,
		"Basic search matching a string across all incidents."
	);

	shn_plus_register_one($server, 'test',
		array(
			'in' => array(
				'x' => 'xsd:integer',
				'y' => 'xsd:integer'
			),
			'out' => array(
				'sum' => 'xsd:integer'
			)
		),
		$namespace,
		"Test function to assist setting up a SOAP client. It returns the summation of the two integers values passed in."
	);

	shn_plus_register_one($server, 'verifyCredentials',
		array(
			'in' => array(
				'email'       => 'xsd:string',
				'password'    => 'xsd:string',
				'api_key'     => 'xsd:string',
				'secret_code' => 'xsd:string'
			),
			'out' => array(
				'passed'      => 'xsd:boolean',
				'secret_code' => 'xsd:string'
			)
		),
		$namespace,
		"Verifies credentials provided. Returns true for valid and false for invalid. 2nd return value is null if sent in as null, the secret_code otherwise on valid."
	);


	shn_plus_register_one($server, 'requestNewPassword',
		array(
			'in' => array(
				'email' => 'xsd:string'
			),
			'out' => array(
				'sent' => 'xsd:boolean'
			)
		),
		$namespace,
		"If the email account is valid, send a change password email. Return value of whether the email account is valid and request sent."
	);


	shn_plus_register_one($server, 'changePassword',
		array(
			'in' => array(
				'email'       => 'xsd:string',
				'oldPassword' => 'xsd:string',
				'newPassword' => 'xsd:string'
			),
			'out' => array(
				'changed' => 'xsd:boolean'
			)
		),
		$namespace,
		"Changes the password for the user provided they supply the correct original password. Returns success of this operation."
	);

	shn_plus_register_one($server, 'askTimeout',
		array(
			'in' => array(),
			'out' => array(
				'timeout' => 'xsd:integer'
			)
		),
		$namespace,
		"Returns the timeout period for applications like ReUnite in seconds."
	);







	shn_plus_register_one($server, 'createUuid',
		array(
			'in' => array(
				'incidentId' => 'xsd:integer'
			),
			'out' => array(
				'uuid' => 'xsd:string'
			)
		),
		$namespace,
		"Returns a single new uuid associated to a specific incident."
	);

	shn_plus_register_one($server, 'createUuidBatch',
		array(
			'in' => array(
				'incidentId' => 'xsd:integer',
				'num'        => 'xsd:integer'
			),
			'out' => array(
				'uuidList' => 'xsd:string'
			)
		),
		$namespace,
		"Returns a batch of new uuids associated to a specific incident."
	);



	shn_plus_register_one($server, 'submitLpfXml',
		array(
			'in' => array(
				'lpfXmlFile' => 'xsd:base64Binary'
			),
			'out' => array(
				'success' => 'xsd:boolean',
				'error'   => 'xsd:string'
			)
		),
		$namespace,
		"Accepts a reported person LPF XML file."
	);
*/
}


// API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


/**
 * Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
 * @return array
 */
function version() {
	shn_plus_logAccess("version");
	return array('apiVersion'=>'2.0.0');
}


/**
* Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
* @return array
*/
function getIncidentList() {
	shn_plus_logAccess("getIncidentList");
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "
		SELECT *
		FROM incident
		ORDER BY `default` DESC, name ASC;
	";
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
	return array('incidentList'=>json_encode($list));
}



/**
 * This a basic search for a person matching a string and assigned to a particular incident.
 * @param  string search_term
 * @param  string incidentShortName
 * @return array search_results
 *
function basicSearch($searchString, $incidentShortName) {
	shn_plus_logAccess("basicSearch");
	global $global;
	$db = $global['db'];
	$termCount = 0;
	$qqq = "";

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
			c.other_comments, c.last_seen
		FROM person_uuid a
		JOIN person_status b USING (p_uuid)
		JOIN image i ON a.p_uuid = i.x_uuid
		JOIN person_details c USING (p_uuid)
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
 * This a basic search for a person matching a string and assigned to a particular incident.
 * @param  string search_term
 * @param  string incidentShortName
 * @return array search_results
 *
function basicSearchWithRange($searchString, $incidentShortName, $startFrom, $limit) {
	shn_plus_logAccess("basicSearchWithRange");
	global $global;
	$db = $global['db'];
	$termCount = 0;
	$list = array();
	$terms = explode(" ", $searchString);
	$qqq = "";

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
			c.other_comments, c.last_seen
		FROM person_uuid a
		JOIN person_status b USING (p_uuid)
		JOIN image i ON a.p_uuid = i.x_uuid
		JOIN person_details c USING (p_uuid)
		JOIN resource_to_incident r ON a.p_uuid = r.x_uuid
		JOIN incident z ON z.incident_id = r.incident_id
		WHERE ".$qqq."
		AND b.isVictim = '1'
		AND r.x_uuid = a.p_uuid
		AND z.shortname = '".$incidentShortName."'
		ORDER BY i.url DESC, b.opt_status DESC
		LIMIT ".$startFrom.", ".$limit.";
	";

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
* This a basic search for a person matching a string across all incidents.
 * @param  string search_term
 * @return array
 *
function basicSearchAll($searchString) {
	shn_plus_logAccess("basicSearchAll");
	global $global;
	$list = null;
	$db = $global['db'];
	$termCount = 0;
	$qqq = "";

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
			c.other_comments, c.last_seen, z.shortname, z.name
	      	FROM person_uuid a
	        JOIN person_status b USING (p_uuid)
	        JOIN image i ON a.p_uuid = i.x_uuid
	        JOIN person_details c USING (p_uuid)
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
 * Returns the number of seconds ReUnite sessions should last.
 * @access public
 * @return integer
 *
function askTimeout() {
	shn_plus_logAccess("askTimeout");

	$timeout = shn_db_get_config("plu s","timeout");
	return array('timeout'=>$timeout);
}







/**
 * returns( true ) when the email and oldPassword match, the newPassword replaces the old password
 * returns( false ) otherwise
 *
 * @access public
 * @return integer
 *
function changePassword($email, $oldPassword, $newPassword) {
	shn_plus_logAccess("shn_plus_changePassword");

	global $global;
	$db = $global['db'];

	$q = "
		SELECT p_uuid, salt
		FROM users
		WHERE user_name = '$email' ;
	";
	$res = $db->Execute($q);
	if($res->EOF){
		return array('changed'=>false); // FAILED ~ no user
	} else {
		$salt   = $res->fields["salt"];
		$p_uuid = $res->fields["p_uuid"];
	}
	$pwd = substr($oldPassword, 0, 4).$salt.substr($oldPassword, 4);
	$password_digest = md5(trim($pwd));
	$q2 = "
		SELECT p_uuid
		FROM users
		WHERE user_name = '$email'
		AND password = '$password_digest' and salt='{$salt}' ;
	";
	$res2 = $db->Execute($q2);
	if(($res2 == null) || ($res2->EOF)){
		return array('changed'=>false); // FAILED challenge
	} else {
		$time = time();
		$new_pwd = substr($newPassword, 0, 4).$salt.substr($newPassword, 4);
		$password_digest = md5(trim($new_pwd));
		$q3 = "
			update users
			set password = '{$password_digest}', changed_timestamp={$time}
			WHERE user_name = '$email' ;
		";
		$res3 = $db->Execute($q3);

		$q4 = "
			update ws_keys
			set password = '".$newPassword."'
			where p_uuid = '".$p_uuid."' ;
		";
		$res4 = $db->Execute($q4);
	}
	return array('changed'=>true);
}










/**
 * This returns a single new uuid associated to a specific incident.
 * @param int incidentId
 * @return string ~ uuid
 *
function createUuid($incidentId) {
	shn_plus_logAccess("createUuid");
	global $global;
	$db = $global['db'];
	$count = 0;
	$q = "
		SELECT incident_id
		FROM incident
		WHERE incident_id = '".$incidentId."';
	";
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
		$q = "
			INSERT into resource_to_incident (incident_id, x_uuid)
			VALUES ('".$incidentId."', '".$uuid."');
		";
		$result = $db->Execute($q);
	} else {
		$uuid = "error: invalid incident id";
	}
	return array('uuid'=>$uuid);
}



/**
 * This returns a batch of new uuids associated to a specific incident.
 * @access public
 * @param int incident
 * @param int num ~ number of id's to create
 * @return array ~ list of new uuid's
 *
function createUuidBatch($incidentId, $num) {
	shn_plus_logAccess("createUuidBatch");
	global $global;
	$db = $global['db'];
	$list = array();
	$count = 0;
	$maxUUIDs = 100;
	$q = "
		SELECT incident_id
		FROM incident
		WHERE incident_id = '".$incidentId."';
	";
	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		// incident exists
		$count = 1;
		$result->MoveNext();
	}
	// if its a valid incident create a uuid and assign it to a incident otherwise error
	if ($count > 0) {
		if ($num > 0 && $num <= $maxUUIDs) {
			include_once $global['approot'].'/inc/lib_uuid.inc';
			for ($i = 0; $i < $num; $i++) {
				$uuid = shn_create_uuid();
				$list[] = array('uuid'=>$uuid);
				$q = "
					INSERT into resource_to_incident (incident_id, x_uuid)
					VALUES ('".$incidentId."', '".$uuid."');
				";
				$result = $db->Execute($q);
			}
		} else {
			$list[] = "error: can only request 1-100 uuid's at a time or you did not match parameter names correctly.";
		}
	} else {
		$list[] = "error: invalid incident id";
	}
	return array('uuidList'=>json_encode($list));
}



/**
 * Accepts LPF XML v1.6+ person reports.
 * @access public
 * @param int lpfXml
 * @return array
 *
function submitLpfXml($lpfXmlFile) {
	shn_plus_logAccess("submitLpfXml");

	$a = xml2array(base64_decode($lpfXmlFile));

	require_once("../mod/mpres/class.lpfPatient.php");
	require_once("../mod/mpres/class.imageAttachment.php");
	require_once("../inc/lib_uuid.inc");
	require_once("../inc/lib_image.inc");
	$person = new lpfPatient();

	$person->uuid         =                   $a['lpfContent']['person']['personId'];
	$person->shortName    = strtolower(       $a['lpfContent']['person']['eventShortName']);
	$person->firstName    =                   $a['lpfContent']['person']['firstName'];
	$person->familyName   =                   $a['lpfContent']['person']['familyName'];
	$person->gender       = substr(strtolower($a['lpfContent']['person']['gender']), 0, 3);
	$person->age          =                   $a['lpfContent']['person']['estimatedAgeInYears'];
	$person->sahanaStatus = substr(strtolower($a['lpfContent']['person']['status']['healthStatus']), 0, 3);
	$person->comments     =                   $a['lpfContent']['person']['notes'];


	// check if the event being reported to is closed...
	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."';
	";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$closed = $row['closed'];

	// event is closed, report error.....
	if($closed != null) {
		$success = false;
		$error = "Error #21: The current event is closed to new person reports.";

	// event is still open, insert person, report success....
	} else {
		$person->insertPersonXML();

		$messages = $person->uuid."\n";

		// save the image and thumbnail
		if ($a['lpfContent']['person']['photo']['data'] != null) {
			$newFilename   = $a['lpfContent']['person']['photo']['fileName'];
			$fullzizePath  = "../../www/tmp/mpres_cache/".$newFilename;
			$thumbnailPath = "../../www/tmp/mpres_cache/thumb_".$newFilename;
			$fullzizeUrl   = "/tmp/mpres_cache/".$newFilename;
			$thumbnailUrl  = "/tmp/mpres_cache/thumb_".$newFilename;

			file_put_contents($fullzizePath, base64_decode($a['lpfContent']['person']['photo']['data']));
			shn_image_resize_height($fullzizePath, $thumbnailPath, 320);
			// make the files world writeable for other applications
			chmod($fullzizePath,  0777);
			chmod($thumbnailPath, 0777);

			$info = getimagesize($fullzizePath);
			$width = $info[0];
			$height = $info[1];

			$person->images[] = new imageAttachment($newFilename, NULL, $height, $width, 'jpg', $fullzizeUrl, $thumbnailUrl, $f);
			$messages .= "found image attachment>>(".$f.")\n";
			$messages .= "fullzize url>>>(".$fullzizeUrl.")\n";
			$messages .= "thumbnail url>>(".$thumbnailUrl.")\n";
		}

		$success = true;
		$error = "no error";
	}
	return array('success'=>$success, 'error'=>$error);
}

*/

