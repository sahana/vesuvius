<?php

function _shn_die_csv_import($file){
    $_SESSION['import_data']=null;
    //open file
    $file = fopen($file, "r");
    //count the fields
    $table_info=array();
    $field_count=0;
    while (($data = fgetcsv($file, 1000, ",")) !== FALSE) {
        if($field_count!=count($data)){
            $field_count=count($data);
            $c++;
        }
        $_SESSION['import_data']['table'.$c][]=$data;
    }

    //alter the temp tables

    //parse the data to tmp table

    //close file
    fclose($file);
    return;
}
