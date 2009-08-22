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
 * ProjectController.php - define the ProjectController class
 *
 * This class, a subclass of the ProjectView, implements the Controller interface
 * and decides which pages in the ProjectView to show or act upon.
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
				$this->showPagingNavigation("index.php?mod=vm&amp;act=project&amp;vm_action=default");
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
				if($getvars['proj_id'] == '') {
					add_error(SHN_ERR_VM_NO_PROJECT);

					//if the user is just a site manager who got here due to overriding access control, only display his projects, otherwise display all
					if($dao->isSiteManager($_SESSION['user_id']) && !$ac->dataAccessIsAuthorized(array('vm_vol_position' => 'ru'), false))
						$projects = $dao->listProjects($_SESSION['user_id'], true);
					else
						$projects = $dao->listProjects();

					$this->displaySelectProjectForAssignmentForm($projects);
				} else {
					if($this->validateAssignForm($getvars)) {
						$p_uuid = $this->getAssigningVolId($getvars);
						$dao->assignVolunteerToPosition($p_uuid, $getvars['pos_id_'.$p_uuid]);
						add_confirmation(_('Volunteer has been successfully assigned'));
					}
					$p = new Project($getvars['proj_id']);
					$this->assignVol($getvars['proj_id'], $p->positions);
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
				$this->showPagingNavigation("index.php?mod=vm&amp;act=project&amp;vm_action=display_my_list");
			break;

			case 'process_add_position':
				if ($getvars['pos_id'] != null)
					$p = new Position($getvars['pos_id']);
				else
					$p= new Position();
				$p->proj_id= $getvars['proj_id'];
				$p->ptype_id = $getvars['ptype_id'];
				$p->description= $getvars['description'];
				$p->title= $getvars['title'];
				$p->numSlots= $getvars['numSlots'];
				$p->payrate= $getvars['payrate'];

				if($this->validateAddPosition($getvars)) {
				    $dao->savePosition($p);
				    //$this->displayConfirmation("Position assignment has been added to {$p->position_title}");
					$this->controlHandler(array('vm_action' => 'display_single', 'proj_id' => $p->proj_id));
				} else {
					$this->addPosition($p);
				}
			break;

			case 'add_position':
				//this case only displays the form to add/edit a position
				if($getvars['pos_id'])
					$p= new Position($getvars['pos_id']);
				else
			 		$p= new Position();

			 	if(isset($getvars['proj_id']))
			 		$p->proj_id = $getvars['proj_id'];

			 	$this->addPosition($p);
			break;

			case 'remove_position':
				$dao->removePosition($getvars['pos_id']);
				$this->controlHandler(array('vm_action' => 'display_single', 'proj_id'=> $getvars['proj_id']));
			break;

			default: 
				$this->listProjects();
				$this->showPagingNavigation("index.php?mod=vm&amp;act=project&amp;vm_action=default");
			break;
		}

 	}

	/**
	 * Gets the id of the volunteer who is being assigned.
	 * 
	 * @param $getvars the getvars used to submit the form
	 * @return the p_uuid of the volunteer who is being assigned, or null if not found
	 */
	 
	function getAssigningVolId($getvars) {
		//the volunteer's id is included in the name of the button used to submit the form
		$prefix = "assigning_vol_";
 		foreach($getvars as $key => $value) {
 			if(substr($key, 0, strlen($prefix)) == $prefix) {
 				return substr($key, strlen($prefix));
 			}
 		}
 		return null;
	}

 	/**
 	 * Validates that the required fields are filled out in order to assign a volunteer
 	 * or continue filtering when assigning
 	 *
 	 * @access public
 	 * @return true if the form is valid, false otherwise
 	 */
// Needed to be added - check if a valid position has been selected
 	function validateAssignForm($getvars)
 	{
 		global $global;
		require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

		$p_uuid = $this->getAssigningVolId($getvars);
		return ($p_uuid != null && isset($getvars["pos_id_$p_uuid"]));
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

 	 	//validate that a site manager has been selected only if we're adding
 	 	if(!isset($getvars['proj_id']))
 	 		$validated = $validated && shn_vm_not_empty($getvars['manager'], SHN_ERR_VM_NO_MGR);

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

	/**
	 * Validates adding a new position
	 */

	function validateAddPosition($getvars) {
		//assume valid to begin with
		$valid = true;

		if(!shn_vm_not_empty($getvars['title'])) {
			$valid = false;
			add_error(SHN_ERR_VM_NO_TITLE);
		}
		if(!shn_vm_not_empty($getvars['ptype_id'])) {
			$valid = false;
			add_error(SHN_ERR_VM_NO_POSITION_TYPE);
		}
		if(!shn_vm_not_empty($getvars['payrate']) || !is_numeric($getvars['payrate']) || $getvars['payrate'] <= 0) {
			$valid = false;
			add_error(SHN_ERR_VM_NO_PAYRATE);
		}
		if(!shn_vm_not_empty($getvars['numSlots']) || !is_numeric($getvars['numSlots']) || $getvars['numSlots'] <= 0) {
			$valid = false;
			add_error(SHN_ERR_VM_NO_TARGET);
		}
		if(!shn_vm_not_empty($getvars['description'])) {
			$valid = false;
			add_error(SHN_ERR_VM_NO_DESCRIPTION);
		}

		return $valid;
	}
 }

