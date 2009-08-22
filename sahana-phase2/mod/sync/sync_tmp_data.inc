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

//this process must not end in the middle
ignore_user_abort(true);

//if the overwrite data is yes update the tables;
if($_SESSION['oed']=='yes'){
        foreach($_SESSION['sync']['tables'] as $table)
            shn_sync_update_duplicate($table);
}

//controler to handel the threshold value
switch ($_SESSION['threshold']){
    case '1': //case to check locations
        //include_once('handler_location_sync.inc');
    break;
    case '0':
    break;
}

//loop through remaining temperory tables and merge
foreach($_SESSION['sync']['tables'] as $table)
    shn_sync_delete_duplicate($table);

foreach($_SESSION['sync']['tables'] as $table)
    shn_sync_insert($table);

//

//add the instance data to the instance table
$sql="SELECT * FROM sync_instance WHERE base_uuid='".$_SESSION['sync_inst']['base_uuid']."'";
$row=$global['db']->GetRow($sql);
if(count($row)>0){
    $sql="UPDATE sync_instance SET owner='".$_SESSION['sync_inst']['owner']."',contact='".$_SESSION['sync_inst']['contact']."',last_update='".$_SESSION['sync_inst']['last_update']."',sync_count=sync_count+1 WHERE base_uuid='".$_SESSION['sync_inst']['base_uuid']."'";
}
else{
    $sql="INSERT INTO sync_instance VALUES('".$_SESSION['sync_inst']['base_uuid']."','".$_SESSION['sync_inst']['owner']."','".$_SESSION['sync_inst']['contact']."','server','".$_SESSION['sync_inst']['last_update']."',1)";
}
$rs=$global['db']->Execute($sql);
if ($rs=== false) {
    print 'error inserting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
}


