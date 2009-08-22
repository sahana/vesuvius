<?php
/**
* The Sahana Disaster Preparedness System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Chamara Caldera <chamaracal@gmail.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

function _shn_pre_print_header($header){
	?>
	<h2><?php echo $header; ?></h2>
	<br>
	<?php
}

function _shn_pre_print_alert($alert)
{
	?>
<div class="alert"><!-- TODO: change style --> <strong><?php print ("Alert") . " : $alert"?></strong>
</div>
	<?php
}


/**
 * Return a basic details about a disaster 
 */
function _shn_pre_get_disaster_details($disaster_uuid){
	global $global;
	$sql1 = "SELECT disaster_uuid, disaster,reason, description, possibility FROM pre_disaster WHERE disaster_uuid = '$disaster_uuid'";
	$res1 = $global['db']->Execute($sql1);
	if ($res1->RecordCount() > 0){
		$tb_items[] = array('<Strong>Disaster :-</strong>', $res1->fields['disaster']);
		$tb_items[] = array('<strong>Reason :-</strong>', $res1->fields['reason']);
		$tb_items[] = array('<strong>Possibility :-</strong>', $res1->fields['possibility']);
		$tb_items[] = array('<strong>Description :-</strong>', $res1->fields['description']);
		$sql2 = "SELECT f.option_description AS effect FROM field_options AS f, pre_disaster_effects AS d WHERE d.disaster_uuid='".$res1->fields['disaster_uuid']."' AND f.option_code = d.effect";
		$res2 = $global['db']->Execute($sql2);
		for($i = 0; $i < $res2->RecordCount(); $i++){
			$effects .= '<br>'.$res2->fields['effect'];
			$res2->MoveNext();
		}
		$tb_items[] = array('<strong>Effects</strong>',$effects);
		shn_html_table($tb_items,null,null,array('class'=>'layout','width'=>'wide'));
	}
}

/**
 * Return a list of identified disasters 
 */
