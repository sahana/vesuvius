<?php
/**Processing functions(add ,edit,delete,ect) for Volunteers of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/


function _shn_or_reg_vol_cr()
{
    global $global;
    include_once "reg_vol.inc";
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $VARCHAR=100;
    $error=false;
    list($error,$name)=(shn_validate_field($_POST{"name"},"Full Name",$VARCHAR,true))?array($error,$_POST{"name"}):array(true,NULL);
    if (!shn_valid_date($_POST{"dob"})){
        $error=true;
    }else {    
        $dob=$_POST{"dob"};
    }
    list($error,$male)=(shn_validate_opt_field('opt_gender',$_POST{"opt_gender"},"Gender",$VARCHAR,false))?array($error,$_POST{"opt_gender"}):array(true,NULL);
    $job=$_POST{"job"};
    $nic=trim($_POST{"nic"});
    $pas=trim($_POST{"pas"});
    $dln=trim($_POST{"dln"});
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=$_POST{"4"};
    }
    $parents=shn_or_get_parents($bsd_village);
    $bsd_country=$parents[0][0];
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_fax=$_POST{"contact_fax"};
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }
    $db=$global['db'];
    $pid = $db->GenID('person_seq',1);
    $q="select p_uuid from person_uuid where p_uuid='{$pid}'";
    $res=$db->Execute($q);
    if(!$res->EOF){
        $error=true;
        add_error(SHN_ERR_OR_PERSON_EXISTS);
    }
    if(!$error){
        $q="insert into person_uuid(p_uuid,full_name) values($pid,'{$name}')";
        $res=$db->Execute($q);
	$q="insert into person_details(p_uuid,birth_date,opt_country,opt_gender,occupation) values($pid,'{$dob}','{$bsd_country}','{$male}','{$job}')";
    $res=$db->Execute($q);
    $q="insert into person_status(p_uuid,isReliefWorker) values($pid,1)";
    $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$nic}','nic')";
   $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$pas}','pas')";
    $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$dln}','dln')";
    $res=$db->Execute($q);
    $i=0;
    while($i<count($sector)){
            $q="insert into sector(pgoc_uuid,opt_sector) values($pid,'{$sector[$i]}')";
           $res=$db->Execute($q);
           $i=$i+1;
        }
    }
    $q="insert into location_details(poc_uuid,location_id,opt_person_loc_type,address) values($pid,'{$bsd_village}','hom','{$contact_address}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'curr','{$contact_phone}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'fax','{$contact_fax}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'email','{$contact_mail}')";
    $res=$db->Execute($q);
    if($error!=true){
?>
    <div id="result_msg">
       <?php echo $name?> was succesfully registered
    </div>
    <br />
<?php
    }
    _shn_or_regform_vol($error);
}

function _shn_or_edit_vol()
{
    global $global;
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $VARCHAR=100;
    $error=false;
    $pid=$_POST{"pid"};
list($error,$name)=(shn_validate_field($_POST{"name"},"Full Name",$VARCHAR,true))?array($error,$_POST{"name"}):array(true,NULL);
    if (!shn_valid_date($_POST{"dob"})){
        $error=true;
        add_error(SHN_ERR_DOB_INCORRECT);
    }else {    
        $dob=$_POST{"dob"};
    }
    list($error,$male)=(shn_validate_opt_field('opt_gender',$_POST{"opt_gender"},"Gender",$VARCHAR,false))?array($error,$_POST{"opt_gender"}):array(true,NULL);
    $job=$_POST{"job"};
    $nic=trim($_POST{"nic"});
    $pas=trim($_POST{"pas"});
    $dln=trim($_POST{"dln"});
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    if (is_null($_POST{"1"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_country=$_POST{"1"};
    }
    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=$_POST{"4"};
    }
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_fax=$_POST{"contact_fax"};
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }
    $db=$global['db'];
    $q="update person_uuid set full_name='{$name}' where p_uuid=$pid";
    $res=$db->Execute($q);
	$q="update person_details set birth_date='{$dob}',opt_country='{$bsd_country}',opt_gender='{$male}',occupation='{$job}' where p_uuid=$pid";
    $res=$db->Execute($q);
	$q="update identity_to_person set serial='{$nic}' where p_uuid=$pid and opt_id_type='nic'";
    $res=$db->Execute($q);
$q="update identity_to_person set serial='{$pas}' where p_uuid=$pid and opt_id_type='pas'";
    $res=$db->Execute($q);
    $q="update identity_to_person set serial='{$dln}' where p_uuid=$pid and opt_id_type='dln'";
    $res=$db->Execute($q);
    $q="delete from sector where pgoc_uuid=$pid";
    $res=$db->Execute($q);
    $i=0;
    while($i<count($sector)){
        $q="insert into sector(pgoc_uuid,opt_sector) values($pid,'{$sector[$i]}')";
        $res=$db->Execute($q);
        $i=$i+1;
    }
    $q="update location_details set location_id='{$bsd_village}',address='{$contact_address}' where poc_uuid=$pid";
    $res=$db->Execute($q);
    $q="update contact set contact_name='{$contact_name}' where pgoc_uuid=$pid and opt_contact_type='name'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_phone}' where pgoc_uuid=$pid and opt_contact_type='curr'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_fax}' where pgoc_uuid=$pid and opt_contact_type='fax'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_mail}' where pgoc_uuid=$pid and opt_contact_type='email'";
    $res=$db->Execute($q);
    if($error==true){
		_shn_or_viewform_vol($pid,$error);
        	return false;
	    }
    
?>
    <div id="result_msg">
       <?php echo $name?> was succesfully Updated
    </div>
    <br />
<h2> Volunteer Registry</h2>
<?php
        _shn_or_viewform_allvol();    
}


function _shn_or_del_vol()
{ 
    global $global;
    $db=$global['db'];
    $pid=$_POST{"pid"};
    $q="select full_name from person_uuid where p_uuid=$pid";
    $res=$db->Execute($q);
    $name=$res->fields[0];
    $q="update person_status set isReliefWorker=0 where p_uuid=$pid";
    $res=$db->Execute($q);
     ?>
    <div id="result_msg">
       <?php echo $name?> Volunteer was succesfully Deleted
    </div>
    <br />
<h2> Volunteer Registry</h2>
<?php
        _shn_or_viewform_allvol();   
}
?>
