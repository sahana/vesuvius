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

//this function will delete the duplicate records considering the uuid
function shn_sync_delete_duplicate($table){
    global $global;
    //getting the primary keys of the tables
    $primary=$global['db']->MetaPrimaryKeys($table);
    //creating the delete query
    if(!is_array($primary)){
        $primary=$global['db']->MetaColumnNames($table);
        $del_sql="DELETE a FROM tmp_".$table." AS a , ".$table." AS b WHERE ";
        foreach($primary as $key){
            $del_sql.= "a.".$key."=b.".$key." AND ";
        }
        $del_sql.="1>0";
    }
    else if(1==count($primary)){
        $del_sql="DELETE FROM tmp_".$table." WHERE ";
        $del_sql.=$primary[0]." IN (SELECT ".$primary[0]." FROM ".$table.")";
    }
    else{
        $del_sql="DELETE a FROM tmp_".$table." AS a , ".$table." AS b WHERE ";
        foreach($primary as $key){
            $del_sql.= "a.".$key."=b.".$key." AND ";
        }
        $del_sql.="1>0";
    }

    //deleting the existing tables
    if ($global['db']->Execute($del_sql) === false) {
        add_error('Error deleting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n");
        throw new Exception($error);
    }
    $del_no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_delete_number($table,$del_no);
}





function shn_sync_update_duplicate($table){
    global $global;
    //getting the primary keys of the tables
    $primary=$global['db']->MetaPrimaryKeys($table);
    $fields=$global['db']->MetaColumnNames($table);
    //creating the update query
    if(!is_array($primary)){ return;}
    else if(1==count($primary)){
        $sql="UPDATE ".$table." AS a INNER JOIN tmp_".$table." AS b ON a.".$primary[0]."=b.".$primary[0]." SET ";
    }
    else{
        $sql="UPDATE ".$table." AS a INNER JOIN tmp_".$table." AS b ON (";
        foreach($primary as $key){
            $sql.= "a.".$key."=b.".$key." AND ";
        }
        $sql.="1>0 ) SET ";
    }
    
    foreach($fields as $key){
        $sql.= "a.".$key."=b.".$key." ,";
    }
    $sql=rtrim($sql, ",");

    //update the existing tables
    if ($global['db']->Execute($sql) === false) {
        add_error('Error upating: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n");
        throw new Exception($error);
    }
    $no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_update_number($table,$no);
}





//this function will insert the records in tmp_table to the table
function shn_sync_insert($table){
    global $global;
    //mearging the tables
    $in_sql="INSERT INTO ".$table." SELECT * FROM tmp_".$table;
    if (($rs=$global['db']->Execute($in_sql)) === false) {
        add_error('Error inserting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n");
        throw new Exception($error);
    }
    $ins_no=$global['db']->Affected_Rows();
    $_SESSION['report']->set_insert_number($table,$ins_no);
}


//function to upate the sync instance table
function _shn_sync_update_instance(){
    global $global;
    if ($global['db']->Replace('sync_instance',$_SESSION['sync_instance'], 'base_uuid') === false) {
        add_error("Error updating instance information");
        add_error('Error updating: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n");
        throw new Exception($error);
    }
}

