<?php


/**
 *Major functions to edit a new disaster victim
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ('lib.inc');
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_errors.inc');
include_once ($global['approot'] . '/inc/lib_image.inc');
include_once ($global['approot'] . '/mod/or/lib_or.inc');
include_once ($global['approot'] . '/inc/lib_uuid.inc');
include_once ($global['approot'] . '/mod/dvr/data_access.inc');

function _shn_dvr_populate_individual_details() {
	$p_uuid = $_GET['p_uuid'];
	$_SESSION['dvr']['person']['p_uuid'] = $p_uuid;
	$results = get_person_major_details($p_uuid);
	$group_type = $results->fields['group_type'];
	$head_id = $results->fields['head_id'];
	$group_id = $results->fields['groupid'];

	$personal = get_person_full_name($p_uuid);

	$p_full_name = $personal->fields['full_name'];
	$p_family_name = $personal->fields['family_name'];
	$p_local_name = $personal->fields['l10n_name'];

	$head_details = get_person_full_name($head_id);
	$head_full_name = $head_details->fields['full_name'];

	$_SESSION['dvr']['person']['typ_of_grp'] = $group_type;
//	print 'head name is' . $_POST['head_name'];
	$_SESSION['dvr']['person']['head_name'] = $head_full_name;
	//$group=_shn_dvr_get_group_id($_POST['head_name']);

	$_SESSION['dvr']['person']['group_id'] = $group_id;
	$_SESSION['dvr']['person']['full_name'] = $p_full_name;
	$_SESSION['dvr']['person']['family_name'] = $p_family_name;
	$_SESSION['dvr']['person']['local_name'] = $p_local_name;

	$personal_results = get_personal_details($p_uuid);

	$dob = $personal_results->fields['birth_date'];
	$age_group = $personal_results->fields['opt_age_group'];
	$gender = $personal_results->fields['opt_gender'];
	$marital = $personal_results->fields['opt_marital_status'];
	$religion = $personal_results->fields['opt_religion'];

	$race = $personal_results->fields['opt_race'];

	$id_results = get_identity_to_person($p_uuid);

	while (!$id_results->EOF) {
		$id = $id_results->fields['serial'];
		$val = $id_results->fields['opt_id_type'];
		if ($id == 'nic') {
			$_SESSION['dvr']['person']['idcard'] = $val;
		} else
			if ($id == 'pas') {
				$_SESSION['dvr']['person']['passport'] = $val;
			} else
				if ($id == 'dln') {
					$_SESSION['dvr']['person']['dln'] = $val;
				}
		$id_results->MoveNext();
	}
	$_SESSION['dvr']['person']['dob'] = $dob;
	$_SESSION['dvr']['person']['opt_age_group'] = $age_group;
	$_SESSION['dvr']['person']['opt_gender'] = $gender;
	$_SESSION['dvr']['person']['opt_marital_status'] = $marital;
	$_SESSION['dvr']['person']['opt_religion'] = $religion;
	$_SESSION['dvr']['person']['opt_race'] = $race;

	$contact_results = get_contacts($p_uuid);

	while (!$contact_results->EOF) {
		$ctct_type = $contact_results->fields['opt_contact_type'];
		$ctct_value = $contact_results->fields['contact_value'];

		if ($ctct_type == "mobile") {
			$_SESSION['dvr']['person']['mobile'] = $ctct_value;
		} else
			if ($ctct_type == "telephone") {
				$_SESSION['dvr']['person']['telephone'] = $ctct_value;
			} else
				if ($ctct_type == "address") {
					$_SESSION['dvr']['person']['address'] = $ctct_value;
				}
		$contact_results->MoveNext();

	}
	
}

function _shn_dvr_edit_individual_start($errors = false) {

	if ($_SESSION['dvr']['person']['edit_individual_clicked'] == false | $_SESSION['dvr']['person']['edit_individual_clicked']==null) {
		_shn_dvr_populate_individual_details();
	}
	if ($errors)
		display_errors();

	_shn_dvr_print_header(_("Edit Individual"));

	shn_form_fopen("edit_individual", null, array (
		'req_message' => true,
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'add_new_individual'
	));
	shn_form_fsopen(_("Select Group Type"));
	print '<div class="info">';
	print _("Please select a Group that describes you well");

	print '<br />';

	print '</div>';
	print '<br />';

	
	$extra_opts['help'] = _("Please Select the group type");
	$extra_opts['req'] = true;
	$extra_opts['value'] = $_SESSION['dvr']['person']['typ_of_grp'];
	$extra_opts['sort'] = 'option_code';

	shn_form_opt_select('opt_group_type', _("Type of Group"), 'onChange=document.forms[1].submit()', $extra_opts);

	$type = $_POST['opt_group_type'];

	$heads = _shn_dvr_getgroupheadspertype($type);

	array_push($heads, 'Other');
	$extra_opts['help'] = _("Please Select the Head Name");
	$extra_opts['req'] = true;
	$extra_opts['value'] = $_SESSION['dvr']['person']['group_head_name'];
	shn_form_select($heads, 'Select the group head', 'head name', '', $extra_opts);

	shn_form_fsclose();

	print '<br />';

	shn_form_fsopen(_('Basic Details'));
	print '<br />';
	$extra_opts['value'] = $_SESSION['dvr']['person']['full_name'];
	$extra_opts['help'] = _("Enter the Full Name.(Required)");
	$extra_opts['req'] = true;

	shn_form_text(_('Full Name'), 'full_name', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['family_name'];
	$extra_opts['help'] = _("'Family name, or the surname could be specified for matching of people with similar Family names");
	$extra_opts['req'] = false;
	shn_form_text(_('Family Name'), 'family_name', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['local_name'];
	$extra_opts['help'] = _("You may also specify the local name, even in different script than English");

	shn_form_text(_('Local Name'), 'local_name', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['dob'];
	$extra_opts['help'] = _("You may also specify the date of birth");

	shn_form_text(_('Date of Birth   (YYYY-MM-DD)'), 'dob', 'size=8', $extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_age_group'];
	$extra_opts['help'] = _("You may also specify the age group");

	shn_form_opt_select("opt_age_group", _('Age Group'), '', $extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_gender'];

	shn_form_opt_select("opt_gender", _('Gender'), '', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_marital_status'];

	shn_form_opt_select("opt_marital_status", _('Marital Status'), '', $extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_religion'];

	shn_form_opt_select("opt_religion", _('Religion'), '', $extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_race'];

	shn_form_opt_select("opt_race", _('Race'), '', $extra_opts);
	shn_form_fsclose();
	print '<br />';

	shn_form_fsopen(_('Identity'));
	print '<br />';
	$extra_opts['value'] = $_SESSION['dvr']['person']['idcard'];
	$extra_opts['help'] = 'Specify the Identity card Number, Although this is not required this will be useful in searching for the person';
	shn_form_text(_('Identity Card Number'), 'idcard', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['passport'];
	$extra_opts['help'] = 'Please Specify the passport number, Although this is not required this will be useful in searching for the person';

	shn_form_text(_('Passport Number'), 'passport', 'size="30"', $extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['person']['drv_licence'];
	$extra_opts['help'] = 'Please Specify the driving License number, Although this is not required this will be useful in searching for the person';

	shn_form_text(_('Driving License'), 'drv_license', 'size="30"', $extra_opts);
	shn_form_fsclose();

	print '<br />';
	shn_form_fsopen(_('Upload Picture'));
	print '<br />';
if (	$_SESSION['dvr']['person']['edit_individual_clicked']==true) {
		shn_form_label(_("Current Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

		shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addvictim_img', true);
?>
	
	</p>
	<?php

	}
	
	else
	{
		
shn_form_label(_("Current Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php
//print 'here'.$_SESSION['dvr']['group']['headid'];
		shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], 'database', 'dvr', 'addvictim_img', false);
?>
	
	</p>
	<?php

	}
		

	shn_form_upload(_('Upload Picture'), "picture");
	shn_form_fsclose();

	shn_form_fsopen(_('Contact Information Of The Disaster Victim'));
	print '<div class="info">';
	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['person']['address'];
	$extra_opts['help'] = 'Your address can be specified to contact you';

	shn_form_textarea(_('Address'), "address", null, array (
		'help' => _('Your address can be specified to contact you'
	)));

	$extra_opts['value'] = $_SESSION['dvr']['person']['zip'];
	$extra_opts['help'] = 'Specify a zip code, if it is available';

	shn_form_text(_('Postal Code'), 'zip', 'size="15"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['phone'];
	$extra_opts['help'] = 'Specify a phone, if it is available';

	shn_form_text(_('Home Phone'), 'phone', 'size="15"');

	$extra_opts['value'] = $_SESSION['dvr']['person']['mobile'];
	$extra_opts['help'] = 'Specify a mobile, if it is available';
	shn_form_text(_('Mobile'), 'mobile', 'size="15"');
	shn_form_fsclose();



shn_form_fsopen(_('Displaced Location Of The Victim'));
	print '<br />';
	$typ_of_grp = array ();
	//array_push($typ_of_grp, '-- Select Option --');
	array_reverse($typ_of_grp);

	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	$extra_opts['value'] = $_SESSION['dvr']['person']['displacedlocationtypeof_group'];

	shn_form_select($typ_of_grp, _("Displaced Location"), 'displacedlocationtypeof_group', '', $extra_opts);

	$range = shn_dvr_get_loc_range();

	$locid = get_person_location_details($_SESSION['dvr']['person']['p_uuid'].'-disp');
	if ($_SESSION['dvr']['person']['edit_individual_clicked'] == null |  $_SESSION['dvr']['person']['edit_individual_clicked']==false)
		shn_location($range, $locid, null, $extra_opts);
	else
		shn_location($range, $_SESSION['dvr']['person']['displaced_loc'], null, $extra_opts);

	shn_form_fsclose();



	shn_form_submit("Next", "name=location_individual");

	shn_form_fclose();
	print '<br />';

}

function shn_dvr_set_person_major_details() {
	global $global;
	//$_SESSION['dvr']['person']['p_uuid']=shn_create_uuid();
	$_SESSION['dvr']['person']['typ_of_grp'] = $_POST['opt_group_type'];
//	print 'head name is' . $_POST['head_name'];
	$_SESSION['dvr']['person']['head_name'] = $_POST['head_name'];
	//$group=_shn_dvr_get_group_id($_POST['head_name']);

	//$_SESSION['dvr']['person']['group_id']=$_SESSION['dvr']['person']['head_name'];//group id 
	$_SESSION['dvr']['person']['full_name'] = $_POST['full_name'];
	$_SESSION['dvr']['person']['family_name'] = $_POST['family_name'];
	$_SESSION['dvr']['person']['local_name'] = $_POST['local_name'];
	$_SESSION['dvr']['person']['dob'] = $_POST['dob'];
	$_SESSION['dvr']['person']['opt_age_group'] = $_POST['opt_age_group'];
	$_SESSION['dvr']['person']['opt_gender'] = $_POST['opt_gender'];
	$_SESSION['dvr']['person']['opt_marital_status'] = $_POST['opt_marital_status'];
	$_SESSION['dvr']['person']['opt_religion'] = $_POST['opt_religion'];
	$_SESSION['dvr']['person']['opt_race'] = $_POST['opt_race'];

	$_SESSION['dvr']['person']['idcard'] = $_POST['idcard'];
	$_SESSION['dvr']['person']['passport'] = $_POST['passport'];
	$_SESSION['dvr']['person']['drv_licence'] = $_POST['drv_licence'];

	$_SESSION['dvr']['person']['mobile'] = $_POST['mobile'];
	$_SESSION['dvr']['person']['telephone'] = $_POST['telephone'];
	$_SESSION['dvr']['person']['email'] = $_POST['email'];
	$_SESSION['dvr']['person']['address'] = $_POST['address'];
	
	
	
	
	
	$loc = shn_location_get_form_submit_loc();

	//$_SESSION['dvr']['person']['displaced_loc'] = '';
	$_SESSION['dvr']['person']['displaced_loc'] = $loc;

	//$location=_shn_org_location_string($_SESSION['dvr']['group']['dis_loc']);

	$disloctype = $_POST['displacedlocationtypeof_group'];
	//$curloctype = $_POST['currentlocationtypeof_group'];

	//$_SESSION['dvr']['person']['currentlocationtypeof_group'] = $curloctype;
	$_SESSION['dvr']['person']['displacedlocationtypeof_group'] = $disloctype;
	
	
	
	
	
	
	
	
	
	if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type 
		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['picture']['tmp_name']);
			$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
			$_SESSION['dvr']['person']['image'] = $pic;
			$_SESSION['dvr']['person']['person_image_type'] = $ext;
			$_SESSION['dvr']['person']['person_image_height'] = $info[1];
			$_SESSION['dvr']['person']['person_image_width'] = $info[0];

		}

		$ext = '.' . $ext;
		$upload_dir = $global['approot'] . 'www/tmp/';
		$uploadfile = $upload_dir . 'ori_' . $_SESSION['dvr']['person']['p_uuid'] . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $_SESSION['dvr']['person']['p_uuid'] . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);

	}
}
function _shn_dvr_individual_physical_details_validate_error() {

	clean_errors();
	$error_flag = false;

	$pics = $_POST['finger_picture'];

	//print 'picture is' . $pics;

	if ($_FILES['finger_picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['finger_picture']['tmp_name']);
		//check the image type 

		if (!$info) {
			add_error(_("Invalid Image Type Please try again"));
			$error_flag = true;
		}
	}

	return $error_flag;

}

function _shn_dvr_individual_validate_error() {
	clean_errors();
	$error_flag = false;

	$gt = $_POST['opt_group_type'];
	$full_name = $_POST['full_name'];

	if (trim($gt) == null | trim($gt) == '===') {
		add_error(_("Please  select the group type"));
		$error_flag = true;
	}

	if (trim($full_name) == null | trim($full_name) == '') {
		add_error(_("Please fill the full name"));
		$error_flag = true;
	}

	$pics = $_POST['picture'];



	if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);

		
		//check the image type 

		if (!$info) {
			add_error(_("Invalid Image Type Please try again"));
			$error_flag = true;
		}
	}

	return $error_flag;

}

//add location dettails

function _shn_dvr_regconfirm_individual() {
	global $global;
	global $conf;
	$db = $global['db'];
?>
<h2><?= _('Confirm  Details of').$_SESSION['dvr']['person']['name'] ?></h2>
<div id="formcontainer">
<?php


	shn_form_fopen("edit_individual", null);

	shn_form_fsopen('Group Type and Personal details');

	shn_form_label(_("Group type: "), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['typ_of_grp']));

	shn_form_label(_("Full name"), $_SESSION['dvr']['person']['full_name']);

	shn_form_label(_("Family name"), $_SESSION['dvr']['person']['family_name']);

	shn_form_label(_("Local name"), $_SESSION['dvr']['person']['local_name']);

	shn_form_label(_("Current Photograph"), $_SESSION['dvr']['person']['picture']);
?>
	<p align='center'>
	<?php

	shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'adddvr_img', true);
?>
	
	</p>
	<?php


	shn_form_label(_("Date Of birth"), $_SESSION['dvr']['person']['dob']);

	shn_form_label(_("Age group"), $_SESSION['dvr']['person']['opt_age_group']);

	shn_form_label(_("Gender"), $_SESSION['dvr']['person']['opt_gender']);

	shn_form_label(_("Marital Status"), $_SESSION['dvr']['person']['opt_marital_status']);

	shn_form_label(_("Religion"), $_SESSION['dvr']['person']['opt_religion']);

	shn_form_label(_("Race"), $_SESSION['dvr']['person']['opt_race']);

	shn_form_fsclose();

	shn_form_fsopen("Identity");
	shn_form_label(_("Identity Card Number"), $_SESSION['dvr']['person']['nic']);
	shn_form_label(_("Passport Number"), $_SESSION['dvr']['person']['passport']);
	shn_form_label(_("Driving License"), $_SESSION['dvr']['person']['driving_licence']);

	shn_form_fsclose();

	shn_form_fsopen("Contact Information ");
	shn_form_label(_("Address"), $_SESSION['dvr']['person']['address']);
	shn_form_label(_("Postal Code"), $_SESSION['dvr']['person']['postal_code']);
	shn_form_label(_("Home Phone"), $_SESSION['dvr']['person']['telephone']);
	shn_form_label(_("Mobile"), $_SESSION['dvr']['person']['mobile']);
	shn_form_fsclose();

	shn_form_fsopen("Displaced/Current Location");
	$location = _shn_org_location_string($_SESSION['dvr']['person']['displaced_loc']);

	shn_form_label(_("Displaced Location"), $location);
	
	$location = _shn_org_location_string($_SESSION['dvr']['person']['current_loc']);
	$map_location = "Latitude= " . $_SESSION['dvr']['person']['gis_loc_x'] . " Longitude= " . $_SESSION['dvr']['person']['gis_loc_y'];
	shn_form_label(_("Current Location"), $location);
	shn_form_label(_("Map Location"), $map_location);
	shn_form_fsclose();

	// Contact infomation
	shn_form_fsopen("PhysicalInformation");

	shn_form_label(_("Current Fingerprint"), $_SESSION['dvr']['person']['finger_picture']);
?>
	<p align='center'>
	<?php

	shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addfingerprint_img', true,"fingerprint");
?>
	
	</p>
	<?php


	shn_form_label(_("Eye Color"), $_SESSION['dvr']['person']['opt_eye_color']);
	shn_form_label(_("Skin Color"), $_SESSION['dvr']['person']['opt_skin_color']);
	shn_form_label(_("Hair Color"), $_SESSION['dvr']['person']['opt_hair_color']);
	shn_form_label(_("Height"), $_SESSION['dvr']['person']['height']);
	shn_form_label(_("Weight"), $_SESSION['dvr']['person']['weight']);
	shn_form_label(_("Blood Type"), $_SESSION['dvr']['person']['opt_blood_type']);
	shn_form_label(_("Clothing and appearence"), $_SESSION['dvr']['person']['last_clothing']);
	shn_form_label(_("Other Details"), $_SESSION['dvr']['person']['comments']);

	shn_form_fsclose();
?>
<br />
<center>
<?php


	//create the submit button
	$extra_opts['br'] = false;

	shn_form_submit(_("Save"), 'name="save"');

	shn_form_submit(_("Edit Details"), "name=edit_details");
	shn_form_hidden(array (
		'action' => '0'
	));
	// _shn_dvr_action_change_javascript("confirm_reg","action");
?>
</center>
<br />
<?php


	//close the form
	shn_form_fclose();
?>				     
</div>
<?php


}

function shn_dvr_person_confirm() {

	$msg = $_SESSION['dvr']['person']['full_name'] . " was succesfully registered ";
	add_confirmation($msg);
}

function shn_dvr_disp_and_crnt_loc() {
	_shn_dvr_print_header(_("Edit Individual"));
	global $global;
	global $conf;
	shn_form_fopen("edit_individual", null, array (
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'entry'
	));
	/*shn_form_fsopen(_('Displaced Location Of The Victim'));
	print '<br />';
	$typ_of_grp = array ();
	//array_push($typ_of_grp, '-- Select Option --');
	array_reverse($typ_of_grp);

	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	$extra_opts['value'] = $_SESSION['dvr']['person']['displacedlocationtypeof_group'];

	shn_form_select($typ_of_grp, _("Displaced Location"), 'displacedlocationtypeof_group', '', $extra_opts);

	$range = shn_dvr_get_loc_range();

	shn_location($range, null, null, $extra_opts);

	shn_form_fsclose();*/
	shn_form_fsopen(_('Current Location Of The Victim'));

	print '<br />';
	$typ_of_grp = array ();
	array_push($typ_of_grp, '-- Select Option --');
	array_reverse($typ_of_grp);
	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	$extra_opts['value'] = $_SESSION['dvr']['person']['currentlocationtypeof_group'];
	shn_form_select($typ_of_grp, _("Current Location"), 'currentlocationtypeof_group', '', $extra_opts);
	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();

	$extra_opts['camps'] = true;

	//shn_location($range, $_POST[$range["end"]], $parent, $extra_opts);

	$locid = get_person_location_details($_SESSION['dvr']['person']['p_uuid'].'-curr');
	if ($_SESSION['dvr']['person']['edit_individual_clicked'] == null |  $_SESSION['dvr']['person']['edit_individual_clicked']==false)
		shn_location($range, $locid, null, $extra_opts);
	else
		shn_location($range, $_SESSION['dvr']['person']['current_loc'], null, $extra_opts);

	shn_form_fsclose();

	shn_form_fsopen(_("Location Information"));
	echo _("Plot the Camp/Shelter Location or Coordinates below");
	shn_form_hidden(array (
		'seq' => 'chk'
	));
	shn_form_fsclose();

	//call gis api from gis module
	include $global['approot'] . "/mod/gis/gis_fns.inc";
	shn_gis_add_marker_map_form("GIS Map", "Disaster Victims Registry");

	shn_form_fsclose();
	shn_form_submit("Next", "name=physical_button");
	shn_form_fclose();
	print '<br />';

	//shn_dvr_crnt_loc_vic();

}

