<?php
/* $Id: utility_functions.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- utility functions.
 *
 * <p>This file is part of the Volunteer Management module. It includes utility 
 * functions used in various source files. It should be included in most VM source files.</p>
 *
 * @package    Trinity_College_vm_demo
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 *
 */

/**
 * Retrieves the id number of the site manager for a given project.
 * 
 * Performs a DB query of the <b>vm_projects</b> table given the project's id.
 *
 * @param string  $project_id The project being queried.
 * @access public
 * @return string
 */
//error_reporting(E_ALL);

function get_manager_id($project_id) {
    global $global;
    $db=$global['db'];
    $q="select mgr_id from vm_projects where proj_id='{$project_id}'";
    $res_mgr=$db->Execute($q);
    return $res_mgr->fields[0];
} // get_manager_id()

/**
 * Retrieves the site manager's name for a given project.
 * 
 * Performs a DB query of the <b>person_uuid</b> table given the project's id.
 *
 * @param string  $project_id The project being queried.
 * @access public
 * @return string The site manager's name for a given project.
 */
function get_manager_name($project_id) {
    global $global;
    $db=$global['db'];
    $mgr_id=get_manager_id($project_id);
    $q="select p_uuid,full_name from person_uuid where p_uuid='{$mgr_id}'";
    $mgr_id=$db->Execute($q);
    $manager=$mgr_id->fields[1];
    return ucfirst($manager);
} // get_manager_name()


/**
 * Returns a list of skills needed for a given project.
 * 
 * Performs a DB query of the <b>vm_proj_skills</b> table given the project's id.
 *
 * @param string  $project_id The project being queried.
 * @access public
 * @return string A string of skills delimited by <BR> tags or the empty string.
 */
function get_project_skills_list($project_id) {
  global $global;
  $db=$global['db'];
  $skills="";
  $q = "select opt_skill_code from vm_proj_skills where p_uuid='{$project_id}'";
  $skill_opts_list=$db->Execute($q);
  while(!$skill_opts_list==NULL && !$skill_opts_list->EOF){
    $q = "select option_description,option_code from field_options where option_code='{$skill_opts_list->fields[0]}'";
    $skill_descriptions=$db->Execute($q);
    $skills=$skills . ucfirst($skill_descriptions->fields[0]) . "<BR>";
    $skill_opts_list->MoveNext();
  } // while
  if ($skills=="")
    $skills="N/A";
  return $skills;
} // get_project_skills_list()

/**
 * Returns a person's named geographical location given the person's id.
 * 
 * Performs a DB query of the <b>location_details</b> and <b>location</b> tables given the 
 * person's id.
 *
 * @param string  $person_id The person being located.
 * @access public
 * @return string A string giving the name of the person's location (e.g., Hartford, CT).
 */
function get_personal_location_string($person_id) {
  global $global;
  $db=$global['db'];
  $q="select poc_uuid, location_id  from location_details where poc_uuid='{$person_id}'";   
  $res_location=$db->Execute($q);
  $q="select loc_uuid,name,iso_code from location where loc_uuid='{$res_location->fields[1]}'";   
  $res_location=$db->Execute($q);
  if ($res_location->fields[0] == NULL)
    return "";
  else
    return substr($res_location->fields[1],0,strpos($res_location->fields[1],"-")-1) . ", " . $res_location->fields[2];
} // get_personal_location_string()

/**
 * Returns a project's geographical location given its id.
 *
 * Performs a DB query of the tables <b>vm_projects</b> and <b>location</b>
 * given the project id.  It returns a conjunction of location_details and location
 * in a string of the form "Hartford, CT".
 *
 * @param string  $project_id The project being queried.
 * @access public
 * @return string The name of the project's location 
 */
function get_project_location_string($project_id) {
  global $global;
  $db=$global['db'];
  $q="select location_id, proj_id  from vm_projects where proj_id='{$project_id}'";   
  $res_location=$db->Execute($q);
  $q="select loc_uuid,name,iso_code from location where loc_uuid='{$res_location->fields[0]}'";   
  $res_location=$db->Execute($q);
  if ($res_location->fields[0] == NULL)
    return "";
  else
    return substr($res_location->fields[1],0,strpos($res_location->fields[1],"-")-1) . ", " . $res_location->fields[2];
} // get_project_location_string()

