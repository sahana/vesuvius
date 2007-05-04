<?php


/* $Id; */

/**
* DVR Controller
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * This function displays the default page of the module when it is selected
 * This function has to exist! 
 *
 * @access public
 * @return void
 */

function shn_dvr_default() {
	global $global;
	require ($global['approot'] . 'mod/dvr/home.inc');

}

function shn_dvr_add_new_indv() {
	global $global;
	include ($global['approot'] . '/mod/dvr/add_new_indv.inc');

	if ($_REQUEST['location_individual']) {

		if (_shn_dvr_individual_validate_error()) {
			shn_dvr_add_new_individual(true);
		} else {

			shn_dvr_set_person_major_details();

			shn_dvr_disp_and_crnt_loc();
		}
	} else
		if ($_REQUEST['physical_button']) {

			shn_dvr_set_person_location_details();
			shn_dvr_physical_information();
		} else
			if ($_REQUEST['finish']) {

				switch ($_REQUEST['seq']) {
					case 'chk' :
						{
							if (_shn_dvr_individual_physical_details_validate_error()) {
								shn_dvr_physical_information(true);
							} else {
								_shn_dvr_regconfirm_individual();
							}
						}

				}

			} else
				if ($_REQUEST['edit_details']) {
					$_SESSION['dvr']['person']['edit_individual_clicked'] = true;
					shn_dvr_add_new_individual();
				} else
					if ($_REQUEST['save']) {
						_shn_dvr_add_individual_todb();
						//shn_dvr_person_confirm();
						shn_dvr_default();
					} else {
						
						
						
						//unset individual major details
						unset($_SESSION['dvr']['person']['p_uuid']) ;
	unset($_SESSION['dvr']['person']['typ_of_grp']);
	unset($_SESSION['dvr']['person']['head_name']);
	
	unset($_SESSION['dvr']['person']['group_id']) ;
	unset($_SESSION['dvr']['person']['full_name']);
	unset($_SESSION['dvr']['person']['family_name']);
	unset($_SESSION['dvr']['person']['local_name']) ;
	unset($_SESSION['dvr']['person']['dob']);
	unset($_SESSION['dvr']['person']['opt_age_group']);
	unset($_SESSION['dvr']['person']['opt_gender']);
	unset($_SESSION['dvr']['person']['opt_marital_status']) ;
	unset($_SESSION['dvr']['person']['opt_religion']) ;
	unset($_SESSION['dvr']['person']['opt_race']) ;

	unset($_SESSION['dvr']['person']['idcard']);
	unset($_SESSION['dvr']['person']['passport']) ;
	unset($_SESSION['dvr']['person']['drv_licence']);

	unset($_SESSION['dvr']['person']['mobile'] );
	unset($_SESSION['dvr']['person']['telephone']);
	unset($_SESSION['dvr']['person']['email']);
	unset($_SESSION['dvr']['person']['address']);
	unset($_SESSION['dvr']['person']['adlt_mls']);
	unset($_SESSION['dvr']['person']['adlt_fmls']);
	unset($_SESSION['dvr']['person']['chldrn']);
	unset($_SESSION['dvr']['person']['dsplcd']) ;
	unset($_SESSION['dvr']['person']['mising']);
	unset($_SESSION['dvr']['person']['dead']);
	unset($_SESSION['dvr']['person']['rehbd']) ;

	unset($_SESSION['dvr']['person']['image']);
	unset($_SESSION['dvr']['person']['person_image_type']);
	unset($_SESSION['dvr']['person']['person_image_height']);
	unset($_SESSION['dvr']['person']['person_image_width']) ;
						
						
//unset person physical

unset($_SESSION['dvr']['person']['opt_eye_color']);
	unset($_SESSION['dvr']['person']['opt_skin_color']) ;
	unset($_SESSION['dvr']['person']['opt_hair_color'] );
	unset($_SESSION['dvr']['person']['height']) ;
	unset($_SESSION['dvr']['person']['weight']) ;
	unset($_SESSION['dvr']['person']['opt_blood_type']);
	unset($_SESSION['dvr']['person']['last_clothing']);
	unset($_SESSION['dvr']['person']['comments']);
	unset($_SESSION['dvr']['person']['finger_picture']);

	unset($_SESSION['dvr']['person']['finger_image']);
	unset($_SESSION['dvr']['person']['finger_image_type']) ;
	unset($_SESSION['dvr']['person']['finger_image_height']);
	unset($_SESSION['dvr']['person']['finger_image_width']);						
						
						//unset person locations
						
							unset($_SESSION['dvr']['person']['gis_loc_x']);
		unset($_SESSION['dvr']['person']['gis_loc_y']);;
	unset($_SESSION['dvr']['person']['camps']);
	

	unset($_SESSION['dvr']['person']['displaced_loc']) ;
	unset($_SESSION['dvr']['person']['current_loc']);

	unset($_SESSION['dvr']['person']['currentlocationtypeof_group']);
	unset($_SESSION['dvr']['person']['displacedlocationtypeof_group']);
						
						
						

						shn_dvr_add_new_individual();
					}

}

