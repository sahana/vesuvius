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

include_once $global['approot'].'/inc/reporting/lib_chart.inc';
include_once $global['approot'].'/inc/reporting/lib_reporting.inc';
include_once $global['approot'].'/inc/lib_paging.inc';
include_once 'lib_rms.inc';

function shn_rms_rpt_default(){
	shn_rms_request_status_chart();
	shn_rms_requested_items_chart();
	shn_rms_items_without_request_chart();
	shn_rms_scarcity_of_item_chart();
}


/**
 * generate pie chart based on the status of the request 
 */
function shn_rms_request_status_chart(){
    global $global;
    $sql = "SELECT status, COUNT(req_uuid) AS count FROM rms_request GROUP BY status";
    $res = $global['db']->Execute($sql);
    if($res === false){
       $msg = $global['db']->ErrorMsg();
       add_error($msg);
       display_errors();
       return false;
    }
    else{
    	if ($res->RecordCount() <= 0){
    		add_alert("No Requests are available");
    		
    	}
    	else{
    		for($i = 0;$i < $res->RecordCount();$i++){
    			add_data($res->fields['status'], $res->fields['count']);
    			$res->MoveNext();
    		}
    	}
    }
	$keyword_arr = array('chart'=>'pie chart','mod'=>'rms');	
	generate_piechart("Piechart","Status of items","","",$keyword_arr);
}

/**
 * return the item amounts in hand(from pledges and inventory)
 */
function _shn_rms_plg_item_amount($item){
	global $global;
	$sql1 = "SELECT SUM(quantity) AS qty FROM rms_fulfil WHERE item_uuid = '$item' AND plg_uuid != ''";
	$sql2 = "SELECT SUM(quantity) AS qty FROM rms_plg_item WHERE item_uuid = '$item' AND (status ='delivered' || status = 'confirmed')";
	$sql3 = "SELECT SUM(amount) AS qty FROM ims_item_records WHERE catalog_id = '$item'";
	$res1 = $global['db']->Execute($sql1);
	$res2 = $global['db']->Execute($sql2);
	$res3 = $global['db']->Execute($sql3);
	if ($res1 === false || $res2 === false || $res3 === false){
       return false;
    }
    else{
    	if ($res2->fields['qty'] > $res1->fields['qty']){
    		return (($res2->fields['qty'] - $res1->fields['qty']) + $res3->fields['qty']);
    	}
    	else
    		return $res3->fields['qty'];
    }
}

/**
 *return fulfilled quanitities for open requests 
 */
function _shn_rms_get_fulfiled_quantity($item_id){
	global $global;
	$sql = "SELECT SUM(quantity) AS qty FROM rms_fulfil WHERE item_uuid = '$item_id' AND req_uuid IN (SELECT req_uuid FROM rms_request WHERE status = 'open') GROUP BY item_uuid";
	$res = $global['db']->Execute($sql);
	return $res->fields['qty'];
}

/**
 * generate table for requested item
 * consider only open request
 */
function _shn_rms_requested_items_table($rec){
	global $global;
	$sql = "SELECT req_uuid, item_uuid, SUM(quantity) AS qty, unit FROM rms_req_item WHERE req_uuid IN (SELECT req_uuid FROM rms_request WHERE status = 'open') GROUP BY item_uuid ORDER BY SUM(quantity) DESC";
	$res = $global['db']->Execute($sql);
	if($res === false){
       $msg = $global['db']->ErrorMsg();
       add_error($msg);
       display_errors();
       return false;
    }
    
    else{
    	if ($res->RecordCount() <= 0){
    		add_error("No Requests are available");
    		
    	}
    	else{
    		$check_i = 0;
    		$th_items[] = array(_t('Item'), _t('To be Fulfilled quantity'), _t('Quantity in-hand'), _t('Unit'));
    		for($i = 0;$i < $res->RecordCount();$i++){
    			if($_SESSION['record_start'] <= $i && $check_i < 5){
    				$item = _shn_rms_get_itemname($res->fields['item_uuid']);
    				$pqty = _shn_rms_plg_item_amount($res->fields['item_uuid']);
    				$qty = $res->fields['qty'] - _shn_rms_get_fulfiled_quantity($res->fields['item_uuid']);
    				$unit = $unit = _shn_rms_get_iunit_name($res->fields['unit']);
    				$check_i++;
    				$tb_items[]=array($item, $qty, $pqty, $unit);
    			}
    			else{
    				if ($check_i == 5)
    					break;
    				
    			}
    			$res->MoveNext();
    		}
    		print '<h4>' . _t("To be fulfilled Quantity of requested item vs Quantity in hand") . '</h4>';
			shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
			print '<br />';
    		if($rec != 0)
    		    echo '<a href="index.php?mod=rms&act=requested_items&rec='.($rec-5).'">Previous</a>';
    		if(($rec + 5) < $res->RecordCount())
    		  echo '<a href="index.php?mod=rms&act=requested_items&rec='.($rec+5).'">next</a>';
    	}
    }
}

