<?php

/**
 * 
 * This file represents the major data access functions of the DVR module
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
include $global['approot'] . "/inc/lib_paging.inc";

function _shn_dvr_add_group()
{
	global $conf;
	global $global;
    $db = $global['db'];
	include $global['approot'] . "/inc/lib_gis/gis_fns.inc";
	
//if($_SESSION['dvr']['group']['image']!=null)	
    shn_image_to_db_ex($_SESSION['dvr_add_group']['entry']['p_uuid'], $_SESSION['dvr']['group']['image'], $_SESSION['dvr']['group']['image_type'], $_SESSION['dvr']['group']['image_height'], $_SESSION['dvr']['group']['image_width'], null, 'dvr_person');

	$groupid = shn_create_uuid('victim_group');

	//inserting to the incident table
	if($_SESSION['dvr']['incident_id']==null)
	$q1 = "INSERT INTO resource_to_incident(incident_id,x_uuid) VALUES('1','{$groupid}')";
	else
	$q1 = "INSERT INTO resource_to_incident(incident_id,x_uuid) VALUES('{$_SESSION['dvr']['incident_id']}','{$groupid}')";
	
	$db->Execute($q1);

	$q2 = "INSERT INTO pgroup(g_uuid,opt_group_type) VALUES ('{$groupid}','{$_SESSION['dvr']['group']['typ_of_grp']}')";
	$db->Execute($q2);

	//insert displaced location
	$q3 = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$groupid}-disp','{$_SESSION['dvr']['group']['displaced_loc']}','')";
	$res=$db->Execute($q3);

	//insert current location            
	$q4 = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$groupid}-curr','{$_SESSION['dvr']['group']['current_loc']}','')";
	$res = $db->Execute($q4);

	$q5 = "INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) VALUES ('{$_SESSION['dvr_add_group']['entry']['p_uuid']}','{$_SESSION['dvr']['group']['nic']}','idcard')";
	$res = $db->Execute($q5);

	$pas = "INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) VALUES ('{$_SESSION['dvr_add_group']['entry']['p_uuid']}','{$_SESSION['dvr']['group']['dln']}','pas')";
	$res = $db->Execute($pas);

	$dln = "INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) VALUES ('{$_SESSION['dvr_add_group']['entry']['p_uuid']}','{$_SESSION['dvr']['group']['dln']}','dln')";
	$res = $db->Execute($dln);

	_dvr_add_contact($_SESSION['dvr_add_group']['entry']['p_uuid'], 'mobile', $_SESSION['dvr']['group']['mobile']);

	_dvr_add_contact($_SESSION['dvr_add_group']['entry']['p_uuid'], 'telephone', $_SESSION['dvr']['group']['telephone']);

	_dvr_add_contact($_SESSION['dvr_add_group']['entry']['p_uuid'], 'email', $_SESSION['dvr']['group']['email']);

	_dvr_add_contact($_SESSION['dvr_add_group']['entry']['p_uuid'], 'address', $_SESSION['dvr']['group']['address']);

	//echo '< LOCATION: X:' . $_SESSION['dvr']['group']['gis_loc_x'] . 'Y: ' . $_SESSION['dvr']['group']['gis_loc_y'];
    /*
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        shn_gis_create_feature($keys_);
    
    */

	$q5 = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name,custom_name) VALUES ('{$_SESSION['dvr_add_group']['entry']['p_uuid']}'," .
	"'{$_SESSION['dvr']['group']['full_name']}','{$_SESSION['dvr']['group']['family_name']}','{$_SESSION['dvr']['group']['local_name']}','')";

	$db->Execute($q5);

	$dvr_services = $_SESSION['dvr']['group']['opt_dvr_service'];
	//creating the comma seperated sevices string
	if ($dvr_services == null)
		$dvr_services = array ();
	$services_string = implode($dvr_services, ','); //php imploding haha

	$other = $_SESSION['dvr']['group']['other'];

	$q6 = "INSERT INTO group_details(g_uuid,head_uuid,no_of_adult_males,no_of_adult_females,no_of_children,no_displaced,no_missing,no_dead,no_rehabilitated,checklist,description) VALUES('{$groupid}','{$_SESSION['dvr_add_group']['entry']['p_uuid']}','{$_SESSION['dvr']['group']['adlt_mls']}','{$_SESSION['dvr']['group']['adlt_fmls']}','{$_SESSION['dvr']['group']['chldrn']}','{$_SESSION['dvr']['group']['dsplcd']}','{$_SESSION['dvr']['group']['misng']}','{$_SESSION['dvr']['group']['dead']}','{$_SESSION['dvr']['group']['rehbd']}','{$services_string}','{$other}') ";
	$db->Execute($q6);
	
	
	
	$q7="INSERT INTO person_to_pgroup(p_uuid,g_uuid) VALUES ('{$_SESSION['dvr_add_group']['entry']['p_uuid']}','{$groupid}')";
    $db->Execute($q7);

    if($_SESSION['dvr']['incident_id']==null)
    $q8 = "INSERT INTO resource_to_incident(incident_id,x_uuid) VALUES('1','{$_SESSION['dvr_add_group']['entry']['p_uuid']}')";
	else
    $q8 = "INSERT INTO resource_to_incident(incident_id,x_uuid) VALUES('{$_SESSION['dvr']['incident_id']}','{$_SESSION['dvr_add_group']['entry']['p_uuid']}')";
	
	
	$db->Execute($q8);




    $q9 = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$_SESSION['dvr_add_group']['entry']['p_uuid']}-disp','{$_SESSION['dvr']['group']['displaced_loc']}','')";
	$res=$db->Execute($q9);

	//insert current location            
	$q10 = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$_SESSION['dvr_add_group']['entry']['p_uuid']}-curr','{$_SESSION['dvr']['group']['current_loc']}','')";
	$res = $db->Execute($q10);



    $q11="INSERT INTO resource_to_shelter(x_uuid,c_uuid) VALUES('{$groupid}','{$_SESSION['dvr']['group']['camps']}') ";
    $db->Execute($q11);

	$q12 = "INSERT INTO person_details(p_uuid) VALUES('{$_SESSION['dvr_add_group']['entry']['p_uuid']}')";
    $res = $db->Execute($q12);

	$q13 = "INSERT INTO person_physical (p_uuid) VALUES ('{$_SESSION['dvr_add_group']['entry']['p_uuid']}')";
	$db->Execute($q13);

}



