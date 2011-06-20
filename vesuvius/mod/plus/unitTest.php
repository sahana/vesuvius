<?
// INTERNAL PLUS TESTER //

// load nusoap client library
require_once("../../3rd/nusoap/lib/nusoap.php");
require_once("unitTestLib.php");
require_once("conf.inc");

global $sites;
global $conf;
init();
if(!isset($_GET['api'])) {
	showEntry();
} else {
	$api = "&api=".$_GET['api'];

	$sites = array(
		"PL"               => "https://pl.nlm.nih.gov/?wsdl".$api,
		"PLstage"          => "https://plstage.nlm.nih.gov/?wsdl".$api,
		"PLstageGreg"      => "http://plstage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl".$api,
		"archiveStageGreg" => "http://archivestage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl".$api
	);

	$user = "testDontDelete";
	$pass = "dontDelete99";

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

	echo "</table><br><h2>Note: deprecated functions are not listed/tested.</h2></body>";
}