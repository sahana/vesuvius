<?php

/**
 * SN group creation
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


//include_once ('lib.inc');
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_errors.inc');
include_once ($global['approot'] . '/inc/lib_image.inc');
include_once ($global['approot'] . '/mod/or/lib_or.inc');
include_once ($global['approot'] . '/inc/lib_uuid.inc');
include_once ($global['approot'] . '/inc/lib_ajax.inc');
include_once $global['approot'] . '/mod/sn/lib_sn.inc';


//include_once ($global['approot'] . '/inc/handler_upload.inc');

if(isset($_REQUEST['seq'])) {
	switch($_REQUEST['seq']){
		case 'page2':
            {
            $button = $_POST['button'];
            if($button == 'Create Group'){
            	if(_shn_sn_validate()){
            		_shn_sn_create_group(true);
            	}else{
            		_shn_sn_set_details();
            		_shn_sn_show_summary();
            		//_shn_sn_add_gr_to_db();
            		//_shn_sn_invite_friends();
            	}

            }else{
                 _shn_sn_show_summary();
            }
            break;

            }

         case 'page3' :
         {


		     $button = $_POST['button'];

			 if($button == 'Confirm'){

                _shn_sn_add_gr_to_db();
			 }

			 if($button == 'Edit'){
                _shn_sn_show_ed_group();

			 }
             break;

         }
         case 'page4' :
         {
              _shn_sn_show_ed_group();
              break;
         }
	}


}
else{

	_shn_sn_create_group();

}


function _shn_sn_create_group($errors = false){

    if($errors){
    	display_errors();
    }

	?>
	<div align="right"><a href="index.php?mod=sn&act=log_out"><b><?php echo  ('Logout'); ?> </b></a></div>
    <h2><center><?php print (('Create your own groups as you wish')); ?></center></h2>
    <?php
   // shn_form_fopen('sn_groups','sn', array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));

    shn_form_fopen('cr_groups','sn',array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));
    shn_form_fsopen(('Create Group'));

    shn_form_hidden(array('seq' => 'page2'));

    print '<br />';
       $radio_options = array('public'=>'Public','private'=>'Private');
       $catogery_options = array('default'=>'select one','disaster'=>'Based on disaster insident','disease'=>'Based on disease condition');

       $deseaseslist = array();

       $diseases = _shn_sn_get_disease_list();

       while(!$diseases->EOF){

           array_push($deseaseslist,$diseases->fields['dis_name']);
       	   $diseases->MoveNext();
       }



       $diseases = array ('default'=>'select one','disease0'=>'Disease 0','disease1'=>'Disease 1','disease2'=>'Disease 2','disease3'=>'Disease 3');

	   $extra_opts['help'] = ("Enter the group name here(Required)");
	   $extra_opts['req'] = true;
	   shn_form_text(('Group Name'), 'g_name', 'size="30"', $extra_opts);



	   $extra_opts['help'] = ("Select the group catogery on which you would make your own groups");
	   //shn_form_select($catogery_options, 'category', 'category','select one', $extra_opts);

	   shn_form_select($diseases , 'category', 'category','select one', $extra_opts);

	   $extra_opts['help'] = ("Description about the group.for what you are making such a group");
	   shn_form_textarea(('Description'), 'description', 'size="30"', $extra_opts);

	   $extra_opts['help'] = ("In case of searching your group what are the tags you like to use");
	   shn_form_text(('Search tags'), 'search_tags', 'size="30"', $extra_opts);

	   shn_form_upload(('Group Image'), "picture");

       shn_form_radio(  $radio_options,'Access Level','ac_level');

/*       ?>
       <br><br>
       <h3></h3>

       <div align="left">
       <p><input type="checkbox" name="name" value="value"/>I agree to the Sahana <a href="#" >SN terms and condition</a> </p>
       </div>
      <?php*/
      // shn_form_checkbox('','ter_con','left');

       //shn_form_label('','I agree to the Sahana SN terms and condition');
	   shn_form_fsclose();
       ?> <div align='center' ><br>
	   <?php shn_form_submit('Create Group',"name='button'");
	         shn_form_submit('Cancel',"name='button'");

	   ?> </div>
	   <?php
	   shn_form_fclose();
	   print '<br />';






}

