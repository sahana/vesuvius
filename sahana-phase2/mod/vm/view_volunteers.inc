<?php
/* $Id: [sahana_home]/mod/vm/vol_assign.inc,v 1.0 2006/06/12  */
/**
 *
 *  Volunteer Management Module -- displays details about a project, including a 
 *  detailed list of the project's volunteers.
 *
 *  <p>This file is part of the Volunteer Management module.  It
 *  generates the Project Details page, which is composed of three
 *  sections.  The first displays general project information, the 
 *  second is a description of the project, and the third is 
 *  a table of project volunteer information.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 *
 */
 
global $global;

/** Contains functions for displaying detailed volunteer information */
include_once ("volunteer_detail.inc"); 
/** Contains functions for GIS mapping of volunteers */
include_once ("vol_locate.inc"); 
/** Contains utility functions for VM and VR modules */
include_once $global['approot']."/mod/vm/utility_functions.inc";

/**
 *  Generates the Project Details page.
 *
 *  This function generates the first two sections
 *  of the Project Details page: the project details
 *  section, and the project description section.
 *  This function is called when the following php query is made:
 *  index.php?mod=vm&act=proj_detail&project=1
 *
 *  @access public
 *  @return void
 *  @ignore
 */
function _shn_vm_proj_detail(){
  $project_id_param = $_GET['project'];   // Retrieve the project parameter's value from the GET query
  $removal = $_GET['person'];
  //error_reporting(E_ALL);                 // Set error reporting on. (This should be turned off in production version.)
  global $global;
  $db=$global['db'];

// Query the vm_projects table to retrieve data about the given project.
  if($removal!=NULL){
  	$q = "select name from vm_projects where proj_id='{$project_id_param}'";
      	$result = $db->Execute($q);
      	$name = $result->fields[0];
        $current_user = get_current_user_id();
	$q = "select max(message_id) from vm_messages";
      	$result = $db->Execute($q);
        $message_id = $result->fields[0] + 1;      
      	$q = "insert into vm_courier (message_id, to_id, from_id) 
      	  VALUES ('{$message_id}', '{$removal}', '{$current_user}')";
  	$db->Execute($q);
      	$q = "insert into vm_messages (message_id, message)
      			     VALUES ('{$message_id}', 'You have been removed from the project titled {$name}')";
      	$db->Execute($q);
	$q = "delete from vm_proj_vol where proj_id='{$project_id_param}' and p_uuid='{$removal}'";
	$result=$db->Execute($q);
  }

  $q = "select proj_id,name,start_date,end_date,location_id from vm_projects where proj_id='{$project_id_param}'";
  $result=$db->Execute($q);
  $proj_id=$result->fields[0];
  $name=$result->fields[1];
  $start=$result->fields[2];
  $end=$result->fields[3];
  $location=$result->fields[4];

// Break out of PHP to display a summary of the project.
?>
    <div id="home">
       <h2><?=_("Project Details")?></h2>
       <table width="100%">
        <thead>
         <td><?=_("Project Name")?></td>
         <td><?=_("Start Date")?></td>
         <td><?=_("End Date")?></td>
         <td><?=_("Location")?></td>
         <td><?=_("Specialties Needed")?></td>
         <td><?=_("Site Manager")?></td>
         <td><?=_("Volunteers Assigned")?></td>
         <td><?=_("Volunteers On Hold")?></td>
        </thead>
        <tbody>
         <tr>
          <td><?php echo ucfirst($name)?></td>
          <td><?php echo $start?></td>
          <td><?php echo $end?></td>
          <td>
           <div>
            <a href="index.php?mod=vm&act=proj_locate&project=<?php echo $proj_id?>"><?php echo _shn_vm_location_string($location) ?></a>
           </div>
          </td>
          <td><?php echo get_project_skills_list($project_id_param) ?></td>
          <td>
           <div>
            <a href="index.php?mod=vm&act=volunteer_detail&volunteer=<?php echo get_manager_id($project_id_param)?>"><?php echo get_manager_name($project_id_param)  ?></a>
           </div>
          </td>
          <td><?php echo get_volunteer_count($project_id_param) ?></td>
          <td><?php echo get_volunteer_count($project_id_param, 'onhold') ?></td>
         </tr>
        </tbody>
       </table>
     </div>
     <br />
<?php
_display_description($proj_id);
?><br><?php
// RAM -- 11/26/2006 -- Adding an if clause to make the call to _display_volunteers() conditional on there being >0 volunteers.
    if (get_volunteer_count($project_id_param) != 0)
        _display_volunteers($proj_id);   // Display 	a list of volunteers

} // _shn_vm_proj_detail()

