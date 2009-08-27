<?php
/**
 * Add a diagnosis - disease + symptoms + signs + causality factors
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      Pradeeper <pradeeper@respere.com>
 * @copyright   Respere Lanka (Pvt) Ltd. - http://www.respere.com/
 * @package     module
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function shn_bsm_add_entry($fopen_name = 'add_sign',$fsopen_name='Add Sign'){
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
    shn_form_text(_('Sign '),'sign','size="30"',array('help' => _('Enter Sign.'), 'req'=>false));
		shn_form_text(_('Sign Enum '),'sign_enum','size="10"',array('help' => _('Enter Sign Enum.'), 'req'=>false));
    shn_form_text(_('Sign Code'),'sign_code','size="30"',array('help' => _('Enter Sign Code.'), 'req'=>false));
		shn_form_select($arrary, _('Sign Priority'), 'sign_priority', null, array('help'=>_('Select Sign Priority')));
		shn_form_textarea(_('Sign Description '),'sign_desc',null,array('help' => _('Enter Sign Description.'), 'req'=>false));
		//shn_form_text(_('Symptom Priority'),'symptom_priority','size="30"',array('help' => _('Enter Symptom Priority.'), 'req'=>false));
		
    shn_form_fsclose();
		    
		shn_form_hidden(array('case_uuid'=>$_REQUEST['rtnid']));
    shn_form_submit(_('Add'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_add_sign()
{
	global $global;
	$db = $global['db'];
	/*$insert_array = array();
	$insert_array['case_uuid'] = trim($_POST['case_uuid']);
	$insert_array['sign'] = trim($_POST['sign']);
	$insert_array['sign_enum'] = trim($_POST['sign_enum']); 
	$insert_array['sign_code'] = trim($_POST['sign_code']); 
	$insert_array['sign_priority'] = trim($_POST['sign_priority']); 
	$insert_array['sign_desc'] = trim($_POST['sign_desc']);

	$res = $db->AutoExecute('bsm_sign', $insert_array, 'INSERT');
	$res1 = $db->AutoExecute('bsm_case_sign', $insert_array, 'INSERT');
*/
//var_dump($insert_array);

	$case_uuid = trim($_POST['case_uuid']);
	$sign = trim($_POST['sign']);
	$sign_enum = trim($_POST['sign_enum']); 
	$sign_code = trim($_POST['sign_code']); 
	$sign_priority = trim($_POST['sign_priority']); 
	$sign_desc = trim($_POST['sign_desc']);

	$sql = "INSERT INTO bsm_sign (sign, sign_desc, sign_code, sign_priority, sign_enum) VALUES ('{$sign}', '{$sign_desc}', '{$sign_code}', '{$sign_priority}', '{$sign_enum}');";
	$res = $db->Execute($sql);
	
	$sql = "INSERT INTO bsm_dis_sign (disease, sign) VALUES ('{$case_uuid}', '{$sign}')";
	$res1 = $db->Execute($sql);
	

	if($res){
		 add_confirmation(_("Sign Added Successfully"));
		 include_once 'edit_disease.inc';
		 shn_bsm_edit_load($case_uuid); // loading the stored data (handling sessions)
         shn_bsm_edit_entry(false);
	}
    else{
        add_error(_('Error while saving Sign.'));
    }
}
?>