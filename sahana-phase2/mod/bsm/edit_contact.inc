<?php
function shn_bsm_edit_load()
{
		global $global;
    global $conf;
		$db = $global['db'];

		$sql = "SELECT * FROM bsm_contact WHERE cont_uuid = '".$_REQUEST['id']."'";
		$res = $db->Execute($sql);
		$_SESSION['bsm']['edit']['cont_mode'] = $res->fields['cont_mode'];
		$_SESSION['bsm']['edit']['cont_val'] = $res->fields['cont_val'];

//print $_SESSION['bsm']['edit']['cont_mode'];
}

function shn_bsm_edit_entry($fopen_name = 'edit_contact',$fsopen_name='Edit'){
    

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Contact Details'));
    shn_form_text(_('Contact Mode'),'contact_mode','size="30"',array('help' => _('Enter Contact Mode.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['cont_mode']));
    shn_form_text(_('Contact Value'),'contact_value','size="30"',array('help' => _('Enter Contact Value.'), 'req'=>false, 'value'=> $_SESSION['bsm']['edit']['cont_val']));
    shn_form_fsclose();

    
		shn_form_hidden(array('id'=>$_REQUEST['id']));
    shn_form_submit(_('Edit'));
    shn_form_fsclose();

		

    shn_form_fclose();
}

function _shn_edit_contact()
{
	global $global;
	$db = $global['db'];
	/*$insert_array = array();
	//$insert_array['cont_uuid'] = trim($_POST['id']);
	$insert_array['cont_mode'] = trim($_POST['contact_mode']);
	$insert_array['cont_val'] = trim($_POST['contact_value']);
	$update_id = trim($_POST['id']);
//print $update_id;

	$res = $db->AutoExecute('bsm_contact', $insert_array, 'UPDATE', "cont_uuid = $update_id");*/
//var_dump($res);

	$cont_mode = trim($_POST['contact_mode']);
	$cont_val = trim($_POST['contact_value']);
	$update_id = trim($_POST['id']);

	$sql = "UPDATE bsm_contact SET cont_mode='$cont_mode', cont_val='$cont_val' WHERE cont_uuid='$update_id'";
	$res = $db->Execute($sql);
//print $sql;
	    
    if($res)
        add_confirmation(_t("Contacts Updated Successfully"));
    else{
        add_error(_('Error while saving location.'));
				}

}
?>