/** 
 *  Displays the "Volunteers" section of the Project Details page.  
 *
 *  This function displays the third section of the Project Details page:
 *  a table of volunteers associated with a project whose
 *  id is given as a parameter.  It performs a DB query of the tables
 *  <b>vm_proj_vol</b> and <b>vm_vol_details</b>.
 *
 *  @param string $project_id  The id of the project being queried.
 *  @param string $org_id  The id of the organization being queried.  
 *  @access public
 *  @return void
 *  @ignore
 */
function _display_volunteers($project_id=NULL, $org_id=NULL){
    global $global;
    $db=$global['db'];
// Break out of PHP and display the table headings.
?>
    <div id="result">
	<table>
        <caption><strong>Working Volunteers</strong></caption>
        <thead>
            <td><?=_("Volunteer")?></td>
	    <td><?=_("Affiliation")?></td>
            <td><?=_("Status")?></td>
            <td><?=_("Assigned Task")?></td>
            <td><?=_("Hours Worked")?></td>
	    <td><?=_("Pay Rate")?></td>
	    <td><?=_("Dollar Value")?></td>
            <td><?=_("Location")?></td>
	    <?php if($project_id==NULL){}else{
	    ?><td><?=_("Remove")?></td><?php }?>
        </thead>
        <tbody>
<?php
$q = "select vm_proj_vol.p_uuid, proj_id, status, payrate, hours, opt_skill_type, org_id from vm_proj_vol, vm_vol_details where vm_proj_vol.p_uuid = vm_vol_details.p_uuid";
    if($project_id==NULL&&$org_id==NULL){
	$q = $q . " group by p_uuid";
    }else{
	if($project_id!=NULL){
	$q = $q . " and proj_id='{$project_id}'";
	}
	if($org_id!=NULL){
	$q = $q . " and org_id='{$org_id}'";
	}
    } // else
    
	$q = $q . " limit 50";
	
    $result=$db->Execute($q);
    while(!$result==NULL && !$result->EOF){
	$q = "select p_uuid, full_name from person_uuid where p_uuid='{$result->fields[0]}'";
        $result_person=$db->Execute($q);
	$person_id=$result_person->fields[0];
	$name=$result_person->fields[1];
	$status=ucfirst($result->fields[2]);
        $payrate=$result->fields[3];                  
        $hours=$result->fields[4];                  
        $task=$result->fields[5];
	$task=get_skill_description($task);
	$location = get_personal_location_string($person_id);
	$org = get_volunteer_affiliation($person_id);
	// Break out of PHP to display one row of the volunteers table. 
?>
        <tr>
          <td>
           <div>
            <a href="index.php?mod=vm&act=volunteer_detail&volunteer=<?php echo $person_id?>"><?php echo ucfirst($name) ?></a>
           </div>
          </td>

        <td><?php echo ucfirst($org) ?></td>
        <td><?php echo ucfirst($status) ?></td>
        <td><?php echo ucfirst($task) ?></td>
        <td><?php echo $hours ?></td>
        <td><?php echo "$" . number_format($payrate,2)?></td>
        <td><?php echo "$" . number_format(($hours * $payrate), 2)?></td>
        <td>
         	<div>
        	   <a href="index.php?mod=vm&act=vol_locate&volunteer=<?php echo $person_id?>"><?php echo $location?></a>
        	</div>
         </td>
	 <?php if($project_id==NULL){}else{?>
	 <td align=center>
	 <form method = "POST" action="index.php?mod=vm&act=proj_detail&project=<?php echo $project_id?>&person=<?php echo $person_id?>" >
	 <input type=SUBMIT value="Remove This Volunteer" >
	 </td>
	 <?php }?>
        </tr>
<?php
        $result->MoveNext();
    } // while loop
?>
       </tbody>
       </table>
    </div>
<?php
} // _display_volunteers()

/**
 *  Displays the description associated with a given project.  
 *
 *  @param string $project_id  The id of the project being queried.
 *  @access public
 *  @return void
 */
function _display_description($project_id=NULL){
    global $global;
    $db=$global['db'];
    $q = "select description from vm_projects where proj_id='{$project_id}'";
    $result=$db->Execute($q);
    $description=$result->fields[0];

?>
    <div id="result">
    <div align="center">
    <strong align="center">Description</strong>
    </div><?php echo $description?>
    </div>
<?php    

}  //_display_description() 
?>
