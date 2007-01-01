<?php
/* $Id: [sahana_home]/mod/vm/proj_report.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- creates the Work Summaries Report page.
 *
 *  <p>This file is part of the Volunteer Management module. It
 *  generates the Work Summaries page, which is composed of 3 sections:
 *  the first section
 </p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 *
 */
 
global $global;

/** Contains library functions for creating forms */
include_once $global['approot']."/inc/lib_form.inc";
/** Contains functions for viewing volunteers */
include_once ("view_volunteers.inc"); 
/** Contains utility functions for VM and VR modules */
include_once $global['approot']."/mod/vm/utility_functions.inc";
/** Contains library functions for VM and VR module's forms */
include_once $global['approot']."/mod/vm/lib_vm.inc";

/**
 *
 *
 */

function _shn_vm_proj_report($no = NULL){
 
  $project_id = $_GET['project'];
  if($project_id == NULL){
  _shn_report_1();
  _shn_report_2();
  }
  else {
  _shn_project_report($project_id);
  }
 
}

/**
 *  Generates a Project Report page for a specific project.
 *
 *  This function generates the Project Report page, which is composed
 *  of three sections: one for the project's details, one to narrow 
 *  the search results by organization, and one that lists the participating
 *  volunteers and their details.  It performs a DB query of tables 
 *  <b>vm_vol_details</b>, <b>org_main</b> and <b>vm_proj_vol</b> given 
 *  project id as a parameter.  
 *
 *  @param string $project_id  The project being queried.
 *  @access public
 *  @return void
 */
function _shn_project_report($project_id = NULL){
    global $global;
    $db=$global["db"];

    $org_id = $_POST['org_id'];

    $q = "select name from vm_projects where proj_id = {$project_id}";
    $result=$db->Execute($q);
    $name = $result->fields[0];
    $q = "select vm_proj_vol.p_uuid, proj_id, org_id, name from vm_vol_details, org_main, vm_proj_vol where vm_proj_vol.p_uuid = vm_vol_details.p_uuid and org_id = o_uuid and proj_id = {$project_id} group by o_uuid";
    $res_orgs=$db->Execute($q);
    $orgs="";
    $test=array();
    $test[NULL]="All Organizations";
    while(!$res_orgs==NULL && !$res_orgs->EOF){
        $orgs = $orgs . $res_orgs->fields[3] . "<br>";                  // Get the project's ID
	$test[$res_orgs->fields[2]]=$res_orgs->fields[3];
        $res_orgs->MoveNext();
    }

    $skills = get_project_skills_list($project_id);
    $q = "select avg(payrate) from vm_proj_vol, vm_vol_details where proj_id = '{$project_id}' and vm_proj_vol.p_uuid = vm_vol_details.p_uuid";
    if($org_id!=NULL){
	$q = $q . " and org_id = '{$org_id}'";
	$orgs = get_org_name($org_id);
    }
    $result=$db->Execute($q);
    $payrate = $result->fields[0];
    $payrate = "$" . number_format($payrate,2);
    if(get_volunteer_count($project_id,NULL,$org_id)==0){
    $dolls = "n/a";
	}else{	
    $dolls = get_project_dollar_total($project_id,$org_id) / get_volunteer_count($project_id,NULL,$org_id);
    $dolls = "$" . number_format($dolls,2);
	}

//  start "Project Report" section 
?>
<div id="home">
    <h2><?=_("Project Report")?></h2>

<table width="100%">
	<colgroup>
	<col width="20%">
	<col width="20%">
	<col width="20%">
	<col width="20%">
	<col width="20%">
    
    <thead>
        <td><strong><?=_("Project Name")?></strong></td>
        <td><strong><?=_("Organizations Involved")?></strong></td>
        <td><strong><?=_("Skills Required")?></strong></td>
        <td><strong><?=_("Average Payrate")?></strong></td>
        <td><strong><?=_("Dollars/Volunteers")?></strong></td>
    </thead>
    <tbody>
        <tr>
	<td><?php echo $name?></td>
	<td><?php echo $orgs?></td>
	<td><?php echo $skills?></td>
	<td><?php echo $payrate?></td>
	<td><?php echo $dolls?></td>
	</tr>
    </tbody>
    </table>
</div>
<br />

<?php
//  start "Project Search Criteria" section
    form_open("proj_report", $project_id); 
    shn_form_fsopen('Project Search Criteria');
    //_shn_form_date(_("Start Date : "),'start', $initdate=$_POST{"start_date"}, $required=true, $format='YYYY-MM-DD');
    //_shn_form_date(_("End Date : "),'end', $initdate=$_POST{"end_date"}, $required=true, $format='YYYY-MM-DD');
    // form_select($org_array, 'Organization', 'org_id');
    form_select($test, 'Organization', 'org_id');
    shn_form_submit('SUBMIT');
    shn_form_fsclose();
    form_close();
?>
    <br>    
<?php
//  start "Volunteers" table
    _display_volunteers($project_id,$org_id);

} // end _shn_project_report()

