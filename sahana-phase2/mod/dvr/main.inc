<?php


/**
 * 
 * This file includes the main links of the DVR module
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . '/inc/lib_menu.inc';
include_once $global['approot'] . '/inc/lib_form.inc';
include_once $global['approot'] . '/inc/lib_validate.inc';
include_once $global['approot'] . '/inc/lib_errors.inc';
include_once $global['approot'] . '/inc/lib_location.inc';
include_once $global['approot'] . '/mod/dvr/main_fns.inc';

/**
 * This function allows you to override the mainmenu. This is often done 
 * to include the modules own menu
 * 
 * @access public
 * @return void
 */
function shn_dvr_mainmenu() {
	global $global;
	$module = $global['module'];

	// Create the module menu
	shn_mod_menuopen(_('Disaster Victim Registry'));

	shn_mod_menuitem('default', _('Home'));
	shn_sub_mod_menuopen(_('Add Disaster Victim(s)'));
	shn_sub_mod_menuitem('add_new_grp', _('Add New Group'));
	shn_sub_mod_menuitem('add_new_indv', _('Add New Individual'));
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_('Edit Disaster Victim(s)'));
	shn_sub_mod_menuitem('search_group', _('Search and Edit Group'));
	shn_sub_mod_menuitem('search_individual', _('Search and Edit Individual'));
	shn_sub_mod_menuclose();

	/*shn_sub_mod_menuopen(_('Search Disaster Victim(s)'));
	shn_sub_mod_menuitem('search_group', _('Search Person'));
	shn_sub_mod_menuclose();*/

	shn_sub_mod_menuopen(_('List groups '));
	shn_sub_mod_menuitem('list_groups', _('List groups/View members '));
	//shn_sub_mod_menuitem('list_persons', _('List All persons'));
	shn_sub_mod_menuclose();
	
	///////
	shn_sub_mod_menuopen(_('Transfer Victims'));
	shn_sub_mod_menuitem('transfer_indv', _('Transfer Individual'));
	shn_sub_mod_menuitem('transfer_group', _('Transfer Group'));
	shn_sub_mod_menuclose();
	/////////

	shn_sub_mod_menuopen(_('Reports'));
	shn_sub_mod_menuitem('drill_downby_group', _('Drill Down By Group'));
	shn_sub_mod_menuitem('drill_downby_shelter', _('Drill Down By Shelter'));
	shn_sub_mod_menuitem('drill_downby_incident', _('Drill Down By Incident '));
	shn_sub_mod_menuclose();

	shn_mod_menuclose();

	// include the main menu so that the user can navigate outside the module
	include $global['approot'] . '/inc/handler_mainmenu.inc';

}
?>