function _dvr_add_contact($uuid, $contacttype, $contactvalue) {

	global $global;

	$db = $global['db'];

	$contact_query = "INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES ('{$uuid}','{$contacttype}','{$contactvalue}')";

	$db->Execute($contact_query);

}



function _dvr_update_contact($uuid, $contacttype, $contactvalue) {

	global $global;

	$db = $global['db'];

	$contact_query = "UPDATE contact SET contact_value='$contactvalue' WHERE pgoc_uuid='$uuid' AND opt_contact_type='$contacttype'";
	$db->Execute($contact_query);
}



function _shn_dvr_commit_individual() {

	global $global;
	$db = $global['db'];
//if($_SESSION['dvr']['person']['person_image']!=null | $_SESSION['dvr']['person']['person_image']!='')
	shn_image_to_db_ex($_SESSION['dvr']['person']['p_uuid'], $_SESSION['dvr']['person']['person_image'], $_SESSION['dvr']['person']['person_image_type'], $_SESSION['dvr']['person']['person_image_height'], $_SESSION['dvr']['person']['person_image_width'], null, 'dvr_person');

	$groupid = shn_create_uuid('group');

	//inserting to the incident table
	
	$q1 = "INSERT INTO resource_to_incident (incident_id,x_uuid) VALUES ('{$_SESSION['dvr']['incident_id']}','{$_SESSION['dvr']['person']['p_uuid']}')";
	
	$db->Execute($q1);

	$q2 = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name,custom_name) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['full_name']}','{$_SESSION['dvr']['person']['family_name']}','{$_SESSION['dvr']['person']['local_name']}','')";
	$db->Execute($q2);

	$group = $_SESSION['dvr']['person']['group_id'];
	
	if ($group == '0')
		$group = 'notrelavant';
	$q3 = "INSERT INTO person_to_pgroup (p_uuid,g_uuid) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$group}') ";
	$db->Execute($q3);

	$other = $_SESSION['dvr']['person']['last_clothing'] . ',' . $_SESSION['dvr']['person']['comments'];
	$q4 = "INSERT INTO person_physical (p_uuid,opt_blood_type,height,weight,opt_eye_color,opt_skin_color,opt_hair_color,injuries,comments) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['opt_blood_type']}','{$_SESSION['dvr']['person']['height']}','{$_SESSION['dvr']['person']['weight']}','{$_SESSION['dvr']['person']['opt_eye_color']}','{$_SESSION['dvr']['person']['opt_skin_color']}','{$_SESSION['dvr']['person']['opt_hair_color']}','','{$other}')";
	$db->Execute($q4);