function _shn_pre_list_disaster(){
	global $global;
	$sql = "SELECT disaster_uuid,disaster,possibility, status FROM pre_disaster";
	$extra_opt = array('return'=>'true');
	$res = shn_paging_get_report($sql, 10, '',$extra_opt);
	$th_items[] = array('Disaster', 'Possibility', 'status', 'Warning');
	if($res->RecordCount() > 0){
		for($i = 0; $i < $res->RecordCount(); $i++){
			$duuid = $res->fields['disaster_uuid'];
			$disaster = $res->fields['disaster'];
			$possibility = $res->fields['possibility'];
			$tb_items[] = array(
							'<a href="index.php?mod=pre&act=add_disaster&seq=list&dis_id='.$duuid.'">'.$disaster.'</a>',
							$possibility,
							$res->fields['status'],
							'<a href="index.php?mod=pre&act=add_warning&dis_id='.$duuid.'"> Select </a>'
							);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No disaster has identified yet');
	}
}

/**
 * retrun the name of disaster
 */
 function _shn_pre_get_disaster_name($disaster_uuid){
 	global $global;
 	$sql = "SELECT disaster FROM pre_disaster WHERE disaster_uuid = '$disaster_uuid'";
 	$res = $global['db']->Execute($sql);
 	if ($res->RecordCount() > 0){
 		return $res->fields['disaster'];	
 	}
 	else{
 		return false;
 	}
 }
 
 /**
  * return a option name for a given option code  
  */
 function _shn_pre_get_field_name($code){
 	global $global;
 	$sql = "SELECT option_description AS des FROM field_options WHERE option_code ='$code'";
 	$res = $global['db']->Execute($sql);
 	if($res === false || $res->RecordCount() <= 0){
 		return false;
 	}
 	else{
 		return $res->fields['des'];
 	}
 }
 
 /**
  * set a table of recovery method and priority
  * disaster_uuid = $duuid
  * term = $term
  * effect = $effect
  * effect of disaster = $status
  */
 function _shn_pre_get_recovery_by_status($duuid, $term, $effect, $status, $return = ''){
 	global $global;
 	$sql = "SELECT id, method, priority FROM pre_disaster_recovery WHERE disaster_uuid = '$duuid' AND term = '$term' AND effect = '$effect' AND disaster_status = '$status'";
 	//$res = $global['db']->Execute($sql);
 	$extra_opt = array('return'=>'true', 'post'=>true);
	if($return == ''){
		$res = shn_paging_get_report($sql, 5, '',$extra_opt);
 	}
 	else{
 		$res = $global['db']->Execute($sql);
 	}
 	if($res === false){
 		add_error($global['db']->ErrorMsg());
 	}
 	else{
 		if($return == ''){
 			$th_items[] = array('Recovery Method', 'Priority', '');
 			for($i = 0; $i < $res->RecordCount(); $i++){
 				$tb_items[] = array(
 							$res->fields['method'],
 							$res->fields['priority'],
 							'<a href="index.php?mod=pre&act=add_disaster&seq=edit_rec&id='.$res->fields['id'].'">Edit</a>',
 							);
 				$res->MoveNext();
 			}
 			if($res->RecordCount() > 0){
 				echo '<dd><strong><em>Recovery method '.$status.' disaster</em></strong>';
 				shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
 				echo '</dd>';
 			}
 			else{
 				echo '<dd>';
 				print('No recovery method has been identified');
 				echo '</dd>';
 			}
 		}
 		else{
 			if($res->RecordCount() > 0){
 				return $res;
 			}
 			else{
 				return false;
 			}
 		}
 	}
 }
 
 function _shn_pre_get_recovery_by_effect($duuid, $term, $effect){
 	global $global;
 	$sql = "SELECT disaster_status AS status FROM pre_disaster_recovery WHERE disaster_uuid = '$duuid' AND term = '$term' AND effect = '$effect' GROUP BY disaster_status";
 	$res = $global['db']->Execute($sql);
 	echo '<dt><strong>Recovery methods for '._shn_pre_get_field_name($effect).'</strong>';
 	for($i = 0; $i < $res->RecordCount(); $i++){
 		_shn_pre_get_recovery_by_status($duuid, $term, $effect, $res->fields['status']);
		$res->MoveNext();
 	}
 	echo '</dt>';
 	/*echo '<dt><strong>Before the disaster</strong>';
 	_shn_pre_get_recovery_by_status($duuid, $term, $effect, 'before');
 	echo '</dt><dt><strong>On the disaster</strong>';
 	_shn_pre_get_recovery_by_status($duuid, $term, $effect, 'on');
 	echo '</dt><dt><strong>After the disaster</strong>';
 	_shn_pre_get_recovery_by_status($duuid, $term, $effect, 'after');
 	echo '</dt>';*/
 }
 
 function _shn_pre_get_recovery_by_term($duuid, $term){
 	global $global;
 	$sql = "SELECT effect FROM pre_disaster_recovery WHERE disaster_uuid = '$duuid' AND term = '$term' GROUP BY effect";
 	$res = $global['db']->Execute($sql);
 	for($i = 0; $i < $res->RecordCount(); $i++){
 		echo '<dl>';
 		_shn_pre_get_recovery_by_effect($duuid, $term, $res->fields['effect']);
 		echo '</dl>';
 		$res->MoveNext();
 	}
 	
 }
 
 function _shn_pre_get_recovery_by_disaster($duuid){
 	global $global;
 	$sql = "SELECT term FROM pre_disaster_recovery WHERE disaster_uuid = '$duuid' GROUP BY term";
 	$res = $global['db']->Execute($sql);
 	for($i = 0; $i < $res->RecordCount(); $i++){
 		echo '<h4>Recovery methods for '._shn_pre_get_field_name($res->fields['term']).' term</h4>';
 		_shn_pre_get_recovery_by_term($duuid, $res->fields['term']);
 		$res->MoveNext();
 	}
 }

/**
 *table of the recovery method
 */
function _shn_pre_get_recovery_details($rec_id){
	global $global;
	$sql = "SELECT method, disaster_status, effect, term, priority FROM pre_disaster_recovery WHERE id = '$rec_id'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$tb_items[] = array('<strong>Method</strong>', $res->fields['method']);
		$tb_items[] = array('<strong>Effect</strong>', _shn_pre_get_field_name($res->fields['effect']));
		$tb_items[] = array('<strong>Disaster Status</strong>', $res->fields['disaster_status']);
		$tb_items[] = array('<strong>Term</strong>' , _shn_pre_get_field_name($res->fields['term']));
		$tb_items[] = array('<strong>Priority</strong>', $res->fields['priority']);
		shn_html_table($tb_items, null, null, array('class'=>'wide'));
	}
	else{
		return false;
	}
}

/**
 * return the name of a recovery method
 */
function _shn_pre_get_recovery_name($rec_id){
	global $global;
	$sql = "SELECT method FROM pre_disaster_recovery WHERE id= '$rec_id'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res->fields['method'];
	}
	else{
		return 0;
	}
}

