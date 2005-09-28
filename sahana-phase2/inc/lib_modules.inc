<?php  
/**
* This library helps in handling the dynamism of plugin module design 
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

// get all available modules regardless of weather they are enabled or not
function shn_get_module_names()
{
    global $global;
    $module_list = array();

    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (is_dir($approot."mod/".$f) && 
          file_exists($approot."mod/".$f."/main.inc")) {
          array_push($module_list, $f);
        }
    }
    return $module_list; 
}

// get all modules that have admin pages
function shn_get_modules_with_admin()
{
    global $global;
    $module_list = array();

    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (is_dir($approot."mod/".$f) && 
          file_exists($approot."mod/".$f."/admin.inc")) {
          array_push($module_list, $f);
        }
    }
    return $module_list; 
}

?>