//if($_SESSION['dvr']['person']['finger_image']!=null)
	shn_image_to_db_ex($_SESSION['dvr']['person']['p_uuid'], $_SESSION['dvr']['person']['finger_image'], $_SESSION['dvr']['person']['finger_image_type'], $_SESSION['dvr']['person']['finger_image_height'], $_SESSION['dvr']['person']['finger_image_width'], null, 'finger_print');

	{
		_dvr_add_contact($_SESSION['dvr']['person']['p_uuid'], 'mobile', $_SESSION['dvr']['person']['mobile']);
	}

	{
		_dvr_add_contact($_SESSION['dvr']['person']['p_uuid'], 'telephone', $_SESSION['dvr']['person']['telephone']);
	}

	{
		_dvr_add_contact($_SESSION['dvr']['person']['p_uuid'], 'email', $_SESSION['dvr']['person']['email']);

	}

	{
		_dvr_add_contact($_SESSION['dvr']['person']['p_uuid'], 'address', $_SESSION['dvr']['person']['address']);

	}

	$q5 = "INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['idcard']}','idcard')";
	$res = $db->Execute($q5);

	$q6 = "INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['passport']}','pas')";
	$res = $db->Execute($q6);
	$q7 = "INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['drv_licence']}','dln')";
	$res = $db->Execute($q7);
	
	//insert displaced location
	$q8 = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$_SESSION['dvr']['person']['p_uuid']}-disp','{$_SESSION['dvr']['person']['displaced_loc']}','')";
	$res=$db->Execute($q8);

	//insert current location            
	$q9 = "INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$_SESSION['dvr']['person']['p_uuid']}-curr','{$_SESSION['dvr']['person']['current_loc']}','')";
	$res = $db->Execute($q9);
	
    $q10="INSERT INTO resource_to_shelter(x_uuid,c_uuid) VALUES ('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['camps']}')";
    $res = $db->Execute($q10);

    $q11 = "INSERT INTO person_details(p_uuid,birth_date,opt_age_group,opt_race,opt_religion,opt_marital_status,opt_gender) VALUES('{$_SESSION['dvr']['person']['p_uuid']}','{$_SESSION['dvr']['person']['dob']}','{$_SESSION['dvr']['person']['opt_age_group']}','{$_SESSION['dvr']['person']['opt_race']}','{$_SESSION['dvr']['person']['opt_religion']}','{$_SESSION['dvr']['person']['opt_marital_status']}','{$_SESSION['dvr']['person']['opt_gender']}')";
    $res = $db->Execute($q11);

  
}

function _shn_dvr_get_shelter($group_id)
{
	global $global;
	$db = $global['db'];
	$search_q1 = "SELECT c_uuid FROM resource_to_shelter WHERE x_uuid='{$group_id}'";

	$results = $db->Execute($search_q1);
	return $results->fields['c_uuid'];
}


function _shn_dvr_get_headid($group_id) {

	global $global;
	$db = $global['db'];
	$search_q1 = "SELECT head_uuid FROM group_details WHERE g_uuid='{$group_id}'";

	$results = $db->Execute($search_q1);
	return $results->fields['head_uuid'];
}


function _shn_dvr_get_all_groups($incident_id=null,$camp_id=null) {
	global $global;
	global $conf;
	$db = $global['db'];
	if($incident_id!=null)
	{
	$search_q1 = "SELECT DISTINCT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address FROM identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd,resource_to_incident re WHERE re.x_uuid=gd.g_uuid AND re.incident_id='{$incident_id}' AND gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' order by group_type";
	
	}
	else if($camp_id!=null)
{
	$search_q1 = "SELECT DISTINCT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address FROM identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd,resource_to_shelter rs WHERE rs.c_uuid='{$camp_id}' AND rs.x_uuid=gd.g_uuid AND gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' order by group_type";
	
}
	else
	{
	$search_q1 = "SELECT DISTINCT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address FROM identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' order by group_type";	
	}
	$results = $db->Execute($search_q1);
	$results = shn_paging_get_report($search_q1,$conf['mod_dvr_results_per_page'],$headers,array('post'=>false,'return'=>true));
	//print count($results);
	return $results;
}



