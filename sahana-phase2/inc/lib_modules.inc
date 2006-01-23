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
/**
 * shn_get_module_names 
 * 
 * @access public
 * @return void
 */
function shn_get_module_names()
{
    global $global;
    $module_list = array();

    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (file_exists($approot."mod/".$f."/main.inc")) {
          array_push($module_list, $f);
        }
    }
    return $module_list; 
}

// get all modules that have admin pages
/**
 * shn_get_modules_with_admin 
 * 
 * @access public
 * @return void
 */
function shn_get_modules_with_admin()
{
    global $global;
    $module_list = array();

    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (file_exists($approot."mod/".$f."/admin.inc")) {
          array_push($module_list, $f);
        }
    }
    return $module_list; 
}

/**
 * shn_include_module_conf 
 * 
 * @access public
 * @return void
 */
function shn_include_module_conf()
{
    global $global;
    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (file_exists($approot."mod/".$f."/conf.inc")) {
          include_once ($approot."mod/".$f."/conf.inc");
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
function shn_include_page_section($section, $module=null)
{
    global $global;
    if ($module == null)
        $module = $global['module'];

    $module_function = 'shn_'.$module.'_'.$section;
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($global['approot'].'inc/handler_'.$section.'.inc');
    } 
}
 
?>
