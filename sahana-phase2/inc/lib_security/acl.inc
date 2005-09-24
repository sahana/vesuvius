<?php
include("3rdparty/ACL/gacl.class.php");
require_once("3rdparty/ACL/gacl_api.class.php");

function checkpermission($aco,$aro){
echo $aco;
echo $aro;

$gacl_options = array(
                                                                'debug' => 'TRUE',
                                                                'items_per_page' => 100,
                                                                'max_select_box_items' => 100,
                                                                'max_search_return_items' => 200,
                                                                'db_type' => 'mysql',
                                                                'db_host' => 'localhost',
                                                                'db_user' => 'sahana',
                                                                'db_password' => 'sahanapwd',
                                                                'db_name' => 'sahanaACL',
                                                                'db_table_prefix' => 'gacl_',
                                                                'caching' => FALSE,
                                                                'force_cache_expire' => TRUE,
                                                                'cache_dir' => '/tmp/phpgacl_cache',
                                                                'cache_expire_time' => 600
                                                        );

$gacl_api = new gacl_api($gacl_options);


$gacl_api->acl_check('system',$aco,'users',$aro);
return gacl;
}

function addACO($aco){
$result = $gacl_api->add_object('system', 'Enable - Login',$aco, 10, 0, 'ACO'); //Must specifiy Object Type.

if ($result !== FALSE) {
    echo "Created ACO sucessfully. <br>\n";
} else {
   echo "Error creating ACO.<br>\n";
}
unset($result);
}

function addARO($aro){

$gacl_options = array(
                                                                'debug' => 'TRUE',
                                                                'items_per_page' => 100,
                                                                'max_select_box_items' => 100,
                                                                'max_search_return_items' => 200,
                                                                'db_type' => 'mysql',
                                                                'db_host' => 'localhost',
                                                                'db_user' => 'sahana',
                                                                'db_password' => 'sahanapwd',
                                                                'db_name' => 'sahanaACL',
                                                                'db_table_prefix' => 'gacl_',
                                                                'caching' => FALSE,
                                                                'force_cache_expire' => TRUE,
                                                                'cache_dir' => '/tmp/phpgacl_cache',
                                                                'cache_expire_time' => 600
                                                        );

$gacl_api = new gacl_api($gacl_options);

$result = $gacl_api->add_object('users','user name is'.$aro,$aro, 10, 0, 'ARO');

if ($result !== FALSE) {
        echo "Created $aro  sucessfully. <br>\n";
} else {
   echo "Error creating $aro  ARO.<br>\n";
}
unset($result);
}


