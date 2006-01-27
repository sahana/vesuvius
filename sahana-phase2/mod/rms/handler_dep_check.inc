<?php
/**
* Sahana Request Management System dependancy check
*
* This will check for the DB schema and other dependancies for the
* Request Management System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package
* @subpackage
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


include_once $global['approot']."/inc/lib_dependency.inc";


$error	= false;
$tables = array(rms_request,rms_req_category,rms_req_units,rms_req_priority,
				rms_req_item,rms_req_ff,rms_req_donor,rms_pledge);
$error	=  __check_tables($tables);

if($error) {
	_shn_rms_adderror(_("<strong>Please create the required tables using the 'mod/rms/ins/rms.sql' file</strong>"));
	_shn_rms_showerrors();

	$error	= false;
}

$tables	= array(rms_req_category,rms_req_units,rms_req_priority);
$error	= __check_empty_tables($tables);

if ($error) {
	_shn_rms_adderror(_("<strong>Please populate the tables using the 'mod/rms/ins/rms.sql' file</strong>"));
	_shn_rms_showerrors();
}

function __check_tables($tables)
{
	$error = false;

	foreach($tables as $table) {
		if(!_shn_dep_is_table("$table")) {
			_shn_rms_adderror("Missing table : $table");
			$error = true;
		}
	}

	return $error;
}

function __check_empty_tables($tables)
{
	$error = false;

	foreach($tables as $table) {
		if(_shn_dep_is_empty("$table")) {
			_shn_rms_adderror("Empty table : $table");
			$error = true;
		}
	}

	return $error;
}
?>



