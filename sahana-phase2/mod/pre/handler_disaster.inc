<?php

include_once $global['approot'].'/inc/lib_form.inc';

include_once 'lib_pre.inc';
include_once 'lib_pre_frm.inc';
//include_once $global['approot'].'/inc/lib_uuid.inc';

function _shn_pre_delete_recovery_by_edit($duuid){
	global $global;
	$sql = "DELETE FROM pre_disaster_recovery WHERE disaster_uuid = '$duuid' AND effect NOT IN (SELECT effect FROM pre_disaster_effects WHERE disaster_uuid = '$duuid')";
	$global['db']->Execute($sql);
}

function _shn_pre_edit_disaster_form($duuid){
	
	_shn_pre_print_header('Add a suspectable disaster');
	
	global $global;
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	$result = $res->GetArray();
	$selections = array();
	foreach ($result as $r){
		$selections[$r['option_description']] = $r['option_description'];
	}
	shn_form_fopen('add_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Edit Disaster'));
	shn_form_hidden(array('seq'=>'edit_db'));
	shn_form_hidden(array('dis_id'=>$duuid));
	shn_form_text(_('Disaster : '),'disaster','',array('req'=>true, 'value'=>$_SESSION['disaster']));
	shn_form_text(_('Reason : '),'reason','',array('value'=>$_SESSION['reason']));
	shn_form_select($selections, 'Threat Level','threat_level',array('selected'=>$_SESSION['possibility']));
	shn_form_textarea(_('Description'), 'description', '', array('value'=>$_SESSION['description']));
	shn_form_fsopen('Possible effects');
	shn_form_opt_checkbox('opt_disaster_effect', array('selected'=>$_SESSION['effects']));
	shn_form_fsclose();
	shn_form_submit(_('Submit'));
	shn_form_fsclose();
	shn_form_fclose();
	
	shn_form_fopen('add_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Delete Disaster'));
	shn_form_hidden(array('seq'=>'del'));
	shn_form_hidden(array('dis_id'=>$duuid));
	shn_form_submit('Delete');
	shn_form_fsclose();
	shn_form_fclose();
	
	
}

function _shn_pre_edit_disaster($duuid){
	global $global;
	$sql ="SELECT disaster, reason, possibility, description FROM pre_disaster WHERE disaster_uuid = '$duuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$_SESSION['disaster'] = $res->fields['disaster'];
		$_SESSION['reason'] = $res->fields['reason'];
		$_SESSION['possibility'] = $res->fields['possibility'];
		$_SESSION['description'] = $res->fields['description'];
		
		$sql2 = "SELECT effect FROM pre_disaster_effects WHERE disaster_uuid = '$duuid'";
		$res2 = $global['db']->Execute($sql2);
		$eff_arr = $res2->GetArray();
		$effect = array();
		foreach($eff_arr as $eff){
			array_push($effect, $eff['effect']);
		}
		$_SESSION['effects'] = $effect;
		_shn_pre_edit_disaster_form($duuid);
	}
}

function _shn_pre_edit_disaster_db($duuid){
	global $global;
	$disaster = $_SESSION['disaster'];
	$reason = $_SESSION['reason'];
	$possibility = $_SESSION['possibility'];
	$description = $_SESSION['description'];
	$effects = $_SESSION['effects'];
	$sql1 = "UPDATE pre_disaster SET disaster = '$disaster', reason = '$reason', possibility = '$possibility', description = '$description' WHERE disaster_uuid = '$duuid'";
	$res1 = $global['db']->Execute($sql1);
	$sql2 = "DELETE FROM pre_disaster_effects WHERE disaster_uuid = '$duuid'";
	$res2 = $global['db']->Execute($sql2);
	echo $global['db']->ErrorMsg();
	
	foreach($effects as $eff){
		$sql3 = "INSERT INTO pre_disaster_effects VALUES('$duuid', '$eff')";
		$res3 = $global['db']->Execute($sql3);
	echo $global['db']->ErrorMsg();
	}
	add_confirmation('Edit succusfull');
	_shn_pre_delete_recovery_by_edit($duuid);
	_shn_pre_get_disaster_details($duuid);
}

