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

function _shn_pre_change_access($public){
	global $global;
	$access = !$public? 1: 0;
	$sql = "UPDATE pre_recovery_plan SET access = '$access' WHERE rec_id = '{$_SESSION['rec_id']}'";
	$res = $global['db']->Execute($sql);
	if($res === false){
		add_error('Unable to edit');
	}
	else{
		add_confirmation('Edit successfully');
	}
}

function _shn_pre_delete_plan_rec(){
	global $global;
	$sql1 = "DELETE FROM pre_recovery_plan WHERE rec_id = '{$_SESSION['rec_id']}'";
	$res1 = $global['db']->Execute($sql1);
	if($res1 === false){
		add_error('Unable to delete');
	}
	else{
		$sql2 = "DELETE FROM pre_area_rec_plan WHERE rec_id = '{$_SESSION['rec_id']}'";
		$res2 = $global['db']->Execute($sql2);
		add_confirmation('Delete successfull');
	}
}

function _shn_pre_edit_form($public){
	shn_form_fopen('rec_plan', '', array('req'=>true));
	shn_form_fsopen('Edit Recovery Plan');
	shn_form_hidden(array('seq'=>'edit_db'));
	shn_form_hidden(array('access'=>$public));
	if($public)
		shn_form_submit('Change to System', 'name="public"');
	else
		shn_form_submit('Change to Public', 'name="private"');
	shn_form_submit('Delete', 'name="delete"');
	shn_form_fsclose();
	shn_form_fclose();
}

function _shn_pre_search_recovery_method_frm($disaster){
	shn_form_fopen('rec_plan',null, array('req_message'=>false));
	shn_form_fsopen(_('Search Recovery Methods'));
	shn_form_hidden(array('seq'=>'sch_rec'));
	shn_form_hidden(array('dis_id'=>$disaster));
	_shn_pre_sch_recovery($disaster);
	shn_form_submit('Search');
	shn_form_fsclose();
	shn_form_fclose();
}

function _shn_pre_is_added_rec($rec_id, $duuid){
	global $global;
	$sql = "SELECT rec_id FROM pre_recovery_plan WHERE rec_id IN (SELECT id FROM pre_disaster_recovery WHERE id = '$rec_id') AND disaster_uuid = '$duuid'";
	$res = $global['db']->Execute($sql);
	return $res->RecordCount();
}

