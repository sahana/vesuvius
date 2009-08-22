<?php
/**
 *Major functions to transfer a group of disaster victims to a new location
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/mod/dvr/lib.inc');
include_once ($global['approot'] . '/mod/or/lib_or.inc');

function _shn_dvr_populate_grp_details()
{
	$_SESSION['dvr']['trns_grp']['p_uuid'] = $_GET['groupid'];
	$_SESSION['dvr']['trns_grp']['curr_loc'] = _shn_dvr_get_groupcurrent_location($_SESSION['dvr']['trns_grp']['p_uuid']);
	//$_SESSION['dvr']['trns_grp']['curr_loc'] = _shn_dvr_get_groupcurrent_location($_SESSION['dvr']['trns_grp']['p_uuid']);
	$curr_loc = _shn_org_location_string($_SESSION['dvr']['trns_grp']['curr_loc']);
	
	shn_form_fsopen(_t("Current Location"));
	shn_form_label(_t('Current Location of the Group'), $curr_loc, $extra_opts);
	shn_form_fsclose();
	
}
/**
 * //////////////////////////////////////////////////////////////////////
 */	
	_shn_dvr_print_header(_t("Transfer Group"));
	
	switch ($_REQUEST['seq']) {
		case '' :
			{
				shn_form_fopen("transfer_grp", null, false);
				//shn_form_fsopen(_t("Details of the Victims"));
				shn_form_hidden(array ('seq' => 'finish'));
				_shn_dvr_populate_grp_details();
				
				shn_form_fsopen(_t("New Location"));
				$range = shn_dvr_get_loc_range();
				$parent = _shn_dvr_get_start_loc();
				$extra_opts['org'] = true;
			    $extra_opts['camps'] = true;
				shn_location($range, null, null, $extra_opts);
				
				shn_form_fsclose();
				
				shn_form_submit(_t('Next'),"name=finish");
				shn_form_fclose();
				break;
			}
		case 'finish' :
			{
				global $global;
				$db=$global['db'];
				$loc = shn_location_get_form_submit_loc();
				
				$sql = "UPDATE location_details SET location_id='$loc' WHERE poc_uuid='{$_SESSION['dvr']['trns_grp']['p_uuid']}-curr'";
				$res=$db->Execute($sql);
				shn_dvr_search_group();
				//shn_dvr_dafault();
				
				break;
			}
	}
