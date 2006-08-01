<?php
/**Main Controller of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once ("lib_or.inc");

function shn_or_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];
    $loc=_shn_or_get_start_loc();
    shn_mod_menuopen(_lc($conf['mod_or_name']));
    shn_mod_menuitem("default","Home",$module);
	shn_mod_menuitem("search","Search",$module);
    shn_sub_mod_menuopen(_("Register"));
    shn_mod_menuitem("reg_org","Register an Organization",$module);
    shn_mod_menuitem("reg_operation","Register a Department/Branch",$module);
    shn_sub_mod_menuclose();
    shn_mod_menuitem("view_org","View and Edit",$module);
    shn_sub_mod_menuopen(_("Reports"));
    shn_mod_menuitem("drill_report_loc&id=".$loc,"Drill down Location Coverage",$module);
    shn_mod_menuitem("drill_report_org&id=".$loc,"Drill down Organization Coverage",$module);
  //  shn_mod_menuitem("org_incident","Organizations by Incident",$module);
    shn_mod_menuitem("org_sector","Organizations by Sector",$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

function shn_or_reg_org($error=false)
{
    include_once ("reg_org.inc"); 
    _shn_or_regform_org(false);
}

function shn_or_reg_org_confirm()
{
    include_once("reg_org.inc");
    $error=_shn_or_check_org_reg_info_complete();
	if($error==true){
		_shn_or_regform_org($error);
	}else{
    		_shn_or_regconfirm_org();
	}
}

function shn_or_reg_org_cr()
{ 
	if($_POST["action"]=="edit"){
		include_once("reg_org.inc");
		_shn_or_regform_org(true);
	}else{
    		include_once("process_org.inc");
    		_shn_or_reg_org_cr();
	}
}
function shn_or_reg_org_finalize()
{ 
	include_once("reg_org.inc");
	if($_POST["action"]=="org"){
		_shn_or_regform_org(false);
	}else{
		_shn_or_regform_operation(false,$_POST["org_id"]);
	}
}

function shn_or_reg_operation($error=false)
{
    include_once ("reg_org.inc"); 
    if($_POST["org_id"]==null){
    		_shn_or_regform_operation(false);
    }else{
    		_shn_or_regform_operation(false,$_POST["org_id"]);	
    }
}
function shn_or_reg_operation_cr(){
    include_once("process_org.inc");
     _shn_or_reg_operation_cr();
}

function shn_or_view_org_submit(){
    include_once("process_org.inc");
    include_once ("view_org.inc");
    require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    $act=$_POST{"action"};
    $acl_enabled=shn_acl_get_state("or");
    $req_act="_shn_or_".$act."_org";
    $allow = (!shn_acl_check_perms_action($_SESSION['user_id'],$req_act) || 
             !$acl_enabled)? true : false;
    if(!$allow){
    	?>
    	<div id="error">
        <p><em><?=_('Sorry, you do not have permisssion to access this section')?></em>.<br/><br/><?=_('This could be because:')?></ul>
        <ul>
        <li><?=_('You have not logged in or Anonymous access is not allowed to this section')?></li>
        <li><?=_('Your username has not been given permission to access this section')?></li>
        </ul>
        <p><?=_('To gain access to this section please contact the administrator')?></p>
    	</div> <!-- /error -->
    	<?
    	return false;
    }
    switch ($act) {
        case "edit":
            _shn_or_edit_org();
            break;
        case "del":
            _shn_or_del_org();
            break;
        default:
            shn_or_view_org();
            break;
    }
}

function shn_or_view_page(){
	include_once ("view_org.inc");
	_shn_or_display_page($_GET["page"]);
}
function shn_or_view_org()
{
    include_once ("view_org.inc");
	$_SESSION["incidents"]=array($_SESSION['user_pref_ims_incident_id']);
	unset($_SESSION["org"]["total_pages"]);
	unset($_SESSION["org"]["pages"]);
	$incident_arr=array($_SESSION['user_pref_ims_incident_id']);
	shn_get_incident_descendants($_SESSION['user_pref_ims_incident_id'],$incident_arr);
	$org_list=shn_or_org_incident_list($incident_arr);
	_shn_or_viewform_allorg($org_list);
    			
    		   
}
function shn_or_edit_org()
{
    include_once ("view_org.inc");
    _shn_or_viewform_org($_GET['org_id']);
}


function shn_or_drill_report_loc()
{
    include_once("report.inc");
//	$_SESSION["incidents"]=$_POST["incidents"];
	$_SESSION["incidents"]=array($_SESSION['user_pref_ims_incident_id']);
			//$parent=$_GET["id"];
     		_shn_or_drill_loc();
}

function shn_or_drill_report_loc_next()
{
	include_once("report.inc");
	$parent=$_GET["parent"];
	_shn_or_drill_loc($parent);
}

function shn_or_drill_report_loc_show_orgs()
{
    include_once ("view_org.inc");
	$_SESSION["incidents"]=array($_SESSION['user_pref_ims_incident_id']);
	unset($_SESSION["org"]["total_pages"]);
	unset($_SESSION["org"]["pages"]);
	$incident_arr=array($_SESSION['user_pref_ims_incident_id']);
	shn_get_incident_descendants($_SESSION['user_pref_ims_incident_id'],$incident_arr);
	$loc_arr=array($_GET["loc"]);
	shn_location_get_descendants($_GET["loc"],&$loc_arr);
	$org_list=shn_or_org_loc_sector_incident_list($loc_arr,$_GET["sec"],$incident_arr);
	_shn_or_viewform_allorg($org_list);
  		   
}

function shn_or_drill_report_org_next()
{
	include_once("report.inc");
	$parent=$_GET["parent"];
	_shn_or_drill_org($parent);
}
   
   
function shn_or_drill_report_org()
{
    include_once("report.inc");
	$_SESSION["incidents"]=array($_SESSION['user_pref_ims_incident_id']);
    _shn_or_drill_org();
    		
}

function shn_or_drill_report_org_show_orgs()
{
    include_once ("view_org.inc");
	$_SESSION["incidents"]=array($_SESSION['user_pref_ims_incident_id']);
	unset($_SESSION["org"]["total_pages"]);
	unset($_SESSION["org"]["pages"]);
	$incident_arr=array($_SESSION['user_pref_ims_incident_id']);
	shn_get_incident_descendants($_SESSION['user_pref_ims_incident_id'],$incident_arr);
	$loc_arr=array($_GET["loc"]);
	shn_location_get_descendants($_GET["loc"],&$loc_arr);
	$org_list=shn_or_org_loc_sector_incident_list($loc_arr,$_GET["sec"],$incident_arr);
	_shn_or_viewform_allorg($org_list);
  		   
}

function shn_or_org_sector()
{
    include_once("report.inc");
    _shn_or_report_org_sector();
}
// default page, welcome page 
function shn_or_default()
{
    include_once ("home.inc");
}
function shn_or_search()
{
    include_once "search.inc";
     _shn_or_form_search();
}
function shn_or_search_cr(){
    global $global;
    include_once $global['approot']."/inc/lib_location.inc";
    include_once "view_org.inc";
    
    $VARCHAR=100;
    $db=$global["db"];
   // $incident=$_POST["incidents"];
    	$incident=array($_SESSION['user_pref_ims_incident_id']);
	shn_get_incident_descendants($_SESSION['user_pref_ims_incident_id'],$incident);
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);

   	//$type=shn_or_create_database_IN_array($org_type);
   	//$sector=shn_or_create_database_IN_array($sector);
   	$inci=shn_or_create_database_IN_array($incident);
	$org_list=array();
	if($org_name!=NULL){
		$q="select distinct o_uuid from org_main where name LIKE '%$org_name%'";
	}else{
		list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,false))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    		list($error,$org_type)=(shn_validate_opt_field('opt_org_type',$_POST{"opt_org_type"},"Organization Type",$VARCHAR,false))?array($error,$_POST{"opt_org_type"}):array(true,NULL);
    		$loc=shn_location_get_form_submit_loc();
    		if($loc==-1){
			$q="select distinct o_uuid from sector,org_main,resource_to_incident where sector.opt_sector='{$sector}' and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type='{$org_type}' and resource_to_incident.incident_id in $inci and resource_to_incident.x_uuid=org_main.o_uuid";
    		}else{
			$locs=array();
			shn_location_get_descendants($loc,$locs);
			$loc=shn_or_create_database_IN_array($locs);
    		//$q="select distinct o_uuid from location_details,sector,org_main,resource_to_incident where location_details.location_id in $loc and location_details.poc_uuid=org_main.o_uuid and sector.opt_sector in $sector and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type in $type and resource_to_incident.incident_id in $inci and resource_to_incident.x_uuid=org_main.o_uuid";
    			$q="select distinct o_uuid from location_details,sector,org_main,resource_to_incident where location_details.location_id in $loc and location_details.poc_uuid=org_main.o_uuid and sector.opt_sector='{$sector}' and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type='{$org_type}' and resource_to_incident.incident_id in $inci and resource_to_incident.x_uuid=org_main.o_uuid";
    		}
	}
	
    $res_org=$db->Execute($q);
   
    while(!$res_org==NULL && !$res_org->EOF){
    		array_push($org_list,$res_org->fields["o_uuid"]);
        $res_org->MoveNext();
    }
    _shn_or_viewform_allorg($org_list);
    /*
    
?>
<h2><?=_("Search Result")?></h2>
    <div id ="result">
	<table>
        <thead>
        		<td></td>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Services Provided")?></td>
            <td><?=_("Organization Type")?></td>
          <!--  <td><?//=_("Country of Origin")?></td>-->
            <td><?=_("Address")?></td>
            <td><?=_("Contact Numbers")?></td>
            <td><?=_("Man Power")?></td>
            <td><?=_("Equipment")?></td>
            <td><?=_("Other <br /> Facilities")?></td>
        </thead>
        <tbody>
<?php
    $i=1;
    $org=array_unique($org);
   
   foreach ($org as $o_id){
  
    		if(!$o_id==null){
    			_shn_display_org($o_id,$i);
    			 $i=$i+1;
    		}
       
    }
?>
        </tbody>
    </table>
</div>
<?php
*/
}
?>
