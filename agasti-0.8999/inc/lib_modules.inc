<?php  
/**
* This library helps in handling the dynamism of plugin module design 
* Sahana - http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage module 
* @author     http://www.linux.lk/~chamindra
* @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
* @author     Greg Miernicki <g@miernicki.com>
* @copyright  Sahana Foundation - http://www.sahanafoundation.org
*/



/**
 * shn_get_all_modules
 * 
 * @access public
 * @return void
 *
 * Description: get all available modules regardless of weather they are enabled or not
 */
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

// helper function to above function
function compare_nice_name($a, $b) {
	return strnatcmp($a['nice_name'], $b['nice_name']);
}



/**
 * shn_get_module_names 
 * 
 * @access public
 * @return void
 *
 * Description: get all available modules regardless of weather they are enabled or not
 */
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



/**
 * shn_get_module_names 
 * 
 * @access public
 * @return void
 */
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



/**
 * shn_get_modules_with_admin 
 * 
 * @access public
 * @return void
 * 
 * Description: get all modules that have admin pages
 */
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



/**
 * shn_get_modules_with_web_services 
 * 
 * @access public
 * @return void
 * 
 * Description: get all modules that expose web services
 */
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




/**
 * shn_include_module_conf 
 * 
 * @access public
 * @depracted
 * @return void
 */
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



/**
 * shn_include_page_section 
 * 
 * @param mixed $section 
 * @param mixed $module 
 * @access public
 * @return void
 */
function shn_include_page_section($section, $module=null) {
	global $global;
	if ($module == null) {
		$module = $global['module'];
	}
	if(($global["setup"]) == false) {
		$mods=shn_get_allowed_mods_current_user();
		$module_function = 'shn_'.$module.'_'.$section;
		if (function_exists($module_function)) {
			$res=array_search($module,$mods,false);
			if(FALSE !== $res) {
				$module_function();
			} else {
				include($global['approot'].'inc/handler_'.$section.'.inc');
			}
		} else {
			include($global['approot'].'inc/handler_'.$section.'.inc');
		} 
	} else {
		include($global['approot'].'inc/handler_'.$section.'.inc');
	}
}
 


/**
 * Return the 'nice' name of the module 
 * 
 * @param mixed $module 
 * @access public
 * @return string
 */
function shn_get_module_name($module=null) {
	global $global;
	global $conf;
	
	if (!$module) {
		return $conf['mod_' . $global['module'] . '_name'];          
	} else {
		return $conf['mod_' . $module . '_name'];
	}
}



/**
 * Check if module exists 
 * 
 * @param mixed $module 
 * @return boolean
 */
function shn_module_exists($module=null) {
	global $global;
	$module_file = $global['approot'].'mod/'.$module;
	return file_exists($module_file);
}

