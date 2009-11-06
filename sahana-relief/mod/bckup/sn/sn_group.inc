<?php
/**
 * SN groups
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
include_once $global['approot'] . '/mod/sn/lib_sn.inc';



if(isset($_REQUEST['seq'])) {
	switch($_REQUEST['seq']){
		case 'page2':
            {
               _shn_sn_show_gr_home();
               break;

            }

         case 'page3' :
           {
               _shn_sn_join_group();
               break;
           }
        case 'page4' :
           {
               _shn_sn_view_group();
               break;
           }
        case 'page5' :
           {
           	   $member_id = $_REQUEST['member_id'];
               _shn_sn_show_group_mem($member_id);
               break;
           }
       case 'page6' :
           {
               _shn_sn_edit_group();
               break;
           }
       case 'page7' :
           {

              $button = $_POST['button'];
              if($button == 'Save Changes'){
              	  _shn_sn_save_changes();
              }else{
                $gr_id = $_REQUEST['group_id'];
                _shn_sn_view_group($gr_id);
              }
               break;
           }
        case 'page8' :
           {
           	  $button = $_POST['button'];
              if($button == 'Write Now'){
              	  _shn_sn_write_to_mem();

              }else{
                   _shn_sn_view_group($_SESSION['group_id']);
              }
               break;
           }
        case 'page9' :
           {
               _shn_sn_show_file_upload_form();
               break;
           }
        case 'page10' :
           {
               _shn_sn_do_file_upload();
               break;
           }
       case 'page11' :
           {
               _shn_sn_show_uploaded_file();
               break;
           }
       case 'page12' :
           {
               _shn_sn_write_to_gr();
               break;
           }
        case 'page13' :
           {
            $button = $_POST['button'];
              if($button == 'Write to group'){
              	 _shn_sn_show_write_to_gr_form();
              }else{
                 _shn_sn_show_gr_home();
              }
               break;
           }
	}
}else{
     _shn_sn_show_gr_home();
}



function _shn_sn_show_gr_home(){
	 ?>

    <h2><center><?php print (('Social Network Groups')); ?></center></h2>
    <?php

     ?><a href="index.php?mod=sn&act=cr_groups"><?php echo  ('Create a New Group'); ?> </a><br><br> <?php
     //shn_show_thumb_url( ' bt2sp-80 ','database','sn','sn_groups',false);

     ?>



     <?php


    global $global;

    shn_form_fsopen('Group Details');
    //shn_form_hidden(array('seq' => '2'));

    $topic_id =$_REQUEST['topic_id'];

    $recent1 = _shn_sn_get_gr_info();
    $record = $recent1->fields['group_name'];

    if($record){

    	 ?>

    <h4>Available groups </h4><br>


    <div id ="result">
    <table width="800" border="0">
          <thead>
            <td><?php echo ("Group Image")?></td>
            <td><?php echo ("Group Name")?></td>
            <td><?php echo ("Group Category")?></td>
            <td><?php echo ("Theme")?></td>
          	<td><?php echo ("Access Level")?></td>
          	<td><?php echo ("Join Group")?></td>
            <td></td>

          </thead>


    <?php
    while (!$recent1->EOF) {
      // $post_text= null;

    ?>
    <div align="right">
          <tr>
          <td align="right"><?php  shn_show_thumb_url($recent1->fields['group_id'],'database','sn','group_img',false); ?>  </td>
          <td align="right"><?php echo $recent1->fields['group_name'].'<br>'.$recent1->fields['group_category']; ?>  </td>
          <td align="right"><?php echo $recent1->fields['group_category']; ?>  </td>
          <td align="right"><?php echo $recent1->fields['group_description']; ?>  </td>
          <td align="right"><?php echo $recent1->fields['group_access_level']; ?>  </td>

           <td>
           <a href="index.php?mod=sn&act=sn_groups&seq=page3&id=<?php echo $recent1->fields['group_id'] ?>">Join Group </a><br><br>
           <a href="index.php?mod=sn&act=sn_groups&seq=page4&id=<?php echo $recent1->fields['group_id'] ?>">View Group </a>
           </td>

           </tr>
     </div>
     <?php


       $recent1->MoveNext();

    }
    ?>
    </table>
    </div>

    <?php

    }else{

    	?> <h4> No groups available yet.. feel free to create your own group </h4><br><?php

    }
    shn_form_fsclose();

}




function _shn_sn_view_group($gr_id = null ){

    global $members, $db;
    shn_form_fopen('sn_groups','sn','');
    if($gr_id){
    	$recent1 = _shn_sn_get_gr_info($gr_id);
        $group_id = $gr_id;
    }else{
    	$recent1 = _shn_sn_get_gr_info($_REQUEST['id']);
    	$group_id = $_REQUEST['id'];
    }

    $mem_count = _shn_sn_get_gr_mem_count($group_id);

     $_SESSION['group_id'] = $group_id;
    while (!$recent1 ->EOF) {


    //$id = $recent1->fields['group_id'];
    $gr_name = $recent1->fields['group_name'] ;
    $gr_category = $recent1->fields['group_category'] ;
    $gr_des = $recent1->fields['group_description'] ;
    $se_tags =  $recent1->fields['group_key_word'] ;
    $ac_level = $recent1->fields['group_access_level'];
    $gr_owner = $recent1->fields['group_owner'];

    ?>
    <div align="center">
    <h2> This group is owned by <?php echo  $gr_owner ?> <h2>


    <?php echo '<br> Description : '.$gr_des ; ?><br><br>
    <table width="500" cellpadding="50">

        <tr><td rowspan="7" align="center"><?php shn_show_thumb_url($group_id,'database','sn','group_img',false);?> </td></tr>
        <tr> <td><?php echo 'Group Name : '.$gr_name ;?></td> </tr>
        <tr> <td><?php echo 'Catogery Name : '.$gr_category ?></td></tr>
        <tr> <td><?php echo 'Members : '. $mem_count ?></td></tr>
        <tr> <td><?php echo 'Access Level  : '.$ac_level ?></td></tr>

    </table>
    <?php
    $recent1->MoveNext();

    }



   if($gr_owner ==  $_SESSION[sn][mem_username] ){
    	 ?><br><br> <a href="index.php?mod=sn&act=sn_groups&seq=page6&id=<?php echo $group_id ?>&name=<?php echo $gr_name?>&category=<?php echo $gr_category?>&desc=<?php echo $gr_des?>&tags=<?php echo $se_tags?>&level=<?php echo $ac_level?>"><?php echo  ('Edit My Group'); ?> </a><br/> <?php
         ?><br> <br> </div>
    <?php


    $members = _shn_sn_get_gr_mem($group_id);

    if($members){
    ?>
    <div align="center">
    <br><h3><div align="left">Group Members</div> <div align="right"> <?php
    shn_form_hidden(array('seq' => 'page13','gr_id'=>$group_id));
    shn_form_submit('Write to group',"name='button'");
    shn_form_submit('<< Back',"name='button'");?></h3>

    <table width="300" border="0">
          <thead>
            <td><?php echo ("Image")?></td>
            <td><?php echo ("Name")?></td>
          </thead>
    <?php
    while (!$members ->EOF) {
          $username =  _shn_sn_get_username($members->fields['sn_mem_uuid']);?>
          <tr>
          <td align="right"><?php shn_show_thumb_url($members->fields['sn_mem_uuid'],'database','sn','mem_img',false); ?>  </td>
          <td align="left"><a href="index.php?mod=sn&act=sn_groups&seq=page5&id=<?php echo $members->fields['sn_mem_uuid']?>&gr_id="><?php  echo '<b> Name :</b>'.$username; ?></a> <br> <?php echo '<b> Interests :</b>'. $members->fields['sn_mem_interests']; ?>
          <br><a href="index.php?mod=sn&act=ad_view_mem&seq=page2&id=<?php echo $members->fields['sn_mem_uuid']?>">Remove</a>
          </td>
          <?php

       $members->MoveNext();
    }
    ?>
    </table>
    </div>
    <?php
    }else{
    	echo 'No members are in this group yet';
    }


 }else{
    ?><br> <br><h3><div align="left"> Group Members </div> <div align="right"><?php
    shn_form_hidden(array('seq' => 'page13','gr_id'=>$group_id));
    shn_form_submit('Write to group',"name='button'");
    shn_form_submit('<< Back',"name='button'");
     ?></div></h3><br>
     <?php

    $members = _shn_sn_get_gr_mem($group_id);

    if($members){
    ?>
    <div align="center">
    <table width="300" border="0">
          <thead>
            <td><?php echo ("Image")?></td>
            <td><?php echo ("Name")?></td>
          </thead>
    <?php
    while (!$members ->EOF) {
           $username =  _shn_sn_get_username($members->fields['sn_mem_uuid']);?>
          <tr>
          <td align="right"><?php shn_show_thumb_url($members->fields['sn_mem_uuid'],'database','sn','mem_img',false); ?>  </td>
          <td align="left"><a href="index.php?mod=sn&act=sn_groups&seq=page5&id=<?php echo $members->fields['sn_mem_uuid']?>&gr_id="><?php  echo '<b> Name :</b>'.$username; ?></a> <br> <?php echo '<b> Interests :</b>'. $members->fields['sn_mem_interests']; ?> </td>
          <?php

       $members->MoveNext();
    }
    ?>
    </table>
    </div>
    <?php
    }else{
    	echo 'No members are in this group yet';
    }

 }
//***********************************************list group members********************
  // <h3> Group Members </h3> <a href="index.php?mod=sn&act=sn_groups&seq=page9"> Upload a file </a>
   shn_form_fclose();
 }

function _shn_sn_join_group(){
    $check = false;
    $check1 = false;
	$gr_id = $_REQUEST['id'];
	$member_id = $_SESSION[sn][p_uuid];



    $sql1 = "SELECT sn_mem_uuid FROM sn_group_mem WHERE group_id='$gr_id'";
    $res1 = _shn_sn_execute($sql1);
    //$check = null;

   while (!$res1 ->EOF) {

       if ($res1->fields['sn_mem_uuid'] == $member_id){

		   //add_error('You have already joined in this group');
    	   //add_error('Try joining in a different group');
           $check = true;
        }
         $res1 -> MoveNext();

       }
       if($check){
       	   add_error('You have already joined in this group');
    	   add_error('Try joining in a different group');
       }
       else{
       	  $in_area= _shn_sn_get_interest_area($_SESSION[sn][p_uuid]);
          $gr_category= _shn_get_gr_category($gr_id);

          if($in_area != $gr_category){
        	   add_error('Your interest is diffrent from this group interest(category)');
    	       add_error('So you cant be a member of this group');
               $check1 = true;
          }
       }

    if($check1 || $check)	{

    	   display_errors();
    	  _shn_sn_show_gr_home();

    }else{
    	$sql = "INSERT INTO sn_group_mem VALUES ('{$_SESSION[sn][p_uuid]}','$gr_id')";
    	$query_ok = _shn_sn_execute($sql);
		if ($query_ok) {
	    	add_confirmation('You have joined Successfuly' );
		}
		_shn_sn_view_group($gr_id);

    }


   // _shn_sn_view_group($gr_id);

}

function _shn_sn_show_group_mem($mem_id = null){

	if($mem_id){
		$memb_id = $mem_id;
	}else{
		$memb_id = $_REQUEST['id'];
	}
    $fullname= _shn_sn_get_full_name($memb_id);
    $details = _shn_sn_get_mem_details($memb_id);
    $username = _shn_sn_get_username($memb_id);
    $friend_count = _shn_sn_get_fr_count();
    shn_form_fopen('sn_groups','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page8','member_id'=> $memb_id));
    ?>
    <div id="home">
    <h2><?php print (_('Member Profile')); ?></h2>
    <p>
    <?php
    while (!$details ->EOF) {

    ?>
    <div align="center">

    <table width="500" cellpadding="50">
        <tr><td rowspan="7" align="center"><?php shn_show_thumb_url($memb_id,'database','sn','mem_img',false);?> </td></tr>
        <tr><td><?php echo 'Full Name : '.$fullname ;?></td></tr>
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
    	 ?> <a href="index.php?mod=sn&act=my_prof&seq=page2"><?php echo  ('Edit My Profile'); ?> </a><br/><br> <?php
    	 shn_form_submit('<< Back',"name='button'");
    }else{
    	 ?><h2><center><?php echo 'Write something to '.$username ?></center></h2><br><br><?php
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



function _shn_sn_edit_group(){

    $id = null;
    $id = $_REQUEST['id'];
    $gr_name = $_REQUEST['name'];
    $category = $_REQUEST['category'];
    $desc = $_REQUEST['desc'];
    $tags = $_REQUEST['tags'];
    $level = $_REQUEST['level'];

        $array0['value'] = $gr_name;
    	$array1['value'] = $category;
    	$array2['value'] = $desc;
    	$array3['value'] = $tags;
    	$array4['value'] = $level;

       shn_form_fopen('sn_groups','sn',array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'));
       shn_form_fsopen(('Edit Group'));

       shn_form_hidden(array('seq' => 'page7','group_id' =>$id));


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

       	    shn_show_thumb_url($id ,'database','sn','group_img',false); ?> </div> <?php echo '<br><br><br><br>';

	   shn_form_upload(('Change Image'), "picture");

       shn_form_radio(  $radio_options,'Access Level','ac_level','',$array4);


	   shn_form_fsclose();
       ?> <div align='center' ><br>
	   <?php shn_form_submit('Save Changes',"name='button'");
	         shn_form_submit('<< Back',"name='button'");

	   ?> </div>
	   <?php
	   shn_form_fclose();
	   print '<br />';


}

function _shn_sn_save_changes(){

    $p_uuid = $_REQUEST['group_id'];
	$g_name = $_POST['g_name'];
    $category = $_POST['category'];
	$description = $_POST['description'];
	$search_tags = $_POST['search_tags'];

	$picture = $_POST['picture'];
    $ac_level = $_POST['ac_level'];


	 global $global;
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
		$uploadfile = $upload_dir . 'ori_' . $p_uuid . $ext;
		move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
		$desc_path = $upload_dir . 'thumb_' . $p_uuid . $ext;
		//resize the image size

		shn_image_resize($uploadfile, $desc_path, 100, 100);

	    }



	    $sql = "UPDATE sn_groups SET group_name ='$g_name',group_key_word='$search_tags',group_category='$category',group_description='$description',group_access_level='$ac_level' " .
	    		"where group_id='$p_uuid'";
	    $res = _shn_sn_execute($sql);

        if($image){
        	 $id = _shn_sn_get_image_id($p_uuid);
	         shn_image_to_db_ex('', $image,$image_type,$image_height,$image_width,$id, 'group_image');
        }
	    if ($res) {

        	 add_confirmation(('Group Updated successfully'));
	    }
        _shn_sn_show_gr_home();
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

    shn_form_fopen('sn_groups','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page5','member_id'=> $written_to));
    ?><div align="center">
    <h2><br>
    <?php echo shn_form_submit('Back',"name='button'"); ?>
    </h2></div> <?php
}


 function _shn_sn_show_file_upload_form(){

    shn_form_fopen('sn_groups','sn',array ('req_message' => true,'enctype' => 'enctype="multipart/form-data"'),'');
    shn_form_fsopen('Upload a file which would be usefull to members','');

    shn_form_hidden(array('seq'=>'page10','MAX_FILE_SIZE'=> '2000000'));
    ?>
    <table width="350" border="0" cellpadding="1" cellspacing="1" class="box">
        <tr>
        <td width="246">
        <input type="hidden" name="MAX_FILE_SIZE" value="2000000">
        <input name="userfile" type="file" id="userfile">
        </td>
		<td width="80"><input name="upload" type="submit" class="box" id="upload" value=" Upload "></td>
		</tr>
	</table>
 	<?php
 	shn_form_fsclose();
 	shn_form_fclose();

 }

function _shn_sn_do_file_upload(){


	if(isset($_POST['upload']) && $_FILES['userfile']['size'] > 0){
	$fileName = $_FILES['userfile']['name'];
	$tmpName  = $_FILES['userfile']['tmp_name'];
	$fileSize = $_FILES['userfile']['size'];
	$fileType = $_FILES['userfile']['type'];

	$fp      = fopen($tmpName, 'r');
	$content = fread($fp, filesize($tmpName));
	$content = addslashes($content);
	fclose($fp);

	if(!get_magic_quotes_gpc())
	{
   		$fileName = addslashes($fileName);
	}


	$query = "INSERT INTO upload (name, size, type, content ) ".
	"VALUES ('$fileName', '$fileSize', '$fileType', '$content')";

	$res = _shn_sn_execute($query);
	if($res){
		echo "<br>File $fileName uploaded<br>";

	}
	_shn_sn_show_uploaded_links();
	}

}

function _shn_sn_show_uploaded_links(){

	$query = "SELECT id, name FROM upload";
	$res = _shn_sn_execute($query);

	 while (!$res ->EOF) { ?>

	 	<a href="index.php?mod=sn&act=sn_groups&seq=page11&id=<?php echo $res->fields['id']?>"><?php echo $res->fields['name']?></a> <br>

	 	<?php
     $res->MoveNext();
	 }

}

function _shn_sn_show_uploaded_file(){

  	$file_id = $_REQUEST['id'];
    if(isset($file_id)) {

   $query = "SELECT name, type, size, content " .
         "FROM upload WHERE id = '$file_id'";
   $res = _shn_sn_execute($query);

   while (!$res ->EOF) {

   	 $name =$res->fields['name'];
     $type =$res->fields['type'];
   	 $size =$res->fields['size'];
   	 $content =$res->fields['content'];
     $res->MoveNext();
	 }


	header("Content-length: $size");
	header("Content-type: $type");
	header("Content-Disposition: attachment; filename=$name");

	echo $content;

	}

}

function _shn_sn_show_write_to_gr_form(){
	     $state = false;
	     $group_id = $_REQUEST['gr_id'];
	     $chk_gr_member = _shn_sn_chk_gr_member($group_id);

	     while (!$chk_gr_member->EOF) {
		    $mem_id = $chk_gr_member->fields['sn_mem_uuid'];

		    if($mem_id == $_SESSION[sn][p_uuid]){
			$state = true;
		    }
		    $chk_gr_member->MoveNext();
	    }

	    if($state){
		  ?> <div align="center"><h2><center><?php echo 'Write something to group'; ?></center></h2><br><br><?php

          shn_form_fopen('sn_groups','sn',array('req'=> 'true'));
          shn_form_hidden(array('seq'=>'page12','gr_id'=>$group_id));
    	  $array_options['cols'] = '70';
          $array_options['rows'] = '5';
          shn_form_textarea('','written_text','',$array_options);echo '<br>';
          shn_form_submit('Write Now',"name='button'");
          shn_form_submit('<< Back',"name='button'");
          shn_form_fclose();
          ?></div> <?php
	    }else{
	        clean_errors();
    	    add_error('You are not a member of this group');
    	    add_error('Hence you are not allowed to write for this group');
		    display_errors();
		    _shn_sn_view_group($group_id);
	    }

}


function _shn_sn_write_to_gr(){


	$written_text = $_POST['written_text'];
	$written_by = _shn_sn_get_username($_SESSION[sn][p_uuid]);
	$group_id = $_REQUEST['gr_id'];
    $result = _shn_sn_get_gr_mem_ids($group_id);

    while (!$result->EOF){
        $written_to = $result->fields['sn_mem_uuid'];
    	if($written_to != $_SESSION[sn][p_uuid]){
    		$sql = "INSERT INTO sn_mem_posts VALUES ('','$written_to','$written_text','$written_by',now())";
            $res = _shn_sn_execute($sql);
    	}

    $result->MoveNext();
    }


    if($res){
         add_confirmation('Written to group successfully');
    }
    shn_form_fopen('sn_groups','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page4','id'=> $group_id));
    ?><div align="center">
    <h2><br>
    <?php echo shn_form_submit('Back',"name='button'"); ?>
    </h2></div> <?php

}


?>












