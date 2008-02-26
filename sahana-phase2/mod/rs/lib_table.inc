<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Agnieszka Kulikowska <agnieszka.kulikowska@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once $global['approot']."/inc/handler_db.inc";



// function returns array where key is table name and value is tables user-friendly name
function _shn_dr_tables(){
	global $global;

// 		print "<p>db: ".$global["db"]."</p>";

	// getting user-friendly tables names
	$sql = "SELECT dr_tables.usrfr_table_name,dr_tables.table_name FROM dr_tables";
	$res = $global['db']->Execute($sql); 

	while($res->fields != NULL){
		$tables[$res->fields['table_name']] = $res->fields['usrfr_table_name'];
		$res->MoveNext();
	}

	return $tables;
}
 



// function returns array where key is field name and value is fields user-friendly name
function _shn_dr_fields($table_name){
	global $global;

	// getting user-friendly tables names
	$sql = "SELECT dr_fields.usrfr_field_name,dr_fields.field_name FROM dr_fields 
					WHERE dr_fields.table_name='$table_name'";
	$res = $global['db']->Execute($sql); 

// 	$fields[0] = 'Select all';
	while($res->fields != null){
		$fields[$res->fields['field_name']] = $res->fields['usrfr_field_name'];
		$res->MoveNext();
	}
	return $fields;
}



// function returns array containing all tables that are corelated with tables from array $tables_name
function _shn_dr_get_foreign_tables($tables_name){
	global $global;

	$sql = "SELECT dr_fields.tab_for_key,dr_fields.table_name FROM dr_fields 
					WHERE dr_fields.tab_for_key<>'none'";
	$res = $global['db']->Execute($sql); 

	$foreign = array();
	while($res->fields != NULL){
		if (in_array($res->fields['tab_for_key'], $tables_name))
			if($res->fields['tab_for_key'] != $res->fields['table_name'])
				array_push($foreign, $res->fields['table_name']);
		if (in_array($res->fields['table_name'], $tables_name))
			if($res->fields['tab_for_key'] != $res->fields['table_name'])
				array_push($foreign, $res->fields['tab_for_key']);
		$res->MoveNext();
	}

	$ret = array();
	foreach($foreign as $tab)
		if(!in_array($tab, $ret))
			array_push($ret, $tab);

	return $ret;
}





// getting tables that have grouping fields
function _shn_dr_get_group_tables(){
	global $global;

	$sql = "SELECT DISTINCT dr_fields.table_name FROM dr_fields 
					WHERE dr_fields.opt_field_type = 'group'";
	$res = $global['db']->Execute($sql); 

	$group = array();
	while($res->fields != NULL){
		array_push($group, $res->fields['table_name']);
		$res->MoveNext();
	}
	return $group;
}





// getting grouping fields of selected table
function _shn_dr_get_group_fields($table){
	global $global;

	$sql = "SELECT dr_fields.field_name, dr_fields.usrfr_field_name FROM dr_fields 
					WHERE dr_fields.opt_field_type = 'group' AND dr_fields.table_name = '$table'"; 
// 		print "<p> ".$sql."</p>";
	$res = $global['db']->Execute($sql); 

	$group = array();
	while($res->fields != NULL){
		$group[$res->fields['field_name']] = $res->fields['usrfr_field_name'];
		$res->MoveNext();
	}
	return $group;
}