/**
 * generate a bar chart for requested item
 */
function shn_rms_requested_items_chart(){
	global $global;
	$sql = "SELECT req_uuid, item_uuid, SUM(quantity) AS qty FROM rms_req_item WHERE req_uuid IN (SELECT req_uuid FROM rms_request WHERE status = 'open') GROUP BY item_uuid ORDER BY SUM(quantity) DESC";
	$res = $global['db']->Execute($sql);	
	//$res = $_SESSION['res']; 
	if($res === false){
       $msg = $global['db']->ErrorMsg();
       add_error($msg);
       display_errors();
       return false;
    }
    
    else{
    	if ($res->RecordCount() <= 0){
    		add_alert("No Requests are available");
    		
    	}
    	else{
    		$check_i = 0;
    		for($i = 0;$i < $res->RecordCount();$i++){
    			if($_SESSION['record_start'] <= $i && $check_i < 5){
    				$item = _shn_rms_get_itemname($res->fields['item_uuid']);
    				$pqty = _shn_rms_plg_item_amount($res->fields['item_uuid']);
    				add_data($item, $res->fields['qty']);
    				add_data($item, $pqty);
    				$check_i++;
    			}
    			$res->MoveNext();
    		}
    		$keyword_arr = array('chart'=>'bar chart'.$_SESSION['record_start'],'mod'=>'rms');
    		$legend = array('To be fulfilled', 'In hand');	
			generate_barchart("Barchart".$_SESSION['record_start'],"Requested items","","",$keyword_arr,$legend);
		}
    }

}

function shn_rms_requested_items(){
	if ($_REQUEST['rec'] == NULL){
		$_SESSION['record_start'] = 0;
	}
	else{
		$_SESSION['record_start'] = $_REQUEST['rec'];
	}		
		_shn_rms_requested_items_table($_SESSION['record_start']);
		shn_chart_display("shn_rms_requested_items_chart");			
}

/**
 * get available amounts in inventories 
 */
function _shn_rms_get_items_in_inventory($item){
	global $global;
	$sql = "SELECT SUM(amount) AS qty FROM ims_item_records WHERE catalog_id = '$item' GROUP BY catalog_id";
	$res = $global['db']->Execute($sql);
	if ($res === false){
		return 0;
	}
	else{
		return $res->fields['qty'];
	}
}

/**
 * generate a bar chart for items in hand without request
 */
