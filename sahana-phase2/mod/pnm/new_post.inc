<?php
function shn_pnm_news_post_form(){

	global $global;
	echo '<h2 align="center">(' . _t('Post new News item') . ')</h2>';
	shn_form_fopen("new_post",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
	shn_form_fsopen(_t("Post new News"));
	shn_form_wysiwyg(_t("News Item"),"news",array('value'=>$_SESSION['pnm']['news']['text']));
	shn_form_hidden(array('seq'=>'conf'));
	shn_form_submit(_t("Post"));
	
	shn_form_fsclose();
}

function shn_pnm_confirm_post(){
	echo '<h2 align="center">(' . _t('Confirm News') . ')</h2>';
	
	shn_form_fopen("new_post",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => false));
	shn_form_fsopen(_t("Confirm News post"));
	
	echo $_SESSION['pnm']['news']['text'];
	
	shn_form_submit(_t("Post"),'post');
	shn_form_submit(_t("Edit"),'edit');
	shn_form_fsclose();

}

?>