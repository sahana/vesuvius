<?php
/* $Id: [sahana_home]/mod/vm/vol_assign.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- assign a volunteer to a project.
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates the volunteer assignment page.  It has 
 *  two main components: a "Project Selection" and "Project Details" 
 *  section, and an "Assign Unassigned Volunteers" section.  Once 
 *  a search query is entered into the "Project Selection" section, 
 *  corresponding data is posted in "Project Details" and the
 *  "Assign Unassigned Volunteers" section.  The user may then  
 *  assign unassigned volunteers to the selected project. </p>
 *
 *  <p>The page displayed by this file contains several form elements all of which
 *  are processed by this page.</p>
 *
 *  <p>Suggestions for further development: 
 *  Put checkboxes instead of buttons next to each 
 *  volunteer's profile.  Put a "Submit" button at
 *  the bottom of the page which posts into the database
 *  the data of the volunteers who have been selcted.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 *
 */

/**
 * Manages the volunteer assignment task.
 * 
 * The volunteer assignment task enables a volunteer administrator
 * to assign a registered but currently unassigned volunteer to
 * an existing project.  The form provides drop-down boxes for
 * a project (required) and organization (optional). Once a project
 * is selected details about the project are displayed and a list
 * of currently unassigned volunteers is presented. The user can
 * then assign one or more volunteers to the project by using
 * drop-down boxes to assign the volunteer a task from among the tasks
 * for which the volunteer is available and qualified.
 * The function performs a DB insertion on the table <b>vm_proj_vol</b>.
 * 
 * @param boolean $errors Set to true if an error has occurred. Currently ignored.
 * @access public
 * @return void
 */
