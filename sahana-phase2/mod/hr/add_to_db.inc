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

function shn_hr_add_to_db($function_string=null)
{	
	switch($function_string)
	{
		case "reg_new_homeless_family":
			shn_hr_add_updt_hf_to_dbs();
			shn_hr_reg_new_homeless_family();
			break;
		case "reg_new_damaged_house":
			shn_hr_add_updt_damaged_house_to_dbs();
			shn_hr_reg_new_damaged_house();
			break;
		case "reg_new_contractor":
			shn_hr_add_updt_contractor_to_dbs();
			shn_hr_reg_new_contractor();
			break;
		case "reg_new_site":
			shn_hr_add_updt_site_to_dbs();
			shn_hr_reg_new_site();
			break;

		case "edit_registered_hf":
			if((shn_hr_add_updt_hf_to_dbs(true)==true)) shn_hr_reg_new_homeless_family(true);
			else shn_hr_reg_new_homeless_family();
			break;
		case "edit_registered_damaged_house":
			if((shn_hr_add_updt_damaged_house_to_dbs(true)==true)) shn_hr_reg_new_damaged_house(true);
			else shn_hr_reg_new_damaged_house();
			break;
		case "edit_registered_contractor":
			if((shn_hr_add_updt_contractor_to_dbs(true)==true)) shn_hr_reg_new_contractor(true);
			else shn_hr_reg_new_contractor();
			break;
		case "edit_registered_st":
			if((shn_hr_add_updt_site_to_dbs(true)==true)) shn_hr_reg_new_site(true);
			else shn_hr_reg_new_site();
			break;
			
		case "assign_to_site_dbs":
			shn_hr_assign_to_site_dbs();
			shn_hr_assign_to_site();
			break;
		case "assign_contractor_dbs":
			shn_hr_assign_contractor_dbs();
			shn_hr_assign_contractor();
			break;
	}
}


