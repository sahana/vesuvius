<?php
/* $Id: [sahana_home]/mod/vm/projects.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- creates the class definition for a volunteer.
 *
 *  <p>This file is part of the Volunteer Management module.  It
 *  defines what data are entailed in the definition of a volunteer object:
 *  i.e., Name, DOB, Gender, Type of ID, ID Number, Affiliation, Occupation, 
 *  Specialties, Start Date, End Date, Start Hours, End Hours, Country, State,
 *  City, Phone, Fax, and Email. 
 *  If a volunteer is being registered, it is given a volunteer ID and its information
 *  is entered into the DB.  If an existing volunteer's information is being edited,
 *  the new information is entered into the DB for the project with the 
 *  corresponding volunteer ID.</p>
 *
 * @package    Trinity_College_vm_demo
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 *
 */

//error_reporting(E_ALL);

class Volunteer {
   var $name;
   var $p_uuid;
   var $dob;
   var $gender;
   var $id_type;
   var $id_num;
   var $org;
   var $job;
   var $skills = array();
   var $start_date;
   var $stop_date;
   var $start_hour;
   var $stop_hour;
   var $city;
   var $phone;
   var $fax;
   var $email;
     
/**
 *  Declares a constructor method for a volunteer object.
 * 
 *  This function declares a constructor method that 
 *  is called on each newly-created volunteer object.  
 *  If the volunteer object has not yet been initialized, 
 *  it is given a volunteer ID and a set of fields, including: 
 *  Name, DOB, Gender, Type of ID, ID Number, Affiliation, Occupation, 
 *  Specialties, Start Date, End Date, Start Hours, End Hours, Country, State,
 *  City, Phone, Fax, and Email.  If the volunteer object has 
 *  already been initialized, then the old field values are updated.   
 *
 *  @param bigint $id  The volunteer's number.  
 *  @access public     
 *  @return void
 */
   function __construct($id) {
	global $global;
	$db= $global['db'];
  	if($id==NULL){
	    $q = "select id from person_seq";
	    $result=$db->Execute($q);
	    $id=$result->fields[0];
	    $this->p_uuid = $id;
	    $q="update person_seq set id = '{$this->p_uuid}'";
	    $res=$db->Execute($q);

	}else{
	    $this->p_uuid = $id;
	    $q = "select full_name from person_uuid where p_uuid = '" . $this->p_uuid . "'";
	    $result=$db->Execute($q);
	    $this->name=$result->fields[0];
	    $q = "select birth_date, opt_gender, occupation from person_details where p_uuid = '" . $this->p_uuid . "'";
	    $result=$db->Execute($q);
	    $this->dob=$result->fields[0];
	    $this->gender=$result->fields[1];
	    $this->job=$result->fields[2];
	    $q = "select opt_skill_code from vm_vol_skills where p_uuid = '" . $this->p_uuid . "'";
	    $result=$db->Execute($q);
	    $i=0;
	    while(!$result==NULL && !$result->EOF){
		$this->skills[$i++] = $result->fields[0];
		$result->MoveNext();
	    }
	    //$this->skills=$result->fields[0];
	    $q = "select org_id, date_avail_start, date_avail_end, hrs_avail_start, hrs_avail_end from vm_vol_details where p_uuid = '" . $this->p_uuid . "'";
	    $result=$db->Execute($q);
	    $this->org=$result->fields[0];
	    $this->start_date=$result->fields[1];
	    $this->stop_date=$result->fields[2];
	    $this->start_hour=$result->fields[3];
	    $this->stop_hour=$result->fields[4];
	    $q = "select opt_id_type, serial from identity_to_person where p_uuid = '" . $this->p_uuid . "'";
	    $result=$db->Execute($q);
	    $this->id_type=$result->fields[0];
	    $this->id_num=$result->fields[1];
	    $q = "select location_id from location_details where poc_uuid = '" . $this->p_uuid . "'";
	    $result=$db->Execute($q);
	    $this->city=$result->fields[0];
	    $q = "select contact_value from contact where p_uuid = '" . $this->p_uuid . "' and opt_contact_type = 'email'";
	    $result=$db->Execute($q);
	    $this->email=$result->fields[0];
	    $q = "select contact_value from contact where p_uuid = '" . $this->p_uuid . "' and opt_contact_type = 'fax'";
	    $result=$db->Execute($q);
	    $this->fax=$result->fields[0];
	    $q = "select contact_value from contact where p_uuid = '" . $this->p_uuid . "' and opt_contact_type = 'curr'";
	    $result=$db->Execute($q);
	    $this->phone=$result->fields[0];
	}
   }

/**
 *  This function declares a destructor method that will be called 
 *  when all references to a volunteer object are gone.   
 *
 *  @access public     
 *  @return void
 */
   function __destruct() {
       //echo "Default Constructor...\n";
   }
   
/**
 *  This function initializes the fields in the 
 *  "Personal Details" section of the Volunteer Registry page,
 *  including: Name, DOB, Gender, ID type, and ID Number.  
 *
 *  @param string $full_name
 *  @param string $birth_date
 *  @param string $sex
 *  @param string $type_id
 *  @param string $num_id
 *  @access public     
 *  @return void
 */
   function setPersonalDetails($full_name,$birth_date,$sex,$type_id,$num_id){
	$this->name = $full_name;
	$this->dob = $birth_date;
	$this->gender = $sex;
	$this->id_type = $type_id;
	$this->id_num = $num_id;
   }
   
/**
 *  This function initializes the fields in the 
 *  "Work Details" section of the Volunteer Registry page,
 *  including: affiliation, occupation, specialties.
 *
 *  @param string $affiliation
 *  @param string $occupations
 *  @param string $specialties
 *  @access public     
 *  @return void
 */
   function setWorkDetails($affiliation,$occupation,$specialties) {
        $this->org = $affiliation;
  	$this->job = $occupation;
  	$this->skills = $specialties;
   }
   
/**
 *  This function initializes the fields in the 
 *  "Availability" section of the Volunteer Registry page,
 *  including: Start Availability, End Availability, Start Time, and End Time.
 *
 *  @param string $start_avail
 *  @param string $end_avail
 *  @param string $start_time
 *  @param string $end_time
 *  @access public     
 *  @return void
 */
   function setAvailability($start_avail,$end_avail,$start_time,$end_time) {
  	$this->start_date = $start_avail;
	$this->stop_date = $end_avail;
	$this->start_hour = $start_time;
	$this->stop_hour = $end_time;
   }
   
/**
 *  This function initializes the fields in the 
 *  "Location" and "Contacts" sections of the Volunteer Registry page,
 *  including: Location, Phone, Fax, and Email.
 *
 *  @param string $location
 *  @param string $phone_number
 *  @param string $fax_number
 *  @param string $email_address
 *  @access public     
 *  @return void
 */
   function setContacts($location,$phone_num,$fax_num,$email_address) {
	$this->city = $location;
   	$this->phone = $phone_num;
	$this->fax = $fax_num;
	$this->email = $email_address;
   }
   
/**
 *  This function inserts the values entered into the fields 
 *  on the Volunteer Registry page into the DB.  Insertions are 
 *  performed on tables <b>person_uuid</b>, <b>person_details</b>,
 *  <b>identity_to_person</b>, and <b>vm_vol_details</b>.  
 *
 *  @access public     
 *  @return void
 */
   function addToDB() {
   	global $global;
	$db= $global['db'];
   	$q="insert into person_uuid(p_uuid,full_name) values('{$this->p_uuid}','{$this->name}')";
        $res=$db->Execute($q);
	$q="insert into person_details(p_uuid,birth_date,opt_gender,occupation) values('{$this->p_uuid}','{$this->dob}','{$this->gender}','{$this->job}')";
        $res=$db->Execute($q);
     	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values('{$this->p_uuid}','{$this->id_num}','{$this->id_type}')";
        $res=$db->Execute($q);
	$i=0;
	while($i<count($this->skills)){
	  $q="insert into vm_vol_skills(p_uuid,opt_skill_code) values('{$this->p_uuid}','{$this->skills[$i]}')";
	  $res=$db->Execute($q);
	  $i=$i+1;
        }

	/*foreach($this->skills as $key => $desc){
	  $q="insert into vm_vol_skills(p_uuid,opt_skill_code) values('{$this->p_uuid}','{$this->skills[$i]}')";
	  $res=$db->Execute($q);
	}*/
	$q="insert into vm_vol_details(p_uuid,org_id,date_avail_start,date_avail_end,hrs_avail_start,hrs_avail_end) values('{$this->p_uuid}','{$this->org}','{$this->start_date}','{$this->stop_date}','{$this->start_hour}','{$this->stop_hour}')";
        $res=$db->Execute($q);
	$q="insert into location_details(poc_uuid,location_id) values('{$this->p_uuid}','{$this->city}')";
	$res=$db->Execute($q);
	$q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$this->p_uuid}','curr','{$this->phone}')";
	$res=$db->Execute($q);
	$q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$this->p_uuid}','fax','{$this->fax}')";
	$res=$db->Execute($q);
	$q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values('{$this->p_uuid}','email','{$this->email}')";
	$res=$db->Execute($q);

   }
  
