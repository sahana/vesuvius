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
		$numVolunteers = $dao->getVolunteersInProject($p->proj_id);

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
		$this->engine->assign('skills', $dao->getVolSkillsTree($p->proj_id, true));

		$this->engine->assign('numVolunteers', $numVolunteers);
		$this->engine->assign('showVolunteersAssigned', $showVolunteersAssigned);
		$this->engine->assign('proj_id', $p->proj_id);
		$this->engine->assign('position_title',$p->ptype_title);

		$this->engine->assign('positions',$p->positions);

		$ac = new AccessController();
		$this->engine->assign('edit_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_edit', array('proj_id' => $p->proj_id))));
		$this->engine->assign('delete_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_confirm_delete', array('proj_id' => $p->proj_id))));


		$this->engine->assign('add_pos_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'add_position', array('proj_id' => $p->proj_id))));
		$this->engine->assign('delete_pos_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'remove_position', array('proj_id' => $p->proj_id))));
		$this->engine->assign('assign_auth', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_assign', array('proj_id' => $p->proj_id))));

		$this->engine->display('project/display.tpl');
		if($showVolunteersAssigned && $numVolunteers > 0)
		{
			$extra_opts = array
			(
				'showPictures'			=> true,
				'showLocation'			=> true,
				'showRemove'			=> true,
				'modifyProjId'			=> $p->proj_id,
				'showPositions'         => true,
				'showHours'             => true
 			);
			$vView = new VolunteerView();
			$vView->listVolunteers($volunteers, $extra_opts);
			$this->showPagingNavigation("index.php?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id={$p->proj_id}");
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

	function listProjects($p_uuid=null) {
		$p = new Project();
		$this->engine->assign('projects', $p->getProjects($p_uuid, false, false, true));
		$this->engine->display('project/list.tpl');
	}

	/**
	 * Add a new Project
	 */
	function addProject($p=null)
	{

		global $dao;
		$this->engine->assign('action',($p==null)?"Add":"Edit");
		$raw_mgr_data = $dao->getVolunteersByAbility('MGR', 'approved');
		$mgrs_select = array();
		foreach($raw_mgr_data as $p_uuid => $info)
			$mgrs_select[$p_uuid] = $info['name'];
		$this->engine->assign('managers', $mgrs_select);


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

	function assignVol($proj_id, $positions=null)
	{
		$p = new Project($proj_id);
		$this->engine->assign('proj_id', $proj_id);
		$this->displayProject($p, false);

		$this->engine->display('volunteer/assign_header.tpl');
		$this->engine->assign('proj_name', $p->info['name']);
		$getvars = array_merge($_REQUEST, array('act' => 'volunteer', 'vm_action' => 'process_search', 'assigning' => true, 'proj_id' => $p->proj_id, 'positions' => $positions));

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

	/*
	 *Adds a new Position to a project
	 */
	function addPosition($p=null) {
		global $dao;
		if ($p != null) {
			$this->engine->assign('pos_id',$p->pos_id);
			$this->engine->assign('proj_id',$p->proj_id);
			$this->engine->assign('ptype_id',$p->ptype_id);
			$this->engine->assign('position_title',$p->position_title);
			$this->engine->assign('numSlots',$p->numSlots);
			$this->engine->assign('title', $p->title);
			$this->engine->assign('description', $p->description);
			$this->engine->assign('payrate', $p->payrate);
		}
		$this->engine->assign('position_types', $dao->getSkillList());
		$this->engine->display('project/position.tpl');
	}
}