function _shn_pre_edit_disaster_session($duuid){
	if ($_POST['disaster'] == NULL){
		add_error('Please give a disaster');
		_shn_pre_edit_disaster($duuid);
	}
	else{
		$_SESSION['duuid'] = $duuid;
		$_SESSION['disaster'] = $_POST['disaster'];
		$_SESSION['reason'] = $_POST['reason'];
		$_SESSION['possibility'] = $_POST['threat_level'];
		$_SESSION['description'] = $_POST['description'];
		$_SESSION['effects'] = $_POST['opt_disaster_effect'];
		if(_shn_pre_is_disaster($_SESSION['disaster']) > 1){
			_shn_pre_print_alert($_SESSION['disaster'].' is already identified.');
			/////////////////////
			shn_form_fopen('add_disaster',null, array('req_message'=>false));
			shn_form_hidden(array('seq'=>'edit_it'));
			shn_form_hidden(array('dis_id'=>$duuid));
			shn_form_submit('Edit It Anyway');
			echo '<br><strong><em>Or</em></strong><br>';
			echo '[<a href="index.php?mod=pre&act=list_disaster&act=sch_dis_frm">Edit another disaster</a>]';
		}
		else{
			_shn_pre_edit_disaster_db($duuid);
		}
	}
}

function _shn_pre_edit_recovery_db($id){
	if($_POST['recovery'] == NULL){
		add_error('Recovery should not be null');
		_shn_pre_edit_recovery_form($id);
	}
	else{
		global $global;
		$sql = "UPDATE pre_disaster_recovery SET method = '".$_POST['recovery']."', effect = '".$_POST['effect']."', term = '".$_POST['term']."', disaster_status = '".$_POST['status']."', priority = '".$_POST['priority']."'WHERE id = '$id'";
		$res = $global['db']->Execute($sql);
		if($res != false){
			add_confirmation('Successfully edited');
			_shn_pre_get_recovery_by_disaster($_POST['duuid']);
		}
	}
}

function _shn_pre_edit_recovery_form($id){
	_shn_pre_print_header('Edit Recovering Deatils');
	global $global;	
	
	$sql = "SELECT disaster_uuid, method, effect, term, disaster_status, priority FROM pre_disaster_recovery WHERE id = '$id'";
	$res = $global['db']->Execute($sql);
	
	$sql1 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_recovering_term'";
	$res1 = $global['db']->Execute($sql1);
	for($i = 0; $res1->RecordCount() > $i; $i++){
		$term[$res1->fields['code']] = $res1->fields['dis'];
		$res1->MoveNext();
	}
	
	$sql2 = "SELECT f.option_description AS des ,f.option_code AS code FROM field_options AS f, pre_disaster_effects AS d WHERE f.option_code = d.effect AND d.disaster_uuid = '".$res->fields['disaster_uuid']."'";
	$res2 = $global['db']->Execute($sql2);
	for($i = 0; $res2->RecordCount() > $i; $i++){
		$effect[$res2->fields['code']] = $res2->fields['des'];
		$res2->MoveNext();
	}
	
	$sql3 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_disaster_status'";
	$res3 = $global['db']->Execute($sql3);
	for($i = 0; $res3->RecordCount() > $i; $i++){
		$status[$res3->fields['dis']] = $res3->fields['dis'];
		$res3->MoveNext();
	}
	
	$priority = array('Low'=>'Low', 'Moderate'=>'Moderate', 'High'=>'High');
	//$status = array('before'=>'before', 'on'=>'on', 'after'=>'after');
		
	shn_form_fopen('add_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Edit a Recovery Method'));
	shn_form_hidden(array('seq'=>'edit_rec_db'));
	shn_form_hidden(array('id'=>$id));
	shn_form_hidden(array('duuid'=>$res->fields['disaster_uuid']));
	shn_form_textarea(_('Recovery : '),'recovery','',array('req'=>true, 'value'=>$res->fields['method']));
	shn_form_select($effect, 'Effect', 'effect');
	shn_form_select($term, 'Term of advantages','term');
	shn_form_select($status, 'Status of disaster','status');
	shn_form_select($priority, 'Priority','priority');
	shn_form_submit('Edit');
	shn_form_fsclose();
	shn_form_fclose();	
}

