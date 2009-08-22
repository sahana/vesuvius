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

function _shn_pre_area_rec_plan($area_uuid, $disaster_uuid){
	global $global;
	$sql = "SELECT method, effect, priority, term, disaster_status FROM pre_disaster_recovery WHERE id IN " .
			"(SELECT rec_id FROM pre_recovery_plan WHERE access = '1' AND rec_id IN " .
			"(SELECT rec_id FROM pre_area_rec_plan WHERE area_uuid = '$area_uuid' AND disaster_uuid = '$disaster_uuid'))";
	$res = $global['db']->Execute($sql);
	echo $global['db']->ErrorMsg();
	if($res === false || $res->RecordCount() <= 0){
		_shn_pre_print_alert('No recovery method has assigned');
	}
	else{
		$th_items[] = array('Method', 'Effect', 'Priority', 'Term', 'Status');
		for($i = 0; $res->RecordCount() > $i; $i++){
			$tb_items[] = array(
								$res->fields['method'],
								_shn_pre_get_field_name($res->fields['effect']),
								$res->fields['priority'],
								_shn_pre_get_field_name($res->fields['term']),
								$res->fields['disaster_status']);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
}

function _shn_pre_show_disaster($res){
	echo '<h4>Possible Disasters</u></h4>';
	shn_form_fopen('', '', '', array('req'=>false));
	shn_form_fsopen('Possible Disasters');
	echo '<strong>';
	for($i = 0; $i < $res->RecordCount(); $i++){
		echo '<li><a href="index.php?mod=pre&act=dis_report&seq=dis_show&dis_id='.$res->fields['disaster_uuid'].'">'._shn_pre_get_disaster_name($res->fields['disaster_uuid']).'</a></li>';
		$res->MoveNext();
	}
	echo '</strong><br>';
	$puuid = _shn_pre_get_threat_area_puuid($_SESSION['area_uuid']);
	if($puuid != false){
		
		shn_form_fsopen('Contact details of authorized person');
		shn_form_label('Name : ', _shn_pre_get_person_name($puuid));;
		shn_form_label('Address : ', _shn_pre_get_contact($puuid, 'address'));
		shn_form_label('Contact No :', _shn_pre_get_contact($puuid, 'tel_no'));
		shn_form_label('Mobile No : ', _shn_pre_get_contact($puuid, 'mobile_no'));
		shn_form_label('Fax No   ', _shn_pre_get_contact($puuid, 'fax_no'));
		shn_form_label('Email : ', _shn_pre_get_contact($puuid, 'email'));
		shn_form_fsclose();
	}
	shn_form_fsclose();
	shn_form_fclose();
}

switch($_REQUEST['seq']){
	case '':
		_shn_pre_print_header('Public Disaster Report');
		_shn_pre_list_area_selection('dis_report', 'list');
		break;
	case 'list':
		$_SESSION['area_uuid'] = $_REQUEST['area'];
		_shn_pre_print_header('Public Disaster Report for '._shn_pre_get_threat_area_name($_SESSION['area_uuid']));
		$res = _shn_pre_get_threat_area_disaster($_SESSION['area_uuid']);
		if($res === false){
			_shn_pre_print_alert('No disaster');
		}
		else{
			_shn_pre_show_disaster($res);
		}
		echo '<br><a href="index.php?mod=pre&act=dis_report">Back</a>';
		break;
	case 'dis_show':
		$_SESSION['disaster'] = $_REQUEST['dis_id'];
		echo '<h4>'._shn_pre_get_disaster_name($_SESSION['disaster']).'</h4><br>';
		_shn_pre_get_disaster_details($_SESSION['disaster']);
		echo '<br><h5>Evacuation Plan</h5>';
		_shn_pre_get_area_disaster_evacuation($_SESSION['area_uuid'], $_SESSION['disaster']);
		echo '<br><a href="index.php?mod=pre&act=dis_report&seq=list&area='.$_SESSION['area_uuid'].'">Back</a>';
		echo ' :: <a href="index.php?mod=pre&act=dis_report&seq=rec_plan">Show Recovery Plan</a>';
		break;
	case 'rec_plan':
		_shn_pre_print_header('Public Reovery Plan for '._shn_pre_get_threat_area_name($_SESSION['area_uuid']).' on '._shn_pre_get_disaster_name($_SESSION['disaster']));
		_shn_pre_area_rec_plan($_SESSION['area_uuid'], $_SESSION['disaster']);
		echo '<br><a href="index.php?mod=pre&act=dis_report&seq=dis_show&dis_id='.$_SESSION['disaster'].'">Back</a>';
		break;
	default :
		break;
}