/**
 * Check curruntly identified disaster in same name
 */
 function _shn_pre_is_disaster($disaster){
 	global $global;
 	$sql = "SELECT disaster_uuid FROM pre_disaster WHERE disaster = '$disaster'";
 	$res = $global['db']->Execute($sql);
 	return $res->RecordCount();
 }
 
 /**
 * Delete the effects of disaster
 */
 function _shn_pre_delete_disaster_effects($duuid){
 	global $global;
 	$sql = "DELETE FROM pre_disaster_effects WHERE disaster_uuid = '$duuid'";
 	$res = $global['db']->Execute($sql);
 }
 
  
 /**
  * delete a recovery detail
  */
 function _shn_pre_delete_disaster_recovery($duuid){
 	global $global;
 	$sql = "DELETE FROM pre_disaster_recovery WHERE disaster_uuid = '$duuid'";
 	$res = $global['db']->Execute($sql);	
 }
 
 /**
  * delete a disaster
  */
 function _shn_pre_delete_disaster($duuid){
 	global $global;
 	$sql = "DELETE FROM pre_disaster WHERE disaster_uuid = '$duuid'";
 	$res = $global['db']->Execute($sql);
 	_shn_pre_delete_disaster_effects($duuid);
 	_shn_pre_delete_disaster_recovery($duuid);
 	if($res != false){
 		add_confirmation("Deletion successfully done");
 	}
 	else{
 		add_error("Error occurs");
 	}
 }
 
 /**
  * check possitive number
  */
function _shn_pre_is_positive_number($nr)
{
    if (ereg("^[0-9]+$", $nr) && $nr >= 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * vlidating gis(longitude and latitude)
 */
function _shn_pre_validate_gis(){
    clean_errors();
    $error_flag = true;

    // latitude
    if (!(null == ($_POST['gps_y']))) {
        if (!shn_valid_y_coordinate(trim($_POST['gps_y']))) {
            //add_error(_t("Coordinates invalid: should be between -180 & 180"));
            $error_flag = false;
        }
    }
    //longitude
    if (!(null == ($_POST['gps_x']))) {
        if (!shn_valid_x_coordinate(trim($_POST['gps_x']))) {
            //add_error(_t("Coordinates invalid: should be between -180 & 180"));
            $error_flag = false;
        }
    }
    return $error_flag;
}

/**
 * set gis detail to session
 */
function _shn_pre_gis_session(){
	if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
    	$_SESSION['gis_loc_x']=$_POST['loc_x'];
        $_SESSION['gis_loc_y']=$_POST['loc_y'];
    } else {
        $_POST['loc_x'] = $_POST['gps_x'];
        $_POST['loc_y'] = $_POST['gps_y'];
        $_SESSION['gis_loc_x']=$_POST['loc_x'];
        $_SESSION['gis_loc_y']=$_POST['loc_y'];
    }
}

/**
 * return a complete location string 
 */
function _shn_pre_get_location_string($loc)
{
	global $global;
    $db = $global["db"];
    $loc_arr = array();
   	shn_get_parents($loc, &$loc_arr);
   	if ($loc_arr[0] == 'unknown') {
   	} 
   	else {
   	    $max = count($loc_arr) - 1;
   	    array_pop($loc_arr);
   	    for ($count = 0; $count < $max; $count++) {
   	        $x = array_pop($loc_arr);
   	        $q = "SELECT name FROM location WHERE loc_uuid='{$x}'";
   	        $res = $db->Execute($q);
   	        if ($count == 0) {
   	            $location = $location . $res->Fields("name");
   	        } else {
   	            $location = $location . " -->" . $res->Fields("name");
   	        }

   	    }
   	}
    return $location;
}

/**
 * get person details with given name
 */
function _shn_pre_get_person_uuid($person){
	global $global;
	$sql = "SELECT p_uuid, full_name FROM person_uuid WHERE full_name = '$person'";
	$res = $global['db']->Execute($sql);
	return $res;
}

/**
 * get person details with given name
 * who are already used in tables of this module
 */
function _shn_pre_get_existing_person($person){
	global $global;
	$sql = "SELECT p_uuid AS person_uuid, full_name FROM person_uuid WHERE p_uuid IN (SELECT person_uuid FROM pre_threat_area) GROUP BY person_uuid";
	$res = $global['db']->Execute($sql);
	return $res;
}

/**
 * return tha name of person
 */
function _shn_pre_get_person_name($person_uuid){
	global $global;
	$sql = "SELECT full_name FROM person_uuid WHERE p_uuid = '$person_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res->fields['full_name'];
	}
	else{
		return false;
	}
}

