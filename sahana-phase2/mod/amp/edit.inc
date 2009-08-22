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



function shn_amp_sahana_edit_load_method($new_wsdl_url){
	global $global;
	shn_form_fopen("load_edit_result_add",null,array('req_message'=>false));
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
	shn_form_fsopen(_t("Edit Mashup"));
	//$_SESSION['edit_url']=null;
	?>

<div
	id="n_sec_div">
<div class="info"><?php echo  _t("If the web service provider requires authentication ,then switch to secure mode")?></div>
	<?php
	$button_opts="onclick=\"switchMode('n_sec_div','ap_div','mode','sec');\"";
	shn_form_button("Switch to Secure Authentication Mode",$button_opts , null);
	?> <!-- <a href="#" onclick="switchMode('no_sec_div','api_div','mode','sec');">Switch to Secure Authentication Mode</a>-->

</div>
<br />
<div id="ap_div"><?php
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
        switchMode('ap_div','n_sec_div','mode','no_sec');
    </script>
<center><?php

//create the submit button
shn_form_submit(_t("Edit Mashup"));
?></center>
<?php
shn_form_fclose();
$_SESSION['sec_flag']=false;
 

}	
}


function shn_amp_load_edit_result_add(){

	$method=trim($_SESSION['amp_service']);
	echo '<h2>Masup Edit Mode</h2><br />';
	$native=extension_loaded('soap');
	
	$url=trim($_POST["wsdl_url"]);
	$url= trim(html_entity_decode($url));

	//$url="http://localhost/week1/WS1/www/index.php?wsdl&stream=soap&wbsmod=or&mod=ws&act=reg";

	$digest="{$_SERVER['REQUEST_TIME']}$method";
	$secret=trim($_POST["secret"]);
	$sign=shn_acl_hmac_sha1($digest,$secret);
	$sign=md5($sign);
	$uid=trim($_POST["key"]).",".trim($_POST["pwd"]).",$digest";
	$_SESSION['edit_parm']='true';

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
			//_shn_amp_save_mashup();
			_shn_amp_edit_add_url();
			_shn_amp_delete_ws_ins();
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


function _shn_amp_edit_add_url(){

shn_form_fopen("locate_edit_ws_add",null,array('req_message'=>false));
shn_form_fsopen(_t("Add Another Instense"));
//shn_form_select($methods,"Methods",'method',null,array('br'=>false));
//shn_form_hidden(array('wbsmod'=>$_POST['method'],'wsdl_url'=>$url));
shn_form_submit(_t('Add URL>>'));
shn_form_fsclose();
shn_form_fclose();

}



function _shn_amp_delete_ws_ins(){

global $global;
$db = $global['db'];
$mashup_uuid=$_SESSION['mashup_uuid'];
$query = "SELECT url FROM amp_mashup_url where mashup_uuid='$mashup_uuid'";
$res=$db->Execute($query);


 $mashupurl_list=array();

    while((!$res==NULL) && (!$res->EOF)) {
   
    	    $mashupurl_list[$res->fields["url"]] =$res->fields["url"];
    		$res->MoveNext();
    }


shn_form_fopen('delete_inws',null,array("req_message"=>false));
	//$methods=shn_amp_get_methods($filtered);
	shn_form_fsopen(_t("Delete Instense"));
	shn_form_select($mashupurl_list,"Mashup Instense URL",'mashup_iurl',null,array('br'=>false));
	shn_form_submit(_t('Delete instense >>'));	
	shn_form_fsclose();
	shn_form_fclose();

}


function shn_amp_delete_inws(){

global $global;
$db = $global['db'];
$mashup_inst_url=$_POST['mashup_iurl'];
$mashup_uuid=$_SESSION['mashup_uuid'];
$query = "DELETE FROM amp_mashup_url WHERE mashup_uuid='$mashup_uuid' AND url='$mashup_inst_url'";
$res=$db->Execute($query);

if($res==false){
$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $query);
		display_errors();
}


}



function shn_amp_locate_edit_ws_add(){

?>
<h2><?php echo  _t('Access another SAHANA system through web services')?></h2>
	

<div id="formcontainer"><?php
$_SESSION['sec_flag']='true';
shn_form_fopen("sahana_edit_load_method_add");
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

function shn_amp_sahana_edit_load_method_add(){


	global $global;
	// parse the wsdl and get it's components
	$url = $_POST['wsdl_url'];
	
	//$_SESSION['url']=$url ;
	$url=$url."index.php?wsdl&stream=soap&wbsmod=".$_SESSION['wbsmod']."&mod=ws&act=reg";
	$_SESSION['edit_url'][0]="edited url";
	$_SESSION['edit_url'][sizeof($_SESSION['edit_url'])]=$url;
	
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

}


function shn_amp_sahana_edit_save(){


	global $global;
	$db = $global['db']; 

$mashup_uuid=$_SESSION['mashup_uuid'];
if($_SESSION['add_delurl']=='true'){

for($p=1;$p<sizeof($_SESSION['amp_url']);$p++){
	$url=$_SESSION['amp_url'][$p];
	$query = "INSERT INTO amp_mashup_url VALUES('$mashup_uuid','$url')";
 	$db->Execute($query);
	echo '<h2>Save Successful</h2><br/>';
}

}else{

for($p=1;$p<sizeof($_SESSION['edit_url']);$p++){
	$url=$_SESSION['edit_url'][$p];
	$query = "INSERT INTO amp_mashup_url VALUES('$mashup_uuid','$url')";
 	$db->Execute($query);
	echo '<h2>Save Successful</h2><br/>';
}
	}
}

function _shn_amp_locate_edit_ws_save(){

?>

<div><?php
shn_form_fopen("sahana_edit_save",null,array('req_message'=>false));
shn_form_fsopen(_t("Save Edited Mashup"));
shn_form_submit(_t("Save Mashup >> "));
shn_form_fsclose();

?> <?php
//close the form

shn_form_fclose();
?></div>
<?php

}

?>

