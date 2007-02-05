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
					$_SESSION['edit_individual_clicked'] = true;
					shn_dvr_add_new_individual();
				} else
					if ($_REQUEST['save']) {
						_shn_dvr_add_individual_todb();
						//shn_dvr_person_confirm();
						shn_dvr_default();
					} else {
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
			$_SESSION['edit_clicked'] = true;
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
			$_SESSION['edit_clicked'] = true;
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
					$_SESSION['edit_individual_clicked'] = true;
					shn_dvr_add_new_individual();
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
