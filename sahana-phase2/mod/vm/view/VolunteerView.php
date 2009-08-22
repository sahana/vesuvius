<?php

/**
* VolunteerView.php - define the view for volunteer-related functions
*
* The VolunteerView class handles any view functionality with regards to
* volunteers. It is a subclass of the View class, so it inherits the reference
* to the engine object for use of PHP templates.
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

// think this is required for running phpunit
require_once('View.php');

class VolunteerView extends View
{
	/**
	 * Display an entire single volunteer's information
	 *
	 * @param $p_uuid the p_uuid of the volunteer to display
	 * @return void
	 */

	function displayVolunteer($p_uuid)
	{
		if($this->model != null)
		{
			global $dao;

			// Displays gender of volunteer
			$info = $this->model->info;
			if (isset($info['gender']))
			{
				if (strcasecmp($info['gender'],'m')==0)
					$info['gender']='Male';
				else
					$info['gender']='Female';
			}

			// get project(s), if any, to which volunteer is assigned
			$projects = array();
			if(is_array($this->model->proj_id))
				foreach($this->model->proj_id as $proj_id)
					$projects[$proj_id] = $dao->getProjectName($proj_id);

			$this->engine->assign('projects', $projects);

			$this->engine->assign('info',$info);
			$this->engine->assign('ids', $info['ids']);
			$this->engine->assign('dob', $info['dob']);
			$this->engine->assign('id_types', $dao->getIdTypes());
			$this->engine->assign('contact_types', $dao->getContactTypes());
			$this->engine->assign('p_uuid', $this->model->p_uuid);
			$this->engine->assign('date_format', vm_date_format);
			$this->engine->assign('occupation', $info['occupation']);
			$this->engine->assign('VolPositions',$dao->listPositions(null,$p_uuid));
			$org_info = $dao->getOrganizationInfo($info['affiliation']);
			$this->engine->assign('affiliation', $org_info['name']);
			$this->engine->assign('special_needs', $info['special_needs']);


			$contact_types=$dao->getContactTypes();
			$this->engine->assign('contact_types',$contact_types);

			if($img_uuid = $this->model->getPictureID())
				$this->engine->assign('pictureID', $img_uuid);

			$this->engine->assign('dob', ($info['dob'] == '0000-00-00')?'':($info['dob']));
			$this->engine->assign('date_start', ($info['date_start'] == '0000-00-00')?'':($info['date_start']));
			$this->engine->assign('date_end', ($info['date_end'] == '0000-00-00')?'':$info['date_end']);
			$this->engine->assign('hour_start', ($info['hour_start'] == '00:00:00')?'':$info['hour_start']);
			$this->engine->assign('hour_end', ($info['hour_end'] == '00:00:00')?'':$info['hour_end']);

			/*
			 * Get the various location information and assign it to the engine object
			 */

			$location_info = array();
			if(isset($info['locations']))
			{
				foreach($info['locations'] as $loc_uuid)
				{
					if($loc_uuid != null && $loc_uuid != -1 && $loc_uuid != 'NULL')
						$location_info[] = $dao->getLocation($loc_uuid);
				}
			}

			$this->engine->assign('locations', $location_info);

			/*
			 * Get Skills information
			 */

			$this->engine->assign('vol_skills', $dao->getVolSkillsTree($p_uuid));

			//get whether the current logged in user is allowed to edit or delete this information

			$ac = new AccessController();
			$this->engine->assign('edit_auth', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_edit', array('p_uuid' => $p_uuid))));
			$this->engine->assign('delete_auth', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_confirm_delete', array('p_uuid' => $p_uuid))));
			$this->engine->assign('ac', $ac);

			//check to see how much info to display about the person

			if($ac->dataAccessIsAuthorized($ac->access['volunteer']['display_single']['tables'], false) || $_REQUEST['p_uuid'] == $_SESSION['user_id'])
				$this->engine->assign('view_auth', VM_ACCESS_ALL);
			else if($dao->isSiteManager($_SESSION['user_id']))
				$this->engine->assign('view_auth', VM_ACCESS_PARTIAL);
			else
				$this->engine->assign('view_auth', VM_ACCESS_MINIMAL);

			$this->engine->display('volunteer/display.tpl');

		}
	}

	/**
	 * Display a small subset of all volunteers' information
	 *
	 * @access public
	 * @param $volunteers		- an array of volunteers to display (result from DAO::getVolunteers())
	 * @param $extra_opts		- an array specifying any of the following optional parameters:
	 * 		'showPictures'		- true to show pictures of volunteers
	 *		'showAvailability 	- true to show volunteer's availability
	 *		'showIDs 			- true to show volunteer's identification numbers
	 * 		'showSkills'	 	- true to show a drop-down list of all skills
	 * 		'searchParams'		- list of optional parameters that apply to using this volunteer list as a search result list:
	 * 							- 'justAssignedVol'	- true if we just assigned a volunteer
	 * 							- 'advanced'		- true if it is an advanced search
	 * 		'showStatus'		- true to show the volunteer's status
	 * 		'showAffiliation'	- true to show the volunteer's affiliation
	 * 		'showLocation'		- true to show the volunteer's location
	 * 		'modifyProjId'		- set this to the appropriate project ID if using this volunteer list to assign or remove volunteers from a project
	 * 		'showAssignButton'  - true to show a button to assign the volunteer to a project (must also specify modifyProjId)
	 *  	'showRemove'			- true to show a link to remove the volunteer from a project (must also specify modifyProjId)
	 *		'reporting'			- true to show reporting information (payrate, hours, etc.)
	 *		'reportProjId'		- if reporting, the project ID of the project that we're reporting about
	 *		'reportOrgId'		- if reporting, the organization ID of the organization that we're reporting about
	 * 		'rowHeight'			- if specified, will define the height (in pixels) of the rows displayed, otherwise will default to VM_IMAGE_THUMB_HEIGHT
	 * @return void
	 */

	function listVolunteers($volunteers, $extra_opts=array())
	{
		global $dao;
		$ac = new AccessController();
		View :: View(new Volunteer());
		//get the display options from extra_options
		$modifyProjId 		= isset($extra_opts['modifyProjId'])?$extra_opts['modifyProjId']:null;
		$showPictures 		= isset($extra_opts['showPictures'])?$extra_opts['showPictures']:false;
		$showRemove 			= isset($extra_opts['showRemove'])?$extra_opts['showRemove']:false;
		$showAvailability	= isset($extra_opts['showAvailability'])?$extra_opts['showAvailability']:false;
		$showIDs 			= isset($extra_opts['showIDs'])?$extra_opts['showIDs']:false;
		$showSkills			= isset($extra_opts['showSkills'])?$extra_opts['showSkills']:false;
		$showAssignButton	= isset($extra_opts['showAssignButton'])?$extra_opts['showAssignButton']:false;
		$searchParams		=!empty($extra_opts['searchParams'])?$extra_opts['searchParams']:array();
		$reporting 			= isset($extra_opts['reporting'])?$extra_opts['reporting']:false;
		$rowHeight 			= isset($extra_opts['rowHeight'])?$extra_opts['rowHeight']:VM_IMAGE_THUMB_HEIGHT;
		$showStatus			= isset($extra_opts['showStatus'])?$extra_opts['showStatus']:false;
		$showAffiliation	= isset($extra_opts['showAffiliation'])?$extra_opts['showAffiliation']:false;
		$showLocation		= isset($extra_opts['showLocation'])?$extra_opts['showLocation']:false;
		$reportProjName		= isset($extra_opts['reportProjName'])?$extra_opts['reportProjName']:null;
		$reportOrgName		= isset($extra_opts['reportOrgName'])?$extra_opts['reportOrgName']:null;
		$showHours		    = isset($extra_opts['showHours'])?$extra_opts['showHours']:false;
		$showPositions		= isset($extra_opts['showPositions'])?$extra_opts['showPositions']:false;
		$positions			= empty($extra_opts['positions'])?array():$extra_opts['positions'];

		// if we're displaying images here, get the IDs
		if(VM_LIST_PICTURES && $showPictures)
			foreach($volunteers as $key => $vol)
				if($img_uuid = $dao->getPictureID($vol->p_uuid))
					$volunteers[$key]->pictureID = $img_uuid;

		//assign the booleans to tell what to display
		$this->engine->assign('modifyProjId', 		$modifyProjId);
		$this->engine->assign('showPictures', 		VM_LIST_PICTURES && $showPictures);
		$this->engine->assign('showRemove', 		$showRemove);
		$this->engine->assign('showAvailability', 	$showAvailability);
		$this->engine->assign('showIDs', 			$showIDs);
		$this->engine->assign('showSkills',			$showSkills);
		$this->engine->assign('showAssignButton', 	$showAssignButton);
		$this->engine->assign('reporting', 			$reporting);
		$this->engine->assign('rowHeight', 			$rowHeight);
		$this->engine->assign('showStatus', 		$showStatus);
		$this->engine->assign('showAffiliation', 	$showAffiliation);
		$this->engine->assign('showLocation', 		$showLocation);
		$this->engine->assign('reportProjName', 	$reportProjName);
		$this->engine->assign('reportOrgName', 		$reportOrgName);
		$this->engine->assign('showHours', 		    $showHours);
		$this->engine->assign('showPositions', 		$showPositions);

		$this->engine->assign('searching', 			!empty($searchParams));
		$this->engine->assign('justAssignedVol', 	isset($searchParams['justAssignedVol'])?$searchParams['justAssignedVol']:false);
		$this->engine->assign('advancedSearch',		isset($searchParams['advanced'])?$searchParams['advanced']:false);

		$this->engine->assign('volunteers', $volunteers);
		$this->engine->assign('positions', $positions);

		//suppress certain data based on access control
		if($ac->dataAccessIsAuthorized($ac->access['volunteer']['display_single']['tables'], false))
			$this->engine->assign('view_auth', VM_ACCESS_ALL);
		else if($dao->isSiteManager($_SESSION['user_id']))
			$this->engine->assign('view_auth', VM_ACCESS_PARTIAL);
		else
			$this->engine->assign('view_auth', VM_ACCESS_MINIMAL);

		$this->engine->display('volunteer/list.tpl');
	}

	/**
	 * Displays the form to either add a new volunteer or edit an existing one.
	 *
	 * @param $v a reference to a volunteer object, if it is desired to edit this volunteer's
	 *           information. Alternatively, if this parameter is not specified, a form to
	 *           add a new volunteer will be displayed.
	 */

	function addVolunteer($v=null) {
		/*
		 * Assign some important information to the engine object
		 */

 		global $dao;
		$this->engine->assign("action",($v==null)?"Add":"Save");
		$this->engine->assign('info', (($v==null)?array():$v->info));
		$this->engine->assign('full_name', $v==null?'':$v->info["full_name"]);
		$this->engine->assign('id_types', $dao->getIdTypes());
		if($v != null)
			$this->engine->assign('p_uuid', $v->p_uuid);

		//Id type of select from
 		if (count($v->info["ids"]) > 0)
 			$id_type= array_pop(array_keys($v->info["ids"]));
 		$this->engine->assign('id_type', $v==null?'':$id_type);
		$this->engine->assign('id_types', $dao->getIdTypes());
		$this->engine->assign('serial', $v->info['ids'][$id_type]);

		//most specific location
		$this->engine->assign('location', ($v != null && count($v->info['locations']) != 0)?$v->info['locations'][0]:null);
		//Create an array of necessary hidden inputs and assign them to engine

		$hidden= array();
		if ($v!=null)
			$hidden["p_uuid"]=$v->p_uuid;
		$this->engine->assign('hidden',$hidden);

		//gender, occupation, and organization affiliation
		$this->engine->assign('gender', $v->info['gender']);
		$this->engine->assign('occupation', $v->info['occupation']);
		$this->engine->assign('affiliation', $v->info['affiliation']);

		//list of organziations
		$orgs = array(''=>'');

		$this->engine->assign('orgs', array_merge($orgs, $dao->getOrganizations()));

		if($v != null && $img_uuid = $v->getPictureID())
			$this->engine->assign('pictureID', $img_uuid);

		// Start/End date & Start/End Hours
		$this->engine->assign('dob', ($v->info['dob'] == '0000-00-00')?'':($v->info['dob']));
		$this->engine->assign('date_start', ($v->info['date_start'] == '0000-00-00')?'':($v->info['date_start']));
		$this->engine->assign('date_end', ($v->info['date_end'] == '0000-00-00')?'':$v->info['date_end']);
		$this->engine->assign('hour_start', ($v->info['hour_start'] == '00:00:00')?'':$v->info['hour_start']);
		$this->engine->assign('hour_end', ($v->info['hour_end'] == '00:00:00')?'':$v->info['hour_end']);

		$this->engine->assign('contact_types', $dao->getContactTypes());

		//Skills information

		//Skills information
		if($_GET['vm_action'] == 'process_add') {
			//we are responding to POST data. Preset the skills accordingly.
			$skills = array();
			foreach($_REQUEST as $key => $value) {
				$matches = array();
				if($value == 'on' && preg_match("@SKILL_(.*)$@", $key, $matches)) {
					$skills[] = $matches[1];
				}
			}
			$this->engine->assign('select_skills_tree', $dao->getSelectSkillsTree(null, false, $skills));
		} else {
			//we are displaying the add or edit form for the first time
			if($v == null) {
				$this->engine->assign('select_skills_tree', $dao->getSelectSkillsTree());
			} else {
				$this->engine->assign('select_skills_tree', $dao->getSelectSkillsTree($v->p_uuid));
			}
		}

		//special needs information
		$this->engine->assign('special_needs', $v->info['special_needs']);

		//Handle whether or not the user must register a Sahana account
		$this->engine->assign('reg_account', !$_SESSION['logged_in']);

		//Display the template

		$this->engine->display('volunteer/add.tpl');
	}

	/**
	 * Tells the user to login (after registering as a volunteer)
	 *
	 * @return void
	 */

	function displayPleaseLogin()
	{
		$this->engine->display('volunteer/please_login.tpl');
	}


	/**
	 * Displays a confirmation page asking if you really want to delete the volunteer.
	 *
	 * @param $p_uuid
	 * @return void
	 */
	function confirmDelete($p_uuid) {
		$v = new Volunteer($p_uuid);
		$name = $v->info['full_name'];
		$this->engine->assign('p_uuid', $p_uuid);
		$this->engine->assign('name', $name);
		$this->engine->display('volunteer/confirm_delete.tpl');
	}

	/**
	 * Displays the home screen for a volunteer
	 *
	 * @return void
	 * @access public
	 */

	function displayPortal()
	{
	 	//display links and their descriptions according to access control
		$ac = new AccessController();

		$this->engine->assign('vol_assign', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_select_project')));
		$this->engine->assign('showAssigned', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_list_assigned')));
		$this->engine->assign('listVolunteers', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_list_all')));
		$this->engine->assign('search', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_search')));
		$this->engine->assign('add_proj', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_add')));
		$this->engine->assign('listMyProjects', $ac->isAuthorized(false, $ac->buildURLParams('project', 'display_my_list')));
		$this->engine->assign('listAllProjects', $ac->isAuthorized(false, $ac->buildURLParams('project', 'default')));
		$this->engine->assign('inbox', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_mailbox')));
		$this->engine->assign('outbox', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_mailbox', array('box' => 'outbox'))));
		$this->engine->assign('sendMessage', $ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_send_message')));


	 	$this->engine->assign('projects', $this->model->proj_id);
	 	$this->engine->assign('p_uuid', $this->model->p_uuid);
	 	$this->engine->assign('messages', $this->model->info['messages']);
	 	$this->engine->display('volunteer/portal.tpl');
	}

	 /**
	  * Displays a form for changing user's password.
	  *
	  * @access public
	  * @param p_uuid 	- the user's unique id
	  * @return void
	  */

	 function changePass($p_uuid) {
			$this->engine->assign('p_uuid', $p_uuid);
			$this->engine->display('volunteer/change_pass.tpl');
	 }

	  /**
	   * Displays a volunteer's inbox or outbox
	   *
	   * @param $box	- 'outbox' to display outbox, anything to display inbox
	   * @return void
	   */

	function displayMailbox($box='inbox')
	{
		global $dao;

	   		//set up regular expressions for special syntax rules

	   		$find = array	(
	   							"/</",
								"/>/",
								"/{proj\s+(.+?)\s+(.+?)}/",
								"/{vol\s+(.+?)\s+(.+?)}/",
								"/\r\n/",
								"/\r/",
								"/\n/"
							);

			$replace = array(
								"&lt;",
								"&gt;",
								"$2",
								"$2",
								" ",
								" ",
								" ",
							);

	   		$messages = $dao->getMessages($this->model->p_uuid, $box!='outbox');
	   		foreach($messages as $key=>$value)
	   		{
	   			//apply special formatting to the message

				$messages[$key]['message'] = preg_replace($find, $replace, $messages[$key]['message']);

	   			if(strlen($messages[$key]['message'])>= 34)
  	 				$messages[$key]['message'] = substr($messages[$key]['message'], 0, 30)."...";

				$messages[$key]['bgcolor'] = ($value['checked'] == 0)?'#FFFFA0':'white';

				//get the list of message recipients as well as who the message is from

				if($value['from_id'] == 'SYS_MSG')
					$messages[$key]['from'] = _('System Message');
				else
					$messages[$key]['from'] = $dao->getPersonName($value['from_id']);

    			$list = $dao->getToList($messages[$key]['message_id']);
    			$to_list = "";
    			foreach($list as $p_uuid => $name){
    				$to_list .= $name . ", ";
    			}
    			$to_list = substr($to_list, 0, strlen($to_list) - 2);

    			if(strlen($to_list) > 34)
    				$to_list = substr($to_list, 0, 30) . "...";

    			$messages[$key]['to'] = $to_list;
	   		}
	   		$this->engine->assign('messages', $messages);
	   		$this->engine->assign('box', $box!='outbox');
	   		$this->engine->assign('box_name', ($box!='outbox')?'inbox':$box);
	   		$this->engine->display('message/mailbox.tpl');
	   		$this->showPagingNavigation("index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_mailbox&amp;box=$box");
	}

	   /**
	    * Display a message
	    *
	    * @param $p_uuid		- the p_uuid of the volunteer who this message was sent to
	    * @param $message_id		- the message ID of the message to display
	    * @return void
	    *
	    * To avoid having HTML be stored in the database, messages can include the following special syntax:
	    *
	    * {proj <id> <name>} to link to a project
	    * {vol <id> <name>} to link to a volunteer
	    * "\r", "\n", or "\r\n" are all translated to line breaks
	    * HTML syntax is displayed and not allowed to be parsed by the browser
	    */

	function displayMessage($p_uuid, $message_id, $box='inbox')
	{
	    	global $dao;
	    	$message = $dao->getMessage($p_uuid, $message_id, $box!='outbox');

			if(!empty($message))
			{
				//get who the message is from
				if($message['from_id'] == 'SYS_MSG')
					$message['from'] = _('System Message');
				else
					$message['from'] = $dao->getPersonName($message['from_id']);

		    	//get the list of message recipients
		    	$list = $dao->getToList($message['message_id']);
		    	$to_list = "";
		    	foreach($list as $p_uuid => $name)
		    		$to_list .= "$name, ";

		    	$to_list = substr($to_list, 0, strlen($to_list) - 2);
		    	$message['to'] = $to_list;

		    	//apply special syntax rules to the message
				$find = array	(
									"/</",
									"/>/",
									"/{proj\s+(.+?)\s+(.+?)}/",
									"/{vol\s+(.+?)\s+(.+?)}/",
									"/\r\n/",
									"/\r/",
									"/\n/"
								);

				$replace = array(
									"&lt;",
									"&gt;",
									"<a href=\"?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id=$1\">$2</a>",
									"<a href=\"?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid=$1\">$2</a>",
									"<br />",
									"<br />",
									"<br />",
								);
				$message = preg_replace($find, $replace, $message);
			}

	    	$this->engine->assign('box', $box!='outbox');
	    	$this->engine->assign('message', $message);
	    	$this->engine->display('message/message.tpl');

	}

	    /**
	     * Displays a form to send a message
	     *
	     * @access public
	     * @param $to the volunteers to preset the 'To' list to
	     * @return void
	     */

	function displaySendMessageForm($to=array())
	{
		global $dao;
		$this->engine->assign('to_list', $dao->getVolunteerNames());
		$this->engine->assign('to', $to);
		$this->engine->display('message/send_message.tpl');
	}

	/**
	 * Opens the search form. Calling this function early on in the page is important to
	 * preserve all POST data whenever redirecting to the same search form, such as in
	 * paging.
	 */

	function openSearchForm() {
		shn_form_fopen('volunteer&vm_action=process_search', null, array('req_message' => false));
	}

	    /**
	     * Displays a search form for a volunteer
	     *
	     * @param $advanced 	- true to display an advanced search form
	     * @param $assigning	- true if we are using this to filter results when assigning a volunteer
	     */

	    function displaySearchForm($advanced=false, $assigning=false)
	    {
	    	global $dao;
	    	$this->engine->assign('advanced', $advanced);

	    	$skills = array();
			$skill_ids = $dao->getSkillIDs();
			foreach($skill_ids as $sk)
			{
				if($_REQUEST["SKILL_$sk"] == 'on')
					$skills[] = $sk;
			}

	    	$this->engine->assign('skills', $dao->getSelectSkillsTree(null, null, $skills));
	    	$this->engine->assign('assigning', $assigning);

	    	$this->engine->display('volunteer/search.tpl');
	    }

	    /**
	     * Displays the search results for a particular volunteer search
	     *
	     * @param $results 				- 	an array of Volunteer objects.
	     * @param $assigning			- 	true if we are searching to assign these volunteers
	     * @param $proj_id				- 	the project ID to be assigning to if $assigning is true
	     * @param $advanced				- 	true if we are displaying search results from an advanced search
	     * @param $just_assigned_vol	- 	true if $assigning is true and we just assigned a volunteer (nice to know if no search results are found to not display an error)
	     */

	    function displaySearchResults($results, $assigning=false, $proj_id=null, $advanced=false, $just_assigned_vol=false, $positions=null)
	    {
	    	$extra_opts = array
			(
				'showPictures'			=> true,
				'showAvailability'		=> true,
				'showLocation'			=> true,
				'showStatus'			=> true,
				'showAffiliation'		=> true,
				'showSkills'			=> true,
				'searchParams'			=> array('advancedSearch' => $advanced, 'justAssignedVol' => $just_assigned_vol),
				'showAssignButton'		=> $assigning,
				'modifyProjId'			=> $proj_id,
				'positions'				=> $positions
			);
	    	$this->listVolunteers($results, $extra_opts);
	    	$this->showPagingNavigation(null, true);
	    }

	    /**
	     * Displays a form to filter report information by
	     */

	    function displayCustomReportFilter($projects, $orgs, $vols)
	    {
	    	$this->engine->assign('projects', $projects);
	    	$this->engine->assign('orgs', $orgs);
	    	$this->engine->assign('vols', $vols);
	    	$this->engine->display('volunteer/custom_report_select.tpl');
	    }

	    /**
	     * Displays a form to filter report information intended for only site managers
	     */

	    function displayCustomReportFilterForMgrs($projects)
	    {
	    	$this->engine->assign('projects', $projects);
	    	$this->engine->display('volunteer/custom_report_select_for_mgrs.tpl');
	    }

	    /**
	     * Displays a volunteer report
	     *
	     * @param	$volunteers		- an array of volunteer information to report (typically a result from DAO::getVolunteersForReport())
	     * @param	$extra_opts		- an array of optional extra options to specify, with the following structure:
	     * Array
	     * (
	     * 		'reportProjName'					=> the name of the project reporting on
	     * 		'reportOrgName'					=> the name of the organization reporting on
	     * 		'reportingSpecificVolunteers'	=> true if reporting only on specificly chosen volunteers
	     * )
	     */

	    function displayVolunteerReport($volunteers, $extra_opts=array())
	    {
	    	$this->engine->assign('volunteers', $volunteers);
	    	$this->engine->assign('reportProjName', isset($extra_opts['reportProjName'])?$extra_opts['reportProjName']:null);
	    	$this->engine->assign('reportOrgName', isset($extra_opts['reportOrgName'])?$extra_opts['reportOrgName']:null);
	    	$this->engine->assign('reportingSpecificVolunteers', isset($extra_opts['reportingSpecificVolunteers'])?$extra_opts['reportingSpecificVolunteers']:false);
	    	$this->engine->display('volunteer/report.tpl');
	    }

	    /**
		 * Displays a form to handle adding/removing skills
		 */

		function displayModifySkills()
		{
			$v = new Volunteer();
			$this->engine->assign('skills', $v->getSkillList());
			$this->engine->display('volunteer/modify_skills.tpl');
		}

		/**
		 * Displays a form to approve site managers (later credential approval should be added)
		 */

		function displayApprovalForm($vols, $mgrs)
		{
			$this->engine->assign('managers', $mgrs);
			$this->engine->assign('volunteers', $vols);
			$this->engine->display('volunteer/approve.tpl');
		}

	function showLogTime($p_uuid, $pos_id) {
		if(!empty($p_uuid) && !empty($pos_id)) {
			$v = new Volunteer($p_uuid);
			$p = new Position($pos_id);

			$this->engine->assign('p_uuid', $p_uuid);
			$this->engine->assign('pos_id', $pos_id);
			$this->engine->assign('info', $v->info);
			$this->engine->assign('pos_title', $p->title);
			$this->engine->assign('proj_name', $p->proj_name);
			$this->engine->assign('nowDate', date('Y/m/d'));
			$this->engine->assign('startTime', date('g:00 a'));
			$this->engine->assign('nowTime', date('g:i a'));

			$this->engine->display('volunteer/log_time.tpl');
		} else {
			echo "Invalid user or position.";
		}
	}

	function displayReviewHours($proj_id) {
		if(!empty($proj_id)) {
			$this->engine->assign('proj_id', $proj_id);
			$this->engine->display('volunteer/reviewListHours.tpl');
		}
	}

	function displaySelectReviewHours() {
		$this->engine->display('volunteer/showListHours.tpl');
	}
}


