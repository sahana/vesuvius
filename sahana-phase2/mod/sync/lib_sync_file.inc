<?php
/**
 * This Library contains functions to handel sync.xml
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_sync_file_tables($module,$tables=array()){
    global $global;
    //load the sync file
    $syncfile=$global['approot']."mod/".$module."/sync.xml";
    $scema=simplexml_load_file($syncfile); // loading the sync.xml file
    //itrate data
    foreach ($scema->xpath('//table') as $table) {
        if(!in_array((string)$table['name'],$tables))
        array_push($tables,(string)$table['name']);
    }
    foreach ($scema->xpath('//foreign_key') as $fk) {
        if(!in_array((string)$fk['ref_table'],$tables))
        array_push($tables,(string)$fk['ref_table']);
    }
    return $tables;
}

function _shn_sync_data_tables($module,$arr,$tables=array()){
    global $global;
    //load the sync file
    $syncfile=$global['approot']."mod/".$module."/sync.xml";
    $scema=simplexml_load_file($syncfile); // loading the sync.xml file
    foreach($arr as $key=>$d){
        //echo $scema->data[$key]->asXML();
        $dataxml=simplexml_load_string($scema->data[(int)$d]->asXML());
        foreach ($dataxml->xpath('//table') as $table) {
            if(!in_array((string)$table['name'],$tables))
            array_push($tables,(string)$table['name']);
        }
        foreach ($dataxml->xpath('//foreign_key') as $fk) {
            if(!in_array((string)$fk['ref_table'],$tables))
            array_push($tables,(string)$fk['ref_table']);
        }
    }
    return $tables;
}
?>