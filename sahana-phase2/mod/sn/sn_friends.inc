<?php
/**
 * SN friends Page
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
include_once ($global['approot'] . '/inc/lib_image.inc');

if(isset($_REQUEST['seq'])) {
	switch($_REQUEST['seq']){
		case 'page2':
            {
               _shn_sn_show_fr_details();
               break;

            }
       case 'page3':
            {


           	  $button = $_POST['button'];
              if($button == 'Write Now'){
              	  _shn_sn_write_to_mem();

              }else{
                  _shn_sn_show_fr_list();
              }
               break;
           }
       case 'page4':
            {
               _shn_sn_show_fr_list();
               break;

            }
       case 'page5':
            {

               _shn_sn_add_fr_to_db();
               _shn_sn_show_fr_list();
               break;

            }
       case 'page6':
            {
               _shn_sn_approve_as_friend();
               _shn_sn_show_fr_list();
               break;

            }
	}
}else{
_shn_sn_show_fr_list();

}
function _shn_sn_show_fr_list(){
?>

<div id="home">

<h2><?php print (_('People who have similar interest to you ')); ?></h2>
<div align="center">
    <table border='1'>
<p>
<?php
 $interest = _shn_sn_get_interest_area($_SESSION[sn][p_uuid]);

 $chk_availability = _shn_sn_ck_friends_availability($interest);

 if($chk_availability>1){
 	 $friends = _shn_sn_get_friends($interest);

    while (!$friends ->EOF) {
 	    if($friends->fields['sn_mem_uuid'] != $_SESSION[sn][p_uuid]){

 		$username =  _shn_sn_get_username($friends->fields['sn_mem_uuid']);
        ?>
        <tr>
        <td><?php shn_show_thumb_url($friends->fields['sn_mem_uuid'],'database','sn','mem_img',false)?></td>
        <td><?php  echo '<b> Name :</b>'.$username; ?></a><br>
           Interests :<?php echo $friends->fields['sn_mem_interests'];?><br>
        <a href="index.php?mod=sn&act=sn_friend&seq=page5&id=<?php echo $friends->fields['sn_mem_uuid']?>"><font color="red"> Add as a friend</font></a><br>
        <a href="index.php?mod=sn&act=sn_friend&seq=page6&id=<?php echo $friends->fields['sn_mem_uuid']?>">Approve as a friend</a>
        </td>
        </tr><?php
 	    }
      $friends->MoveNext();

   }

   ?>
   </table>
   </div>
   <?php   _shn_sn_show_my_fr_list();

   }else{
  	   ?> <h3> No people interested in your area yet </h3> <?php
   }
}

function _shn_sn_show_my_fr_list(){

  $check_friends = _shn_sn_ck_my_friends_availability($_SESSION[sn][p_uuid]);

  if ($check_friends){
     ?>
    <div align="center"><br>
    <h3><?php print (('My Friends ')); ?></h3>
    <table border='1'>
    <p><?php
     //$interest = _shn_sn_get_interest_area($_SESSION[sn][p_uuid]);
     $friends = _shn_sn_get_my_friends($_SESSION[sn][p_uuid]);

    while (!$friends ->EOF) {

 	    if($friends->fields['friend_id'] != $_SESSION[sn][p_uuid]){
            $username =  _shn_sn_get_username($friends->fields['friend_id']);?>
            <tr>
            <td><?php shn_show_thumb_url($friends->fields['friend_id'],'database','sn','mem_img',false)?></td>
            <td><a href="index.php?mod=sn&act=sn_friend&seq=page2&id=<?php echo $friends->fields['friend_id']?>&gr_id="><?php  echo '<b> Name :</b>'.$username; ?></a><br>
            </td>
            </tr><?php
 	     }
         $friends->MoveNext();

    }?>
    </table>
    </div><?php
  }else{
     ?>
     <div align="center"><br>
     <h3><?php print (_('You have no friends yet')); ?></h3> <?php

  }




}

function _shn_sn_add_fr_to_db(){
    $state0 = false;
    $state1 = false;
	$fr_id = $_REQUEST['id'];


	$chk_friend = _shn_sn_chk_my_fr_list($_SESSION[sn][p_uuid]);

	while (!$chk_friend->EOF) {
		$friend_id = $chk_friend->fields['friend_id'];
		if($friend_id == $fr_id){
			$state0 = true;
		}
		$chk_friend->MoveNext();
	}

	if($state0){
		clean_errors();
    	add_error('You have already added this friend');
    	add_error('Try adding a different friend');
		display_errors();

	}else{
		$sql = "INSERT INTO sn_friend_list VALUES ('{$_SESSION[sn][p_uuid]}','$fr_id')";
        $sql = _shn_sn_execute($sql);
	    if ($sql) {

        	 add_confirmation(('Friend added successfully'));
	    }
	}
}
function _shn_sn_approve_as_friend(){

    $state = false;
	$fr_id = $_REQUEST['id'];

	$chk_fr_list = _shn_sn_count_fr_list($fr_id);

	if($chk_fr_list){
	    $chk_friend = _shn_sn_chk_my_fr_list($fr_id);
   	    while (!$chk_friend->EOF) {
		    $mem_id = $chk_friend->fields['friend_id'];

		    if($mem_id == $_SESSION[sn][p_uuid]){
			$state = true;
		    }
		    $chk_friend->MoveNext();
	    }

	    if($state){
		    clean_errors();
    	    add_error('You are already a  friend');
    	    add_error('Try approving a different friend');
		    display_errors();

	    }else{
	        $sql = "INSERT INTO sn_friend_list VALUES ('$fr_id','{$_SESSION[sn][p_uuid]}')";
            $sql = _shn_sn_execute($sql);
	        if ($sql) {
        	   add_confirmation(('Approved as a friend'));
	        }
	    }

	}else{
		    $sql = "INSERT INTO sn_friend_list VALUES ('$fr_id','{$_SESSION[sn][p_uuid]}')";
            $sql = _shn_sn_execute($sql);
	        if ($sql) {
        	   add_confirmation(('Approved as a friend'));
	        }
	}



}


function _shn_sn_show_fr_details($mem_id = null){

	if($mem_id){
		$memb_id = $mem_id;
	}else{
		$memb_id = $_REQUEST['id'];
	}
    $fullname= _shn_sn_get_full_name($memb_id);
    $details = _shn_sn_get_mem_details($memb_id);
    $username = _shn_sn_get_username($memb_id);
    $friend_count = _shn_sn_get_fr_count();
    shn_form_fopen('sn_friend','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page3','member_id'=>$memb_id));
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
        <tr><td><?php echo 'Full  Name : '.$fullname ;?></td></tr>
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
function _shn_sn_write_to_mem(){


	$written_text = $_POST['written_text'];
	$written_by = _shn_sn_get_username($_SESSION[sn][p_uuid]);
	$written_to = $_REQUEST['member_id'];
	$sql = "INSERT INTO sn_mem_posts VALUES ('','$written_to','$written_text','$written_by',now())";
    $res = _shn_sn_execute($sql);
    if ($res) {

       add_confirmation(('Post Written Successfully'));
	}

    shn_form_fopen('sn_friend','sn',array('req'=> 'true'));
    shn_form_hidden(array('seq'=>'page4'));
    ?><div align="center">
    <h2><br>
    <?php echo shn_form_submit('Back',"name='button'"); ?>
    </h2></div> <?php
}


?>

