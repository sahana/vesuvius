<?php
/**
* The Sahana Disaster Preparedness System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Chamara Caldera <chamaracal@gmail.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/
include_once 'lib_pre.inc';

function _shn_pre_set_status($wrn_uuid = '', $duuid, $type, $useage = ''){
	global $global;
	$sql2 = "UPDATE pre_disaster SET status = '$type' WHERE disaster_uuid = '$duuid'";
	$res2 = $global['db']->Execute($sql2);
	$sql3 = "SELECT area_uuid FROM pre_threat_area WHERE area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid = '$duuid')";
	$res3 = $global['db']->Execute($sql3);
	echo $global['db']->ErrorMsg();
	if($res3 != false && $res3->RecordCount() > 0){
		for($i = 0; $i < $res3->recordCount(); $i++){
			if(isset($_POST[$res3->fields['area_uuid']])){
				$sql4 = "UPDATE pre_threat_area_disaster SET status = '$type' WHERE area_uuid = '".$_POST[$res3->fields['area_uuid']]."' AND disaster_uuid = '".$duuid."'";
				$res4 = $global['db']->Execute($sql4);				
				$area = $_POST[$res3->fields['area_uuid']];
				if($useage == ''){
					$sql5 = "INSERT INTO pre_area_history(warn_uuid, area_uuid) VALUES('$wrn_uuid', '$area')";
					$sql5 = $global['db']->Execute($sql5);
				}
			}
			$res3->MoveNext();
		}
	}
}

function _shn_pre_register_disaster(){
	global $global;
	$sql1 = "INSERT INTO incident(name) VALUES('"._shn_pre_get_disaster_name($_POST['dis_id'])."')";
	$res1 = $global['db']->Execute($sql1);
	if($res1 === false){
		add_error('Error Occurs in adding incident');
	}
	else{
		$sql2 = "SELECT incident_id FROM incident WHERE name = '"._shn_pre_get_disaster_name($_POST['dis_id'])."'";
		$res2 = $global['db']->Execute($sql2);
		if($res2->RecordCount() > 0){
			$wrn_uuid = shn_create_uuid();
			$incident_id = $res->fields['incident_id'];	
			$date = date("y-m-d h:i:s");
			$sql3 = "INSERT INTO pre_disaster_history(wrn_uuid, disaster_uuid, incident_id, registered_date, type) VALUES" .
					"('$wrn_uuid', '{$_POST['dis_id']}', '$incident_id', '$date', 'on  ')";
			$res3 = $global['db']->Execute($sql3);
			if($res3 === false){
				add_error('Error occurs in adding to disaster history'.$global['db']->ErrorMsg());
			}
			else{
				_shn_pre_set_status($wrn_uuid, $_POST['dis_id'], 'on');
				add_confirmation('Submision successfull');
			}
		}
	}
}

function _shn_pre_add_warning($duuid){
	global $global;
	$wrn_uuid = shn_create_uuid();
	$date = date("y-m-d h:i:s");
	
	$sql1 = "INSERT INTO pre_disaster_history(wrn_uuid, disaster_uuid, registered_date, type) VALUES('$wrn_uuid', '$duuid', '$date', 'warned')";
	$res1 = $global['db']->Execute($sql1);
	if($res1 != false){
		_shn_pre_set_status($wrn_uuid, $duuid, 'warned');
		add_confirmation('Warned succussefully');
	}
	else{
		add_error('Error occurs');
	}
}

function _shn_pre_warning_unregister($duuid, $type, $cur_type){
	global $global;
	$date = date('y-m-d h:i:s');
	$sql1 = "UPDATE pre_disaster_history SET expired_date = '$date'  WHERE expired_date IS NULL AND disaster_uuid = '$duuid' AND type = '$cur_type'";
	$res1 = $global['db']->Execute($sql1);
	if($res1 != false){
		_shn_pre_set_status('', $duuid, $type, 'remove');
		add_confirmation('Change the status');
	}
}

function _shn_pre_threat_area_selection($duuid){
	global $global;
	//shn_form_checkbox()
}

?>

<script>
function swapArea(){
	document.getElementById('link').innerHTML = '';
	document.getElementById('area').innerHTML = '<br><select name="threat"><option value="">--select--</option><option value="high">High</option><option value="moderate">Moderate</option><option value="low">Low</option></select><br><br>';
}
</script>
<?php
function _shn_pre_disaster_registration_form($duuid){
	global $global;
	if(!shn_acl_is_enabled() || $_SESSION['user_uuid'] == 1){
		
		shn_form_fopen('add_warning',null, array('req_message'=>false));
		shn_form_fsopen(_('Declair the Disaster'));
		shn_form_hidden(array('seq'=>'reg'));
		shn_form_hidden(array('dis_id'=>$duuid));
		$sql = "SELECT area_uuid, area FROM pre_threat_area WHERE area_uuid IN (SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid = '$duuid')";
		$res = $global['db']->Execute($sql);
		echo '<a href="#" onclick="swapArea()" id="link">Select Area using priority list</a>';
		echo '<div id="area">';
		for($i = 0; $i < $res->RecordCount(); $i++){
			shn_form_checkbox($res->fields['area'], $res->fields['area_uuid'], '', array('value'=>$res->fields['area_uuid']));
			$res->MoveNext();
		}
		echo '</div>';
		if(!_shn_pre_is_declaired($duuid, 'on') && !_shn_pre_is_declaired($duuid, 'post')){
			shn_form_submit('Register', 'name="register"');
		}
		else{
			if(!_shn_pre_is_declaired($duuid, 'post')){
				shn_form_submit('Post Disaster', 'name="post"');
			}
			shn_form_submit('Unregister', 'name="unreg"');
		}
		if(!_shn_pre_is_declaired($duuid, 'warned')){
			shn_form_submit('Warning', 'name="warning"');
		}
		else{
			shn_form_submit('Remove Warning', 'name="unwarn"');
		}
		shn_form_fsclose();
		shn_form_fclose();
	}
}

switch($_POST['seq']){
	case '':
		$duuid = $_REQUEST['dis_id'];
		_shn_pre_disaster_registration_form($duuid);
		break;
	case 'reg':
		if(isset($_POST['register'])){
			_shn_pre_register_disaster();
		}
		else{
			if(isset($_POST['warning'])){
				_shn_pre_add_warning($_POST['dis_id']);
			}
			else{
				if(isset($_POST['unreg'])){
					 if(!_shn_pre_is_declaired($duuid, 'post')){
					 	_shn_pre_warning_unregister($_POST['dis_id'], 'pre', 'on');
					 }
					 else{
					 	_shn_pre_warning_unregister($_POST['dis_id'], 'pre', 'post');
					 }
				}
				else{
					if(isset($_POST['post'])){
						_shn_pre_warning_unregister($_POST['dis_id'], 'post', 'on');
					}
					else{
						_shn_pre_warning_unregister($_POST['dis_id'], 'pre', 'warned');
					}
				}
			}
		}
		break;
	case 'pri_sel':
		break;
	default:
		break;
}

