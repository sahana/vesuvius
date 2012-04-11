<?
/**
 * @name         Cryptographic Library
 * @version      1.0
 * @package      framework
 * @author       Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


global $global;
require_once("constants.inc");
require_once($global['approot'].'inc/lib_security/lib_auth.inc');
require_once("errors.inc");
define("ADODB_SESSION", $global['approot']."/3rd/adodb/session");
include_once(ADODB_SESSION.'/crypt.inc.php');



function encrypt($data, $key) {
	$md5crypt = new MD5Crypt();
	$enc = $md5crypt->encrypt($data, $key);
}



function decrypt($data, $key) {
	$md5crypt = new MD5Crypt();
	return $md5crypt->decrypt($data, $key);
}



function readkey($sess_id){
	global $global;
	$db = $global['db'];
	$sql = "
		select key
		from session_keys
		where session_id = '{$sess_id}';
	";
	$res = $db->Execute($sql);
	if(($res == null) || ($res->EOF)) {
		return false;
	} else {
		return $res->fields["key"];
	}
}



function genkey($sess_id){
	$salt1 = _shn_generateSalt();
	$salt2 = _shn_generateSalt();
	return md5(trim($salt1.$salt2.$sess_id));
}