function _shn_pre_add_recovery_db(){
	$id = 'rcv' . time();
	$duuid = $_POST['dis_id'];
	$recovery = $_POST['recovery'];
	$term = $_POST['term'];
	$priority = $_POST['priority'];
	$status = $_POST['status'];
	$effect = $_POST['effect'];
	global $global;
	$sql = "INSERT INTO pre_disaster_recovery VALUES('$id', '$duuid', '$effect', '$recovery', '$term', '$status', '$priority')";
	$res = $global['db']->Execute($sql);
	if($res != false){
		add_confirmation($recovery.'<br>added as a '._shn_pre_get_field_name($term).' term recovery method for recover for '._shn_pre_get_field_name($effect).' caused by '._shn_pre_get_disaster_name($duuid));
	} 
	echo '[<a href="index.php?mod=pre&act=default"> Back </a>] ::';
	echo ' [<a href="index.php?mod=pre&act=list_disaster&seq=list_rec&dis_id='.$duuid.'"> [[List recovery details]] </a>] :: ';
	echo ' [<a href="index.php?mod=pre&act=add_disaster&seq=rec&dis_id='.$duuid.'"> [[Add another Recovery details]] </a>]';
}

function _shn_pre_add_recovery_form($disaster_uuid){
	_shn_pre_print_header('Add Recovering Deatils for '._shn_pre_get_disaster_name($disaster_uuid));
	global $global;
	$sql1 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_recovering_term'";
	$res1 = $global['db']->Execute($sql1);
	for($i = 0; $res1->RecordCount() > $i; $i++){
		$term[$res1->fields['code']] = $res1->fields['dis'];
		$res1->MoveNext();
	}
	
	$sql2 = "SELECT f.option_description AS des ,f.option_code AS code FROM field_options AS f, pre_disaster_effects AS d WHERE f.option_code = d.effect AND d.disaster_uuid = '$disaster_uuid'";
	$res2 = $global['db']->Execute($sql2);
	for($i = 0; $res2->RecordCount() > $i; $i++){
		$effect[$res2->fields['code']] = $res2->fields['des'];
		$res2->MoveNext();
	}
	
	$sql3 = "SELECT option_description AS dis, option_code AS code FROM field_options WHERE field_name = 'opt_disaster_status'";
	$res3 = $global['db']->Execute($sql3);
	for($i = 0; $res3->RecordCount() > $i; $i++){
		$status[$res3->fields['dis']] = $res3->fields['dis'];
		$res3->MoveNext();
	}
	
	$priority = array('Low'=>'Low', 'Moderate'=>'Moderate', 'High'=>'High');
	//$status = array('before'=>'before', 'on'=>'on', 'after'=>'after');
	shn_form_fopen('add_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Add a Recovery Method'));
	shn_form_hidden(array('seq'=>'add_rec'));
	shn_form_hidden(array('dis_id'=>$disaster_uuid));
	shn_form_textarea(_('Recovery : '),'recovery','',array('req'=>true));
	_shn_pre_sch_recovery($disaster_uuid);	
	shn_form_select($priority, 'Priority','priority');
	shn_form_submit('Submit');
	shn_form_fsclose();
	shn_form_fclose();
	
}

function _shn_pre_add_disaster_db(){
	global $global;
	$duuid = $_SESSION['duuid'];
	$disaster = $_SESSION['disaster'];
	$reason = $_SESSION['reason'];
	$possibility = $_SESSION['possibility'];
	$description = $_SESSION['description'];
	$effects = $_SESSION['effects'];
	$sql1 = "INSERT INTO pre_disaster VALUES('$duuid', '$disaster', '$reason', '$possibility', '$description', 'pre')";
	$res1 = $global['db']->Execute($sql1);
	foreach ($effects as $effect){
		$sql = "INSERT INTO pre_disaster_effects VALUES('$duuid', '$effect')";
		$res2 = $global['db']->Execute($sql);
	}
	if( $res1 != false){
		add_confirmation($disaster.' succusefully added');
		_shn_pre_get_disaster_details($duuid);
	}
	echo '[<a href="index.php?mod=pre&act=default"> Back </a>] ::';
	echo ' [<a href="index.php?mod=pre&act=add_disaster"> Add another disaster </a>] :: ';
	echo ' [<a href="index.php?mod=pre&act=add_disaster&seq=rec&dis_id='.$duuid.'"> Add Recovery details </a>]';
	return $duuid;
}

