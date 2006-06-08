<?php
/**
* Sahana Inventory Management System Item transfer page
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author        Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright        Lanka Software Foundation - http://www.opensource.lk
* @package        Sahana
* @subpackage        ims
* @tutorial        
* @license          http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
include_once $global['approot'].'/mod/cs/lib_cs.inc';
include_once $global['approot']."/inc/lib_errors.inc";
include_once ("errors.inc");
include_once ('lib_ims.inc');

function _shn_ims_send_main()
{
?>
    <h1 align="center"><?php print _("Send Item between Inventories"); ?> </h1>
    <h1 align="center"><?php print _("Please select the Item to be sent"); ?></h1>
    <div id="result">
<?php
    $form_opts['name']='subcat';
    shn_form_fopen("send_item_page",null,$form_opts);
    $depth=get_max_depth();
    shn_sub_cat($depth,'subcat');
    //shn_sub_cat(6,'subcat');


    shn_form_fclose();
}

/**
**Function For Send Item table view page
**/
function _shn_ims_send_item_table_view_($catalog_id)
{
    //print $catalog_id;
    $depth=get_max_depth();

    if($catalog_id==NULL)
    {
        $parent_id = trim($_POST['0']);
        for($i=1;$i<$depth;$i++)
        {
            $parent_id = trim($_POST[$i]);
    
            if($parent_id==null)
            {
                $parent_id = $_POST[$i-1];
                break;
            }
        }
    }
    else
    {
        $parent_id=$catalog_id;
    }
    //print ("test");    
    //echo $parent_id;
?>
    <h1 align="center"><?php print _("Send Item between Inventories") ?></h1>
    <div id="result">
    <table>
    <thead>
            <td><?=_("Item")?></td>
            <td><?=_("Amount");?></td>
            <td><?=_("Unit");?></td>
            <td><?=_("Manufactured Date")?></td>
                <td><?=_("Expire Date")?></td>
            <td><?=_("Available Inventory")?></td>
                <td><?=_("state")?></td>
        <td><?=_("Send Item")?></td>
        </thead>
    <tbody>
<?php
        global $global;
        $state_des="destroyed";
        $db=$global["db"];
                
        $sql1 = "SELECT item_id,inv_id,item_name,amount,unit,manufactured_date,expire_date,state FROM ims_item_records WHERE catalog_id='$parent_id' AND state!='$state_des' ;";

        //print $sql1;
        
        $ims1 = $db->Execute($sql1);

        while (!$ims1==NULL && !$ims1->EOF)
        {
            $item_id=$ims1->fields["item_id"];
            $inv_id=$ims1->fields["inv_id"];
            $item_name=$ims1->fields["item_name"];
            $amount=$ims1->fields["amount"];
            $unit=$ims1->fields["unit"];
            $manufactured_date=$ims1->fields["manufactured_date"];
            $expire_date=$ims1->fields["expire_date"];
            $state=$ims1->fields["state"];

            $unit_name=get_unit_name($unit);
            
            
        
        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid=$inv_id;";
        $ims2= $db->Execute($sql2);
        //print $sql2;
        $inventory_name = $ims2->fields["inventory_name"];            

?>
        <tr>
        <td><?php print ($item_name);?></td>
        <td><?php print ($amount); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($manufactured_date); ?></td>
        <td><?php print ($expire_date);?></td>
        <td><?php print ($inventory_name);?></td>
        <td><?php print ($state); ?></td>
        <td><a href="index.php?mod=ims&act=send_item_data_collectpage&item_id=<?php echo $item_id;?>&parent_id=<?php echo $parent_id; ?>&unit_id=<?php echo $unit;?>"><?php print ("Send");?></a></td>        
        </tr>

<?php
        $ims1->MoveNext();
        //$ims2->MoveNext();
        }
?>
            
    </tbody>
    </table>
</div>
<?php    
}

