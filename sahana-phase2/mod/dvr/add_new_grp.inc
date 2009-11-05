<?php

/**
 * 
 * Functions to add group in DVR
 * 
 *
 *  PHP version 4 and 5
 *in
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera  
 * @author     Sheran Corera
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


//add group type and group head details
function shn_dvr_grouptype_and_head_details_start($errors = false) {
	
    //unset($_SESSION['dvr_add_group']['entry']['p_uuid']);
	_shn_dvr_print_header(_t("Add New Group"));
	shn_dvr_grouptype_and_head_details($errors);
	
}


//error handling
function _shn_dvr_group_validate_error() {
	clean_errors();
	$error_flag = false;

	$gt = $_POST['opt_group_type'];
	$full_name = $_POST['full_name'];
	
	
	if (trim($gt) == null | trim($gt) == '===') {
		add_error(_t("Please  select the group type"));
		$error_flag = true;
	}

	if (trim($full_name) == null | trim($full_name) == '') {
		add_error(_t("Please fill the full name"));
		$error_flag = true;
	}
	

    $email=$_POST['email'];
    if(!shn_valid_email($email,false))
    {
        add_error(_t("Invalid email entered"));	
        $error_flag = true;
    }
	
	$adltmales=$_POST['adlt_mls'];
	$adltfmales=$_POST['adlt_fmls'];
	$chldrn=$_POST['chldrn'];
	
	$dsplcd = $_POST['dsplcd'];
	$misng = $_POST['misng'];
    $dead =	$_POST['dead'];
    $rehbd =	 $_POST['rehbd'];
	
	if($adltmales!=null)
	{
	if(!shn_valid_number($adltmales))
	{
		add_error(_t("Adult male count should be a number"));
			$error_flag = true;
	}
	}
	
	if($adltfmales!=null)
	{
	if(!shn_valid_number($adltfmales))
	{
		add_error(_t("Adult female count should be a number"));
			$error_flag = true;
	}
	
	}
	
	
	if($chldrn!=null)
	{
	if(!shn_valid_number($chldrn))
	{
		add_error(_t("Children count should be a number"));
			$error_flag = true;
	}
	
	}
	
	
	
	
	
	if($dsplcd!=null)
	{
	if(!shn_valid_number($dsplcd))
	{
		add_error(_t("Displaced count should be a number"));
			$error_flag = true;
	}
	
	}
	
	
	
	if($misng!=null)
	{
	if(!shn_valid_number($misng))
	{
		add_error(_t("Missing people count should be a number"));
			$error_flag = true;
	}
	
	}
	

	
	if($dead!=null)
	{
	if(!shn_valid_number($dead))
	{
		add_error(_t("Death count should be a number"));
			$error_flag = true;
	}
	
	}
	
	
	
	
	
	if($rehbd!=null)
	{
	if(!shn_valid_number($rehbd))
	{
		add_error(_t("Rehabilitated count should be a number"));
			$error_flag = true;
	}
	
	}
	
	
	if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type 

		if (!$info) {
			add_error(_t("Invalid image type.Please try again"));
			$error_flag = true;
		}

	}


	return $error_flag;
}

function _shn_dvr_group_location_validate_error() {
	$error = false;
	$loc = shn_location_get_form_submit_loc();
	if ($loc == -1) {
		$error = true;
		add_error("Please select  a valid location");

	}
	return $error;
}


//setting the group major details
function shn_dvr_set_group_major_details() {

	global $global;
	global $conf;
	
	if($_SESSION['dvr']['group']['edit_clicked'] != true)
	$_SESSION['dvr_add_group']['entry']['p_uuid'] = shn_create_uuid();
	
	$_SESSION['dvr']['group']['typ_of_grp'] = $_POST['opt_group_type'];
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
	$_SESSION['dvr']['group']['misng'] = $_POST['misng'];
	$_SESSION['dvr']['group']['dead'] = $_POST['dead'];
	$_SESSION['dvr']['group']['rehbd'] = $_POST['rehbd'];

    $loc = shn_location_get_form_submit_loc();
    $_SESSION['dvr']['group']['displaced_loc'] = $loc;

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
		$uploadfile = $upload_dir . 'ori_' . $_SESSION['dvr_add_group']['entry']['p_uuid'] . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $_SESSION['dvr_add_group']['entry']['p_uuid'] . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);

	}
}

//group type and head details
function shn_dvr_grouptype_and_head_details($errors = false) 
{
	if ($errors)
	display_errors();

	shn_form_fopen("add_new_grp", null, array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));


	shn_form_hidden(array ('seq' => 'chk'));
	//select the group type
	shn_form_fsopen(_t("Select Group Type"));
	print '<div class="info">';
	print _t("Please select a group that describes you well");
	print '<br />';

	print '<br />';
	print '</div>';
	print '<br />';
    $extra_opts['help'] = _t("Disaster victims are classified according to groups. Please Select the 'group type' from the drop down menu");
	$extra_opts['req'] = true;
	$extra_opts['value'] = $_SESSION['dvr']['group']['typ_of_grp'];
	$extra_opts['sort'] = 'option_code';

	shn_form_opt_select('opt_group_type', _t("Type of Group"), '', $extra_opts);

	shn_form_fsclose();
	//group head information

	shn_form_fsopen(_t("Head Of Group"));

	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['group']['full_name'];
	$extra_opts['help'] = _t("Enter the name of the head of the group here(Required). You can provide Family name or Local name if applicable.");
	$extra_opts['req'] = true;

	shn_form_text(_t("Full Name"), 'full_name', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['family_name'];
	$extra_opts['help'] = _t("Enter the family name of the head of the group here.");
	$extra_opts['req'] = false;

	shn_form_text(_t("Family Name"), 'family_name', null,$extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['group']['local_name'];
	$extra_opts['help'] = _t("Enter the local Name of the head of the group here.");
	$extra_opts['req'] = false;

	shn_form_text(_t("Local Name"), 'local_name', null,$extra_opts);
	$extra_opts['value'] = $_SESSION['dvr']['group']['nic'];
	$extra_opts['help'] = _t("Enter the National Identity Card Number, Passport number or any other proof for identity(Optional)");
	$extra_opts['req'] = false;

	shn_form_text(_t("NIC No"), 'nic', null, $extra_opts);


	if ($_SESSION['dvr']['group']['edit_clicked']==true) {
		shn_form_label(_t("Current Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

		shn_show_thumb_url($_SESSION['dvr_add_group']['entry']['p_uuid'], '', 'dvr', 'adddvr_img', true);
?>
	
	</p>
	<?php

	}
    //$_SESSION['dvr']['group']['edit_clicked'] = false;
	$extra_opts['help'] = _t("Upload the photograph of the head of the group if available");
	$extra_opts['req'] = false;
	
	shn_form_upload(_t('Upload Photograph'), "picture");

	$extra_opts['value'] = $_SESSION['dvr']['group']['mobile'];
	$extra_opts['help'] = _t("Enter the Mobile phone number if available. (Optional)");
	shn_form_text(_t("Mobile"), 'mobile', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['telephone'];
	$extra_opts['help'] = _t("Enter a Land Phone number if available. (Optional)");
	shn_form_text(_t("Telephone"), 'telephone', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['email'];
	$extra_opts['help'] = _t("Enter a Email Address if available. (Optional)");
	shn_form_text(_t("Email"), 'email', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['address'];
	$extra_opts['help'] = _t("Enter a postal address of head of the group if available. (Optional)");

	shn_form_textarea(_t("Address"), 'address', null, $extra_opts);
?>
   
<?php


	shn_form_fsclose();
	print '<br />';

	//head count
	shn_form_fsopen(_t("No Of Members In Group"));

	print '<br />';
	$extra_opts['value'] = $_SESSION['dvr']['group']['adlt_mls'];
	$extra_opts['help'] = _t("Enter the number of adult males in the group if known. (Optional)");
	shn_form_text(_t("Adult Males"), 'adlt_mls', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['adlt_fmls'];
	$extra_opts['help'] = _t("Enter the number of adult females in the group if known. (Optional)");
	shn_form_text(_t("Adult Females"), 'adlt_fmls', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['chldrn'];
	$extra_opts['help'] = _t("Enter the number of children in the group  (Optional)");
	shn_form_text(_t("Children"), 'chldrn', null, $extra_opts);
	shn_form_fsclose();
	
	print '<br />';
	//member status
	
	shn_form_fsopen(_t("Status Of Members In Group"));
	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['group']['dsplcd'];
	$extra_opts['help'] = _t("Enter the number of displaced people in the group(Optional)");
	shn_form_text(_t("Displaced"), 'dsplcd', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['misng'];
	$extra_opts['help'] = _t("Enter the number of missing people in the group(Optional)");
	shn_form_text(_t("Missing"), 'misng', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['dead'];
	$extra_opts['help'] = _t("Enter the number of deceased people in the group(Optional)");
	shn_form_text(_t("Dead"), 'dead', null, $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['group']['rehbd'];
	$extra_opts['help'] = _t("Enter the number of rehabilitated people in the group(Optional)");
	shn_form_text(_t("Rehabilitated"), 'rehbd', null, $extra_opts);

	shn_form_fsclose();
	
	
	shn_form_fsopen(_t("Displaced Location"));

	$range = shn_dvr_get_loc_range();	

	shn_location($range, $_SESSION['dvr']['group']['displaced_loc'], null,null);

	shn_form_fsclose();
	
	//shn_form_submit(_t("Add Location Check Details"), "name=location_button");
	shn_form_submit(_t("Next"), "name=location_button");
	//shn_form_submit(_t("Finish"));
	shn_form_fclose();
	print '<br />';
}

//location details
function shn_dvr_loc_dtls($errors = false) {

	global $global;
	global $conf;
	_shn_dvr_print_header(_t("Add New Group"));

	if ($errors)
		display_errors();

	shn_form_fopen("add_new_grp", null, array (
		'req_message' => false
	));
	shn_form_hidden(array (
		'seq' => 'chk'
	));

	/*shn_form_fsopen(_t("Displaced Location"));

	$range = shn_dvr_get_loc_range();

	shn_location($range, null, null,null);

	shn_form_fsclose();*/
