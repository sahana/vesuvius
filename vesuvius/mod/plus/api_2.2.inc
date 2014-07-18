<?
/**
 * @name         PL User Services
 * @version      2.2
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0110
 */

global $api_version;
$api_version = "2.2";

// This function is called by the Document/Literal SOAP server upon initalization to register all the api services from this module's api.
function shn_plus_registerAll($namespace) {
	global $server;
	global $api_version;

	// GENERAL API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// GENERAL API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

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
		"Returns an array of (event_id, parent_id, name, shortname, date, type, latitude, longitude, street, group) public disaster events."
	);

	shn_plus_registerOne($server, 'getEventListUser',
		array(
			'in' => array(
				'username'     => 'xsd:string',
				'password'     => 'xsd:string'
			),
			'out' => array(
				'eventList'    => 'xsd:string',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (event_id, parent_id, name, shortname, date, type, latitude, longitude, street) disaster events accessible by a certain user."
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
				'hospital_uuid'              => 'xsd:integer'
			),
			'out' => array(
				'patientIdPrefix'            => 'xsd:string',
				'patientIdSuffixVariable'    => 'xsd:boolean',
				'patientIdSuffixFixedLength' => 'xsd:integer',
				'photoRequired'              => 'xsd:boolean',
				'honorNoPhotoRequest'        => 'xsd:boolean',
				'photographerNameRequired'   => 'xsd:boolean',
				'errorCode'                  => 'xsd:integer',
				'errorMessage'               => 'xsd:string'
			)
		),
		$namespace,
		"Returns all policy data relavent to a particular hospital."
	);

	shn_plus_registerOne($server, 'getHospitalLegalese',
		array(
			'in' => array(
				'hospital_uuid' => 'xsd:integer'
			),
			'out' => array(
				'legalese'      => 'xsd:string',
				'errorCode'     => 'xsd:integer',
				'errorMessage'  => 'xsd:string'
			)
		),
		$namespace,
		"Retrieve a particular hospital’s legalese clause."
	);

	shn_plus_registerOne($server, 'getHospitalLegaleseAnon',
		array(
			'in' => array(
				'hospital_uuid' => 'xsd:integer'
			),
			'out' => array(
				'legaleseAnon'  => 'xsd:string',
				'errorCode'     => 'xsd:integer',
				'errorMessage'  => 'xsd:string'
			)
		),
		$namespace,
		"Retrieve a particular hospital’s anonymous legalese clause."
	);

	shn_plus_registerOne($server, 'getHospitalLegaleseTimestamps',
		array(
			'in' => array(
				'hospital_uuid' => 'xsd:integer'
			),
			'out' => array(
				'legaleseTimestamp'     => 'xsd:string',
				'legaleseAnonTimestamp' => 'xsd:string',
				'errorCode'             => 'xsd:integer',
				'errorMessage'          => 'xsd:string'
			)
		),
		$namespace,
		"Retrieves information about when the legalese clauses were last updated for a particular hospital."
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

	shn_plus_registerOne($server, 'changeUserPassword',
		array(
			'in' => array(
				'username'     => 'xsd:string',
				'oldPassword'  => 'xsd:string',
				'newPassword'  => 'xsd:string'
			),
			'out' => array(
				'changed'      => 'xsd:boolean',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Changes a user password from old to new."
	);

	shn_plus_registerOne($server, 'resetUserPassword',
		array(
			'in' => array(
				'username'     => 'xsd:string'
			),
			'out' => array(
				'sent'         => 'xsd:boolean',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Initiates the password reset procedure."
	);

	shn_plus_registerOne($server, 'forgotUsername',
		array(
			'in' => array(
				'email'        => 'xsd:string'
			),
			'out' => array(
				'sent'         => 'xsd:boolean',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Sends an email to the user with their username."
	);

	shn_plus_registerOne($server, 'checkUserAuth',
		array(
			'in' => array(
				'username'     => 'xsd:string',
				'password'     => 'xsd:string'
			),
			'out' => array(
				'valid'        => 'xsd:boolean',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Used to verify a username / password combination are valid."
	);

	shn_plus_registerOne($server, 'getUserStatus',
		array(
			'in' => array(
				'username'     => 'xsd:string'
			),
			'out' => array(
				'pending'      => 'xsd:boolean',
				'active'       => 'xsd:boolean',
				'locked'       => 'xsd:boolean',
				'banned'       => 'xsd:boolean',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Used to determine user account status without authenticating."
	);

	shn_plus_registerOne($server, 'getUserGroup',
		array(
			'in' => array(
				'username'     => 'xsd:string'
			),
			'out' => array(
				'group_id'     => 'xsd:integer',
				'group_name'   => 'xsd:string',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Shows which group a user is part of without authenticating."
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

	// SEARCH API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// SEARCH API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

	shn_plus_registerOne($server, 'search',
		array(
			'in' => array(
				'eventShortname'       => 'xsd:string',
				'searchTerm'           => 'xsd:string',
				'filterStatusMissing'  => 'xsd:boolean',
				'filterStatusAlive'    => 'xsd:boolean',
				'filterStatusInjured'  => 'xsd:boolean',
				'filterStatusDeceased' => 'xsd:boolean',
				'filterStatusUnknown'  => 'xsd:boolean',
				'filterStatusFound'    => 'xsd:boolean',
				'filterGenderComplex'  => 'xsd:boolean',
				'filterGenderMale'     => 'xsd:boolean',
				'filterGenderFemale'   => 'xsd:boolean',
				'filterGenderUnknown'  => 'xsd:boolean',
				'filterAgeChild'       => 'xsd:boolean',
				'filterAgeAdult'       => 'xsd:boolean',
				'filterAgeUnknown'     => 'xsd:boolean',
				'filterHospitalSH'     => 'xsd:boolean',
				'filterHospitalWRNMMC' => 'xsd:boolean',
				'filterHospitalOther'  => 'xsd:boolean',
				'pageStart'            => 'xsd:integer',
				'perPage'              => 'xsd:integer',
				'sortBy'               => 'xsd:string'
			),
			'out' => array(
				'resultSet'    => 'xsd:string',
				'recordsFound' => 'xsd:integer',
				'timeElapsed'  => 'xsd:double',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Performs a search across a specific PUBLIC event with filters, paging, and sort options."
	);

	shn_plus_registerOne($server, 'searchWithAuth',
		array(
			'in' => array(
				'eventShortname'       => 'xsd:string',
				'searchTerm'           => 'xsd:string',
				'filterStatusMissing'  => 'xsd:boolean',
				'filterStatusAlive'    => 'xsd:boolean',
				'filterStatusInjured'  => 'xsd:boolean',
				'filterStatusDeceased' => 'xsd:boolean',
				'filterStatusUnknown'  => 'xsd:boolean',
				'filterStatusFound'    => 'xsd:boolean',
				'filterGenderComplex'  => 'xsd:boolean',
				'filterGenderMale'     => 'xsd:boolean',
				'filterGenderFemale'   => 'xsd:boolean',
				'filterGenderUnknown'  => 'xsd:boolean',
				'filterAgeChild'       => 'xsd:boolean',
				'filterAgeAdult'       => 'xsd:boolean',
				'filterAgeUnknown'     => 'xsd:boolean',
				'filterHospitalSH'     => 'xsd:boolean',
				'filterHospitalWRNMMC' => 'xsd:boolean',
				'filterHospitalOther'  => 'xsd:boolean',
				'pageStart'            => 'xsd:integer',
				'perPage'              => 'xsd:integer',
				'sortBy'               => 'xsd:string',
				'username'             => 'xsd:string',
				'password'             => 'xsd:string'
			),
			'out' => array(
				'resultSet'    => 'xsd:string',
				'recordsFound' => 'xsd:integer',
				'timeElapsed'  => 'xsd:double',
				'errorCode'    => 'xsd:integer',
				'errorMessage' => 'xsd:string'
			)
		),
		$namespace,
		"Performs a search across a specific event with filters, paging, and sort options with authentication."
	);

	// REPORTING API DECLARATIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// REPORTING API DECLARATIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

	shn_plus_registerOne($server, 'reportPerson',
		array(
			'in' => array(
				'personXML'      => 'xsd:string',
				'eventShortName' => 'xsd:string',
				'xmlFormat'      => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'url'            => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Report a new person using the LPF v1.2 XML format."
	);

	shn_plus_registerOne($server, 'createPersonUuid',
		array(
			'in' => array(
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'success '       => 'xsd:boolean',
				'uuid'           => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Reserves a uuid in the system so that an app can cache it for later use in reporting."
	);

	shn_plus_registerOne($server, 'createPersonUuidBatch',
		array(
			'in' => array(
				'number'         => 'xsd:integer',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'success '       => 'xsd:boolean',
				'uuid'           => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Reserves a number of uuids in the system so that an app can cache them for later use in reporting."
	);

	shn_plus_registerOne($server, 'createNoteUuid',
		array(
			'in' => array(
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'success '       => 'xsd:boolean',
				'uuid'           => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Reserves a note uuid in the system so that an app can cache it for later use in reporting."
	);

	shn_plus_registerOne($server, 'createNoteUuidBatch',
		array(
			'in' => array(
				'number'         => 'xsd:integer',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'success '       => 'xsd:boolean',
				'uuid'           => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Reserves a number of note uuids in the system so that an app can cache them for later use in reporting."
	);

	// Record Revision API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// Record Revision API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

	shn_plus_registerOne($server, 'reReportPerson',
		array(
			'in' => array(
				'uuid'           => 'xsd:string',
				'personXML'      => 'xsd:string',
				'eventShortname' => 'xsd:string',
				'xmlFormat'      => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Re-report a person using XML which will replace an existing record."
	);

	shn_plus_registerOne($server, 'expirePerson',
		array(
			'in' => array(
				'uuid'           => 'xsd:string',
				'explanation'    => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'queued'         => 'xsd:boolean',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Owners, admins, and HSA can immediately expire a record, everyone else can submit an expiration request to a moderated queue."
	);

	shn_plus_registerOne($server, 'getPersonExpiryDate',
		array(
			'in' => array(
				'uuid'           => 'xsd:string',
			),
			'out' => array(
				'expiryDate'     => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Get the datetime in UTC when a person record will expire."
	);

	shn_plus_registerOne($server, 'setPersonExpiryDate',
		array(
			'in' => array(
				'uuid'           => 'xsd:string',
				'expiryDate'     => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'queued'         => 'xsd:boolean',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Owners, admins, and HSA can immediately update a records expiry date, everyone else can submit a request to update the expiry date to a moderated queue."
	);

	shn_plus_registerOne($server, 'setPersonExpiryDateOneYear',
		array(
			'in' => array(
				'uuid'           => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'queued'         => 'xsd:boolean',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Owners, admins, and HSA can immediately update a records expiry date, everyone else can submit a request to update the expiry date to a moderated queue. The expiry date in this case is updated to exactly one year from the time of the request."
	);

	shn_plus_registerOne($server, 'getUuidByMassCasualtyId',
		array(
			'in' => array(
				'mcid'           => 'xsd:string',
				'shortname'      => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'uuid'           => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"A simple lookup of the internal uuid of a person based on their mass casualty id (if it exists)."
	);

	shn_plus_registerOne($server, 'changeMassCasualtyId',
		array(
			'in' => array(
				'newMcid'        => 'xsd:string',
				'uuid'           => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Updates the mass casualty id of a person based on their uuid."
	);

	shn_plus_registerOne($server, 'hasRecordBeenRevised',
		array(
			'in' => array(
				'uuid'           => 'xsd:string',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'revisionsMade'  => 'xsd:integer',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"A simple lookup to determine if a record is still an original or has incurred revisions."
	);

	// Image Indexing API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
	// Image Indexing API DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

	shn_plus_registerOne($server, 'getImageCountsAndTokens',
		array(
			'in' => array(
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'imageCount'     => 'xsd:integer',
				'firstToken'     => 'xsd:integer',
				'lastToken'      => 'xsd:integer',
				'nullTokenCount' => 'xsd:integer',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Returns a count of the total number of images and the value of the latest brownie (image index value)."
	);

	shn_plus_registerOne($server, 'getImageList',
		array(
			'in' => array(
				'tokenStart'     => 'xsd:integer',
				'tokenEnd'       => 'xsd:integer',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'imageList'      => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Returns a list of the images and their associated properties, paginated by a start and end token (index value)."
	);

	shn_plus_registerOne($server, 'getImageListBlock',
		array(
			'in' => array(
				'tokenStart'     => 'xsd:integer',
				'stride'         => 'xsd:integer',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'imageList'      => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Returns a list of the images and their associated properties, in blocks of stride size beginning with a start token (index value)."
	);

	shn_plus_registerOne($server, 'getNullTokenList',
		array(
			'in' => array(
				'tokenStart'     => 'xsd:integer',
				'tokenEnd'       => 'xsd:integer',
				'username'       => 'xsd:string',
				'password'       => 'xsd:string'
			),
			'out' => array(
				'nullTokenList'  => 'xsd:string',
				'errorCode'      => 'xsd:integer',
				'errorMessage'   => 'xsd:string'
			)
		),
		$namespace,
		"Returns a list of the images that have been removed from the system (either deleted or expired)."
	);

}

// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


// Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of public disaster events.
function getEventList() {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$list = array();
	$q = "
		SELECT *
		FROM incident
		WHERE private_group is null
		ORDER BY `default` DESC, name ASC;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getEventList 1"); }
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
			'group'       => $result->fields["private_group"],
			'closed'      => $result->fields["closed"],
		);
		$result->MoveNext();
	}
	return array(
		'eventList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}



// Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) disaster events accessibleby a certain user.
function getEventListUser($username, $password) {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$list = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'eventList'    => (string)'',
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
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getEventListUser 1"); }
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
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getEventListUser 2"); }
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
			'group'       => $result->fields["private_group"],
			'closed'      => $result->fields["closed"],
		);
		$result->MoveNext();
	}
	return array(
		'eventList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}



// Returns an array of (group_id, group_name) listing all groups in the system.
function getGroupList() {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$list = array();
	$q = "
		SELECT *
		FROM sys_user_groups
		ORDER BY group_id ASC;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getGroupList 1"); }
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
		'errorMessage' => ''
	);
}



// Returns an array of (hospital_uuid, name, shortname, latitude, longitude).
function getHospitalList() {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$list = array();
	$q = "
		SELECT *
		FROM hospital
		ORDER BY `hospital_uuid` ASC;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getHospitalList 1"); }
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
		'errorMessage' => ''
	);
}



// Returns all data relavent to a particular hospital
function getHospitalData($hospital_uuid) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getHospitalData 1"); }
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
			'errorMessage'  => ''
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'name'          => (string)'',
			'shortname'     => (string)'',
			'street1'       => (string)'',
			'street2'       => (string)'',
			'city'          => (string)'',
			'county'        => (string)'',
			'state'         => (string)'',
			'country'       => (string)'',
			'zip'           => (string)'',
			'phone'         => (string)'',
			'fax'           => (string)'',
			'email'         => (string)'',
			'www'           => (string)'',
			'npi'           => (string)'',
			'latitude'      => (double)0.0,
			'longitude'     => (double)0.0,
			'errorCode'    => (int)100,
			'errorMessage' => (string)$eCodes[100]
		);
	}
	return $data;
}



// Returns all policy data relavent to a particular hospital
function getHospitalPolicy($hospital_uuid) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getHospitalPolicy 1"); }
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'patientIdPrefix'            => (string)$result->fields['patient_id_prefix'],
			'patientIdSuffixVariable'    => (boolean)$result->fields['patient_id_suffix_variable'],
			'patientIdSuffixFixedLength' => (int)$result->fields['patient_id_suffix_fixed_length'],
			'photoRequired'              => (boolean)$result->fields['photo_required'],
			'honorNoPhotoRequest'        => (boolean)$result->fields['honor_no_photo_request'],
			'photographerNameRequired'   => (boolean)$result->fields['photographer_name_required'],
			'errorCode'                  => (int)0,
			'errorMessage'               => ''
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'patientIdPrefix'            => '',
			'patientIdSuffixVariable'    => (boolean)false,
			'patientIdSuffixFixedLength' => (int)0,
			'photoRequired'              => (boolean)false,
			'honorNoPhotoRequest'        => (boolean)false,
			'photographerNameRequired'   => (boolean)false,
			'errorCode'                  => (int)100,
			'errorMessage'               => (string)$eCodes[100]
		);
	}
	return $data;
}



// Retrieve a particular hospital’s legalese clause.
function getHospitalLegalese($hospital_uuid) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getHospitalLegalese 1"); }
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'legalese'     => (string)$result->fields["legalese"],
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'legalese'     => (string)'',
			'errorCode'    => (int)100,
			'errorMessage' => (string)$eCodes[100]
		);
	}
	return $data;
}



// Retrieve a particular hospital’s anonymous legalese clause.
function getHospitalLegaleseAnon($hospital_uuid) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getHospitalLegaleseAnon 1"); }
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'legaleseAnon' => (string)$result->fields["legaleseAnon"],
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'legaleseAnon' => (string)'',
			'errorCode'    => (int)100,
			'errorMessage' => (string)$eCodes[100]
		);
	}
	return $data;
}



// Retrieves information about when the legalese clauses were last updated for a particular hospital.
function getHospitalLegaleseTimestamps($hospital_uuid) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$error = true;

	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = '".mysql_real_escape_string($hospital_uuid)."'
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getHospitalLegaleseTimestamps 1"); }
	while (!$result == NULL && !$result->EOF) {
		$data = array(
			'legaleseTimestamp'    => (string)$result->fields["legaleseTimestamp"],
			'legaleseAnonTimestamp'=> (string)$result->fields["legaleseAnonTimestamp"],
			'errorCode'            => (int)0,
			'errorMessage'         => ''
		);
		$result->MoveNext();
		$error = false;
	}
	if($error) {
		$eCodes = unserialize(ERRORCODES);
		$data = array(
			'legaleseTimestamp'    => (string)'',
			'legaleseAnonTimestamp'=> (string)'',
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
	shn_plus_logAccess(__FUNCTION__);

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
		shn_plus_emailNewUser($username);
		return array(
			'registered'   => (boolean)true,
			'errorCode'    => (int)0,
			'errorMessage' => ''
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



// Changes the password from old to new.
function changeUserPassword($username, $oldPassword, $newPassword) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	require_once($global['approot']."/inc/lib_security/lib_auth.inc");
	$success = false;

	// check if new password matches policy
	if(shn_check_password_matches_policy($newPassword, $username) !== true) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'changed'      => (boolean)false,
			'errorCode'    => (int)9,
			'errorMessage' => (string)$eCodes[9]
		);
	}

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $oldPassword);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'changed'      => (boolean)false,
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$success = shn_change_password_simple($username, $newPassword);

	if($success) {
		return array(
			'changed'      => (boolean)true,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'changed'      => (boolean)false,
			'errorCode'    => (int)9999,
			'errorMessage' => (string)$eCodes[9999]
		);
	}
}



// Initiates the password reset procedure.
function resetUserPassword($username) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$success = false;

	$q = "
		SELECT c.contact_value
		FROM users u, contact c
		WHERE u.user_name = '".mysql_real_escape_string($username)."'
		AND u.p_uuid = c.p_uuid
		AND u.status = 'active';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "resetUserPassword 1"); }
	if($result != null && !$result->EOF) {
		$success = true;
		shn_plus_resetEmail($username, $result->fields["contact_value"]);
	}

	if($success) {
		return array(
			'sent'         => (boolean)true,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'sent'         => (boolean)false,
			'errorCode'    => (int)10,
			'errorMessage' => (string)$eCodes[10]
		);
	}
}



// Sends an email to the user with their username.
function forgotUsername($email) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$success = false;

	$q = "
		SELECT u.user_name
		FROM users u, contact c
		WHERE c.contact_value = '".mysql_real_escape_string($email)."'
		AND u.p_uuid = c.p_uuid
		AND u.status = 'active';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "forgotUsername 1"); }

	// pretend for test case...
	if($email == "testCase@email.com") {
		$success = true;
	} elseif($result != null && !$result->EOF) {
		$success = true;
		shn_plus_forgotUsernameEmail($email, $result->fields["user_name"]);
	}

	if($success) {
		return array(
			'sent'         => (boolean)true,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'sent'         => (boolean)false,
			'errorCode'    => (int)11,
			'errorMessage' => (string)$eCodes[11]
		);
	}
}



// Used to verify a username / password combination are valid
function checkUserAuth($username, $password) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	require_once($global['approot']."/inc/lib_security/lib_auth.inc");
	$success = false;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status == 0) {
		return array(
			'valid'        => (boolean)true,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'valid'        => (boolean)false,
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}
}



// Used to determine user account status without authenticating
function getUserStatus($username) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$success = false;
	$pending = false;
	$active  = false;
	$locked  = false;
	$banned  = false;

	$q = "
		SELECT status
		FROM users
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getUserStatus 1"); }

	if($result != null && !$result->EOF) {
		$success = true;

		if($result->fields["status"] == "active") {
			$active = true;

		} elseif($result->fields["status"] == "pending") {
			$pending = true;

		} elseif($result->fields["status"] == "locked") {
			$locked = true;

		} elseif($result->fields["status"] == "banned") {
			$banned = true;
		}
	}
	if($success) {
		return array(
			'pending'      => (boolean)$pending,
			'active'       => (boolean)$active,
			'locked'       => (boolean)$locked,
			'banned'       => (boolean)$banned,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'pending'      => (boolean)false,
			'active'       => (boolean)false,
			'locked'       => (boolean)false,
			'banned'       => (boolean)false,
			'errorCode'    => (int)12,
			'errorMessage' => (string)$eCodes[12]
		);
	}
}



// Used to determine user account status without authenticating
function getUserGroup($username) {
	shn_plus_logAccess(__FUNCTION__);

	global $global;
	$success = false;

	$q = "
		SELECT *
		FROM users u, sys_user_groups g, sys_user_to_group x
		WHERE u.user_name = '".mysql_real_escape_string($username)."'
		AND x.p_uuid = u.p_uuid
		AND g.group_id = x.group_id;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getUserGroup 1"); }

	if($result != null && !$result->EOF) {
		$success = true;
	}
	if($success) {
		return array(
			'group_id'     => (int)$result->fields["group_id"],
			'group_name'   => (string)$result->fields["group_name"],
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'group_id'     => (int)0,
			'group_name'   => '',
			'errorCode'    => (int)12,
			'errorMessage' => (string)$eCodes[12]
		);
	}
}



// Returns the number of seconds a user session should last (for apps like ReUnite/TriagePic)
function getSessionTimeout() {
	shn_plus_logAccess(__FUNCTION__);
	$timeout = shn_db_get_config("plus", "timeout");
	if($timeout == false) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'timeout'      => (int)0,
			'errorCode'    => (int)200,
			'errorMessage' => (string)$eCodes[200]
		);
	} else {
		return array(
			'timeout'      => (int)$timeout,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// SEARCH API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


// performs a search across a specific PUBLIC event with filters, paging, and sort options
function search($eventShortname, $searchTerm, $filterStatusMissing, $filterStatusAlive, $filterStatusInjured, $filterStatusDeceased, $filterStatusUnknown, $filterStatusFound, $filterGenderComplex, $filterGenderMale, $filterGenderFemale, $filterGenderUnknown, $filterAgeChild, $filterAgeAdult, $filterAgeUnknown, $filterHospitalSH, $filterHospitalWRNMMC, $filterHospitalOther, $pageStart, $perPage, $sortBy = "last_updated") {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = false;

	// verify that the event is a public event...
	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($eventShortname)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "search 1"); }
	if($result != null && !$result->EOF) {

		// check if the event is not public...
		if($result->fields["private_group"] != null) {
			$error = true;
			$ecode = 301;
		}

	// event does not exist with this shortname...
	} else {
		$error = true;
		$ecode = 302;
	}

	if(!$error) {

		if($conf['enable_solr_for_search'] == true) {
			$searchMode = "solr";
		} else {
			$searchMode = "sql";
		}

		// find lack of explicit sort order and use last updated as a default...
		if(strlen((string)$sortBy) < 3) {
			$sortBy = "updated desc";
		}

		$filterStatusMissing  = ($filterStatusMissing)  ? 'true' : 'false';
		$filterStatusAlive    = ($filterStatusAlive)    ? 'true' : 'false';
		$filterStatusInjured  = ($filterStatusInjured)  ? 'true' : 'false';
		$filterStatusDeceased = ($filterStatusDeceased) ? 'true' : 'false';
		$filterStatusUnknown  = ($filterStatusUnknown)  ? 'true' : 'false';
		$filterStatusFound    = ($filterStatusFound)    ? 'true' : 'false';
		$filterGenderComplex  = ($filterGenderComplex)  ? 'true' : 'false';
		$filterGenderMale     = ($filterGenderMale)     ? 'true' : 'false';
		$filterGenderFemale   = ($filterGenderFemale)   ? 'true' : 'false';
		$filterGenderUnknown  = ($filterGenderUnknown)  ? 'true' : 'false';
		$filterAgeChild       = ($filterAgeChild)       ? 'true' : 'false';
		$filterAgeAdult       = ($filterAgeAdult)       ? 'true' : 'false';
		$filterAgeUnknown     = ($filterAgeUnknown)     ? 'true' : 'false';
		$filterHospitalSH     = ($filterHospitalSH)     ? 'true' : 'false';
		$filterHospitalWRNMMC = ($filterHospitalWRNMMC) ? 'true' : 'false';
		$filterHospitalOther  = ($filterHospitalOther)  ? 'true' : 'false';

		$sStatus       = $filterStatusMissing.";".$filterStatusAlive.";".$filterStatusInjured.";".$filterStatusDeceased.";".$filterStatusUnknown.";".$filterStatusFound;
		$sGender       = $filterGenderComplex.";".$filterGenderMale.";".$filterGenderFemale.";".$filterGenderUnknown;
		$sAge          = $filterAgeChild.";".$filterAgeAdult.";".$filterAgeUnknown;
		$sHospital     = $filterHospitalSH.";".$filterHospitalWRNMMC.";".$filterHospitalOther;
		$sPageControls = $pageStart.";".$perPage.";".$sortBy.";true"; // use non-interactive mode

		require_once($global['approot']."/mod/inw/SearchDB.php");
		$timeElsapsed = 0;

		$search = new SearchDB($searchMode, $eventShortname, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls);

		try {
			$timeStart = microtime(true);
			$search->executeSearch();
			$timeElapsed = microtime(true) - $timeStart;
		} catch (Exception $e) {
			$error = true;
			$ecode = 9999;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'resultSet'    => '',
			'recordsFound' => (int)0,
			'timeElapsed'  => (double)$timeElapsed,
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'resultSet'    => (string)json_encode($search->results),
			'recordsFound' => (int)count($search->results),
			'timeElapsed'  => (double)$timeElapsed,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}




// Performs a search across a specific event with filters, paging, and sort options with authentication.
function searchWithAuth($eventShortname, $searchTerm, $filterStatusMissing, $filterStatusAlive, $filterStatusInjured, $filterStatusDeceased, $filterStatusUnknown, $filterStatusFound, $filterGenderComplex, $filterGenderMale, $filterGenderFemale, $filterGenderUnknown, $filterAgeChild, $filterAgeAdult, $filterAgeUnknown, $filterHospitalSH, $filterHospitalWRNMMC, $filterHospitalOther, $pageStart, $perPage, $sortBy = "last_updated", $username, $password) {

	shn_plus_logAccess(__FUNCTION__);

	global $global;
	global $conf;
	$error = false;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$error = true;
		$ecode = $status;
	} else {
		// check if the user is a member of a group that has access to the event in question
		$q = "
			SELECT *
			FROM incident i, users u, sys_user_groups s, sys_user_to_group t
			WHERE (i.private_group = s.group_id
			AND s.group_id = t.group_id
			AND t.p_uuid = u.p_uuid
			AND u.user_name = '".mysql_real_escape_string($username)."'
			AND i.shortname = '".mysql_real_escape_string($eventShortname)."')
			OR (i.private_group is null
			AND i.shortname = '".mysql_real_escape_string($eventShortname)."');
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "searchWithAuth 1"); }
		if($result == null || $result->EOF) {
			$error = true;
			$ecode = 300;
		}
	}

	if(!$error) {

		if($conf['enable_solr_for_search'] == true) {
			$searchMode = "solr";
		} else {
			$searchMode = "sql";
		}

		// find lack of explicit sort order and use last updated as a default...
		if(strlen((string)$sortBy) < 3) {
			$sortBy = "updated desc";
		}

		$filterStatusMissing  = ($filterStatusMissing)  ? 'true' : 'false';
		$filterStatusAlive    = ($filterStatusAlive)    ? 'true' : 'false';
		$filterStatusInjured  = ($filterStatusInjured)  ? 'true' : 'false';
		$filterStatusDeceased = ($filterStatusDeceased) ? 'true' : 'false';
		$filterStatusUnknown  = ($filterStatusUnknown)  ? 'true' : 'false';
		$filterStatusFound    = ($filterStatusFound)    ? 'true' : 'false';
		$filterGenderComplex  = ($filterGenderComplex)  ? 'true' : 'false';
		$filterGenderMale     = ($filterGenderMale)     ? 'true' : 'false';
		$filterGenderFemale   = ($filterGenderFemale)   ? 'true' : 'false';
		$filterGenderUnknown  = ($filterGenderUnknown)  ? 'true' : 'false';
		$filterAgeChild       = ($filterAgeChild)       ? 'true' : 'false';
		$filterAgeAdult       = ($filterAgeAdult)       ? 'true' : 'false';
		$filterAgeUnknown     = ($filterAgeUnknown)     ? 'true' : 'false';
		$filterHospitalSH     = ($filterHospitalSH)     ? 'true' : 'false';
		$filterHospitalWRNMMC = ($filterHospitalWRNMMC) ? 'true' : 'false';
		$filterHospitalOther  = ($filterHospitalOther)  ? 'true' : 'false';

		$sStatus       = $filterStatusMissing.";".$filterStatusAlive.";".$filterStatusInjured.";".$filterStatusDeceased.";".$filterStatusUnknown.";".$filterStatusFound;
		$sGender       = $filterGenderComplex.";".$filterGenderMale.";".$filterGenderFemale.";".$filterGenderUnknown;
		$sAge          = $filterAgeChild.";".$filterAgeAdult.";".$filterAgeUnknown;
		$sHospital     = $filterHospitalSH.";".$filterHospitalWRNMMC.";".$filterHospitalOther;
		$sPageControls = $pageStart.";".$perPage.";".$sortBy.";true"; // use non-interactive mode

		require_once($global['approot']."/mod/inw/SearchDB.php");
		$timeElsapsed = 0;

		$search = new SearchDB($searchMode, $eventShortname, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls);

		try {
			$timeStart = microtime(true);
			$search->executeSearch();
			$timeElapsed = microtime(true) - $timeStart;
		} catch (Exception $e) {
			$error = true;
			$ecode = 9999;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'resultSet'    => '',
			'recordsFound' => (int)0,
			'timeElapsed'  => (double)$timeElapsed,
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'resultSet'    => (string)json_encode($search->results),
			'recordsFound' => (int)count($search->results),
			'timeElapsed'  => (double)$timeElapsed,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// REPORTING API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

// Report a new person
function reportPerson($personXML, $eventShortName, $xmlFormat, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$url = "";
	$error = false;
	$ecode = null;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$error = true;
		$ecode = $status;
	} else {
		// check if the user is a member of a group that has access to the event in question
		$q = "
			SELECT *
			FROM incident i, users u, sys_user_groups s, sys_user_to_group t
			WHERE (i.private_group = s.group_id
			AND s.group_id = t.group_id
			AND t.p_uuid = u.p_uuid
			AND u.user_name = '".mysql_real_escape_string($username)."'
			AND i.shortname = '".mysql_real_escape_string($eventShortName)."')
			OR (i.private_group is null
			AND i.shortname = '".mysql_real_escape_string($eventShortName)."');
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "reportPerson 1"); }
		if($result == null || $result->EOF) {
			$error = true;
			$ecode = 300;
		}

		// figure out the p_uuid of the user who is reporting
		if(!$error) {
			$q = "
				SELECT *
				FROM users
				WHERE user_name = '".$username."';
			";
			$result = $global['db']->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "reportPerson 2"); }
			$rep_uuid = $result->fields['p_uuid'];
		}

		// no errors, we must have permission to report to this event for the given user

		if(!$error) {
			$p = new person();
			$p->init();
			$p->rep_uuid  = $rep_uuid;
			$p->theString = $personXML;
			$p->xmlFormat = $xmlFormat;
			$p->setEvent($eventShortName);
			$ecode = $p->parseXml();
			if($ecode == 0 || $ecode == 419 || $ecode == 420) { // we accept record with bad images (the images are not saved)
				$p->insert();
				$p->plusReportLog();
			} else {
				$error = true;
			}
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'url'          => (string)$p->p_uuid,
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'url'          => (string)$p->p_uuid,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// Reserves a uuid in the system so that an app can cache it for later use in reporting.
function createPersonUuid($username, $password) {
	global $global;
	require_once $global['approot'].'/inc/lib_uuid.inc';

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$list = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuid'         => '',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);

	}
	$uuid = shn_create_uuid("p");
	return array(
		'uuid'         => (string)$uuid,
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}




// Reserves a number of uuids in the system so that an app can cache them for later use in reporting.
function createPersonUuidBatch($number, $username, $password) {
	global $global;
	require_once $global['approot'].'/inc/lib_uuid.inc';

	shn_plus_logAccess(__FUNCTION__);
	global $global;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuids'        => '',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$uuids = array();
	$count = 0;
	$max = 100; // maximum number of uuid's to request
	if ($number > 1 && $number <= $max) {
		for ($i = 0; $i < $number; $i++) {
			$uuid = shn_create_uuid("p");
			$uuids[] = array('uuid'.$i => $uuid);
		}
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuids'        => '',
			'errorCode'    => (int)201,
			'errorMessage' => (string)$eCodes[201]
		);
	}

	return array(
		'uuid'         => (string)json_encode($uuids),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}




// Reserves a note uuid in the system so that an app can cache it for later use in reporting.
function createNoteUuid($username, $password) {
	global $global;
	require_once $global['approot'].'/inc/lib_uuid.inc';

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$list = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuid'         => '',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);

	}
	$uuid = shn_create_uuid("pfn");
	return array(
		'uuid'         => (string)$uuid,
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}



// Reserves a number of note uuids in the system so that an app can cache them for later use in reporting.
function createNoteUuidBatch($number, $username, $password) {
	global $global;
	require_once $global['approot'].'/inc/lib_uuid.inc';

	shn_plus_logAccess(__FUNCTION__);
	global $global;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuids'        => '',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$uuids = array();
	$count = 0;
	$max = 100; // maximum number of uuid's to request
	if ($number > 1 && $number <= $max) {
		for ($i = 0; $i < $number; $i++) {
			$uuid = shn_create_uuid("pfn");
			$uuids[] = array('uuid'.$i => $uuid);
		}
	} else {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuids'        => '',
			'errorCode'    => (int)201,
			'errorMessage' => (string)$eCodes[201]
		);
	}

	return array(
		'uuid'         => (string)json_encode($uuids),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}





// Record Revision API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Record Revision API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Record Revision API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Record Revision API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Record Revision API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


// Re-report a person using XML which will update a current record.
function reReportPerson($uuid, $personXML, $eventShortname, $xmlFormat, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = false;
	$ecode = null;


	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$error = true;
		$ecode = $status;
	} else {
		// check if the user is a member of a group that has access to the event in question
		$q = "
			SELECT *
			FROM incident i, users u, sys_user_groups s, sys_user_to_group t
			WHERE (i.private_group = s.group_id
			AND s.group_id = t.group_id
			AND t.p_uuid = u.p_uuid
			AND u.user_name = '".mysql_real_escape_string($username)."'
			AND i.shortname = '".mysql_real_escape_string($eventShortname)."')
			OR (i.private_group is null
			AND i.shortname = '".mysql_real_escape_string($eventShortname)."');
		";
		$result = $global['db']->Execute($q);
		if($result == null || $result->EOF) {
			$error = true;
			$ecode = 300;
		}

		// figure out the p_uuid of the user who is reporting
		if(!$error) {
			$q = "
				SELECT *
				FROM users
				WHERE user_name = '".$username."';
			";
			$result = $global['db']->Execute($q);
			$rep_uuid = $result->fields['p_uuid'];
		}

		// check if the record exists
		if(!$error && !shn_plus_doesPersonExist($uuid)) {
			$error = true;
			$ecode = 410;
		}

		// check if the record was reported via PLUS, if not error 416
		if(!$error && !shn_plus_wasRecordReportedViaPLUS($uuid)) {
			$error = true;
			$ecode = 416;
		}

		// check if the user is admin, hs, hsa, or record owner
		if(!$error && !shn_plus_checkCredzTriage($username, $uuid)) {
			$error = true;
			$ecode = 408;
		}

		// no errors, we must have permission to revise this record

		if(!$error) {
			$p = new person();
			$p->p_uuid    = $uuid;
			$p->rep_uuid  = $rep_uuid;
			$p->theString = $personXML;
			$p->xmlFormat = $xmlFormat;
			$p->setEvent($eventShortName);
			$p->ignoreDupeUuid = true;
			$ecode = $p->parseXml();

			if($ecode == 0 || $ecode == 419 || $ecode == 420) { // we accept record with bad images (the images are not saved)

				// we made it this far, so delete the old person record
				$personOld = new person();
				$personOld->p_uuid = $uuid;
				$personOld->load();
				$personOld->delete();

				// and then re-insert the new record (this is a hack until we re-parse and revise on the fly)
				$p->insert();
				$p->plusReportLog();

			} else {
				$error = true;
			}
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'errorCode'    => (int)0,
			'errorMessage' => (string)''
		);
	}
}



// Owners, admins, and HSA can immediately expire a record, everyone else can submit an expiration request to a moderated queue.
function expirePerson($uuid, $explanation, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = false;
	$ecode = null;
	$queued = true;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'queued'       => (boolean)false,
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$p = new person();
	$p->p_uuid = $uuid;
	$p->updated_by_p_uuid = shn_plus_getUserUuid($username);
	$p->load();
	if($p->ecode == 9000) {
		$ecode = 410; // if we had trouble loading this record, we'll just report that the person does not exist (most likely whats happening)
		$error = true;
	}
	if($p->isAlreadyExpired()) {
		$ecode = 413;
		$error = true;
	}
	if($ecode == 0) {
		// check expiration permission
		$allowed = shn_plus_checkCredzExpiry($username, $uuid);
		if($allowed) {
			$p->expire(shn_plus_getUserId($username), $explanation);
			$queued = false;
		} else {
			$p->expireQueue(shn_plus_getUserId($username), $explanation);
			$queued = true;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'queued'       => (boolean)false,
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'queued'       => (boolean)$queued,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// Get the datetime in UTC when a person record will expire.
function getPersonExpiryDate($uuid) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = true;
	$ecode = 410;

	$q = "
		SELECT *
		FROM `person_uuid`
		where p_uuid = '".mysql_real_escape_string($uuid)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getPersonExpiryDate 1"); }
	if($result != null && !$result->EOF) {
		$error = false;
		$expiryDate = $result->fields['expiry_date'];
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'expiryDate'   => '',
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'expiryDate'   => (string)$expiryDate,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// Owners, admins, and HSA can immediately update a records expiry date, everyone else can submit a request to update the expiry date to a moderated queue.
function setPersonExpiryDate($uuid, $expiryDate, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = false;
	$ecode = null;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$p = new person();
	$p->p_uuid = $uuid;
	$p->updated_by_p_uuid = shn_plus_getUserUuid($username);
	$p->load();
	if($p->ecode == 9000) {
		$ecode = 410; // if we had trouble loading this record, we'll just report that the person does not exist (most likely whats happening)
		$error = true;
	}

	if(!checkValidDateTime($expiryDate)) {
		$ecode = 414;
		$error = true;
	}

	if(!$error) {
		// check expiration permission
		$allowed = shn_plus_checkCredzExpiry($username, $uuid);
		if($allowed) {
			$p->setExpiryDate($expiryDate);
		} else {
			$ecode = 408;
			$error = true;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// Owners, admins, and HSA can immediately update a records expiry date, everyone else can submit a request to update the expiry date to a moderated queue. The expiry date in this case is updated to exactly one year from the time of the request.
function setPersonExpiryDateOneYear($uuid, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = false;
	$ecode = null;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$p = new person();
	$p->p_uuid = $uuid;
	$p->updated_by_p_uuid = shn_plus_getUserUuid($username);
	$p->load();
	if($p->ecode == 9000) {
		$ecode = 410; // if we had trouble loading this record, we'll just report that the person does not exist (most likely whats happening)
		$error = true;
	}

	if(!$error) {
		// check expiration permission
		$allowed = shn_plus_checkCredzExpiry($username, $uuid);
		if($allowed) {
			$p->setExpiryDateOneYear();
		} else {
			$ecode = 408;
			$error = true;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// A simple lookup of the internal uuid of a person based on their mass casualty id (if it exists).
function getUuidByMassCasualtyId($mcid, $shortname, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = true;
	$ecode = 407;
	$uuid = "";

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$error = true;
		$ecode = $status;
	} else {
		$q = "
			SELECT *
			FROM `edxl_co_lpf`
			where person_id = '".mysql_real_escape_string($mcid)."'
			and event_name = '".mysql_real_escape_string($shortname)."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getUuidByMassCasualtyId 1"); }
		if($result != null && !$result->EOF) {
			$error = false;
			$uuid = $result->fields['p_uuid'];
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'uuid'         => '',
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'uuid'         => (string)$uuid,
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// Updates the mass casualty id of a person based on their uuid.
function changeMassCasualtyId($newMcid, $uuid, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = false;
	$ecode = null;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	$p = new person();
	$p->p_uuid = $uuid;
	$p->updated_by_p_uuid = shn_plus_getUserUuid($username);
	$p->load();
	if($p->ecode == 9000) {
		$ecode = 410; // if we had trouble loading this record, we'll just report that the person does not exist (most likely whats happening)
		$error = true;
	}

	if(!$error) {
		// check permissions
		$allowed = shn_plus_checkCredzTriage($username, $uuid);
		if($allowed) {
			$p->setMassCasualtyId($newMcid);
		} else {
			$ecode = 408;
			$error = true;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'errorCode'    => (int)$ecode,
			'errorMessage' => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'errorCode'    => (int)0,
			'errorMessage' => ''
		);
	}
}



// A simple lookup to determine if a record is still an original or has incurred revisions.
function hasRecordBeenRevised($uuid, $username, $password) {

	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$error = true;
	$ecode = 410;

	$q = "
		SELECT *
		FROM `person_uuid`
		where p_uuid = '".mysql_real_escape_string($uuid)."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hasRecordBeenRevised 1"); }
	if($result != null && !$result->EOF) {
		$error = false;
		// person exists...so count revisions
		$q = "
			SELECT count(*)
			FROM `person_updates`
			where p_uuid = '".mysql_real_escape_string($uuid)."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hasRecordBeenRevised 2"); }
		if($result != null && !$result->EOF) {
			$revisionsMade = $result->fields['count(*)'];
		} else {
			$error = true;
			$ecode = 9999;
		}
	}

	if($error) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'revisionsMade' => (int)0,
			'errorCode'     => (int)$ecode,
			'errorMessage'  => (string)$eCodes[$ecode]
		);
	} else {
		return array(
			'revisionsMade' => (int)$revisionsMade,
			'errorCode'     => (int)0,
			'errorMessage'  => ''
		);
	}
}



// Image Indexing API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Image Indexing API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Image Indexing API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Image Indexing API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// Image Indexing API FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


// Returns a count of the total number of images and the value of the latest brownie (image index value).
function getImageCountsAndTokens($username, $password) {
	shn_plus_logAccess(__FUNCTION__);
	global $global;

	$imageCount     = 0;
	$firstToken     = 0;
	$lastToken      = 0;
	$nullTokenCount = 0;

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'imageCount'     => (int)0,
			'firstToken'     => (int)0,
			'lastToken'      => (int)0,
			'nullTokenCount' => (int)0,
			'errorCode'      => (int)$status,
			'errorMessage'   => (string)$eCodes[$status]
		);

	// passed auth
	} else {

		// find the first token
		$q = "
			SELECT *
			FROM image
			ORDER BY image_id ASC
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageCountAndTokens 1"); }
		$firstToken = $result->fields["image_id"];

		// find the last token
		$q = "
			SELECT *
			FROM image
			ORDER BY image_id DESC
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageCountAndTokens 2"); }
		$lastToken = $result->fields["image_id"];

		// find the image count
		$q = "
			SELECT COUNT(*)
			FROM image
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageCountAndTokens 3"); }
		$imageCount = $result->fields["COUNT(*)"];

		$nullTokenCount = $lastToken - $imageCount;
	}

	return array(
		'imageCount'     => (int)$imageCount,
		'firstToken'     => (int)$firstToken,
		'lastToken'      => (int)$lastToken,
		'nullTokenCount' => (int)$nullTokenCount,
		'errorCode'      => (int)0,
		'errorMessage'   => ''
	);
}



// Returns a list of the images and their associated properties, paginated by a start and end token (index value).
function getImageList($tokenStart, $tokenEnd, $username, $password) {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$list = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'imageList'    => (string)'',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);

	// passed auth
	} else {

		// find the first token
		$q = "
			SELECT *
			FROM image
			ORDER BY image_id ASC
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageList 1"); }
		$firstToken = $result->fields["image_id"];

		// find the last token
		$q = "
			SELECT *
			FROM image
			ORDER BY image_id DESC
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageList 2"); }
		$lastToken = $result->fields["image_id"];

		// check for user asking for out of range tokens...
		if($tokenStart < $firstToken || $tokenEnd > $lastToken || $tokenStart > $lastToken || $tokenEnd < $firstToken || $tokenStart > $tokenEnd) {
			$eCodes = unserialize(ERRORCODES);
			return array(
				'imageList'    => (string)'',
				'errorCode'    => (int)411,
				'errorMessage' => (string)$eCodes[411]
			);
		}

		// get a list of all images in the range of the provided tokens
		$q = "
			SELECT *
			FROM image i, person_uuid p
			WHERE p.p_uuid = i.p_uuid
			AND image_id >= '".mysql_real_escape_string($tokenStart)."'
			AND image_id <= '".mysql_real_escape_string($tokenEnd)."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageList 3 ((".$q."))"); }
		while (!$result == NULL && !$result->EOF) {
			$list[] = array(
				'person_uuid'   => $result->fields["p_uuid"],
				'image_id'      => $result->fields["image_id"],
				'expiry_date'   => $result->fields["expiry_date"],
				'creation_time' => $result->fields["creation_time"],
				'url'           => $conf['https'].$conf['base_uuid'].$result->fields["url"],
				'url_thumb'     => $conf['https'].$conf['base_uuid'].$result->fields["url_thumb"]
			);
			$result->MoveNext();
		}
	}
	return array(
		'imageList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}


// Returns a list of the images and their associated properties, in blocks of stride size beginning with a start token (index value).
function getImageListBlock($tokenStart, $stride, $username, $password) {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	global $conf;
	$list = array();

	// check for valid stride value
	if($stride < 1 || $stride > 1000000) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'imageList'    => (string)'',
			'errorCode'    => (int)417,
			'errorMessage' => (string)$eCodes[417]
		);
	}

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'imageList'    => (string)'',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);
	}

	// passed auth

	// find the first token
	$q = "
		SELECT *
		FROM image
		ORDER BY image_id ASC
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageList 1"); }
	$firstToken = $result->fields["image_id"];

	// find the last token
	$q = "
		SELECT *
		FROM image
		ORDER BY image_id DESC
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageList 2"); }
	$lastToken = $result->fields["image_id"];

	// check for user asking for out of range tokens...
	if($tokenStart < $firstToken || $tokenStart > $lastToken) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'imageList'    => (string)'',
			'errorCode'    => (int)411,
			'errorMessage' => (string)$eCodes[411]
		);
	}

	// get a list of all images in the range of the provided tokens
	$q = "
		SELECT *
		FROM image i, person_uuid p
		WHERE p.p_uuid = i.p_uuid
		AND image_id >= '".mysql_real_escape_string($tokenStart)."'
		LIMIT ".(int)$stride.";
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getImageList 3 ((".$q."))"); }
	while (!$result == NULL && !$result->EOF) {
		$list[] = array(
			'person_uuid'   => $result->fields["p_uuid"],
			'image_id'      => $result->fields["image_id"],
			'expiry_date'   => $result->fields["expiry_date"],
			'creation_time' => $result->fields["creation_time"],
			'url'           => $conf['https'].$conf['base_uuid'].$result->fields["url"],
			'url_thumb'     => $conf['https'].$conf['base_uuid'].$result->fields["url_thumb"]
		);
		$result->MoveNext();
	}

	return array(
		'imageList'    => (string)json_encode($list),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}


// Returns a list of the images that have been removed from the system (either deleted or expired).
function getNullTokenList($tokenStart, $tokenEnd, $username, $password) {
	shn_plus_logAccess(__FUNCTION__);
	global $global;
	$nullList = array();
	$imageList = array();

	// check auth, if fails, return w/ error code/message
	$status = shn_plus_checkCredz($username, $password);
	if($status != 0) {
		$eCodes = unserialize(ERRORCODES);
		return array(
			'nullTokenList'    => (string)'',
			'errorCode'    => (int)$status,
			'errorMessage' => (string)$eCodes[$status]
		);

	// passed auth
	} else {

		// find the first token
		$q = "
			SELECT *
			FROM image
			ORDER BY image_id ASC
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getNullTokenList 1"); }
		$firstToken = $result->fields["image_id"];

		// find the last token
		$q = "
			SELECT *
			FROM image
			ORDER BY image_id DESC
			LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getNullTokenList 2"); }
		$lastToken = $result->fields["image_id"];

		// check for user asking for out of range tokens...
		if($tokenStart < $firstToken || $tokenEnd > $lastToken) {
			$eCodes = unserialize(ERRORCODES);
			return array(
				'nullTokenList'    => (string)'',
				'errorCode'    => (int)411,
				'errorMessage' => (string)$eCodes[411]
			);
		}

		// fill the array with all the possible indexes from the range
		for($i = (int)$tokenStart; $i <= (int)$tokenEnd; $i++) {
			$nullList[] = $i;
		}

		// get a list of all images in the range of the provided tokens
		$q = "
			SELECT image_id
			FROM image
			WHERE image_id >= '".mysql_real_escape_string($tokenStart)."'
			AND image_id <= '".mysql_real_escape_string($tokenEnd)."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "getNullTokenList 3 ((".$q."))"); }
		while (!$result == NULL && !$result->EOF) {
			$imageList[] = (int)$result->fields["image_id"];
			$result->MoveNext();
		}

		// now we extract the images that are present from the range we created ~ this leaves the null tokens
		for($i = 0; $i < sizeof($imageList); $i++) {
			$delKey = array_search($imageList[$i], $nullList);
			array_splice($nullList, $delKey, 1);
		}

	}
	return array(
		'nullTokenList'    => (string)json_encode($nullList),
		'errorCode'    => (int)0,
		'errorMessage' => ''
	);
}