/**
 *  Generates the upper half of the "Work Summary Reports" page.
 *
 *  This function generates the first two sections of the "Work
 *  Summary Reports" page: the "Work Summary Reports" section, and
 *  the "Project Search Criteria" section.  It performs a DB query 
 *  of tables <b>org_main</b>, <b>vm_vol_details</b>, and <b>vm_projects</b>.
 *  
 *  @param string $no
 *  @access public
 *  @return void
 */
function _shn_report_1($no = NULL){
    global $global;
    $db=$global["db"];

    	$org = $_POST['org'];
    
	$q = "select o_uuid, name from org_main";
        $org_names=$db->Execute($q);

   	$org_array=array();
	$org_array[NULL]="All Organizations";
	while(!$org_names==NULL && !$org_names->EOF){
        $org_array[$org_names->fields[0]]=$org_names->fields[1];
	$org_names->MoveNext();
	}

	$q = "select name from org_main where o_uuid = '{$org}'";
        $orgo=$db->Execute($q);
	$orgon=$orgo->fields[0];

	$q = "select proj_id, name, mgr_id, p_uuid, org_id, start_date, end_date from vm_projects, vm_vol_details
	where mgr_id = p_uuid";
	if($org!= NULL){
	$q = $q . " and org_id = '{$org}' and
	start_date >= '{$_POST['start_date']}' and
	end_date <= '{$_POST['end_date']}'";
	}
	$projects=$db->Execute($q);
    	
	$vol_cnt=0;
	$ammount=0;
	$total = 0;
	
    while(!$projects==NULL && !$projects->EOF){
	$proj_uuid=$projects->fields[0];
	$ammount = get_volunteer_count($proj_uuid,NULL);
	$vol_cnt = $vol_cnt + $ammount;
	$ammount = get_project_dollar_total($proj_uuid);
	$total = $total + $ammount;
	$projects->MoveNext();
    }

//start "Work Summary Reports" section    
?>
<div id="home">
    <h2>
    	<?php
    	echo "Work Summary Reports";
    	if($org!= NULL){
	echo " for " . $orgon;
	}
    	?>
    </h2>

<table width="100%">
	<colgroup>
	<col width="33%">
	<col width="34%">
	<col width="33%">
    <thead>
        <td><strong><?=_("Project Name")?></strong></td>
        <td><strong><?=_("Total Volunteers")?></strong></td>
        <td><strong><?=_("Approximate Dollar Value")?></strong></td>
    </thead>
    <tbody>
        <tr>
	<td align = "center">All <?php echo $orgon?> Projects</td>
     	<td align = "center"><?php echo $vol_cnt?></td>
     	<td align = "center"><?php echo "$" . number_format($total, 2)?></td>
	</tr>
    </tbody>
    </table>
</div>
<br />
  
<?php    
//  start "Project Search Criteria" section
    form_open("proj_report"); 
    shn_form_fsopen('Project Search Criteria');
shn_form_date(_("Start Date : "),'start_date',$extra_opts=NULL);
	echo "<br>";
	shn_form_date(_("End Date : "),'end_date',$extra_opts=NULL);
	echo "<br>";

    //_shn_form_date(_("Start Date : "),'start_date', $initdate=$_POST{"start_date"}, $required=true, $format='YYYY-MM-DD');
    //_shn_form_date(_("End Date : "),'end_date', $initdate=$_POST{"end_date"}, $required=true, $format='YYYY-MM-DD');
    form_select($org_array, 'Organization', 'org');
    shn_form_submit('SUBMIT');
    shn_form_fsclose();
    form_close();
    ?><br><?php

}  // end _shn_report_1()

/**
 *  Generates the bottom half of the "Work Summary Reports" page.
 *
 *  This function generates the "Results" section of the 
 *  "Work Summary Reports" page.  The "Results" section
 *  contains project details for projects that fulfill 
 *  the search criteria entered in the "Project Search Criteria" 
 *  section. This function performs DB queries of tables <b>vm_projects</b> 
 *  and <b>vm_vol_details</b>.  
 *
 *  @param string $no
 *  @access public
 *  @return void
 */
