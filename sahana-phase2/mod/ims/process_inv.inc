<?php
/**Processing functions(add ,edit,delete,ect) for Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
*             Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/
function _shn_ims_reg_inv_cr()
{
    global $global;
    include_once "reg_inv.inc";
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc"; 
    include_once $global['approot']."/inc/lib_gis/gis_fns.inc";

    
    $error=false;
    $VARCHAR=100;
    list($error,$org_name)=(shn_validate_field($_SESSION['ims']['inv_name'],"Organization Name",$VARCHAR,true))?array($error,$_SESSION['ims']['inv_name']):array(true,NULL);
    $bsd_village=$_SESSION['ims']['bsd_village'];

    if (trim(strlen($_SESSION['ims']['contact_name'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_name=$_SESSION['ims']['contact_name'];
    }

    $contact_address=$_SESSION['ims']['contact_add'];
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_phone=$_SESSION['ims']['contact_add'];
    }
     if (trim(strlen($_SESSION['ims']['contact_mobile'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_mobile=$_SESSION['ims']['contact_mobile'];
    }
    if (trim(strlen($_SESSION['ims']['contact_fax'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
         $contact_fax=$_SESSION['ims']['contact_fax'];
    }
    if (trim(strlen($_SESSION['ims']['contact_mail'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_SESSION['ims']['contact_mail'];
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_or_ims_EMAIL);
            $error=true;
        }
    }
     if (trim(strlen($_SESSION['ims']['contact_web'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_web=$_SESSION['ims']['contact_web'];
    }
    if (trim(strlen($_SESSION['ims']['man_power'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $man_power=$_SESSION['ims']['man_power'];
    }
    if (trim(strlen($_SESSION['ims']['equipment'])) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $equipment=$_SESSION['ims']['equipment'];
    }
    $resources=$_SESSION['ims']['resources'];
    if (trim(strlen($_SESSION['ims']['space']))>$VARCHAR)
	{
		add_error(SHN_ERR_ims_SPACE);
		$error=true;
	}
    else
	{
		$space=$_SESSION['ims']['space'];
	}
   
    $db=$global['db'];
    if($error!=true){
        $org_id = shn_create_uuid('inventory');
        if (empty($org_id)){
            $error=true;
            //("add_org(): ORG_ID generation failed!");
            return false;

        }
        /**GIS*/
        //shn_gis_dbinsert($org_id,0,null,$_POST['loc_x'],$_POST['loc_y'],null);
		$coords = shn_gis_coord_encode(array(array($_POST['loc_x'], $_POST['loc_y'], 0)), 'point');
            $keys_ = array(
                'f_class'         => null,
                'f_type'          => 'point',
                'f_coords'        => $coords,
                'f_module_item'   => $org_id,
                'f_name'          => $org_name,
                'f_url'           => $_SESSION['ims']['contact_web'],
            );
            shn_gis_create_feature($keys_);

		/**GISEND
		*/
        $q="SELECT inv_uuid FROM ims_inventory_records WHERE inv_uuid='{$org_id}'";
        $res=$db->Execute($q);
        if(!$res->EOF){
            $error=true;
            add_error(SHN_ERR_or_ims_ORG_EXISTS);
            return false;
        }
        
        if($error!=true){
	    $added_date=date("Y-m-d");
            //no validation done on other fields as they are not unique
            $q="INSERT INTO  ims_inventory_records(inv_uuid,parent_id,inventory_name,man_power,equipment,resources,space,added_date) VALUES('{$org_id}',0,'{$org_name}','{$man_power}','{$equipment}','{$resources}','{$space}','{$added_date}')";
            $res=$db->Execute($q);

	$q="INSERT INTO location_details(poc_uuid,location_id,address) VALUES('{$org_id}','{$bsd_village}','{$contact_address}')";
            $res=$db->Execute($q);
	    
 $arr = array(
 	array($org_id,'pmob',$contact_mobile),
 	array($org_id,'name',$contact_name),
 	array($org_id,'fax',$contact_fax),
 	array($org_id,'curr',$contact_phone),
 	array($org_id,'email',$contact_mail),
 	array($org_id,'web',$contact_web),
 	);
	 $res=$db->Execute('INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES (?,?,?)',$arr);

	 
	 $insert_array = array();
	 $insert_array['inv_uuid'] = $org_id;
	 if($_SESSION['ims']['destination']=='shelter')
	 {
	 	$insert_array['shel_org_id'] = $_SESSION['ims']['shelter_to'];
	 	$insert_array['shel_org_flag'] = 'shelter';
	 }
	 if($_SESSION['ims']['destination']=='organization')
	 {
	 	$insert_array['shel_org_id'] = $_SESSION['ims']['organization_to'];
	 	$insert_array['shel_org_flag'] = 'org';
	 }
	 //var_dump($insert_array);
	 $res_ims = $db->AutoExecute('ims_inventory_relation', $insert_array, 'INSERT');
	 
/*
            $q="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','curr','{$contact_phone}')";
            $res=$db->Execute($q);

            $q="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','pmob','{$contact_mobile}')";
            $res=$db->Execute($q);

            $q="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','name','{$contact_name}')";
            $res=$db->Execute($q);

            $q="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','fax','{$contact_fax}')";
            $res=$db->Execute($q);
            $q="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','email','{$contact_mail}')";
            $res=$db->Execute($q);
            $q="INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) VALUES('{$org_id}','web','{$contact_web}')";
            $res=$db->Execute($q);*/ //finish editing this section

            //no validation as organization can have multiple locations
            //$q="INSERT INTO org_location(org_id,location_id) VALUES('{$org_id}','{$bsd_village}')";
           // $res=$db->Execute($q);

    }
}
    if((!$chk_branch) or $error){
        if($error!=true){

	    add_confirmation($org_name._t(' Inventory was successfully added'));


        }
	unset($_SESSION['ims']['inv_name']);
	unset($_SESSION['ims']['destination']);
	unset($_SESSION['ims']['shelter_to']);
	unset($_SESSION['ims']['organization_to']);
    unset($_SESSION['ims']['contact_name']);
    unset($_SESSION['ims']['contact_add']);
    unset($_SESSION['ims']['contact_phone']);
    unset($_SESSION['ims']['contact_mobile']);
    unset($_SESSION['ims']['contact_fax']);
    unset($_SESSION['ims']['contact_mail']);
    unset($_SESSION['ims']['contact_web']);
    unset($_SESSION['ims']['man_power']);
    unset($_SESSION['ims']['equipment']);
    unset($_SESSION['ims']['resources']);
    unset($_SESSION['ims']['space']);
    unset($_SESSION['ims']['bsd_village']);
	shn_ims_view_inv();
        //_shn_ims_regform_org($error);
        //return false;
    }else {
         $_SESSION["parent_name"]=$org_name;
         $_SESSION["parent_id"]=$org_id;
         //$_SESSION["opt_org_type"]=$opt_org_type;
         $_SESSION["contact_name"]=$contact_name;
         $_SESSION["contact_address"]=$contact_address;
         $_SESSION["contact_phone"]=$contact_phone;
         $_SESSION["contact_mobile"]=$contact_mobile;
         $_SESSION["contact_fax"]=$contact_fax;
         $_SESSION["contact_email"]=$contact_mail;
         $_SESSION["contact_web"]=$contact_web;
         $_SESSION["man_power"]=$man_power;
         $_SESSION["equipment"]=$equipment;
         $_SESSION["resources"]=$resources;
	 $_SESSION["space"]=$space;
         _shn_ims_regform_operation($error=false);
	
    }
}




