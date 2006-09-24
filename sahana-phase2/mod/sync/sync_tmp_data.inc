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
global $global;
include_once('lib_sync.inc');

//controler to handel the threshold value
switch ($_SESSION['threshold']){

    case '1': //case to check locations
        include_once('handler_location_sync.inc');
    break;
    case '0':
        //loop through tables
        foreach($_SESSION['sync']['tables'] as $table){
            shn_sync_merge($table);
        }
    break;
}

    //add the instance data to the instance table
    $sql="SELECT * FROM sync_instance WHERE base_uuid='".$_SESSION['sync_inst']['base_uuid']."'";
    $row=$global['db']->GetRow($sql);
    $_SESSION['sync_inst']['sync_count']=$row['count']+1;
    if(count($row)>0){
        $sql="UPDATE sync_instance SET owner='".$_SESSION['sync_inst']['owner']."',contact='".$_SESSION['sync_inst']['contact']."',last_update='".$_SESSION['sync_inst']['last_update']."',sync_count=sync_count+1 WHERE base_uuid='".$_SESSION['sync_inst']['base_uuid']."'";
    }
    else{
        $sql="INSERT INTO sync_instance VALUES('".$_SESSION['sync_inst']['base_uuid']."','".$_SESSION['sync_inst']['owner']."','".$_SESSION['sync_inst']['contact']."','server','".$_SESSION['sync_inst']['last_update']."',sync_count=".$_SESSION['sync_inst']['sync_count'].")";
    }
    $rs=$global['db']->Execute($sql);
    if ($rs=== false) {
        print '41 error inserting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
    }
    
//
?>