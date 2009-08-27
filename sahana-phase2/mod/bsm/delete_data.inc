<?php
function _shn_bsm_delete_symptom($case_uuid, $symptom)
{
	global $global;
	$db = $global['db'];
	$sql = "DELETE FROM bsm_case_symp WHERE case_uuid = '$case_uuid' AND symptom = '$symptom'";
	//print $sql;
	$res = $db->Execute($sql);
	if($res){
		add_warning(_($symptom.' deleted from the '. $case_uuid.' Case'));
	} else {
		add_error(_('Error removing Symptom from the Case'));
	}
}

function _shn_bsm_delete_sign($case_uuid, $sign)
{
	global $global;
	$db = $global['db'];
	$sql = "DELETE FROM bsm_case_sign WHERE case_uuid = '$case_uuid' AND sign = '$sign'";
	//print $sql;
	$res = $db->Execute($sql);
	if($res){
		add_warning(_($sign.' deleted from the '. $case_uuid.' Case'));
	} else {
		add_error(_('Error removing Symptom from the Case'));
	}
}
?>