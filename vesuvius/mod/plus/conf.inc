<?
/**
 * @name         PL User Services
 * @version      2.0.0
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0316
 */


$conf['mod_plus_name']         = _t("PL User Services");  // Defines the name of the module
$conf['mod_plus_menuorder']    = 99;                     // Defines this module's main menu priority
$conf['mod_plus_dependencies'] = "pop(0.1):lpf(0.1)";
$conf['mod_plus_version']      = "2.0.0";

// api version to default to if one is not specified
$conf['mod_plus_latest_api'] = "2.0.0";