function _shn_ims_send($item_id,$parent_id,$unit_id_send)
{
    
    global $global;
    $db=$global["db"];
    $sql1="SELECT item_name,inv_id,suplier_id,unit,cost_per_unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims1=$db->Execute($sql1);
    $item_name=$ims1->fields['item_name'];
    $inv_id_from=$ims1->fields['inv_id'];
    $suplier_id=$ims1->fields['suplier_id'];
    $unit=$ims1->fields['unit'];
    $cost_per_unit=$ims1->fields['cost_per_unit'];

    $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
    $ims2=$db->Execute($sql2);
    $inv_from=$ims2->fields['inventory_name'];
    
        
?>
<h1 align="center"><?php print _("Send Item between Inventories")?> </h1>
<div id="result">
<?php
    shn_form_fopen("send_item_db");
    //$extra_opts['req']=true;
    shn_form_fsopen("Item Transfer");
    
    $extra_opts['value']=$item_name;
    shn_form_text(_("Item Send : "),'item_name','size="50" readonly=true',$extra_opts);
    //$extra_opts['req']=true;
    shn_form_text(_("Amount Send: "),'amount','size="50"',array('req'=>true));

    /*$myoptions=array();
    $myoptions=get_unitid_array();
    
    shn_form_select($myoptions,_("Unit : "),'unit_select','size="1"',array('help'=>_('Select the Measurement unit for entered amount. If this box is empty go back to the catalogue system and add a measurement unit')));*/
    
//-------------------------------------------------------------------------------------------------------------

    $cq="SELECT name FROM ct_unit WHERE unit_uuid='$unit_id_send';";
    $cms=$db->Execute($cq);
    //print $cq;
    $unit_select_array[$unit_id_send]=$cms->fields['name'];
    
    $query="select * from ct_cat_unit where ct_uuid='$parent_id'";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {



    $temp2=$res->fields['unit_uuid'];
    $query1="select name from ct_unit where unit_uuid ='$temp2'";
    $res2=$db->Execute($query1);
    
    $unit_select_array[$res->fields['unit_uuid']]=$res2->fields['name'];
    $res->MoveNext();
    }    

    shn_form_select($unit_select_array,_("Unit : "),'unit_select','size="1"',array('req'=>true,'help'=>_('Select the Measurement unit for entered amount. If this box does not contain the desired measurement unit please go back to the catalogue system and add')));
    /*$query="select * from ct_cat_unit where ct_uuid='$parent_id'";
    $res=$db->Execute($query);
    //print $query;

    while(!$res==NULL && !$res->EOF)
    {
    $temp2=$res->fields['unit_uuid'];
    $query1="select name from ct_unit where unit_uuid ='$temp2'";
    $res2=$db->Execute($query1);
    //print $query1;    
    $myoptions[$res->fields['unit_uuid']]=$res2->fields['name'];;
    $res->MoveNext();
    }
    
    shn_form_select($myoptions,_("Unit : "),'unit_select','size="1"',array('req'=>true,'help'=>_('Select the Measurement unit for entered amount. If this box does not contain the desired measurement unit please go back to the catalogue system and add')));*/

//-------------------------------------------------------------------------------------------------------------    

    
    
    $extra_opts['value']=$inv_from;
    shn_form_text(_("From the Inventory : "),'inv_from','size="50" readonly=true',$extra_opts);

    $inventory_array=array();
    $sql3="SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid!='$inv_id_from';";
    $ims3=$db->Execute($sql3);
    while($ims3!=NULL && !$ims3->EOF)
    {
        $inventory_array[$ims3->fields['inv_uuid']]=$ims3->fields['inventory_name'];
        $ims3->MoveNext();
    }
    shn_form_select($inventory_array,_("To the Inventory : "),'inv_to','size="1"',array('req'=>true,'help'=>_('Select the Inventory which items to be sent')));

    shn_form_text(_("Date"),'date','size="50"',array('req'=>true,'help'=>_('Year-Month-Date. Only - seperater is accepted')));
    $extra_opts['value']=$cost_per_unit;
    shn_form_text(_("Cost Per Unit : "),'cost_per_unit','size="50"',$extra_opts);

    shn_form_fsclose();

    shn_form_fsopen("Contacts");
    shn_form_text(_("Authorized by : "),'authorized_person','size="50"',array('req'=>true,'help'=>_('Person who send Item')));
    shn_form_text(_("Requested by : "),'requested_person','size="50"',array('req'=>true));
    shn_form_text(_("Destribution Method : "),'destribution','size="50"',array('req'=>true));
    shn_form_textarea(_("Cause"),'cause','size="40"',null);
    
    shn_form_fsclose();

    shn_form_hidden(array('item_id'=>$item_id));
    shn_form_hidden(array('inv_id_from'=>$inv_id_from));
    shn_form_hidden(array('parent_id'=>$parent_id));
    shn_form_hidden(array('suplier_id'=>$suplier_id));
    shn_form_submit("Send");
    shn_form_fclose();
}


