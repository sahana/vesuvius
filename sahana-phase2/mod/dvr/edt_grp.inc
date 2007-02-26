

<?php


/**
 * 
 * Functions to edit a group in DVR
 * 
 *
 *  PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera  
 * @author     Sheran Corera
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ('lib.inc');
//include_once ('add_new_indv.inc');
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_errors.inc');
include_once ($global['approot'] . '/inc/lib_image.inc');
include_once ($global['approot'] . '/mod/or/lib_or.inc');
include_once ($global['approot'] . '/inc/lib_uuid.inc');
include_once ($global['approot'] . '/mod/dvr/data_access.inc');

//get the value from database
function get_dvr_populate_group_major_details() {
	$head_details = get_group_type_and_head_details($_GET['groupid']);

	//print 'head details are' . $head_details->fields['group_type'];
	$_SESSION['dvr']['group']['id'] = $_GET['groupid'];
	$_SESSION['dvr']['group']['typ_of_grp'] = $head_details->fields['group_type'];
	$_SESSION['dvr']['group']['full_name'] = $head_details->fields['full_name'];
	$_SESSION['dvr']['group']['family_name'] = $head_details->fields['family_name'];
	$_SESSION['dvr']['group']['local_name'] = $head_details->fields['l10n_name'];
	$_SESSION['dvr']['group']['nic'] = $head_details->fields['nic'];
	$_SESSION['dvr']['group']['headid'] = $head_details->fields['head_id'];
	$contact_details = get_contacts($_SESSION['dvr']['group']['headid']);
	while (!$contact_details->EOF) {

		$contacttype = $contact_details->fields['opt_contact_type'];
		$contactvalue = $contact_details->fields['contact_value'];

		if ($contacttype == 'address') {
			$_SESSION['dvr']['group']['address'] = $contactvalue;
		} else
			if ($contacttype == 'email') {
				$_SESSION['dvr']['group']['email'] = $contactvalue;
			} else
				if ($contacttype == 'mobile') {
					$_SESSION['dvr']['group']['mobile'] = $contactvalue;
				} else
					if ($contacttype == 'telephone') {
						$_SESSION['dvr']['group']['telephone'] = $contactvalue;
					}
		$contact_details->MoveNext();
	}

	$group_content = get_group_description($_GET['groupid']);
	$_SESSION['dvr']['group']['adlt_mls'] = $group_content->fields['no_of_adult_males'];
	$_SESSION['dvr']['group']['adlt_fmls'] = $group_content->fields['no_of_adult_females'];
	$_SESSION['dvr']['group']['chldrn'] = $group_content->fields['no_of_children'];
	$_SESSION['dvr']['group']['dsplcd'] = $group_content->fields['no_displaced'];
	$_SESSION['dvr']['group']['mising'] = $group_content->fields['no_missing'];
	$_SESSION['dvr']['group']['dead'] = $group_content->fields['no_dead'];
	$_SESSION['dvr']['group']['rehbd'] = $group_content->fields['no_rehabilitated'];
	$_SESSION['dvr']['group']['opt_dvr_service'] = $group_content->fields['checklist'];
	$_SESSION['dvr']['group']['other'] = $group_content->fields['description'];

}

//add group type and group head details
function shn_dvr_edit_grouptype_and_head_details_start($errors = false) {
	if ($_SESSION['dvr']['editgroup']['edit_clicked']  == false)
		get_dvr_populate_group_major_details();
	_shn_dvr_print_header(_("Edit Group"));
	shn_dvr_grouptype_and_head_details($errors);
}

//error handling
function _shn_dvr_group_validate_error() {
	clean_errors();
	$error_flag = false;

	$gt = $_POST['opt_group_type'];
	$full_name = $_POST['full_name'];

/*	if (!isset ($_SESSION['dvr']['group']['headid'])) {
		$_SESSION['dvr']['group']['headid'] = shn_create_uuid();

	}*/

	if (trim($gt) == null | trim($gt) == '===') {
		add_error(_("Please  select the group type"));
		$error_flag = true;
	}
	if (trim($full_name) == null | trim($full_name) == '') {
		add_error(_("Please fill the full name"));
		$error_flag = true;
	}

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

