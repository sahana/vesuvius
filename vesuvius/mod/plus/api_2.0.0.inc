<?
/**
 * @name         PL User Services
 * @version      1.9.4
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0705
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

























/*
GRAVEYARD OF OLD v1 API CODE
*/


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
		SELECT a.p_uuid, a.full_name, b.opt_gender, b.years_old, c.opt_status, c.updated, i.image_height, i.image_width, i.url, e.last_seen, e.comments
		FROM person_uuid a
		LEFT OUTER JOIN person_details b USING (p_uuid)
		LEFT OUTER JOIN person_status c USING (p_uuid)
		LEFT OUTER JOIN image i ON a.p_uuid = i.p_uuid
		LEFT OUTER JOIN person_missing e USING (p_uuid)
		WHERE a.p_uuid = '".$uuid."';";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('uuid'=>$result->fields["p_uuid"], 'name'=>$result->fields["full_name"], 'gender'=>$result->fields["opt_gender"], 'years_old'=>$result->fields["years_old"], 'statusSahana'=>$result->fields["opt_status"], 'statusSahanaUpdated'=>$result->fields["updated"], 'statusTriage'=>$result->fields["triageCategory"], 'id'=>$result->fields["personId"], 'peds'=>$result->fields["peds"], 'orgName'=>$result->fields["orgName"], 'imageWidth'=>$result->fields["image_width"], 'imageHeight'=>$result->fields["image_height"], 'imageUrl'=>$result->fields["url"], 'last_seen'=>$result->fields["last_seen"], 'comments'=>strip_tags($result->fields["comments"]));
		$result->MoveNext();
	}
	return $list;
}

















