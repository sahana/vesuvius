<?
/**
 * @name         PL User Services
 * @version      1.9.3
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0614
 */

$user = "testDontDelete";
$pass = "dontDelete99";

require_once("../../3rd/nusoap/lib/nusoap.php");
$wsdl = "https://plstage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl&api=1.9.3";
//$wsdl = "https://pl.nlm.nih.gov/?wsdl";
$client = new nusoap_client($wsdl);


//$result = $client->call('registerUser', array('username'=>'testCaseUser', 'emailAddress'=>'testCase@email.com', 'password'=>'testPassword99', 'givenName'=>'testCaseGiven', 'familyName'=>'testCaseFamily'));
//$result = $client->call('changeUserPassword', array('username'=>$user, 'oldPassword'=>$pass, 'newPassword'=>$pass));
//$result = $client->call('resetUserPassword', array('username'=>"testCaseUser9"));
//$result = $client->call('forgotUsername', array('email'=>"testCase@email.com"));
$result = $client->call('checkUserAuth', array('username'=>$user, 'password'=>$pass));

echo "<pre>".print_r($result, true)."</pre>";
