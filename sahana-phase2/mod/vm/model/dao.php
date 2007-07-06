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

 		$result = $this->execute("select location_id from location_details where poc_uuid = '" . $id . "'");
 		$locations = array();
 		if (!$result->EOF)
 		{
	 		$lastId = $result->fields["location_id"];
	 		do
	 		{
	 			$locations[]= $lastId;
	 			$result= $this->execute("select parent_id from location where loc_uuid = '$lastId'");
	 			$lastId = $result->fields["parent_id"];
	 		}
	 		while($lastId!=NULL && $lastId!='NULL' && !$result->EOF);
 		}

 		$info['locations'] = $locations;

 		// get project[s] to which they are assigned
 		// a volunteer may be assigned to more than one project

		$info['proj_id'] = array();
		$result = $this->execute("select proj_id from vm_proj_vol where p_uuid = '$id'");
		if(!$result->EOF)
		{
			while(!$result->EOF)
			{
				$info['proj_id'][] = $result->fields['proj_id'];
				$result->MoveNext();
			}
		}

		//get the gender,  birth date, and occupation

		$result = $this->execute("select opt_gender, birth_date, occupation from person_details where p_uuid = '$id'");
		$info['gender'] = $result->fields['opt_gender'];
		$info['dob'] = $result->fields['birth_date'];
		$info['occupation'] = $result->fields['occupation'];
		$info['status'] = $this->volIsAssignedToProject($id)?'Assigned':'Unassigned';

		//get work times and organization affiliation

		$result= $this->execute(" select date_avail_start, date_avail_end, hrs_avail_start, hrs_avail_end, org_id from vm_vol_details where p_uuid = '$id' ");
		$info['date_start'] = $result->fields['date_avail_start'];
		$info['date_end'] = $result->fields['date_avail_end'];
		$info['hour_start'] = $result->fields['hrs_avail_start'];
		$info['hour_end'] = $result->fields['hrs_avail_end'];

		$info['affiliation'] = $result->fields['org_id'];

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
	 * Retrieve a list of volunteers and some related information
	 *
	 * @param $proj_id (optional) - give a value to return volunteers only from this project
	 * @param $assigned (optional, default VM_SHOW_ALL_VOLUNTEERS) -
	 * 						VM_SHOW_ALL_VOLUNTEERS_ASSIGNED to return only assigned volunteers
	 * 						VM_SHOW_ALL_VOLUNTEERS_UNASSIGNED to return only unassigned volunteers
	 * 						VM_SHOW_ALL_VOLUNTEERS to return all volunteers
	 *
	 * @return an array, where each key is a volunteer's p_uuid and each value is the following array of information:
	 *	Array
     * (
     * 		'full_name'		=> the volunteer's full name
     *		'ids'			=> an array  of the volunteer's IDs, where each key is
     *							the full description for ID type and each value is the ID code
     *		'skills'		=> an array of skill codes => descriptions for the volunteer
     *		'date_start'	=> the volunteer's available start date
     *		'date_end'		=> the volunteer's available end date
     *		'projs'			=> an array of project IDs => volunteer's task for each project that the volunteer is assigned to
     *		'locations'		=> an array of the volunteer's location and its parents
     *		'affiliation'	=> the organization that the volunteer is affiliated with
     * )
	 */

	function getVolunteers($proj_id=null, $assigned=VM_SHOW_ALL_VOLUNTEERS)
	{
		if(is_null($proj_id))
		{
			if($assigned == VM_SHOW_ALL_VOLUNTEERS_ASSIGNED)
				$whereClause = " WHERE person_uuid.p_uuid IN (SELECT p_uuid FROM vm_proj_vol)";
			else if($assigned == VM_SHOW_ALL_VOLUNTEERS_UNASSIGNED)
				$whereClause = " WHERE person_uuid.p_uuid NOT IN (SELECT p_uuid FROM vm_proj_vol)";
			else
				$whereClause = "";
		}
		else
		{
			$whereClause = (" WHERE p_uuid IN (SELECT p_uuid FROM vm_proj_vol WHERE proj_id='$proj_id') ");
		}

		$q = 	"SELECT 	vm_vol_details.p_uuid, person_uuid.full_name, vm_proj_vol.proj_id, location_id, opt_id_type, serial, org_id, org_main.name org_name, option_description id_desc, date_avail_start, date_avail_end, task
				 FROM 		vm_vol_details LEFT JOIN person_uuid USING (p_uuid)
				 			LEFT JOIN vm_proj_vol USING (p_uuid)
							LEFT JOIN location_details ON (location_details.poc_uuid = person_uuid.p_uuid)
							LEFT JOIN identity_to_person USING(p_uuid)
							LEFT JOIN org_main ON (vm_vol_details.org_id = org_main.o_uuid)
							LEFT JOIN field_options ON (identity_to_person.opt_id_type = field_options.option_code) "
				. $whereClause;

		$result = $this->execute($q);

		// put all information into an array for returning

		$volunteers = array();
		while(!$result->EOF)
		{
			//first check to see if we already started this volunteer's information
			//if so, just update the volunteer's info with the info from this next row because
			//since we are doing so many joins, we may have more than one row returned per volunteer

			$p_uuid = $result->fields['p_uuid'];
			if(isset($volunteers[$p_uuid]))
			{
				//update the existing entry for the volunteer

				if($result->fields['proj_id'] != null)
					if(!in_array($result->fields['proj_id'], $volunteers[$p_uuid]['projs']))
						$volunteers[$p_uuid]['projs'][$result->fields['proj_id']] = $result->fields['task'];

				if($result->fields['serial'] != null)
					$volunteers[$p_uuid]['ids'][$result->fields['id_desc']] = $result->fields['serial'];

				if($result->fields['org_name'] != null)
					$volunteers[$p_uuid]['affiliation'] = $result->fields['org_name'];
			}
			else
			{
				//create a new entry in the array for the volunteer

				if(empty($result->fields['location_id']))
					$locations = array();
				else
					$locations = $this->getParentLocations($result->fields['location_id']);

				$volunteers[$result->fields['p_uuid']] = array
				(
					'full_name'		=> $result->fields['full_name'],
					'projs'			=> ($result->fields['proj_id']==null)?array():array($result->fields['proj_id'] => $result->fields['task']),
					'ids'			=> ($result->fields['serial']==null)?array():array($result->fields['id_desc'] => $result->fields['serial']),
					'locations'		=> $locations,
					'affiliation'	=> ($result->fields['org_name']==null)?'':$result->fields['org_name'],
					'skills'		=> $this->getSkillsAndDescriptions($result->fields['p_uuid']),
					'date_start'	=> $result->fields['date_avail_start'],
					'date_end'		=> $result->fields['date_avail_end']
				);
			}

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


			//Update a volunteers availability and organization affiliation
			$this->execute("update vm_vol_details SET date_avail_start= '{$v->info['date_start']}',date_avail_end='{$v->info['date_end']}' ,hrs_avail_start= '{$v->info['hour_start']}',hrs_avail_end= '{$v->info['hour_end']}', org_id='{$v->info['affiliation']}' WHERE p_uuid='".$v->p_uuid."'");

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
				$this->execute("INSERT INTO vm_vol_skills VALUES('{$v->p_uuid}', '$skill')");
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
				//create an account and give the user 'Registered User' privileges
				shn_auth_add_user($acct['account_name'], $acct['user_name'], $acct['pass'], REGISTERED, $v->p_uuid);
			}
			//add phonetic sound matching
			$names = preg_split("/\s+/", $v->info['full_name']);

            foreach($names as $single_name)
            {
                $this->execute("INSERT INTO phonetic_word VALUES('" . soundex($single_name) . "', '" . metaphone($single_name) . "', '{$v->p_uuid}')");

            }

			//insert the volunteer's full name
			$result = $this->db->execute("insert into person_uuid (p_uuid, full_name) values ('".$v->p_uuid."', '".$v->info['full_name']."')");

			//insert the volunteer's availibility and organization affiliation
			$this->execute("insert into vm_vol_details (p_uuid,date_avail_start,date_avail_end,hrs_avail_start,hrs_avail_end, org_id) values ('{$v->p_uuid}', '{$v->info['date_start']}', '{$v->info['date_end']}', '{$v->info['hour_start']}', '{$v->info['hour_end']}', '{$v->info['affiliation']}')");

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
				$this->execute("INSERT INTO vm_vol_skills VALUES('{$v->p_uuid}', '$skill')");
			}

			//insert the location information
			$specific_loc = $v->info['locations'][0];
	 		if($specific_loc != null && $specific_loc != -1)
	 			$this->execute("INSERT INTO location_details (poc_uuid, location_id) VALUES ('{$v->p_uuid}', '$specific_loc')");

 		}
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

 			$this->execute("INSERT INTO vm_projects (name, description,mgr_id,location_id,start_date,end_date) values ('{$p->info['name']}', '{$p->info['description']}', '{$p->info['mgr_id']}', $specific_loc, '{$p->info['start_date']}', '{$p->info['end_date']}')");
 			$result = $this->execute("SELECT LAST_INSERT_ID()");
 			$p->proj_id = $result->fields[0];

			if (!empty($p->info['skills'])) {
				foreach($p->info['skills'] as $skill)
				{
					$this->execute("INSERT INTO vm_proj_skills (p_uuid,opt_skill_code) VALUES('{$p->proj_id}', '$skill')");
				}
			}
 		}
 		else
 		{
 			//update existing project information

 			$specific_loc= $p->info['locations'][0];
 			if($specific_loc==-1 ||$specific_loc==="0" || $specific_loc===null)
 				$specific_loc= "null";
 			 else
 			 	$specific_loc="'".$specific_loc."'";

 			$result = $this->execute("UPDATE vm_projects SET name = '{$p->info['name']}', description = '{$p->info['description']}', mgr_id = '{$p->info['mgr_id']}', location_id = $specific_loc, start_date = '{$p->info['start_date']}', end_date = '{$p->info['end_date']}' WHERE proj_id = '{$p->proj_id}'");

 			//get rid of the old skills and insert the new

 			$this->execute("DELETE FROM vm_proj_skills WHERE p_uuid = '{$p->proj_id}'");

			if (!empty($p->info['skills']))  {
	 			foreach($p->info['skills'] as $skill)
				{
					$this->execute("INSERT INTO vm_proj_skills VALUES('{$p->proj_id}', '$skill')");
				}
			}
 		}
 	}

	/**
	 * Retrieve a list of project information
	 *
	 * @access public
	 * @param $p_uuid		- (optional) if specified, only return projects that this volunteer is working on (site managers are handled as well)
	 * @param $mgr			- (optional) if specified, $p_uuid is treated as site manager and only projects he is a site manager for will be returned; if $p_uuid
	 * 							is a site manager but this is false, it will also return any projects that the site manager may just be assigned to
	 * @return an array of project information arrays, where each key is the project ID and each value
	 * is an array with the following structure:
	 *
	 * 	Array
	 * 	(
	 * 		'name'			=> the name of the project
	 * 		'description'	=> the project's description
	 * 	)
	 */


 	function listProjects($p_uuid=null, $mgr=false)
 	{
 		//build the query

 		$query = "SELECT proj_id, name, description FROM vm_projects";
 		if(!is_null($p_uuid))
 		{
 			if($mgr)
 				$query .= " WHERE mgr_id = '$p_uuid'";
 			else
 				$query .= " WHERE proj_id IN (SELECT proj_id FROM vm_proj_vol WHERE p_uuid = '$p_uuid') OR proj_id IN (SELECT proj_id FROM vm_projects WHERE mgr_id ='$p_uuid')";
 		}
		//store the info

		$result = $this->execute($query);
		$projects = array();
		while(!$result->EOF)
		{
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
 	 * 		'mgr_id'			=> the p_uuid of the project's site manager
 	 * 		'location_id'	=> the 'loc_uuid' from the 'location' table of the most specific location
 	 * 							where the project takes place
 	 * 		'start_date'	=> the beginning date of the project
 	 * 		'end_date'		=> the end date of the project
 	 * 		'description'	=> a brief description of the project
 	 * )
 	 */

 	function getProject($proj_id) //
 	{
		$result = $this->execute("SELECT name, mgr_id, location_id, start_date, end_date, description FROM vm_projects WHERE proj_id = '$proj_id'");

		//Get rid of numerically-based indices
		$this->remove_keys($result->fields);

		return $result->fields;
 	}

 	/**
 	 * Retrieves a project's name
 	 *
 	 * @access public
 	 * @param $proj_id	- the ID of the project
 	 * @return the project's name
 	 */

 	function getProjectName($proj_id) //
 	{
		$result = $this->execute("SELECT name FROM vm_projects WHERE proj_id = '$proj_id'");
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

 	function volIsAssignedToProject($p_uuid, $proj_id=null) //
 	{
 		$query = "SELECT p_uuid FROM vm_proj_vol WHERE p_uuid = '$p_uuid' ";
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
		$this->execute("delete from vm_vol_details where p_uuid = '$id'");
		$this->execute("delete from person_uuid where p_uuid = '$id'");
		$this->execute("delete from location_details where poc_uuid = '$id'");
		$this->execute("delete from contact where pgoc_uuid = '$id'");
		$this->execute("delete from vm_vol_skills where p_uuid = '$id'");
		$this->execute("delete from identity_to_person where p_uuid = '$id'");
		$this->execute("delete from person_details where p_uuid = '$id'");
		$this->execute("delete from users where p_uuid = '$id'");
		$this->execute("delete from vm_mailbox where p_uuid = '$id'");
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
		$this->execute("delete from vm_proj_vol where p_uuid = '$p_uuid' AND proj_id = '$proj_id'");

		//send the volunteer a message from the site manager notifying them of the assignment
		$result = $this->execute("SELECT name, mgr_id FROM vm_projects WHERE proj_id = '$proj_id'");
		$this->sendMessage($_SESSION['user_id'], array($p_uuid), "You have been removed from {proj $p_id {$result->fields['name']}}. \n\n (This is an automated message)");
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
 		$this->execute("delete from vm_projects where proj_id = '$proj_id'");
 		$this->execute("DELETE FROM vm_proj_skills WHERE p_uuid = '$proj_id'");
 		$this->execute("DELETE FROM vm_proj_vol WHERE proj_id = '$proj_id'");
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
	 * @param $hide_mgr		- (optional) true to hide the apply for site manager and approve site manager skills
	 * @return the Tree object
	 */

	function getSelectSkillsTree($p_uuid=null, $vol=true, $any_skills=null, $hide_mgr=false)
	{
		//first get and store all of the volunteer's skills as an array if necessary

		if($p_uuid != null)
			$skills_array = $this->getVolSkillsArray($p_uuid, $vol);
		else if(is_array($any_skills))
			$skills_array = $any_skills;
		else
			$skills_array = array();

		if($hide_mgr)
			$extra_clause = " AND option_code <> 'MGR_APPLY' ";

	    //now query for all skills and store them in a Tree structure

		//if we are looking up a volunteer and he is not a site manager, exclude the approved site manager skill, otherwise also exclude the apply for a site manager skill

		if($vol && !in_array('MGR_APPROVED', $skills_array))
	    	$result = $this->execute("SELECT DISTINCT option_code, option_description FROM field_options WHERE field_name = 'opt_skill_type' AND option_code <> 'MGR_APPROVED' $extra_clause ORDER BY option_description");
	    else
	    	$result = $this->execute("SELECT DISTINCT option_code, option_description FROM field_options WHERE field_name = 'opt_skill_type' AND option_code <> 'MGR_APPROVED' AND option_code <> 'MGR_APPLY' ORDER BY option_description");

	    $tree = new Tree("?mod=vm&amp;stream=text&amp;act=display_js&amp;js=");
	    $tree->setRoot(new Node('Skills'));

	    while(!$result->EOF)
	    {
	        $split = preg_split('/'. VM_SKILLS_DELIMETER .'/', $result->fields['option_description']);
	        $cur_parent = $tree->root;

	        foreach($split as $index => $name)
	        {
	            if($index < (count($split) - 1))
	            {
	                $name = trim($name);
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

	        $result->MoveNext();
	    }

	    return $tree;
	}

	/**
	 * Retrieves all skills for a particular volunteer as an array
	 *
	 * @access public
	 * @param $p_uuid 	- the volunteer's p_uuid
	 * @param $vol		- true to return a set of volunteer's skills, false to return a set of
	 * 						project's required skills
	 * @return the array, where each key is numerically based and each value is the skill ID
	 */

	function getVolSkillsArray($p_uuid, $vol=true)
	{
		$skills_array = array();
		$table = $vol?'vm_vol_skills':'vm_proj_skills';
		$result = $this->execute("SELECT opt_skill_code FROM $table WHERE p_uuid = '$p_uuid'");

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

	function getVolSkillsTree($p_uuid, $vol=true)
	{
	    // query for all skills that belong to this volunteer

	    $table = $vol?'vm_vol_skills':'vm_proj_skills';

	    $result = $this->execute("SELECT option_description FROM field_options WHERE option_code IN
	    		                  (SELECT opt_skill_code FROM $table WHERE p_uuid = '$p_uuid')
	    		                  ORDER BY option_description");
	    $tree = new Tree("?mod=vm&amp;stream=text&amp;act=display_js&amp;js=");
	    $tree->setRoot(new Node('Skills'));

		// now store the skills in a Tree structure

	    while(!$result->EOF)
	    {
	        $split = preg_split('/'. VM_SKILLS_DELIMETER .'/', $result->fields['option_description']);
	        $cur_parent = $tree->root;

	        foreach($split as $index => $name)
	        {
                $name = trim($name);
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

	        $result->MoveNext();
	    }

	    return $tree;
	}


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
		} else {
			return false;
		}
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
	 * @return an associative array, where each key is the organization's o_uuid and each
	 * 			value is its corresponding name
	 */

	function getOrganizations()
	{
		$result = $this->execute("SELECT o_uuid, name FROM org_main");
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
	 * Checks to see if the given user is registered as a volunteer.
	 *
	 * @access public
	 * @param $p_uuid	- the user's p_uuid
	 * @return true if the user is a volunteer, false otherwise
	 */

	function isVolunteer($p_uuid) //
	{
		$result = $this->execute("SELECT p_uuid FROM vm_vol_details WHERE p_uuid = '$p_uuid'");
		return !$result->EOF;
	}

	/**
	 * Retrieves site managers
	 *
	 * @access public
	 * @param $type	 	VM_MGR_APPROVED		return only site managers that have been approved by an administrator to
	 * 										fulfill site management duties
	 * 					VM_MGR_UNAPPROVED	return only site managers that have not yet been approved
	 * @return an associative array where each key is a site manager's p_uuid and the corresponding value is an array with
	 * 			the following structure:
	 *
	 * 	Array
	 * 	(
	 * 		'name'		=> the site manager's name
	 * 		'approved'	=> true if already approved
	 * 	)
	 */

	function getSiteManagers($type=VM_MGR_APPROVED)
	{
		if($type == VM_MGR_APPROVED)
			$extra_clause = " AND opt_skill_code = 'MGR_APPROVED' ";
		else if($type == VM_MGR_UNAPPROVED)
			$extra_clause = " AND opt_skill_code = 'MGR_APPLY' ";
		else
			$extra_clause = " AND (opt_skill_code = 'MGR_APPROVED' OR opt_skill_code = 'MGR_APPLY')";

		$result = $this->execute(	"SELECT DISTINCT vm_vol_skills.p_uuid mgr_id, full_name, (SELECT DISTINCT 1 FROM vm_vol_skills WHERE p_uuid = mgr_id AND opt_skill_code = 'MGR_APPROVED') approved
									 FROM vm_vol_skills, person_uuid
									 WHERE vm_vol_skills.p_uuid = person_uuid.p_uuid
									 $extra_clause
									 ORDER BY approved DESC");

		$mgrs = array();
		while(!$result->EOF)
		{
			$mgrs[$result->fields['mgr_id']] = array('name' => $result->fields['full_name'], 'approved' => $result->fields['approved']==1);
			$result->moveNext();
		}
		return $mgrs;
	}

	/**
	 * Updates a volunteers's manager status
	 *
	 * @access public
	 * @param $p_uuid		- the p_uuid of the volunteer whose manager status to update
	 * @param $approved		- true to approve the manager status, false to deny it (or revoke it if they area already an approved manager)
	 * @return void
	 */
	function updateManagerStatus($p_uuid, $approved)
	{
		if($approved)
		{
			$this->execute("DELETE FROM vm_vol_skills WHERE p_uuid = '$p_uuid' AND opt_skill_code = 'MGR_APPLY'");
			$this->execute("INSERT INTO vm_vol_skills (p_uuid, opt_skill_code) VALUES ('$p_uuid', 'MGR_APPROVED')");
			$this->sendMessage($_SESSION['user_id'], array($p_uuid), "Your site manager status request has been approved. \n\n (This is an automated message)");
		}
		else
		{
			$result = $this->execute("SELECT 1 FROM vm_vol_skills WHERE p_uuid = '$p_uuid' AND opt_skill_code = 'MGR_APPROVED'");
			$previously_approved = !$result->EOF;	//true if we must revoke the site manager status from an existing manager, false if we must deny it to a volunteer who has applied for it
			$this->execute("DELETE FROM vm_vol_skills WHERE p_uuid = '$p_uuid' AND (opt_skill_code = 'MGR_APPLY' OR opt_skill_code = 'MGR_APPROVED')");

			if($previously_approved)
				$this->sendMessage($_SESSION['user_id'], array($p_uuid), "Your site manager status has been revoked. \n\n (This is an automated message)");
			else
				$this->sendMessage($_SESSION['user_id'], array($p_uuid), "Your site manager status request has been denied. \n\n (This is an automated message)");
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
 	 	if($inbox)
 			$result = $this->execute("SELECT from_id, vm_message.message_id, time, message, checked FROM vm_message, vm_courier, vm_mailbox WHERE p_uuid = '$p_uuid' AND box = 0 AND to_id = '$p_uuid' AND vm_message.message_id = vm_courier.message_id AND vm_message.message_id = vm_mailbox.message_id ORDER BY time DESC");
		else
			$result = $this->execute("SELECT vm_message.message_id, time, message, checked FROM vm_message, vm_courier, vm_mailbox WHERE p_uuid = '$p_uuid' AND box = 1 AND from_id = '$p_uuid' AND vm_message.message_id = vm_courier.message_id AND vm_message.message_id = vm_mailbox.message_id GROUP BY vm_message.message_id ORDER BY time DESC");

 		$messages = array();
 		while(!$result->EOF)
 		{
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

			$result = $this->execute("SELECT from_id, to_id, vm_message.message_id, time, message, checked FROM vm_message, vm_courier, vm_mailbox WHERE p_uuid = '$p_uuid' AND box=$box_num AND vm_message.message_id = vm_courier.message_id AND vm_message.message_id = vm_mailbox.message_id AND vm_message.message_id = $message_id");
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
 	     * @return an array where each key is a p_uuid of a volunteer and each value is an array with the following structure:
 	     *
 	     * Array
 	     * (
 	     * 		'full_name'		=> the volunteer's full name
 	     *		'ids'			=> an array  of the volunteer's IDs, where each key is
 	     *							the abbreviation for an ID type and each value is the ID code
 	     *		'skills'		=> an array of skill codes => descriptions for the volunteer
 	     *		'date_start'	=> the volunteer's available start date
 	     *		'date_end'		=> the volunteer's available end date
 	     *		'locations'		=> an array of the volunteer's location and its parents where each key is a location id and each value is the location name
 	     *		'projs'			=> an array of project ID => task for each project that the volunteer is assigned to
 	     *		'affiliation'	=> the organization that the volunteer is affiliated with
 	     *		'id_searched'	=> the Id number searched for, nice to have when displaying to highlight the searched-for substring
 	     *		'levenshtein'	=> the levenshtein distance between the name searched for and this
 	     *							volunteer's full name
 	     * )
 	     *
 	     * The search results are ordered by increasing levenshtein distance.
 	     */

 	    function getVolSearchResults($id, $name, $skills, $skills_matching, $start_date, $end_date, $location, $date_constraint, $unassigned=false, $loose=false, $assigning_proj=null)
 	    {
 	    	$name_set = $name != '';
 	    	$id_set = $id != '';
 	    	$date_set = $start_date != '';
 	    	$skills_set = count($skills) > 0;
 	    	$location_set = $location != '';

 	    	$query = 	"SELECT 	vm_vol_details.p_uuid, person_uuid.full_name, vm_proj_vol.proj_id, location_id, opt_id_type, serial, org_id, org_main.name org_name, option_description id_desc, date_avail_start, date_avail_end, task
				 		 FROM 		vm_vol_details
				 		 			LEFT JOIN person_uuid USING (p_uuid)
						 			LEFT JOIN vm_proj_vol USING (p_uuid)
									LEFT JOIN location_details ON (location_details.poc_uuid = person_uuid.p_uuid)
									LEFT JOIN identity_to_person USING(p_uuid)
									LEFT JOIN org_main ON (vm_vol_details.org_id = org_main.o_uuid)
									LEFT JOIN field_options ON (identity_to_person.opt_id_type = field_options.option_code) ";

			//generate the FROM clause

			if($name_set)
				$query .= " JOIN phonetic_word ON (person_uuid.p_uuid = phonetic_word.pgl_uuid) ";

			//generate the WHERE clause

			$where_said = false;	//will be true once we write the first "WHERE" clause, so we know when to start saying "AND"

			//search by name

			if($name_set)
			{
				if($where_said)
					$query .= " AND ";
				else
				{
					$query .= " WHERE ";
					$where_said=true;
				}

				$query .= $this->generateSelectPhoneticClauses($name, $loose);
			}

			//search by IDs

			if($id_set)
			{
				if($where_said)
					$query .= " AND ";
				else
				{
					$query .= " WHERE ";
					$where_said=true;
				}

				$query .= " serial LIKE '%{$id}%' ";
			}

			//search by skills

			if($skills_set)
			{
				if($where_said)
					$query .= " AND ";
				else
				{
					$query .= " WHERE ";
					$where_said=true;
				}

				$skills_set_search = " (";
				foreach($skills as $skill_id)
				{
					$skills_set_search .= "'$skill_id', ";
				}
				$skills_set_search = substr($skills_set_search, 0, strlen($skills_set_search) - 2);
				$skills_set_search .= ') ';

				$query .= "(
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
				if($where_said)
					$query .= " AND ";
				else
				{
					$query .= " WHERE ";
					$where_said=true;
				}

				if($date_constraint)
				{
					//volunteer must be available for entire date range specified
					$query .= " date_avail_start<='$start_date' AND date_avail_end>='$end_date' ";
				}
				else
				{
					if($end_date == '')
					{
						//volunteer must be available for any time after the start date specified
						$query .= " date_avail_end>='$start_date' AND date_avail_start<='$start_date'";
					}
					else
					{
						//volunteer must be available for any portion of time between the dates specified
						$query .= " date_avail_start<='$end_date' AND date_avail_end>='$start_date' ";
					}
				}
			}

			//get only unassigned

			if($unassigned)
			{
				if($where_said)
					$query .= " AND ";
				else
				{
					$query .= " WHERE ";
					$where_said=true;
				}

				$query .= " person_uuid.p_uuid NOT IN (SELECT DISTINCT p_uuid FROM vm_proj_vol) ";
			}

			//if we are assigning to a project, exclude results from the project we are assigning to

			if($assigning_proj != null)
			{
				if($where_said)
					$query .= " AND ";
				else
				{
					$query .= " WHERE ";
					$where_said=true;
				}

				$query .= " person_uuid.p_uuid NOT IN (SELECT p_uuid FROM vm_proj_vol WHERE proj_id = '$assigning_proj') AND person_uuid.p_uuid != (SELECT mgr_id FROM vm_projects WHERE proj_id = '$assigning_proj') ";
			}

		    //get the results and format them into the resulting array

			$result = $this->execute($query);
			$search_results = array();

			while(!$result->EOF)
			{
				//first check to see if there already is an entry in the array (since we are doing so many joins, more than one row may be returned per volunteer)
				$p_uuid = $result->fields['p_uuid'];

				if(isset($search_results[$p_uuid]))
				{
					//update existing information for this entry

					if($result->fields['proj_id'] != null)
					if(!in_array($result->fields['proj_id'], $search_results[$p_uuid]['projs']))
						$search_results[$p_uuid]['projs'][$result->fields['proj_id']] = $result->fields['task'];

					if($result->fields['serial'] != null)
						$search_results[$p_uuid]['ids'][$result->fields['id_desc']] = $result->fields['serial'];

					if($result->fields['org_name'] != null)
						$search_results[$p_uuid]['affiliation'] = $result->fields['org_name'];
				}
				else
				{
					//create a new entry for the volunteer in the $search_results array

					//first, have to do refinement of results by location manually due to its recursive nature
					//if we are searching by location and the location to search by is not in the resulting volunteer's
					//location hierarchy, exclude him from the results

					$move_on = true;

					$location_tree = $this->getParentLocations($result->fields['location_id']);
					if($location_set)
					{
						if(!in_array($location, array_keys($location_tree)))
							$move_on = false;
					}

					if($move_on)
					{
						$search_results[$p_uuid] = array
						(
							'full_name' 	=> $result->fields['full_name'],
							'projs'			=> ($result->fields['proj_id']==null)?array():array($result->fields['proj_id'] => $result->fields['task']),
							'ids'			=> ($result->fields['serial']==null)?array():array($result->fields['id_desc'] => $result->fields['serial']),
							'date_start' 	=> $result->fields['date_avail_start'],
							'date_end' 		=> $result->fields['date_avail_end'],
							'locations' 	=> $location_tree,
							'skills' 		=> $this->getSkillsAndDescriptions($result->fields['p_uuid']),
							'affiliation'	=> $result->fields['org_name'],
							'id_searched' 	=> $id
						);

						$levenshtein = 0;

		            	if($name_set)
		                	$levenshtein = levenshtein(strtoupper($result->fields['full_name']), strtoupper($name));

						$search_results[$p_uuid]['levenshtein'] = $levenshtein;
					}
				}

				$result->MoveNext();
			}

			/*
	         * Sort the resulting array by levenshtein distance. To change the acceptable levenshtein distance
	         * between the inputted name and resulting names, modify SHN_VM_MAX_LEVENSHTEIN in the Constants.php file.
	         */

	        if($name_set)
	        {
	        	//bucket sort

		        $buckets = array();
	            foreach($search_results as $p_uuid => $info)
	            {
	            	if(isset($buckets[$info['levenshtein']]))
	            		$buckets[$info['levenshtein']][$p_uuid] = $info;
	            	else
	            		$buckets[$info['levenshtein']] = array($p_uuid => $info);
	            }

	            $sorted_results = array();
	            for($i = 0; $i < VM_MAX_LEVENSHTEIN; $i++)
	            {
	            	if(isset($buckets[$i]))
		            	foreach($buckets[$i] as $p_uuid => $info)
		            		$sorted_results[$p_uuid] = $info;
	            }

		        return $sorted_results;
	        }
	        else
	        {
	        	return $search_results;
	        }

 	    }

 	    /**
		 * Update the 'phonetic_word' table with volunteer phonetic word information. This is
		 * included in case someone's name changes outside the VM module.
		 *
		 * @return void
		 */

		function updatePhonetics()
		{
		    $result = $this->execute("SELECT p_uuid, full_name FROM person_uuid WHERE p_uuid IN (SELECT p_uuid FROM vm_vol_details)");

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
		 * @param $task		- the volunteer's task in this project
		 * @return void
		 */

		function assignToProject ($vol_id, $p_id, $task)
		{
			$this->execute("INSERT INTO vm_proj_vol (p_uuid,proj_id, task) values('$vol_id', '$p_id', '$task') ");

			//send the volunteer a message from the site manager notifying them of the assignment
			$result = $this->execute("SELECT name, mgr_id FROM vm_projects WHERE proj_id = '$p_id'");
			$this->sendMessage($result->fields['mgr_id'], array($vol_id), "You have been assigned to {proj $p_id {$result->fields['name']}}. \n\n (This is an automated message)");
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
										 FROM 		vm_vol_skills
										 WHERE 		opt_skill_code = 'MGR_APPROVED' AND p_uuid = '$p_uuid'");
			return !$result->EOF;
		}

		function getVMPicture($img_uuid) {
			$result = $this->execute("select image_data, thumb_data, p_uuid, width, height, thumb_width, thumb_height, mime_type, name from vm_image where img_uuid = '$img_uuid'");
			if($result->EOF)
				return false;
			else {
				$this->remove_keys($result->fields, MYSQL_ASSOC);
				return $result->fields;
			}
		}

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

			if($result == null)
				return false;
			else
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

				$result->MoveNext();
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

		function getSkillsAndDescriptions($id, $proj=false)
		{
			if($proj)
				$result = $this->execute("select opt_skill_code, option_description from vm_proj_skills, field_options where p_uuid = '{$id}' AND opt_skill_code = option_code order by option_description asc");
			else
				$result = $this->execute("select opt_skill_code, option_description from vm_vol_skills, field_options where p_uuid = '{$id}' AND opt_skill_code = option_code order by option_description asc");

			$options = array();

			while(!$result==NULL && !$result->EOF)
			{
			      $options[$result->fields['opt_skill_code']] = $result->fields['option_description'];
			      $result->MoveNext();
			}

			return $options;
		}

		/**
		 * Retrieves the task a volunteer is assigned to for a specific project
		 *
		 * @param $p_uuid	- the volunteer's p_uuid
		 * @param $proj_id	- the project to look up
		 * @return the volunteer's task
		 */
		function getVolTask($p_uuid, $proj_id)
		{
			$result = $this->execute("SELECT task FROM vm_proj_vol WHERE p_uuid = '$p_uuid' AND proj_id = '$proj_id'");

			if($result->EOF)
				return null;
			else
				return $result->fields['task'];
		}

		/**
		 * Updates a volunteer's task for a specific project
		 *
		 * @param $p_uuid	- the volunteer's p_uuid
		 * @param $proj_id	- the project to look up
		 * @param $task		- the task to set
		 */
		function setVolTask($p_uuid, $proj_id, $task)
		{
			$this->execute("UPDATE vm_proj_vol SET task = '$task' WHERE p_uuid = '$p_uuid' AND proj_id = '$proj_id'");
		}

}



?>