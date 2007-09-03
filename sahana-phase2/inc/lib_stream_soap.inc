<?php
/* $Id: lib_stream_soap.inc,v 1.10 2007-09-03 09:48:40 ravids Exp $ */

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
