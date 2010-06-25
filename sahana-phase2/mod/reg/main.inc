<?php
/**
 * REG Module
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module reg
 * @version    0.2
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */



/**
 * Default Admin function 
 * 
 * @access public
 * @return void
 */
function shn_reg_default() {
	global $global;
	?><div id="home">
		<h2><?= _t('REG ~ Sahana Device/User Registration'); ?></h2><br>
		<div>
			<b><em><?= (_t("Features:")) ?></em></b>
		</div>
		<br></br>
		<ul>
			<li><?= _t('Allows mobile devices to register for API_KEYs to gain access to web services.'); ?></li>
			<li><?= _t('In the process a Sahana user account is also created for the user to access the Sahana website.'); ?></li>
			<li><?= _t('Newly created accounts are inactive until verified by email.'); ?></li>
			<li><?= _t('Deletion/Activation/Inactivation of accounts are managed from the link below.'); ?></li>
		</ul>
		<br/><br/>
		<strong><? echo _t("Module Actions:"); ?></strong><br/><br/>
		<ul>
			<li><a href="index.php?mod=reg&act=log"><b><?= _t('View Registered Users/Devices'); ?> </b></a></li>
		</ul>
		<br/>
	</div><?
}




/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_reg_mainmenu() {
	global $global;
	$module = $global['module'];
	include $global['approot']."/inc/handler_mainmenu.inc";

	// Create the module menu
	shn_mod_menuopen(_t("REG"));
		shn_mod_menuitem("default", _t("REG Home"));
		shn_mod_menuitem("log", _t("Registration Log"));
	shn_mod_menuclose();
}




/**
 * Default Admin function 
 * 
 * @access public
 * @return void
 */
function shn_reg_log() {
	global $global;
	?><div id="home">
		log
	</div><?
}