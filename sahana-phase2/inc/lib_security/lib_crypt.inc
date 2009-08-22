<?php
/**
 *
 * This library helps in authentication ,but not authorization. A vital component of the framework.
 * Developers are required to use this library for security.
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

global $global;
require_once "constants.inc";
require_once ($global['approot'].'inc/lib_security/lib_auth.inc');
require_once "errors.inc";
define(ADODB_SESSION, $global['approot']."/3rd/adodb/session");
include_once ADODB_SESSION . '/crypt.inc.php';

function encrypt($data, $key){
		$md5crypt =& new MD5Crypt();
		$enc= $md5crypt->encrypt($data, $key);	
}

function decrypt($data, $key) {
		$md5crypt =& new MD5Crypt();
		return $md5crypt->decrypt($data, $key);
}

function readkey($sess_id){
	global $global;
	$db=$global['db'];
	$sql="select key from session_keys where session_id='{$sess_id}'";
	$res=$db->Execute($sql);
    if(($res==null) or ($res->EOF)){
        return false;
    }else {
        return $res->fields["key"];
    }
}



function genkey($sess_id){
	$salt1=_shn_generateSalt();
    $salt2=_shn_generateSalt();
    return md5(trim($salt1.$salt2.$sess_id));
	
}



