<?php
/**
 * SN member registration Page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Harsha Halgaswatta(harsha.halgaswatta@gmail.com)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage s
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once $global['approot'] . '/inc/handler_form.inc';
include_once $global['approot'] . '/inc/lib_uuid.inc';
include_once $global['approot'] . '/inc/lib_validate.inc';
include_once ($global['approot'] . '/inc/lib_image.inc');
include_once $global['approot'] . '/mod/sn/lib_sn.inc';
//include_once $global['approot'] . '/inc/lib_form.inc';


//shn_form_open();
if(isset($_REQUEST['seq'])) {
    switch ($_REQUEST['seq']) {
	    case 'page2' :
		    {

		        if(_shn_sn_validate()){
		    		if($_SESSION['admin']){
		    			//_shn_sn_shw_prev_mem_details($_SESSION['tmp_pwd']);
		    			unset($_SESSION['tmp_pwd']);
		    			unset($_SESSION['admin']);
		    		}
		    		else{
		    		    _shn_sn_get_data(true);
		    		}
		    	}
		    	else{
		    		 _shn_sn_set_datails();
		             _shn_sn_confirm();
		    	}

		    	//_shn_sn_add_details();
			    break;
		    }
	    case 'page3' :
	    	{
                _shn_sn_write_to_db();
                _shn_sn_show_welcome_page();
	    	    break;
	    	}
	    case 'finish' :
	    	{
	    		_shn_dsm_write_to_db();
	    		unset($_SESSION['symptoms']);
	    	    break;
	    	}
//	    default :
//	    	{
//	    		//_shn_dsm_get_data(); //every time display the things
//	    	}

      }
} else {
	   _shn_sn_get_data(); //This is the first page to be registered
}
/**
 *
 * show the self sign up form
 */
function _shn_sn_get_data($errors = false)
{
	?>
    <div id="home">
    <h2><?php print (_('Self Sign Up process')); ?></h2>
    </div>
    <?php

    $fullname= _shn_sn_get_full_name($_SESSION[sn][p_uuid]);

	if($errors){
		display_errors();
	}
    shn_form_fopen('add_mem','sn',array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));
    shn_form_hidden(array ('seq' => 'page2'));

    shn_form_fsopen(_('General Details'));
    $extra_opts['req'] = true;
    if($fullname){
        shn_form_label('Full Name',$fullname,'');
    }else{
    	shn_form_text(_('Full Name'),'f_name','', $extra_opts);
    }

   /* $extra_opts['req'] = true;
	shn_form_text(_('Last Name'),'l_name','', $extra_opts);*/
    $extra_opts = array();
	/*$extra_opts['help'] = "Enter a username for logging the Sahana SN";
	$extra_opts['req'] = true;
	shn_form_text(_('User Name'),'u_name','', $extra_opts);

    $extra_opts['help'] = "Enter a password for logging the Sahana SN";
	$extra_opts['req'] = true;
	shn_form_password(_('Password'),'pwd','',$extra_opts);
	shn_form_password(_('Confirm Password'),'cpwd','',$extra_opts);
*/
	$radio_options = array('male'=>'Male','female'=>'Female');
	shn_form_radio(  $radio_options,'Gender','gender');

	shn_form_upload(_('Picture'),'picture');
    shn_form_text(_('E-Mail'),'e_mail');
    shn_form_text(_('Confirm Email'),'con_e_mail');
    shn_form_date(_("Date of Birth"),'dob');

    shn_form_fsclose();

    shn_form_fsopen(_('Expertice Details'));
    $deseaseslist = array();
    /*$diseases = _shn_sn_get_disease_list();

       while(!$diseases->EOF){

           array_push($deseaseslist,$diseases->fields['dis_name']);
       	   $diseases->MoveNext();
       }*/



    $diseases = array ('default'=>'select one','disease1'=>'Disease 1','disease2'=>'Disease 2','disease3'=>'Disease 3','disease4'=>'Disease 4');


    $extra_opts['req'] = true;

    shn_form_select($diseases , 'Interest Area', 'in_area','select one', $extra_opts);
    //shn_form_text(_('Interest Area'),'in_area');
    shn_form_text(_('Experience'),'expr');
    shn_form_textarea(_('Other infomation'),'oth_info');

    shn_form_fsclose();

    shn_form_fsopen(_('Location (optional)'));


    shn_form_text(_('Country'),'country');
    shn_form_text(_('City'),'city');

    shn_form_fsclose();

    shn_form_submit(_('Register'),"name='next'");

    shn_form_fclose();
}

/**
 * if username is already in the sahana db, for administrative purposes
 * this function show the details of the current member.
 */
