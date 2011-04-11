<?
/**
 * @name         PL User Services
 * @version      2.0.0
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0411
 */

// PLUS SOAP Server

global $global;
global $server;
global $conf;
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');
require_once($global['approot'].'/mod/plus/lib_plus.inc');
require_once($global['approot'].'3rd/nusoap/lib/nusoap.php');

// determine if web services are on or off
if(!isset($conf['enable_plus_web_services']) || (isset($conf['enable_plus_web_services']) &&  $conf['enable_plus_web_services'] == false)) {
	echo "web services disabled";
	die();
}

// figure out which api version to load ~ not specified, load default
if(isset($_GET['api']) && file_exists($global['approot']."/mod/plus/api_".$_GET['api'].".inc")) {
	require_once($global['approot']."/mod/plus/api_".$_GET['api'].".inc");
	$versionString = "&amp;api=".$_GET['api'];
	$global['apiVersion'] = $_GET['api'];
} else {
	require_once("api_".$conf['mod_plus_latest_api'].".inc");
	$versionString = "";
	$global['apiVersion'] = $conf['mod_plus_latest_api'];

}

// fix broken apache servers that don't default to index.php
$fix = "";
if(($_SERVER['HTTP_HOST'] == "archivestage.nlm.nih.gov") || ($_SERVER['HTTP_HOST'] == "archivestage")) {
	$fix = "index.php";
}

// init vars
$serviceName = "plusWebServices";
$ns          = "urn:".$serviceName;
$endpoint    = makeBaseUrl().$fix."?wsdl".$versionString;

$server = new nusoap_server;
$server->configureWSDL($serviceName, $ns, $endpoint, 'document');
$server->wsdl->schemaTargetNamespace = $ns;

shn_plus_registerAll($ns);

//if in safe mode, raw post data not set:
if(!isset($HTTP_RAW_POST_DATA)) {
	$HTTP_RAW_POST_DATA = implode("\r\n", file('php://input'));
}

$server->service($HTTP_RAW_POST_DATA);
