<?php
/**Main Controller of the Web Services Module 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ws
*/

global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_xml.inc";
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
require_once "reg.inc";	


function shn_ws_mainmenu() 
{
    global $global;
    global $conf;
    $mods=shn_get_modules_with_web_services();
    $module = $global['module'];
    shn_mod_menuopen(_lc("Web Services"));
 	shn_mod_menuitem("api_key","Sign up for API Key",$module);
    shn_sub_mod_menuopen(_lc("SOAP"));
    foreach($mods as $mod=>$data_arr){
    	shn_mod_menuitem("main&wbsmod=".$data_arr[0],$data_arr[1],$module);
    }
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_lc("REST"));
    foreach($mods as $mod=>$data_arr){
    	shn_mod_menuitem($data_arr[0],$data_arr[1],$module);
    }
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
} 



function shn_ws_main(){
	global $global;
	global $conf;
	$mod=$_GET['wbsmod'];
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

		/*
		if(trim($type->attrs)!=null){
				$attrs=array();
				foreach($type->attrs as $attr){
					if(findAttribute($attr, "type")=="ref"){
						$attrs["ref"]=$attr;
					}
				}
		}else{
			$attrs='';
		}
*/
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
   		$function=trim($service->api_function);
   		$name="{$name}";
   		$input_arr=array();


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

	global $HTTP_RAW_POST_DATA;
	$server->service($HTTP_RAW_POST_DATA);

}

function shn_ws_default(){
	global $conf;
?>
<div id="home">
    <h2><?=_lc($conf['mod_ws_name'])?></h2>
    		<div><b><i><?=_("\"SAHANA functionality exposed as  web services\"")?></i></b></div>
        <br></br>
		<div><?=_("The Web Services Module generates WSDL for each service.")?>
        </div>
		<ul>
            <li><?=_("Displays the methods that are exposed as web serivices with additional information")?></li>
            <li><?=_("Generates and display the WSDL for those services")?></li>
         </ul>
</div>
<br />

<?php	
}


   
/**
 * The function that registers the types and services
 * @return void
 * @access public
 */
 
function shn_soap_ws_reg(){
	global $global;
	global $server;
	require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
	$mod=$_GET["wbsmod"];// A web service of this mod is requested
	$ns="http://localhost/".$mod; //change this to the actual namespace later
	$xml =simplexml_load_file($global['approot']."/mod/".$mod."/ws.xml");
	//read the XML file describing the types and services for that module.
	
	//first register the types that will be referenced in the services
	foreach ($xml->types->type as $type) {
		$typeName=trim($type->name);//name of the type
		$class=(trim($type->typeclass)==null)?'complexType':trim($type->typeclass);//simple vs complex
		$phpType=(trim($type->phptype)==null)?'array':trim($type->phptype);//the type in PHP
		$compositor=(trim($type->compositor)==null)?array():trim($type->compositor);//how the elements are composed. e.g all arr need,or only one is neede
		$restrictionbase=trim($type->restrictionBase);//the base type if there is any
		$attrs=(trim($type->attrs)==null)?'':trim($type->attrs);//attributes if there are any
		if($type->elements!=null){
			switch ($phpType){
			
			case "struct":
				$elements=array();
				foreach($type->elements->element as $element){
					$at=findAttribute($element, "type");//find the attribute 'type' for the element from the ws.xml
					$elements["$element"]=array('name'=>(string)$element,'type'=>$at);
					//every element should have name and type
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

  	//now register the services

	foreach ($xml->service as $service) {
   		$name= trim($service->name);//name of the service
   		$function=trim($service->api_function);//function that is exposed
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

?>
