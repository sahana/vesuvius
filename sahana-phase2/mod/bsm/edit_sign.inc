<?php
function shn_bsm_edit_load()
{
	global $global;
	$db = $global['db'];
	$rtnid = trim($_REQUEST['rtnid']);
	$sql = "SELECT * FROM bsm_sign WHERE sign='$rtnid' AND deactivate_dt IS NULL";
	$res = $db->Execute($sql);
//print $sql;
	$_SESSION['bsm']['edit']['sign'] = $res->fields['sign'];
	$_SESSION['bsm']['edit']['sign_enum'] = $res->fields['sign_enum'];
	$_SESSION['bsm']['edit']['sign_code'] = $res->fields['sign_code'];
	$_SESSION['bsm']['edit']['sign_priority'] = $res->fields['sign_priority'];
	$_SESSION['bsm']['edit']['sign_description'] = $res->fields['sign_desc'];
}

function shn_bsm_edit_entry($fopen_name = 'edit_sign',$fsopen_name='Edit Sign'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

		$arrary = array();
		$arrary['high'] = _('High');
		$arrary['medium'] = _('Medium');
		$arrary['low'] = _('Low');

    //include('service_type.inc');

    shn_form_fsopen(_('Sign'));
    shn_form_text(_('Sign '),'sign','size="30" readonly=true',array('help' => _('Enter Sign.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['sign']));
		shn_form_text(_('Sign Enum '),'sign_enum','size="10"',array('help' => _('Enter Sign Enum.'), 'req'=>false , 'value'=>$_SESSION['bsm']['edit']['sign_enum']));
    shn_form_text(_('Sign Code'),'sign_code','size="30"',array('help' => _('Enter Sign Code.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['sign_code']));
		shn_form_select($arrary, _('Sign Priority'), 'sign_priority', null, array('help'=>_('Select Sign Priority'), 'value'=>$_SESSION['bsm']['edit']['sign_priority']));
		shn_form_textarea(_('Sign Description '),'sign_desc',null,array('help' => _('Enter Sign Description.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['sign_description']));
		//shn_form_text(_('Symptom Priority'),'symptom_priority','size="30"',array('help' => _('Enter Symptom Priority.'), 'req'=>false));
		
    shn_form_fsclose();
		    
		shn_form_hidden(array('case_uuid'=>$_REQUEST['rtnid']));
    shn_form_submit(_('Edit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_edit_sign()
{
	global $global;
	$db = $global['db'];
	$sign = trim($_POST['sign']);
	$sign_enum = trim($_POST['sign_enum']);
	$sign_code = trim($_POST['sign_code']);
	$sign_priority = trim($_POST['sign_priority']);
	$sign_description = trim($_POST['sign_desc']);
	$sign_pre = $_SESSION['bsm']['edit']['sign'];
	$sql = "UPDATE bsm_sign SET sign_desc='{$sign_description}', sign_code='{$sign_code}', sign_priority='{$sign_priority}', sign_enum='{$sign_enum}' WHERE sign='$sign_pre'";
	$res=$db->Execute($sql);
//print $sql;
	if($res){
		add_confirmation(_('Record Updated Successfully'));
	} else {
		add_error(_('An error occured while updating the data'));
	}
}
?>