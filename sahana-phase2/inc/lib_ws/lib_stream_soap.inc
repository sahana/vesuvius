<?php
/* $Id: lib_stream_soap.inc,v 1.2 2009-08-22 17:17:25 ravithb Exp $ */

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

	//at this point , the web service call has passed basic authentication
	
	global $server;
	global $global;
	global $conf;
	require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');
	$server = new soap_server();
	require_once($global['approot'].'/mod/ws/main.inc');
	//the initiliazation stuff is done, now bulk of the work is done in the shn_soap_ws_reg() method
	
}

function shn_stream_close(){
	global $server;
	global $HTTP_RAW_POST_DATA;// its essential to make this global, otherwise no content
	$server->service($HTTP_RAW_POST_DATA); //starts the service with SOAP (RAW HTTP) data

}





