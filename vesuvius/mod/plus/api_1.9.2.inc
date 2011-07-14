<?
/**
 * @name         PL User Services
 * @version      1.9.2
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0606
 */

global $api_version;
$api_version = "1.9.2";

/**
 * This function is called by the Document/Literal SOAP server upon initalization to register all the api services from this module's api.
 * @access public
 * @param string namespace
 */
function shn_plus_registerAll($namespace) {
	global $server;
	global $api_version;
	shn_plus_registerOne($server, 'version',
		array(
			'in' => array(),
			'out' => array(
				'versionMajor'    => 'xsd:integer',
				'versionMinor'    => 'xsd:integer',
				'versionRevision' => 'xsd:integer',
				'versionString'   => 'xsd:string'
			)
		),
		$namespace,
		"Returns version info (".$api_version.")"
	);

	shn_plus_registerOne($server, 'getEventList',
		array(
			'in' => array(),
			'out' => array(
				'eventList'    => 'xsd:string',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (event_id, parent_id, name, shortname, date, type, latitude, longitude, street, group) listing disaster events' components."
	);

	shn_plus_registerOne($server, 'getEventListUser',
		array(
			'in' => array(
				'username' => 'xsd:string',
				'password' => 'xsd:string'
			),
			'out' => array(
				'eventList'    => 'xsd:string',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (event_id, parent_id, name, shortname, date, type, latitude, longitude, street) listing disaster events' components accessible by a certain user."
	);

	shn_plus_registerOne($server, 'getGroupList',
		array(
			'in' => array(),
			'out' => array(
				'groupList'    => 'xsd:string',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (group_id, group_name) listing all groups in the system."
	);

	shn_plus_registerOne($server, 'getHospitalList',
		array(
			'in' => array(),
			'out' => array(
				'hospitalList' => 'xsd:string',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (hospital_uuid, name, shortname, latitude, longitude)."
	);

	shn_plus_registerOne($server, 'getHospitalData',
		array(
			'in' => array(
				'hospital_uuid' => 'xsd:integer'
			),
			'out' => array(
				'name'          => 'xsd:string',
				'shortname'     => 'xsd:string',
				'street1'       => 'xsd:string',
				'street2'       => 'xsd:string',
				'city'          => 'xsd:string',
				'county'        => 'xsd:string',
				'state'         => 'xsd:string',
				'country'       => 'xsd:string',
				'zip'           => 'xsd:string',
				'phone'         => 'xsd:string',
				'fax'           => 'xsd:string',
				'email'         => 'xsd:string',
				'www'           => 'xsd:string',
				'npi'           => 'xsd:string',
				'latitude'      => 'xsd:string',
				'longitude'     => 'xsd:string',
				'errorCode'     => 'xsd:integer',
				'errorMessage'  => 'xsd:string'
			)
		),
		$namespace,
		"Returns all data relavent to a perticular hospital."
	);

	shn_plus_registerOne($server, 'getHospitalPolicy',
		array(
			'in' => array(
				'hospital_uuid' => 'xsd:integer'
			),
			'out' => array(
				'patientIdPrefix'            => 'xsd:string',
				'patientIdSuffixVariable'    => 'xsd:boolean',
				'patientIdSuffixFixedLength' => 'xsd:integer',
				'errorCode'                  => 'xsd:integer',
				'errorMessage'               => 'xsd:string'
			)
		),
		$namespace,
		"Returns all policy data relavent to a particular hospital."
	);
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
	global $api_version;
	shn_plus_logAccess("version");

	$e        = explode(".", $api_version);
	$major    = $e[0];
	$minor    = $e[1];
	$revision = $e[2];

	return array(
		'versionMajor'    => (int)$major,
		'versionMinor'    => (int)$minor,
		'versionRevision' => (int)$revision,
		'versionString'   => (string)$api_version
	);
}



/**
* Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
* @return array
*/
function getEventList() {
	shn_plus_logAccess("getEventList");
	global $global;
	$list = array();
	$q = "
		SELECT *
		FROM incident
		ORDER BY `default` DESC, name ASC;
	";
	$result = $global['db']->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'incident_id' => $result->fields["incident_id"],
			'parent_id'   => $result->fields["parent_id"],
			'name'        => $result->fields["name"],
			'shortname'   => $result->fields["shortname"],
			'date'        => $result->fields["date"],
			'type'        => $result->fields["type"],
			'latitude'    => $result->fields["latitude"],
			'longitude'   => $result->fields["longitude"],
			'street'      => $result->fields["street"],
			'group'       => $result->fields["private_group"]
		);
		$result->MoveNext();
	}
	return array(
		'eventList'    => json_encode($list),
		'errorCode'    => 0,
		'errorMessage' => null
	);
}



/**
* Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
* @return array
*/
function getEventListUser($username, $password) {
	shn_plus_logAccess("getEventListUser");
	global $global;
	$list = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array('eventList'=>null, 'errorCode'=>$status, 'errorMessage'=>$eCodes[$status]);

	// find the user's p_uuid
	} else {
		$q = "
			SELECT *
			FROM users
			WHERE user_name = '".mysql_real_escape_string($username)."';
		";
		$result = $global['db']->Execute($q);
		// re can assume, the row exists, since we passed auth check
		$p_uuid = $result->fields["p_uuid"];
	}

	// get a list of all public events and events where the user has access
	$q = "
		SELECT *
		FROM incident i
		LEFT JOIN sys_user_to_group s ON i.private_group = s.group_id
		LEFT JOIN users u ON u.p_uuid = s.p_uuid
		WHERE i.private_group is null
		OR (
			s.group_id = i.private_group
			and s.p_uuid = u.p_uuid
			and u.p_uuid = '".$p_uuid."'
		);
	";
	$result = $global['db']->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'incident_id' => $result->fields["incident_id"],
			'parent_id'   => $result->fields["parent_id"],
			'name'        => $result->fields["name"],
			'shortname'   => $result->fields["shortname"],
			'date'        => $result->fields["date"],
			'type'        => $result->fields["type"],
			'latitude'    => $result->fields["latitude"],
			'longitude'   => $result->fields["longitude"],
			'street'      => $result->fields["street"],
			'group'       => $result->fields["private_group"]
		);
		$result->MoveNext();
	}
	return array(
		'eventList'    => json_encode($list),
		'errorCode'    => 0,
		'errorMessage' => null
	);
}



/**
* Returns an array of (group_id, group_name) listing all groups in the system.
* @return array
*/
function getGroupList() {
	shn_plus_logAccess("getGroupList");
	global $global;
	$list = array();
	$q = "
		SELECT *
		FROM sys_user_groups
		ORDER BY group_id ASC;
	";
	$result = $global['db']->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'group_id'  => $result->fields["group_id"],
			'group_name'=> $result->fields["group_name"]
		);
		$result->MoveNext();
	}
	return array(
		'groupList'    => json_encode($list),
		'errorCode'    => 0,
		'errorMessage' => null
	);
}




/**
* Returns an array of (hospital_uuid, name, shortname, latitude, longitude).
* @return array
*/
function getHospitalList() {
	shn_plus_logAccess("getHospitalList");
	global $global;
	$list = array();
	$q = "
		SELECT *
		FROM hospital
		ORDER BY `hospital_uuid` ASC;
	";
	$result = $global['db']->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'hospital_uuid' => $result->fields["hospital_uuid"],
			'npi'           => $result->fields["npi"],
			'name'          => $result->fields["name"],
			'shortname'     => $result->fields["short_name"],
			'latitude'      => $result->fields["latitude"],
			'longitude'     => $result->fields["longitude"],
		);
		$result->MoveNext();
	}
	return array(
		'hospitalList' => json_encode($list),
		'errorCode'    => 0,
		'errorMessage' => null
	);
}