function _shn_ims_send_db()
{
    $item_id = trim($_POST['item_id']);
    $inv_id_from = trim($_POST['inv_id_from']);
    $suplier_id = trim($_POST['suplier_id']);
    $amount = trim($_POST['amount']);
    $unit = trim($_POST['unit_select']);
    //print $amount;
    $person_send = trim($_POST['authorized_person']);
    $date_send = trim($_POST['date']);
    $cost_per_unit=trim($_POST['cost_per_unit']);
    
    //$inv_from = $_POST['inv_from'];
    $inv_from = trim($_POST['inv_from']);
    $inv_to = trim($_POST['inv_to']);
    //print $item_id;
    $authorized_person=trim($_POST['authorized_person']);
    $requested_person=trim($_POST['requested_person']);
    $destribution=trim($_POST['destribution']);

    //print($item_id);
    $state=-1;
    
    global $global;
    $db=$global["db"];

    $sql = "SELECT catalog_id,amount,unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims = $db->Execute($sql);
    $catalog_id = $ims->fields["catalog_id"];
    $current_amount = $ims->fields["amount"];
    $current_unit = $ims->fields['unit'];

    
    $multiplier=unit_converter($unit,$current_unit);
    
    $current_amount_convert=$current_amount*$multiplier;
    
    
    //print $current_amount_convert;
    $remaining_amount=$current_amount_convert-$amount;
    
    $remaining_amount_new=$remaining_amount/$multiplier;
    
    
    

    $sql1 = "INSERT INTO ims_transfer_item (item_id,amount_send,unit,inv_id_to,person_send,date_send,destribution_method ,requested_person,received_item_id,amount_received,person_received,date_received) VALUES ('$item_id','$amount','$unit','$inv_to','$person_send','$date_send','$destribution','$requested_person','$state','$state','$state','$state');";  
    $ims1 = $db->Execute($sql1);
    $sql2="UPDATE ims_item_records SET amount='$remaining_amount_new',cost_per_unit='$cost_per_unit' WHERE item_id='$item_id';";
    $ims2 = $db->Execute($sql2);

?>
    <div id="result_msg">
       Item Sent
    </div>
    <br />    

<?php

    shn_ims_send_item_page($catalog_id);
    
    
    
    
    
}
/***********************************************************************************************************************************                  Receive Item                  ******************************************
***************************************************************************************************************
*/
/**
***Function to Receive item
**/
function _shn_ims_receive()
{
?>
<h1 align="center"><?php print _("Item Transit")?> </h1>
<div id="result">


    <table>
        <thead>
        <td><?=_("Item")?></td>
        <td><?=_("Amount Sent");?></td>
        <td><?=_("Unit");?></td>
        <td><?=_("Inventory From")?></td>
        <td><?=_("Inventory To")?></td>
            <td><?=_("Date Sent")?></td>
            <td><?=_("Authorized Person")?></td>
        <td><?=_("Transit Item")?></td>
            
        </thead>
    <tbody>
<?php
    $state=-1;
    global $global;
    $db=$global["db"];
    $sql1="SELECT transit_id,item_id,amount_send,unit,inv_id_to,person_send,date_send FROM ims_transfer_item WHERE received_item_id='$state';";
    $ims1 = $db->Execute($sql1);
    
    while (!$ims1==NULL && !$ims1->EOF)
    {    
        $transit_id=$ims1->fields['transit_id'];
        $item_id=$ims1->fields['item_id'];
        $amount_send=$ims1->fields['amount_send'];
        $unit_id=$ims1->fields['unit'];
        $unit_name=get_unit_name($unit_id);
        $inv_id_to=$ims1->fields['inv_id_to'];
        $person_send=$ims1->fields['person_send'];
        $date_send=$ims1->fields['date_send'];

        /*$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
        $ims2=$db->Execute($sql2);
        $inventory_from=$ims2->fields['inventory_name'];*/

        $sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_to';";
        $ims3=$db->Execute($sql3);
        $inventory_to=$ims3->fields['inventory_name'];

        $sql4="SELECT item_name,inv_id,suplier_id FROM ims_item_records WHERE item_id='$item_id';";
        $ims4=$db->Execute($sql4);
        $item_name=$ims4->fields['item_name'];
        $inv_id_from=$ims4->fields['inv_id'];
        $suplier_id=$ims4->fields['suplier_id'];

        $sql5="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
        $ims5=$db->Execute($sql5);
        $inventory_from=$ims5->fields['inventory_name'];
    
?>
        <tr>
        <td><?php print($item_name);?></td>
        <td><?php print($amount_send);?></td>
        <td><?php print($unit_name);?></td>
        <td><?php print($inventory_from);?></td>
        <td><?php print($inventory_to);?></td>
        <td><?php print($date_send);?></td>
        <td><?php print($person_send);?></td>
        <td><a href="index.php?mod=ims&act=receive_item_page&transit_id=<?php echo $transit_id;?>&suplier_id=<?php echo $suplier_id;?>"><?php print("Received");?></a></td>
        </tr>
<?php
        $ims1->MoveNext();
    }
?>
    </tbody>
    </table>
    </div>

<?php
    
}

