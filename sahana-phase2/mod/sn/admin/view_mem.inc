<?php
/**
 * View member details
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

               _shn_sn_rem_mem();
               break;

            }

         case 'page3' :
           {
               _shn_sn_join_group();
               break;
           }
	}

}else {

    _shn_sn_show_all_mem();

}

function _shn_sn_show_all_mem(){

	$chk_mem = _shn_sn_count_members();
	if($chk_mem){
		//$fullname= _shn_sn_get_full_name($_SESSION[sn][p_uuid]);
		?>

        <div id="home">

        <h2><?php print (_('Social Network Members')); ?></h2>
        <div align="center">
        <table border='1'>
        <p>
        <?php
        $members = _shn_sn_get_all_members();
        while (!$members ->EOF) {
        	$fullname= _shn_sn_get_full_name($members->fields['sn_mem_uuid']);

         ?>
        <tr>
             <td><?php shn_show_thumb_url($members->fields['sn_mem_uuid'],'database','sn','mem_img',false)?></td>
             <td><a href="index.php?mod=sn&act=sn_groups&seq=page5&id=<?php echo $members->fields['sn_mem_uuid']?>"><?php echo $fullname ?></a><?php
             echo '<br>'.'Interests :'.$members->fields['sn_mem_interests'];?>
             <br><a href="index.php?mod=sn&act=ad_view_mem&seq=page2&id=<?php echo $members->fields['sn_mem_uuid']?>">Remove</a>
             </td>
        </tr>
        <?php
 	    $members->MoveNext();

        }
        ?></table></div> <?php
   }else{
  	  ?><div align="center">
      <h3>No members in SN yet</h3></div><?php

   }
}

function _shn_sn_rem_mem(){
	$id = $_REQUEST['id'];
	$sql = "DELETE FROM sn_members WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql);

	$sql = "DELETE FROM sn_group_mem WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql);

	$sql = "DELETE FROM sn_friend_list WHERE sn_mem_uuid='$id'";
	$res = _shn_sn_execute($sql);

    $sql = "DELETE FROM sn_friend_list WHERE friend_id='$id'";
	$res = _shn_sn_execute($sql);

    $sql = "DELETE FROM image WHERE x_uuid='$id'";
	$res = _shn_sn_execute($sql);


	if($res){

      add_confirmation(('Member Removed successfully'));
	}


}


