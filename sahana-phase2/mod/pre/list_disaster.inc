<?php

include_once 'lib_pre.inc';
include_once 'lib_pre_frm.inc';

function _shn_pre_show_history_area($wrn_id, $duuid){
	global $global;
	$sql = "SELECT a.area_uuid, a.area, a.loc_uuid, d.threat_level FROM pre_threat_area AS a, pre_threat_area_disaster AS d WHERE a.area_uuid = d.area_uuid AND d.disaster_uuid = '$duuid' AND a.area_uuid IN (SELECT area_uuid FROM pre_area_history WHERE warn_uuid = '$wrn_id')";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() <= 0){
		_shn_pre_print_alert('No area has been assigned for this incident');
	}
	else{
		$th_items[] = array('Area', 'Location', 'Threat Level', 'Remove');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$tb_items[] = array(
								$res->fields['area'],
								_shn_pre_get_location_string($res->fields['loc_uuid']),
								$res->fields['threat_level'],
								'Remove');
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
}

function _shn_pre_show_disaster_history($duuid){
	global $global;
	$sql = "SELECT wrn_uuid, disaster_uuid, registered_date, expired_date, type FROM pre_disaster_history WHERE disaster_uuid = '$duuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$th_items[] = array('Registered Date', 'Expired Date', 'Type', 'Areas');
		for($i = 0; $i <$res->RecordCount(); $i++){
			$tb_items[] = array(
								$res->fields['registered_date'],
								$res->fields['expired_date'],
								$res->fields['type'],
								'<a href="index.php?mod=pre&act=list_disaster&seq=show_history_area&wrn_id='.$res->fields['wrn_uuid'].'&dis_id='.$res->fields['disaster_uuid'].'">Show Areas</a>');
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No history records has been found');
	}
}

function _shn_pre_search_disaster_sql(){
	$sql = "SELECT disaster_uuid, disaster, possibility FROM pre_disaster WHERE ";
	if($_POST['threat'] == ''){
		$sql .= "'1' = '1'";
	}
	else{
		$sql .= "possibility = '".$_POST['threat']."'";
	}
	if($_POST['disaster'] != NULL){
		$sql .= " AND disaster = '".$_POST['disaster']."'";
	}
	if($_POST['reason'] != NULL){
		$sql .= "AND reason = '".$_POST['reason']."'";
	}
	if($_POST['status'] != ''){
		$sql .= "AND status = '".$_POST['status']."'";
	}
	return $sql;
}


/**
 * Search for a disaster
 * by disaster
 * by reason
 * by threat level
 */
function _shn_pre_search_disaster(){
	global $global;
	$sql = _shn_pre_search_disaster_sql();
	$extra_opt = array('return'=>'true', 'post'=>true);
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	$th_items[] = array('Disaster', 'Possibility', 'Warning', 'Edit');
	if($res->RecordCount() > 0){
		for($i = 0; $i < $res->RecordCount(); $i++){
			$duuid = $res->fields['disaster_uuid'];
			$disaster = $res->fields['disaster'];
			$possibility = $res->fields['possibility'];
			$tb_items[] = array(
							'<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$duuid.'">'.$disaster.'</a>',
							$possibility,
							'<a href="index.php?mod=pre&act=add_warning&dis_id='.$duuid.'"> Select </a>',
							'<a href="index.php?mod=pre&act=add_disaster&seq=edit&dis_id='.$duuid.'">Edit</a>'
							);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No such disaster has identified yet');
		echo '<h4>List of all disasters</h4>';
		_shn_pre_list_disaster();
	}
}

function _shn_pre_sch_disaster_form(){
	global $global;
	$sql1 = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res1 = $global['db']->Execute($sql1);
	$threat[''] = 'Any';
	for($i= 0 ; $i < $res1->RecordCount(); $i++){
		$threat[$res1->fields['des']] = $res1->fields['des'];
		$res1->MoveNext();
	}
	
	$sql3 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_disaster_status'";
	$res3 = $global['db']->Execute($sql3);
	$status[''] = '';
	for($i = 0; $res3->RecordCount() > $i; $i++){
		$status[$res3->fields['dis']] = $res3->fields['dis'];
		$res3->MoveNext();
	}
	
	shn_form_fopen('list_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Search a disaster'));
	shn_form_hidden(array('seq'=>'sch_dis'));
	shn_form_text('Disaster','disaster');
	shn_form_text('Reason', 'reason');
	shn_form_select($status, 'Status', 'status');
	shn_form_select($threat, 'Threat Lavel', 'threat');
	shn_form_submit('Search');
	shn_form_fsclose();
	shn_form_fclose();
}

switch ($_REQUEST['seq']){
	case '':
		_shn_pre_print_header("List of identified disasters");
		_shn_pre_list_disaster();
		break;
	case 'list_rec':
		$duuid = $_REQUEST['dis_id'];
		_shn_pre_print_header("Recoverying methods of "._shn_pre_get_disaster_name($duuid));
		_shn_pre_get_recovery_by_disaster($duuid);
		break;
	case 'sch_dis_frm':
		_shn_pre_print_header("Search identified disasters");
		_shn_pre_sch_disaster_form();
		break;
	case 'sch_dis':
		_shn_pre_print_header("Result for searching");
		_shn_pre_search_disaster();
		echo '<br><a href="index.php?mod=pre&act=list_disaster&seq=sch_dis_frm">Back</a>';
		break;
	case 'history':
		_shn_pre_print_header('Disaster history');
		_shn_pre_list_disaster_selection('list_disaster', 'show_history');
		break;
	case 'show_history':
		$_SESSION['disaster'] = $_REQUEST['disaster'];
		_shn_pre_print_header('History of '._shn_pre_get_disaster_name($_SESSION['disaster']));
		_shn_pre_show_disaster_history($_SESSION['disaster']);
		echo '<br><a href="index.php?mod=pre&act=list_disaster&seq=history">Back</a>';
		break;
	case 'show_history_area':
		_shn_pre_print_header('Areas of incident');
		_shn_pre_show_history_area($_REQUEST['wrn_id'], $_REQUEST['dis_id']);
		echo '<br><a href="index.php?mod=pre&act=list_disaster&seq=show_history&disaster='.$_REQUEST['dis_id'].'">Back</a>';
		break;
	default:
		break;
}
