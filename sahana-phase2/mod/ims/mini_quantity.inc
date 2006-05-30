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
* @copyright	Lanka Software Foundation - http://www.opensource.lk
* @package		Sahana
* @subpackage	
* @tutorial		
* @license	  	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function _shn_ims_mini_quantity_item_select()
{
?>

<h1 align="center"><?php print _("Item Selection");?><br></h1>
<dev id="report">

</dev>

<?php
	$form_opts['name']='subcat';
	shn_form_fopen("minimum_quantity",null,$form_opts);
	$depth=get_max_depth();
	shn_sub_cat($depth,'subcat');
	//shn_sub_cat(6,'subcat');
	shn_form_fclose();
	
}

function _shn_ims_mini_quantity($catalog_id, $inv_id)
{
	if($catalog_id!=null && $inv_id!=null)
	{
		global $global;
		$db=$global["db"];
		$query="SELECT minimum_quantity,unit FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
		$ims=$db->Execute($query);
		
		$minimum_quantity=$ims->fields['minimum_quantity'];
		$unit=$ims->fields['unit'];
		$unit_name=get_unit_name($unit);

		$query1="SELECT item_name FROM ims_item_records WHERE catalog_id='$catalog_id';";
		$ims_q1=$db->Execute($query1);
		$item_name=$ims_q1->fields['item_name'];

		$parent_id=$catalog_id;
		$flag=true;
		//$next_action="";
	}

	else
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
		$minimum_quantity="";
		$unit="";
		$flag=false;

		//$next_action="mini_quantity_db";
	}
	

	shn_form_fopen("mini_quantity_db");

	shn_form_fsopen("Item Name");
	shn_form_text(_("Item Name : "),'item_name','size="50" readonly=true',array('value'=>$item_name));
	shn_form_fsclose();

	shn_form_fsopen("Inventory Selection");
	
	global $global;
	$db=$global["db"];

	if($flag==true)
	{
		//$inv_id_edit=$inv_id;
		$q1="SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$imsq1=$db->Execute($q1);
		$inventory_array=array();
		$inventory_array[$imsq1->fields['inv_uuid']]=$imsq1->fields['inventory_name'];
		shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',null);
	}

	if($flag==false)
	{
	$sql1="SELECT catalog_id,inv_id FROM ims_item_records WHERE catalog_id='$parent_id';";
	$ims1=$db->Execute($sql1);

	
	
	$inventory_array=array();
		
	while($ims1!=NULL && !$ims1->EOF)
	{
		$inv_id=$ims1->fields['inv_id'];
		$catalog_id=$ims1->fields['catalog_id'];
		//$item_id=$ims1->fields['item_id'];

		$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims2=$db->Execute($sql2);
		$inventory_array[$inv_id]=$ims2->fields['inventory_name'];//}
		$ims1->MoveNext();
		
	}	
	
	shn_form_select($inventory_array,_("Inventory : "),'inventory_id','size="1"',array('req'=>true));
	}

	shn_form_fsclose();

	shn_form_fsopen("Item Quantity ");
	shn_form_text(_("Re-Order Level : "),'mini_quantity','size="50"',array('req'=>true,'value'=>$minimum_quantity));
	
	$unit_array=array();
	$unit_array=_shn_cs_get_units($parent_id);
	shn_form_select($unit_array,_("Unit : "),'unit_select','size="1"',array('help'=>_('Select the Measurement unit for entered amount. If this box is empty go back to the catalogue system and add a measurement unit')));
	shn_form_fsclose();
	//shn_form_hidden(array('item_id'=>$item_id));
	
	shn_form_hidden(array('catalog_id'=>$catalog_id));
	shn_form_hidden(array('flag'=>$flag));
	shn_form_hidden(array('parent_id'=>$parent_id));
	shn_form_hidden(array('inv_id'=>$inv_id));
	shn_form_submit("Submit");
	
	shn_form_fclose();
}

