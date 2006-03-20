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
include_once ("lib_vol.inc");

function shn_vol_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];
    $loc=_shn_vol_get_start_loc();
    
?>
   <div id="modmenuwrap"> 
        <h2><?=_lc($conf['mod_vol_name'])?></h2>
            <ul id="modulemenu">
	        	<li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
                
              	    
                        <li><a href="index.php?mod=<?=$module?>&act=search">Search </a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=reg">Register</a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=view">View and Edit</a></li>
			            <li><a href="index.php?mod=<?=$module?>&act=drill_report&id=<?php echo $loc?>">Drill down by Location</a></li>
    	                <li><a href="index.php?mod=<?=$module?>&act=sector_report"> Volunteers by Sector</a></li>
                   
   		       
	        </ul>
    </div>
<?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 


function shn_vol_reg(){
    include_once ("reg_vol.inc");
	_shn_vol_regform();
}
function shn_vol_reg_cr(){
    include_once("process_vol.inc");
   _shn_vol_reg_cr();
}

function shn_vol_view_submit(){
    include_once("process_vol.inc");
    include_once ("view_vol.inc");
    require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    $act=$_POST{"action"};
    $acl_enabled=shn_acl_get_state("or");
    $req_act="_shn_or_".$act."_vol";
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
            _shn_vol_edit();
            break;
        case "del":
            _shn_vol_del();
            break;
        default:
            shn_vol_view();
            break;
    }
}
function shn_vol_view()
{
    include_once ("view_vol.inc");
    if(NULL == $_REQUEST['id']){
         ?>
        <h2> Volunteer Registry</h2>
         <?php
        _shn_vol_viewform_all();
    }else{
        _shn_vol_viewform($_REQUEST['id']);
    }
}

function shn_vol_drill_report()
{
    include_once("report.inc");
    $parent=$_GET["id"];
     _shn_vol_level($parent);
}
function shn_vol_sector_report()
{
    include_once("report.inc");
    _shn_vol_report_sector();
}
// default page, welcome page 
function shn_vol_default()
{
    include_once ("home.inc");
}
function shn_vol_search()
{
    include_once "search.inc";
     _shn_vol_form_search();
}
function shn_vol_search_cr(){
    global $global;
    include_once $global['approot']."/inc/lib_location.inc";
    include_once "view_vol.inc";
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