function shn_rms_items_without_request_chart(){
	global $global;
	$sql = '
SELECT p.plg_uuid, p.item_uuid AS item_uuid, SUM( p.quantity ) AS pqty, SUM( f.quantity ) AS fqty
FROM rms_plg_item AS p
LEFT JOIN rms_fulfil AS f ON p.plg_uuid = f.plg_uuid
WHERE (

status = "confirmed"
OR status = "delivered"
)
AND p.item_uuid NOT
IN (

SELECT rms_plg_item.item_uuid
FROM rms_plg_item
INNER JOIN rms_req_item ON rms_req_item.item_uuid = rms_plg_item.item_uuid
WHERE rms_req_item.req_uuid
IN (

SELECT req_uuid
FROM rms_request
WHERE STATUS = "open"
)
)
GROUP BY item_uuid';
	$res = $global['db']->Execute($sql);
	
	$sql2 = 'SELECT SUM( amount ) AS qty, catalog_id
		FROM ims_item_records
		WHERE catalog_id NOT
		IN ( SELECT item_uuid FROM rms_plg_item WHERE status = "confirmed" OR status ="delivered") ' .
		'AND catalog_id NOT IN (SELECT item_uuid FROM rms_req_item WHERE req_uuid IN (SELECT req_uuid FROM rms_request WHERE status = "open"))GROUP BY catalog_id';
    $res2 = $global['db']->Execute($sql2);
    
    $rec = $_SESSION['record_start'];
    $check_i=0;
	for($i = 0;$i < $res->RecordCount();$i++){		
    		if($_SESSION['record_start'] <= $i && $check_i < 5 ){
    			$item = _shn_rms_get_itemname($res->fields['item_uuid']);
    			if ($res->fields['pqty'] >= $res->fields['fqty']){
    				$qty = $res->fields['pqty'] - $res->fields['fqty'] + _shn_rms_get_items_in_inventory($res->fields['item_uuid']);
    			}
    			else{
    				$qty = _shn_rms_get_items_in_inventory($res->fields['item_uuid']);
    			}
    			if ($qty > 0){
    				add_data($item, $qty);
    				$check_i++;
    			}
    		}
    		else{
    			if ($check_i == 5){
    				break;
    			}
    		}
    		$res->MoveNext();
    }
    
    $rec = $rec - $res->RecordCount();
    
    for($i = 0;$i < $res2->RecordCount();$i++){
    		if($rec <= $i && $check_i < 5 ){
    			$item = _shn_rms_get_itemname($res2->fields['catalog_id']);
    			add_data($item, $res2->fields['qty']);
    			$check_i++;
    		}
    		else{
    			if ($check_i == 5)
    				break;
    		}
    		$res2->MoveNext();
    }
    $keyword_arr = array('chart'=>'bar chart','mod'=>'rms');	
	generate_barchart("Barchart".$_SESSION['record_start'],"Items without requests","","",$keyword_arr);
}

/**
 * generate a table for items in hand without a request
 */
function _shn_rms_items_without_request_table($rec){
	global $global;
	
	$sql = '
SELECT p.plg_uuid, p.item_uuid AS item_uuid, SUM( p.quantity ) AS pqty, SUM( f.quantity ) AS fqty, p.unit
FROM rms_plg_item AS p
LEFT JOIN rms_fulfil AS f ON p.plg_uuid = f.plg_uuid
WHERE (

status = "confirmed"
OR status = "delivered"
)
AND p.item_uuid NOT
IN (

SELECT rms_plg_item.item_uuid
FROM rms_plg_item
INNER JOIN rms_req_item ON rms_req_item.item_uuid = rms_plg_item.item_uuid
WHERE rms_req_item.req_uuid
IN (

SELECT req_uuid
FROM rms_request
WHERE STATUS = "open"
)
)
GROUP BY item_uuid';
	$res = $global['db']->Execute($sql);

	$sql2 = 'SELECT SUM( amount ) AS qty, catalog_id, unit
FROM ims_item_records
WHERE catalog_id NOT
IN ( SELECT item_uuid FROM rms_plg_item WHERE status = "confirmed" OR status ="delivered") ' .
		'AND catalog_id NOT IN (SELECT item_uuid FROM rms_req_item WHERE req_uuid IN (SELECT req_uuid FROM rms_request WHERE status = "open"))GROUP BY catalog_id';
    $res2 = $global['db']->Execute($sql2);
    
    if ($res->RecordCount() <= 0 && $res2->RecordCount() <= 0){
    	add_Error('No items in hand without a request');
    }
    else{
    	$check_i=0;
    	$cur = 0;
    	$th_items[] = array(_t('Item'), _t('Quantity'), _t('Unit'));
    	for ($i = 0; $i < $res->RecordCount(); $i++){
    		if($_SESSION['record_start'] <= $i && $check_i < 5 ){
    			$item = _shn_rms_get_itemname($res->fields['item_uuid']);    			
    			if($res->fields['pqty'] > $res->fields['fqty']){
    				$qty = $res->fields['pqty'] - $res->fields['fqty'] + _shn_rms_get_items_in_inventory($res->fields['item_uuid']);
    			}
    			else{
    				$qty = _shn_rms_get_items_in_inventory($res->fields['item_uuid']); 
    			}
    			$unit = _shn_rms_get_iunit_name($res->fields['unit']);
    			if($qty > 0){
    				$tb_items[] = array($item, $qty, $unit);
    				$check_i++;
    			}
    		}
    		else{
    			if ($check_i == 5){
    				break;
    			}
    		}
    		$res->MoveNext();
    	}
    	$rec = $rec - $res->RecordCount();
    	for ($i = 0; $i < $res2->RecordCount(); $i++){
    		if($rec <= $i && $check_i < 5 ){
    			$item = _shn_rms_get_itemname($res2->fields['catalog_id']);
    			$unit = _shn_rms_get_iunit_name($res2->fields['unit']);
    			if ($res2->fields['qty'] > 0){
    				$tb_items[] = array($item, $res2->fields['qty'], $unit);
    				$check_i++;
    			}
    		}
    		else{
    			if ($check_i == 5)
    				break;
    		}
    		$res2->MoveNext();
    	}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
		print '<br />';
    	if($_SESSION['record_start'] != 0)
    	    echo '<a href="index.php?mod=rms&act=items_without_request&rec='.($_SESSION['record_start']-5).'">Previous</a>';
    	if(($_SESSION['record_start'] + 5) < ($res->RecordCount() + $res2->RecordCount()))
    	    echo '<a href="index.php?mod=rms&act=items_without_request&rec='.($_SESSION['record_start']+5).'">next</a>';
    }

}

