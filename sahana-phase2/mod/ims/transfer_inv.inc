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

function _shn_ims_send()
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
	//print ("test");	
	echo $parent_id;
	
?>
<h1 align="center"><?php print _("Send Item to an Inventory")?> </h1>
<div id="report">
<?php
	shn_form_fopen("send_item_db");
	$extra_opts['req']=true;
	shn_form_fsopen("Item Transfer");
	
	shn_form_text(_("Item Send : "),'item_name','size="50"',$extra_opts);
	shn_form_text(_("Amount Send: "),'amount','size="50"',$extra_opts);

	global $global;
	$db=$global["db"];
	$inventory_array=array();
	//$inventory_array['0']="None";
	$q="SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
	$ims=$db->Execute($q);
	//$j=0;
	while($ims!=NULL && !$ims->EOF)
	{
		
		$inventory_array[$ims->fields['inv_uuid']]=$ims->fields['inventory_name'];//}
		$ims->MoveNext();
		//$j=$j+1;
		//print ($j);
	}	
	
	shn_form_select($inventory_array,_("From the Inventory : "),'inv_from','size="1"',$extra_opts);
	shn_form_select($inventory_array,_("To the Inventory : "),'inv_to','size="1"',$extra_opts);

	shn_form_text(_("Date"),'date','size="50"',$extra_opts);
	shn_form_text(_("Cost Per Event"),'cost_per_event','size="50"',null);

	shn_form_fsclose();

	shn_form_fsopen("Contacts");
	shn_form_text(_("Authorized by : "),'authorized_person','size="50"',null);
	shn_form_text(_("Requested by : "),'requested_person','size="50"',null);
	shn_form_text(_("Destribution Method : "),'destribution','size="50"',null);
	shn_form_textarea(_("Cause"),'cause','size="40"',null);
	//shn_form_text(_("Cause : "),'cause','size="50"',null);
	shn_form_hidden(array('parent_id'=>$parent_id));
	shn_form_fsclose();
	shn_form_submit("Send");
	shn_form_fclose();
}
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
	    <td><?=_("Date")?></td>
            <td><?=_("Authorized Person")?></td>
            
        </thead>
	<tbody>
<?php
	$state="send";
	global $global;
	$db=$global["db"];
	$sql1="SELECT item_id,item_name,amount_send,item_send_from,item_send_to FROM ims_item_records WHERE transit_state='$state';";
	$ims1 = $db->Execute($sql1);
	
	while (!$ims1==NULL && !$ims1->EOF)
	{	
		$item_id=$ims1->fields['item_id'];
		$item_name=$ims1->fields['item_name'];
		$amount_send=$ims1->fields['amount_send'];
		$item_send_from=$ims1->fields['item_send_from'];
		$item_send_to=$ims1->fields['item_send_to'];

		$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$item_send_from';";
		$ims2=$db->Execute($sql2);
		$inventory_from=$ims2->fields['inventory_name'];

		$sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$item_send_to';";
		$ims3=$db->Execute($sql3);
		$inventory_to=$ims3->fields['inventory_name'];
	
?>
		<tr>
		<td><a href="index.php?mod=ims&act=receive_item_page&item_id=<?php echo $item_id;?>"<?php print($item_name);?>></a></td>
		<td><?php print($amount_send);?></td>
		<td><?php print("");?></td>
		<td><?php print($inventory_from);?></td>
		<td><?php print($inventory_to);?></td>
		</tr>
<?php
		$ims1->MoveNext();
	}
?>
	</tbody>
	</table>

