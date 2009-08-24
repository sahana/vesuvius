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
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/
//global $global;
_shn_rms_print_hedder(_t("Fulfil Requests"));

function _shn_mng_set_close($req_id){
	global $global;
	$sql = "UPDATE rms_request SET status = 'closed' WHERE req_uuid = '$req_id'";
	$res = $global['db']->Execute($sql);
	$insert_array['req_uuid'] = $req_id;
	$insert_array['status_date'] = date('Y-m-d');
	//print 'testaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa';
	$q = "SELECT req_uuid FROM rms_request_status_date WHERE req_uuid='$req_id'";
	$rset = $global['db']->Execute($q);
	if($rset->RecordCount()==0)
	{
		$reset = $global['db']->AutoExecute('rms_request_status_date', $insert_array, 'INSERT');
		//print $res;
	}
	else
	{
		$reset = $global['db']->AutoExecute('rms_request_status_date', $insert_array, 'UPDATE', "req_uuid = '".$req_id."'");
		//print $res;
	}
	if ($res === false || $reset=== false){
		$msg = $global['db']->ErrorMsg();
          add_error($msg.' <br> '.$sql);
          display_errors();
          return false;
	} 
	else{
		add_confirmation("Closing request successfully");
		print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_ls">Fullfil Other Request</a> ]';
	}
}

function _shn_rms_mng_change_status($req_id){
	shn_form_fopen("mng_ff",null, array('req_message'=>false));
		shn_form_fsopen(_t("Change the status"));
		_shn_html_print_alert(_t("You have completly fulfill the request, Do you want to close the request?"));
        shn_form_hidden(array('seq'=>'chg_stat'));
        shn_form_submit(_t("Close"),'close');
        shn_form_fsclose();
        shn_form_fclose();
}

function _shn_rms_mng_fulfill_check($req_id){
	global $global;
	
	$sql = "SELECT item_uuid,quantity FROM rms_req_item WHERE req_uuid = '$req_id'";
	$res = $global['db']->Execute($sql);
	if ($res === false){
		$msg = $global['db']->ErrorMsg();
          add_error($msg.' <br> '.$sql);
          display_errors();
          return false;
	} 
	else{
		if ($res->RecordCount() <= 0){
			return false;
		}
		$res_array = $res->GetArray();
		$bool = true;
		foreach ($res_array as $itm){
			$sql1 = "SELECT SUM(quantity) as qty FROM rms_fulfil WHERE req_uuid = '$req_id' AND item_uuid = '$itm[0]'";
			$result = $global['db']->Execute($sql1);
			if ($result === false){
				$msg = $global['db']->ErrorMsg();
          		add_error($msg.' <br> '.$sql);
          		display_errors();
          		return false;
			}
			else{
				if ($itm[1] > $result->fields['qty']){	
					$bool = false;				
					return false;
				}
				//echo $result->fields['qty'];
				
			}
			
		}
		return $bool;
	}
}

function _shn_rms_mng_request()
{
    $_SESSION['rms_req_id'] = null;
    
    
    print '<div id="req_id">';
    print '<div class="info">';
    //print _t("Request / Pledge Matching ");
    print _t("Select a Request from the "). '<a href="index.php?mod=rms&act=req_ls">' . _t("request list") . '</a>';
    print '<br />';
    print '</div>';
//    shn_form_fopen("mng_ff",null, array('req_message'=>false));
//    shn_form_hidden(array('seq'=>'get_req'));
//    shn_form_fsopen(_t("Request"));
//    shn_form_text(_t("Request ID"),'req_id',null,array('br'=>false));
//    shn_form_submit(_t("Next"));
//    shn_form_fsclose();
//    shn_form_fclose();
    print '</div>';
}