function shn_rms_items_without_request(){
	print '<h4>' . _t("Items in hand without a request") . '</h4><br>';
	if ($_REQUEST['rec'] == NULL){
		$_SESSION['record_start'] = 0;
	}
	else{
		$_SESSION['record_start'] = $_REQUEST['rec'];
	}
	_shn_rms_items_without_request_table($_SESSION['record_start']);
	shn_chart_display("shn_rms_items_without_request_chart");	
}

/**
 * generate a bar chart for scarcity of items
 */
function shn_rms_scarcity_of_item_chart(){
	global $global;
	$sql = "SELECT SUM(quantity) AS qty, item_uuid FROM rms_req_item WHERE req_uuid IN(SELECT req_uuid FROM rms_request WHERE status = 'open') GROUP BY item_uuid";
	$res = $global['db']->Execute($sql);
	echo $global['db']->ErrorMsg();
	for($i = 0;$i < $res->RecordCount();$i++){
    	$item = _shn_rms_get_itemname($res->fields['item_uuid']);
    	$pqty = _shn_rms_plg_item_amount($res->fields['item_uuid']);
    	$rqty = $res->fields['qty'];
    	$qty = $rqty - $pqty;
    	if ($qty > 0){
    		$array[] = array($qty, $item);
    	}
    	$res->MoveNext();
    }
    array_multisort($array, SORT_DESC);
    $index = 0;
    $check_i = 0;
    foreach($array as $a){
    	if($_SESSION['record_start'] <= $index && $check_i < 5){
    		add_data($a[1], $a[0]);
    		$check_i++;
    	}
    	else{
    		if($check_i == 5){
    			break;
    		}
    	}
    	$res->MoveNext();
    	$index++;
    }
    $keyword_arr = array('chart'=>'bar chart','mod'=>'rms');	
	generate_barchart("Barchart".$_SESSION['record_start'],"Scarcity of items","","",$keyword_arr);
}

/**
 * generate a table for scarcity of items
 */
