<?php

/**
* Data Access Object
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
 * The DAO class is designed to handle the retrieval and manipulation
 * of information from the database.
 */

global $global;
require_once($global['approot'].'inc/lib_paging.inc');

 class DAO
 {
 	private $db;	//a reference to Sahana's database object

	/**
	 * Constructor that stores Sahana's object object
	 *
	 * @access public
	 * @param $db 	- reference to sahana's database
	 * @return void
	 */

 	function DAO(&$db)
 	{
 		$this->db = &$db;
 		$this->execute("set names 'utf8'");
 	}

	/**
	 * Performs queries to Sahana's database
	 *
	 * @access public
	 * @param $query 	- the query string
	 * @return an ADODB query result object
	 */

 	function execute($query)
 	{
 		//optionally show the query if desired
 		if(debug_show_queries)
 		{
 			global $query_count;
 			echo (++$query_count). " $query<br />\n";
 		}
 		return $this->db->Execute($query);
 	}


	/**
	 * Returns information about a specific volunteer
	 *
	 * @param $id 		- the volunteer's p_uuid
	 * @return an associative array, with the following structure:
	 * Array
	 * (
	 * 		'full_name' 		=> volunteer's full name,
	 * 		'ids' 			=> an array of IDs for the volunteers where each key
	 * 							is an ID type ('nic', 'dln', etc.) and each value
	 * 							is the corresponding serial number
	 * 		'locations' 	=> 	an array specifying the volunteer's location, where
	 * 							each key is numerically-based (starting from 0), and each
	 * 							value is a 'loc_uuid' from the 'location' table; the
	 * 							locations are specified from most specific to most
	 * 							general (e.g., New York City, New York, USA)
	 * 		'proj_id'		=> an array of project IDs that the volunteer is currently assigned to
	 * 		'gender'		=> the volunteer's gender
	 * 		'dob'			=> the volunteer's date of birth
	 * 		'date_start'	=> the day that the volunteer can begin working
	 * 		'date_end'		=> the last day that the volunteer can work
	 * 		'hour_start'	=> the time of day that the volunteer can begin working
	 * 		'hour_end'		=> the time of day that the volunteer must stop working
	 * 		'contact'		=> an array of contact information for the volunteer, where each
	 * 							key is an 'opt_contact_type' from the 'field_options' table
	 * 							and each value is the corresponding contact information
	 * 		'occupation'	=> the volunteer's occupation
	 * 		'affiliation'	=> the organization that the volunteer is affiliated with
	 * 		'status'		=> either 'Assigned' or 'Unassigned', whether the volunteer has
	 * 							been assigned to a project
	 * 		'messages'		=> the number of unread messages for this volunteer
	 * )
	 */

 	function getVol($id) //
 	{
 		$info = array();

 		// full name

 		$result = $this->execute("select p_uuid, full_name from person_uuid where p_uuid = '$id'");
 		if($result->EOF)
 			return false;
 		$info["full_name"] = $result->fields["full_name"];

 		// IDs and ID types

 		$result = $this->execute("select opt_id_type, serial from identity_to_person where p_uuid = '" . $id. "'");
 		$info["ids"]= array();
 		while(!$result->EOF)
 		{
 			$info["ids"][$result->fields["opt_id_type"]] = $result->fields["serial"];
 			$result->moveNext();
 		}

		// locations

 		$result = $this->execute("select location_id, location.name from location_details join location on (location.loc_uuid = location_details.location_id) where poc_uuid = '" . $id . "'");
 		$locations = array();
 		$location_names = array();
 		if (!$result->EOF) {
	 		$lastId = $result->fields["location_id"];
	 		do {
	 			$locations[]= $lastId;
	 			$location_names[] = $result->fields['name'];
	 			$result= $this->execute("select loc_uuid, location.name from location where loc_uuid = (select parent_id from location where loc_uuid = '$lastId')");
	 			$lastId = $result->fields["loc_uuid"];
	 		}
	 		while($lastId!=NULL && $lastId!='NULL' && !$result->EOF);
 		}

 		$info['locations'] = $locations;
 		$info['location_names'] = $location_names;

 		// get project[s] to which they are assigned
 		// a volunteer may be assigned to more than one project

		$info['proj_id'] = $info['pos_id'] = array();
		$result = $this->execute("select pos_id, proj_id from vm_vol_assignment_active where p_uuid = '$id'");

		while(!$result->EOF) {
			$info['pos_id' ][] = $result->fields['pos_id'];
			$info['proj_id'][] = $result->fields['proj_id'];
			$result->MoveNext();
		}


		//get the gender,  birth date, and occupation

		$result = $this->execute("select opt_gender, birth_date, occupation from person_details where p_uuid = '$id'");
		$info['gender'] = $result->fields['opt_gender'];
		$info['dob'] = $result->fields['birth_date'];
		$info['occupation'] = $result->fields['occupation'];
		$info['status'] = $this->volIsAssignedToProject($id)?'Assigned':'Unassigned';

		//get work times and organization affiliation

		$result= $this->execute(" select date_avail_start, date_avail_end, hrs_avail_start, hrs_avail_end, org_id from vm_vol_active where p_uuid = '$id' ");
		$info['date_start'] = $result->fields['date_avail_start'];
		$info['date_end'] = $result->fields['date_avail_end'];
		$info['hour_start'] = $result->fields['hrs_avail_start'];
		$info['hour_end'] = $result->fields['hrs_avail_end'];

		$org_id = $result->fields['org_id'];
		$info['affiliation'] = $org_id;

		$org_info = $this->getOrganizationInfo($org_id);
		$info['affiliation_name'] = (empty($org_info)) ? '' : $org_info['name'];

		//all the contact information

		$result = $this->execute("select opt_contact_type, contact_value from contact " .
				"where pgoc_uuid = '$id'");

		$contacts=array();
		while(!$result->EOF)
		{
			$contacts[$result->fields['opt_contact_type']] = $result->fields['contact_value'];
			$result->moveNext();
		}
		$info['contact'] = $contacts;

		//number of unread messages
		$info['messages'] = $this->getUnreadMessages($id);


		//get special needs of volunteers, if any
		$result = $this->execute("SELECT special_needs FROM vm_vol_details WHERE p_uuid='$id'");
		$info['special_needs']=$result->fields['special_needs'];

		//get skills
		$info['skills'] = array();
		$result = $this->execute("SELECT opt_skill_code, option_description FROM vm_vol_skills JOIN field_options ON (opt_skill_code = option_code AND field_name = 'opt_skill_type') WHERE p_uuid = '$id'");
		while(!$result->EOF) {
			$info['skills'][$result->fields['opt_skill_code']] = $result->fields['option_description'];
			$result->moveNext();
		}

 		return $info;
 	}

	/**
	 * Gets the ID types available for anyone in the Sahana system
	 *
	 * @access public
	 * @return $id_types 	- an associative array, where each key is the shorthand
	 * 							identifier for the ID type, and each value is the
	 * 							corresponding description of the ID (e.g., 'dln' =>
	 * 							'Driver's License Number')
	 */

 	function getIdTypes() //
 	{
 		// get the ID codes and names from the 'field_options' table
 		$result = $this->execute("select option_code, option_description from field_options where field_name = 'opt_id_type'");
 		$id_types = array();
 		while(!$result->EOF)
 		{
 			$id_types[$result->fields['option_code']]= $result->fields['option_description'];
 			$result->moveNext();
 		}
		return $id_types;
 	}

	/**
	 * Function removes, by default, the numerically indexed keys of an array, or optionally the associative ones.
	 * this is because the database object returns arrays with both.
	 *
	 * @param $a 		- the array to remove keys from
	 * @param $type 	- the type of keys to remove; either MYSQL_NUM or MYSQL_ASSOC
	 */

	function remove_keys(&$a, $type=MYSQL_NUM) //
	{
 		$count = count($a);
 		if($type == MYSQL_NUM){
 			for($i = 0; $i<$count/2; $i++){
 				unset($a[$i]);
 			}
 		}
 		else
 		{
	 		$result = array();
	 		for($i=0; $i<count($a)/2; $i++)
	 			$result[$i] = $a[$i];
	 		$a = $result;
 		}
 	}

	/**
	 * Retrieves general location information about a specific location.
	 *
	 * @access public
	 * @param $loc_uuid - the location ID to look up
	 * @return an associative array, with the following structure:
	 * Array
	 * (
	 * 		'opt_location_type'	=> the location level,
	 * 		'name'				=> the location's name,
	 * 		'iso_code'			=> the location's ISO code,
	 * 		'description'		=> a brief description about the location
	 * )
	 */

	/*
	 *
	*/
 	function getLocation($loc_uuid) //
 	{
 		// get the information from the 'location' table
 		$result = $this->execute("select opt_location_type, name, iso_code, description from location where loc_uuid = '$loc_uuid'");
		$this->remove_keys($result->fields);
 		return $result->fields;
 	}

 	/**
 	 * Retrieves the names and location IDs of a location and all parent locations
 	 *
 	 * @param $child	- the Id of the location to look up
 	 * @return an array, where each key is each location ID and each value is the name of the location; results
 	 * are sorted from most specific to most general
 	 */

 	function getParentLocations($child, &$locs=array())
 	{
		$result = $this->execute("SELECT name, parent_id FROM location WHERE loc_uuid = '$child'");

		if(!$result->EOF)
			$locs[$child] = $result->fields['name'];

		if($result->fields['parent_id'] == null)
			return $locs;
		else
			return $this->getParentLocations($result->fields['parent_id'], $locs);
 	}


	/**
	 * Retrieves all contact types and their descriptions.
	 *
	 * @access public
	 * @return an associative array, where each key is the shorthand name for the contact
	 * 			and each value is the corresponding description for that contact type
	 * 			(e.g., 'emai' => 'Email Address')
	 */

	function getContactTypes() //
	{
		$result = $this->execute("select option_code, option_description from field_options where field_name = 'opt_contact_type'");
		$contact_types = array();
		while(!$result->EOF)
		{
			$contact_types[$result->fields['option_code']]= $result->fields['option_description'];
			$result->moveNext();
		}
		return $contact_types;
	}

	/**
	 * Gets the number of hours worked by the given volunteer for the given project.
	 *
	 * @param $p_uuid	volunteer's id
	 * @param $proj_id	project id
	 * @return number of hours
	 */

	function getVolHoursByProject($p_uuid, $proj_id) {
		$result = $this->execute("SELECT SUM(HOUR(shift_end - shift_start)) AS hours FROM vm_hours WHERE p_uuid = '$p_uuid' AND proj_id = '$proj_id'");
		$hours = $result->fields['hours'];
		if($hours == null) {
			return 0;
		} else {
			return $hours;
		}
	}

	/**
	 * Retrieves the hours and payrate of a volunteer for each position he is assigned in each project/
	 * Specifying both $proj_id and $org_id is ok
	 *
	 * @access 	public
	 * @param 	$p_uuid		- the p_uuid of the volunteer
	 * @param	$proj_id	- (optional) specify this to only return results from this project
	 * @return an array with the following structure:
	 *
	 * 	Array
	 * 	(
	 *		proj_id =>
	 *			Array
	 *			(
	 *				'project_name'	=> the name of the project
	 *				 pos_id	=>
	 *					Array
	 *					(
	 *						'title'		=> the position title
	 *						'hours'		=> the total number of hours worked
	 *						'payrate'	=> the volunteer's hourly payrate
	 *						'status'	=> the volunteer's status for this position
	 *					)
	 *			)
	 * 	)
	 */

	function getVolHoursAndRate($p_uuid, $proj_id=null)
	{
		//get all of the volunteer's positions' information

		$q =	"SELECT  proj_id, project_name, status, pos_id, title, payrate
				 FROM    vm_vol_assignment
				 WHERE   p_uuid = '$p_uuid' ";


		if(!is_null($proj_id))
			$q .= " AND proj_id = '$proj_id' ";

		$r = $this->execute($q);

		$info = array();

		while(!$r->EOF)
		{
			if(!isset($info[$r->fields['proj_id']]))
				$info[$r->fields['proj_id']] = array('project_name' => $r->fields['project_name']);

			$info[$r->fields['proj_id']][$r->fields['pos_id']] = array
			(
				'title'		=> $r->fields['title'],
				'payrate'	=> $r->fields['payrate'],
				'status'	=> $r->fields['status']
			);

			$r->MoveNext();
		}


		//get the volunteer's hours worked for each project position

		foreach($info as $proj_id => $positions)
		{
			foreach($positions as $pos_id => $pos_info)
			{
				if($pos_id != 'project_name')
				{
					$t = $this->execute(	"SELECT	SUM(HOUR(TIMEDIFF(shift_end, shift_start))) hours, SUM(MINUTE(TIMEDIFF(shift_end, shift_start))) minutes, SUM(SECOND(TIMEDIFF(shift_end, shift_start))) seconds
											 FROM	vm_hours
											 WHERE	p_uuid = '$p_uuid'
											 AND	pos_id = '$pos_id'");

					$hours = $t->fields['hours'];
					$minutes = $t->fields['minutes'];
					$seconds = $t->fields['seconds'];

					$info[$proj_id][$pos_id]['hours'] = $hours + $minutes / 60 + $seconds / 3600;
				}
			}
		}

		return $info;
	}

	/**
	 * Retrieve a list of volunteers and some related information
	 *
	 * @param $proj_id (optional) - give a value to return volunteers only from this project
	 * @param $assigned (optional, default VM_SHOW_ALL_VOLUNTEERS) -
	 * 						VM_SHOW_ALL_VOLUNTEERS_ASSIGNED to return only assigned volunteers
	 * 						VM_SHOW_ALL_VOLUNTEERS_UNASSIGNED to return only unassigned volunteers
	 * 						VM_SHOW_ALL_VOLUNTEERS to return all volunteers
	 *
	 * @return An array of Volunteer Objects. This function uses paging.
	 */

	function getVolunteers($proj_id=null, $assigned=VM_SHOW_ALL_VOLUNTEERS) {
		if(is_null($proj_id)) {
			if($assigned == VM_SHOW_ALL_VOLUNTEERS_ASSIGNED)
				$whereClause = " WHERE vm_vol_active.p_uuid IN (SELECT DISTINCT p_uuid FROM vm_vol_assignment_active)";
			else if($assigned == VM_SHOW_ALL_VOLUNTEERS_UNASSIGNED)
				$whereClause = " WHERE vm_vol_active.p_uuid NOT IN (SELECT DISTINCT p_uuid FROM vm_vol_assignment_active)";
			else
				$whereClause = "  ";
		} else {
			$whereClause = " WHERE vm_vol_active.p_uuid IN (SELECT p_uuid FROM vm_vol_assignment_active WHERE proj_id='$proj_id')";
		}

		$q = 	"SELECT 	vm_vol_active.p_uuid
				 FROM 		vm_vol_active " . $whereClause;

		//get volunteer ids based on paging
		$result = $this->getCurrentPage($q);

		// put all information into an array for returning
		$volunteers = array();
		while(!$result->EOF) {
			$volunteers[] = new Volunteer($result->fields['p_uuid']);
			$result->moveNext();
		}
		return $volunteers;
	}

	/**
	 * Retrieve a list of volunteers with information pertinent to reporting. All volunteers
	 * (regardless of status) are returned.
	 *
	 * @param $proj_id (optional) - specify this to return volunteers only from this project
	 * @param $org_id (optional) - specify this to return volunteers only from this organization
	 * @param $vols (optionsla) - an array of p_uuids of volunteers to report on; specifying this will make the proj_id and org_id parameters be ignored
	 *
	 * @return an array, where each key is a volunteer's p_uuid and each value is the following array of information:
	 *	Array
     * (
     * 		'full_name'		=> the volunteer's full name
     * 		'status'		=> the volunteer's overall status
     *		'locations'		=> an array of the volunteer's location and its parents
     *		'affiliation'	=> the organization that the volunteer is affiliated with
     *		'pay_info'		=> the volunteer's pay information
     * )
	 */

	function getVolunteersForReport($proj_id=null, $org_id=null, $vols=array())
	{
		$whereSaid = false;
		$whereClause = "WHERE 1";

		if(!empty($vols))
		{
			$id_list = "(";
			foreach($vols as $index => $p_uuid)
			{
				$id_list .= "'$p_uuid'";
				if($index < count($vols) - 1)
					$id_list .= ", ";
			}
			$id_list .= ")";
			$whereClause .= " AND vm_vol_details.p_uuid IN $id_list ";
		}
		else
		{
			if(!is_null($proj_id))
				$whereClause .= " AND vm_vol_details.p_uuid IN (SELECT p_uuid FROM vm_vol_assignment WHERE proj_id='$proj_id')";

			if(!is_null($org_id))
				$whereClause .= " AND org_id = '$org_id' ";
		}

		$q = 	"SELECT	DISTINCT person_uuid.p_uuid, person_uuid.full_name, vm_vol_details.status, location_id, org_main.name org_name
				 FROM 		vm_vol_details LEFT JOIN person_uuid ON (person_uuid.p_uuid=vm_vol_details.p_uuid)
				 			LEFT JOIN vm_vol_assignment ON (vm_vol_assignment.p_uuid=vm_vol_details.p_uuid)
							LEFT JOIN location_details ON (location_details.poc_uuid = person_uuid.p_uuid)
							LEFT JOIN org_main ON (vm_vol_details.org_id = org_main.o_uuid) "
				. $whereClause;

		$result = $this->getCurrentPage($q);

		// put all information into an array for returning

		$volunteers = array();
		while(!$result->EOF)
		{
			if(empty($result->fields['location_id']))
				$locations = array();
			else
				$locations = $this->getParentLocations($result->fields['location_id']);

			$volunteers[$result->fields['p_uuid']] = array
			(
				'full_name'		=> $result->fields['full_name'],
				'locations'		=> $locations,
				'affiliation'	=> ($result->fields['org_name']==null)?'':$result->fields['org_name'],
				'pay_info'		=> $this->getVolHoursAndRate($result->fields['p_uuid'], $proj_id),
				'status'		=> $result->fields['status']
			);

			$result->moveNext();
		}
		return $volunteers;
	}

	/**
	 * Either creates volunteer information in the database if a volunteer is being added, or updates
	 * volunteer information if a volunteer already exists.
	 *
	 * @param $v - a Volunteer object. If it's p_uuid is not set, new volunteer information is
	 * 				inserted into the database. Otherwise, the information of the volunteer
	 * 				whose p_uuid is $v->p_uuid is simply updated.
	 * @param $shn_user	- (optional, default false) set to true if registering a current Sahana user as a volunteer
	 * @return void
	 */

 	function saveVol(&$v, $shn_user=false)
 	{
	 	if(isset($v->p_uuid) && !$shn_user)
	 	{
	 		// this Volunteer already has a p_uuid, so simply update its information

	 		//update full name
			$this->execute("UPDATE person_uuid SET full_name='{$v->info['full_name']}' WHERE p_uuid = '{$v->p_uuid}'");

			//delete old ID information and insert the new
			$this->execute("DELETE FROM identity_to_person WHERE p_uuid = '{$v->p_uuid}'");
			foreach($v->info['ids'] as $id_type => $serial)
			{
				if(trim($serial) != '')
					$this->execute("INSERT INTO identity_to_person (opt_id_type,serial, p_uuid) values ('$id_type','$serial'  ,'{$v->p_uuid}')");
				else
					unset($v->info['ids'][$id_type]);
			}

			//update phonetic sound matching
			$this->execute("DELETE FROM phonetic_word WHERE pgl_uuid='{$v->p_uuid}'");
			$names = preg_split("/\s+/", $v->info['full_name']);

            foreach($names as $single_name)
            {
                $this->execute("INSERT INTO phonetic_word VALUES('" . soundex($single_name) . "', '" . metaphone($single_name) . "', '{$v->p_uuid}')");

            }

			//update gender, date of birth, and occupation information
			$result= $this->execute("Select p_uuid from person_details where  p_uuid ='{$v->p_uuid}'");
			if ($result->EOF)
				$this->execute("INSERT INTO person_details (p_uuid,opt_gender,birth_date,occupation) values ('".$v->p_uuid."','".$v->info['gender']."','".$v->info['dob']."','".$v->info['occupation']."')");
			else
				$this->execute("UPDATE person_details SET opt_gender = '{$v->info['gender']}', birth_date = '{$v->info['dob']}', occupation = '{$v->info['occupation']}' WHERE p_uuid ='{$v->p_uuid}'");

	 		//update the location information
	 		$specific_loc = $v->info['locations'][0];
	 		if($specific_loc == -1 || $specific_loc == null || $specific_loc === '0')
	 		{
	 			$this->execute("DELETE FROM location_details WHERE poc_uuid='{$v->p_uuid}'");
	 		}
	 		else
	 		{
	 			$result = $this->execute("SELECT location_id FROM location_details WHERE poc_uuid='{$v->p_uuid}'");

	 			if($result->EOF)
	 				$this->execute("INSERT INTO location_details (poc_uuid, location_id) VALUES ('{$v->p_uuid}', '$specific_loc')");
	 			else
	 				$this->execute("UPDATE location_details SET location_id='$specific_loc' WHERE poc_uuid='{$v->p_uuid}'");
	 		}


			//Update a volunteers availability and organization affiliation along with hours of availability and special needs
			$this->execute("update vm_vol_details SET date_avail_start= '{$v->info['date_start']}',date_avail_end='{$v->info['date_end']}' ,hrs_avail_start= '{$v->info['hour_start']}',hrs_avail_end= '{$v->info['hour_end']}', org_id='{$v->info['affiliation']}', special_needs='{$v->info['special_needs']}' WHERE p_uuid='".$v->p_uuid."'");

	 		//delete the old contacts and replace with new ones if they are not blank
	 		$this->execute("DELETE FROM contact WHERE pgoc_uuid = '{$v->p_uuid}'");
			foreach($v->info['contact'] as $key => $value)
			{
				if(trim($value != ''))
					$this->execute("insert into contact (pgoc_uuid, opt_contact_type, contact_value) values ('{$v->p_uuid}', '$key', '$value')");
			}

			//get rid of any pre-existing skills and replace them with the new

	 		$this->execute("DELETE FROM vm_vol_skills WHERE p_uuid = '{$v->p_uuid}'");
	 		foreach($v->info['skills'] as $skill)
			{
				$this->execute("INSERT INTO vm_vol_skills (p_uuid, opt_skill_code) VALUES('{$v->p_uuid}', '$skill')");
			}

	 	}
 		else
 		{
 			//create a new p_uuid for the volunteer and insert its new information into the database

 			//generate a new p_uuid only if $shn_user is false
 			global $global;

 			if(!$shn_user)
 			{
				require_once($global['approot']."/inc/lib_uuid.inc");
				$v->p_uuid = shn_create_uuid();
 			}

			//create a Sahana account if necessary

			if(isset($v->info['account_info']))
			{
				include_once($global['approot'].'inc/lib_security/lib_auth.inc');
				include_once($global['approot'].'inc/lib_security/constants.inc');
				$acct = $v->info['account_info'];
				//create an account and give the user 'Anonymous User' privileges
				shn_auth_add_user($acct['account_name'], $acct['user_name'], $acct['pass'], ANONYMOUS, $v->p_uuid);
			}
			//add phonetic sound matching
			$names = preg_split("/\s+/", $v->info['full_name']);

            foreach($names as $single_name)
            {
                $this->execute("INSERT INTO phonetic_word VALUES('" . soundex($single_name) . "', '" . metaphone($single_name) . "', '{$v->p_uuid}')");

            }

			//insert the volunteer's full name
			$result = $this->db->execute("insert into person_uuid (p_uuid, full_name) values ('".$v->p_uuid."', '".$v->info['full_name']."')");

			//insert the volunteer's availibility and organization affiliation along with hours of availability and special needs
			$this->execute("insert into vm_vol_details (p_uuid,date_avail_start,date_avail_end,hrs_avail_start,hrs_avail_end, org_id, special_needs) values ('{$v->p_uuid}', '{$v->info['date_start']}', '{$v->info['date_end']}', '{$v->info['hour_start']}', '{$v->info['hour_end']}', '{$v->info['affiliation']}', '{$v->info['special_needs']}')");

			//insert new ID information
			if (!empty($v->info['ids'])) {
			$id_type= array_pop(array_keys($v->info["ids"]));
			$serial=$v->info['ids'][$id_type];
			if($serial != '')
				$this->execute("INSERT INTO identity_to_person (opt_id_type,serial, p_uuid) values ('$id_type','$serial'  ,'{$v->p_uuid}')");
			else
				unset($v->info['ids'][$id_type]);
			}
			//insert gender, birth date, and occupation information
			$this->execute("INSERT INTO person_details (p_uuid,opt_gender,birth_date,occupation) values ('".$v->p_uuid."','".$v->info['gender']."','".$v->info['dob']."','".$v->info['occupation']."')");

			//insert contact types
			if(!empty($v->info['contact']))
			foreach($v->info['contact'] as $key => $value)
			{
				if(trim($value != ''))
					$this->execute("insert into contact (pgoc_uuid, opt_contact_type, contact_value) values ('{$v->p_uuid}', '$key', '$value')");
			}

			//insert skill information
			if(!empty($v->info['skills']))
			foreach($v->info['skills'] as $skill)
			{
				$this->execute("INSERT INTO vm_vol_skills (p_uuid, opt_skill_code) VALUES('{$v->p_uuid}', '$skill')");
			}

			//insert the location information
			$specific_loc = $v->info['locations'][0];
	 		if($specific_loc != null && $specific_loc != -1)
	 			$this->execute("INSERT INTO location_details (poc_uuid, location_id) VALUES ('{$v->p_uuid}', '$specific_loc')");
 		}
 	}

 	 /*
 	  * Return all of the position of a specific project of a user using
 	  * @param pos_id
 	  * @param proj_id
 	  * @param p_uuid  - to select position that are assigned to a volunteer.
 	  */
	function listPositions($proj_id=null, $p_uuid=null) {
		if($proj_id == null && $p_uuid == null)
			$whereClause = '';
		else if($proj_id == null)
			$whereClause = "WHERE p_uuid = '$p_uuid' AND status='active'";
		else if($p_uuid == null)
			$whereClause = "WHERE proj_id = '$proj_id'";
		else
			$whereClause = "WHERE proj_id = '$proj_id' AND p_uuid = '$p_uuid'";

		$result = $this->execute("SELECT pos_id, proj_id,project_name, ptype_id, slots, title, description, ptype_title, ptype_description, skill_code FROM vm_vol_assignment $whereClause ORDER BY proj_id ");
		$positions = array();
		while(!$result->EOF) {

			$this->remove_keys($result->fields);
			$positions[] = $result->fields;
			$result->moveNext();
		}

		$result = $this->execute("select pos_id, count(*) numVolunteers FROM vm_vol_assignment_active group by pos_id");

		return $positions;
	}
 /*
  * Saves changes to a position
  * @ param $p-  reference of a Positisn object. If the position does not have an ID, a new position
	 *				is inserted into the database, otherwise existing position information is updated.
	 * @return void
  */
	function savePosition(&$p) {
		global $global;
		if(!isset($p->pos_id))  {
			//generate a new id
			require_once($global['approot']."/inc/lib_uuid.inc");
			$p->pos_id = shn_create_uuid();
			//create a new position
			$this->execute("INSERT INTO vm_position (pos_id, proj_id, ptype_id, title, slots, description,payrate)
							values ('{$p->pos_id}', '{$p->proj_id}', '{$p->ptype_id}', '{$p->title}', '{$p->numSlots}', '{$p->description}', '{$p->payrate}')");
		} else {
	 	//update existing position information
 			$this->execute("UPDATE vm_position SET proj_id = '{$p->proj_id}', ptype_id = '{$p->ptype_id}', title = '{$p->title}', slots = '{$p->numSlots}', description = '{$p->description}', payrate = '{$p->payrate}'
 					where pos_id = '{$p->pos_id}'");
		}
	}

    /*
     *  Removes all active positions and sets the position in the database
     * @param $pos_id  - However does not remove from the database but sets as inactive position
     */
	function removePosition($pos_id) {
		$this->execute("update vm_position set status = 'retired' where pos_id = '$pos_id'");
	}

	//returns the number of volunteers involved in the given project
	function getVolunteersInProject($proj_id) {
		$result = $this->execute("SELECT COUNT(*) as num FROM vm_vol_assignment_active where proj_id = '$proj_id'");
		if($result->EOF) {
			return 0;
		} else {
			return $result->fields['num'];
		}
	}

    /*
     *  Select a project
     * @param $proj_id - so locate all position within a given a project
     */
	function getPostionsByProject($proj_id) {
	//build the query

 		$query = "SELECT skill_code,pos_id, title, description, payrate FROM vm_position JOIN vm_proj_position USING (pos_id) WHERE(proj_id = '$proj_id')";

		//store the info

		$result = $this->execute($query);
		$position = array();
		while(!$result->EOF)
		{
			$position[$result->fields['pos_id']] = array('title' => $result->fields['title'],'skill_code' => $result->fields['skill_code'], 'payrate' => $result->fields['payrate'], 'description' => $result->fields['description'],'slots' => $result->fields['slots']);
			$result->moveNext();
		}
		return $position;
	}

	/*
	 *  Select the type of position
	 * @param $pos_id - and returns  the type of position of a project
	 */
	function getPositionType($pos_id) {

		$query = "SELECT skill_code, title, description FROM vm_positiontype WHERE (pos_id='$pos_id')";

		//store the info

		$result = $this->execute($query);
		$this->remove_keys($result->fields);
		return $result->fields;
	}

	/*
	 * List the type of positions and returns all the positions
	 * @ param $ptypes
	 */
	function listPositionTypes() {
		$result = $this->execute("select ptype_id, title, description, skill_code from vm_positiontype");
		$ptypes = array();
		while(!$result->EOF) {
			$this->remove_keys($result->fields);
			$ptypes[] = $result->fields;
			$result->moveNext();
		}
		return $ptypes;
	}

	/*
	 *  getPosition select a position
	 * @param $pos_id - with a array of information with the $pos_id and return that information
	 * @param $p
	 */
	function getPosition($pos_id) {
		$query = "SELECT proj_id, ptype_id, slots, title, description, project_name, ptype_title, ptype_description, skill_code, payrate FROM vm_position_full WHERE (pos_id='$pos_id')";
		$result = $this->execute($query);
		$this->remove_keys($result->fields);
		$p = $result->fields;

		$result = $this->execute("select count(*) numVolunteers from vm_vol_assignment_active where pos_id = '$pos_id'");
		$p['numVolunteers'] = $result->fields['numVolunteers'];

		return $p;
	}

	/**
	 * Saves changes made to a project to the database
	 *
	 * @access public
	 * @param @p - reference of a Project object. If the project does not have an ID, a new project
	 *				is inserted into the database, otherwise existing project information is updated.
	 * @return void
	 */

 	function saveProject(&$p)
 	{
 		if(!isset($p->proj_id))
 		{
 			//create a new project

 			$specific_loc= $p->info['locations'][0];
 			if($specific_loc==-1 ||$specific_loc==="0" || $specific_loc===null)
 				$specific_loc= "null";
 			 else
 			 	$specific_loc="'".$specific_loc."'";
 			$this->execute("INSERT INTO vm_projects (name, description,location_id,start_date,end_date) values ('{$p->info['name']}', '{$p->info['description']}', $specific_loc, '{$p->info['start_date']}', '{$p->info['end_date']}')");

			$result = $this->execute("SELECT LAST_INSERT_ID()");
			$proj_id = $result->fields[0];

 			//create a site manager position using the site manager position type

 			$pos = new Position();
 			$pos->title = 'Site Manager';
			$pos->proj_id = $proj_id;
			$pos->ptype_id = 'smgr';
			$pos->description = 'Manage the entire project';
			$pos->numSlots = 1;
			$pos->payrate = 20.00;
			$this->savePosition($pos);

			//assign the site manager to the position and refresh the project information
			//cannot simply redeclare $p because we're in the middle of a method call
			$this->assignVolunteerToPosition($p->info['mgr_id'], $pos->pos_id);
 			$p_tmp = new Project($proj_id);
 			$p->proj_id = $proj_id;
 			$p->positions = $p_tmp->positions;
 		}
 		else
 		{
 			//update existing project information

 			$specific_loc= $p->info['locations'][0];
 			if($specific_loc==-1 ||$specific_loc==="0" || $specific_loc===null)
 				$specific_loc= "null";
 			 else
 			 	$specific_loc="'".$specific_loc."'";

 			$result = $this->execute("UPDATE vm_projects SET name = '{$p->info['name']}', description = '{$p->info['description']}', location_id = $specific_loc, start_date = '{$p->info['start_date']}', end_date = '{$p->info['end_date']}' WHERE proj_id = '{$p->proj_id}'");
			}
 	}

	/**
	 * Retrieve a list of project information
	 *
	 * @access public
	 * @param $p_uuid		- (optional) if specified, only return projects that this volunteer is working on (site managers are handled as well)
	 * @param $mgr			- (optional) if specified, $p_uuid is treated as site manager and only projects he is a site manager for will be returned; if $p_uuid
	 * 							is a site manager but this is false, it will also return any projects that the site manager may just be assigned to
	 * @param $simple		- (optional) if true, the return array only contains the proj_id for each key and the project name for each value
	 * @param $paged		- (optional) if true, the current place in the paging navigation as well as rows per page are taken into account when querying
	 * @return an array of project information arrays, where each key is the project ID and each value
	 * is an array with the following structure:
	 *
	 * 	Array
	 * 	(
	 * 		'name'			=> the name of the project
	 * 		'description'	=> the project's description
	 * 	)
	 */


 	function listProjects($p_uuid=null, $mgr=false, $simple=false, $paged=false)
 	{
 		//build the query

 		$query = "SELECT proj_id, name, description FROM vm_projects_active";
 		if(!is_null($p_uuid))
 		{
 			if($mgr)
 				$query .= " WHERE proj_id IN (SELECT proj_id FROM vm_vol_assignment_active WHERE p_uuid = '$p_uuid' AND ptype_id = 'smgr')";
 			else
 				$query .= " WHERE proj_id IN (SELECT proj_id FROM vm_vol_assignment_active WHERE p_uuid = '$p_uuid') OR proj_id IN (SELECT proj_id FROM vm_vol_assignment_active WHERE p_uuid = '$p_uuid' AND ptype_id = 'smgr')";
 		}

		//store the info
		if($paged) {
			$result = $this->getCurrentPage($query);
		} else {
			$result = $this->execute($query);
		}
		$projects = array();
		while(!$result->EOF)
		{
			if($simple)
				$projects[$result->fields['proj_id']] = $result->fields['name'];
			else
				$projects[$result->fields['proj_id']] = array('name' => $result->fields['name'], 'description' => $result->fields['description']);
			$result->moveNext();
		}

		return $projects;
 	}

 	/**
 	 * Retrieves information about a single project.
 	 *
 	 * @access public
 	 * @param $id - the project's ID
 	 * @return the project information in an associative array, with the following structure:
 	 * Array
 	 * (
 	 * 		'name'			=> the name of the project,
 	 * 		'location_id'	=> the 'loc_uuid' from the 'location' table of the most specific location
 	 * 							where the project takes place
 	 * 		'start_date'	=> the beginning date of the project
 	 * 		'end_date'		=> the end date of the project
 	 * 		'description'	=> a brief description of the project
 	 * )
 	 */

 	function getProject($proj_id)
 	{
		$result = $this->execute("SELECT name, location_id, start_date, end_date, description FROM vm_projects_active WHERE proj_id = '$proj_id'");
		//Get rid of numerically-based indices
		$this->remove_keys($result->fields);

		$proj = $result->fields;

		//get positions for this project
		$result = $this->execute("select pos_id this_pos_id, ptype_id, title, description, ptype_title, ptype_description, slots numSlots, payrate, (select count(*) FROM vm_vol_assignment_active WHERE pos_id = this_pos_id AND proj_id='$proj_id') numVolunteers, skill_code " .
				"from vm_position_active where proj_id = '$proj_id'");

		$proj['positions'] = array();
		while(!$result->EOF) {
			$this->remove_keys($result->fields);
			$result->fields['pos_id'] = $result->fields['this_pos_id'];
			unset($result->fields['this_pos_id']);
			$proj['positions'][$result->fields['pos_id']] = $result->fields;
			$result->moveNext();
		}

		return $proj;
 	}

 	/**
 	 * Retrieves a project's name
 	 *
 	 * @access public
 	 * @param $proj_id	- the ID of the project
 	 * @return the project's name
 	 */

 	function getProjectName($proj_id)
 	{
		$result = $this->execute("SELECT name FROM vm_projects_active WHERE proj_id = '$proj_id'");
		if(!$result->fields)
			return false;
		return $result->fields['name'];
 	}

 	/**
 	 * Retrieves whether or not the volunteer is assigned to the given project
 	 *
 	 * @param $p_uuid	- the p_uuid of the volunteer to check
 	 * @param $proj_id	- the p_uuid of the project to check
 	 * @return true if the volunteer is assigned to the given project, false if not
 	 */

 	function volIsAssignedToProject($p_uuid, $proj_id=null)
 	{
 		$query = "SELECT p_uuid FROM vm_vol_assignment_active WHERE p_uuid = '$p_uuid'";
 		if($proj_id!=null)
 			$query .= " AND proj_id = '$proj_id'";
 		$result = $this->execute($query);
 		return !$result->EOF;
 	}

	/**
	 * Removes a volunteer and all the related information relating to that specific
	 * volunteer from the database
	 *
	 * @access public
	 * @param $id	- the volunteer's p_uuid
	 * @return void
	 */

	function deleteVolunteer($id)
	{
		$this->execute("UPDATE vm_vol_details SET status = 'retired' WHERE p_uuid = '$id'");
		$this->execute("UPDATE vm_vol_assignment SET status = 'retired' WHERE p_uuid = '$id'");
	}

	/**
	 * Removes a volunteer from a project
	 *
	 * @access public
	 * @param $p_uuid	- the p_uuid of the volunteer to remove
	 * @param $proj_id	- the ID of the project to remove the volunteer from
	 * @return void
	 */

	function deleteFromProject($p_uuid, $proj_id)
	{
		$this->execute("UPDATE vm_vol_assignment SET status='retired' WHERE p_uuid = '$p_uuid' AND proj_id = '$proj_id'");

		//send the volunteer a message from the site manager notifying them of the assignment
		$result = $this->execute("SELECT name, FROM vm_projects WHERE proj_id = '$proj_id'");
		$this->sendMessage('SYS_MSG', array($p_uuid), _("You have been removed from Project").": {$result->fields['name']}. \n\n ("._("This is an automated message").")");
	}

	/**
	 * Removes a project and all related information.
	 *
	 * @access public
	 * @param $id	- the project's ID
	 * @return void
	 */

 	function deleteProject($proj_id)
 	{

 		$this->execute("UPDATE vm_projects SET status = 'completed' WHERE proj_id = '$proj_id'");
 		$this->execute("UPDATE vm_vol_assignment SET status = 'retired' WHERE proj_id = '$proj_id'");

 	}


	/**
	 * Retrieves all possible skills as a Tree object with CheckboxNodes for all
	 * Nodes other than the root node. Optionally, the skills of a particular
	 * volunteer can be pre-checked.
	 *
	 * @access public
	 * @param $p_uuid		- if specified, the skills of the volunteer  or project with this p_uuid
	 * 							are pre-checked; otherwise, all skill checkboxes remain empty.
	 * @param $vol 			- true to return a set of volunteer's skills , false to return a set of
	 * 							project's skills (this only matters if $p_uuid is set)
	 * @param $any_skills	- (optional) an array of any skill codes to pre-check
	 * @return the Tree object
	 */

	function getSelectSkillsTree($p_uuid=null, $vol=true, $any_skills=null)
	{
		//first get and store all of the volunteer's skills as an array if necessary

		if($p_uuid != null)
			$skills_array = $this->getVolSkillsArray($p_uuid);
		else if(is_array($any_skills))
			$skills_array = $any_skills;
		else
			$skills_array = array();

	    //now query for all skills and store them in a Tree structure

	    $result = $this->execute("SELECT DISTINCT option_code, option_description FROM field_options WHERE field_name = 'opt_skill_type' ORDER BY option_description");

	    $tree = new Tree("?mod=vm&amp;stream=text&amp;act=display_js&amp;js=");
	    $tree->setRoot(new Node(_('Skills and Work Restrictions')));

	    while(!$result->EOF)
	    {
	        $split = preg_split('/'. VM_SKILLS_DELIMETER .'/', $result->fields['option_description']);
	        $cur_parent = $tree->root;

	        foreach($split as $index => $name)
	        {
	            $name = trim($name);
	            if($name != '') 
	            {
		            if($index < (count($split) - 1))
		            {
		                $search_result = $tree->findNodeAux($cur_parent, $name);
		                if($search_result == null)
		                {
		                    $tmp_child = new Node($name, 'CheckboxNode', array('input_name' => 'null'));
		                    $cur_parent->addChild($tmp_child);
		                    $cur_parent = $tmp_child;
		                }
		                else
		                {
		                    $cur_parent = $search_result;
		                }
		            }
		            else
		            {
		            	$extra_info = array('input_name' => "'SKILL_{$result->fields['option_code']}'");
	
		            	if(in_array($result->fields['option_code'], $skills_array))
		            		$extra_info['checked'] = true;
	
		                $tmp_child = new Node($name, 'CheckboxNode', $extra_info);
		                $cur_parent->addChild($tmp_child);
		            }
	            }
	        }

	        $result->MoveNext();
	    }

	    return $tree;
	}

	/**
	 * Retrieves all skills for a particular volunteer as an array
	 *
	 * @access public
	 * @param $p_uuid 	- the volunteer's p_uuid
	 * @return the array, where each key is numerically based and each value is the skill ID
	 */

	function getVolSkillsArray($p_uuid)
	{
		$skills_array = array();
		$result = $this->execute("SELECT opt_skill_code FROM vm_vol_skills WHERE p_uuid = '$p_uuid'");

		while(!$result->EOF)
		{
			$skills_array[] = $result->fields['opt_skill_code'];
			$result->MoveNext();
		}

		return $skills_array;
	}

	/**
	 * Retrieves all skills for a particular volunteer as a Tree object with simple
	 * Nodes for everything (no CheckboxNodes)
	 *
	 * @access public
	 * @param $p_uuid 	- the volunteer's p_uuid
	 * @param $vol		- true to retrieve a volunteer's skills, false to retrieve a
	 * 						project's required skills
	 * @return the Tree object
	 */

	function getVolSkillsTree($p_uuid)
	{
	    // query for all skills that belong to this volunteer

	    $result = $this->execute("SELECT option_description FROM field_options WHERE option_code IN
	    		                  (SELECT opt_skill_code FROM vm_vol_skills WHERE p_uuid = '$p_uuid')
	    		                  ORDER BY option_description");
	    $tree = new Tree("?mod=vm&amp;stream=text&amp;act=display_js&amp;js=");
	    $tree->setRoot(new Node(_('Skills and Work Restrictions')));

		// now store the skills in a Tree structure

	    while(!$result->EOF)
	    {
	        $split = preg_split('/'. VM_SKILLS_DELIMETER .'/', $result->fields['option_description']);
	        $cur_parent = $tree->root;

	        foreach($split as $index => $name)
	        {
                $name = trim($name);
                if($name != '') {
	                $search_result = $tree->findNodeAux($cur_parent, $name);
	                if($search_result == null)
	                {
	                    $tmp_child = new Node($name);
	                    $cur_parent->addChild($tmp_child);
	                    $cur_parent = $tmp_child;
	                }
	                else
	                {
	                    $cur_parent = $search_result;
	                }
                }

	        }

	        $result->MoveNext();
	    }

	    return $tree;
	}

	/**

	/**
	 * Returns all skill IDs as an array
	 *
	 * @access public
	 * @return all skill IDs as a numerically-based array, where each value is the shorthand ID of a skill
	 */

	function getSkillIDs()
	{
		$result = $this->execute("SELECT option_code FROM field_options WHERE field_name = 'opt_skill_type'");
		$skill_ids = array();
		while(!$result->EOF)
		{
			$skill_ids[] = $result->fields['option_code'];
			$result->MoveNext();
		}
		return $skill_ids;
	}

	function getSkillList() {
		$result = $this->execute("select option_code code, option_description skill from field_options where field_name = 'opt_skill_type' order by option_description asc");
		if(!$result->EOF) {
			$skills = array();
			while(!$result->EOF) {
				$skills[$result->fields['code']] = $result->fields['skill'];
				$result->moveNext();
			}
			return $skills;
		} else
			return false;
	}

	function removeSkill($code)
	{
		$this->execute("delete from field_options where field_name = 'opt_skill_type' and option_code = '$code'");
	}

	/**
	 * Adds a new skill to the field_options table
	 *
	 * @param $code		- the abbreviated name for the skill
	 * @param $desc		- a description of the skill
	 * @return true if successful, false if the skill already exists
	 */

	function addSkill($code, $desc)
	{
		$result = $this->execute("SELECT 1 FROM field_options WHERE field_name = 'opt_skill_type' AND option_code = '$code'");

		if(!$result->EOF)
			return false;

		$this->execute("INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', '$code', '$desc')");
		return true;
	}
	/**
	 * Retrieves all organizations registered in the system
	 *
	 * @param	$vmOnly	- (optional, default false) - true to return only organizations that at least one
	 * 						volunteer (active or retired) is a part of (useful for reports)
	 * @return an associative array, where each key is the organization's o_uuid and each
	 * 			value is its corresponding name
	 */

	function getOrganizations($vmOnly=false)
	{
		$q = "SELECT o_uuid, name FROM org_main ";

		if($vmOnly)
			$q .= "WHERE o_uuid IN (SELECT org_id FROM vm_vol_active)";

		$result = $this->execute($q);
		$orgs = array();
		while(!$result->EOF)
		{
			$orgs[$result->fields['o_uuid']] = $result->fields['name'];
			$result->MoveNext();
		}
		return $orgs;
	}

	/**
	 * Retrieves an organization's information.
	 *
	 * @param $o_uuid 	- the UUID of the organization
	 * @return an associative array, which has the following structure:
	 * Array
	 * (
	 * 		'name'		=> the organization's name
	 * )
	 *
	 * NOTE: If the organization is not found, an empty array is returned.
	 */

	function getOrganizationInfo($o_uuid)
	{
		$result = $this->execute("SELECT name FROM org_main WHERE o_uuid = '{$o_uuid}'");
		if($result->EOF)
		{
			return array();
		}
		else
		{
			$this->remove_keys($result->fields);
			return $result->fields;
		}
	}

	/**
	 * Checks to see if the given user is registered as a volunteer and still being active (not retired)
	 *
	 * @access public
	 * @param $p_uuid	- the user's p_uuid
	 * @return true if the user is a volunteer, false otherwise
	 */

	function isVolunteer($p_uuid) //
	{
		$result = $this->execute("SELECT p_uuid FROM vm_vol_active WHERE p_uuid = '$p_uuid'");
		return !$result->EOF;
	}


	/**
	 * Gets a list of volunteers who have the given skill/credential
	 *
	 * @param $ability 		- the skill code of the skill/credential to search by
	 * @param $status 		- (optional, default null) set to the ability status to filter by:
	 *						'approved'		- already approved
	 * 						'denied'		- ability request was denied
	 * 						'unapproved'	- not yet approved but not yet denied
	 * @return an associative array where each key is a volunteer's p_uuid and the corresponding value is an array with the following structure:
	 *
	 * 	Array
	 * 	(
	 * 		'name'		=> the volunteer's name
	 * 		'status'	=> the status of the volunteer's ability:
	 * 						'approved'		- already approved
	 * 						'denied'		- ability request was denied
	 * 						'unapproved'	- not yet approved but not yet denied
	 * 	)
	 */

	function getVolunteersByAbility($ability, $status=null)
	{
		if($status != null)
			$extra_clause = " AND vm_vol_skills.status = '$status' ";
		else
			$extra_clause = "";

		$result = $this->execute(	"SELECT DISTINCT vm_vol_skills.p_uuid, full_name, vm_vol_skills.status
									 FROM vm_vol_skills JOIN person_uuid USING(p_uuid)
									 JOIN vm_vol_active USING (p_uuid)
									 WHERE opt_skill_code = '$ability'
									 $extra_clause
									 ORDER BY status");

		$vols = array();
		while(!$result->EOF)
		{
			$vols[$result->fields['p_uuid']] = array('name' => $result->fields['full_name'], 'status' => $result->fields['status']);
			$result->moveNext();
		}
		return $vols;
	}

	/**
	 * Updates a volunteers's ability's status
	 *
	 * @access public
	 * @param $p_uuid		- the p_uuid of the volunteer whose manager status to update
	 * @param $ability		- the skill code of the ability whose status to modify
	 * @param $approved		- true to approve the status, false to deny it
	 * @return void
	 */
	function updateAbilityStatus($p_uuid, $ability, $approved)
	{
		//get the name of the ability for later use in messaging
		$result = $this->execute("SELECT option_description FROM field_options WHERE option_code = '$ability'");
		$ability_name = $result->fields['option_description'];

		//check to see if we're modifying an existing ability or adding a new ability
		$result = $this->execute("SELECT 1 FROM vm_vol_skills WHERE p_uuid = '$p_uuid' AND opt_skill_code = '$ability'");
		if(!$result->EOF)
		{
			if($approved)
			{
				$this->execute("UPDATE vm_vol_skills SET status='approved' WHERE opt_skill_code = '$ability' AND p_uuid = '$p_uuid'");
				$this->sendMessage('SYS_MSG', array($p_uuid), _("Your ability status for")." $ability_name "._("has been approved").". \n\n ("._("This is an automated message").")");
			}
			else
			{
				//check to see if we're denying or revoking the status from the user (just for messaging)
				$result = $this->execute("SELECT 1 FROM vm_vol_skills WHERE p_uuid = '$p_uuid' AND opt_skill_code = '$ability' AND status = 'approved'");
				if(!$result->EOF)
					$this->sendMessage('SYS_MSG', array($p_uuid), _("Your ability status for")." $ability_name "._("has been revoked").". \n\n ("._("This is an automated message").")");
				else
					$this->sendMessage('SYS_MSG', array($p_uuid), _("Your ability status request for")." $ability_name "._("has been denied").". \n\n ("._("This is an automated message").")");

				$this->execute("UPDATE vm_vol_skills SET status='denied' WHERE opt_skill_code = '$ability' AND p_uuid = '$p_uuid'");
			}
		}
		else
		{
			$this->execute("INSERT INTO vm_vol_skills (p_uuid, opt_skill_code, status) VALUES ('$p_uuid', '$ability', 'approved')");
			$this->sendMessage('SYS_MSG', array($p_uuid), _("You have been given an approved ability status for")." $ability_name. \n\n ("._("This is an automated message").")");
		}
	}

	/**
	 * Sends a message to a volunteer from another person
	 *
	 * @param $from_id 		- the p_uuid of the sender
	 * @param $to_id		- an array of p_uuids representing the recepients
	 * @param $message 		- the text to send
	 * @return  void
	 */

 	function sendMessage($from_id, $to_ids, $message)
 	{
 		$this->execute("INSERT INTO vm_message (message) values ('$message')");

 		$result= $this->execute("SELECT LAST_INSERT_ID()");
 		$message_id = $result->fields[0];

 		foreach($to_ids as $to_id)
 		{
	 		$this->execute("INSERT INTO vm_courier (message_id, to_id, from_id) VALUES ($message_id, '$to_id', '$from_id')");
	 		$this->execute("INSERT INTO vm_mailbox (p_uuid, message_id, box, checked) VALUES ('$to_id', $message_id, 0, 0)");
 		}

 		$this->execute("INSERT INTO vm_mailbox (p_uuid, message_id, box, checked) VALUES ('$from_id', $message_id, 1, 0)");
 	}

 	/**
 	 * Retrieves information about all the  messages sent to the volunteer
 	 *
 	 * @param $p_uuid 		- the id of the volunteer
 	 * @param $inbox		- true to retrieve inbox messages, false to retrieve outbox messages
 	 * 							(defaults to outbox)
 	 * @return an array of arrays, where each inner array has following structure:
 	 * Array
 	 * (
 	 * 		'message_id'		=> the ID of the message
 	 * 		'from_id'		=> the p_uuid of the person who the message is from
 	 * 		'to_id'			=> the p_uuid of the person who the message is to
 	 * 		'time'			=> a timestamp of when the message was sent
 	 * 		'message'		=> the message sent
 	 * 		'checked'		=> 1 if the message has been read yet, 0 if not
 	 * )
 	 */

 	 function getMessages($p_uuid, $inbox=true)
 	 {
 	 	if($inbox) {
 			$query = "SELECT from_id, vm_message.message_id, time, message, checked FROM vm_message, vm_courier, vm_mailbox WHERE p_uuid = '$p_uuid' AND box = 0 AND to_id = '$p_uuid' AND vm_message.message_id = vm_courier.message_id AND vm_message.message_id = vm_mailbox.message_id ORDER BY time DESC";
 	 	} else {
			$query = "SELECT vm_message.message_id, time, message, checked FROM vm_message, vm_courier, vm_mailbox WHERE p_uuid = '$p_uuid' AND box = 1 AND from_id = '$p_uuid' AND vm_message.message_id = vm_courier.message_id AND vm_message.message_id = vm_mailbox.message_id GROUP BY vm_message.message_id ORDER BY time DESC";
 	 	}

 	 	$result = $this->getCurrentPage($query);
 		$messages = array();
 		while(!$result->EOF) {
 			$this->remove_keys($result->fields);
 			$messages[]= $result->fields;
 			$result->moveNext();
 		}
 		return $messages;
 	 }

 	 /**
 	  * Retrieves the entire list of who a message is sent to
 	  *
 	  * @access public
 	  * @param $msg_id	- the ID of the message to check
 	  * @return an associative array, where each key is a person's p_uuid and each
 	  * value is the person's name
 	  */

 	 function getToList($msg_id)
 	 {
 	 	$result = $this->execute("SELECT to_id, full_name FROM vm_courier, person_uuid WHERE p_uuid = to_id AND message_id = $msg_id");
 	 	$list = array();
 	 	while(!$result->EOF && $result != null)
 	 	{
 	 		$list[$result->fields['to_id']] = $result->fields['full_name'];
 	 		$result->MoveNext();
 	 	}
 	 	return $list;
 	 }

 	 /**
 	  * Retrieves a person's name
 	  *
 	  * @param $p_uuid 		- a person's unique id
 	  * @return their name
 	  */

 	  function getPersonName($p_uuid) //
 	  {
 	  	$result = $this->execute("SELECT full_name FROM person_uuid WHERE p_uuid ='$p_uuid'");
 	  	if(!$result->fields)
 	  		return false;
 	  	return $result->fields['full_name'];
 	  }
 	  /**
 	   * Retrieves the information from a message and sets it as checked.
 	   *
 	   * @param $p_uuid 	- the p_uuid of the volunteer to check the message for
 	   * @param $message_id	- the message ID
 	   * @param	$box		- true to check someone's inbox, false to check the outbox
 	   * @return the array of message information if successful, or an empty array if the message was not found
 	   */

 	   function getMessage($p_uuid, $message_id, $box=true)
 	   {
 	   		$box_num = ($box)?'0':'1';

			$result = $this->execute("SELECT from_id, vm_message.message_id, time, message, checked FROM vm_message, vm_courier, vm_mailbox WHERE p_uuid = '$p_uuid' AND box=$box_num AND vm_message.message_id = vm_courier.message_id AND vm_message.message_id = vm_mailbox.message_id AND vm_message.message_id = $message_id");
			if(!$result->EOF)
  			{
  				//set the message as checked and return the info

  				$this->execute("UPDATE vm_mailbox SET checked = 1 WHERE p_uuid='$p_uuid' AND message_id = $message_id AND box=$box_num");
  				$this->remove_keys($result->fields);
 	 			return $result->fields;
  			}
  			else
  			{
  				return array();
  			}
 	   }

 	   /**
 	    * Deletes a message
 	    *
 	    * @param $p_uuid	- the person to delete the message for
 	    * @param $msg_id 	- the ID of the message
 	    * @param $box		- true to delete from inbox, false to delete from outbox
 	    * @return void
 	    */

 	    function deleteMessage($p_uuid, $msg_id, $box)
 	    {
 	    	$box_num = ($box)?'0':'1';
 	    	$this->execute("DELETE FROM vm_mailbox WHERE message_id = '$msg_id' AND p_uuid = '$p_uuid' AND box=$box_num");
 	    }

 	   /**
 	    * Retrieve number of unread messages from an inbox
 	    *
 	    * @param $p_uuid	- the p_uuid of the volunteer to check
 	    * @return the number of unread messages
 	    */

 	    function getUnreadMessages($p_uuid)
 	    {
 	    	$result = $this->execute("SELECT COUNT(*) FROM vm_mailbox WHERE p_uuid = '$p_uuid' AND box = 0 AND checked = 0");
 	    	return $result->fields[0];
 	    }

		/**
		 * Generates the SQL SELECT statement clauses based on a phonetic search for a volunteer's name
		 *
		 * @param $vol_name 	- the full volunteer's name (spaces ok)
		 * @param $loose	- true to use looser matching, false otherwise
		 * @return the SELECT statement
		 */

		function generateSelectPhoneticClauses($vol_name, $loose=false)
		{
		    if(trim($vol_name)=='')
		    	return '';
		    else
		    {
			    $query = " (";

			    $names = preg_split("/\s+/", $vol_name);

			    if($loose)
			    {
			    	//looser matching only matters for metaphone
			        foreach($names as $single_name)
			        {
			            $query .= " encode2 LIKE '%" . metaphone($single_name) . "%' OR ";
			            $query .= "'" . metaphone($single_name) . "'" . " LIKE  concat('%', encode2, '%') OR ";
			        }
			    }
			    else
			    {
			        foreach($names as $single_name)
			        {
			            $query .= " encode1 = '" . soundex($single_name) . "' OR ";
			            $query .= " encode2 = '" . metaphone($single_name) . "' OR ";
			        }
			    }

			    $query = substr($query, 0, strlen($query) - 3);
			    $query .= ") ";

			    return $query;
		    }
		}

 	    /**
 	     * Retrieve a set of search results for a volunteer search. It is assumed
 	     * that validation on the parameters has already occurred.
 	     *
 	     * @param $id				- an ID to look for (NIC, DLN, etc.)
 	     * @param $name				- a name to search by
 	     * @param $skills			- an array of skill IDs to search by
 	     * @param $skills_matching	- VM_SKILLS_ALL to match all $skills, VM_SKILLS_ANY to match any $skills
 	     * @param $start_date  		- the start date of required availability
 	     * @param $end_date 		- the end date of required availability
 	     * @param $location 		- the most specific location to search by
 	     * @param $date_constraint	- true to search for a volunteer that is available for the entire time period specified, false
 	     * 								to search for a volunteer that is available for any portion of the time period specified
 	     * @param $unassigned		- (optional) true to show only unassigned volunteers, false to show all
 	     * @param $loose			- (optional) true for looser matching on the name
 	     * @param $assigning_proj	- (optional, for assigning) the project ID of the project we are assigning to, to exclude all volunteers already assigned to it
 	     * @return An array of Volunteer Objects. This function uses paging.
 	     */

 	    function getVolSearchResults($id, $name, $skills, $skills_matching, $start_date, $end_date, $location, $date_constraint, $unassigned=false, $loose=false, $soundslike=false, $assigning_proj=null)
 	    {
 	    	$name_set = $name != '';
 	    	$id_set = $id != '';
 	    	$date_set = $start_date != '';
 	    	$skills_set = count($skills) > 0;
 	    	$location_set = $location != '';

 	    	$query = 	"SELECT 	DISTINCT vm_vol_active.p_uuid
				 		 FROM 		vm_vol_active
				 		 			LEFT JOIN person_uuid USING (p_uuid)
									LEFT JOIN identity_to_person USING (p_uuid)
									LEFT JOIN org_main ON (vm_vol_active.org_id = org_main.o_uuid)
									LEFT JOIN field_options ON (identity_to_person.opt_id_type = field_options.option_code)
									LEFT JOIN location_details ON (location_details.poc_uuid = person_uuid.p_uuid) ";

			//generate the FROM clause

			// This joins on the phonetic word table
			if($name_set && ($soundslike || $loose)) {
				$query .= " JOIN phonetic_word ON (person_uuid.p_uuid = phonetic_word.pgl_uuid) ";
			}
			$query .= "WHERE 1 ";

			//generate the WHERE clause

			//Search by name -- this sets the search criteria in the WHERE clause

			if($name_set) {
				if($soundslike || $loose) {
					$query .= " AND ".$this->generateSelectPhoneticClauses($name, $loose);
				} else {
					$query .= " AND (";
					$query .= "'".$name."' LIKE CONCAT('%', full_name, '%') OR ";
					$query .= "'".$name."' LIKE CONCAT('%', family_name, '%') OR ";
					$query .= "'".$name."' LIKE CONCAT('%', l10n_name, '%') OR ";
					$query .= "'".$name."' LIKE CONCAT('%', custom_name, '%') OR ";
					$query .= "full_name LIKE '%$name%' OR ";
					$query .= "family_name LIKE '%$name%' OR ";
					$query .= "l10n_name LIKE '%$name%' OR ";
					$query .= "custom_name LIKE '%$name%'";
					$query .= ") ";

				}
			}
			//search by ID

			if($id_set) {
				$query .= " AND serial LIKE '%{$id}%' ";
			}

			//search by location
			if($location_set) {
				$location_level = shn_get_level($location);
				$tmp = shn_get_last_level();
				$most_specific_level = $tmp[0];

				//now, basically we want to store the location hierarchy starting from the searched location
				//since any location that falls under it should match.
				//we want to search for inclusion in a result such as
				//SELECT l1.loc_uuid AS lev1, l2.loc_uuid as lev2, l3.loc_uuid as lev3
				//FROM location AS l1
				//LEFT JOIN location AS l2 ON l2.parent_id = l1.loc_uuid
				//LEFT JOIN location AS l3 ON l3.parent_id = l2.loc_uuid
				//WHERE l1.loc_uuid = 'qbhglc-1';

				//create temporary table to hold the given location and all of its children
				$q = "CREATE TEMPORARY TABLE vm_temp_locations (";
				for($i = $location_level; $i <= $most_specific_level; $i++) {
					$q .= "l$i VARCHAR(255),";
				}
				$q = substr($q, 0, strlen($q) - 1);
				$q .= ")";
				$this->execute($q);

				//insert into it the searched location and all of its children
				$q = "INSERT INTO vm_temp_locations SELECT ";
				for($i = $location_level; $i <= $most_specific_level; $i++) {
					$q .= "l".$i.".loc_uuid AS lev$i,";
				}
				$q = substr($q, 0, strlen($q) - 1);
				$q .= " FROM location AS l$location_level ";
				for($i = $location_level + 1; $i <= $most_specific_level; $i++) {
					$q .= "LEFT JOIN location AS l".$i." ON l$i.parent_id = l".($i - 1).".loc_uuid ";
				}
				$q .= " WHERE l$location_level.loc_uuid = '$location'";
				$this->execute($q);

				//create a temporary table to store all distinct locations for easier searching
				$this->execute("CREATE TEMPORARY TABLE vm_temp_location_search (loc_uuid VARCHAR(255))");
				for($i = $location_level; $i <= $most_specific_level; $i++) {
					$q = "INSERT INTO vm_temp_location_search SELECT DISTINCT l$i FROM vm_temp_locations";
					$this->execute($q);
				}

				//now finally add the clause to the search query
				$query .= " AND location_details.location_id IN (SELECT loc_uuid FROM vm_temp_location_search) ";
			}

			//search by skills
			if($skills_set)
			{
				$skills_set_search = " (";
				foreach($skills as $skill_id)
				{
					$skills_set_search .= "'$skill_id', ";
				}
				$skills_set_search = substr($skills_set_search, 0, strlen($skills_set_search) - 2);
				$skills_set_search .= ') ';

				$query .= " AND (
							    SELECT  COUNT(*)
							    FROM    vm_vol_skills
							    WHERE   p_uuid = person_uuid.p_uuid
							    AND     opt_skill_code IN $skills_set_search
							) ";
				if($skills_matching == VM_SKILLS_ALL)
					$query .= "= ". count($skills) . " ";
				else
					$query .= "> 0 ";
			}
			//search by availability

			if($date_set)
			{

				if($date_constraint)
				{
					//volunteer must be available for entire date range specified
					$query .= " AND date_avail_start<='$start_date' AND date_avail_end>='$end_date' ";
				}
				else
				{
					if($end_date == '')
					{
						//volunteer must be available for any time after the start date specified
						$query .= " AND date_avail_end>='$start_date' AND date_avail_start<='$start_date'";
					}
					else
					{
						//volunteer must be available for any portion of time between the dates specified
						$query .= " AND date_avail_start<='$end_date' AND date_avail_end>='$start_date' ";
					}
				}
			}

			//get only unassigned

			if($unassigned) {
				$query .= " AND person_uuid.p_uuid NOT IN (SELECT DISTINCT p_uuid FROM vm_vol_assignment_active) ";
			}

			//if we are assigning to a project, exclude results from the project we are assigning to

			if($assigning_proj != null) {
				$query .= " AND person_uuid.p_uuid NOT IN (SELECT p_uuid FROM vm_vol_assignment_active WHERE proj_id = '$assigning_proj') AND person_uuid.p_uuid NOT IN (SELECT p_uuid FROM vm_vol_assignment_active WHERE proj_id = '$assigning_proj' AND ptype_id = 'smgr') ";
			}

		    //get the results and format them into the resulting array
			$result = $this->getCurrentPage($query);
//			print_r($this->db);

			$search_results = array();

			while(!$result->EOF) {
				$search_results[] = new Volunteer($result->fields['p_uuid']);
				$result->MoveNext();
			}

	        return $search_results;
 	    }

 	    /**
		 * Update the 'phonetic_word' table with volunteer phonetic word information. This is
		 * included in case someone's name changes outside the VM module.
		 *
		 * @return void
		 */

		function updatePhonetics()
		{
		    $result = $this->execute("SELECT p_uuid, full_name FROM person_uuid WHERE p_uuid IN (SELECT p_uuid FROM vm_vol_active)");

	        while(!$result->EOF)
	        {
	            $p_uuid = $result->fields['p_uuid'];
	            $full_name = $result->fields['full_name'];

	            $this->execute("DELETE FROM phonetic_word WHERE pgl_uuid='{$p_uuid}'");

	            $names = preg_split("/\s+/", $full_name);
	            foreach($names as $single_name)
	            {
	                $this->execute("INSERT INTO phonetic_word VALUES('" . soundex($single_name) . "', '" . metaphone($single_name) . "', '{$p_uuid}')");
	            }

	            $result->MoveNext();
	        }
		}

		/**
		 * Assigns a volunteer to a project.
		 *
		 * @access public
		 * @param $vol_id	- the p_uuid of the volunteer to assign
		 * @param $p_id		- the ID of the project to assign the volunteer to
		 * @return void
		 */

		function assignToProject ($vol_id, $p_id)
		{
			$this->execute("INSERT INTO vm_vol_assignment (p_uuid,proj_id) values('$vol_id', '$p_id') ");

			//send the volunteer a message notifying them of the assignment
			$result = $this->execute("SELECT name FROM vm_projects WHERE proj_id = '$p_id'");
			$this->sendMessage('SYS_MSG', array($vol_id), _("You have been assigned to")." {proj $p_id {$result->fields['name']}}. \n\n ("._("This is an automated message").")");
		}


		/**
		 * Retrieves whether or not the volunteer is an approved site manager
		 *
		 * @param $p_uuid	- the p_uuid of the volunteer
		 * @return true if the volunteer is an approved site manager, false if not
		 */

		function isSiteManager($p_uuid)
		{
			$result = $this->execute(	"SELECT 	1
										 FROM 		vm_vol_skills, vm_vol_active
										 WHERE 		opt_skill_code = 'MGR'
										 AND		vm_vol_skills.status='approved'
										 AND 		vm_vol_active.p_uuid = '$p_uuid'
										 AND		vm_vol_active.p_uuid = vm_vol_skills.p_uuid");
			return !$result->EOF;
		}

		/*
		 *  retieves a pictue and returns the results
		 */
		function getVMPicture($img_uuid) {
			$result = $this->execute("select image_data, thumb_data, p_uuid, width, height, thumb_width, thumb_height, mime_type, name from vm_image where img_uuid = '$img_uuid'");
			if($result->EOF)
				return false;
			else {
				$this->remove_keys($result->fields, MYSQL_ASSOC);
				return $result->fields;
			}
		}

		/*
		 *  Save the image or updates a new image that will be displayed as the users image
		 */
		function saveVMPicture($pic) {
			$original = addslashes($pic->original);
			$image_data = addslashes($pic->image_data);
			$thumb_data = addslashes($pic->thumb_data);
			if(!empty($pic->p_uuid))
				$this->execute("delete from vm_image where p_uuid = '{$pic->p_uuid}'");
			$this->execute("insert into vm_image (img_uuid, original, image_data, thumb_data, p_uuid, date_added, width, height, thumb_width, thumb_height, mime_type, name) " .
					"values ('{$pic->img_uuid}', '$original', '$image_data', '$thumb_data', '{$pic->p_uuid}', now(), '{$pic->width}', '{$pic->height}', '{$pic->thumb_width}', '{$pic->thumb_height}', '{$pic->type}', '{$pic->name}')");
		}

		function getPictureID($p_uuid) {
			$result = $this->execute("select img_uuid from vm_image where p_uuid = '$p_uuid'");
			if($result->EOF)
				return false;
			else
				return $result->fields['img_uuid'];
		}

        /*
         *  Removes the current picture that is display as your image
         */
		function deletePicture($img_uuid) {
			$this->execute("delete from vm_image where img_uuid = '$img_uuid'");
		}

		/**
		 * Retrieves all possible VM access constraints that could apply to any given access request
		 *
		 * @return an array, where each key is the access constraint short-hand and each value is
		 * 			a description of the access constraint
		 */

		function getPossibleAccessConstraints()
		{
			$result = $this->execute("SELECT constraint_id, description FROM vm_access_constraint");
			$constraints = array();
			while(!$result->EOF)
			{
				$constraints[$result->fields['constraint_id']] = $result->fields['description'];
				$result->MoveNext();
			}
			return $constraints;
		}

		/**
		 * Retrieves constraints on access requests particular to the VM module
		 */

		function getAccessRequestConstraints()
		{
			//first get VM-specific access constraints

			$result = $this->execute(	"SELECT 	act, vm_action, vm_access_constraint.constraint_id
										 FROM 		vm_access_request, vm_access_constraint, vm_access_constraint_to_request
										 WHERE		vm_access_request.request_id = vm_access_constraint_to_request.request_id
										 AND 		vm_access_constraint.constraint_id = vm_access_constraint_to_request.constraint_id");
			$access = array();

			while(!$result->EOF)
			{
				$act = $result->fields['act'];
				$vm_action = $result->fields['vm_action'];
				$constraint = $result->fields['constraint_id'];
				$req_desc = $result->fields['req_desc'];

				if(!is_array($access[$act]))
					$access[$act] = array();

				if(!is_array($access[$act][$vm_action]))
					$access[$act][$vm_action] = array();

				if(!is_array($access[$act][$vm_action]['extra']))
					$access[$act][$vm_action]['extra'] = array();

				$access[$act][$vm_action]['extra'][] = $constraint;

				$result->MoveNext();
			}

			//next get Sahana-specific data classification constraints

			$result = $this->execute(	"SELECT 	act, vm_action, table_name, crud
										 FROM 		vm_access_request, vm_access_classification_to_request
										 WHERE		vm_access_request.request_id = vm_access_classification_to_request.request_id");

			while(!$result->EOF)
			{
				$act = $result->fields['act'];
				$vm_action = $result->fields['vm_action'];
				$table_name = $result->fields['table_name'];
				$crud = $result->fields['crud'];

				if(!is_array($access[$act]))
					$access[$act] = array();

				if(!is_array($access[$act][$vm_action]))
					$access[$act][$vm_action] = array();

				if(!is_array($access[$act][$vm_action]['tables']))
					$access[$act][$vm_action]['tables'] = array();

				$access[$act][$vm_action]['tables'][$table_name] = $crud;

				$result->MoveNext();
			}

			return $access;
		}

		/**
		 * Gets a specific access request's name based on act and vm_action
		 *
		 * @param $act			the act
		 * @param $vm_action	the vm_action
		 * @return the description if a match found, otherwise null
		 */

		function getAccessRequestName($act, $vm_action) {
			$result = $this->execute("SELECT description FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action'");
			if(!$result->EOF)
				return $result->fields['description'];
			else
				return null;
		}

		/**
		 * Retreives all access requests
		 */

		function getAccessRequests()
		{
			$result = $this->execute("SELECT act, vm_action, description FROM vm_access_request ORDER BY description");
			$requests = array();
			while(!$result->EOF)
			{
				$act = $result->fields['act'];
				$vm_action = $result->fields['vm_action'];
				$desc = $result->fields['description'];

				if(!is_array($requests[$act]))
					$requests[$act] = array();

				$requests[$act][$vm_action] = $desc;

				$result->moveNext();
			}
			return $requests;
		}

		/**
		 * Retreives all access requests and return them in a way that is easier for displaying
		 */

		function getAccessRequestsForDisplay()
		{
			$result = $this->execute("SELECT act, vm_action, description FROM vm_access_request ORDER BY description");
			$requests = array();
			while(!$result->EOF)
			{
				$act = $result->fields['act'];
				$vm_action = $result->fields['vm_action'];
				$desc = $result->fields['description'];

				$matches = array();
				preg_match("/^\s*(\w+)(.*)/", $desc, $matches);

				$requests[] = array('display_action' => $matches[1], 'partial_desc' => $matches[2], 'act' => $act, 'vm_action' => $vm_action);

				$result->MoveNext();
			}
			return $requests;
		}

		/**
		 * Retrieves all access constraints for a particular request situation
		 */

		function getSpecificAccessRequestConstraints($act, $vm_action)
		{
			$constraints = array('tables' => array(), 'extra' => array());

			//special case access constraints
			$result = $this->execute(  "SELECT  vm_access_constraint.constraint_id, vm_access_constraint.description
										FROM    vm_access_request, vm_access_constraint, vm_access_constraint_to_request
										WHERE   act = '$act' AND vm_action = '$vm_action'
										AND     vm_access_request.request_id = vm_access_constraint_to_request.request_id
										AND     vm_access_constraint.constraint_id = vm_access_constraint_to_request.constraint_id");
			while(!$result->EOF)
			{
				$constraints['extra'][] = $result->fields['constraint_id'];
				$result->MoveNext();
			}

			//data classification access constraints
			$result = $this->execute(  "SELECT  table_name, crud
										FROM    vm_access_request, vm_access_classification_to_request
										WHERE   act = '$act' AND vm_action = '$vm_action'
										AND     vm_access_request.request_id = vm_access_classification_to_request.request_id");
			while(!$result->EOF)
			{
				$constraints['tables'][$result->fields['table_name']] = $result->fields['crud'];
				$result->MoveNext();
			}

			return $constraints;
		}

		/**
		 * Updates the 'vm_access_classification_to_request' table with new data classification access information
		 *
		 * @param $act			- 	the 'act' of the request to modify
		 * @param $vm_action	- 	the 'vm_action' of the request to modify
		 * @param $tables		- 	an array specifying the tables and permissions to modify, where each key is the table name
		 * 							and each value is the permissions (in 'crud' format to require)
		 * @return void
		 */
		function updateClassificationConstraints($act, $vm_action, $tables)
		{
			//first get the request_id of the request

			$result = $this->execute("SELECT request_id FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action'");
			$request_id = $result->fields['request_id'];

			//get rid of the old classification constraints

			$this->execute("DELETE FROM vm_access_classification_to_request WHERE request_id = $request_id");

			//add the new classification constraints

			foreach($tables as $table_name => $crud)
				$this->execute("INSERT INTO vm_access_classification_to_request (request_id, table_name, crud) VALUES ($request_id, '$table_name', '$crud')");
		}

		/**
		 * Retrieves all tables in the database
		 */

		function getDBTables()
		{
			$tables = array();
			$result = $this->execute("SHOW TABLES");
			while(!$result->EOF)
			{
				$tables[] = $result->fields[0];
				$result->MoveNext();
			}
			return $tables;
		}

		/**
		 * Retreives the description of an access request
		 *
		 * @param $act			- the 'act' to look up by
		 * @param $vm_action		- the 'vm_action' to look up by
		 * @return the description
		 */

		function getAccessRequestDescription($act, $vm_action)
		{
			$result = $this->execute("SELECT description FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action'");
			return $result->fields['description'];
		}

		/**
		 * Adds a constraint on an access request
		 */

		function addConstraint($act, $vm_action, $constraint)
		{
			$this->execute("INSERT INTO vm_access_constraint_to_request (request_id, constraint_id) VALUES
							((SELECT request_id FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action'), '$constraint')");
		}

		/**
		 * Removes all access constraints on an access request
		 */

		function removeConstraints($act, $vm_action)
		{
			$this->execute("DELETE FROM vm_access_constraint_to_request WHERE request_id =
							(SELECT request_id FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action')");
		}

		/**
		 * Retrieves a set of skills and descriptions of those skills
		 *
		 * $id		- the ID to search by
		 * $proj	- true to return a project's needed set of skills
		 */

		function getSkillsAndDescriptions($id)
		{
				$result = $this->execute("select opt_skill_code, option_description from vm_vol_skills, field_options where p_uuid = '{$id}' AND opt_skill_code = option_code order by option_description asc");

			$options = array();

			while(!$result==NULL && !$result->EOF)
			{
			      $options[$result->fields['opt_skill_code']] = $result->fields['option_description'];
			      $result->MoveNext();
			}
			return $options;
		}

		function assignVolunteerToPosition($p_uuid, $pos_id) {
			$this->execute("delete from vm_vol_position where p_uuid = '$p_uuid' and pos_id = '$pos_id'");
			$this->execute("insert into vm_vol_position (p_uuid, pos_id, date_assigned) values ('$p_uuid', '$pos_id', now())");
		}

		/**
		 * Retrieves a set of volunteer p_uuids and names
		 *
		 * @param	$all - (optional, default false) true to return all volunteers, not only active ones
		 * @return an array where each key is the volunteer's id and each value is the corresponding name
		 */

		function getVolunteerNames($all=false)
		{
			$q = "SELECT person_uuid.p_uuid, full_name FROM vm_vol_details JOIN person_uuid USING(p_uuid)";


			if(!$all)
				$q .= " WHERE status = 'active'";

			$result = $this->execute($q);
			$vols = array();
			while(!$result->EOF)
			{
				$vols[$result->fields['p_uuid']] = $result->fields['full_name'];
				$result->moveNext();
			}
			return $vols;
		}

		function logShift($p_uuid, $pos_id, $start, $end) {
			if(!empty($p_uuid) && !empty($pos_id) && !empty($start) && !empty($end)) {
				$startStamp = date("Y-m-d H:i:s", $start);
				$endStamp = date("Y-m-d H:i:s", $end);
				$this->execute("insert into vm_hours (p_uuid, pos_id, shift_start, shift_end)
						values ('$p_uuid', '$pos_id', '$startStamp', '$endStamp')");
				return true;
			} else return false;
		}

		/**
		 * Retrieves whether or not the given volunteer is a site manager for the given project
		 */

		function isSiteManagerForProject($p_uuid, $proj_id)
		{
			$result = $this->execute("SELECT 1 FROM vm_vol_assignment_active WHERE p_uuid = '$p_uuid' AND proj_id = '$proj_id' AND ptype_id = 'smgr'");
			return !$result->EOF;
		}

		/**
		 * Retrieves whether or not the given 'act' and 'vm_action' are in the vm_access_request table
		 */

		function isAccessRequest($act, $vm_action)
		{
			$result = $this->execute("SELECT 1 FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action'");
			return !$result->EOF;
		}

		/**
		 * Retrieves whether or not the given database table is given any classification level under Sahana's ACL system
		 */

		function isClassified($table)
		{
			$result = $this->execute("SELECT 1 FROM sys_tablefields_to_data_classification WHERE table_field = '$table'");
			return !$result->EOF;
		}

		/**
		 * Retreieves whether or not the given position is or was ever in a project for which the given volunteer is a site manager for
		 *
		 * @param	$pos_id		- the position ID
		 * @param	$p_uuid		- the site manager's p_uuid
		 * @return	true if $pos_id is a position in any of $p_uuid's projects, active or retired
		 */

		function isPositionUnderManager($pos_id, $p_uuid)
		{
			$result = $this->execute("SELECT 1 FROM vm_position WHERE '$pos_id' IN (SELECT pos_id FROM vm_position_full WHERE proj_id IN (SELECT proj_id FROM vm_vol_assignment_active WHERE p_uuid = '$p_uuid' AND ptype_id = 'smgr'))");
			return !$result->EOF;
		}

		/**
		 * Retrieves all possible levels of data classification
		 *
		 * @return an array, where each key is the level and each value is its description
		 */

		function getDataClassificationLevels()
		{
			$result = $this->execute("SELECT level_id, level FROM sys_data_classifications");
			$levels = array();
			while(!$result->EOF)
			{
				$levels[$result->fields['level_id']] = $result->fields['level'];
				$result->moveNext();
			}
			return $levels;
		}

		/**
		 * Adds an access request
		 *
		 * @param	$act			- the act parameter of the request
		 * @param	$vm_action		- the vm_action parameter of the request
		 * @param	$description	- a brief description of what is being requested when the request is loaded
		 * @return void
		 */

		function addAccessRequest($act, $vm_action, $description)
		{
			$this->execute("INSERT INTO vm_access_request (act, vm_action, description) VALUES ('$act', '$vm_action', '$description')");
		}

		/**
		 * Removes an access request
		 *
		 * @param	$act			- the act parameter of the request
		 * @param	$vm_action		- the vm_action parameter of the request
		 * @return void
		 */

		function removeAccessRequest($act, $vm_action)
		{
			$result = $this->execute("SELECT request_id FROM vm_access_request WHERE act = '$act' AND vm_action = '$vm_action'");
			$id = $result->fields['request_id'];

			$this->execute("DELETE FROM vm_access_request WHERE request_id = '$id'");
			$this->execute("DELETE FROM vm_access_constraint_to_request WHERE request_id = '$id'");
			$this->execute("DELETE FROM vm_access_classification_to_request WHERE request_id = '$id'");
		}

		/**
		 * Gives the table the given classification level
		 *
		 * @param	$table	- the table to classify
		 * @param	$level	- the level ID to classify the table as
		 * @return void
		 */

		function classifyTable($table, $level)
		{
			$this->execute("DELETE FROM sys_tablefields_to_data_classification WHERE table_field = '$table'");
			$this->execute("INSERT INTO sys_tablefields_to_data_classification (table_field, level_id) VALUES ('$table', '$level')");
		}

		/**
		 * Uses the sahana paging library to get the paging result with the given query and results per page.
		 * When the user clicks on a page link (GET) in the view or a page submit button (POST) the
		 * library function, _shn_page_get_rs(), will take the page parameter from either the GET
		 * or POST variable.  The user can also set the RPP (rows per page) value in the view before
		 * selecting a specific page.
		 * @param $query	The query to use
		 * @return the ADODB query result
		 */

		function getCurrentPage($query) {
			global $global;

			//get number of rows per page
			$rpp = isset($_REQUEST['rpp']) ? $_REQUEST['rpp'] : VM_DEFAULT_RPP;
			$result = _shn_page_get_rs($query, $rpp);

			//set the paging result and rpp to $global to use the metadata later in the views
			$global['vm_page_result'] = $result;
			$global['vm_page_rpp'] = $rpp;

			//VERY IMPORTANT: the _shn_page_get_rs() function above sets the DB query fetchmode to ADODB_FETCH_ASSOC, so to ensure proper
			//working of other things in Sahana (like location functionality), need to reset to 3, which is both numerical and assoc
			//see http://phplens.com/adodb/reference.varibles.adodb_fetch_mode.html
			$this->db->SetFetchMode(3);
			return $result;
		}

}



