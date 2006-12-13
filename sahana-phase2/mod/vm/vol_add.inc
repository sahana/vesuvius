<?php
/* $Id: [sahana_home]/mod/vm/vol_add.inc,v 1.0 2006/06/12  */
/**
 *  Volunteer Registry Module -- generates the Volunteer Registry page.
 *
 *  <p>This file was previously called vm_vol_add.inc.
 *  It was adpated from the Organization Registry's 
 *  reg_vol.inc.  
 *  This file creates the registration form for  
 *  volunteers.  The data enetred into the form
 *  is passed to vol_reg, where it is entered 
 *  into the database.  
 *  The function shn_vm_vol_add() leads to the web get 
 *  query index.php?mod=vm&act=vol_add.</p>  
 *
 *  @package    Trinity_College_vm_demo
 *  @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 *  @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 *  @author     R. Morelli <ralph.morelli@trincoll.edu>
 *  @author     Jonathan Raye <jr978@bard.edu>
 *  @author     Ravindra <ravindra@opensource.lk>
 *  @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 */

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/mod/vm/lib_vm.inc";
include_once $global['approot']."/mod/vm/utility_functions.inc";
	include_once "auth_form.inc";


/** 
*  Creates the Volunteer Registry page.
*
*  This file creates the form that users fill in
*  to register as volunteers.  It has five fields:
*  Personal Details, Work Details, Availability, 
*  Address, and Contact Information.  At the bottom
*  of the Contact Information field is a "Submit" button.
*  When the user clicks this, the data he/she has entered 
*  is processed by the file vol_reg.inc. 
*
*  @param string $error  
*  @access public
*  @return void
*
*/
function shn_vm_vol_add($error=false)
{
    global $global;
    global $conf;
    $db=$global['db'];
    if(NULL!=$_POST{"uuid"}){  //this is in the case that we are coming from the add user page
	if(NULL==$_POST{"user_name"}){  //if they did not enter a user name, call user add again
	$header=array('method'=>'POST','action'=>'index.php?mod=vm&act=vol_add','id'=>'formset');
	shn_auth_form_user_add($title="Error - Must enter a user name.  Re-Submit User Name and Password", $header, $error=false, $_POST{"uuid"});
	}elseif($_POST{"password"}!=$_POST{"re_password"}){ //if password confirmation doesn't match
	$header=array('method'=>'POST','action'=>'index.php?mod=vm&act=vol_add','id'=>'formset');
	shn_auth_form_user_add($title="Error - Confirm your password.  Re-Submit User Name and Password", $header, $error=false, $_POST{"uuid"});
	}else{ //otherwise commit data to db and output a success message
	$account_name=$_POST{"account_name"};
	$user_name=$_POST{"user_name"};
	$password = md5(trim($_POST{"password"}));
	$p_uuid=$_POST{"uuid"};
	$q="insert into users(p_uuid, user_name, password) values ('{$p_uuid}','{$user_name}','{$password}');";
	$res=$db->Execute($q);
	?><h2><?=_("Your Account has been created.")?> </h2><br><?php
	}
    }else{ //in the case that we are navigating to this page


    if($_SESSION['logged_in'] != true){
    
        
?>
<h2><?=_("Volunteer Registry - Thank you for your help!")?> </h2><br><br>
<h3><?=_("To register, fill in as many of the below fields as possible.  When you are finished, click \"Submit\".")?> </h3>
<h3><?=_("Your registration will be confirmed via phone or email.")?> </h3>
<?php
    if($error)
        display_errors();
?>               
<div id="formcontainer">
<?php

    shn_form_fopen("vol_reg");
   
    shn_form_fsopen('Personal Details');
    $extra_opts['req']=true;
    shn_form_text(_("Name in Full : "),'name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    shn_form_date(_("Date of Birth : "),'dob', $initdate=NULL);
    echo "<br>";
//_shn_form_date(_("Date of Birth : "),'dob', $initdate=NULL, $required=true, $format='YYYY-MM-DD'); 
    _shn_form_select_gender($error,NULL);
    _shn_form_select_idtype($error,NULL);
    $extra_opts['req']=false;
    shn_form_text(_("Identification Number : "),'idnum','size="50"',$extra_opts);
    shn_form_fsclose();

    shn_form_fsopen("Work Details");
    _shn_form_select_organization($error, $parent_id=NULL, $label='Affiliation', $opt_organization_type=NULL, $extra_opts=NULL);
    shn_form_text(_("Occupation : "),'job','size="50"',$extra_opts); 
    $extra_opts['req']=false;
    _shn_form_select_specialities($error);
    shn_form_fsclose();

    shn_form_fsopen("Availability");
shn_form_date(_("Start Date : "),'start_date',$extra_opts=NULL);
	echo "<br>";
	shn_form_date(_("End Date : "),'end_date',$extra_opts=NULL);
	echo "<br>";

   // _shn_form_date(_("Start Date : "),'date_avail_start', $initdate=NULL, $required=true, $format='YYYY-MM-DD');
   // _shn_form_date(_("End Date : "),'date_avail_end', $initdate=NULL, $required=true, $format='YYYY-MM-DD');
    shn_form_text(_("Start Hours (e.g. 08:00) : "),'hrs_avail_start','size="10"',$extra_opts); 
    shn_form_text(_("End Hours (e.g. 17:00) : "),'hrs_avail_end','size="10"',$extra_opts); 
    shn_form_fsclose();

    //$location_inf = _shn_location_form_volunteer('2','3'); 
    shn_location_form_org(1,5);
   //shn_location(null,null,null,$extra_opts);
    
    shn_form_fsopen("Contact Information");
    _shn_form_get_contact_info($error, $org=false, $po_uuid=null);
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
}else{ //if they are a logged in user, not just a guest

?>
<h2><?=_("Edit your Personal Details")?> </h2><br><br>
<h3><?=_("Fill in as many of the below fields as possible.  When you are finished, click \"Submit\".")?> </h3>
<?php
    if($error)
        display_errors();
?>               
<div id="formcontainer">
<?php
	$q="select p_uuid from users where user_name='{$_SESSION['user']}'";
	$res=$db->Execute($q);
	$p_uuid=$res->fields[0];
	include_once("volunteer.inc");
    	$vol= new Volunteer($p_uuid);
	$vol->__construct($p_uuid); //populate data into volunteer object, from db given p_uuid

//$vol->printVolunteer();


    shn_form_fopen("edit_vol");
   ?><input type="hidden" name="p_uuid" value="<?php echo $p_uuid?>"><?php
    shn_form_fsopen('Personal Details');
    $extra_opts['req']=true;
    $extra_opts['value']=$vol->name;
    //shn_form_text(_("Name in Full : "),'name','size="50"',$extra_opts);
    //shn_form_text(_("Name in Full : "),'bogus','size="50"',$extra_opts);
    shn_form_text(_("Name in Full : "),'name','size="50"',$extra_opts);
 $extra_opts['req']=false;
    $extra_opts['value']=$vol->dob;
    shn_form_text(_("Date of Birth : "),'dob','size="10"',$extra_opts);
//    _shn_form_date(_("Date of Birth : "),'dob', $vol->dob, $required=true, $format='YYYY-MM-DD'); 
    _shn_form_select_gender($error,$vol->gender);
    $extra_opts['req']=false;
    _shn_form_select_idtype($error,$vol->id_type);
    //$extra_opts['req']=false;
    $extra_opts['value']=$vol->id_num;
    shn_form_text(_("Identification Number : "),'idnum','size="50"',$extra_opts);
    shn_form_fsclose();

    shn_form_fsopen("Work Details");
    $extra_opts['value']=$vol->org;
    _shn_form_select_organization($error, $parent_id=NULL, $label='Affiliation', $opt_organization_type=NULL, $extra_opts);
    $extra_opts['value']=$vol->job;
    shn_form_text(_("Occupation : "),'job','size="50"',$extra_opts); 
    $extra_opts['req']=false;

	//echo "ALERT: " . $vol->skills;
//this is not complete, must be passed an array of the volunteer's skill set as a second argument
    _shn_form_select_specialities($error,$vol->skills);
    shn_form_fsclose();

    shn_form_fsopen("Availability");
$extra_opts['req']=false;
    $extra_opts['value']=$vol->start_date;
    shn_form_text(_("Start Date : "),'date_avail_start','size="10"',$extra_opts);
     $extra_opts['req']=false;
    $extra_opts['value']=$vol->stop_date;
    shn_form_text(_("End Date : "),'date_avail_end','size="10"',$extra_opts);

//    _shn_form_date(_("Start Date : "),'date_avail_start', $vol->start_date, $required=true, $format='YYYY-MM-DD');
   // _shn_form_date(_("End Date : "),'date_avail_end', $vol->stop_date, $required=true, $format='YYYY-MM-DD');
    $extra_opts['value']=$vol->start_hour;
    shn_form_text(_("Start Hours (e.g. 08:00) : "),'hrs_avail_start','size="10"',$extra_opts); 
    $extra_opts['value']=$vol->stop_hour;
    shn_form_text(_("End Hours (e.g. 17:00) : "),'hrs_avail_end','size="10"',$extra_opts); 
    shn_form_fsclose();

    //$location_inf = _shn_location_form_volunteer('2','3'); 
    //shn_location(null,null,null,$extra_opts);
    shn_location_form_org(1,5,$vol->city);
   
    shn_form_fsopen("Contact Information");
    _shn_form_get_contact_info($error, $org=false, $vol->p_uuid);
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
}//else

}                                               
?>