function shn_dvr_set_person_physical_details() {
	$_SESSION['dvr']['person']['opt_eye_color'] = $_POST['opt_eye_color'];
	$_SESSION['dvr']['person']['opt_skin_color'] = $_POST['opt_skin_color'];
	$_SESSION['dvr']['person']['opt_hair_color'] = $_POST['opt_hair_color'];
	$_SESSION['dvr']['person']['height'] = $_POST['height'];
	$_SESSION['dvr']['person']['weight'] = $_POST['weight'];
	$_SESSION['dvr']['person']['opt_blood_type'] = $_POST['opt_blood_type'];
	$_SESSION['dvr']['person']['last_clothing'] = $_POST['last_clothing'];
	$_SESSION['dvr']['person']['comments'] = $_POST['comments'];
	$_SESSION['dvr']['person']['finger_picture'] = $_POST['finger_picture'];

	if ($_FILES['finger_picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['finger_picture']['tmp_name']);
		//check the image type 

		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['finger_picture']['tmp_name']);
			$pic = fread(fopen($_FILES['finger_picture']['tmp_name'], "r"), $size);
			$_SESSION['dvr']['person']['finger_image'] = $pic;
			$_SESSION['dvr']['person']['finger_image_type'] = $ext;
			$_SESSION['dvr']['person']['finger_image_height'] = $info[1];
			$_SESSION['dvr']['person']['finger_image_width'] = $info[0];

		}

	}

}

