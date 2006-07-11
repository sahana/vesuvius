<?php
/**Setup - Create Default data 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sanjeewa Jayasinghe <sditfac@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage cs
*/

function shn_cs_datacreate()
{
	global $global;
	$db=$global["db"];

	// INSERT UNIT TYPES AND UNITS UNDER THEM
	//data1
	$unit_type_id1 = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$unit_type_id1','Mass','Mass')";
	$res=$db->Execute($q);

	$unit_id1=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id1','$unit_id1','Kg','1',0)";
	$res=$db->Execute($query);

	$unit_id2=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id1','$unit_id2','g','0',0.001)";
	$res=$db->Execute($query);

	$unit_id3=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id1','$unit_id3','mg','0',0.000001)";
	$res=$db->Execute($query);

	//data2
	$unit_type_id2 = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$unit_type_id2','Length','Length')";
	$res=$db->Execute($q);

	$unit_id4=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id2','$unit_id4','m','1',0)";
	$res=$db->Execute($query);

	$unit_id5=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id2','$unit_id5','km','0',1000)";
	$res=$db->Execute($query);

	$unit_id6=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id2','$unit_id6','cm','0',0.001)";
	$res=$db->Execute($query);


	//data3
	$unit_type_id3 = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$unit_type_id3','Volume','Volume')";
	$res=$db->Execute($q);

	$unit_id7=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id3','$unit_id7','l','1',0)";
	$res=$db->Execute($query);

	$unit_id8=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id3','$unit_id8','ml','0',0.001)";
	$res=$db->Execute($query);

	$unit_id9=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id3','$unit_id9','kl','0',1000)";
	$res=$db->Execute($query);

	//data4
	$unit_type_id4 = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$unit_type_id4','Miscellaneous','Miscellaneous')";
	$res=$db->Execute($q);

	$unit_id10=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id4','$unit_id10','Truck','1',0)";
	$res=$db->Execute($query);

	$unit_id11=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id4','$unit_id11','Box','0',0)";
	$res=$db->Execute($query);

	$unit_id12=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$unit_type_id4','$unit_id12','Bottle','0',0)";
	$res=$db->Execute($query);

	// INSERT MAIN CATALOGUES & SUB CATALOGUE TO THE DATABASE
	//data 1
		// -main catalogue
	$id1 = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$id1','Food','Food','food')";
	$res=$db->Execute($q);
				// -sub catalogue
			$parent_id1 = $id1;
			$id2 = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$parent_id1','$id2','Dry Food','Dry Food','food')";
			$res=$db->Execute($q);
						// -item1
					$parent_id2 = $id2;
					$id3 = shn_create_uuid("catalogue");
					$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$parent_id2','$id3','Rice','Rice','1','food')";
					$res=$db->Execute($q);
								// -unit/units that item use -(kg)
							$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id3','$unit_id1')";
							$res=$db->Execute($q);
		
						// -item2
					$parent_id3 = $id2;
					$id4 = shn_create_uuid("catalogue");
					$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$parent_id3','$id4','Sugar','Sugar','1','food')";
					$res=$db->Execute($q);
								// -unit/units that item use -(kg)
							$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id4','$unit_id1')";
							$res=$db->Execute($q);
								// -unit/units that item use -(kg)
							$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id4','$unit_id3')";
							$res=$db->Execute($q);


	//data 2
		// - main catalogue
	$id5 = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$id5','Medicine','Medicine','medicine')";
	$res=$db->Execute($q);
			// -sub catalogue level1
		$parent_id4 = $id5;
		$id6 = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$parent_id4','$id6','Paracetamol','Paracetamol','medicine')";
		$res=$db->Execute($q);
				//sub catalogue level2
			$parent_id5 = $id6;
			$id7 = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$parent_id5','$id7','Panadol','Panadol','medicine')";
			$res=$db->Execute($q);

						// -item1
					$parent_id6 = $id7;
					$id8 = shn_create_uuid("catalogue");
					$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$parent_id6','$id8','Cyrup','Cyrup','1','medicine')";
					$res=$db->Execute($q);
								// -unit/units that item use -(kg)
							$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id8','$unit_id8')";
							$res=$db->Execute($q);

						// -item2
					$parent_id7 = $id7;
					$id9 = shn_create_uuid("catalogue");
					$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$parent_id7','$id9','Tablet','Tablet','1','medicine')";
					$res=$db->Execute($q);
								// -unit/units that item use -(kg)
							$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id9','$unit_id3')";
							$res=$db->Execute($q);

}


?>
