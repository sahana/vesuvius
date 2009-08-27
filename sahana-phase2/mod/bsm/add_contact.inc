<?php
function shn_bsm_add_entry($fopen_name = 'add_contact',$fsopen_name='add'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Contact Details'));
    shn_form_text(_('Contact Mode'),'contact_mode','size="30"',array('help' => _('Enter Contact Mode.'), 'req'=>false));
    shn_form_text(_('Contact Value'),'contact_value','size="30"',array('help' => _('Enter Contact Value.'), 'req'=>false));
    shn_form_fsclose();

    
		shn_form_hidden(array('id'=>$_REQUEST['id']));
    shn_form_submit(_('Add'));
    shn_form_fsclose();

		

    shn_form_fclose();
}

function _shn_add_contact()
{
	global $global;
	$db = $global['db'];
	include_once 'lib_uuid.inc';
	$cont_uuid = shn_create_uuid('contact');
	$insert_array=array();
	$insert_array['cont_uuid'] = $cont_uuid;
	$insert_array['p_uuid'] = trim($_POST['id']);
	$insert_array['cont_mode'] = trim($_POST['contact_mode']);
	$insert_array['cont_val'] = trim($_POST['contact_value']);

	$res = $db->AutoExecute('bsm_contact', $insert_array, 'INSERT');
	$res1 = $db->AutoExecute('bsm_prsn_cont', $insert_array, 'INSERT');
    
    if($res)
        add_confirmation(_t("Contacts Added Successfully"));
    else{
        add_error(_('Error while saving location.'));
    }
}
?>