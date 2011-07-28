<?php
/**
 * @name         MPR Email Service
 * @version      1.9
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0728
 */


/**
 * Gives the nice name of the module
 */
$conf['mod_mpres_name'] = _t("MPR Email Service");

/**
 * Gives the priority order in the main menu when listed
 */
$conf['mod_mpres_menuorder']    = 89;
$conf['mod_mpres_dependencies'] = "mpr(1.0)";
$conf['mod_mpres_version']      = 1.6;