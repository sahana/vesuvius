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

// INTERNAL PLUS TESTER //

// load nusoap client library
require_once("../../3rd/nusoap/lib/nusoap.php");
require_once("unitTestLib.php");
require_once("conf.inc");

global $sites;
global $conf;
global $count;
$count = 0;
init();
if(!isset($_GET['api'])) {
	showEntry();
} else {
	$api = "&api=".$_GET['api'];

	$sites = array(
		"PL"               => "https://pl.nlm.nih.gov/?wsdl".$api,
		"PLstage"          => "https://plstage.nlm.nih.gov/?wsdl".$api,
		"devGreg"      => "http://plstage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl".$api,
		//"archiveStageGreg" => "http://archivestage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl".$api
	);

	$user  = "testDontDelete";
	$pass  = "dontDelete99";
	$email = "testCase@email.com";

	init2();

	// perform tests...
	version();
	getEventList();
	getEventListUser($user, $pass);
	getGroupList();
	getHospitalList();
	getHospitalData("1");
	getHospitalPolicy("1");
	getSessionTimeout();
	registerUser("testCaseUser", "testCase@email.com", "testPassword99", "testCaseGiven", "testCaseFamily");
	changeUserPassword($user, $pass, $pass);
	resetUserPassword($user);
	forgotUsername($email);
	checkUserAuth($user, $pass);
	getUserStatus($user);
	getUserGroup($user);
	search("test", "t");
	searchWithAuth("test", "t", "testDontDelete", "dontDelete99");

	echo "</table><br><h2>Note: deprecated functions are not listed/tested.</h2></body>";
}




