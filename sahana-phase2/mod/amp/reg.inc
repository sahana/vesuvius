<?php


global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_xml.inc";
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');





function shn_amp_api_key(){
	
	?>
<h2><?php echo  _t('Sign Up for the SAHANA API Key')?></h2>
<?php

?>  
<div class="info"><?php echo  _t("The API Key allows you to access the web services of this SAHANA instance for the domain you register with us. For each domain you need a separate Key. For the time being only one key per domain is issued. To access SAHANA web services, a developer must have a login(an account).
In this section , you are given an API Key,a password and a Secret Access Code. The API Key and password, which is associated with your login, is used in requests to identify the party responsible for the request." .
		" However, because both the API Key and password is sent as a request parameter, it is not secret and could be used by anyone sending a request to SAHANA web service. Therefore to improve the security(reduce impersonation attacks), a request signature is calculated using the Secret Access Code. The Secret Access Code is a automatically generated 32-character alphanumeric sequence.");?>
		 </div><br />
<?php
	$user=shn_current_user();
	if($user==null){
		add_error("You need to be logged in to continue");
		return;
	}else{
		echo "<strong><font color='green'>"._lc("You are logged in as ")."<font color='red'>".$_SESSION['user']."</font>"._lc(" to obtain the API key")."</font></strong>";
	}
    shn_form_fopen("api_key_step2");
    $label="SAHANA API terms of use";
    $extra_opts["value"]="SAHANA API terms of use";
    $text_opts ="readonly=\"readonly\" onfocus=\"this.blur()\"";  
    shn_form_fsopen($label); 
    shn_form_textarea("", "terms", $text_opts, $extra_opts);
	shn_form_fsclose();
    shn_form_fsopen(_t("Domain"));
    shn_form_text(_t("URL : "),'domain','size="50"',null);
    shn_form_fsclose();
  
   
   
?>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_t("Next"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_hidden(array('org_type'=>'1'));
    shn_form_fclose();
?>				     
</div>
<?php
	

}


function shn_amp_api_key_step2(){
	if(trim($_POST["domain"])==null){
		add_error("you need to specify the domain");
		shn_amp_api_key();
		return;
	}else{
		$_SESSION["amp_domain"]=trim($_POST["domain"]);
	}
	?>
<h2><?php echo  _t('Sign Up for the SAHANA API Key - Step 2')?></h2>
<?php

?>  
<div class="info"><?php echo  _t("The API Key allows you to access the web services of this SAHANA instance for the domain you register with us. For each domain you need a seperate Key. For the time being only one key per domain is issued. To access SAHANA web services, a developer must have a login(an account).
In this section , you are given an API Key,a password and a Secret Access Code. The API Key and password, which is associated with your login, is used in requests to identify the party responsible for the request." .
		" However, because both the API Key and password is sent as a request parameter, it is not secret and could be used by anyone sending a request to SAHANA web service. Therefore to improve the security(reduce impersonation attacks), a request signature is calculated using the Secret Access Code. The Secret Access Code is a automatically generated 32-character alphanumeric sequence.");?>
		 </div><br />
<div id="formcontainer">
<?php
	$key=md5(uniqid(rand(), true));
	$pwd=md5(uniqid(rand(), true));
	$code=md5(uniqid(rand(), true));
    shn_form_fopen("api_key_step3");
    add_warning("Make sure you write down the values of the API Key,password and Secret");
 	$text_opts ="readonly=\"readonly\"";
 	$extra_opts["value"]=$key;
    shn_form_fsopen("Your API Key"); 
    shn_form_textarea("", "key", $text_opts, $extra_opts);
	shn_form_fsclose();
	$extra_opts["value"]=$pwd;
	shn_form_fsopen("Your Password"); 
    shn_form_textarea("", "pwd", $text_opts, $extra_opts);
	shn_form_fsclose();
	$extra_opts["value"]=$code;
	shn_form_fsopen("Your Secret Code"); 
    shn_form_textarea("", "secret", $text_opts, $extra_opts);
	shn_form_fsclose();

  
   
   
?>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_t("Finish"));
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

function shn_amp_api_key_step3(){
	global $global;
	$db=$global['db'];
	$domain=$_SESSION["amp_domain"];
	$key=trim($_POST["key"]);
	$pwd=trim($_POST["pwd"]);
	$secret=trim($_POST["secret"]);
	$user=shn_current_user();
	$sql="insert into amp_keys(p_uuid,domain,api_key,password,secret) values('{$user}','{$domain}','{$key}','{$pwd}','{$secret}')";
	$res=$db->Execute($sql);
	$msg= "You can now use SAHANA web services using the API key,password and secret ";
    add_confirmation($msg);
}


