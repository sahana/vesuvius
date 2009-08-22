<?php
/**News Functionality of the Press and Media Module
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
function shn_pnm_news_post_form(){

	global $global;
	echo '<h2 align="center">(' . _t('Post new News item') . ')</h2>';
	shn_form_fopen("new_post",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => false));
	shn_form_fsopen(_t("Post new News"));
	shn_form_text(_t("Title"),'title', 'size="30"',array('value'=>$_SESSION['pnm']['news']['title']));
	shn_form_wysiwyg(_t("News Item"),"news",array('value'=>$_SESSION['pnm']['news']['text']));
	shn_form_hidden(array('seq'=>'post_news'));
	shn_form_submit(_t("Post"));
	
	shn_form_fsclose();
}

function shn_pnm_confirm_post(){
	echo '<h2 align="center">' . _t('Confirm News') . '</h2>';
	echo '<h1 align="left"> Title : ' . $_SESSION['pnm']['news']['title'] . '</h2>';
	shn_form_fopen("new_post",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => false));

	echo $_SESSION['pnm']['news']['text'];
	shn_form_hidden(array('seq'=>'conf'));

//	shn_form_fsclose();
	shn_form_submit(_t("Post"),'name="post"');
	shn_form_submit(_t("Edit"),'name="edit"');
	shn_form_fclose();

}
 function shn_pnm_news_commit(){
 	global $global;
 	$db = $global['db'];
 	
 	$uuid=shn_create_uuid('news');
 	$title=$_SESSION['pnm']['news']['title'];
 	$news = $_SESSION['pnm']['news']['text'];
 	$time = time();
 	$sql = "INSERT INTO pnm_news(uuid,title,news,time) values('$uuid','$title','$news','$time')";
 	$db->Execute($sql);
 	add_confirmation("News posting successful");
 	
 }