function _shn_sn_show_ed_group($errors = null){

   if($errors){
    	display_errors();
     }
      $id = null;
      $id = $_REQUEST['id'];
      $gr_name = $_REQUEST['name'];
      $category = $_REQUEST['category'];
      $desc = $_REQUEST['desc'];
      $tags = $_REQUEST['tags'];
      $level = $_REQUEST['level'];
    //$id = $_REQUEST['id'];


      $array0['value'] = $_SESSION['g_name'];
      $array1['value'] = $_SESSION['category'];
      $array2['value'] = $_SESSION['description'];
      $array3['value'] = $_SESSION['search_tags'];
      $array4['value'] = $_SESSION['ac_level'];
      $gr_id = $_SESSION['p_uuid'];


	?>

    <h2><center><?php print (('Create your own groups as you wish')); ?></center></h2>
    <?php
   // shn_form_fopen('sn_groups','sn', array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));

      shn_form_fopen('cr_groups','sn',array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));
      shn_form_fsopen(('Create Group'));

       shn_form_hidden(array('seq' => 'page2'));

       print '<br />';
       $radio_options = array('public'=>'Public','private'=>'Private');
       $catogery_options = array('default'=>'select one','disaster'=>'Based on disaster insident','disease'=>'Based on disease condition');
       $diseases = array ('default'=>'select one','disaster'=>'Tsunami','disease1'=>'Disease 1','disease2'=>'Disease 2','disease3'=>'Disease 3');

	   $array0['help'] = ("Enter the group name here(Required)");
	   $array0['req'] = true;
	   shn_form_text(('Group Name'), 'g_name', 'size="30"', $array0);



	   $array1['help'] = ("Enter the group catogery on which you would make your own groups");
       $array1['req'] = true;
	   shn_form_select($catogery_options, 'category', 'category','select one', $array1);

	   //shn_form_select($diseases , 'category', 'category','select one', $extra_opts);

	   $array2['help'] = ("Description about the group.for what you are making such a group");
	   shn_form_textarea(('Description'), 'description', 'size="30"', $array2);

	   $array3['help'] = ("In case of searching your group what are the tags you like to use");
	   shn_form_text(('Search tags'), 'search_tags', 'size="30"', $array3);


       ?> <div align="center"> <?php

       	    shn_show_thumb_url($_SESSION['p_uuid'] ,'','sn','group_img',true); ?> </div> <?php echo '<br><br><br><br>';

	   shn_form_upload(('Change Image'), "picture");

       shn_form_radio(  $radio_options,'Access Level','ac_level','',$array4);


	   shn_form_fsclose();
       ?> <div align='center' ><br>
	   <?php shn_form_submit('Create Group',"name='button'");
	         shn_form_submit('Cancel',"name='button'");

	   ?> </div>
	   <?php
	   shn_form_fclose();
	   print '<br />';




}



