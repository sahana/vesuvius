<?php
/**Admin controller of the Press and Media Module
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue, Miyuru Daminda, Reka Sandaruwan, Chamara Caldera, Nishantha Pradeep
 * @copyright Respective Authors
 * @package    sahana
 * @subpackage pnm
 *
 * Developed during Sahana 2009 as a tribute.
 */
function shn_pnm_adm_default(){

	_shn_pnm_adm_head();
}

function _shn_pnm_adm_head(){
	echo "<h2>"._t("Press and Media Module Administration")."</h2>";

	shn_tabmenu_open();
	shn_tabmenu_item('adm_upload_video',_t('Upload Videos'),'pnm');
	shn_tabmenu_item('adm_delete_video',_t('Delete Videos'),'pnm');
	shn_tabmenu_item('adm_upload_image',_t('Upload Images'),'pnm');
	shn_tabmenu_item('adm_add_news',_t('Add News'),'pnm');
	shn_tabmenu_close();
}

function shn_pnm_adm_upload_video(){
	global $global;
	$db = $global['db'];

	$tabid = $_REQUEST['tabid'];


	if($_POST['submit']==null){
		_shn_pnm_adm_head();
		echo "<h3>"._t("Upload Videos")."</h3>";
		//show form
		shn_form_fopen('adm_upload_video','pnm',array('enctype'=>'enctype="multipart/form-data"'));
		shn_form_fsopen();
		shn_form_hidden(array('tabid'=>$tabid));
		shn_form_text(_t('Video Title'),'video_title','',array('req'=>true));
		shn_form_textarea(_t('Video Description'),'video_descr');
		shn_form_upload(_t('Video File to Upload'),'video_file');
		shn_form_fsclose();
		shn_form_submit(_t('Upload'),'name="submit"');
		shn_form_fclose();
	}else{
		// upload.

		$file_name = $_FILES['video_file']['tmp_name'];
		$errors = false;
		if(preg_match('/video\/.*/i',$_FILES['video_file']['type'])==0){
			add_error(_t("Please upload a video file"));
			$errors = true;
		}
		if($_POST['video_title']==null || strlen(trim($_POST['video_title']))==0){
			add_error(_t('Please enter a title'));
			$errors = true;
		}
		if($errors==false){
			$mime_type = $_FILES['video_file']['type'];
			$media_type = "VIDEO";
			$media_id = $db->GenID('seq_pnm_media');
			$media_descr = $_POST['video_descr'];
			$media_title = $_POST['video_title'];
			$date = date('Y-m-d H:i:s');
			$ext = explode('.',$_FILES['video_file']['name']);
			$ext = $ext[(count($ext)-1)];
			$path = 'res/media_'.$media_id.'.'.$ext;
			$move_to = $global['approot'].'www/'.$path;

			$query = "INSERT INTO pnm_media(media_id,media_title,media_description,media_type,mime_type,media_path,date) VALUES (?,?,?,?,?,?,?)";
			$db->StartTrans();
			$ret = move_uploaded_file($_FILES['video_file']['tmp_name'],$move_to);
			if($ret==false){
				$db->FailTrans();
			}
			$db->Execute($query,array($media_id,$media_title,$media_descr,$media_type,$mime_type,$path,$date));
			$failed = $db->HasFailedTrans();

			$db->CompleteTrans();
			if($failed){
				add_error(_t('Video upload failed'));
			}else{
				add_confirmation(_t('Video uploaded'));
			}
			$_POST = null;
			$_FILES = null;
			shn_pnm_adm_upload_video();



		}
	}
}

function shn_pnm_adm_delete_video(){
	global $global;
	$db = $global['db'];
	$tabid = $_REQUEST['tabid'];
	_shn_pnm_adm_head();
	echo "<h3>"._t("Delete Videos")."</h3>";
	$page = isset($_REQUEST['page'])?$_REQUEST['page']:1;

	if(isset($_POST['submit'])){
		// show confirmation dialog
		shn_form_fopen('adm_delete_video','pnm',array('req_message'=>false));
		shn_form_hidden(array('page'=>$page,'media_id'=>$_POST['media_id'],'tabid'=>$tabid));
		shn_form_fsopen(_t("Confirm Delete"));
		echo "Are you sure you need to delete this video? Please not that this action cannot be undone.";
		shn_form_fsclose();
		shn_form_submit(_t('No'));
		echo "&nbsp;&nbsp;";
		shn_form_submit(_t('Yes'),'name="delete"');
		shn_form_fclose();
	}else if (isset($_POST['delete'])){
		$query = "SELECT * FROM pnm_media WHERE media_id=?";
		$res = $db->Execute($query,array($_POST['media_id']));
		$no_errors = true;
		$path = $res->fields['media_path'];
		$no_errors = unlink($global['approot'].'www/'.$path);
		if($no_errors){
			$db->StartTrans();
			$query2 = "DELETE FROM pnm_media WHERE media_id=?";
			$db->Execute($query2,array($_POST['media_id']));
			$no_errors &= ($db->HasFailedTrans()==false);
			$db->CompleteTrans();
		}
		if($no_errors){
			add_confirmation(_t("Video deleted successfully"));
		}else{
			add_error(_t("Video delete failed due to an unknown error"));
		}
		_shn_pnm_delete_video_form($page);
	}else{
		_shn_pnm_delete_video_form($page);
	}
}

function _shn_pnm_delete_video_form($page = 1){
	global $global;
	$db = $global['db'];
	$tabid = $_REQUEST['tabid'];
	$rpp = 15;

	$count_query = "SELECT COUNT(*) AS c FROM pnm_media WHERE media_type='VIDEO'";
	$res = $db->Execute($count_query);
	$count = $res->fields['c'];

	if($count==0){
		echo "<em>"._t("No videos found")."</em>";
	}else{

		$record_query = "SELECT * FROM pnm_media WHERE media_type='VIDEO'";
		$res = $db->SelectLimit($record_query,$rpp,($page-1)*$rpp);
		while($row = $res->FetchRow()){
			shn_form_fopen('adm_delete_video','pnm',array('req_message'=>false));
			echo "<div>";
			echo "<h4>".$row['media_title']."</h4>";
			echo "<em>".$row['date']."</em><br/>";
			echo "<p>".$row['media_description']."</p>";
			shn_form_hidden(array('media_id'=>$row['media_id'],'page'=>$page,'tabid'=>$tabid));
			shn_form_submit(_t('Delete'),'name="submit"');
			echo "</div>";
			shn_form_fclose();
		}
		echo "<br/><hr/>";
		$pg_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
		echo _t("Pages : ");
		for($i=1;$i<$pg_count;$i++){
			echo "<a href='index.php?mod=pnm&act=adm_delete_video&page=$i&tabid=$tabid'>".$i."</a>&nbsp;&nbsp;";
		}
	}

}


