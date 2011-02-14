<?
// nusoap client test

// load nusoap client library
require_once("../../3rd/nusoap/lib/nusoap.php");

$wsdl     = "http://archivestage.nlm.nih.gov/~gmiernicki/sahanaDev/www/index.php?wsdl";
$client   = new nusoap_client($wsdl);
$client->useHTTPPersistentConnection();

// Check for an error
if ( $client->getError() ) {
	print "<h2>Soap Constructor Error:</h2><pre>".$client->getError()."</pre>";
	die();
}


//$result = $client->call('basicSearch', array('searchString'=>'e', 'incidentShortName'=>'cmax2009'));
//$result = $client->call('basicSearchWithRange', array('searchString'=>'jos', 'incidentShortName'=>'cmax2009', 'startFrom'=>2, 'limit'=>1));
//$result = $client->call('basicSearchAll', array('searchString'=>'jos'));
//$result = $client->call('askTimeout', array(null));
//$result = $client->call('getPersonData', array('uuid'=>'8y2fp-45'));
//$result = $client->call('createUuidBatch', array('incidentId'=>'1', 'num'=>'5'));
//$result = $client->call('createUuid', array('incidentId'=>'1'));
$result = $client->call('getIncidentList', array(null));


//$result = $client->call('shn_plus_test', array('x'=>317, 'y'=>123));

//$results = $client->call('shn_pls_submitLPFXML', array('lpfXmlFile'=>file_get_contents("lpf.xml")));


// un wrap and decode the results
//$result2 = json_decode($result['results']);

if($client->fault) {
	//soap_fault
	print "<h2>Soap Fault: </h2><pre>(". $client->fault->faultcode .")  ".$client->fault->faultstring. "</pre>";

} elseif($client->getError()) {
	print "<h2>Soap Error: </h2><pre>". $client->getError() ."</pre>";

} else {
	print "<h2>Result: </h2><pre>".print_r($result, true)."</pre>";
}


print '<h2>Details:</h2><hr />'.
	'<h3>Request</h3><pre>' .
	htmlspecialchars( $client->request, ENT_QUOTES) .'</pre>'.
	'<h3>Response</h3><pre>' .
	htmlspecialchars( $client->response, ENT_QUOTES) .'</pre>'.
	'<h3>Debug</h3><pre>' .
	htmlspecialchars( $client->debug_str, ENT_QUOTES) .'</pre>';