function shn_dvr_add_new_grp() {

	global $global;
	include ($global['approot'] . '/mod/dvr/add_new_grp.inc');
	//include ($global['approot'] . '/mod/dvr/edit_grp.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	// check action sequence

	if ($_REQUEST['save'] != null) {

		_shn_dvr_commit();
		//shn_dvr_mbr_confirm();
		shn_dvr_mbr_confirm();
	} else
		if ($_REQUEST['edit_details'] != null) {
			$_SESSION['dvr']['group']['edit_clicked'] = true;
			shn_dvr_grouptype_and_head_details_start();

		} else
			if ($_REQUEST['member_button'] != null) {

				shn_dvr_mbr_dtls();

			} else
				if ($_REQUEST['location_button'] != null) {

					$sequence = $_POST['seq'];
					switch ($sequence) {
						case 'chk' :
							{
								if (_shn_dvr_group_validate_error()) {
									shn_dvr_grouptype_and_head_details_start(true);
								} else {
									shn_dvr_set_group_major_details();
									shn_dvr_loc_dtls();
								}

							}
					}

				} else
					if ($_REQUEST['checklist_button'] != null) {
						$sequence = $_POST['seq'];

						switch ($sequence) {
							case 'chk' :
								{
									if (_shn_dvr_group_location_validate_error()) {
										shn_dvr_loc_dtls(true);
									} else {
										shn_dvr_set_location_details();
										shn_dvr_cklst_and_desc();

									}
								}

								//print 'gis loc' . $_SESSION['dvr']['group']['gis_loc_x'];

						}

					} else
						if ($_REQUEST['end_button'] != null) {

							_shn_dvr_set_checklist();
							_shn_dvr_regconfirm_group();
						} else {
							switch ($_REQUEST['seq']) {

								case 'chk' :
									{

										if (_shn_dvr_validate_error())
											shn_dvr_grouptype_and_head_details_start(true);
										else
											print 'ok';

									}
									break;
								case 'showmbrdtls' :
									{

										shn_dvr_mbr_dtls();
										break;
									}
								default :
									{
    //unset group major details
    unset($_SESSION['dvr']['group']['typ_of_grp']);
	unset($_SESSION['dvr']['group']['full_name']);
	unset($_SESSION['dvr']['group']['family_name']);
	unset($_SESSION['dvr']['group']['local_name']);
	unset($_SESSION['dvr']['group']['nic']);
	unset($_SESSION['dvr']['group']['picture']);
	unset($_SESSION['dvr']['group']['mobile']) ;
	unset($_SESSION['dvr']['group']['telephone']) ;
	unset($_SESSION['dvr']['group']['email']);
	unset($_SESSION['dvr']['group']['address']);
	unset($_SESSION['dvr']['group']['adlt_mls']);
	unset($_SESSION['dvr']['group']['adlt_fmls']);
	unset($_SESSION['dvr']['group']['chldrn']) ;
	unset($_SESSION['dvr']['group']['dsplcd']) ;
	unset($_SESSION['dvr']['group']['misng']) ;
	unset($_SESSION['dvr']['group']['dead']) ;
	unset($_SESSION['dvr']['group']['rehbd']);
	unset($_SESSION['dvr']['group']['image']);
	unset($_SESSION['dvr']['group']['image_type']);
	unset($_SESSION['dvr']['group']['image_height']);
	unset($_SESSION['dvr']['group']['image_width']) ;
	
	//unset group location details
	unset($_SESSION['dvr']['group']['camps']);
	
	unset($_SESSION['dvr']['group']['gis_loc_x']);
	unset($_SESSION['dvr']['group']['gis_loc_y']);
	unset($_SESSION['dvr']['group']['displaced_loc']);
	unset($_SESSION['dvr']['group']['current_loc']);
	
	//unset checklist
	
	unset($_SESSION['dvr']['group']['opt_dvr_service']);
	unset($_SESSION['dvr']['group']['other']);
	
	unset($_SESSION['dvr']['group']['camps']);
	shn_dvr_grouptype_and_head_details_start();
									}

							}
						}
}

function shn_dvr_search_individual() {
	global $global;
	include ($global['approot'] . '/mod/dvr/search_individual.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');

	switch ($_REQUEST['seq']) {

		case 'advanced' :
			{
				shn_dvr_search_advance();
				break;
			}

		case 'search' :
			{
				shn_dvr_individual_search_results();
				break;
			}

		default :
			{
				shn_dvr_search_default();
			}
	}
}

function shn_dvr_search_group() {
	global $global;
	include ($global['approot'] . '/mod/dvr/search_group.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	switch ($_REQUEST['seq']) {
		case 'advanced' :
			{
				shn_dvr_advanced_search_group();
				break;
			}
		case 'search' :
			{
				shn_dvr_group_search_results();
				break;
			}
		default :
		unset($_SESSION['dvr']['person']['typ_of_grp']);
			shn_dvr_search_default();
	}
}

