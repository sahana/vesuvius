<?php
/**
 * This handler will stream the data file
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
global $global;
global $conf;
include_once('lib_sync_file.inc');
include_once('lib_dump_data.inc');



//table array
$tables=array();
//modules
$modules=shn_get_module_names();

//get the table names from selected modules
if(isset($_POST['modules'])){
    foreach($_POST['modules'] as $module){
        $tables=_shn_sync_file_tables($module,$tables);
    }
}

//get the tables from selected data blocks
foreach($modules as $module){
    if(isset($_POST[$module])){
        $tables=_shn_sync_data_tables($module,$_POST[$module],$tables);
    }
}


//dependancy algorithem
foreach($tables as $table){
    $keys=$global['db']->MetaForeignKeys($table);
    //_shn_add_reference_tables($table,$tables);
    foreach($keys as $table=>$k){
        if(in_array($table,$tables));
        else
            array_push($tables,$table);
    }
}

require_once('compressor.inc');
$fp = fopen($tmp_file, 'rb');
switch ($_POST['file_type']){
    case 'xml':
        //creating headers
        header("Content-type: text/xml");
        header("Content-Disposition: attachment; filename=sahana_data_dump_".$conf['base_uuid']."_".time().".xml".$com);
        header("Cache-Control: no-cache, must-revalidate");
        fpassthru($fp);
        //dump the data in the tables
        
        exit();
    case 'csv':
        echo "csv";
        exit();
    case 'sql':
        echo "sql";
        exit();
    case 'sqlite':
        echo "sqlite";
        exit();
}


