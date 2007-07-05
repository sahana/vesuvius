<?php

/**
* Volunteer view
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
 * VolunteerView.php - define the VolunteerView class.
 *
 * The VolunteerView class handles any view functionality with regards to
 * volunteers. It is a subclass of the View class, so it inherits the reference
 * to the engine object for use of PHP templates.
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

			$org_info = $dao->getOrganizationInfo($info['affiliation']);
			$this->engine->assign('affiliation', $org_info['name']);

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
	 * @param $volunteers		- an array of volunteers to display (result from DAO::getVolunteers())
	 * @param $proj_id			- (optional) if using this volunteer list to assign or remove volunteers from a project, set this to the project ID
	 * @param $showRemove		- (optional, default false) true to show a link to remove the volunteer from a project (only applies to a call to this method from ProjectView::displayProject())
	 * @param $showAvailability - (optional, default false) true to show volunteer's availability
	 * @param $showIDs 			- (optional, default false) true to show volunteer's identification numbers
	 * @param $showSkills	 	- (optional, default false) true to show a drop-down list of all skills
	 * @param $showAssignButton - (optional, default false) true to show a button to assign the volunteer to a project (only applies to a call to this method from ProjectView::assignVol())
	 * @param $search_params		- (optional, default empty array) list of optional parameters that apply to using this volunteer list as a search result list
	 * @return void
	 */

	function listVolunteers($volunteers, $proj_id=null, $showRemove=false, $showAvailability=false, $showIDs=false, $showSkills=false, $showAssignButton=false, $search_params = array())
	{
		global $dao;

		$ac = new AccessController();

		// if we're displaying images here, get the IDs
		if(VM_LIST_PICTURES)
			foreach($volunteers as $p_uuid => $vol)
				if($img_uuid = $dao->getPictureID($p_uuid))
					$volunteers[$p_uuid]['pictureID'] = $img_uuid;

		//a few booleans to tell what to display
		$this->engine->assign('showRemove', $showRemove);
		$this->engine->assign('showAvailability', $showAvailability);
		$this->engine->assign('showIDs', $showIDs);
		$this->engine->assign('showSkills',$showSkills);
		$this->engine->assign('showAssignButton', $showAssignButton);
		$this->engine->assign('listPictures', VM_LIST_PICTURES);

		$this->engine->assign('searching', $search_params['searching']);
		$this->engine->assign('just_assigned_vol', $search_params['just_assigned_vol']);
		$this->engine->assign('advanced', $search_params['advanced']);

		$this->engine->assign('volunteers', $volunteers);
		$this->engine->assign('proj_id', $proj_id);
		if(!is_null($proj_id) && !$showAssignButton)
		{
			$this->engine->assign('showTask', true);
			$this->engine->assign('showEditTask', true);
		}

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

		if($v == null)
			$this->engine->assign('select_skills_tree', $dao->getSelectSkillsTree());
		else
			$this->engine->assign('select_skills_tree', $dao->getSelectSkillsTree($v->p_uuid));

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

				$messages[$key]['from'] = $dao->getPersonName($value['from_id']);

    			$list = $dao->getToList($messages[$key]['message_id']);
    			end($list);
    			$last_key = key($list);

    			$to_list = "";
    			foreach($list as $p_uuid => $name)
    			{
    				$to_list .= $name;
    				if($p_uuid != $last_key)
    					$to_list .= ', ';
    			}

    			if(strlen($to_list) > 34)
    				$to_list = substr($to_list, 0, 30) . "...";

    			$messages[$key]['to'] = $to_list;
	   		}
	   		$this->engine->assign('messages', $messages);
	   		$this->engine->assign('box', $box!='outbox');
	   		$this->engine->assign('box_name', ($box!='outbox')?'inbox':$box);
	   		$this->engine->display('message/mailbox.tpl');
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
	    	$all_vols = $dao->getVolunteers();

	    	$to_list = array();
	    	foreach($all_vols as $p_uuid => $vol)
	    	{
	    		$to_list[$p_uuid] = $vol['full_name'];
	    	}

	    	$this->engine->assign('to_list', $to_list);
	    	$this->engine->assign('to', $to);
	    	$this->engine->display('message/send_message.tpl');
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
	     * @param $results 				- 	an array of result information, returned by the
	     * 									DAO::getVolSearchResults() function
	     * @param $assigning			- 	true if we are searching to assign these volunteers
	     * @param $proj_id				- 	the project ID to be assigning to if $assigning is true
	     * @param $advanced				- 	true if we are displaying search results from an advanced search
	     * @param $just_assigned_vol	- 	true if $assigning is true and we just assigned a volunteer (nice to know if no search results are found to not display an error)
	     */

	    function displaySearchResults($results, $assigning=false, $proj_id=null, $advanced=false, $just_assigned_vol=false)
	    {
			//function listVolunteers($volunteers, $proj_id=null, $showRemove=false, $showAvailability=false, $showIDs=false, $showSkills=false, $showAssignButton=false, $search_params = array())
	    	$this->listVolunteers($results, $proj_id, false, true, false, true, $assigning, array('advanced' => $advanced, 'just_assigned_vol' => $just_assigned_vol, 'searching' => true));
	    }

}

?>
