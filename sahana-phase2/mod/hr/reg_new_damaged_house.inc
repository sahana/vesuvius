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

function shn_hr_reg_new_damaged_house($edit=false)
{//Register New Damaged House
   _shn_hr_print_header(_t("Register New Damaged House(s)"));
   if ($edit) shn_hr_damaged_house_owner_information(true);
   else shn_hr_damaged_house_owner_information();
   shn_hr_damaged_house_basic_details();
   if ($edit) shn_hr_damaged_house_deed_upload(true);
   else shn_hr_damaged_house_deed_upload();
   shn_hr_damaged_house_location_details();
   if ($edit) shn_hr_damaged_house_location_details_gis(true);
   else shn_hr_damaged_house_location_details_gis();
}

function shn_hr_damaged_house_owner_information($set_edit_seq=false)
{
   include_once ('add_to_session.inc');
   
   shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
   if($set_edit_seq)
   {
    	shn_form_hidden(array('seq'=>'edit_registered_damaged_house'));
   }
   else 
   {
   	shn_form_hidden(array('seq'=>'reg_new_damaged_house'));
   }
   shn_form_fsopen(_t('Damaged House Owner Information'));


   print '<div class="info">';
   print _t("Please use this form to enter the unique id of the damaged house owner and/or head of the homeless family.");
   print '<br />';
   print _t("If you do on have an id you may create one by registering yourself into the Sahana system.");
   print '<br />';
   print '</div>';
   print '<br />';

   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'];
   $extra_opts['req']=true;
   $extra_opts['help']=(_t("Please specify the Unique ID created from this module or the" .  			       "Disaster Victim Registry module."));
   if($set_edit_seq) shn_form_text('Enter Your Unique ID','enter_uid','readonly=true',$extra_opts);
   else shn_form_text('Enter Your Unique ID','enter_uid',null,$extra_opts);


   shn_form_fsclose();
   print '<br />';
}

function shn_hr_damaged_house_basic_details()
{
   shn_form_fsopen(_t('Basic Details Of Damaged House'));


   print '<div class="info">';
   print _t("Please use this form to enter the basic details of the damaged house.");
   print '<br />';
   print '</div>';
   print '<br />';

   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_value'];
   $extra_opts['req']=false;
   $extra_opts['help']=(_t("Please specify the Monetary Value of the Damaged House"));
   shn_form_text('Estimated House Value','damaged_house_value',null,$extra_opts);

   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_total_sqft'];
   $extra_opts['req']=false;
   $extra_opts['help']=(_t("Please specify the Total Square Feet of the Damaged House"));
   shn_form_text(_t('Total Square Feet Of House'),'damaged_house_total_sqft',null,$extra_opts);

   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['optn_dstrctn_lvl'];
   $extra_opts['req']=true;
   $extra_opts['help']=(_t("Please specify the Destruction Level of the Damaged House"));
   shn_form_opt_select('optn_dstrctn_lvl','Destruction Level',null,$extra_opts);

   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_address'];
   $extra_opts['req']=false;
   $extra_opts['help']=(_t("Please specify the Address of the Damaged House"));
   shn_form_textarea(_t('Address Of House'),'damaged_house_address',null,$extra_opts);

   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_additional_details'];
   $extra_opts['req']=false;
   $extra_opts['help']=(_t("Please specify any Additional Details of the Damaged House"));
   shn_form_textarea(_t('Additional Details'),'damaged_house_additional_details',null,$extra_opts);


   shn_form_fsclose();
   print '<br />';
}

function shn_hr_damaged_house_deed_upload($set_edit_seq=false)
{
   global $global;
   global $conf;
   
   include_once $global['approot'].'/inc/lib_image.inc';
   
   shn_form_fsopen(_t('Upload Deed Copy Of Damaged House'));


   print '<div class="info">';
   print _t("Please use this form to upload a deed copy of the damaged house if available.");
   print '<br />';
   print '</div>';
   print '<br />';

   if($set_edit_seq)
   { 
	shn_show_thumb_url("hr_dd_img_".$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'],'database','hr','ad_dd_img',false);
		?><br /><?php
   }
   $extra_opts['value']=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_pic'];
   $extra_opts['req']=false;
   $extra_opts['help']=(_t("Please specify any Additional Details of the Damaged House"));
   shn_form_upload(_t('Upload Deed Copy'),"picture",$extra_opts);


   shn_form_fsclose();
   print '<br />';
}

function shn_hr_damaged_house_location_details()
{
   shn_form_fsopen(_t("Location Of Damaged House"));

   global $global;
   global $conf;
  
   include_once $global['approot'].'/inc/lib_location.inc';
   
   $parent=_shn_hr_get_start_loc();
   $range= shn_hr_get_loc_range();
   shn_location($range,$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details'],null,$parent);


   shn_form_fsclose();
   print '<br />';
}

function shn_hr_damaged_house_location_details_gis($set_edit_seq=false)
{
 
   global $global;
   global $conf;

   include_once $global['approot'].'/mod/gis/gis_fns.inc';
   
   if($set_edit_seq)
   {
   		shn_form_fopen("hr_damaged_house_location_details_gis");
    	$map_arr=array();
    	$url="mod=hr&act=add_to_session&edit_seq=edit_registered_damaged_house&damaged_house_uid=".$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'];
    	array_push($map_arr,array('lat'=>$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_x'],'lon'=>$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_y'],'name'=>$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'],'id'=>$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'],'url'=>$url));
		shn_gis_map_with_markers($map_arr);
   }
   else shn_gis_add_marker_map_form("GIS Map","Housing Registry");
   print '<br />';


   shn_form_fsclose();
   shn_form_submit(_t("Finish"));
   shn_form_fclose();
   print '<br />';
}
