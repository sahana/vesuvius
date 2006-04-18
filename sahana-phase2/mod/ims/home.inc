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

//function shn_ims_home(){
function _shn_ims_default() {
?>
<h1 align="center"><?php print _("Inventory Mananagement System Home")?> </h1>
<div id="home_des">
	<ul>
		<li>The Inventory Management System is a system to manage Invetories</li>
		<br>
		<li>It keeps the track of items in the warehouses</li>
		<br>
		<li>It facilitates to get reports and statistics about the inventory</li>
		<br>
		<li>The Inventory Management System facilitates to manage multiple inventories </li>
		<br>

		
	</ul>
</div>
<h2 align="center"><?php print _("Most recently added ten items ")?></h2>
<div id="home_res">
</div>
<?php
	//shn_form_fopen(null);
	shn_form_fsopen();
?>	
	<table>
	<thead>
	    <td><?=_("Item ID")?></td>
	    <td><?=_("Item")?></td>
	    <td><?=_("Amount")?></td>
	    <td><?=_("Unit")?></td>
	    <td><?=_("Manufactured Date")?></td>
	    <td><?=_("Expire Date")?></td>
            <td><?=_("Suplier Name")?></td>
            <td><?=_("Suplier Address")?></td>
            <td><?=_("Suplier Contact Number")?></td>
            <td><?=_("Suplier e-mail")?></td>
	</thead>
	<tbody>
	<?php
		global $global;
		$db=$global["db"];
		//$item_search=$_POST['item_name_search'];
		//print ($item_search);
		
		$sql = "select item_id,item_name,amount,unit,manufactured_date,expire_date,suplier_name,suplier_address,suplier_telephone,suplier_email from ims_item_records order by item_id desc ;";
		$ims = $db->Execute($sql);

		while (!$ims==NULL && !$ims->EOF)
		{
			$item_id=$ims->fields["item_id"];
			$item_name=$ims->fields["item_name"];
			$amount=$ims->fields["amount"];
			$unit=$ims->fields["unit"];
			$manufactured_date=$ims->fields["manufactured_date"];
			$expire_date=$ims->fields["expire_date"];
			$suplier_name=$ims->fields["suplier_name"];
			$suplier_address=$ims->fields["suplier_address"];
			$suplier_telephone=$ims->fields["suplier_telephone"];
			$suplier_email=$ims->fields["suplier_email"];

?>
		<tr>
		<td><?php print ($item_id);?></td>
		<td><?php print ($item_name); ?></td>
		<td><?php print ($amount); ?></td>
		<td><?php print ($unit); ?></td>
		<td><?php print ($manufactured_date); ?></td>
		<td><?php print ($expire_date);?></td>
		<td><?php print ($suplier_name);?></td>
		<td><?php print ($suplier_address);?></td>
		<td><?php print ($suplier_telephone);?></td>
		<td><?php print ($suplier_email);?></td>
		</tr>

<?php

			$ims->MoveNext();
		}


	?>
	
	</tbody>
	</table>

<?php
	shn_form_fsclose();
	//shn_form_fclose();
}
?>






