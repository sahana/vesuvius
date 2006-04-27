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

/**
**function for view edit header 
**/
function _shn_ims_view_edit_header()
{
?>

<h1 align="center"><?php print _("View and Edit Items");?><br></h1>
<dev id="reports">

</dev>
<?php

}

/**
**GUI for View edit form
**/

function _shn_ims_view_edit()
{


global $global;
$module = $global['module'];

	shn_form_fsopen();
	
?>
	<div id ="report">
	<table>
        <thead>
	    <td><?=_("Item ID")?></td>
	    <td><?=_("Item")?></td>
	    <td><?=_("Amount");?></td>
	    <td><?=_("Unit");?></td>
	    <td><?=_("Manufactured Date")?></td>
            <td><?=_("Expire Date")?></td>
	    <td><?=_("Available Inventory/ies")?></td>
            <td><?=_("Suplier Name")?></td>
            
        </thead>
	<tbody>
<?php
		global $global;
		$db=$global["db"];
		//$item_search=$_POST['item_name_search'];
		//print ($item_search);
		
		$sql = "select item_id,catalog_id,inv_id,item_name,amount,unit,manufactured_date,expire_date from ims_item_records order by item_name ;";
		//$sql1 = "SELECT name FROM ct_catalogue WHERE (SELECT catalog_id FROM ims_item_records );";
		$ims = $db->Execute($sql);

		while (!$ims==NULL && !$ims->EOF)
		{
			$item_id=$ims->fields["item_id"];
			$catalog_id=$ims->fields["catalog_id"];
			$inv_id=$ims->fields["inv_id"];
			//$category=$ims->fields["category"];
			$item_name=$ims->fields["item_name"];
			$amount=$ims->fields["amount"];
			$unit=$ims->fields["unit"];
			$manufactured_date=$ims->fields["manufactured_date"];
			$expire_date=$ims->fields["expire_date"];
			

		$sql1="SELECT name FROM ct_catalogue WHERE ct_uuid='$catalog_id';";
		$ims1 = $db->Execute($sql1);
			$category=$ims1->fields["name"];

		$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims2= $db->Execute($sql2);
		$inventory_name = $ims2->fields["inventory_name"];
			//$parent_id=$ims1->fields["parentid"];

	
			
?>
		<tr>
		<td><?php print ($item_id); ?></td>
		<td><a href="index.php?mod=ims&act=add_item1&item_id=<?php echo $item_id;?>"><?php print ($item_name);?></a></td>
		<td><?php print ($amount); ?></td>
		<td><?php print ($unit); ?></td>
		<td><?php print ($manufactured_date); ?></td>
		<td><?php print ($expire_date);?></td>
		<td><?php print ($inventory_name);?></td>
		
		</tr>

	
<?php
	
	$ims->MoveNext();
	}
?>
	</tbody>
	</table>
	</div>
<?php
	shn_form_fclose();
}
?>