function _shn_pre_search_recovery_method($res){
	if($res === false){
		_shn_pre_print_alert('No recovery method has been found');
		echo '<br><a href="index.php?mod=pre&act=rec_plan&seq=sch_rec_frm&disaster='.$_SESSION['disaster'].'"> Select another recovery method</a> :: ';
	}
	else{
		$th_items[] = array('Recovery Method', 'Priority', 'Select', 'Access');
		
		shn_form_fopen('rec_plan', null, array('req_message'=>false));
		shn_form_fsopen('Select Recovery Methods');
		shn_form_hidden(array('seq'=>'add_plan'));
		for($i = 0; $i < $res->RecordCount(); $i++){
			if(_shn_pre_is_added_rec($res->fields['id'], $_SESSION['disaster']) == 0)
			$tb_items[] = array(
								$res->fields['method'],
								$res->fields['priority'],
								'<input type="checkbox" name="rec_'.$res->fields['id'].'">',
								'<input type="checkbox" name="access_'.$res->fields['id'].'">');
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
		echo '<br>';
		shn_form_submit('ADD');
		shn_form_fsclose();
		shn_form_fclose();
	}
}

function _shn_pre_add_recovery_plan(){
	global $global;
	$res = _shn_pre_get_recovery_by_status($_SESSION['disaster'], $_SESSION['term'], $_SESSION['effect'], $_SESSION['status'], 'return');
	$error_count = 0;
	$full_count = 0;
	for($i = 0; $i < $res->RecordCount(); $i++){
		if(isset($_POST['rec_'.$res->fields['id']])){
			$full_count++;
			$access = (isset($_POST['access_'.$res->fields['id']])) ? 1 : 0;
			$sql = "INSERT INTO pre_recovery_plan(disaster_uuid, rec_id, access) VALUES('{$_SESSION['disaster']}', '".$res->fields['id']."', '$access')";
			$result = $global['db']->Execute($sql);
			echo $global['db']->ErrorMsg();
			if($result === false){
				$error_count++;
			}
		}
		$res->MoveNext();
	}
	if($error_count < $full_count){
		add_confirmation($full_count-$error_count.' has been added successfilly');
	}
	if($error_count > 0){
		add_error($error_count.' errors occured');
	}
}

function _shn_pre_add_rec_plan_area_frm($duuid, $rec_id){
	global $global;
	$sql = "SELECT area, area_uuid FROM pre_threat_area WHERE area_uuid NOT IN (SELECT area_uuid FROM pre_area_rec_plan WHERE disaster_uuid = '$duuid' AND rec_id = '$rec_id') AND area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid = '$duuid')";
	$res = $global['db']->Execute($sql);
	shn_form_fopen('rec_plan', null, null, array('req'=>false));
	shn_form_fsopen('Assign recovery methods');
	shn_form_hidden(array('seq'=>'add_area'));
	for($i = 0; $i < $res->RecordCount(); $i++){
		shn_form_checkbox($res->fields['area'], $res->fields['area_uuid'], '', array('value'=>$res->fields['area_uuid']));
		$res->MoveNext();
	}
	shn_form_submit('Assign');
	shn_form_fsclose();
	shn_form_fclose();
}

function _shn_pre_add_area_rec_plan($duuid, $rec_id){
	global $global;
	$sql1 = "SELECT area_uuid FROM pre_threat_area WHERE area_uuid NOT IN (SELECT area_uuid FROM pre_area_rec_plan WHERE disaster_uuid = '$duuid' AND rec_id = '$rec_id') AND area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid = '$duuid')";
	$res1 = $global['db']->Execute($sql1);
	$error_count = 0;
	$full_count = 0;
	if($res1 != false && $res1->RecordCount() > 0){
		for($i = 0; $i < $res1->recordCount(); $i++){
			if(isset($_POST[$res1->fields['area_uuid']])){
				$full_count++;
				$sql2 = "INSERT INTO pre_area_rec_plan(disaster_uuid, rec_id, area_uuid) VALUES('$duuid', '$rec_id', '{$res1->fields['area_uuid']}')";
				$res2 = $global['db']->Execute($sql2);
				echo $global['db']->ErrorMsg();
				if($res2 === false){
					$error_count++;
				}
			}
			$res1->MoveNext();
		}
	}
	if($error_count < $full_count){
		add_confirmation($full_count.' no of areas added successfuly');
	}
	else{
		if($error_count > 0){
			add_error($error_count.' errors occured');
		}
	}
}

switch($_REQUEST['seq']){
	case '':
		_shn_pre_print_header('Recovery Planning');
		_shn_pre_list_disaster_selection('rec_plan', 'sch_rec_frm');
		break;
	case 'sch_rec_frm':
		_shn_pre_print_header('Search Recovery Methods for '._shn_pre_get_disaster_name($_REQUEST['disaster']));
		$_SESSION['disaster'] = $_REQUEST['disaster'];
		_shn_pre_search_recovery_method_frm($_SESSION['disaster']);		
		echo '<a href="index.php?mod=pre&act=rec_plan">Back</b>';
		break;
	case 'sch_rec':
		_shn_pre_print_header('Recovery Methods for '._shn_pre_get_disaster_name($_POST['dis_id']));
		$_SESSION['term'] = $_POST['term'];
		$_SESSION['effect'] = $_POST['effect'];
		$_SESSION['status'] = $_POST['status'];
		$res = _shn_pre_get_recovery_by_status($_SESSION['disaster'], $_POST['term'], $_POST['effect'], $_POST['status'], 'return');
		_shn_pre_search_recovery_method($res);		
		echo '<a href="index.php?mod=pre&act=rec_plan&seq=sch_rec_frm&disaster='.$_SESSION['disaster'].'">Back</b>';
		break;
	case 'add_plan':
		_shn_pre_add_recovery_plan();
		break;
	case 'add_area_frm':
		$_SESSION['disaster'] = $_REQUEST['disaster'];
		$_SESSION['rec_id'] = $_REQUEST['rec_id'];
		_shn_pre_add_rec_plan_area_frm($_SESSION['disaster'], $_SESSION['rec_id']);
		echo '<a href="index.php?mod=pre&act=list_rec_plan&seq=list&disaster='.$_SESSION['disaster'].'">Back</a>';
		break;
	case 'add_area':
		_shn_pre_add_area_rec_plan($_SESSION['disaster'], $_SESSION['rec_id']);
		break;
	case 'edit_frm':
		$_SESSION['rec_id'] = $_REQUEST['rec_id'];
		_shn_pre_edit_form($_REQUEST['access']);
		break;
	case 'edit_db':
		if(isset($_POST['delete'])){
			_shn_pre_delete_plan_rec();
		}
		else{
			_shn_pre_change_access($_REQUEST['access']);
		}
	default:
		break;
}
