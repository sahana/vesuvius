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
    shn_sub_mod_menuopen(_lc("Client"));
   	shn_mod_menuitem("sahana","Other SAHANA systems",$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
} 



function shn_ws_main(){

	global $global;
	global $server;	
	global $conf;
	$server = new soap_server();
	shn_soap_ws_reg();
	global $HTTP_RAW_POST_DATA;
	$server->service($HTTP_RAW_POST_DATA);
	return;
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
	global $conf;
	$mod=$_GET["wbsmod"];// A web service of this mod is requested
	$ns="http://localhost/".$mod; //change this to the actual namespace later
	$nice_name=$conf['mod_'.$mod.'_name'];
	$server->configureWSDL($nice_name.' Web Services',$ns);
	$server->wsdl->schemaTargetNamespace=$ns;
	//read the XML file describing the common types.
	$xml_file=$global['approot']."/inc/lib_ws/ws.xml";
	//read the XML file describing the types and services for that module.
	$xml =simplexml_load_file($xml_file);
	shn_soap_ws_type_reg($xml,$ns);
	//read the XML file describing the types and services for that module.
	$xml_file=$global['approot']."/mod/".$mod."/ws.xml";
	//read the XML file describing the types and services for that module.
	$xml =simplexml_load_file($xml_file);
	//first register the types that will be referenced in the services
	shn_soap_ws_type_reg($xml,$ns);
	$module_file = $global['approot'].'/mod/'.$mod.'/api.inc';
    include($module_file);
  	//now register the services
	shn_soap_ws_service_reg($xml,$ns);
	
}
function shn_soap_ws_type_reg($xml,$ns){
	global $server;
	if($xml->types->type!=null){
		//first register the types that will be referenced in the services
		foreach ($xml->types->type as $type) {
			$typeName=trim($type->name);//name of the type
			$class=(trim($type->typeclass)==null)?'complexType':trim($type->typeclass);//simple vs complex
			$phpType=(trim($type->phptype)==null)?'array':trim($type->phptype);//the type in PHP
			$compositor=(trim($type->compositor)==null)?'':trim($type->compositor);//how the elements are composed. e.g all arr need,or only one is neede
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
			$elements=null;
			$attrs=null;
			$typeName=null;
			$class=null;
			$phpType=null;
	    	$compositor=null;
	    	$restrictionbase=null;
		}
	}	
}
function shn_soap_ws_service_reg($xml,$ns){
	global $server;
	foreach ($xml->services->service as $service) {
   		$name= trim($service->name);//name of the service
   		$function=trim($service->api_function);//function that is exposed
   		$in=array();
   		if($service->input!=null){
   			foreach ($service->input as $input) {
   				$in_attr=findAttribute($input, "type");
   				if(preg_match("/xsd/",$in_attr)){
   					$in[trim($input)]=findAttribute($input, "type");
   				}else{
   					$in[trim($input)]="tns:".findAttribute($input, "type");
   				}
				
   			}
   		}
   		//if($service->output!=null){
   			$out=trim(findAttribute($service->output, "type"));
   			if(preg_match("/xsd/",$out)){
   				$out=array('return' => $out);
   			}else{
   				$out=array('return' => "tns:".$out);
   			}
   			
   		//}
   		if($service->documentation!=null){
   			$doc=$service->documentation;
   		}
   		$action=$ns."#".$function;
   		$server->register($function,
			$in,
			$out,
		$ns,$action,"rpc","encoded",$doc,'',$name);

	}
}
function shn_ws_sahana(){
	?>
<h2><?= _('Access another SAHANA system through web services')?></h2>
<?php

?>  

<div id="formcontainer">
<?php
	
    shn_form_fopen("sahana_cr");
    shn_form_fsopen(_("Web Service (WSDL) URL"));
    shn_form_text(_("URL : "),'wsdl_url','size="50"',null);
    shn_form_fsclose();
    
   	$methods=shn_ws_get_methods();
    shn_form_fsopen(_("Select Method"));
	shn_form_select($methods,"Methods",'method',null,null);
    shn_form_fsclose();

    ?>
    <div id="no_sec_div">
    <div class="info"><?= _("If the web service provider requires authentication ,then switch to secure mode")?></div>
    <?php
    $button_opts="onclick=\"switchMode('no_sec_div','api_div','mode','sec');\"";
    shn_form_button("Switch to Secure Authentication Mode",$button_opts , null);
    ?>
   <!-- <a href="#" onclick="switchMode('no_sec_div','api_div','mode','sec');">Switch to Secure Authentication Mode</a>-->
    
    </div>
    <br />
    <div id="api_div">
    <?php
    $button_opts="onclick=\"switchMode('api_div','no_sec_div','mode','no_sec');\"";
    shn_form_button("Switch off Secure Authentication Mode",$button_opts , null);
    ?>
    <!-- <a href="#" onclick="switchMode('api_div','no_sec_div','mode','no_sec');">Switch off Secure Authentication Mode</a>-->
     <br />
    <div class="info"><?= _("The API Key allows you to access the web services of another SAHANA instance which requires authentication. To access SAHANA web services, a developer must have a login(an account).
	That is you should have an API Key,a password and a Secret Access Code. The API Key and password, which is associated with your login, is used in requests to identify the party responsible for the request." .
		" However, because both the API Key and password is sent as a request parameter, it is not secret and could be used by anyone sending a request to SAHANA web service. Therefore to improve the security(reduce impersonation attacks), a request signature is calculated using the Secret Access Code. The Secret Access Code is a automatically generated 32-character alphanumeric sequence.");?>
	</div><br />
	<?php
	
	
	shn_form_fsopen("Your API Key"); 
	$extra_opts["req"]=true;
    shn_form_textarea("", "key", null, $extra_opts);
	shn_form_fsclose();
	
	shn_form_fsopen("Your Password"); 
    shn_form_textarea("", "pwd", null, $extra_opts);
	shn_form_fsclose();
	
	shn_form_fsopen("Your Secret Code"); 
    shn_form_textarea("", "secret", null, $extra_opts);
	shn_form_fsclose();
	
 	shn_form_hidden(array('mode'=>'no_sec'));
   
   
?>
	</div>
	<script type="text/javascript">
    	switchMode('api_div','no_sec_div','mode','no_sec');
    </script>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_("View Result ..."));
