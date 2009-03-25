<?php
include $global['approot'].'inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_table.inc';

include_once 'lib_ims_rss.inc';
require_once($global['approot']."/inc/lib_rss.inc");

include_once $global['approot'].'/inc/lib_form.inc';


function shn_pnm_default(){
	echo "<h2>"._t("Sahana Press and Media Module")."</h2>";

	echo "<p>"._t("This module is the public interface for press and media to provide the most latest information about the disaster situation.");

	echo "<ul>";
	echo "<li><a href='index.php?mod=pnm&act=lnews'>"._t("News")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=lvideos'>"._t("Videos")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=limages'>"._t("Images")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=lfeeds'>"._t("RSS Feeds")."</a>";
	echo "</ul>";
	
	echo '<br>';

	include_once 'figure_update.inc';
	
    shn_rss_add_feed('rss_expired_list',_t('press and meadia'));

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
	shn_mod_menuitem("lvideos",_t("Videos"),$module);
	shn_mod_menuitem("limages",_t("Images"),$module);
	shn_mod_menuitem("lfeeds",_t("RSS Feeds"),$module);
	shn_mod_menuitem("mediareg", _t("Media"), $module);	
	shn_sub_mod_menuclose();
	shn_mod_menuclose();

	include $global['approot']."/inc/handler_mainmenu.inc";
}


//function shn_pnm_figure_update(){
    
//}


function shn_pnm_new_post(){
	global $global;
	require ($global['approot'] . 'mod/pnm/new_post.inc');
	require ($global['approot'] . 'inc/lib_uuid.inc');
	

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
function getrss() {
	shn_pnm_generaterss();
}
?>

