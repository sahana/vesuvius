<?php
/**
 * @name         Dynamic Portable App
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0723
 */


$conf['mod_dpa_name']      = _t("Dynamic Portable App");
$conf['mod_dpa_version']   = 0.1;
$conf['mod_dpa_menuorder'] = 98;
$conf['mod_dpa_config_file'] = 'dpa-config.xml';
$conf['mod_dpa_log_file'] = 'dpa-activity.log';
$conf['mod_dpa_bin'] = $global['approot'] . "/mod/dpa/bin/";
$conf['mod_dpa_required'] = array("admin", "eap", "em", "home", "pref", "report", "inw", "lpf", "xst");