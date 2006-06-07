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
	      Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/
function _shn_ims_reg_inv_cr()
{
    global $global;
    include_once "reg_inv.inc";
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_security/authenticate.inc"; 
    include_once $global['approot']."/inc/lib_validate.inc"; 
    $error=false;
    $VARCHAR=100;
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
   // list($error,$opt_org_type)=(shn_validate_opt_field('opt_org_type',$_POST{"opt_org_type"},"Organization Type",$VARCHAR,false))?array($error,$_POST{"opt_org_type"}):array(true,NULL);
   // list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    $range= shn_ims_get_loc_range();
    /*if (is_null($_POST{$range["end"]})){
        $error=true;
        add_error(SHN_ERR_or_ims_LOCATION_INCOMPLETE);
    }else {    */
        $bsd_village=trim($_POST{$range["end"]});
    //}
    //if (trim(strlen($_POST{"reg_no"})) > $VARCHAR){
      //  add_error(SHN_ERR_or_ims_REG_MAX);
       // $error=true;
   // }else {
     //   $reg_no=$_POST{"reg_no"};
   // }
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
    if (trim(strlen($_POST{"space"}))>$VARCHAR)
	{
		add_error(SHN_ERR_ims_SPACE);
		$error=true;
	}
    else
	{
		$space=$_POST{"space"};
	}
   // if (trim(strlen($_POST{"account_name"})) > $VARCHAR){
     //   $error=true;
       // add_error(SHN_ERR_or_ims_REG_MAX);
    //}else {
       // $account_name=$_POST{"account_name"};
   // }
    //$chk_avail=(isset ($_POST{"chk_avail"}))?1:0;
    //$chk_branch=(isset ($_POST{"chk_branch"}))?1:0;
    $db=$global['db'];
    if($error!=true){
        $org_id = $db->GenID('org_seq',1);
        if (empty($org_id)){
            $error=true;
            //("add_org(): ORG_ID generation failed!");
            return false;
        }
        $q="select inv_uuid from ims_inventory_records where inv_uuid='{$org_id}'";
        $res=$db->Execute($q);
        if(!$res->EOF){
            $error=true;
            add_error(SHN_ERR_or_ims_ORG_EXISTS);
            return false;
        }
        if($error!=true){
            //no validation done on other fields as they are not unique
            $q="insert into  ims_inventory_records(inv_uuid,parent_id,inventory_name,man_power,equipment,resources,space)values($org_id,0,'{$org_name}','{$man_power}','{$equipment}','{$resources}','{$space}')";
            $res=$db->Execute($q);
//print
		
           /*
            $i=0;
            while($i<count($sector)){
                $q="insert into sector(pgoc_uuid,opt_sector) values($org_id,'{$sector[$i]}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            */
            $q="insert into location_details(poc_uuid,location_id,address) values($org_id,'{$bsd_village}','{$contact_address}')";
            $res=$db->Execute($q);
//print $q;
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'curr','{$contact_phone}')";
            $res=$db->Execute($q);
//print $q;
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'pmob','{$contact_mobile}')";
            $res=$db->Execute($q);
//print $q;
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'name','{$contact_name}')";
            $res=$db->Execute($q);
//print $q;
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'fax','{$contact_fax}')";
            $res=$db->Execute($q);
//print $q;
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'email','{$contact_mail}')";
            $res=$db->Execute($q);
//print $q;
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'web','{$contact_web}')";
            $res=$db->Execute($q);
//print $q;
            //no validation as organization can have multiple locations
            $q="insert into org_location(org_id,location_id) values($org_id,'{$bsd_village}')";
            $res=$db->Execute($q);
//print $q;
    }
}
    if((!$chk_branch) or $error){
        if($error!=true){
?>
    <div id="result_msg">
       <?php echo $org_name?> Inventory was succesfully Added
    </div>
    <br />
<?php
        }
        _shn_ims_regform_org($error);
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
    $q="select inventory_name from  ims_inventory_records where inv_uuid=$org_id";
    $res=$db->Execute($q);
    $org_name=$res->fields[0];
    $q="delete from  ims_inventory_records where inv_uuid=$org_id";
    $res=$db->Execute($q);
    $q="delete from sector where pgoc_uuid=$org_id";
    $res=$db->Execute($q);
    $q="delete from location_details where poc_uuid=$org_id";
    $res=$db->Execute($q);
    $q="delete from contact where pgoc_uuid=$org_id";
    $res=$db->Execute($q);
/*
  if($error==true){
		_shn_or_ims_viewform_org($org_id,$error);
        	return false;
	    }
*/
  ?>
    <div id="result_msg">
       <?php echo $org_name?> Inventory was succesfully Deleted
    </div>
    <br />
<h2>Inventory Registry</h2>
<?php
        _shn_ims_viewform_allorg();    
}

function _shn_ims_edit_org()
{
    global $global;
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $error=false;
    $VARCHAR=100;
    $org_id=$_POST{"org_id"};
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
   // list($error,$org_type)=(shn_validate_opt_field('opt_org_type',$_POST{"opt_org_type"},"Organization Type",$VARCHAR,false))?array($error,$_POST{"opt_org_type"}):array(true,NULL);
   // list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
   	$range= shn_ims_get_loc_range();
    /*if (is_null($_POST{$range["end"]})){
        $error=true;
        add_error(SHN_ERR_or_ims_LOCATION_INCOMPLETE);
    }else {    */
        $bsd_village=trim($_POST{$range["end"]});
   // }
  /*
    if (trim(strlen($_POST{"reg_no"})) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error=true;
    }else {
        $reg_no=$_POST{"reg_no"};
    }
    */
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
           //no validation done on other fields as they are not unique
            $q="update ims_inventory_records set inventory_name='{$org_name}',man_power='{$man_power}',equipment='{$equipment}',resources='{$resources}',space='{$space}' where inv_uuid=$org_id";
            $res=$db->Execute($q);
            /*
            $q="delete from sector where pgoc_uuid=$org_id";
            $res=$db->Execute($q);
            $i=0;
            while($i<count($sector)){
                $q="insert into sector(pgoc_uuid,opt_sector) values($org_id,'{$sector[$i]}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            */
            $q="update location_details set location_id='{$bsd_village}',address='{$contact_address}' where poc_uuid=$org_id";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_name}' where pgoc_uuid=$org_id and opt_contact_type='name'";
            $res=$db->Execute($q);
    		$q="update contact set contact_value='{$contact_phone}' where pgoc_uuid=$org_id and opt_contact_type='curr'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_mobile}' where pgoc_uuid=$org_id and opt_contact_type='pmob'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_fax}' where pgoc_uuid=$org_id and opt_contact_type='fax'";
            $res=$db->Execute($q);
           	$q="update contact set contact_value='{$contact_mail}' where pgoc_uuid=$org_id and opt_contact_type='email'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_web}' where pgoc_uuid=$org_id and opt_contact_type='web'";
            $res=$db->Execute($q);
           
  ?>
    <div id="result_msg">
       <?php echo $org_name?> Inventory was succesfully Updated
    </div>
    <br />
<h2>Inventory Registry</h2>
<?php
    }
     if($error==true){
		_shn_ims_viewform_org($org_id,$error);
        	return false;
	 }
        _shn_ims_viewform_allorg();    
}
?>
