<?php
/* $Id: [sahana_home]/mod/vm/view_projects.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- displays project details on the "Recently Added Projects" page.  
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates the table inside the "Recently Added Projects"
 *  page.</p>
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
include_once $global['approot']."/inc/lib_form.inc";
/** Contains library functions for location forms. */
include_once $global['approot']."/inc/lib_location.inc";
//include_once ("vm_utility_functions.inc"); 

include_once $global['approot']."/mod/vm/utility_functions.inc";

/**
 *  Displays the table headings for the Recently Added Projects table.
 * 
 *  This function creates the Project Name, Start Date, End Date,
 *  Location, Specialties Needed, Site Manager, Volunteers Assigned, and
 *  Volunteers On Hold headings on the Recently Added Projects table. 
 *  If the function's parameter is NULL, then all projects are displayed. If
 *  an integer argument is supplied, then just that many projects are
 *  listed.  It performs a DB query of the table <b>vm_projects</b>.
 *
 *  @param string $no
 *  @access public
 *  @return void
 */
function _shn_vm_viewform_allproj($no=NULL)
{
    global $global;
    $db=$global['db'];
?>

<!-- 
  This HTML table displays a navigable list of the registered projects. After printing
  a heading, it calls the _shn_or_viewform_allorg() function, which displays the list.
-->

    <div id="note">
    <strong><?=_("Recently Added Projects")?></strong>
    </div>
<div id ="result">
	<table>
        <thead>
            <td><?=_("Project Name")?></td>
	    <td><?=_("Start Date")?></td>
            <td><?=_("End Date")?></td>
            <td><?=_("Location")?></td>
            <td><?=_("Site Manager")?></td>
	    <td><?=_("Volunteers Assigned")?></td>
            <td><?=_("Volunteers On Hold")?></td>
        </thead>
        <tbody>

<?php
/*
*Two different queries are issued depending on the value of $no.
*/
    if($no==NULL){
        $q = "select proj_id,name,start_date,end_date,location_id from vm_projects order by proj_id asc";
        //$q = "select proj_id,name,manager,start_date,end_date,location_id,vols_assigned,vols_on_hold from vm_projects order by proj_id asc";
        $res_proj=$db->Execute($q);
    }else {
        $q = "select proj_id,name,start_date,end_date,location_id from vm_projects order by proj_id asc";
        //$q = "select proj_id,name,manager,start_date,end_date,location_id,vols_assigned,vols_on_hold from vm_projects order by proj_id asc";        
	$res_proj=$db->SelectLimit($q,$no);
    }

/* 
* This loop displays all projects retrieved from the DB.
*/ 
    while(!$res_proj==NULL && !$res_proj->EOF){
        $proj_id=$res_proj->fields[0];                  // Get the project's ID
        if($proj_id!=0){                                // And display the project's name
        _shn_display_proj($proj_id);                    
        $res_proj->MoveNext();
	}
    }   
    
?>
   </tbody>
  </table>
</div>
<?php
} // end _shn_viewform_allproj

/**
 *  Displays the details of the project whose ID is given as a parameter.
 * 
 *  This function populates the Recently Added Projects table.  
 *  It performs a DB query of the table <b>vm_projects</b>.
 * 
 *  @param string $proj_id
 *  @param string $indent
 *  @param string $edit
 *  @access public
 *  @return void
 */
function _shn_display_proj($proj_id,$indent=true,$edit=false)
{
    global $global;
    $db=$global["db"];
    $q = "select name,start_date,end_date,location_id from vm_projects where proj_id='${proj_id}'";
    $result=$db->Execute($q);
    $name=$result->fields[0];
    $start=$result->fields[1];
    $end=$result->fields[2];
    $location=$result->fields[3];
    //    $manager= get_manager_name($proj_id);
    $vols_assigned= get_volunteer_count($proj_id);
    $vols_on_hold= get_volunteer_count($proj_id, 'onhold');
?>

<tr>
      <td>
     	<div>
			<a href="index.php?mod=vm&act=proj_detail&project=<?php echo $proj_id?>">
	                   <?=($name)?>
        	        </a>
	</div>
     <td><?php echo $start?></td>
     <td><?php echo $end?></td>
     <td>
     	<div>
			<a href="index.php?mod=vm&act=proj_locate&project=<?php echo $proj_id?>">
	                   <?php echo get_project_location_string($proj_id) ?>
        	        </a>
	</div>
     </td>
     <td>
       <div>
        <a href="index.php?mod=vm&act=volunteer_detail&volunteer=<?php echo get_manager_id($proj_id)?>"><?php echo get_manager_name($proj_id) ?></a>
      </div>
     </td>
<!--      <td><?php echo $manager?></td>-->
     <td><?php echo $vols_assigned?></td>
     <td><?php echo $vols_on_hold?></td>
</tr>
<?php
}  // end _shn_display_proj()
 
?>