function _shn_rms_scarcity_of_item_table($rec){
	global $global;
	$sql = "SELECT SUM(quantity) AS qty, item_uuid, unit FROM rms_req_item WHERE req_uuid IN(SELECT req_uuid FROM rms_request WHERE status = 'open') GROUP BY item_uuid";
	$res = $global['db']->Execute($sql);
	echo $global['db']->ErrorMsg();
	for($i = 0;$i < $res->RecordCount();$i++){
    	$item = _shn_rms_get_itemname($res->fields['item_uuid']);
    	$pqty = _shn_rms_plg_item_amount($res->fields['item_uuid']);
    	$rqty = $res->fields['qty'];
    	$qty = $rqty - $pqty;
    	$unit = _shn_rms_get_iunit_name($res->fields['unit']);
    	if ($qty > 0){
    		$array[] = array($qty, $item, $unit);
    	}
    	$res->MoveNext();
    }
    array_multisort($array, SORT_DESC);
    $index = 0;
    $check_i = 0;
    $th_items[] = array(_t('Item'), _t('Scarcity'), _t('Unit'));
    foreach($array as $a){
    	if($_SESSION['record_start'] <= $index && $check_i < 5){
    		$tb_items[] = array($a[1], $a[0], $a[2]);
    		$check_i++;
    	}
    	else{
    		if($check_i == 5){
    			break;
    		}
    	}
    	$res->MoveNext();
    	$index++;
    }
    shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	print '<br />';
    if($_SESSION['record_start'] != 0)
        echo '<a href="index.php?mod=rms&act=scarcity_of_item&rec='.($_SESSION['record_start']-5).'">Previous</a>';
    if(($_SESSION['record_start'] + 5) < $res->RecordCount())
        echo '<a href="index.php?mod=rms&act=scarcity_of_item&rec='.($_SESSION['record_start']+5).'">next</a>';
    
}

function shn_rms_scarcity_of_item(){
	print '<h4>' . _t("Scarcity of Requested Items") . '</h4><br>';
	if ($_REQUEST['rec'] == NULL){
		$_SESSION['record_start'] = 0;
	}
	else{
		$_SESSION['record_start'] = $_REQUEST['rec'];
	}
	_shn_rms_scarcity_of_item_table($_SESSION['record_start']);
	shn_chart_display("shn_rms_scarcity_of_item_chart");
}

/**
 * for for select the location and the status 
 */
function _shn_rms_item_by_loaction_form(){
	global $global;
	$sql = 'SELECT loc_uuid FROM rms_request WHERE status = "open"';
	$res = $global['db']->Execute($sql);
	if ($res->RecordCount() > 0){
		$d_arr = array();
		for ($i = 0; $i < $res->RecordCount(); $i++){
			$d_arr[$res->fields('loc_uuid')] = _shn_rms_get_name($res->fields('loc_uuid'));
			$res->MoveNext();
		}
		$status = array('open'=>'Open', 'closed'=>'Closed');
		shn_form_fopen("item_by_location",null, array('req_message'=>false));
		shn_form_fsopen(_t("Select the location and the status"));
		shn_form_hidden(array('seq'=>'gen'));
		shn_form_select($d_arr, _t('Location'), 'location');
		shn_form_select($status, _t('Status'), 'status');
    	shn_form_submit(_t("Generate"),'submit');
    	shn_form_fsclose();
    	shn_form_fclose();
	}
	else{
		_shn_html_print_alert("No Request has been added");	
	}
}

/**
 * return the fulfill quantity
 * filtered by location and the status
 */
function _shn_rms_get_fulfilled_qty($item){
	global $global;
	$sql = "SELECT SUM(quantity) AS qty FROM rms_fulfil WHERE item_uuid = '$item' AND req_uuid IN (SELECT req_uuid FROM rms_request WHERE loc_uuid = '".$_SESSION['location']."' AND status = '".$_SESSION['status']."') GROUP BY item_uuid";
	$res = $global['db']->Execute($sql);
	if ($res->RecordCount() <= 0){
		return 0;
	}
	else{
		return $res->fields['qty'];
	}
}

/**
 * generate the customized table
 * filted by location and status
 */
