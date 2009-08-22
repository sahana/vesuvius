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

function _shn_pre_list_disaster_selection($action, $seq){
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
		shn_form_fopen($action,'', array('req_message'=>true,));
    	shn_form_hidden(array('seq'=>$seq));
    	shn_form_fsopen("Select the disaster");
    	shn_form_select($disaster, 'Disaster', 'disaster', 'onChange="submit(this);"',array('br'=>false, 'req'=>true));
    	shn_form_fsclose();
    	shn_form_fclose();
	}
	else{
		_shn_pre_print_alert('No disaster has been identified yet');
	}
}

function _shn_pre_sch_recovery($disaster_uuid){
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
	
	shn_form_select($effect, 'Effect', 'effect');
	shn_form_select($term, 'Term of advantages','term');
	shn_form_select($status, 'Status of disaster','status');
	
}

function _shn_pre_list_area_selection($action, $seq){
	global $global;
	$sql = "SELECT area_uuid, area FROM pre_threat_area";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$area = array();
		$area[''] = '--Select a area--';
		for($i = 0; $i < $res->RecordCount(); $i++){
			$area[$res->fields['area_uuid']] = $res->fields['area'];
			$res->MoveNext();
		}
		shn_form_fopen($action,'', array('req_message'=>true,));
    	shn_form_hidden(array('seq'=>$seq));
    	shn_form_fsopen("Select the area");
    	shn_form_select($area, 'Area Under Threat', 'area', 'onChange="submit(this);"',array('br'=>false, 'req'=>true));
    	shn_form_fsclose();
    	shn_form_fclose();
	}
	else{
		_shn_pre_print_alert('No Area under threat has been identified yet');
	}
}

function _shn_pre_edit_contact_form($res1){
	    	shn_form_fsopen("Contact Details");
?>

	<div calss="info">
<?php
	echo 'Contact details of the person who is responsible to reponse for the disasters';
?>
	<br></div>
<?php
	shn_form_checkbox('New Person', 'new');
	shn_form_text('Name', 'textname', '', array('value'=>_shn_pre_get_person_name($res1->fields['person_uuid'])));
	shn_form_hidden(array('name'=>$res1->fields['person_uuid']));	
	shn_form_textarea('Address', 'address', '', array('value'=>_shn_pre_get_contact($res1->fields['person_uuid'], 'address')));
	shn_form_text('Contact No', 'tel_no', '', array('value'=>_shn_pre_get_contact($res1->fields['person_uuid'], 'tel_no')));
	shn_form_text('Mobile No', 'mobile_no', '', array('value'=>_shn_pre_get_contact($res1->fields['person_uuid'], 'mobile_no')));
	shn_form_text('Fax', 'fax_no', '', array('value'=>_shn_pre_get_contact($res1->fields['person_uuid'], 'fax_no')));
	shn_form_text('Email', 'email', '', array('value'=>_shn_pre_get_contact($res1->fields['person_uuid'], 'email')));
	shn_form_fsclose();
}

function _shn_pre_delete_area_form($area_uuid, $action){
	shn_form_fopen($action, '', array('req'=>true));
	shn_form_fsopen('Delete the area');
	shn_form_hidden(array('seq'=>'del'));
	shn_form_hidden(array('area_uuid'=>$area_uuid));
	shn_form_submit('Delete');
	shn_form_fsclose();
	shn_form_fclose();
}
