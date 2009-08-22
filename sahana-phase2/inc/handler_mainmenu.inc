<?php
/**
 * This handler displays the mainmenu dynamically based on action
 * Sahana - http://sahana.sourceforge.net
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage    handler
 * @author     http://www.linux.lk/~chamindra
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

global $conf;
global $global;
require_once $global['approot'].'/inc/lib_modules.inc';
require_once $global['approot'].'/inc/lib_menu.inc';

shn_mainmenuopen(_t('Main Menu'));

// display the list of modules on the menu bar
if(shn_acl_is_enabled()==true){
	$module_list = shn_get_enabled_module_names();
}else{
	$module_list = shn_get_all_modules(false);
}


$module_names = array();
$module_menuorder = array();
$module_directory = array();

foreach ($module_list as $i) {
	if(isset($conf['mod_'.$i.'_hide_in_menu'])==false){
		$tmp = isset($conf['mod_'.$i.'_name'])?$conf['mod_'.$i.'_name']:null;
		array_push($module_names,( null == $tmp )? $i : $tmp);
		$tmp = isset($conf['mod_'.$i.'_menuorder'])?$conf['mod_'.$i.'_menuorder']:null;
		array_push($module_menuorder,( null == $tmp )? 10 : $tmp);
		$tmp = isset($conf['mod_'.$i.'_directory'])?$conf['mod_'.$i.'_directory']:null;
		array_push($module_directory, $i );
	}
}

array_multisort($module_menuorder, $module_names, $module_directory);

for ($i = 0; $i < count($module_menuorder); $i++) {
	shn_mainmenuitem('default',$module_names[$i], $module_directory[$i]);
}

shn_mainmenuclose();


