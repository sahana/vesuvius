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
 * @author      Kethees <ks@respere.com>
 * @copyright   Respere Lanka (Pvt) Ltd. - http://www.respere.com/
 * @package     module
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function shn_bsm_add_entry($fopen_name = 'add_caus_factor',$fsopen_name='Add Causality Factor'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

		$arrary = array();
		$arrary['high'] = _('High');
		$arrary['medium'] = _('Medium');
		$arrary['low'] = _('Low');

    shn_form_fsopen(_('Causality Factor'));
    shn_form_text(_('Causality Factor '),'caus_factor','size="30"',array('help' => _('Enter Causality.'), 'req'=>false));
	shn_form_text(_('Causality Enum '),'caus_factor_enum','size="10"',array('help' => _('Enter Sign Enum.'), 'req'=>false));
    shn_form_text(_('Causality Code'),'caus_factor_code','size="30"',array('help' => _('Enter Sign Code.'), 'req'=>false));
	shn_form_select($arrary, _('Causality Priority'), 'caus_factor_priority', null, array('help'=>_('Select Sign Priority')));
	shn_form_textarea(_('Causality Description '),'caus_factor_desc',null,array('help' => _('Enter Sign Description.'), 'req'=>false));		
    shn_form_fsclose();
		    
	shn_form_hidden(array('case_uuid'=>$_REQUEST['rtnid']));
    shn_form_submit(_('Add'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_add_caus_factor()
{
	global $global;
	$db = $global['db'];	

	$case_uuid = trim($_POST['case_uuid']);
	$caus_factor = trim($_POST['caus_factor']);
	$caus_factor_enum = trim($_POST['caus_factor_enum']);
	$caus_factor_priority = trim($_POST['caus_factor_priority']);
	$caus_factor_desc = trim($_POST['caus_factor_desc']);
	$caus_factor_code = trim($_POST['caus_factor_code']);
 
	$sql = "INSERT INTO bsm_caus_fact (caus_fact, caus_fact_enum, caus_fact_priority, caus_fact_desc, caus_fact_code) VALUES ('{$caus_factor}', '{$caus_factor_enum}', '{$caus_factor_priority}', '{$caus_factor_desc}', '{$caus_factor_code}');";
	$res = $db->Execute($sql);
	
	$sql = "INSERT INTO bsm_dis_caus_fact (disease, caus_fact) VALUES ('{$case_uuid}', '{$caus_factor}')";
	$res1 = $db->Execute($sql);

	if($res){
		 add_confirmation(_("Causality Factor Added Successfully"));
		 include_once 'edit_disease.inc';
		 shn_bsm_edit_load($case_uuid);
         shn_bsm_edit_entry(false);
	}
    else{
        add_error(_('Error while saving Sign.'));
    }
}
?>
