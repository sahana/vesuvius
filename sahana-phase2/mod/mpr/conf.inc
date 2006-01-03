<?php

// provide the nice display name for the DVR module
$conf['mod_mpr_name'] = "Missing Person Registry";

$conf['mod_mpr']['search']['limit'] = 5;

$conf['mod_mpr']['location']['upper_limit'] = 1;
$conf['mod_mpr']['location']['lower_limit'] = 4;

// $action_sequence => caption
$conf['mod_mpr']['edit']['tabs'] = array('Edit Details', 'Add Tracker', 
'Upload Picture', 'Confirm');
?>
