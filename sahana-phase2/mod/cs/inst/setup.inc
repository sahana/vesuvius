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
	include_once $global['approot'].'/mod/cs/lib_cs.inc';

	$db=$global["db"];

	// INSERT UNIT TYPES AND UNITS UNDER THEM
	//unit type - mass
	$mass = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$mass','Mass','Mass')";
	$res=$db->Execute($q);

		$kg=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$mass','$kg','Kg','1',0)";
		$res=$db->Execute($query);
	
		$g=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$mass','$g','g','0',0.001)";
		$res=$db->Execute($query);
	
		$mg=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$mass','$mg','mg','0',0.000001)";
		$res=$db->Execute($query);

		$microgram=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$mass','$microgram','microgram','0',0.00000001)";
		$res=$db->Execute($query);

	//unit type - length
	$length = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$length','Length','Length')";
	$res=$db->Execute($q);

		$m=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$length','$m','m','1',0)";
		$res=$db->Execute($query);
	
		$km=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$length','$km','km','0',1000)";
		$res=$db->Execute($query);
	
		$cm=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$length','$cm','cm','0',0.001)";
		$res=$db->Execute($query);


	//unit type - volume
	$volume = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$volume','Volume','Volume')";
	$res=$db->Execute($q);

		$l=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$volume','$l','l','1',0)";
		$res=$db->Execute($query);
	
		$ml=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$volume','$ml','ml','0',0.001)";
		$res=$db->Execute($query);
	
		$kl=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$volume','$kl','kl','0',1000)";
		$res=$db->Execute($query);

		$microl=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$volume','$microl','microlitre','0',0.000001)";
		$res=$db->Execute($query);
        
		$gal=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$volume','$gal','gal','0',1)";
		$res=$db->Execute($query);
		
	//unit type - miscellaneous
	$miscellaneous = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$miscellaneous','Miscellaneous','Miscellaneous')";
	$res=$db->Execute($q);

		$truck=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$truck','Truck','0',1)";
		$res=$db->Execute($query);
	
		$box=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$box','Box','0',1)";
		$res=$db->Execute($query);
	
		$bottle=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$bottle','Bottle','0',1)";
		$res=$db->Execute($query);

		$bag=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$bag','Bag','0',1)";
		$res=$db->Execute($query);
		
		$piece=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$piece','Piece','0',1)";
		$res=$db->Execute($query);

		$kit=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$kit','Kit','0',1)";
		$res=$db->Execute($query);
	
		$ration=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$ration','Ration','0',1)";
		$res=$db->Execute($query);
		
		$packet=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$packet','Packet','0',1)";
		$res=$db->Execute($query);
		
		$units=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$units','Units','0',1)";
		$res=$db->Execute($query);

	//unit type - medical
	$medical = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$medical','Medical','Medical')";
	$res=$db->Execute($q);

		$tab=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$medical','$tab','Tablet','0',1)";
		$res=$db->Execute($query);

		$cap=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$medical','$cap','Capsule','0',1)";
		$res=$db->Execute($query);

		$vial=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$medical','$vial','Vial','0',1)";
		$res=$db->Execute($query);

		$ampoule=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$medical','$ampoule','Ampoule','0',1)";
		$res=$db->Execute($query);

		$suspension=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$medical','$suspension','Suspension','0',1)";
		$res=$db->Execute($query);
		
	$currency = shn_create_uuid("unit_type");
	$q="insert into ct_unit_type (unit_type_uuid,name,description) values('$currency','Currency','Currency')";
	$res=$db->Execute($q);

		$rs=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$currency','$rs','RS','0',1)";
		$res=$db->Execute($query);

	// INSERT MAIN CATALOGUES & SUB CATALOGUE TO THE DATABASE
	//data 1
		// -food - main catalogue-1
	$food = "ct_default-1";
	$food_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$food','Food and Nutrition','Food','food','$food_serial')";
	$res=$db->Execute($q);
			// -sub catalogue-1.1
		
		$dryfood = "ct_default-2";
		$dryfood_serial = shn_cs_generate_subcat_item_serial($food);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$food','$dryfood','Dry Food','Dry Food','food','$dryfood_serial')";
		$res=$db->Execute($q);

			// -item1.1.1
			$rice = "ct_default-3";
			$rice_serial = shn_cs_generate_subcat_item_serial($dryfood);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$dryfood','$rice','Rice','Rice','1','food','$rice_serial')";
			$res=$db->Execute($q);
						// -unit/units that item use -(kg)
					$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$rice','$kg')";
					$res=$db->Execute($q);

			// -item1.1.2
			$sugar = "ct_default-4";
			$sugar_serial = shn_cs_generate_subcat_item_serial($dryfood);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$dryfood','$sugar','Sugar','Sugar','1','food','$sugar_serial')";
			$res=$db->Execute($q);
						// -unit/units that item use -(kg)
					$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$sugar','$kg')";
					$res=$db->Execute($q);
					
			// -item1.1.3
			$milk_powder = "ct_default-5";
			$milk_powder_serial = shn_cs_generate_subcat_item_serial($dryfood);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$dryfood','$milk_powder','Milk Powder','Milk Powder','1','food','$milk_powder_serial')";
			$res=$db->Execute($q);
						// -unit/units that item use -(packet)
					$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$milk_powder','$packet')";
					$res=$db->Execute($q);
					
        // -Item Under Food (main category)-1.2
		$pre_cooked_food = "ct_default-6";
		$pre_cooked_food_serial = shn_cs_generate_subcat_item_serial($food);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$food','$pre_cooked_food','Pre-cooked Food','Pre-cooked Food',1,'food','$pre_cooked_food_serial')";
		$res=$db->Execute($q);
		    // -unit/units that item use -(ration)
					$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$pre_cooked_food','$ration')";
					$res=$db->Execute($q);

	//data
	// -non food items - main catalogue-2
	$nonfood = "ct_default-7";
	$nonfood_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$nonfood','Non Food Items','Non Food Items','non food','$nonfood_serial')";
	$res=$db->Execute($q);

		// - clothing - item-2.1
		$clothing = "ct_default-8";
		$clothing_serial = shn_cs_generate_subcat_item_serial($nonfood);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$nonfood','$clothing','Clothing','Clothing','clothing','$clothing_serial')";
		$res=$db->Execute($q);
		
		    /// -blanket - item-2.1.1
			$blanket = "ct_default-9";
			$blanket_serial = shn_cs_generate_subcat_item_serial($clothing);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$clothing','$blanket','Blankets','Blankets','1','blankets','$blanket_serial')";
			$res=$db->Execute($q);
					// -unit/units that blanket uses -(piece)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$blanket','$piece')";
				$res=$db->Execute($q);
					
		// - Cooking Supplies - sub catalogue-2.2
		$cooking_equipments = "ct_default-10";
		$cooking_equipments_serial = shn_cs_generate_subcat_item_serial($nonfood);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$nonfood','$cooking_equipments','Cooking Equipments','Cooking Equipments',1,'Cooking','$cooking_equipments_serial')";
		$res=$db->Execute($q);
            // -unit/units for cooking Equipments -(piece)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$cooking_equipments','$piece')";
				$res=$db->Execute($q);
				
				
			
    //------Shelter & Housing -main category-3------------------------------------------------------------
    $shelter_housing = "ct_default-11";
	$shelter_housing_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$shelter_housing','Shelter & Housing','Shelter & Housing','Shelter & Housing','$shelter_housing_serial')";
	$res=$db->Execute($q);
	
        // - Housing equipments - sub catalogue-3.1
        $housing_equipments = "ct_default-12";
		$housing_equipments_serial = shn_cs_generate_subcat_item_serial($shelter_housing);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$shelter_housing','$housing_equipments','Housing Equipments','Housing Equipments','Housing','$housing_equipments_serial')";
		$res=$db->Execute($q);
		
		    /// -Tents - item-3.1.1
			$tent = "ct_default-13";
			$tent_serial = shn_cs_generate_subcat_item_serial($housing_equipments);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$housing_equipments','$tent','Tents','Tents','1','tents','$tent_serial')";
			$res=$db->Execute($q);
					// -unit/units for tents -(units)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$tent','$units')";
				$res=$db->Execute($q);
				
		    /// -Shelter sheets - item-3.1.2
			$shelter_sheet = "ct_default-14";
			$shelter_sheet_serial = shn_cs_generate_subcat_item_serial($housing_equipments);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$housing_equipments','$shelter_sheet','Shelter sheets','Shelter sheets','1','Shelter','$shelter_sheet_serial')";
			$res=$db->Execute($q);
					// -unit/units for shelter sheets -(piece)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$shelter_sheet','$piecce')";
				$res=$db->Execute($q);
				
			/// -Cement - item-3.1.3
			$cement = "ct_default-15";
			$cement_serial = shn_cs_generate_subcat_item_serial($housing_equipments);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$housing_equipments','$cement','Cement','Cement','1','cement','$cement_serial')";
			$res=$db->Execute($q);
					// -unit/units for cement -(bags)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$cement','$bag')";
				$res=$db->Execute($q);
		
		
		// - Sanitary equipments - sub catalogue-3.2
        $sanitary_equipments = "ct_default-16";
		$sanitary_equipments_serial = shn_cs_generate_subcat_item_serial($shelter_housing);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$shelter_housing','$sanitary_equipments','Sanitary Equipments','Sanitary Equipments','Sanitary','$sanitary_equipments_serial')";
		$res=$db->Execute($q);
		
		    //-temporary lavatory
		    $temporary_lavatory = "ct_default-17";
			$temporary_lavatory_serial = shn_cs_generate_subcat_item_serial($sanitary_equipments);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$sanitary_equipments','$temporary_lavatory','Temporary Lavatory','Temporary Lavatory','1','Lavatory','$temporary_lavatory_serial')";
			$res=$db->Execute($q);
					// -unit/units for temporary_lavatory -(units)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$temporary_lavatory','$units')";
				$res=$db->Execute($q);

    //--Water--main catalog-4---------------
    $water = "ct_default-18";
	$water_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$water','Water','Water','water','$water_serial')";
	$res=$db->Execute($q);
	
	    //---cooking & Drinking -item-4.1-----
	    $water_cook_drink = "ct_default-19";
		$water_cook_drink_serial = shn_cs_generate_subcat_item_serial($water);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$water','$water_cook_drink','Water for Drinking & Cooking','Water for Drinking & Cooking','1','water','$water_cook_drink_serial')";
		$res=$db->Execute($q);
			// -unit/units for temporary_lavatory -(units)
			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$water_cook_drink','$l')";
			$res=$db->Execute($q);
			// -unit/units for temporary_lavatory -(units)
			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$water_cook_drink','$gal')";
			$res=$db->Execute($q);
			
		//---other-item-4.2-----
	    $water_other = "ct_default-20";
		$water_other_serial = shn_cs_generate_subcat_item_serial($water);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$water','$water_other','Water for other purposes','Water for other purposes','1','water','$water_other_serial')";
		$res=$db->Execute($q);
			// -unit/units for temporary_lavatory -(units)
			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$water_other','$l')";
			$res=$db->Execute($q);
			// -unit/units for temporary_lavatory -(units)
			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$water_other','$gal')";
			$res=$db->Execute($q);
    
	//--fuel-main catalog-5
	$fuel = "ct_default-21";
	$fuel_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$fuel','Fuel','Fuel','fuel','$fuel_serial')";
	$res=$db->Execute($q);
	
		// - fuel for cooking - sub catalogue-5.1
        $fuel_cook = "ct_default-22";
		$fuel_cook_serial = shn_cs_generate_subcat_item_serial($fuel);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$fuel','$fuel_cook','Fuel for cooking','Fuel for cooking','fuel','$fuel_cook_serial')";
		$res=$db->Execute($q);
		
		    //---kerosine-item-5.1.1-----
	        $kerosine = "ct_default-23";
		    $kerosine_serial = shn_cs_generate_subcat_item_serial($fuel);
		    $q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$fuel','$kerosine','Kerosine','Kerosine','1','kerosine','$kerosine_serial')";
		    $res=$db->Execute($q);
			    // -unit/units for fuel -(units)
			    $q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$kerosine','$l')";
			    $res=$db->Execute($q);

		// - fuel for transport - sub catalogue-5.2
        $fuel_transport = "ct_default-24";
		$fuel_transport_serial = shn_cs_generate_subcat_item_serial($fuel);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$fuel','$fuel_transport','Fuel for transporting','Fuel for transporting','fuel','$fuel_transport_serial')";
		$res=$db->Execute($q);
		
		    //---petrol-item-5.2.1-----
	        $petrol = "ct_default-25";
		    $petrol_serial = shn_cs_generate_subcat_item_serial($fuel);
		    $q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$fuel','$petrol','Petrol','Petrol','1','petrol','$petrol_serial')";
		    $res=$db->Execute($q);
			    // -unit/units for fuel -(units)
			    $q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$petrol','$l')";
			    $res=$db->Execute($q);
			    
			//---diesel-item-5.2.2-----
	        $diesel = "ct_default-26";
		    $diesel_serial = shn_cs_generate_subcat_item_serial($fuel);
		    $q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$fuel','$diesel','diesel','diesel','1','diesel','$diesel_serial')";
		    $res=$db->Execute($q);
			    // -unit/units for fuel -(units)
			    $q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$diesel','$l')";
			    $res=$db->Execute($q);
				
	// - helth kit - main catalogue-6 ----------------------------------------------------------------------------------------------------------------------------------------
	$HealthKits = "ct_default-27";
	$HealthKits_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$HealthKits','Health Kits','Health Kits','health kits','$HealthKits_serial')";
	$res=$db->Execute($q);

		// - Burn Dressing Kits - sub catalogue-6.1
		$BurnDressingKits = "ct_default-28";
		$BurnDressingKits_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$BurnDressingKits','Burn Dressing Kits','Burn Dressing Kits','1','kits','$BurnDressingKits_serial')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$BurnDressingKits','$kit')";
			$res=$db->Execute($q);

		// - Clean Delivery Kits - sub catalogue-6.2
		$CleanDeliveryKits = "ct_default-29";
		$CleanDeliveryKits_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$CleanDeliveryKits','Clean Delivery Kits','Clean Delivery Kits','1','kits','$CleanDeliveryKits_serial')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$CleanDeliveryKits','$kit')";
			$res=$db->Execute($q);

		// - Diarrhoea Kits - sub catalogue-6.3
		$DiarrhoeaKits = "ct_default-30";
		$DiarrhoeaKits_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$DiarrhoeaKits','Diarrhoea Kits','Diarrhoea Kits','1','kits','$DiarrhoeaKits_serial')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$DiarrhoeaKits','$kit')";
			$res=$db->Execute($q);

		// - Emergency Health Kits - sub catalogue-6.4
		$EmergencyHealthKits = "ct_default-31";
		$EmergencyHealthKits_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$EmergencyHealthKits','Emergency Health Kits','Emergency Health Kits','1','kits','$EmergencyHealthKits_serial')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$EmergencyHealthKits','$kit')";
			$res=$db->Execute($q);

		// - EMOC Kits - sub catalogue-6.5
		$EmOCKits = "ct_default-32";
		$EmOCKits_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$EmOCKits','EmOC Kits','EmOC Kits','1','kits','$EmOCKits_serial')";
		$res=$db->Execute($q); 
		    //units
			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$EmOCKits','$kit')";
			$res=$db->Execute($q);

		// -Vaccines - sub catalogue-6.6
		$Vaccines = "ct_default-33";
		$Vaccines_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HealthKits','$Vaccines','Vaccines','Vaccines','kits','$Vaccines_serial')";
		$res=$db->Execute($q);
		    //items-measles vaccines-6.6.1
		    $measles_vaccines = "ct_default-34";
		    $measles_vaccines_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		    $q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$measles_vaccines','Measles Vaccines','Measles Vaccines','1','kits','$measles_vaccines_serial')";
		    $res=$db->Execute($q);
                
			    
			//polio vaccine items-6.6.2
			$polio_vaccines = "ct_default-35";
		    $polio_vaccines_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		    $q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$polio_vaccines','Polio Vaccines','Polio Vaccines','1','kits','$polio_vaccines_serial')";
		    $res=$db->Execute($q);
                

		// - Trauma Kits - sub catalogue-6.7
		$TraumaKits = "ct_default-36";
		$TraumaKits_serial = shn_cs_generate_subcat_item_serial($HealthKits);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$HealthKits','$TraumaKits','Trauma Kits','Trauma Kits','1','kits','$TraumaKits_serial')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$TraumaKits','$kit')";
			$res=$db->Execute($q);
         //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// - Medical Equipment - main catalogue-7 --------------------------------------------------------------------------------------------------------------------
	$MedicalEquipment = "ct_default-37";
	$MedicalEquipment_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$MedicalEquipment','Medical Equipment','Medical Equipment','medical equipment','$MedicalEquipment_serial')";
	$res=$db->Execute($q);

		// - Anaesthesia Equipment - sub catalogue-7.1
		$AnaesthesiaEquipment = "ct_default-38";
		$AnaesthesiaEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$AnaesthesiaEquipment','Anaesthesia Equipment','Anaesthesia Equipment','medical equipment','$AnaesthesiaEquipment_serial')";
		$res=$db->Execute($q);

		// - Cold Chain Equipment - sub catalogue-7.2
		$ColdChainEquipment = "ct_default-39";
		$ColdChainEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$ColdChainEquipment','Cold Chain Equipment','Cold Chain Equipment','medical equipment','$ColdChainEquipment_serial')";
		$res=$db->Execute($q);

		// - Diagnostic Equipment - sub catalogue-7.3
		$DiagnosticEquipment = "ct_default-40";
		$DiagnosticEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$DiagnosticEquipment','Diagnostic Equipment','Diagnostic Equipment','medical equipment','$DiagnosticEquipment_serial')";
		$res=$db->Execute($q);

		// - Exercise Equipment - sub catalogue-7.4
		$ExerciseEquipment = "ct_default-41";
		$ExerciseEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$ExerciseEquipment','Exercise Equipment ','Exercise Equipment','medical equipment','$ExerciseEquipment_serial')";
		$res=$db->Execute($q);

		// - Hospital Equipment - sub catalogue-7.5
		$HospitalEquipment = "ct_default-42";
		$HospitalEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$HospitalEquipment','Hospital Equipment','Hospital Equipment','medical equipment','$HospitalEquipment_serial')";
		$res=$db->Execute($q);

		// - Medical Utensils - sub catalogue-7.6
		$MedicalUtensils = "ct_default-43";
		$MedicalUtensils_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$MedicalUtensils','Medical Utensils','Medical Utensils','medical equipment','$MedicalUtensils_serial')";
		$res=$db->Execute($q);

		// - Resuscitation Equipment - sub catalogue-7.7
		$ResuscitationEquipment = "ct_default-44";
		$ResuscitationEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$ResuscitationEquipment','Resuscitation Equipment','Resuscitation Equipment','medical equipment','$ResuscitationEquipment_serial')";
		$res=$db->Execute($q);

		// - Sterilization Equipment - sub catalogue-7.8
		$SterilizationEquipment = "ct_default-45";
		$SterilizationEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$SterilizationEquipment','Sterilization Equipment','Sterilization Equipment','medical equipment','$SterilizationEquipment_serial')";
		$res=$db->Execute($q);

		// - Surgical Equipment - sub catalogue-7.9
		$SurgicalEquipment = "ct_default-46";
		$SurgicalEquipment_serial = shn_cs_generate_subcat_item_serial($MedicalEquipment);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$MedicalEquipment','$SurgicalEquipment','Surgical Equipment','Surgical Equipment','medical equipment','$SurgicalEquipment_serial')";
		$res=$db->Execute($q);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Medical drugs - main catalogue-8 ------------------------------------------------------------------------------------------------------------------------------
	$medicaldrug = "ct_default-47";
	$medicaldrug_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$medicaldrug','Medical Drugs','Medical Drugs','medical drugs','$medicaldrug_serial')";
	$res=$db->Execute($q);
		// ANAESTHETICS- sub catalogue - level 1
		$ANAESTHETICS = "ct_default-48";
		$ANAESTHETICS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANAESTHETICS','ANAESTHETICS','ANAESTHETICS','medical drugs','$ANAESTHETICS_serial')";
		$res=$db->Execute($q);
			// General Anaesthetics & Oxygen- sub catalogue - level 2
			$GeneralAnaestheticsOxygen = "ct_default-49";
			$GeneralAnaestheticsOxygen_serial = shn_cs_generate_subcat_item_serial($ANAESTHETICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANAESTHETICS','$GeneralAnaestheticsOxygen','General Anaesthetics & Oxygen','General Anaesthetics & Oxygen','medical drugs','$GeneralAnaestheticsOxygen_serial')";
			$res=$db->Execute($q);
			// Local Anaesthetics- sub catalogue - level 2
			$LocalAnaesthetics = "ct_default-50";
			$LocalAnaesthetics_serial = shn_cs_generate_subcat_item_serial($ANAESTHETICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANAESTHETICS','$LocalAnaesthetics','Local Anaesthetics','Local Anaesthetics','medical drugs','$LocalAnaesthetics_serial')";
			$res=$db->Execute($q);
			// Preoperative medication and sedation for short-term procedures- sub catalogue - level 2
			$Preoperativemedication = "ct_default-51";
			$Preoperativemedication_serial = shn_cs_generate_subcat_item_serial($ANAESTHETICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANAESTHETICS','$Preoperativemedication','Preoperative medication and sedation for short-term procedures','Preoperative medication and sedation for short-term procedures','medical drugs','$Preoperativemedication_serial')";
			$res=$db->Execute($q);

		// ANALGESICS- sub catalogue - level 1
		$ANALGESICS = "ct_default-52";
		$ANALGESICS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANALGESICS','ANALGESICS','ANALGESICS, ANTIPYRETICS, NON-STEROIDAL ANTI-INFLAMMATORY DRUGS (NSAIDs), DRUGS USED TO TREAT GOUT AND DISEASE MODIFYING AGENTS IN RHEUMATOID DISORDERS (DMARDs)','medical drugs','$ANALGESICS_serial')";
		$res=$db->Execute($q);
			// Non-opioids and NSAIDs- sub catalogue - level 2
			$NonopioidsandNSAIDs = "ct_default-53";
			$NonopioidsandNSAIDs_serial = shn_cs_generate_subcat_item_serial($ANALGESICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANALGESICS','$NonopioidsandNSAIDs','Non-opioids and NSAIDs','Non-opioids and NSAIDs','medical drugs','$NonopioidsandNSAIDs_serial')";
			$res=$db->Execute($q);
			// Opioid Analgesics- sub catalogue - level 2
			$OpioidAnalgesics = "ct_default-54";
			$OpioidAnalgesics_serial = shn_cs_generate_subcat_item_serial($ANALGESICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANALGESICS','$OpioidAnalgesics','Opioid Analgesics','Opioid Analgesics','medical drugs','$OpioidAnalgesics_serial')";
			$res=$db->Execute($q);
			// Drugs used to treat gout- sub catalogue - level 2
			$Drugsusedtotreatgout = "ct_default-55";
			$Drugsusedtotreatgout_serial = shn_cs_generate_subcat_item_serial($ANALGESICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANALGESICS','$Drugsusedtotreatgout','Drugs used to treat gout','Drugs used to treat gout','medical drugs','$Drugsusedtotreatgout_serial')";
			$res=$db->Execute($q);
			// Disease modifying agents used in rheumatoid disorders (DMARDs) - sub catalogue - level 2
			$DMARDs = "ct_default-56";
			$DMARDs_serial = shn_cs_generate_subcat_item_serial($ANALGESICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANALGESICS','$DMARDs','DMARD','Disease modifying agents used in rheumatoid disorders (DMARDs)','medical drugs','$DMARDs_serial')";
			$res=$db->Execute($q);

		// ANTIALLERGICS AND DRUGS USED IN ANAPHYLAXIS- sub catalogue - level 1
		$ANTIALLERGICSANAPHYLAXIS = "ct_default-57";
		$ANTIALLERGICSANAPHYLAXIS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTIALLERGICSANAPHYLAXIS','ANTIALLERGICS AND ANAPHYLAXIS Treatment Agent','ANTIALLERGICS AND DRUGS USED IN ANAPHYLAXIS Treatment Agent','medical drugs','$ANTIALLERGICSANAPHYLAXIS_serial')";
		$res=$db->Execute($q);

		// ANTIDOTES AND OTHER SUBSTANCES USED IN POISONING- sub catalogue - level 1
		$ANTIDOTESUSEDINPOISONING = "ct_default-58";
		$ANTIDOTESUSEDINPOISONING_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTIDOTESUSEDINPOISONING','ANTIDOTES AND OTHER SUBSTANCES USED IN POISONING','ANTIDOTES AND OTHER SUBSTANCES USED IN POISONING','medical drugs','$ANTIDOTESUSEDINPOISONING_serial')";
		$res=$db->Execute($q);
			// 4.1 Non-specific- sub catalogue - level 2 
			$Nonspecific = "ct_default-59";
			$Nonspecific_serial = shn_cs_generate_subcat_item_serial($ANTIDOTESUSEDINPOISONING);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIDOTESUSEDINPOISONING','$Nonspecific','Non-specific','Non-specific','medical drugs','$Nonspecific_serial')";
			$res=$db->Execute($q);
			// 4.2 Specific- sub catalogue - level 2
			$Specific = "ct_default-60";
			$Specific_serial = shn_cs_generate_subcat_item_serial($ANTIDOTESUSEDINPOISONING);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIDOTESUSEDINPOISONING','$Specific','Specific','Specific','medical drugs','$Specific_serial')";
			$res=$db->Execute($q);

		// 5. ANTICONVULSANTS/ANTIEPILEPTICS- sub catalogue - level 1
		$ANTICONVULSANTSANTIEPILEPTICS = "ct_default-61";
		$ANTICONVULSANTSANTIEPILEPTICS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTICONVULSANTSANTIEPILEPTICS','ANTICONVULSANTS/ANTIEPILEPTICS','ANTICONVULSANTS/ANTIEPILEPTICS','medical drugs','$ANTICONVULSANTSANTIEPILEPTICS_serial')";
		$res=$db->Execute($q);

		// 6. ANTI-INFECTIVE DRUGS - sub catalogue - level 1
		$ANTIINFECTIVEDRUGS = "ct_default-62";
		$ANTIINFECTIVEDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTIINFECTIVEDRUGS','ANTI-INFECTIVE DRUGS','ANTI-INFECTIVE DRUGS','medical drugs','$ANTIINFECTIVEDRUGS_serial')";
		$res=$db->Execute($q);
			// 6.1.1 Intestinal anthelminthics- sub catalogue - level 2 
			$Intestinalanthelminthics = "ct_default-63";
			$Intestinalanthelminthics_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Intestinalanthelminthics','Intestinal anthelminthics','Intestinal anthelminthics','medical drugs','$Intestinalanthelminthics_serial')";
			$res=$db->Execute($q);
			// 6.1.2 Antifilarials- sub catalogue - level 2 
			$Antifilarials = "ct_default-64";
			$Antifilarials_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antifilarials','Antifilarials','Antifilarials','medical drugs','$Antifilarials_serial')";
			$res=$db->Execute($q);
			// 6.1.3 Antischistosomals and anti-trematode drugs- sub catalogue - level 2 
			$Antischistosomalsandantitrematodedrugs = "ct_default-65";
			$Antischistosomalsandantitrematodedrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antischistosomalsandantitrematodedrugs','Antischistosomals and anti-trematode drugs','Antischistosomals and anti-trematode drugs','medical drugs','$Antischistosomalsandantitrematodedrugs_serial')";
			$res=$db->Execute($q);
			// 6.2 Antibacterials- sub catalogue - level 2 
			$Antibacterials = "ct_default-66";
			$Antibacterials_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antibacterials','Antibacterials','Antibacterials','medical drugs','$Antibacterials_serial')";
			$res=$db->Execute($q);
			// 6.2.1 Beta lactam drugs- sub catalogue - level 2 
			$Betalactamdrugs = "ct_default-67";
			$Betalactamdrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Betalactamdrugs','Beta lactam drugs','Beta lactam drugs','medical drugs','$Betalactamdrugs_serial')";
			$res=$db->Execute($q);
			// 6.2.2 Other antibacterials- sub catalogue - level 2 
			$Otherantibacterials = "ct_default-68";
			$Otherantibacterials_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Otherantibacterials','Other antibacterials','Other antibacterials','medical drugs','$Otherantibacterials_serial')";
			$res=$db->Execute($q);
			// 6.2.3 Antileprosy drugs- sub catalogue - level 2 
			$Antileprosydrugs = "ct_default-69";
			$Antileprosydrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antileprosydrugs','Antileprosy drugs','Antileprosy drugs','medical drugs','$Antileprosydrugs_serial')";
			$res=$db->Execute($q);
			// 6.2.4 Antituberculosis drugs- sub catalogue - level 2 
			$Antituberculosisdrugs = "ct_default-70";
			$Antituberculosisdrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antituberculosisdrugs','Antituberculosis drugs','Antituberculosis drugs','medical drugs','$Antituberculosisdrugs_serial')";
			$res=$db->Execute($q);
			// 6.3 Antifungal drugs- sub catalogue - level 2 
			$Antifungaldrugs = "ct_default-71";
			$Antifungaldrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antifungaldrugs','Antifungal drugs','Antifungal drugs','medical drugs','$Antifungaldrugs_serial')";
			$res=$db->Execute($q);
			// 6.4.1 Antiherpes- sub catalogue - level 2 
			$Antiherpes = "ct_default-72";
			$Antiherpes_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antiherpes','Antiherpes','Antiherpes','medical drugs','$Antiherpes_serial')";
			$res=$db->Execute($q);
			// 6.4.2 Antiretrovirals - sub catalogue - level 2 
			$Antiretrovirals = "ct_default-73";
			$Antiretrovirals_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antiretrovirals','Antiretrovirals','Antiretrovirals','medical drugs','$Antiretrovirals_serial')";
			$res=$db->Execute($q);
			// 6.5.1 Antiamoebic and antigiardiasis drugs - sub catalogue - level 2 
			$Antiamoebicandantigiardiasisdrugs = "ct_default-74";
			$Antiamoebicandantigiardiasisdrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antiamoebicandantigiardiasisdrugs','Antiamoebic and antigiardiasis drugs','Antiamoebic and antigiardiasis drugs','medical drugs','$Antiamoebicandantigiardiasisdrugs_serial')";
			$res=$db->Execute($q);
			// 6.5.2 Antileishmaniasis drugs - sub catalogue - level 2 
			$Antileishmaniasisdrugs = "ct_default-75";
			$Antileishmaniasisdrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antileishmaniasisdrugs','Antileishmaniasis drugs','Antileishmaniasis drugs','medical drugs','$Antileishmaniasisdrugs_serial')";
			$res=$db->Execute($q);
			// 6.5.3 Antimalarial drugs - sub catalogue - level 2 
			$Antimalarialdrugs = "ct_default-76";
			$Antimalarialdrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antimalarialdrugs','Antimalarial drugs','Antimalarial drugs','medical drugs','$Antimalarialdrugs_serial')";
			$res=$db->Execute($q);
			// 6.5.4 Anti-pneumocystosis and anti-toxoplasmosis drugs - sub catalogue - level 2 
			$Antipneumocystosisandantitoxoplasmosisdrugs = "ct_default-77";
			$Antipneumocystosisandantitoxoplasmosisdrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antipneumocystosisandantitoxoplasmosisdrugs','Anti-pneumocystosis and anti-toxoplasmosis drugs','Anti-pneumocystosis and anti-toxoplasmosis drugs','medical drugs','$Antipneumocystosisandantitoxoplasmosisdrugs_serial')";
			$res=$db->Execute($q);
			// 6.5.5 Antitrypanosomal drugs - sub catalogue - level 2 
			$Antitrypanosomaldrugs = "ct_default-78";
			$Antitrypanosomaldrugs_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Antitrypanosomaldrugs','Antitrypanosomal drugs','Antitrypanosomal drugs','medical drugs','$Antitrypanosomaldrugs_serial')";
			$res=$db->Execute($q);
			// 6.6 Insect repellents - sub catalogue - level 2 
			$Insectrepellents = "ct_default-79";
			$Insectrepellents_serial = shn_cs_generate_subcat_item_serial($ANTIINFECTIVEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIINFECTIVEDRUGS','$Insectrepellents','Insect repellents','Insect repellents','medical drugs','$Insectrepellents_serial')";
			$res=$db->Execute($q);

		// 7. ANTIMIGRAINE DRUGS - sub catalogue - level 1
		$ANTIMIGRAINEDRUGS = "ct_default-80";
		$ANTIMIGRAINEDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTIMIGRAINEDRUGS','ANTIMIGRAINE DRUGS','ANTIMIGRAINE DRUGS','medical drugs','$ANTIMIGRAINEDRUGS_serial')";
		$res=$db->Execute($q);
			// 7.1  For treatment of acute attack- sub catalogue - level 2 
			$Fortreatmentofacuteattack = "ct_default-81";
			$Fortreatmentofacuteattack_serial = shn_cs_generate_subcat_item_serial($ANTIMIGRAINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIMIGRAINEDRUGS','$Fortreatmentofacuteattack',' For treatment of acute attack',' For treatment of acute attack','medical drugs','$Fortreatmentofacuteattack_serial')";
			$res=$db->Execute($q);
			// 7.2 For prophylaxis - sub catalogue - level 2 
			$Forprophylaxis = "ct_default-82";
			$Forprophylaxis_serial = shn_cs_generate_subcat_item_serial($ANTIMIGRAINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTIMIGRAINEDRUGS','$Forprophylaxis','  For prophylaxis',' For prophylaxis','medical drugs','$Forprophylaxis_serial')";
			$res=$db->Execute($q);

		// 8. ANTINEOPLASTIC, IMMUNOSUPPRESSIVES AND DRUGS USED IN PALLIATIVE CARE - sub catalogue - level 1
		$ANTINEOPLASTICIMMUNOSUPPRESSIVES = "ct_default-83";
		$ANTINEOPLASTICIMMUNOSUPPRESSIVES_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTINEOPLASTICIMMUNOSUPPRESSIVES','ANTINEOPLASTIC IMMUNOSUPPRESSIVES AND DRUGS USED IN PALLIATIVE CARE','ANTINEOPLASTIC IMMUNOSUPPRESSIVES AND DRUGS USED IN PALLIATIVE CARE','medical drugs','$ANTINEOPLASTICIMMUNOSUPPRESSIVES_serial')";
		$res=$db->Execute($q);
			// 8.1  Immunosuppressive drugs- sub catalogue - level 2 
			$Immunosuppressivedrugs = "ct_default-84";
			$Immunosuppressivedrugs_serial = shn_cs_generate_subcat_item_serial($ANTINEOPLASTICIMMUNOSUPPRESSIVES);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Immunosuppressivedrugs','Immunosuppressive drugs','Immunosuppressive drugs','medical drugs','$Immunosuppressivedrugs_serial')";
			$res=$db->Execute($q);
			// 8.2  Cytotoxic drugs- sub catalogue - level 2 
			$Cytotoxicdrugs = "ct_default-85";
			$Cytotoxicdrugs_serial = shn_cs_generate_subcat_item_serial($ANTINEOPLASTICIMMUNOSUPPRESSIVES);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Cytotoxicdrugs','Cytotoxic drugs','Cytotoxic drugs','medical drugs','$Cytotoxicdrugs_serial')";
			$res=$db->Execute($q);
			// 8.3  Hormones and antihormones- sub catalogue - level 2 
			$Hormonesandantihormones = "ct_default-86";
			$Hormonesandantihormones_serial = shn_cs_generate_subcat_item_serial($ANTINEOPLASTICIMMUNOSUPPRESSIVES);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Hormonesandantihormones','Hormones and antihormones','Hormones and antihormones','medical drugs','$Hormonesandantihormones_serial')";
			$res=$db->Execute($q);
			// 8.4 Drugs used in palliative care - sub catalogue - level 2 
			$Drugsusedinpalliativecare = "ct_default-87";
			$Drugsusedinpalliativecare_serial = shn_cs_generate_subcat_item_serial($ANTINEOPLASTICIMMUNOSUPPRESSIVES);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Drugsusedinpalliativecare','Drugs used in palliative care','Drugs used in palliative care','medical drugs','$Drugsusedinpalliativecare_serial')";
			$res=$db->Execute($q);

		// 9. ANTIPARKINSONIAN DRUGS - sub catalogue - level 1
		$ANTIPARKINSONIANDRUGS = "ct_default-88";
		$ANTIPARKINSONIANDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$ANTIPARKINSONIANDRUGS','ANTIPARKINSONIAN DRUGS','ANTIPARKINSONIAN DRUGS','medical drugs','$ANTIPARKINSONIANDRUGS_serial')";
		$res=$db->Execute($q);

		//10. DRUGS AFFECTING THE BLOOD - sub catalogue - level 1
		$DRUGSAFFECTINGTHEBLOOD = "ct_default-89";
		$DRUGSAFFECTINGTHEBLOOD_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$DRUGSAFFECTINGTHEBLOOD','DRUGS AFFECTING THE BLOOD','DRUGS AFFECTING THE BLOOD','medical drugs','$DRUGSAFFECTINGTHEBLOOD_serial')";
		$res=$db->Execute($q);
			// 10.1 Anti-anaemia drugs - sub catalogue - level 2 
			$Antianaemiadrugs = "ct_default-90";
			$Antianaemiadrugs_serial = shn_cs_generate_subcat_item_serial($DRUGSAFFECTINGTHEBLOOD);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DRUGSAFFECTINGTHEBLOOD','$Antianaemiadrugs','Anti-anaemia drugs','Anti-anaemia drugs','medical drugs','$Antianaemiadrugs_serial')";
			$res=$db->Execute($q);
			// 10.2 Drugs affecting coagulation - sub catalogue - level 2 
			$Drugsaffectingcoagulation = "ct_default-91";
			$Drugsaffectingcoagulation_serial = shn_cs_generate_subcat_item_serial($DRUGSAFFECTINGTHEBLOOD);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DRUGSAFFECTINGTHEBLOOD','$Drugsaffectingcoagulation','Drugs affecting coagulation','Drugs affecting coagulation','medical drugs','$Drugsaffectingcoagulation_serial')";
			$res=$db->Execute($q);

		//11. BLOOD PRODUCTS AND PLASMA SUBSTITUTES - sub catalogue - level 1
		$BLOODPRODUCTSANDPLASMASUBSTITUTES = "ct_default-92";
		$BLOODPRODUCTSANDPLASMASUBSTITUTES_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$BLOODPRODUCTSANDPLASMASUBSTITUTES','BLOOD PRODUCTS AND PLASMA SUBSTITUTES','BLOOD PRODUCTS AND PLASMA SUBSTITUTES','medical drugs','$BLOODPRODUCTSANDPLASMASUBSTITUTES_serial')";
		$res=$db->Execute($q);
			// 11.1 Plasma substitutes - sub catalogue - level 2 
			$Plasmasubstitutes = "ct_default-93";
			$Plasmasubstitutes_serial = shn_cs_generate_subcat_item_serial($BLOODPRODUCTSANDPLASMASUBSTITUTES);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$BLOODPRODUCTSANDPLASMASUBSTITUTES','$Plasmasubstitutes','Plasma substitutes','Plasma substitutes','medical drugs','$Plasmasubstitutes_serial')";
			$res=$db->Execute($q);
			// 11.2 Plasma fractions for specific use - sub catalogue - level 2 
			$Plasmafractionsforspecificuse = "ct_default-94";
			$Plasmafractionsforspecificuse_serial = shn_cs_generate_subcat_item_serial($BLOODPRODUCTSANDPLASMASUBSTITUTES);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$BLOODPRODUCTSANDPLASMASUBSTITUTES','$Plasmafractionsforspecificuse','Plasma fractions for specific use','Plasma fractions for specific use','medical drugs','$Plasmafractionsforspecificuse_serial')";
			$res=$db->Execute($q);

		//12. CARDIOVASCULAR DRUGS - sub catalogue - level 1
		$CARDIOVASCULARDRUGS = "ct_default-95";
		$CARDIOVASCULARDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$CARDIOVASCULARDRUGS','CARDIOVASCULAR DRUGS','CARDIOVASCULAR DRUGS','medical drugs','$CARDIOVASCULARDRUGS_serial')";
		$res=$db->Execute($q);
			// 12.1 Antianginal drugs - sub catalogue - level 2 
			$Antianginaldrugs = "ct_default-96";
			$Antianginaldrugs_serial = shn_cs_generate_subcat_item_serial($CARDIOVASCULARDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$CARDIOVASCULARDRUGS','$Antianginaldrugs','Antianginal drugs','Antianginal drugs','medical drugs','$Antianginaldrugs_serial')";
			$res=$db->Execute($q);
			// 12.2 Antiarrhythmic drugs - sub catalogue - level 2 
			$Antiarrhythmicdrugs = "ct_default-97";
			$Antiarrhythmicdrugs_serial = shn_cs_generate_subcat_item_serial($CARDIOVASCULARDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$CARDIOVASCULARDRUGS','$Antiarrhythmicdrugs','Antiarrhythmic drugs','Antiarrhythmic drugs','medical drugs','$Antiarrhythmicdrugs_serial')";
			$res=$db->Execute($q);
			// 12.3 Antihypertensive drugs - sub catalogue - level 2 
			$Antihypertensivedrugs = "ct_default-98";
			$Antihypertensivedrugs_serial = shn_cs_generate_subcat_item_serial($CARDIOVASCULARDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$CARDIOVASCULARDRUGS','$Antihypertensivedrugs','Antihypertensive drugs','Antihypertensive drugs','medical drugs','$Antihypertensivedrugs_serial')";
			$res=$db->Execute($q);
			// 12.4 Drugs used in heart failure - sub catalogue - level 2 
			$Drugsusedinheartfailure = "ct_default-99";
			$Drugsusedinheartfailure_serial = shn_cs_generate_subcat_item_serial($CARDIOVASCULARDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$CARDIOVASCULARDRUGS','$Drugsusedinheartfailure','Drugs used in heart failure','Drugs used in heart failure','medical drugs','$Drugsusedinheartfailure_serial')";
			$res=$db->Execute($q);
			// 12.5  Antithrombotic drugs - sub catalogue - level 2 
			$Antithromboticdrugs = "ct_default-100";
			$Antithromboticdrugs_serial = shn_cs_generate_subcat_item_serial($CARDIOVASCULARDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$CARDIOVASCULARDRUGS','$Antithromboticdrugs',' Antithrombotic drugs',' Antithrombotic drugs','medical drugs','$Antithromboticdrugs_serial')";
			$res=$db->Execute($q);
			// 12.6  Lipid-lowering agents - sub catalogue - level 2 
			$Lipidloweringagents = "ct_default-101";
			$Lipidloweringagents_serial = shn_cs_generate_subcat_item_serial($CARDIOVASCULARDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$CARDIOVASCULARDRUGS','$Lipidloweringagents','Lipid-lowering agents','Lipid-lowering agents','medical drugs','$Lipidloweringagents_serial')";
			$res=$db->Execute($q);
	
		//13. DERMATOLOGICAL DRUGS (topical)  - sub catalogue - level 1
		$DERMATOLOGICALDRUGS = "ct_default-102";
		$DERMATOLOGICALDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$DERMATOLOGICALDRUGS','DERMATOLOGICAL DRUGS (topical) ','DERMATOLOGICAL DRUGS (topical) ','medical drugs','$DERMATOLOGICALDRUGS_serial')";
		$res=$db->Execute($q);
			// 13.1 Antifungal drugs - sub catalogue - level 2 
			$DERMATOAntifungaldrugs = "ct_default-103";
			$DERMATOAntifungaldrugs_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATOAntifungaldrugs','Antifungal drugs','Antifungal drugs','medical drugs','$DERMATOAntifungaldrugs_serial')";
			$res=$db->Execute($q);
			// 13.2 Anti-infective drugs - sub catalogue - level 2 
			$DERMATOAntiinfectivedrugs = "ct_default-104";
			$DERMATOAntiinfectivedrugs_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATOAntiinfectivedrugs','Anti-infective drugs','Anti-infective drugs','medical drugs','$DERMATOAntiinfectivedrugs_serial')";
			$res=$db->Execute($q);
			// 13.3 Anti-inflammatory and antipruritic drugs - sub catalogue - level 2 
			$DERMATOAntiinflammatoryandantipruriticdrugs = "ct_default-105";
			$DERMATOAntiinflammatoryandantipruriticdrugs_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATOAntiinflammatoryandantipruriticdrugs','Anti-inflammatory and antipruritic drugs','Anti-inflammatory and antipruritic drugs','medical drugs','$DERMATOAntiinflammatoryandantipruriticdrugs_serial')";
			$res=$db->Execute($q);
			// 13.4 Astringent drugs - sub catalogue - level 2 
			$DERMATOAstringentdrugs = "ct_default-106";
			$DERMATOAstringentdrugs_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATOAstringentdrugs','Astringent drugs','Astringent drugs','medical drugs','$DERMATOAstringentdrugs_serial')";
			$res=$db->Execute($q);
			// 13.5 Drugs affecting skin differentiation and proliferation - sub catalogue - level 2 
			$DERMATODrugsaffectingskindifferentiationandproliferation = "ct_default-107";
			$DERMATODrugsaffectingskindifferentiationandproliferation_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATODrugsaffectingskindifferentiationandproliferation','Drugs affecting skin differentiation and proliferation','Drugs affecting skin differentiation and proliferation','medical drugs','$DERMATODrugsaffectingskindifferentiationandproliferation_serial')";
			$res=$db->Execute($q);
			// 13.6 Scabicides and pediculicides - sub catalogue - level 2 
			$DERMATOScabicidesandpediculicides = "ct_default-108";
			$DERMATOScabicidesandpediculicides_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATOScabicidesandpediculicides','Scabicides and pediculicides','Scabicides and pediculicides','medical drugs','$DERMATOScabicidesandpediculicides_serial')";
			$res=$db->Execute($q);
			// 13.7 Ultraviolet blocking agents - sub catalogue - level 2 
			$DERMATOUltravioletblockingagents = "ct_default-109";
			$DERMATOUltravioletblockingagents_serial = shn_cs_generate_subcat_item_serial($DERMATOLOGICALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DERMATOLOGICALDRUGS','$DERMATOUltravioletblockingagents','Ultraviolet blocking agents','Ultraviolet blocking agents','medical drugs','$DERMATOUltravioletblockingagents_serial')";
			$res=$db->Execute($q);
		
		//14. DIAGNOSTIC AGENTS  - sub catalogue - level 1
		$DIAGNOSTICAGENTS = "ct_default-110";
		$DIAGNOSTICAGENTS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$DIAGNOSTICAGENTS','DIAGNOSTIC AGENTS ','DIAGNOSTIC AGENTS ','medical drugs','$DIAGNOSTICAGENTS_serial')";
		$res=$db->Execute($q);
			// 14.1 Ophthalmic drugs - sub catalogue - level 2 
			$DIAGNOSTICOphthalmicdrugs = "ct_default-111";
			$DIAGNOSTICOphthalmicdrugs_serial = shn_cs_generate_subcat_item_serial($DIAGNOSTICAGENTS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DIAGNOSTICAGENTS','$DIAGNOSTICOphthalmicdrugs','Ophthalmic drugs','Ophthalmic drugs','medical drugs','$DIAGNOSTICOphthalmicdrugs_serial')";
			$res=$db->Execute($q);
			// 14.2 Radiocontrast media - sub catalogue - level 2 
			$DIAGNOSTICORadiocontrastmedia = "ct_default-112";
			$DIAGNOSTICORadiocontrastmedia_serial = shn_cs_generate_subcat_item_serial($DIAGNOSTICAGENTS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DIAGNOSTICAGENTS','$DIAGNOSTICORadiocontrastmedia','Radiocontrast media','Radiocontrast media','medical drugs','$DIAGNOSTICORadiocontrastmedia_serial')";
			$res=$db->Execute($q);

		//15. DISINFECTANTS AND ANTISEPTICS  - sub catalogue - level 1
		$DISINFECTANTSANDANTISEPTICS = "ct_default-113";
		$DISINFECTANTSANDANTISEPTICS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$DISINFECTANTSANDANTISEPTICS','DISINFECTANTS AND ANTISEPTICS ','DISINFECTANTS AND ANTISEPTICS ','medical drugs','$DISINFECTANTSANDANTISEPTICS_serial')";
		$res=$db->Execute($q);
			// 15.1 Antiseptics - sub catalogue - level 2 
			$DISINFECTAntiseptics = "ct_default-114";
			$DISINFECTAntiseptics_serial = shn_cs_generate_subcat_item_serial($DISINFECTANTSANDANTISEPTICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DISINFECTANTSANDANTISEPTICS','$DISINFECTAntiseptics','Ophthalmic drugs','Ophthalmic drugs','medical drugs','$DISINFECTAntiseptics_serial')";
			$res=$db->Execute($q);
			// 15.2 Disinfectants - sub catalogue - level 2 
			$DISINFECTDisinfectants = "ct_default-115";
			$DISINFECTDisinfectants_serial = shn_cs_generate_subcat_item_serial($DISINFECTANTSANDANTISEPTICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DISINFECTANTSANDANTISEPTICS','$DISINFECTDisinfectants','Disinfectants','Disinfectants','medical drugs','$DISINFECTDisinfectants_serial')";
			$res=$db->Execute($q);
		
		//16. DIURETICS  - sub catalogue - level 1
		$DIURETICS = "ct_default-116";
		$DIURETICS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$DIURETICS','DIURETICS','DIURETICS','medical drugs','$DIURETICS_serial')";
		$res=$db->Execute($q);

		//17. GASTROINTESTINAL DRUGS  - sub catalogue - level 1
		$GASTROINTESTINALDRUGS = "ct_default-117";
		$GASTROINTESTINALDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$GASTROINTESTINALDRUGS','GASTROINTESTINAL DRUGS','GASTROINTESTINAL DRUGS','medical drugs','$GASTROINTESTINALDRUGS_serial')";
		$res=$db->Execute($q);
			// 17.1 Antacids and other antiulcer drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntacidsandotherantiulcerdrugs = "ct_default-118";
			$GASTROINTESTINALAntacidsandotherantiulcerdrugs_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntacidsandotherantiulcerdrugs','Antacids and other antiulcer drugs','Antacids and other antiulcer drugs','medical drugs','$GASTROINTESTINALAntacidsandotherantiulcerdrugs_serial')";
			$res=$db->Execute($q);
			// 17.2 Antiemetic drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntiemeticdrugs = "ct_default-119";
			$GASTROINTESTINALAntiemeticdrugs_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntiemeticdrugs','Antiemetic drugs','Antiemetic drugs','medical drugs','$GASTROINTESTINALAntiemeticdrugs_serial')";
			$res=$db->Execute($q);
			// 17.3 Antihaemorrhoidal drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntihaemorrhoidaldrugs = "ct_default-120";
			$GASTROINTESTINALAntihaemorrhoidaldrugs_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntihaemorrhoidaldrugs','Antihaemorrhoidal drugs','Antihaemorrhoidal drugs','medical drugs','$GASTROINTESTINALAntihaemorrhoidaldrugs_serial')";
			$res=$db->Execute($q);
			// 17.4 Anti-inflammatory drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntiinflammatorydrugs = "ct_default-121";
			$GASTROINTESTINALAntiinflammatorydrugs_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntiinflammatorydrugs','Anti-inflammatory drugs','Anti-inflammatory drugs','medical drugs','$GASTROINTESTINALAntiinflammatorydrugs_serial')";
			$res=$db->Execute($q);
			// 17.5 Antispasmodic drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntispasmodicdrugs = "ct_default-122";
			$GASTROINTESTINALAntispasmodicdrugs_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntispasmodicdrugs','Antispasmodic drugs','Antispasmodic drugs','medical drugs','$GASTROINTESTINALAntispasmodicdrugs_serial')";
			$res=$db->Execute($q);
			// 17.6 Laxatives- sub catalogue - level 2 
			$GASTROINTESTINALLaxatives = "ct_default-123";
			$GASTROINTESTINALLaxatives_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALLaxatives','Laxatives','Laxatives','medical drugs','$GASTROINTESTINALLaxatives_serial')";
			$res=$db->Execute($q);
			// 17.7.1 Oral rehydration- sub catalogue - level 2 
			$GASTROINTESTINALOralrehydration = "ct_default-124";
			$GASTROINTESTINALOralrehydration_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALOralrehydration','Oral rehydration','Oral rehydration','medical drugs','$GASTROINTESTINALOralrehydration_serial')";
			$res=$db->Execute($q);
			// 17.7.2 Antidiarrhoeal (symptomatic) drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntidiarrhoealsymptomaticdrugs = "ct_default-125";
			$GASTROINTESTINALAntidiarrhoealsymptomaticdrugs_serial = shn_cs_generate_subcat_item_serial($GASTROINTESTINALDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntidiarrhoealsymptomaticdrugs','Antidiarrhoeal (symptomatic) drugs','Antidiarrhoeal (symptomatic) drugs','medical drugs','$GASTROINTESTINALAntidiarrhoealsymptomaticdrugs_serial')";
			$res=$db->Execute($q);

		//18. HORMONES, OTHER ENDOCRINE DRUGS AND CONTRACEPTIVES  - sub catalogue - level 1
		$HORMONESOTHERENDOCRINEDRUGS = "ct_default-126";
		$HORMONESOTHERENDOCRINEDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$HORMONESOTHERENDOCRINEDRUGS','HORMONES OTHER ENDOCRINE DRUGS AND CONTRACEPTIVES','HORMONES OTHER ENDOCRINE DRUGS AND CONTRACEPTIVES','medical drugs','$HORMONESOTHERENDOCRINEDRUGS_serial')";
		$res=$db->Execute($q);
			// 18.1 Adrenal hormones and synthetic substitutes- sub catalogue - level 2 
			$HORMONESAdrenalhormonesandsyntheticsubstitutes = "ct_default-127";
			$HORMONESAdrenalhormonesandsyntheticsubstitutes_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESAdrenalhormonesandsyntheticsubstitutes','Adrenal hormones and synthetic substitutes','Adrenal hormones and synthetic substitutes','medical drugs','$HORMONESAdrenalhormonesandsyntheticsubstitutes_serial')";
			$res=$db->Execute($q);
			// 18.2 Androgens- sub catalogue - level 2 
			$HORMONESAndrogens = "ct_default-128";
			$HORMONESAndrogens_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESAndrogens','Androgens','Androgens','medical drugs','$HORMONESAndrogens_serial')";
			$res=$db->Execute($q);
			// 18.3.1 Hormonal contraceptives- sub catalogue - level 2 
			$HORMONESHormonalcontraceptives = "ct_default-129";
			$HORMONESHormonalcontraceptives_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESHormonalcontraceptives','Hormonal contraceptives','Hormonal contraceptives','medical drugs','$HORMONESHormonalcontraceptives_serial')";
			$res=$db->Execute($q);
			// 18.3.2 Intrauterine devices- sub catalogue - level 2 
			$HORMONESIntrauterinedevices = "ct_default-130";
			$HORMONESIntrauterinedevices_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESIntrauterinedevices',' Intrauterine devices',' Intrauterine devices','medical drugs','$HORMONESIntrauterinedevices_serial')";
			$res=$db->Execute($q);
			// 18.3.3 Barrier methods- sub catalogue - level 2 
			$HORMONESBarriermethods = "ct_default-131";
			$HORMONESBarriermethods_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESBarriermethods','Barrier methods','Barrier methods','medical drugs','$HORMONESBarriermethods_serial')";
			$res=$db->Execute($q);
			// 18.4 Estrogens- sub catalogue - level 2 
			$HORMONESEstrogens = "ct_default-132";
			$HORMONESEstrogens_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESEstrogens','Estrogens','Estrogens','medical drugs','$HORMONESEstrogens_serial')";
			$res=$db->Execute($q);
			// 18.5  Insulins and other antidiabetic agents- sub catalogue - level 2 
			$HORMONESInsulinsandotherantidiabeticagents = "ct_default-133";
			$HORMONESInsulinsandotherantidiabeticagents_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESInsulinsandotherantidiabeticagents','Insulins and other antidiabetic agents',' Insulins and other antidiabetic agents','medical drugs','$HORMONESInsulinsandotherantidiabeticagents_serial')";
			$res=$db->Execute($q);
			// 18.6 Ovulation inducers- sub catalogue - level 2 
			$HORMONESOvulationinducers = "ct_default-134";
			$HORMONESOvulationinducers_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESOvulationinducers','Ovulation inducers','Ovulation inducers','medical drugs','$HORMONESOvulationinducers_serial')";
			$res=$db->Execute($q);
			// 18.7 Progestogens- sub catalogue - level 2 
			$HORMONESProgestogens = "ct_default-135";
			$HORMONESProgestogens_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESProgestogens','Progestogens','Progestogens','medical drugs','$HORMONESProgestogens_serial')";
			$res=$db->Execute($q);
			// 18.8  Thyroid hormones and antithyroid drugs- sub catalogue - level 2 
			$HORMONESThyroidhormonesandantithyroiddrugs = "ct_default-136";
			$HORMONESThyroidhormonesandantithyroiddrugs_serial = shn_cs_generate_subcat_item_serial($HORMONESOTHERENDOCRINEDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESThyroidhormonesandantithyroiddrugs','Thyroid hormones and antithyroid drugs','Thyroid hormones and antithyroid drugs','medical drugs','$HORMONESThyroidhormonesandantithyroiddrugs_serial')";
			$res=$db->Execute($q);

		//19. IMMUNOLOGICALS  - sub catalogue - level 1
		$IMMUNOLOGICALS = "ct_default-137";
		$IMMUNOLOGICALS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$IMMUNOLOGICALS','IMMUNOLOGICALS','IMMUNOLOGICALS','medical drugs','$IMMUNOLOGICALS_serial')";
		$res=$db->Execute($q);
			// 19.1 Diagnostic agents- sub catalogue - level 2 
			$IMMUNOLOGICALSDiagnosticagents = "ct_default-138";
			$IMMUNOLOGICALSDiagnosticagents_serial = shn_cs_generate_subcat_item_serial($IMMUNOLOGICALS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSDiagnosticagents','Diagnostic agents','Diagnostic agents','medical drugs','$IMMUNOLOGICALSDiagnosticagents_serial')";
			$res=$db->Execute($q);
			// 19.2 Sera and immunoglobulins- sub catalogue - level 2 
			$IMMUNOLOGICALSSeraandimmunoglobulins = "ct_default-139";
			$IMMUNOLOGICALSSeraandimmunoglobulins_serial = shn_cs_generate_subcat_item_serial($IMMUNOLOGICALS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSSeraandimmunoglobulins','Sera and immunoglobulins','Sera and immunoglobulins','medical drugs','$IMMUNOLOGICALSSeraandimmunoglobulins_serial')";
			$res=$db->Execute($q);
			// 19.3.1  Vaccines for universal immunization- sub catalogue - level 2 
			$IMMUNOLOGICALSVaccinesforuniversalimmunization = "ct_default-140";
			$IMMUNOLOGICALSVaccinesforuniversalimmunization_serial = shn_cs_generate_subcat_item_serial($IMMUNOLOGICALS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSVaccinesforuniversalimmunization','Vaccines for universal immunization','Vaccines for universal immunization','medical drugs','$IMMUNOLOGICALSVaccinesforuniversalimmunization_serial')";
			$res=$db->Execute($q);
			// 19.3.2 Vaccines for specific groups of individuals- sub catalogue - level 2 
			$IMMUNOLOGICALSVaccinesforspecificgroupsofindividuals = "ct_default-141";
			$IMMUNOLOGICALSVaccinesforspecificgroupsofindividuals_serial = shn_cs_generate_subcat_item_serial($IMMUNOLOGICALS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSVaccinesforspecificgroupsofindividuals','Vaccines for specific groups of individuals','Vaccines for specific groups of individuals','medical drugs','$IMMUNOLOGICALSVaccinesforspecificgroupsofindividuals_serial')";
			$res=$db->Execute($q);
		
		//20. MUSCLE RELAXANTS (PERIPHERALLY ACTING) AND CHOLINESTERASE INHIBITORS  - sub catalogue - level 1
		$MUSCLERELAXANTS  = "ct_default-142";
		$MUSCLERELAXANTS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$MUSCLERELAXANTS','MUSCLE RELAXANTS PERIPHERALLY ACTING AND CHOLINESTERASE INHIBITORS','MUSCLE RELAXANTS PERIPHERALLY ACTING AND CHOLINESTERASE INHIBITORS','medical drugs','$MUSCLERELAXANTS_serial')";
		$res=$db->Execute($q);

		//21. OPHTHALMOLOGICAL PREPARATIONS  - sub catalogue - level 1
		$OPHTHALMOLOGICALPREPARATIONS = "ct_default-143";
		$OPHTHALMOLOGICALPREPARATIONS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$OPHTHALMOLOGICALPREPARATIONS','OPHTHALMOLOGICAL PREPARATIONS','OPHTHALMOLOGICAL PREPARATIONS','medical drugs','$OPHTHALMOLOGICALPREPARATIONS_serial')";
		$res=$db->Execute($q);
			// 21.1 Anti-infective agents- sub catalogue - level 2 
			$OPHTHALMOLOGICALAntiinfectiveagents = "ct_default-144";
			$OPHTHALMOLOGICALAntiinfectiveagents_serial = shn_cs_generate_subcat_item_serial($OPHTHALMOLOGICALPREPARATIONS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALAntiinfectiveagents','Anti infective agents','Anti infective agents','medical drugs','$OPHTHALMOLOGICALAntiinfectiveagents_serial')";
			$res=$db->Execute($q);
			// 21.2 Anti-inflammatory agents- sub catalogue - level 2 
			$OPHTHALMOLOGICALAntiinflammatoryagents = "ct_default-145";
			$OPHTHALMOLOGICALAntiinflammatoryagents_serial = shn_cs_generate_subcat_item_serial($OPHTHALMOLOGICALPREPARATIONS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALAntiinflammatoryagents','Anti inflammatory agents','Anti inflammatory agents','medical drugs','$OPHTHALMOLOGICALAntiinflammatoryagents_serial')";
			$res=$db->Execute($q);
			// 21.3 Local anaesthetics- sub catalogue - level 2 
			$OPHTHALMOLOGICALLocalanaesthetics = "ct_default-146";
			$OPHTHALMOLOGICALLocalanaesthetics_serial = shn_cs_generate_subcat_item_serial($OPHTHALMOLOGICALPREPARATIONS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALLocalanaesthetics','Local anaesthetics','Local anaesthetics','medical drugs','$OPHTHALMOLOGICALLocalanaesthetics_serial')";
			$res=$db->Execute($q);
			// 21.4 Miotics and antiglaucoma drugs - sub catalogue - level 2 
			$OPHTHALMOLOGICALMioticsandantiglaucomadrugs = "ct_default-147";
			$OPHTHALMOLOGICALMioticsandantiglaucomadrugs_serial = shn_cs_generate_subcat_item_serial($OPHTHALMOLOGICALPREPARATIONS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALMioticsandantiglaucomadrugs','Miotics and antiglaucoma drugs','Miotics and antiglaucoma drugs','medical drugs','$OPHTHALMOLOGICALMioticsandantiglaucomadrugs_serial')";
			$res=$db->Execute($q);
			// 21.5 Mydriatics - sub catalogue - level 2 
			$OPHTHALMOLOGICALMydriatics = "ct_default-148";
			$OPHTHALMOLOGICALMydriatics_serial = shn_cs_generate_subcat_item_serial($OPHTHALMOLOGICALPREPARATIONS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALMydriatics','Mydriatics','Mydriatics','medical drugs','$OPHTHALMOLOGICALMydriatics_serial')";
			$res=$db->Execute($q);

		//22. OXYTOCICS AND ANTIOXYTOCICS  - sub catalogue - level 1
		$OXYTOCICSANDANTIOXYTOCICS = "ct_default-149";
		$OXYTOCICSANDANTIOXYTOCICS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$OXYTOCICSANDANTIOXYTOCICS','OXYTOCICS AND ANTIOXYTOCICS','OXYTOCICS AND ANTIOXYTOCICS','medical drugs','$OXYTOCICSANDANTIOXYTOCICS_serial')";
		$res=$db->Execute($q);
			// 22.1 Oxytocics - sub catalogue - level 2 
			$OXYTOCICSOxytocics = "ct_default-150";
			$OXYTOCICSOxytocics_serial = shn_cs_generate_subcat_item_serial($OXYTOCICSANDANTIOXYTOCICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OXYTOCICSANDANTIOXYTOCICS','$OXYTOCICSOxytocics','Oxytocics','Oxytocics','medical drugs','$OXYTOCICSOxytocics_serial')";
			$res=$db->Execute($q);
			// 22.2 Antiocytocics - sub catalogue - level 2 
			$OXYTOCICSAntiocytocics = "ct_default-151";
			$OXYTOCICSAntiocytocics_serial = shn_cs_generate_subcat_item_serial($OXYTOCICSANDANTIOXYTOCICS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$OXYTOCICSANDANTIOXYTOCICS','$OXYTOCICSAntiocytocics','Antiocytocics','Antiocytocics','medical drugs','$OXYTOCICSAntiocytocics_serial')";
			$res=$db->Execute($q);

		//23. PERITONEAL DIALYSIS SOLUTION  - sub catalogue - level 1
		$PERITONEALDIALYSISSOLUTION = "ct_default-152";
		$PERITONEALDIALYSISSOLUTION_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$PERITONEALDIALYSISSOLUTION','PERITONEAL DIALYSIS SOLUTION','PERITONEAL DIALYSIS SOLUTION','medical drugs','$PERITONEALDIALYSISSOLUTION_serial')";
		$res=$db->Execute($q);

		//24. PSYCHOTHERAPEUTIC DRUGS  - sub catalogue - level 1
		$PSYCHOTHERAPEUTICDRUGS = "ct_default-153";
		$PSYCHOTHERAPEUTICDRUGS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$PSYCHOTHERAPEUTICDRUGS','PSYCHOTHERAPEUTIC DRUGS','PSYCHOTHERAPEUTIC DRUGS','medical drugs','$PSYCHOTHERAPEUTICDRUGS_serial')";
		$res=$db->Execute($q);

			// 24.1 Drugs used in psychotic disorders - sub catalogue - level 2 
			$PSYCHODrugsusedinpsychoticdisorders = "ct_default-154";
			$PSYCHODrugsusedinpsychoticdisorders_serial = shn_cs_generate_subcat_item_serial($PSYCHOTHERAPEUTICDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedinpsychoticdisorders','Drugs used in psychotic disorders','Drugs used in psychotic disorders','medical drugs','$PSYCHODrugsusedinpsychoticdisorders_serial')";
			$res=$db->Execute($q);

			// 24.2.1 Drugs used in depressive disorders - sub catalogue - level 2 
			$PSYCHODrugsusedindepressivedisorders = "ct_default-155";
			$PSYCHODrugsusedindepressivedisorders_serial = shn_cs_generate_subcat_item_serial($PSYCHOTHERAPEUTICDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedindepressivedisorders','Drugs used in depressive disorders','Drugs used in depressive disorders','medical drugs','$PSYCHODrugsusedindepressivedisorders_serial')";
			$res=$db->Execute($q);

			// 24.2.2 Drugs used in bipolar disorders - sub catalogue - level 2 
			$PSYCHODrugsusedinbipolardisorders = "ct_default-156";
			$PSYCHODrugsusedinbipolardisorders_serial = shn_cs_generate_subcat_item_serial($PSYCHOTHERAPEUTICDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedinbipolardisorders','Drugs used in bipolar disorders','Drugs used in bipolar disorders','medical drugs','$PSYCHODrugsusedinbipolardisorders_serial')";
			$res=$db->Execute($q);

			// 24.3 Drugs used in generalized anxiety and sleep disorders - sub catalogue - level 2 
			$PSYCHODrugsusedingeneralizedanxietyandsleepdisorders = "ct_default-157";
			$PSYCHODrugsusedingeneralizedanxietyandsleepdisorders_serial = shn_cs_generate_subcat_item_serial($PSYCHOTHERAPEUTICDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedingeneralizedanxietyandsleepdisorders','Drugs used in generalized anxiety and sleep disorders','Drugs used in generalized anxiety and sleep disorders','medical drugs','$PSYCHODrugsusedingeneralizedanxietyandsleepdisorders_serial')";
			$res=$db->Execute($q);
			// 24.4 Drugs used for obsessive compulsive disorders and panic attacks - sub catalogue - level 2 
			$PSYCHODrugsusedforobsessivecompulsivedisordersandpanicattacks = "ct_default-158";
			$PSYCHODrugsusedforobsessivecompulsivedisordersandpanicattacks_serial = shn_cs_generate_subcat_item_serial($PSYCHOTHERAPEUTICDRUGS);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedforobsessivecompulsivedisordersandpanicattacks','Drugs used for obsessive compulsive disorders and panic attacks','Drugs used for obsessive compulsive disorders and panic attacks','medical drugs','$PSYCHODrugsusedforobsessivecompulsivedisordersandpanicattacks_serial')";
			$res=$db->Execute($q);

		//25. DRUGS ACTING ON THE RESPIRATORY TRACT  - sub catalogue - level 1
		$DRUGSACTINGONTHERESPIRATORYTRACT = "ct_default-159";
		$DRUGSACTINGONTHERESPIRATORYTRACT_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$DRUGSACTINGONTHERESPIRATORYTRACT','DRUGS ACTING ON THE RESPIRATORY TRACT','DRUGS ACTING ON THE RESPIRATORY TRACT','medical drugs','$DRUGSACTINGONTHERESPIRATORYTRACT_serial')";
		$res=$db->Execute($q);
			// 25.1 Antiasthmatic drugs - sub catalogue - level 2 
			$RESPIRATORYAntiasthmaticdrugs = "ct_default-160";
			$RESPIRATORYAntiasthmaticdrugs_serial = shn_cs_generate_subcat_item_serial($DRUGSACTINGONTHERESPIRATORYTRACT);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DRUGSACTINGONTHERESPIRATORYTRACT','$RESPIRATORYAntiasthmaticdrugs','Antiasthmatic drugs','Antiasthmatic drugs','medical drugs','$RESPIRATORYAntiasthmaticdrugs_serial')";
			// 25.2 Antitussives - sub catalogue - level 2 
			$RESPIRATORYAntitussives = "ct_default-161";
			$RESPIRATORYAntitussives_serial = shn_cs_generate_subcat_item_serial($DRUGSACTINGONTHERESPIRATORYTRACT);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$DRUGSACTINGONTHERESPIRATORYTRACT','$RESPIRATORYAntitussives','Antitussives','Antitussives','medical drugs','$RESPIRATORYAntitussives_serial')";
			$res=$db->Execute($q);

		//26. SOLUTIONS CORRECTING WATER, ELECTROLYTE AND ACID-BASE DISTURBANCES  - sub catalogue - level 1
		$SOLUTIONSCORRECTINGWATERELECTROLYTE  = "ct_default-162";
		$SOLUTIONSCORRECTINGWATERELECTROLYTE_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$SOLUTIONSCORRECTINGWATERELECTROLYTE','SOLUTIONS CORRECTING WATER ELECTROLYTE AND ACID-BASE DISTURBANCES','SOLUTIONS CORRECTING WATER ELECTROLYTE AND ACID BASE DISTURBANCES','medical drugs','$SOLUTIONSCORRECTINGWATERELECTROLYTE_serial')";
		$res=$db->Execute($q);
			// 26.1 Oral - sub catalogue - level 2 
			$SOLUTIONSOral = "ct_default-163";
			$SOLUTIONSOral_serial = shn_cs_generate_subcat_item_serial($SOLUTIONSCORRECTINGWATERELECTROLYTE);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$SOLUTIONSCORRECTINGWATERELECTROLYTE','$SOLUTIONSOral','Oral','Oral','medical drugs','$SOLUTIONSOral_serial')";
			$res=$db->Execute($q);
			// 26.1 Parenteral - sub catalogue - level 2 
			$SOLUTIONSOParenteral = "ct_default-164";
			$SOLUTIONSOParenteral_serial = shn_cs_generate_subcat_item_serial($SOLUTIONSCORRECTINGWATERELECTROLYTE);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$SOLUTIONSCORRECTINGWATERELECTROLYTE','$SOLUTIONSOParenteral','Parenteral','Parenteral','medical drugs','$SOLUTIONSOParenteral_serial')";
			$res=$db->Execute($q);
			// 26.1 Miscellaneous - sub catalogue - level 2 
			$SOLUTIONSOMiscellaneous = "ct_default-165";
			$SOLUTIONSOMiscellaneous_serial = shn_cs_generate_subcat_item_serial($SOLUTIONSCORRECTINGWATERELECTROLYTE);
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$SOLUTIONSCORRECTINGWATERELECTROLYTE','$SOLUTIONSOMiscellaneous','Miscellaneous','Miscellaneous','medical drugs','$SOLUTIONSOMiscellaneous_serial')";
			$res=$db->Execute($q);

		//27. VITAMINS AND MINERALS  - sub catalogue - level 1
		$VITAMINSANDMINERALS  = "ct_default-166";
		$VITAMINSANDMINERALS_serial = shn_cs_generate_subcat_item_serial($medicaldrug);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('$medicaldrug','$VITAMINSANDMINERALS','VITAMINS AND MINERALS','VITAMINS AND MINERALS','medical drugs','$VITAMINSANDMINERALS_serial')";
		$res=$db->Execute($q);
		
		
		$currency = "ct_default-167";
	$currency_serial = shn_cs_generate_maincat_serial();
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) values('0','$currency','Financial','Financial','Financial','$currency_serial')";
	$res=$db->Execute($q);
			// -sub catalogue-1.1
		
		$money = "ct_default-168";
		$money_serial = shn_cs_generate_subcat_item_serial($currency);
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword,serial) values('$currency','$money','Money','Money','1','money','$money_serial')";
		$res=$db->Execute($q);
		
		$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$money','$rs')";
					$res=$db->Execute($q);

}

