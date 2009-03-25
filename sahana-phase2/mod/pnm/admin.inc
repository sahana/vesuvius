<?php
function shn_pnm_adm_default(){
	echo "<h2>"._t("Press and Media Module Administration")."</h2>";
	
	shn_tabmenu_open();
	shn_tabmenu_item('upload_video',_t('Upload Videos'),'pnm');
	shn_tabmenu_item('upload_image',_t('Upload Images'),'pnm');
	shn_tabmenu_item('add_news',_t('Add News'),'pnm');
	shn_tabmenu_close();
	
}

?>