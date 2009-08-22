<?php

/**
* Defines the menus for the vm module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @author		Sylvia Hristakeva
* @author		Kumud Nepal
* @author		Ernel Wint
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

/**
 * Displays the 'Volunteers' submenu only if any of its submenu items can be displayed
 */


function shn_vm_home_submenu(){
	
	$ac = new AccessController();
	
	$ac->addMenuItem(_('Home'), $ac->buildURLParams('home', 'display_portal'));
	
	
}



function shn_vm_volunteer_submenu()
{
	$ac = new AccessController();

	if(	$ac->isAuthorized(false, $ac->buildURLParams('project', 'display_select_project')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_list_assigned')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_list_all')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_search')))

	{
		shn_sub_mod_menuopen(_("Volunteers"));
		    $ac->addMenuItem(_('Assign to Project'), $ac->buildURLParams('project', 'display_select_project'), true);
		    $ac->addMenuItem(_('Show Assigned'), $ac->buildURLParams('volunteer', 'display_list_assigned'), true);
		    $ac->addMenuItem(_('View All'), $ac->buildURLParams('volunteer', 'display_list_all'), true);
		    $ac->addMenuItem(_('Search for a Volunteer'), $ac->buildURLParams('volunteer', 'display_search'), true);

	    shn_sub_mod_menuclose();
	}
}




/**
 * Displays the 'Projects' submenu only if any of its submenu items can be displayed
 */

function shn_vm_project_submenu()
{
	$ac = new AccessController();

	if(	$ac->isAuthorized(false, $ac->buildURLParams('project', 'display_add')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('project', 'display_my_list')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('project', 'default')))
	{
		shn_sub_mod_menuopen(_("Projects"));
	    	$ac->addMenuItem(_('Add New'), $ac->buildURLParams('project', 'display_add'), true);
	    	$ac->addMenuItem(_('View My Projects'), $ac->buildURLParams('project', 'display_my_list'), true);
			$ac->addMenuItem(_('View All'), $ac->buildURLParams('project', 'default'), true);
		shn_sub_mod_menuclose();
	}
}

/**
 * Displays the 'Messaging' submenu only if any of its submenu items can be displayed
 */

function shn_vm_messaging_submenu()
{
	$ac = new AccessController();

	if(	$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_mailbox')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_mailbox', array('box' => 'outbox'))) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_send_message')))
	{
		shn_sub_mod_menuopen(_("Messaging"));
			$ac->addMenuItem(_('Inbox'), $ac->buildURLParams('volunteer', 'display_mailbox', array('rpp' => VM_DEFAULT_MAILBOX_RPP)), true);
			$ac->addMenuItem(_('Outbox'), $ac->buildURLParams('volunteer', 'display_mailbox', array('box' => 'outbox', 'rpp' => VM_DEFAULT_MAILBOX_RPP)), true);
			$ac->addMenuItem(_('Send Message'), $ac->buildURLParams('volunteer', 'display_send_message'), true);
		shn_sub_mod_menuclose();
	}
}

/**
 * Displays the 'Reports' submenu only if any of its submenu items can be displayed
 */

function shn_vm_reports_submenu()
{
	$ac = new AccessController();

	if(	$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_report_all')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_custom_report_select')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_custom_report_select_for_mgrs')))
	{
		shn_sub_mod_menuopen(_("Reporting"));
			//$ac->addMenuItem('Report All Volunteers', $ac->buildURLParams('volunteer', 'display_report_all'), true);
			$ac->addMenuItem(_('Custom Report'), $ac->buildURLParams('volunteer', 'display_custom_report_select'), true);
			$ac->addMenuItem(_('Report On My Projects'), $ac->buildURLParams('volunteer', 'display_custom_report_select_for_mgrs'), true);
		shn_sub_mod_menuclose();
	}
}

/**
 * Displays the 'Managing' submenu only if any of its submenu items can be displayed
 */

function shn_vm_management_submenu()
{
	$ac = new AccessController();

	if(	$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_modify_skills')) ||
		$ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_approval_management')))
	{
		shn_sub_mod_menuopen(_("Management"));
			$ac->addMenuItem(_('Modify Abilities/Limitations'), $ac->buildURLParams('volunteer', 'display_modify_skills'), true);
			$ac->addMenuItem(_('Approve Abilities'), $ac->buildURLParams('volunteer', 'display_approval_management'), true);
		shn_sub_mod_menuclose();
	}
}





/**
 * Display the main menu for the VM module.
 *
 * @return void
 */

function shn_vm_mainmenu()
{
    shn_vm_load_db();
    global $global, $dao, $conf;

	$ac = new AccessController($_REQUEST);

    shn_mod_menuopen(_("Volunteer Management"));

		$ac->addMenuItem(_('Home'), $ac->buildURLParams('volunteer', 'display_portal'));
        //shn_vm_home_submenu();
		shn_vm_volunteer_submenu();
		shn_vm_project_submenu();
		shn_vm_messaging_submenu();
		shn_vm_reports_submenu();
		shn_vm_management_submenu();

		if($dao->isVolunteer($_SESSION['user_id']))
			$ac->addMenuItem(_('Edit Your Details'), $ac->buildURLParams('volunteer', 'display_edit', array('p_uuid' => $_SESSION['user_id'])), true);
		else
			$ac->addMenuItem(_('Register to Volunteer'), $ac->buildURLParams('volunteer', 'display_add'), true);

		//$ac->addMenuItem('Change Password', $ac->buildURLParams('volunteer', 'display_change_pass'));

	shn_mod_menuclose();

	include $global['approot']."/inc/handler_mainmenu.inc";
}


