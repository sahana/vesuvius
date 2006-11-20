<?php
/* $Id: [sahana_home]/mod/vm/projects.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- creates the class definition for a project.
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  defines what data are entailed in the definition of a project object:
 *  i.e., Project Name, Start Date, End Date, Description, 
 *  Project Manager, Specialties, Country, State, and City.  If a 
 *  project is being registered, it is given a project ID and its information
 *  is entered into the DB.  If an existing project's data are being edited,
 *  the new information is entered into the DB for the project with the 
 *  corresponding project ID.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Raye <jr978@bard.edu>
 *
 */
 
//error_reporting(E_ALL);

/**
 * Project Class defines a project, and can interface with the database.
 * 
 *  This class gives functions for creating new projects, filling their fields
 *  with data, and dumping it to the database.  It also can populate a project
 *  object with data from the database if that project already exists, modify 
 *  the data, then update the database.
 * 
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 *
 */    
class Project {
   var $proj_id;
   var $name;
   var $mgr_id;
   var $location_id;
   var $start_date;
   var $end_date;
   var $description;
   var $opt_skill_code;
   
/**
 *  Declares a constructor method for a project object.
 * 
 *  This function declares a constructor method that 
 *  is called on each newly-created project object.  
 *  If the project object has not yet been initialized, 
 *  it is given a project ID and a set of fields, including: 
 *  Project Name, Start Date, End Date, Description, Project Manager, 
 *  Specialties, Country, State, and City.  If the project object has 
 *  already been initialized, then the old field values are updated.   
 *
 *  @param bigint $proj_id  The project ID number.  
 *  @access public     
 *  @return void
 */
   function __construct($proj_id) {
	global $global;
	$db= $global['db'];
  	if($proj_id==NULL){
	    $this->proj_id= get_next_project_id();
	}else{
	    $this->proj_id = $proj_id;
	    $q = "select name,mgr_id,location_id,start_date,end_date,description from vm_projects where proj_id = '" . $this->proj_id . "'";
	    $result=$db->Execute($q);
	    $this->name=$result->fields[0];
	    $this->mgr_id=$result->fields[1];
	    $this->location_id=$result->fields[2];
	    $this->start_date=$result->fields[3];
	    $this->end_date=$result->fields[4];
	    $this->description=$result->fields[5];
	    foreach($this->opt_skill_code as $key => $desc){
	        $q="insert into vm_proj_skills(p_uuid,opt_skill_code) values('{$this->p_uuid}','{$this->opt_skill_code[$i]}')";
	        $res=$db->Execute($q);
	    $result=$db->Execute($q);
	    $this->opt_skill_code=$result->fields[0];   
	}
   }
   
/**
 *  This function declares a destructor method that will be called 
 *  when all references to a project object are gone.   
 *
 *  @access public     
 *  @return void
 */
   function __destruct() {
       echo "Default Constructor...\n";
   }
   
/**
 *  This function initializes the fields in the "Project Information"
 *  section of the Register New Project page, which include:
 *  $proj_name, $start_day, $end_day, and $proj_description.  
 *
 *  @param string  $proj_name
 *  @param string  $start_day
 *  @param string  $end_day
 *  @param string  $proj_description
 *  @access public     
 *  @return void
 */
   function setProjectInformation($proj_name,$start_day,$end_day,$proj_description){
	$this->name = $proj_name;
	$this->start_date = $start_day;
	$this->end_date = $end_day;
	$this->description = $proj_description;
   }

/**
 *  This function initializes the fields in the "Details"
 *  section of the Register New Project page, which include:
 *  $proj_name, $start_day, $end_day, and $proj_description.  
 *
 *  @param string  $manager
 *  @param string  $specialties
 *  @access public     
 *  @return void
 */
   function setDetails($manager,$specialties){
	$this->mgr_id = $manager;
	$this->opt_skill_code = $specialties;
   }
   
/**
 *  This function initializes the field $location in the 
 *  "Base Location" section of the Register New Project page.
 *
 *  @param string $location
 *  @access public     
 *  @return void
 */
   function setLocation($location){
	$this->location_id = $location;
   }
   
/**
 *  This function inserts the values entered into the fields 
 *  on the Register New Project page into the DB.  Insertions are 
 *  performed on tables <b>vm_proj_skills</b> and <b>vm_projects</b>.  
 *
 *  @access public     
 *  @return void
 */
   function addToDB() {
   	global $global;
	$db= $global['db'];
   foreach($this->opt_skill_code as $key => $desc){
	  $q="insert into vm_proj_skills(p_uuid,opt_skill_code) values('{$this->p_uuid}','{$this->opt_skill_code[$i]}')";
	  $res=$db->Execute($q);
	}
	$q="insert into vm_projects(proj_id,name,mgr_id,location_id,start_date,end_date,description) values('{$this->proj_id}','{$this->name}','{$this->mgr_id}','{$this->location_id}','{$this->start_date}','{$this->end_date}','{$this->description}')";
	$res=$db->Execute($q);
   }

}
}
?>
   

