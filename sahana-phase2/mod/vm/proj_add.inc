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
	if($errors)
		display_errors();
	if($_POST['project_name']!=NULL){
		project_addto_db();
		echo "<div id=\"error\"><p>Your project has been successfully added!<p></div>";
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

        shn_form_select($managers, 'Project Manager : ', 'manager_id', NULL, NULL);
   	_shn_form_select_specialities($error);
	shn_form_fsclose();
	
//  start section 3  
	//$location_inf = _shn_location_form_volunteer('2','3'); 
	shn_location_form_org(1,5);
	
	shn_form_submit(_("Submit"));
	shn_form_fclose();
} //  end _shn_vm_regform_proj_add()

/*
function _shn_vm_validate_error(){
	clean_errors();
	$error_flag=false;


	if(null == ($_POST['project_name'])){
			add_error(_("Please Enter the Project Name"));
			$error_flag=true;
	}

        if(!(null == ($_POST['family']))){
		if(!is_numeric(trim($_POST['family']))){
			add_error(_("The Family Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['total']))){
		if(!is_numeric(trim($_POST['total']))){
			add_error(_("The Total Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['men']))){
		if(!is_numeric(trim($_POST['men']))){
			add_error(_("The Men Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['women']))){
		if(!is_numeric(trim($_POST['women']))){
			add_error(_("The Women Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['children']))){
		if(!is_numeric(trim($_POST['children']))){
			add_error(_("The Children Count is not a valid number"));
			$error_flag=true;
		}
	}
	
	return $error_flag;
}
*/

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

list($error,$specialty)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);

list($error, $specialty)=array($error, $_POST{'opt_skill_type'});

$i=0;
while($i<count($specialty)){
	  $q="insert into vm_proj_skills(p_uuid,opt_skill_code) values('" . $proj_id . "','" . $specialty[$i] . "')";
	 // echo $q;
	  $res=$db->Execute($q);
	  $i=$i+1;
        }


$q="insert into vm_projects (proj_id, name, mgr_id, location_id, start_date, end_date, description) VALUES ('$proj_id','{$_POST['project_name']}','{$_POST['manager_id']}','{$_POST['3']}','{$_POST['start_date']}','{$_POST['end_date']}','{$_POST['project_description']}')";
	 // echo $q;

$result=$db->Execute($q);


}


?>

