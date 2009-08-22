<?php
include_once $global['approot']."/inc/lib_gis/gis_fns.inc";

//include_once 'lib_pre_ajax.inc';

function _shn_pre_validate_threat_area_general(){
	$valid = true;
	if($_POST['area'] == null){
		add_error('Add a name for area');
		$valid = false;
	}
	if($_POST['disaster'] == NULL){
		add_error('Add one or more suspectable disaster');
		$valid = false;
	}
	if($_POST['population'] != NULL && !_shn_pre_is_positive_number($_POST['population'])){
		add_error('Population should be a positive integer (>= 0)');
		$valid = false;
	}
	if($_POST['family'] != NULL && !_shn_pre_is_positive_number($_POST['family'])){
		add_error('Total families should be a positive integer(>=0)');
		$valid = false;
	}
	if($_POST['house'] != NULL && !_shn_pre_is_positive_number($_POST['house'])){
		add_error('Total houses should be a positive integer(>=0)');
		$valid = false;
	}
	if(($_POST['population'] != NULL && $_POST['family'] != NULL) && $_POST['population'] < $_POST['family']){
		add_error('Number of families should be smaller or equal than the population');
		$valid = false;
	}
	if($_POST['email'] != NULL && !shn_valid_email($_POST['email'])){
		add_error('Invalid email adress');
		$valid = false;
	}
	return $valid;
}

