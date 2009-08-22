<?php
/**
 *lib in SN
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

function _shn_sn_execute($sql)
{


	global $global;

	$db = $global['db'];

	$res = $db->Execute($sql);
	if ($res) {
	    return $res;
	} else {
		return false;
	}
}


function _shn_sn_limit_execute($sql,$items=6)
{
	global $global;

	$rs = $global['db']->SelectLimit($sql,$items);

    if ($rs) {
	    return $rs;
	} else {
		return false;
	}
}


function _shn_get_stored_topics(){
	$sql = "SELECT topic_id,topic_title,date_format(topic_create_time, '%b %e %Y at %r') as fmt_topic_create_time," .
			"topic_owner FROM sn_forum_topics order by topic_create_time desc";
	$res = _shn_sn_execute($sql);
    return $res;
}

function _shn_get_num_posts($topic_id){
	$sql = " select count(post_id) as num_posts from sn_forum_posts where topic_id='$topic_id'";
	$res = _shn_sn_execute($sql)->fields['num_posts'];
	//$details['count'] = $res->fields['number'];
	//$num_posts = mysql_result($res,0,'count(post_id)');

	return $res;


}

function _shn_sn_get_friends($interest= ''){// using this f_id select friend list****************8
    $sql = "SELECT * FROM sn_members WHERE sn_mem_interests='$interest'";
    $res = _shn_sn_execute($sql);
    return $res;
}

function _shn_sn_get_users_list(){

    $sql = "SELECT * FROM sn_members";
    $res = _shn_sn_execute($sql);
    return $res;


}

function _shn_sn_get_posts($topic_id){
	$sql = "SELECT post_id,post_text,date_format(post_create_time,'%b %e %Y at %r') as fmt_post_create_time,".
			"post_owner from sn_forum_posts WHERE topic_id='$topic_id'";
    // $sql = "select * from sn_forum_posts where topic_id='$topic_id'";

    $res = _shn_sn_execute($sql);
    return $res;


}

function _shn_get_post_owners_img(){



}

function _shn_sn_ck_my_friends_availability($id = null){
    $sql = "SELECT count(friend_id) as num FROM sn_friend_list WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;
}

function _shn_sn_chk_mem_posts($id = null){
    $sql = "SELECT count(written_id) as num FROM sn_mem_posts WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;
}

function _shn_sn_chk_mem_info($id = null){
    $sql = "SELECT count(sn_mem_interests) as num FROM sn_members WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;

}

function _shn_sn_ck_friends_availability($interst = null){
    $sql = "SELECT count(sn_mem_interests) as num FROM sn_members WHERE sn_mem_interests='$interst'";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;
}


/**
 * check wheather the username is already in users table before
 * registration.
 */
function _shn_sn_chk_usrname($uname = null){


	$sql = "SELECT  p_uuid FROM users where user_name='$uname'";
    $res = _shn_sn_execute($sql)->fields['p_uuid'];

    $sql = "SELECT  sn_mem_uuid FROM sn_members where sn_mem_username='$uname'";
    $res1 = _shn_sn_execute($sql)->fields['sn_mem_uuid'];


	if ($res != null || $res1 != null){
		return true;

	}

}
function _shn_sn_chk_gr_member($group_id= null){
	$sql = "SELECT  sn_mem_uuid FROM sn_group_mem where group_id='$group_id'";
    $res = _shn_sn_execute($sql);
	return $res;
}

function _shn_sn_get_gr_info($id = null){

	if($id == null){
	    $sql = "SELECT * FROM sn_groups";
	    $res = _shn_sn_execute($sql);
	}else{
		$sql = "SELECT * FROM sn_groups WHERE group_id = '$id'";
		$res = _shn_sn_execute($sql);
	}
	return $res;

}

function _shn_sn_get_mem_posts($member_id = null){
    $sql = "SELECT * FROM sn_mem_posts WHERE sn_mem_uuid='$member_id'";
	$res = _shn_sn_execute($sql);

	return $res;

}

function _shn_get_mem_id($mem_name = null){

	$sql = "SELECT p_uuid FROM users where user_name='$mem_name'";
	$res = _shn_sn_execute($sql)->fields['p_uuid'];

	return $res;


}

function _shn_sn_get_my_friends($id = null){
    $sql = "SELECT friend_id FROM sn_friend_list WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql);
	return $res;
}

function _shn_sn_get_username($user_id = null){

    $sql = "SELECT user_name FROM users where p_uuid='$user_id'";
	$res = _shn_sn_execute($sql)->fields['user_name'];

 return $res;

}

