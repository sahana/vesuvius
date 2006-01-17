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
require_once $global['approot'].'/inc/lib_modules.inc';
require_once $global['approot'].'/inc/lib_menu.inc';

shn_mainmenuopen(_('Main Menu'));
shn_mainmenuitem('default',_('Sahana Home'),'home');

// display the list of modules on the menu bar
$module_list = shn_get_module_names();

foreach ($module_list as $i) {  
    
    if ( ( 'home' != $i ) && ('admin' != $i ) ) {
        $module_name = $conf['mod_'.$i.'_name']; 
        $module_name = ( null == $module_name )? $i : $module_name ;
        shn_mainmenuitem('default',$module_name, $i);
    }
} 

shn_mainmenuitem('default',_('System Administration'),'admin');
shn_mainmenuclose();
?>
