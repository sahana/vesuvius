<?php
/**Main controller of the Press and Media Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravith Botejue, Miyuru Daminda, Reka Sandaruwan, Chamara Caldera, Nishantha Pradeep
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage pnm
* 
* Developed during Sahana 2009 as a tribute.
*/
include_once $global['approot'].'inc/lib_menu.inc';
include_once $global['approot'].'inc/lib_table.inc';
include_once 'lib_pnm_rss.inc';
include_once $global['approot'].'inc/lib_form.inc';
include_once $global['approot'].'inc/lib_rss.inc';
include_once $global['approot'].'inc/lib_uuid.inc';


function shn_pnm_default(){
	echo "<h2>"._t("Sahana Press and Media Module")."</h2>";

	echo "<p>"._t("This module is the public interface for press and media to provide the most latest information about the disaster situation.");

	echo "<ul>";
	echo "<li><a href='index.php?mod=pnm&act=list_news'>"._t("News")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=list_videos'>"._t("Videos")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=list_images'>"._t("Images")."</a>";
	echo "</ul>";

	echo '<br>';
	echo '<br>';
	shn_rss_add_feed('rss_news_list',_t('News RSS '));
	shn_rss_add_feed('rss_video_list',_t('Video RSS'));
	echo '<br>';

	include_once 'figure_update.inc';
}

function shn_pnm_mainmenu(){
	global $global;
	global $conf;
	$module = $global['module'];
	//  $loc=_shn_or_get_start_loc();
	shn_mod_menuopen($conf['mod_pnm_name']);
	shn_mod_menuitem("default",_t("Home"),$module);
	shn_sub_mod_menuopen(_t("News"));
	shn_mod_menuitem("new_post",_t("Post new News"),$module);
	shn_mod_menuitem("list_news",_t("List News"),$module);
	shn_sub_mod_menuclose();
	shn_mod_menuitem("list_videos",_t("Videos"),$module);
	shn_mod_menuitem("list_images",_t("Images"),$module);
	shn_mod_menuitem("mediareg", _t("Media"), $module);
	shn_sub_mod_menuclose();
	shn_mod_menuclose();

	include $global['approot']."/inc/handler_mainmenu.inc";
}


//function shn_pnm_figure_update(){

//}

function shn_pnm_mediareg(){
    include_once 'media.inc';
}

function shn_pnm_new_post(){
	global $global;
	require ($global['approot'] . 'mod/pnm/new_post.inc');


	switch($_POST['seq']){
		case 'post_news':
			$_SESSION['pnm']['news']['text']=$_POST['news'];
			$_SESSION['pnm']['news']['title']=$_POST['title'];
			shn_pnm_confirm_post();
			break;
		case 'conf':
			if($_POST['post']){
				shn_pnm_news_commit();
				shn_pnm_default();
			}
			else if($_POST['edit']){
				shn_pnm_news_post_form();
			}
			break;
		default:
			$_SESSION['pnm']=null;
			shn_pnm_news_post_form();
			break;
	}
}

function shn_pnm_list_news(){

	global $global;
	include_once ($global['approot'] . 'mod/pnm/view_news.inc');

	_shn_pnm_list_news();

}

function shn_pnm_view_news_item(){
	global $global;
	include_once ($global['approot'] . 'mod/pnm/view_news.inc');
	_shn_pnm_view_news_item($_GET['uuid']);
}

function shn_pnm_list_videos(){
	global $global;
	$db = $global['db'];

	echo "<h2>"._t("Latest list of videos")."</h2>";

	$query = "SELECT * FROM pnm_media WHERE media_type='VIDEO' ORDER BY date DESC";
	$res = $db->SelectLimit($query,15);
	echo "<br/>";
	while($row = $res->FetchRow()){
		echo "<div>";
		echo "<h4>".$row['media_title']."</h4>";
		echo "<em>".$row['date']."</em><br/>";
		echo "<p>".$row['media_description']."</p>";
		echo "<a href='".$row['media_path']."'>"._t("Download Video")."</a>";
		echo "</div>";
	}
	echo "<hr/>";
	echo "<br/>";
	echo "<a href='index.php?mod=pnm&act=video_archives'>"._t('View Archives')."</a>";
}

function shn_pnm_video_archives(){
	global $global;
	$db = $global['db'];
	if($_REQUEST['submit']==null){
		// show date form
		_shn_pnm_video_archive_search_form();
	}else{
		$errors = false;
		if(shn_valid_date($_REQUEST['video_date_start'])==false){
			add_error(_t('Please enter the date in the format yyyy-mm-dd'));
			$errors = true;
		}

		if(shn_valid_date($_REQUEST['video_date_end'])==false){
			add_error(_t('Please enter the date in the format yyyy-mm-dd'));
			$errors = true;
		}

		if($errors==false){
			_shn_pnm_video_archive_search_form($_REQUEST['video_date_start'],$_REQUEST['video_date_end']);
			echo "<br/>";
			echo "<h3>"._t("Search Results")."</h3>";
			$page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
			$rpp = 15;

			$count_query = "SELECT COUNT(*) AS c FROM pnm_media WHERE media_type='VIDEO' AND date BETWEEN ? AND ?";
			$res = $db->Execute($count_query,array($_REQUEST['video_date_start'],$_REQUEST['video_date_end']));
			$count = $res->fields['c'];

			if($count==0){
				echo "<em>"._t("No videos found")."</em>";
			}else{					
				$record_query = "SELECT * FROM pnm_media WHERE media_type='VIDEO' AND date BETWEEN ? AND ?";
				$res = $db->SelectLimit($record_query,$rpp,($page-1)*$rpp,array($_POST['video_date_start'],$_POST['video_date_end']));
				while($row = $res->FetchRow()){
					echo "<div>";
					echo "<h4>".$row['media_title']."</h4>";
					echo "<em>".$row['date']."</em><br/>";
					echo "<p>".$row['media_description']."</p>";
					echo "<a href='".$row['media_path']."'>"._t("Download Video")."</a>";
					echo "</div>";
				}
				echo "<br/><hr/>";
				$pg_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
				echo _t("Pages : ");
				for($i=1;$i<$pg_count;$i++){
					echo "<a href='index.php?mod=pnm&act=video_archives&page=$i&submit=true&video_date_start=".$_REQUEST['video_date_start']."&video_date_end=".$_POST['video_date_end']."'>".$i."</a>&nbsp;&nbsp;";
				}
			}
		}
	}
}

function _shn_pnm_video_archive_search_form($date_start = '', $date_end=''){
	echo "<h2>"._t("Video archive")."</h2>";
	shn_form_fopen('video_archives','pnm');
	shn_form_fsopen(_t('Select a Date Range'));
	shn_form_date(_t('From Date'),'video_date_start',array('req'=>true,'value'=>$date_start));
	shn_form_date(_t('To Date'),'video_date_end',array('req'=>true,'value'=>$date_end));
	shn_form_fsclose();
	shn_form_submit(_t('Search Archive'),'name="submit"');
	shn_form_fclose();
}
