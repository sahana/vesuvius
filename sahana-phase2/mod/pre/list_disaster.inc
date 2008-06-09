<?php

include_once 'lib_pre.inc';

function _shn_pre_sch_disaster_form(){
	global $global;
	$sql1 = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res1 = $global['db']->Execute($sql1);
	$threat[''] = 'Any';
	for($i= 0 ; $i < $res1->RecordCount(); $i++){
		$threat[$res1->fields['des']] = $res1->fields['des'];
		$res1->MoveNext();
	}
	shn_form_fopen('list_disaster',null, array('req_message'=>false));
	shn_form_fsopen(_('Search a disaster'));
	shn_form_hidden(array('seq'=>'sch_dis'));
	shn_form_text('Disaster','disaster');
	shn_form_text('Reason', 'reason');
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
		_shn_pre_search_disaster();
	default:
		break;
}
?>