function _shn_sn_validate(){
	clean_errors();
	$error_flag= false;
	$username = $_SESSION['username'];
	$gr_name = $_POST['g_name'];
	$category = $_POST['category'];
	$description = $_POST['description'];
	$search_tags = $_POST['search_tags'];
	$group_image = $_POST['gr_image'];
	$access_level = $_POST['ac_level'];

	if ($gr_name == null) {
		//$errors[0] = 'Please enter a username';
		add_error('please enter a group name');
        $error_flag = true;
	}
	if($category  == null){
		add_error('please select a category');
		$error_flag = true;
	}
	if($description== null){
		add_error('please enter a description');
		$error_flag = true;
	}
	if($search_tags == null){
		add_error('No search tag entered');
		$error_flag = true;
	}
	if($access_level == null){
		add_error('No access level selected');
		$error_flag = true;
	}
	if($_FILES['picture'] == null || !isset($_FILES['picture'])){
	   $_SESSION['a']= false;

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
 * This function would responsible for inviting friends at the
 * group creation...
 * In the future it may be usefull, when sahana SN develops more.
 *
 *
 */
/*function _shn_sn_invite_friends(){
	?>
	<div align="right"><a href="index.php?mod=sn&act=log_out"><b><?php echo  _t('Logout'); ?> </b></a></div>
	<h3><font color="red"> Group Created Successfully....... </font></h3>
    <h2><center><?php print (_t('Invite your friends to be involved in this group')); ?></center></h2>
    <?php
	shn_form_fopen('cr_groups','sn');

    shn_form_fsopen(_t('Invite Friends'));

	shn_form_hidden(array('seq' => 'page3'));


    $extra_opts['value'] = 'Let we get together in Sahana Social Network';
    $extra_opts['req'] = true;
    shn_form_text('Subject :','subject','',$extra_opts);

    $array_opts['cols'] = '100';
    $array_opts['rows'] = '1';
    $extra_opts['value'] = 'harsha.halgaswatta@gmail.com';
    shn_form_text('From :','from','',$extra_opts);
    ?><div align="center">
    <br>
    <u><b><i> select people you want to send invitations  </i> </b></u>
    <br><br>
    </div>





    <?php
    //$extra_opts = array();
    //$extra_opts['value'] = 'Let we get together in Sahana Social Network';
   // shn_form_text(_t('Subject'), 'subject', 'size="30"',$extra_opts);
    //shn_form_text(_t('From'), 'from', 'size="30"');

     $users_list = _shn_sn_get_users_list();

     while (!$users_list ->EOF) {

    ?>

     <tr>
          <td align="left" height="200pt"><?php


          $extra_opts['value'] = $users_list->fields['sn_mem_email'];
          shn_form_checkbox($users_list->fields['sn_mem_username'] ,'chkboxarray[]','', $extra_opts);


          ?></td>
          <td align="right" heitht="200pt"><?php //shn_show_thumb_url($users_list->fields['sn_mem_uuid'],'database','sn','mem_img',false)?></td>

     </tr>

    <?php

 	$users_list->MoveNext();

    }

    ?>
    <br><br>
   <table>
    <tr>

    </tr>


  </table>
    <br>
   <?php
    $extra_options = array();
    $array_options['cols'] = '50';
    $array_options['rows'] = '5';
    shn_form_textarea('Personal message','body','',$array_options);


    shn_form_submit('Invite Now'," name='button'");
    shn_form_fsclose();
    shn_form_fclose();


}*/


function _shn_sn_set_details(){
    global $global;

    $_SESSION['p_uuid'] = shn_create_uuid();
	$_SESSION['g_name'] = $_POST['g_name'];
    $_SESSION['category'] = $_POST['category'];
	$_SESSION['description'] = $_POST['description'];
	$_SESSION['search_tags'] = $_POST['search_tags'];

	$_SESSION['picture'] = $_POST['picture'];
    $_SESSION['ac_level'] = $_POST['ac_level'];




 if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type
		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['picture']['tmp_name']);
			$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
			$_SESSION['sn']['group']['image'] = $pic;
			$_SESSION['sn']['group']['image_type'] = $ext;
			$_SESSION['sn']['group']['image_height'] = $info[1];
			$_SESSION['sn']['group']['image_width'] = $info[0];
		}


		$ext = '.' . $ext;
		$upload_dir = $global['approot'] . 'www/tmp/';
		$uploadfile = $upload_dir . 'ori_' . $_SESSION['p_uuid'] . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $_SESSION['p_uuid'] . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);


	}
}