function shn_dvr_set_group_major_details() {

	global $global;
	global $conf;
	$_SESSION['dvr']['group']['typ_of_grp'] = $_POST['typ_of_grp'];
	$_SESSION['dvr']['group']['full_name'] = $_POST['full_name'];
	$_SESSION['dvr']['group']['family_name'] = $_POST['family_name'];
	$_SESSION['dvr']['group']['local_name'] = $_POST['local_name'];
	$_SESSION['dvr']['group']['nic'] = $_POST['nic'];
	$_SESSION['dvr']['group']['picture'] = $_POST['picture'];

	$_SESSION['dvr']['group']['mobile'] = $_POST['mobile'];
	$_SESSION['dvr']['group']['telephone'] = $_POST['telephone'];
	$_SESSION['dvr']['group']['email'] = $_POST['email'];
	$_SESSION['dvr']['group']['address'] = $_POST['address'];
	$_SESSION['dvr']['group']['adlt_mls'] = $_POST['adlt_mls'];
	$_SESSION['dvr']['group']['adlt_fmls'] = $_POST['adlt_fmls'];
	$_SESSION['dvr']['group']['chldrn'] = $_POST['chldrn'];
	$_SESSION['dvr']['group']['dsplcd'] = $_POST['dsplcd'];
	$_SESSION['dvr']['group']['mising'] = $_POST['misng'];
	$_SESSION['dvr']['group']['dead'] = $_POST['dead'];
	$_SESSION['dvr']['group']['rehbd'] = $_POST['rehbd'];

	if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type 
		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['picture']['tmp_name']);
			$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
			$_SESSION['dvr']['group']['image'] = $pic;
			$_SESSION['dvr']['group']['image_type'] = $ext;
			$_SESSION['dvr']['group']['image_height'] = $info[1];
			$_SESSION['dvr']['group']['image_width'] = $info[0];

		}

		$ext = '.' . $ext;
		$upload_dir = $global['approot'] . 'www/tmp/';
		$uploadfile = $upload_dir . 'ori_' . $_SESSION['dvr']['group']['headid'] . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $_SESSION['dvr']['group']['headid'] . $ext;
		//resize the image size
		shn_image_resize($uploadfile, $desc_path, 100, 100);

	}
}