/**
 *edit person name 
 */
function _shn_pre_edit_person($puuid, $name){
	global $global;
	$sql = "UPDATE person_uuid SET full_name = '$name' WHERE p_uuid = '$puuid'";
	$res = $global['db']->Execute($sql);
	return $res;
}

/**
 *  add contact details
 */
function _shn_pre_add_contact($puuid, $type, $contact){
	global $global;
	$sql = "INSERT INTO contact VALUES('$puuid', '$type', '$contact')";
	$res = $global['db']->Execute($sql);
	return $res;
}

/**
 * edit contact details
 */
function _shn_pre_edit_contact($puuid, $type, $contact){
	global $global;
	if($contact != null && !_shn_pre_get_contact($puuid, $type)){
		return _shn_pre_add_contact($puuid, $type, $contact);
	}
	else{
		$sql = "UPDATE contact SET contact_value = '$contact' WHERE pgoc_uuid = '$puuid' AND opt_contact_type = '$type'";
		$res = $global['db']->Execute($sql);
		return $res;
	}
}
/**
 * return contact details in given type for given person
 */
function _shn_pre_get_contact($puuid, $type){
	global $global;
	$sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$puuid' AND opt_contact_type = '$type'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0)
		return $res->fields['contact_value'];
	else
		return false;
} 

/**
 * complete details on a area under threat
 */
function _shn_pre_get_threat_area($area_id){
	global $global;
	global $conf;
	$sql1 = "SELECT area_uuid, area, loc_uuid, population, families, houses, person_uuid FROM pre_threat_area WHERE area_uuid = '$area_id'";
	$res1 = $global['db']->Execute($sql1);
	
	$sql2 = "SELECT disaster_uuid, threat_level FROM pre_threat_area_disaster WHERE area_uuid = '$area_id'";
	$res2 = $global['db']->Execute($sql2);
	
	global $range;
	_shn_pre_print_header('Details of '.$res1->fields['area'].' (Area under threat)');
	shn_form_fopen('add_threat_area','', array('req_message'=>true,));
    //shn_form_hidden(array('seq'=>'db'));
    shn_form_fsopen("General Information");
    shn_form_label('Area Name : ', $res1->fields('area'));
    //shn_form_label('Threat Level : ', $res1->fields('threat_level'));
    $disaster = '';
    for($i = 0; $i < $res2->RecordCount(); $i++){
    	$disaster .= _shn_pre_get_disaster_name($res2->fields['disaster_uuid']).' - '.$res2->fields['threat_level'].'<br>';    	
    	$res2->MoveNext();
    }
    shn_form_label('Disaster : ', $disaster);
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_form_label(' Loaction : ', _shn_pre_get_location_string($res1->fields('loc_uuid')));
    if($conf['gis'])
    	shn_form_label('', '<a href="index.php?mod=pre&act=list_threat_area&seq=gis&area='.$area_id.'">MAP VIEW</a>');
    shn_form_fsclose();
    /*shn_form_fsopen(_t('GPS Coordinates'));
    shn_form_label(_t("Latitude") . " : ", $res->fileds('gis_loc_y'));
    shn_form_label(_t("Longitude") . " : ", $res->fileds('gis_loc_x'));
    shn_form_fsclose();*/
    
    if($res1->fields['person_uuid'] != null){
    	shn_form_fsopen("Contact Details");
?>
	<div calss="info">
<?php
		echo 'Contact details of the person who is responsible to reponse for the disasters';
?>
	<br></div>
<?php
		shn_form_label('Name : ', _shn_pre_get_person_name($res1->fields['person_uuid']));
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'address')) != false){
			shn_form_label('Address', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'tel_no')) != false){
			shn_form_label('Contact No : ', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'mobile_no')) != false){
			shn_form_label('Mobile No : ', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'fax_no')) != false){
			shn_form_label('Fax No : ', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'email')) != false){
			shn_form_label('Email : ', $contact);
		}
		shn_form_fsclose();
    }
	
	shn_form_fsopen('Population Details');
	if($res1->fields['population'] != NULL)
		shn_form_label('Total Population : ', $res1->fields['population']);
	if($res1->fields['families'] != NULL)
		shn_form_label('Total Family : ', $res1->fields['families']);
	if($res1->fields['houses'] != NULL)
		shn_form_label('Total Houses : ', $res1->fields['houses']);
	/*shn_form_fsclose();
    shn_form_submit('Save', 'name="save"');
    shn_form_submit('Edit', 'name="edit"');
    */
    shn_form_fclose();
}

