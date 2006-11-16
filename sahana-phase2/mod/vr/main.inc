<?php
/* $Id: [sahana_home]/mod/vr/main.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Registry Module --  creates the menu system for the VR module 
 *
 * <p>This file was adapted from Volunteer Management's 
 * version of main.inc.  Volunteer Management's version of
 * main.inc was adapted from Organization Registry's main.inc.  
 * This file creates a two-field menu system when the Volunteer Registry 
 * field in the main menu is clicked.  It calls the
 * function shn_vr_vol_add() via the function shn_vr_default().
 * shn_vr_default() produces the web get query:
 * index.php?mod=vr&act=default.</p>  
 *
 * @package    Trinity_College_vm_demo
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Ravindra <ravindra@opensource.lk>
 * @author     Pradeeper <pradeeper@opensource.lk>
 * @author     Chathra <chathra@opensource.lk>
 *
 */
 
global $global;
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/mod/vr/lib_vr.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once ("vol_add.inc"); 
include_once ("vol_reg.inc"); 

/**
 * Creates the main menu for the VR module.
 *
 * Creates the menu items that appear when the VR module 
 * link is clicked.  There are 2 fields: Add Volunteer and Edit.
 * The Add Volunteer field generates another Voluneer Registry 
 * page.  The edit field is not currently running.    
 *
 * @access public
 * @return void
 */
function shn_vr_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];

    shn_mod_menuopen(_lc("Volunteer Registry"));

if($_SESSION['logged_in'] != true){

	shn_mod_menuitem("vol_add","Register to Volunteer",$module);

}else{
		
    shn_mod_menuitem("default","Portal",$module);
    shn_mod_menuitem("vol_add","Edit Details for {$_SESSION['user']}",$module);
    shn_mod_menuitem("ch_pwd","Change Password",$module);


}
      shn_mod_menuclose();


 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

function shn_vr_ch_pwd()
{
    include_once ("auth_form.inc"); 
    shn_auth_form_ch_pwd();
}

function shn_vr_ch_pwd_cr()
{
    include_once ("auth_form.inc"); 
    _shn_admin_ch_pwd_cr();
}
/*
function shn_vr_vol_display()
{
    include_once("vol_display.inc");
    _shn_vr_vol_display();
}
function shn_vr_vol_search(){
    include_once("vol_search.inc");
     _shn_vr_vol_search();
}
function shn_vr_vol_locate(){
    include_once ("vol_locate.inc");
	_shn_vr_vol_locate();
}
function shn_vr_vol_edit(){
    include_once("vol_edit.inc");
   _shn_vr_regform_vol_edit();
}

function shn_vr_volunteer_detail(){
    include_once("volunteer_detail.inc");
   _shn_vr_volunteer_detail();
}

function shn_vr_proj_add($error=false)
{
    include_once ("proj_add.inc"); 
    _shn_vr_regform_proj_add($error);
}
function shn_vr_proj_display()
{
    include_once("proj_display.inc");
    _shn_vr_proj_display();
}
function shn_vr_proj_search(){
    include_once("proj_search.inc");
     _shn_vr_proj_search();
}
function shn_vr_proj_locate(){
    include_once ("proj_locate.inc");
	_shn_vr_proj_locate();
}
function shn_vr_proj_report(){
    include_once ("proj_report.inc");
	_shn_vr_proj_report();
}

function shn_vr_vol_report(){
    include_once ("vol_report.inc");
	_shn_vr_vol_report();
}

function shn_vr_proj_edit(){
    include_once("proj_edit.inc");
   _shn_vr_regform_proj_edit();
}
*/
function shn_vr_home(){
    include_once("home.inc");
}


/**
*  This function is called automatically when the VR module is 
*  selected.  It displays the default welcome page defined in home.inc.
*
*  @access public
*  @return void
*/
function shn_vr_default()
{
if($_SESSION['logged_in'] == true){
    shn_vr_home();
    }else{
	shn_vr_vol_add();
    }
}
?>