/**
 * Counts the number of entries in a given table.
 * 
 * Performs a DB query with db_table provided as a parameter.  
 * Returns the number of entries in the table as an integer.   
 *
 * @param string  $db_table
 * @access public
 * @return integer The number of entries in a given table.   
 */

function count_entries($db_table){
  global $global;                      
  $db=$global["db"];                               
  $q="select count(*) from $db_table";   
  $res=$db->Execute($q);
  if(!$res->EOF) 
    $proj_no=($res->fields[0]);                   
  else
    $proj_no=0;                   
  return $proj_no;
}

/**
 * Counts the number of volunteers associated with a project.  
 *
 * Performs a DB query of the tables <b>vm_proj_vol</b> and <b>vm_vol_details</b> 
 * given the project's id, the volunteer's status, and the volunteer's organization's id.  
 * If $status=NULL, then all volunteers are counted, regardless of status.  
 * If $status=onhold or some other valid value, then just a count of those volunteers is returned.
 * 
 * @param string $project_id_param  The project being queried.  
 * @param string $status  Status is either working, assigned, or on hold.  
 * @param string $org_id The organization with which the volunteer is associated.
 * @access public
 * @return integer The number of volunteers associated with a given project
 */
function get_volunteer_count($project_id_param=NULL, $status=NULL, $org_id=NULL){
  global $global;
  $db=$global['db'];
  
  $q="select count(*) from vm_proj_vol, vm_vol_details where vm_proj_vol.p_uuid = vm_vol_details.p_uuid";   
   if($project_id_param!=NULL)
  	$q= $q . " and proj_id='{$project_id_param}'";
   if($status!=NULL)
  	$q= $q . " and status='{$status}'";
   if($org_id!=NULL)
  	$q= $q . " and org_id='{$org_id}'";
  $vols_count=$db->Execute($q);
  return $vols_count->fields[0];
} // get_volunteer_count()

/**
 * Returns a string with contact information for a volunteer.
 * 
 * Performs a DB query of the table <b>location_details</b> or <b>contact</b>
 * given the contact_type and/or person_id.  If contact_type is 'addr', then
 * the volunteer's address is returned.  If not, then at least one 
 * contact type is returned.  The codes for contact types are as follows:
 * curr=phone, cur=address, fax=fax number, email= email address.
 *
 * @param string $person_id  The id of the volunteer whose contact information is needed. 
 * @param string $contact_type The contact info for the volunteer  
 * @access public
 * @return string The contact information associated with a given volunteer.
 */
function get_contact_info($person_id, $contact_type) {
  global $global;
  $db=$global['db'];
  if ($contact_type=='addr')
    $q="select address from location_details where poc_uuid='{$person_id}'";   
  else
    $q="select contact_value from contact where pgoc_uuid='{$person_id}' and opt_contact_type='{$contact_type}'";   
  $contact_list=$db->Execute($q);
  $contact_string="";
  while(!$contact_list==NULL && !$contact_list->EOF) {
    $contact_string = $contact_string . $contact_list->fields[0] . "<BR>" ;
    $contact_list->MoveNext();
  } // while
  return $contact_string;  
} // get_contact_info()

/**
 * Returns the organization with which a given volunteer
 * is affiliated.  
 *
 * Performs a DB query of <b>vm_vol_details</b> given 
 * the person's id.  It returns the name of the organization with which 
 * the volunteer is associated as a string.     
 *
 * @param string $person_id  The id of the person whose affiliation is needed
 * @access public
 * @return string The volunteer's organization.
 */
function get_volunteer_affiliation($person_id)  {
  global $global;
  $db=$global['db'];
  $q="select org_id from vm_vol_details where p_uuid='{$person_id}'";   
  $result_org=$db->Execute($q);
  $org_id=$result_org->fields[0];
  $q="select name from org_main where o_uuid='{$org_id}'";   
  $result_org=$db->Execute($q);
  $org_name=$result_org->fields[0];
  if ($org_name=="")
    $org_name="N/A";
  return $org_name;
}

