<?php
/**
 * This is the conf file for the POP module.
 *
 * The POP module add 2 capabilities to Sahana:
 * 1) the ability to send email via an outbound smtp server
 * 2) the ability to walk a pop/imap inbox and retrieve emails/attachments
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
 *
 */

$conf['mod_pop_name']         = _t("Outbound Email");  // Defines the name of the module
$conf['mod_pop_menuorder']    = 99;                             // Defines this module's main menu priority 
$conf['mod_pop_dependencies'] = "";
$conf['mod_pop_version']      = 1.0;