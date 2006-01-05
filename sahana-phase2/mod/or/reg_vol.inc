<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
include_once "lib_or.inc";

function _shn_or_regform_vol($error=false)
{
  global $global;
    $db=$global['db'];
     
?>
<h2><?=_("Volunteer Registration")?> </h2>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
shn_form_fopen("reg_vol_cr");
   	shn_form_fsopen('Primary Details');
    $extra_opts['req']=true;
    shn_form_text(_("Name in Full : "),'name','size="50"',$extra_opts); 
$extra_opts['req']=false;
shn_form_text(_("Date of Birth : "),'dob','size="10"',$extra_opts); 
//shn_form_date(_("Date of Birth: "),'dob', null ) ;

shn_form_text(_("Occupation : "),'job','size="50"',$extra_opts); 

_shn_or_display_gender($error,NULL);
shn_form_fsclose();
shn_form_fsopen('Identity Information');
 shn_form_text(_("National ID No : "),'nic','size="50"',$extra_opts); 
shn_form_text(_("Passporl No : "),'pas','size="50"',$extra_opts); 
shn_form_text(_("Driving License No : "),'dln','size="50"',$extra_opts); 
shn_form_fsclose();

    // base location
   $location_inf = shn_location_form_org('1','4'); 
// call OR name
  
   shn_form_fsopen("Services Offered");
_shn_or_display_sector($error);
shn_form_fsclose();

shn_form_fsopen("Contact Information");
    _shn_or_display_contact_person($error,true,null);
shn_form_fsclose();
    
 ?>
   
<br />
<center>
<?php
//create the submit button
    
	shn_form_submit("Submit");
?>
</center>
<br />
<?php
        //close the form
     	shn_form_fclose();
?>				     
</div>
<?php
}                                               
?>
