<?php
/**Registration related forms for Organizations of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
include_once "lib_or.inc";

function _shn_or_regform_org($error=false)
{
    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?= _('Organization Registration')?></h2>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("reg_org_cr");
    shn_form_fsopen('Primary Details');
    $extra_opts['req']=true;
    shn_form_text(_("* Organization Name : "),'org_name','size="50"',$extra_opts); 
    shn_form_text(_("Registration Number : "),'reg_no','size="50"'); 
    shn_form_fsclose();
    shn_form_fsopen("Organization Type");
    _shn_or_display_org_type($error);
    shn_form_fsclose();
    shn_form_fsopen("Organization Sector");
    _shn_or_display_sector($error);
    shn_form_fsclose();
    
   // base location
   	$parent=_shn_or_get_start_loc();
	if($parent==$conf['mod_or_start_loc']){
  		$location_inf = shn_location('1','4'); 
    }else {
        $location_inf = shn_location_parent($parent,'1','4'); 
    }
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location *(req)',$return=false,$default_val_req=$error);
    // Contact infomation
    shn_form_fsopen("Contact Information");
    _shn_or_display_contact_person($error,true,null);
    shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
    _shn_or_display_org_facilities($error);
    shn_form_fsclose();
 	shn_form_fsopen("Extra Information");
    _shn_or_display_extra($error);
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
} 

function _shn_or_regform_operation($error=false)
{
    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?=_("Add an Operation/Branch under the Organization ").$_SESSION["parent_name"]?> </h2>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
    shn_form_fopen("reg_operation_cr");
    shn_form_fsopen('Primary Details');
    $extra_opts['req']=true;
    shn_form_text(_("Operation/Branch Name : "),'org_name','size="50"',$extra_opts); 
	shn_form_fsclose();
    shn_form_fsopen("Organization Sector");
    _shn_or_display_sector($error);
    shn_form_fsclose();
 // base location
   	$parent=_shn_or_get_start_loc();
	if($parent==$conf['mod_or_start_loc']){
  		$location_inf = shn_location('1','4'); 
    }else {
        $location_inf = shn_location_parent($parent,'1','4'); 
    }
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location *(req)',$return=false,$default_val_req=$error); 
    shn_form_fsopen("Contact Information");
    _shn_or_display_contact_person($error,true,null);
shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
   _shn_or_display_org_facilities($error);
    shn_form_fsclose();
 	shn_form_fsopen("Extra Information");
    _shn_or_display_extra($error);
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
   shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
  
} 
?>
