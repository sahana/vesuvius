<?php
/* $Id: [sahana_home]/mod/vm/proj_add.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- registers a new project.
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates the Register New Project page, which allows a user to register 
 *  a new project.  It includes a section for Project Information (the
 *  fields in which are name, start/end date, and description), a section 
 *  for Project Details (the fields in which are project manager and 
 *  specialties), and a section for Project Address (the fields in which 
 *  are state, city, and street address).  There is a submit button at the 
 *  bottom of the page.  When clicked, it enters the project into the database, 
 *  provided there were no errors/omissions in the registration.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 *   
 *
 */

global $global;

/** Contains library functions for creating forms */
include_once($global['approot'].'/inc/lib_form.inc');
/** Contains library functions for validating forms */
include_once($global['approot'].'/inc/lib_validate.inc');
/** Contains library functions for error checking end-user entered data */
include_once($global['approot'].'/inc/lib_errors.inc');
/** Contains library functions for creating forms in VM and VR Modules */
include_once $global['approot']."/mod/vm/lib_vm.inc";
/** Contains utility functions for VM and VR Modules */
include_once $global['approot']."/mod/vm/utility_functions.inc";

/**
 *  Creates the Register New Project page.
 *
 *  This function generates the three sections on the 
 *  Register New Project page.  The first section is Project 
 *  Information.  It includes project name, start/end date, and 
 *  project description.  The second section is Project Details.  
 *  It includes project manager and specialties.  The third section
 *  is Project Address.  It includes state, city, and street address.  
 *  The function also creates the "Submit" button, which appears at 
 *  bottom of the three sections.
 *
 *  @access public
 *  @return void 
 */
function _shn_vm_regform_proj_add($error=false)
{   
	if ($errors)                // This code appears to have no effect on whether errors are displayed and 
	    display_errors();       //  can possibly be commented out.  Errors are displayed automatically
                                    //  by shn_stream_close() in inc/lib_stream_html.inc

				    // Project is added only if both Name and Specialties fields are non-null
	if($_POST['project_name']!=NULL){
	    $valid = _shn_vm_validate_project_data();     // Validate the form data
	    if($valid)  {
		project_addto_db();                       // Add to DB
	    }
	}
	global $global;
	$db = $global['db'];
?>
<h2 align="center"><?php echo _("Register New Project")?></h2>
<?php
//  start section 1
	shn_form_fopen(proj_add, vm);
	shn_form_fsopen(_("Project Information"));
			
	shn_form_text(_("Project Name"),"project_name",'size="50"',array('req'=>true));
	shn_form_date(_("Start Date : "),'start_date',$extra_opts=NULL);
	echo "<br>";
	shn_form_date(_("End Date : "),'end_date',$extra_opts=NULL);
	echo "<br>";
//_shn_form_date(_("Start Date : "),'start_date', $initdate=NULL, $required=true, $format='YYYY-MM-DD'); 
//	_shn_form_date(_("End Date : "),'end_date', $initdate=NULL, $required=true, $format='YYYY-MM-DD'); 
?>
</select><br>
<?php
			
	shn_form_textarea(_("Description : "),"project_description");
	shn_form_fsclose();

//  start section 2
        shn_form_fsopen(_("Details"));

        $q = "select person_uuid.p_uuid, full_name from person_uuid, vm_vol_skills where opt_skill_code = 'mgr' and person_uuid.p_uuid = vm_vol_skills.p_uuid order by full_name asc";
        $res_man=$db->Execute($q);
        $managers=array();
        while(!$res_man==NULL && !$res_man->EOF){
	    $managers[$res_man->fields[0]]=$res_man->fields[1];
            $res_man->MoveNext();
        }

        shn_form_select($managers, 'Project Manager: (A Volunteer with SITE MANAGER skill) ', 'manager_id', NULL, NULL);
        shn_form_opt_multi_select('opt_skill_type','Specialties : <br />(Hold the CTRL-Key to choose more than one skill)','multiple="true"',array('req'=>true));
//   	_shn_form_select_specialities($error);
	shn_form_fsclose();
	
//  start section 3  
//    $location_inf = _shn_location_form_volunteer('2','3'); 
//	shn_location_form_org(1,5);
    shn_form_fsopen("Base Location");
//    shn_location(null,null,null,$extra_opts=NULL);
//  RAM Hack: The following call to shn_location is copied from reg_org.inc. The checkbox
//  doesn't seem to work if the second parameter is NULL.
//    shn_location(null,$_SESSION['org']['loc'],null,$extra_opts=NULL);
    shn_location(null,null,null,$extra_opts);
    shn_form_fsclose();
?>
<br />
<center>
<?php
	shn_form_submit("Submit"); //create the submit button
        shn_form_fclose();
?>
</center>
<br />
<?php
} //  end _shn_vm_regform_proj_add()

