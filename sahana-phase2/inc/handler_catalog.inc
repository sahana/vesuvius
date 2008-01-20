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
 * @author     Ishan Liyanage <ishan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */
 
function shn_text_catalog_unit_cat()
{
	/*require_once('../3rd/adodb/adodb.inc.php');
	require_once('../conf/sysconf.inc');
	//Make the connection to $global['db']
	$db = NewADOConnection($conf['db_engine']);
	$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
	t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);*/
    global $global;
    $db=$global['db'];
	$cat=$_GET{"cat"};

	$q="select unit_uuid,name from ct_unit where unit_type_uuid ='$cat'";
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



function shn_text_catalog_sub_cat(){
	/*require_once('../3rd/adodb/adodb.inc.php');
	require_once('../conf/sysconf.inc');
	//Make the connection to $global['db']
	$db = NewADOConnection($conf['db_engine']);
	$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);*/
    global $global;
    $db=$global['db'];
	$cat=$_GET{"cat"};
	$flag=$_GET{"flag"};
	if($flag==false)
	{
		$q="select ct_uuid,name from ct_catalogue where parentid='{$cat}'";
		$res_child=$db->Execute($q);
	}
	else if($flag==true)
	{
		$q="select ct_uuid,name from ct_catalogue where parentid='{$cat}' and final_flag='0' ";
		$res_child=$db->Execute($q);
	}

	$res=$res.","."";
	$res=$res.","."";

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
?>