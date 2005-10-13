<?php

// provide the nice display name for the DVR module
$conf['mod_dvr_name'] = "People Registry";

// list the available permissions for the dvr modules
$conf['shn_perms_dvr'] = array(
    'create' => 'AUG',
    'delete' => 'A',
    'update' => 'U',
    'view'   => 'AUG',
);

// assign the functions to permissions to be used by the ACL
$conf['shn_dvr_view'] = array('create'); 
?>