/*	shn_form_fclose();
	shn_form_fopen("add_new_grp", null, array (
		'req_message' => false
	));*/
	shn_form_fsopen(_t("Current Location"));

	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();

	$extra_opts['camps'] = true;
	$extra_opts['org'] = true;
    $extra_opts['camp_id']=$_SESSION['dvr']['group']['camps'];
	$extra_opts['value'] = $_SESSION['dvr']['group']['current_loc'];
	shn_location($range, $_SESSION['dvr']['group']['current_loc'], null, $extra_opts);

	shn_form_fsclose();

	//shn_form_fsopen(_t("Location Information"));
	//echo _t("Plot the Camp/Shelter Location or Coordinates below");
	//shn_form_hidden(array (
	//	'seq' => 'chk'
	//));

	shn_form_fsclose();
	
	shn_form_submit(_t("Next"), "name=checklist_button");
	shn_form_fclose();
	print '<br />';

}

function shn_dvr_set_location_details() {

	$loc = shn_location_get_form_submit_loc();
    $_SESSION['dvr']['group']['camps']=$_POST['camps'];

	if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
		$_SESSION['dvr']['group']['gis_loc_x'] = $_POST['loc_x'];
		$_SESSION['dvr']['group']['gis_loc_y'] = $_POST['loc_y'];
	} else {
		$_POST['loc_x'] = $_POST['gps_x'];
		$_POST['loc_y'] = $_POST['gps_y'];
		$_SESSION['dvr']['group']['gis_loc_x'] = $_POST['loc_x'];
		$_SESSION['dvr']['group']['gis_loc_y'] = $_POST['loc_y'];
	}

