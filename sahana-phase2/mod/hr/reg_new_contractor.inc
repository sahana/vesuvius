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

function shn_hr_reg_new_contractor($edit=false)
{//Register New Contractor
    _shn_hr_print_header(_t("Register New Contractor(s)"));
    if ($edit) shn_hr_contractor_information(true);
    else shn_hr_contractor_information();
    shn_hr_assign_site_to_contractor();
}

function shn_hr_contractor_information($set_edit_seq=false)
{
	include_once ('add_to_session.inc');
    
    shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
    if($set_edit_seq)
    {
    	shn_form_hidden(array('seq'=>'edit_registered_contractor'));
    }
    else 
    {
    	shn_form_hidden(array('seq'=>'reg_new_contractor'));
    }
    shn_form_fsopen(_t('Contractor Information'));


    print '<div class="info">';
    print _t("Please use this form to enter information about a contractor.");
    print '<br />';
    print '</div>';
    print '<br />';


    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['optn_contractor_level'];
    $extra_opts['req']=true;
    $extra_opts['help']=(_t("Please specify the Contractor Level"));
    shn_form_opt_select('optn_contractor_level','Contractor Level',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_name'];
    $extra_opts['req']=true; 
    $extra_opts['help']=_t("Please specify the Full Name");
    shn_form_text(_t("Full Name"),'contractor_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_uid'];
    $extra_opts['req']=true; 
    $extra_opts['help']=_t("Please create a Unique ID in order to identify the " . 				  "entry");
    if($set_edit_seq) shn_form_text(_t("Create Unique ID"),'contractor_uid','readonly=true',$extra_opts);
    else shn_form_text(_t("Create Unique ID"),'contractor_uid',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_dob'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Date Of Birth using the given format and/or ". 				"Calander");
    $extra_opts[$initdate]=null;
    shn_form_date(_t('Date Of Birth   (YYYY-MM-DD)'),'contractor_dob',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_adrs']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Address");
    shn_form_textarea(_t('Address'),"contractor_adrs", null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_pstl_cd']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Postal Code");
    shn_form_text(_t('Postal Code'),'contractor_pstl_cd','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_hm_phn']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Home Phone Number");
    shn_form_text(_t('Home Phone'),'contractor_hm_phn','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_mbl']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Mobile Number");
    shn_form_text(_t('Mobile'),'contractor_mbl','size="15"',$extra_opts);


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_assign_site_to_contractor()
{
    shn_form_fsopen(_t('Assign The Contractor To Site(s)'));


    print '<div class="info">';
    print _t("Please use this form to assign the contractor to one or multiple sites.");
    print '<br />';
    print _t("You may have to add one or more sites before using this feature.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['optn_unq_site_name'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Site(s) you wish to assign the Contractor to"));
    shn_form_opt_multi_select('optn_unq_site_name','Assign Contractor To Site(s)','multiple="true"',$extra_opts);
	

    shn_form_fsclose();
    shn_form_submit(_t("Finish"));
    shn_form_fclose();
    print '<br />';
}

?>
