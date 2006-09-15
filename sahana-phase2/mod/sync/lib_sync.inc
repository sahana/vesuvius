<?php
/**
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


function shn_sync_merge($table){
    global $global;
    //getting the primary keys of the tables
    $primary=$global['db']->MetaPrimaryKeys($table);
    //creating the delete query
    if(!is_array($primary)){
        $primary=$global['db']->MetaColumnNames($table);
        $del_sql="DELETE a FROM tmp_".$table." as a , ".$table." as b WHERE ";
        foreach($primary as $key){
            $del_sql.= "a.".$key."=b.".$key." AND ";
        }
        $del_sql.="1>0";
    }
    else if(1==count($primary)){
        $del_sql="DELETE FROM tmp_".$table." WHERE ";
        $del_sql.=$primary[0]." IN (select ".$primary[0]." from ".$table.")";
    }
    else{
        $del_sql="DELETE a FROM tmp_".$table." as a , ".$table." as b WHERE ";
        foreach($primary as $key){
            $del_sql.= "a.".$key."=b.".$key." AND ";
        }
        $del_sql.="1>0";
    }

    //deleting the existing tables
    if ($global['db']->Execute($del_sql) === false) {
        print_r($primary);
        print '36 error deleting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
    }
    $del_no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_delete_number($table,$del_no);
    //mearging the tables
    $in_sql=" insert into ".$table." select * from tmp_".$table;
    if (($rs=$global['db']->Execute($in_sql)) === false) {
        print '41 error inserting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
    }
    $ins_no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_insert_number($table,$ins_no);
}

//this function will delete the duplicate records considering the uuid
function shn_sync_delete_duplicate($table){
    global $global;
    //getting the primary keys of the tables
    $primary=$global['db']->MetaPrimaryKeys($table);
    //creating the delete query
    if(!is_array($primary)){
        $primary=$global['db']->MetaColumnNames($table);
        $del_sql="DELETE a FROM tmp_".$table." as a , ".$table." as b WHERE ";
        foreach($primary as $key){
            $del_sql.= "a.".$key."=b.".$key." AND ";
        }
        $del_sql.="1>0";
    }
    else if(1==count($primary)){
        $del_sql="DELETE FROM tmp_".$table." WHERE ";
        $del_sql.=$primary[0]." IN (select ".$primary[0]." from ".$table.")";
    }
    else{
        $del_sql="DELETE a FROM tmp_".$table." as a , ".$table." as b WHERE ";
        foreach($primary as $key){
            $del_sql.= "a.".$key."=b.".$key." AND ";
        }
        $del_sql.="1>0";
    }
    //deleting the existing tables
    if ($global['db']->Execute($del_sql) === false) {
        print 'error deleting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
    }
    $del_no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_delete_number($table,$del_no);
}


//this function will insert the records in tmp_table to the table
function shn_sync_insert($table){
    //mearging the tables
    $in_sql=" insert into ".$table." select * from tmp_".$table;
    if (($rs=$global['db']->Execute($in_sql)) === false) {
        print 'error inserting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
    }
    $ins_no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_insert_number($table,$ins_no);
}

//this function will delete records with same patterns
function shn_sync_delete_pattern(){

}
?>