<?php
/* $Id: lib_stream_soap.inc,v 1.6 2007-08-26 04:00:06 ravids Exp $ */

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
	/*
	$server->wsdl->addComplexType(
    'Org',
    'complexType',
    'struct',
    'all',
    '',
    array(
        'name' => array('name'=>'name','type'=>'xsd:string'),
        'o_uuid' => array('name'=>'o_uuid','type'=>'xsd:string')
    )
);
 
$server->wsdl->addComplexType(
    'OrgArray',
    'complexType',
    'array',
    '',
    'SOAP-ENC:Array',
    array(),
    array(
        array('ref'=>'SOAP-ENC:arrayType','wsdl:arrayType'=>'tns:Org[]')
    ),
    'tns:Org'
);

$server->wsdl->addComplexType(
    'Chapter',
    'complexType',
    'struct',
    'all',
    '',
    array(
        'title' => array('name'=>'title','type'=>'xsd:string'),
        'page' => array('name'=>'page','type'=>'xsd:int')
    )
);
 
$server->wsdl->addComplexType(
    'ChapterArray',
    'complexType',
    'array',
    '',
    'SOAP-ENC:Array',
    array(),
    array(
        array('ref'=>'SOAP-ENC:arrayType','wsdl:arrayType'=>'tns:Chapter[]')
    ),
    'tns:Chapter'
);
	$server->wsdl->addComplexType(
    'List',
    'complexType',
    'struct',
    'all',
    '',
    array(
		"o" => array('name' => 'firstname', 'type' => 'xsd:string','maxOccurs'=>'10','minOccurs'=>'0')
		//"o2" => array('name' => 'secname', 'type' => 'xsd:string')
    )
);*/
	$xml =simplexml_load_file($global['approot']."/mod/".$mod."/ws.xml");
	foreach ($xml->types->type as $type) {
		$typeName=trim($type->name);
		$class=trim($type->typeclass);
		$phpType=trim($type->phptype);
		$compositor=(trim($type->compositor)==null)?'':trim($type->compositor);
		$restrictionbase=trim($type->restrictionBase);
		$elements=trim($type->elements);
		$attrs=(trim($type->attrs)==null)?'':trim($type->attrs);
		//$arrayType=(strlen($type->arrayType)==0)?:trim($type->arrayType);
		$server->wsdl->addComplexType(
    		$typeName,
    		$class,
    		$phpType,
    		$compositor,
    		$restrictionbase,
   		 	$elements,
			$attrs,
    		''
    		//$arrayType
		);
	}

 

	foreach ($xml->service as $service) {
   		$name= trim($service->name);
   		$name="{$name}";
   		$function=trim($service->api_function);

	}
			$server->register('shn_or_org_list',
			array('amount' => 'xsd:string'),
			array('return' => 'tns:OrgArray'),
			//array('return' => 'tns:List'),
		$ns);
			$server->register('shn_or_service_list',
			array('amount' => 'xsd:string'),
			array('return' => 'tns:ChapterArray'),
			//array('return' => 'tns:List'),
		$ns);
}
function shn_stream_close(){
	global $server;
	global $HTTP_RAW_POST_DATA;// its essential to make this global, otherwise no content
	$server->service($HTTP_RAW_POST_DATA);

}




?>
