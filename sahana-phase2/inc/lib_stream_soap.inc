<?php
/* $Id: lib_stream_soap.inc,v 1.12 2007-09-04 00:17:22 ravids Exp $ */

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
		/* If the WSDL is requested, we do not perform any authentication
		 * Thus lets first find if wsdl is in the query string
		 */
		global $HTTP_SERVER_VARS;

		if (isset($_SERVER['QUERY_STRING'])) {
			$qs = $_SERVER['QUERY_STRING'];
		} elseif (isset($HTTP_SERVER_VARS['QUERY_STRING'])) {
			$qs = $HTTP_SERVER_VARS['QUERY_STRING'];
		} else {
			$qs = '';
		}
		

		if (ereg('wsdl', $qs) ){
			// wsdl is requested, thus skip authentication
		}else{
			/* HTTP basic authentication
			 * Since i wanted to authenticate based on the following policy, had to use the basic authentication
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
			 * As a work around md5 hash is applied to the signature and sent , and doing the comparison also md5 is used at the last stage.
			 * 
			 */
			if (!isset($_SERVER['PHP_AUTH_USER'])) {
				/*
				 * send the basic authentication challenge
				 */
		    	header('WWW-Authenticate: Basic realm="Sahana"');                   
		    	header("HTTP/1.0 401 Unauthorized");
			}else{
				
				$arg1=explode(",", trim($_SERVER['PHP_AUTH_USER']));
				$sign=$_SERVER['PHP_AUTH_PW'];
				$digest=$arg1[2];
				/*
				 * authenticate the user using the API Key and Password, if succeeds returns the secret for that user
				 */
				$secret=shn_authenticate_ws_user($arg1[0],$arg1[1]);
				if($secret==null){
					header("HTTP/1.0 401 Unauthorized");
					return;
				}else{
					/*
					 * Verify the signature to ensure the digest was signed using the same secret the server is having in its database
					 */
					if(shn_authenticate_ws_signature($secret,$sign,$digest)==false){
						header("HTTP/1.0 401 Unauthorized");
						return;
					}
				}
			}
	}
		
	//at this point , the web service call has passed basic authentication
	
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
	//the initiliazation stuff is done, now bulk of the work is done in the shn_soap_ws_reg() method
	
}

function shn_stream_close(){
	global $server;
	global $HTTP_RAW_POST_DATA;// its essential to make this global, otherwise no content
	$server->service($HTTP_RAW_POST_DATA); //starts the service with SOAP (RAW HTTP) data

}




?>
