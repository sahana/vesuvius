<?php
/**
* The Sahana Disaster Preparedness System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Chamara Caldera <chamaracal@gmail.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

include_once 'lib_pre.inc';
include_once 'lib_pre_frm.inc';

function _shn_pre_list_recovery_plan($duuid, $public = false){
	global $global;
	if($_POST['access'] == '1'){
		$public = true;
	}
	$sql = "SELECT id, method, priority FROM pre_disaster_recovery WHERE id IN (SELECT rec_id FROM pre_recovery_plan WHERE disaster_uuid = '$duuid'" ;
	if($public){
		$sql .= " AND access = '1')";
	}
	else{
		$sql .= " AND access = '0')";
	}
	if(isset($_POST['effect']) && $_POST['effect'] != ''){
		$sql .= " AND effect = '".$_POST['effect']."'";
	}
	if(isset($_POST['status']) && $_POST['status'] != ''){
		$sql .= " AND disaster_status = '".$_POST['status']."'";
	}
	if(isset($_POST['term']) && $_POST['term'] != ''){
		$sql .= " AND term='".$_POST['term']."'";
	}
	$sql .= " ORDER BY priority" ;
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$th_items[] = array('Recovery Method', 'Priority', 'Show Areas', 'Add Area', 'Edit');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$tb_items[] = array(
								'<a href="index.php?mod=pre&act=list_rec_plan&seq=list_rec&rec_id='.$res->fields['id'].'">'.$res->fields['method'].'</a>',
								$res->fields['priority'],
								'<a href="index.php?mod=pre&act=list_rec_plan&seq=list_area&disaster='.$duuid.'&rec_id='.$res->fields['id'].'">Show</a>',
								'<a href="index.php?mod=pre&act=rec_plan&seq=add_area_frm&disaster='.$duuid.'&rec_id='.$res->fields['id'].'">Select</a>',
								'<a href="index.php?mod=pre&act=rec_plan&seq=edit_frm&access='.$public.'&rec_id='.$res->fields['id'].'">Edit</a>');
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('Recovery Plan has not construct yet...');
	}
}

function _shn_pre_recovery_list_filter($disaster_uuid){
	global $global;
	$sql1 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_recovering_term'";
	$res1 = $global['db']->Execute($sql1);
	$term[''] = 'All';
	for($i = 0; $res1->RecordCount() > $i; $i++){
		$term[$res1->fields['code']] = $res1->fields['dis'];
		$res1->MoveNext();
	}
	
	$effect[''] = 'All';
	$sql2 = "SELECT f.option_description AS des ,f.option_code AS code FROM field_options AS f, pre_disaster_effects AS d WHERE f.option_code = d.effect AND d.disaster_uuid = '$disaster_uuid'";
	$res2 = $global['db']->Execute($sql2);
	for($i = 0; $res2->RecordCount() > $i; $i++){
		$effect[$res2->fields['code']] = $res2->fields['des'];
		$res2->MoveNext();
	}
	
	$status[''] = 'All';
	$sql3 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_disaster_status'";
	$res3 = $global['db']->Execute($sql3);
	for($i = 0; $res3->RecordCount() > $i; $i++){
		$status[$res3->fields['dis']] = $res3->fields['dis'];
		$res3->MoveNext();
	}
	
	$access = array('0'=>'System', '1'=>'Public');
	
	echo '<table><tr><td>';
	shn_form_fopen('list_rec_plan', '', '', array('req'=>false));
	shn_form_hidden(array('seq'=>'list'));
	shn_form_hidden(array('disaster'=>$disaster_uuid));
	shn_form_select($effect, 'Effect', 'effect', 'onChange=submit(this)');
	shn_form_fclose();
	echo '</td><td>';
	shn_form_fopen('list_rec_plan', '', '', array('req'=>false));
	shn_form_hidden(array('seq'=>'list'));
	shn_form_hidden(array('disaster'=>$disaster_uuid));
	shn_form_select($status, 'Disaster Status', 'status', 'onChange=submit(this)');
	shn_form_fclose();
	echo '</td><td>';
	shn_form_fopen('list_rec_plan', '', '', array('req'=>false));
	shn_form_hidden(array('seq'=>'list'));
	shn_form_hidden(array('disaster'=>$disaster_uuid));
	shn_form_select($term, 'Term', 'term', 'onChange=submit(this)');
	shn_form_fclose();	
	echo '</td><td>';
	shn_form_fopen('list_rec_plan', '', '', array('req'=>false));
	shn_form_hidden(array('seq'=>'list'));
	shn_form_hidden(array('disaster'=>$disaster_uuid));
	shn_form_select($access, 'Access', 'access', 'onChange=submit(this)');
	shn_form_fclose();
	echo '</td></tr></table><br>';
} 

function _shn_pre_list_rec_plan_area($duuid, $rec_id){
	global $global;
	$sql = "SELECT a.area_uuid, a.area, a.loc_uuid, d.threat_level FROM pre_threat_area AS a, pre_threat_area_disaster AS d WHERE a.area_uuid = d.area_uuid AND d.disaster_uuid = '$duuid' AND a.area_uuid IN (SELECT area_uuid FROM pre_area_rec_plan WHERE disaster_uuid = '$duuid' AND rec_id = '$rec_id')";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() <= 0){
		_shn_pre_print_alert('No area has been assigned for this recovery method');
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

switch($_REQUEST['seq']){
	case '':
		_shn_pre_print_header('List Recovery Plan');
		_shn_pre_list_disaster_selection('list_rec_plan', 'list');
		break;
	case 'list':
		$_SESSION['disaster'] = $_REQUEST['disaster'];
		_shn_pre_print_header('List Recovery Plan for '._shn_pre_get_disaster_name($_REQUEST['disaster']));
		_shn_pre_recovery_list_filter($_REQUEST['disaster']);
		_shn_pre_list_recovery_plan($_REQUEST['disaster']);
		break;
	case 'list_rec':
		_shn_pre_print_header('List Details of Recovery Method');
		_shn_pre_get_recovery_details($_REQUEST['rec_id']);
		echo '<a href="index.php?mod=pre&act=list_rec_plan&seq=list&disaster='.$_SESSION['disaster'].'">Back</a>';
		break;
	case 'list_area':
		_shn_pre_print_header('List of areas '._shn_pre_get_recovery_name($_REQUEST['rec_id']));
		_shn_pre_list_rec_plan_area($_REQUEST['disaster'], $_REQUEST['rec_id']);
		
		break;
	default:
		break;
}