//	$_SESSION['dvr']['group']['displaced_loc'] = '';

	$_SESSION['dvr']['group']['current_loc'] = $loc;

//	$location = _shn_org_location_string($_SESSION['dvr']['group']['dis_loc']);

		//	shn_dvr_set_location_details();
}

function shn_dvr_cklst_and_desc() {
	_shn_dvr_print_header(_t("Add New Group"));
	shn_form_fopen("add_new_grp", null, array (
		'req_message' => false
	));

	shn_form_fsopen(_t("Checklist"));

//write description for checklist
    print '<div class="info">';
	print _t("You are able to make requests for items/aid here. Select the checkbox(s) in front of the required item(s).");
	print '</div>';
	
	$extra_opts['help'] = _t("Please select items " .
	"tick the Check Box (Optional)");

	$extra_opts['selected'] = $_SESSION['dvr']['group']['opt_dvr_service'];

	shn_form_opt_checkbox(_t("opt_dvr_service"), $extra_opts);
	shn_form_fsclose();

	print '<br />';

	shn_form_fsopen(_t("Group Description"));

	$extra_opts['value'] = $_SESSION['dvr']['group']['other'];
	$extra_opts['help'] = _t("Enter the group description. (Optional)");
	shn_form_textarea(_t("Description"), 'desc', null, $extra_opts);
	
	shn_form_submit(_t("Finish"), 'name="end_button"');

	shn_form_fsclose();

	shn_form_fclose();
	print '<br />';

}

function _shn_dvr_set_checklist() {
	$dvr_service = $_POST['opt_dvr_service'];
	$_SESSION['dvr']['group']['opt_dvr_service'] = $dvr_service;
	$_SESSION['dvr']['group']['other'] = $_POST['desc'];

}

