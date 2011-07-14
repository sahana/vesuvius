<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Kethees <ks@respere.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */


global $global;

array_push($global['xajax_functions'],'admin_get_field_options');
array_push($global['xajax_functions'],'admin_conf_ajax_update');

include_once 'lib_fo_config.inc';
include_once 'conf_admin.inc';

function admin_get_field_options($field_name) {
	global $global;
	$res = shn_admin_field_options_xajax($field_name);
	foreach ($res as $rs){
		$html .= "<option value =". $rs['option_code'].">" . $rs['option_description'] . "</option>";
	}
	$global['xajax_res']->addAssign('opt_data','innerHTML',$html);

	return $global['xajax_res']->getXML();
}



function admin_conf_ajax_update($key,$value) {
	global $global;

	shn_config_database_update($key,$value);

	// truncate the new value before display.
	$new_value = htmlspecialchars_decode(shn_html_truncate($value,25));
	$new_value = shn_html_bool2str($new_value);
	$new_value = shn_html_truncate($new_value,25);

	// create async response
	$xajax_response = &$global['xajax_res'];
	$xajax_response->addAssign("target_$key","innerHTML",$new_value);;

	// hide row.
	$xajax_response->addScript("_hide('$key')");
	return $xajax_response->getXML();
}



