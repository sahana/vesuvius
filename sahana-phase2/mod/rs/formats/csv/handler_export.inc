<?php

global $global;
include_once($global['approot'].'3rd/adodb/toexport.inc.php');
header("Content-type: application/x-msdownload");
header("Content-Disposition: attachment; filename=sahana_".date('Y-m-d').".csv");
header("Pragma: no-cache");
header("Expires: 0"); 

$global['db']->SetFetchMode(ADODB_FETCH_NUM);
$recordSet = $global['db']->Execute($_SESSION['export_sql']);//check weather the sql is empty
if (!$recordSet){
    add_error($conn->ErrorMsg());
    return;
}
else
    print rs2csv($recordSet);
