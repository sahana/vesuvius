<?php

include_once 'lib_pre.inc';
include_once 'lib_pre_frm.inc';


function _shn_pre_list_shelter_allocation(){
	global $global;
	$sql = "SELECT shelter_uuid, SUM(allocation) AS allocation FROM pre_evacuation WHERE disaster_uuid = '".$_SESSION['disaster']."' GROUP BY shelter_uuid";
	$res = $global['db']->Execute($sql);
	echo $global['db']->ErrorMsg();
	if($res->RecordCount() > 0){
		$th_items[] = array('Shelter', 'location', 'Allocation', 'Description of Alloc:');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$shelter = '<a href="index?mod=pre&act=list_shelter_area&seq=list&area='.$res->fields['shelter_uuid'].'">';
			$shelter .= _shn_pre_get_shelter_area_name($res->fields['shelter_uuid']).'</a>';
			$tb_items[] = array(
							$shelter,
							_shn_pre_get_location_string(_shn_pre_get_shelter_area_location($res->fields['shelter_uuid'])),
							$res->fields['allocation'],
							_shn_pre_get_shelter_disaster_allocation($res->fields['shelter_uuid'], $_SESSION['disaster'])
							);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No evacuation planning has been done');
	}
}

function _shn_pre_get_shelter_disaster_allocation($shelter, $disaster){
	global $global;
	$sql = "SELECT area_uuid, SUM(allocation) AS allocation FROM pre_evacuation WHERE shelter_uuid = '$shelter' AND disaster_uuid = '$disaster' GROUP BY area_uuid";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$alloc = '';
		for($i = 0; $i < $res->RecordCount(); $i++){
			$area = '<a href="index.php?mod=pre&act=list_threat_area&seq=list&area='.$res->fields['area_uuid'].'">';
			$area .= _shn_pre_get_threat_area_name($res->fields['area_uuid']).'</a>';
			$alloc .= $area.' : '.$res->fields['allocation'].'<br>';
			$res->MoveNext();
		}
		return $alloc;
	}
	else{
		_shn_pre_print_alert('No evacuation to this shelter');
		return false;
	}
}

switch($_REQUEST['seq']){
	case '':
		_shn_pre_print_header('List evacuation planning');
		_shn_pre_list_disaster_selection('list_evac', 'list');
		break;
	case 'list':
		$_SESSION['disaster'] = $_POST['disaster'];
		_shn_pre_print_header('Evacuation planning for '._shn_pre_get_disaster_name($_SESSION['disaster']));
		_shn_pre_list_shelter_allocation();
		break;
	case 'show_alloc':
		$_SESSION['shelter_uuid'] = $_REQUEST['shlt_id'];
		_shn_pre_get_shelter_disaster_allocation($_SESSION['shelter_uuid'], $_SESSION['disaster']);
		break;
	default:
		break;
}


