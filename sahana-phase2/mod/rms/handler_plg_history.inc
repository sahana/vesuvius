<?php
/**
* The Sahana Resquest Management System
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

include_once 'lib_rms.inc';

function _shn_rms_user_pledge(){
	global $global;
	$sql = "SELECT plg_uuid, status, plg_date FROM rms_pledge WHERE donor_uuid = '".$_SESSION['user_id']."'";
	$res = $global['db']->Execute($sql);
	if($res === false){
		add_error('Error in query exicution '.$global['db']->ErrorMsg());
	}
	if($res->RecordCount() > 0){
		$th_items[] = array(_t('Date'), _t('Status'), _t('Show'));
		for($i = 0; $i <$res->RecordCount(); $i++){
			$url = '<a href="index.php?mod=rms&act=plg_history&seq=show&plg_id='.$res->fields['plg_uuid'].'">Show</a>';
			$tb_items[] = array(
							$res->fields['plg_date'],
							$res->fields['status'],
							$url);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_html_print_alert(_t('You have not done any pledge'));
	}
}

function _shn_rms_pledge_history_form(){
	if(shn_acl_is_enabled()){
		echo '<h4>Pledges you have done</h4>';
		_shn_rms_user_pledge();
		echo '<br>';
	}
	shn_form_fopen("plg_history",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'show'));
    shn_form_fsopen(_t("Give the pledge ID"));
    shn_form_text(_t('Pledge ID : '), 'plg_id', null, array('req'=>true));
    shn_form_submit(_('Search'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_rms_show_plg_items($plg_id, $item_id = ''){
	global $global;
	$sql = "SELECT p.item_uuid, p.quantity, p.status, SUM(f.quantity) AS qty FROM rms_plg_item AS p LEFT JOIN rms_fulfil AS f ON f.plg_uuid = p.plg_uuid AND f.item_uuid = p.item_uuid" .
			" WHERE p.plg_uuid = '$plg_id'";
	if($item_id != ''){
		$sql .= " AND p.item_uuid = '$item_id'";
	}
	$sql .= " GROUP BY p.item_uuid";
	$res = $global['db']->Execute($sql);
	if($res === false){
		add_error(_t('Error has been occured').$global['db']->ErrorMsg());
	}
	else{
		if($res->RecordCount() > 0){
			echo '<h4>Pledged Items</h4>';
			$th_items[] = array(_t('Item'), _t('Donated Quantity'), _('Used Qty'), _t('Status'), _t('History'));
			for($i = 0; $i < $res->RecordCount(); $i++){
				$url = '<a href="index.php?mod=rms&act=plg_history&seq=history&plg_id='.$plg_id.'&item_id='.$res->fields['item_uuid'].'">Show</a>';
				$tb_items[] = array(
							_shn_rms_get_cat_name($res->fields['item_uuid']),
							$res->fields['quantity'],
							$res->fields['qty'],
							$res->fields['status'],
							$url);
				$res->MoveNext();
			}
			shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
		}
		else{
			_shn_html_print_alert(_t('No such pledge'));
			_shn_rms_pledge_history_form();
		}
	}
}

function _shn_rms_show_plg($plg_id){
	if(count($plg_id) > 0){
		_shn_rms_view_donor($plg_id['donor_uuid']);
		$tb_items[] = array('<strong>'._t('Date').'</strong>', $plg_id['plg_date']);
		$width=array('20%');
		shn_html_table($tb_items,null,null,array('class'=>'layout','width'=>$width));
		echo '<br>';
		_shn_rms_show_plg_items($plg_id['plg_uuid']);
		echo '<br>';
		//echo '<'
	}
	else{
		_shn_html_print_alert(_t('No such pledge'));
		_shn_rms_pledge_history_form();
	}
}

function _shn_rms_show_history($plg_id, $item_id = ''){
	global $global;
	echo '<br>';
	echo '<h4>'._t('Fulfillment History').'</h4>';
	$sql = "SELECT req_uuid, ff_date, quantity FROM rms_fulfil WHERE plg_uuid = '$plg_id'" ;
	if($item_id != ''){
		$sql .= " AND item_uuid = '$item_id'";
	}
	$res = $global['db']->Execute($sql);
	
	if($res == false){
		add_error(_t('An Error has been occured'));
	}
	else{
		if($res->RecordCount() > 0){
			$th_items[] = array(_t('Request ID'), _t('Date'), _t('Allocation'));
			for($i = 0; $i < $res->RecordCount(); $i++){
				$tb_items[] = array(
									$res->fields['req_uuid'],
									$res->fields['ff_date'],
									$res->fields['quantity']);
				$res->MoveNext();
			}
			shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
		}
		else{
			_shn_html_print_alert(_t('Zero Quantity has been used for fulfllmentings'));
		}
	}
}

_shn_rms_print_hedder(_t('Pledge History'));
switch($_REQUEST['seq']){
	case '':		
		_shn_rms_pledge_history_form();
		echo '<br><a href="index.php?mod=rms">Home</a>';
		break;
	case 'show':
		$_SESSION['plg_id'] = $_REQUEST['plg_id'];
		$plg_id = _shn_rms_get_pledge($_SESSION['plg_id']);
		_shn_rms_show_plg($plg_id);
		echo '<a href="index.php?mod=rms">Home</a> :: ';
		echo '<a href="index.php?mod=rms&act=plg_history">Back</a>';
		break;
	case 'history':
		$_SESSION['item_id'] = $_REQUEST['item_id'];
		_shn_rms_show_plg_items($_SESSION['plg_id'], $_SESSION['item_id']);
		_shn_rms_show_history($_SESSION['plg_id'], $_SESSION['item_id']);
		echo '<br><a href="index.php?mod=rms">Home</a> :: ';
		echo '<a href="index.php?mod=rms&act=plg_history&seq=show&plg_id='.$_SESSION['plg_id'].'">Back</a>';
		break;
	default:
		break;
}
?>