<?php
/* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     H Iroshan <iroshanmail@gmail><http://www.fosspirit.blogspot.com>
* @package    sahana
* @subpackage amp
*/

include_once $global['approot']."/inc/lib_xml.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
include_once $global['approot'].'/inc/lib_table.inc';
require_once "reg.inc";
include_once $global['approot']."/inc/lib_uuid.inc";
include_once $global['approot']."/mod/amp/edit.inc";
include_once $global['approot']."/mod/amp/save.inc";
include_once $global['approot']."/mod/amp/view.inc";



function shn_amp_locate_ws(){

?>
<h2><?php echo  _t('Access another SAHANA system through web services')?></h2>
	

<div id="formcontainer"><?php
$_SESSION['sec_flag']='true';
$_SESSION['edit_parm']='false';
if($_POST['status']==null){
$_SESSION['add_delurl']='false';
}else{

$_SESSION['add_delurl']='true';
}
shn_form_fopen("sahana_load_method");
shn_form_fsopen(_t("Create New Mashup"));
shn_form_text(_t("Sahana Instense URL: "),'wsdl_url','size="50"',array('br'=>false));
shn_form_submit(_t("Load Modules >> "));
shn_form_fsclose();

?> <?php
//close the form

shn_form_fclose();
//shn_amp_select_mashup();
?></div>
<?php

}