function _shn_ims_del_org()
{
    global $global;
    $db=$global['db'];
    $org_id=$_POST{"org_id"};
    $q="SELECT inventory_name FROM  ims_inventory_records WHERE inv_uuid='{$org_id}'";
    $res=$db->Execute($q);
    $org_name=$res->fields[0];
    $q="SELECT * FROM ims_transfer_item WHERE (inv_id_from='{$org_id}' OR inv_id_to='{$org_id}') AND amount_received='-1' AND person_received='-1';";
    $res=$db->Execute($q);
    $transit_id=$res->fields['transit_id'];
    
    if($transit_id!=NULL)
    {
	
	add_error($org_name." ".SHN_ERR_IMS_INVENTORY_IN_USE);
    }
    else
    {

        $table_name = array('ims_inventory_records', 'ims_item_records', 'ims_reorder_level', 'ims_alternate', 'ims_relation', 'sector', 'location_details', 'contact');
	$field_name = array ('inv_uuid', 'inv_id', 'inv_id', 'inv_id', 'inv_id', 'pgoc_uuid', 'poc_uuid', 'pgoc_uuid');
	
	for ($a= 0; $a < 8; $a++ ) {
		$query = "DELETE FROM ".$table_name[$a]." WHERE ".$field_name[$a]." = '{$org_id}'";
		$res=$db->Execute($query); 
	}
        
   	/*
        $q="DELETE FROM  ims_inventory_records WHERE inv_uuid='{$org_id}'";
        $res=$db->Execute($q);
        $q="DELETE FROM ims_item_records WHERE inv_id='{$org_id}';";
        $res=$db->Execute($q);
        $q="DELETE FROM ims_reorder_level WHERE inv_id='{$org_id}';";
        $res=$db->Execute($q);
        $q="DELETE FROM ims_alternate WHERE inv_id='{$org_id}';";
        $res=$db->Execute($q);
        $q="DELETE FROM ims_relation WHERE inv_id='{$org_id}';";
        $res=$db->Execute($q);
        $q="DELETE FROM sector WHERE pgoc_uuid='{$org_id}'";
        $res=$db->Execute($q);
        $q="DELETE FROM location_details WHERE poc_uuid='{$org_id}'";
        $res=$db->Execute($q);
        $q="DELETE FROM contact WHERE pgoc_uuid='{$org_id}'";
        $res=$db->Execute($q); */ //finish editing this section
    
/*
  if($error==true){
		_shn_or_ims_viewform_org($org_id,$error);
        	return false;
	    }
*/
        add_confirmation($org_name._t(' Inventory was successfully deleted'));
    }
  ?>
    
<h2><?php echo _t("Inventory Registry"); ?></h2>
<?php
        _shn_ims_viewform_allorg(null,null,$Limit=20);    
}

