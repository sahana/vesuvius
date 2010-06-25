<?php
/**
 * This is the main admin file for the POP module.
 *
 * PHP version 5.2+ (compiled with imap support)
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @package	module
 * @subpackage	pop
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */



/**
 * Default Admin function 
 * 
 * @access public
 * @return void
 */
function shn_inw_default() {
	global $global;
	?><script>
		window.location.href = '/inw/iWall.php';
	</script>
	<a href="/inw/iWall.php">Click here if not automatically redirected</a>
	<?
}




/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_inw_mainmenu() {
	global $global;
	$module = $global['module'];
	include $global['approot']."/inc/handler_mainmenu.inc";

	// Create the module menu
	shn_mod_menuopen(_t("Interactive Notification Wall"));
		shn_mod_menuitem("default", _t("INW Home"));
	shn_mod_menuclose();
}
