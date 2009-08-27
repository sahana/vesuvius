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

function shn_bsm_add_entry($fopen_name = 'add_symptom',$fsopen_name='Add Symptom'){
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
    shn_form_text(_('Symptom '),'symptom','size="30"',array('help' => _('Enter Symptom.'), 'req'=>false));
		shn_form_text(_('Symptom Enum '),'symptom_enum','size="10"',array('help' => _('Enter Symptom Enum.'), 'req'=>false));
    shn_form_text(_('Symptom Code'),'symptom_code','size="30"',array('help' => _('Enter Symptom Code.'), 'req'=>false));
		shn_form_select($arrary, _('Symptom Priority'), 'symptom_priority', null, array('help'=>_('Select Symptom Priority')));
		shn_form_textarea(_('Symptom Description '),'symptom_desc',null,array('help' => _('Enter Sign Description.'), 'req'=>false));
		//shn_form_text(_('Symptom Priority'),'symptom_priority','size="30"',array('help' => _('Enter Symptom Priority.'), 'req'=>false));
		
    shn_form_fsclose();
		    
		shn_form_hidden(array('case_uuid'=>$_REQUEST['rtnid']));
    shn_form_submit(_('Add'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_add_symptom()
{
	global $global;
	$db = $global['db'];
	/*$insert_array = array();
	$insert_array['case_uuid'] = trim($_POST['case_uuid']);
	$insert_array['symptom'] = trim($_POST['symptom']);
	$insert_array['symp_enum'] = trim($_POST['symptom_enum']); 
	$insert_array['symp_code'] = trim($_POST['symptom_code']); 
	$insert_array['symp_priority'] = trim($_POST['symptom_priority']); 
	$insert_array['symp_desc'] = trim($_POST['symptom_desc']);

	$res = $db->AutoExecute('bsm_symptom', $insert_array, 'INSERT');
	$res1 = $db->AutoExecute('bsm_case_symp', $insert_array, 'INSERT');*/

	$case_uuid = trim($_POST['case_uuid']);
	$symptom = trim($_POST['symptom']);
	$sym_enum = trim($_POST['symptom_enum']); 
	$sym_code = trim($_POST['symptom_code']); 
	$sym_priority = trim($_POST['symptom_priority']); 
	$sym_desc = trim($_POST['symptom_desc']);

	$sql = "INSERT INTO bsm_symptom (symptom, symp_desc, symp_code, symp_priority, symp_enum) VALUES ('{$symptom}', '{$sym_desc}', '{$sym_code}', '{$sym_priority}', '{$sym_enum}');";
	$res = $db->Execute($sql);

	$sql = "INSERT INTO bsm_dis_symp (disease, symptom) VALUES ('{$case_uuid}', '{$symptom}')";
	$res1 = $db->Execute($sql);
	//print $sql;
	//if($res && $res1){
	if($res){
		 add_confirmation(_("Sign Added Successfully"));
		 include_once 'edit_disease.inc';
		 shn_bsm_edit_load($case_uuid); // loading the stored data (handling sessions)
         shn_bsm_edit_entry(false);
	}
    else{
        add_error(_('Error while saving Symptom.'));
    }
}
?>