function _shn_rms_mng_getrequest($req_id)
{
    $req = _shn_rms_view_request($req_id);
    if ($req === false)
    {
        add_error(_t("Please Enter a valid Request ID"));
        display_errors();
        _shn_rms_mng_request();
        return false;
    }
    print '<br />';
    
    shn_html_table_open(array('class'=>'wide'));
    shn_html_tbody_open();
    shn_html_tr_open();
        
        shn_html_td_open();
        shn_form_fopen("req_ls",null, array('req_message'=>false));
        shn_form_hidden(array('seq'=>''));
        shn_form_submit(_t("Back"));
        shn_form_fclose();
        shn_html_td_close();
        
        shn_html_td_open(array('align'=>'right'));
        shn_form_fopen("mng_ff",null, array('req_message'=>false));
        shn_form_hidden(array('seq'=>'sel_itm'));
        shn_form_submit(_t("Next"));
        shn_form_fclose();
                  
    shn_html_tr_close();
    shn_html_tbody_close();
    shn_html_table_close();


}

function _shn_rms_mng_select_item()
{
    $req_id = $_SESSION['rms_req_id'];
    
    print '<div class="info">';
    print _t("This shows the current fulfillment status of the request, ");
    print _t("Please select an item from the request to be fulfilled.");
    print '<br />';
    print '</div>';
    
    _shn_rms_view_reqff($req_id);
}

function _shn_rms_mng_select_pledge()
{
    global $global;
    $_SESSION['rms_plg_id'] = null;
    $itm = $_SESSION['rms_req_item'];
    
    $sql2 = "SELECT plg_uuid, item_uuid, quantity AS plg_qty, status FROM rms_plg_item WHERE item_uuid = '$itm' AND (status = 'Delivered' OR status = 'Confirmed')";
    
    $rs2 = $global['db']->Execute($sql2);
    if ($rs2 === false){
       $msg = $global['db']->ErrorMsg();
       add_error($msg.' <br> '.$sql2);
       display_errors();
    }
    else{
    	$res_array = $rs2->GetArray();
    	$th_plg[] = array (_t("Item"), _t("Qty"), _t("Used"), _t('Status'), '');
    	if ($rs2->RecordCount() > 0){
    		foreach ($res_array as $res){
    			$sql3 = "SELECT SUM(quantity) AS ff_qty FROM rms_fulfil WHERE plg_uuid = '".$res['plg_uuid'].
						"' AND item_uuid = '".$res['item_uuid']."' ";
				$rs3 = $global['db']->Execute($sql3);
				if ($rs3 === false){
       				$msg = $global['db']->ErrorMsg();
       				add_error($msg.' <br> '.$sql2);
       				display_errors();
    			}
    			else{
    				if ($rs3->RecordCount() > 0){
    					$max_qty = $res['plg_qty'] - $rs3->fields['ff_qty'];
 						$used = $rs3->fields['ff_qty'];
    				}
    				else{
    					$max_qty = $res['plg_qty'];
    					$used = 0;
    				}
    				$sel_url = '<a href=index.php?mod=rms&amp;act=mng_ff' .
                    	    '&amp;seq=add_ff&amp;max_qty=' . $max_qty .
                        	'&amp;plg_id=' . $res['plg_uuid'] .'>' .
                        	_t("Select") . '</a>';
                    if($max_qty > 0){
            			$tb_plg[] = array (
                                 _shn_rms_get_itemname($res['item_uuid']), 
                                 $res['plg_qty'],
                                 $used,
                                 $res['status'],
                                 $sel_url
                                );
                    }
    			}    	
    		}
    	
 
        /**
         * Display the list of pledges
         */
        print '<div class="info">';
        print _t("This shows the list of pledges that have the selected item, ");
        print _t("Please select a pledge from the request to be fulfilled.");
        print '<br />';
        print '</div>';
        print '<br />';
        shn_html_table($tb_plg, $th_plg, null, array('class'=>'wide'));
 	  }
    	else
    	{
    	print '<div id="reqstr_id">';
        print '<div class="info">';
        print _t("No Pledges registered !!!");
        print '<br />';
      //  echo $rs2->RecordCount();
        //print _t("Please try again after adding some pledges.");
        print '<br />';
        print '</div>';
    	}
   ////
   }



print '<br>';
print '<br>';

//**************************** Inventory Items ************************
?>
<div id="result"> 
 
    <table>
    <caption>Items from inventories</caption>
    <thead>
        <td><?=_t("Item")?></td>
        <td><?=_t("Amount")?></td>
        <td><?=_t("Inventory")?></td>
        <td><?=_t('State')?></td>
        <td><?=_t("Action")?></td>
            
            
    </thead>
    <tbody>
    <?php
    $state="available";
   // $ignore_amount=0;
    $db=$global['db'];
    $sql="SELECT item.item_id AS item_id, item.amount AS amount, item.state AS state, inventory.inv_uuid AS inv_uuid, inventory.inventory_name AS inventory_name FROM ims_item_records as item, ims_inventory_records AS inventory WHERE item.inv_id=inventory.inv_uuid AND item.catalog_id='$itm' AND item.state='$state' AND item.amount!=0;";
   // print $sql;
    $res=$db->Execute($sql);
    while(!$res==NULL && !$res->EOF)
    {
        $sql2="SELECT name FROM ct_catalogue WHERE ct_uuid='$itm';";
        $res2=$global['db']->Execute($sql2);
        $item_name=$res2->fields['name'];

        $amount=$res->fields['amount'];
        $inventory_name=$res->fields['inventory_name'];
        $state=$res->fields['state'];
        $inv_id=$res->fields['inv_uuid'];
        $item_id=$res->fields['item_id'];

        //$res->MoveNext();
   // }
    /*$sql="SELECT inv_uuid,inventory_name FROM ims_inventory_records ORDER BY inv_uuid;";
    $res=$db->Execute($sql);
    while(!$res==NULL && !$res->EOF)
    {
        $inv_id=$res->fields['inv_uuid'];
        $inventory_name=$res->fields['inventory_name'];
        $sql1="SELECT SUM(total_amount) as amount FROM ims_item_records WHERE catalog_id='$itm' AND inv_id='$inv_id';";
        $res1=$global['db']->Execute($sql1);
//print $sql1;
        $sql2="SELECT name FROM ct_catalogue WHERE ct_uuid='$itm';";
        $res2=$global['db']->Execute($sql2);
//print $sql2;
        $item_name=$res2->fields['name'];
        $amount=$res1->fields['amount'];
    ?>*/
?>
        <tr>
        <td><?php print $item_name; ?></td>
        <td><?php print $amount; ?></td>
        <td><?php print $inventory_name; ?></td>
        <td><?php print $state;?></td>
        <td><a href="index.php?mod=rms&act=fullfill_from_inventory&seq=<?php echo 'mng_ff_inventory';?>&item_id=<?php echo $item_id;?>&inv_id=<?php echo $inv_id;?>&ct_uuid=<?php echo $itm;?>"><?php print ("Select");?></a></td>
        </tr>
    <?php
        $res->MoveNext();
    }
    ?>
    </tbody>
    </table>
    </div>
    <?php
//*********************************************************************

}

