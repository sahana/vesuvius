<?php
/**Registration related forms for Volunteers of the Organization Registry 
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
include_once "lib_vol.inc";

function _shn_vol_regform($error=false)
{
    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?=_("Volunteer Registration")?> </h2>
<?php
    if($error)
        display_errors();
?>               
<div id="formcontainer">
<?php
    shn_form_fopen("reg_vol_confirm");
   	shn_form_fsopen('Primary Details');
   	?><div class="info"><?= _("These are the basic details of a Volunteer. Name is required ,but others optional")."</div><br />";
    $extra_opts['req']=true;
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['name'];
    }
    shn_form_text(_("Name in Full : "),'name','size="50"',$extra_opts); 
    $extra_opts['req']=false;
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['dob'];
    }
    shn_form_text(_("Date of Birth (yyyy-mm-dd) : "),'dob','size="10"',$extra_opts); 
    //shn_form_date(_("Date of Birth: "),'dob', null ) ;

    shn_form_text(_("Occupation : "),'job','size="50"',$extra_opts); 
    _shn_vol_display_gender($error,NULL);
    shn_form_fsclose();
    shn_form_fsopen('Identity Information');
    ?><div class="info"><?= _("Please enter all the identity information you have. e.g Passport No ")."</div><br />";
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['nic'];
    }
    shn_form_text(_("National ID No : "),'nic','size="50"',$extra_opts); 
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['pas'];
    }
    shn_form_text(_("Passport No : "),'pas','size="50"',$extra_opts); 
    if($error==true){
    		$extra_opts['value']=$_SESSION['vol']['dln'];
    }
    shn_form_text(_("Driving License No : "),'dln','size="50"',$extra_opts); 
    shn_form_fsclose();
 // base location
    shn_form_fsopen("Base Location");
   	$parent=_shn_vol_get_start_loc();
   	$range= shn_vol_get_loc_range();
 	if($error==true){
 		shn_location($range,$_SESSION['vol']['loc']);
 	}else{
 		shn_location($range);
 	} 
    shn_form_fsclose();
   	shn_form_fsopen("Services Offered");
   	    
    if($error==true){
    		_shn_vol_display_sector($error,$_SESSION['vol']['sector']);
    }else{
    		_shn_vol_display_sector($error);
    }
  //  _shn_vol_display_sector($error);
    shn_form_fsclose();
    shn_form_fsopen("Contact Information");
    _shn_vol_display_contact_person($error,false,null);
    shn_form_fsclose();
    /*
    shn_form_fsopen("Extra Information");
    _shn_vol_display_extra(false);
    shn_form_fsclose();
    */
    $_SESSION["incident"]=$_POST["incidents"];
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
function _shn_vol_regconfirm()
{
	global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?= _('Confirm Registration Details of ').$_SESSION['vol']['name'] ?></h2>
<div id="formcontainer">
<?php
    shn_form_fopen("reg_cr",null,array('req_message'=>false,'name'=>"confirm_reg"));
    shn_form_fsopen('Primary Details');
    shn_form_label(_("Volunteer Name : "),$_SESSION['vol']['name']); 
    shn_form_label(_("Date of Birth : "),$_SESSION['vol']['dob']);
    shn_form_label(_("Occupation : "),$_SESSION['vol']['job']);  
 	shn_form_label(_("National Identity No : "),$_SESSION['vol']['nic']);
 	shn_form_label(_("Passport No : "),$_SESSION['vol']['pas']);
 	shn_form_label(_("Driving License No : "),$_SESSION['vol']['dln']); 
    $count=1;
    foreach ($_SESSION['vol']['sector'] as $i){
    		$q="select option_description from field_options where field_name='opt_sector_type' and option_code='{$i}'";
    		$res=$db->Execute($q);
    		$sector=$sector." ".$count.".".$res->Fields("option_description"); 
    		$count++;
    }
    shn_form_label(_("Volunteer Services"),$sector);
    shn_form_fsclose();
    /*
    // base location
    $parent=_shn_or_get_start_loc();
   	$range= shn_or_get_loc_range();
   	*/
   	shn_form_fsopen("Base Location");
	$location=_shn_vol_location_string($_SESSION['vol']['loc']);
 	shn_form_label(_("Volunteer Location"),$location);
   	shn_form_fsclose();
    
    // Contact infomation
    shn_form_fsopen("Contact Information");
    _shn_vol_display_contact_person($error,true,null);
    shn_form_fsclose();
 
 ?>
<br />
<center>
<?php
//create the submit button
	$extra_opts['br'] = false;
    shn_form_button(_("Save"),"onClick='change_action(\"close\")'",$extra_opts);
	shn_form_button(_("Edit Details"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
    _shn_vol_action_change_javascript("confirm_reg","action");
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