function _shn_ims_edit_org()
{
    global $global;
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $error=false;
    $VARCHAR=100;
    $org_id=$_POST{"org_id"};
    
    $ownership = trim($_POST['destination']);
    if($ownership == 'shelter')
    {
    	 $shelter_to = trim($_POST['shelter_to']);
    	 if($shelter_to == '')
    	 {
    	 	//add_error(_t('Shelter Ownership is essential'));
    	 	//$error=true;
    	 }
    	 else
    	 {
    	 	$owner = $shelter_to;
    	 }
    	 
    }
    if($ownership == 'org')
    {
    	$organization_to = trim($_POST['organization_to']);
    if($organization_to == '')
    	 {
    	 	//add_error(_t('Organization Ownership is essential'));
    	 	//$error=true;
    	 }
    	 else
    	 {
    	 	$owner = $organization_to;
    	 }
    }
    
    
    
    
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
   
        
    $_SESSION['ims_1']=$_POST['1'];
    $_SESSION['ims_2']=$_POST['2'];
    $_SESSION['ims_3']=$_POST['3'];
    $_SESSION['ims_4']=$_POST['4'];
    $_SESSION['ims_5']=$_POST['5'];


    $location=_shn_ims_get_locid();
    $location_previous=$_POST['bsd_village'];
   
    if($location=='0')
    {
	$bsd_village=$location_previous;
    }
    else
    {
	$bsd_village=$location;
    }
    $bsd_village=shn_location_get_form_submit_loc();
    if (trim(strlen($_POST{"contact_name"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_name=$_POST{"contact_name"};
    }
/*
    if (trim(strlen($_POST{"contact_add"})) > $CONTACT_ADDRESS){
        add_error(SHN_ERR_or_ims_REG_MAX);
    }else {
       $contact_address=$_POST{"contact_add"};
    }
*/
    $contact_address=$_POST{"contact_add"};
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_phone=$_POST{"contact_phone"};
    }
    if (trim(strlen($_POST{"contact_mobile"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_mobile=$_POST{"contact_mobile"};
    }
    if (trim(strlen($_POST{"contact_fax"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
         $contact_fax=$_POST{"contact_fax"};
    }
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_or_ims_EMAIL);
            $error=true;
        }
    }
    if (trim(strlen($_POST{"contact_web"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $contact_web=$_POST{"contact_web"};
    }
    if (trim(strlen($_POST{"man_power"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $man_power=$_POST{"man_power"};
    }
    if (trim(strlen($_POST{"equipment"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $equipment=$_POST{"equipment"};
    }
    $resources=$_POST{"resources"};
    $space=$_POST{"space"};
    if(!$error){
    $db=$global['db'];
    
    		$sql = "UPDATE ims_inventory_relation SET shel_org_id='{$owner}' shel_org_id='{$ownership}' WHERE inv_uuid='{$org_id}'";
    		$r=$db->Execute($sql);
    		//print $sql;
    		
           //no validation done on other fields as they are not unique
            $q="UPDATE ims_inventory_records SET inventory_name='{$org_name}',man_power='{$man_power}',equipment='{$equipment}',resources='{$resources}',space='{$space}' WHERE inv_uuid='{$org_id}'";
            $res=$db->Execute($q);
           
	    
            $q="UPDATE location_details SET location_id='{$bsd_village}',address='{$contact_address}' WHERE poc_uuid='{$org_id}'";
            $res=$db->Execute($q);
	
	$set_field_values= array($contact_name, $contact_phone, $contact_mobile, $contact_fax, $contact_mail, $contact_web);
	$contact_type_field_name = array('name', 'curr', 'pmob', 'fax', 'email', 'web');

	for ($b = 0; $b < 6; $b++) {
		$query = "UPDATE contact SET contact_value='".$set_field_values[$b]."' WHERE pgoc_uuid = '{$org_id}' AND opt_contact_type ='".$contact_type_field_name[$b]."'";	
		$res=$db->Execute($query);
	}
 	    /*
            $q="UPDATE contact SET contact_value='{$contact_name}' WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='name'";
            $res=$db->Execute($q);
    		$q="UPDATE contact SET contact_value='{$contact_phone}' WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='curr'";
            $res=$db->Execute($q);
            $q="UPDATE contact SET contact_value='{$contact_mobile}' WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='pmob'";
            $res=$db->Execute($q);
            $q="UPDATE contact SET contact_value='{$contact_fax}' WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='fax'";
            $res=$db->Execute($q);
           	$q="UPDATE contact SET contact_value='{$contact_mail}' WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='email'";
            $res=$db->Execute($q);
            $q="UPDATE contact SET contact_value='{$contact_web}' WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='web'";
            $res=$db->Execute($q);*/  //finish editing this section
           
	add_confirmation($org_name._t(' Inventory was successfully updated'));
  ?>
    
<h2>Inventory Registry</h2>
<?php
    }
     if($error==true){
		_shn_ims_viewform_org($org_id,$error);
        	return false;
	 }
        _shn_ims_viewform_allorg(null,null,$Limit=20);    
}
?>
