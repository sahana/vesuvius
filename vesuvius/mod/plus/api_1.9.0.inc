<?
/**
 * @name         PL User Services
 * @version      1.9.0
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0328
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
function shn_plus_register_all($namespace) {
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

	shn_plus_register_one($server, 'version',
		array(
			'in' => array(),
			'out' => array(
				'apiVersion' => 'xsd:string'
			)
		),
		$namespace,
		"Returns version info (2)."
	);

	shn_plus_register_one($server, 'getIncidentList',
		array(
			'in' => array(),
			'out' => array(
				'incidentList' => 'xsd:string'
			)
		),
		$namespace,
		"Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude, street) listing disaster incidents' components."
	);
}



function shn_plus_register_one($server, $methodname, $params, $ns, $rtfm) {
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


// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// API FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //



/**
 * Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
 * @return array
 */
function version() {
	logAccess("version"); // log access
	return array('apiVersion'=>'1.9.0');
}


/**
* Returns an array of (incident_id, parent_id, name, shortname, date, type, latitude, longitude) of listed disaster incidents.
* @return array
*/
function getIncidentList() {
	global $global;
	$db = $global['db'];
	$list = array();
	$q = "
		SELECT incident_id, parent_id, name, shortname, date, type, latitude, longitude
		FROM `incident`
		ORDER BY `default` DESC, `name` ASC;
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
			//'street'   => $result->fields["street"]
		);
		$result->MoveNext();
	}
	return array('incidentList'=>json_encode($list));
}


