<?php


/* $Id; */

/**
* Default functions of DVR
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
		shn_dvr_disp_and_crnt_loc();
	} else
		if ($_REQUEST['physical_button']) {
			shn_dvr_physical_information();
		} else {
			shn_dvr_add_new_individual();
		}

}

function shn_dvr_add_new_grp() {

	global $global;
	include ($global['approot'] . '/mod/dvr/add_new_grp.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');
	// check action sequence

	if ($_REQUEST['member_button'] != null) {

		shn_dvr_mbr_dtls();

	} else
		if ($_REQUEST['location_button'] != null) {

			shn_dvr_loc_dtls();

		} else
			if ($_REQUEST['checklist_button'] != null) {
				shn_dvr_cklst_and_desc();
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
							//print $_REQUEST['seq'];

							shn_dvr_grouptype_and_head_details_start();
						}

				}
			}
}

function shn_dvr_search_individual() {
	global $global;
	include ($global['approot'] . '/mod/dvr/search_individual.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');

	_shn_dvr_search_default();
}

function shn_dvr_search_group() {
	global $global;
	include ($global['approot'] . '/mod/dvr/search_group.inc');
	require_once ($global['approot'] . '/inc/handler_form.inc');

	_shn_dvr_search_default();
}
?>
