<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */

function shn_admin_lc_select_tag() {
	global $global;
	$locale = $_REQUEST['locale'];
	$translateword = $_REQUEST['translateword'];
	$dropdownvalue = $_REQUEST['dropdownvalue'];
	$tagname = $_REQUEST['tagname'];
	$q = "SELECT option_code FROM field_options WHERE option_description='{$dropdownvalue}' AND field_name='{$tagname}'";
	$res = $global['db']->Execute($q);
	$opt_code = $res->fields[0];

	$q = "INSERT INTO field_options_locale(field_name,option_code,option_description,locale) VALUES ('{$tagname}','{$opt_code}','{$translateword}','{$locale}')";
	$global['db']->Execute($q);
}


