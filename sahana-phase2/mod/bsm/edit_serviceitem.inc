<?php 
function shn_bsm_edit_load()
{
		global $global;
    global $conf;
		$db = $global['db'];

		$sql = "SELECT si.item_name AS item_name, si.item_state AS item_state, si.serv_cate AS service_category, si.item_desc AS item_description, i.serv_uuid AS service_uuid FROM bsm_serv_type_item si INNER JOIN bsm_serv_item i ON si.item_name = i.item_name WHERE i.deactivate_dt IS NULL ";
    $sql .= "AND i.serv_uuid = '".$_REQUEST['rtnid']."'";
//print $sql;
    $res = $global['db']->Execute($sql);
		$_SESSION['bsm']['edit']['item_name'] = $res->fields['item_name'];
		$_SESSION['bsm']['edit']['service_category'] = $res->fields['service_category'];
		$_SESSION['bsm']['edit']['item_description'] = $res->fields['item_description'];
		$_SESSION['bsm']['edit']['item_state'] = $res->fields['item_state'];

//print $_SESSION['bsm']['edit']['cont_mode'];
}

function shn_bsm_edit_entry($fopen_name = 'edit_serviceitem',$fsopen_name='Edit Service Item'){
    

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');
//print $_SESSION['bsm']['edit']['item_description'];
    shn_form_fsopen(_('Item'));
    shn_form_text(_('Item Name'),'item_name','size="30"',array('help' => _('Enter Item Name.'), 'req'=>false, 'value' => $_SESSION['bsm']['edit']['item_name']));
		shn_form_text(_('Service Category'),'service_category','size="30"',array('help' => _('Enter Service Category Details.'), 'req'=>false, 'value' => $_SESSION['bsm']['edit']['service_category']));
		shn_form_textarea(_('Item Description'), 'item_description', null, array('help' => _('Enter a Brief description about the Item'), 'req'=>false,  'value'=>$_SESSION['bsm']['edit']['item_description']));
		shn_form_text(_('Item State'),'item_state','size="30"',array('help' => _('Enter Item Status.'), 'req'=>false, 'value' => $_SESSION['bsm']['edit']['item_state']));
    shn_form_fsclose();

		

    /*shn_form_fsopen(_('Service Recipient'));
    shn_form_text(_('Last Name'),'recipient_last_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_text(_('First Name'),'recipient_first_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_fsclose();*/
		//shn_form_hidden(array('fclty_uuid'=>$_REQUEST['id']));
    //shn_form_submit(_('Add'));

    
		shn_form_hidden(array('id'=>$_REQUEST['rtnid']));
    shn_form_submit(_('Edit'));
    shn_form_fsclose();

		

    shn_form_fclose();
}

function _shn_edit_service_item()
{
	global $global;
	$db = $global['db'];
	$insert_array = array();
	//$insert_array['cont_uuid'] = trim($_POST['id']);
	$insert_array['item_name'] = trim($_POST['item_name']);
	$insert_array['service_category'] = trim($_POST['service_category']);
	$insert_array['item_description'] = trim($_POST['item_description']);
	$insert_array['item_state'] = trim($_POST['item_state']);
	$serv_uuid = trim($_POST['id']);
//print $update_id;

	
//var_dump($res);
				$sql = "UPDATE bsm_serv_item i INNER JOIN bsm_serv_type_item ti ON i.item_name = ti.item_name SET ti.item_name = '".$insert_array['item_name']."', ti.serv_cate = '".$insert_array['service_category']."', ti.item_desc = '".$insert_array['item_description']."', ti.item_state = '".$insert_array['item_state']."', i.item_name = '".$insert_array['item_name']."', i.item_state = '".$insert_array['item_state']."' WHERE i.serv_uuid = '$serv_uuid' AND i.deactivate_dt IS NULL";
				//print $sql;
				$res = $db->Execute($sql);
				//$res = $db->AutoExecute('bsm_address', $insert_array, 'UPDATE', "addr_uuid = $update_id");
	
	    
    if($res)
        add_confirmation(_t("Contacts Updated Successfully"));
    else{
        add_error(_('Error while saving location.'));
				}

}
?>