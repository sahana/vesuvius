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

$user = "testDontDelete";
$pass = "dontDelete99";

require_once("../../3rd/nusoap/lib/nusoap.php");
//$wsdl = "https://plstage.nlm.nih.gov/?wsdl&api=1.9.5";
//$wsdl = "http://plstage.nlm.nih.gov/~miernickig/vesuvius/vesuvius/www/index.php?wsdl&api=1.9.5";
$wsdl = "https://pl.nlm.nih.gov/?wsdl";
$client = new nusoap_client($wsdl);

//$result = $client->call('getHospitalLegalese', array('hospital_uuid'=>1));
//$result = $client->call('registerUser', array('username'=>'testCaseUser', 'emailAddress'=>'testCase@email.com', 'password'=>'testPassword99', 'givenName'=>'testCaseGiven', 'familyName'=>'testCaseFamily'));
//$result = $client->call('changeUserPassword', array('username'=>$user, 'oldPassword'=>$pass, 'newPassword'=>$pass));
//$result = $client->call('resetUserPassword', array('username'=>"testCaseUser9"));
//$result = $client->call('forgotUsername', array('email'=>"testCase@email.com"));
//$result = $client->call('reportPerson', array('personXML'=>null, 'eventShortName'=>null, 'xmlFormat'=>'TRIAGEPIC', 'username'=>null, 'password'=>null));
//$result = $client->call('createPersonUuid', array('username'=>'testDontDelete', 'password'=>'dontDelete99'));
//$result = $client->call('createPersonUuidBatch', array('number'=>5, 'username'=>'testDontDelete', 'password'=>'dontDelete99'));

/*
$result = $client->call('searchWithAuth', array(
	'eventShortname'=>'test',
	'searchTerm'=>'t',
	'filterStatusMissing'=>true,
	'filterStatusAlive'=>true,
	'filterStatusInjured'=>true,
	'filterStatusDeceased'=>true,
	'filterStatusUnknown'=>true,
	'filterStatusFound'=>true,
	'filterGenderComplex'=>true,
	'filterGenderMale'=>true,
	'filterGenderFemale'=>true,
	'filterGenderUnknown'=>true,
	'filterAgeChild'=>true,
	'filterAgeAdult'=>true,
	'filterAgeUnknown'=>true,
	'filterHospitalSH'=>true,
	'filterHospitalNNMCC'=>true,
	'filterHospitalOther'=>true,
	'pageStart'=>0,
	'perPage'=>10,
	'sortBy'=>'',
	'mode'=>true,
	'username'=>'testDontDelete',
	'password'=>'dontDelete99'
));
*/

//$x = file_get_contents("referenceXML_RU.xml");
//$result = $client->call('reportPerson', array('personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'REUNITE3', 'username'=>$user, 'password'=>$pass));

$x = file_get_contents("referenceXML_TP.xml");
$result = $client->call('reportPerson', array('personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'TRIAGEPIC1', 'username'=>$user, 'password'=>$pass));

echo "<pre>wsdl >> ".$wsdl."\n\n".var_export($result, true)."</pre>";


