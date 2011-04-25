<?
/**
 * @name         PL User Services
 * @version      1.9.0
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
		"Returns version info (1.9.1)"
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
	shn_plus_logAccess("version");
	return array('apiVersion'=>'1.9.1');
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
* Returns an array of (hospital_uuid, name, shortname, latitude, longitude).
* @return array
*/
function getHospitalList() {
	shn_plus_logAccess("getHospitalList");
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "
		SELECT *
		FROM hospital
		ORDER BY `hospital_uuid` ASC;
	";
	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'hospital_uuid' => $result->fields["hospital_uuid"],
			'npi'           => $result->fields["npi"],
			'name'          => $result->fields["name"],
			'shortname'     => $result->fields["short_name"],
			'latitude'      => $result->fields["latitude"],
			'longitude'     => $result->fields["longitude"]
		);
		$result->MoveNext();
	}
	return array('hospitalList'=>json_encode($list), 'errorCode'=>0, 'errorMessage'=>null);
}



/**
* Returns all data relavent to a particular hospital
* @return array
*/
function getHospitalData($hospital_uuid) {
	shn_plus_logAccess("getHospitalData");

	global $global;
	$error = true;
	$db    = $global['db'];

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".$hospital_uuid."'
		LIMIT 1;
	";
	$result = $db->Execute($q);
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
		$data = array(
			'errorCode'     => UNDEFINED_HOSPITAL_CODE,
			'errorMessage'  => UNDEFINED_HOSPITAL_MSG
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
	$db    = $global['db'];

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".$hospital_uuid."'
		LIMIT 1;
	";
	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'patientIdPrefix'            => $result->fields["patient_id_prefix"],
			'patientIdSuffixVariable'    => (boolean)$result->fields["patient_id_suffix_variable"],
			'patientIdSuffixFixedLength' => $result->fields["patient_id_suffix_fixed_length"],
			'errorCode'     => 0,
			'errorMessage'  => null
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$data = array(
			'errorCode'     => UNDEFINED_HOSPITAL_CODE,
			'errorMessage'  => UNDEFINED_HOSPITAL_MSG
		);
	}
	return $data;
}



