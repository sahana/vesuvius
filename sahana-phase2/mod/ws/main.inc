<?php
/**Main Controller of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/
//
global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');



function shn_ws_mainmenu() 
{
    global $global;
    global $conf;
    $mods=shn_get_modules_with_web_services();
    $module = $global['module'];
  //  $loc=_shn_or_get_start_loc();
    shn_mod_menuopen(_lc("SOAP"));
    foreach($mods as $mod=>$data_arr){
    	shn_mod_menuitem("main&wbsmod=".$data_arr[0],$data_arr[1],$module);
    }
    shn_mod_menuclose();
    shn_mod_menuopen(_lc("REST"));
    foreach($mods as $mod=>$data_arr){
    	shn_mod_menuitem($data_arr[0],$data_arr[1],$module);
    }
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
	foreach ($xml->service as $service) {
   		$name= trim($service->name);
   		$function=trim($service->api_function);
   		$name="{$name}";
   		$input_arr=array();
   		if($service->inputs->required!=null){
   			foreach ($service->inputs->required as $req_input) {
				$input_arr["$req_input"]='xsd:string';
   			}
   		}
		if($service->inputs->optional!=null){
			foreach ($service->inputs->optional as $opt_input) {
				$input_arr["$opt_input"]='xsd:string';
   			}
		}

   		
		$server->register($function,
			$input_arr,
			array('return' => 'xsd:string'),
		$ns,false,false,false,"help the ors",'',$name);
		
	}

	global $HTTP_RAW_POST_DATA;
	$server->service($HTTP_RAW_POST_DATA);

}


?>