<?php
	/**$transit_state="send";
	global $global;
	$db=$global["db"];
	$sent_item_array=array();

	$sql1="SELECT item_id,item_name FROM ims_item_records WHERE transit_state='$transit_state';";
	$ims1=$db->Execute($sql1);

	while($ims1!=NULL && !$ims1->EOF)
	{
		$sent_item_array[$ims1->fields['item_id']]=$ims1->fields['item_name'];
		$ims1->MoveNext();
	}
	shn_form_select($sent_item_array,_("Item Name : "),'item_received','size="1"',$extra_opts);
	
	//shn_form_text(_("Item Received : "),'item_received','size="50"',$extra_opts);
	shn_form_text(_("Amount Received : "),'amount_received','size="50"',$extra_opts);
	
	$inventory_array=array();
	//$inventory_array['0']="None";
	$sql="SELECT item_send_to,item_send_from FROM ims_item_records ";
	$ims2=$db->Execute($sql);
	$item_send_to=$ims2->fields['item_send_to'];
	$item_send_from=$ims2->fields['item_send_from'];

	$q="SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid='$item_send_from';";
	$ims=$db->Execute($q);
	//$j=0;
	while($ims!=NULL && !$ims->EOF)
	{
		
		$inventory_array[$ims->fields['inv_uuid']]=$ims->fields['inventory_name'];//}
		$ims->MoveNext();
		//$j=$j+1;
		//print ($j);
	}	
	
	shn_form_select($inventory_array,_("Received From the Inventory : "),'inv_id_from','size="1"',$extra_opts);

	$sql3="SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid='$item_send_to';";
	$received_inventory_array=array();
	$ims3=$db->Execute($sql3);
	while($ims3!=NULL && !$ims3->EOF)
	{
		$received_inventory_array[$ims3->fields['inv_uuid']]=$ims3->fields['inventory_name'];
		$ims3->MoveNext();
	}
	shn_form_select($received_inventory_array,_("Received To the Inventory : "),'inv_id_to','size="1"',$extra_opts);
	shn_form_text(_("Date Received : "),'date_received','size="50"',$extra_opts);*/
	/*global $global;
	$db=$global['db']; 
	$sql-"SELECT item_name FROM ims_item_records";
	$ims=$db->Execute($sql);
	while(!$ims==NULL && !$ims->EOF)
	{
		$name=$ims->fields["item_name"];
		list($user, $pass, $uid, $gid, $extra) =  split("->", $name);
	}
	for ($i=0;$i<10;$i++)
	{
		shn_form_text("Hello",'hello','size="50"',null);
	}*/
	/**shn_form_fsclose();
	shn_form_submit("Received");
	shn_form_fclose();*/
}

function _shn_ims_send_db()
{
	$parent_id = $_POST['parent_id'];
	$item_name = $_POST['item_name'];
	$amount = $_POST['amount'];
	$inv_from = $_POST['inv_from'];
	$inv_to = $_POST['inv_to'];

	$send="send";
	
	global $global;
	$db=$global["db"];

	$sql = "SELECT amount FROM ims_item_records WHERE catalog_id='$parent_id';";
	$ims = $db->Execute($sql);
	$current_amount = $ims->fields["amount"];
	$remaining_amount=$current_amount-$amount;	

	$sql1 = "UPDATE ims_item_records SET amount='{$remaining_amount}',item_send_to='{$inv_to}',item_send_from='{$inv_from}',amount_send='{$amount}',transit_state='{$send}' WHERE catalog_id='$parent_id';";
	$ims1 = $db->Execute($sql1);
	
	
	
	print($remaining_amount);
	//print($sql);
	//print($inv_from);
	//print($inv_to);
	
	
}

function _shn_ims_receive_item_page($temp)
{
?>
<h1 align="center"><?php print _("Receive Item ")?> </h1>
<div id="report">
<?php
	global $global;
	$db=$global["db"];
	$sql = "SELECT item_name,amount_send,item_send_from,item_send_to FROM ims_item_records WHERE item_id='$temp';";
	$ims = $db->Execute($sql);
	//$inv_id=$ims->fields['inv_id'];
	$item_received=$ims->fields['item_name'];
	$received_amount=$ims->fields['amount_send'];
	$inventory_from=$ims->fields['item_send_from'];
	$inventory_to=$ims->fields['item_send_to'];

	$sql1="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inventory_from';";
	$ims1=$db->Execute($sql1);
	$inventory_from=$ims1->fields['inventory_name'];

	$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inventory_to';";
	$ims2=$db->Execute($sql2);
	$inventory_to=$ims2->fields['inventory_name'];
		
	shn_form_fopen(null);
	shn_form_fsopen("Received Item");
	$extra_opts['value'] = $item_received;
	shn_form_text(_("Item Name : "),'item_received','size="50"',$extra_opts);
	$extra_opts['value'] = $received_amount;
	shn_form_text(_("Received Amount : "),'received_amount','size="50"',$extra_opts);
	$extra_opts['value']=$inventory_from;
	shn_form_text(_("From : "),'inventory_from','size="50"',$extra_opts);
	$extra_opts['value']=$inventory_to;
	shn_form_text(_("To : "),'inventory_to','size="50"',$extra_opts);
	shn_form_text(_("Date Received : "),'received_date','size="50"',null);
	shn_form_text(_("Authorized Person : "),'authorized_person','size="50"',null);
	shn_form_fsclose();
	shn_form_submit(_("Received"));
	shn_form_fclose();	
}
?>