?>
</center>
<br />
<?php
    //close the form
   
    shn_form_fclose();
?>				     
</div>
<?php	
}
function shn_ws_sahana_cr(){
	
	$method=trim($_POST["method"]);
	echo '<h2>Method</h2><pre>' . $method . '</pre><br />';
	$native=extension_loaded('soap');
	$url=trim($_POST["wsdl_url"]);
	$url= trim(collapseEntities($url));

	$url="http://localhost/trunk/index.php?wsdl&stream=soap&wbsmod=or&mod=ws&act=reg";

		$digest="adsadsdsd";
		$secret=trim($_POST["secret"]);
		$sign=shn_acl_hmac_sha1($digest,$secret);
		$sign=md5($sign);
		$uid=trim($_POST["key"]).",".trim($_POST["pwd"]).",adsadsdsd";
	


	if($native==true){
		ini_set("soap.wsdl_cache_enabled", "0");
		
			
		$client = new  SoapClient($url, array('login' => $uid, 
          	'password' => $sign));

		//sending the user name ,password mode will work even if security is disabled at the provider
		
		print_r($client->__call( $method,
        /* Parameters */
        array(
            new SoapParam(
                /* Parameter Value */
                5,
                /* Parameter Name */
                "symbol"
        	))
        ));

		
	}else{

		$client = new soapclient2($url,true);
		$client->setCredentials($uid,$sign);
	
		// Check for an error
		$err = $client->getError();
		if ($err) {
	    // Display the error
	    	echo '<h2>Constructor error</h2><pre>' . $err . '</pre><br />';
	    // At this point, you know the call that follows will fail
		}

		$result = $client->call($method, array('limit' => 5));
		
		// Check for a fault
		if ($client->fault) {
	    	echo '<h2>Fault</h2><pre>';
	    	print_r($result);
	   		echo '</pre>';
		} else {
	    // Check for errors
	    	$err = $client->getError();
	    	if ($err) {
	        // Display the error
	        	echo '<h2>Error</h2><pre>' . $err . '</pre>';
	    	} else {
	    		echo '<h2>Result</h2><pre>' ;
	    		print_r($result);
	    		echo '</pre>';
	    	}
		}
	}
}

function shn_ws_get_methods($mod="or"){
	global $global;
	$methods=array();
	$xml_file=$global['approot']."/mod/".$mod."/ws.xml";
	//read the XML file describing the types and services for that module.
	$xml =simplexml_load_file($xml_file);
	foreach ($xml->services->service as $service) {
   		$name= trim($service->name);//name of the service
   		$function=trim($service->api_function);//function that is exposed
   		$methods["$function"]=$name."->".$function;
	}
	return $methods;
}

	/**
	* collapse entities, e.g. changes '&lt;' to '<'.
	*
	* @param	string	$val	The string in which to expand entities.
	* @access	private
	*/
	function collapseEntities($val) {
		
			$val = str_replace('&amp;', '&', $val);
	    	/*
	    	$val = str_replace("'", '&apos;', $val);
	    	$val = str_replace('"', '&quot;', $val);
	    	$val = str_replace('<', '&lt;', $val);
	    	$val = str_replace('>', '&gt;', $val);
	    	*/
	    
	    return $val;
	}
?>
