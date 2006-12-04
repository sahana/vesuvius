<?php


/**
 * All the commonly used functionalities in the  DVR are stored in this file
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera (isuru@opensource.lk)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_dvr_print_header($string = null) {
	print '<h2>' . $string . '</h2>';
}

function shn_dvr_get_loc_range() {
	global $global;
	global $conf;
	$db = $global['db'];
	$loc = array ();
	$q = "select value from config where module_id='or' and confkey='loc_range_start'";
	$res = $db->Execute($q);
	if ($res->fields[0] == NULL) {
		$loc["start"] = $conf['mod_or_loc_level_start'];
	} else {
		$loc["start"] = $res->fields[0];
	}
	$q = "select value from config where module_id='dvr' and confkey='loc_range_end'";
	$res = $db->Execute($q);
	if ($res->fields[0] == NULL) {
		$loc["end"] = $conf['mod_or_loc_level_end'];
	} else {
		$loc["end"] = $res->fields[0];
	}
	return $loc;
}

function _shn_dvr_get_start_loc() {
	global $global;
	global $conf;
	$db = $global['db'];
	$q = "select value from config where module_id='dvr' and confkey='loc_start'";
	$res = $db->Execute($q);
	//   if($res->fields[0]==NULL){
	//    	return $conf['mod_or_start_loc'];
	//}else {
	if ($res == NULL) {
		return NULL;
	} else {
		return $res->fields["value"];
	}
}
?>
