<?php
/* $Id: [sahana_home]/mod/vm/vol_process.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- 
 *
 *  <p>This file is part of the Volunteer Management module. It
 </p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Ravindra <ravindra@opensource.lk>
 *
 */

/**
 *  This function takes data entered by the user
 *  on the Volunteer Registry page and inserts them
 *  into the DB, provided there are no errors or
 *  omissions.  The function then gives the user
 *  a unique ID.  If registration is successful, 
 *  a message will pop up to confirm their registration. 
 *  Data is entered in the DB tables: <b>person_uuid</b>,
 *  <b>person_details</b>, <b>vm_vol_details</b>, 
 *  <b>person_status</b>, <b>identity_to_person</b>, 
 *  <b>vm_vol_skills</b>, <b>location_details</b>, and
 *  <b>contact</b>.
 *  Suggestions for future development: create a confirm email 
 *  field.  Also, some type of contact data 
 *  (e.g. email, phone, address) must be 
 *  required in order for Sahana to communicate 
 *  with the volunteer.     
 */
function _shn_vm_reg_vol_cr()
{
    global $global;
    include_once "vol_add.inc";
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $VARCHAR=100;
    $error=false;

    list($error,$name)=(shn_validate_field($_POST{"name"},"Full Name",$VARCHAR,true))?array($error,$_POST{"name"}):array(true,NULL);
     
    if (!shn_valid_date($_POST{"dob"})){
        $error=true;
        add_error(SHN_ERR_DOB_INCORRECT);
    }else {    
        $dob=$_POST{"dob"};
    }
    
    $job=$_POST{"job"};
    list($error,$male)=(shn_validate_opt_field('opt_gender',$_POST{"opt_gender"},"Gender",$VARCHAR,false))?array($error,$_POST{"opt_gender"}):array(true,NULL);
    list($error,$idtype)=(shn_validate_opt_field('opt_id_type',$_POST{"opt_id_type"},"Type of Identification",$VARCHAR,false))?array($error,$_POST{"opt_id_type"}):array(true,NULL);

    $idnum=trim($_POST{"idnum"});
    $organization_id = $_POST{"organization"};
    list($error,$specialty)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);

    $avail_start=$_POST{"avail_start"};
    $avail_end=$_POST{"avail_end"};
    $hrs_start=$_POST{"hrs_start"};
    $hrs_end=$_POST{"hrs_end"};

    $country_id='4';   // 4 = USA
    $state_id=$_POST{"2"};
    $city_id=$_POST{"3"};
    $street_address=$_POST{"address"};

    //$project_id = $_POST{"project"};
    //$task_id = $_POST{"task"};

    $contact_phone=$_POST{"contact_phone"};
    $contact_fax=$_POST{"contact_fax"};

    if (trim(strlen($_POST{"contact_email"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_email=$_POST{"contact_email"};
        if(!shn_valid_email($contact_email)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }

    $db=$global['db'];

     /* *** BUG FIX, 6/4/2006 R.Morelli Embedded the queries to 
     * person_seq inside this conditional block.  
     */
    if(!$error) {
      $pid = $db->GenID('person_seq',1);
      $q="select p_uuid from person_uuid where p_uuid='{$pid}'";
      $res=$db->Execute($q);
      if(!$res->EOF){
        $error=true;
        add_error(SHN_ERR_OR_PERSON_EXISTS);
      }
    } // if (!error)

/* Development code to display $_Post and variables used to extract POST data. */

  //  dbgpost($_POST);
    //    echo "name =" . $name;
    //    echo " dob =" . $dob;
    //    echo " job =" . $job;
    //    echo " male =" . $male;
    //    echo " idtype =" . $idtype . " idnum=" . $idnum;
    //    echo " organization_id =" . $organization_id;
    //    $i=0;
    //    while($i<count($specialty)){
    //      echo " specialty= " . $specialty[$i];
    //      $i=$i+1;
    //    }
    //    echo " avail_start = " . $avail_start;
    //    echo " avail_end = " . $avail_end;
    //    echo " hrs_start = " . $hrs_start;
    //    echo " hrs_end = " . $hrs_end;
    //    echo " state_id =" . $state_id;
    //    echo " city_id =" . $city_id;
    //    echo " street_address =" . $street_address;
    //    echo " contact_phone =" . $contact_phone;
    //    echo " contact_fax =" . $contact_fax;
    //    echo " contact_email =" . $contact_email;

    if(!$error){
        $q="insert into person_uuid(p_uuid,full_name) values($pid,'{$name}')";
        $res=$db->Execute($q);
	$q="insert into person_details(p_uuid,birth_date,opt_country,opt_gender,occupation) values($pid,'{$dob}','{$country_id}','{$male}','{$job}')";
        $res=$db->Execute($q);
	$q="insert into vm_vol_details(p_uuid,org_id) values($pid,'{$organization_id}')";
        $res=$db->Execute($q);
        $q="insert into person_status(p_uuid,isReliefWorker) values($pid,1)";
        $res=$db->Execute($q);
 	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$idnum}','{$idtype}')";
        $res=$db->Execute($q);
        $i=0;
	while($i<count($specialty)){
	  $q="insert into vm_vol_skills(p_uuid,opt_skill_code) values($pid,'{$specialty[$i]}')";
	  $res=$db->Execute($q);
	  $i=$i+1;
        }
	$q="insert into vm_vol_details(p_uuid,date_avail_start,date_avail_end,hrs_avail_start,hrs_avail_end) values($pid,'{$avail_start}','{$avail_end}','{$hrs_start}','{$hrs_end}')";
        $res=$db->Execute($q);
	//$q="insert into vm_proj_vol(p_uuid,proj_id,status,opt_skill_type) values($pid,'{$project_id}','assigned','{$task_id}')";
	//$res=$db->Execute($q);

	/* *** BUG FIX, 6/4/2006 R.Morelli Embedded the insertions to location_details and contact inside this if (!error) condition. */

	//	$q="insert into location_details(poc_uuid,location_id,opt_person_loc_type,address) values($pid,'{$bsd_village}','hom','{$contact_address}')";
	$q="insert into location_details(poc_uuid,location_id,opt_person_loc_type,address) values($pid,'{$city_id}','hom','{$street_address}')";
	$res=$db->Execute($q);
	$q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'curr','{$contact_phone}')";
	$res=$db->Execute($q);
	$q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'fax','{$contact_fax}')";
	$res=$db->Execute($q);
	$q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'email','{$contact_email}')";
	$res=$db->Execute($q);
    } // if(!error)

    if($error!=true){

	    $msg= $name." was succesfully registered ";
     	add_confirmation($msg);
    }
    _shn_vm_vol_add($error);
}

