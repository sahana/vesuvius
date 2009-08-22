<?php
/**
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
 * @author     Ishan Liyanage <ishan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */



function shn_location_get_loc(){
	
    global $global;
    $db=$global['db'];
	$level=$_GET{"lvl"}+1;
	$parent=$_GET{"sel"};

	$q = "SELECT location.name,location.loc_uuid,parent_id FROM location WHERE location.opt_location_type='{$level}' AND parent_id='{$parent}' ORDER BY location.name";
	//echo $q;
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

function _shn_get_locations(){
	
    global $global;
    $db=$global['db'];
	$level=1;
	$sel_id=$_GET{"sel"};

	if($_GET{"type"}=="camp"){
		$q="SELECT location_id FROM camp_general WHERE c_uuid='{$sel_id}'";
		$res=$db->Execute($q);
		if($res->EOF)
		return;
		$loc_id=$res->fields["location_id"];
	}else if($_GET{"type"}=="poc"){
		$q = "SELECT location_id FROM location_details WHERE poc_uuid='{$sel_id}'";
		$res=$db->Execute($q);
		if($res->EOF)
		return;
		$loc_id=$res->fields["location_id"];
	}else{
		$loc_id=$_GET{"sel"};
	}



	$q = "SELECT parent_id,opt_location_type FROM location WHERE loc_uuid='{$loc_id}'";
	$res=$db->Execute($q);
	if($res->EOF)
	return;
	 
	$parent=$res->fields["parent_id"];
	$header.="loc_dir".",".$parent;
	$header.=",".$res->fields["opt_location_type"];
	 
	$level=$res->fields["opt_location_type"];

	$q = "SELECT location.name,location.loc_uuid FROM location WHERE location.opt_location_type='{$level}' AND parent_id='{$parent}' ORDER BY location.name";
	//echo $q;
	$res_child=$db->Execute($q);
	if($res_child->EOF)
	return;
	$count=0;
	while(!$res_child->EOF){
		if($count==0){
			$res_data=$res_data.$res_child->fields["loc_uuid"];
			$res_data=$res_data.":".$res_child->fields["name"];
		}else{
			$res_data=$res_data.",".$res_child->fields["loc_uuid"];
			$res_data=$res_data.":".$res_child->fields["name"];
		}
		if($res_child->fields["loc_uuid"]==$loc_id){
			$header.=",".$count;
		}
		$count++;
		$res_child->MoveNext();
	}
	//echo $header;
	// echo $res_data;
	
	 
	echo $header.";".$res_data;
}


function _shn_get_level_location(){
	require_once('../3rd/adodb/adodb.inc.php');
	require_once('../conf/sysconf.inc.php');
	//Make the connection to $global['db']
	$db = NewADOConnection($conf['db_engine']);
	$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);


	$level=$_GET{"sel"};
	if($level==1){
		echo "none,";
	}
	$q = "SELECT location.name,location.loc_uuid,parent_id FROM location WHERE location.opt_location_type={$level}";
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


