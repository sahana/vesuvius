<?php
global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_xml.inc";
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');

function shn_amp_sahana_cr(){

	$method=trim($_POST["method"]);
	echo '<h2>Method</h2><pre>' . $method . '</pre><br />';
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

			$client = new  SoapClient(html_entity_decode($url), array('login' => $uid,
          	'password' => $sign));
			echo '<h2>TEST CASE</h2><pre>' . $client . '</pre><br />';
			//sending the user name ,password mode will work even if security is disabled at the provider


//var_dump($param_array);
			print_r($client->__call($method,$param_array));


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

