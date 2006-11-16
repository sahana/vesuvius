<?php
/* $Id: [sahana_home]/mod/vr3/vol_reg.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Registry Module -- inserts volunteer information into the database
 *
 *  <p>This file is part of the Volunteer Registry module. It
 *  was previously called vol_process.inc.  It was adapted 
 *  from the Organization Registry's process_org.inc.  
 *  This file takes the data entered in the Volunteer 
 *  Registry page (in the Volunteer Registry module) 
 *  and inserts it into the database.  Database tables that are 
 *  referenced are: contact, identity_to_person, location_details, 
 *  person_details, person_status, person_uuid, vm_vol_details, and 
 *  vm_vol_skills.</p>
 *
 *  @package    Trinity_College_vr_demo
 *  @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 *  @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 *  @author     R. Morelli <ralph.morelli@trincoll.edu>
 *  @author     Jonathan Raye <jr978@bard.edu>
 *  @author     Ravindra <ravindra@opensource.lk>
 *
 */

/**
 *  This function takes data entered by the user
 *  on the Volunteer Registry page and inserts them
 *  into the DB, provided there are no errors or
 *  omissions.  The function then gives the user
 *  a unique ID.  If registration is successful, 
 *  a message will pop up to confirm their registration. 
 *  Data is entered in the DB tables: <b>contact</b>,
 *  <b>identity_to_person</b>,<b>location_details</b>,
 *  <b>person_details</b>, <b>person_status</b>, <b>person_uuid</b>,
 *  <b>vm_vol_details</b>, and <b>vm_vol_skills</b>. 
 *  Suggestions for future development: create a confirm email 
 *  field.  Also, some type of contact data 
 *  (e.g. email, phone, address) must be 
 *  required in order for Sahana to communicate 
 *  with the volunteer.     
 */
function shn_vr3_vol_reg()
{
    global $global;
    include_once "vol_add.inc";
    include_once "errors.inc";
    include_once "volunteer.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    include_once $global['approot']."/inc/lib_security/auth_form.inc";
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

    $avail_start=$_POST{"date_avail_start"};
    $avail_end=$_POST{"date_avail_end"};
    $hrs_start=$_POST{"hrs_avail_start"};
    $hrs_end=$_POST{"hrs_avail_end"};

    $country_id='4';   // 4 = USA
    $state_id=$_POST{"2"};
    $city_id=$_POST{"3"};
    //$street_address=$_POST{"address"};

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

   // dbgpost($_POST);
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
    	$vol= new Volunteer(null);
	$vol->__construct(null);
	$vol->setPersonalDetails($name, $dob, $male, $idtype, $idnum);
	$vol->setWorkDetails($organization_id, $job, $specialty);
	$vol->setAvailability($avail_start, $avail_end, $hrs_start, $hrs_end);
	$vol->setContacts($city_id, $contact_phone, $contact_fax, $contact_email);
	//$vol->printVolunteer();
	$vol->addToDB();
    } // if(!error)

    if($error!=true){
?>
    <div id="result_msg">
       <?php echo $name?> was succesfully registered
    </div>
    <br />
<?php
    }
	shn_vr3_vol_add($error);
//    shn_auth_form_user_add(false);
}

/**  
 *  This function allows a volunteer's
 *  registration information to be updated.  It is not 
 *  presently used.  
 */
function _shn_vr3_edit_vol()
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
      _shn_vr_viewform_vol($pid,$error);
      return false;
    }
    
?>
    <div id="result_msg">
       <?php echo $name?> was succesfully Updated
    </div>
    <br />
<h2> Volunteer Registry</h2>
<?php
        _shn_vr_viewform_allvol();    
}

/**  
*  This function deletes volunteers from
*  the database.
*/
function _shn_vr3_del_vol()
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
        _shn_vr_viewform_allvol();   
}

/**
*  This function works in conjunction with the 
*  dbgpost($_POST) located in _shn_vr_reg_vol_cr().
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


