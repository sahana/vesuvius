<?php
include_once $global['approot'] . '/inc/handler_form.inc';
include_once $global['approot'] . '/inc/lib_uuid.inc';
include_once $global['approot'] . '/mod/sn/lib_sn.inc';
include_once ($global['approot'] . '/inc/lib_image.inc');


if(isset($_REQUEST['seq'])) {
    switch ($_REQUEST['seq']) {
	    case 'page2' :
		    {
		    	_shn_sn_show_ed_prof_form();
                 break;
		    }
		case 'page3' :
		    {
		    	if(_shn_sn_validate()){
		    		 _shn_sn_show_profile(true);

		    	}else{
		    		//_shn_sn_set_info();
		    		_shn_sn_update_prof();
		    		//_shn_sn_show_mem_profile();
		    	}

                 break;
		    }
	  case 'page4' :
		    {
		       $button = $_POST['button'];
              if($button == 'Write Now'){
              	  _shn_sn_write_to_mem();

              }else{
                  _shn_sn_show_profile('');
              }

              break;
		    }
	   case 'page5' :
		    {
		    	$id = $_REQUEST['id'];
		    	_shn_sn_show_mem_profile($id);
                 break;
		    }

    }


}else{
	_shn_sn_show_profile('');

}

/**
 * show particular users profile
 */


function _shn_sn_show_profile($errors = ''){

	if($errors){
     	display_errors();
	}

	$chk_info = _shn_sn_chk_mem_info($_SESSION[sn][p_uuid]);
	if($chk_info){
     	$details = _shn_sn_get_mem_details($_SESSION[sn][p_uuid]);
     	$friend_count = _shn_sn_get_fr_count($_SESSION[sn][p_uuid]);
     	$fullname= _shn_sn_get_full_name($_SESSION[sn][p_uuid]);

   	    while (!$details ->EOF) {
    		$email      = $details->fields['sn_mem_email'];
    		$dob        = $details->fields['sn_mem_dob'];
        	$in_area    =  $details->fields['sn_mem_interests'];
        	$details->MoveNext();
    	}


    ?>
    <div id="home">
    <h2><?php print (_('My Profile')); ?></h2><br>
    <div align="center">

     <table width="500" cellpadding="50">
         <tr><td rowspan="7" align="center"><?php shn_show_thumb_url($_SESSION[sn][p_uuid],'database','sn','mem_img',false);?> </td></tr>
         <tr><td><?php echo 'Full Name : '.$fullname;?></td></tr>
         <tr><td><?php echo 'Interest Area : '.$in_area ?></td></tr>
         <tr><td><?php echo 'Date of Birth  : '.$dob ?></td></tr>
         <tr><td><?php echo 'E-mail : '.$email ?></td></tr>
         <tr><td><?php echo 'Friends : '.$friend_count ?></td></tr>
      </table>
      <br> <br>
      <a href="index.php?mod=sn&act=my_prof&seq=page2"><?php echo  ('Edit My Profile'); ?> </a><br/>

    <?php
        _shn_sn_show_mem_posts();

    }else{
     	?><div align="center">
     	<h3> You have not registered in Social Network yet</h3><br>
     	<a href="index.php?mod=sn&act=me_reg"><?php echo  ('Register Now'); ?> </a></div><?php
	}

}

function _shn_sn_show_mem_posts(){?>
	  </div>
      <h3> Recieved posts </h3> <br>
      <div align="center">
      <table width="300" border="0"><?php
      $chk_posts = _shn_sn_chk_mem_posts($_SESSION[sn][p_uuid]);
      if($chk_posts){
    	   $posts = _shn_sn_get_mem_posts($_SESSION[sn][p_uuid]);
    	   while (!$posts ->EOF) {

    	   $text = $posts->fields['written_text'];
    	   $person = $posts->fields['written_person'];
           $time = $posts->fields['written_time'];
           ?>
          <tr>
          <td align="right"><?php echo $text ?>  </td>
          <td align="right"><a href="index.php?mod=sn&act=my_prof&seq=page5&name=<?php echo $person ?>"><?php echo $person.'</a><br>'.$time; ?>
          </td></tr>

          <?php
          $posts->MoveNext();
          }

          ?></table> </div><?php

      }else{
   	     ?><h3> No posts added yet </h3>  <?php
      }
}


