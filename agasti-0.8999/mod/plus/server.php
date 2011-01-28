<?

global $APPROOT;
require_once($APPROOT."3rd/nusoap/lib/nusoap.php");

$serviceName = "plsWebServices";
$ns          = "urn:".$serviceName;
$endpoint    = "http://archivestage.nlm.nih.gov/~gmiernicki/sahanaDev/www/index.php";

$server = new nusoap_server;
$server->configureWSDL($serviceName, $ns, $endpoint, 'document');
$server->wsdl->schemaTargetNamespace = $ns;
//$server->setContentType("text/xml", "UTF-8");


doRegister($server, 'shn_pls_basicSearch',
	array(
		'in' => array(
			'searchString'      => 'xsd:string',
			'incidentShortName' => 'xsd:string'
		),
		'out' => array(
			'results' => 'xsd:string'
		)
	)
);


//if in safe mode, raw post data not set:
if(!isset($HTTP_RAW_POST_DATA)) {
	$HTTP_RAW_POST_DATA = implode("\r\n", file('php://input'));
}

$server->service($HTTP_RAW_POST_DATA);



function doRegister($server, $methodname, $params) {
	global $ns;
	$server->register(
		$methodname,
		$params["in"],
		$params["out"],
		$ns,
		$server->wsdl->endpoint.'#'.$methodname, // soapaction
		'document',
		'literal',
		'RTFM!!!'
	);
}



function shn_pls_basicSearch($searchString, $incidentShortName) {
	return array('results'=>json_encode(array('name'=>'lucy','age'=>'23')));
}
