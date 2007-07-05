<?php
/**
* Admin View
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

require_once('View.php');

/**
 * View class for all administrative functions
 */

class AdminView extends View
{
	/**
	 * Displays the menu at the top of each admin page
	 */

	function displayAdminVMenu()
	{
		$ac = new AccessController();
		$this->engine->assign('skills', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'display_modify_skills')));
		$this->engine->assign('acl', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'display_acl_situations')));
		$this->engine->assign('managers', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'display_approve_managers')));
		$this->engine->assign('search_registry', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'process_update_phonetics')));
		$this->engine->assign('clear_cache', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'process_clear_cache')));
		$this->engine->display('admin/vmenu.tpl');
	}

	/**
	 * Displays a form to handle adding/removing skills
	 */

	function displayAdminSkills()
	{
		$v = new Volunteer();
		$this->engine->assign('skills', $v->getSkillList());
		$this->engine->display('admin/skills.tpl');
	}

	/**
	 * Displays a form for choosing an access request situation to modify access to
	 *
	 * @param $requests	- an array of all 'act' => 'vm_action' pairs
	 */

	function displayAdminACL($requests)
	{
		//sort the requests only by partial description
		$partial_descriptions = array();
		$sorted_requests = array();

		foreach($requests as $info)
			$partial_descriptions[] = $info['partial_desc'];

		asort($partial_descriptions);

		foreach($partial_descriptions as $key => $value)
			$sorted_requests[$key] = $requests[$key];

		$this->engine->assign('requests', $sorted_requests);
		$this->engine->display('admin/acl.tpl');
	}

	/**
	 * Displays a form for handling changes to ACL specific to the VM module
	 */

	function displayAdminACLModify($act, $vm_action, $request_description, $req_constraints, $pos_constraints, $tables)
	{
		$this->engine->assign('act', $act);
		$this->engine->assign('vm_action', $vm_action);
		$this->engine->assign('request_description', $request_description);
		$this->engine->assign('request_constraints', $req_constraints);
		$this->engine->assign('possible_constraints', $pos_constraints);
		$this->engine->assign('tables', $tables);
		$this->engine->display('admin/acl_modify.tpl');
	}

	/**
	 * Displays a form to allow site manager approval
	 *
	 * @param $managers	- 	an array of unapproved site managers, where each key is each p_uuid and each value
	 * 						is each name
	 */

	function displaySiteManagerApprovalForm($managers)
	{
		$this->engine->assign('managers', $managers);
		$this->engine->display('admin/approve_managers.tpl');
	}

	/**
	 * Displays the default admin page, which simply contains instructions on what each administrative function does
	 */

	function displayDefaultAdminPage()
	{
		$ac = new AccessController();
		$this->engine->assign('skills', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'display_modify_skills')));
		$this->engine->assign('acl', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'display_acl_situations')));
		$this->engine->assign('managers', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'display_approve_managers')));
		$this->engine->assign('search_registry', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'process_update_phonetics')));
		$this->engine->assign('clear_cache', $ac->isAuthorized(false, array('act' => 'adm_default', 'vm_action' => 'process_clear_cache')));
		$this->engine->display('admin/default.tpl');
	}

}

?>