//group type and head details
function shn_dvr_grouptype_and_head_details($errors = false) {
	if ($errors)
		display_errors();

	shn_form_fopen("edit_group", null, array (
		'req_message' => true,
		'enctype' => 'enctype="multipart/form-data"'
	));
?>
    <?php


	shn_form_hidden(array (
		'seq' => 'chk'
	));
	//select the group type
	shn_form_fsopen(_("Select Group Type"));
	print '<div class="info">';
	print _("Please select a Group that describes you well");
	print '<br />';

	print '<br />';
	print '</div>';
	print '<br />';

	//$extra_opts['sort'] = ;
	$extra_opts['help'] = _("Please Select the group type");
	$extra_opts['req'] = true;
	$extra_opts['value'] = $_SESSION['dvr']['group']['typ_of_grp'];
	$extra_opts['sort'] = 'option_code';

	shn_form_opt_select('opt_group_type', _("Type of Group"), '', $extra_opts);

	shn_form_fsclose();
	//group head information
	shn_form_fsopen(_("Head Of Group"));

	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['group']['full_name'];
	$extra_opts['help'] = _("Enter the Full Name.(Required)");
	$extra_opts['req'] = true;

	shn_form_text(_("Full Name"), 'full_name', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['family_name'];
	$extra_opts['help'] = _("Enter the Family Name.");
	$extra_opts['req'] = false;

	shn_form_text(_("Family Name"), 'family_name', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['local_name'];
	$extra_opts['help'] = _("Enter the local Name.");
	$extra_opts['req'] = false;

	shn_form_text(_("Local Name"), 'local_name', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['nic'];
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	$extra_opts['req'] = false;

	shn_form_text(_("NIC No"), 'nic', null, $extra_opts);

/*	shn_form_label(_("Current Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

	//print 'headid is' . $_SESSION['dvr']['group']['headid'];

	shn_show_thumb_url($_SESSION['dvr']['group']['headid'], 'database', 'dvr', 'addvictim_img', false);
?>
	
	</p>
	<?php*/

	if (	$_SESSION['dvr']['editgroup']['edit_clicked']==true) {
		shn_form_label(_("Current Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

		shn_show_thumb_url($_SESSION['dvr']['group']['headid'], '', 'dvr', 'adddvr_img', true);
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
		shn_show_thumb_url($_SESSION['dvr']['group']['headid'], '', 'dvr', 'adddvr_img', false);
?>
	
	</p>
	<?php

	}
		
		
		
	
	
	
	$extra_opts['value'] = $_SESSION['dvr']['group']['picture'];
	$extra_opts['help'] = _("Upload the photograph if available");
	$extra_opts['req'] = false;
	shn_form_upload(_('Upload Photograph'), "picture");

	$extra_opts['value'] = $_SESSION['dvr']['group']['mobile'];
	$extra_opts['help'] = _("Enter the Mobile number if available. (Optional)");
	shn_form_text(_("Mobile"), 'mobile', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['telephone'];
	$extra_opts['help'] = _("Enter a Land Phone number if available. (Optional)");
	shn_form_text(_("Telephone"), 'telephone', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['email'];
	$extra_opts['help'] = _("Enter a Email Address if available. (Optional)");
	shn_form_text(_("Email"), 'email', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['address'];
	$extra_opts['help'] = _("Enter a Address if available. (Optional)");

	shn_form_textarea(_("Address"), 'address', null, $extra_opts);
?>
   
<?php


	shn_form_fsclose();
	print '<br />';

	//head count
	shn_form_fsopen(_("No Of Members In Group"));

	print '<br />';
	$extra_opts['value'] = $_SESSION['dvr']['group']['adlt_mls'];
	$extra_opts['help'] = _("Enter the adult mail count. (Optional)");
	shn_form_text(_("Adult Males"), 'adlt_mls', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['fmls'];
	$extra_opts['help'] = _("Enter the adult female count. (Optional)");
	shn_form_text(_("Adult Females"), 'adlt_fmls', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['chldrn'];
	$extra_opts['help'] = _("Enter the Children count  (Optional)");
	shn_form_text(_("Children"), 'chldrn', null, $extra_opts);
	shn_form_fsclose();
	print '<br />';
	//member status
	shn_form_fsopen(_("Status Of Members In Group"));
	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['group']['dsplcd'];
	$extra_opts['help'] = _("Enter the displaced people count(Optional)");
	shn_form_text(_("Displaced"), 'dsplcd', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['misng'];
	$extra_opts['help'] = _("Enter the missing people count  (Optional)");
	shn_form_text(_("Missing"), 'misng', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['dead'];
	$extra_opts['help'] = _("Enter the dead people count. (Optional)");
	shn_form_text(_("Dead"), 'dead', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['rehbd'];
	$extra_opts['help'] = _("Enter the rehabilated  people count(Optional)");
	shn_form_text(_("Rehabilitated"), 'rehbd', null, $extra_opts);

	shn_form_fsclose();
	shn_form_submit(_("Edit Location Check Details"), "name=location_button");
//	shn_form_submit(_("Finish"));
	shn_form_fclose();
	print '<br />';
}

function shn_dvr_loc_dtls($errors = false) {

	global $global;
	global $conf;
	_shn_dvr_print_header(_("Edit Group"));

	if ($errors)
		display_errors();

	shn_form_fopen("edit_group", null, array (
		'req_message' => false
	));
	shn_form_hidden(array (
		'seq' => 'chk'
	));

	shn_form_fsopen(_("Displaced Location"));

	$range = shn_dvr_get_loc_range();

	shn_location($range, null, null, $extra_opts);

	shn_form_fsclose();
	shn_form_fclose();
	shn_form_fopen("edit_group", null, array (
		'req_message' => false
	));
	shn_form_fsopen(_("Current Location"));

	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();

	$extra_opts['camps'] = true;

	//shn_location($range, $_POST[$range["end"]], $parent, $extra_opts);

	$locid = get_group_location_details($_SESSION['dvr']['group']['id']);
	if ($_SESSION['dvr']['editgroup']['edit_clicked'] == false)
		shn_location($range, $locid, null, $extra_opts);
	else
		shn_location($range, $_SESSION['dvr']['group']['current_loc'], null, $extra_opts);

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
	shn_form_submit(_("Check List"), "name=checklist_button");
	//shn_form_submit(_("Finish"));
	shn_form_fclose();

	print '<br />';

}

function _shn_dvr_group_location_validate_error() {
	$error = false;
	$loc = shn_location_get_form_submit_loc();
	if ($loc == -1) {
		$error = true;
		add_error(SHN_ERR_DVR_LOCATION_INCOMPLETE);

	}
	return $error;
}

function shn_dvr_set_location_details() {

	$loc = shn_location_get_form_submit_loc();

	if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
		$_SESSION['dvr']['group']['gis_loc_x'] = $_POST['loc_x'];
		$_SESSION['dvr']['group']['gis_loc_y'] = $_POST['loc_y'];
	} else {
		$_POST['loc_x'] = $_POST['gps_x'];
		$_POST['loc_y'] = $_POST['gps_y'];
		$_SESSION['dvr']['group']['gis_loc_x'] = $_POST['loc_x'];
		$_SESSION['dvr']['group']['gis_loc_y'] = $_POST['loc_y'];
	}

	$_SESSION['dvr']['group']['displaced_loc'] = '';
	$_SESSION['dvr']['group']['current_loc'] = $loc;

	$location = _shn_org_location_string($_SESSION['dvr']['group']['dis_loc']);

	//	shn_dvr_set_location_details();
}

function shn_dvr_cklst_and_desc() {
	_shn_dvr_print_header(_("Edit Group"));
	shn_form_fopen("edit_group", null, array (
		'req_message' => false
	));

	shn_form_fsopen(_("Checklist"));

	print '<br />';

	//$extra_opts['value'] = $dry_rtns;
	$extra_opts['help'] = _("Please select items " .
	"tick the Check Box (Optional)");

	if ($_SESSION['dvr']['editgroup']['edit_clicked'] == false) {
		$_SESSION['dvr']['group']['opt_dvr_service'] = explode(',', $_SESSION['dvr']['group']['opt_dvr_service']);

	//	print 'services are' . $_SESSION['dvr']['group']['opt_dvr_service'];
	}
	$extra_opts['selected'] = $_SESSION['dvr']['group']['opt_dvr_service'];

	shn_form_opt_checkbox(_("opt_dvr_service"), $extra_opts);

	shn_form_fsclose();

	print '<br />';

	shn_form_fsopen(_("Group Description"));

	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['group']['other'];
	$extra_opts['help'] = _("Enter the group description. (Optional)");
	shn_form_textarea(_("Description"), 'desc', null, $extra_opts);
	shn_form_submit(_("Finish"), 'name="end_button"');
$_SESSION['dvr']['editgroup']['edit_clicked'] ='false';
	shn_form_fsclose();

	shn_form_fclose();
	print '<br />';

}

function _shn_dvr_set_checklist() {
	$dvr_service = $_POST['opt_dvr_service'];

	$_SESSION['dvr']['group']['opt_dvr_service'] = $dvr_service;
	$_SESSION['dvr']['group']['other'] = $_POST['other'];

}

function _shn_dvr_regconfirm_group() {
	global $global;
	global $conf;
	$db = $global['db'];
?>
<h2><?= _('Confirm Group Details  Headed by').$_SESSION['dvr']['group']['full_name'] ?></h2>

<div id="formcontainer">

<?php


	shn_form_fopen("edit_group", null);

	shn_form_fsopen('Group type and head details');

	if ($_SESSION['dvr']['group']['typ_of_grp'] == 1) {
		$type = 'Families';
	} else
		if ($_SESSION['dvr']['group']['typ_of_grp'] == 2) {
			$type = 'Passengers';
		} else
			if ($_SESSION['dvr']['group']['typ_of_grp'] == 3) {
				$type = 'Tourists';
			} else {
				$type = 'Other';
			}

	shn_form_label(_("Group type: "), $type);
	shn_form_label(_("Full name"), $_SESSION['dvr']['group']['full_name']);
	shn_form_label(_("Family name"), $_SESSION['dvr']['group']['family_name']);
	shn_form_label(_("Local name"), $_SESSION['dvr']['group']['local_name']);
	shn_form_label(_("NIC"), $_SESSION['dvr']['group']['nic']);
	shn_form_label(_("Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

//	if ($_SESSION['dvr']['group']['picture'] != null)
		shn_show_thumb_url($_SESSION['dvr']['group']['headid'], '', 'dvr', 'addvictim_img', true);
	//else
		//shn_show_thumb_url($_SESSION['dvr']['group']['headid'], 'database', 'dvr', 'addvictim_img', false);
?>
	
	</p>
	<?php


	shn_form_label(_("Mobile"), $_SESSION['dvr']['group']['mobile']);
	shn_form_label(_("Telephone"), $_SESSION['dvr']['group']['telephone']);
	shn_form_label(_("Email"), $_SESSION['dvr']['group']['email']);
	shn_form_label(_("Address"), $_SESSION['dvr']['group']['address']);
	shn_form_fsclose();
	shn_form_fsopen("Member Count");
	shn_form_label(_("Adult Males"), $_SESSION['dvr']['group']['adlt_mls']);
	shn_form_label(_("Adult Females"), $_SESSION['dvr']['group']['adlt_fmls']);
	shn_form_label(_("Children"), $_SESSION['dvr']['group']['chldrn']);
	shn_form_fsclose();

	shn_form_fsopen("Status of Members in Group");
	shn_form_label(_("Displaced"), $_SESSION['dvr']['group']['dsplcd']);
	shn_form_label(_("Missing"), $_SESSION['dvr']['group']['misng']);
	shn_form_label(_("Dead"), $_SESSION['dvr']['group']['dead']);
	shn_form_label(_("Rehabilitated"), $_SESSION['dvr']['group']['rehbd']);
	shn_form_fsclose();

	shn_form_fsopen(" Location");
	$location = _shn_org_location_string($_SESSION['dvr']['group']['displaced_loc']);

	shn_form_label(_("Displaced Location"), $location);
	$location = _shn_org_location_string($_SESSION['dvr']['group']['current_loc']);

	$map_location = "Latitude= " . $_SESSION['dvr']['group']['gis_loc_x'] . " Longitude= " . $_SESSION['dvr']['group']['gis_loc_y'];

	shn_form_label(_("Current Location"), $location);
	shn_form_label(_("Current Map Location"), $map_location);
	shn_form_fsclose();

	// Contact infomation
	shn_form_fsopen("Checklist Information");

	$checklist = _shn_dvr_getchecklist();
	$count = $_SESSION['elementcount'];
	$selected = array ();

	$selected = $_SESSION['dvr']['group']['opt_dvr_service'];

	for ($l = 0; $l < count($selected); $l++) {

		$opt = _shn_dvr_getoptiondescription($selected[$l]);

		shn_form_label(_($opt), 'Required');
	}

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


	// end of form
}
//shn_dvr_mbr_confirm();

function shn_dvr_mbr_confirm() {

	$msg = $_SESSION['dvr']['group']['name'] . " group was succesfully updated ";
	add_confirmation($msg);
}
function _shn_dvr_commit() {

	global $global;

	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
	_shn_dvr_update_group();
}
?>
