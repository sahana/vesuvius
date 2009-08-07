<?php
/**
 *
 * Shows the Description of the field_option, when given the vaule
 *
 * @todo Need to move this to a library.
 * @param mixed $value 
 * @param mixed $field_name 
 * @access public
 * @return void
 */


function shn_get_field_opt($value,$field_name) {
	global $global;
	return $global['db']->GetOne("SELECT option_description FROM field_options WHERE option_code = '$value' AND field_name='$field_name'");
}