function _shn_dvr_get_group_search_results($group_type, $card, $name) {

	global $global;
	$db = $global['db'];
//print 'group type'.$group_type;
//print 'card is'.$card;
	if ($group_type == '===' & $card == null & $name == null) {
		$search_q1 = "SELECT distinct pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard'";
	} else
		if ($group_type == "===" & $card == null & $name != null) {
			$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%') ";
		} else
			if ($group_type == "===" & $card != null & $name == null) {
				$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  id.serial='{$card}'";
			} else
				if ($group_type == "===" & $card != null & $name != null) {
					$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  id.serial='{$card}' AND (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%')";
				} else
					if ($group_type != "===" & $card == null & $name == null) {
						$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  pg.opt_group_type='{$group_type}'";
					} else
						if ($group_type != "===" & $card == null & $name != null) {
							$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  pg.opt_group_type='{$group_type}' AND (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%')";
						} else
							if ($group_type != "===" & $card != null & $name == null) {
								$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  pg.opt_group_type='{$group_type}' AND id.serial like '%{$card}%'";
							} else
								if ($group_type != "===" & $card != null & $name != null) {
									$search_q1 = "SELECT pg.g_uuid AS group_id,pg.opt_group_type AS group_type,pn.full_name AS full_name ,pn.family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial,co.contact_value AS address from identity_to_person id,contact co,person_uuid pn,pgroup pg,group_details gd WHERE gd.g_uuid=pg.g_uuid AND gd.head_uuid=pn.p_uuid AND gd.head_uuid=id.p_uuid AND gd.head_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  pg.opt_group_type='{$group_type}' AND id.serial='{$card}' AND (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%')";
								}

	//$results = $db->Execute($search_q1);
	global $conf;
	$results=shn_paging_get_report($search_q1,$conf['mod_dvr_results_per_page'],$headers,array('post'=>true,'return'=>true));
	return $results;
}



function _shn_dvr_get_individual_search_results($card, $name, $incident) {
	global $global;
	global $conf;
	$db = $global['db'];

	if ($card == null & $name == null & $incident == null) {
		//$search_q1="SELECT pn.full_name,pn,family_name,pn.l10n_name,id.serial,co.contact_value AS address from person_to_pgroup persontopg,pgroup pg,person_uuid pn,contact co,identity_to_person id WHERE persontopg.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard'";
		$search = " SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,pgroup pg,group_details gd,person_uuid pn,contact co,identity_to_person id,resource_to_incident res  WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid  AND pg.g_uuid=persontopg.g_uuid  AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND res.incident_id='{$_SESSION['dvr']['incident_id']}' ";
	} else
		if ($card == null & $name == null & $incident != null) {
			$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,pgroup pg,group_details gd,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard'  "; //all incidents

		} else
			if ($card == null & $name != null & $incident == null) {
				$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,pgroup pg,group_details gd,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND res.incident_id='{$_SESSION['dvr']['incident_id']}' AND (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%')";

			} else
				if ($card == null & $name != null & $incident != null) {
					$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,group_details gd,pgroup pg,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%')";

				} else
					if ($card != null & $name == null & $incident == null) {
						$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,group_details gd,pgroup pg,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid  AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND res.incident_id='{$_SESSION['dvr']['incident_id']}' AND id.serial='{$card}'";

					} else
						if ($card != null & $name == null & $incident != null) {
							$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,group_details gd,pgroup pg,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard'  AND id.serial='{$card}'";

						} else
							if ($card != null & $name != null & $incident == null) {

								$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,group_details gd,pgroup pg,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%') AND id.serial='{$card}' AND res.incident_id='{$_SESSION['dvr']['incident_id']}'";

							} else if ($card != null & $name != null & $incident != null) {

									$search = "SELECT distinct pn.p_uuid AS pid,pg.opt_group_type AS group_type,gd.head_uuid AS head_uuid,pn.full_name AS full_name,family_name AS family_name,pn.l10n_name AS local_name,id.serial AS serial ,co.contact_value AS address from person_to_pgroup persontopg,group_details gd,pgroup pg,person_uuid pn,contact co,identity_to_person id,resource_to_incident res WHERE gd.g_uuid=pg.g_uuid AND persontopg.p_uuid=pn.p_uuid AND pg.g_uuid=persontopg.g_uuid AND res.x_uuid=pn.p_uuid AND persontopg.p_uuid=co.pgoc_uuid AND id.p_uuid=pn.p_uuid AND co.opt_contact_type='address' AND id.opt_id_type='idcard' AND  (pn.full_name like '%{$name}%' or pn.l10n_name like '%{$name}%' or pn.family_name like '%{$name}%') AND id.serial='{$card}'";

								}
	//$results = $db->Execute($search);
    $results=shn_paging_get_report($search,$conf['mod_dvr_results_per_page'],$headers,array('post'=>true,'return'=>true));
	return $results;

}

function get_person_major_details($person_uuid) {
	global $global;
	$db = $global['db'];
	$sql = " SELECT pgr.g_uuid AS groupid,pgr.opt_group_type AS group_type,gls.head_uuid AS head_id FROM person_to_pgroup pg,pgroup pgr,group_details gls WHERE gls.g_uuid=pgr.g_uuid AND gls.g_uuid=pg.g_uuid AND pgr.g_uuid=pg.g_uuid AND pg.p_uuid='{$person_uuid}'";
	$results = $db->Execute($sql);

	return $results;

}

function get_personal_details($p_uuid) {
	global $global;
	$db = $global['db'];
	$sql = " SELECT birth_date,opt_age_group,opt_gender,opt_marital_status,opt_religion,opt_race FROM person_details WHERE p_uuid='{$p_uuid}'";
	$results = $db->Execute($sql);

	return $results;
}

function get_person_physical_details($p_uuid)
{
	global $global;
	$db = $global['db'];
	$sql = "SELECT * FROM person_physical WHERE p_uuid='{$p_uuid}'";
	$results = $db->Execute($sql);

	return $results;
}


function get_person_full_name($p_uuid) {
	global $global;
	$db = $global['db'];
	$sql = " SELECT full_name,family_name,l10n_name from person_uuid WHERE p_uuid='{$p_uuid}'";
	$results = $db->Execute($sql);

	return $results;
}

function get_identity_to_person($p_uuid) {
	global $global;
	$db = $global['db'];
	$sql = " SELECT serial,opt_id_type FROM identity_to_person WHERE p_uuid='{$p_uuid}'";
	$results = $db->Execute($sql);

	return $results;
}

function get_group_type_and_head_details($group_id) {

	global $global;
	$db = $global['db'];
	$sql = "SELECT pp.opt_group_type AS group_type,pe.p_uuid AS head_id ,pe.full_name AS full_name,pe.l10n_name AS l10n_name,pe.family_name AS family_name ,id.serial AS nic from group_details pg,person_uuid pe,pgroup pp,identity_to_person id WHERE pp.g_uuid=pg.g_uuid AND pe.p_uuid=pg.head_uuid  AND id.p_uuid=pe.p_uuid AND   id.opt_id_type='idcard' AND  pg.g_uuid='{$group_id}'";
	$results = $db->Execute($sql);

	return $results;
}

function get_contacts($person_uuid) {
	global $global;
	$db = $global['db'];
	$sql = "SELECT opt_contact_type,contact_value from contact WHERE pgoc_uuid='{$person_uuid}'";
	$results = $db->Execute($sql);
	
	return $results;
}

function get_group_description($group_id) {
	global $global;
	$db = $global['db'];

	$sql = "SELECT no_of_adult_males,no_of_adult_females,no_of_children,no_displaced,no_missing,no_dead,no_rehabilitated,checklist,description from group_details WHERE g_uuid ='{$group_id}'";

	$results = $db->Execute($sql);
	return $results;
}

function get_group_location_details($group_id) {

	global $global;
	$db = $global['db'];
	$q = "SELECT loc_uuid from location,location_details WHERE poc_uuid='{$group_id}' AND location_details.location_id=location.loc_uuid";
	$result = $db->Execute($q);
	return $result->fields['loc_uuid'];
}

function get_person_location_details($person_id) {

	global $global;
	$db = $global['db'];
	$q = "SELECT loc_uuid from location,location_details WHERE poc_uuid='{$person_id}' AND location_details.location_id=location.loc_uuid";
	$result = $db->Execute($q);
	return $result->fields['loc_uuid'];
}


function get_dvr_group_member_count($group_id)
{
	global $global;
	$db = $global['db'];
	$q = "SELECT no_of_adult_males AS nm ,no_of_adult_females AS nfm,no_of_children AS nc from group_details WHERE g_uuid='{$group_id}' ";
	$result = $db->Execute($q);
	$nm=$result->fields['nm'];
	$nfm=$result->fields['nfm'];
	$nc=$result->fields['nc'];
	$mc=array();
	$mc[0]=$nm;
	$mc[1]=$nfm;
	$mc[2]=$nc;
	
	return $mc;
}

/*function get_dvr_group_adult_count()
{global $global;
	$db = $global['db'];
	$q = "SELECT loc_uuid from location,location_details WHERE poc_uuid='{$person_id}' AND location_details.location_id=location.loc_uuid";
	$result = $db->Execute($q);
	return $result->fields['loc_uuid'];
}*/

function _shn_dvr_update_individual() {

	global $global;
	$db = $global['db'];
	//inserting the image

	include $global['approot'] . "/inc/lib_gis/gis_fns.inc";
	//include $global['approot'] . "/mod/dvr/lib.inc";

	$image_id = _shn_dvr_get_image_id($_SESSION['dvr']['person']['p_uuid'], 'dvr_person');

	
if ($_SESSION['dvr']['person']['person_image'] != null) {
	//if($image_id != null){	
     shn_image_to_db_ex($_SESSION['dvr']['person']['p_uuid'], $_SESSION['dvr']['person']['person_image'], $_SESSION['dvr']['person']['person_image_type'], $_SESSION['dvr']['person']['person_image_height'], $_SESSION['dvr']['person']['person_image_width'], $image_id, 'dvr_person');

	//}
}

	$image_id = _shn_dvr_get_image_id($_SESSION['dvr']['person']['p_uuid'], 'finger_print');
//echo $image_id;
	if ($_SESSION['dvr']['person']['finger_image'] != null){
	//	if($image_id != null){
		shn_image_to_db_ex($_SESSION['dvr']['person']['p_uuid'], $_SESSION['dvr']['person']['finger_image'], $_SESSION['dvr']['person']['finger_image_type'], $_SESSION['dvr']['person']['finger_image_height'], $_SESSION['dvr']['person']['finger_image_width'], $image_id, 'finger_print');

	//}
	}

	        
	/*
	 * commented fix bug 1916335
	$q1 = "UPDATE resource_to_incident set incident_id='{$_SESSION['dvr']['incident_id']}' WHERE x_uuid ='{$_SESSION['dvr']['person']['p_uuid']}'";
	$db->Execute($q1);
	*/
	
	/*
	$q1="insert into resource_to_incident (incident_id,x_uuid) values ('{$_SESSION['user_pref_ims_incident_id']}','{$_SESSION['dvr']['person']['p_uuid']}')";
	$db->Execute($q1);*/

	$q2 = "UPDATE person_uuid set full_name='{$_SESSION['dvr']['person']['full_name']}',family_name='{$_SESSION['dvr']['person']['family_name']}',l10n_name='{$_SESSION['dvr']['person']['local_name']}' WHERE p_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
	$db->Execute($q2);

	//todo changing the group
	/*$group=$_SESSION['dvr']['person']['group_id'];
	if($group=='0')
	$group='notrelavant';
	$q3="UPDATE person_to_pgroup (p_uuid,g_uuid) values ('{$_SESSION['dvr']['person']['p_uuid']}','{$group}') "	;
	$db->Execute($q3);*/

	$other = $_SESSION['dvr']['person']['last_clothing'] . ',' . $_SESSION['dvr']['person']['comments'];
	
	$q4 = "UPDATE person_physical SET opt_blood_type='{$_SESSION['dvr']['person']['opt_blood_type']}', height='{$_SESSION['dvr']['person']['height']}', weight='{$_SESSION['dvr']['person']['weight']}', opt_eye_color='{$_SESSION['dvr']['person']['opt_eye_color']}', opt_skin_color='{$_SESSION['dvr']['person']['opt_skin_color']}', opt_hair_color='{$_SESSION['dvr']['person']['opt_hair_color']}',injuries='',comments='$other' WHERE p_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
    $db->Execute($q4);
	//$q4="insert into person_details (p_uuid,next_kin_uuid,birth_date,opt_age_group,relation,opt_country,opt_race,opt_relegion,opt_marital_status,opt_gender,occupation) values ('{$_SESSION['dvr']['person']['p_uuid']}',$_SESSION['dvr']['person']['opt_eye_color'],)";
	

	_dvr_update_contact($_SESSION['dvr']['person']['p_uuid'], 'mobile', $_SESSION['dvr']['person']['mobile']);
	_dvr_update_contact($_SESSION['dvr']['person']['p_uuid'], 'telephone', $_SESSION['dvr']['person']['telephone']);
	_dvr_update_contact($_SESSION['dvr']['person']['p_uuid'], 'email', $_SESSION['dvr']['person']['email']);
	_dvr_update_contact($_SESSION['dvr']['person']['p_uuid'], 'address', $_SESSION['dvr']['person']['address']);

	$q5 = "UPDATE identity_to_person set serial='{$_SESSION['dvr']['person']['idcard']}' WHERE opt_id_type='idcard' AND p_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
	$res = $db->Execute($q5);

	$q6 = "UPDATE identity_to_person set serial='{$_SESSION['dvr']['person']['passport']}' WHERE opt_id_type='pas' AND p_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
	$res = $db->Execute($q6);
	$q7 = "UPDATE identity_to_person set serial='{$_SESSION['dvr']['person']['drv_licence']}' WHERE opt_id_type='dln' AND p_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
	$res = $db->Execute($q7);


    $q8="UPDATE resource_to_shelter set c_uuid='{$_SESSION['dvr']['person']['camps']}' WHERE x_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
    $db->Execute($q8);
 
    $q9 = "UPDATE person_details SET birth_date='{$_SESSION['dvr']['person']['dob']}',opt_age_group='{$_SESSION['dvr']['person']['opt_age_group']}',opt_race='{$_SESSION['dvr']['person']['opt_race']}',opt_religion='{$_SESSION['dvr']['person']['opt_religion']}',opt_marital_status='{$_SESSION['dvr']['person']['opt_marital_status']}',opt_gender='{$_SESSION['dvr']['person']['opt_gender']}' WHERE p_uuid='{$_SESSION['dvr']['person']['p_uuid']}'";
    $db->Execute($q9);
    
    $q10 = "UPDATE location_details SET location_id='{$_SESSION['dvr']['person']['displaced_loc']}' WHERE poc_uuid='{$_SESSION['dvr']['person']['p_uuid']}-disp'";
	$res=$db->Execute($q10);
	
	$q11 = "UPDATE location_details SET location_id='{$_SESSION['dvr']['person']['current_loc']}' WHERE poc_uuid='{$_SESSION['dvr']['person']['p_uuid']}-curr'";
	$res=$db->Execute($q11);
}

function _shn_dvr_update_group()
{
	global $conf;
	global $global;
	$db = $global['db'];
	//inserting the image
	include $global['approot'] . "/inc/lib_gis/gis_fns.inc";
	//include $global['approot'] . "/mod/dvr/lib.inc";

	$image_id = _shn_dvr_get_image_id($_SESSION['dvr']['group']['headid'], 'dvr_person');

	if ($_SESSION['dvr']['group']['image'] != null) {
		shn_image_to_db_ex($_SESSION['dvr']['group']['headid'], $_SESSION['dvr']['group']['image'], $_SESSION['dvr']['group']['image_type'], $_SESSION['dvr']['group']['image_height'], $_SESSION['dvr']['group']['image_width'], $image_id, 'dvr_person');
		//   print 'before';  
	}
    /*
     * commented fix bug 1916335
	$q1 = "UPDATE resource_to_incident set incident_id='{$_SESSION['dvr']['incident_id']}' WHERE x_uuid ='{$_SESSION['dvr']['group']['id']}'";
	$db->Execute($q1);
	*/
	
	//insert a group
	$q2 = "UPDATE pgroup set opt_group_type='{$_SESSION['dvr']['group']['typ_of_grp']}' WHERE g_uuid='{$_SESSION['dvr']['group']['id']}'";
	$db->Execute($q2);

	//insert displaced location
	$q3 = "UPDATE location_details set location_id='{$_SESSION['dvr']['group']['displaced_loc']}' WHERE poc_uuid='{$_SESSION['dvr']['group']['id']}-disp'";
	$res=$db->Execute($q3);

	//insert current location            
	$q4 = "UPDATE location_details set location_id='{$_SESSION['dvr']['group']['current_loc']}' WHERE poc_uuid='{$_SESSION['dvr']['group']['id']}-curr'";
	$res = $db->Execute($q4);
//print 'here'.$_SESSION['dvr']['group']['nic'].'test'.$_SESSION['dvr']['group']['headid'];
	$q5 = "UPDATE  identity_to_person set serial='{$_SESSION['dvr']['group']['nic']}' WHERE opt_id_type='idcard' AND p_uuid='{$_SESSION['dvr']['group']['headid']}'";
	 $db->Execute($q5);

	_dvr_update_contact($_SESSION['dvr']['group']['headid'], 'mobile', $_SESSION['dvr']['group']['mobile']);

	_dvr_update_contact($_SESSION['dvr']['group']['headid'], 'telephone', $_SESSION['dvr']['group']['telephone']);

	_dvr_update_contact($_SESSION['dvr']['group']['headid'], 'email', $_SESSION['dvr']['group']['email']);

	_dvr_update_contact($_SESSION['dvr']['group']['headid'], 'address', $_SESSION['dvr']['group']['address']);
	$x = $_SESSION['dvr']['group']['gis_loc_x'];
	$y = $_SESSION['dvr']['group']['gis_loc_y'];

    /*
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        shn_gis_modify_feature_module_item($f_module_item_, $keys_)
    }
    */

    
	$q5 = "update person_uuid set full_name='{$_SESSION['dvr']['group']['full_name']}',family_name='{$_SESSION['dvr']['group']['family_name']}',l10n_name='{$_SESSION['dvr']['group']['local_name']}' WHERE p_uuid='{$_SESSION['dvr']['group']['headid']}'";

	$db->Execute($q5);

	$dvr_services = $_SESSION['dvr']['group']['opt_dvr_service'];
	//creating the comma seperated sevices string
	if ($dvr_services == null)
		$dvr_services = array ();
	$services_string = implode($dvr_services, ',');//haha
	$other = $_SESSION['dvr']['group']['other'];

	$q6 = "UPDATE group_details SET no_of_adult_males='{$_SESSION['dvr']['group']['adlt_mls']}',no_of_adult_females='{$_SESSION['dvr']['group']['adlt_fmls']}',no_of_children='{$_SESSION['dvr']['group']['chldrn']}',no_displaced='{$_SESSION['dvr']['group']['dsplcd']}',no_missing='{$_SESSION['dvr']['group']['mising']}',no_dead='{$_SESSION['dvr']['group']['dead']}',no_rehabilitated='{$_SESSION['dvr']['group']['rehbd']}',checklist='$services_string',description='$other' WHERE g_uuid='{$_SESSION['dvr']['group']['id']}'";
	$db->Execute($q6);


$q7="update resource_to_shelter set c_uuid='{$_SESSION['dvr']['person']['camps']}' WHERE x_uuid='{$_SESSION['dvr']['group']['headid']}'";
	$db->Execute($q7);
}


function _shn_dvr_get_members($g_uuid)
{
$sql="SELECT p_uuid FROM person_to_pgroup p  WHERE p.g_uuid='{$g_uuid}'";
global $global;
$db = $global['db'];	

$res=$db->Execute($sql);

return $res;
}

/*function _shn_dvr_get_persons($g_uuid)
{
	$sql="SELECT "
}*/
//$x=SELECT id from person WHERE personid=fgfg

//count >0

function _shn_dvr_delete_person($p_uuid)
{
	
global $global;
$db = $global['db'];	
	//todo by isuru
	
$q1="delete from person_uuid  WHERE p_uuid='{$p_uuid}' ";
$db->Execute($q1);
$q2="delete from identity_to_person WHERE p_uuid='{$p_uuid}'";
$db->Execute($q2);
$q3="delete from person_details WHERE p_uuid='{$p_uuid}'";
$db->Execute($q3);
$q4="delete from contact WHERE pgoc_uuid='{$p_uuid}' ";
$db->Execute($q4);
$q5="delete from resource_to_incident WHERE x_uuid='{$p_uuid}'";
$db->Execute($q5);

$q6="delete from image WHERE x_uuid='{$p_uuid}'";
$db->Execute($q6);
$q7="DELETE FROM person_details WHERE p_uuid='{$p_uuid}'";
$db->Execute($q7);

$q8="DELETE FROM person_to_pgroup WHERE p_uuid='{$p_uuid}'";
$db->Execute($q8);
	
	
}



function  _shn_dvr_get_camps()
{
	$sql="select c_uuid,name,address,capacity from camp_general ";
global $global;
$db = $global['db'];	

$res=$db->Execute($sql);

return $res;
}

function _shn_dvr_delete_group($g_uuid)
{
global $global;
$db = $global['db'];	
	//todo by isuru
$members=_shn_dvr_get_members($g_uuid);
$q1="delete from pgroup WHERE g_uuid='{$g_uuid}' ";
$db->Execute($q1);

$q2="delete from person_to_pgroup WHERE g_uuid='{$g_uuid}' ";
$db->Execute($q2);

$q3="delete from resource_to_incident WHERE resource_to_incident='{$g_uuid}'";
$db->Execute($q3);





while(!$members->EOF)
{
	$id=$members->fields['p_uuid'];
     _shn_dvr_delete_person($id);

$members->MoveNext();
//$q3="delete from person_to_pgroup WHERE g_uuid='{$}'";
	
}

//delete head
$q4="delete from image i,group_details gd WHERE  i.x_uuid=gd.head_uuid AND gd.g_uuid='{$g_uuid}' ";
$db->Execute($q4);

}


function _shn_dvr_get_incidents()
{

global $global;
$db = $global['db'];	
$sql="SELECT * from incident";
//print 'here';
$result=$db->Execute($sql);
//print 'count is'.count($result);
return $result;
}

function _shn_dvr_get_child_incidents($parentid)
{
	global $global;
$db = $global['db'];	
$sql="SELECT * from incident WHERE parent_id ='{$parentid}'";
//print 'here';
$result=$db->Execute($sql);
//print 'count is'.count($result);
return $result;
}

/*function _shn_dvr_delete_individual($p_uuid)
{//todo by isuru
	
	global $global;
	$db = $global['db'];
	
}*/


?>

