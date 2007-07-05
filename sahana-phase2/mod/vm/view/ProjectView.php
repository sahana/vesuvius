<?php

/**
* Project View
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

class ProjectView extends View
{
	function displayProject($p, $showVolunteersAssigned=true)
	{
		global $global, $dao;
		$this->engine->assign('info', $this->model->info);

		$volunteers = $dao->getVolunteers($p->proj_id);
		$numVolunteers = count($volunteers);

		// get manager name
		$v = new Volunteer($p->info['mgr_id']);
		$this->engine->assign('mgr_name', $v->info['full_name']);

		// get location hierarchy
		require_once($global['approot']. 'inc/lib_location.inc');
		$parents = array();
		shn_get_parents($p->info['location_id'], $parents);
		$locations = array();
		if(!empty($parents))
			foreach($parents as $loc_id)
				if($loc_id != 'NULL') {
					$loc = $dao->getLocation($loc_id);
					$locations[] = $loc['name'];
				}
		$locations = join("<br />\n", $locations);

		$this->engine->assign('info', $p->info);
		$this->engine->assign('start_date', ($p->info['start_date'] == '0000-00-00')?'':$p->info['start_date']);
		$this->engine->assign('end_date', ($p->info['end_date'] == '0000-00-00')?'':$p->info['end_date']);
		$this->engine->assign('location', $locations);
		$this->engine->assign('skills', $dao->getVolSkillsTree($p->proj_id, false));
		$this->engine->assign('mgr_id', $p->info['mgr_id']);
		$this->engine->assign('numVolunteers', $numVolunteers);
		$this->engine->assign('showVolunteersAssigned', $showVolunteersAssigned);
		$this->engine->assign('proj_id', $p->proj_id);

		$ac = new AccessController();
		$this->engine->assign('edit_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_edit', array('proj_id' => $p->proj_id))));
		$this->engine->assign('delete_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_confirm_delete', array('proj_id' => $p->proj_id))));

		$this->engine->display('project/display.tpl');
		if($showVolunteersAssigned && $numVolunteers > 0)
		{
			$vView = new VolunteerView();
			$vView->listVolunteers($volunteers, $p->proj_id, true);
		}
	}

	/**
	 * Display a list of projects
	 *
	 * @access public
	 * @param $p_uuid	- (optional) if specified, show only projects that this volunteer is assigned to
	 * 						(or is a site manager for)
	 * @return void
	 */

	function listProjects($p_uuid=null)
	{
		$p = new Project();
		$this->engine->assign('projects', $p->getProjects($p_uuid));
		$this->engine->display('project/list.tpl');
	}

	/**
	 * Add a new Project
	 */
	function addProject($p=null)
	{

		global $dao;
		$this->engine->assign('action',($p==null)?"Add":"Edit");
		$raw_mgr_data = $dao->getSiteManagers(VM_MGR_APPROVED);
		$mgrs_select = array();
		foreach($raw_mgr_data as $p_uuid => $info)
			$mgrs_select[$p_uuid] = $info['name'];
		$this->engine->assign('managers', $mgrs_select);

		if($p == null)
			$this->engine->assign('skills', $dao->getSelectSkillsTree(null, false, null, true));
		else
			$this->engine->assign('skills', $dao->getSelectSkillsTree($p->proj_id, false));

		$this->engine->assign('info', $p->info);
		$this->engine->assign('start_date', ($p->info['start_date'] == '0000-00-00')?'':$p->info['start_date']);
		$this->engine->assign('end_date', ($p->info['end_date'] == '0000-00-00')?'':$p->info['end_date']);

		/*
		 * Create an array of necessary hidden inputs and assign them to engine
		 */
		$hidden= array();
		if ($p!=null)
			$hidden["proj_id"]=$p->proj_id;
		$this->engine->assign('hidden',$hidden);
		$this->engine->display('project/add.tpl');
	}

	/**
	 * Displays a form for assigning volunteers to a project
	 */

	function assignVol ($proj_id)
	{
		$p = new Project($proj_id);
		$this->engine->assign('proj_id', $proj_id);
		$this->displayProject($p, false);

		$this->engine->display('volunteer/assign_header.tpl');
		$this->engine->assign('proj_name', $p->info['name']);
		$getvars = array_merge($_REQUEST, array('act' => 'volunteer', 'vm_action' => 'process_search', 'assigning' => true, 'proj_id' => $p->proj_id));
		$vc = new VolunteerController();
		$vc->controlHandler($getvars);
	}

	/**
	 * Displays a confirmation page asking if you really want to delete the volunteer.
	 *
	 * @param $id
	 * @return void
	 */
	function confirmDelete($proj_id) {
		$p = new Project($proj_id);
		$this->engine->assign('proj_id', $proj_id);
		$this->engine->assign('name', $p->info['name']);
		$this->engine->display('project/confirm_delete.tpl');
	}

	/**
	 * Displays a form for selecting a project to assign volunteers to
	 *
	 * @param $project_list 	- the result from listProjects() in the DAO
	 */

	function displaySelectProjectForAssignmentForm($project_list)
	{
		$projects = array();
		foreach($project_list as $key => $info)
			$projects[$key] = $info['name'];

		$this->engine->assign('projects', $projects);
		$this->engine->display('project/assign.tpl');
	}

	/**
	 * Displays a form to edit a volunteer's task
	 *
	 * @param $p_uuid		- the volunteer's p_uuid
	 * @param $proj_id		- the project to change the volunteer's task for
	 * @param $current_task	- the volunteer's current task
	 */
	function displayEditTaskForm($p_uuid, $proj_id, $current_task)
	{
		$this->engine->assign('p_uuid', $p_uuid);
		$this->engine->assign('proj_id', $proj_id);
		$this->engine->assign('current_task', addslashes($current_task));
		$this->engine->display('project/edit_task.tpl');
	}

}

?>