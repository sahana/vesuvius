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


function _shn_add_reference_tables($table,$tables){
    global $global;
    static $dbsql;
    if(!isset($dbsql)){
        $files=_shn_get_dbfiles();
        foreach($files as $key=>$file)
            $dbsql.=file_get_contents($file);
    }
    echo $dbsql;
    

}

function _shn_get_dbfiles(){
    global $global;
    $files=array();
    array_push($files,$global['approot']."/inst/mysql-dbcreate.sql");
    $modules=shn_get_module_names();
    foreach($modules as $module){
        if(file_exists($file=$global['approot'].'/mod/'.$module.'/ins/dbcreate.sql'))
            array_push($files,$file);
    }
    return $files;
}

