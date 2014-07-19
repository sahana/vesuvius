<?
/**
 * @name         Module Library
 * @version      10
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



/** Get all available modules regardless of weather they are enabled or not */
function shn_get_all_modules($nice_name_req=true) {

	global $global;
	global $conf;

	$module_list = array();
	$temp        = array();
	$approot     = $global['approot'];
	$d           = dir($approot."/mod");

	while (false !== ($f = $d->read())) {
		if (file_exists($approot."mod/".$f."/main.inc")) {
			$nice_name = $conf['mod_'.$f.'_name'];
			$temp[] = array("nice_name" => $nice_name, "mod" => $f);
		}
	}

	usort($temp, 'compare_nice_name');

	foreach($temp as $t) {
		if($nice_name_req == true) {
			array_push($module_list, array($t['mod'], $t['nice_name']));
		} else {
			array_push($module_list, $t['mod']);
		}
	}
	return $module_list;
}



/** helper function to above function */
function compare_nice_name($a, $b) {
	return strnatcmp($a['nice_name'], $b['nice_name']);
}



/** Get all available modules regardless of weather they are enabled or not */
function shn_get_module_names() {

	global $global;
	global $conf;

	$module_list = array();
	$mods        = shn_get_allowed_mods_current_user();
	$approot     = $global['approot'];
	$d           = dir($approot."/mod");

	while (false !== ($f = $d->read())) {
		if (file_exists($approot."mod/".$f."/main.inc")) {
			$res=array_search($f,$mods,false);
			if(FALSE !== $res) {
				array_push($module_list, $f);
			}
		}
	}
	return $module_list;
}



/** Get the names of all mlodules */
function shn_get_enabled_module_names() {

	global $global;
	global $conf;

	$module_list = array();
	$mods        = shn_get_enabled_mods_current_user();
	$approot     = $global['approot'];
	$d           = dir($approot."/mod");

	while (false !== ($f = $d->read())) {
		if (file_exists($approot."mod/".$f."/main.inc")) {
			$res=array_search($f,$mods,false);
			if(FALSE !== $res) {
				array_push($module_list, $f);
			}
		}
	}
	return $module_list;
}



/** Get all modules that have admin pages */
function shn_get_modules_with_admin() {

	global $global;

	$module_list = array();
	$approot     = $global['approot'];
	$d           = dir($approot."/mod");

	while (false !== ($f = $d->read())) {
		if (file_exists($approot."mod/".$f."/admin.inc")) {
			array_push($module_list, $f);
		}
	}
	return $module_list;
}



/** Get all modules that expose web services */
function shn_get_modules_with_web_services() {

	global $global;
	global $conf;

	$module_list = array();
	$approot     = $global['approot'];
	$d           = dir($approot."/mod");

	while (false !== ($f = $d->read())) {
		if (file_exists($approot."mod/".$f."/ws.xml")) {
			$nice_name=$conf['mod_'.$f.'_name'];
			array_push($module_list, array($f,$nice_name));
		}
	}
	return $module_list;
}




function shn_include_module_conf() {

	global $global;
	global $conf;

	$approot = $global['approot'];
	$d       = dir($approot."/mod");

	while (false !== ($f = $d->read())) {
		if (file_exists($approot."mod/".$f."/conf.inc")) {
			include_once ($approot."mod/".$f."/conf.inc");
			if (!defined($conf['shn_'.$f.'_enabled'])) {
				$conf['shn_'.$f.'_enabled'] = true;
			}
		}
	}
}



function shn_include_page_section($section, $module=null) {

	global $global;

	$mods = shn_get_allowed_mods_current_user();
	$module_function = 'shn_'.$module.'_'.$section;

	if (function_exists($module_function)) {
		$res = array_search($module, $mods, false);
		if(FALSE !== $res) {
			$module_function();
		} else {
			require_once($global['approot'].'inc/handler_'.$section.'.inc');
		}
	} else {
		require_once($global['approot'].'inc/handler_'.$section.'.inc');
	}

}



/** Return the 'nice' name of the module */
function shn_get_module_name($module=null) {

	global $global;
	global $conf;

	if (!$module) {
		return $conf['mod_' . $global['module'] . '_name'];
	} else {
		return $conf['mod_' . $module . '_name'];
	}
}



/** Check if module exists */
function shn_module_exists($module=null) {

	global $global;
	$module_file = $global['approot'].'mod/'.$module;
	return file_exists($module_file);
}

