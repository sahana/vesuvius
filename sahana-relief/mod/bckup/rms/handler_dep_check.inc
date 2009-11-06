<?php
/**
* The Sahana Resquest Management System Dependancy Check
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

$error  = false;

/**
 * List of tables that should exist
 */
$tables = array (
                    rms_request,
                    rms_req_item,
                    rms_priority,
                    rms_status,
                    rms_pledge,
                    rms_plg_item,
                    rms_fulfil,
                    rms_tmp_sch,
                    ct_catalogue,
                    ct_unit,
                    ct_unit_type,
                    ct_cat_unit
                );
$error  =  __check_tables($tables);

if($error)
{
    add_error("<strong>"._t("Please contact the system admin <br />and create the required tables using the 'mod/rms/ins/dbcreate.sql' file, and properly setup the Sahana Catalogue System")."</strong>");
    display_errors();

    $error  = false;
}

/**
 * List of tables that should not be empty
 */
$tables = array (
                    ct_catalogue,
                    ct_unit,
                    ct_unit_type,
                    ct_cat_unit
                );
$error  = __check_empty_tables($tables);

if ($error)
{
    add_error("<strong>"._t("Please contact the system admin <br />and and add the initial data thats required by this module")."</strong>");
    display_errors();
}

function __check_tables($tables)
{
    $error = false;

    foreach($tables as $table)
    {
        if(!_shn_dep_is_table("$table"))
        {
            add_error("Missing table : $table");
            $error = true;
        }
    }

    return $error;
}

function __check_empty_tables($tables)
{
    $error = false;

    foreach($tables as $table)
    {
        if(_shn_dep_is_empty("$table"))
        {
            add_error("Empty table : $table");
            $error = true;
        }
    }

    return $error;
}
?>