function shn_amp_get_methods($mod="home"){
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



function shn_amp_sahana_load_method(){
	global $global;
	// parse the wsdl and get it's components
	$_SESSION['url']=null;
	///shn_form_fopen("load_result_add",null,array('req_message'=>false));
	$url = $_POST['wsdl_url'];
	$_SESSION['url']=$url ;
	$_SESSION['cstatus']='true';
	$url=$url."index.php?wsdl&stream=soap&wbsmod=amp&mod=ws&act=reg";
	
	if(strlen(trim($url))==0){
		add_error(_t("Please enter a WSDL Url."));
		shn_amp_locate_ws();
		return;
	}

	// split the wsdl module value
	$components = parse_url($url);
	$startidx = stripos($components['query'],"wbsmod=");
	$endidx = stripos($components['query'],"&",$startidx);
	$filtered = substr($components['query'],$startidx+7,($endidx-($startidx+7)));
	$_SESSION['filtered']=$filtered;
	//shn_form_fopen('sahana_load_method',null,array("req_message"=>false));
	$methods=shn_amp_get_methods($filtered);
	shn_form_fopen("sahana_cr",null,array('req_message'=>false));
	$mod = $filtered;

	$method = "shn_amp_get_mods";
	shn_form_fsopen($method);
   	 $wsdl_url=$url;
	$xml_file=$global['approot']."/mod/".$mod."/ws.xml";
	//read the XML file describing the types and services for that module.
	$xml =simplexml_load_file($xml_file);
	$target = null;
	foreach ($xml->services->service as $service) {
		//var_dump($service);
		$function=trim($service->api_function);//function that is exposed

		if(strcasecmp($function,$method)==0){
			$target = $service;
			break;
		}
	}
	$input_form=$xml->services->service->input_form;
	//echo $input_form;
    shn_form_hidden(array("method"=>$method,"wbsmod"=>$mod,"wsdl_url"=>$wsdl_url));
    if($input_form=="true"){
    	include_once $global['approot']."mod/".$mod."/api.inc";
    	$function="shn_".$mod."_amp_default";
    	$function();
    }
    else{
	if(count($target->params->param)>0){
		echo "<h2>"._t(sprintf("Method : %s",$method))."</h2>";

		shn_form_fsopen(_t("Method Parameters"));

		// process the target
		$counter = 0;
		foreach ($target->params->param as $param){
			$name = "";
			foreach($param->attributes()as $attr=>$name){
				// just to oset the $name
			}
			shn_form_text(($name!=null)?$name:_t(sprintf("Param-%d",$counter)),"param".$counter);
			echo "<br/>";
			$counter ++;
		}
			
		shn_form_fsclose();
		
	}
    }
 
    
   if($_SESSION['sec_flag']=='true'){
	shn_form_fsopen(_t("Security"));
	?>

<div
	id="no_sec_div">
<div class="info"><?php echo  _t("If the web service provider requires authentication ,then switch to secure mode")?></div>
	<?php
	$button_opts="onclick=\"switchMode('no_sec_div','api_div','mode','sec');\"";
	shn_form_button("Switch to Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('no_sec_div','api_div','mode','sec');">Switch to Secure Authentication Mode</a>-->

</div>
<br />
<div
	id="api_div"><?php
	$button_opts="onclick=\"switchMode('api_div','no_sec_div','mode','no_sec');\"";
	shn_form_button("Switch off Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('api_div','no_sec_div','mode','no_sec');">Switch off Secure Authentication Mode</a>-->
<br />
<div class="info"><?php echo  _t("The API Key allows you to access the web services of another SAHANA instance which requires authentication. To access SAHANA web services, a developer must have a login(an account).
    That is you should have an API Key,a password and a Secret Access Code. The API Key and password, which is associated with your login, is used in requests to identify the party responsible for the request." .
        " However, because both the API Key and password is sent as a request parameter, it is not secret and could be used by anyone sending a request to SAHANA web service. Therefore to improve the security(reduce impersonation attacks), a request signature is calculated using the Secret Access Code. The Secret Access Code is a automatically generated 32-character alphanumeric sequence.");?>
</div>
<br />
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


	?></div>
<script type="text/javascript">
        switchMode('api_div','no_sec_div','mode','no_sec');
    </script>
<center><?php

//create the submit button
shn_form_submit(_t("View Result ..."));
?></center>
<?php
shn_form_fclose();
$_SESSION['sec_flag']=false;
}
}



function shn_amp_sahana_cr(){

	$method=trim($_POST["method"]);
	echo '<h2>Modules</h2><pre></pre><br />';
	$native=extension_loaded('soap');
	
	$url=trim($_POST["wsdl_url"]);
	$url= trim(html_entity_decode($url));

	//$url="http://localhost/week1/WS1/www/index.php?wsdl&stream=soap&wbsmod=or&mod=ws&act=reg";

	$digest="{$_SERVER['REQUEST_TIME']}$method";
	$secret=trim($_POST["secret"]);
	$sign=shn_acl_hmac_sha1($digest,$secret);
	$sign=md5($sign);
	$uid=trim($_POST["key"]).",".trim($_POST["pwd"]).",$digest";
	$filterd= $_SESSION['filtered'];
	
	try{
		if($native==true){
			ini_set("soap.wsdl_cache_enabled", "0");
			$param_array = array();

			foreach($_POST as $key=>$val){
				$value = $_POST[$key];
				
				//echo "$key<br/>";
				if(strlen(trim($value))>0){
					if(preg_match('/param\d/i',$key)){
						array_push($param_array,new SoapParam($value,$key));
					}
				}
			}

			$client = new  SoapClient(html_entity_decode($url), array('login' => $uid,
          	'password' => $sign));
			
			//sending the user name ,password mode will work even if security is disabled at the provider

			

			$modules=$client->__call($method,$param_array);
			shn_amp_select_module($modules,$filtered);

		}else{

			$client = new soapclient2($url,true);
			$client->setCredentials($uid,$sign);

			$param_array = array();
			foreach($_POST as $key=>$value){
				if(preg_match('/param\d/i',$key)){
					$param_array[$key] = $value;
				}
			}

			// Check for an error
			$err = $client->getError();
			if ($err) {
				// Display the error
				echo '<h2>Constructor error</h2><pre>' . $err . '</pre><br />';
				// At this point, you know the call that follows will fail
			}

			//$result = $client->call($method, array('limit' => 5));
			
			$result = $client->call($method, $param_array);

			$modules=$client->__call($method,$param_array);
			shn_amp_select_module($modules,$filtered);
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
	}catch(Exception $e){
		//echo $e->getMessage();
		//if('Unauthorized'==$e->getMessage())
		add_error($e->getMessage());
		display_errors('Error');
	}
}

function shn_amp_select_module($modules,$filtered){
	$item="item";
	$mod=array();
	for($i=0;$i<sizeof($modules);$i++){
	$arr = $modules[$i]->$item;
	if($arr[0]=="amp")
	continue;
	$mod[$arr[0]]=$arr[1];
	
	
	}
	
	shn_form_fopen('sahana_load_wsdl',null,array("req_message"=>false));
	$methods=shn_amp_get_methods($filtered);
	shn_form_fsopen(_t("Select Modules"));
	shn_form_select($mod,"Modules",'method',null,array('br'=>false));
	shn_form_hidden(array('wbsmod'=>$filtered,'wsdl_url'=>$url));
	shn_form_submit(_t('Load Method >>'));	
	shn_form_fsclose();
}

function shn_amp_sahana_load_wsdl(){
	
	// parse the wsdl and get it's components
	$url = $_SESSION['url']."index.php?wsdl&stream=soap&wbsmod=".$_POST['method']."&mod=ws&act=reg";
	if(strlen(trim($url))==0){
		add_error(_t("Please enter a WSDL Url."));
		//shn_amp_sahana();
		return;
	}

	// split the wsdl module value
	$components = parse_url($url);
	$startidx = stripos($components['query'],"wbsmod=");
	$endidx = stripos($components['query'],"&",$startidx);
	$filtered = substr($components['query'],$startidx+7,($endidx-($startidx+7)));

	shn_form_fopen('sahana_load_other_method',null,array("req_message"=>false));
	$methods=shn_amp_get_methods($filtered);
	shn_form_fsopen(_t("Select Method"));
	shn_form_select($methods,"Methods",'method',null,array('br'=>false));
	shn_form_hidden(array('wbsmod'=>$_POST['method'],'wsdl_url'=>$url));
	shn_form_submit(_t('Load Method >>'));
	shn_form_fsclose();

	shn_form_fclose();
}

function shn_amp_sahana_load_other_method(){
	global $global;

	shn_form_fopen("load_result",null,array('req_message'=>false));
	$mod = $_POST['wbsmod'];
	$_SESSION['wbsmod']=$mod;
	$method = $_POST['method'];
	
	$_SESSION['service'] = $method;
	$wsdl_url=$_POST['wsdl_url'];
	$xml_file=$global['approot']."/mod/".$mod."/ws.xml";
	//read the XML file describing the types and services for that module.
	$xml =simplexml_load_file($xml_file);
	$target = null;
	foreach ($xml->services->service as $service) {
		//var_dump($service);
		$function=trim($service->api_function);//function that is exposed

		if(strcasecmp($function,$method)==0){
			$target = $service;
			break;
		}
	}
	$input_form=$xml->services->service->input_form;
	//echo $input_form;
    shn_form_hidden(array("method"=>$method,"wbsmod"=>$mod,"wsdl_url"=>$wsdl_url));
    if($input_form=="true"){
    	include_once $global['approot']."mod/".$mod."/api.inc";
    	$function="shn_".$mod."_ws_default";
    	$function();
    }
    else{

echo 'inside';
	if(count($target->params->param)>0){
		echo "<h2>"._t(sprintf("Method : %s",$method))."</h2>";

		shn_form_fsopen(_t("Method Parameters"));

		// process the target
		$counter = 0;
		foreach ($target->params->param as $param){
			$name = "";
			foreach($param->attributes()as $attr=>$name){
				// just to oset the $name
			}
			shn_form_text(($name!=null)?$name:_t(sprintf("Param-%d",$counter)),"param".$counter);
			echo "<br/>";
			$counter ++;
		}
		
		shn_form_fsclose();
	}
    }

	shn_form_fsopen(_t("Security"));
	?>

<div
	id="no_sec_div">
<div class="info"><?php echo  _t("If the web service provider requires authentication ,then switch to secure mode")?></div>
	<?php
	$button_opts="onclick=\"switchMode('no_sec_div','api_div','mode','sec');\"";
	shn_form_button("Switch to Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('no_sec_div','api_div','mode','sec');">Switch to Secure Authentication Mode</a>-->

</div>
<br />
<div
	id="api_div"><?php
	$button_opts="onclick=\"switchMode('api_div','no_sec_div','mode','no_sec');\"";
	shn_form_button("Switch off Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('api_div','no_sec_div','mode','no_sec');">Switch off Secure Authentication Mode</a>-->
<br />
<div class="info"><?php echo  _t("The API Key allows you to access the web services of another SAHANA instance which requires authentication. To access SAHANA web services, a developer must have a login(an account).
    That is you should have an API Key,a password and a Secret Access Code. The API Key and password, which is associated with your login, is used in requests to identify the party responsible for the request." .
        " However, because both the API Key and password is sent as a request parameter, it is not secret and could be used by anyone sending a request to SAHANA web service. Therefore to improve the security(reduce impersonation attacks), a request signature is calculated using the Secret Access Code. The Secret Access Code is a automatically generated 32-character alphanumeric sequence.");?>
</div>
<br />
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


	?></div>
<script type="text/javascript">
        switchMode('api_div','no_sec_div','mode','no_sec');
    </script>
<center><?php

//create the submit button
shn_form_submit(_t("View Result ..."));
?></center>
<?php

shn_form_fclose();
}

function shn_amp_load_result(){

	$method=trim($_POST["method"]);
	echo '<h2>Masup generated service</h2>';
	$native=extension_loaded('soap');
	
	$url=trim($_POST["wsdl_url"]);
	$url= trim(html_entity_decode($url));

	//$url="http://localhost/week1/WS1/www/index.php?wsdl&stream=soap&wbsmod=or&mod=ws&act=reg";

	$digest="{$_SERVER['REQUEST_TIME']}$method";
	$secret=trim($_POST["secret"]);
	$sign=shn_acl_hmac_sha1($digest,$secret);
	$sign=md5($sign);
	$uid=trim($_POST["key"]).",".trim($_POST["pwd"]).",$digest";

	try{
		if($native==true){
			ini_set("soap.wsdl_cache_enabled", "0");
			$param_array = array();

			foreach($_POST as $key=>$val){
				$value = $_POST[$key];
				//echo "$key<br/>";
				if(strlen(trim($value))>0){
					if(preg_match('/param\d/i',$key)){
						array_push($param_array,new SoapParam($value,$key));
					}
				}
			}


			
			
			$_SESSION['amp_service']=$method;
			$_SESSION['amp_url']=null;
			$_SESSION['amp_url'][0]="hold_amp_url_list";
			_shn_amp_check_url_aded($_SESSION['amp_url'],$url);
			
			
			
			for($p=1;$p<sizeof($_SESSION['amp_url']);$p++){
			$client = new  SoapClient(html_entity_decode($_SESSION['amp_url'][$p]), array('login' => $uid,
          	'password' => $sign));
			
			$results=$client->__call($method,$param_array);
			//var_dump($results);					
			shn_amp_view_result($results);
			
			//
			
			}

		if($_SESSION['add_delurl']=='true'){
		
		_shn_amp_locate_edit_ws_save();
		}else{
			_shn_amp_save_mashup();
		}
			_shn_amp_add_url();
		}else{

			$client = new soapclient2($url,true);
			$client->setCredentials($uid,$sign);

			$param_array = array();
			foreach($_POST as $key=>$value){
				if(preg_match('/param\d/i',$key)){
					$param_array[$key] = $value;
				}
			}

			// Check for an error
			$err = $client->getError();
			if ($err) {
				// Display the error
				echo '<h2>Constructor error</h2><pre>' . $err . '</pre><br />';
				// At this point, you know the call that follows will fail
			}

			//$result = $client->call($method, array('limit' => 5));
			
			$result = $client->call($method, $param_array);
			shn_amp_view_result($results);
			//
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
	}catch(Exception $e){
		//echo $e->getMessage();
		//if('Unauthorized'==$e->getMessage())
		add_error($e->getMessage());
		display_errors('Error');
	}
}


function _shn_amp_add_url(){
shn_form_fopen("locate_ws_add",null,array('req_message'=>false));
shn_form_fsopen(_t("Add Another Instense"));
//shn_form_select($methods,"Methods",'method',null,array('br'=>false));
//shn_form_hidden(array('wbsmod'=>$_POST['method'],'wsdl_url'=>$url));
shn_form_submit(_t('Add URL>>'));
shn_form_fsclose();
shn_form_fclose();

}




function shn_amp_load_other_url(){

	$method=trim($_POST["method"]);
	echo '<h2>Method</h2><pre>' . $method . '</pre><br />';
	$native=extension_loaded('soap');
	$url=$_POST["wsdl_url"]."index.php?wsdl&stream=soap&wbsmod=".$_POST['method']."&mod=ws&act=reg";
	$url=trim($url);
	$url= trim(html_entity_decode($url));

	//$url="http://localhost/week1/WS1/www/index.php?wsdl&stream=soap&wbsmod=or&mod=ws&act=reg";

	$digest="{$_SERVER['REQUEST_TIME']}$method";
	$secret=trim($_POST["secret"]);
	$sign=shn_acl_hmac_sha1($digest,$secret);
	$sign=md5($sign);
	$uid=trim($_POST["key"]).",".trim($_POST["pwd"]).",$digest";


	try{
		if($native==true){
			ini_set("soap.wsdl_cache_enabled", "0");
			$param_array = array();

			foreach($_POST as $key=>$val){
				$value = $_POST[$key];
				//echo "$key<br/>";
				if(strlen(trim($value))>0){
					if(preg_match('/param\d/i',$key)){
						array_push($param_array,new SoapParam($value,$key));
					}
				}
			}

			$client = new  SoapClient(html_entity_decode($url), array('login' => $uid,
          	'password' => $sign));

			//sending the user name ,password mode will work even if security is disabled at the provider

			
//var_dump($param_array);
			
			
			$results=$client->__call($method,$param_array);
			shn_amp_view_result($results);
			//
			
		}else{

			$client = new soapclient2($url,true);
			$client->setCredentials($uid,$sign);

			$param_array = array();
			foreach($_POST as $key=>$value){
				if(preg_match('/param\d/i',$key)){
					$param_array[$key] = $value;
				}
			}

			// Check for an error
			$err = $client->getError();
			if ($err) {
				// Display the error
				echo '<h2>Constructor error</h2><pre>' . $err . '</pre><br />';
				// At this point, you know the call that follows will fail
			}

			//$result = $client->call($method, array('limit' => 5));
			
			$result = $client->call($method, $param_array);
			shn_amp_view_result($results);
			//
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
	}catch(Exception $e){
		//echo $e->getMessage();
		//if('Unauthorized'==$e->getMessage())
		add_error($e->getMessage());
		display_errors('Error');
	}
}


function _shn_amp_check_url_aded($url_array,$currunt_url){
$count=-1;

for($i=1;$i<sizeof($url_array);$i++)	{
	if (strcmp($url_array[$i], $currunt_url) == 0) {
   		//dont put in to the session array

   	 	$count=0;
   		break;
      	 }
    }
    if($count==-1){
  	 $_SESSION['amp_url'][sizeof($url_array)]=$currunt_url;
   
	
	}
}


function shn_amp_locate_ws_add(){

?>
<h2><?php echo  _t('Access another SAHANA system through web services')?></h2>
	

<div id="formcontainer"><?php
$_SESSION['sec_flag']='true';
shn_form_fopen("sahana_load_method_add");
shn_form_fsopen(_t("Add New Instense to Mashup"));
shn_form_text(_t("Sahana Instense URL: "),'wsdl_url','size="50"',array('br'=>false));
shn_form_submit(_t("Load Modules >> "));
shn_form_fsclose();

?> <?php
//close the form

shn_form_fclose();
?></div>
<?php

}

function shn_amp_sahana_load_method_add(){


	global $global;
	// parse the wsdl and get it's components
	$url = $_POST['wsdl_url'];
	
	$_SESSION['url']=$url ;
	$url=$url."index.php?wsdl&stream=soap&wbsmod=".$_SESSION['wbsmod']."&mod=ws&act=reg";
	echo 'service'.$_SESSION['wbsmod'];
	if(strlen(trim($url))==0){
		add_error(_t("Please enter a WSDL Url."));
		shn_amp_locate_ws();
		return;
	}

	// split the wsdl module value
	$components = parse_url($url);
	$startidx = stripos($components['query'],"wbsmod=");
	$endidx = stripos($components['query'],"&",$startidx);
	$filtered = substr($components['query'],$startidx+7,($endidx-($startidx+7)));
	$_SESSION['filtered']=$filtered;
	//shn_form_fopen('sahana_load_method',null,array("req_message"=>false));
	$methods=shn_amp_get_methods($filtered);

	shn_amp_sahana_load_other_method_add($url);
	//shn_form_fopen("sahana_load_other_method_add",null,array('req_message'=>false));



	//shn_form_hidden(array("wbsmod"=>$mod,"wsdl_url"=>$wsdl_url));

	//shn_form_submit(_t("View Result ..."));
	//shn_form_fclose();
}

function shn_amp_sahana_cr_add(){

	/*$method=trim($_POST["method"]);
	echo '<h2>Modules</h2><pre></pre><br />';
	
	$native=extension_loaded('soap');
	
	$url=trim($_POST["wsdl_url"]);
	echo "ESDL URL ---> ".$url;
	$url= trim(html_entity_decode($url));

	*/

	//shn_amp_sahana_load_other_method_add();
}


function shn_amp_sahana_load_other_method_add($new_wsdl_url){
	global $global;
	shn_form_fopen("load_result_add",null,array('req_message'=>false));
	$mod = $_SESSION['wbsmod'];
	$method = $_SESSION['amp_service'];
	$_SESSION['service'] =$new_wsdl_url;
	$wsdl_url=$new_wsdl_url;

	$xml_file=$global['approot']."mod/".$mod."/ws.xml";
	
	//read the XML file describing the types and services for that module.
	$xml =simplexml_load_file($xml_file);
	$target = null;
	foreach ($xml->services->service as $service) {
		//var_dump($service);
		
		$function=trim($service->api_function);//function that is exposed

		if(strcasecmp($function,$method)==0){
			$target = $service;
			break;
		}
	}
	$input_form=$xml->services->service->input_form;
	//echo $input_form;
    shn_form_hidden(array("method"=>$method,"wbsmod"=>$mod,"wsdl_url"=>$wsdl_url));
    if($input_form=="true"){
    	include_once $global['approot']."mod/".$mod."/api.inc";
    	$function="shn_".$mod."_ws_default";
    	$function();
    }
    else{

if($_SESSION['edit_parm']=='false'){
	if(count($target->params->param)>0){
		echo "<h2>"._t(sprintf("Method : %s",$method))."</h2>";

		shn_form_fsopen(_t("Method Parameters"));

		// process the target
		$counter = 0;
		foreach ($target->params->param as $param){
			$name = "";
			foreach($param->attributes()as $attr=>$name){
				// just to oset the $name
			}
			shn_form_text(($name!=null)?$name:_t(sprintf("Param-%d",$counter)),"param".$counter);
			echo "<br/>";
			$counter ++;
		}
		
		shn_form_fsclose();
	}
    }
    
  }
	if($_SESSION['sec_flag']=='true'){
	shn_form_fsopen(_t("Security"));
	
	?>

<div
	id="no_sec_div">
<div class="info"><?php echo  _t("If the web service provider requires authentication ,then switch to secure mode")?></div>
	<?php
	$button_opts="onclick=\"switchMode('no_sec_div','api_div','mode','sec');\"";
	shn_form_button("Switch to Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('no_sec_div','api_div','mode','sec');">Switch to Secure Authentication Mode</a>-->

</div>
<br />
<div
	id="api_div"><?php
	$button_opts="onclick=\"switchMode('api_div','no_sec_div','mode','no_sec');\"";
	shn_form_button("Switch off Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('api_div','no_sec_div','mode','no_sec');">Switch off Secure Authentication Mode</a>-->
<br />
<div class="info"><?php echo  _t("The API Key allows you to access the web services of another SAHANA instance which requires authentication. To access SAHANA web services, a developer must have a login(an account).
    That is you should have an API Key,a password and a Secret Access Code. The API Key and password, which is associated with your login, is used in requests to identify the party responsible for the request." .
        " However, because both the API Key and password is sent as a request parameter, it is not secret and could be used by anyone sending a request to SAHANA web service. Therefore to improve the security(reduce impersonation attacks), a request signature is calculated using the Secret Access Code. The Secret Access Code is a automatically generated 32-character alphanumeric sequence.");?>
</div>
<br />
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


	?></div>
<script type="text/javascript">
        switchMode('api_div','no_sec_div','mode','no_sec');
    </script>
<center><?php

//create the submit button
shn_form_submit(_t("View Result ..."));
?></center>
<?php

shn_form_fclose();
  
 // $_SESSION['sec_flag']='false';
 
shn_form_fopen('delete_mashup',null,array("req_message"=>false));
	shn_form_fsopen(_t("Delete Mashup"));
	shn_form_submit(_t('Delete Mashup >>'));	
	shn_form_fsclose();
	shn_form_fclose();
	
shn_amp_sahana_edit_load_method($new_wsdl_url);
}	
}


function shn_amp_load_result_add(){


	$method=trim($_SESSION['amp_service']);
	echo '<h2>Masup generated service</h2><br />';
	$native=extension_loaded('soap');
	
	$url=trim($_POST["wsdl_url"]);
	$url= trim(html_entity_decode($url));

	//$url="http://localhost/week1/WS1/www/index.php?wsdl&stream=soap&wbsmod=or&mod=ws&act=reg";

	$digest="{$_SERVER['REQUEST_TIME']}$method";
	$secret=trim($_POST["secret"]);
	$sign=shn_acl_hmac_sha1($digest,$secret);
	$sign=md5($sign);
	$uid=trim($_POST["key"]).",".trim($_POST["pwd"]).",$digest";

	try{
		if($native==true){
			ini_set("soap.wsdl_cache_enabled", "0");
			$param_array = array();

			foreach($_POST as $key=>$val){
				$value = $_POST[$key];
				//echo "$key<br/>";
				if(strlen(trim($value))>0){
					if(preg_match('/param\d/i',$key)){
						array_push($param_array,new SoapParam($value,$key));
					}
				}
			}

			_shn_amp_check_url_aded($_SESSION['amp_url'],$url);
			
		
			for($p=1;$p<sizeof($_SESSION['amp_url']);$p++){

			$client = new  SoapClient(html_entity_decode($_SESSION['amp_url'][$p]), array('login' => $uid,
          	'password' => $sign));
			
			$results=$client->__call($method,$param_array);
			
						
			shn_amp_view_result($results);
			
			//
			
			}
			_shn_amp_save_mashup();
			_shn_amp_locate_edit_ws_save();
			if($_SESSION['cstatus']=='true'){
			_shn_amp_add_url();
			}
		}else{

			$client = new soapclient2($url,true);
			$client->setCredentials($uid,$sign);

			$param_array = array();
			foreach($_POST as $key=>$value){
				if(preg_match('/param\d/i',$key)){
					$param_array[$key] = $value;
				}
			}

			// Check for an error
			$err = $client->getError();
			if ($err) {
				// Display the error
				echo '<h2>Constructor error</h2><pre>' . $err . '</pre><br />';
				// At this point, you know the call that follows will fail
			}

			//$result = $client->call($method, array('limit' => 5));
			
			$result = $client->call($method, $param_array);
			shn_amp_view_result($results);
			//
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
	}catch(Exception $e){
		//echo $e->getMessage();
		//if('Unauthorized'==$e->getMessage())
		add_error($e->getMessage());
		display_errors('Error');
	}
}




function shn_amp_select_mashup(){
	
global $global;
$db = $global['db'];
$user_id=$_SESSION['user_id'];
$query = "SELECT mashup_uuid,name FROM amp_mashup WHERE user_uuid=$user_id";
$res=$db->Execute($query);
//var_dump($res);
 $mashup_list=array();
$_SESSION['edit_parm']='true';
   // $type_list[] = array('Masup Names');
    while((!$res==NULL) && (!$res->EOF)) {
   
    	    $mashup_list[$res->fields["mashup_uuid"]] =$res->fields["name"];
    		$res->MoveNext();
    }

shn_form_fopen('show_mashup',null,array("req_message"=>false));
	//$methods=shn_amp_get_methods($filtered);
	shn_form_fsopen(_t("Saved Mashup"));
	shn_form_select($mashup_list,"Mashup",'mashup',null,array('br'=>false));
	shn_form_submit(_t('Load Mashup >>'));	
	shn_form_fsclose();
	shn_form_fclose();	
}


function shn_amp_delete_mashup(){
global $global;
$db = $global['db'];
try{
$mashup_uuid=$_SESSION['del_muid'];
$query1="DELETE FROM amp_mashup WHERE mashup_uuid='$mashup_uuid'";
$query2="DELETE FROM amp_mashup_url WHERE mashup_uuid='$mashup_uuid'";
$db->Execute($query2);
$db->Execute($query1);
echo '<h2>Masup Delete Sucessfully</h2>';
}catch(Exception $ex){
$ex->getMessage();

}

}
