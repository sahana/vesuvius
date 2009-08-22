<?php


//echo $locale.'////';
//echo $translateword.'////';
//echo $dropdownvalue.'////';
//echo $tagname.'////';

function shn_admin_lc_select_tag()
{
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