function _shn_sn_chk_my_fr_list($id = null){
    $sql = "SELECT friend_id FROM sn_friend_list where sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql);
    return $res;
}
function _shn_sn_count_fr_list($fr_id= null){
	$sql = "SELECT count(friend_id) as num FROM sn_friend_list WHERE sn_mem_uuid='$fr_id'";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;

}
function _shn_sn_count_topic(){
    $sql = "SELECT count(topic_id) as num FROM sn_forum_topics";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;


}

function _shn_sn_count_posts($id=null){
    $sql = "SELECT count(post_id) as num FROM sn_forum_posts WHERE topic_id='$id'";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;
}


function _shn_sn_chk_my_fr_list_to_ap($id = null){
    $sql = "SELECT sn_mem_uuid FROM sn_friend_list where friend_id='$id'";
	$res = _shn_sn_execute($sql);
    return $res;
}

function _shn_sn_get_full_name($id = null){

    $sql = "SELECT full_name FROM person_uuid WHERE p_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['full_name'];

    return $res;
}


function _shn_sn_get_gr_mem($group_id){
     $sql = "select sn_mem_interests,sn_mem_uuid from sn_members where sn_mem_uuid in (select sn_mem_uuid from sn_group_mem where group_id='$group_id')";

	 //$sql ="select sn_mem_uuid from sn_group_mem where group_id='$group_id'";
	 $res = _shn_sn_execute($sql);

     return $res;
}

function _shn_sn_get_image_id($id= null){

	$sql = "SELECT image_id FROM image WHERE x_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['image_id'];

 return $res;
}

function _shn_sn_get_gr_mem_ids($id= null){

	$sql = "SELECT sn_mem_uuid FROM sn_group_mem WHERE group_id='$id'";
	$res = _shn_sn_execute($sql);

 return $res;
}

function _shn_sn_wr_to_db(){

	$sql = "INSERT INTO sn_members(sn_mem_uuid,sn_mem_username,sn_mem_password,sn_mem_firstname) VALUES ('{$_SESSION['tmp_pwd']}','{$_POST['username']}','{$_POST['password']}','{$_POST['firstname']}')";

}

function  _shn_sn_validate_login($uname=null,$pwd=null){
   $sql = "SELECT sn_mem_password FROM sn_members where sn_mem_username='$uname'";
   $res = _shn_sn_execute($sql)->fields['sn_mem_password'];

   if($res != null){
       if($res == $pwd){
   	 	   return false;
   	   }
   	   else {
   	 	   return true;
   	   }
   } else{
       return true;
   }
}


function _shn_sn_get_details($uname=''){

	$sql = "SELECT * FROM sn_members where sn_mem_username='$uname'";
	$res = _shn_sn_execute($sql);

	return $res;

}


function _shn_sn_get_mem_details($uid=''){
    //$sql = "SELECT * FROM person_details where p_uuid='$uid'";
	$sql = "SELECT * FROM sn_members where sn_mem_uuid='$uid'";
	$res = _shn_sn_execute($sql);

	return $res;

}

function _shn_sn_get_all_members(){
    $sql = "SELECT * FROM sn_members";
	$res = _shn_sn_execute($sql);

	return $res;

}

function _shn_sn_get_gr_mem_count($id = null){
    $sql = "SELECT count(sn_mem_uuid) as num FROM sn_group_mem WHERE group_id='$id'";
	$res = _shn_sn_execute($sql)->fields['num'];

	return $res;

}

function _shn_sn_get_fr_count($id = null){

    $sql = "SELECT count(friend_id) as num FROM sn_friend_list WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['num'];

	return $res;

}

function _shn_sn_count_members(){
    $sql = "SELECT count(sn_mem_uuid) as num FROM sn_members";
	$res = _shn_sn_execute($sql)->fields['num'];
	return $res;
}

function _shn_sn_chk_user_in_sn($id = null){

    $sql = "SELECT sn_mem_interests FROM sn_members WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['sn_mem_interests'];
	return $res;
}


function _shn_sn_get_disease_list(){

    $sql = "SELECT dis_name FROM diseases";
	$res = _shn_sn_execute($sql);
	return $res;

}

function _shn_get_gr_category($gr_id = null){

    $sql = "SELECT group_category FROM sn_groups WHERE group_id='$gr_id'";
	$res = _shn_sn_execute($sql)->fields['group_category'];
	return $res;

}

function _shn_sn_get_interest_area($id= null){

    $sql = "SELECT sn_mem_interests FROM sn_members where sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql)->fields['sn_mem_interests'];
	return $res;

}


function _shn_sn_get_level($uname=''){
  $sql = "SELECT ad_level from sn_admin where ad_username='$uname'";
  $result = _shn_sn_execute($sql)->fields['ad_level'];

  return $result;
}


