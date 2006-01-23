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
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once ("lib_or.inc");

function shn_or_mainmenu() 
{
    global $global;
    $module = $global['module'];
    $loc=_shn_or_get_start_loc();
?>
   <div id="modmenuwrap"> 
        <h2>Organization Registry</h2>
            <ul id="modulemenu">
	        	<li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
                <li><a href="#">Organizations </a></li>
              	    <ul id="modsubmenu">
                        <li><a href="index.php?mod=or&act=search">Search </a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=reg_org">Register</a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=view_org">View and Edit</a></li>
			            <li><a href="index.php?mod=or&act=drill_report&id=<?php echo $loc?>">Drill down by Location</a></li>
    	                <li><a href="index.php?mod=or&act=org_sector"> Organizations by Sector</a></li>
                    </ul>
   		        <li><a href="#">Volunteers </a></li>
              	    <ul id="modsubmenu">
                        <li><a href="index.php?mod=<?=$module?>&act=reg_vol">Add</a></li>
	        	        <li><a href="index.php?mod=<?=$module?>&act=view_vol">View and Edit</a></li>
                    </ul>   
	        </ul>
    </div>
<?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

function shn_or_reg_org($error=false)
{
    include_once ("reg_org.inc"); 
    _shn_or_regform_org($error);
}
function shn_or_reg_org_cr()
{
    include_once("process_org.inc");
    _shn_or_reg_org_cr();
}
function shn_or_reg_operation_cr(){
    include_once("process_org.inc");
     _shn_or_reg_operation_cr();
}
function shn_or_reg_vol(){
    include_once ("reg_vol.inc");
	_shn_or_regform_vol();
}
function shn_or_reg_vol_cr(){
    include_once("process_vol.inc");
   _shn_or_reg_vol_cr();
}
function shn_or_view_org_submit(){
    include_once("process_org.inc");
    include_once ("view_org.inc");
    $act=$_POST{"action"};
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

function shn_or_view_org()
{
    include_once ("view_org.inc");
?>
<?php
    if(NULL == $_REQUEST['id']){
    ?>
<h2> Organization Registry</h2>
<?php
        _shn_or_viewform_allorg();
    }else{
        _shn_or_viewform_org($_REQUEST['id']);
    }
}

function shn_or_view_vol_submit(){
    include_once("process_vol.inc");
    include_once ("view_vol.inc");
    $act=$_POST{"action"};
    switch ($act) {
        case "edit":
            _shn_or_edit_vol();
            break;
        case "del":
            _shn_or_del_vol();
            break;
        default:
            shn_or_view_vol();
            break;
    }
}
function shn_or_view_vol()
{
    include_once ("view_vol.inc");
    if(NULL == $_REQUEST['id']){
         ?>
        <h2> Volunteer Registry</h2>
         <?php
        _shn_or_viewform_allvol();
    }else{
        _shn_or_viewform_vol($_REQUEST['id']);
    }
}

function shn_or_drill_report()
{
    include_once("report.inc");
    $parent=$_GET["id"];
    _shn_or_level($parent);
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
     list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    $post_loc=$_POST{"loc_sel"};
	$locs=shn_location_get_descendants($post_loc);
    $loc="($locs)";
    $i=0;
    $org=array();
    $org_type=$_POST{"opt_org_type"};
    while($i<count($sector)){
        $q="select o_uuid from location_details,sector,org_main where location_details.location_id in $loc and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector[$i]}' and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type='{$org_type}'";
        $res_org=$db->Execute($q);
        while(!$res_org==NULL && !$res_org->EOF){
            array_push($org,$res_org->fields[0]);
            $res_org->MoveNext();
        }
        $i=$i+1;
    }
?>
<h2><?=_("Search Result")?></h2>
    <div id ="result">
        <table>
            <thead>
                <td><?=_("Organization Name")?></td>
                <td><?=_("Services Offered")?></td>
                <td><?=_("Organization Type")?></td>
                <td><?=_("Country of Origin")?></td>
                <td><?=_("Contact Address")?></td>
                <td><?=_("Contact Number")?></td>
                <td><?=_("Contact Email")?></td>
                <td><?=_("Man Power")?></td>
                <td><?=_("Facilities")?></td>
            </thead>
            <tbody>
<?php
    $i=0;
    $org=array_unique($org);
    $i=0;
    while($i<count($org)){
        _shn_display_org($org[$i],false,true);
        $i=$i+1;
    }
?>
        </tbody>
    </table>
</div>
<?php
}
?>