function _shn_sn_shw_prev_mem_details($errors = false){
	if($errors){
		clean_errors();
		add_error('Username already exist! ' .$_SESSION['tmp_pwd']);
		display_errors();
	}
    ?>
    <div id="home">
    <h2><?php print (_('Details of the person having the username u entered')); ?></h2>
    </div>
    <?php
    shn_form_fopen('add_mem','sn',array('req'=>false));
    shn_form_hidden(array ('seq' => 'page3'));


    shn_form_fsopen('details of previous member');

    shn_form_label('Username :','uname'); //******************* how to store the particular person ,,,,, ASK
    shn_form_label('First name :','fname');
    shn_form_label('Last Name :','lname');
    shn_form_label('E-mail :','email');
    shn_form_label('User Role :','role');




    shn_form_fsclose();
    shn_form_fclose();


}
/**
 * validate all the fields,specially the username availability.
 * accordingly it will act.
 */

function _shn_sn_validate()
{
	clean_errors();

	$error_flag = false;
	//$u_name = $_POST['u_name'];
	$f_name = $_POST['f_name'];
    $in_area = $_POST['in_area'];
    //$pwd = $_POST['pwd'];
    //$cpwd = $_POST['cpwd'];
    $email = $_POST['e_mail'];
    $cemail = $_POST['con_e_mail'];
    $dob = $_POST['dob'];


    $arr = array("t" => "Tsunami", "e" => "EarthQuake", "b" => "Bomb Blast");
/*	if ($u_name == null) {
		//$errors[0] = 'Please enter a username';
		add_error('please enter username');
        $error_flag = true;
	}
	else{
		$tmp_pwd = _shn_sn_chk_usrname($u_name);
		if($tmp_pwd){
		   add_error('Username already exist in Sahana');
	      // $_SESSION['user'] = true;
		   $error_flag = true;
		}


	}*/
	if($f_name){
		if($f_name == null){
		add_error('please enter fulltname');
		$error_flag = true;
	   }
	}

    if($in_area == 'default'){
		add_error('please select a interest area');
		$error_flag = true;
	}
    if($email){

    	if(!shn_valid_email($email,true)){
        add_error('please enter a correct email address');
		$error_flag = true;
    	}
    	if($cemail== null){
    		 add_error('Confirm your email address');
		     $error_flag = true;
    	}else{
    		if($email != $cemail ){
    			add_error('E-mail addresses dont match');
		        $error_flag = true;
    		}
    	}

	}


/*	if($l_name == null){
		add_error('please enter lasttname');
		$error_flag = true;
	}*/
/*	if($pwd == null){
		add_error('please enter password');
		$error_flag = true;
	}
    if($cpwd == null){
		add_error('please confirm your password');
		$error_flag = true;
	}
	else{
		if($pwd != $cpwd ){
		    add_error('password do not match');
		    $error_flag = true;
	    }
	}*/
   	if($_FILES['picture'] == null || !isset($_FILES['picture'])){
	  // $_SESSION['a']= false;

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

/**
 * set details into session;
 *
 */
function _shn_sn_set_datails(){
	global $global;
	//$_SESSION['p_uuid'] = $_SESSION[sn][p_uuid];
	if($_POST['f_name']){
		$_SESSION['full_name'] = $_POST['f_name'];
	}
    $_SESSION['gender'] = $_POST['gender'];
	$_SESSION['email'] = $_POST['e_mail'];
	$_SESSION['dob'] = $_POST['dob'];
	$_SESSION['in_area'] = $_POST['in_area'];
	$_SESSION['expr'] = $_POST['expr'];
	$_SESSION['oth_info'] = $_POST['oth_info'];
	$_SESSION['country'] = $_POST['country'];
	$_SESSION['city'] = $_POST['city'];


	 if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type
		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['picture']['tmp_name']);
			$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
			$_SESSION['sn']['mem']['image'] = $pic;
			$_SESSION['sn']['mem']['image_type'] = $ext;
			$_SESSION['sn']['mem']['image_height'] = $info[1];
			$_SESSION['sn']['mem']['image_width'] = $info[0];
		}


		$ext = '.' . $ext;
		$upload_dir = $global['approot'] . 'www/tmp/';
		$uploadfile = $upload_dir . 'ori_' . $_SESSION[sn][p_uuid] . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $_SESSION[sn][p_uuid] . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);
		//echo 'image uploaded';

	}
}
/**
 * show entered details just to confirm
 */
