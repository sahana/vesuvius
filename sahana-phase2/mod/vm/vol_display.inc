<?php
/* $Id: [sahana_home]/mod/vm/vol_display.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- creates the show all volunteers page.  
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates a table of all volunteers in all projects.  
 *  The columns in the table include: Name, Affiliation,
 *  Status, Assigned Task, Hours Worked, Pay Rate, Dollar Value
 *  and Location.  Only volunteers who have been assigned appear
 *  in the table.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Ravindra <ravindra@opensource.lk>
 *
 */

global $global;
/** Contains library functions for creating forms. */
include_once $global['approot']."/inc/lib_form.inc";
/** Contains library functions for location forms. */
include_once $global['approot']."/inc/lib_location.inc";
/** Contains functions for GIS mapping of volunteers. */
include_once $global['approot']."/mod/vm/vol_locate.inc";

/**
 *  Calls _display_all_volunteers() and _shn_vm_vol_locate_all().
 *
 *  @param string $no  
 *  @access public
 *  @return void
 */
function shn_vm_vol_display($no=NULL){
   _display_all_volunteers();
   ?><div><br></div><?php
  // _shn_vm_vol_locate_all();
   
}   

/** 
 *  Creates the "Volunteers" table.  
 *
 *  This function creates a table of volunteer information, 
 *  including: Name, Affiliation, Status, Assigned Task, 
 *  Hours Worked, Pay Rate, Dollar Value and Location.  
 *  All volunteers are shown in the table, regardless of 
 *  project affiliation.  This function calls the function 
 *  _display_volunteers(), which is responsible
 *  for actually generating the volunteers table 
 *  and which is located in ../vm/view_volunteers.inc.
 *
 *  @param string $no
 *  @access public
 *  @return void
 */
function _display_all_volunteers($no=NULL){
    include_once "view_volunteers.inc";	
    _display_volunteers();
   
} // _display_all_volunteers()
?>
