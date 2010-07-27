<?php
/**
 * This is the conf file for the PLS module.
 *
 * This module provides "Person Locator Services" and is a web services only module.
 *
 * PHP version 5.2+ (compiled with imap support)
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Greg Miernicki
 * @package	module
 * @subpackage	pls
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 *

/**
 * 
 * This function displays the home page of the missing person registry
 *
 * @access public
 * @return void
 */
function shn_pls_default() {
	echo "This is a web services only module and does not have any GUI functions.";
}