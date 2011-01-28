<?php

/** AJAX for  Admin
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Kethees <ks@respere.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

global $global;

array_push($global['xajax_functions'],'admin_get_field_options');
array_push($global['xajax_functions'],'admin_conf_ajax_update');

include_once 'lib_fo_config.inc';
include_once 'conf_admin.inc';


function admin_get_field_options($field_name){
	global $global;
	$res = shn_admin_field_options_xajax($field_name);
	foreach ($res as $rs){
		$html .= "<option value =". $rs['option_code'].">" . $rs['option_description'] . "</option>";
	}
	$global['xajax_res']->addAssign('opt_data','innerHTML',$html);

	return $global['xajax_res']->getXML();
}

function admin_conf_ajax_update($key,$value)
{
	global $global;
	$error = false;
	$error = shn_config_validate_value($key,$value);

	if($error===false){
		// no errors.
		shn_config_database_update($key,$value);
		// truncate the new value before display.
		$new_value = htmlspecialchars_decode(shn_html_truncate($value,25));
		$new_value = shn_html_bool2str($new_value);
		$new_value = shn_html_truncate($new_value,25);

		// create async response
		$xajax_response = &$global['xajax_res'];
		$xajax_response->addAssign("target_$key","innerHTML",$new_value);;
		// hide error if visible
		$xajax_response->addAssign("target_".$key."_error","className","feedback_content_error hide");;
		// hide row.
		$xajax_response->addScript("_hide('$key')");
		return $xajax_response->getXML();
	}else{
		$xajax_response = &$global['xajax_res'];
		$xajax_response->addAssign("target_".$key."_error","innerHTML",$error);;
		$xajax_response->addAssign("target_".$key."_error","className","feedback_content_error show");;
		//echo $xajax_response;
		//file_put_contents("/tmp/errors.txt","helo");
		return $xajax_response->getXML();
	}
}