function shn_dvr_set_person_location_details() {
	$loc = shn_location_get_form_submit_loc();

	if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
		$_SESSION['dvr']['person']['gis_loc_x'] = $_POST['loc_x'];
		$_SESSION['dvr']['person']['gis_loc_y'] = $_POST['loc_y'];
	} else {
		$_POST['loc_x'] = $_POST['gps_x'];
		$_POST['loc_y'] = $_POST['gps_y'];
		$_SESSION['dvr']['person']['gis_loc_x'] = $_POST['loc_x'];
		$_SESSION['dvr']['person']['gis_loc_y'] = $_POST['loc_y'];
	}

	//$_SESSION['dvr']['person']['displaced_loc'] = '';
	$_SESSION['dvr']['person']['current_loc'] = $loc;

	//$location=_shn_org_location_string($_SESSION['dvr']['group']['dis_loc']);

	$disloctype = $_POST['displacedlocationtypeof_group'];
	$curloctype = $_POST['currentlocationtypeof_group'];

	$_SESSION['dvr']['person']['currentlocationtypeof_group'] = $curloctype;
	//$_SESSION['dvr']['person']['displacedlocationtypeof_group'] = $disloctype;

	
}

function shn_dvr_physical_information($errors = false) {

	if ($errors)
		display_errors();

	shn_form_fopen("edit_individual", null, array (
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'chk'
	));

	shn_form_fsopen(_('Upload FingerPrint'));
	print '<br />';
	
	
	
	
	
	
	
	if (	$_SESSION['dvr']['person']['edit_individual_clicked']==true) {
		shn_form_label(_("Current Finger Print"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

		shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addfingerprint_img', true,'fingerprint');
?>
	
	</p>
	<?php

	}
	
	else
	{
		
shn_form_label(_("Current FingerPrint"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php
//print 'here'.$_SESSION['dvr']['group']['headid'];
		shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], 'database', 'dvr', 'addfingerprint_img', false,'fingerprint');
?>
	
	</p>
	<?php

	}
		
	
	
	
	
	shn_form_upload(_('Upload FingerPrint'), "finger_picture");
	shn_form_fsclose();
	print '<br />';
$_SESSION['dvr']['person']['edit_individual_clicked']=false;
	shn_form_fsopen(_('Physical Details'));

	print '<br />';
	shn_form_opt_select("opt_eye_color", _('Eye Colour'));
	shn_form_opt_select("opt_skin_color", _('Skin Colour'));
	shn_form_opt_select("opt_hair_color", _('Hair Colour'));
	shn_form_text(_('Height'), 'height', 'size="10"');
	shn_form_text(_('Weight'), 'weight', 'size="10"');
	shn_form_opt_select("opt_blood_type", _('Blood Type'));
	//shn_form_textarea(_('Other Distinctive Features'), 'physical_comments');
	shn_form_fsclose();
	shn_form_fsopen(_('Other Details'));
	print '<br />';

	shn_form_textarea(_('Description Of Clothing And Appearance'), 'last_clothing');
	shn_form_textarea(_('Other Relevant Information'), 'comments');
	shn_form_fsclose();
	shn_form_submit(_('Finish'), "name=finish");
	shn_form_fclose();
	print '<br />';

}

function _shn_dvr_update_individual_todb() {
	global $global;

	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
	_shn_dvr_update_individual();
}
?>
