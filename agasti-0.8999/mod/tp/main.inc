<?php
/**
 * TP Module
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module tp
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */



/**
 * Default Admin function 
 * 
 * @access public
 * @return void
 */
function shn_tp_default() {
	global $global;
	$intPath = getcwd()."/tmp/triagepic_cache/";
	$extPath = getcwd()."/tmp/triagepic_cache_ext/";
	$intPathReal = realpath($intPath);
	$extPathReal = realpath($extPath);
	$border = "style=\"border: none;\"";
	$show = false;
	
	if(file_exists($intPathReal)) {
		echo "<span style=\"color: red;\"><b>RED = Internal</b> /triagepic_cache</span> ";
		echo "
			<iframe src =\"tmp/triagepic_cache/publish.htm\" width=\"100%\" height=\"470\" style=\"border: 1px solid red;\">
			<p>Your browser does not support iframes.</p>
			</iframe>
		";
		$border = "style=\"border: 1px solid green;\"";
		echo "<br><br><span style=\"color: green;\"><b>GREEN = External</b> /triagepic_cache_ext</span>";
		$show = true;
	}
	if(file_exists($extPathReal)) {
		echo "
			<iframe src =\"tmp/triagepic_cache_ext/publish.htm\" width=\"100%\" height=\"470\" ".$border.">
			<p>Your browser does not support iframes.</p>
			</iframe>
		";
	}
	/*
	if($show) {
		?><br><br><br><br><h1><center><a href="index.php?mod=tp&act=publish">Click here to push TriagePic from PLstage to PL</a></h1><?php
	}
	*/
}




/**
 * Here we push TP from PLstage to PL
 * 
 * @access public
 * @return void
 */
function shn_tp_publish() {
	$out = shell_exec("su gmiernicki -c id;");
	echo "<pre>>".$out."<</pre>";
}




/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_tp_mainmenu() {
	global $global;
	$module = $global['module'];
	include $global['approot']."/inc/handler_mainmenu.inc";

	// Create the module menu
	shn_mod_menuopen(_t("TP"));
		//shn_mod_menuitem("default", _t("TriagePic"));
	shn_mod_menuclose();
}