function _shn_rms_item_by_location_table(){
	global $global;
	$sql = _shn_rms_item_by_location_sql();
	$res = $global['db']->Execute($sql);
	if ($res->RecordCount() <= 0){
		_shn_html_print_alert("No ".$_SESSION['status']." request for "._shn_rms_get_name($_SESSION['location']));
	}
	else{
		$check_i = 0;
		$th_items[] = array(_t('Item'), _t('Requested Quantity'), _t('Fulfilled Quantity'), _t('Unit'));
		for($i = 0; $i < $res->RecordCount(); $i++){
			if ($_SESSION['record_start'] <= $i && $check_i <5){
				$item = _shn_rms_get_itemname($res->fields['item_uuid']);
				$fqty = _shn_rms_get_fulfilled_qty($res->fields['item_uuid']);
				$qty = $res->fields['qty'];
				$unit = _shn_rms_get_iunit_name($res->fields['unit']);
				$tb_items[] = array($item, $qty, $fqty, $unit);
				$check_i++;				
			}
			else{
    			if ($check_i == 5)
    				break;
    		}
    		$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
		if($_SESSION['record_start'] != 0)
        echo '<a href="index.php?mod=rms&act=item_by_location_report&rec='.($_SESSION['record_start']-5).'">Previous</a>';
    if(($_SESSION['record_start'] + 5) < $res->RecordCount())
        echo '<a href="index.php?mod=rms&act=item_by_location_report&rec='.($_SESSION['record_start']+5).'">next</a>';
    
	}
}

/**
 * cunstruct the sql query using filtering parameters
 */
function _shn_rms_item_by_location_sql(){
	$sql = "SELECT item_uuid, SUM(quantity) As qty, unit FROM rms_req_item";
	if ($_SESSION['location'] != ''){
		$sql .=" WHERE req_uuid IN (SELECT req_uuid FROM rms_request WHERE loc_uuid = '".$_SESSION['location']."'";
	}
	if ($_SESSION['status'] != ''){
		$sql .= " AND status = '".$_SESSION['status']."')";
	}
	$sql .= " GROUP BY item_uuid ORDER BY SUM(quantity) DESC";
	return $sql;
}

/**
 * generate the customized chart
 * filted by location and status
 */
function shn_rms_item_by_location_chart(){
	global $global;
	$sql = _shn_rms_item_by_location_sql();
	$res = $global['db']->Execute($sql);
	if ($res->RecordCount() <= 0){
		_shn_rms_print_alert("No request for this location");
		return false;
	}
	else{
		$check_i = 0;
		for($i = 0; $i < $res->RecordCount(); $i++){
			if ($_SESSION['record_start'] <= $i && $check_i <5){
				$item = _shn_rms_get_itemname($res->fields['item_uuid']);
				$fqty = _shn_rms_get_fulfilled_qty($res->fields['item_uuid']);
				$qty = $res->fields['qty'];
				add_data($item, $qty);
				add_data($item, $fqty);
				$check_i++;				
			}
			else{
    			if ($check_i == 5)
    				break;
    		}
    		$res->MoveNext();
		}
		$legend = array('Requested', 'fulfilled');
		$keyword_arr = array('chart'=>'bar chart','mod'=>'rms');	
		generate_barchart("Barchart".$_SESSION['location'].$_SESSION['status'],"","","",$keyword_arr,$legend);
	}
}

function shn_rms_item_by_location_report(){
	print '<h4>' . _t("Requested Items to ") ._shn_rms_get_name($_SESSION['location']). '</h4>';
	print '<strong>Status : </strong>'.$_SESSION['status'].'<br><br>';
	if ($_REQUEST['rec'] == NULL){
		$_SESSION['record_start'] = 0;
	}
	else{
		$_SESSION['record_start'] = $_REQUEST['rec'];
	}
	_shn_rms_item_by_location_table();
	shn_chart_display('shn_rms_item_by_location_chart');
	print '<br><a href="index.php?mod=rms&act=item_by_location">[[Back]]<a>';
}

function shn_rms_item_by_location(){
	switch($_REQUEST['seq']){
		case '':
			_shn_rms_item_by_loaction_form();			
			break;
		case 'gen':
			$_SESSION['location'] = $_POST['location'];
			$_SESSION['status'] = $_POST['status'];
			shn_rms_item_by_location_report();
			break;
	}
}
?>