<?php
/**
 * DSM lib_dsm.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @author     Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_dsm_execute($sql)
{
	global $global;
	
	$db = $global['db'];
	
	$res = $db->Execute($sql);
	if ($res) {
	    return $res;
	} else {
		return false;
	}
}

function _shn_dsm_limit_execute($sql,$items=6)
{
	global $global;
	
	$rs = $global['db']->SelectLimit($sql,$items);
	
    if ($rs) {
	    return $rs;
	} else {
		return false;
	}
}

function _shn_dsm_get_stored_sym($uuid = null, $option = true, $dis_id = null)
{
	if ($uuid==null && $dis_id == null) {
	    $sql = "SELECT sym_id,description FROM dsm_symptoms";
	    $res = _shn_dsm_execute($sql);
	    $result = array();
	    foreach ($res as $r) {
		    $result[$r['sym_id']] = $r['description'];
	    }
	    if ($option == false) {
	    	$result = $res;
	    }
	
	} else {
		$sql = "SELECT description FROM dsm_symptoms WHERE sym_id='$uuid'";
		$result = _shn_dsm_execute($sql)->fields['description'];
	}
	return $result;
}

function _shn_dsm_get_disease_sym($dis_id)
{
	$sql = "SELECT symptoms.sym_id,description,priority FROM dsm_symptoms,dsm_disease_symptoms WHERE dsm_symptoms.sym_id=dsm_disease_symptoms.sym_id AND dis_id='$dis_id'";
	$result = array();
	$res = _shn_dsm_execute($sql);
    foreach ($res as $r) {
		    //$result['sym_id'] = $r['sym_id'];
		    $result['description'] = $r['description'];
		    //$result['priority'] = $r['priority'];
	    }
	return $result;
}

function _shn_dsm_get_disease_factors($dis_id)
{
	$sql = "SELECT causative_factors.fac_id,description FROM dsm_causative_factors,dsm_disease_cau_factors WHERE dsm_causative_factors.fac_id=dsm_disease_cau_factors.fac_id AND dis_id='$dis_id'";
	$result = _shn_dsm_execute($sql)->fields['description'];
	return $result;
}

/**
 * Return the list of diseases(dis_id,dis_name) from the diseases table.
 *
 * @return unknown
 */
function _shn_dsm_diseases()
{
    $sql = "SELECT dis_name,dis_id FROM dsm_diseases";
    $result = array();
    $res = array();
    $res = _shn_dsm_execute($sql);
    foreach ($res as $r) {
		    $result[$r['dis_id']] = $r['dis_name'];
	    }
    return $result;
}

/**
 * Return dis_name from diseases table for a given dis_id
 *
 * @param unknown_type $dis_id
 */
function _shn_dsm_get_disease_name($dis_id)
{
	$sql = "SELECT dis_name FROM dsm_diseases WHERE dis_id='{$dis_id}'";
	$res = _shn_dsm_execute($sql);
	if ($res) {
		return $res->fields['dis_name'];
	} else {
		add_error(_t('Input is not valid.'));
	}
}

/**
 * Return the latest list of diseases which are added to diseases table.
 *
 * @return unknown
 */
function _shn_dsm_get_resent()
{
	$sql = "SELECT dis_id,dis_name FROM dsm_diseases";
	$res = _shn_dsm_limit_execute($sql);//print $res;
	return $res;
}

function _shn_dsm_print_header($header)
{
	?>
    <h2><center><?php print (_t($header)); ?></center></h2>
    <?php
}

/**
 * Return all the data stored in diseases table for a given dis_id.
 *
 * @param unknown_type $disease_id
 * @return unknown
 */
function _shn_general_data_from_table($disease_id)
{
	$sql = "SELECT * FROM dsm_diseases WHERE dis_id='$disease_id'";
	$result = _shn_dsm_execute($sql);
	$details['dis_name'] = $result->fields['dis_name'];
	$details['med_name'] = $result->fields['med_name'];
	$details['age_group'] = $result->fields['age_group'];
	$details['carrier'] = $result->fields['carrier'];
	$details['cause'] = $result->fields['cause'];
	return $details;  
}

function _shn_risks_data_from_table($disease_id){
	
    $sql = "SELECT * FROM dsm_diseases_risks WHERE dis_id='$disease_id'";
    $result = _shn_dsm_execute($sql);
    $details_risks['eff_gender'] = $result->fields['eff_gender'];
    $details_risks['drink_water'] = $result->fields['dri_water'];
    $details_risks['nutrition'] = $result->fields['nutrition_level'];
    $details_risks['sanitary'] = $result->fields['sanitary'];
    $details_risks['seasons'] = $result->fields['seasons'];
    return $details_risks;  
}

function _dsm_add_contact($id,$type,$value)
{
	$sql = "INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES ('$id','$type','$value')";
	_shn_dsm_execute($sql);
}

/**
 * Return full name of a person from person_uuid table for a given p_uuid.
 *
 * @param unknown_type $person_uuid
 * @return unknown
 */
function _shn_dsm_get_person_full_name($person_uuid)
{	
    $sql= "SELECT full_name FROM person_uuid WHERE p_uuid ='{$person_uuid}'";
    $res = _shn_dsm_execute($sql);
    $group = $res->fields['full_name'];
    return $group;
	
}

function _shn_dsm_populate_case($pat_id)
{
	$result = _dsm_get_general_data($pat_id);
	$_SESSION['edit_case']['pat_name'] = $result->fields['full_name'];
	_dsm_get_contacts($pat_id);
	
	$sql = "SELECT * FROM dsm_diagnosis WHERE pat_id='$pat_id'";
	_shn_dsm_execute($sql);
}

function _dsm_get_contacts($pat_id)
{
	$sql = "SELECT * FROM contact WHERE pgoc_uuid='$pat_id'";
	$res = _shn_dsm_execute($sql);
	return $res;
}

function _dsm_get_general_data($pat_id)
{
	$sql = "SELECT * FROM person_uuid WHERE p_uuid='$pat_id'";
	$res = _shn_dsm_execute($sql);
	return $res;
}

function _dsm_update_contact($uuid,$contacttype,$contactvalue)
{
	$sql = "UPDATE contact SET contact_value='$contactvalue' WHERE pgoc_uuid='$uuid' AND opt_contact_type='$contacttype'";
	$update = _shn_dsm_execute($sql);
	//If the contact has not been inserted, Inserting......
	if ($update == false) {
		$sql = "INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES ('$uuid','$contacttype','$contactvalue')";
	}
}

function _dsm_populate_contact($pat_id)
{
	$res = array();
	$result = array();
	$res = _dsm_get_contacts($pat_id);//var_dump($res);
	foreach ($res as $r) {
		$result[$r['opt_contact_type']] = $r['contact_value'];//print $r['contact_value'];
	}
	return $result;
}

