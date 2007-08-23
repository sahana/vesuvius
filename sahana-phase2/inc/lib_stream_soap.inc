<?php
/* $Id: lib_stream_soap.inc,v 1.5 2007-08-23 01:20:09 ravids Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_soap
 * @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');


function shn_stream_init(){
	
	global $server;
	global $global;
	global $conf;
	require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
	
	$mod=$_GET["wbsmod"];
	
	$action=$global['action'];
	$module_function = 'shn_'.$mod.'_'.$action;
	$module_file = $global['approot'].'mod/'.$mod.'/api.inc';
    include($module_file);
	$ns="http://localhost/".$mod;
	$nice_name=$conf['mod_'.$mod.'_name'];
	$server = new soap_server();
	$server->configureWSDL($nice_name.' Web Services',$ns);
	$server->wsdl->schemaTargetNamespace=$ns;
	$server->wsdl->addComplexType(
    'List',
    'complexType',
    'struct',
    'all',
    '',
    array(
		"f1" => array('name' => 'firstname', 'type' => 'xsd:string'),
		"f2" => array('name' => 'secname', 'type' => 'xsd:string')
    )
);
	$xml =simplexml_load_file($global['approot']."/mod/".$mod."/ws.xml");
	foreach ($xml->service as $service) {
   		$name= trim($service->name);
   		$name="{$name}";
   		$function=trim($service->api_function);
   		$input_arr=array();
   		foreach ($service->inputs->required as $req_input) {
			$input_arr["$req_input"]='xsd:string';
   		}
   		foreach ($service->inputs->optional as $opt_input) {
			$input_arr["$opt_input"]='xsd:string';
   		}
   		/*
		$server->register($function,
			$input_arr,
			array('return' => 'xsd:string'),
			//array('return' => 'tns:List'),
		$ns);
		*/
	}
			$server->register('shn_or_org_list',
			array('amount' => 'xsd:string'),
			array('return' => 'tns:List'),
			//array('return' => 'tns:List'),
		$ns);
			$server->register('shn_or_service_list',
			array('amount' => 'xsd:string'),
			array('return' => 'tns:List'),
			//array('return' => 'tns:List'),
		$ns);
}
function shn_stream_close(){
	global $server;
	global $HTTP_RAW_POST_DATA;// its essential to make this global, otherwise no content
	$server->service($HTTP_RAW_POST_DATA);

}




?>
