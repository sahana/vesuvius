<?php
/**
 * Add Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Janaka Wickramasinghe <janaka@opensource.lk>
 * 
 * @copyright	Lanka Software Foundation - http://www.opensource.lk
 * @package	module
 * @subpackage	mpr
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 * Revised 1/23/2010 c.cornwell, NLM-CEB, Merged additional include of lib_uuid.inc in _addmp_commit from haitirelief branch.
 */

include_once($global['approot']."/inc/lib_uuid.inc");
include_once($global['approot']."/inc/lib_location.inc");


/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post 
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post) {
	//trim them all
	foreach($_POST as $k => $v) {
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}
}



/**
 * This is the Add Entry Form
 * @param mixed $errors 
 * @access public
 * @return void
 */
function shn_mpr_addmp_entry($errors=false) {
	global $global;
	global $conf;
	//if($errors)
	//display_errors();

	shn_form_fopen("addmp",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
	if (shn_db_get_config("mpr", "show_warning")) {
		add_warning(_t('Please do a search and check whether the person has already been added.'));
	}
	
	if($_GET['type']=='found'){
		shn_form_fsopen(_t('Status'));
		$q="select * from field_options where field_name='opt_status'";
		$res = $global['db']->Execute($q);
		$opt_status = array();
		while (!$res->EOF) {
			if($res->fields['option_code'] != 'mis')
			$opt_status[$res->fields['option_code']] = $res->fields['option_description'];
			$res->MoveNext();
		}
		shn_form_select($opt_status,_t('Status'),'opt_status');
		shn_form_fsclose();
	} elseif($_GET['type']=='missing') {
		shn_form_hidden(array('opt_status'=>'mis'));
	}
	shn_form_hidden(array('seq'=>'entry'));
	
	shn_form_fsopen(_t('Information Privacy'));
		?><p><?php echo _t("<span class=\"publicText\">Public</span> information that, if you provide, you agree can be exposed to the general public. <span class=\"privateText\">Private</span> information in this report will not be generally released.  It may be shared with other family members and friends you designate, emergency responders, medical providers, clergy/councilors, law enforcement, and authorized displaced-person agencies."); ?></p><?php
	shn_form_fsclose();

	shn_form_fsopen(_t('Identity'));
		?><p><?php //echo  _t('If you have any information about missing person\'s identity numbers, please include them since it will be helpful for finding the person. Otherwise please ignore.'); ?></p><?php
		shn_form_text(_t('Social Security Number'),'idcard','size="30"', array('private'=>true, 'help'=>'Enter the 9 digit number, as a single number of the form 123-45-6789'));
		shn_form_text(_t('Passport Number'),'passport','size="30"', array('private'=>true));
		shn_form_text(_t('Driver\'s License Number'),'drv_license','size="30"', array('private'=>true));
	shn_form_fsclose();

	shn_form_fsopen(_t('Basic Details'));
		?><p><?php echo  _t('Please enter any of the following details of the person:'); ?></p>	<?php
		shn_form_text(_t('Full Name '),'full_name','size="30"',array('req'=>true, 'help'=>'Examples: First Middle Last, First M. Last, First M. I. Last, First Mid1 Mid2 Last, First Mid Last1 Last 2, First “Nickname” Last. This field is required because it is the main field that will be used during searches to locate a person.', 'public'=>true));
		shn_form_text(_t('Family Name'),'family_name','size="30"', array('help'=>_t('Also known as the surname.  Typically the last name or the first.'), 'private'=>true));
		shn_form_text(_t('Local Name'),'local_name','size="30"', array('help'=>_t('Nickname, alias, or (if the computer allows) full name in a non-Roman alphabet.'), 'private'=>true));
		shn_form_date(_t("Date of Birth"),'dob', array('public'=>true, 'help'=>'Please enter a date in the form YYYY-MM-DD'));
		shn_form_opt_select("opt_age_group",_t('Age'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'public'=>true, 'help'=>'If date of birth is unknown, enter an estimated age.'));
		shn_form_opt_select("opt_gender",_t('Gender'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'public'=>true));
		shn_form_opt_select("opt_marital_status",_t('Marital Status'),null,array('sort'=>'display_order, option_description ASC', 'select'=>'true', 'public'=>true));
		shn_form_opt_select("opt_religion",_t('Religion'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'private'=>true));
		shn_form_opt_select("opt_race",_t('Race'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'private'=>true, 'help'=>'The Race choices are those defined by the US Government, e.g., the FBI when reporting missing people.'));
	shn_form_fsclose();

	shn_form_fsopen(_t('Upload Picture'));
		?><p><?php echo  _t('Select a photo that clearly shows the person’s face, and possibly suggests their build.  Ideally, show only one person in the photo; otherwise, tell us which person is the one missing in the “Other information that would help us to find this person” field below.'); ?></p><?php
		shn_form_upload(_t('Upload Picture'), "picture", array('public'=>true, 'help'=> _t('If the photo you intend to use comes from another web site (e.g., photo sharing, web email), you will often need to first make a temporary local copy of it to your local machine, which can then be uploaded to Sahana. Similarly, getting it directly from a USB flash drive, USB transfer cable from your camera, or memory stick (e.g., SD card from your camera or cell phone).')));
	shn_form_fsclose();

	shn_form_fsopen(_t('Missing Person\'s Contact Information'));
		shn_form_textarea(_t('Address'),"address", null, array('cols'=>48, 'help' => _t('Your address can be specified to contact you'), 'private'=>true));
		shn_form_text(_t('Zip/Postal Code'),'zip', 'size="15"', array('private'=>true));
		shn_form_text(_t('Home Phone Number'),'phone', 'size="15"', array('private'=>true));
		shn_form_text(_t('Cell/Mobile Phone Number'),'mobile', 'size="15"', array('private'=>true));
	shn_form_fsclose();

	shn_form_fsopen(_t('Location where the person most likely encountered the disaster <span class="publicText">Public</span>'));
		?><p><?php echo _t("Choose 'County or Equivalent' first, this will auto-populate the second field 'Town or Neighborhood'. Next, choose a 'Town or Neighborhood' from the list.  A 'county equivalent' varies by state, but is typically a city."); ?></p><?php
		shn_location_mpr();
	shn_form_fsclose();

	shn_form_fsopen(_t('Physical Details'));
		shn_form_opt_select("opt_eye_color",_t('Eye Color'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'public'=>true, 'help'=>'The choices for Skin Color are those used by governmental agencies and law enforcement when reporting missing people.  These are frequently-used descriptive words, rather than precise colors.  Adjectives like “light” and “dark” may be considered in conjunction with the choices for “Race” and “Ethnicity” fields above.'));
		shn_form_opt_select("opt_skin_color",_t('Skin Color'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'public'=>true));
		shn_form_opt_select("opt_hair_color",_t('Hair Color'),null,array('sort'=>'display_order, option_description ASC','select'=>'true', 'public'=>true));
		
		// added the usage of different units here and in the general configuration of the module ~ gmiernicki
		if (shn_db_get_config("mpr", "use_english_metrics")) {
			shn_form_text(_t("Height (<i>in feet/inches</i>)"),'height','size="10"',array('public'=>true, 'help'=>'Enter value to the nearest ½ inch.  Examples: 5\' 3 1/2", 60.5", 59"'));
			shn_form_text(_t('Weight (<i>in pounds</i>)'),'weight','size="10"',array('public'=>true, 'help'=>'Enter value to the nearest pound.'));
		} else {
			shn_form_text(_t('Height (<i>in centimeters</i>)'),'height','size="10"',array('public'=>true, 'help'=>'Enter the value to the nearest centimeter.'));
			shn_form_text(_t('Weight (<i>in kilograms</i>)'),'weight','size="10"',array('public'=>true, 'help'=>'Enter the value to the nearest kilogram.'));
		}
				
		shn_form_textarea(_t('Other Obvious Distinctive Features'),'physical_comments', null, array('cols'=>48, 'public'=>true));
	shn_form_fsclose();
	
	shn_form_fsopen(_t('Other Details'));
		shn_form_opt_select("opt_blood_type",_t('Blood Type'),null,array('private'=>true, 'sort'=>'display_order, option_description ASC','select'=>'true'));
		shn_form_textarea(_t('Last Seen Location'),'last_seen', null, array('cols'=>48, 'public'=>true));
		shn_form_textarea(_t('Clothing and Appearance when Last Seen'),'last_clothing', null, array('cols'=>48, 'public'=>true));
		shn_form_textarea(_t('Other Information to Help Locate this Person'),'comments', null, array('cols'=>48, 'public'=>true));
	shn_form_fsclose();

	shn_form_submit(_t('Next'));
	shn_form_fclose();
}



/**
 * This is the Add Entry Validation function
 * @access public
 * @return void
 */
function shn_mpr_addmp_validate() {
	global $global;
	global $conf;

	$error_flag=false;
	
	//clean the post
	shn_tools_clean_post(&$local_post);
	
	$_SESSION['mpr_add']['entry']=$local_post;
	if(! isset($_SESSION['mpr_add']['entry']['p_uuid'])) {
		$_SESSION['mpr_add']['entry']['p_uuid'] = shn_create_uuid();
	}
	$dob=$_POST['dob'];
		
	if(!shn_valid_dob($dob,false,'/^\d{4}-\d{2}-\d{2}$/','Date of birth')) {
		//add_error(_t("Please Check the Date format"));	
		$error_flag = true;
	}	
	if(isset($_POST['height']) && $_POST['height']!=null) {
		$height = $_POST['height'];
		if(is_numeric($height)==false) {
			add_error(_t("Height should be a value in centimeters(cm)"));
			$error_flag = true;
		}
	}

	//anything entered?
	if(empty($local_post)) {
		add_error(_t("You have not completed the form"));
		return false;
	}
	
	//fullname is entered?
	if(! isset($local_post['full_name'])) {
		add_error(_t("Please enter the full name of the missing person"));
		$error_flag=true;
	}

	//Picture upload part
	//No file was uploaded ignore else do the following
	if($_FILES['picture']['error']==0 || $_FILES['picture']['error'] == UPLOAD_ERR_NO_FILE) {
		//if($_FILES['picture']['error']!=UPLOAD_ERR_NO_FILE){
		if($_FILES['picture']['tmp_name']!=''){
			// upload ok
			$info = getimagesize($_FILES['picture']['tmp_name']);
			//check the image type
			if (! $info) {
				add_error(_t("Invalid image type please try again"));
				$error_flag=true;
			}
			list($ignore,$ext) = split("\/",$info['mime']);

			//check for save handler
			if($conf['mod_mpr_upload_pic_handler'] == 'database') {
				$size = filesize($_FILES['picture']['tmp_name']);
				$pic = fread(fopen($_FILES['picture']['tmp_name'],"r"),$size);
				$_SESSION['mpr']['entry']['image'] = $pic;
				$_SESSION['mpr']['entry']['image_type'] = $ext;
				$_SESSION['mpr']['entry']['image_height'] = $info[1];
				$_SESSION['mpr']['entry']['image_width'] = $info[0];
			}

			//putting a dot ;-) 
			$ext = '.'.$ext;
			$upload_dir = $global['approot'].'www/tmp/';
			$uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_add']['entry']['p_uuid'].$ext;
			move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
			$desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_add']['entry']['p_uuid'].$ext; 
			//make thumb 100X100 or some thing like that ;-)
			shn_image_resize($uploadfile,$desc_path,100,100);
		}
	} else {
		add_error(shn_file_upload_error_msg($_FILES['picture']['error']));
		$error_flag = true;
	}   
	if($error_flag) {
		return false;
	} else {
		//set session
		return true;
	}
} 



/**
 * This is the reproter entry form 
 * @param mixed $errors 
 * @access public
 * @return void
 */
function shn_mpr_addmp_reporter($errors=false) {
	if($errors) {
		display_errors();
	}
	shn_js_toggle_layer();
	// todo: Clean the $_GET['act'] baby ;-)
	shn_form_fopen($_GET['act'],null);
	?><p><?php echo  _t('We are collecting the information on the person who is reporting the missing person due to the following reasons.'). 
		'<ul><li>'.
		_t('To inform back on finding the missing person').'</li><li>'.
		_t('In a situation where the person who is reporting also a victim of the disaster. The details given here would help to associate he/she with his/her relatives.')
		.'</li></ul>'; ?></p><?php

	shn_form_hidden(array('seq'=>'report_person'));
	shn_form_fsopen(_t('Details on Person who is reporting on missing person'));
		shn_form_fsopen(_t('Reported Before'));
			shn_form_select(array("yes"=>_t('Yes'),"no"=>_t('No')),	_t('Have you reported anyone? '),"reported_before",'onchange="javascript:toggleLayer(\'reporter_victim\',\'reporter_details\');"');

			?><div id="reporter_victim" <?php
				if(isset($_POST['reported_before'])) {
					if($_POST['reported_before']=='yes') {
						echo 'style="display:none;"';
					} else {
						echo 'style="display:block;"';
					}   
				} else {
					echo 'style="display:none;"';
				}   
				?>  
			>
			<?php 
			shn_form_select(array("yes"=>_t('Yes'),"no"=>_t('No')), _t('Are you a disaster victim too? '), "is_dv", 'onchange="javascript:toggle(\'isvictim\',this.value);"');
			?>
			<div id="isvictim"
			<?php
				if(isset($_POST['is_dv'])){
					if($_POST['is_dv']=='no'){
					echo 'style="display:none;"';
					}else{
					echo 'style="display:block;"';
					}   
				} else {
					echo 'style="display:block;"';
				}
			?>
			>
			<?php
			shn_form_opt_select('opt_status',_t('If you are a victim, Please specify the status'),'',array('value'=>$_SESSION['mpr_reporter']['opt_status']));
			?>
			</div>
			</div>
			<?php
		shn_form_fsclose();

		shn_form_fsopen(_t('Details of the reporting person'));
			?>
			<p><?php echo  _t('NOTE : If you have reported before, we will use the following information to perform a search to see you are in our database or not.'); ?></p><?php
			shn_form_text(_t('Name'),'rep_full_name','size="30"',array('req'=>true));
			shn_form_text('Relationship to Person','opt_relationship_type');
			//  shn_form_text(_t('Relation'),'rep_relation','size="30"',array('req'=>true));
			?>
			<div id="reporter_details" 
			<?php
				if(isset($_POST['reported_before'])) {
					if($_POST['reported_before']=='yes') {
						echo 'style="display:none;"';
					} else {
						echo 'style="display:block;"';
					}
				} else {
					echo 'style="display:none;"';
				}
			?>	
			>
			<p><?php echo  _t('IMPORTANT : At least one of the following contact method is required'); ?></p><?php
			shn_form_textarea(_t('Address'),'rep_address');
			shn_form_text(_t('Phone'),'rep_phone','size="30"');
			shn_form_text(_t('Email'),'rep_email','size="30"');
			?></div><?php
		shn_form_fsclose();
	shn_form_fsclose();
	shn_form_submit(_t('Next'));
	shn_form_fclose();
}



/**
 * This is the reporter entry validation
 * @access public
 * @return void
 */
function shn_mpr_addmp_reporter_validate() {
	$error_flag=false;
	
	//clean the post
	shn_tools_clean_post(&$local_post);

	//tmp fix
	if(empty($local_post)){
		//add_error(_t("You have not completed the form"));
		return false;
	}

	//Reporting person name
	if(! isset($local_post['rep_full_name'])){
		add_error(_t("Please enter the full name of the reporting person"));
		$error_flag=true;
	}

	$email=$local_post['rep_email'];
	if($email!=null) {
		if(!shn_valid_email($email)) {
			add_error(_t("Please enter a valid E-mail"));
			$error_flag=true;
		}
	}

	//Reporting person relation
	/* if(! isset($local_post['opt_relationship_type'])){
		add_error(_t("Please enter the relationship of the reporting person"));
		$error_flag=true;
	}*/

	//Reporting person contact
	if (!( isset($local_post['rep_address']) || isset($local_post['rep_phone']) || isset($local_post['rep_email']) ) ) {
		if ( $_POST['reported_before'] != 'yes' ) {
			add_error(_t("Please enter any contact method of the reporting person"));
			$error_flag=true;
		}
	}
	
	if ($error_flag) {
		return false;
	} else {
		//set session
		$_SESSION['mpr_add']['report_person']=$local_post;
		return true;
	}
}



/**
 * This is the image upload form
 * @param mixed $errors 
 * @access public
 * @return void
 */
function shn_mpr_addmp_upload($errors=false) {
	if($errors) {
		display_errors();
	}
	shn_form_fopen("addmp",null,array('enctype'=>'enctype="multipart/form-data"'));
	?><p><?php echo  _t('If you have a picture of the missing person, please upload the picture. So, that it will be easy for us to identify the person. <br />If you don\'t have a picture to upload just click the "Next" button.'); ?></p><?php
	shn_form_hidden(array('seq'=>'upload_pic'));
	shn_form_fsopen(_t('Upload Picture'));
		shn_form_upload(_t('Upload Picture'),"picture");
		shn_form_fsclose();
		shn_form_submit(_t('Next'));
	shn_form_fclose();
}



/**
 * This checks for the uploaded picture and make the thumbnail.
 * @access public
 * @return void
 */
function shn_mpr_addmp_upload_pic() {
	global $global;
	global $conf;

	//No file was uploaded ignore
	if($_FILES['picture']['error']==UPLOAD_ERR_NO_FILE) {
		return true;
	}

	//Uploads 
	$info = getimagesize($_FILES['picture']['tmp_name']);
	//check the image type 
	if (!$info) {
		add_error(_t("Invalid image type please try again"));
		return false;    
	}

	list($ignore,$ext) = split("\/",$info['mime']);
	//print 'save handler is'.$conf['mod_mpr']['upload_picture']['savehandler'];

	//check for save handler
	if ($conf['mod_mpr_upload_pic_handler'] == 'database') {
		$size = filesize($_FILES['picture']['tmp_name']);
		$pic = fread(fopen($_FILES['picture']['tmp_name'],"r"),$size);
		$_SESSION['mpr']['entry']['image'] = $pic;
		$_SESSION['mpr']['entry']['image_type'] = $ext;
		$_SESSION['mpr']['entry']['image_height'] = $info[1];
		$_SESSION['mpr']['entry']['image_width'] = $info[0];
		return true;
	}

	//putting a dot ;-) 
	$ext = '.'.$ext;
	$upload_dir = $global['approot'].'www/tmp/';
	$uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_add']['entry']['p_uuid'].$ext;
	move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
	$desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_add']['entry']['p_uuid'].$ext; 

	//make thumb 100X100 or some thing like that ;-)
	shn_image_resize($uploadfile,$desc_path,100,100);
	return true;
}



/**
 * This is the confirmation function.
 * @access public
 * @return void
 */
function shn_mpr_addmp_confirm() {
	global $global;
	global $conf;

	//shn_form_fopen("addmp",null,array('req_message'=>false));
	shn_form_fopen("end_flow",null,array('req_message'=>false));
		shn_form_fsopen(_t('Missing Person'));
		shn_form_hidden(array('seq'=>'commit'));
		shn_show_thumb_url($_SESSION['mpr_add']['entry']['p_uuid'],'database', 'mpr', 'addmp_img',true);
		?><hr><?php
		//Identity
		if (isset($_SESSION['mpr_add']['entry']['idcard']) || isset($_SESSION['mpr_add']['entry']['passport']) || isset($_SESSION['mpr_add']['entry']['drv_license']) ) {
			shn_form_fsopen(_t('Identity'));
			$identity_section = true;
		}
		if(isset($_SESSION['mpr_add']['entry']['idcard'])) {
			shn_form_label(_t('Identity Card Number'),$_SESSION['mpr_add']['entry']['idcard']);
		}
		if(isset($_SESSION['mpr_add']['entry']['passport'])) {
			shn_form_label(_t('Passport Number'),$_SESSION['mpr_add']['entry']['passport']);
		}
		if(isset($_SESSION['mpr_add']['entry']['drv_license'])) {
			shn_form_label(_t('Driving License'),$_SESSION['mpr_add']['entry']['drv_license']); 
		}
		if($identity_section) {
			shn_form_fsclose();
		}

		//Basic Details
		if (isset($_SESSION['mpr_add']['entry']['full_name']) || isset($_SESSION['mpr_add']['entry']['family_name']) || isset($_SESSION['mpr_add']['entry']['local_name']) 
			|| isset($_SESSION['mpr_add']['entry']['dob']) || isset($_SESSION['mpr_add']['entry']['opt_age_group']) || isset($_SESSION['mpr_add']['entry']['opt_gender']) 
			|| isset($_SESSION['mpr_add']['entry']['opt_marital_status']) || isset($_SESSION['mpr_add']['entry']['opt_religion']) || isset($_SESSION['mpr_add']['entry']['opt_race']) ) {
			shn_form_fsopen(_t('Basic Details'));
			$basic_section = true;
		}
		if (isset($_SESSION['mpr_add']['entry']['full_name'])) {
			shn_form_label(_t('Full Name'),$_SESSION['mpr_add']['entry']['full_name']);
		}
		if (isset($_SESSION['mpr_add']['entry']['family_name'])) {
			shn_form_label(_t('Family Name'),$_SESSION['mpr_add']['entry']['family_name']);
		}
		if (isset($_SESSION['mpr_add']['entry']['local_name'])) {
			shn_form_label(_t('Local Name'),$_SESSION['mpr_add']['entry']['local_name']);
		}
		if (isset($_SESSION['mpr_add']['entry']['dob'])) {
			shn_form_label(_t('Date of Birth'),$_SESSION['mpr_add']['entry']['dob']);
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_age_group'])) {
			shn_form_label(_t('Age Group'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_age_group'],'opt_age_group'));
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_gender'])) {
			shn_form_label(_t('Gender'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_gender'],'opt_gender'));
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_marital_status'])) {
			shn_form_label(_t('Marital Status'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_marital_status'],'opt_marital_status'));
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_religion'])) {
			shn_form_label(_t('Religion'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_religion'],'opt_religion'));
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_race'])) {
			shn_form_label(_t('Race'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_race'],'opt_race'));
		}
		if ($basic_section) {
			shn_form_fsclose();
		}

		//Physical Details
		if (isset($_SESSION['mpr_add']['entry']['opt_eye_color']) || isset($_SESSION['mpr_add']['entry']['opt_skin_color']) || isset($_SESSION['mpr_add']['entry']['opt_hair_color']) 
			|| isset($_SESSION['mpr_add']['entry']['height']) || isset($_SESSION['mpr_add']['entry']['weight']) || isset($_SESSION['mpr_add']['entry']['physical_comments'])) {
			shn_form_fsopen(_t('Physical Details'));
			$physical_section = true;
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_eye_color'])) {
			shn_form_label(_t('Eye Colour'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_eye_color'],'opt_eye_color'));
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_skin_color'])) {
			shn_form_label(_t('Skin Colour'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_skin_color'],'opt_skin_color'));
		}
		if (isset($_SESSION['mpr_add']['entry']['opt_hair_color'])) {
			shn_form_label(_t('Hair Colour'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_hair_color'],'opt_hair_color'));
		}
		if (isset($_SESSION['mpr_add']['entry']['height'])) {
			shn_form_label(_t('Height'),$_SESSION['mpr_add']['entry']['height']);
		}
		if (isset($_SESSION['mpr_add']['entry']['weight'])) {
			shn_form_label(_t('Weight'),$_SESSION['mpr_add']['entry']['weight']);
		}
		if (isset($_SESSION['mpr_add']['entry']['physical_comments'])) {
			shn_form_label(_t('Comments'),$_SESSION['mpr_add']['entry']['physical_comments']);
		}
		if ($physical_section) {
			shn_form_fsclose();
		}

		//Contact Details
		#    if(isset($_SESSION['mpr_add']['entry']['address']) || 
		#            isset($_SESSION['mpr_add']['entry']['zip']) ||
		#            isset($_SESSION['mpr_add']['entry']['phone']) ||
		#            isset($_SESSION['mpr_add']['entry']['mobile']) ){
		#        shn_form_fsopen("Contact Details");
		#        $contact_section = true;
		#    }
		shn_form_fsopen(_t('Contact Details'));
		$contact_section = true;
		if (isset($_SESSION['mpr_add']['entry']['address'])) {
			shn_form_label(_t('Address'),$_SESSION['mpr_add']['entry']['address']);
		}
		
		/* This hack should also include in the
			lib_location
		*/
		//Starts
		$i = $conf['mod_mpr_location_upper_limit'] - 1;
		while ( $i < $conf['mod_mpr_location_lower_limit'] ) {
			$i++;
			if (isset($_SESSION['mpr_add']['entry'][$i])) {
				$sql = " SELECT location.name , field_options.option_description FROM location ". 
				" INNER JOIN field_options ON field_options.option_code = location.opt_location_type " .
				" WHERE location.opt_location_type = '$i' AND " .
				" location.loc_uuid = '{$_SESSION['mpr_add']['entry'][$i]}' ";
				$result = $global['db']->GetRow($sql);
				shn_form_label($result['option_description'] , $result['name']);
			}
		}
		//Ends
		
		if (isset($_SESSION['mpr_add']['entry']['zip'])) {
			shn_form_label(_t('Postal Code'),$_SESSION['mpr_add']['entry']['zip']);
		}
		if (isset($_SESSION['mpr_add']['entry']['phone'])) {
			shn_form_label(_t('Home Phone'),$_SESSION['mpr_add']['entry']['phone']);
		}
		if (isset($_SESSION['mpr_add']['entry']['mobile'])) {
			shn_form_label(_t('Mobile'),$_SESSION['mpr_add']['entry']['mobile']);
		}
		if ($contact_section) {
			shn_form_fsclose();
		}

		if (isset($_SESSION['mpr_add']['entry']['opt_blood_type']) || isset($_SESSION['mpr_add']['entry']['last_seen']) || isset($_SESSION['mpr_add']['entry']['last_clothing']) 
			|| isset($_SESSION['mpr_add']['entry']['comments']) ) { 
			shn_form_fsopen(_t('Other Details'));
			$other_section = true;
		}

		//Other Details
		if (isset($_SESSION['mpr_add']['entry']['opt_blood_type'])) {
			shn_form_label(_t('Blood Type'),shn_get_field_opt($_SESSION['mpr_add']['entry']['opt_blood_type'],'opt_blood_type'));
		}
		if (isset($_SESSION['mpr_add']['entry']['last_seen'])) {
			shn_form_label(_t('Last Seen'),$_SESSION['mpr_add']['entry']['last_seen']);
		}
		if (isset($_SESSION['mpr_add']['entry']['last_clothing'])) {
			shn_form_label(_t('Last Clothing'),$_SESSION['mpr_add']['entry']['last_clothing']);
		}
		if (isset($_SESSION['mpr_add']['entry']['comments'])) {
			shn_form_label(_t('Comments'),$_SESSION['mpr_add']['entry']['comments']);
		}
		if ($other_section) {
			shn_form_fsclose();
		}

		//Reporting Person
		shn_form_fsopen(_t('Reporting Person'));
			if (isset($_SESSION['mpr_add']['entry']['tracker_id'])) {
				shn_add_get_tracker_details($_SESSION['mpr_add']['entry']['tracker_id']); 
			}
			if (isset($_SESSION['mpr_add']['report_person']['rep_full_name'])) {
				shn_form_label(_t('Name'),$_SESSION['mpr_add']['report_person']['rep_full_name']);
			}
			if (isset($_SESSION['mpr_add']['report_person']['opt_relationship_type'])) {
				shn_form_label(_t('Relation'),$_SESSION['mpr_add']['report_person']['opt_relationship_type']);
			}
			if (isset($_SESSION['mpr_add']['report_person']['rep_address'])) {
				shn_form_label(_t('Address'),$_SESSION['mpr_add']['report_person']['rep_address']);
			}
			if (isset($_SESSION['mpr_add']['report_person']['rep_phone'])) {
				shn_form_label(_t('Phone'),$_SESSION['mpr_add']['report_person']['rep_phone']);
			}
			if (isset($_SESSION['mpr_add']['report_person']['rep_email'])) {
				shn_form_label(_t('Email'),$_SESSION['mpr_add']['report_person']['rep_email']);
			}
		shn_form_fsclose();

		
		/*
		shn_form_fsopen(_t('Confirm'));
			?><p><?php echo  _t('Is the information that you\'ve entered correct?'); ?></p><?php
			shn_form_submit(_t('Next'));
		shn_form_fsclose();
		*/
		?><p><?php echo  _t('Click on the "Next" Button to go back to the main screen.'); ?></p><?php
		shn_form_submit(_t('Next'));
	shn_form_fclose();
}



/**
 * This function commits the given Missing person's data to the databsae.
 * @access public
 * @return void
 */
function shn_mpr_addmp_commit() {
	/* LATER
		global $global;
		include_once($global['approot'].'inc/lib_dbentity/obj_person.inc');
		$missing_person = new shn_Person($_SESSION['mpr_entry']['p_uuid']);
		
		foreach($_SESSION['mpr_entry'] as $k => $v){
			if($k != 'seq')
			echo '$missing_person->set_'."$k($v)<br>";
		}
	*/

	// $insert_array[<field_name>] = value
	global $global;
	global $conf;

    include_once($global['approot'].'inc/lib_uuid.inc');

	//Basic Details : person_uuid
	//@todo: soundex insert
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['full_name'])){
		$insert_array['full_name'] = $_SESSION['mpr_add']['entry']['full_name'];
		shn_db_insert_phonetic($insert_array['full_name'],$insert_array['p_uuid']);
	}
	if(isset($_SESSION['mpr_add']['entry']['family_name'])){
		$insert_array['family_name'] = $_SESSION['mpr_add']['entry']['family_name'];
		shn_db_insert_phonetic($insert_array['family_name'],$insert_array['p_uuid']);
	}
	if(isset($_SESSION['mpr_add']['entry']['local_name'])){
		$insert_array['l10n_name'] = $_SESSION['mpr_add']['entry']['local_name'];
		shn_db_insert_phonetic($insert_array['l10n_name'],$insert_array['p_uuid']);
	}
	shn_db_insert($insert_array,'person_uuid',true, 'p_uuid');
	$insert_array = null; // reset array 


	//Identity
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['idcard'])) {
		$insert_array['serial'] = $_SESSION['mpr_add']['entry']['idcard'];
		$insert_array['opt_id_type'] = 'nic';
		shn_db_insert($insert_array,'identity_to_person',true,'p_uuid');
	}
	if(isset($_SESSION['mpr_add']['entry']['passport'])) {
		$insert_array['serial'] = $_SESSION['mpr_add']['entry']['passport'];
		$insert_array['opt_id_type'] = 'pas';
		shn_db_insert($insert_array,'identity_to_person',true,'p_uuid');
	}
	if(isset($_SESSION['mpr_add']['entry']['drv_license'])) {
		$insert_array['serial'] = $_SESSION['mpr_add']['entry']['drv_license'];
		$insert_array['opt_id_type'] = 'dln';
		shn_db_insert($insert_array,'identity_to_person', true, 'p_uuid');
	}
	$insert_array = null; // reset array


	//Contacts
	$insert_array['pgoc_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];  
	if(isset($_SESSION['mpr_add']['entry']['address'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['address'];
		$insert_array['opt_contact_type'] = 'hom';
	}
	shn_db_insert($insert_array,'contact', true, 'pgoc_uuid');
	$insert_array = null; // reset array


	$insert_array['pgoc_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['phone'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['phone'];
		$insert_array['opt_contact_type'] = 'curr';
		
	}
	shn_db_insert($insert_array,'contact', true, 'pgoc_uuid');
	$insert_array = null; // reset array


	$insert_array['pgoc_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['mobile'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['mobile'];
		$insert_array['opt_contact_type'] = 'cmob';
	}
	shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
	$insert_array = null; // reset array


	/* This hack should be integrated with the lib_location */
	//Starts
	$i = $conf['mod_mpr_location_lower_limit'];
	while((! isset($_SESSION['mpr_add']['entry'][$i])) && $i > $conf['mod_mpr_location_upper_limit'] ) {
		$i--;
	}
	//Ends
	if(isset($_SESSION['mpr_add']['entry'][$i])) {
		$insert_array['location_id'] = $_SESSION['mpr_add']['entry'][$i];
	}

	if(isset($_SESSION['mpr_add']['entry']['zip'])) {
		$insert_array['postcode'] = $_SESSION['mpr_add']['entry']['zip'];
	}
	shn_db_insert($insert_array,'location_details', true, 'poc_uuid');
	$insert_array = null; // reset array


	//insert postal code to contact
	$insert_array['pgoc_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['zip'])){
		$insert_array['contact_value']=$_SESSION['mpr_add']['entry']['zip'];
		$insert_array['opt_contact_type']='zip';
	}
	shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
	/*    $insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	//Contacts
	if(isset($_SESSION['mpr_add']['entry']['address']))
		shn_form_label('Address',$_SESSION['mpr_add']['entry']['address']);
	if(isset($_SESSION['mpr_add']['entry']['']))
		shn_form_label('Postal Code',$_SESSION['mpr_add']['entry']['zip']);
	if(isset($_SESSION['mpr_add']['entry']['address']))
		shn_form_label('Home Phone',$_SESSION['mpr_add']['entry']['phone']);
	if(isset($_SESSION['mpr_add']['entry']['address']))
		shn_form_label('Mobile',$_SESSION['mpr_add']['entry']['mobile']);
	if($contact_section)
	*/
	$insert_array=null; // reset array


	//Physical Details : person_physical
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['opt_eye_color'])) {
		$insert_array['opt_eye_color'] = $_SESSION['mpr_add']['entry']['opt_eye_color'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_skin_color'])) {
		$insert_array['opt_skin_color'] = $_SESSION['mpr_add']['entry']['opt_skin_color'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_hair_color'])) {
		$insert_array['opt_hair_color'] = $_SESSION['mpr_add']['entry']['opt_hair_color'];
	}
	if(isset($_SESSION['mpr_add']['entry']['height'])) {
		$insert_array['height'] = $_SESSION['mpr_add']['entry']['height'];
	}
	if(isset($_SESSION['mpr_add']['entry']['weight'])) {
		$insert_array['weight'] = $_SESSION['mpr_add']['entry']['weight'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_blood_type'])) {
		$insert_array['opt_blood_type'] = $_SESSION['mpr_add']['entry']['opt_blood_type'];
	}
	if(isset($_SESSION['mpr_add']['entry']['physical_comments'])) {
		$insert_array['comments'] = $_SESSION['mpr_add']['entry']['physical_comments'];
	}
	shn_db_insert($insert_array,'person_physical',true,'p_uuid');
	$insert_array = null; // reset array


	//Other Details
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['last_seen'])) {
		$insert_array['last_seen'] = $_SESSION['mpr_add']['entry']['last_seen'];
	}
	if(isset($_SESSION['mpr_add']['entry']['last_clothing'])) {
		$insert_array['last_clothing'] = $_SESSION['mpr_add']['entry']['last_clothing'];
	}
	if(isset($_SESSION['mpr_add']['entry']['comments'])) {
		$insert_array['comments'] = $_SESSION['mpr_add']['entry']['comments'];
	}
	shn_db_insert($insert_array,'person_missing',true,'p_uuid');
	$insert_array = null; // reset array


	//person_details        
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['dob'])) {
		$insert_array['birth_date'] = $_SESSION['mpr_add']['entry']['dob'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_age_group'])) {
		$insert_array['opt_age_group'] = $_SESSION['mpr_add']['entry']['opt_age_group'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_gender'])) {
		$insert_array['opt_gender'] = $_SESSION['mpr_add']['entry']['opt_gender'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_marital_status'])) {
		$insert_array['opt_marital_status'] = $_SESSION['mpr_add']['entry']['opt_marital_status'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_religion'])) {
		$insert_array['opt_religion'] = $_SESSION['mpr_add']['entry']['opt_religion'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_race'])) {
		$insert_array['opt_race'] = $_SESSION['mpr_add']['entry']['opt_race'];
	}
	shn_db_insert($insert_array,'person_details',true,'p_uuid');
	$insert_array = null; // reset array


	//Insert Into person_status mis
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	$insert_array['opt_status'] = $_SESSION['mpr_add']['entry']['opt_status'];
	$insert_array['isvictim'] = 'TRUE';
	shn_db_insert($insert_array,'person_status',true,'p_uuid');
	$insert_array = null; // reset array


	//insert into mutiple incidents 
	$insert_array['x_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	$insert_array['incident_id'] = $_SESSION['user_pref_ims_incident_id'];
	shn_db_insert($insert_array,'resource_to_incident',true,'x_uuid');
	$insert_array = null; // reset array

	/* todo: Later for now using the person_to_report to group 
	//Insert into pgroup
	//For Tracking purpose create a group around missing person
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	$insert_array['opt_group_type'] = 'mpr_trk';
	shn_db_insert($insert_array,'pgroup');
	$insert_array = null; // reset array
	*/


	if($_SESSION['mpr_add']['entry']['tracker_id']){
		shn_add_person_to_report ($_SESSION['mpr_add']['entry']['p_uuid'], $_SESSION['mpr_add']['entry']['tracker_id'], $_SESSION['mpr_add']['report_person']['opt_relationship_type']);
	} else {
		shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['entry']['p_uuid']);
	}

	//Insert Image if image save handler is set to database (chc 1/26/10 : add 'url' param)
	if($conf['mod_mpr_upload_pic_handler']== 'database'){
		// shn_image_to_db_ex($_SESSION['mpr_add']['entry']['p_uuid'], $_SESSION['mpr']['entry']['image'], $_SESSION['mpr']['entry']['image_type'], $_SESSION['mpr']['entry']['image_height'], $_SESSION['mpr']['entry']['image_width'],'','person');

		shn_image_to_db_url($_SESSION['mpr_add']['entry']['p_uuid'], $_SESSION['mpr']['entry']['image'], $_SESSION['mpr']['entry']['image_type'], $_SESSION['mpr']['entry']['image_height'], $_SESSION['mpr']['entry']['image_width'],$_SESSION['mpr']['entry']['url'],'','person');
	} 
	
	//go back to the main menu
	//shn_mpr_default();    
}



/**
 * This function inserts the reporting person to the people registry
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_mpr_addmp_insert_reporter($p_uuid) {
	//Reported person entry 
	$rep_uuid = shn_create_uuid('p');


	//Person uuid table
	$insert_array['p_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['rep_full_name'])){
		$insert_array['full_name'] = $_SESSION['mpr_add']['report_person']['rep_full_name'];
		// Insert into Phonetic words
		shn_db_insert_phonetic($_SESSION['mpr_add']['report_person']['rep_full_name'],$insert_array['p_uuid']);
	}
	shn_db_insert($insert_array,'person_uuid',true,'p_uuid');
	$insert_array = null; // reset array


	//Insert the status
	/*
	* If not a victim, isvictim = false , status = ali (Alive and Well) 
	* If a victim, isvictim = true , status = given status 
	*/
	$insert_array['p_uuid'] = $rep_uuid;
	if($_SESSION['mpr_add']['report_person']['is_dv'] == 'yes') {
		$insert_array['opt_status'] = $_SESSION['mpr_add']['report_person']['opt_status'];
		$insert_array['isvictim'] = 'TRUE';
	} else {
		$insert_array['opt_status'] = 'ali';
		$insert_array['isvictim'] = 'FALSE';
	} 
	shn_db_insert($insert_array,'person_status',true,'p_uuid');
	$insert_array = null; // reset array


	//Contacts
	$insert_array['poc_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['rep_address'])){
		// todo: make the location
		$insert_array['location_id'] = '0';
		$insert_array['address'] = $_SESSION['mpr_add']['report_person']['rep_address'];
		$insert_array['opt_person_loc_type'] = 'hom';
	}
	shn_db_insert($insert_array,'location_details',true,'poc_uuid');
	$insert_array = null; // reset array


	$insert_array['pgoc_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['rep_phone'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['report_person']['rep_phone'];
		$insert_array['opt_contact_type'] = 'curr';
	}
	shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
	$insert_array = null; // reset array


	$insert_array['pgoc_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['rep_email'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['report_person']['rep_email'];
		$insert_array['opt_contact_type'] = 'emai';
	}
	shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
	$insert_array = null; // reset array

	
	/* 
	* Insert into the person_to_report
	*/
	shn_add_person_to_report($p_uuid,$rep_uuid,$_SESSION['mpr_add']['report_person']['opt_relationship_type']);
}



/**
 * This function helps you to add reporting persons to the missing person
 * @param mixed $p_uuid 
 * @param mixed $rep_uuid 
 * @param mixed $relation 
 * @access public
 * @return void
 */
function shn_add_person_to_report($p_uuid, $rep_uuid, $relation) {
	global $global;

	$insert_array['p_uuid'] = $p_uuid;
	$insert_array['rep_uuid'] = $rep_uuid;
	if($relation!=null) {
		$insert_array['relation'] = $relation;
	} else {
		$insert_array['relation'] = "Not Specified";
	}
	shn_db_insert($insert_array,'person_to_report',true,'p_uuid');
}



/**
 * This function fetches the information of the reporting person with given id.
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_add_get_tracker_details($p_uuid) {
	global $global;

	$rs = $global['db']->GetRow(
		"SELECT a.full_name, b.address , c.contact_value as phone, d.contact_value as email FROM person_uuid a ".
		"LEFT OUTER JOIN location_details b ON a.p_uuid = b.poc_uuid AND b.opt_person_loc_type = 'hom' ".
		"LEFT OUTER JOIN contact c ON a.p_uuid = c.pgoc_uuid AND c.opt_contact_type = 'curr' ".
		"LEFT OUTER JOIN contact d ON a.p_uuid = d.pgoc_uuid AND d.opt_contact_type = 'email' ".
		"WHERE a.p_uuid = '$p_uuid'");
	#var_dump($rs);
	$_SESSION['mpr_add']['report_person']['rep_full_name'] = $rs['full_name'];
	$_SESSION['mpr_add']['report_person']['rep_address'] = $rs['address'];
	$_SESSION['mpr_add']['report_person']['rep_phone'] = $rs['phone'];
	$_SESSION['mpr_add']['report_person']['rep_email'] = $rs['email'];
}



/**
 * This is a bunch of javascript helps for the collapse and expanind of a
 * given division.
 * @todo Move to somewhere 
 * @access public
 * @return void
 */
function shn_js_toggle_layer() { 
	?>
	<script language="javascript">
		function toggle(divition,values) {
			var othe = document.getElementById(divition);
			if ( values == "yes" ) {
				othe.style.display = 'block';
			} else {
				othe.style.display = 'none';
			}
	}

	function toggleLayer(whichLayer,whichLayer1) {
		if (document.getElementById) {
			// this is the way the standards work
			var style1 = document.getElementById(whichLayer).style;
			var style2 = document.getElementById(whichLayer1).style;
			if(style1.display == 'none') {
				style1.display = 'block';
			} else {
				style1.display = 'none';
			}
			if (style2.display == 'none') {
				style2.display = 'block';
			} else {
				style2.display = 'none';
			}
			//style2.display = style2.display? "none":"block";
		} else if (document.all) {
			// this is the way old msie versions work
			var style2 = document.all[whichLayer].style;
			style2.display = style2.display? "none":"block";
		} else if (document.layers) {
			// this is the way nn4 works
			var style2 = document.layers[whichLayer].style;
			style2.display = style2.display? "none":"block";
		}
	}
	</script>
	<?php
}