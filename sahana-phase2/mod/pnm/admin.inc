<?php
function shn_pnm_adm_default(){

	_shn_pnm_adm_head();
}

function _shn_pnm_adm_head(){
	echo "<h2>"._t("Press and Media Module Administration")."</h2>";

	shn_tabmenu_open();
	shn_tabmenu_item('adm_upload_video',_t('Upload Videos'),'pnm');
	shn_tabmenu_item('adm_upload_image',_t('Upload Images'),'pnm');
	shn_tabmenu_item('adm_add_news',_t('Add News'),'pnm');
	shn_tabmenu_close();
}

function shn_pnm_adm_upload_video(){
    global $global;
    $db = $global['db'];
	if($_POST['submit']==null){
		_shn_pnm_adm_head();
		//show form
		echo "<h2>"._t("Upload Videos")."</h2>";
		shn_form_fopen('adm_upload_video','pnm',array('enctype'=>'enctype="multipart/form-data"'));
		shn_form_fsopen();
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
			$query = "INSERT INTO pnm_media(media_id,media_title,media_description,media_type,mime_type,media_path,date) VALUES (?,?,?,?,?,?,?)";
			$db->StartTrans();
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
?>