function _shn_pre_get_shelter_area($area_id){
	global $global;
	global $conf;
	$sql1 = "SELECT area_uuid, area, loc_uuid, address, capacity, ownership, owner_uuid, person_uuid, land_type FROM pre_shelter_area WHERE area_uuid = '$area_id'";
	$res1 = $global['db']->Execute($sql1);
	$sql2 = "SELECT disaster_uuid FROM pre_shelter_disaster WHERE area_uuid = '$area_id'";
	$res2 = $global['db']->Execute($sql2);
	
	global $range;
	_shn_pre_print_header('Details of '.$res1->fields['area'].' (Suitable area for shelter)');
	shn_form_fopen('add_shelter_area','', array('req_message'=>true,));
    //shn_form_hidden(array('seq'=>'db'));
    shn_form_fsopen("General Information");
    shn_form_label('Area Name : ', $res1->fields('area'));
    $disaster = '';
    for($i = 0; $i < $res2->RecordCount(); $i++){
    	$disaster .= _shn_pre_get_disaster_name($res2->fields['disaster_uuid']).' - '.$res2->fields['threat_level'].'<br>';    	
    	$res2->MoveNext();
    }
    shn_form_label('Address : ', $res1->fields['address']);
    shn_form_label('Disaster : ', $disaster);
    shn_form_label('Capacity : ', $res1->fields['capacity']);
    shn_form_label('Land type : ', $res1->fields['land_type']);
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_form_label(' Loaction : ', _shn_pre_get_location_string($res1->fields('loc_uuid')));
    if($conf['gis'])
    	shn_form_label('', '<a href="index.php?mod=pre&act=list_shelter_area&seq=gis&area='.$area_id.'">MAP VIEW</a>');
    shn_form_fsclose();
    /*shn_form_fsopen(_t('GPS Coordinates'));
    shn_form_label(_t("Latitude") . " : ", $res->fileds('gis_loc_y'));
    shn_form_label(_t("Longitude") . " : ", $res->fileds('gis_loc_x'));
    shn_form_fsclose();*/
    
    if($res1->fields['person_uuid'] != null){
    	shn_form_fsopen("Contact Details");
?>
	<div calss="info">
<?php
		echo 'Contact details of the person who is responsible to reponse for the disasters';
?>
	<br></div>
<?php
		shn_form_label('Name : ', _shn_pre_get_person_name($res1->fields['person_uuid']));
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'address')) != false){
			shn_form_label('Address', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'tel_no')) != false){
			shn_form_label('Contact No : ', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'mobile_no')) != false){
			shn_form_label('Mobile No : ', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'fax_no')) != false){
			shn_form_label('Fax No : ', $contact);
		}
		if(($contact = _shn_pre_get_contact($res1->fields['person_uuid'], 'email')) != false){
			shn_form_label('Email : ', $contact);
		}
		shn_form_fsclose();
    }
    shn_form_fsopen('Ownreship details');
    shn_form_label('Ownership : ', $res1->fields['ownership']);
    shn_form_label('Owner', _shn_pre_get_person_name($res1->fields['owner_uuid']));
    shn_form_label('Owner Address', _shn_pre_get_contact($res1->fields['owner_uuid'], 'address'));
    shn_form_label('Owner Contact No:', _shn_pre_get_contact($res1->fields['owner_uuid'], 'tel_no'));
}

/**
 * return the name of threat area
 */
function _shn_pre_get_threat_area_name($area_uuid){
	global $global;
	$sql = "SELECT area FROM pre_threat_area WHERE area_uuid = '$area_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res->fields['area'];
	}
}

/**
 * return the loc_uuid of area
 */
function _shn_pre_get_threat_area_location($area_uuid){
	global $global;
	$sql = "SELECT loc_uuid FROM pre_threat_area WHERE area_uuid = '$area_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res->fields['loc_uuid'];
	}
}

/**
 * return the disasters of a area
 */
function _shn_pre_get_threat_area_disaster($area_uuid){
	global $global;
	$sql = "SELECT disaster_uuid, threat_level FROM pre_threat_area_disaster WHERE area_uuid = '$area_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res;
	}
	else{
		return false;
	}
}