function _shn_vm_vol_assign($error=false) {
  global $global;
  $db=$global['db'];
  /** Contains library functions for creating forms. */
  include_once $global['approot']."/inc/lib_form.inc";
  /** Contains utility functions for the VM and VR modules. */
  include_once $global['approot']."/mod/vm/utility_functions.inc";
  /** Contains local library functions for creating forms in VM and VR modules. */
  include_once $global['approot']."/mod/vm/lib_vm.inc";

  // Get the POST data if 'Submit' was clicked
  if(NULL != $_POST['organization']) {
    $org_id = $_POST['organization'];
    $proj_id = $_POST['project'];
    $search_string = $_POST['search_string'];
  } else {
    $org_id = 0;
    $proj_id = 1;
    $search_string = NULL;
  }
  //  dbgpost($_POST);   // Displays post data

  // Search through $_POST for task postings.
  foreach($_POST as $key => $value) {
    if (strpos($key, "_vol#")) {   // If a volunteer is being assigned, a key will have the form: 'task_vol#' . $person_id;
      $pid = substr($key,9);
      //      echo "Insert volunteer " . $pid . " into project " . $proj_id;
      $q = "select p_uuid from vm_proj_vol where p_uuid='{$pid}'"; 
      $result = $db->Execute($q);
      if ($result->fields[0] == NULL) {  //  if the volunteer is not already in the DB 
      	$q = "insert into vm_proj_vol (p_uuid, proj_id, status, payrate, hours, opt_skill_type) 
                             VALUES ('{$pid}', '{$proj_id}', 'assigned', '10',  '0',  '{$value}')";
      	$db->Execute($q);
      
      	//  insert a message from the volunteer coordinator to the volunteer
      	$q = "select name from vm_projects where proj_id='{$proj_id}'";
      	$result = $db->Execute($q);
      	$name = $result->fields[0];
      	$current_user = get_current_user_id();
      	$q = "select max(message_id) from vm_messages";
      	$result = $db->Execute($q);
        $message_id = $result->fields[0] + 1;      
      	$q = "insert into vm_courier (message_id, to_id, from_id) 
      			     VALUES ('{$message_id}', '{$pid}', '{$current_user}')";
      	$db->Execute($q);
      	$q = "insert into vm_messages (message_id, message)
      			     VALUES ('{$message_id}', 'You have been assigned to the project titled {$name}')";
      	$db->Execute($q);
      } // if 
    }  // if
  }  // foreach
?>

<h2><?=_("Assign Volunteers to a Project")?> </h2><br>

<?php 
   // This subsection of the form enables the user to select a project and optionally an organization.

  shn_form_fopen($actiont="vol_assign");                // Opens a <form> element
  shn_form_fsopen($label='Project/Volunteer Selection');         // Open a subsection 
  $extra_opts['req']=true;
  _shn_form_select_project($error, $value_selected=NULL, $label="Choose a Project : ", $select_opts=NULL, $extra_opts);
  $extra_opts['req']=false;
  $extra_opts['all_org']=true;
  _shn_form_select_organization($error, $value_selected=$org_id, $label="Filter by Organization : ", $select_opts=NULL, $extra_opts);
  shn_form_text(_("Search Name (optional) : "),"search_string",'size="30"',array('req'=>false));
  shn_form_submit($name="Search");
  shn_form_fsclose();                          // Close the subsection
     
  // DB Query: Query the vm_projects and person_uuid tables for information about the selected project.

  $subtitle = "Project Details";
  if (!$proj_id == NULL) {
    $q = "select name, start_date, end_date, description from vm_projects where proj_id='{$proj_id}'";
    $result = $db->Execute($q);
    $name = $result->fields[0];
    $start = $result->fields[1];
    $end = $result->fields[2];
    $desc = $result->fields[3];
    $q = "select full_name from person_uuid, vm_projects where mgr_id=p_uuid and proj_id='{$proj_id}'";
    $res_mgr = $db->Execute($q);
    $mgr = $res_mgr->fields[0];
    $vols_assigned= get_volunteer_count($proj_id);
    $subtitle = $subtitle . ": $name";
  }

  // This subsection of the form displays details about the selected project.

  shn_form_fsopen($subtitle);
  $extra_opts['req']=true;
  $project_skills = get_project_skills_list($proj_id);
  $project_location = get_project_location_string($proj_id);
?>
    <div id="result">
	<table width="100%" align=center>
        <thead>
            <td><?=_("Start Date")?></td>
            <td><?=_("End Date")?></td>
            <td><?=_("Site Manager")?></td>	    
            <td><?=_("Location")?></td>
            <td><?=_("Skills Needed")?></td>
            <td><?=_("Volunteers Assigned")?></td>	    
        </thead>
        <tbody>
        <tr>
            <td align=center><?php echo $start ?></td>
            <td><?php echo $end ?></td>
            <td><?php echo $mgr ?></td>
	    <td>  	    
	       <div>
	    <a href="index.php?mod=vm&act=proj_locate&project=<?php echo $proj_id?>"><?php echo $project_location?></a>
	       </div>
            </td>
            <td><?php echo $project_skills ?></td>
	    <td><?php echo $vols_assigned ?></td>

        </tr>
        </tbody>
        </table>
    </div>
<?php       
  shn_form_fsclose();   // Close the subsection
  shn_form_fclose();    // Close the form

  // This section of the page contains a second form that displays a 
  // a table of currently unassigned volunteers, each row of which 
  // contains a separate form for assigning the volunteer to a  project.  
  // All of the forms are processed by this file.

  shn_form_fopen($action="vol_assign",$mod="vm",$opts= array('req_message'=>false));   // Opens <form> tag
  $subtitle = "Assign Unassigned Volunteers to Project " . $name;
  shn_form_fsopen($subtitle);

  // The following table displays all unassigned volunteers -- i.e., those who have
  //   an entry in vm_vol_details and other person data tables, but not in vm_proj_vol.
?>
    <div id="result">
	<table width="100%">
        <thead>
            <td><?=_("Volunteer Name")?></td>
            <td><?=_("Organization")?></td>
            <td><?=_("Location")?></td>
            <td><?=_("Avail Start")?></td>
            <td><?=_("Avail End")?></td>
            <!-- <td><?=_("Task")?></td> -->
	    <td><?=_("Status")?></td>
	    <td><?=_("Specialties")?></td>
        </thead>
        <tbody>

<?php
  _display_volunteers($projid=$proj_id, $org_id, $search_string);
  shn_form_fsclose();         // Close the subsection
?>
	</tbody>
	</table>
	</div>
<?php
  shn_form_fclose();        // Close the form
} // end shn_vm_vol_assign()


/**
 * Displays a table of unassigned volunteers associated within a given organization.
 * 
 * There is no DB table/field combination that identifies a volunteer as currently 
 * unassigned. An assigned volunteer is identified by an entry in the <b>vm_proj_vol</b>
 * table. To identify unassigned volunteers we query <b>vm_vol_details</b> to obtain
 * a list of all volunteers associated with a given organization ($org_id), and then 
 * remove all assigned volunteers (those listed in <b>vm_proj_vol</b>) from the list.
 *
 * Each row of the table contains information about a volunteer including a
 * form for assigning the volunteer to the project given in $project_id. 
 *
 * @param long  $project_id The project to which listed individuals will be assigned.
 * @param string  $org_id  The organization to which listed individuals belong.
 * @access public
 * @return void
 */
