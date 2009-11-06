<?php


/**
 *Major functions for add a new disaster victim
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera
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
include_once ($global['approot'] . '/inc/lib_ajax.inc');

//include_once ($global['approot'] . '/inc/handler_upload.inc');

function shn_dvr_add_new_individual($errors = false) {
    global $conf;
	if ($errors)
    display_errors();

	_shn_dvr_print_header(_t("Add New Individual"));

	shn_form_fopen("add_new_indv", null, array (
		'req_message' => true,
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'add_new_individual'
	));
	shn_form_fsopen(_t("Select Group"));
	print '<div class="info">';
	//print _t("Please select a Group that describes you well");

	print '<br />';

	print '</div>';
	print '<br />';

	//$typ_of_grp = array ();
	//clear all previous session variables
	//if($_SESSION['dvr']['person']['edit_individual_clicked']!=true)
	//unset($_SESSION['dvr']['person']);

	$extra_opts['help'] = _t("Please Select the group type");
	$extra_opts['req'] = true;
	$extra_opts['value'] = $_SESSION['dvr']['person']['typ_of_grp'];
	$extra_opts['sort'] = 'option_code';
//print 'installed'.$conf['acl_base'];
/*if($conf['acl_base']=='installed')

	shn_form_opt_select('opt_group_type', _t("Type of Group"), '', $extra_opts);
else
	shn_form_opt_select('opt_group_type', _t("Type of Group"), '', $extra_opts);
*/
	$type = $_POST['opt_group_type'];

	$heads = _shn_dvr_getgroupheadspertype($type);
//print 'fff'.count($heads);
//print 'gggg'.$heads[1];


	array_push($heads, 'Other');
	$extra_opts['help'] = _t("Type the first few letters and then select the name of the Head of the group");
	$extra_opts['req'] = true;
	//$extra_opts['value'] = $_SESSION['dvr']['person']['head_name'];
//	shn_form_select($heads, 'Select the group head', 'head name', '', $extra_opts);


//shn_ajax_initiate_request_famaily();
	//shn_ajax_add_suggest_family('family_name','familyHint','family_id');
	//shn_form_text(_t('Group head'),'family_name',"size=\"30\" autocomplete=off onkeyup=\"get_family(this.value,'familyHint','index.php?mod=dvr&act=get_family&stream=text')\"" ,$extra_opts);
	
	shn_ajax_text_look_up(array('Group head'),array('group_id'),array('familyHint'),'index.php?mod=dvr&act=get_family&stream=text',array($_SESSION['dvr']['person']['group_name']),true,$extra_opts);
	//echo '<div id="familyHint"></div>';
	if(isset( $_POST['group_id'])){
	    _shn_dvr_set_ajax_group_id();
	}
	if(isset($_SESSION['dvr']['person']['group_id'])){
	    _shn_dvr_set_ajax_group_id(true);
	}

//echo $_POST['family_id'];





//$heads=	$_POST['heads'];

