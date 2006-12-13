<?php
/* $Id: [sahana_home]/mod/vm/main.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module --  creates the menu system for the VM module 
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates the menu system that appears when you click on the
 *  Volunteer Management module link in the main menu.  This file
 *  also includes all the files that can be called from the Volunteer
 *  Management homepage.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 * @author     Ravindra <ravindra@opensource.lk>
 * @author     Pradeeper <pradeeper@opensource.lk>
 * @author     Chathra <chathra@opensource.lk>
 * sample text
 */

global $global;
global $conf;
/** Contains library functions for modules */
include_once $global['approot']."/inc/lib_modules.inc";
/** Contains library functions for error checking */
include_once $global['approot']."/inc/lib_errors.inc";
/** Contains library functions for validation */
include_once $global['approot']."/inc/lib_validate.inc";
/** Contains local library functions for creating forms in VM and VR modules. */
include_once $global['approot']."/mod/vm/lib_vm.inc";
/** Contains functions for displaying volunteers and data*/
include_once("vol_display.inc");
include_once("vol_reg.inc");
include_once("vol_add.inc");

/** Contains functions for creating menu items. */
include_once $global['approot']."/inc/lib_menu.inc";



/**
 * Creates the main menu for the VM module.
 *
 * Creates the menu items that appear when the VM module 
 * link is clicked.  There are 3 main sections: Home, Volunteers,
 * and Projects.  Home links to the VM homepage.  Volunteers has 
 * 2 subheadings: Assign to Project, and Show All.  Projects has 
 * 3 subheadings: Add New, Show All, and Work Summaries.  These 
 * subheadings are clickable links that break out into new pages.  
 *
 * @access public
 * @return void
 */
function shn_vm_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];

if(0==$conf['mod_vm_hack']){
if($_SESSION['logged_in'] == true){
    //user section
    shn_mod_menuopen(_lc("Volunteer Management"));
    shn_mod_menuitem("default","Home",$module);
    shn_mod_menuitem("vol_add","Edit Details for {$_SESSION['user']}",$module);
    shn_mod_menuitem("ch_pwd","Change Password",$module);
    shn_mod_menuclose();
}else{
    //guest section
    shn_mod_menuopen(_lc("Volunteer Management"));
    shn_mod_menuitem("default","Register to Volunteer",$module);
    shn_mod_menuclose();
}
}else{
    //admin section
    shn_mod_menuopen(_lc("Volunteer Management"));
    shn_mod_menuitem("portal","Home",$module);
    shn_mod_menuitem("proj_report","Work Summaries",$module);
    shn_sub_mod_menuopen(_("Volunteers"));
    shn_mod_menuitem("vol_display","Show All",$module);
    shn_mod_menuitem("vol_assign","Assign to Project",$module);
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_("Projects"));
    shn_mod_menuitem("proj_display","Show All",$module);
    shn_mod_menuitem("proj_add","Add New",$module);
    shn_sub_mod_menuclose();
    shn_mod_menuitem("vol_add","Edit Details for {$_SESSION['user']}",$module);
    shn_mod_menuitem("ch_pwd","Change Password",$module);
    shn_mod_menuclose();
}

    
/** */
include $global['approot']."/inc/handler_mainmenu.inc";

} 

/** 
*  Breaks out to the Assign to Project page.
* 
*  The file called in this function allows 
*  the site administrator to 
*  assign unassigned volunteers.
*
*  @access public
*  @return void
*/

function shn_vm_vol_assign($error=false)
{
    include_once ("vol_assign.inc"); 
    _shn_vm_vol_assign($error);
}
/*
function shn_vm_reg_vol_cr()
{
    include_once ("vol_process.inc"); 
    _shn_vm_reg_vol_cr($error);
}
*/

/*
function shn_vm_vol_display()
{
    include_once("vol_display.inc");
    _shn_vm_vol_display();
}
*/
function shn_vm_ch_pwd()
{
    include_once ("auth_form.inc"); 
    shn_auth_form_ch_pwd();
}

function shn_vm_ch_pwd_cr()
{
    include_once ("auth_form.inc"); 
    _shn_admin_ch_pwd_cr();
}

/*
function shn_vm_vol_search(){
    include_once("vol_search.inc");
     _shn_vm_vol_search();
}
*/

/** 
*  Breaks out to a map with a pointer to the volunteer's location.
* 
*  @access public
*  @return void
*/
function shn_vm_vol_locate(){
    include_once ("vol_locate.inc");
	_shn_vm_vol_locate();
}

/*
function shn_vm_vol_edit(){
    include_once("vol_edit.inc");
   _shn_vm_regform_vol_edit();
}
*/

/** 
*  Breaks out to a Volunteer Details page.
*
*  The file that is called in this function 
*  displays details about
*  an individual volunteer, including sections 
*  for contact information, availability, and 
*  engagement information. 
*
*  @access public
*  @return void
*/
function shn_vm_volunteer_detail(){
    include_once("volunteer_detail.inc");
   _shn_vm_volunteer_detail();
}

/** 
*  Breaks out to the Register New Project page.
*
*  The file that is called in this function 
*  generates a page that allows end users to 
*  register new projects.  
*
*  @access public
*  @return void
*/
function shn_vm_proj_add($error=false)
{
    include_once ("proj_add.inc"); 
    _shn_vm_regform_proj_add($error);
}

/** 
*  Breaks out to the Recently Added Projects page.
*
*  The file called in this function 
*  displays details about recently registered projects,
*  including Project Name, Start Date, End Date,
*  Location, Specialties Needed, Site Manager,
*  Volunteers Assigned, and Volunteers On Hold,
*
*  @access public
*  @return void
*/
function shn_vm_proj_display()
{
    include_once("proj_display.inc");
    _shn_vm_proj_display();
}

/*
function shn_vm_proj_search(){
    include_once("proj_search.inc");
     _shn_vm_proj_search();
}
*/

/** 
*  Breaks out to a map with a pointer to the project's location.
* 
*  @access public
*  @return void
*/
function shn_vm_proj_locate(){
    include_once ("proj_locate.inc");
	_shn_vm_proj_locate();
}

/** 
*  Breaks out to the Work Summaries Report page
*
*  The file called in this function breaks out to 
*  the Work Summaries Report page, which allows the user
*  to search for projects based on start/end dates and
*  organizations involved.  There is also a work summary
*  report on the top of the page, which displays the total 
*  number of volunteers and the total dollar value of their 
*  work.
*
*  @access public
*  @return void
*/
function shn_vm_proj_report(){
    include_once ("proj_report.inc");
	_shn_vm_proj_report();
}

function shn_vm_proj_edit(){
    include_once("proj_edit.inc");
   _shn_vm_regform_proj_edit();
}

/** 
*  Breaks out to a Project Details page.
*
*  The file that is called in this function 
*  displays details about registered projects,
*  including Project Name, Start Date, End Date,
*  Location, Specialties Needed, Site Manager,
*  Volunteers Assigned, Volunteers On Hold, a 
*  description of the project, as well as 
*  volunteer statistics.
*
*  @access public
*  @return void
*/
function shn_vm_proj_detail(){
    include_once("view_volunteers.inc");
    _shn_vm_proj_detail();
}

function shn_vm_portal(){
    include_once ("home.inc");
}

/**
*  This function is called automatically when the VM module is 
*  selected.  It displays the default welcome page defined in home.inc.
*
*  @access public
*  @return void
*/
function shn_vm_default()
{
if($_SESSION['logged_in'] == true){
        shn_vm_portal();
    }else{
	shn_vm_vol_add();
    }

}



