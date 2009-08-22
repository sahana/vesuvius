<?php
/**
 * Library to creat temporary data
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

function create_tmp_table($table){
    //get the field info
    global $global;
    $fields=$global['db']->MetaColumns($table,true);
    //print_r($fields);
    //create the sql
    $sql="CREATE TABLE tmp_".$table."(";
    foreach($fields as $field){
        $sql.="\n".$field->name." ".$field->type;
        switch ($field->type){
            case 'varchar':
                $sql.="(".$field->max_length.")";
            break;
        }
        $sql.=" ,";
    }
    $sql=rtrim($sql,",");
    $sql.=")";
    //drop the previous table
    $sql_drop="DROP TABLE tmp_".$table.
    //create the table
    $global['db']->DropSequence("tmp_".$table);
    $global['db']->Execute($sql);
}

function insert_record($rec,$table){
    global $global;
    $global['db']->AutoExecute("tmp_".$table,$rec,'INSERT');
}