function _shn_pre_add_threat_area_db(){
	global $global;
	global $conf;
	$area_uuid = shn_create_uuid('l');
	if($_SESSION['name'] == '/'){
		$person_uuid = shn_create_uuid('p');
	}
	else{
		$person_uuid = $_SESSION['name'];
	}
	$sql1 = "INSERT INTO pre_threat_area VALUES('$area_uuid', '{$_SESSION['area']}', ";
	$sql1 .= "'{$_SESSION['location']}', '$person_uuid', '{$_SESSION['population']}', ";
	$sql1 .= "'{$_SESSION['family']}', '{$_SESSION['house']}')";
	$res1 = $global['db']->Execute($sql1);
	 
	foreach($_SESSION['disaster'] as $disaster){
		$sql2 = "INSERT INTO pre_threat_area_disaster VALUES('$disaster', '$area_uuid', '".$_SESSION['threat_level'.$disaster]."', 'pre')";
		$res2 = $global['db']->Execute($sql2);
	}
	
	if($conf['gis']){
		//shn_gis_dbinsert($area_uuid,$_SESSION['location'],$conf['mod_gis'],$_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'],NULL);
		require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
        $class = 'theat_area';
        $coords = shn_gis_coord_encode(array(array($_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'], 0)), 'point');
        $keys = array(  
            'f_class'         => $class,
            'f_type'          => 'point',
            'f_coords'        => $coords,
            'f_module_item'   => $area_uuid,
            'f_name'          => $_SESSION['area'],
            'f_url'           => '',
            'f_address'       => $_SESSION['area']
        );
        shn_gis_create_feature($keys);
   }
	
	if($_SESSION['name'] == '/'){
		$sql3 = "INSERT INTO person_uuid(p_uuid, full_name) VALUE('$person_uuid', '{$_SESSION['text_name']}')";
		$res3 = $global['db']->Execute($sql3);
		if($_SESSION['address'] != NULL){
			_shn_pre_add_contact($person_uuid, 'address', $_SESSION['address']);
		}
		if($_SESSION['tel_no'] != NULL){
			_shn_pre_add_contact($person_uuid, 'tel_no', $_SESSION['tel_no']);
		}
		if($_SESSION['mobile_no'] != NULL){
			_shn_pre_add_contact($person_uuid, 'mobile_no', $_SESSION['mobile_no']);
		}
		if($_SESSION['fax_no'] != NULL){
			_shn_pre_add_contact($person_uuid, 'fax_no', $_SESSION['fax_no']);
		}
		if($_SESSION['email'] != NULL){
			_shn_pre_add_contact($person_uuid, 'email', $_SESSION['email']);
		}
	}
	
	
	if($res1 == true){
		add_confirmation("Submition successfull");
		_shn_pre_get_threat_area($area_uuid);
	}
}


function _shn_pre_edit_threat_area($res){
	_shn_pre_print_header('Edit area under threat');
	unset($_SESSION['disaster']);
	global $global;  
	global $range;
	global $conf;
	for($i = 0; $i < $res->RecordCount(); $i++){
		$disaster[$res->fields['disaster_uuid']] = $res->fields['disaster'];
		$res->MoveNext();
	}
	
	$sql = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	for($i = 0; $i < $res->RecordCount(); $i++){
		$threat[$res->fields['des']] = $res->fields['des'];
		$res->MoveNext();
	}
	
    shn_form_fopen('add_threat_area','', array('req_message'=>true,));
    if($conf['gis'] == true){
    	if($_POST['seq'] == 'db'){
    		shn_form_hidden(array('seq'=>'gis'));
    	}
    	else{
    		shn_form_hidden(array('seq'=>'gis_ed'));
    	}
    }
    else{
    	shn_form_hidden(array('seq'=>'threat'));
    }
    shn_form_fsopen("General Information");
    shn_form_text('Area Name', 'area', '', array('req'=>true, 'value'=>$_SESSION['area']));
    shn_form_select($threat, 'Threat Level', 'threat');
    shn_form_multi_select('disaster', $disaster, 'Disaster','multiple="true"', array('req'=>true, 'value'=>$_SESSION['disaster']));
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_location($range, $_SESSION['location']);
    shn_form_fsclose();
    shn_form_fsopen("Contact Details");
?>
	<div calss="info">
<?php
	echo 'Contact details of the person who is responsible to reponse for the disasters';
?>
	<br></div>
<?php
	$value = array($_SESSION['text_name']);
	shn_ajax_text_look_up(array('Name'), array('name'), array('hint'), 'index.php?mod=pre&amp;act=get_contact_person&stream=text', $value, true );
	//shn_form_text('Name', 'name', '', array('value'=>$_SESSION['text_name']));
	//shn_form_hidden(array('name'=>$_SESSION['name']));	
	shn_form_textarea('Address', 'address', '', array('value'=>$_SESSION['address']));
	shn_form_text('Contact No', 'tel_no', '', array('value'=>$_SESSION['tel_no']));
	shn_form_text('Mobile No', 'mobile_no', '', array('value'=>$_SESSION['mobile_no']));
	shn_form_text('Fax', 'fax_no', '', array('value'=>$_SESSION['fax_no']));
	shn_form_text('Email', 'email', '', array('value'=>$_SESSION['email']));
	shn_form_fsclose();
	shn_form_fsopen('Population Details');
	shn_form_text('Total Population', 'population', '', array('value'=>$_SESSION['population']));
	shn_form_text('Total Family', 'family', '', array('value'=>$_SESSION['family']));
	shn_form_text('Total Houses', 'house', '', array('value'=>$_SESSION['house']));
	shn_form_fsclose();
    shn_form_submit('Next>>');
    
    shn_form_fclose();
}

/**
 * show details for confirmation
 */
function _shn_pre_add_threat_area_confirm(){
	$disaster = array();
	foreach($_SESSION['disaster'] as $d){
		$disaster[$d] = _shn_pre_get_disaster_name($d).' - '.$_SESSION['threat_level'.$d];
	}
	global $range;
	_shn_pre_print_header('Add a area under threat confirm');
	shn_form_fopen('add_threat_area','', array('req_message'=>true,));
    shn_form_hidden(array('seq'=>'db'));
    shn_form_fsopen("General Information");
    shn_form_label('Area Name : ', $_SESSION['area']);
    shn_form_label('Threat Level : ', $_SESSION['threat_level']);
    shn_form_multi_select('disaster', $disaster, 'Disaster','multiple="true"', array('req'=>true, 'value'=>$disaster));
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_form_label(' Loaction : ', _shn_pre_get_location_string($_SESSION['location']));
    shn_form_fsclose();
    shn_form_fsopen(_t('GPS Coordinates'));
    shn_form_label(_t("Latitude") . " : ",$_SESSION['gis_loc_y']);
    shn_form_label(_t("Longitude") . " : ",$_SESSION['gis_loc_x']);
    shn_form_fsclose();
    shn_form_fsopen("Contact Details");
?>
	<div calss="info">
<?php
	echo 'Contact details of the person who is responsible to reponse for the disasters';
?>
	<br></div>
<?php
	shn_form_label('Name : ', $_SESSION['text_name']);
	shn_form_label('Address', $_SESSION['address']);
	shn_form_label('Contact No : ', $_SESSION['tel_no']);
	shn_form_label('Mobile No : ', $_SESSION['mobile_no']);
	shn_form_label('Fax : ', $_SESSION['fax_no']);
	shn_form_label('Email : ', $_SESSION['email']);
	shn_form_fsclose();
	shn_form_fsopen('Population Details');
	shn_form_label('Total Population : ', $_SESSION['population']);
	shn_form_label('Total Family : ', $_SESSION['family']);
	shn_form_label('Total Houses : ', $_SESSION['house']);
	shn_form_fsclose();
    shn_form_submit('Save', 'name="save"');
    shn_form_submit('Edit', 'name="edit"');
    
    shn_form_fclose();
}

/**
 * set session on threat levels
 */
function _shn_pre_set_area_threat_session(){
	foreach($_SESSION['disaster'] as $disaster){
		$_SESSION['threat_level'.$disaster] = $_POST[$disaster];
	}
}

/**
 * set threat levels on each disaster
 */
function _shn_pre_set_area_threat_level($add = true){
	global $global;
	$sql = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	for($i = 0; $i < $res->RecordCount(); $i++){
		$threat[$res->fields['des']] = $res->fields['des'];
		$res->MoveNext();
	}
	_shn_pre_print_header("Set the threat level for each disaster");
	shn_form_fopen('add_threat_area',null,array('req'=>false));
    shn_form_fsopen(_("Set threat levels"));
    if($add){
    	shn_form_hidden(array('seq'=>'confirm'));
    }
    else{
    	shn_form_hidden(array('seq'=>'edit_db'));
    }
	foreach($_SESSION['disaster'] as $disaster){
		shn_form_select($threat, _shn_pre_get_disaster_name($disaster), $disaster);
	}
	shn_form_submit(" Set ");
	shn_form_fsclose();
	shn_form_fclose();
}

/**
 * gis map
 */
function _shn_pre_add_threat_area_map(){
	shn_form_fopen('add_threat_area',null,array('req'=>false));
    shn_form_fsopen(_("Location Information"));
    echo _("Plot the Location OR Enter its GPS coordinates below");
    shn_form_hidden(array('seq'=>'threat'));
    shn_form_fsclose();
    shn_gis_add_marker_map_form("GIS Map",$_POST['area']);
    shn_form_submit("Next");
    shn_form_fclose();
}

/**
 * Set the session on genaral information
 */
function _shn_pre_add_threat_area_session($add = true){
	$_SESSION['area'] = $_POST['area'];
	//$_SESSION['threat_level'] = $_POST['threat'];
	$_SESSION['disaster'] = $_POST['disaster'];
	$_SESSION['location'] = shn_location_get_form_submit_loc();
	$_SESSION['name'] = $_POST['name'];
	$_SESSION['text_name'] = $_POST['textname'];	
	if(!$add || $_SESSION['name'] == '/'){
		$_SESSION['address'] = $_POST['address'];
		$_SESSION['tel_no'] = $_POST['tel_no'];
		$_SESSION['mobile_no'] = $_POST['mobile_no'];
		$_SESSION['fax_no'] = $_POST['fax_no'];
		$_SESSION['email'] = $_POST['email'];
	}
	else{
		$_SESSION['address'] = _shn_pre_get_contact($_POST['name'], 'address');
		$_SESSION['tel_no'] = _shn_pre_get_contact($_POST['name'], 'tel_no');
		$_SESSION['mobile_no'] = _shn_pre_get_contact($_POST['name'], 'mobile_no');
		$_SESSION['fax_no'] = _shn_pre_get_contact($_POST['name'], 'fax_no');
		$_SESSION['email'] = _shn_pre_get_contact($_POST['name'], 'email');
	}
	$_SESSION['population'] = $_POST['population'];
	$_SESSION['family'] = $_POST['family'];
	$_SESSION['house'] = $_POST['house'];
}



/**
 * form interface to add general information on area under threat
 * if gis is enable
 * 	set location on map
 * else
 * 	set threat level
 */
function _shn_pre_add_threat_area_general($res){
	_shn_pre_print_header('Add a area under threat');
	global $global;  
	global $range;
	global $conf;
	for($i = 0; $i < $res->RecordCount(); $i++){
		$disaster[$res->fields['disaster_uuid']] = $res->fields['disaster'];
		$res->MoveNext();
	}
	
	$sql = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	for($i = 0; $i < $res->RecordCount(); $i++){
		$threat[$res->fields['des']] = $res->fields['des'];
		$res->MoveNext();
	}
	
    shn_form_fopen('add_threat_area','', array('req_message'=>true,));
    if($conf['gis'] == true){
    	shn_form_hidden(array('seq'=>'gis'));
    }
    else{
    	shn_form_hidden(array('seq'=>'threat'));
    }
    shn_form_fsopen("General Information");
    shn_form_text('Area Name', 'area', '', array('req'=>true));
    //shn_form_select($threat, 'Threat Level', 'threat');
    shn_form_multi_select('disaster', $disaster, 'Disaster','multiple="true"', array('req'=>true));
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_location($range);
    shn_form_fsclose();
    shn_form_fsopen("Contact Details");
?>
	<div calss="info">
<?php
	echo 'Contact details of the person who is responsible to reponse for the disasters';
?>
	<br></div>
<?php
	shn_ajax_text_look_up(array('Name'), array('name'), array('hint'), 'index.php?mod=pre&amp;act=get_contact_person&stream=text', null, true);
	
	?>
	<div id="name_list"></div>
	<?php
	shn_form_textarea('Address', 'address', '', '');
	shn_form_text('Contact No', 'tel_no');
	shn_form_text('Mobile No', 'mobile_no');
	shn_form_text('Fax', 'fax_no');
	shn_form_text('Email', 'email');
	shn_form_fsclose();
	shn_form_fsopen('Population Details');
	shn_form_text('Total Population', 'population');
	shn_form_text('Total Family', 'family');
	shn_form_text('Total Houses', 'house');
	shn_form_fsclose();
    shn_form_submit('Next>>');
    
    shn_form_fclose();
}

function _shn_pre_delete_area_disaster(){
	global $global;
	$sql1 = "DELETE FROM pre_threat_area_disaster WHERE ";
	$sql2 = "DELETE FROM pre_evacuation WHERE ";
	$i = 0;
	foreach($_SESSION['disaster'] as $dis){
		if($i == 0){
			$sql1 .= "(disaster_uuid <> '$dis'";
			$sql2 .= "(disaster_uuid <> '$dis'";
		}
		else{
			$sql1 .= " AND disaster_uuid <> '$dis'";
			$sql .= " AND disaster_uuid <> '$dis'";
		}
		$i++;
	}
	$sql1 .= ") AND area_uuid = '{$_SESSION['area_uuid']}'";
	$sql2 .= ") AND area_uuid = '{$_SESSION['area_uuid']}'";
	$global['db']->Execute($sql1);
	echo $global['db']->ErrorMsg();
	$global['db']->Execute($sql2);
	echo $global['db']->ErrorMsg();
}

/**
 * Editing area under threat -db
 */
function _shn_pre_edit_threat_area_db(){
	global $global;
	$sql1 = "UPDATE pre_threat_area " .
			"SET area = '{$_SESSION['area']}', loc_uuid = '{$_SESSION['location']}', population ='{$_SESSION['population']}', families = '{$_SESSION['family']}', houses = '{$_SESSION['house']}'" .
			" WHERE area_uuid = '{$_SESSION['area_uuid']}'";
	$res1 = $global['db']->Execute($sql1);
	if($res1 === false){
		add_error('Unable to edit');
	}
	else{
		_shn_pre_delete_area_disaster();
		foreach($_SESSION['disaster'] as $dis){
			$sql = "SELECT disaster_uuid FROM pre_threat_area_disaster WHERE area_uuid ='{$_SESSION['area_uuid']}' AND disaster_uuid = '$dis'";
			$res = $global['db']->Execute($sql);
			if($res->RecordCount() <= 0){
				$sql2 = "INSERT INTO pre_threat_area_disaster VALUES('$dis', '{$_SESSION['area_uuid']}', '{$_SESSION['threat_level'.$dis]}')";
			}
			else{
				$sql2 = "UPDATE pre_threat_area_disaster SET threat_level = '{$_SESSION['threat_level'.$dis]}' WHERE area_uuid = '{$_SESSION['area_uuid']}' AND disaster_uuid = '$dis'";
			}	
			$global['db']->Execute($sql2);
		}
		if(isset($_SESSION['new_p'])){
			$person_uuid = shn_create_uuid('p');
			$sql3 = "INSERT INTO person_uuid(p_uuid, full_name) VALUE('$person_uuid', '{$_SESSION['text_name']}')";
			$res3 = $global['db']->Execute($sql3);
			$sql4 = "UPDATE pre_threat_area SET person_uuid = '$person_uuid' WHERE area_uuid = '{$_SESSION['area_uuid']}'";
			$res4 = $global['db']->Execute($sql4);
			if($_SESSION['address'] != NULL){
				_shn_pre_add_contact($person_uuid, 'address', $_SESSION['address']);
			}
			if($_SESSION['tel_no'] != NULL){
				_shn_pre_add_contact($person_uuid, 'tel_no', $_SESSION['tel_no']);
			}
			if($_SESSION['mobile_no'] != NULL){
				_shn_pre_add_contact($person_uuid, 'mobile_no', $_SESSION['mobile_no']);
			}
			if($_SESSION['fax_no'] != NULL){
				_shn_pre_add_contact($person_uuid, 'fax_no', $_SESSION['fax_no']);
			}
			if($_SESSION['email'] != NULL){
				_shn_pre_add_contact($person_uuid, 'email', $_SESSION['email']);
			}
		}	
		else{
			_shn_pre_edit_person($_SESSION['name'], $_SESSION['text_name']);
			_shn_pre_edit_contact($_SESSION['name'], 'address', $_SESSION['address']);
			_shn_pre_edit_contact($_SESSION['name'], 'tel_no', $_SESSION['tel_no']);
			_shn_pre_edit_contact($_SESSION['name'], 'mobile_no', $_SESSION['mobile_no']);
			_shn_pre_edit_contact($_SESSION['name'], 'fax_no', $_SESSION['fax_no']);
			_shn_pre_edit_contact($_SESSION['name'], 'email', $_SESSION['email']);
		}
		add_confirmation('Edit successful');
		_shn_pre_get_threat_area($_SESSION['area_uuid']);
	}
}

/**
 * editing area under threat-interface
 */ 
function _shn_pre_edit_threat_area_form($area_uuid){
	_shn_pre_print_header('Edit Area information');
	global $global;
	global $range;
	global $conf;
	
	$disaster = array();
	$sql3 = "SELECT disaster_uuid, disaster FROM pre_disaster";
	$res3 = $global['db']->Execute($sql3);
	for($di = 0; $di < $res3->RecordCount(); $di++){
		$disaster[$res3->fields['disaster_uuid']] = $res3->fields['disaster'];
		$res3->MoveNext();
	}
	
	$sql = "SELECT option_code AS code, option_description AS des FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	for($i = 0; $i < $res->RecordCount(); $i++){
		$threat[$res->fields['des']] = $res->fields['des'];
		$res->MoveNext();
	}
	
	$sql1 = "SELECT * FROM pre_threat_area WHERE area_uuid = '$area_uuid'";
	$res1 = $global['db']->Execute($sql1);
	
	if($res1->RecordCount() > 0){
		$sql2 = "SELECT disaster_uuid, threat_level FROM pre_threat_area_disaster WHERE area_uuid = '$area_uuid'";
		$res2 = $global['db']->Execute($sql2);
		$disaster_sel = array();
		for($di = 0; $di < $res2->RecordCount(); $di++){
			$disaster_sel[$res2->fields['disaster_uuid']] = $res2->fields['disaster_uuid'];
			$res2->MoveNext();
		}
	    shn_form_fopen('add_threat_area','', array('req_message'=>true,));
    	shn_form_hidden(array('seq'=>'edit_threat'));
    	shn_form_hidden(array('area_uuid'=>$area_uuid));
    	shn_form_fsopen("General Information");
    	shn_form_text('Area Name', 'area', '', array('req'=>true, 'value'=>$res1->fields['area']));
    	shn_form_multi_select('disaster', $disaster, 'Disaster','multiple="true"', array('req'=>true, 'br'=>false, 'value'=>$disaster_sel));
    	shn_form_fsclose();
    	shn_form_fsopen(_("Location Details"));
    	shn_location($range, $res1->fields['loc_uuid']);
    	shn_form_fsclose();
		_shn_pre_edit_contact_form($res1);
		shn_form_fsopen('Population Details');
		shn_form_text('Total Population', 'population', '', array('value'=>$res1->fields['population']));
		shn_form_text('Total Family', 'family', '', array('value'=>$res1->fields['families']));
		shn_form_text('Total Houses', 'house', '', array('value'=>$res1->fields['houses']));
		shn_form_fsclose();
    	shn_form_submit('Edit>>');
        shn_form_fclose();
        echo '<br>';
        _shn_pre_delete_area_form($area_uuid, 'add_threat_area');
	}
	
}

/**
 * delete the selected area
 */
function _shn_pre_delete_threat_area($area_uuid){
	global $global;
	$sql1 = "DELETE FROM pre_threat_area WHERE area_uuid= '$area_uuid'";
	$res1 = $global['db']->Execute($sql1);
	if($res1 === false){
		add_error('Unable to delete the area');
	}
	else{
		$sql2 = "DELETE FROM pre_threat_area_disaster WHERE area_uuid = '$area_uuid'";
		$res2 = $global['db']->Execute($sql2);
		if($res2 === false){
			add_error('Unable to delete the disasters of the area');
		}
		else{
			$sql3 = "DELETE FROM pre_evacuation WHERE area_uuid = '$area_uuid'";
			$res3 = $global['db']->Execute($sql3);
			if($res3 === false){
				add_error('Unable to delete the evacuation details for area');
			}
			else{
				$sql4 = "DELETE FROM gis_location WHERE poc_uuid = '$area_uuid'";
				$res4 = $global['db']->Execute($sql4);
				if($res4 === false){
					add_error('Unable to delete gis information');
				}
				else{
					add_confirmation('Deletion Succussefull');
				}
			}
		}
	}
}

