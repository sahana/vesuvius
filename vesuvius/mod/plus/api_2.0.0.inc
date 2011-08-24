<?
/**
 * @name         PL User Services
 * @version      1.9.5
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0823
 */

global $api_version;
$api_version = "2.0.0";

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
}


// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// GENERAL API FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


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



