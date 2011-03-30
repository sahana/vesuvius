<?
/**
 * @name         PL User Services
 * @version      2.0.0
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

// PLUS SOAP Server

global $APPROOT;
global $server;
global $conf;

if(!isset($conf['enable_plus_web_services']) || (isset($conf['enable_plus_web_services']) &&  $conf['enable_plus_web_services'] == false)) {
	echo "web services disabled";
	die();
}

require_once($APPROOT."3rd/nusoap/lib/nusoap.php");

// figure out which api version to load
if(isset($_GET['api']) && file_exists($APPROOT."/mod/plus/api_".$_GET['api'].".inc")) {
	require_once($APPROOT."/mod/plus/api_".$_GET['api'].".inc");
	$versionString = "&amp;api=".$_GET['api'];
} else {
	require_once("api_".$conf['mod_plus_latest_api'].".inc");
	$versionString = "";
}


// fix broken apache servers that don't default to index.php
if(($_SERVER['HTTP_HOST'] == "archivestage.nlm.nih.gov")
|| ($_SERVER['HTTP_HOST'] == "archivestage")) {
	$fix = "index.php";
} else {
	$fix = "";
}


// init vars
$serviceName = "plusWebServices";
$ns          = "urn:".$serviceName;
$endpoint     = makeBaseUrl().$fix."?wsdl".$versionString;

$server = new nusoap_server;
$server->configureWSDL($serviceName, $ns, $endpoint, 'document');
$server->wsdl->schemaTargetNamespace = $ns;

shn_plus_register_all($ns);

//if in safe mode, raw post data not set:
if(!isset($HTTP_RAW_POST_DATA)) {
	$HTTP_RAW_POST_DATA = implode("\r\n", file('php://input'));
}

$server->service($HTTP_RAW_POST_DATA);


function makeBaseUrl() {
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace("index.php", "", $link);
	return $link;
}