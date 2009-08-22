<?php
/**
* Library of various trypes of dependancy checks.
*
* This will check for the Database schema and other dependancies for the
* Sahana Framework and Modules
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  framework
* @subpackage dependancy check
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * Check whether a table exists in the database
 *
 * @param string $table
 * @access public
 * @return bool
 */
function _shn_dep_is_table($table)
{
	global $global;

	$sql = "SELECT * FROM $table";

	if ($global['db']->Execute($sql) === false) {
        return false;
    } else {
    		return true;
    }

}

/**
 * Check whether a table is empty or not.
 *
 * @param string $table
 * @access public
 * @return bool
 */
function _shn_dep_is_empty($table)
{
	global $global;

	$sql = "SELECT * FROM $table";
	$rs = $global['db']->Execute($sql);

	if (false == $rs) {
        return true;
    } else if (1 > $rs->RecordCount()) {
    		return true;
	} else {
		return false;
    }
}


