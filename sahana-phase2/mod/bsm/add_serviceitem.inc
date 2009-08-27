<?php
function shn_bsm_add_entry($fopen_name = 'add_serviceitem',$fsopen_name='Add Service Item'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Item'));
    shn_form_text(_('Item Name'),'item_name','size="30"',array('help' => _('Enter Item Name.'), 'req'=>false));
		shn_form_text(_('Service Category'),'service_category','size="30"',array('help' => _('Enter Service Category Details.'), 'req'=>false));
		shn_form_textarea(_('Item Description'), 'item_description', array('help' => _('Enter a Brief description about the Item')));
		shn_form_text(_('Item State'),'item_state','size="30"',array('help' => _('Enter Item Status.'), 'req'=>false));
   
    shn_form_fsclose();
		shn_form_hidden(array('service_id'=>trim($_REQUEST['id'])));
//print(trim($_REQUEST['id']));
    shn_form_submit(_('Add'));
    shn_form_fsclose();

		

    shn_form_fclose();
}

function _shn_add_service_item()
{
	global $global;
	$db = $global['db'];

	$insert_array = array();
	$insert_array['serv_uuid'] = trim($_POST['service_id']);
	$insert_array['item_name'] = trim($_POST['item_name']);
	$insert_array['serv_cate'] = trim($_POST['service_category']);
	$insert_array['item_desc'] = trim($_POST['item_description']);
	$insert_array['item_state'] = trim($_POST['item_state']);
//var_dump($insert_array);
	$res = $db->AutoExecute('bsm_serv_type_item', $insert_array, 'INSERT');
	$res1 = $db->AutoExecute('bsm_serv_item', $insert_array, 'INSERT');
	    
    if($res && $res1)
        add_confirmation(_t("Contacts Added Successfully"));
    else{
        add_error(_('Error while saving location.'));
    }
}
?>