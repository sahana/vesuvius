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

include_once $global['approot'].'/inc/lib_form.inc';
include_once($global['approot']."/inc/lib_user_pref.inc");



function _shn_xform_conf_value() {

  return $conf['shn_xform_enabled'];
}


function _shn_xform_set_config_value($state) {

global $global;
	if($state == false) {
	        $sql = "UPDATE config SET value = 'true' WHERE confkey = 'shn_xform_enabled'";
        	$global['db']->Execute($sql);
	    	$sql = "SELECT value FROM config WHERE confkey = 'shn_xform_enabled'";
    		$arr = $global['db']->GetAll($sql);
		if(!empty($arr)){
			foreach($arr as $row){
				$val = $row['value'];
			}
		  return $val;
		}
	}
	else {
	        $sql = "UPDATE config SET value = 'false' WHERE confkey = 'shn_xform_enabled'";
        	$global['db']->Execute($sql);
		$sql1 = "SELECT value FROM config WHERE confkey = 'shn_xform_enabled'";
		$arr = $global['db']->GetAll($sql1);
		if(!empty($arr)){
			foreach($arr as $row){
				$val = $row['value'];
			}
		  return $val;
		}
	}
}


