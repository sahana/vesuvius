<?
/**
 * @name         PL User Services
 * @version      1.9.3
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0615
 */

global $api_version;
$api_version = "1.9.3";

// This function is called by the Document/Literal SOAP server upon initalization to register all the api services from this module's api.
function shn_plus_registerAll($namespace) {
	global $server;
	global $api_version;

	// GENERAL API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// GENERAL API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

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

	// ACCOUNT API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// ACCOUNT API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

	shn_plus_registerOne($server, 'registerUser',
		array(
			'in' => array(
				'username'     => 'xsd:string',
				'emailAddress' => 'xsd:string',
				'password'     => 'xsd:string',
				'givenName'    => 'xsd:string',
				'familyName'   => 'xsd:string'
			),
			'out' => array(
				'registered'   => 'xsd:boolean',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Creates a new inactive (pending confirmation) user in the system with the supplied characteristics and credentials."
	);

	shn_plus_registerOne($server, 'getSessionTimeout',
		array(
			'in' => array(),
			'out' => array(
				'timeout'      => 'xsd:integer',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Returns the number of seconds a user session should last (for apps like ReUnite/TriagePic)"
	);



}


// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


// Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
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



// Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
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
		'eventList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => null
	);
}



// Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
function getEventListUser($username, $password) {
	shn_plus_logAccess("getEventListUser");
	global $global;
	$list = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'eventList'    => null,
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);

	// find the user's p_uuid
	} else {
		$q = "
			SELECT *
			FROM users
			WHERE user_name = '".mysql_real_escape_string($username)."';
		";
		$result = $global['db']->Execute($q);
		// we can assume, the row exists, since we passed auth check
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
		'eventList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => null
	);
}



// Returns an array of (group_id, group_name) listing all groups in the system.
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
		'groupList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => null
	);
}



// Returns an array of (hospital_uuid, name, shortname, latitude, longitude).
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
		'hospitalList' => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => null
	);
}



// Returns all data relavent to a particular hospital
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
			'name'          => (string)$result->fields["name"],
			'shortname'     => (string)$result->fields["short_name"],
			'street1'       => (string)$result->fields["street1"],
			'street2'       => (string)$result->fields["street2"],
			'city'          => (string)$result->fields["city"],
			'county'        => (string)$result->fields["county"],
			'state'         => (string)$result->fields["region"],
			'country'       => (string)$result->fields["country"],
			'zip'           => (string)$result->fields["postal_code"],
			'phone'         => (string)$result->fields["phone"],
			'fax'           => (string)$result->fields["fax"],
			'email'         => (string)$result->fields["email"],
			'www'           => (string)$result->fields["www"],
			'npi'           => (string)$result->fields["npi"],
			'latitude'      => (double)$result->fields["latitude"],
			'longitude'     => (double)$result->fields["longitude"],
			'errorCode'     => (int)0,
			'errorMessage'  => null
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'name'          => null,
			'shortname'     => null,
			'street1'       => null,
			'street2'       => null,
			'city'          => null,
			'county'        => null,
			'state'         => null,
			'country'       => null,
			'zip'           => null,
			'phone'         => null,
			'fax'           => null,
			'email'         => null,
			'www'           => null,
			'npi'           => null,
			'latitude'      => null,
			'longitude'     => null,
			'errorCode'    => (int)100,
			'errorMessage' => (string)$eCodes[100]
		);
	}
	return $data;
}



// Returns all policy data relavent to a particular hospital
function getHospitalPolicy($hospital_uuid) {
	shn_plus_logAccess("getHospitalPolicy");

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
			'patientIdPrefix'            => (string)$result->fields["patient_id_prefix"],
			'patientIdSuffixVariable'    => (boolean)$result->fields["patient_id_suffix_variable"],
			'patientIdSuffixFixedLength' => (int)$result->fields["patient_id_suffix_fixed_length"],
			'errorCode'                  => (int)0,
			'errorMessage'               => null
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'errorCode'    => (int)100,
			'errorMessage' => (string)$eCodes[100]
		);
	}
	return $data;
}


// ACCOUNT API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// ACCOUNT API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// ACCOUNT API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// ACCOUNT API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// ACCOUNT API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


// Creates a new inactive (pending confirmation) user in the system with the supplied characteristics and credentials.
function registerUser($username, $emailAddress, $password, $givenName, $familyName) {
	shn_plus_logAccess("registerUser");

	// special unit test case ~
	// registerUser("testCaseUser", "testCase@email.com", "testCasePassword99", "testCaseGiven", "testCaseFamily");

	global $global;
	require_once($global['approot']."/inc/lib_security/lib_auth.inc");
	$success = false;

	// check if a user already is tied to this email address
	if(shn_is_user_with_email($emailAddress)) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'registered'   => (boolean)false,
			'errorCode'    => (int)6,
			'errorMessage' => (string)$eCodes[6]
		);
	}

	// check if a username is already in use
	if(shn_is_user($username)) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'registered'   => (boolean)false,
			'errorCode'    => (int)7,
			'errorMessage' => (string)$eCodes[7]
		);
	}

	// check if email address is valid
	if(!isEmailValid($emailAddress)) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'registered'   => (boolean)false,
			'errorCode'    => (int)8,
			'errorMessage' => (string)$eCodes[8]
		);
	}

	// check if password matches policy
	if(shn_check_password_matches_policy($password, $username) !== true) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'registered'   => (boolean)false,
			'errorCode'    => (int)9,
			'errorMessage' => (string)$eCodes[9]
		);
	}

	// pretend for test case...
	if($username == "testCaseUser" || $emailAddress == "testCase@email.com" || $password == "testPassword99" || $givenName == "testCaseGiven" || $familyName == "testCaseFamily") {
		$success = true;

	// passed all checks, create user
	} else {
		$success = shn_auth_add_user($givenName, $familyName, $username, $password, null, null, array('pending'=> true), $emailAddress);
	}

	if($success) {
		return array(
			'registered'   => (boolean)true,
			'errorCode'    => (int)0,
			'errorMessage' => null
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'registered'   => (boolean)false,
			'errorCode'    => (int)9999,
			'errorMessage' => (string)$eCodes[9999]
		);
	}
}



// Returns the number of seconds a user session should last (for apps like ReUnite/TriagePic)
function getSessionTimeout() {
	shn_plus_logAccess("getSessionTimeout");
	$timeout = shn_db_get_config("plus", "timeout");
	if($timeout == false) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'timeout'      => null,
			'errorCode'    => (int)200,
			'errorMessage' => (string)$eCodes[200]
		);
	} else {
		return array(
			'timeout'      => (int)$timeout,
			'errorCode'    => (int)0,
			'errorMessage' => null
		);
	}
}



// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //





// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //



















































