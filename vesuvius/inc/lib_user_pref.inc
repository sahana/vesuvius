<?
/**
 * @name         User Preferences Library
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
 */


function shn_user_pref_populate() {
	global $global;

	$q = "
		SELECT module_id, pref_key, value
		FROM user_preference
		WHERE p_uuid = '".$_SESSION['user_id']."';
	";
	$arr = $global['db']->GetAll($q);
	if(!empty($arr)) {
		//clean the session
		$_SESSION['user_pref'] = null;
		foreach($arr as $row){
			$_SESSION['user_pref_'.$row['module_id'].'_'.$row['pref_key']] = $row['value'];
		}
	} else {
		// go with the session.. hmmm
	}
}



function shn_get_user_pref_value($module, $key, $userid = NULL) {
	global $global;
	if(NULL==$userid) {
		$userid=$_SESSION['user_id'];
	}
	$q = "
		SELECT value
		FROM user_preference
		WHERE p_uuid = '".$_SESSION['user_id']."'
		AND module_id = '$module'
		AND pref_key='$key';
	";
	$res = $global['db']->Execute($q);
	if(NULL!=$res) {
		return $res->fields['value'];
	} else {
		return NULL;
	}
}



function shn_user_pref_update($module, $key, $value = null, $delete = false) {
	global $global;
	if($delete) {
		$q = "
			DELETE FROM user_preference
			WHERE p_uuid = '".$_SESSION['user_id']."'
			AND module_id = '$module'
			AND pref_key = '$key';
		";
		$global['db']->Execute($q);
	} else {
		//create the session
		$_SESSION['user_pref_'.$module.'_'.$key] = $value;

		//dump to the database
		$q = "
			DELETE FROM user_preference
			WHERE p_uuid = '".$_SESSION['user_id']."'
			AND module_id = '$module'
			AND pref_key = '$key';
		";
		$global['db']->Execute($q);
		$q = "
			INSERT INTO user_preference (p_uuid, module_id, pref_key, value)
			VALUES ('{$_SESSION['user_id']}','$module','$key','$value');
		";
		$global['db']->Execute($q);
	}
	return $value;
}



function _shn_pref_ajax_update($module, $key, $value) {
	shn_user_pref_update($module, $key, $value);
}

