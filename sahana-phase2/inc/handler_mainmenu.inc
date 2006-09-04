<?php  
/**
* This handler displays the mainmenu dynamically based on action  
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $conf;
global $global;
require_once $global['approot'].'/inc/lib_modules.inc';
require_once $global['approot'].'/inc/lib_menu.inc';

shn_mainmenuopen(_('Main Menu'));

// display the list of modules on the menu bar
$module_list = shn_get_module_names();

$module_names = array();
$module_menuorder = array();
$module_directory = array();

foreach ($module_list as $i) {  
    $tmp = $conf['mod_'.$i.'_name']; 
    array_push($module_names,( null == $tmp )? $i : $tmp);
    $tmp = $conf['mod_'.$i.'_menuorder']; 
    array_push($module_menuorder,( null == $tmp )? 10 : $tmp);
    $tmp = $conf['mod_'.$i.'_directory']; 
    array_push($module_directory, $i );
} 

array_multisort($module_menuorder, $module_names, $module_directory);

for ($i = 0; $i < count($module_menuorder); $i++) {
    shn_mainmenuitem('default',$module_names[$i], $module_directory[$i]);
}

shn_mainmenuclose();

?>
