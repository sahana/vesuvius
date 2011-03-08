<?
/**
 * @name         User Preferences
 * @version      1.0
 * @package      pref
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


global $global;
include_once ($global['approot'].'/inc/lib_security/lib_acl.inc');

$currentrole = _shn_acl_get_roles(shn_current_user());

foreach ($currentrole as $key => $val) {
	$user = $val;
}

if ($_SESSION['logged_in'] == true ){
	shn_mod_menuitem("ch_passwd",_t("Change My Password"));
	shn_mod_menuitem("personal",_t("Edit My Personal Details"));
}
