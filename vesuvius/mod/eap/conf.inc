<?php
/**
 * @name         Edit A Person
 * @version      1.11
 * @package      eap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0119
 */

$conf['mod_eap_name']         = _t("Edit a Person");  // Defines the name of the module
$conf['mod_eap_menuorder']    = 2;                    // Defines this module's main menu priority
$conf['mod_eap_dependencies'] = "rap";                // Requires POP module for email and REZ for displaying some page content
$conf['mod_eap_hide_in_menu'] = true;
$conf['mod_eap_version']      = 1.8;
