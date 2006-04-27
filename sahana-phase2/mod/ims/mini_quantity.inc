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


function _shn_ims_mini_quantity()
{
	shn_form_fopen(null);
	shn_form_fsopen("Inventory Selection");
	
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
	
	shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',$extra_opts);

	shn_form_fsclose();

	shn_form_fsopen("Item Quantity ");
	shn_form_text(_("Minimum Quantity : "),'mini_quantity','size="50"',null);
	shn_form_fsclose();
	shn_form_submit("Submit");
	shn_form_fclose();
}

?>