function shn_hr_add_updt_hf_to_dbs($updt=false)
{
	global $global;
	global $conf;
	$db = $global['db'];

    include_once $global['approot'].'/inc/lib_validate.inc';
    include_once $global['approot'].'/inc/lib_errors.inc';
    include_once $global['approot'].'/inc/lib_gis/gis_fns.inc';

	$reg_new_homeless_family_err=false;

	if(!shn_valid_date($_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_dob']))$reg_new_homeless_family_err=true;
	if($_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name']==""||$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid']=="")
	{
		if($_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name']=="")
		{
			add_error("Please enter the Full Name of the Head of Family");
		}
		if($_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid']=="")
		{
			add_error("Please enter a Unique ID");
		}
		add_error("Please fill all the Required fields marked *req.");
		$reg_new_homeless_family_err=true;
	}

	$error_validate_reg_new_homeless_family_q="select COUNT(family_head_create_uid) as c from hr_family_head_details_table where hr_family_head_details_table.family_head_create_uid='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid']}'";
	$error_validate_reg_new_homeless_family_res=$db->Execute($error_validate_reg_new_homeless_family_q);
	$error_validate_res_reg_new_homeless_family_rslt=$error_validate_reg_new_homeless_family_res->fields['c'];

	if($error_validate_res_reg_new_homeless_family_rslt>0 && $updt==false)
	{
		add_error("The selected Unique ID already exists. Please select a different ID");
		$reg_new_homeless_family_err=true;
	}
	if(!$reg_new_homeless_family_err)
	{
		$hf_and_damaged_house_uid=$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid'];
		$hf_and_damaged_house_gis_uid="hr_damaged_house_gis_uid_".$hf_and_damaged_house_uid;
		$hf_and_damaged_house_contact_uid="hf_and_damaged_house_contact_".$hf_and_damaged_house_uid;
		
		$q="INSERT INTO hr_family_head_details_table(family_head_name,family_head_create_uid,family_head_dob)VALUES('{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name']}','{$hf_and_damaged_house_uid}','{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_dob']}')";
		$q2="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$hf_and_damaged_house_contact_uid}','fhd_adrs','{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_address']}')";
		$q3="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$hf_and_damaged_house_contact_uid}','fhd_pcd','{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_postal_code']}')";
		$q4="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$hf_and_damaged_house_contact_uid}','fhd_hm_phn','{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_home_phone']}')";
		$q5="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$hf_and_damaged_house_contact_uid}','fhd_mbl','{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_mobile']}')";
		$q6="INSERT INTO hr_damaged_house_basic_details_table(damaged_house_basic_details_uid,damaged_house_destruction_level)VALUES('{$hf_and_damaged_house_uid}','nt_slctd')"; 
		$q7="INSERT INTO hr_damaged_house_location_details_table(damaged_house_location_uid,damaged_house_location)VALUES('{$hf_and_damaged_house_uid}','-1')"; //-1 is no location according to the location table
		$updt_q="UPDATE hr_family_head_details_table SET family_head_name='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name']}',family_head_dob='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_dob']}' WHERE hr_family_head_details_table.family_head_create_uid='{$hf_and_damaged_house_uid}'";
		$updt_q2="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_address']}' WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_adrs'";
		$updt_q3="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_postal_code']}' WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_pcd'";
		$updt_q4="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_home_phone']}' WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_hm_phn'";
		$updt_q5="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_mobile']}' WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_mbl'";


		if($updt==false)
		{
   			$res=$db->Execute($q);
			$res2=$db->Execute($q2);
			$res3=$db->Execute($q3);
   			$res4=$db->Execute($q4);
   			$res5=$db->Execute($q5);
   			$res6=$db->Execute($q6);
   			$res7=$db->Execute($q7);
			shn_gis_dbinsert($hf_and_damaged_house_gis_uid,0,null,$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_x'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_y'],null);
			
			add_confirmation("Successfully added to the Database");
			session_unset(); 
		}
		else
		{
   			$updt_res=$db->Execute($updt_q);
   			$updt_res=$db->Execute($updt_q2);
   			$updt_res=$db->Execute($updt_q3);
   			$updt_res=$db->Execute($updt_q4);
   			$updt_res=$db->Execute($updt_q5);
			add_confirmation("Successfully updated to the Database");
			session_unset(); 
		}
	}
	return $reg_new_homeless_family_err;
}

function shn_hr_add_updt_damaged_house_to_dbs($updt=false)
{
	global $global;
	global $conf;
	$db = $global['db'];
    
    include_once $global['approot'].'/inc/lib_image.inc';
    include_once $global['approot'].'/inc/lib_validate.inc';
    include_once $global['approot'].'/inc/lib_errors.inc';
	
	$reg_new_damaged_house_err=false;

	if($_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid']==""||$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['optn_dstrctn_lvl']=="nt_slctd")
	{
		if($_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid']=="")
		{
			add_error("Please enter your Unique ID");
		}
		if($_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['optn_dstrctn_lvl']=="nt_slctd")
		{
			add_error("Please select a Distruction Level");
		}
		add_error("Please fill all the Required fields marked *req.");
		$reg_new_damaged_house_err=true;
	}
	
	$error_validate_reg_new_damaged_house_q="select COUNT(family_head_create_uid) as c from hr_family_head_details_table where hr_family_head_details_table.family_head_create_uid='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid']}'";
	$error_validate_reg_new_damaged_house_res=$db->Execute($error_validate_reg_new_damaged_house_q);
	$error_validate_res_reg_new_damaged_house_rslt=$error_validate_reg_new_damaged_house_res->fields['c'];

	if($error_validate_res_reg_new_damaged_house_rslt==0 && $updt==false)
	{
		add_error("The selected Unique ID does not exist. Please selected an existing ID");
		$reg_new_damaged_house_err=true;
	}
	if(!$reg_new_damaged_house_err)
	{

		$damaged_house_uid=$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'];
		$hf_and_damaged_house_gis_uid="hr_damaged_house_gis_uid_".$damaged_house_uid;

		$q="UPDATE hr_damaged_house_basic_details_table SET damaged_house_value='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_value']}', damaged_house_total_sqft='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_total_sqft']}', damaged_house_destruction_level='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['optn_dstrctn_lvl']}', damaged_house_address='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_address']}', damaged_house_additional_details ='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_additional_details']}' WHERE hr_damaged_house_basic_details_table.damaged_house_basic_details_uid='{$damaged_house_uid}'";
		$q2="UPDATE hr_damaged_house_location_details_table SET damaged_house_location='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details']}' WHERE hr_damaged_house_location_details_table.damaged_house_location_uid='{$damaged_house_uid}'";
		$q3="UPDATE gis_location SET map_northing='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_x']}',map_easting='{$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_y']}' WHERE gis_location.poc_uuid='{$hf_and_damaged_house_gis_uid}'";

		$hr_dd_img_x_uuid="hr_dd_img_".$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'];
		$img_updt_cnt_q5="SELECT COUNT(x_uuid) AS c FROM image WHERE image.x_uuid='{$hr_dd_img_x_uuid}'";
		$img_updt_dlt_q6="DELETE FROM image WHERE image.x_uuid='{$hr_dd_img_x_uuid}'";

		$img_updt_cnt_res5=$db->Execute($img_updt_cnt_q5);//CHECK IF YOU ARE REPLACING A IMAGE OR ADDING A NEW ONE
	
		if($_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['img_fld_nt_blnk'])
		{
			if($img_updt_cnt_res5->fields['c']==0) shn_image_to_db_ex("hr_dd_img_".$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_pic'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_ext'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_info1'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_info0']);
			else
			{
				$img_updt_dlt_res6=$db->Execute($img_updt_dlt_q6);
				shn_image_to_db_ex("hr_dd_img_".$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_pic'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_ext'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_info1'],$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_info0']);
				
			}
		}

		if($updt==false)
		{
   			$res=$db->Execute($q);
			$res2=$db->Execute($q2);
			$res3=$db->Execute($q3);

			add_confirmation("Successfully added to the Database");
			session_unset(); 
		}
		else
		{
   			$updt_res=$db->Execute($q);
			$updt_res2=$db->Execute($q2);
			//$updt_res3=$db->Execute($q3); Since the GIS MAPPING CANNOT BE CHANGED!!
			
			add_confirmation("Successfully updated to the Database");
			session_unset(); 
		}
	}
	return $reg_new_damaged_house_err;
}

function shn_hr_add_updt_contractor_to_dbs($updt=false)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	include_once $global['approot'].'/inc/lib_validate.inc';
	include_once $global['approot'].'/inc/lib_errors.inc';

	$reg_new_contractor_err=false;

	if(!shn_valid_date($_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_dob']))$reg_new_contractor_err=true;
	if($_SESSION['hr']['reg_new_contractor']['contractor_information']['optn_contractor_level']=="nt_slctd"||$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_uid']=="")
	{
		if($_SESSION['hr']['reg_new_contractor']['contractor_information']['optn_contractor_level']=="nt_slctd")
		{
			add_error("Please select a Contractor Level");
		}
		if($_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_name']=="")
		{
			add_error("Please enter the Full Name of the Contractor");
		}
		if($_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_uid']=="")
		{
			add_error("Please enter a Unique ID");
		}
		add_error("Please fill all the Required fields marked *req.");
		$reg_new_contractor_err=true;
	}

	$error_validate_reg_new_contractor_q="select COUNT(contractor_uid) as c from hr_contractor_table where hr_contractor_table.contractor_uid='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_uid']}'";
	$error_validate_reg_new_contractor_res=$db->Execute($error_validate_reg_new_contractor_q);
	$error_validate_res_reg_new_contractor_rslt=$error_validate_reg_new_contractor_res->fields['c'];

	if($error_validate_res_reg_new_contractor_rslt>0 && $updt==false)
	{
		add_error("The selected Unique ID already exists. Please select a different ID");
		$reg_new_contractor_err=true;
	}
	if(!$reg_new_contractor_err)
	{	
		$contractor_uid=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_uid'];
		$contractor_name_and_uid_string=$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_name']."-".$contractor_uid;
		$contractor_contact_uid="contractor_contact_".$contractor_uid;

		if($_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['optn_unq_site_name']!=NULL) $assign_site_to_contractor_string=implode(",", $_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['optn_unq_site_name']);
		else $assign_site_to_contractor_string="";
 			
		$q="INSERT INTO hr_contractor_table(contractor_level,contractor_name,contractor_uid,contractor_dob)values('{$_SESSION['hr']['reg_new_contractor']['contractor_information']['optn_contractor_level']}','{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_name']}','{$contractor_uid}','{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_dob']}')";
   		$q2="INSERT INTO hr_assign_site_to_contractor_table(assign_site_to_contractor_uid,assign_site_to_contractor)values('{$contractor_uid}','{$assign_site_to_contractor_string}')";
		$q3="INSERT INTO field_options VALUES('optn_unq_contractor_name','{$contractor_uid}','{$contractor_name_and_uid_string}')";
		$q4="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$contractor_contact_uid}','cnt_adrs','{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_adrs']}')";
		$q5="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$contractor_contact_uid}','cnt_pcd','{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_pstl_cd']}')";
		$q6="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$contractor_contact_uid}','cnt_hm_phn','{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_hm_phn']}')";
		$q7="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$contractor_contact_uid}','cnt_mbl','{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_mbl']}')";
		$updt_q="UPDATE hr_contractor_table SET contractor_level='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['optn_contractor_level']}',contractor_name='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_name']}',contractor_dob='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_dob']}' WHERE hr_contractor_table.contractor_uid='{$contractor_uid}'";
		$updt_q2="UPDATE hr_assign_site_to_contractor_table SET assign_site_to_contractor='{$assign_site_to_contractor_string}' WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$contractor_uid}'";
		$updt_q3="UPDATE field_options SET option_description='{$contractor_name_and_uid_string}' WHERE field_options.option_code='{$contractor_uid}'";
		$updt_q4="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_adrs']}' WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_adrs'";
		$updt_q5="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_pstl_cd']}' WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_pcd'";
		$updt_q6="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_hm_phn']}' WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_hm_phn'";
		$updt_q7="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_mbl']}' WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_mbl'";

   		
		if($updt==false)
		{
   			$res=$db->Execute($q);
			$res2=$db->Execute($q2);
			$res3=$db->Execute($q3);
			$res4=$db->Execute($q4);
			$res5=$db->Execute($q5);
			$res6=$db->Execute($q6);
			$res7=$db->Execute($q7);
			
			shn_hr_assign_to_site_dbs(true,false,$assign_site_to_contractor_string,$contractor_uid);
			
			add_confirmation("Successfully added to the Database");
			session_unset(); 
		}
		else
		{
   			$updt_res=$db->Execute($updt_q);
			$updt_res3=$db->Execute($updt_q3);
			$updt_res4=$db->Execute($updt_q4);
			$updt_res5=$db->Execute($updt_q5);
			$updt_res6=$db->Execute($updt_q6);
			$updt_res7=$db->Execute($updt_q7);
			
			shn_hr_assign_to_site_dbs(false,true,$assign_site_to_contractor_string,$contractor_uid);
			$updt_res2=$db->Execute($updt_q2);
			
			add_confirmation("Successfully updated to the Database");
			session_unset(); 
		}
	}
	return $reg_new_contractor_err;
}

function shn_hr_add_updt_site_to_dbs($updt=false)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	include_once $global['approot'].'/inc/lib_validate.inc';
	include_once $global['approot'].'/inc/lib_errors.inc';
	include_once $global['approot'].'/inc/lib_gis/gis_fns.inc';

	$reg_new_site_err=false;

	if(!shn_valid_date($_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_dob']))$reg_new_site_err=true;
	if($_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']==""||$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid']==""||$_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization']=="nt_slctd"||$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name']=="")
	{
		if($_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']=="")
		{
			add_error("Please enter the Site Name");
		}
		if($_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid']=="")
		{
			add_error("Please enter a Unique ID");
		}
		if($_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization']=="nt_slctd")
		{
			add_error("Please select the Allocated Organization");
		}
		if($_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name']=="")
		{
			add_error("Please enter the Full Name of the Main Coordinator");
		}
		add_error("Please fill all the Required fields marked *req.");
		$reg_new_site_err=true;
	}

	$error_validate_reg_new_site_q="select COUNT(site_uid) as c from hr_site_name_and_uid_table where hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid']}'";
	$error_validate_reg_new_site_res=$db->Execute($error_validate_reg_new_site_q);
	$error_validate_res_reg_new_site_rslt=$error_validate_reg_new_site_res->fields['c'];
	
	if($error_validate_res_reg_new_site_rslt>0 && $updt==false)
	{
		add_error("The selected Unique ID already exists. Please select a different ID");
		$reg_new_site_err=true;
	}

	if(!$reg_new_site_err)
	{
		
		$site_uid=$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid'];
		$site_name_and_uid_string=$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']."-".$site_uid;
		$site_gis_uid="st_gis_uid_".$site_uid;
		$site_mcd_contact_uid="st_mcd_contact_".$site_uid;

		if($_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name']!=NULL) $assign_contractor_to_site_string=implode(",", $_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name']);
		else $assign_contractor_to_site_string="";

		$q="INSERT INTO hr_site_name_and_uid_table(site_name,site_uid)VALUES('{$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']}','{$site_uid}')";
   		$q2="INSERT INTO hr_assign_contractor_to_site_table(assign_contractor_to_site_uid,assign_contractor_to_site)VALUES('{$site_uid}','{$assign_contractor_to_site_string}')";
		$q3="INSERT INTO field_options VALUES('optn_unq_site_name','{$site_uid}','{$site_name_and_uid_string}')";
		$q4="INSERT INTO hr_site_allocated_organization_table(site_allocated_organization_uid,site_allocated_organization)VALUES('{$site_uid}','{$_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization']}')";
		$q5="INSERT INTO hr_site_main_coordinator_details_table(site_main_coordinator_details_uid,site_main_coordinator_name,site_main_coordinator_dob)VALUES('{$site_uid}','{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name']}','{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_dob']}')"; 
		$q6="INSERT INTO hr_site_house_details_table(site_house_details_uid,planned_houses,constructed_houses,vacant_houses)VALUES('{$site_uid}','{$_SESSION['hr']['reg_new_site']['site_hs_details']['planned_houses']}','{$_SESSION['hr']['reg_new_site']['site_hs_details']['constructed_houses']}','{$_SESSION['hr']['reg_new_site']['site_hs_details']['vacant_houses']}')";
		$q7="INSERT INTO hr_site_infrastructure_details_table(site_infrastructure_details_uid,road,water,electricity,telephone_or_communication,sewer)VALUES('{$site_uid}','{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_road']}','{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_water']}','{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_electricity']}','{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_telephone_or_communication']}','{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_sewer']}')";
		$q8="INSERT INTO hr_site_location_details_table(site_location_uid,site_location)VALUES('{$site_uid}','{$_SESSION['hr']['reg_new_site']['site_location']}')";
		$q9="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$site_mcd_contact_uid}','smc_adrs','{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_adrs']}')";
		$q10="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$site_mcd_contact_uid}','smc_pcd','{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_pstl_cd']}')";
		$q11="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$site_mcd_contact_uid}','smc_hm_phn','{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_hm_phn']}')";
		$q12="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value)VALUES('{$site_mcd_contact_uid}','smc_mbl','{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_mbl']}')";
		
		$updt_q="UPDATE hr_site_name_and_uid_table SET site_name='{$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']}' WHERE hr_site_name_and_uid_table.site_uid='{$site_uid}'";
		$updt_q2="UPDATE hr_assign_contractor_to_site_table SET assign_contractor_to_site='{$assign_contractor_to_site_string}' WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$site_uid}'";
		$updt_q3="UPDATE field_options SET option_description='{$site_name_and_uid_string}' WHERE field_options.option_code='{$site_uid}'";
		$updt_q4="UPDATE hr_site_allocated_organization_table SET site_allocated_organization='{$_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization']}' WHERE hr_site_allocated_organization_table.site_allocated_organization_uid='{$site_uid}'";
		$updt_q5="UPDATE hr_site_main_coordinator_details_table SET site_main_coordinator_name='{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name']}',site_main_coordinator_dob='{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_dob']}' WHERE hr_site_main_coordinator_details_table.site_main_coordinator_details_uid='{$site_uid}'";
		$updt_q6="UPDATE hr_site_house_details_table SET planned_houses='{$_SESSION['hr']['reg_new_site']['site_hs_details']['planned_houses']}',constructed_houses='{$_SESSION['hr']['reg_new_site']['site_hs_details']['constructed_houses']}',vacant_houses='{$_SESSION['hr']['reg_new_site']['site_hs_details']['vacant_houses']}' WHERE hr_site_house_details_table.site_house_details_uid='{$site_uid}'";
		$updt_q7="UPDATE hr_site_infrastructure_details_table SET road='{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_road']}',water='{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_water']}',electricity='{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_electricity']}',telephone_or_communication='{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_telephone_or_communication']}',sewer='{$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_sewer']}' WHERE hr_site_infrastructure_details_table.site_infrastructure_details_uid='{$site_uid}'";
		$updt_q8="UPDATE hr_site_location_details_table SET site_location='{$_SESSION['hr']['reg_new_site']['site_location']}' WHERE hr_site_location_details_table.site_location_uid='{$site_uid}'";
		$updt_q9="UPDATE gis_location SET map_northing='{$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_x']}',map_easting='{$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_y']}' WHERE gis_location.poc_uuid='{$site_gis_uid}'";
		$updt_q10="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_adrs']}' WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_adrs'";
		$updt_q11="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_pstl_cd']}' WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_pcd'";
		$updt_q12="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_hm_phn']}' WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_hm_phn'";
		$updt_q13="UPDATE contact SET contact_value='{$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_mbl']}' WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_mbl'";



		if($updt==false)
		{
   			$res=$db->Execute($q);
			$res2=$db->Execute($q2);
			$res3=$db->Execute($q3);
   			$res4=$db->Execute($q4);
			$res5=$db->Execute($q5);
			$res6=$db->Execute($q6);
   			$res7=$db->Execute($q7);
   			$res8=$db->Execute($q8);
   			$res9=$db->Execute($q9);
   			$res10=$db->Execute($q10);
   			$res11=$db->Execute($q11);
   			$res12=$db->Execute($q12);
   			shn_gis_dbinsert($site_gis_uid,0,null,$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_x'],$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_y'],null);
   			
   			shn_hr_assign_contractor_dbs(true,false,$assign_contractor_to_site_string,$site_uid);
			
			add_confirmation("Successfully added to the Database");
			session_unset(); 
		}
		else
		{
   			$updt_res=$db->Execute($updt_q);
			$updt_res3=$db->Execute($updt_q3);
			$updt_res4=$db->Execute($updt_q4);
			$updt_res5=$db->Execute($updt_q5);
			$updt_res6=$db->Execute($updt_q6);
			$updt_res7=$db->Execute($updt_q7);
			$updt_res8=$db->Execute($updt_q8);
			//$updt_res9=$db->Execute($updt_q9); SINCE GIS CANNOT BE CHANGED!!!
			$updt_res10=$db->Execute($updt_q10);
			$updt_res11=$db->Execute($updt_q11);
			$updt_res12=$db->Execute($updt_q12);
			$updt_res13=$db->Execute($updt_q13);
			
			shn_hr_assign_contractor_dbs(false,true,$assign_contractor_to_site_string,$site_uid);
			$updt_res2=$db->Execute($updt_q2);//This has to run AFTER THE METHOD!!!
			
			add_confirmation("Successfully updated to the Database");
			session_unset(); 
		}
	}
	return $reg_new_site_err;
}

function shn_hr_assign_to_site_dbs($add=false,$updt=false,$assign_site_to_contractor_string=NULL,$contractor_uid=NULL)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	include_once $global['approot'].'/inc/lib_errors.inc';
	
	if($add||$updt)
	{
		$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['slctd_string']=$assign_site_to_contractor_string;
		$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid']=$contractor_uid;
	}
	
	if($add==false)
	{
		$assign_to_site_updt_q="SELECT assign_site_to_contractor AS s FROM hr_assign_site_to_contractor_table WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid']}'";
		$assign_to_site_updt_res=$db->Execute($assign_to_site_updt_q);
		$assign_site_to_contractor_string=$assign_to_site_updt_res->fields['s'];
		$assign_site_to_contractor_array=array();
		$assign_site_to_contractor_array=explode(",",$assign_site_to_contractor_string);
		
		for($i=0;$i<count($assign_site_to_contractor_array);$i++)
		{
			$assign_contractor_uid=$assign_site_to_contractor_array[$i];
	    		$assign_to_site_updt_q2="SELECT assign_contractor_to_site AS s FROM hr_assign_contractor_to_site_table WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$assign_contractor_uid}'";
	    		$assign_to_site_updt_res2=$db->Execute($assign_to_site_updt_q2);
	    		$assign_contractor_string=$assign_to_site_updt_res2->fields['s'];
	    		$assign_contractor_array=array();
			$assign_contractor_array=explode(",",$assign_contractor_string);
			$assign_contractor="";
			for($k=0;$k<count($assign_contractor_array);$k++)
			{ 
				if($_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid']!=$assign_contractor_array[$k])	$assign_contractor.=$assign_contractor_array[$k].",";
			}
			if($assign_contractor!="") $assign_contractor=substr($assign_contractor, 0, -1);
			$assign_contractor_q="UPDATE hr_assign_contractor_to_site_table SET assign_contractor_to_site='{$assign_contractor}' WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$assign_contractor_uid}'";
			$assign_contractor_res=$db->Execute($assign_contractor_q);
		}
	}
	
	$assign_contractor_slctd_string_array=array();
	$assign_contractor_slctd_string_array=explode(",",$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['slctd_string']);
	
	for($n=0;$n<count($assign_contractor_slctd_string_array);$n++)
	{
		$assign_contractor_slctd=$assign_contractor_slctd_string_array[$n];
		$assign_to_site_updt_q3="SELECT assign_contractor_to_site AS s FROM hr_assign_contractor_to_site_table WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$assign_contractor_slctd}'";
	    	$assign_to_site_updt_res3=$db->Execute($assign_to_site_updt_q3);
	    	$assign_contractor_slctd_string=$assign_to_site_updt_res3->fields['s'];
	    
	    	if($assign_contractor_slctd_string=="") $assign_contractor_slctd_string.=$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid'];
		else $assign_contractor_slctd_string.=",".$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid'];
		
		$assign_to_site_updt_q4="UPDATE hr_assign_contractor_to_site_table SET assign_contractor_to_site='{$assign_contractor_slctd_string}' WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$assign_contractor_slctd}'";
		$assign_to_site_updt_res4=$db->Execute($assign_to_site_updt_q4);
	}
	
	if($add==false && $updt==false)
	{
		$assign_to_site_updt_q5="UPDATE hr_assign_site_to_contractor_table SET assign_site_to_contractor='{$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['slctd_string']}' WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid']}'";
		$assign_to_site_updt_res5=$db->Execute($assign_to_site_updt_q5);
		add_confirmation("Successfully updated to the Database");
		session_unset(); 
	}
}

function shn_hr_assign_contractor_dbs($add=false,$updt=false,$assign_contractor_to_site_string=NULL,$site_uid=NULL)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	include_once $global['approot'].'/inc/lib_errors.inc';
	
	if($add||$updt)
	{
		$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['slctd_string']=$assign_contractor_to_site_string;
		$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid']=$site_uid;
	}
	
	if($add==false)
	{
		$assign_contractor_updt_q="SELECT assign_contractor_to_site AS s FROM hr_assign_contractor_to_site_table WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid']}'";
		$assign_contractor_updt_res=$db->Execute($assign_contractor_updt_q);
		$asign_contractor_string=$assign_contractor_updt_res->fields['s'];
		$asign_contractor_array=array();
		$asign_contractor_array=explode(",",$asign_contractor_string);
	
		for($i=0;$i<count($asign_contractor_array);$i++)
		{
			$asgn_site_to_contractor_uid=$asign_contractor_array[$i];
	    		$assign_contractor_updt_q2="SELECT assign_site_to_contractor AS s FROM hr_assign_site_to_contractor_table WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$asgn_site_to_contractor_uid}'";
	    		$assign_contractor_updt_res2=$db->Execute($assign_contractor_updt_q2);
	    		$assign_to_site_string=$assign_contractor_updt_res2->fields['s'];
	    		$assign_to_site_array=array();
			$assign_to_site_array=explode(",",$assign_to_site_string);//get e site string
			$assign_to_site="";
			for($k=0;$k<count($assign_to_site_array);$k++)
			{ 
				if($_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid']!=$assign_to_site_array[$k])	$assign_to_site.=$assign_to_site_array[$k].",";
			}
			if($assign_to_site!="") $assign_to_site=substr($assign_to_site, 0, -1);
			$assign_to_site_q="UPDATE hr_assign_site_to_contractor_table SET assign_site_to_contractor='{$assign_to_site}' WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$asgn_site_to_contractor_uid}'";
			$assign_to_site_res=$db->Execute($assign_to_site_q);
		}
	}
	
	$assign_to_site_slctd_string_array=array();
	$assign_to_site_slctd_string_array=explode(",",$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['slctd_string']);
	
	for($n=0;$n<count($assign_to_site_slctd_string_array);$n++)
	{
		$assign_to_site_slctd=$assign_to_site_slctd_string_array[$n];
		$assign_contractor_updt_q3="SELECT assign_site_to_contractor AS s FROM hr_assign_site_to_contractor_table WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$assign_to_site_slctd}'";
	    $assign_contractor_updt_res3=$db->Execute($assign_contractor_updt_q3);
	    $assign_to_site_slctd_string=$assign_contractor_updt_res3->fields['s'];
	    
	    if($assign_to_site_slctd_string=="") $assign_to_site_slctd_string.=$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid'];
		else $assign_to_site_slctd_string.=",".$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid'];
		
		$assign_contractor_updt_q4="UPDATE hr_assign_site_to_contractor_table SET assign_site_to_contractor='{$assign_to_site_slctd_string}' WHERE hr_assign_site_to_contractor_table.assign_site_to_contractor_uid='{$assign_to_site_slctd}'";
		$assign_contractor_updt_res4=$db->Execute($assign_contractor_updt_q4);
	}
	
	if($add==false && $updt==false)
	{
		$assign_contractor_updt_q="UPDATE hr_assign_contractor_to_site_table SET assign_contractor_to_site='{$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['slctd_string']}' WHERE hr_assign_contractor_to_site_table.assign_contractor_to_site_uid='{$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid']}'";
		$assign_contractor_updt_res=$db->Execute($assign_contractor_updt_q);
		add_confirmation("Successfully updated to the Database");
		session_unset(); 
	}
}
?>
