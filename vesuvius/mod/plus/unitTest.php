<?
// INTERNAL PLUS TESTER //

// load nusoap client library
require_once("../../3rd/nusoap/lib/nusoap.php");
require_once("unitTestLib.php");

global $sites;
init();
if(!isset($_GET['api'])) {
	echo "apis";
} else {
	$api = "&api=".$_GET['api'];
	if($_GET['api'] == "current") {
		$api = "";
	}

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

	echo "</table></body>";
}