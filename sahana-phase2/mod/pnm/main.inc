<?php
include $global['approot'].'inc/lib_menu.inc';

function shn_pnm_default(){
	echo "<h2>"._t("Sahana Press and Media Module")."</h2>";

	echo "<p>"._t("This module is the public interface for press and media to provide the most latest information about the disaster situation.");

	echo "<ul>";
	echo "<li><a href='index.php?mod=pnm&act=lnews'>"._t("News")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=lvideos'>"._t("Videos")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=limages'>"._t("Images")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=lfeeds'>"._t("RSS Feeds")."</a>";
	echo "</ul>";
}

function shn_pnm_mainmenu(){
	global $global;
	global $conf;
	$module = $global['module'];
	//  $loc=_shn_or_get_start_loc();
	shn_mod_menuopen($conf['mod_pnm_name']);
	shn_mod_menuitem("default",_t("Home"),$module);
	shn_mod_menuitem("lnews",_t("News"),$module);
	shn_mod_menuitem("lvideos",_t("Videos"),$module);
	shn_mod_menuitem("limages",_t("Images"),$module);
	shn_mod_menuitem("lfeeds",_t("RSS Feeds"),$module);
	shn_sub_mod_menuclose();
	shn_mod_menuclose();

	include $global['approot']."/inc/handler_mainmenu.inc";
}
?>