function _shn_ims_receive_item_page($transit_id,$suplier_id)
{
?>
<h1 align="center"><?php print _("Item Transit ")?> </h1>
<div id="result">
<?php
    
    global $global;
    $db=$global["db"];
    $state=-1;
    $sql = "SELECT item_id,amount_send,unit,inv_id_to FROM ims_transfer_item WHERE transit_id='$transit_id';";
    //print $sql;
    $ims = $db->Execute($sql);
    
    $item_id=$ims->fields['item_id'];
    $amount=$ims->fields['amount_send'];
    $unit=$ims->fields['unit'];
    $unit_name=get_unit_name($unit);
    //$inv_id_from=$ims->fields['inv_id_from'];
    $inv_id_to=$ims->fields['inv_id_to'];
    

    $sql3="SELECT catalog_id,item_name,inv_id,cost_per_unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims3=$db->Execute($sql3);
    $parent_id=$ims3->fields['catalog_id'];
    $item_name=$ims3->fields['item_name'];
    $inv_id_from=$ims3->fields['inv_id'];
    $cost_per_unit=$ims3->fields['cost_per_unit'];

    $sql1="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
    $ims1=$db->Execute($sql1);
    $inventory_from=$ims1->fields['inventory_name'];

    $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_to';";
    $ims2=$db->Execute($sql2);
    $inventory_to=$ims2->fields['inventory_name'];

    
        
    shn_form_fopen('receive_item_db');
    shn_form_fsopen("Received Item");
    $extra_opts['value'] = $item_name;
    shn_form_text(_("Item Name : "),'item_name','size="50" readonly=true',$extra_opts);
    //$extra_opts['value'] = $received_amount;
    shn_form_text(_("Received Amount : "),'received_amount','size="50"',array('req'=>true,'value'=>$amount));

$unit_select_array=array();
    
    $cq="SELECT name FROM ct_unit WHERE unit_uuid='$unit';";
    $cms=$db->Execute($cq);
    //print $cq;
    $unit_select_array[$unit]=$cms->fields['name'];
    
    $query="select * from ct_cat_unit where ct_uuid='$parent_id'";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {

        $temp2=$res->fields['unit_uuid'];
        $query1="select name from ct_unit where unit_uuid ='$temp2'";
        $res2=$db->Execute($query1);
    
        $unit_select_array[$res->fields['unit_uuid']]=$res2->fields['name'];
        $res->MoveNext();
    }    

    shn_form_select($unit_select_array,_("Unit : "),'unit_received','size="1"',array('req'=>true));
    //shn_form_text(_("Unit : "),'unit','size="50" readonly=true',array('value'=>$unit_name));
    $extra_opts['value'] = $cost_per_unit;
    shn_form_text(_("Cost per Unit : "),'cost_per_unit','size="50"',$extra_opts);
    $extra_opts['value']=$inventory_from;
    shn_form_text(_("From : "),'inventory_from','size="50" readonly=true',$extra_opts);
    $extra_opts['value']=$inventory_to;
    shn_form_text(_("To : "),'inventory_to','size="50" readonly=true',$extra_opts);
    shn_form_text(_("Date Received : "),'received_date','size="50"',array('req'=>true,'help'=>_('Year-Month-Date. Only - seperater is accepted')));
    shn_form_text(_("Authorized Person : "),'authorized_person','size="50"',array('req'=>true,'help'=>_('Person who received Item')));

    shn_form_fsclose();

    shn_form_hidden(array('item_id'=>$item_id));
    shn_form_hidden(array('inv_id_from'=>$inv_id_from));
    shn_form_hidden(array('inv_id_to'=>$inv_id_to));
    shn_form_hidden(array('transit_id'=>$transit_id));
    shn_form_hidden(array('suplier_id'=>$suplier_id));

    shn_form_hidden(array('unit'=>$unit));
    shn_form_hidden(array('amount'=>$amount));

    shn_form_submit(_("Received"));
    shn_form_fclose();    
}

