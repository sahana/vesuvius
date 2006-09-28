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

		$piece=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$piece','Piece','0',1)";
		$res=$db->Execute($query);

		$kit=shn_create_uuid("unit");
		$query="insert into ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) values('$miscellaneous','$kit','Kit','0',1)";
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

	// INSERT MAIN CATALOGUES & SUB CATALOGUE TO THE DATABASE
	//data 1
		// -food - main catalogue
	$food = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$food','Food and Nutrition','Food','food')";
	$res=$db->Execute($q);
			// -sub catalogue
		
		$dryfood = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$food','$dryfood','Dry Food','Dry Food','food')";
		$res=$db->Execute($q);

			// -item1
			$rice = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$dryfood','$rice','Rice','Rice','1','food')";
			$res=$db->Execute($q);
						// -unit/units that item use -(kg)
					$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$rice','$kg')";
					$res=$db->Execute($q);

			// -item2
			$sugar = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$dryfood','$sugar','Sugar','Sugar','1','food')";
			$res=$db->Execute($q);
						// -unit/units that item use -(kg)
					$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$sugar','$kg')";
					$res=$db->Execute($q);


	//data
	// -non food items - main catalogue
	$nonfood = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$nonfood','Non Food Items','Non Food Items','non food')";
	$res=$db->Execute($q);

		// - clothing - sub catalogue
		$clothing = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$nonfood','$clothing','Clothing','Clothing','clothing')";
		$res=$db->Execute($q);

		// - clothing - sub catalogue
		$shelter = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$nonfood','$shelter','Shelter & Housing Supplies','Shelter & Housing Supplies','Shelter')";
		$res=$db->Execute($q);

		// - Cooking Supplies - sub catalogue
		$shelter = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$nonfood','$shelter','Cooking Supplies','Cooking Supplies','Cooking')";
		$res=$db->Execute($q);

			// -blanket - item
			$blanket = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$nonfood','$blanket','Blankets','Blankets','1','blankets')";
			$res=$db->Execute($q);
					// -unit/units that blanket uses -(piece)
				$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$blanket','$piece')";
				$res=$db->Execute($q);


	// - helth kit - main catalogue ----------------------------------------------------------------------------------------------------------------------------------------
	$HealthKits = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$HealthKits','Health Kits','Health Kits','health kits')";
	$res=$db->Execute($q);

		// - Burn Dressing Kits - sub catalogue
		$BurnDressingKits = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$BurnDressingKits','Burn Dressing Kits','Burn Dressing Kits','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$BurnDressingKits','$kit')";
			$res=$db->Execute($q);

		// - Clean Delivery Kits - sub catalogue
		$CleanDeliveryKits = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$CleanDeliveryKits','Clean Delivery Kits','Clean Delivery Kits','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$CleanDeliveryKits','$kit')";
			$res=$db->Execute($q);

		// - Diarrhoea Kits - sub catalogue
		$DiarrhoeaKits = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$DiarrhoeaKits','Diarrhoea Kits','Diarrhoea Kits','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$DiarrhoeaKits','$kit')";
			$res=$db->Execute($q);

		// - Emergency Health Kits - sub catalogue
		$EmergencyHealthKits = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$EmergencyHealthKits','Emergency Health Kits','Emergency Health Kits','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$EmergencyHealthKits','$kit')";
			$res=$db->Execute($q);

		// - EMOC Kits - sub catalogue
		$EMOCKits = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$EMOCKits','EMOC Kits','EMOC Kits','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$EMOCKits','$kit')";
			$res=$db->Execute($q);

		// - Measles Vaccines - sub catalogue
		$MeaslesVaccines = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$MeaslesVaccines','Measles Vaccines','Measles Vaccines','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$MeaslesVaccines','$kit')";
			$res=$db->Execute($q);

		// - Trauma Kits - sub catalogue
		$TraumaKits = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,final_flag,keyword) values('$HealthKits','$TraumaKits','Trauma Kits','Trauma Kits','1','kits')";
		$res=$db->Execute($q);

			$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$TraumaKits','$kit')";
			$res=$db->Execute($q);
         //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// - Medical Equipment - main catalogue --------------------------------------------------------------------------------------------------------------------
	$MedicalEquipment = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$MedicalEquipment','Medical Equipment','Medical Equipment','medical equipment')";
	$res=$db->Execute($q);

		// - Anaesthesia Equipment - sub catalogue
		$AnaesthesiaEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$AnaesthesiaEquipment','Anaesthesia Equipment','Anaesthesia Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Cold Chain Equipment - sub catalogue
		$ColdChainEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$ColdChainEquipment','Cold Chain Equipment','Cold Chain Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Diagnostic Equipment - sub catalogue
		$DiagnosticEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$DiagnosticEquipment','Diagnostic Equipment','Diagnostic Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Exercise Equipment - sub catalogue
		$ExerciseEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$ExerciseEquipment','Exercise Equipment ','Exercise Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Hospital Equipment - sub catalogue
		$HospitalEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$HospitalEquipment','Hospital Equipment','Hospital Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Medical Utensils - sub catalogue
		$MedicalUtensils = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$MedicalUtensils','Medical Utensils','Medical Utensils','medical equipment')";
		$res=$db->Execute($q);

		// - Resuscitation Equipment - sub catalogue
		$ResuscitationEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$ResuscitationEquipment','Resuscitation Equipment','Resuscitation Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Sterilization Equipment - sub catalogue
		$SterilizationEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$SterilizationEquipment','Sterilization Equipment','Sterilization Equipment','medical equipment')";
		$res=$db->Execute($q);

		// - Surgical Equipment - sub catalogue
		$SurgicalEquipment = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$MedicalEquipment','$SurgicalEquipment','Surgical Equipment','Surgical Equipment','medical equipment')";
		$res=$db->Execute($q);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Medical drugs - main catalogue ------------------------------------------------------------------------------------------------------------------------------
	$medicaldrug = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('0','$medicaldrug','Medical Drugs','Medical Drugs','medical drugs')";
	$res=$db->Execute($q);
		// ANAESTHETICS- sub catalogue - level 1
		$ANAESTHETICS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANAESTHETICS','ANAESTHETICS','ANAESTHETICS','medical drugs')";
		$res=$db->Execute($q);
			// General Anaesthetics & Oxygen- sub catalogue - level 2
			$GeneralAnaestheticsOxygen = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANAESTHETICS','$GeneralAnaestheticsOxygen','General Anaesthetics & Oxygen','General Anaesthetics & Oxygen','medical drugs')";
			$res=$db->Execute($q);
			// Local Anaesthetics- sub catalogue - level 2
			$LocalAnaesthetics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANAESTHETICS','$LocalAnaesthetics','Local Anaesthetics','Local Anaesthetics','medical drugs')";
			$res=$db->Execute($q);
			// Preoperative medication and sedation for short-term procedures- sub catalogue - level 2
			$Preoperativemedication = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANAESTHETICS','$Preoperativemedication','Preoperative medication and sedation for short-term procedures','Preoperative medication and sedation for short-term procedures','medical drugs')";
			$res=$db->Execute($q);

		// ANALGESICS- sub catalogue - level 1
		$ANALGESICS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANALGESICS','ANALGESICS','ANALGESICS, ANTIPYRETICS, NON-STEROIDAL ANTI-INFLAMMATORY DRUGS (NSAIDs), DRUGS USED TO TREAT GOUT AND DISEASE MODIFYING AGENTS IN RHEUMATOID DISORDERS (DMARDs)','medical drugs')";
		$res=$db->Execute($q);
			// Non-opioids and NSAIDs- sub catalogue - level 2
			$NonopioidsandNSAIDs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANALGESICS','$NonopioidsandNSAIDs','Non-opioids and NSAIDs','Non-opioids and NSAIDs','medical drugs')";
			// Opioid Analgesics- sub catalogue - level 2
			$OpioidAnalgesics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANALGESICS','$OpioidAnalgesics','Opioid Analgesics','Opioid Analgesics','medical drugs')";
			// Drugs used to treat gout- sub catalogue - level 2
			$Drugsusedtotreatgout = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANALGESICS','$Drugsusedtotreatgout','Drugs used to treat gout','Drugs used to treat gout','medical drugs')";
			// Disease modifying agents used in rheumatoid disorders (DMARDs) - sub catalogue - level 2
			$DMARDs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANALGESICS','$DMARDs','DMARD','Disease modifying agents used in rheumatoid disorders (DMARDs)','medical drugs')";

		// ANTIALLERGICS AND DRUGS USED IN ANAPHYLAXIS- sub catalogue - level 1
		$ANTIALLERGICSANAPHYLAXIS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTIALLERGICSANAPHYLAXIS','ANTIALLERGICS AND ANAPHYLAXIS','ANTIALLERGICS AND DRUGS USED IN ANAPHYLAXIS','medical drugs')";
		$res=$db->Execute($q);

		// ANTIDOTES AND OTHER SUBSTANCES USED IN POISONING- sub catalogue - level 1
		$ANTIDOTESUSEDINPOISONING = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTIDOTESUSEDINPOISONING','ANTIDOTES AND OTHER SUBSTANCES USED IN POISONING','ANTIDOTES AND OTHER SUBSTANCES USED IN POISONING','medical drugs')";
		$res=$db->Execute($q);
			// 4.1 Non-specific- sub catalogue - level 2 
			$Nonspecific = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIDOTESUSEDINPOISONING','$Nonspecific','Non-specific','Non-specific','medical drugs')";
			// 4.2 Specific- sub catalogue - level 2
			$Specific = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIDOTESUSEDINPOISONING','$Specific','Specific','Specific','medical drugs')";

		// 5. ANTICONVULSANTS/ANTIEPILEPTICS- sub catalogue - level 1
		$ANTICONVULSANTSANTIEPILEPTICS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTICONVULSANTSANTIEPILEPTICS','ANTICONVULSANTS/ANTIEPILEPTICS','ANTICONVULSANTS/ANTIEPILEPTICS','medical drugs')";
		$res=$db->Execute($q);

		// 6. ANTI-INFECTIVE DRUGS - sub catalogue - level 1
		$ANTIINFECTIVEDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTIINFECTIVEDRUGS','ANTI-INFECTIVE DRUGS','ANTI-INFECTIVE DRUGS','medical drugs')";
		$res=$db->Execute($q);
			// 6.1.1 Intestinal anthelminthics- sub catalogue - level 2 
			$Intestinalanthelminthics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Intestinalanthelminthics','Intestinal anthelminthics','Intestinal anthelminthics','medical drugs')";
			$res=$db->Execute($q);
			// 6.1.2 Antifilarials- sub catalogue - level 2 
			$Antifilarials = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antifilarials','Antifilarials','Antifilarials','medical drugs')";
			$res=$db->Execute($q);
			// 6.1.3 Antischistosomals and anti-trematode drugs- sub catalogue - level 2 
			$Antischistosomalsandantitrematodedrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antischistosomalsandantitrematodedrugs','Antischistosomals and anti-trematode drugs','Antischistosomals and anti-trematode drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.2 Antibacterials- sub catalogue - level 2 
			$Antibacterials = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antibacterials','Antibacterials','Antibacterials','medical drugs')";
			$res=$db->Execute($q);
			// 6.2.1 Beta lactam drugs- sub catalogue - level 2 
			$Betalactamdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Betalactamdrugs','Beta lactam drugs','Beta lactam drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.2.2 Other antibacterials- sub catalogue - level 2 
			$Otherantibacterials = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Otherantibacterials','Other antibacterials','Other antibacterials','medical drugs')";
			$res=$db->Execute($q);
			// 6.2.3 Antileprosy drugs- sub catalogue - level 2 
			$Antileprosydrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antileprosydrugs','Antileprosy drugs','Antileprosy drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.2.4 Antituberculosis drugs- sub catalogue - level 2 
			$Antituberculosisdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antituberculosisdrugs','Antituberculosis drugs','Antituberculosis drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.3 Antifungal drugs- sub catalogue - level 2 
			$Antifungaldrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antifungaldrugs','Antifungal drugs','Antifungal drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.4.1 Antiherpes- sub catalogue - level 2 
			$Antiherpes = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antiherpes','Antiherpes','Antiherpes','medical drugs')";
			$res=$db->Execute($q);
			// 6.4.2 Antiretrovirals - sub catalogue - level 2 
			$Antiretrovirals = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antiretrovirals','Antiretrovirals','Antiretrovirals','medical drugs')";
			$res=$db->Execute($q);
			// 6.5.1 Antiamoebic and antigiardiasis drugs - sub catalogue - level 2 
			$Antiamoebicandantigiardiasisdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antiamoebicandantigiardiasisdrugs','Antiamoebic and antigiardiasis drugs','Antiamoebic and antigiardiasis drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.5.2 Antileishmaniasis drugs - sub catalogue - level 2 
			$Antileishmaniasisdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antileishmaniasisdrugs','Antileishmaniasis drugs','Antileishmaniasis drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.5.3 Antimalarial drugs - sub catalogue - level 2 
			$Antimalarialdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antimalarialdrugs','Antimalarial drugs','Antimalarial drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.5.4 Anti-pneumocystosis and anti-toxoplasmosis drugs - sub catalogue - level 2 
			$Antipneumocystosisandantitoxoplasmosisdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antipneumocystosisandantitoxoplasmosisdrugs','Anti-pneumocystosis and anti-toxoplasmosis drugs','Anti-pneumocystosis and anti-toxoplasmosis drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.5.5 Antitrypanosomal drugs - sub catalogue - level 2 
			$Antitrypanosomaldrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Antitrypanosomaldrugs','Antitrypanosomal drugs','Antitrypanosomal drugs','medical drugs')";
			$res=$db->Execute($q);
			// 6.6 Insect repellents - sub catalogue - level 2 
			$Insectrepellents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIINFECTIVEDRUGS','$Insectrepellents','Insect repellents','Insect repellents','medical drugs')";
			$res=$db->Execute($q);

		// 7. ANTIMIGRAINE DRUGS - sub catalogue - level 1
		$ANTIMIGRAINEDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTIMIGRAINEDRUGS','ANTIMIGRAINE DRUGS','ANTIMIGRAINE DRUGS','medical drugs')";
		$res=$db->Execute($q);
			// 7.1  For treatment of acute attack- sub catalogue - level 2 
			$Fortreatmentofacuteattack = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIMIGRAINEDRUGS','$Fortreatmentofacuteattack',' For treatment of acute attack',' For treatment of acute attack','medical drugs')";
			$res=$db->Execute($q);
			// 7.2 For prophylaxis - sub catalogue - level 2 
			$Forprophylaxis = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTIMIGRAINEDRUGS','$Forprophylaxis','  For prophylaxis',' For prophylaxis','medical drugs')";
			$res=$db->Execute($q);

		// 8. ANTINEOPLASTIC, IMMUNOSUPPRESSIVES AND DRUGS USED IN PALLIATIVE CARE - sub catalogue - level 1
		$ANTINEOPLASTICIMMUNOSUPPRESSIVES = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTINEOPLASTICIMMUNOSUPPRESSIVES','ANTINEOPLASTIC IMMUNOSUPPRESSIVES AND DRUGS USED IN PALLIATIVE CARE','ANTINEOPLASTIC IMMUNOSUPPRESSIVES AND DRUGS USED IN PALLIATIVE CARE','medical drugs')";
		$res=$db->Execute($q);
			// 8.1  Immunosuppressive drugs- sub catalogue - level 2 
			$Immunosuppressivedrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Immunosuppressivedrugs','Immunosuppressive drugs','Immunosuppressive drugs','medical drugs')";
			$res=$db->Execute($q);
			// 8.2  Cytotoxic drugs- sub catalogue - level 2 
			$Cytotoxicdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Cytotoxicdrugs','Cytotoxic drugs','Cytotoxic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 8.3  Hormones and antihormones- sub catalogue - level 2 
			$Hormonesandantihormones = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Hormonesandantihormones','Hormones and antihormones','Hormones and antihormones','medical drugs')";
			$res=$db->Execute($q);
			// 8.4 Drugs used in palliative care - sub catalogue - level 2 
			$Drugsusedinpalliativecare = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$ANTINEOPLASTICIMMUNOSUPPRESSIVES','$Drugsusedinpalliativecare','Drugs used in palliative care','Drugs used in palliative care','medical drugs')";
			$res=$db->Execute($q);

		// 9. ANTIPARKINSONIAN DRUGS - sub catalogue - level 1
		$ANTIPARKINSONIANDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$ANTIPARKINSONIANDRUGS','ANTIPARKINSONIAN DRUGS','ANTIPARKINSONIAN DRUGS','medical drugs')";
		$res=$db->Execute($q);

		//10. DRUGS AFFECTING THE BLOOD - sub catalogue - level 1
		$DRUGSAFFECTINGTHEBLOOD = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$DRUGSAFFECTINGTHEBLOOD','DRUGS AFFECTING THE BLOOD','DRUGS AFFECTING THE BLOOD','medical drugs')";
		$res=$db->Execute($q);
			// 10.1 Anti-anaemia drugs - sub catalogue - level 2 
			$Antianaemiadrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DRUGSAFFECTINGTHEBLOOD','$Antianaemiadrugs','Anti-anaemia drugs','Anti-anaemia drugs','medical drugs')";
			$res=$db->Execute($q);
			// 10.2 Drugs affecting coagulation - sub catalogue - level 2 
			$Drugsaffectingcoagulation = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DRUGSAFFECTINGTHEBLOOD','$Drugsaffectingcoagulation','Drugs affecting coagulation','Drugs affecting coagulation','medical drugs')";
			$res=$db->Execute($q);

		//11. BLOOD PRODUCTS AND PLASMA SUBSTITUTES - sub catalogue - level 1
		$BLOODPRODUCTSANDPLASMASUBSTITUTES = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$BLOODPRODUCTSANDPLASMASUBSTITUTES','BLOOD PRODUCTS AND PLASMA SUBSTITUTES','BLOOD PRODUCTS AND PLASMA SUBSTITUTES','medical drugs')";
		$res=$db->Execute($q);
			// 11.1 Plasma substitutes - sub catalogue - level 2 
			$Plasmasubstitutes = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$BLOODPRODUCTSANDPLASMASUBSTITUTES','$Plasmasubstitutes','Plasma substitutes','Plasma substitutes','medical drugs')";
			$res=$db->Execute($q);
			// 11.2 Plasma fractions for specific use - sub catalogue - level 2 
			$Plasmafractionsforspecificuse = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$BLOODPRODUCTSANDPLASMASUBSTITUTES','$Plasmafractionsforspecificuse','Plasma fractions for specific use','Plasma fractions for specific use','medical drugs')";
			$res=$db->Execute($q);

		//12. CARDIOVASCULAR DRUGS - sub catalogue - level 1
		$CARDIOVASCULARDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$CARDIOVASCULARDRUGS','CARDIOVASCULAR DRUGS','CARDIOVASCULAR DRUGS','medical drugs')";
		$res=$db->Execute($q);
			// 12.1 Antianginal drugs - sub catalogue - level 2 
			$Antianginaldrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$CARDIOVASCULARDRUGS','$Antianginaldrugs','Antianginal drugs','Antianginal drugs','medical drugs')";
			$res=$db->Execute($q);
			// 12.2 Antiarrhythmic drugs - sub catalogue - level 2 
			$Antiarrhythmicdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$CARDIOVASCULARDRUGS','$Antiarrhythmicdrugs','Antiarrhythmic drugs','Antiarrhythmic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 12.3 Antihypertensive drugs - sub catalogue - level 2 
			$Antihypertensivedrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$CARDIOVASCULARDRUGS','$Antihypertensivedrugs','Antihypertensive drugs','Antihypertensive drugs','medical drugs')";
			$res=$db->Execute($q);
			// 12.4 Drugs used in heart failure - sub catalogue - level 2 
			$Drugsusedinheartfailure = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$CARDIOVASCULARDRUGS','$Drugsusedinheartfailure','Drugs used in heart failure','Drugs used in heart failure','medical drugs')";
			$res=$db->Execute($q);
			// 12.5  Antithrombotic drugs - sub catalogue - level 2 
			$Antithromboticdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$CARDIOVASCULARDRUGS','$Antithromboticdrugs',' Antithrombotic drugs',' Antithrombotic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 12.6  Lipid-lowering agents - sub catalogue - level 2 
			$Lipidloweringagents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$CARDIOVASCULARDRUGS','$Lipidloweringagents','Lipid-lowering agents','Lipid-lowering agents','medical drugs')";
			$res=$db->Execute($q);

		//13. DERMATOLOGICAL DRUGS (topical)  - sub catalogue - level 1
		$DERMATOLOGICALDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$DERMATOLOGICALDRUGS','DERMATOLOGICAL DRUGS (topical) ','DERMATOLOGICAL DRUGS (topical) ','medical drugs')";
		$res=$db->Execute($q);
			// 13.1 Antifungal drugs - sub catalogue - level 2 
			$DERMATOAntifungaldrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATOAntifungaldrugs','Antifungal drugs','Antifungal drugs','medical drugs')";
			$res=$db->Execute($q);
			// 13.2 Anti-infective drugs - sub catalogue - level 2 
			$DERMATOAntiinfectivedrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATOAntiinfectivedrugs','Anti-infective drugs','Anti-infective drugs','medical drugs')";
			$res=$db->Execute($q);
			// 13.3 Anti-inflammatory and antipruritic drugs - sub catalogue - level 2 
			$DERMATOAntiinflammatoryandantipruriticdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATOAntiinflammatoryandantipruriticdrugs','Anti-inflammatory and antipruritic drugs','Anti-inflammatory and antipruritic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 13.4 Astringent drugs - sub catalogue - level 2 
			$DERMATOAstringentdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATOAstringentdrugs','Astringent drugs','Astringent drugs','medical drugs')";
			$res=$db->Execute($q);
			// 13.5 Drugs affecting skin differentiation and proliferation - sub catalogue - level 2 
			$DERMATODrugsaffectingskindifferentiationandproliferation = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATODrugsaffectingskindifferentiationandproliferation','Drugs affecting skin differentiation and proliferation','Drugs affecting skin differentiation and proliferation','medical drugs')";
			$res=$db->Execute($q);
			// 13.6 Scabicides and pediculicides - sub catalogue - level 2 
			$DERMATOScabicidesandpediculicides = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATOScabicidesandpediculicides','Scabicides and pediculicides','Scabicides and pediculicides','medical drugs')";
			$res=$db->Execute($q);
			// 13.7 Ultraviolet blocking agents - sub catalogue - level 2 
			$DERMATOUltravioletblockingagents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DERMATOLOGICALDRUGS','$DERMATOUltravioletblockingagents','Ultraviolet blocking agents','Ultraviolet blocking agents','medical drugs')";
			$res=$db->Execute($q);

		//14. DIAGNOSTIC AGENTS  - sub catalogue - level 1
		$DIAGNOSTICAGENTS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$DIAGNOSTICAGENTS','DIAGNOSTIC AGENTS ','DIAGNOSTIC AGENTS ','medical drugs')";
		$res=$db->Execute($q);
			// 14.1 Ophthalmic drugs - sub catalogue - level 2 
			$DIAGNOSTICOphthalmicdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DIAGNOSTICAGENTS','$DIAGNOSTICOphthalmicdrugs','Ophthalmic drugs','Ophthalmic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 14.2 Radiocontrast media - sub catalogue - level 2 
			$DIAGNOSTICORadiocontrastmedia = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DIAGNOSTICAGENTS','$DIAGNOSTICORadiocontrastmedia','Radiocontrast media','Radiocontrast media','medical drugs')";
			$res=$db->Execute($q);

		//15. DISINFECTANTS AND ANTISEPTICS  - sub catalogue - level 1
		$DISINFECTANTSANDANTISEPTICS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$DISINFECTANTSANDANTISEPTICS','DISINFECTANTS AND ANTISEPTICS ','DISINFECTANTS AND ANTISEPTICS ','medical drugs')";
		$res=$db->Execute($q);
			// 15.1 Antiseptics - sub catalogue - level 2 
			$DISINFECTAntiseptics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DISINFECTANTSANDANTISEPTICS','$DISINFECTAntiseptics','Ophthalmic drugs','Ophthalmic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 15.2 Disinfectants - sub catalogue - level 2 
			$DISINFECTDisinfectants = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DISINFECTANTSANDANTISEPTICS','$DISINFECTDisinfectants','Disinfectants','Disinfectants','medical drugs')";
			$res=$db->Execute($q);

		//16. DIURETICS  - sub catalogue - level 1
		$DIURETICS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$DIURETICS','DIURETICS','DIURETICS','medical drugs')";
		$res=$db->Execute($q);

		//17. GASTROINTESTINAL DRUGS  - sub catalogue - level 1
		$GASTROINTESTINALDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$GASTROINTESTINALDRUGS','GASTROINTESTINAL DRUGS','GASTROINTESTINAL DRUGS','medical drugs')";
		$res=$db->Execute($q);
			// 17.1 Antacids and other antiulcer drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntacidsandotherantiulcerdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntacidsandotherantiulcerdrugs','Antacids and other antiulcer drugs','Antacids and other antiulcer drugs','medical drugs')";
			$res=$db->Execute($q);
			// 17.2 Antiemetic drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntiemeticdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntiemeticdrugs','Antiemetic drugs','Antiemetic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 17.3 Antihaemorrhoidal drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntihaemorrhoidaldrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntihaemorrhoidaldrugs','Antihaemorrhoidal drugs','Antihaemorrhoidal drugs','medical drugs')";
			$res=$db->Execute($q);
			// 17.4 Anti-inflammatory drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntiinflammatorydrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntiinflammatorydrugs','Anti-inflammatory drugs','Anti-inflammatory drugs','medical drugs')";
			$res=$db->Execute($q);
			// 17.5 Antispasmodic drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntispasmodicdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntispasmodicdrugs','Antispasmodic drugs','Antispasmodic drugs','medical drugs')";
			$res=$db->Execute($q);
			// 17.6 Laxatives- sub catalogue - level 2 
			$GASTROINTESTINALLaxatives = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALLaxatives','Laxatives','Laxatives','medical drugs')";
			$res=$db->Execute($q);
			// 17.7.1 Oral rehydration- sub catalogue - level 2 
			$GASTROINTESTINALOralrehydration = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALOralrehydration','Oral rehydration','Oral rehydration','medical drugs')";
			$res=$db->Execute($q);
			// 17.7.2 Antidiarrhoeal (symptomatic) drugs- sub catalogue - level 2 
			$GASTROINTESTINALAntidiarrhoealsymptomaticdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$GASTROINTESTINALDRUGS','$GASTROINTESTINALAntidiarrhoealsymptomaticdrugs','Antidiarrhoeal (symptomatic) drugs','Antidiarrhoeal (symptomatic) drugs','medical drugs')";
			$res=$db->Execute($q);

		//18. HORMONES, OTHER ENDOCRINE DRUGS AND CONTRACEPTIVES  - sub catalogue - level 1
		$HORMONESOTHERENDOCRINEDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$HORMONESOTHERENDOCRINEDRUGS','HORMONES OTHER ENDOCRINE DRUGS AND CONTRACEPTIVES','HORMONES OTHER ENDOCRINE DRUGS AND CONTRACEPTIVES','medical drugs')";
		$res=$db->Execute($q);
			// 18.1 Adrenal hormones and synthetic substitutes- sub catalogue - level 2 
			$HORMONESAdrenalhormonesandsyntheticsubstitutes = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESAdrenalhormonesandsyntheticsubstitutes','Adrenal hormones and synthetic substitutes','Adrenal hormones and synthetic substitutes','medical drugs')";
			$res=$db->Execute($q);
			// 18.2 Androgens- sub catalogue - level 2 
			$HORMONESAndrogens = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESAndrogens','Androgens','Androgens','medical drugs')";
			$res=$db->Execute($q);
			// 18.3.1 Hormonal contraceptives- sub catalogue - level 2 
			$HORMONESHormonalcontraceptives = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESHormonalcontraceptives','Hormonal contraceptives','Hormonal contraceptives','medical drugs')";
			$res=$db->Execute($q);
			// 18.3.2 Intrauterine devices- sub catalogue - level 2 
			$HORMONESIntrauterinedevices = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESIntrauterinedevices',' Intrauterine devices',' Intrauterine devices','medical drugs')";
			$res=$db->Execute($q);
			// 18.3.3 Barrier methods- sub catalogue - level 2 
			$HORMONESBarriermethods = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESBarriermethods','Barrier methods','Barrier methods','medical drugs')";
			$res=$db->Execute($q);
			// 18.4 Estrogens- sub catalogue - level 2 
			$HORMONESEstrogens = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESEstrogens','Estrogens','Estrogens','medical drugs')";
			$res=$db->Execute($q);
			// 18.5  Insulins and other antidiabetic agents- sub catalogue - level 2 
			$HORMONESInsulinsandotherantidiabeticagents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESInsulinsandotherantidiabeticagents','Insulins and other antidiabetic agents',' Insulins and other antidiabetic agents','medical drugs')";
			$res=$db->Execute($q);
			// 18.6 Ovulation inducers- sub catalogue - level 2 
			$HORMONESOvulationinducers = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESOvulationinducers','Ovulation inducers','Ovulation inducers','medical drugs')";
			$res=$db->Execute($q);
			// 18.7 Progestogens- sub catalogue - level 2 
			$HORMONESProgestogens = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESProgestogens','Progestogens','Progestogens','medical drugs')";
			$res=$db->Execute($q);
			// 18.8  Thyroid hormones and antithyroid drugs- sub catalogue - level 2 
			$HORMONESThyroidhormonesandantithyroiddrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$HORMONESOTHERENDOCRINEDRUGS','$HORMONESThyroidhormonesandantithyroiddrugs','Thyroid hormones and antithyroid drugs','Thyroid hormones and antithyroid drugs','medical drugs')";
			$res=$db->Execute($q);

		//19. IMMUNOLOGICALS  - sub catalogue - level 1
		$IMMUNOLOGICALS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$IMMUNOLOGICALS','IMMUNOLOGICALS','IMMUNOLOGICALS','medical drugs')";
		$res=$db->Execute($q);
			// 19.1 Diagnostic agents- sub catalogue - level 2 
			$IMMUNOLOGICALSDiagnosticagents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSDiagnosticagents','Diagnostic agents','Diagnostic agents','medical drugs')";
			$res=$db->Execute($q);
			// 19.2 Sera and immunoglobulins- sub catalogue - level 2 
			$IMMUNOLOGICALSSeraandimmunoglobulins = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSSeraandimmunoglobulins','Sera and immunoglobulins','Sera and immunoglobulins','medical drugs')";
			$res=$db->Execute($q);
			// 19.3.1  Vaccines for universal immunization- sub catalogue - level 2 
			$IMMUNOLOGICALSVaccinesforuniversalimmunization = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSVaccinesforuniversalimmunization','Vaccines for universal immunization','Vaccines for universal immunization','medical drugs')";
			$res=$db->Execute($q);
			// 19.3.2 Vaccines for specific groups of individuals- sub catalogue - level 2 
			$IMMUNOLOGICALSVaccinesforspecificgroupsofindividuals = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$IMMUNOLOGICALS','$IMMUNOLOGICALSVaccinesforspecificgroupsofindividuals','Vaccines for specific groups of individuals','Vaccines for specific groups of individuals','medical drugs')";
			$res=$db->Execute($q);

		//20. MUSCLE RELAXANTS (PERIPHERALLY ACTING) AND CHOLINESTERASE INHIBITORS  - sub catalogue - level 1
		$MUSCLERELAXANTS  = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$MUSCLERELAXANTS','MUSCLE RELAXANTS PERIPHERALLY ACTING AND CHOLINESTERASE INHIBITORS','MUSCLE RELAXANTS PERIPHERALLY ACTING AND CHOLINESTERASE INHIBITORS','medical drugs')";
		$res=$db->Execute($q);

		//21. OPHTHALMOLOGICAL PREPARATIONS  - sub catalogue - level 1
		$OPHTHALMOLOGICALPREPARATIONS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$OPHTHALMOLOGICALPREPARATIONS','OPHTHALMOLOGICAL PREPARATIONS','OPHTHALMOLOGICAL PREPARATIONS','medical drugs')";
		$res=$db->Execute($q);
			// 21.1 Anti-infective agents- sub catalogue - level 2 
			$OPHTHALMOLOGICALAntiinfectiveagents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALAntiinfectiveagents','Anti infective agents','Anti infective agents','medical drugs')";
			$res=$db->Execute($q);
			// 21.2 Anti-inflammatory agents- sub catalogue - level 2 
			$OPHTHALMOLOGICALAntiinflammatoryagents = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALAntiinflammatoryagents','Anti inflammatory agents','Anti inflammatory agents','medical drugs')";
			$res=$db->Execute($q);
			// 21.3 Local anaesthetics- sub catalogue - level 2 
			$OPHTHALMOLOGICALLocalanaesthetics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALLocalanaesthetics','Local anaesthetics','Local anaesthetics','medical drugs')";
			$res=$db->Execute($q);
			// 21.4 Miotics and antiglaucoma drugs - sub catalogue - level 2 
			$OPHTHALMOLOGICALMioticsandantiglaucomadrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALMioticsandantiglaucomadrugs','Miotics and antiglaucoma drugs','Miotics and antiglaucoma drugs','medical drugs')";
			$res=$db->Execute($q);
			// 21.5 Mydriatics - sub catalogue - level 2 
			$OPHTHALMOLOGICALMydriatics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OPHTHALMOLOGICALPREPARATIONS','$OPHTHALMOLOGICALMydriatics','Mydriatics','Mydriatics','medical drugs')";
			$res=$db->Execute($q);

		//22. OXYTOCICS AND ANTIOXYTOCICS  - sub catalogue - level 1
		$OXYTOCICSANDANTIOXYTOCICS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$OXYTOCICSANDANTIOXYTOCICS','OXYTOCICS AND ANTIOXYTOCICS','OXYTOCICS AND ANTIOXYTOCICS','medical drugs')";
		$res=$db->Execute($q);
			// 22.1 Oxytocics - sub catalogue - level 2 
			$OXYTOCICSOxytocics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OXYTOCICSANDANTIOXYTOCICS','$OXYTOCICSOxytocics','Oxytocics','Oxytocics','medical drugs')";
			$res=$db->Execute($q);
			// 22.2 Antiocytocics - sub catalogue - level 2 
			$OXYTOCICSAntiocytocics = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$OXYTOCICSANDANTIOXYTOCICS','$OXYTOCICSAntiocytocics','Antiocytocics','Antiocytocics','medical drugs')";
			$res=$db->Execute($q);

		//23. PERITONEAL DIALYSIS SOLUTION  - sub catalogue - level 1
		$PERITONEALDIALYSISSOLUTION = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$PERITONEALDIALYSISSOLUTION','PERITONEAL DIALYSIS SOLUTION','PERITONEAL DIALYSIS SOLUTION','medical drugs')";
		$res=$db->Execute($q);

		//24. PSYCHOTHERAPEUTIC DRUGS  - sub catalogue - level 1
		$PSYCHOTHERAPEUTICDRUGS = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$PSYCHOTHERAPEUTICDRUGS','PSYCHOTHERAPEUTIC DRUGS','PSYCHOTHERAPEUTIC DRUGS','medical drugs')";
		$res=$db->Execute($q);
			// 24.1 Drugs used in psychotic disorders - sub catalogue - level 2 
			$PSYCHODrugsusedinpsychoticdisorders = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedinpsychoticdisorders','Drugs used in psychotic disorders','Drugs used in psychotic disorders','medical drugs')";
			$res=$db->Execute($q);
			// 24.2.1 Drugs used in depressive disorders - sub catalogue - level 2 
			$PSYCHODrugsusedindepressivedisorders = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedindepressivedisorders','Drugs used in depressive disorders','Drugs used in depressive disorders','medical drugs')";
			$res=$db->Execute($q);
			// 24.2.2 Drugs used in bipolar disorders - sub catalogue - level 2 
			$PSYCHODrugsusedinbipolardisorders = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedinbipolardisorders','Drugs used in bipolar disorders','Drugs used in bipolar disorders','medical drugs')";
			$res=$db->Execute($q);
			// 24.3 Drugs used in generalized anxiety and sleep disorders - sub catalogue - level 2 
			$PSYCHODrugsusedingeneralizedanxietyandsleepdisorders = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedingeneralizedanxietyandsleepdisorders','Drugs used in generalized anxiety and sleep disorders','Drugs used in generalized anxiety and sleep disorders','medical drugs')";
			$res=$db->Execute($q);
			// 24.4 Drugs used for obsessive compulsive disorders and panic attacks - sub catalogue - level 2 
			$PSYCHODrugsusedforobsessivecompulsivedisordersandpanicattacks = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$PSYCHOTHERAPEUTICDRUGS','$PSYCHODrugsusedforobsessivecompulsivedisordersandpanicattacks','Drugs used for obsessive compulsive disorders and panic attacks','Drugs used for obsessive compulsive disorders and panic attacks','medical drugs')";
			$res=$db->Execute($q);

		//25. DRUGS ACTING ON THE RESPIRATORY TRACT  - sub catalogue - level 1
		$DRUGSACTINGONTHERESPIRATORYTRACT = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$DRUGSACTINGONTHERESPIRATORYTRACT','DRUGS ACTING ON THE RESPIRATORY TRACT','DRUGS ACTING ON THE RESPIRATORY TRACT','medical drugs')";
		$res=$db->Execute($q);
			// 25.1 Antiasthmatic drugs - sub catalogue - level 2 
			$RESPIRATORYAntiasthmaticdrugs = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DRUGSACTINGONTHERESPIRATORYTRACT','$RESPIRATORYAntiasthmaticdrugs','Antiasthmatic drugs','Antiasthmatic drugs','medical drugs')";
			// 25.2 Antitussives - sub catalogue - level 2 
			$RESPIRATORYAntitussives = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$DRUGSACTINGONTHERESPIRATORYTRACT','$RESPIRATORYAntitussives','Antitussives','Antitussives','medical drugs')";
			$res=$db->Execute($q);

		//26. SOLUTIONS CORRECTING WATER, ELECTROLYTE AND ACID-BASE DISTURBANCES  - sub catalogue - level 1
		$SOLUTIONSCORRECTINGWATERELECTROLYTE  = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$SOLUTIONSCORRECTINGWATERELECTROLYTE','SOLUTIONS CORRECTING WATER ELECTROLYTE AND ACID-BASE DISTURBANCES','SOLUTIONS CORRECTING WATER ELECTROLYTE AND ACID BASE DISTURBANCES','medical drugs')";
		$res=$db->Execute($q);
			// 26.1 Oral - sub catalogue - level 2 
			$SOLUTIONSOral = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$SOLUTIONSCORRECTINGWATERELECTROLYTE','$SOLUTIONSOral','Oral','Oral','medical drugs')";
			$res=$db->Execute($q);
			// 26.1 Parenteral - sub catalogue - level 2 
			$SOLUTIONSOParenteral = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$SOLUTIONSCORRECTINGWATERELECTROLYTE','$SOLUTIONSOParenteral','Parenteral','Parenteral','medical drugs')";
			$res=$db->Execute($q);
			// 26.1 Miscellaneous - sub catalogue - level 2 
			$SOLUTIONSOMiscellaneous = shn_create_uuid("catalogue");
			$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$SOLUTIONSCORRECTINGWATERELECTROLYTE','$SOLUTIONSOMiscellaneous','Miscellaneous','Miscellaneous','medical drugs')";
			$res=$db->Execute($q);

		//27. VITAMINS AND MINERALS  - sub catalogue - level 1
		$VITAMINSANDMINERALS  = shn_create_uuid("catalogue");
		$q="insert into ct_catalogue (parentid,ct_uuid,name,description,keyword) values('$medicaldrug','$VITAMINSANDMINERALS','VITAMINS AND MINERALS','VITAMINS AND MINERALS','medical drugs')";
		$res=$db->Execute($q);

}
?>
