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
        shn_form_fopen("mng_ff",null, array('req_message'=>false));
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
    
    $sql = "SELECT plg.plg_uuid AS plg_uuid, plg.item_uuid AS item_uuid, " .
                "plg.quantity AS plg_qty, SUM(ff.quantity) AS ff_qty  " .
           "FROM rms_plg_item AS plg LEFT JOIN rms_fulfil AS ff " .
           "ON plg.plg_uuid=ff.plg_uuid AND plg.item_uuid=ff.item_uuid " .
           "WHERE plg.item_uuid='$itm' " .
           "AND ff.quantity IS NULL " .
           "OR plg.quantity>ff.quantity " .
           "GROUP BY item_uuid";
    
   // print ">>>>>>>>>>$sql";
    $rs = $global['db']->Execute($sql);
    $rs_arr = $rs->GetArray(); 
    
    if (1 <= count($rs_arr)) 
    {
        $th_plg[] = array (_t("Item"), _t("Qty"), _t("Used"), '');
         
        foreach ($rs_arr as $plg)
        {
            $max_qty = $plg['plg_qty'] - $plg['ff_qty'];
            $sel_url = '<a href=index.php?mod=rms&amp;act=mng_ff' .
                        '&amp;seq=add_ff&amp;max_qty=' . $max_qty .
                        '&amp;plg_id=' . $plg['plg_uuid'] .'>' .
                        _t("Select") . '</a>';
                        
            $tb_plg[] = array (
                                 _shn_rms_get_itemname($plg['item_uuid']), 
                                 $plg['plg_qty'],
                                 $plg['ff_qty'],
                                 $sel_url
                                );
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
        print _t("Please try again after adding some pledges.");
        print '<br />';
        print '</div>';
    }




print '<br>';
print '<br>';

//**************************** Inventory Items ************************
?>
<div id="result"> 
 
    <table>
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
    
    _shn_rms_view_reqff($req_id);
    
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
//print $sql1;
    $sql2 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $res2=$db->Execute($sql2);
    shn_form_fopen('fullfill_from_inventory');
    shn_form_fsopen(_t('Allocate'));
    shn_form_text(_t('Item : '),'item','size="25" readonly=true',array('value'=>$res->fields['name']));
    shn_form_text(_t('Allocatable quantity (Max) : '),'max_quantity','size="25" readonly=true',array('value'=>$res1->fields['amount']));
    shn_form_text(_t('Inventory : '),'inventory','size="25" readonly=true',array('value'=>$res2->fields['inventory_name']));
    shn_form_text(_t('Quantity : '),'quantity','size="25"',null);
    shn_form_fsclose();
    shn_form_hidden(array('seq'=>'inventory_item_allocate_db'));
    shn_form_submit(_t('Submit'));
    shn_form_fclose();
}

function _shn_rms_item_allocation_db()
{
    global $global;
    $db=$global['db'];
    $item_id=$_SESSION['rms']['item_id'];
    $available_quantity=$_SESSION['rms']['max_quantity']-$_SESSION['rms']['quantity'];
    $sql="UPDATE ims_item_records SET amount='$available_quantity' WHERE item_id='$item_id';";
    $res=$db->Execute($sql);
    //print $sql;
    $req_uuid=$_SESSION['rms_req_id'];
    $catalog_id=$_SESSION['rms_req_item'];
    $quantity=$_SESSION['rms']['quantity'];
    //$dt2=date("Y-m-d H:i:s");
    //print $dt2;
    $sql="SELECT * FROM rms_fullfill WHERE req_uuid='$req_uuid';";
    $res=$db->Execute($sql);
    if($res->EOF)
    {
         $sql1="INSERT INTO rms_fullfill VALUES ('$req_uuid', '$catalog_id', '$item_id', '$quantity', $dt2);";
         $res1=$db->Execute($sql1);
    }
    else
    {
        //update
        $previous_quantity=$res->fields['quantity'];
        $new_quantity=$previous_quantity + $quantity;
        $sql2="UPDATE rms_fullfill SET quantity='$new_quantity' WHERE req_uuid='$req_uuid';";
        $res2=$db->Execute($sql2);
    }
/*print $req_uuid;
print '<br>';
print $catalog_id;
print '<br>';
print $item_id;
print '<br>';
print $_SESSION['rms']['quantity'];*/

   // $sql="UPDATE rms_fullfill SET quantity='$_SESSION['rms']['quantity']' WHERE  ";
}

switch ($_REQUEST['seq'])
{

    case '':
            $_SESSION['rms_req_id'] = null;
            $_SESSION['rms_mng_ff_added'] = false;
            _shn_rms_mng_request();
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
            
    case 'finish';
            if ($_POST['qty'] > $_POST['max_qty'])
            {
                add_error(_t("Please enter a valid 'Quantity', The 'Quantity' should be equal or less than the Maximum Value"));
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
                _shn_html_print_alert(_t("The Fulfillment Data was successfully added"));
                _shn_rms_view_reqff($_SESSION['rms_req_id']);
            }
            
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=mng_ff&amp;seq=get_req&amp;req_id='. $_SESSION['rms_req_id'] .'">Fullfil Another Item From the Same Request</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=mng_ff">Fullfil Other Request</a> ]';
            break;
            break;
}
?>