/**  
 *  This function allows a volunteer's
 *  registration information to be updated.  It is not 
 *  presently used.  
 */
function _shn_vm_edit_vol()
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
    $job=$_POST{"job"};
    list($error,$male)=(shn_validate_opt_field('opt_gender',$_POST{"opt_gender"},"Gender",$VARCHAR,false))?array($error,$_POST{"opt_gender"}):array(true,NULL);

    list($error,$idtype)=(shn_validate_opt_field('opt_id_type',$_POST{"opt_id_type"},"Type of Identification",$VARCHAR,false))?array($error,$_POST{"opt_id_type"}):array(true,NULL);
    $idnum=trim($_POST{"idnum"});

//    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    list($error,$speciality)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);

    if (is_null($_POST{"1"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $country_id=$_POST{"1"};
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
    if (trim(strlen($_POST{"contact_email"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_email=$_POST{"contact_email"};
        if(!shn_valid_email($contact_email)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }
    $db=$global['db'];
    $q="update person_uuid set full_name='{$name}' where p_uuid=$pid";
    $res=$db->Execute($q);
    $q="update person_details set birth_date='{$dob}',opt_country='{$country_id}',opt_gender='{$male}',occupation='{$job}' where p_uuid=$pid";
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
    $q="update contact set contact_value='{$contact_email}' where pgoc_uuid=$pid and opt_contact_type='email'";
    $res=$db->Execute($q);
    if($error==true){
      _shn_vm_viewform_vol($pid,$error);
      return false;
    }
    $msg= $name." was succesfully updated";
    add_confirmation($msg);
?>

<h2> Volunteer Registry</h2>
<?php
        _shn_vm_viewform_allvol();    
}

/**  
 *  This function deletes volunteers from
 *  the database.
 */
function _shn_vm_del_vol()
{ 
    global $global;
    $db=$global['db'];
    $pid=$_POST{"pid"};
    $q="select full_name from person_uuid where p_uuid=$pid";
    $res=$db->Execute($q);
    $name=$res->fields[0];
    $q="update person_status set isReliefWorker=0 where p_uuid=$pid";
    $res=$db->Execute($q);
  	$msg= "Volunteer was succesfully deleted";
    add_confirmation($msg);
     ?>

    <br />
<h2> Volunteer Registry</h2>
<?php
        _shn_vm_viewform_allvol();   
}

/**
 *  This function works in conjunction with the 
 *  dbgpost($_POST) located in _shn_vm_reg_vol_cr().
 *  It displays the data that is missing when 
 *  a volunteer does not register properly.
 */
function dbgpost($post) {
        foreach($post as $key => $value) {
          if (is_array($value)) {
              echo "--$key (array)---start--<br />";
                dbgpost($value);
                echo "--$key (array)---end----<br />";
            } else {
                echo "$key: $value <br>";
            }
        }
    } 
?>
