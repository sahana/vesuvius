<?php
/**
 * Add Health cases
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      >
 * @copyright  
 * @package     module
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


function shn_bsm_add_entry($fopen_name = 'add_address',$fsopen_name='Add Addresses'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Address'));
    shn_form_text(_('Address Type'),'addr_type','size="30"',array('help' => _('Enter Address Type.'), 'req'=>false));
    shn_form_text(_('Address Status'),'addr_status','size="30"',array('help' => _('Enter Address Ststus.'), 'req'=>false));
		shn_form_textarea(_('Address 1 '),'addr_1',null,array('help' => _('Enter Address One.'), 'req'=>false));
		shn_form_textarea(_('Address 2 '),'addr_2',null,array('help' => _('Enter Address Two.'), 'req'=>false));
    shn_form_fsclose();

		shn_form_fsopen(_('Location Details'));
		
		shn_form_fsclose();

    /*shn_form_fsopen(_('Service Recipient'));
    shn_form_text(_('Last Name'),'recipient_last_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_text(_('First Name'),'recipient_first_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_fsclose();*/
		shn_form_hidden(array('fclty_uuid'=>$_REQUEST['id']));
    shn_form_submit(_('Add'));
    shn_form_fsclose();

		

    shn_form_fclose();
}

function _shn_add_address()
{
	global $global;
	$db = $global['db'];
	include_once 'lib_uuid.inc';
	$addr_uuid = shn_create_uuid('address');
	$insert_array=array();
	$insert_array['addr_uuid'] = $addr_uuid;
	$insert_array['fclty_uuid'] = trim($_POST['fclty_uuid']);
	$insert_array['addr_type'] = trim($_POST['addr_type']);
	$insert_array['addr_status'] = trim($_POST['addr_status']);
	$insert_array['line_1'] = trim($_POST['addr_1']);
	$insert_array['line_2'] = trim($_POST['addr_2']);

	$res = $db->AutoExecute('bsm_address', $insert_array, 'INSERT');
	$res1 = $db->AutoExecute('bsm_fclty_addr', $insert_array, 'INSERT');
    
    if($res)
        add_confirmation(_t("Contacts Added Successfully"));
    else{
        add_error(_('Error while saving location.'));
    }
}
?>