function _shn_dvr_regconfirm_group() {
	global $global;
	global $conf;
	$db = $global['db'];
?>
<h2><?php echo  _t('Confirm Group Details  Headed by ').$_SESSION['dvr']['group']['full_name']?></h2>
<div id="formcontainer">
<?php


	shn_form_fopen("add_new_grp", null,false);

	shn_form_fsopen(_t('Group type and head details'));

	$type = _shn_dvr_getoptiondescription($_SESSION['dvr']['group']['typ_of_grp']);

	shn_form_label(_t("Group type: "), $type);
	shn_form_label(_t("Full name"), $_SESSION['dvr']['group']['full_name']);
	shn_form_label(_t("Family name"), $_SESSION['dvr']['group']['family_name']);
	shn_form_label(_t("Local name"), $_SESSION['dvr']['group']['local_name']);
	shn_form_label(_t("NIC"), $_SESSION['dvr']['group']['nic']);
	shn_form_label(_t("Photograph"), $_SESSION['dvr']['group']['picture']);
?>
	<p align='center'>
	<?php

	shn_show_thumb_url($_SESSION['dvr_add_group']['entry']['p_uuid'], '', 'dvr', 'adddvr_img', true);
?>
	
	</p>
	<?php


	shn_form_label(_t("Mobile"), $_SESSION['dvr']['group']['mobile']);
	shn_form_label(_t("Telephone"), $_SESSION['dvr']['group']['telephone']);
	shn_form_label(_t("Email"), $_SESSION['dvr']['group']['email']);
	shn_form_label(_t("Address"), $_SESSION['dvr']['group']['address']);
	shn_form_fsclose();

	shn_form_fsopen(_t("Member Count"));
	shn_form_label(_t("Adult Males"), $_SESSION['dvr']['group']['adlt_mls']);
	shn_form_label(_t("Adult Females"), $_SESSION['dvr']['group']['adlt_fmls']);
	shn_form_label(_t("Children"), $_SESSION['dvr']['group']['chldrn']);
	shn_form_fsclose();

	shn_form_fsopen(_t("Status of Members in Group"));
	shn_form_label(_t("Displaced"), $_SESSION['dvr']['group']['dsplcd']);
	shn_form_label(_t("Missing"), $_SESSION['dvr']['group']['misng']);
	shn_form_label(_t("Dead"), $_SESSION['dvr']['group']['dead']);
	shn_form_label(_t("Rehabilitated"), $_SESSION['dvr']['group']['rehbd']);
	shn_form_fsclose();

	shn_form_fsopen(_t("Location"));
	$location = _shn_org_location_string($_SESSION['dvr']['group']['displaced_loc']);

	shn_form_label(_t("Displaced Location"), $location);
	$location = _shn_org_location_string($_SESSION['dvr']['group']['current_loc']);

	//$map_location = "Latitude= " . $_SESSION['dvr']['group']['gis_loc_y'] . " Longitude= " . $_SESSION['dvr']['group']['gis_loc_x'];

	shn_form_label(_t("Current Location"), $location);
	//shn_form_label(_t("Current Map Location"), $map_location);
	shn_form_fsclose();

	// Contact infomation
	shn_form_fsopen(_t("Checklist Information"));

	$checklist = _shn_dvr_getchecklist();

	$count = $_SESSION['elementcount'];

	$selected = array ();

	$selected = $_SESSION['dvr']['group']['opt_dvr_service'];

	for ($l = 0; $l < count($selected); $l++) {

		$opt = _shn_dvr_getoptiondescription($selected[$l]);

		shn_form_label(_t($opt), 'Required');
	}

	shn_form_label(_t('Other'), $_SESSION['dvr']['group']['other']);
	shn_form_fsclose();
?>
<br />
<center>
<?php


	//create the submit button
	$extra_opts['br'] = false;

	shn_form_submit(_t("Save"), 'name="save"');

	shn_form_submit(_t("Edit Details"), "name=edit_details");
	shn_form_hidden(array (
		'action' => '0'
	));
	// _shn_dvr_action_change_javascript("confirm_reg","action");
?>
</center>
<br />
<?php
	shn_form_fclose();
?>				     
</div>
<?php


	
}


function shn_dvr_mbr_confirm() {

	$msg = $_SESSION['dvr']['group']['name'] ._t(" group was succesfully registered");
	add_confirmation($msg);

}

function _shn_dvr_commit() {
	global $global;
	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
	_shn_dvr_add_group();
}

