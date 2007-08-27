<?php
/* $Id: lib_stream_soap.inc,v 1.7 2007-08-27 02:55:03 ravids Exp $ */

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
require_once($global['approot'].'/inc/lib_xml.inc');

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

	$xml =simplexml_load_file($global['approot']."/mod/".$mod."/ws.xml");
	
	foreach ($xml->types->type as $type) {
		$typeName=trim($type->name);
		$class=(trim($type->typeclass)==null)?'complexType':trim($type->typeclass);
		$phpType=(trim($type->phptype)==null)?'array':trim($type->phptype);
		$compositor=(trim($type->compositor)==null)?array():trim($type->compositor);
		$restrictionbase=trim($type->restrictionBase);
		$attrs=(trim($type->attrs)==null)?'':trim($type->attrs);
		if($type->elements!=null){
			switch ($phpType){
			
			case "struct":
				$elements=array();
				foreach($type->elements->element as $element){
					$at=findAttribute($element, "type");
					$elements["$element"]=array('name'=>(string)$element,'type'=>$at);
				}
			break;
			}
		}else{
			$elements=array();
		}

		if(strlen($type->arrayType)!=0){
			$at=$type->arrayType."[]";
			$attrs=array(array('ref'=>'SOAP-ENC:arrayType','wsdl:arrayType'=>$at));
		}else{
			$attrs=array();
			$arrayType='';
		}

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
   		$in=array();
   		if($service->input!=null){
   			foreach ($service->input as $input) {
				$in[trim($input)]=findAttribute($input, "type");
   			}
   		}
   		if($service->output!=null){
   			$out=trim(findAttribute($service->output, "type"));
   			$out=array('return' => $out);
   		}
   		if($service->documentation!=null){
   			$doc=$service->documentation;
   		}
   		
   		$server->register($function,
			$in,
			$out,
		$ns,false,false,false,$doc,'',$name);

	}

}
function shn_stream_close(){
	global $server;
	global $HTTP_RAW_POST_DATA;// its essential to make this global, otherwise no content
	$server->service($HTTP_RAW_POST_DATA);

}




?>
