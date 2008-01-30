<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Sheran Corera (sheran@opensource.lk) 
 * @copyright  Lanka Software Foundation (http://www.opensource.lk)
 * @package    mod
 * @subpackage hr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function shn_hr_reg_new_homeless_family($edit=false)
{//Family Head Information
    _shn_hr_print_header(_t("Register New Homeless Family(ies)"));
    if ($edit) shn_hr_family_head_details(true);
    else shn_hr_family_head_details();
}

function shn_hr_family_head_details($set_edit_seq=false)
{
	include_once ('add_to_session.inc');
	
    shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
    if($set_edit_seq)
    {
    	shn_form_hidden(array('seq'=>'edit_registered_hf'));
    }
    else 
    {
	shn_form_hidden(array('seq'=>'reg_new_homeless_family'));
    }
    shn_form_fsopen(_t('Head Of Family Information'));

    print '<div class="info">';
    print _t("Please use this form to enter information about the head of the homeless family.");
    print '<br />';
    print '</div>';
    print '<br />';

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name'];
    $extra_opts['req']=true; 
    $extra_opts['help']=_t("Please specify the Full Name");

    shn_form_text(_t("Full Name"),'family_head_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid'];
    $extra_opts['req']=true; 
    $extra_opts['help']=_t("Please create a Unique ID in order to identify the " . 				  "entry");
    if($set_edit_seq) shn_form_text(_t("Create Unique ID"),'family_head_create_uid','readonly=true',$extra_opts);
    else shn_form_text(_t("Create Unique ID"),'family_head_create_uid',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_dob'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Date Of Birth using the given format and/or ". 				"Calander");
    $extra_opts[$initdate]=null;
    shn_form_date(_t('Date Of Birth   (YYYY-MM-DD)'),'family_head_dob',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_address'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Address");
    shn_form_textarea(_t('Address'),"family_head_address", null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_postal_code'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Postal Code");
    shn_form_text(_t('Postal Code'),'family_head_postal_code','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_home_phone'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Home Phone Number");
    shn_form_text(_t('Home Phone'),'family_head_home_phone','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_mobile'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Mobile Number");
    shn_form_text(_t('Mobile'),'family_head_mobile','size="15"',$extra_opts);


    shn_form_fsclose();
    shn_form_submit(_t("Finish"));
    shn_form_fclose();
    print '<br />';
}