/**
 *  This function updates the values entered into the fields 
 *  on the Volunteer Registry page into the DB.  Updates are 
 *  performed on tables <b>person_uuid</b>, <b>person_details</b>,
 *  <b>identity_to_person</b>, and <b>vm_vol_details</b>.  
 *
 *  @access public     
 *  @return void
 */
 function updateDB() {
   	global $global;
	$db= $global['db'];
	$q="update person_uuid set full_name='{$this->name}' where p_uuid='{$this->p_uuid}'";
	$res=$db->Execute($q);
	$q="update person_details set birth_date='{$this->dob}',opt_gender='{$this->gender}',occupation='{$this->job}' where p_uuid='{$this->p_uuid}'";
	$res=$db->Execute($q);
	$q="update identity_to_person set serial='{$this->id_num}' where p_uuid='{$this->p_uuid}' and opt_id_type='{$this->id_type}'";
	$res=$db->Execute($q);
	$q="delete from vm_vol_skills where p_uuid='{$this->p_uuid}'";
	$res=$db->Execute($q);
	$i=0;
	while($i<count($this->skills)){
	  $q="insert into vm_vol_skills(p_uuid,opt_skill_code) values('{$this->p_uuid}','{$this->skills[$i]}')";
	  $res=$db->Execute($q);
	  $i=$i+1;
        }
	$q="update location_details set location_id='{$this->city}', where poc_uuid='{$this->p_uuid}'";
	$res=$db->Execute($q);
	$q="update contact set contact_value='{$this->phone}' where pgoc_uuid='{$this->p_uuid}' and opt_contact_type='curr'";
	$res=$db->Execute($q);
	$q="update contact set contact_value='{$this->fax}' where pgoc_uuid='{$this->p_uuid}' and opt_contact_type='fax'";
	$res=$db->Execute($q);
	$q="update contact set contact_value='{$this->email}' where pgoc_uuid='{$this->p_uuid}' and opt_contact_type='email'";
	$res=$db->Execute($q);
	$q="update vm_vol_details set org_id='{$this->org}',date_avail_start='{$this->start_date}',date_avail_end='{$this->stop_date}',hrs_avail_start='{$this->start_hour}',hrs_avail_end='{$this->stop_hour}' where p_uuid='{$this->p_uuid}'";
	$res=$db->Execute($q);
    }//updateDB()
  
   function printVolunteer($no=NULL) {
	$q="name: {$this->name}<br>";
	$q.="p_uuid: {$this->p_uuid}<br>";
	$q.="dob: {$this->dob}<br>";
	$q.="gender: {$this->gender}<br>";
	$q.="id_type: {$this->id_type}<br>";
	$q.="id_num: {$this->id_num}<br>";
	$q.="org: {$this->org}<br>";
	$q.="job: {$this->job}<br>";
	$q.="skills: {$this->skills}<br>";
	$q.="start_date: {$this->start_date}<br>";
	$q.="stop_date: {$this->stop_date}<br>";
	$q.="start_hour: {$this->start_hour}<br>";
	$q.="stop_hour: {$this->stop_hour}<br>";
	$q.="city: {$this->city}<br>";
	$q.="phone: {$this->phone}<br>";
	$q.="fax: {$this->fax}<br>";
	$q.="fax: {$this->email}<br>";
	echo $q;
   }
   
}
?>