function _shn_rms_mng_addff($max_qty)
{
    $req_id = $_SESSION['rms_req_id'];
    $req_item = $_SESSION['rms_req_item'];
    $plg_id = $_SESSION['rms_req_plg'];
    
    print '<div class="info">';
    print _t("Allocate items from a pledge to fulfill a request, ");
    print _t("The 'Maximum Allocatable Quantity' is the maximum you are allowed to allocate.");
    print '<br />';
    print '</div>';
    
   //_shn_rms_view_reqff($req_id);
   _shn_rms_view_req_item($req_id,$req_item);
    
    _shn_html_print_message(_t("Allocate items from the selected pledge to the request"));
    
    shn_form_fopen("mng_ff",null, array('req_message'=>false));
    shn_form_hidden(array('seq'=>'finish'));
    shn_form_fsopen(_t("Allocate"));
    shn_form_text(_t("Item"),'itm_id','readonly="true"',array('value'=>_shn_rms_get_itemname($req_item)));
    shn_form_text(_t("Maximum Allocatable Quantity"),'max_qty','readonly="true"',array('value'=>$max_qty));
    shn_form_text(_t("Quantity"),'qty',null);
    shn_form_submit(_t("Next"));
    shn_form_fsclose();
    shn_form_fclose();
    
    print '<br />';
    shn_form_fopen("mng_ff",null, array('req_message'=>false));
    shn_form_hidden(array('seq'=>''));
    shn_form_fsopen(_t("Cancel Fulfillment Process"));
    shn_form_submit(_t("Cancel"));
    shn_form_fsclose();
    shn_form_fclose();
    
}

