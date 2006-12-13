<?php
/* $Id: [sahana_home]/mod/vm/volunter_detail.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- displays information about a specific volunteer.
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates a Volunteer Information page.  Each Volunteer Information page is
 *  divided into three sections: the first provides general volunteer
 *  information, including: Name, Address, E-mail, Telephone, and 
 *  Affiliation.  The second section provides availability information,
 *  including: Dates Available Start, Dates Available End, Hours Available,
 *  Specialties, and Location (link to a map).  The third section
 *  provides engagement information, including: Current Project,
 *  Role, Status, Hours Worked, Payrate, and Dollar Value.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Ravindra <ravindra@opensource.lk>
 *
 */

global $global;

/** Contains library functions for creating forms. */
include_once ("vol_locate.inc"); 
/** Contains utility functions for VM and VR modules. */
include_once $global['approot']."/mod/vm/utility_functions.inc";

/**
 *  Displays general details and availability information for a specific volunteer.
 *
 *  This function generates the first two sections of the Volunteer 
 *  Information page.  The first section displays general volunteer
 *  information, including: Name, Address, E-mail, Telephone, and 
 *  Affiliation.  The second section displays availability information,
 *  including: Dates Available Start, Dates Available End, Hours Available,
 *  Specialties, and Location (link to a map).  This function performs
 *  a DB query on the table <b>person_uuid</b>. It is called 
 *  when the following php query is made:
 *  index.php?mod=vm&act=volunteer_detail&volunteer=id#
 *  
 *  @access public 
 *  @return void
 */
function _shn_vm_volunteer_detail() 
{
  $volunteer_id = $_GET['volunteer'];     // Retrieve the project parameter's value from the GET query
  //error_reporting(E_ALL);                 // Set error reporting on. (This should be turned off in production version.)
  global $global;
  $db=$global['db'];

// Query the vm_projects table to retrieve data about the given project.

  $q = "select p_uuid,full_name from person_uuid where p_uuid='{$volunteer_id}'";
  $result=$db->Execute($q);
  $person_id=$result->fields[0];
  $name=$result->fields[1];


// Break out of PHP to display information about the individual.
?>
    <div id="home">
       <h2><?php echo "Volunteer Information for " . $name ?></h2><br>
       <table width="100%">
        <thead>
         <td><?=_("Name")?></td>
         <td><?=_("Address")?></td>
         <td><?=_("E-mail")?></td>
         <td><?=_("Telephone")?></td>
         <td><?=_("Affiliation")?></td>
        </thead>
        <tbody>
         <tr align="center">
          <td><?php echo ucfirst($name)?></td>
          <td><?php echo get_contact_info($person_id,'addr') ?></td>
          <td><?php echo get_contact_info($person_id,'email') ?></td>
          <td><?php echo get_contact_info($person_id,'curr') ?></td>
          <td><?php echo get_volunteer_affiliation($person_id) ?></td>
         </tr>
        </tbody>
       </table>
      </div>
       <br />
      <div id="home">      
       <table width="100%">
        <caption><h2>Availability</h2><br></caption>
        <thead>
         <td><?=_("Dates Available Start")?></td>
         <td><?=_("Dates Available End")?></td>
         <td><?=_("Hours Available")?></td>
         <td><?=_("Specialties")?></td>
         <td><?=_("Location")?></td>
        </thead>
        <tbody>
         <tr align="center">
          <td><?php echo get_volunteer_availability_date_time($person_id,true,true) ?></td>
          <td><?php echo get_volunteer_availability_date_time($person_id,true,false) ?></td>
          <td><?php echo get_volunteer_availability_date_time($person_id,false,true) . "-" . get_volunteer_availability_date_time($person_id,false,false)  ?></td>
          <td><?php echo get_volunteer_specialties($person_id) ?></td>
          <td>
           <div>
            <a href="index.php?mod=vm&act=vol_locate&volunteer=<?php echo $volunteer_id?>"><?php echo get_personal_location_string($volunteer_id) ?></a>
           </div>
          </td>
         </tr>
        </tbody>
       </table>
     </div>
     <br />
<?php
       display_engagement_info($volunteer_id);   // Display a list of volunteers
?>
<?php
} // _shn_vm_proj_detail()
?>

<?php

/** 
 *  Displays engagement information for a specific volunteer.
 *
 *  This function generates the third section of the Volunteer
 *  Information page, which is engagement information.  
 *  The engagement information section displays: Current Project,
 *  Role, Status, Hours Worked, Payrate, and Dollar Value.
 *  This function performs a DB query of the tables 
 *  <b>vm_proj_vol</b> and <b>vm_projects</b>.
 *
 *  @param string $volunteer_id  The id of the volunteer whose information is queried
 *  @access public
 *  @return void
 */
function display_engagement_info($volunteer_id=NULL)
{
    global $global;
    $db=$global['db'];
    $q = "select p_uuid, proj_id, status, payrate,hours,opt_skill_type from vm_proj_vol where p_uuid='{$volunteer_id}'";
    $result=$db->Execute($q);
    $project_id=$result->fields[1];
    $status=ucfirst($result->fields[2]);
    $payrate=$result->fields[3];                  
    $hours=$result->fields[4];                  
    $task= ucfirst($result->fields[5]);                  
    $q = "select name from vm_projects where proj_id = '{$project_id}'";
    $result =$db->Execute($q);
    $project_name=$result->fields[0];

// Break out of PHP and display the table headings.
?>
      <div id="home">      
       <table width="100%">
        <caption><h2>Engagement Information</h2><br></caption>
        <thead>
         <td><?=_("Current Project")?></td>
         <td><?=_("Role")?></td>
         <td><?=_("Status")?></td>
         <td><?=_("Hours Worked")?></td>
         <td><?=_("Payrate")?></td>
         <td><?=_("Dollar Value")?></td>
        </thead>
        <tbody>
         <tr align="center">
          <td><?php echo $project_name ?></td>
          <td><?php echo get_skill_description($task)?></td>
          <td><?php echo $status ?></td>
          <td><?php echo $hours ?></td>
          <td><?php echo $payrate ?></td>
          <td><?php echo $hours * $payrate ?></td>
         </tr>
        </tbody>
       </table>
     </div> 
<?php
} // _display_engagement()

?>
