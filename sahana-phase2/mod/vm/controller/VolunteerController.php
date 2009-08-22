<?php
/**
* Volunteer Controller
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

 class VolunteerController extends VolunteerView implements Controller
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
 		global $dao;

		//first authorize the user
 		$ac = new AccessController($getvars);
		if(!$ac->isAuthorized())
			return;

		//if authorized, move on to displaying the correct page
		switch($getvars['vm_action'])
		{
			case 'process_add':
				global $dao;

				/*
				 * First set up a Volunteer object to store all of the
				 * POST data
				 */

				if($_SESSION['logged_in'] && !$dao->isVolunteer($_SESSION['user_id']))
				{
					$v = new Volunteer();
					$v->info['ids'] = array();
					$v->p_uuid = $_SESSION['user_id'];
					$shn_user = true;
				}
				else if(isset($getvars['p_uuid']))
				{
					$v = new Volunteer($getvars['p_uuid']);
					$shn_user = false;
				}
				else
				{
					$v = new Volunteer();
					$v->info['ids'] = array();
					$shn_user = false;
				}

				$v->info['full_name'] = $getvars['full_name'];

				$v->info['ids'][$getvars['id_type']] = trim($getvars['serial']);

				$v->info['gender'] = $getvars['gender'];
				$v->info['dob'] = $getvars['dob'];
				$v->info['date_start'] = $getvars['start_date'];
				$v->info['date_end'] = $getvars['end_date'];
				$v->info['hour_start'] = $getvars['hrs_avail_start'];
				$v->info['hour_end'] = $getvars['hrs_avail_end'];
				$v->info['occupation'] = $getvars['occupation'];
				$v->info['affiliation'] = $getvars['affiliation'];
				$v->info['special_needs'] = $getvars['special_needs'];


				$v->info['locations'] = array();
				shn_get_parents(shn_location_get_form_submit_loc(), $v->info['locations']);

				$v->info['contact']=array();

				// put every input that begins with 'contact_' into the contact array
				foreach($getvars as $key => $value) {
					if(substr($key, 0, strlen('contact_')) == 'contact_') {
						$v->info['contact'][substr($key, strlen('contact_'))] = $value;
					}
				}

				//add skills information

				$v_skills = array();
				$skill_ids = $dao->getSkillIDs();
				foreach($skill_ids as $skill)
				{
					if($getvars["SKILL_$skill"] == 'on')
						$v_skills[] = $skill;
				}
				$v->info['skills'] = $v_skills;

				//add Sahana account information if necessary

				if($getvars['reg_account'] == 'true')
				{
					$v->info['account_info'] = array('account_name' => $getvars['full_name'],'user_name' => $getvars['user_name'],'pass' => $getvars['pass1']);
					$v->p_uuid = $getvars['existing_puuid'];
				}

				View::View($v);


				/*
				 * Check to see if the POST data is valid and act accordingly
				 */

				if($this->validateAddForm($getvars=$_REQUEST))
				{
					$v->save($shn_user);

					// picture
					$p = $_FILES['picture'];
					if(!empty($p['tmp_name'])) {
					$pic = new VMPicture();
					$pic->original = file_get_contents($p['tmp_name']);
					$pic->name = $p['name'];
					$pic->type = $p['type'];
					$pic->size = $p['size'];
					$pic->p_uuid = $v->p_uuid;
					if($pic->resize())
						$pic->save();
					else
						add_error(_("The image file is invalid, or is not of a supported type."));
				}

					add_confirmation(_('Changes saved.'));
					//if we just created a Sahana account, direct the user to log in
					if(!$_SESSION['logged_in'])
					{
						$this->displayPleaseLogin();
					}
					else
					{
						$this->displayVolunteer($v->p_uuid);
					}
				}
				else
				{
					$this->addVolunteer();
				}


			break;
			case 'display_add':
			    View::View();
			    if($dao->isVolunteer($_SESSION['user_id'])) {
			    	//if this user is a volunteer already, display the edit form
					$this->addVolunteer(new Volunteer($_SESSION['user_id']));
			    } else {
				    //otherwise display the add form
				    $this->addVolunteer();
			    }
			break;
			case 'display_edit':
				View::View();
				$this->addVolunteer(new Volunteer($getvars['p_uuid']));
			break;

			case 'display_confirm_delete':
				View::View();
				$this->confirmDelete($getvars['p_uuid']);
			break;

			case 'display_change_pass':
				View::View();
				$this->changePass($_SESSION['user_id']);
			break;

			case 'process_change_pass':
				global $global;
 				require_once($global['approot'].'inc/lib_security/lib_auth.inc');

				if($this->validateChangePassForm($getvars=$_REQUEST))
				{
					if(shn_change_password($getvars['p_uuid'],$getvars['cur_pass'],$getvars['pass1'])===true)
					{
						add_error(SHN_ERR_VM_PASSWORD_NOT_MATCH);
						$this->changePass($getvars['p_uuid']);
					}
					else
						add_confirmation(_("Your Password has been updated"));
				}
				else
					$this->changePass($getvars['p_uuid']);
			break;

			case 'process_delete':
				$v = new Volunteer();
				$v->delete($getvars['p_uuid']);
				View::View();
				$this->displayConfirmation('The requested user was deleted.');

				$extra_opts = array
				(
					'showPictures'			=> true,
					'showAvailability'		=> true,
					'showLocation'			=> true,
					'showStatus'			=> true,
					'showAffiliation'		=> true
				);
				$this->listVolunteers($dao->getVolunteers(), $extra_opts);
			break;

			case 'display_list_all':
				View::View();
				$extra_opts = array
				(
					'showPictures'			=> true,
					'showAvailability'		=> true,
					'showLocation'			=> true,
					'showStatus'			=> true,
					'showAffiliation'		=> true
				);
				$this->listVolunteers($dao->getVolunteers(), $extra_opts);
				$this->showPagingNavigation("index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_list_all");
			break;
			case 'display_list_assigned':
				View::View();
				$extra_opts = array
				(
					'showPictures'			=> true,
					'showAvailability'		=> true,
					'showLocation'			=> true,
					'showStatus'			=> true,
					'showAffiliation'		=> true
				);
				$this->listVolunteers($dao->getVolunteers(null, VM_SHOW_ALL_VOLUNTEERS_ASSIGNED), $extra_opts);
				$this->showPagingNavigation("index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_list_assigned");
			break;

			case 'display_mailbox':
				View::View(new Volunteer($_SESSION['user_id']));
				$this->displayMailbox($getvars['box']);
			break;

			case 'display_message':

				/*
				 * Since we are passing $_SESSION['user_id'] as the p_uuid of the user here,
				 * we can only view the message (i.e., the query will only succeed) if it belongs
				 * to the current logged in user. Therefore, there is no need for extra access
				 * control checks on displaying a message here.
				 */

				View::View();
				$this->displayMessage($_SESSION['user_id'], $getvars['msg_id'], $getvars['box']);
			break;

			case 'process_delete_message':
				global $dao;
				$dao->deleteMessage($_SESSION['user_id'], $getvars['msg_id'], $getvars['box']!='outbox');

				//add_confirmation('_(Message has been deleted'));

				View::View(new Volunteer($_SESSION['user_id']));
				$this->displayMailbox($getvars['box']);
			break;

			case 'display_send_message':
				$this->displaySendMessageForm();
			break;

			case 'process_send_message':
				global $dao;
				if($this->validateSendMessageForm($getvars=$_REQUEST))
				{
					$message = stripslashes($getvars['message']);
					$message = strtr($message, array("'" => "\\'"));		//have to escape any single quotes otherwise querying won't work

					$dao->sendMessage($_SESSION['user_id'], $getvars['to'], $message);

					add_confirmation(_("Message Sent"));
				}
				else
				{

					$to_list = array();

					$to = $getvars['to'];
					if(isset($to))
					{
						foreach($to as $person)
						{
							$to_list[$person] = $dao->getPersonName($person);
						}
					}

					$this->displaySendMessageForm($to_list);
				}
			break;

			case 'display_search':
				$advanced = $getvars['advanced'] == 'true';
				$this->openSearchForm();
				$this->displaySearchForm($advanced);
			break;

			case 'process_search':
				global $dao, $global;
				include_once($global['approot'].'mod/vm/lib/vm_validate.inc');

				View::View();

				//print_r($getvars);
				$vol_name = $getvars['vol_name'];					//name to search by
			    $vol_id = $getvars['vol_iden'];						//Identification number to search by
			    $loose = $getvars['loose'] == 'true';				//true to use loose name matching
			    $soundslike = $getvars['soundslike'] == 'true';		//true to use soundex name matching
			    $start_date =$getvars['start_date'];				//availability start
			    $end_date = $getvars['end_date'];					//availability end
			    $skills_matching = ($getvars['skills_matching']=='and_skills')?VM_SKILLS_ALL:VM_SKILLS_ANY;	//search for all or any of the skills present
			    $unassigned = $getvars['unassigned'] == 'true';		//true to search for only unassigned volunteers
			    $assigning = $getvars['assigning'];					//true if we are using the search to assign volunteers
			    $advanced = $getvars['advanced'] == 'true';			//true if we are using an advanced search
			    $just_assigned_vol = $getvars['p_uuid'] != '' && $assigning;		//true if we just assigned a volunteer to a project (nice to know if no results are found to not display an error)
				$date_constraint = $getvars['date_constraint'] == 'full_date';		//true if we must check for availability for the entire date range specified, false to check for any portion of the data range
				$positions = $getvars['positions'];

			    if($assigning)
			    	$assigning_proj = $getvars['proj_id'];
			    else
			    	$assigning_proj = null;

			    $location = '';
			    if(shn_vm_location_selected())
			    	$location = shn_location_get_form_submit_loc();


			    $skills = array();
				$skill_ids = $dao->getSkillIDs();

				foreach($skill_ids as $sk)
					if($getvars["SKILL_$sk"] == 'on')
						$skills[] = $sk;

				//if we're not using the search results to do assigning, open the form here so that all of our paging navigation
				//will also be part of the form
				if(!$assigning) {
					$this->openSearchForm();
				}

			    //Validate the fields
			    if($this->validateSearchForm($getvars))
			    {
					//get the search results and display them

				    $results = $dao->getVolSearchResults($vol_id, $vol_name, $skills, $skills_matching, $start_date, $end_date, $location, $date_constraint, $unassigned, $loose, $soundslike, $assigning_proj);
				    $this->displaySearchResults($results, $assigning, $assigning_proj, $advanced, $just_assigned_vol, $positions);
			    }

				if(!$assigning)
					$this->displaySearchForm($advanced, false);
				else
					$this->displaySearchForm(true, true);
			break;

			case 'display_single':
				$v = new Volunteer($getvars['p_uuid']);
				View::View($v);
				$this->displayVolunteer($getvars['p_uuid']);
			break;

			case 'process_remove_picture':
				$dao->deletePicture($dao->getPictureID($_GET['id']));
				View::View();
				if(empty($getvars['p_uuid']))
					$this->addVolunteer();
				else
					$this->addVolunteer(new Volunteer($getvars['p_uuid']));
			break;

			case 'display_portal':
				View::View(new Volunteer($_SESSION['user_id']));
				$this->displayPortal();
			break;

			case 'display_report_all':
				View::View();
				$this->displayVolunteerReport($dao->getVolunteersForReport());
			break;

			case 'display_custom_report_select_for_mgrs':
				$this->displayCustomReportFilterForMgrs($dao->listProjects($_SESSION['user_id'], true, true));
			break;

			case 'display_custom_report_select':
				View::View();

				$projects = array('ALL_PROJECTS' => '(all)') + $dao->listProjects(null, false, true);
				$orgs = array('ALL_ORGS' => '(all)') + $dao->getOrganizations(true);

				$this->displayCustomReportFilter($projects, $orgs, $dao->getVolunteerNames(true));
			break;

			case 'display_custom_report':
				View::View();
				$extra_opts = array();

				$proj_id = null;
				$org_id = null;
				$vols = array();

				if(isset($getvars['proj_id']) && $getvars['proj_id'] != 'ALL_PROJECTS')
				{
					$proj_id = $getvars['proj_id'];
					$extra_opts['reportProjName'] = $dao->getProjectName($proj_id);
				}

				if(isset($getvars['org_id']) && $getvars['org_id'] != 'ALL_ORGS')
				{
					$org_id = $getvars['org_id'];
					$temp = $dao->getOrganizationInfo($org_id);
					$extra_opts['reportOrgName'] = $temp['name'];
				}

				if(!empty($getvars['vols']) && is_array($getvars['vols']))
				{
					$extra_opts['reportingSpecificVolunteers'] = true;
					$vols = $getvars['vols'];
				}

				$this->displayVolunteerReport($dao->getVolunteersForReport($proj_id, $org_id, $vols), $extra_opts);
			break;

			case 'display_modify_skills':
				$this->displayModifySkills();
			break;

			case 'process_add_skill':
				global $global;
				require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

				if(empty($getvars['skill_desc']) || empty($getvars['skill_code']))
					add_error(_('Please specify both a skill description and skill code'));
				else
				{
					$find = array("/ *".VM_SKILLS_DELIMETER." */", "/^ +/", "/ +$/");
					$replace = array("-", '', '');
					$description = preg_replace($find, $replace, $getvars['skill_desc']);

					if(!$dao->addSkill($getvars['skill_code'], $description))
						add_error(_('The specified skill code already exists. Please choose another'));
				}
				$this->displayModifySkills();
			break;

			case 'process_remove_skill':
				if(!empty($_REQUEST['skills']))
					foreach($_REQUEST['skills'] as $code)
						$dao->removeSkill($code);
				$this->displayModifySkills();
			break;

			case 'display_approval_management':
				//currently only site manager approval is allowed, later credential approval will be added
				$this->displayApprovalForm($dao->getVolunteerNames(),  $dao->getVolunteersByAbility('MGR'));
			break;

			case 'process_approval_modifications':
				//currently only site manager approval is allowed, later credential approval will be added
				$dao->updateAbilityStatus($getvars['vol_id'], 'MGR', isset($getvars['approve']));
				add_confirmation(_('Approval information has been updated'));
				$this->displayApprovalForm($dao->getVolunteerNames(), $dao->getVolunteersByAbility('MGR'));
			break;

			case 'process_approval_upgrades':
				//currently only site manager approval is allowed, later credential approval will be added
				$dao->updateAbilityStatus($getvars['vol_id'], 'MGR', true);
				add_confirmation(_('Approval information has been updated'));
				$this->displayApprovalForm($dao->getVolunteerNames(), $dao->getVolunteersByAbility('MGR'));
			break;

			case 'display_log_time_form':
				$this->showLogTime($getvars['p_uuid'], $getvars['pos_id']);
			break;

			case 'process_log_time':
				$start = strtotime($getvars['startDate'].' '.$getvars['startTime']);
				if(empty($getvars['numHours']))
					$end = strtotime($getvars['endDate'].' '.$getvars['endTime']);
				else
					$end = $start + $getvars['numHours'] * 60 * 60;

				if(($e = validateShiftTimes($start, $end)) === VM_OK) {
					if($dao->logShift($getvars['p_uuid'], $getvars['pos_id'], $start, $end)) {
						$this->displayConfirmation('Your time was logged successfully.');
						$v = new Volunteer($getvars['p_uuid']);
						View::View($v);
						$this->displayVolunteer($getvars['p_uuid']);
					}
					else
						add_error(_("There was a problem logging your time. Please go back and try again."));
				} else {
					add_error(_("Error logging time:").$e);
					$this->showLogTime($getvars['p_uuid'], $getvars['pos_id']);
				}
			break;

			case 'review_hours':
				if(empty($getvars['proj_id'])) {
					$this->displaySelectReviewHours();
				} else {
					$this->displayReviewHours($getvars['proj_id']);
				}
			break;

			case 'process_review_hours':
				$this->dao->reviewShift($getvars['shift_id'], $getvars['status']);
				$this->displayReviewHours($getvars['p_uuid'], $getvars['pos_id']);
			break;

			default:
				if($_SESSION['logged_in'])
				{
					View::View(new Volunteer($_SESSION['user_id']));
					$this->displayPortal();
				}
		}
 	}

 	/**
 	 * Checks to see if all fields are valid in the add/edit volunteer form.
 	 *
 	 * @access public
 	 * @return false if any fields are invalid, true otherwise; if errors occur, they
 	 * 			are displayed on the page
 	 */

 	function validateAddForm($getvars)
 	{
 		global $global;
 		require_once($global['approot'].'inc/lib_validate.inc');
 		require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

		//assume no errors to begin with
		$validated = true;

		//validate name field
		$validated = $validated && shn_vm_not_empty($getvars['full_name'], SHN_ERR_VM_NO_NAME);

		//validate start and end dates
		if(!shn_vm_valid_date($getvars['start_date']) || !shn_vm_valid_date($getvars['end_date']))
		{
			add_error(SHN_ERR_VM_BAD_DATES);
			$validated = false;
		}
		else
		{
			$validated = $validated && shn_vm_compatible_dates($getvars['start_date'], $getvars['end_date'], SHN_ERR_VM_DATES_INCOMPATIBLE);
		}

		//validate the date of birth only if it is present

		if($getvars['dob'] != '')
		{
			if(!shn_vm_valid_date($getvars['dob']))
			{
				add_error(SHN_ERR_VM_INVALID_DOB);
				$validated = false;
			}
			else
			{
				$validated = $validated && shn_vm_compatible_dates($getvars['dob'], date('Y-m-d'), SHN_ERR_VM_FUTURE_DOB);
			}
		}

		//validate the start and end hours if present

		if($getvars['hrs_avail_start'] != '')
			$validated = $validated && shn_vm_valid_time($getvars['hrs_avail_start'], SHN_ERR_VM_BAD_START_TIME);

		if($getvars['hrs_avail_end'] != '')
			$validated = $validated && shn_vm_valid_time($getvars['hrs_avail_end'], SHN_ERR_VM_BAD_END_TIME);

		//validate if at least one skill has been selected

		$validated = $validated && shn_vm_skill_selected($getvars, SHN_ERR_VM_NO_SKILLS_SELECTED);

		//validate the Sahana account information if necessary

		if($getvars['reg_account'] == 'true')
		{
			$validated = $validated && shn_vm_not_empty($getvars['user_name'], SHN_ERR_VM_BAD_USER_NAME);
			$validated = $validated && shn_vm_username_not_taken($getvars['user_name'], SHN_ERR_VM_USER_EXISTS);

			if(shn_vm_not_empty($getvars['pass1'], SHN_ERR_VM_BAD_PASSWORD))
			{
				if(shn_vm_not_empty($getvars['pass2'], SHN_ERR_VM_BAD_PASSWORD))
					$validated = $validated && shn_vm_fields_equal($getvars['pass1'], $getvars['pass2'], SHN_ERR_VM_INCOMPATIBLE_PASSWORDS);
				else
					$validated = false;
			}
			else
				$validated = false;

		}

		return $validated;
 	}

 	/**
 	 * validates the Change Password form
 	 *
 	 * @access public
 	 * @return true if the form is valid and false otherwise.
 	 */

	function validateChangePassForm($getvars)
	{
		global $global;
 		require_once($global['approot'].'inc/lib_validate.inc');
 		require_once($global['approot'].'mod/vm/lib/vm_validate.inc');


		$validated = true;
		$validated = $validated && shn_vm_not_empty($getvars['cur_pass'], SHN_ERR_VM_BAD_CUR_PASSWORD);
		if(shn_vm_not_empty($getvars['pass1'], SHN_ERR_VM_BAD_NEW_PASSWORD))
		{
			if(shn_vm_not_empty($getvars['pass2'], SHN_ERR_VM_BAD_NEW_PASSWORD))
				$validated = $validated && shn_vm_fields_equal($getvars['pass1'], $getvars['pass2'], SHN_ERR_VM_INCOMPATIBLE_PASSWORDS);
			else
				$validated = false;
		}
		else
			$validated = false;

		return $validated;
	}

	/**
	 * Validates the Send Message form.
	 *
	 * @access public
	 * @return true if the form is valid, false otherwise
	 */

	function validateSendMessageForm($getvars)
	{
		global $global;
 		require_once($global['approot'].'inc/lib_validate.inc');
 		require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

		//assume to be valid
		$validated = true;

		//check 'To' list
		if(count($getvars['to']) == 0)
		{
			$validated = false;
			add_error(SHN_ERR_VM_NO_TO_VOLS);
		}

		//check the message
		$validated = $validated && shn_vm_not_empty($getvars['message'], SHN_ERR_VM_NO_MESSAGE);

		return $validated;
	}
	/**
	 * Validates the fields in the search form
	 *
	 * @return true if the form is valid, false otherwise
	 */
	function validateSearchForm($getvars)
	{
		//print_r($_REQUEST);
		$validated = true;

		//validate that at least one field is specified if we are not assigning to a project
		if(!$getvars['assigning'])
		{
		    if(!shn_vm_not_empty($getvars['vol_iden']) && !shn_vm_not_empty($getvars['vol_name']) && !shn_vm_skill_selected($getvars) && !shn_vm_not_empty($getvars['start_date']) && !shn_vm_not_empty($getvars['end_date']) && !shn_vm_location_selected() && $getvars['unassigned'] != 'true')
		    {
		        add_error(SHN_ERR_VM_SEARCH_NO_PARAMS);
		        $validated = false;
		    }
		    else if((strlen($getvars['vol_iden']) <= 3) && !shn_vm_not_empty($getvars['vol_name']) && !shn_vm_skill_selected($getvars) && !shn_vm_not_empty($getvars['start_date']) && !shn_vm_not_empty($getvars['end_date']) && !shn_vm_location_selected() && $getvars['unassigned'] != 'true')
		    {
		        add_error(SHN_ERR_VM_SEARCH_BAD_ID);
		        $validated = false;
		    }
		}

		if($getvars['date_constraint'] == 'full_date' && (!shn_vm_not_empty($getvars['start_date']) || !shn_vm_not_empty($getvars['end_date'])))
		{
			add_error(SHN_ERR_VM_BAD_DATE_RANGE);
	    	$validated = false;
		}
		else if(!shn_vm_not_empty($getvars['start_date']) && shn_vm_not_empty($getvars['end_date']))
	    {
	    	add_error(SHN_ERR_VM_NO_START_DATE);
	    	$validated = false;
	    }

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

/**
 * In combination with the Sahana stream functions, shows a bare-bones printer friently page representing
 * the last printer frienfly report generated by the current user.
 *
 * Accessed at url : index.php?mod=vm&stream=text&act=printer_friendly_report
 */

function shn_text_vm_printer_friendly_report() {
	//first check to make sure that the user can actually view the report according to access control
	$ac = new AccessController();
	$getvars = array('act' => 'volunteer', 'vm_action' => 'display_custom_report');
	//also add project id to getvars to allow project manager to view reports for their own projects
	if(isset($_REQUEST['proj_id'])) {
		$getvars['proj_id'] = $_REQUEST['proj_id'];
	}
	if($ac->isAuthorized(false, $getvars)) {
		echo "
		<html>
			<head>
				<title>". _("Volunteer Management Report"). "</title>
			</head>
			<body>
				{$_SESSION['vm_last_printer_friendly_report']}
			</body>
		</html>
";
	}
}


