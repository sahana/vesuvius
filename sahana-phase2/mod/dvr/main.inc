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
 * fixed locally for null incident
 */
if(isset($_SESSION['user_pref_ims_incident_id']))
{
	$_SESSION['dvr']['incident_id'] = $_SESSION['user_pref_ims_incident_id'];
}
else
{
	$_SESSION['dvr']['incident_id'] = 1;
}

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
	shn_mod_menuopen(_t('Disaster Victim Registry'));

	shn_mod_menuitem('default', _t('Home'));
	shn_sub_mod_menuopen(_t('Add Disaster Victim(s)'));
	shn_sub_mod_menuitem('add_new_grp', _t('Add New Group'));
	shn_sub_mod_menuitem('add_new_indv', _t('Add New Individual'));
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_t('Edit Disaster Victim(s)'));
	shn_sub_mod_menuitem('search_group', _t('Search/Edit/Transfer Group'));
	shn_sub_mod_menuitem('search_individual', _t('Search/Edit/Transfer Individual'));
	shn_sub_mod_menuclose();

	/*shn_sub_mod_menuopen(_t('Search Disaster Victim(s)'));
	shn_sub_mod_menuitem('search_group', _t('Search Person'));
	shn_sub_mod_menuclose();*/
	shn_sub_mod_menuitem('duplicate_search', _t('List Duplicate Entries'));
	shn_sub_mod_menuopen(_t('List groups '));
	shn_sub_mod_menuitem('list_groups', _t('List groups/View members '));
	//shn_sub_mod_menuitem('duplicate_search', _t('List Duplicate Entries'));
	shn_sub_mod_menuclose();

		///////
//	shn_sub_mod_menuopen(_t('Transfer Victims'));
//	shn_sub_mod_menuitem('search_group', _t('Transfer Group'));
//	shn_sub_mod_menuitem('search_individual', _t('Transfer Individual'));
//	
//	shn_sub_mod_menuclose();
	/////////

	shn_sub_mod_menuopen(_t('Reports'));
	shn_sub_mod_menuitem('drill_downby_group', _t('Drill Down By Group'));
	shn_sub_mod_menuitem('drill_downby_shelter', _t('Drill Down By Shelter'));
	shn_sub_mod_menuitem('drill_downby_incident', _t('Drill Down By Incident '));
	shn_sub_mod_menuclose();

	shn_mod_menuclose();

	// include the main menu so that the user can navigate outside the module
	include $global['approot'] . '/inc/handler_mainmenu.inc';

}
