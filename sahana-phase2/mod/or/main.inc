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
include_once $global['approot']."/inc/lib_paging.inc";

include_once ("lib_or.inc");
include_once ("lib_or_rss.inc");

function shn_or_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];
    //  $loc=_shn_or_get_start_loc();
    shn_mod_menuopen(_lc($conf['mod_or_name']));
    shn_mod_menuitem("default",_t("Home"),$module);
    shn_mod_menuitem("search",_t("Search"),$module);
    
    shn_sub_mod_menuopen(_t("Register"));
      shn_mod_menuitem("reg_org",_t("Register an Organization"),$module);
      shn_mod_menuitem("reg_operation",_t("Register a Department/Branch"),$module);
    shn_sub_mod_menuclose();
    
    shn_mod_menuitem("view_org",_t("View and Edit"),$module);
    
    shn_sub_mod_menuopen(_t("Reports"));
      shn_mod_menuitem("org_sector",_t("List of Organizations"),$module);
      shn_mod_menuitem("drill_report_loc",_t("Spread of Service Provision"),$module);
      shn_mod_menuitem("drill_report_org",_t("Depth of Service Provision"),$module);
      //shn_mod_menuitem("org_incident","Organizations by Incident",$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

function shn_or_reg_org($error=false)
{
    include_once ("reg_org.inc"); 
    $_SESSION['org']['parent_id']=null;
    $_SESSION['org']['same_name_confirm']=false;
    _shn_or_regform_org(false);
}

function shn_or_reg_org_confirm()
{
    include_once("reg_org.inc");
    $error=_shn_or_check_org_reg_map_info_complete();
	if($error==false){
		// patch to fix gis coordinate validation and return to the same form.
		/*if( $_SESSION['org']['parent_id']==null){
    		_shn_or_regform_org(true);
        }else{
    		_shn_or_regform_operation(false);
    	}*/
		_shn_or_reg_gis_map();
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

	switch ($_POST["action"]){
		case "edit":
				include_once("reg_org.inc");
				_shn_or_regform_org(true);
		break;
		case "edit_name":
				include_once("reg_org.inc");
				$_SESSION['org']['same_name_confirm']=false;
				_shn_or_regform_org(true);
		break;
		case "continue":
				if($_SESSION['org']['same_name_confirm']==false){
					$_SESSION['org']['same_name_confirm']=true;
				}else{
					$_SESSION['org']['same_name_confirm']=false;
				}
				
    			include_once("process_org.inc");
    			_shn_or_reg_org_cr();
    	break;
    	case "save":
    	    		include_once("process_org.inc");
    				_shn_or_reg_org_cr();
    	break;
      	
	}
	/*
	if($_POST["action"]=="edit"){
		include_once("reg_org.inc");
		_shn_or_regform_org(true);
	}else{
    		include_once("process_org.inc");
    		_shn_or_reg_org_cr();
	}
	*/
}
function shn_or_reg_org_name_change()
{ 
	if($_POST["action"]=="edit_name"){
		include_once("reg_org.inc");
		$_SESSION['org']['same_name_confirm']=false;
		_shn_or_regform_org(true);
	}else{
		$_SESSION['org']['same_name_confirm']=true;
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
function shn_or_reg_operation_cr()
{
    include_once("process_org.inc");
     _shn_or_reg_operation_cr();
     shn_or_view_org();
}

function shn_or_view_org_submit()
{
    include_once("process_org.inc");
    include_once ("view_org.inc");
    include_once("reg_org.inc");
   // require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    $act=$_POST{"action"};

    switch ($act) {
    	case "gis":
    		//put values to session
    		_shn_or_check_org_reg_info_complete();
			_shn_or_view_map_form_org();
		     break;
   		case "confirm_edit":
   			$error=_shn_or_check_org_reg_info_complete();
   			$error|=(!_shn_or_check_org_reg_map_info_complete());
   			// set the lattitude and logitude as loc_y and loc_x in session if not set
   			if(isset($_SESSION['org']['loc_x'])==false){
   				// we are sure that lat_edited is in the session because of 
   				// the _shn_or_check_org_reg_info_complete() call.
   				$_SESSION['org']['loc_x'] = $_SESSION['org']['lon_edited'];
   			}
   			if(isset($_SESSION['org']['loc_y'])==false){
   				// we are sure that lat_edited is in the session because of 
   				// the _shn_or_check_org_reg_info_complete() call.
   				$_SESSION['org']['loc_y'] = $_SESSION['org']['lat_edited'];
   			}
   			
   			if($error){
   				shn_or_edit_org();
   			}else{
   				_shn_or_regconfirm_org();
   			}
   			break;
        case "edit":
        	shn_or_edit_org();
        	break;
        case "save":
            _shn_or_edit_org();
            // Clear the junk values from the session.
            unset($_SESSION['org']);
            break;
        case "confirm_del":
			_shn_confirm_delete_org($_POST['org_id']);
        	break;
        case "del":
            _shn_or_del_org();
            break;
        default:
            shn_or_view_org();
            break;
    }
}

function shn_or_view_page()
{
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
	//_shn_or_viewform_allorg($org_list);
	_shn_or_display_header();
	
    _shn_display_orgs($org_list,true);			
    _shn_or_close_table();	   
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
    $sector=$_REQUEST['opt_sector'];
    _shn_or_report_org_sector($sector);
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
   	$loc=shn_location_get_form_submit_loc();

   	$sector=$_POST{"opt_sector_type"};
    $org_type=$_POST{"opt_org_type"};
    $addr=$_POST{"loc_txt"};
	$org_list=shn_or_org_search(null,$org_name,$org_type,$sector,$loc,$addr,true);
    //_shn_or_viewform_allorg($org_list);
    
    _shn_or_display_header();
    _shn_display_orgs($org_list,true);
    _shn_or_close_table();
    ?>
    <div>
                <center>
                <a href="index.php?mod=or&act=search">
                  <?php echo "<strong>"._t("Back to Search Page")."</strong>"; ?>
             
                </a>
                </center>
	</div>
    <?php
}

