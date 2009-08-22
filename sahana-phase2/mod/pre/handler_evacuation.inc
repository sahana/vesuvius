<?php
include_once 'lib_pre.inc';

function _shn_pre_get_best_shelters($area_uuid, $disaster){
	global $global;
	$loc_uuid = _shn_pre_get_threat_area_location($area_uuid);
	$sql = "SELECT area_uuid, area, capacity FROM pre_shelter_area WHERE loc_uuid = '$loc_uuid' AND area_uuid IN " .
		"(SELECT area_uuid FROM pre_shelter_disaster WHERE disaster_uuid = '$disaster')";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		echo '<h4>Suitable areas in same location</h4>';
		$th_items[] = array('Area', 'Capacity', 'Available Capacity', 'Select');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$tb_items[] = array(
						$res->fields['area'],
						$res->fields['capacity'],
						_shn_pre_get_shelter_available_capacity($res->fields['area_uuid'], $disaster),
						'<a href="index.php?mod=pre&act=evacuation&seq=alct_frm&sht_id='.$res->fields['area_uuid'].'">Select</a>');
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No suitable area for shelters has not been identified in same area');
	}
}

function _shn_pre_get_other_shelters($area_uuid, $disaster){
	global $global;
	$loc_uuid = _shn_pre_get_threat_area_location($area_uuid);
	$sql = "SELECT area_uuid, area, capacity, loc_uuid FROM pre_shelter_area WHERE loc_uuid <> '$loc_uuid' AND area_uuid IN " .
		"(SELECT area_uuid FROM pre_shelter_disaster WHERE disaster_uuid = '$disaster')";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		echo '<h4>Suitable areas in other location</h4>';
		$th_items[] = array('Area', 'Location', 'Capacity', 'Available Capacity', 'Select');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$tb_items[] = array(
						$res->fields['area'],
						_shn_pre_get_location_string($res->fields['loc_uuid']),
						$res->fields['capacity'],
						_shn_pre_get_shelter_available_capacity($res->fields['area_uuid'], $disaster),
						'<a href="index.php?mod=pre&act=evacuation&seq=alct_frm&sht_id='.$res->fields['area_uuid'].'">Select</a>');
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No suitable area for shelters has not been identified in other area');
	}
}

function _shn_pre_add_allocate_form(){
	shn_form_fopen('evacuation',null, array('req_message'=>false));
	shn_form_fsopen(_('Allocation people to shelters'));
	shn_form_hidden(array('seq'=>'alct_add'));
	shn_form_label(_('Area : '), _shn_pre_get_threat_area_name($_SESSION['area_uuid']));
	shn_form_text(_('Available Population : '), 'population', 'readonly="true"', array('value'=> _shn_pre_get_threat_area_unallocated_population($_SESSION['area_uuid'], $_SESSION['disaster'])));
	shn_form_text('Available Capacity : ', 'capacity', 'readonly="true"', array('value'=> _shn_pre_get_shelter_available_capacity($_SESSION['shelter_uuid'], $_SESSION['disaster'])));
	shn_form_text('Allocation : ', 'allocate', null, array('req'=>true));
    shn_form_submit(_('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_pre_add_allocate_db(){
	global $global;
	$sql = "INSERT INTO pre_evacuation VALUES('{$_SESSION['area_uuid']}', '{$_SESSION['shelter_uuid']}', '{$_SESSION['disaster']}', '{$_SESSION['allocate']}')";
	$res = $global['db']->Execute($sql);
	if($res != false){
		add_confirmation('Allocation is successful');
		_shn_pre_list_evacuation_per_area_disaster($_SESSION['area_uuid'], $_SESSION['disaster']);
		if(_shn_pre_get_threat_area_unallocated_population($_SESSION['area_uuid'], $_SESSION['disaster'])){
			echo '<a href="index.php?mod=pre&act=evacuation&seq=show_shlt&area_id='.$_SESSION['area_uuid'].'&dis_id='.$_SESSION['disaster'].'">Allocate for same location</a>';
		}
		//echo '<a href="index.php?mod=pre&act=evacuation&seq=show_shlt&shlt_id='.$_SESSION['shelter_uuid'].'&dis_id='.$_SESSION['disaster'].'">Allocate to same location</a>';;
	}
	else{
		echo $global['db']->ErrorMsg();
	}
}

function _shn_pre_add_it_allocate(){
	shn_form_fopen('evacuation',null, array('req_message'=>false));
	shn_form_hidden(array('seq'=>'alct_add_it'));
	shn_form_submit(_('Add It'));
	shn_form_fclose();
}