/**
* Returns all data relavent to a particular hospital
* @return array
*/
function getHospitalData($hospital_uuid) {
	shn_plus_logAccess("getHospitalData");

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'name'          => $result->fields["name"],
			'shortname'     => $result->fields["short_name"],
			'street1'       => $result->fields["street1"],
			'street2'       => $result->fields["street2"],
			'city'          => $result->fields["city"],
			'county'        => $result->fields["county"],
			'state'         => $result->fields["region"],
			'country'       => $result->fields["country"],
			'zip'           => $result->fields["postal_code"],
			'phone'         => $result->fields["phone"],
			'fax'           => $result->fields["fax"],
			'email'         => $result->fields["email"],
			'www'           => $result->fields["www"],
			'npi'           => $result->fields["npi"],
			'latitude'      => $result->fields["latitude"],
			'longitude'     => $result->fields["longitude"],
			'errorCode'     => 0,
			'errorMessage'  => null
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'errorCode'    => 100,
			'errorMessage' => $eCodes[100]
		);
	}
	return $data;
}




/**
* Returns all policy data relavent to a particular hospital
* @return array
*/
function getHospitalPolicy($hospital_uuid) {
	shn_plus_logAccess("getHospitalData");

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'patientIdPrefix'            => $result->fields["patient_id_prefix"],
			'patientIdSuffixVariable'    => (boolean)$result->fields["patient_id_suffix_variable"],
			'patientIdSuffixFixedLength' => (int)$result->fields["patient_id_suffix_fixed_length"],
			'errorCode'     => (int)0,
			'errorMessage'  => null
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'errorCode'    => 100,
			'errorMessage' => $eCodes[100]
		);
	}
	return $data;
}



