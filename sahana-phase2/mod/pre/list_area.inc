<?php
include_once 'lib_pre.inc';

function _shn_pre_list_threat_area(){
	global $global;
	$sql = "SELECT area_uuid, area, loc_uuid FROM pre_threat_area";
	$extra_opt = array('return'=>'true');
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	if($res->RecordCount() > 0){
		$th_items[] = array('Area', 'Location', 'disaster');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$sql2 = "SELECT disaster_uuid, threat_level, status FROM pre_threat_area_disaster WHERE area_uuid = '".$res->fields['area_uuid']."'";
			$res2 = $global['db']->Execute($sql2);
			$disaster = '';		
			for($i1 = 0; $i1 < $res2->RecordCount(); $i1++){
    			$disaster .= '<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$res2->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res2->fields['disaster_uuid']).'</a> - '.$res2->fields['threat_level'].' - '.$res2->fields['status'].'<br>';    	
    			$res2->MoveNext();
    		}
			$tb_items[] = array(
						'<a href="index.php?mod=pre&act=list_threat_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
						_shn_pre_get_location_string($res->fields['loc_uuid']),
						$disaster
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
		$th_items[] = array('Area', 'address', 'Location', 'disaster', 'Status');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$sql2 = "SELECT disaster_uuid FROM pre_shelter_disaster WHERE area_uuid = '".$res->fields['area_uuid']."'";
			$res2 = $global['db']->Execute($sql2);
			$disaster = '';
			for($i1 = 0; $i1 < $res2->RecordCount(); $i1++){
    			$disaster .= '<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$res2->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res2->fields['disaster_uuid']).'</a>  <br>';    	
    			$res2->MoveNext();
    		}
    		$status = ($res->fields['status'] == 0)?'Free': 'Occupied';
			$tb_items[] = array(
						'<a href="index.php?mod=pre&act=list_shelter_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
						$res->fields['address'],
						_shn_pre_get_location_string($res->fields['loc_uuid']),
						$disaster,
						$status
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

/**
 * return areas under threat for selected disaster
 */
 function _shn_pre_disaster_threat_area($disaster_uuid){
 	global $global;
 	$sql = "SELECT a.area_uuid, a.area, a.loc_uuid, d.threat_level, a.population FROM pre_threat_area AS a, pre_threat_area_disaster AS d WHERE a.area_uuid = d.area_uuid AND d.disaster_uuid = '$disaster_uuid' ORDER BY threat_level";
 	$res = $global['db']->Execute($sql);
 	echo $global['db']->ErrorMsg();
 	if($res->RecordCount() > 0){
 		_shn_pre_print_header('Areas under threat of '._shn_pre_get_disaster_name($disaster_uuid));
 		$th_items[] = array('Area', 'Location', 'Threat Level', 'Population', 'Unallocated', 'Allocate shelter');
 		for($i = 0; $i < $res->RecordCount(); $i++){
 			if(($unallocated = _shn_pre_get_threat_area_unallocated_population($res->fields['area_uuid'], $disaster_uuid)) > 0){
 				$tb_items[] = array(
 							'<a href="index.php?mod=pre&act=list_threat_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
 							_shn_pre_get_location_string($res->fields['loc_uuid']),
 							$res->fields['threat_level'],
 							$res->fields['population'],
 							$unallocated,
 							'<a href="index.php?mod=pre&act=evacuation&seq=show_shlt&area_id='.$res->fields['area_uuid'].'&dis_id='.$disaster_uuid.'">'.'Select</a>');
 			}
 			$res->MoveNext();
 		}
 	shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));	
 	}
 }

/**
 * form interface for searching area under threat
 */
 function _shn_pre_search_threat_area_form(){
 	global $global;
	$sql = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	$threat[''] = '';
	for($i = 0; $i < $res->RecordCount(); $i++){
		$threat[$res->fields['des']] = $res->fields['des'];
		$res->MoveNext();
	}
 	shn_form_fopen('list_threat_area');
    shn_form_hidden(array('seq'=>'search'));
    shn_form_fsopen("Select searching criterias");
    shn_form_text('Area Name', 'area');
    shn_form_text('Disaster', 'disaster');
    shn_form_select($threat, 'Threat', 'threat');
    shn_form_submit('Search');
    shn_form_fsclose();
    shn_form_fclose();
 }

/**
 * search a area under threat
 */
 function _shn_pre_search_threat_area_sql(){
 	$sql = "SELECT area_uuid, area, loc_uuid FROM pre_threat_area";
 	if($_POST['area'] != ''){
 		$sql .= " WHERE area = '".$_POST['area']."'";
 		if($_POST['disaster'] != ''){
 			$sql .= " AND area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid IN (SELECT disaster_uuid FROM pre_disaster WHERE disaster = '".$_POST['disaster']."'))";
 		}
 		if($_POST['threat'] != ''){
 			$sql .= " AND area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE threat_level = '".$_POST['threat']."')";
 		}
 	}
 	else{
 		if($_POST['threat'] != ''){
 			$sql .= " WHERE area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE threat_level = '".$_POST['threat']."')";
 			if($_POST['disaster'] != ''){
 				$sql .= " AND area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid IN (SELECT disaster_uuid FROM pre_disaster WHERE disaster = '".$_POST['disaster']."'))";
 			}
 		} 
 		else{
 			if($_POST['disaster'] != ''){
 				$sql .= " WHERE area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid IN (SELECT disaster_uuid FROM pre_disaster WHERE disaster = '".$_POST['disaster']."'))";
 			}
 		}		
 	}
 	return $sql;
 }
 
 function _shn_pre_search_threat_area(){
 	global $global;
 	$sql = _shn_pre_search_threat_area_sql();
	$extra_opt = array('return'=>'true');
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	if($res->RecordCount() > 0){
		$th_items[] = array('Area', 'Location', 'Disaster', 'Edit');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$sql2 = "SELECT disaster_uuid, threat_level FROM pre_threat_area_disaster WHERE area_uuid = '".$res->fields['area_uuid']."'";
			$res2 = $global['db']->Execute($sql2);
			$disaster = '';
			$bool = false;
			for($i1 = 0; $i1 < $res2->RecordCount(); $i1++){
    			$disaster .= '<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$res2->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res2->fields['disaster_uuid']).'</a> - '.$res2->fields['threat_level'].'<br>';    	
    			$res2->MoveNext();
    		}
    		$url = '<a href="index.php?mod=pre&act=add_threat_area&seq=edit&area='.$res->fields['area_uuid'].'">Edit</a>';
			$tb_items[] = array(
						'<a href="index.php?mod=pre&act=list_threat_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
						_shn_pre_get_location_string($res->fields['loc_uuid']),
						$disaster,
						$url
								);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert("No area in under threat has been identified yet");
	}
 }

/**
 * search a area for shelter 
 */
function _shn_pre_search_shelter_area_sql(){
	$sql = "SELECT area_uuid, area, address FROM pre_shelter_area";
	if($_POST['area'] != ''){
		$sql .= " WHERE area = '".$_POST['area']."'";
		if($_POST['disaster'] != ''){
			$sql .= " AND area_uuid IN (SELECT area_uuid FROM pre_shelter_disaster WHERE disaster_uuid IN (SELECT disaster_uuid FROM pre_disaster WHERE disaster = '".$_POST['disaster']."'))";
		}
		if($_POST['land_type'] != null){
			$sql .= " AND land_type = '".$_POST['land_type']."'";
		}
		if($_POST[''] != null){
			$sql .= " AND ownership = '".$_POST['owner']."'";
		}
	}
	else{
		if($_POST['disaster'] != ''){
			$sql .= " WHERE area_uuid IN (SELECT area_uuid FROM pre_shelter_disaster WHERE disaster_uuid IN (SELECT disaster_uuid FROM pre_disaster WHERE disaster = '".$_POST['disaster']."'))";
			if($_POST['land_type'] != null){
				$sql .= " AND land_type = '".$_POST['land_type']."'";
			}
			if($_POST[''] != null){
				$sql .= " AND ownership = '".$_POST['owner']."'";
			}
		}
		else{
			if($_POST['land_type'] != null){
				$sql .= " WHERE land_type = '".$_POST['land_type']."'";
				if($_POST[''] != null){
					$sql .= " AND ownership = '".$_POST['owner']."'";
				}
			}
			else{
				if($_POST[''] != null){
					$sql .= " WHERE ownership = '".$_POST['owner']."'";
				}
			}
		}
	}
	return $sql;
}

function _shn_pre_search_shelter_area(){
	global $global;
 	$sql = _shn_pre_search_shelter_area_sql();
	$extra_opt = array('return'=>'true');
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	if($res->RecordCount() > 0){
		$th_items[] = array('Area', 'Address', 'Disaster', 'Edit');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$sql2 = "SELECT disaster_uuid FROM pre_shelter_disaster WHERE area_uuid = '".$res->fields['area_uuid']."'";
			$res2 = $global['db']->Execute($sql2);
			$disaster = '';
			for($i1 = 0; $i1 < $res2->RecordCount(); $i1++){
    			$disaster .= '<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$res2->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res2->fields['disaster_uuid']).'</a>'.'<br>';    	
    			$res2->MoveNext();
    		}
    		$url = '<a href="index.php?mod=pre&act=add_shelter_area&seq=edit&area='.$res->fields['area_uuid'].'">Edit</a>';
			$tb_items[] = array(
						'<a href="index.php?mod=pre&act=list_shelter_area&seq=list&area='.$res->fields['area_uuid'].'">'.$res->fields['area'].'</a>',
						$res->fields['address'],
						$disaster,
						$url
								);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert("No area in under threat has been identified yet");
	}
}

/**
 * form interface for searching areas suitable for shelters
 */
function _shn_pre_search_shelter_area_form(){
	$building = array(''=>'' ,'land'=>'land', 'building'=>'building');
	$ownership = array(''=>'', 'govenment'=>'govenment', 'private'=>'private');
	
	shn_form_fopen('list_shelter_area');
    shn_form_hidden(array('seq'=>'search'));
    shn_form_fsopen("Select searching criterias");
    shn_form_text('Area Name', 'area');
    shn_form_text('Disaster', 'disaster');
    shn_form_select($building, 'Land Type', 'land_type');
    shn_form_select($ownership, 'Ownership', 'owner');
    shn_form_submit('Search');
    shn_form_fsclose();
    shn_form_fclose();
}