/**
 *  Returns either the starting or ending date, or starting or ending time
 *  of a volunteer's availability, depending on the settings of his/her
 *  parameters. 
 * 
 *  Performs a DB query of <b>vm_vol_details</b> given the person's id.  
 *  Depending on the settings of the volunteer's parameters, either the 
 *  starting or ending date, or starting or ending time will be returned.
 *
 *  @param string $person_id  The id of the person whose availability is needed.
 *  @param string $date
 *  @param string $start
 *  @access public
 *  @return string Either the volunteer's starting or ending date, or 
 *  starting or ending time.  
 */
function get_volunteer_availability_date_time($person_id, $date=true, $start=true)  {
  global $global;
  $db=$global['db'];
  if ($date) {                    // Handle starting or ending date
    if ($start) 
      $q="select date_avail_start from vm_vol_details where p_uuid='{$person_id}'";   
      else
	$q="select date_avail_end from vm_vol_details where p_uuid='{$person_id}'";   
  }      
  else {                        // Handle starting or ending time
    if ($start) 
      $q="select hrs_avail_start from vm_vol_details where p_uuid='{$person_id}'";   
    else
      $q="select hrs_avail_end from vm_vol_details where p_uuid='{$person_id}'";   
  }
  $result_date=$db->Execute($q);
  $date_or_time=$result_date->fields[0];
  return $date_or_time;
}

/**
 *  Returns a list of skills associated with a
 *  particular volunteer.
 *
 *  Performs a DB query of <b>vm_vol_skills</b> where person_id
 *  is given as a parameter.  It returns a string of skills delimited 
 *  by <BR> tags or the empty string.  If the volunteer has no skills,
 *  an "N/A" is outputted.
 * 
 *  @param string $person_id  The id of the person whose skills are queried.
 *  @access public
 *  @return string Skills associated with a given volunteer.
 */
function get_volunteer_specialties($person_id) {
  global $global;
  $db=$global['db'];
  $skills="";
  $q = "select opt_skill_code from vm_vol_skills where p_uuid='{$person_id}'";
  $skill_opts_list=$db->Execute($q);
  while(!$skill_opts_list==NULL && !$skill_opts_list->EOF){
    $q = "select option_description,option_code from field_options where option_code='{$skill_opts_list->fields[0]}'";
    $skill_descriptions=$db->Execute($q);
    $skills=$skills . "<BR>" . ucfirst($skill_descriptions->fields[0]);
    $skill_opts_list->MoveNext();
  } // while
  if ($skills=="")
    $skills="N/A";
  return $skills;
} // get_volunteer_specialties()

/**
 *  Returns the equivalent dollar value of each volunteer's
 *  activity for a given project.
 * 
 *  Performs a DB query of <b>vm_proj_vol</b> and <b>vm_vol_details</b> 
 *  where project_id is given as a parameter.  For a given project, each volunteer's 
 *  dollar value contribution is evaluated by the formula:
 *  (payrate * hours) where payrate is what they would 
 *  receive if they weren't volunteering, and hours is the number of hours they 
 *  have volunteered on the project.  
 *  
 *  @param string $project_id  The id of the project for which dollar value contribution is being evaluated.  
 *  @param string $org_id  The organization with which a volunteer is affiliated.
 *  @access public
 *  @return integer For a specific project, each volunteer's dollar value contribution.  
 */
function get_project_dollar_total($project_id, $org_id=NULL) {
  global $global;
  $db=$global['db'];
  $q = "select payrate, hours from vm_proj_vol,vm_vol_details where proj_id='{$project_id}' and vm_proj_vol.p_uuid = vm_vol_details.p_uuid";
  if($org_id!=NULL)
  	$q = $q . " and org_id = '{$org_id}'";
  $total = 0;
  $res_proj=$db->Execute($q);
  while(!$res_proj==NULL && !$res_proj->EOF){
    $payrate = $res_proj->fields[0];
    $hours = $res_proj->fields[1];
    $total = $total + ($payrate * $hours);
    $res_proj->MoveNext();
  } // while

  return $total;
} // get_project_dollar_total()