function _shn_ims_receive_item_db()
{
    $item_id=trim($_POST['item_id']);
    //$item_name=$_POST['item_name'];
    $received_amount=trim($_POST['received_amount']);
    $cost_per_unit=trim($_POST['cost_per_unit']);
    $inventory_from=trim($_POST['inventory_from']);
    $inventory_to=trim($_POST['inventory_to']);
    $received_date=trim($_POST['received_date']);
    $authorized_person=trim($_POST['authorized_person']);
    $unit=trim($_POST['unit_received']);

    

    $inv_id_from=trim($_POST['inv_id_from']);
    $inv_id_to=trim($_POST['inv_id_to']);
    $transit_id=trim($_POST['transit_id']);
    $suplier_id=trim($_POST['suplier_id']);

    //$convert_amount_send=$amount_send*unit_converter($unit,$unit_send);
    
    
    //if($convert_amount_send>$received_amount || $convert_amount_send==$received_amount)
    //{
    global $global;
    $db=$global["db"];
    
    

    $sql2="SELECT catalog_id,item_name,manufactured_date,expire_date,state FROM ims_item_records WHERE item_id='$item_id';";
    $ims2=$db->Execute($sql2);

    $catlog_id=$ims2->fields['catalog_id'];
    $item_name=$ims2->fields['item_name'];
    //$unit=$ims2->fields['unit'];
    $manufactured_date=$ims2->fields['manufactured_date'];
    $expire_date=$ims2->fields['expire_date'];
    $state=$ims2->fields['state'];

    //print $item_name;
    
    $sql3="INSERT INTO ims_item_records(catalog_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date,cost_per_unit,state) VALUES('$catlog_id','$inv_id_to','$suplier_id','$item_name','$received_amount','$unit','$manufactured_date','$expire_date','$cost_per_unit','$state');";
    //print $sql3;
    $ims3=$db->Execute($sql3);

    $sql4="SELECT item_id FROM ims_item_records WHERE transit_id='$transit_id';";
    $ims4=$db->Execute($sql4);
    $item_id_new=$ims4->fields['item_id'];

    $sql1="UPDATE ims_transfer_item SET received_item_id='$item_id_new',amount_received='$received_amount',person_received='$authorized_person',date_received='$received_date' WHERE transit_id='$transit_id';";
    $ims1=$db->Execute($sql1);

?>
    <div id="result_msg">
       Item Received
    </div>
    <br />    

<?php

    shn_ims_receive_item();
    
    //}
    

}