function _shn_sn_show_ed_prof_form()
{
	?>
    <div id="home">
    <h2><?php print (_('Edit Your Details')); ?></h2>
    </div>
    <?php

    $details = _shn_sn_get_mem_details($_SESSION[sn][p_uuid]);

    while(!$details->EOF){
    	$email      = $details->fields['sn_mem_email'];
    	$dob        = $details->fields['sn_mem_dob'];
    	$in_area    = $details->fields['sn_mem_interests'];
    	$expr       = $details->fields['sn_mem_experience'];
    	$oth_info   = $details->fields['sn_mem_other_info'];
    	$country    = $details->fields['sn_mem_country'];
    	$city       = $details->fields['sn_mem_city'];
       //$firstname = $details->fields['sn_mem_firstname'];


    	$details->MoveNext();
    }


    $fullname= _shn_sn_get_full_name($_SESSION[sn][p_uuid]);

    shn_form_fopen('my_prof','sn',array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));
    shn_form_hidden(array ('seq' => 'page3'));

    shn_form_fsopen(_('General Details'));
    $extra_opts['req'] = true;
    $extra_opts['value'] = $fullname;
    shn_form_text(_('First Name'),'f_name','', $extra_opts);



    ?><br><div align="center"> <?php
    shn_show_thumb_url($_SESSION[sn][p_uuid],'database','sn','mem_img',false);?><br><br> <br></div> <?php
	shn_form_upload(_('Change Picture'),'picture');


	$extra_opts['value'] = $email;
	$extra_opts['req'] = false;
    shn_form_text(_('E-Mail'),'email','', $extra_opts);

    $extra_opts['value'] = $dob;
    shn_form_date(_("Date of Birth"),'dob', $extra_opts);

    shn_form_fsclose();

    shn_form_fsopen(_('Strategic Information (optional)'));

    $extra_opts['value'] = $in_area;
    shn_form_text(_('Interest Area'),'in_area','', $extra_opts);

    $extra_opts['value'] = $expr;
    shn_form_text(_('Experience'),'expr','', $extra_opts);

    $extra_opts['value'] = $oth_info;
    shn_form_textarea(_('Other infomation'),'oth_info','', $extra_opts);

    shn_form_fsclose();

    shn_form_fsopen(_('Location (optional)'));

    $extra_opts['value'] = $country;
    shn_form_text(_('Country'),'country','', $extra_opts);

    $extra_opts['value'] = $city;
    shn_form_text(_('City'),'city','', $extra_opts);

    shn_form_fsclose();

    shn_form_submit(_('Save Changes'),"name='next'");

    shn_form_fclose();
}



function _shn_sn_validate()
{
	clean_errors();

	$error_flag = false;
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
 * update database
 */
function _shn_sn_update_prof(){
	  global $global;


        $image = null;
        $image_type ='';
        $image_height = '';
		$image_width = '';


		if ($_FILES['picture']['error'] != UPLOAD_ERR_NO_FILE) {
		$info = getimagesize($_FILES['picture']['tmp_name']);
		//check the image type
		if ($info) {
			list ($ignore, $ext) = split("\/", $info['mime']);

			//check for save handler

			$size = filesize($_FILES['picture']['tmp_name']);
			$pic = fread(fopen($_FILES['picture']['tmp_name'], "r"), $size);
			$image = $pic;
			$image_type = $ext;
			$image_height = $info[1];
			$image_width = $info[0];
		}


		$ext = '.' . $ext;
		$upload_dir = $global['approot'] . 'www/tmp/';
		$uploadfile = $upload_dir . 'ori_' .$_SESSION[sn][p_uuid] . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $_SESSION[sn][p_uuid] . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);

		}





	    $sql = "UPDATE sn_members SET" .
	    		" sn_mem_email ='{$_POST['email']}', sn_mem_dob ='{$_POST['dob']}'" .
	    		", sn_mem_interests ='{$_POST['in_area']}', sn_mem_experience ='{$_POST['expr']}'" .
	    		", sn_mem_other_info ='{$_POST['oth_info']}', sn_mem_country ='{$_POST['country']}'" .
	    		", sn_mem_city ='{$_POST['city']}' WHERE sn_mem_uuid = '{$_SESSION[sn][p_uuid]}'";
	    $res = _shn_sn_execute($sql);


	     $sql = "UPDATE  person_uuid SET full_name='{$_POST['f_name']}' WHERE p_uuid='{$_SESSION[sn][p_uuid]}' ";
         $res = _shn_sn_execute($sql);

        if($image){
        	$id = _shn_sn_get_image_id($_SESSION[sn][p_uuid]);
	        shn_image_to_db_ex('', $image,$image_type,$image_height,$image_width,$id, 'mem_image');

        }

        if ($res) {
	        add_confirmation(('Profile updated successfully'));
	        _shn_sn_show_profile();
	    }


}
/**
 * show particular users members profile
 */