function _shn_rms_allocate_item($ct_uuid, $inv_id)
{
	global $global;
    $db=$global['db'];
    $sql="SELECT name FROM ct_catalogue WHERE ct_uuid='$ct_uuid';";
    $res=$db->Execute($sql);
    $item_id=$_SESSION['rms']['item_id'];
    $sql1="SELECT amount FROM ims_item_records WHERE inv_id='$inv_id' AND item_id='$item_id';";
    $res1=$db->Execute($sql1);

    $sql2 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $res2=$db->Execute($sql2);
    
    $sql_inv = "SELECT inv_uuid, inventory_name FROM ims_inventory_records WHERE inv_uuid !='$inv_id';";
    
    $db->SetFetchMode(ADODB_FETCH_ASSOC);
    $inv_lists = $db->Execute($sql_inv);
    $inventory_list = array();
    foreach($inv_lists as $inv_list){    	   	
    	foreach($inv_list as $key=>$inv){    		
    		$inventory_list[$inv_list['inv_uuid']] = $inv_list['inventory_name'];    		 	
    	}	
    }
    
    
    $req_id = $_SESSION['rms_req_id'];
    _shn_rms_view_req_item($req_id,$ct_uuid);
    _shn_html_print_message(_t("Allocate items from the selected inventory to the request"));
    
    shn_form_fopen('fullfill_from_inventory');
    shn_form_fsopen(_t('Allocate'));
    shn_form_text(_t('Item : '),'item','size="25" readonly=true',array('value'=>$res->fields['name']));
    shn_form_text(_t('Allocatable quantity (Max) : '),'max_quantity','size="25" readonly=true',array('value'=>$res1->fields['amount']));
    shn_form_text(_t('Inventory(From) : '),'inventory','size="25" readonly=true',array('value'=>$res2->fields['inventory_name']));
    shn_form_select($inventory_list,_t('Inventory To'),'inventory_to',null,null);
    shn_form_text(_t('Quantity : '),'quantity','size="25"',null);
    shn_form_fsclose();
    shn_form_hidden(array('seq'=>'inventory_item_allocate_db'));
    shn_form_hidden(array('item_id'=>$item_id));//$inv_id
    shn_form_hidden(array('inv_id'=>$inv_id));    
    shn_form_submit(_t('Submit'));
    shn_form_fclose();
}