function _shn_ims_validate_send_item_page()
{
    global $global;
    $error_flag=false;
    clean_errors();

    $amount=trim($_POST['amount']);
    $item_id = trim($_POST['item_id']);
    $cost_per_unit=trim($_POST['cost_per_unit']);
    $date=trim($_POST['date']);
    $unit=trim($_POST['unit_select']);
    
    if($amount==null)
    {
        add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
        $error_flag=true;
    }
    if(!is_numeric($amount))
    {
        add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE);
        $error_flag=true;
    }
    if($unit==null)
    {
	add_error(SHN_ERR_IMS_UNIT_INCOMPLETE);
	$error_flag=true;
    }
    if($cost_per_unit!=null)
    {
        if(!is_numeric($cost_per_unit))
        {
            add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE_COST);
            $error_flag=true;
        }
    }

    if (!shn_valid_date($date))
    {
        $error_flag=true;
    
        }

    if($date==null)
    {
        add_error(SHN_ERR_IMS_DATE_INCOMPLETE);
        $error_flag=true;
    }

    if($date!=null)
    {
        if(_shn_ims_date_validate($date))
        {
            $error_flag=true;
        }
    }
    
    
    if(trim($_POST['authorized_person'])==null)
    {
        add_error(SHN_ERR_IMS_AUTHORIZED_PERSON_INCOMPLETE);
        $error_flag=true;
    }
    if(trim($_POST['requested_person'])==null)
    {
        add_error(SHN_ERR_IMS_REQUESTED_PERSON_INCOMPLETE);
        $error_flag=true;
    }
    if(trim($_POST['destribution'])==null)
    {
        add_error(SHN_ERR_IMS_DESTRIBUTION_METHOD_INCOMPLETE);
        $error_flag=true;
    }

    global $global;
    $db=$global["db"];

    $sql = "SELECT catalog_id,amount,unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims = $db->Execute($sql);
    $catalog_id = $ims->fields["catalog_id"];
    $current_amount = $ims->fields["amount"];
    $current_unit = $ims->fields['unit'];

    
    $multiplier=unit_converter($unit,$current_unit);
    
    $current_amount_convert=$current_amount*$multiplier;
    
    
    

    if($current_amount_convert<$amount)
    {
        add_error(SHN_ERR_IMS_INVALID_AMOUNT);
        $error_flag=true;
    }

    
    
    if($cost_per_unit<0)
    {
        add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
        $error_flag=true;
    }

    return $error_flag;
}

/*****************************************************************************************************************
*****         Validate Receive_item page                                             *****************************
*****************************************************************************************************************/

function _shn_ims_validate_receive_item_page()
{
    global $global;
    $error_flag=false;
    
    clean_errors();

    $unit_send=trim($_POST['unit']);
    $amount_send=trim($_POST['amount']);
    
    
    $received_amount=trim($_POST['received_amount']);
    $unit_received=trim($_POST['unit_received']);
    
    $cost_per_unit=trim($_POST['cost_per_unit']);
    $received_date=trim($_POST['received_date']);
    
    $convert_amount_send=$amount_send*unit_converter($unit_received,$unit_send);
    
    
    //if($convert_amount_send>$received_amount || $convert_amount_send==$received_amount)
    

    if($convert_amount_send<$received_amount)
    {
        add_error(SHN_ERR_IMS_INVALID_RECEIVED_AMOUNT);
        $error_flag=true;
    }

    if($received_amount==null)
    {
        add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
        $error_flag=true;
    }
    if(!is_numeric($received_amount))
    {
        add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE);
        $error_flag=true;
    }
    if($unit_received==null)
    {
	add_error(SHN_ERR_IMS_UNIT_INCOMPLETE);
	$error_flag=true;
    }
    if($received_date==null)
    {
        add_error(SHN_ERR_IMS_INVALID_DATE);
        $error_flag=true;
    }
    if (!shn_valid_date($received_date))
    {
        $error_flag=true;
    
        }

    if($received_date!=null)
    {
        if(_shn_ims_date_validate($received_date))
        {
            $error_flag=true;
        }
    }

    if(trim($_POST['authorized_person'])==null)
    {
        add_error(SHN_ERR_IMS_AUTHORIZED_PERSON_INCOMPLETE);
        $error_flag=true;
    }
    if($received_amount<0)
    {
        add_error(SHN_ERR_IMS_INVALID_RECEIVED_AMOUNT);
        $error_flag=true;
    }
    if($cost_per_unit<0)
    {
        add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
        $error_flag=true;
    }
    if($cost_per_unit!=null)
    {
        if(!is_numeric($cost_per_unit))
        {
            add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE_COST);
            $error_flag=true;
        }
    }
    
    return $error_flag;
}
?>