function _shn_pre_add_disaster_session(){
	if ($_POST['disaster'] == NULL){
		add_error('Please give a disaster');
		_shn_pre_add_disaster_form();
	}
	else{
		$_SESSION['duuid'] = shn_create_uuid('log');
		$_SESSION['disaster'] = $_POST['disaster'];
		$_SESSION['reason'] = $_POST['reason'];
		$_SESSION['possibility'] = $_POST['threat_level'];
		$_SESSION['description'] = $_POST['description'];
		$_SESSION['effects'] = $_POST['opt_disaster_effect'];
		if(_shn_pre_is_disaster($_SESSION['disaster']) > 0){
			_shn_pre_print_alert($_SESSION['disaster'].' is already identified.');
			/////////////////////
			shn_form_fopen('add_disaster',null, array('req_message'=>false));
			shn_form_hidden(array('seq'=>'add_it'));
			shn_form_submit('Add It Anyway');
			echo '<br><strong><em>Or</em></strong><br>';
			echo '[<a href="index.php?mod=pre&act=add_disaster">Add another disaster</a>]';
		}
		else{
			_shn_pre_add_disaster_db();
		}
	}
}

function _shn_pre_add_disaster_form(){
	
	_shn_pre_print_header('Add a suspectable disaster');
	
	global $global;
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	$result = $res->GetArray();
	$selections = array();
	foreach ($result as $r){
		$selections[$r['option_description']] = $r['option_description'];
	}
	shn_form_fopen('add_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Add a Disaster'));
	shn_form_hidden(array('seq'=>'add'));
	shn_form_text(_('Disaster : '),'disaster','',array('req'=>true));
	shn_form_text(_('Reason : '),'reason','','');
	shn_form_select($selections, 'Threat Level','threat_level');
	shn_form_textarea(_('Description'), 'description', '', '');
	shn_form_fsopen('Possible effects');
	shn_form_opt_checkbox('opt_disaster_effect');
	shn_form_fsclose();
	shn_form_submit(_('Submit'));
	shn_form_fsclose();
	shn_form_fclose();
}

	switch($_REQUEST['seq']){
		case '':
			_shn_pre_add_disaster_form();
			break;
		case 'add':
			//$_SESSION['disaster_uuid'] = $_POST['disaster_uuid'];
			_shn_pre_add_disaster_session();
			$duuid = $_SESSION['disaster_uuid'];
			
			break;
		case 'add_it':
			_shn_pre_add_disaster_db();
			break;
		case 'edit':
			$duuid = $_REQUEST['dis_id'];
			_shn_pre_edit_disaster($duuid);
			break;
		case 'edit_db':
			$duuid = $_REQUEST['dis_id'];
			_shn_pre_edit_disaster_session($duuid);
			break;
		case 'edit_it':
			$duuid = $_REQUEST['dis_id'];
			_shn_pre_edit_disaster_db($duuid);
			break;
		case 'del':
			$duuid = $_REQUEST['dis_id'];
			_shn_pre_delete_disaster($duuid);
			_shn_pre_list_disaster();
			break;
		case 'rec':
			$duuid = $_REQUEST['dis_id'];
			_shn_pre_add_recovery_form($duuid);
			break;
		case 'add_rec':
			if($_POST['recovery'] == NULL){
				add_error('Please give a recovering method');
				_shn_pre_add_recovery_form($_POST['dis_id']);
			}
			else{
				_shn_pre_add_recovery_db();
			}
			break;
		case 'edit_rec':
			$id = $_REQUEST['id'];
			_shn_pre_edit_recovery_form($id);
			break;
		case 'edit_rec_db':
			$id = $_POST['id'];
			_shn_pre_edit_recovery_db($id);
			break;
		case 'list':
			$duuid = $_REQUEST['dis_id'];
			_shn_pre_print_header("Datail description of "._shn_pre_get_disaster_name($duuid));
			_shn_pre_get_disaster_details($duuid);
			echo '[<a href="index.php?mod=pre&act=list_disaster"> Back </a>] ::';
			echo ' [<a href="index.php?mod=pre&act=add_disaster&seq=rec&dis_id='.$duuid.'"> Add Recovery details </a>] :: ';
			echo ' [<a href="index.php?mod=pre&act=list_disaster&seq=list_rec&dis_id='.$duuid.'"> List recovery details </a>] ::  ';
			echo '[<a href="index.php?mod=pre&act=add_disaster&seq=edit&dis_id='.$duuid.'">Edit</a>]';
			break;
		default:
			break;
	}
