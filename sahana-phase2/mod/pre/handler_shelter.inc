<?php


function _shn_pre_add_shelter_area_db(){
	global $global;
	global $conf;
	$area_uuid = shn_create_uuid('l');
	if($_SESSION['name'] == '/'){
		$person_uuid = shn_create_uuid('p');
	}
	else{
		$person_uuid = $_SESSION['name'];
	}
	$owner_uuid = shn_create_uuid('p');
	$sql1 = "INSERT INTO pre_shelter_area VALUES(" .
			"'$area_uuid', '{$_SESSION['area']}', '{$_SESSION['address']}', '{$_SESSION['location']}', " .
			"'$person_uuid', '{$_SESSION['ownership']}', '$owner_uuid', '{$_SESSION['capacity']}', " .
			"'{$_SESSION['land_type']}')";
	$res1 = $global['db']->Execute($sql1);
	foreach($_SESSION['disaster'] as $disaster){
		$sql2 = "INSERT INTO pre_shelter_disaster VALUES('$area_uuid', '$disaster')";
		$res2 = $global['db']->Execute($sql2);
	}
	echo $global['db']->ErrorMsg();
	if($conf['gis']){
		shn_gis_dbinsert($area_uuid,$_SESSION['location'],$conf['mod_gis'],$_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'],NULL);
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
	
	if($_SESSION['owner'] != NULL){
		$sql4 = "INSERT INTO person_uuid(p_uuid, full_name) VALUE('$owner_uuid', '{$_SESSION['owner']}')";
		$res4 = $global['db']->Execute($sql4);
		if($_SESSION['address'] != NULL){
			_shn_pre_add_contact($owner_uuid, 'address', $_SESSION['owner_address']);
		}
		if($_SESSION['tel_no'] != NULL){
			_shn_pre_add_contact($owner_uuid, 'tel_no', $_SESSION['owner_tel_no']);
		}
		
	}
	if($res1 == true){
		add_confirmation("Submition successfull");
		_shn_pre_get_shelter_area($area_uuid);
	}
}

/**
 * Confirmation 
 */
function _shn_pre_add_shelter_confirmation(){
	$disaster = array();
	foreach($_SESSION['disaster'] as $d){
		$disaster[$d] = _shn_pre_get_disaster_name($d);
	}
	shn_form_fopen('add_shelter_area','', array('req_message'=>true,));
    shn_form_hidden(array('seq'=>'db'));
    shn_form_fsopen("General Information");
    shn_form_label('Area Name',$_SESSION['area']);
    shn_form_multi_select('disaster', $disaster, 'Disaster','multiple="true"', array('value'=>$disaster));
    shn_form_label('Location Address', $_SESSION['location_address']);
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
	echo 'Contact details of the person who is responsible to reponse for establise the shelter after disasters';
?>
	<br></div>
<?php
	
	?>
	<div id="name_list"></div>
	<?php
	shn_form_label('Name : ', $_SESSION['text_name']);
	shn_form_label('Address', $_SESSION['address']);
	shn_form_label('Contact No : ', $_SESSION['tel_no']);
	shn_form_label('Mobile No : ', $_SESSION['mobile_no']);
	shn_form_label('Fax : ', $_SESSION['fax_no']);
	shn_form_label('Email : ', $_SESSION['email']);
	shn_form_fsclose();
	shn_form_fsopen("Other Details");
	shn_form_label('Ownership : ', $_SESSION['ownership']);
	shn_form_label('Owner : ', $_SESSION['owner']);
	shn_form_fsopen("Contact details of owners");
	shn_form_label('Address : ', $_SESSION['owner_address']);
	shn_form_label('Contact No : ', $_SESSION['owner_tel_no']);
	shn_form_fsclose();
	shn_form_label('Capacity : ', $_SESSION['capacity']);
	shn_form_label('Land Type : ', $_SESSION['land_type']);
	shn_form_fsclose();
	shn_form_submit("Save", 'name="save"');
	shn_form_submit("Edit", 'name="edit"');
	shn_form_fclose();
}
	
/**
 * gis map
 */
function _shn_pre_add_shelter_area_map(){
	shn_form_fopen('add_shelter_area',null,array('req'=>false));
    shn_form_fsopen(_("Location Information"));
    echo _("Plot the Location OR Enter its GPS coordinates below");
    shn_form_hidden(array('seq'=>'confirm'));
    shn_form_fsclose();
    shn_gis_add_marker_map_form("GIS Map",$_POST['area']);
    shn_form_submit("Next");
    shn_form_fclose();
}

/**
 * set session on general information on areas ofr shelters
 */
function _shn_pre_add_shelter_general_session(){
	$_SESSION['area'] = $_POST['area'];
	//$_SESSION['threat_level'] = $_POST['threat'];
	$_SESSION['disaster'] = $_POST['disaster'];
	$_SESSION['location_address'] = $_POST['location_address'];
	$_SESSION['location'] = shn_location_get_form_submit_loc();
	$_SESSION['name'] = $_POST['name'];
	$_SESSION['text_name'] = $_POST['textname'];
	if($_SESSION['name'] == '/'){
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
	$_SESSION['ownership'] = $_POST['ownership'];
	$_SESSION['owner'] = $_POST['owner'];
	$_SESSION['owner_address'] = $_POST['owner_address'];
	$_SESSION['owner_tel_no'] = $_POST['owner_tel_no'];
	$_SESSION['capacity'] = $_POST['capacity'];
	$_SESSION['land_type'] = $_POST['land_type'];
}

function _shn_pre_validate_shelter_area_general(){
	$error = false;
	if($_POST['area'] == NULL){
		add_error('Area can not be null');
		$error = true;
	}
	if($_POST['disaster'] == NULL){
		add_error('Atleast one disaster should be given');
		$error = true;
	}
	if($_POST['capacity'] != NULL && !_shn_pre_is_positive_number($_POST['capacity'])){
		add_error('capacity should be equal or greater than 0');
		$error = true;
	}
	if($_POST['email'] != NULL && !shn_valid_email($_POST['email'])){
		add_error('Invalid email adress');
		$error = true;
	}
	return $error;
}

/**
 * form interface for tracking general information on areas ofr shelters
 */
function _shn_pre_add_shelter_area_general($res){
	_shn_pre_print_header('Add a suitable area for shelter');
	global $global;  
	global $range;
	global $conf;
	for($i = 0; $i < $res->RecordCount(); $i++){
		$disaster[$res->fields['disaster_uuid']] = $res->fields['disaster'];
		$res->MoveNext();
	}
	
	$building = array('land'=>'land', 'building'=>'building');
	$ownership = array('govenment'=>'govenment', 'private'=>'private');
	
	shn_form_fopen('add_shelter_area','', array('req_message'=>true,));
    if($conf['gis'] == true){
    	shn_form_hidden(array('seq'=>'gis'));
    }
    else{
    	shn_form_hidden(array('seq'=>'confirm'));
    }
    shn_form_fsopen("General Information");
    shn_form_text('Area Name', 'area', '', array('req'=>true));
    shn_form_multi_select('disaster', $disaster, 'Disaster','multiple="true"', array('req'=>true));
    shn_form_textarea('Location Address', 'location_address', '', '');
    shn_form_fsclose();
    shn_form_fsopen(_("Location Details"));
    shn_location($range);
    shn_form_fsclose();
    shn_form_fsopen("Contact Details");
?>
	<div calss="info">
<?php
	echo 'Contact details of the person who is responsible to reponse for establise the shelter after disasters';
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
	shn_form_fsopen("Other Details");
	shn_form_select($ownership, 'Ownership', 'ownership');
	shn_form_text('Owner', 'owner');
	shn_form_fsopen("Contact details of owners");
	shn_form_textarea('Address', 'owner_address', '', '');
	shn_form_text('Contact No', 'owner_tel_no');
	shn_form_fsclose();
	shn_form_text('Capacity', 'capacity');
	shn_form_select($building, 'Land Type', 'land_type');
	shn_form_submit("Next>>");
	shn_form_fsclose();
	shn_form_fclose();
}

?>