<?php
include_once 'lib_pre.inc';

function _shn_pre_list_threat_area(){
	global $global;
	$sql = "SELECT area_uuid, area, loc_uuid FROM pre_threat_area";
	$extra_opt = array('return'=>'true');
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	if($res->RecordCount() > 0){
		$th_items[] = array('Area', 'Location', 'disaster', 'status');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$sql2 = "SELECT disaster_uuid, threat_level FROM pre_threat_area_disaster WHERE area_uuid = '".$res->fields['area_uuid']."'";
			$res2 = $global['db']->Execute($sql2);
			for($i = 0; $i < $res2->RecordCount(); $i++){
    			$disaster .= '<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$res2->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res2->fields['disaster_uuid']).'</a> - '.$res2->fields['threat_level'].'<br>';    	
    			$res2->MoveNext();
    		}
			$tb_items[] = array(
						'<a href="index.php?mod=pre&act=list_threat_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
						_shn_pre_get_location_string($res->fields['loc_uuid']),
						$disaster,
						'NOT YET'
								);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert("No area in under threat has been identified yet");
	}
}

function _shn_pre_list_shelter_area(){
	global $global;
	$sql = "SELECT area_uuid, area, loc_uuid, address FROM pre_shelter_area";
	$extra_opt = array('return'=>'true');
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	if($res->RecordCount() > 0){
		$th_items[] = array('Area', 'address', 'Location', 'disaster', 'status');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$sql2 = "SELECT disaster_uuid FROM pre_shelter_disaster WHERE area_uuid = '".$res->fields['area_uuid']."'";
			$res2 = $global['db']->Execute($sql2);
			for($i = 0; $i < $res2->RecordCount(); $i++){
    			$disaster .= '<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$res2->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res2->fields['disaster_uuid']).'</a> <br>';    	
    			$res2->MoveNext();
    		}
			$tb_items[] = array(
						'<a href="index.php?mod=pre&act=list_shelter_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
						$res->fields['address'],
						_shn_pre_get_location_string($res->fields['loc_uuid']),
						$disaster,
						'NOTයෙට'
								);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert("No area suitable for shelter has been identified yet");
	}
}

function _shn_pre_seach_disaster_area_form(){
	global $global;
	$sql = "SELECT disaster_uuid ,disaster FROM pre_disaster";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$disaster = array();
		$disaster[''] = '--Select a disaster--';
		for($i = 0; $i < $res->RecordCount(); $i++){
			$disaster[$res->fields['disaster_uuid']] = $res->fields['disaster'];
			$res->MoveNext();
		}
		shn_form_fopen('list_threat_area','', array('req_message'=>true,));
    	shn_form_hidden(array('seq'=>'sch_d'));
    	shn_form_fsopen("Select the disaster");
    	shn_form_select($disaster, 'Disaster', 'disaster', 'onChange="submit(this);"',array('br'=>false, 'req'=>true));
    	shn_form_fsclose();
    	shn_form_fclose();
	}
	else{
		_shn_pre_print_alert('No disaster has been identified yet');
	}
}

function _shn_pre_seach_disaster_area($disaster_uuid){
	global $global;
	$sql = "SELECT areaFROM WHERE";
}
?>