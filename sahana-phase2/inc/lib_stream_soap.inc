<?php
/* $Id: lib_stream_soap.inc,v 1.11 2007-09-03 11:09:07 ravids Exp $ */

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
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
global $global;
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
require_once($global['approot'].'/inc/lib_xml.inc');
require_once ($global['approot'].'inc/lib_security/lib_auth.inc');

function shn_stream_init(){
	/* HTTP basic authentication
	 * Since i wanted to authenticate based on the following policy, had to use the basic athentication
	 * credentials in an alternative way.
	 * Policy: In the process of signing up for the API key the following are issued
	 * 1. API key
	 * 2. Password
	 * 3. Secret Code
	 * API key and Password helps to identify the user. How ever, since these are transmitted in plain text
	 * needed something additional to prevent impersonation.
	 * Thus a digest is signed using HMAC_Sha1 algorithm and this signature is sent in the basic authentication.
	 * The digest is also , sent created using the time and few other values. How ever ,yet to write code to use those.
	 * Since the secret is shared only between the web server and user , only the user could have signed to be matched with the 
	 * signature created with the shared secret at the server applied on the digest.
	 * How ever with basic authentication, only two values could be sent, but here 4 values are being sent.
	 * API key, password and digest were sent as PHP_AUTH_USER seperated by comma.
	 * PHP_AUTH_PW contains the signature. How ever , there are restrictions on the characters that
	 * can be sent in PHP_AUTH_PW. Thus most of the time , only part of the wierd signature gets transmitted.
	 * Thus md5 hash is applied to the signature and sent , and doing the comparison also md5 is used at the last stage.
	 * 
	 */
	if (!isset($_SERVER['PHP_AUTH_USER'])) {
    	header('WWW-Authenticate: Basic realm="Sahana"');                   
    	header("HTTP/1.0 401 Unauthorized");
	}else{
		
		$arg1=explode(",", trim($_SERVER['PHP_AUTH_USER']));
		$sign=$_SERVER['PHP_AUTH_PW'];
		$digest=$arg1[2];
		$secret=shn_authenticate_ws_user($arg1[0],$arg1[1]);
		if($secret==null){
			header("HTTP/1.0 401 Unauthorized");
			return;
		}else{
			if(shn_authenticate_ws_signature($secret,$sign,$digest)==false){
				header("HTTP/1.0 401 Unauthorized");
				return;
			}
		}
	}

	
	global $server;
	global $global;
	global $conf;
	require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
	
	$mod=$_GET["wbsmod"];
	$ns="http://localhost/".$mod;
	$module_file = $global['approot'].'mod/'.$mod.'/api.inc';
    include($module_file);
	
	$nice_name=$conf['mod_'.$mod.'_name'];
	$server = new soap_server();
	$server->configureWSDL($nice_name.' Web Services',$ns);
	$server->wsdl->schemaTargetNamespace=$ns;



}
function shn_stream_close(){
	global $server;
	global $HTTP_RAW_POST_DATA;// its essential to make this global, otherwise no content
	$server->service($HTTP_RAW_POST_DATA);

}




?>