function shn_dvr_list_groups() {
	global $global;
	include ($global['approot'] . '/mod/dvr/list.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	list_all_groups();

}

function shn_dvr_list_persons() {
	global $global;
	include ($global['approot'] . '/mod/dvr/list.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	list_all_individuals();

}

function shn_dvr_drill_downby_group() {
	global $global;
	include ($global['approot'] . '/mod/dvr/reporting.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	_shn_drill_downby_group();

}

function shn_dvr_drill_downby_shelter() {
	global $global;
	include ($global['approot'] . '/mod/dvr/reporting.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	_shn_drill_downby_shelter();

}

function shn_dvr_drill_downby_incident() {
	global $global;
	include ($global['approot'] . '/mod/dvr/reporting.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');

	_shn_drill_downby_incident();

}

function shn_dvr_edit_group() {
	global $global;
	include ($global['approot'] . '/mod/dvr/edt_grp.inc');

	//include ($global['approot'] . '/mod/dvr/edit_grp.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	// check action sequence

	if ($_REQUEST['save'] != null) {

		_shn_dvr_commit();
		//shn_dvr_mbr_confirm();
		shn_dvr_mbr_confirm();
	} else
		if ($_REQUEST['edit_details'] != null) {
			$_SESSION['dvr']['editgroup']['edit_clicked'] = true;
			shn_dvr_edit_grouptype_and_head_details_start();
		} else
			if ($_REQUEST['member_button'] != null) {

				shn_dvr_mbr_dtls();

			} else
				if ($_REQUEST['location_button'] != null) {

					$sequence = $_POST['seq'];
					switch ($sequence) {
						case 'chk' :
							{
								if (_shn_dvr_group_validate_error()) {
									shn_dvr_edit_grouptype_and_head_details_start(true);
								} else {
									
								
									shn_dvr_set_group_major_details();
									shn_dvr_loc_dtls();
								}

							}
					}

				} else
					if ($_REQUEST['checklist_button'] != null) {
						$sequence = $_POST['seq'];

						switch ($sequence) {
							case 'chk' :
								{
									if (_shn_dvr_group_location_validate_error()) {
										shn_dvr_loc_dtls(true);
									} else {
										shn_dvr_set_location_details();
										shn_dvr_cklst_and_desc();

									}
								}

								//	print 'gis loc' . $_SESSION['dvr']['group']['gis_loc_x'];

						}

					} else
						if ($_REQUEST['end_button'] != null) {

							_shn_dvr_set_checklist();
							_shn_dvr_regconfirm_group();
						} else {
							switch ($_REQUEST['seq']) {

								case 'chk' :
									{

										if (_shn_dvr_validate_error())
											shn_dvr_grouptype_and_head_details_start(true);

									}
									break;
								case 'showmbrdtls' :
									{

										shn_dvr_mbr_dtls();
										break;
									}
								default :
									{
										//print $_REQUEST['seq'];

										shn_dvr_edit_grouptype_and_head_details_start();
									}

							}
						}

}

function shn_dvr_view_members() {

	global $global;
	include ($global['approot'] . '/mod/dvr/view_members.inc');
	//_shn_dvr_home_show_dvr();
}


function shn_dvr_delete_individual()
{
	
	global $global;
	include ($global['approot'] . '/mod/dvr/data_access.inc');
	
	$person_id=$_GET['p_uuid'];
	
	_shn_dvr_delete_person($person_id);
	$msg = $person_id . "person was succesfully deleted ";
	add_confirmation($msg);

}
	
	
function shn_dvr_delete_group()
{
	
	global $global;
	include ($global['approot'] . '/mod/dvr/data_access.inc');
	
	$group_id=$_GET['groupid'];
	
	_shn_dvr_delete_group($group_id);
	$msg = $group_id. "group was succesfully deleted ";
	add_confirmation($msg);

}
		



function shn_dvr_edit_individual() {
	global $global;
	include ($global['approot'] . '/mod/dvr/edt_indv.inc');

	if ($_REQUEST['location_individual']) {

		if (_shn_dvr_individual_validate_error()) {
			_shn_dvr_edit_individual_start(true);
		} else {

			shn_dvr_set_person_major_details();

			shn_dvr_disp_and_crnt_loc();
		}
	} else
		if ($_REQUEST['physical_button']) {

			shn_dvr_set_person_location_details();
			shn_dvr_physical_information();
		} else
			if ($_REQUEST['finish']) {

				switch ($_REQUEST['seq']) {
					case 'chk' :
						{
							if (_shn_dvr_individual_physical_details_validate_error()) {
								shn_dvr_physical_information(true);
							} else {
								_shn_dvr_regconfirm_individual();
							}
						}

				}

			} else
				if ($_REQUEST['edit_details']) {
					$_SESSION['dvr']['person']['edit_individual_clicked'] = true;
					_shn_dvr_edit_individual_start();
				} else
					if ($_REQUEST['save']) {
						_shn_dvr_update_individual_todb();
						//shn_dvr_person_confirm();
						shn_dvr_default();
					} else {
						_shn_dvr_edit_individual_start();
					}

}
?>
