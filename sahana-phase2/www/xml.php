<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

/* }}} */
$act=$_GET{"act"};
if($act=='add_loc'){
    _shn_get_level_location();
}else if ($act=='sub_cat'){
		_shn_get_sub_catalogs();
	}else{
	    _shn_get_children();
	}


function _shn_get_sub_catalogs(){
require_once('../3rd/adodb/adodb.inc.php');
require_once('../conf/sysconf.inc');
//Make the connection to $global['db']
$db = NewADOConnection($conf['db_engine']);
$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);

$cat=$_GET{"cat"};

	$q="select ct_uuid,name from ct_catalogue where parentid='{$cat}'";
    $res_child=$db->Execute($q);
   	if(!$res_child==NULL && !$res_child->EOF){
    		while(!$res_child->EOF){
        		$res=$res.",".$res_child->fields[0];
        		$res=$res.",".$res_child->fields[1];
        		$res_child->MoveNext();
    		}
		echo $res;
   	}else{
   		echo "null,";
	}
}

function _shn_get_children(){
require_once('../3rd/adodb/adodb.inc.php');
require_once('../conf/sysconf.inc');
//Make the connection to $global['db']
$db = NewADOConnection($conf['db_engine']);
$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);

$level=$_GET{"lvl"}+1;
$parent=$_GET{"sel"};
$q = "select location.name,location.location_id,parent_id from location where location.opt_location_type={$level} and parent_id={$parent}";
    $res_child=$db->Execute($q);
    if($res_child->EOF)
        return;
    while(!$res_child->EOF){
        $res=$res.",".$res_child->fields[1];
        $res=$res.",".$res_child->fields[0];
        $res_child->MoveNext();
    }
echo $res;
}

function _shn_get_level_location(){
require_once('../3rd/adodb/adodb.inc.php');
require_once('../conf/sysconf.inc');
//Make the connection to $global['db']
$db = NewADOConnection($conf['db_engine']);
$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);


$level=$_GET{"sel"};
if($level==1){
echo "none,";
}
$q = "select location.name,location.location_id,parent_id from location where location.opt_location_type={$level}";
    $res_child=$db->Execute($q);
    if($res_child->EOF)
        return;
    while(!$res_child->EOF){
        $res=$res.",".$res_child->fields[1];
        $res=$res.",".$res_child->fields[0];
        $res_child->MoveNext();
    }
echo $res;
}
?>

