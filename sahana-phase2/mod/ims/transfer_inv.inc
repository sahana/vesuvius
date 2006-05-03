<?php
/**
* Sahana Inventory Management System main page
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright		Lanka Software Foundation - http://www.opensource.lk
* @package		Sahana
* @subpackage		ims
* @tutorial		
* @license	  	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
include_once $global['approot'].'/mod/cs/lib_cs.inc';

function _shn_ims_send_main()
{
?>
<h1 align="center"><?php print _("Send Item to an Inventory"); ?> </h1>
<h1 align="center"><?php print _("Please select the Item to be sent"); ?></h1>
<div id="report">
<?php
	$form_opts['name']='subcat';
	shn_form_fopen("send_item_page",null,$form_opts);
	shn_sub_cat(6,'subcat');


	shn_form_fclose();
}

/**
**Function For Send Item table view page
**/
function _shn_ims_send_item_table_view_($catalog_id)
{
	//print $catalog_id;
	if($catalog_id==NULL)
	{
	$parent_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
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
<h1 align="center"><?php print _("Send Item to an Inventory") ?></h1>
<div id="report">
	<table>
	<thead>
	    	<td><?=_("Item ID")?></td>
	    	<td><?=_("Item")?></td>
	    	<td><?=_("Amount");?></td>
	    	<td><?=_("Unit");?></td>
	    	<td><?=_("Manufactured Date")?></td>
            	<td><?=_("Expire Date")?></td>
	    	<td><?=_("Available Inventory")?></td>
            	<td><?=_("state")?></td>
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
			
			
		
		$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid=$inv_id;";
		$ims2= $db->Execute($sql2);
		//print $sql2;
		$inventory_name = $ims2->fields["inventory_name"];			

?>
		<tr>
		<td><?php print ($item_id); ?></td>
		<td><a href="index.php?mod=ims&act=send_item_data_collectpage&item_id=<?php echo $item_id;?>"><?php print ($item_name);?></a></td>
		<td><?php print ($amount); ?></td>
		<td><?php print ($unit); ?></td>
		<td><?php print ($manufactured_date); ?></td>
		<td><?php print ($expire_date);?></td>
		<td><?php print ($inventory_name);?></td>
		<td><?php print ($state); ?></td>		
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

function _shn_ims_send($item_id)
{
	
	global $global;
	$db=$global["db"];
	$sql1="SELECT item_name,inv_id,cost_per_unit FROM ims_item_records WHERE item_id='$item_id';";
	$ims1=$db->Execute($sql1);
	$item_name=$ims1->fields['item_name'];
	$inv_id_from=$ims1->fields['inv_id'];
	$cost_per_unit=$ims1->fields['cost_per_unit'];

	$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
	$ims2=$db->Execute($sql2);
	$inv_from=$ims2->fields['inventory_name'];
	
?>
<h1 align="center"><?php print _("Send Item to an Inventory")?> </h1>
<div id="report">
<?php
	shn_form_fopen("send_item_db");
	//$extra_opts['req']=true;
	shn_form_fsopen("Item Transfer");
	
	$extra_opts['value']=$item_name;
	shn_form_text(_("Item Send : "),'item_name','size="50"',$extra_opts);
	//$extra_opts['req']=true;
	shn_form_text(_("Amount Send: "),'amount','size="50"',null);
	
	$extra_opts['value']=$inv_from;
	shn_form_text(_("From the Inventory : "),'inv_from','size="50"',$extra_opts);

	$inventory_array=array();
	$sql3="SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid!='$inv_id_from';";
	$ims3=$db->Execute($sql3);
	while($ims3!=NULL && !$ims3->EOF)
	{
		$inventory_array[$ims3->fields['inv_uuid']]=$ims3->fields['inventory_name'];
		$ims3->MoveNext();
	}
	shn_form_select($inventory_array,_("To the Inventory : "),'inv_to','size="1"',$extra_opts);

	shn_form_text(_("Date"),'date','size="50"',null);
	$extra_opts['value']=$cost_per_unit;
	shn_form_text(_("Cost Per Unit : "),'cost_per_unit','size="50"',$extra_opts);

	shn_form_fsclose();

	shn_form_fsopen("Contacts");
	shn_form_text(_("Authorized by : "),'authorized_person','size="50"',null);
	shn_form_text(_("Requested by : "),'requested_person','size="50"',null);
	shn_form_text(_("Destribution Method : "),'destribution','size="50"',null);
	shn_form_textarea(_("Cause"),'cause','size="40"',null);
	
	shn_form_hidden(array('item_id'=>$item_id));
	shn_form_hidden(array('inv_id_from'=>$inv_id_from));
	shn_form_fsclose();
	shn_form_submit("Send");
	shn_form_fclose();
}


function _shn_ims_send_db()
{
	$item_id = $_POST['item_id'];
	$inv_id_from = $_POST['inv_id_from'];
	$amount = $_POST['amount'];
	//print $amount;
	$person_send = $_POST['authorized_person'];
	$date_send = $_POST['date'];
	$cost_per_unit=$_POST['cost_per_unit'];
	
	//$inv_from = $_POST['inv_from'];
	$inv_from = $_POST['inv_from'];
	$inv_to = $_POST['inv_to'];
	//print $item_id;

	//print($item_id);
	$state=-1;
	
	global $global;
	$db=$global["db"];

	$sql = "SELECT catalog_id,amount FROM ims_item_records WHERE item_id='$item_id';";
	$ims = $db->Execute($sql);
	$catalog_id = $ims->fields["catalog_id"];
	$current_amount = $ims->fields["amount"];
	$remaining_amount=$current_amount-$amount;
		

	$sql1 = "INSERT INTO ims_transfer_item (item_id,amount_send,inv_id_to,person_send,date_send,received_item_id,amount_received,person_received,date_received) VALUES ('$item_id','$amount','$inv_to','$person_send','$date_send','$state','$state','$state','$state');";  
	$ims1 = $db->Execute($sql1);

	$sql2="UPDATE ims_item_records SET amount='$remaining_amount',cost_per_unit='$cost_per_unit' WHERE item_id='$item_id';";
	$ims2 = $db->Execute($sql2);

	shn_ims_send_item_page($catalog_id);
	
	
	//print($remaining_amount);
	//print($sql);
	//print($inv_from);
	//print($inv_to);
	
	
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
<h1 align="center"><?php print _("Receive Item from an Inventory")?> </h1>
<div id="report">
</div>

	<table>
        <thead>
	    <td><?=_("Item")?></td>
	    <td><?=_("Amount Sent");?></td>
	    <td><?=_("Unit");?></td>
	    <td><?=_("Inventory From")?></td>
	    <td><?=_("Inventory To")?></td>
            <td><?=_("Date Sent")?></td>
            <td><?=_("Authorized Person")?></td>
            
        </thead>
	<tbody>
<?php
	$state=-1;
	global $global;
	$db=$global["db"];
	$sql1="SELECT transit_id,item_id,amount_send,inv_id_to,person_send,date_send FROM ims_transfer_item WHERE received_item_id='$state';";
	$ims1 = $db->Execute($sql1);
	
	while (!$ims1==NULL && !$ims1->EOF)
	{	
		$transit_id=$ims1->fields['transit_id'];
		$item_id=$ims1->fields['item_id'];
		$amount_send=$ims1->fields['amount_send'];
		$inv_id_to=$ims1->fields['inv_id_to'];
		$person_send=$ims1->fields['person_send'];
		$date_send=$ims1->fields['date_send'];

		/*$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
		$ims2=$db->Execute($sql2);
		$inventory_from=$ims2->fields['inventory_name'];*/

		$sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_to';";
		$ims3=$db->Execute($sql3);
		$inventory_to=$ims3->fields['inventory_name'];

		$sql4="SELECT item_name,inv_id FROM ims_item_records WHERE item_id='$item_id';";
		$ims4=$db->Execute($sql4);
		$item_name=$ims4->fields['item_name'];
		$inv_id_from=$ims4->fields['inv_id'];

		$sql5="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
		$ims5=$db->Execute($sql5);
		$inventory_from=$ims5->fields['inventory_name'];
	
?>
		<tr>
		<td><a href="index.php?mod=ims&act=receive_item_page&transit_id=<?php echo $transit_id;?>"<?php print($item_name);?>></a></td>
		<td><?php print($amount_send);?></td>
		<td><?php print("");?></td>
		<td><?php print($inventory_from);?></td>
		<td><?php print($inventory_to);?></td>
		<td><?php print($date_send);?></td>
		<td><?php print($person_send);?></td>
		</tr>
<?php
		$ims1->MoveNext();
	}
?>
	</tbody>
	</table>

<?php
	
}

function _shn_ims_receive_item_page($transit_id)
{
?>
<h1 align="center"><?php print _("Receive Item ")?> </h1>
<div id="report">
<?php
	
	global $global;
	$db=$global["db"];
	$state=-1;
	$sql = "SELECT item_id,amount_send,inv_id_to FROM ims_transfer_item WHERE transit_id='$transit_id';";
	//print $sql;
	$ims = $db->Execute($sql);
	
	$item_id=$ims->fields['item_id'];
	$received_amount=$ims->fields['amount_send'];
	//$inv_id_from=$ims->fields['inv_id_from'];
	$inv_id_to=$ims->fields['inv_id_to'];
	

	$sql3="SELECT item_name,inv_id,cost_per_unit FROM ims_item_records WHERE item_id='$item_id';";
	$ims3=$db->Execute($sql3);
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
	shn_form_text(_("Item Name : "),'item_name','size="50"',$extra_opts);
	$extra_opts['value'] = $received_amount;
	shn_form_text(_("Received Amount : "),'received_amount','size="50"',$extra_opts);
	$extra_opts['value'] = $cost_per_unit;
	shn_form_text(_("Cost per Unit : "),'cost_per_unit','size="50"',$extra_opts);
	$extra_opts['value']=$inventory_from;
	shn_form_text(_("From : "),'inventory_from','size="50"',$extra_opts);
	$extra_opts['value']=$inventory_to;
	shn_form_text(_("To : "),'inventory_to','size="50"',$extra_opts);
	shn_form_text(_("Date Received : "),'received_date','size="50"',null);
	shn_form_text(_("Authorized Person : "),'authorized_person','size="50"',null);
	shn_form_fsclose();

	shn_form_hidden(array('item_id'=>$item_id));
	shn_form_hidden(array('inv_id_from'=>$inv_id_from));
	shn_form_hidden(array('inv_id_to'=>$inv_id_to));
	shn_form_hidden(array('transit_id'=>$transit_id));

	shn_form_submit(_("Received"));
	shn_form_fclose();	
}

function _shn_ims_receive_item_db()
{
	$item_id=$_POST['item_id'];
	//$item_name=$_POST['item_name'];
	$received_amount=$_POST['received_amount'];
	$cost_per_unit=$_POST['cost_per_unit'];
	$inventory_from=$_POST['inventory_from'];
	$inventory_to=$_POST['inventory_to'];
	$received_date=$_POST['received_date'];
	$authorized_person=$_POST['authorized_person'];

	$inv_id_from=$_POST['inv_id_from'];
	$inv_id_to=$_POST['inv_id_to'];
	$transit_id=$_POST['transit_id'];

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
	

//------------------------unit has to be added ----------------------------------------------------------------
	
	$sql3="INSERT INTO ims_item_records(catalog_id,inv_id,item_name,amount,manufactured_date,expire_date,cost_per_unit,state) VALUES('$catlog_id','$inv_id_to','$item_name','$received_amount','$manufactured_date','$expire_date','$cost_per_unit','$state');";
	//print $sql3;
	$ims3=$db->Execute($sql3);

	$sql4="SELECT item_id FROM ims_item_records WHERE transit_id='$transit_id';";
	$ims4=$db->Execute($sql4);
	$item_id_new=$ims4->fields['item_id'];

	$sql1="UPDATE ims_transfer_item SET received_item_id='$item_id_new',amount_received='$received_amount',person_received='$authorized_person',date_received='$received_date' WHERE transit_id='$transit_id';";
	$ims1=$db->Execute($sql1);

	shn_ims_receive_item();
	
}
?>