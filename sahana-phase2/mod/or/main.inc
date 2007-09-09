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
//
global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/reporting/lib_chart.inc";
include_once $global['approot']."/inc/reporting/lib_reporting.inc";
include_once ("lib_or.inc");

function shn_or_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];
  //  $loc=_shn_or_get_start_loc();
    shn_mod_menuopen(_lc($conf['mod_or_name']));
    shn_mod_menuitem("default",_("Home"),$module);
	shn_mod_menuitem("search",_("Search"),$module);
    shn_sub_mod_menuopen(_("Register"));
    shn_mod_menuitem("reg_org",_("Register an Organization"),$module);
    shn_mod_menuitem("reg_operation",_("Register a Department/Branch"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuitem("view_org",_("View and Edit"),$module);
    shn_sub_mod_menuopen(_("Reports"));
    shn_mod_menuitem("drill_report_loc",_("Drill down Location Coverage"),$module);
    shn_mod_menuitem("drill_report_org",_("Drill down Organization Coverage"),$module);
  //  shn_mod_menuitem("org_incident","Organizations by Incident",$module);
    shn_mod_menuitem("org_sector",_("Organizations by Sector"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

function shn_or_reg_org($error=false)
{
    include_once ("reg_org.inc"); 
    $_SESSION['org']['parent_id']=null;
    _shn_or_regform_org(false);
}

function shn_or_reg_org_confirm()
{
    include_once("reg_org.inc");
    $error=_shn_or_check_org_reg_map_info_complete();
	if($error==true){
		if( $_SESSION['org']['parent_id']==null){
    			_shn_or_regform_org(true);
    		}else{
    			_shn_or_regform_operation(false);
    		}
	}else{
    		_shn_or_regconfirm_org();
	}
}

function shn_or_reg_org_gis_map()
{
    include_once("reg_org.inc");
    $error=_shn_or_check_org_reg_info_complete();
  
    if($error){
    		if( $_SESSION['org']['parent_id']==null){
    			_shn_or_regform_org(true);
    		}else{
    			_shn_or_regform_operation(false);
    		}
    }else{
    	   
    	    _shn_or_reg_gis_map();
        
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
		_shn_or_regform_operation(false,$_SESSION['org']['parent_id']);
	}
}

function shn_or_reg_operation($error=false)
{
    include_once ("reg_org.inc"); 
    if($_POST["org_id"]!=null){
    		$_SESSION['org']['parent_id']=$_POST["org_id"];
    }
    if($_SESSION['org']['parent_id']==null){
    		_shn_or_regform_operation(false);
    }else{
    		_shn_or_regform_operation(false,$_SESSION['org']['parent_id']);	
    }
}
function shn_or_reg_operation_cr(){
    include_once("process_org.inc");
     _shn_or_reg_operation_cr();
     shn_or_view_org();
}

function shn_or_view_org_submit(){
    include_once("process_org.inc");
    include_once ("view_org.inc");
   // require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    $act=$_POST{"action"};

    switch ($act) {
    		case "gis":
			_shn_or_view_map_form_org();
			     break;
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
    $org_name=$_POST{"org_name"};
   	//$type=shn_or_create_database_IN_array($org_type);
   	//$sector=shn_or_create_database_IN_array($sector);
   	$sector=$_POST{"opt_sector_type"};
    $org_type=$_POST{"opt_org_type"};
    $loc_txt=$_POST{"loc_txt"};
    $search_str="select distinct o_uuid from org_main";
    if($sector!='all'){
    	$search_str.=",sector";
    }
	if(strlen(trim($loc_txt))!=0){
    	$search_str.=",contact";
    }
    $search_str.=" where 1=1 ";
   	if(strlen(trim($org_name))!=0){
    	$search_str.=" and name LIKE '%$org_name%'";
    }
    if($sector!='all'){
    	$search_str.=" and sector.opt_sector='{$sector}' and org_main.o_uuid=sector.pgoc_uuid";
    }
    if($org_type!='all'){
    	$search_str.=" and org_main.opt_org_type='{$org_type}'";
    }
    if(strlen(trim($loc_txt))!=0){
    	$search_str.=" and pgoc_uuid=org_main.o_uuid and contact_value LIKE  '%{$loc_txt}%' and opt_contact_type='loc_txt'";
    }
	$org_list=array();
	
    $res_org=$db->Execute($search_str);
   
    while(!$res_org==NULL && !$res_org->EOF){
    		array_push($org_list,$res_org->fields["o_uuid"]);
        	$res_org->MoveNext();
    }
	
    _shn_or_viewform_allorg($org_list);

}
?>