function _shn_sn_confirm(){
    ?>
    <div id="home">
    <h2><?php print (_('Confirm your details')); ?></h2>
    </div>
    <?php
    shn_form_fopen('add_mem','sn');
    shn_form_hidden(array ('seq' => 'page3'));
    $text_options = array();
    shn_form_fsopen(_('General Details'));

    if(isset($_SESSION['full_name'])){
    	$text_options['value'] = $_SESSION['full_name'];
        shn_form_text(_('Full Name'),'fullname','', $text_options);
    }else{
    	$fullname= _shn_sn_get_full_name($_SESSION[sn][p_uuid]);
    	shn_form_label('Full Name',$fullname,'');
    }

/*    $text_options['value'] = $_SESSION['last_name'];
	shn_form_text(_('Last Name'),'lastname','', $text_options);*/
	//$text_options['value'] = $_SESSION['user_name'];
	//shn_form_text(_('User Name'),'username','', $text_options);

    $radio_options = array('male'=>'Male','female'=>'Female');
    $text_options['value'] = $_SESSION['gender'];
    shn_form_radio(  $radio_options,'Gender','gender','',$text_options);

    shn_form_label(("Current Photograph"), '');
    ?>
	<p align='center'>
	<?php

	shn_show_thumb_url($_SESSION[sn][p_uuid],'','sn','mem_img',true);
    ?>

	</p>
	<?php


	//shn_show_thumb_url($_SESSION['p_uuid'],'','sn','add_mem',true);
	$text_options['value'] = $_SESSION['email'];
    shn_form_text(_('E-Mail'),'email','', $text_options);

    shn_form_date(_("Date of Birth"),'dob','', $text_options);

    shn_form_fsclose();

    shn_form_fsopen(_('Preference Details'));

    $text_options['value'] = $_SESSION['in_area'];
    shn_form_text(_('Interest Area'),'in_area', '',$text_options);
    $text_options['value'] = $_SESSION['expr'];
    shn_form_text(_('Experience'),'expr','', $text_options);
    $text_options['value'] = $_SESSION['oth_info'];
    shn_form_textarea(_('Other infomation'),'oth_info', '',$text_options);

    shn_form_fsclose();

    shn_form_fsopen(_('Location (optional)'));

    $text_options['value'] = $_SESSION['country'];
    shn_form_text(_('Country'),'country', '',$text_options);

    $text_options['value'] = $_SESSION['city'];
    shn_form_text(_('City'),'city', '',$text_options);

    shn_form_fsclose();

    shn_form_submit(_('Save'),"name='next'");

    shn_form_fclose();
}

/**
 * insert details into the sn_members table.
 */
function _shn_sn_write_to_db()
{

		 $sql = "INSERT INTO sn_members(sn_mem_uuid," .
        		"sn_mem_email,sn_mem_dob,sn_mem_gender," .
        		"sn_mem_country,sn_mem_city,sn_mem_interests,sn_mem_experience,sn_mem_other_info) VALUES " .
        		"('{$_SESSION[sn][p_uuid]}'," .
        		"'{$_POST['email']}','{$_POST['dob']}','{$_POST['gender']}','{$_POST['country']}','{$_POST['city']}'" .
        		",'{$_POST['in_area']}','{$_POST['expr']}','{$_POST['oth_info']}')";

	    $res = _shn_sn_execute($sql);

	    if($_REQUEST['fullname']){
	    	    $sql1 ="UPDATE  person_uuid SET full_name='{$_POST['fullname']}' WHERE p_uuid='{$_SESSION[sn][p_uuid]}'";
                $res = _shn_sn_execute($sql1);
		        if ($res) {
					add_confirmation(('Your registration is successful ,Have benefits of Social Network'));
	            }
	    }

	    if($_SESSION['sn']['mem']['image']){
    	       shn_image_to_db_ex($_SESSION[sn][p_uuid], $_SESSION['sn']['mem']['image'], $_SESSION['sn']['mem']['image_type'],$_SESSION['sn']['mem']['image_height'],$_SESSION['sn']['mem']['image_width'], null, 'mem_image');

         }
    unset($_SESSION['full_name']);
    unset($_SESSION['email']);
    unset($_SESSION['country']);
    unset($_SESSION['city']);
    unset($_SESSION['gender']);
    unset($_SESSION['in_area']);
    unset($_SESSION['expr']);
    unset($_SESSION['oth_info']);
    unset($_SESSION['sn']['mem']['image']);
    unset($_SESSION['sn']['mem']['image_type']);
    unset($_SESSION['sn']['mem']['image_height']);
    unset($_SESSION['sn']['mem']['image_width']);


}

/**
 * show welcome page after registering successfully.
 */
function _shn_sn_show_welcome_page(){
    ?>
    <div id="home">
        <h2><?php print (_('Thank you for registering in Social Network, ENJOY SN... ')); ?></h2>
    </div>
    <?php
    shn_form_fopen('log_page','sn',array('req'=>false));
    ?>
    <h3><div align="center"><?php shn_form_submit('Go to home'); ?></div></h3>
    <?php

    shn_show_thumb_url($_SESSION[sn][p_uuid],'database','sn','mem_img',false);
    shn_form_fclose();

}
//shn_form_close();
