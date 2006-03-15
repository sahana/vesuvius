<?php
/* $Id: down.inc,v 1.2 2006-03-15 10:49:49 priyanga Exp $ */

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

function shn_sync_dump_base()
{
    /* Base tables are 
     * location
     * field_options
     * modules
     * config
     * lc_fields
     * lc_tmp_po
     */

    global $global;

    $all_xml = "<?xml version=\"1.0\" ?>\n";
    $all_xml = "<base_tables>\n";
    //field_options dump
    $sql_field = "SELECT field_name, option_code, option_description 
                  FROM field_options";
    $arr = $global['db']->GetAll($sql_field);
    $all_xml .= _shn_sync_generate_xml('field_options',
            array('field_name', 'option_code', 'option_description'), $arr);

    // Location Dump
    $sql_loc = "SELECT location_id, parent_id, search_id, opt_location_type, 
                name, iso_code, description FROM location";
    $arr = $global['db']->GetAll($sql_loc);
    $all_xml .= _shn_sync_generate_xml('location',
            array('location_id', 'parent_id', 'search_id', 'opt_location_type',
            'name', 'iso_code', 'description'), $arr);

    //Modules
    $sql_modules = "SELECT module_id, version, active FROM modules";
    $arr = $global['db']->GetAll($sql_modules);
    $all_xml .= _shn_sync_generate_xml('modules',
            array('module_id', 'version', 'active'), $arr);
    
    //config
    $sql_config = "SELECT module_id, confkey, value FROM config";
    $arr = $global['db']->GetAll($sql_config);
    $all_xml .= _shn_sync_generate_xml('config',
            array('module_id', 'confkey', 'value'), $arr);

    $all_xml .= "</base_tables>\n";
    echo $all_xml;
}

function shn_sync_dump_field_options()
{
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
    // Location Dump
    $sql_loc = "SELECT location_id, parent_id, search_id, opt_location_type, 
                name, iso_code, description FROM location";
    $arr = $global['db']->GetAll($sql_loc);
    $all_xml .= _shn_sync_generate_xml('location',
            array('location_id', 'parent_id', 'search_id', 'opt_location_type',
            'name', 'iso_code', 'description'), $arr);
    echo $all_xml;
}

function shn_sync_dump_modules()
{
    $sql_modules = "SELECT module_id, version, active FROM modules";
    $arr = $global['db']->GetAll($sql_modules);
    $all_xml .= _shn_sync_generate_xml('modules',
            array('module_id', 'version', 'active'), $arr);
    echo $all_xml;
}

function shn_sync_dump_config()
{
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
            $output .= "\t\t\t<$field>".$data[$field]."</$field>\n";
        }
        $output .= "\t\t</record>\n";
    }
    
    $output .= "\t</$node>\n";
    return $output;
}

?>
