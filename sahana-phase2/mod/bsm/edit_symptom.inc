<?php
function shn_bsm_edit_load()
{
	global $global;
	$db = $global['db'];
	$rtnid = trim($_REQUEST['rtnid']);
	$sql = "SELECT * FROM bsm_symptom WHERE symptom='$rtnid' AND deactivate_dt IS NULL";
	$res = $db->Execute($sql);
//print $sql;
	$_SESSION['bsm']['edit']['symptom'] = $res->fields['symptom'];
	$_SESSION['bsm']['edit']['symp_enum'] = $res->fields['symp_enum'];
	$_SESSION['bsm']['edit']['symp_code'] = $res->fields['symp_code'];
	$_SESSION['bsm']['edit']['symp_priority'] = $res->fields['symp_priority'];
	$_SESSION['bsm']['edit']['symp_description'] = $res->fields['symp_desc'];
}

function shn_bsm_edit_entry($fopen_name = 'edit_symptom',$fsopen_name='Edit Symptom'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

		$arrary = array();
		$arrary['high'] = _('High');
		$arrary['medium'] = _('Medium');
		$arrary['low'] = _('Low');

    //include('service_type.inc');

    shn_form_fsopen(_('Symptom'));
    shn_form_text(_('Symptom '),'symptom','size="30" readonly=true',array('help' => _('Enter Symptom.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['symptom']));
		shn_form_text(_('Symptom Enum '),'symptom_enum','size="10"',array('help' => _('Enter Symptom Enum.'), 'req'=>false , 'value'=>$_SESSION['bsm']['edit']['symp_enum']));
    shn_form_text(_('Symptom Code'),'symptom_code','size="30"',array('help' => _('Enter Symptom Code.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['symp_code']));
		shn_form_select($arrary, _('Symptom Priority'), 'symptom_priority', null, array('help'=>_('Select Symptom Priority'), 'value'=>$_SESSION['bsm']['edit']['symp_priority']));
		shn_form_textarea(_('Symptom Description '),'symptom_desc',null,array('help' => _('Enter Symptom Description.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['symp_description']));
		//shn_form_text(_('Symptom Priority'),'symptom_priority','size="30"',array('help' => _('Enter Symptom Priority.'), 'req'=>false));
		
    shn_form_fsclose();
		    
		shn_form_hidden(array('case_uuid'=>$_REQUEST['rtnid']));
    shn_form_submit(_('Edit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_edit_symptom()
{
	global $global;
	$db = $global['db'];
	$symptom = trim($_POST['symptom']);
	$symptom_enum = trim($_POST['symptom_enum']);
	$symptom_code = trim($_POST['symptom_code']);
	$symptom_priority = trim($_POST['symptom_priority']);
	$symptom_description = trim($_POST['symptom_desc']);
	$sym_pre = $_SESSION['bsm']['edit']['symptom'];
	$sql = "UPDATE bsm_symptom SET symp_desc='{$symptom_description}', symp_code='{$symptom_code}', symp_priority='{$symptom_priority}', symp_enum='{$symptom_enum}' WHERE symptom='$sym_pre'";
	$res=$db->Execute($sql);
	if($res){
		add_confirmation(_('Record Updated Successfully'));
	} else {
		add_error(_('An error occured while updating the data'));
	}
}
?>