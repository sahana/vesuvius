<?php
/* $Id: down.inc,v 1.6 2006-06-02 07:24:22 priyanga Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    <package>
 * @subpackage <subpackage>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

$syncdata['base']='base';
$basetables=array('field_options','location','modules','config');



function shn_sync_dump_field_options()
{
    global $global;
    //field_options dump
    $sql_field = "SELECT field_name, option_code, option_description 
                  FROM field_options";
    $arr = $global['db']->GetAll($sql_field);
    $all_xml .= _shn_sync_generate_xml('field_options',
            array('field_name', 'option_code', 'option_description'), $arr);
    echo $all_xml;
}

function shn_sync_dump_location()
{
    global $global;
    // Location Dump
    $sql_loc = "SELECT loc_uuid, parent_id, opt_location_type, 
                name, iso_code, description FROM location";
    $arr = $global['db']->GetAll($sql_loc);
    $all_xml .= _shn_sync_generate_xml('location',
            array('loc_uuid', 'parent_id', 'opt_location_type',
            'name', 'iso_code', 'description'), $arr);
    echo $all_xml;
}

function shn_sync_dump_modules()
{
    global $global;
    $sql_modules = "SELECT module_id, version, active FROM modules";
    $arr = $global['db']->GetAll($sql_modules);
    $all_xml .= _shn_sync_generate_xml('modules',
            array('module_id', 'version', 'active'), $arr);
    echo $all_xml;
}

function shn_sync_dump_config()
{
    global $global;
    $sql_config = "SELECT module_id, confkey, value FROM config";
    $arr = $global['db']->GetAll($sql_config);
    $all_xml .= _shn_sync_generate_xml('config',
            array('module_id', 'confkey', 'value'), $arr);
    echo $all_xml;
}

function _shn_sync_generate_xml($node,$fields, $arr)
{
    $output = "\t<$node>\n";
    
    foreach($arr as $data){
        $output .= "\t\t<record>\n";
        foreach($fields as $field){
            $output .= "\t\t\t<$field>".htmlspecialchars($data[$field])."</$field>\n";
        }
        $output .= "\t\t</record>\n";
    }
    
    $output .= "\t</$node>\n";
    return $output;
}

?>
