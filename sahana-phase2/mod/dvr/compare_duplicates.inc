<?php
/**
 *Major functions to compare details of duplicate entries of disaster victims
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
include_once ($global['approot'] . '/mod/dvr/data_access.inc');
include_once ($global['approot'] . '/mod/or/lib_or.inc');

/**
 * get all the details of the victim from database and return those
 *
 * @param unknown_type $p_uuid
 * @param unknown_type $person
 * @return $_SESSION['dvr'][$person][......]
 */
function _shn_dvr_get_compare_details($p_uuid,$person)
{
	$results = get_person_major_details($p_uuid);
	$_SESSION['dvr'][$person]['group_type'] = _shn_dvr_getoptiondescription($results->fields['group_type']);
	$_SESSION['dvr'][$person]['head_id'] = $results->fields['head_id'];
	$_SESSION['dvr'][$person]['group_id'] = $results->fields['groupid'];
	
	$personal = get_person_full_name($p_uuid);

	$_SESSION['dvr'][$person]['p_full_name'] = $personal->fields['full_name'];
	$_SESSION['dvr'][$person]['p_family_name'] = $personal->fields['family_name'];
	$_SESSION['dvr'][$person]['p_local_name'] = $personal->fields['l10n_name'];
	
	$personal_results = get_personal_details($p_uuid);
	
	$_SESSION['dvr'][$person]['dob'] = $personal_results->fields['birth_date'];
	$_SESSION['dvr'][$person]['age_group'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_age_group']);
	$_SESSION['dvr'][$person]['gender'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_gender']);
	$_SESSION['dvr'][$person]['marital'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_marital_status']);
	$_SESSION['dvr'][$person]['religion'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_religion']);
	$_SESSION['dvr'][$person]['race'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_race']);
	
	$_SESSION['dvr'][$person]['curr_loc'] = _shn_dvr_get_current_location($p_uuid);
	$_SESSION['dvr'][$person]['dis_loc'] = _shn_dvr_get_displaced_location($p_uuid);
	
	$id_results = get_identity_to_person($p_uuid);

	while (!$id_results->EOF) {
		$id = $id_results->fields['serial'];
		$val = $id_results->fields['opt_id_type'];
		if ($val == 'idcard') {
			$_SESSION['dvr'][$person]['idcard'] = $id;
		} else
			if ($val == 'pas') {
				$_SESSION['dvr'][$person]['passport'] = $id;
			} else
				if ($val == 'dln') {
					$_SESSION['dvr'][$person]['drv_licence'] = $id;
				}
		$id_results->MoveNext();
	}
	
	$contact_results = get_contacts($p_uuid);
	
	while (!$contact_results->EOF) {
		$ctct_type = $contact_results->fields['opt_contact_type'];
		$ctct_value = $contact_results->fields['contact_value'];

		if ($ctct_type == "mobile") {
			$_SESSION['dvr'][$person]['mobile'] = $ctct_value;
		} else
			if ($ctct_type == "telephone") {
				$_SESSION['dvr'][$person]['telephone'] = $ctct_value;
			} else
				if ($ctct_type == "address") {
					$_SESSION['dvr'][$person]['address'] = $ctct_value;
				}
		$contact_results->MoveNext();

	}
	
	$physical_result = get_person_physical_details($p_uuid);
	
	$_SESSION['dvr'][$person]['opt_eye_color'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_eye_color']);
	$_SESSION['dvr'][$person]['opt_skin_color'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_skin_color']);
	$_SESSION['dvr'][$person]['opt_hair_color'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_hair_color']);
	$_SESSION['dvr'][$person]['height'] = $physical_result->fields['height'];
	$_SESSION['dvr'][$person]['weight'] = $physical_result->fields['weight'];
	$_SESSION['dvr'][$person]['opt_blood_type'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_blood_type']);
	$_SESSION['dvr'][$person]['comments'] = $physical_result->fields['comments'];
	$chars = preg_split('/,/', $comments);
	$_SESSION['dvr'][$person]['last_clothing'] = $chars[0];
	
	return $_SESSION['dvr'][$person];
}

/**
 * //////////////////////////////////////////////////////////////////////////
 */

	_shn_dvr_print_header(_t("Compare Duplicates"));
	shn_form_fopen("compare_duplicate", null, false);

	$p_uuid1 = $_GET['p_uuid1'];
	$p_uuid2 = $_GET['p_uuid2'];

	_shn_dvr_get_compare_details($p_uuid1, "person1");
	_shn_dvr_get_compare_details($p_uuid2, "person2");
	
	?>
<DIV id ="result">	
<table width="100%">
  <thead>
  	<tr>
  	   	<td><?=_t('Description') ?></td>
    	<td><?=_t('Detail of the Entry') ?></td>
    	<td><?=_t('Detail of the Duplicate') ?></td>
    </tr>
  </thead>
  <tr>
  	   	<td></td>
    	<td style="text-align: center;"><?shn_show_thumb_url($p_uuid1, 'database', 'dvr', 'addvictim_img', false);?></td>
    	<td style="text-align: center;"><?shn_show_thumb_url($p_uuid2, 'database', 'dvr', 'addvictim_img', false);?></td>
    </tr>
  <tr>
  <td><b><?=_t('Personel details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  
  <tr>
  	<td><?=_t('Full Name') ?></td>
    <td><?=$_SESSION['dvr']['person1']['p_full_name'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['p_full_name']?></td>
  </tr>
  <tr>
  	<td><?=_t('Family Name') ?></td>
    <td><?=$_SESSION['dvr']['person1']['p_family_name']?></td>
    <td><?=$_SESSION['dvr']['person2']['p_family_name'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Local Name') ?></td>
    <td><?=$_SESSION['dvr']['person1']['p_local_name'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['p_local_name'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Group Type') ?></td>
    <td><?=$_SESSION['dvr']['person1']['group_type'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['group_type']  ?></td>
  </tr>
  <tr>
  	<td><?=_t('Date of Birth') ?></td>
    <td><?=$_SESSION['dvr']['person1']['dob'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['dob'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Age Group') ?></td>
    <td><?=$_SESSION['dvr']['person1']['age_group'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['age_group'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Gender') ?></td>
    <td><?=$_SESSION['dvr']['person1']['gender'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['gender'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Marital Status') ?></td>
    <td><?=$_SESSION['dvr']['person1']['marital'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['marital'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Religion') ?></td>
    <td><?=$_SESSION['dvr']['person1']['religion'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['religion'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Race') ?></td>
    <td><?=$_SESSION['dvr']['person1']['race'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['race'] ?></td>
  </tr>
  <tr>
  <td><b><?=_t('Contact Details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  <tr>
  	<td><?=_t('Mobile Number') ?></td>
    <td><?=$_SESSION['dvr']['person1']['mobile']?></td>
    <td><?=$_SESSION['dvr']['person2']['mobile']?></td>
  </tr>
  <tr>
  	<td><?=_t('Telephone Number') ?></td>
    <td><?=$_SESSION['dvr']['person1']['telephone']?></td>
    <td><?=$_SESSION['dvr']['person2']['telephone']?></td>
  </tr>
  <tr>
  	<td><?=_t('Address') ?></td>
    <td><?=$_SESSION['dvr']['person1']['address']?></td>
    <td><?=$_SESSION['dvr']['person2']['address']?></td>
  </tr>
  <tr>
  <td><b><?=_t('Location Details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  <tr>
  	<td><?=_t('Current Location') ?></td>
    <td><?=shn_location_string($_SESSION['dvr']['person1']['curr_loc']) ?></td>
    <td><?=shn_location_string($_SESSION['dvr']['person2']['curr_loc'])?></td>
  </tr>
  <tr>
  	<td><?=_t('Displaced Location') ?></td>
    <td><?=shn_location_string($_SESSION['dvr']['person1']['dis_loc']) ?></td>
    <td><?=shn_location_string($_SESSION['dvr']['person2']['dis_loc']) ?></td>
  </tr>
   <tr>
  <td><b><?=_t('Identity') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  <tr>
  	<td><?=_t('NIC') ?></td>
    <td><?=$_SESSION['dvr']['person1']['idcard']?></td>
    <td><?=$_SESSION['dvr']['person2']['idcard'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Passport') ?></td>
    <td><?=$_SESSION['dvr']['person1']['passport']?></td>
    <td><?=$_SESSION['dvr']['person2']['passport'] ?></td>
  </tr>
  <tr>
  	<td><?=_t('Driving Licence') ?></td>
    <td><?=$_SESSION['dvr']['person1']['drv_licence'] ?></td>
    <td><?=$_SESSION['dvr']['person2']['drv_licence'] ?></td>
  </tr>
  <tr>
  <td><b><?=_t('Physical Details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  
  <tr>
  	   	<td><?=_t('Finger Photograph') ?></td>
    	<td><?shn_show_thumb_url($p_uuid1, 'database', 'dvr', 'addfingerprint_img', false, "finger");?></td>
    	<td><?shn_show_thumb_url($p_uuid2, 'database', 'dvr', 'addfingerprint_img', false, "finger");?></td>
    </tr>
  <tr>
  	<td><?=_t('Eye Colour') ?></td>
    <td><?=$_SESSION['dvr']['person1']['opt_eye_color']?></td>
    <td><?=$_SESSION['dvr']['person2']['opt_eye_color']?></td>
  </tr>
  <tr>
  	<td><?=_t('Skin Colour') ?></td>
    <td><?=$_SESSION['dvr']['person1']['opt_skin_color']?></td>
    <td><?=$_SESSION['dvr']['person2']['opt_skin_color']?></td>
  </tr>
  <tr>
  	<td><?=_t('Hair Colour') ?></td>
    <td><?=$_SESSION['dvr']['person1']['opt_hair_color']?></td>
    <td><?=$_SESSION['dvr']['person2']['opt_hair_color']?></td>
  </tr>
  <tr>
  	<td><?=_t('Height') ?></td>
    <td><?=$_SESSION['dvr']['person1']['height']?></td>
    <td><?=$_SESSION['dvr']['person2']['height']?></td>
  </tr>
  <tr>
  	<td><?=_t('Weight') ?></td>
    <td><?=$_SESSION['dvr']['person1']['weight']?></td>
    <td><?=$_SESSION['dvr']['person2']['weight']?></td>
  </tr>
   <tr>
  	<td><?=_t('Blood Type') ?></td>
    <td><?=$_SESSION['dvr']['person1']['opt_blood_type']?></td>
    <td><?=$_SESSION['dvr']['person2']['opt_blood_type']?></td>
  </tr>
  <tr>
  <td><b><?=_t('Other') ?></b></td>
  <td></td>
  <td></td>
  </tr>
   <tr>
  	<td><?=_t('Last Clothing') ?></td>
    <td><?=$_SESSION['dvr']['person1']['last_clothing']?></td>
    <td><?=$_SESSION['dvr']['person2']['last_clothing']?></td>
  </tr>
  
</table>
</DIV>
	
<?php

	shn_form_fclose();
	unset($_SESSION['dvr']['person1']);
	unset($_SESSION['dvr']['person2']);
?>
