<?php
/**
* The Situation Report (SITRep) Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   sr
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/

include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once "lib_form.inc";

include_once($global['approot'].'inc/lib_log.inc');


function shn_sr_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    shn_mod_menuopen(_t('Situation Report'));
    	shn_mod_menuitem('default',_t('Home'));
    	shn_mod_menuitem('create',_t('Report'));
    	shn_mod_menuitem('view',_t('View'));
    	shn_mod_menuitem('update',_t('Update'));
    shn_sub_mod_menuclose();

    include $global['approot'].'/inc/handler_mainmenu.inc';

}

// Form submition capture
function shn_sr_form_submit($values)
{
	print "got it";
}

function shn_sr_default()
{
	print "<h1><center>Welcome to Situation Report</center></h1>";
	print "SITRep Dashboard!";
}

function shn_sr_create()
{
	print "<h1>Report an incident</h1>";
	shn_sr_form_create();
}


function shn_sr_view()
{
	print "view";
}

function shn_sr_update()
{
	print "update";
}
?>