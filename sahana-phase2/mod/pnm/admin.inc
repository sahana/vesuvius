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

	if($_POST['submit']==null){
		_shn_pnm_adm_head();
		//show form
		echo "<h2>"._t("Upload Videos")."</h2>";
		shn_form_fopen('adm_upload_video','pnm',array('enctype'=>'enctype="multipart/form-data"'));
		shn_form_fsopen();

		shn_form_upload(_t('Video File to Upload'),'video_file');

		shn_form_fsclose();
		shn_form_submit(_t('Upload'),'name="submit"');
		shn_form_fclose();
	}else{
		// upload.

		$file_name = $_FILES['video_file']['tmp_name'];
		if(preg_match('/video\/.*/i',$_FILES['video_file']['type'])==0){
			add_error(_t("Please upload a video file"));
		}else{

		}

		echo $file_name;
		echo $_FILES['video_file']['type'];
	}
}
?>