function _shn_sn_show_mem_profile($id = null){
    if($id){
    	$memb_id = $id;
    }else{
    	$mem_name = $_REQUEST['name'];
        $memb_id = _shn_get_mem_id($mem_name);
    }

	$details = _shn_sn_get_mem_details($memb_id);
    $friend_count = _shn_sn_get_fr_count($memb_id);
    shn_form_fopen('my_prof','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page4','member_id'=> $memb_id));
    ?>
    <div align="center">
    <h2><?php print (_('Member Profile')); ?></h2>
    <p>
    <?php
    while (!$details ->EOF) {

    ?>
    <div align="center">

    <table width="500" cellpadding="50">
        <tr><td rowspan="7" align="center"><?php shn_show_thumb_url($memb_id,'database','sn','mem_img',false);?> </td></tr>
        <tr><td><?php echo 'First Name : '.$details->fields['sn_mem_firstname'] ;?></td></tr>
        <tr><td><?php echo 'Last Name : '.$details->fields['sn_mem_lastname'] ?></td></tr>
        <tr><td><?php echo 'Interest Area : '.$details->fields['sn_mem_interests'] ?></td></tr>
        <tr><td><?php echo 'Date of Birth  : '.$details->fields['sn_mem_dob'] ?></td></tr>
        <tr><td><?php echo 'E-mail : '.$details->fields['sn_mem_email'] ?></td></tr>
        <tr><td><?php echo 'Friends : '.$friend_count ?></td></tr>
    </table>
    <br> <br>
    <?php
       	 $details->MoveNext();
    }
    if($memb_id ==  $_SESSION[sn][p_uuid] ){
    	 ?> <a href="index.php?mod=sn&act=my_prof&seq=page2"><?php echo  _t('Edit My Profile'); ?> </a><br/><br> <?php
    	 shn_form_submit('<< Back',"name='button'");
    }else{
    	 ?><h2><center><?php echo 'Write something to '.$mem_name ?></center></h2><br><br><?php
    	  $array_options['cols'] = '70';
          $array_options['rows'] = '5';
          shn_form_textarea('','written_text','',$array_options);echo '<br>';
          shn_form_submit('Write Now',"name='button'");
          shn_form_submit('<< Back',"name='button'");
    }
    shn_form_fsclose();
    shn_form_fclose();
    ?>


    </div>
    </p>
    </div>
    <?php
}



function _shn_sn_write_to_mem(){


	$written_text = $_POST['written_text'];
	$written_by = _shn_sn_get_username($_SESSION[sn][p_uuid]);
	$written_to = $_REQUEST['member_id'];
	$sql = "INSERT INTO sn_mem_posts VALUES ('','$written_to','$written_text','$written_by',now())";
    $res = _shn_sn_execute($sql);
    if ($res) {

       add_confirmation(('Post Written Successfully'));
	}

    shn_form_fopen('my_prof','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page5','id'=>$written_to));
    ?><div align="center">
    <h2><br>
    <?php echo shn_form_submit('Back',"name='button'"); ?>
    </h2></div> <?php
}







  
