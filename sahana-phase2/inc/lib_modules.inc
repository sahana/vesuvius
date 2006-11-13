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
    global $conf;
    $module_list = array();

    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if ($conf['mod_'.$f.'_enabled'] && 
                file_exists($approot."mod/".$f."/main.inc")) {
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
 * @depracted
 * @return void
 */
function shn_include_module_conf() // DEPCRATED
{
    global $global;
    global $conf;

    $approot = $global['approot'];
    $d = dir($approot."/mod");
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
 

/**
 * Return the 'nice' name of the module 
 * 
 * @param mixed $module 
 * @access public
 * @return string
 */
function shn_get_module_name($module=null)
{
    global $global;
    global $conf;
    
    if (!$module)
    {
        return $conf['mod_' . $global['module'] . '_name'];          
    }
    else
    {
        return $conf['mod_' . $module . '_name'];
    }
}

/**
 * Check if module exists 
 * 
 * @param mixed $module 
 * @return boolean
 */
function shn_module_exists($module=null)
{
    global $global;
 
    $module_file = $global['approot'].'mod/'.$module;

    return file_exists($module_file);
}

   
?>