function _shn_rms_item_allocation_db()
{
   global $global;
    $db = $global['db'];
    $item_id = $_SESSION['rms']['item_id'];
    $req_uuid = $_SESSION['rms_req_id'];
    $catalog_id = $_SESSION['rms_req_item'];
    $quantity = $_SESSION['rms']['quantity'];
    if ($quantity <= 0 || max_quantity < $quantity){
    	add_error("Quantity should be larger than 0");
        display_errors();
        _shn_rms_allocate_item($catalog_id, $item_id);
    }
    else{
    $available_quantity = $_SESSION['rms']['max_quantity']-$_SESSION['rms']['quantity'];
    if ($available_quantity >= 0){
    $sql = "UPDATE ims_item_records SET amount='$available_quantity' WHERE item_id='$item_id';";
    $res = $db->Execute($sql);
    //print $sql;
    
    $dt2 = date("Y-m-d H:i:s");
    	
    	//$db->StartTrans();
    
		$sql1 = "INSERT INTO rms_fulfil(req_uuid, item_uuid, quantity, ff_date) VALUES ('$req_uuid', '$catalog_id', '$quantity', '$dt2');";
      	$res1 = $db->Execute($sql1);
      	
      	$sql = "SELECT catalog_id, inv_id, transit_id, suplier_id,	item_name, amount, unit, manufactured_date,  
      	expire_date, cost_per_unit, state, inserted_date FROM ims_item_records WHERE item_id = '{$_REQUEST['item_id']}'";
      	
      	$res = $db->GetAll($sql);
      		
      	$insert_item_to_transfer = array();
      	$insert_item_to_transfer['item_id'] = $_REQUEST['item_id'];
      	$insert_item_to_transfer['catalog_id'] = $res[0]['catalog_id'];
      	$insert_item_to_transfer['amount_send'] = $_REQUEST['quantity'];
      	$insert_item_to_transfer['unit'] = $res[0]['unit'];
      	$insert_item_to_transfer['inv_id_from'] = $_REQUEST['inv_id'];
      	$insert_item_to_transfer['inv_id_to'] = $_REQUEST['inventory_to'];
      	$insert_item_to_transfer['destination_type'] = 'Inventory';
      	$insert_item_to_transfer['date_send'] = $dt2;
      	$insert_item_to_transfer['requested_person'] = $req_uuid;      	
      	$insert_item_to_transfer['amount_received'] = $_REQUEST['quantity'];
      	$insert_item_to_transfer['date_received'] = $dt2;	
      	
      	$transfer_res = $db->AutoExecute('ims_transfer_item',$insert_item_to_transfer,'INSERT');
      	$transit_id = $db->Insert_ID();
      	
      	$insert_item_to_inventory = array();
      	$insert_item_to_inventory['catalog_id'] = $res[0]['catalog_id'];
      	$insert_item_to_inventory['inv_id'] = $_REQUEST['inventory_to'];
      	$insert_item_to_inventory['transit_id'] = $transit_id;
      	$insert_item_to_inventory['suplier_id'] = $res[0]['suplier_id'];
      	$insert_item_to_inventory['item_name'] = $res[0]['item_name'];
      	$insert_item_to_inventory['amount'] = $_REQUEST['quantity'];
      	$insert_item_to_inventory['unit'] = $res[0]['unit'];
      	$insert_item_to_inventory['manufactured_date'] = $res[0]['manufactured_date'];
      	$insert_item_to_inventory['expire_date'] = $res[0]['expire_date'];
      	$insert_item_to_inventory['cost_per_unit'] = $res[0]['cost_per_unit'];
      	$insert_item_to_inventory['state'] = $res[0]['state'];
      	$insert_item_to_inventory['inserted_date'] = $dt2;
      	
      	$inventory_res = $db->AutoExecute('ims_item_records',$insert_item_to_inventory,'INSERT');      
      	$received_item_id = $db->Insert_ID();
      	
      	
      	$insert_item_to_transfer_update = array();
      	$insert_item_to_transfer_update['received_item_id'] = $received_item_id;
      	
      	$transfer_res_update = $db->AutoExecute('ims_transfer_item',$insert_item_to_transfer_update,'UPDATE',"transit_id='$transit_id'");
      	
      	$insert_ims_item_amount_history = array();
      	$insert_ims_item_amount_history['item_id'] = $received_item_id;
      	$insert_ims_item_amount_history['first_amount'] = $_REQUEST['quantity'];
      	$insert_ims_item_amount_history['unit'] = $res[0]['unit'];
      	
      	$amount_history_res = $db->AutoExecute('ims_item_amount_history',$insert_ims_item_amount_history,'INSERT');
      	//$db->CompleteTrans();
      	
      	if($sql1 && $transfer_res && $inventory_res && $transfer_res_update && $amount_history_res){
	      	add_confirmation("Submition successfull");
	      	$stat = _shn_rms_mng_fulfill_check($_SESSION['rms_req_id']);
	        if ($stat){
	        	_shn_rms_mng_change_status($_SESSION['rms_req_id']);
	        }	
      	}
      	else{
      		$msg = $global['db']->ErrorMsg();
	        add_error($msg.' <br> '.$sql);
	        display_errors();
      	}      	
	   
  	  _shn_rms_view_reqff($_SESSION['rms_req_id']);
  	  print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_ls&amp;seq=view_req&amp;req_id='. $_SESSION['rms_req_id'] .'">Fullfil Another Item From the Same Request</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_ls">Fullfil Other Request</a> ]';
    }
    else{
    	 add_error(_t("Please enter a valid 'Quantity', The 'Quantity' should be equal or less than the Maximum Value"));
         display_errors();
         _shn_rms_allocate_item($_POST['max_qty']);
         return false;
    }
    }
}

