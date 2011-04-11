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
		"Returns version info (1.9.0)"
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
	return array('apiVersion'=>'1.9.0');
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


