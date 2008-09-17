<?php

/**
 * PHP version 5
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

include_once ('add_to_db.inc');

function shn_hr_add_to_session()
{
    global $global;
    global $conf;
    $db = $global['db'];
    if ($conf['gis']) {
        include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    }

	switch (true) { 
    		
        case ($_REQUEST['seq']=='reg_new_homeless_family'||$_REQUEST['seq']=='edit_registered_hf'):

			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name']=$_POST['family_head_name'];
			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid']=$_POST['family_head_create_uid'];
			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_dob']=$_POST['family_head_dob'];
			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_address']=$_POST['family_head_address'];
			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_postal_code']=$_POST['family_head_postal_code'];
			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_home_phone']=$_POST['family_head_home_phone'];
			$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_mobile']=$_POST['family_head_mobile'];

			if($_REQUEST['seq']=='edit_registered_hf') {
                shn_hr_add_to_db("edit_registered_hf");
            } else {
                shn_hr_add_to_db("reg_new_homeless_family");
            }
    		break;

        case ($_REQUEST['seq']=='reg_new_damaged_house'||$_REQUEST['seq']=='edit_registered_damaged_house'):

			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid']=$_POST['enter_uid'];
			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_value']=$_POST['damaged_house_value'];
			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_total_sqft']=$_POST['damaged_house_total_sqft'];
			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['optn_dstrctn_lvl']=$_POST['optn_dstrctn_lvl'];
			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_address']=$_POST['damaged_house_address'];
			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_additional_details']=$_POST['damaged_house_additional_details'];

			if($_FILES['picture']['tmp_name']!='') {
				$info = getimagesize($_FILES['picture']['tmp_name']);
				//check the image type 
				if($info) {
					list ($ignore, $ext) = split("\/", $info['mime']);
					//check for save handler
					$size = filesize($_FILES['picture']['tmp_name']);
					$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_pic'] = $pic;
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_ext'] = $ext;
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_info1'] = $info[1];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['upload_deed_info0'] = $info[0];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['img_fld_nt_blnk']=true; // Added by me and will pass true if the image entering field is not blank
				}
				$ext = '.'.$ext;
				$upload_dir = $global['approot'].'www/tmp/';
		    	$uploadfile = $upload_dir.'ori_'.$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'].$ext;
				move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
				$desc_path = $upload_dir.'thumb_'.$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid'].$ext;
				//resize the image size	
				//shn_image_resize($uploadfile, $desc_path, 50, 50);
			} else {
                $_SESSION['hr']['reg_new_damaged_house']['damaged_house_deed_upload']['img_exsts']=false; // Added by me and will pass false if the image entering field is blank
            }
			
			include_once $global['approot'].'/inc/lib_location.inc';
			
			$loc = shn_location_get_form_submit_loc();
			$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details'] = $loc;

			if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
				$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_x'] = $_POST['loc_x'];
				$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_y'] = $_POST['loc_y'];
			} else 	{
				$_POST['loc_x'] = $_POST['gps_x'];
				$_POST['loc_y'] = $_POST['gps_y'];
				$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_x'] = $_POST['loc_x'];
				$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_y'] = $_POST['loc_y'];
			}

			if($_REQUEST['seq']=='edit_registered_damaged_house') {
                shn_hr_add_to_db("edit_registered_damaged_house");
            } else {
                shn_hr_add_to_db("reg_new_damaged_house");
            }
    		break;


        case ($_REQUEST['seq']=='reg_new_contractor'||$_REQUEST['seq']=='edit_registered_contractor'):

			$_SESSION['hr']['reg_new_contractor']['contractor_information']['optn_contractor_level']=$_POST['optn_contractor_level'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_name']=$_POST['contractor_name'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_uid']=$_POST['contractor_uid'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_dob']=$_POST['contractor_dob'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_adrs']=$_POST['contractor_adrs'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_pstl_cd']=$_POST['contractor_pstl_cd'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_hm_phn']=$_POST['contractor_hm_phn'];
			$_SESSION['hr']['reg_new_contractor']['contractor_information']['contractor_mbl']=$_POST['contractor_mbl'];
			$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['optn_unq_site_name']=$_POST['optn_unq_site_name'];

			if($_REQUEST['seq']=='edit_registered_contractor') {
                shn_hr_add_to_db("edit_registered_contractor");
            } else {
                shn_hr_add_to_db("reg_new_contractor");
            }
    		break;


		case ($_REQUEST['seq']=='reg_new_site'||$_REQUEST['seq']=='edit_registered_st'):

			$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']=$_POST['site_name'];
			$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid']=$_POST['site_uid'];
			$_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization']=$_POST['optn_site_allocated_organization'];
			$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name']=$_POST['site_main_coordinator_name'];
			$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_dob']=$_POST['site_main_coordinator_dob'];
			$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_adrs']=$_POST['main_coordinator_adrs'];
			$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_pstl_cd']=$_POST['main_coordinator_pstl_cd'];
			$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_hm_phn']=$_POST['main_coordinator_hm_phn'];
			$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_mbl']=$_POST['main_coordinator_mbl'];
			$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name']=$_POST['optn_unq_contractor_name'];
			$_SESSION['hr']['reg_new_site']['site_hs_details']['planned_houses']=$_POST['planned_houses'];
			$_SESSION['hr']['reg_new_site']['site_hs_details']['constructed_houses']=$_POST['constructed_houses'];
			$_SESSION['hr']['reg_new_site']['site_hs_details']['vacant_houses']=$_POST['vacant_houses'];
			$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_road']=$_POST['optn_road'];
			$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_water']=$_POST['optn_water'];
			$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_electricity']=$_POST['optn_electricity'];
			$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_telephone_or_communication']=$_POST['optn_telephone_or_communication'];
			$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_sewer']=$_POST['optn_sewer'];
			
			include_once $global['approot'].'/inc/lib_location.inc';
			
			$loc = shn_location_get_form_submit_loc();
			$_SESSION['hr']['reg_new_site']['site_location'] = $loc;

			if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
				$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_x'] = $_POST['loc_x'];
				$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_y'] = $_POST['loc_y'];
			} else {
				$_POST['loc_x'] = $_POST['gps_x'];
				$_POST['loc_y'] = $_POST['gps_y'];
				$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_x'] = $_POST['loc_x'];
				$_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_y'] = $_POST['loc_y'];
			}

			if($_REQUEST['seq']=='edit_registered_st') {
                shn_hr_add_to_db("edit_registered_st");
            } else {
                shn_hr_add_to_db("reg_new_site");
            }
            break;


		case ($_REQUEST['seq']=='search_hf'):
				
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']=$_POST['search_family_head_name'];
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']=$_POST['search_family_head_uid'];
				
			_shn_hr_print_header(_t("Search Homeless Famil(ies)"));
			shn_hr_search_hf();
			print '<br />';
			shn_hr_list_menu1_and_menu2(true);
            break;


		case ($_REQUEST['seq']=='search_damaged_house'):
				
			$_SESSION['hr']['search_hf']['primary_detail_search']['optn_dstrctn_lvl']=$_POST['optn_dstrctn_lvl'];

			_shn_hr_print_header(_t("Search Damaged House(s)"));			
			shn_hr_search_damaged_house();
			print '<br />';
			shn_hr_list_menu1_and_menu2(true,true);
            break;


		case ($_REQUEST['seq']=='search_contractor'||$_REQUEST['seq']=='assign_to_site'):
				
			$_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']=$_POST['optn_contractor_level'];
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']=$_POST['search_contractor_name'];
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']=$_POST['search_contractor_uid'];
			
			_shn_hr_print_header(_t("Search Contractor(s)"));	
			if($_REQUEST['seq']=='assign_to_site') {
				shn_hr_search_contractor(false,true);
				print '<br />';
				shn_hr_list_menu3(true,false,true);
			} else {
				shn_hr_search_contractor();
				print '<br />';
				shn_hr_list_menu3(true);
			}
            break;


		case ($_REQUEST['seq']=='search_st'||$_REQUEST['seq']=='assign_contractor'):
				
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=$_POST['search_site_name'];
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']=$_POST['search_site_uid'];
			$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=$_POST['optn_site_allocated_organization'];
			$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=$_POST['search_site_main_coordinator_name'];
			
			_shn_hr_print_header(_t("Search Site(s)"));
			if($_REQUEST['seq']=='assign_contractor') {
				shn_hr_search_site(false,true);
				print '<br />';
				shn_hr_list_menu4(true,false,true);
			} else {
				shn_hr_search_site();
				print '<br />';
				shn_hr_list_menu4(true);
			}
            break;
	}

	switch ($_GET['edit_seq']) {
    		
            case 'edit_registered_hf':

    			$hf_uid = $_GET['hf_uid'];
    			$hf_and_damaged_house_contact_uid = "hf_and_damaged_house_contact_".$hf_uid;
    
    			$edit_registered_hf_q1 = "SELECT family_head_name,family_head_create_uid,family_head_dob FROM hr_family_head_details_table WHERE '{$hf_uid}'=hr_family_head_details_table.family_head_create_uid";
				$edit_registered_hf_q2 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_adrs'";
				$edit_registered_hf_q3 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_pcd'";
				$edit_registered_hf_q4 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_hm_phn'";
				$edit_registered_hf_q5 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}' AND contact.opt_contact_type='fhd_mbl'";

    			$edit_registered_hf_res1=$db->Execute($edit_registered_hf_q1);
    			$edit_registered_hf_res2=$db->Execute($edit_registered_hf_q2);
    			$edit_registered_hf_res3=$db->Execute($edit_registered_hf_q3);
    			$edit_registered_hf_res4=$db->Execute($edit_registered_hf_q4);
    			$edit_registered_hf_res5=$db->Execute($edit_registered_hf_q5);

        		if((!$edit_registered_hf_res1==NULL && !$edit_registered_hf_res1->EOF)&&(!$edit_registered_hf_res2==NULL && !$edit_registered_hf_res2->EOF)&&(!$edit_registered_hf_res3==NULL && !$edit_registered_hf_res3->EOF)&&(!$edit_registered_hf_res4==NULL && !$edit_registered_hf_res4->EOF)&&(!$edit_registered_hf_res5==NULL && !$edit_registered_hf_res5->EOF))
       			{
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_name']=$edit_registered_hf_res1->fields[0];
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_create_uid']=$edit_registered_hf_res1->fields[1];
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_dob']=$edit_registered_hf_res1->fields[2];
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_address']=$edit_registered_hf_res2->fields[0];
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_postal_code']=$edit_registered_hf_res3->fields[0];
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_home_phone']=$edit_registered_hf_res4->fields[0];
					$_SESSION['hr']['reg_new_homeless_family']['family_head_details']['family_head_mobile']=$edit_registered_hf_res5->fields[0];
				}

    			shn_hr_reg_new_homeless_family(true);
        		break;

     		case 'edit_registered_damaged_house':

                $damaged_house_uid = $_GET['damaged_house_uid'];
    			$hf_and_damaged_house_gis_uid = "hr_damaged_house_gis_uid_".$damaged_house_uid;

    			$edit_registered_damaged_house_q1 = "SELECT damaged_house_basic_details_uid,damaged_house_value,damaged_house_total_sqft,damaged_house_destruction_level,damaged_house_address,damaged_house_additional_details,damaged_house_location FROM hr_damaged_house_basic_details_table,hr_damaged_house_deed_upload_table,hr_damaged_house_location_details_table WHERE '{$damaged_house_uid}'=hr_damaged_house_basic_details_table.damaged_house_basic_details_uid AND hr_damaged_house_basic_details_table.damaged_house_basic_details_uid=hr_damaged_house_location_details_table.damaged_house_location_uid";
                $edit_registered_damaged_house_res1=$db->Execute($edit_registered_damaged_house_q1);
    			
                if ($conf['gis']) {
                    $keys = array('f_coords' => 1);
                    $gis_results = shn_gis_get_features_item_ref($hf_and_damaged_house_gis_uid, $keys);
                }

        		if(!$edit_registered_damaged_house_res1==NULL && !$edit_registered_damaged_house_res1->EOF)	{
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_owner_information']['enter_uid']=$edit_registered_damaged_house_res1->fields[0];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_value']=$edit_registered_damaged_house_res1->fields[1];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_total_sqft']=$edit_registered_damaged_house_res1->fields[2];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['optn_dstrctn_lvl']=$edit_registered_damaged_house_res1->fields[3];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_address']=$edit_registered_damaged_house_res1->fields[4];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_basic_details']['damaged_house_additional_details']=$edit_registered_damaged_house_res1->fields[5];
					$_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details'] = $edit_registered_damaged_house_res1->fields[6];
				}

        		if($conf['gis'] && $gis_results) {
                    $gis_coords = shn_gis_coord_decode($gis_results[0]['f_coords']);
                    $_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_x'] = $gis_coords[0][0];
                    $_SESSION['hr']['reg_new_damaged_house']['damaged_house_location_details_gis']['gis_loc_y'] = $gis_coords[0][1];
                }

                shn_hr_reg_new_damaged_house(true);
    			break;

    	
     		case 'edit_registered_contractor':

    			$contractor_uid = $_GET['contractor_uid'];
    			$contractor_contact_uid="contractor_contact_".$contractor_uid;

    			$edit_registered_contractor_q1 = "SELECT contractor_level,contractor_name,contractor_uid,contractor_dob,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE '{$contractor_uid}'=hr_contractor_table.contractor_uid AND hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid";
				$edit_registered_contractor_q2 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_adrs'";
				$edit_registered_contractor_q3 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_pcd'";
				$edit_registered_contractor_q4 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_hm_phn'";
				$edit_registered_contractor_q5 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$contractor_contact_uid}' AND contact.opt_contact_type='cnt_mbl'";

    			$edit_registered_contractor_res1=$db->Execute($edit_registered_contractor_q1);
    			$edit_registered_contractor_res2=$db->Execute($edit_registered_contractor_q2);
    			$edit_registered_contractor_res3=$db->Execute($edit_registered_contractor_q3);
    			$edit_registered_contractor_res4=$db->Execute($edit_registered_contractor_q4);
    			$edit_registered_contractor_res5=$db->Execute($edit_registered_contractor_q5);

    			break;


     		case 'edit_registered_st':

    			$site_uid = $_GET['site_uid'];
    			$site_gis_uid="st_gis_uid_".$site_uid;
    			$site_mcd_contact_uid="st_mcd_contact_".$site_uid;

    			$edit_registered_site_q1 = "SELECT site_name,site_uid,site_allocated_organization,site_main_coordinator_name,site_main_coordinator_dob,assign_contractor_to_site,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_assign_contractor_to_site_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table WHERE '{$site_uid}'=hr_site_name_and_uid_table.site_uid AND hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_assign_contractor_to_site_table.assign_contractor_to_site_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid";
				if ($conf['gis']) {
                    $keys = array('f_coords' => 1);
                    $gis_results = shn_gis_get_features_item_ref($site_gis_uid, $keys);
                }
				$edit_registered_site_q3 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_adrs'";
				$edit_registered_site_q4 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_pcd'";
				$edit_registered_site_q5 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_hm_phn'";
				$edit_registered_site_q6 = "SELECT contact_value FROM contact WHERE contact.pgoc_uuid='{$site_mcd_contact_uid}' AND contact.opt_contact_type='smc_mbl'";

    			$edit_registered_site_res1=$db->Execute($edit_registered_site_q1);
    			$edit_registered_site_res3=$db->Execute($edit_registered_site_q3);
    			$edit_registered_site_res4=$db->Execute($edit_registered_site_q4);
    			$edit_registered_site_res5=$db->Execute($edit_registered_site_q5);
    			$edit_registered_site_res6=$db->Execute($edit_registered_site_q6);

    			$assign_contractor_to_site_string = array();
    			$assign_contractor_to_site_string = explode(",",$edit_registered_site_res1->fields[5]);

            	if((!$edit_registered_site_res1==NULL && !$edit_registered_site_res1->EOF)&&(!$edit_registered_site_res2==NULL && !$edit_registered_site_res2->EOF)&&(!$edit_registered_site_res3==NULL && !$edit_registered_site_res3->EOF)&&(!$edit_registered_site_res4==NULL && !$edit_registered_site_res4->EOF)&&(!$edit_registered_site_res5==NULL && !$edit_registered_site_res5->EOF)&&(!$edit_registered_site_res6==NULL && !$edit_registered_site_res6->EOF))
           		{
    				$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_name']=$edit_registered_site_res1->fields[0];
    				$_SESSION['hr']['reg_new_site']['site_name_and_uid']['site_uid']=$edit_registered_site_res1->fields[1];
    				$_SESSION['hr']['reg_new_site']['site_allocated_organization']['optn_site_allocated_organization']=$edit_registered_site_res1->fields[2];
    				$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_name']=$edit_registered_site_res1->fields[3];
    				$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['site_main_coordinator_dob']=$edit_registered_site_res1->fields[4];
    				$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_adrs']=$edit_registered_site_res3->fields[0];
    				$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_pstl_cd']=$edit_registered_site_res4->fields[0];
    				$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_hm_phn']=$edit_registered_site_res5->fields[0];
    				$_SESSION['hr']['reg_new_site']['site_main_coordinator_details']['main_coordinator_mbl']=$edit_registered_site_res6->fields[0];
    				$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name']=$assign_contractor_to_site_string;
    				$_SESSION['hr']['reg_new_site']['site_hs_details']['planned_houses']=$edit_registered_site_res1->fields[6];
    				$_SESSION['hr']['reg_new_site']['site_hs_details']['constructed_houses']=$edit_registered_site_res1->fields[7];
    				$_SESSION['hr']['reg_new_site']['site_hs_details']['vacant_houses']=$edit_registered_site_res1->fields[8];
    				$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_road']=$edit_registered_site_res1->fields[9];
    				$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_water']=$edit_registered_site_res1->fields[10];
    				$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_electricity']=$edit_registered_site_res1->fields[11];
    				$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_telephone_or_communication']=$edit_registered_site_res1->fields[12];
    				$_SESSION['hr']['reg_new_site']['site_infrastructure_details']['optn_sewer']=$edit_registered_site_res1->fields[13];
    				$_SESSION['hr']['reg_new_site']['site_location'] = $edit_registered_site_res1->fields[14];
    			 }

            	if($conf['gis'] && $gis_results) {
                    $gis_coords = shn_gis_coord_decode($gis_results[0]['f_coords']);
                    $_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_x'] = $gis_coords[0][0];
                    $_SESSION['hr']['reg_new_site']['site_location_gis']['gis_loc_y'] = $gis_coords[0][1];
                }

    			shn_hr_reg_new_site(true);
    			break;
   

     		case 'assign_to_site':

        		$contractor_uid = $_GET['contractor_uid'];
        		$slctd_string = $_GET['slctd_string'];

    			$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['contractor_uid']=$contractor_uid;
    			$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['slctd_string']=$slctd_string;		

    			shn_hr_add_to_db("assign_to_site_dbs");
    			break;


     		case 'assign_contractor':

        		$site_uid = $_GET['site_uid'];
        		$slctd_string = $_GET['slctd_string'];
    			
    			$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['site_uid']=$site_uid;
    			$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['slctd_string']=$slctd_string;

    			shn_hr_add_to_db("assign_contractor_dbs");
    			break;
	}
}
?>