/**
 *  Validates data for new project .  
 *
 *  To be a valid form, neither the project name nor the specialties fields may be NULL.
 *
 *  @access public
 *  @return boolean
 */

function _shn_vm_validate_project_data(){
//    dbgpost($_POST);    //  Uncomment this line to display $_POST values.
	clean_errors();
	$valid_flag=true;;

	if(null == ($_POST['project_name'])){       // Name must not be NULL
			add_error(_("Please Enter the Project Name"));
			$valid_flag=false;
	}
	
	// Specialties Field must not be NULL -- If shn_validate_opt_field raises an error flag, an error message will automatically be
	//   displayed by the shn_stream_close() function in inc/lib_stream_html.inc. 
	list($error,$specialty)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Specialties",$max_len=100,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);
//	list($error, $specialty)=array($error, $_POST{'opt_skill_type'});  // RAM: I'm not sure what this does---appears to have no effect on error checking

	if ($error) {
	    $valid_flag=false;
	}
	return $valid_flag;
}

/**
 *  Adds data for new project into the database.  
 *
 *  This function posts data entered in the Register New Projects
 *  page into the DB.  It also assigns the project a unique project id.
 *  Data is entered in the DB tables <b>vm_proj_skills</b> and
 *  <b>vm_projects</b>.  
 *
 *  @access public
 *  @return void
 */

function project_addto_db(){
	global $global;
	$db = $global['db'];

	$proj_id = get_next_project_id();

//list($error,$specialty)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);
// RAM -- 11/26/2006 -- BUG FIX:  $VARCHAR is null and is invalid argument for $max_len of the field.  Set to 100 because opt_skill_code is VARCHAR(100) in DB.

//RAM -- 12-3-06 These statements were moved into the validate method just above.
//list($error,$specialty)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Volunteer Service",$max_len=100,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);
//list($error, $specialty)=array($error, $_POST{'opt_skill_type'});
//	if ($error){
//	    echo "There was an error";
//	    return false;
//	}

$i=0;
while($i<count($specialty)){
	  $q="insert into vm_proj_skills(p_uuid,opt_skill_code) values('" . $proj_id . "','" . $specialty[$i] . "')";
	 // echo $q;
	  $res=$db->Execute($q);
	  $i=$i+1;
        }

// RAM: This code is added to handle the check box in the base location subform.  If the checkbox is checked, then the location_id is set to 0.
// This will occur even if the user has entered values in the locations fields (country, state, city).

/** ravi **/
    $location_id=shn_location_get_form_submit_loc();
    if ($location_id==-1){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }

//echo "Location_id = " . $location_id;

//$q="insert into vm_projects (proj_id, name, mgr_id, location_id, start_date, end_date, description) VALUES ('$proj_id','{$_POST['project_name']}','{$_POST['manager_id']}','{$_POST['3']}','{$_POST['start_date']}','{$_POST['end_date']}','{$_POST['project_description']}')";

// RAM: Modification required to add Location Unknown checkbox.  Changed $_POST['3'] to $location_id, which is set above.
$q="insert into vm_projects (proj_id, name, mgr_id, location_id, start_date, end_date, description) VALUES ('$proj_id','{$_POST['project_name']}','{$_POST['manager_id']}','{$location_id}','{$_POST['start_date']}','{$_POST['end_date']}','{$_POST['project_description']}')";
	 
	$result=$db->Execute($q);
	//echo "<div id=\"note\"><p><strong>Your project has been successfully added!</strong><p></div>";
	    $msg= "Your project has been successfully added! ";
     	add_confirmation($msg);

}


?>

