<?php
function shn_bsm_edit_load()
{
		global $global;
    global $conf;
		$db = $global['db'];

		$sql = "SELECT a.* FROM bsm_address a INNER JOIN bsm_fclty_addr fa ON a.addr_uuid = fa.addr_uuid WHERE a.addr_uuid = '".$_REQUEST['id']."'";
//print $sql;
		$res = $db->Execute($sql);
		$_SESSION['bsm']['edit']['addr_type'] = $res->fields['addr_type'];
		$_SESSION['bsm']['edit']['addr_status'] = $res->fields['addr_status'];
		$_SESSION['bsm']['edit']['line1'] = $res->fields['line_1'];
		$_SESSION['bsm']['edit']['line2'] = $res->fields['line_2'];

//print $_SESSION['bsm']['edit']['cont_mode'];
}

function shn_bsm_edit_entry($fopen_name = 'edit_address',$fsopen_name='Edit'){
    

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Address'));
    shn_form_text(_('Address Type'),'addr_type','size="30"',array('help' => _('Enter Address Type.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['addr_type']));
    shn_form_text(_('Address Status'),'addr_status','size="30"',array('help' => _('Enter Address Ststus.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['addr_status']));
		shn_form_textarea(_('Address 1 '),'addr_1',null,array('help' => _('Enter Address One.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['line1']));
		shn_form_textarea(_('Address 2 '),'addr_2',null,array('help' => _('Enter Address Two.'), 'req'=>false, 'value'=>$_SESSION['bsm']['edit']['line2']));
    shn_form_fsclose();

		//shn_form_fsopen(_('Location Details'));
		
		//shn_form_fsclose();

    /*shn_form_fsopen(_('Service Recipient'));
    shn_form_text(_('Last Name'),'recipient_last_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_text(_('First Name'),'recipient_first_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_fsclose();*/
		//shn_form_hidden(array('fclty_uuid'=>$_REQUEST['id']));
    //shn_form_submit(_('Add'));

    
		shn_form_hidden(array('id'=>$_REQUEST['id']));
    shn_form_submit(_('Edit'));
    shn_form_fsclose();

		

    shn_form_fclose();
}

function _shn_edit_address()
{
	global $global;
	$db = $global['db'];
	$insert_array = array();
	//$insert_array['cont_uuid'] = trim($_POST['id']);
// 	$insert_array['addr_type'] = trim($_POST['addr_type']);
// 	$insert_array['addr_status'] = trim($_POST['addr_status']);
// 	$insert_array['addr_1'] = trim($_POST['addr_1']);
// 	$insert_array['addr_2'] = trim($_POST['addr_2']);
// 	$update_id = trim($_POST['id']);
// //print $update_id;
// 
// 	
// //var_dump($res);
// 				$res = $db->AutoExecute('bsm_address', $insert_array, 'UPDATE', "addr_uuid = $update_id");
	

	$addr_type = trim($_POST['addr_type']);
	$addr_status = trim($_POST['addr_status']);
	$addr_1 = trim($_POST['addr_1']);
	$addr_2 = trim($_POST['addr_2']);
	$update_id = trim($_POST['id']);

	$sql = "UPDATE bsm_address SET addr_type='$addr_type', addr_status='$addr_status', line_1='$addr_1', line_2='$addr_2' WHERE addr_uuid='$update_id'";
	$res=$db->Execute($sql);
	    
    if($res)
        add_confirmation(_t("Contacts Updated Successfully"));
    else{
        add_error(_('Error while saving location.'));
				}

}
?>