function _display_volunteers($project_id=NULL, $org_id=NULL, $search_string=NULL)  {
  global $global;
  $db=$global['db'];
  // Find all unassigned volunteers that belong to the selected organization -- i.e.,
  //  those that have no entry in vm_proj_vol.

  // First find all registered volunteers.
  $q = "select vm_vol_details.p_uuid, org_id, date_avail_start, date_avail_end from vm_vol_details, person_uuid where person_uuid.p_uuid = vm_vol_details.p_uuid";
  if('-1'==$org_id){}else{
	$q.=" and org_id='{$org_id}'";
  }
  if($search_string){
	$q.=" and full_name like convert(_utf8'%{$search_string}%' using latin1)";
  }
  $result=$db->Execute($q);

  while(!$result==NULL && !$result->EOF) {

    // Now skip all those who have already been assigned to a project.

    $q = "select p_uuid from vm_proj_vol where p_uuid='{$result->fields[0]}'";
    $result_assigned=$db->Execute($q);
    //    $person_id = NULL;
    $status = NULL;
    if ($result_assigned->fields[0] == NULL) {     // If the volunteer is unassigned (i.e., not in vm_proj_vol)
                                                   //   query the volunteer's details from various tables.
      $q = "select p_uuid, full_name from person_uuid where p_uuid='{$result->fields[0]}'";
      $result_person=$db->Execute($q);
      $person_id=$result_person->fields[0];
      $name=$result_person->fields[1];
      $org = get_volunteer_affiliation($person_id);
      $location = get_personal_location_string($person_id);
      $date_start = $result->fields[2];
      $date_end = $result->fields[3];
      //    $status=ucfirst($result->fields[2]);
      //$task=$_POST['task_'.$person_id];
      //      if ($task != NULL)
      //      	$status = 'assigned';
      //      else 
      $status = 'Unassigned';

      // Create an array of the volunteer's skills from which the assignment will be selected.

      $skill_opts_list = $db->Execute("select opt_skill_code from vm_vol_skills where p_uuid = '{$person_id}'");
      $options = array();
      while(!$skill_opts_list==NULL && !$skill_opts_list->EOF) {
          $q = "select option_code, option_description from field_options where option_code='{$skill_opts_list->fields[0]}'";
          $skill_descriptions=$db->Execute($q);
          $options[$skill_descriptions->fields[0]] = $skill_descriptions->fields[1];  // [value=opt_code,description=opt_n; 
          $skill_opts_list->MoveNext();
      } // while
      $post_id='task_vol#' . $person_id;   // Construct a distinct id containing an underscore  (_)
                                       // based on the volunteer's id for each selection box.
      $value = $_POST[$post_id];       // This is used when the selection box is created (below).
 
    // Break out of PHP to display one row of the volunteers table. 
?>
        <tr>
          <td>
           <div>
            <a href="index.php?mod=vm&act=volunteer_detail&volunteer=<?php echo $person_id?>"><?php echo ucfirst($name) ?></a>
           </div>
          </td>
        <td><?php echo ucfirst($org) ?></td>
        <td>
	   <div>
	   <a href="index.php?mod=vm&act=vol_locate&volunteer=<?php echo $person_id?>"><?php echo $location?></a>
	   </div>
        </td>
        <td><?php echo $date_start ?></td>
        <td><?php echo $date_end ?></td>
        <td><?php echo ucfirst($status) ?></td>
        <td align=center>

	 <!-- The form for assigning a volunteer a task for the given project. -->  
         <form method = "POST" action="index.php?mod=vm&act=vol_assign" >
         <table>
         <tr>
          <td align=left>
           <select name="<?=$post_id?>" >
<?php
	   // List the volunteer's skill options
	   foreach ($options as $opt_value => $desc ) {
	     $sel = ( $opt_value == $value ) ? "selected" : null ;
?>
             <option value="<?=$opt_value?>" <?=$sel?>><?=$desc?></option>
<?php
	   } // foreach
?>
          </select> 
          <input type=HIDDEN name='project' value=<?=$project_id ?> >
          <input type=HIDDEN name='organization' value=<?=$org_id ?> >
          <input type=SUBMIT value="Assign This Volunteer" >
         </td>
         <tr>
         </table>
         </form>
        </td>
       </tr>
<?php
   } // if unassigned
        $result->MoveNext();
  } // while loop
?>
       </tbody>
       </table>
    </div>
<?php
} // display_volunteers()
?>