//print   'head details r'.$heads;
	shn_form_fsclose();

	print '<br />';

	shn_form_fsopen(_t('Basic Details'));
	print '<br />';
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['full_name'];
	$extra_opts['help'] = _t("Enter your Full Name here(Required)");
	$extra_opts['req'] = true;
	shn_form_text(_t('Full Name'), 'full_name', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['family_name'];
	$extra_opts['help'] = _t("Family name, or the surname could be specified for matching of people with similar Family names");
	$extra_opts['req'] = false;
	shn_form_text(_t('Family Name'), 'family_nme', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['local_name'];
	$extra_opts['help'] = _t("You may also specify the local name, even in different script than English");
	shn_form_text(_t('Local Name'), 'local_name', 'size="30"', $extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['dob'];
	unset($extra_opts['help']);
	//$extra_opts['help'] = _t("You may also specify the date of birth");
    shn_form_date(_t("Date of Birth"),'dob',$extra_opts);
//	shn_form_text(_t('Date of Birth   (YYYY-MM-DD)'), 'dob', 'size=8', $extra_opts);
	$extra_opts['sort'] =false;
    $extra_opts['value'] = $_SESSION['dvr']['person']['opt_age_group'];
	$extra_opts['help'] = _t("You may also specify the age group");
	shn_form_opt_select("opt_age_group", _t('Age Group'), '',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_gender'];
    $extra_opts['help'] = _t("You can specify the gender");
	shn_form_opt_select("opt_gender", _t('Gender'), '',$extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_marital_status'];
    $extra_opts['help'] = _t("You can specify the marital status");
	shn_form_opt_select("opt_marital_status", _t('Marital Status'), '',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_religion'];
    $extra_opts['help'] = _t("You may also specify the religion");
	shn_form_opt_select("opt_religion", _t('Religion'), '',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_race'];
    $extra_opts['help'] = _t("You can also so specify the race");
	shn_form_opt_select("opt_race", _t('Race'), '',$extra_opts);
	
	shn_form_fsclose();
	print '<br />';

	shn_form_fsopen(_t('Identity'));
	print '<br />';
	$extra_opts['value'] = $_SESSION['dvr']['person']['idcard'];
	$extra_opts['help'] = 'Specify the Identity card Number, Although this is not required this will be useful in searching for the person';
	shn_form_text(_t('Identity Card Number'), 'idcard', 'size="30"',$extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['passport'];
	$extra_opts['help'] = 'Please Specify the passport number, Although this is not required this will be useful in searching for the person';
    shn_form_text(_t('Passport Number'), 'passport', 'size="30"',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['drv_licence'];
	$extra_opts['help'] = 'Please Specify the driving License number, Although this is not required this will be useful in searching for the person';
	shn_form_text(_t('Driving License'), 'drv_licence', 'size="30"',$extra_opts);

	shn_form_fsclose();
    
	print '<br />';
	shn_form_fsopen(_t('Upload Picture'));
	print '<br />';
	
	if ($_SESSION['dvr']['person']['edit_individual_clicked']==true) {
		shn_form_label(_t("Current Photograph"), $_SESSION['dvr']['person']['picture']);
?>
	<p align='center'>
	<?php
//shn_show_thumb_url($x_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null)
		shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addvictim_img');
?>
	
	</p> 
	<?php

	}

	
	shn_form_upload(_t('Upload Picture'), "picture");
	shn_form_fsclose();

	shn_form_fsopen(_t('Contact Information of the Disaster Victim'));
	print '<div class="info">';
	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['person']['address'];
	$extra_opts['help'] = 'Your address can be specified to contact you';

	shn_form_textarea(_t('Address'), "address", null, $extra_opts);

	/*$extra_opts['value'] = $_SESSION['dvr']['person']['zip'];
	$extra_opts['help'] = 'Specify a zip code, if it is available';

	shn_form_text(_t('Postal Code'), 'zip', 'size="15"', $extra_opts);*/

	$extra_opts['value'] = $_SESSION['dvr']['person']['telephone'];
	$extra_opts['help'] = 'Specify a phone, if it is available';

	shn_form_text(_t('Home Phone'), 'telephone', 'size="15"',$extra_opts);

	$extra_opts['value'] = $_SESSION['dvr']['person']['mobile'];
	$extra_opts['help'] = 'You may specify the displaced location of the victim';
	shn_form_text(_t('Mobile'), 'mobile', 'size="15"',$extra_opts);
	shn_form_fsclose();
	
	shn_form_fsopen(_t('Displaced Location of the Victim'));
	print '<br />';
	$typ_of_grp = array ();
	//array_push($typ_of_grp, '-- Select Option --');
	//array_reverse($typ_of_grp);

	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	$extra_opts['value'] = $_SESSION['dvr']['person']['displaced_location_type'];
	
    shn_form_select($typ_of_grp, _t("Displaced Location"), 'displaced_location_type', 'onchange="javascript:toggle(\'other\',this.value);"', $extra_opts);
	$range = shn_dvr_get_loc_range();

	//shn_location($range, $_SESSION['dvr']['person']['displaced_loc'], null, $extra_opts);
	$gr_id = $_SESSION['dvr']['person']['group_id'];
	//$w = _shn_dvr_get_groupdisplaced_location($gr_id);
	$extra_opts['value'] = $_SESSION['dvr']['person']['displaced_loc'];
	$w = $_SESSION['dvr']['person']['displaced_loc'];
    ?>
    <div id="other" 
    <?php 
    if(isset($_SESSION['dvr']['person']['displaced_location_type'])==false){
        echo 'style="display:none;"';
    }
    else{
      if($_SESSION['dvr']['person']['displaced_location_type']==2)
          echo 'style="display:block;"';
      else
          echo 'style="display:none;"';
    }
    ?>
    >
    <?php
    shn_location($range, $w, null, $extra_opts);

    ?>
    </div>
    <?php
	//	$loc = shn_location_get_form_submit_loc();
//	$_SESSION['dvr']['person']['displaced_loc'] = $loc;
//	$disloctype = $_POST['displacedlocationtypeof_group'];
//	
//	
//	$_SESSION['dvr']['person']['displacedlocationtypeof_group'] = $disloctype;

	shn_form_fsclose();
	
	
	shn_form_submit("Next", "name=location_individual");

	shn_form_fclose();
	print '<br />';

}

/**
 * get input
 *
 */

function shn_dvr_set_person_major_details() {
	global $global;
	if($_SESSION['dvr']['person']['edit_individual_clicked'] != true)
	$_SESSION['dvr']['person']['p_uuid'] = shn_create_uuid();
	//$_SESSION['dvr']['person']['typ_of_grp'] = $_POST['opt_group_type'];

	//print 'head name is' . $_POST['head_name'];
	$_SESSION['dvr']['person']['head_name'] = $_POST['family_name'];
	$_SESSION['dvr']['person']['head_id'] = $_POST['head_id'];
	
	
	//$group=_shn_dvr_get_group_id($_POST['head_name']);

	//$_SESSION['dvr']['person']['group_id'] = $_SESSION['dvr']['person']['head_name']; //group id 
	
	if(isset($_POST['group_id']) && '/'!=$_POST['group_id']){
	$_SESSION['dvr']['person']['group_id'] = $_POST['group_id']; //group id 
	}
	$_SESSION['dvr']['person']['group_name']=$_POST['textgroup_id'];
	$_SESSION['dvr']['person']['typ_of_grp'] = _shn_dvr_getgrouptype($_SESSION['dvr']['person']['group_id']);

	
	$_SESSION['dvr']['person']['full_name'] = $_POST['full_name'];
	$_SESSION['dvr']['person']['family_name'] = $_POST['family_nme'];
	$_SESSION['dvr']['person']['local_name'] = $_POST['local_name'];
	
	$_SESSION['dvr']['person']['dob'] = $_POST['dob'];
	$_SESSION['dvr']['person']['opt_age_group'] = $_POST['opt_age_group'];
	$_SESSION['dvr']['person']['opt_gender'] = $_POST['opt_gender'];
	$_SESSION['dvr']['person']['opt_marital_status'] = $_POST['opt_marital_status'];
	$_SESSION['dvr']['person']['opt_religion'] = $_POST['opt_religion'];
	$_SESSION['dvr']['person']['opt_race'] = $_POST['opt_race'];

	//to identity_to_person
	$_SESSION['dvr']['person']['idcard'] = $_POST['idcard'];
	$_SESSION['dvr']['person']['passport'] = $_POST['passport'];
	$_SESSION['dvr']['person']['drv_licence'] = $_POST['drv_licence'];

	//to contact
	$_SESSION['dvr']['person']['mobile'] = $_POST['mobile'];
	$_SESSION['dvr']['person']['telephone'] = $_POST['telephone'];
	$_SESSION['dvr']['person']['email'] = $_POST['email'];
	$_SESSION['dvr']['person']['address'] = $_POST['address'];
	
	$_SESSION['dvr']['person']['adlt_mls'] = $_POST['adlt_mls'];
	$_SESSION['dvr']['person']['adlt_fmls'] = $_POST['adlt_fmls'];
	$_SESSION['dvr']['person']['chldrn'] = $_POST['chldrn'];
	$_SESSION['dvr']['person']['dsplcd'] = $_POST['dsplcd'];
	$_SESSION['dvr']['person']['mising'] = $_POST['misng'];
	$_SESSION['dvr']['person']['dead'] = $_POST['dead'];
	$_SESSION['dvr']['person']['rehbd'] = $_POST['rehbd'];
	
	$disloctype = $_POST['displaced_location_type'];
	$_SESSION['dvr']['person']['displaced_location_type'] = $disloctype;
	//if as group selected
	if($disloctype==1)
	{ 
		//echo $disloctype.'no..........';
	   // echo $_SESSION['dvr']['person']['family_id'].'head...';
		$g_id = $_SESSION['dvr']['person']['group_id'];
		//echo $g_id.'gid...';
		$_SESSION['dvr']['person']['displaced_loc'] = _shn_dvr_get_groupdisplaced_location($g_id);
		//$_SESSION['dvr']['person']['displaced_loc'] = _shn_dvr_get_groupdisplaced_location($_SESSION['dvr']['person']['family_id']);
		//echo $_SESSION['dvr']['person']['displaced_loc'].'loca........';
	  //$_SESSION['dvr']['person']['displaced_loc'] = get_group_disloc();
		//same as group.get from  
	}
	   //if other loc selected,get it
	elseif($disloctype==2)
	{
			$loc = shn_location_get_form_submit_loc();
	        $_SESSION['dvr']['person']['displaced_loc'] = $loc;
//echo $loc.'loc';	
//echo $disloctype.'no';	        
	}

     $_SESSION['dvr']['person']['displacedlocationtypeof_group'] = $disloctype;

	if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {	
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type 
		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['picture']['tmp_name']);
			$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
			$_SESSION['dvr']['person']['person_image'] = $pic;
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

	//	print 'here' . $info;
		//check the image type 

		if (!$info) {
			add_error(_t("Invalid Image Type Please try again"));
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
    $head=$_POST['textgroup_id'];
    $gt = _shn_dvr_getgrouptype($_POST['group_id']);

	if (trim($head) == null | trim($head) == '') {
		add_error(_t("Please select the Group Head"));
		$error_flag = true;
	} elseif (trim($gt) == null | trim($gt) == '===') {
		add_error(_t("Please select the Group Head from the list."));
		$error_flag = true;
	}

	if (trim($full_name) == null | trim($full_name) == '') {
		add_error(_t("Please fill the full name"));
		$error_flag = true;
	}
//get_dvr_group_member_count($group_id)

    $email=$_POST['email'];
    if(!shn_valid_email($email,false))
    {
        add_error(_t("Invalid Email entered"));	
        $error_flag = true;
    }
	$dob=$_POST['dob'];
    $valid_date = true;	
    $dob_val = $_POST['dob'];	
    if(!shn_valid_date($dob_val))
    {
	//add_error(_t("Please Check the Date format"));	
        $error_flag = true;
        $valid_date = false;
    }


    if($valid_date){
		$dob_val = $_POST['dob'];
		$today_val = date('Y-m-d');

		$dob = strtotime($dob_val);
		$today = strtotime($today_val);
		if($today<=$dob){
			add_error(_t("Please enter a valid date of birth."));
			$error_flag = true;
		}
    }
	
	$pics = $_POST['picture'];

	if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);

		if (!$info) {
			add_error(_t("Invalid Image Type Please try again"));
			$error_flag = true;
		}
	}

	return $error_flag;

}


//add location dettails

function _shn_dvr_regconfirm_individual() {
	
    shn_dvr_set_person_physical_details();
	global $global;
	global $conf;
	$db = $global['db'];
?>
<h2><?php echo  _t('Confirm  Details of ').$_SESSION['dvr']['person']['full_name'] ?></h2>
<div id="formcontainer">
<?php


	shn_form_fopen("add_new_indv", null,false);

	shn_form_fsopen(_t('Group Type and Personal details'),false);
	shn_form_label(_t("Group type "), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['typ_of_grp']));
	//shn_form_label(_t("Group head"),$_SESSION['dvr']['person']['head_name']);
//	print 'date of birth is'.$_SESSION['dvr']['person']['family_id'];
	shn_form_label(_t("Full name"), $_SESSION['dvr']['person']['full_name']);
	shn_form_label(_t("Family name"), $_SESSION['dvr']['person']['family_name']);
	shn_form_label(_t("Local name"), $_SESSION['dvr']['person']['local_name']);

	shn_form_label(_t("Current Photograph"), $_SESSION['dvr']['person']['picture']);
?>
	<p align='center'>
	<?php

	shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addvictim_img', true);
?>
	
	</p>
	<?php


	shn_form_label(_t("Date Of birth"), $_SESSION['dvr']['person']['dob']);
	shn_form_label(_t("Age group"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_age_group']));
	shn_form_label(_t("Gender"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_gender']));
	shn_form_label(_t("Marital Status"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_marital_status']));
	shn_form_label(_t("Religion"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_religion']));
	shn_form_label(_t("Race"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_race']));
	shn_form_fsclose();
	shn_form_fsopen(_t("Identity"));
	shn_form_label(_t("Identity Card Number"), $_SESSION['dvr']['person']['idcard']);
	shn_form_label(_t("Passport Number"), $_SESSION['dvr']['person']['passport']);
	shn_form_label(_t("Driving License"), $_SESSION['dvr']['person']['drv_licence']);

	shn_form_fsclose();

	shn_form_fsopen(_t("Contact Information"));
	shn_form_label(_t("Address"), $_SESSION['dvr']['person']['address']);
	//shn_form_label(_t("Postal Code"), $_SESSION['dvr']['person']['postal_code']);
	shn_form_label(_t("Home Phone"), $_SESSION['dvr']['person']['telephone']);
	shn_form_label(_t("Mobile"), $_SESSION['dvr']['person']['mobile']);
	shn_form_fsclose();
	

	shn_form_fsopen(_t("Displaced/Current Location"));
	$location = _shn_org_location_string($_SESSION['dvr']['person']['displaced_loc']);
    shn_form_label(_t("Displaced Location"), $location);
	
    $location = _shn_org_location_string($_SESSION['dvr']['person']['current_loc']);
	$map_location = "Latitude= " . $_SESSION['dvr']['person']['gis_loc_x'] . " Longitude= " . $_SESSION['dvr']['person']['gis_loc_y'];
	shn_form_label(_t("Current Location"), $location);
	//shn_form_label(_t("Map Location"), $map_location);
	shn_form_fsclose();

	// Contact infomation
	shn_form_fsopen(_t("Physical Information"));

	shn_form_label(_t("Current Fingerprint"), $_SESSION['dvr']['person']['finger_picture']);
?>
	<p align='center'>
	<?php

	shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addfingerprint_img', true,"finger");
?>
	
	</p>
	<?php


	shn_form_label(_t("Eye Color"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_eye_color'],'opt_eye_color'));
	shn_form_label(_t("Skin Color"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_skin_color'],'opt_skin_color'));
	shn_form_label(_t("Hair Color"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_hair_color'],'opt_hair_color'));
	shn_form_label(_t("Height"), $_SESSION['dvr']['person']['height']);
	shn_form_label(_t("Weight"), $_SESSION['dvr']['person']['weight']);
	shn_form_label(_t("Blood Type"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_blood_type']));
	shn_form_label(_t("Clothing and appearence"), $_SESSION['dvr']['person']['last_clothing']);
	shn_form_label(_t("Other Details"), $_SESSION['dvr']['person']['comments']);

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


	//close the form
	shn_form_fclose();
?>				     
</div>
<?php


}



/**
 * confirm input that is given by the user
 *
 */
function shn_dvr_person_confirm() {

	$msg = $_SESSION['dvr']['person']['full_name'] . " was succesfully registered ";
	add_confirmation($msg);
}

function shn_dvr_disp_and_crnt_loc() {
	_shn_dvr_print_header(_t("Add New Individual"));
	global $global;
	global $conf;
	shn_form_fopen("add_new_indv", null, array ('enctype' => 'enctype="multipart/form-data"'));
	shn_form_hidden(array ('seq' => 'entry'));
/*	shn_form_fsopen(_t('Displaced Location Of The Victim'));
	print '<br />';
	$typ_of_grp = array ();
	//array_push($typ_of_grp, '-- Select Option --');
	array_reverse($typ_of_grp);

	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	$extra_opts['value'] = $_SESSION['dvr']['person']['displacedlocationtypeof_group'];

	shn_form_select($typ_of_grp, _t("Displaced Location"), 'displacedlocationtypeof_group', '', $extra_opts);

	$range = shn_dvr_get_loc_range();

	shn_location($range, null, null, $extra_opts);

	shn_form_fsclose();*/
	
	

	shn_form_fsclose();
	
	
	shn_form_fsopen(_t('Current Location of the Victim'));

	print '<br />';
	$typ_of_grp1 = array ();
	//array_push($typ_of_grp1, '-- Select Option --');
	//array_reverse($typ_of_grp1,true);
	$typ_of_grp1[1] = "Same As Group";
	$typ_of_grp1[2] = "Other";
	$extra_opts['value'] = $_SESSION['dvr']['person']['current_location_type'];
	shn_form_select($typ_of_grp1, _t("Current Location"), 'current_location_type', 'onchange="javascript:toggle(\'curr_other\',this.value);"', $extra_opts);
	
	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();

    $extra_opts["camps"]=true;
    $extra_opts["org"]=true;
    //$extra_opts["camp_id"]=$_SESSION['dvr']['person']['camps'];
	
	//shn_location($range, $_POST[$range["end"]], $parent, $extra_opts);
    ?>
    <div id="curr_other" 
    <?php 
    if(isset($_SESSION['dvr']['person']['current_location_type'])==false){
        echo 'style="display:none;"';
    }
    else{
      if($_SESSION['dvr']['person']['current_location_type']==2)
          echo 'style="display:block;"';
      else
          echo 'style="display:none;"';
    }
    ?>
    >
    <?php
    shn_location($range, $_SESSION['dvr']['person']['current_loc'], null, $extra_opts);

    ?>
    </div>	
    <?php

//$cur_loc = shn_location_get_form_submit_loc();
//$_SESSION['dvr']['person']['displaced_loc'] = $cur_loc;


	shn_form_fsclose();
////////////////////////////////////////////////////////////////////////////////
//	shn_form_fsopen(_t("Location Information"));
//	echo _t("Plot the Camp/Shelter Location or Coordinates below");
//	shn_form_hidden(array (
//		'seq' => 'chk'
//	));
//	shn_form_fsclose();
/////////////////////////////////////////////////////////////////////////////////////

	shn_form_fsclose();
	shn_form_submit(_t("Next"), "name=physical_button");
	shn_form_fclose();
	print '<br />';

	//shn_dvr_crnt_loc_vic();

}

function shn_dvr_set_person_physical_details() {
	
    global $global;
	
    //to person_physical
    $_SESSION['dvr']['person']['opt_eye_color'] = $_POST['opt_eye_color'];
	$_SESSION['dvr']['person']['opt_skin_color'] = $_POST['opt_skin_color'];
	$_SESSION['dvr']['person']['opt_hair_color'] = $_POST['opt_hair_color'];
	$_SESSION['dvr']['person']['height'] = $_POST['height'];
	$_SESSION['dvr']['person']['weight'] = $_POST['weight'];
	$_SESSION['dvr']['person']['opt_blood_type'] = $_POST['opt_blood_type'];
	$_SESSION['dvr']['person']['last_clothing'] = $_POST['last_clothing'];
	$_SESSION['dvr']['person']['comments'] = $_POST['comments'];
	
	
	$_SESSION['dvr']['person']['finger_picture'] = $_POST['finger_picture'];

	//print 'here';
	if ($_FILES['finger_picture']['error'] != UPLOAD_ERR_NO_FILE) {	
		$info = getimagesize($_FILES['finger_picture']['tmp_name']);
	//print 'in';
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

		$ext = '.' . $ext;
		$upload_dir = $global['approot'] . 'www/tmp/';
		$uploadfile = $upload_dir . 'ori_fin' . $_SESSION['dvr']['person']['p_uuid'] . $ext;
		move_uploaded_file($_FILES['finger_picture']['tmp_name'], $uploadfile);
		
		$desc_path = $upload_dir . 'thumb_fin' . $_SESSION['dvr']['person']['p_uuid'] . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);

	}

}

function shn_dvr_set_person_location_details() {
	$curloctype = $_POST['current_location_type'];

	$_SESSION['dvr']['person']['current_location_type'] = $curloctype;
	
	if($curloctype==2)
	{$loc = shn_location_get_form_submit_loc();
	$_SESSION['dvr']['person']['current_loc'] = $loc;}
	else
	{//echo $disloctype.'no..........';
	   // echo $_SESSION['dvr']['person']['family_id'].'head...';
		$g_id = $_SESSION['dvr']['person']['group_id'];
		//echo $g_id.'gid...';
		$_SESSION['dvr']['person']['current_loc'] = _shn_dvr_get_groupcurrent_location($g_id);
		//$_SESSION['dvr']['person']['displaced_loc'] = _shn_dvr_get_groupdisplaced_location($_SESSION['dvr']['person']['family_id']);
		//echo $_SESSION['dvr']['person']['current_loc'].'loca........';
		}
//echo $loc;
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
	
	
//$camps =$_POST['camps'];
//print 'camp is'.$camps;
    $_SESSION['dvr']['person']['camps']=$_POST['camps'];
//$_SESSION['dvr']['person']['shelter_id']=$camps;
	//$location=_shn_org_location_string($_SESSION['dvr']['group']['dis_loc']);

	//$disloctype = $_POST['displacedlocationtypeof_group'];
	
	//$_SESSION['dvr']['person']['displacedlocationtypeof_group'] = $disloctype;

}


function shn_dvr_physical_information($errors = false) {

	if ($errors)
		display_errors();

	shn_form_fopen("add_new_indv", null, array (
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'chk'
	));

	shn_form_fsopen(_t('Upload FingerPrint'));
	print '<br />';
	
	if ($_SESSION['dvr']['person']['edit_individual_clicked']==true) {
		shn_form_label(_t("Current Fingerprint"), $_SESSION['dvr']['person']['finger_picture']);
?>
	<p align='center'>
	<?php
//shn_show_thumb_url($x_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null)
		shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], '', 'dvr', 'addfingerprint_img', false,"finger");
?>
	
	</p>
	<?php

	}

	$_SESSION['dvr']['person']['edit_individual_clicked']=false;
	shn_form_upload(_t('Upload Fingerprint'), "finger_picture");
	shn_form_fsclose();
	print '<br />';

	shn_form_fsopen(_t('Physical Details'));
	print '<br />';
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_eye_color'] ;
	shn_form_opt_select("opt_eye_color", _t('Eye Colour'),'',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_skin_color']; 
	shn_form_opt_select("opt_skin_color", _t('Skin Colour'),'',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_hair_color']; 
	shn_form_opt_select("opt_hair_color", _t('Hair Colour'),'',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['height'];
	shn_form_text(_t('Height'), 'height', 'size="10"',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['weight'];
	shn_form_text(_t('Weight'), 'weight', 'size="10"',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['opt_blood_type'] ;
	shn_form_opt_select("opt_blood_type", _t('Blood Type'),'',$extra_opts);
	//shn_form_textarea(_t('Other Distinctive Features'), 'physical_comments');
	shn_form_fsclose();
	shn_form_fsopen(_t('Other Details'));
	print '<br />';

	$extra_opts['value'] = $_SESSION['dvr']['person']['last_clothing'];
	shn_form_textarea(_t('Description Of Clothing And Appearance'), 'last_clothing','',$extra_opts);
	
	$extra_opts['value'] = $_SESSION['dvr']['person']['comments'];
	shn_form_textarea(_t('Other Relevant Information'), 'comments','',$extra_opts);
	shn_form_fsclose();
	shn_form_submit(_t('Finish'), "name=finish");
	shn_form_fclose();
	print '<br />';

}

function _shn_dvr_add_individual_todb() {
	global $global;

	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
	_shn_dvr_commit_individual();
}

function get_group_disloc()
{
	//_shn_dvr_get_group_id();
	$q1 = "SELECT g_uuid FROM group_details WHERE head_uuid =''";
	$resu = handler($q1);
	
	
	$tag = $resu.'-disp';
	$q2 = "SELECT location_id FROM location_details loc WHERE loc.poc_uuid='$tag'";
	$resul = handler($q2);
	
}


function _shn_dvr_set_ajax_group_id($session = false){
    
    if(!$session){
	?>
	<script>
		    document.getElementById('group_id').value='<?php echo $_POST['group_id'];?>';
	</script>
    <?php
    }else{
        ?>
    	<script>
		    document.getElementById('group_id').value='<?php echo $_SESSION['dvr']['person']['group_id'];?>';
		</script>
    	<?php
    }
}
?>



<script language="javascript">

function toggle(divition,values)
{

var othe = document.getElementById(divition);

	if ( values == "2" ) {
		
		othe.style.display = 'block';
	}
	
	else{
	othe.style.display = 'none';
	}
}

</script>
<?php
