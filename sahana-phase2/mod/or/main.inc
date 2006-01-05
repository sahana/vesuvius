<?php
/*
*
* Sahana HTML form handler
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once ("lib_or.inc");
//ravindra,chathra,pradeeper
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
               <!--  <li><a href="#">Update </a></li>
              	    <ul id="modsubmenu">
                        <li><a href="index.php?mod=<?=$module?>&act=search&edit=true">Organizations</a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=view_vol&edit=true">Volunteers</a></li>
                    </ul> -->
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


//author ravindra
// register a OR
function shn_or_reg_org($error=false)
{
include_once ("reg_org.inc"); 
    _shn_or_regform_org($error);
}

//author ravindra
function shn_or_reg_org_cr()
{
include_once("process_org.inc");
_shn_or_reg_org_cr();
}

//author ravindra
function shn_or_reg_operation_cr(){
include_once("process_org.inc");
 _shn_or_reg_operation_cr();
}

//author ravindra
// register a volunteer
function shn_or_reg_vol(){
include_once ("reg_vol.inc");
	_shn_or_regform_vol();
}

//author ravindra
// register a volunteer
function shn_or_reg_vol_cr(){
include_once("process_vol.inc");
   _shn_or_reg_vol_cr();
}

function shn_or_view_org_submit(){
include_once("process_org.inc");
include_once ("view_org.inc");
$act=$_POST{"action"};
//var_dump($_POST);
switch ($act) {
    case "edit":
        _shn_or_edit_org();
        _shn_or_view_org();
        break;
    case "del":
        _shn_or_del_org();
        _shn_or_view_org();
        break;
    default:
        _shn_or_view_org();
        break;
}
}

//author ravindra
// view all OR
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
//var_dump($_POST);
switch ($act) {
    case "edit":
        _shn_or_edit_vol();
        _shn_or_view_vol();
        break;
    case "del":
        _shn_or_del_vol();
        _shn_or_view_vol();
        break;
    default:
        _shn_or_view_vol();
        break;
}
}
//author ravindra
// view all Volunteers
function shn_or_view_vol()
{
include_once ("view_vol.inc");
if(NULL == $_REQUEST['id']){
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
    //shn_or_province();
}
//author ravindra
// view all orgs group by sector
function shn_or_org_sector()
{
include_once("report.inc");
    _shn_or_report_org_sector();
}


//author ravindra,pradeeper,chathra
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
 $VARCHAR=100;
global $global;
$db=$global["db"];
 list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);

if (is_null($_POST{"1"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_country=trim($_POST{"1"});
    }

if (is_null($_POST{"2"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_province=trim($_POST{"2"});
    }

if (is_null($_POST{"3"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_district=trim($_POST{"3"});
    }
    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=trim($_POST{"4"});
    }
$post_loc=$_POST{"opt_location_type"};
switch ($post_loc){
	case "2":
       $loc=shn_or_province_villages($bsd_province);
	break;
	case "3":
	   $loc=shn_or_district_villages($bsd_district);
              
    break;
	case "4":
    	$loc="($bsd_village)";
	break;

}
$loc="($loc)";
$i=0;
$org=array();


while($i<count($sector)){
            $q="select o_uuid from location_details,sector,org_main where location_details.location_id in $loc and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector[$i]}' and org_main.o_uuid=sector.pgoc_uuid";

            $res_org=$db->Execute($q);
while(!$res_org==NULL && !$res_org->EOF){
            array_push($org,$res_org->fields[0]);
            
            $res_org->MoveNext();
        }
$i=$i+1;
}

?>

    <h1 align="center">Search Result</h1>
	
<div id ="result">
    <table>
        <thead>
            <td>Organization Name</td>
            <td>Services Offered</td>
            <td>Organization Type</td>
            <td>Country of Origin</td>
            <td>Contact Address</td>
            <td>Contact Number</td>
            <td>Contact Email</td>
            <td>Man Power</td>
            <td>Facilities</td>
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
