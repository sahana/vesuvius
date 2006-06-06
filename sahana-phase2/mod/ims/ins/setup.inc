<?php
/**Default data for the Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

function shn_ims_datacreate()
{
	global $global;
	$db=$global["db"];

	$sql1="insert into ims_inventory_records(inv_uuid,parent_id,inventory_name,man_power,equipment,resources,space)values(1,0,'galle','300','','','500 square meters');";
	$ims1=$db->Execute($sql1);
	
	$sql2="insert into location_details(poc_uuid,location_id,address) values(1,'','NO 25, New street, Fort, Galle');";
	$ims2=$db->Execute($sql2);

	$sql3="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values(1,'curr','0912223456');";
	$ims3=$db->Execute($sql3);

	$sql4="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values(1,'pmob','0713555666');";
	$ims4=$db->Execute($sql4);

	$sql5="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values(1,'name','mahesh');";
	$ims5=$db->Execute($sql5);

	$sql6="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values(1,'fax','');";
	$ims6=$db->Execute($sql6);

	$sql7="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values(1,'email','maheshkalu@yahoo.com');";
	$ims7=$db->Execute($sql7);

	$sql8="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values(1,'web','www.abcdef.com');";
	$ims8=$db->Execute($sql8);

	$sql9="insert into org_location(org_id,location_id) values(1,'');";
	$ims9=$db->Execute($sql9);

}

?>