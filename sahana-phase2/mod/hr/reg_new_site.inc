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

function shn_hr_reg_new_site($edit=false)
{//Register New Site

    _shn_hr_print_header(_t("Register New Site(s)"));
    if ($edit) shn_hr_site_name_and_uid(true);
    else shn_hr_site_name_and_uid();
    shn_hr_site_allocated_organization();
    shn_hr_site_main_coordinator_details();
    shn_hr_assign_contractor_to_site();
    shn_hr_site_hs_details();
    shn_hr_site_infrastructure_details();
    shn_hr_site_location();
    if ($edit) shn_hr_site_location_gis(true);
    else shn_hr_site_location_gis();

}

function shn_hr_site_name_and_uid($set_edit_seq=false)
{//Site Name
	include_once ('add_to_session.inc');
    
    shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
    if($set_edit_seq)
    {
    	shn_form_hidden(array('seq'=>'edit_registered_st'));
    }
    else 
    {
    	shn_form_hidden(array('seq'=>'reg_new_site'));
    }
    shn_form_fsopen(_t('Site Name And Unique ID'));


    print '<div class="info">';
    print _t("Please use this form to enter information about a site.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name'];
    $extra_opts['req']=true;
    $extra_opts['help']=(_t("Please specify the Site Name"));
    shn_form_text(_t('Site Name'),'site_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid'];
    $extra_opts['req']=true;
    $extra_opts['help']=(_t("Please create a Unique ID in order to identify the Site"));
    if($set_edit_seq) shn_form_text(_t('Unique ID'),'site_uid','readonly=true',$extra_opts);
    else shn_form_text(_t('Unique ID'),'site_uid',null,$extra_opts);


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_site_allocated_organization()
{//Allocated Organization

    shn_form_fsopen(_t('Allocated Organization'));


    print '<div class="info">';
    print _t("Please use this form to select the allocated organization of the site.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization'];
    $extra_opts['req']=true;
    $extra_opts['help']=(_t("Please specify the Allocated Organization"));
    shn_form_opt_select('optn_site_allocated_organization','Allocated Organization',null,$extra_opts);


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_site_main_coordinator_details()
{//Main Coordinator Details
    shn_form_fsopen(_t('Main Coordinator Details'));


    print '<div class="info">';
    print _t("Please use this form to enter information about the main coordinator of the site.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name'];
    $extra_opts['req']=true; 
    $extra_opts['help']=_t("Please specify the Full Name");
    shn_form_text(_t("Full Name"),'site_main_coordinator_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_dob'];
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Date Of Birth using the given format and/or ". 				"Calander");
    $extra_opts[$initdate]=null;
    shn_form_date(_t('Date Of Birth   (YYYY-MM-DD)'),'site_main_coordinator_dob',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_adrs']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Address");
    shn_form_textarea(_t('Address'),'main_coordinator_adrs', null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_pstl_cd']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Postal Code");
    shn_form_text(_t('Postal Code'),'main_coordinator_pstl_cd','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_hm_phn']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Home Phone Number");
    shn_form_text(_t('Home Phone'),'main_coordinator_hm_phn','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_mbl']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Mobile Number");
    shn_form_text(_t('Mobile'),'main_coordinator_mbl','size="15"',$extra_opts);


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_assign_contractor_to_site()
{
    shn_form_fsopen(_t('Assign The Site To Contractor(s)'));


    print '<div class="info">';
    print _t("Please use this form to assign the site to one or multiple contractors.");
    print '<br />';
    print _t("You may have to add one or more contractors before using this feature.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Site(s) you wish to assign the Contractor to"));
    shn_form_opt_multi_select('optn_unq_contractor_name','Assign Site To Contractor(s)','multiple="true"',$extra_opts);
	

    shn_form_fsclose();
    print '<br />';
}

function shn_hr_site_hs_details()
{//House Details
    shn_form_fsopen(_t('House Details'));


    print '<div class="info">';
    print _t("Please use this form to enter information about the houses of the site.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_hs_details']['planned_houses']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Number Of Planned Houses");
    shn_form_text(_t('Number Planned'),'planned_houses','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_hs_details']['constructed_houses']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Number Of Constructed Houses");
    shn_form_text(_t('Number Constructed'),'constructed_houses','size="15"',$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_hs_details']['vacant_houses']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Number Of Vacant Houses");
    shn_form_text(_t('Number Vacant'),'vacant_houses','size="15"',$extra_opts);


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_site_infrastructure_details()
{//Infrastructure
    shn_form_fopen("st_infrastructure_details",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_t('Site Infrastructure Details'));


    print '<div class="info">';
    print _t("Please use this form to select the available infrastructure of the site.");
    print '<br />';
    print '</div>';
    print '<br />'; 

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_road']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Road Availability");
    shn_form_opt_select('optn_road','Road',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_water']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Water Availability");
    shn_form_opt_select('optn_water','Water',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_electricity']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Electricity Availability");
    shn_form_opt_select('optn_electricity','Electricity',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_telephone_or_communication']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Telephone / Communication Availability");
    shn_form_opt_select('optn_telephone_or_communication','Telephone / Communication',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_sewer']; 
    $extra_opts['req']=false;
    $extra_opts['help']=_t("Please specify the Sewer / Drainage System Availability");
    shn_form_opt_select('optn_sewer','Sewer',null,$extra_opts);


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_site_location()
{
    shn_form_fsopen(_t("Location Of House"));

    global $global;
    global $conf;
  
    include_once $global['approot'].'/inc/lib_location.inc';
    
    $parent=_shn_hr_get_start_loc();
    $range= shn_hr_get_loc_range();
    shn_location($range,$_SESSION['hr']['reg_new_site']['site_location'],null,$parent); 


    shn_form_fsclose();
    print '<br />';
}

function shn_hr_site_location_gis($set_edit_seq=false)
{ 
	
   global $global;
   global $conf;

   include_once $global['approot'].'/inc/lib_gis/gis_fns.inc';

   if($set_edit_seq)
   {
   		shn_form_fopen("hr_site_location_gis");
    	$map_arr=array();
    	$url="mod=hr&act=add_to_session&edit_seq=edit_registered_st&site_uid=".$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid'];
    	array_push($map_arr,array('lat'=>$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_x'],'lon'=>$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_y'],'name'=>$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name'],'id'=>$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid'],'url'=>$url));
		shn_gis_map_with_markers($map_arr);
   }
   else shn_gis_add_marker_map_form("GIS Map","Housing Registry");
   print '<br />';


   shn_form_fsclose();
   shn_form_submit(_t("Finish"));
   shn_form_fclose();
   print '<br />';
}
