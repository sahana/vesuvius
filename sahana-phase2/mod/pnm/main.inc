<?php
function shn_pnm_default(){
	echo "<h2>"._t("Sahana Press and Media Module")."</h2>";
	
	echo "<p>"._t("This module is the public interface for press and media to provide the most latest information about the disaster situation.");
	
	echo "<ul>";
	echo "<li><a href='index.php?mod=pnm&act=lnews'>"._t("Latest News")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=lvideos'>"._t("Latest Videos")."</a>";
	echo "<li><a href='index.php?mod=pnm&act=limages'>"._t("Latest Images")."</a>";
	echo "</ul>";
}
?>