/**
 *  Returns the sum total of all hours for every
 *  volunteer on a specific project
 *
 *  Peforms a DB query of <b>vm_proj_vol</b> with 
 *  project_id given as a parameter. So for a specific project,
 *  the sum total of hours worked on it is returned.
 *
 *  @param string $project_id  The id of the project for which total hour contribution is being evaluated.
 *  @access public
 *  @return integer The number of hours worked.  
 */
function get_project_hours($project_id) {
  global $global;
  $db=$global['db'];
  $q = "select sum(hours) from vm_proj_vol where proj_id='{$project_id}'";
  $result=$db->Execute($q);
  $hours = $result->fields[0];
  return $hours;
} // get_project_hours()

/**
 *  Returns the skill description (e.g. electrician) for a
 *  particular skill code (e.g. ELE1).
 *
 *  Performs a DB query of <b>field_options</b> where 
 *  skill_code is given as a parameter.  The skill description (e.g. electrician)
 *  corresponding to a particular skill code (e.g. ELE1) is returned.
 *
 *  @param string $skill_code  The code associated with a particular skill
 *  @access public
 *  @return string The description associated with a particular skill code.
 */
function get_skill_description($skill_code) {
  global $global;
  $db=$global['db'];
  $q = "select option_description from field_options where field_name = 'opt_skill_type' and option_code ='{$skill_code}'";
  $result=$db->Execute($q);
  $skill_description=$result->fields[0];
  return $skill_description;
} // get_skill_description()

/**
 * Returns the name of an organization by ID.
 *  
 * Performs a query of <b>org_main</b> where org_id
 * is provided as a parameter.  It returns the name of an 
 * organization as a string.
 *
 * @param string $org_id  The id of the organization.
 * @access public
 * @return string The name of the organization.
 */
function get_org_name($org_id) {
  global $global;
  $db=$global['db'];
  $q = "select name from org_main where o_uuid ='{$org_id}'";
  $result=$db->Execute($q);
  $org_name=$result->fields[0];
  return $org_name;
} // get_org_name()

/**
 * Returns the ID for a new project.
 *  
 * Performs a DB query of <b>vm_projects</b>.  The 
 * highest project id to date is incremented by 1 and 
 * is then returned as the next project id.  
 *
 * @param string $no
 * @access public
 * @return integer The id for a new project.  
 */
function get_next_project_id($no=NULL) {
  global $global;
  $db=$global['db'];
 	$q = "select max(proj_id) from vm_projects";
	$proj_num=$db->Execute($q);
	$id=$proj_num->fields[0];
	$id=$id + 1;
	return $id;
 } // get_next_project_id()

/**
 * Returns the ID for the logged in user
 *  
 * Performs a DB query of <b>users</b>.  The 
 * username is returned by $_SESSION.  
 *
 * @param string $no
 * @access public
 * @return integer The id for current logged in user.  
 */
function get_current_user_id($no=NULL) {
  global $global;
  global $conf;
  $db=$global['db'];
  if($_SESSION['logged_in'] == true){
	$q="select p_uuid from users where user_name='{$_SESSION['user']}'";
	$res=$db->Execute($q);
	$p_uuid=$res->fields[0];
  	return $p_uuid;
  }else{
	return 0;
  }
} // get_current_user_id()

/**
 * Displays POST data when a form is submitted.
 *
 * Post data for a form is stored in the $_POST variable,
 * which is meant to be passed as the parameter to this 
 * function. The function is recursive.
 *
 * @param array $post represents the POST data.
 * @access public
 * @return void
 * @author PHP Freaks
 * @link http://www.phpfreaks.com/tutorials/134/4.php 
 */
function dbgpost($post) {
  foreach($post as $key => $value) {
    if (is_array($value)) {
      echo "--$key (array)---start--<br />";
      dbgpost($value);
      echo "--$key (array)---end----<br />";
    } else {
      echo "$key: $value <br>";
    }
  }
} // dbgpost()

?>