function _shn_pre_get_threat_area_puuid($area_uuid){
	global $global;
	$sql = "SELECT person_uuid FROM pre_threat_area WHERE area_uuid = '$area_uuid'";
	$res = $global['db']->Execute($sql);
	if($res === false || $res->RecordCount() <= 0){
		return false;
	}
	return $res->fields['person_uuid'];
}
/**
 * return the population of a area under threat
 */
function _shn_pre_get_threat_area_unallocated_population($area_uuid, $disaster){
	global $global;
	$sql = "SELECT population FROM pre_threat_area WHERE area_uuid = '$area_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$sql2 = "SELECT SUM(allocation) AS allocation FROM pre_evacuation WHERE disaster_uuid = '$disaster' AND area_uuid = '$area_uuid' GROUP BY area_uuid";
		$res2 = $global['db']->Execute($sql2);
		if($res2->RecordCount() > 0){
			return ($res->fields['population'] - $res2->fields['allocation']);
		}
		else{
			return $res->fields['population'];
		}
	}
}

/**
 * return the name of a are for shelter
 */
 function _shn_pre_get_shelter_area_name($shlt_uuid){
 	global $global;
	$sql = "SELECT area FROM pre_shelter_area WHERE area_uuid = '$shlt_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res->fields['area'];
	}
 }

/**
 * return the location of a shelter
 */
function _shn_pre_get_shelter_area_location($area_uuid){
	global $global;
	$sql = "SELECT loc_uuid FROM pre_shelter_area WHERE area_uuid = '$area_uuid'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		return $res->fields['loc_uuid'];
	}
}

/**
 * return available capacity of a shelter
 */
function _shn_pre_get_shelter_available_capacity($shlt_id, $disaster){
	global $global;
	$sql = "SELECT capacity FROM pre_shelter_area WHERE area_uuid = '$shlt_id'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$sql1 = "SELECT SUM(allocation) AS allocation FROM pre_evacuation WHERE shelter_uuid = '$shlt_id' AND disaster_uuid = '$disaster' GROUP BY shelter_uuid";
		$res1 = $global['db']->Execute($sql1);
		if($res1->RecordCount() > 0){
			return ($res->fields['capacity'] - $res1->fields['allocation']);
		}
		else{
			return $res->fields['capacity'];
		}
	}
}

/**
 * show the already allocated for a shelter on a disaster
 */
function _shn_pre_list_evacuation_per_area_disaster($area_uuid, $disaster){
	global $global;
	$sql = "SELECT shelter_uuid, allocation FROM pre_evacuation WHERE area_uuid = '$area_uuid' AND disaster_uuid = '$disaster'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){
		$th_items[] = array('Shelter', 'Allocation');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$tb_items[] = array(
							_shn_pre_get_shelter_area_name($res->fields['shelter_uuid']),
							$res->fields['allocation']);
			$res->MoveNext();
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
	else{
		_shn_pre_print_alert('No shelter has been assigned');
	}
}

//functions on warning system

/**
 * check whether registerd or warned
 */
function _shn_pre_is_declaired($duuid, $type){
	global $global;
	$sql = "SELECT * FROM pre_disaster_history WHERE disaster_uuid = '$duuid' AND type = '$type' AND expired_date IS NULL";
	$res = $global['db']->Execute($sql);
	if($res === false || $res->RecordCount() <= 0){
		return false;
	}
	else{
		return true;
	}
}

/**
 * return evacuation details for a area
 */
function _shn_pre_get_area_disaster_evacuation($area_uuid, $disaster_uuid){
	global $global;
	$sql = "SELECT shelter_uuid, allocation FROM pre_evacuation WHERE area_uuid = '$area_uuid' AND disaster_uuid = '$disaster_uuid'";
	$res = $global['db']->Execute($sql);
	if($res === false || $res->RecordCount() <= 0){
		_shn_pre_print_alert('Evacuation has no planed');
	}
	else{
		$th_items[] = array('Shelter', 'Location', 'Allocation');
		for($i = 0; $i < $res->RecordCount(); $i++){
			$tb_items[] = array(
								'<a href="index.php?mod=pre&act=list_shelter_area&seq=list&area='.$res->fields['shelter_uuid'].'">'._shn_pre_get_shelter_area_name($res->fields['shelter_uuid']).'</a>',
								_shn_pre_get_location_string(_shn_pre_get_shelter_area_location($res->fields['shelter_uuid'])),
								$res->fields['allocation']);
			$res->MoveNext();	
		}
		shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	}
}