switch ($_REQUEST['seq'])
{

    case '':
            $_SESSION['rms_req_id'] = null;
            $_SESSION['rms_mng_ff_added'] = false;
            _shn_rms_mng_request();
            echo "do something";
            break;
            
    case 'get_req':
            $req_id = $_REQUEST['req_id'];
            $_SESSION['rms_req_id'] = $req_id;
            $_SESSION['rms_mng_ff_added'] = false;
            _shn_rms_mng_getrequest($req_id);
            break;
    
    case 'sel_itm':
            $_SESSION['rms_req_item'] = null;
            _shn_rms_mng_select_item();
            break;
    
    case 'sel_plg':
            $_SESSION['rms_req_id'] = $_REQUEST['req_id'];
            $_SESSION['rms_req_item'] = $_REQUEST['itm_id'];
            _shn_rms_mng_select_pledge();
            break;
            
    case 'add_ff':
            $_SESSION['rms_req_plg'] = $_REQUEST['plg_id'];
            $max_qty = $_REQUEST['max_qty'];            
            _shn_rms_mng_addff($max_qty);
            break;

    case 'mng_ff_inventory':
            $_SESSION['rms']['ct_uuid'] = $_REQUEST['ct_uuid'];
            $_SESSION['rms']['inv_id'] = $_REQUEST['inv_id'];
            $_SESSION['rms']['item_id'] = $_REQUEST['item_id'];
            _shn_rms_allocate_item($_SESSION['rms']['ct_uuid'], $_SESSION['rms']['inv_id']);
            break;

    case 'inventory_item_allocate_db':
            $_SESSION['rms']['quantity'] = $_POST['quantity'];
            $_SESSION['rms']['max_quantity'] = $_POST['max_quantity'];
            _shn_rms_item_allocation_db($_SESSION['rms']['quantity'],$_SESSION['rms']['max_quantity']);
            break;
            
    case 'chg_stat':
    		//if (isset($_POST['close'])){
    			_shn_mng_set_close($_SESSION['rms_req_id']);
    		//}
    		
    		break;
            
    case 'finish';
            if ($_POST['qty'] > $_POST['max_qty'])
            {
                add_error(_t("Please enter a valid 'Quantity', The 'Quantity' should be equal or less than the Maximum Value"));
                display_errors();
                _shn_rms_mng_addff($_POST['max_qty']);
                return false;
            }
            if ($_POST['qty'] <= 0){
            	add_error(_("Please enter a valid 'Quantity', The 'Quantity' should be larger than the 0"));
                display_errors();
                _shn_rms_mng_addff($_POST['max_qty']);
                return false;
            }
            if (!$_SESSION['rms_mng_ff_added'])
            {
                $req_id = $_SESSION['rms_req_id'];
                $req_item = $_SESSION['rms_req_item'];
                $plg_id = $_SESSION['rms_req_plg'];
                $qty = $_POST['qty'];
                
                $res = _shn_rms_add_ff($req_id, $req_item, $plg_id, $qty);
                $_SESSION['rms_mng_ff_added'] = $res;
            }
            
            if ($_SESSION['rms_mng_ff_added'])
            {
                add_confirmation(_t("The Fulfillment Data was successfully added"));
                _shn_rms_view_reqff($_SESSION['rms_req_id']);
                $_SESSION['rms_mng_ff_added'] = 0;
                $stat = _shn_rms_mng_fulfill_check($_SESSION['rms_req_id']);
                if ($stat){
                	_shn_rms_mng_change_status($_SESSION['rms_req_id']);
                }
            }
            
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=mng_ff&amp;seq=get_req&amp;req_id='. $_SESSION['rms_req_id'] .'">Fullfil Another Item From the Same Request</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_ls">Fullfil Other Request</a> ]';
            break;
            break;
}
?>
