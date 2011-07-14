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

$user = "testDontDelete";
$pass = "dontDelete99";

require_once("../../3rd/nusoap/lib/nusoap.php");
$wsdl = "https://plstage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl&api=1.9.5";
//$wsdl = "http://localhost/vesuvius-trunk/vesuvius/www/index.php?wsdl&api=1.9.4";
//$wsdl = "https://pl.nlm.nih.gov/?wsdl";
$client = new nusoap_client($wsdl);


//$result = $client->call('registerUser', array('username'=>'testCaseUser', 'emailAddress'=>'testCase@email.com', 'password'=>'testPassword99', 'givenName'=>'testCaseGiven', 'familyName'=>'testCaseFamily'));
//$result = $client->call('changeUserPassword', array('username'=>$user, 'oldPassword'=>$pass, 'newPassword'=>$pass));
//$result = $client->call('resetUserPassword', array('username'=>"testCaseUser9"));
//$result = $client->call('forgotUsername', array('email'=>"testCase@email.com"));

$result = $client->call('reportPersonViaLPFXML', array('personXML'=>null, 'eventShortName'=>null, 'username'=>null, 'password'=>null));

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


echo "<pre>".print_r($result, true)."</pre>";