function _shn_ims_mini_quantity_db()
{
	global $global;
	$db=$global["db"];

	//$item_id=$_POST['item_id'];
	$flag=trim($_POST['flag']);
	$catalog_id=trim($_POST['catalog_id']);
	$inv_id=trim($_POST['inv_id']);
	$mini_quantity=trim($_POST['mini_quantity']);
	$unit=trim($_POST['unit_select']);

	$inventory_id=trim($_POST['inventory_id']);

	print $catalog_id;
	print $inv_id;
	print $mini_quantity;
	print $unit;
	print ("\n");
	print ($inventory_id);

	if($flag==false)
	{

	$sql="INSERT INTO ims_reorder_level (catalog_id,inv_id,minimum_quantity,unit) VALUES ('$catalog_id','$inventory_id','$mini_quantity','$unit');";
	$ims=$db->Execute($sql);
	
	shn_ims_minimum_quantity_item();
	}
	if($flag==true)
	{
	$sql="UPDATE ims_reorder_level SET minimum_quantity='{$mini_quantity}',unit='{$unit}' WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims=$db->Execute($sql);
	//print $sql;
	shn_ims_reorder_level_edit();
	}

		
	//shn_ims_minimum_quantity_item();


	
}

function _shn_ims_view_edit_reorder()
{
?>

<h1 align="center"><?php print _("Item Selection");?><br></h1>
<dev id="result">

</dev>

<?php
	$form_opts['name']='subcat';
	shn_form_fopen("view_edit_reorder_page",null,$form_opts);
	shn_sub_cat(6,'subcat');
	shn_form_fclose();
	

}

function _shn_ims_view_edit_reorder_page()
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
?>
<h1 align="center"><?php print _("Re-Order Level");?><br></h1>
<div id="result">
<?php
	
	
	shn_form_fsopen();
	
?>
	
	<table>
        <thead>
	    <td><?=_("Item");?></td>
	    <td><?=_("Amount");?></td>
	    <td><?=_("Unit");?></td>
	    <td><?=_("Inventory")?></td>
	    <td><?=_("Edit")?></td>
	    <td><?=_("Delete")?></td>
            
            
        </thead>
	<tbody>
<?php
		global $global;
		$db=$global["db"];
		//$state_des="destroyed";
		//$item_search=$_POST['item_name_search'];
		//print ($item_search);
		
		$sql1 = "SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level;";  
		$ims1 = $db->Execute($sql1);

		while (!$ims1==NULL && !$ims1->EOF)
		{
			$catalog_id=$ims1->fields["catalog_id"];
			$inv_id=$ims1->fields["inv_id"];
			$minimum_quantity=$ims1->fields['minimum_quantity'];
			$unit=$ims1->fields["unit"];
			$unit_name=get_unit_name($unit);
			
		$sql2="SELECT item_id,item_name FROM ims_item_records WHERE catalog_id='$catalog_id' ORDER BY(item_name);";	
		$ims2=$db->Execute($sql2);
		$item_id=$ims2->fields['item_id'];
		$item_name=$ims2->fields['item_name'];

		$sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims3= $db->Execute($sql3);
		$inventory_name = $ims3->fields["inventory_name"];
		
	
			
?>
		<tr>
		<td><?php print ($item_name); ?></td>
		<td><?php print ($minimum_quantity); ?></td>
		<td><?php print ($unit_name); ?></td>
		<td><?php print ($inventory_name);?></td>
		<td><a href="index.php?mod=ims&act=reorder_level_edit&inv_id=<?php echo $inv_id;?>&catalog_id=<?php echo $catalog_id;?>"><?php print ("Edit");?></a></td>
		<td><a href="index.php?mod=ims&act=reorder_level_delete&inv_id=<?php echo $inv_id;?>&catalog_id=<?php echo $catalog_id;?>"><?php print ("Delete");?></a></td>
		
		
		
		</tr>

	
<?php
	
	$ims1->MoveNext();
	}
?>
	</tbody>
	</table>
	</div>
<?php
	shn_form_fclose();
}

function _shn_ims_validate_minimum_quantity()
{
	$error_flag=false;
	clean_errors();
	$minimum_quantity=trim($_POST['mini_quantity']);

	if(trim($_POST['inv_id'])==null)
	{
	add_error(SHN_ERR_IMS_INVENTORY_INCOMPLETE);
	$error_flag=true;
	}
	if($minimum_quantity==null)
	{
	add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
	$error_flag=true;
	}
	if($minimum_quantity<0)
	{
	add_error(SHN_ERR_IMS_AMOUNT_NEGATIVE);
	$error_flag=true;
	}
	if(!is_numeric($minimum_quantity))
	{
	add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
	$error_flag=true;
	}
	return $error_flag;
}

?>