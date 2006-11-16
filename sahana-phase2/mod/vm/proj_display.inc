<?php
/* $Id: [sahana_home]/mod/vm/proj_display.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- displays details about registered projects.
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  displays details about recently registered projects,
 *  including Project Name, Start Date, End Date,
 *  Location, Specialties Needed, Site Manager,
 *  Volunteers Assigned, and Volunteers On Hold.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     R. Morelli <ralph.morelli@trincoll.edu> 
 */

global $global;

/** Contains library functions for creating forms */
include_once $global['approot']."/inc/lib_form.inc";
/** Contains library functions for location forms */
include_once $global['approot']."/inc/lib_location.inc";
/** Contains functions for viewing projects and relevant data */
include_once "view_projects.inc";
/** Contains functions for GIS mapping of projects */
include_once "proj_locate.inc";

/**
 *  This function calls the function
 *  _shn_vm_viewform_allproj(), which creates the 
 *  table headings in the Recently Added Projects table.
 *   _shn_vm_viewform_allproj() is located
 *  in ../vm/view_projects.inc.  
 *  
 *  @param string $no
 *  @access public
 *  @return void
 */
function _shn_vm_proj_display($no=NULL)
{
   //error_reporting(E_ALL);
   
   _shn_vm_viewform_allproj();
   ?><div><br></div><?php
   _shn_vm_proj_locate_all();   
}

function _shn_vm_proj_detail($no=NULL) 
{
} 


?>

