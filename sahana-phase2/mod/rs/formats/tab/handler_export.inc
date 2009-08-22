<?php

global $global;
header("Content-type: application/x-msdownload");
header("Content-Disposition: attachment; filename=sahana_".date('Y-m-d').".txt");
header("Pragma: no-cache");
header("Expires: 0"); 

$global['db']->SetFetchMode(ADODB_FETCH_NUM);
$recordSet = $global['db']->Execute($_SESSION['export_sql']);//check weather the sql is empty
if (!$recordSet){
    add_error($conn->ErrorMsg());
    return;
}
else
foreach($recordSet as $row){
    $line = '';
    $data = '';
    foreach($row as $value) {
        if ((!isset($value)) OR ($value == "")) {
            $value = "\t";
        } 
        else {
            $value = str_replace('"', '""', $value);
            $value = '"' . $value . '"' . "\t";
        }
        $line .= $value;
    }
    $data .= trim($line)."\n";
    $data = str_replace("\r","",$data);
    echo $data;
}
