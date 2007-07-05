<?php

/**
* Project Controller
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
 * VolunteerController.php - define the VolunteerController class
 *
 * This class, a subclass of the VolunteerView, implements the Controller interface
 * and decides which pages in the VolunteerView to show or act upon.
 */

 class ProjectController extends ProjectView implements Controller
 {
 	/**
	 * The function that decides what to do and which page to view.
	 *
	 * @param $getvars an associative array, representing the GET variables
	 *                 from the URL
	 * @return void
	 */

 	function controlHandler($getvars)
 	{
 		global $dao, $global;
 		include_once($global['approot'].'inc/lib_location.inc');

		//first authorize the user
 		$ac = new AccessController($getvars);
		if(!$ac->isAuthorized())
			return;

 		// temporary, to support older 'action' instead of 'vm_action'
 		$vm_action = ($getvars['vm_action']?$getvars['vm_action']:$getvars['action']);

		switch($vm_action)
		{
			case 'display_single':
				$p = new Project($getvars['proj_id']);
				View::View($p);
				$this->displayProject($p);
			break;

			case 'display_add':
				View::View();
				$this->addProject();
			break;

			case 'display_edit':
				View::View();
				$this->addProject(new Project($getvars['proj_id']));
			break;

			case 'process_add':
				$p = new Project($getvars['proj_id']);
				$p->info['name'] = $getvars['name'];
				$p->info['description'] =$getvars['description'];
				$p->info['start_date'] =$getvars['start_date'];
				$p->info['end_date'] =$getvars['end_date'];
				$p->info['mgr_id']=$getvars['manager'];
				$p->info['locations'] = array();
				shn_get_parents(shn_location_get_form_submit_loc(), $p->info['locations']);
				$p_skills = array();
				$skill_ids = $dao->getSkillIDs();
				foreach($skill_ids as $skill)
				{
					if($getvars["SKILL_$skill"] == 'on')
						$p_skills[] = $skill;
				}
				$p->info['skills'] = $p_skills;

				if($this->validateAddForm($getvars))
				{
					$p->save();
					View::View($p);
					$this->displayConfirmation('Changes Saved.');
					$this->displayProject($p);
				}
				else
				{
					View::View($p);
					$this->addProject();
				}
			break;
			case 'process_delete':
				$p = new Project();
				$p->delete($getvars['proj_id']);
				View::View();
				$this->displayConfirmation('The requested Project was deleted.');
				$this->listProjects();
			break;

			case 'display_confirm_delete':
				View::View();
				$this->confirmDelete($getvars['proj_id']);
			break;

			case 'display_select_project':
				View::View();
				if($dao->isSiteManager($_SESSION['user_id']) && !$ac->dataAccessIsAuthorized(array('vm_proj_vol' => 'ru'), false))
					$projects = $dao->listProjects($_SESSION['user_id'], true);
				else
					$projects = $dao->listProjects();

				$this->displaySelectProjectForAssignmentForm($projects);
			break;

			case 'display_assign':
				View::View();
				if($getvars['proj_id'] == '')
				{
					add_error(SHN_ERR_VM_NO_PROJECT);

					if($dao->isSiteManager($_SESSION['user_id']) && !$ac->dataAccessIsAuthorized(array('vm_proj_vol' => 'ru'), false))
						$projects = $dao->listProjects($_SESSION['user_id'], true);
					else
						$projects = $dao->listProjects();

					$this->displaySelectProjectForAssignmentForm($projects);
				}
				else
				{
					if($getvars['p_uuid'] != '' && $this->validateAssignForm($getvars))
					{
						$dao->assignToProject($getvars['p_uuid'], $getvars['proj_id'], $getvars["{$getvars['p_uuid']}_task"]);
						add_confirmation('Volunteer has been successfully assigned');
					}

					$this->assignVol($getvars['proj_id']);
				}
			break;

			case 'process_remove_from_project':
				$dao->deleteFromProject($getvars['p_uuid'], $getvars['proj_id']);
				$p = new Project($getvars['proj_id']);
				View::View($p);
				$this->displayProject($p);
			break;

			case 'display_my_list':
				$this->listProjects($_SESSION['user_id']);
			break;

			case 'display_edit_task':
				$this->displayEditTaskForm($getvars['p_uuid'], $getvars['proj_id'], $dao->getVolTask($getvars['p_uuid'], $getvars['proj_id']));
			break;

			case 'process_edit_task':
				global $global;
				require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

				if(shn_vm_not_empty($getvars['task']))
				{
					$dao->setVolTask($getvars['p_uuid'], $getvars['proj_id'], $getvars['task']);
					add_confirmation('Task has been updated');

					$p = new Project($getvars['proj_id']);
					View::View($p);
					$this->displayProject($p);
				}
				else
				{
					add_error(SHN_ERR_VM_NO_TASK);
					$this->displayEditTaskForm($getvars['p_uuid'], $getvars['proj_id'], $dao->getVolTask($getvars['p_uuid'], $getvars['proj_id']));
				}
			break;

			default:
				$this->listProjects();
			break;
		}

 	}

 	/**
 	 * Validates that the required fields are filled out in order to assign a volunteer
 	 * or continue filtering when assigning
 	 *
 	 * @access public
 	 * @return true if the form is valid, false otherwise
 	 */

 	function validateAssignForm($getvars)
 	{
 		global $global;
		require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

 		if(!shn_vm_not_empty($getvars["{$getvars['p_uuid']}_task"]))
 		{
 			add_error(SHN_ERR_VM_NO_TASK);
 			return false;
 		}

 		return true;
 	}

 	/**
 	 * Validates that the required fields are filled in and correct
 	 *
 	 * @access public
 	 * @return true if the form is valid, and false otherwise;
 	 */

 	 function validateAddForm($getvars)
 	 {
 	 	//include the validation library
 	 	global $global;
 		require_once($global['approot'].'inc/lib_validate.inc');
 		require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

 	 	//assume the form is valid
 	 	$validated =true;

		//validate that there is a name entered
 	 	$validated = $validated && shn_vm_not_empty($getvars['name'], SHN_ERR_VM_NO_NAME);

 	 	//validate that a site manager has been selected
 	 	$validated = $validated && shn_vm_not_empty($getvars['manager'], SHN_ERR_VM_NO_MGR);

 	 	//validate that at least one required skill is selected
 	 	$validated = $validated && shn_vm_skill_selected($getvars, SHN_ERR_VM_NO_SKILLS_SELECTED);

 	 	//validate that the dates if specified are in the correct format and if both specified the start date is before the end date;

 	 	$valid_start = null;
 	 	$valid_end = null;

 	 	if($getvars['start_date'] !='')
 	 	{
 	 		if(!shn_vm_valid_date($getvars['start_date']))
			{
				add_error(SHN_ERR_VM_BAD_PROJECT_DATES);
				$validated = false;
				$valid_start=false;
			}
			else
				$valid_start=true;
 	 	}

 	 	if($getvars['end_date'] !='')
 	 	{
 	 		if(!shn_vm_valid_date($getvars['end_date']))
			{
				if($valid_start!==false)
					add_error(SHN_ERR_VM_BAD_PROJECT_DATES);
				$valid_end=false;
				$validated = false;
			}
			else
				$valid_end=true;
 	 	}
		if($valid_start && $valid_end)
			$validated = $validated && shn_vm_compatible_dates($getvars['start_date'], $getvars['end_date'], SHN_ERR_VM_DATES_INCOMPATIBLE);

 	 	return $validated;
 	 }


 }
?>