/*function _shn_sn_send_mail_to_friends(){
	$subject = $_POST['subject'];
	$from = $_POST['from'];
	$body = $_POST['body'];


    $selected = array ();
    var_dump($_POST['chkboxarray']);

    $pieces = array();
    $pieces = explode(":", $_POST['chkboxarray']);
	//$selected = $_POST['chkboxarray'];


    echo $pieces;

	foreach ($pieces as $select){

		echo $select;
	}

	for ($l = 0; $l < count($pieces); $l++) {

		$opt = $$pieces[$l];

		echo 'Array items :'.$opt;
	}



}*/


function  _shn_sn_add_gr_to_db(){

    $gr_id = $_REQUEST['group_id'];

	$owner = $_SESSION[sn][p_uuid];

	global $global;
	$db = $global['db'];


    if($_SESSION['sn']['group']['image']){
    	shn_image_to_db_ex($_SESSION['p_uuid'], $_SESSION['sn']['group']['image'], $_SESSION['sn']['group']['image_type'],$_SESSION['sn']['group']['image_height'],$_SESSION['sn']['group']['image_width'], null, 'group_image');
        //echo 'group image added successfully';
        //unset($_SESSION['a']);
    }


    $sql = "INSERT INTO sn_groups VALUES ('{$_SESSION['p_uuid']}','{$_SESSION['g_name']}','{$_SESSION['search_tags']}','{$_SESSION['category']}','{$_SESSION[sn][mem_username]}',now(),'{$_SESSION['description']}','{$_SESSION['ac_level']}')";
    $sql_ok = _shn_sn_execute($sql);
	if ($sql_ok) {

        	 add_confirmation(('Group Created successfully'));
	}
    $query   = "INSERT INTO sn_group_mem VALUES ('$owner','{$_SESSION['p_uuid']}')";
    $query = _shn_sn_execute($query);

    unset($_SESSION['p_uuid']);
    unset($_SESSION['sn']['group']['image']);
    unset($_SESSION['sn']['group']['image_type']);
    unset($_SESSION['sn']['group']['image_height']);
    unset($_SESSION['sn']['group']['image_width']);
    unset($_SESSION['g_name']);
    unset($_SESSION['search_tags']);
    unset($_SESSION['category']);
    unset($_SESSION['description']);
    unset($_SESSION['ac_level']);

	    ?>
    <div id="home">
        <h2><?php print (_('Thank you for creating a group in social network '));?></h2>

        <ul>
	        <li><p><font color="blue"> You are the administrator of this group,later you can grant admin priviledges to anyone u like </p></li>
            <li><p><font color="blue"> Anyone is free to join in your group</p></li>
            <li><p><font color="blue"> You will be notified when anyone joins in this group</p> </li>
        </ul>

    </div>

    <?php
    shn_form_fopen('sn_groups','sn','');
    ?>

    <h3><div align="center"><br> <?php shn_form_submit('Go to Group Home'); ?></div></h3>
    <?php

    shn_form_fclose();

}

function _shn_sn_show_summary(){



    shn_form_fopen('cr_groups','sn','');
    shn_form_fsopen('Confirm Details');
    shn_form_hidden(array('seq' => 'page3'));
	?> <div align = "center"><h3> Your group details </h3> <?php


	shn_show_thumb_url($_SESSION['p_uuid'],'','sn','group_img',true);


	echo '<br><br><br><b> Group Name : </b>' . $_SESSION['g_name'];
	echo '<br><br><b> Category : </b>' . $_SESSION['category'];
	echo '<br><br><b> Search Tags : </b>' . $_SESSION['search_tags'];
	echo '<br><br><b> Access Level : </b>' . $_SESSION['ac_level'];
	echo '<br><br><b> Description : </b>' . $_SESSION['description'];

	echo '<br><br>';

    shn_form_submit ('Confirm'," name='button'");
    shn_form_submit ('Edit'," name='button'");

    shn_form_fsclose();
    shn_form_fclose();

    ?> </div> <?php
}

?>



