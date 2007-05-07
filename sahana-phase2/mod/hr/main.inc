<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Sheran Corera (sheran@opensource.lk) 
 * @copyright  Lanka Software Foundation (http://www.opensource.lk)
 * @package    mod
 * @subpackage hr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once ('lib.inc');

/**
 * This function allows you to override the mainmenu. This is often done 
 * to include the modules own menu
 * 
 * @access public
 * @return void
 */
function shn_hr_mainmenu() 
{
	include_once ('default.inc');
    include_once ('reg_new_homeless_family.inc');
    include_once ('reg_new_damaged_house.inc');
    include_once ('reg_new_contractor.inc');
    include_once ('reg_new_site.inc');
    include_once ('list_menus.inc');
    include_once ('search.inc');
    include_once ('search_list_and_edit_menus.inc');
    include_once ('assign_to_site.inc');
    include_once ('assign_contractor.inc');

    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen(_('Housing Registry And Reconstruction'));


    shn_sub_mod_menuitem('default',_('Main Page'));

    shn_sub_mod_menuopen(_('Quick Search And Reports'));
    shn_mod_menuitem('search',_('Quick Search'));
    //shn_mod_menuitem('report',_('Reports'));
	shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_('Homeless Family(ies)'));
    shn_sub_mod_menuitem('reg_new_homeless_family',_('Register New'));
    shn_mod_menuitem('search_list_and_edit_menu1',_('View, Search Or Edit'));
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_('Damaged House(s)'));
    shn_sub_mod_menuitem('reg_new_damaged_house',_('Register New'));
    shn_mod_menuitem('search_list_and_edit_menu2',_('View, Search Or Edit'));
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_('Contractor(s)'));
    shn_sub_mod_menuitem('reg_new_contractor',_('Register New'));
    shn_mod_menuitem('search_list_and_edit_menu3',_('View, Search Or Edit'));
    shn_mod_menuitem('assign_to_site',_('Assign To Site(s)'));
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_('Site(s)'));
    shn_sub_mod_menuitem('reg_new_site',_('Register New'));
    shn_mod_menuitem('search_list_and_edit_menu4',_('View, Search Or Edit'));
    shn_mod_menuitem('assign_contractor',_('Assign Contractor(s)'));
    shn_sub_mod_menuclose();


    shn_mod_menuclose();
   
    // include the main menu so that the user can navigate outside the module
    include $global['approot'].'/inc/handler_mainmenu.inc';
} 