function _shn_report_2($no = NULL){
    global $global;
    $db=$global["db"];
    $start_date = $_POST['start_date'];
    $end_date = $_POST['end_date'];
    $org = $_POST['org'];
    //if($org==NULL){$org= -1;}
?>
  <div id="note">
   <strong><?php
   if($org== NULL){
   echo "Results";
   }else{
   echo "Results from " . $start_date . " to " . $end_date . ".";
   }?></strong>
    </div>
<div id ="result">
	<table>
        <thead>
            <td><?=_("Project Name")?></td>
	    <td><?=_("Organization")?></td>
	    <td><?=_("Start Date")?></td>
	    <td><?=_("End Date")?></td>
            <td><?=_("Tasks")?></td>
	    <td><?=_("Volunteers")?></td>
            <td><?=_("Hours")?></td>
            <td><?=_("Approximate Dollar Value")?></td>
	</thead>
        <tbody>
<?php
	$q = "select proj_id, name, mgr_id, p_uuid, org_id, start_date, end_date from vm_projects, vm_vol_details
	where mgr_id = p_uuid";
	if($org!= NULL){
	$q = $q . " and org_id = '{$org}' and
	start_date >= '{$start_date}' and
	end_date <= '{$end_date}'";
	}
	$res_proj=$db->Execute($q);
    	
	if($res_proj->EOF){
	?>
	<tr>
	<td>No projects fit the criteria...</td>
	</tr>

<?php
	}
	
    while(!$res_proj==NULL && !$res_proj->EOF){
	$project_id=$res_proj->fields[0];            
        $name=$res_proj->fields[1];                  
        $org_id=$res_proj->fields[4];  
        $start=$res_proj->fields[5];  
        $end=$res_proj->fields[6];  
	
	$q = "select name, o_uuid from org_main where o_uuid = '{$org_id}'";
	$result=$db->Execute($q);
        $org_name=$result->fields[0];       
	
?>
<tr>
     <td><a href="index.php?mod=vm&act=proj_report&project=<?php echo $project_id?>"><?php echo $name?></a></td>
     <td><?php echo $org_name?></td>
     <td><?php echo $start?></td>
     <td><?php echo $end?></td>
     <td><?php echo get_project_skills_list($project_id)?></td>
     <td><?php echo get_volunteer_count($project_id)?></td>
     <td><?php echo get_project_hours($project_id)?></td>
     <td><?php echo "$" . number_format(get_project_dollar_total($project_id),2)?></td>
</tr>
<?php
	$res_proj->MoveNext();
    }
?>
  </tbody>
  </table>
</div>
<?php
} // end _shn_report_2()

/**
 *  Defines form_open as the beginning of an instance of an HTML "formcontainer". 
 *
 *  @param string $act
 *  @param string $project
 *  @access public
 *  @return void
 */
function form_open($act=NULL, $project=NULL){
    global $global;
    $mod = $global['module'];

?>
    <div id="formcontainer">
    <form method="POST" action="index.php?mod=<?=$mod?>&act=<?=$act?>&project=<?=$project?>" id="formset" <?=$form_opts['enctype']?>name="<?=$form_opts['name']?>">
<?php
}

/**
 *  Defines form_close as the end of an instance of an HTML "formcontainer".
 *
 *  @access public
 *  @return void
 */
function form_close(){ 
?>
    </form>
    </div> <!-- /formcontainer -->
<?php
}

/**
 *  Generates a drop-down menu. 
 *
 *  This function generates a drop-down menu, which in
 *  the case of the "Work Summary Reports" page contains 
 *  a listing of organizations.  Once one of the organizations
 *  is selected the drop-down menu closes.  This menu can 
 *  be made optional or mandatory, depending on the truth value  
 *  of $extra_opts.  
 *
 *  @param string $options  
 *  @param string $label  The label given to the menu.
 *  @param string $name
 *  @param string $select_opts
 *  @param string $extra_opts  Determines whether menu is optional or required
 *  @access public
 *  @return void
 */
function form_select($options, $label, $name, $select_opts = "", $extra_opts = null){
    global $global;

    $value = $_POST{$name};
?>
    <label><?=$label?></label>   
    <select name="<?=$name?>" onblur="submit();" <?=$select_opts?> >
   
<?php
    foreach ($options as $opt_value => $desc ) {
    $sel = ( $opt_value == $value ) ? "selected" : null ;
?>
    <option value="<?=$opt_value?>" <?=$sel?>><?=$desc?></option>
<?php
    }
?>
    </select> 
<?php
    shn_form_extra_opts($extra_opts);
} 
?>
