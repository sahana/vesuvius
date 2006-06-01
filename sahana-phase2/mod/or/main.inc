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
//     shn_mod_menuitem("search","Search",$module);
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
    if(isset($_POST["incident"])){
    		if(empty($_POST["incidents"])){
    			$error=true;
        		add_error(_("You have to select an incident"));
        		_shn_or_display_incident_form(true,"reg_org");
    		}else{
    			_shn_or_regform_org(true);
    		}
    }else{
    		_shn_or_display_incident_form(false,"reg_org");
    }
}
function shn_or_reg_org_cr()
{
    include_once("process_org.inc");
    _shn_or_reg_org_cr();
}
function shn_or_reg_operation($error=false)
{
    include_once ("reg_org.inc"); 
    _shn_or_regform_operation(false);
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
	_shn_or_viewform_allorg($_GET["page"],$_GET["end"]);
}
function shn_or_view_org()
{
    include_once ("view_org.inc");
?>
<?php
	if(isset($_POST["incident"])){
    		if(empty($_POST["incidents"])){
    			$error=true;
        		add_error(_("You have to select an incident"));
        		_shn_or_display_incident_form(true,"view_org");
    		}else{
    			
    		?>
<h2> Organization Registry</h2>
			<?php
				
				$_SESSION["incidents"]=$_POST["incidents"];
				_shn_or_viewform_allorg();
    			
    		}
    }else{
    		_shn_or_display_incident_form(false,"view_org");
    }
    
}
function shn_or_edit_org()
{
    include_once ("view_org.inc");
    _shn_or_viewform_org($_GET['org_id']);
}


function shn_or_drill_report_loc()
{
    include_once("report.inc");
    	if(isset($_POST["incident"])){
    		if(empty($_POST["incidents"])){
    			$error=true;
        		add_error(_("You have to select an incident"));
        		_shn_or_display_incident_form(true,"drill_report_loc");
    		}else{
    			$_SESSION["incidents"]=$_POST["incidents"];
			//$parent=$_GET["id"];
     		_shn_or_drill_loc();
    			
    		}
    }else{
    		_shn_or_display_incident_form(false,"drill_report_loc");
    }

}

function shn_or_drill_report_loc_next()
{
	include_once("report.inc");
	$parent=$_GET["parent"];
	_shn_or_drill_loc($parent);
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
    	if(isset($_POST["incident"])){
    		if(empty($_POST["incidents"])){
    			$error=true;
        		add_error(_("You have to select an incident"));
        		_shn_or_display_incident_form(true,"drill_report_org");
    		}else{
    			$_SESSION["incidents"]=$_POST["incidents"];
			//$parent=$_GET["id"];
     		_shn_or_drill_org();
    			
    		}
    }else{
    		_shn_or_display_incident_form(false,"drill_report_org");
    }

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
    $incident=$_POST["incidents"];
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    list($error,$org_type)=(shn_validate_opt_field('opt_org_type',$_POST{"opt_org_type"},"Organization Type",$VARCHAR,true))?array($error,$_POST{"opt_org_type"}):array(true,NULL);
    $loc=shn_location_get_form_submit_loc();
    if($loc==-1){
    		add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
        $error=true;
    }
	$locs=array();
	shn_location_get_descendants($loc,$locs);
	$loc=shn_or_create_database_IN_array($locs);
   	$type=shn_or_create_database_IN_array($org_type);
   	$sector=shn_or_create_database_IN_array($sector);
   	$inci=shn_or_create_database_IN_array($incident);
	$org=array();
    $q="select o_uuid from location_details,sector,org_main,resource_to_incident where location_details.location_id in $loc and location_details.poc_uuid=org_main.o_uuid and sector.opt_sector in $sector and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type in $type and resource_to_incident.incident_id in $inci and resource_to_incident.x_uuid=org_main.o_uuid";
    
    $res_org=$db->Execute($q);
    while(!$res_org==NULL && !$res_org->EOF){
    		array_push($org,$res_org->fields["o_uuid"]);
        $res_org->MoveNext();
    }
        $i=$i+1;
    
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
    $i=0;
    $org=array_unique($org);
   
    while($i<count($org)){
        _shn_display_org($org[$i],$i);
        $i=$i+1;
    }
?>
        </tbody>
    </table>
</div>
<?php
}
?>
