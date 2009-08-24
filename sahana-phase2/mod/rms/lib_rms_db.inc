<?php
/**
* The Sahana Resquest Management System
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

function _shn_rms_db_addcontact($uuid, $type, $value)
{
    global $global;
    
    $sql = "INSERT INTO contact (pgoc_uuid, opt_contact_type, contact_value) " .
            "VALUES ('$uuid', '$type', '$value')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    else
    {
        return true;
    }    
}

function _snf_rms_db_is_contactex($uuid, $type)
{
    global $global;
    
    $sql = "SELECT pgoc_uuid, opt_contact_type FROM contact " .
            "WHERE pgoc_uuid='$uuid'" .
            "AND opt_contact_type='$type'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}

?>
