<?php
/**Reports of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_location.inc";
include_once("lib_vol.inc");

function _shn_vol_level($parent)
{
    global $global;
    $db=$global['db'];
    if($parent<0){
    	$parent=NULL;
    }
    $q="select option_description,option_code,name from field_options,location where field_options.option_code=location.opt_location_type and location.location_id=$parent and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    if($res_label!=NULL && !$res_label->EOF){
        $parent_type="For  ".$res_label->fields[2];
    }
    $child=$res_label->fields[1]+1;
    $q="select option_description from field_options where field_options.option_code=$child and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    $child_type=$res_label->fields[0];
    $child=$child+1;
    $q="select option_description from field_options where field_options.option_code=$child and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    $grand_child_type=$res_label->fields[0];
?>
<h2><?php echo _t("Volunteer Report By ". $child_type." ".$parent_type) ?></h2>
    <div id="note">
<?php echo _t("Each Row is a ".$child_type." ,Column is a  Service.")?><br />
<?php 
    $last=shn_get_last_level();
    if ($last[0]!=$child-1){
        echo _t("Intersection shows the precentage of Sub-divisions Covered per each service.")."<br />";
        echo _t("For this report Sub-division is a  ".$grand_child_type.".");
        echo _t("If atleast one ".$last[1]. " in the Sub-division has a volunteer providing the service then that Sub-division is considered as covered for that service.");
    }else {
        echo _t("Intersection shows whether each ".$child_type." has atleast one organization providing the service.")."<br />";
    }
?>
</div>
<div id ="result">
    <table>
        <thead>
        <td>
<?php
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
       echo "<td>".$res_sector->fields[1]."</td>";
       $res_sector->MoveNext();
    }
       $res_sector->MoveFirst();
?>       
        </thead>
    <tbody>
<?php
	if($parent==NULL){
		$q = "select location_id,name from location where parent_id is NULL order by name";
	}else {
		$q = "select location_id,name from location where parent_id=$parent order by name";
	}
    $res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
<?php if(shn_is_last_level($res_loc->fields[0])){
        echo $res_loc->fields[1];
      }else {
        echo "<a href='index.php?mod=or&act=drill_report&id=".$res_loc->fields[0]."'>".$res_loc->fields[1]."</a>";
      }
?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
            if(shn_is_last_level($res_loc->fields[0])){
                echo ($res["active"]);
               if(_shn_is_covered($res_loc->fields[0],$res_sector->fields[0])){
                    $active=_t("Covered");
		            echo "<td><b><font color=#2E8B57>".$active."</font></b></td>";
                }else {
                    $active=_t("Not Covered");
		            echo "<td><b><font color=#FF0000>".$active."</font></b></td>";
                }
            }else {
                $res=_shn_coverage_loc($res_loc->fields[0],$res_sector->fields[0]);
                $precent=0;
                if($res["total"]>0){
                    $precent=round($res["active"]/$res["total"] *100,2);
                }
                echo "<td><b><font color=#2E8B57>".$res["active"]."/".$res["total"]."</font> (<font color=#FF0000>".$precent."%</font>)</b></td>";
            }
            $res_sector->MoveNext();
        }
        $res_sector->MoveFirst();
        $res_loc->MoveNext();
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>

<?php
}

function _shn_coverage_loc($loc,$sector)
{
    global $global;
    $db=$global["db"];
    $result=array();
    $result["total"]=0;
    $result["active"]=0;
    $q="select location_id,name from location where parent_id={$loc}";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $result["total"]=$result["total"]+1;
        $next_lvl=$res_tmp->fields[0];
        if(_shn_is_covered($res_tmp->fields[0],$sector)){    
            $result["active"]=$result["active"]+1;
        }
        $res_tmp->MoveNext();
    }
   return $result; 
}

function _shn_is_covered($loc,$sector)
{
    global $global;
    $db=$global["db"];
    $q="select location_id from location_details,sector where location_details.location_id={$loc} and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector}'";
    $res_village=$db->Execute($q);
     if(!$res_village==NULL && !$res_village->EOF){
            return true;
    }
    $q="select location_id,name from location where parent_id={$loc}";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $next_lvl=$res_tmp->fields[0];
        if(_shn_is_covered($next_lvl,$sector)){
            return true;
        }
        $res_tmp->MoveNext();
    }
   return false; 
}

function _shn_vol_report_sector()
{
    include_once("view_vol.inc");
    global $global;
    $db=$global['db'];
  ?><h2>Under construction</h2>
  <?php  
  return
?>
<h2><?php echo _t("Organization Report by Sector")?></h2>
<div id ="result">
    <table>
        <thead>
            <td><?php echo _t("Name")?></td>
            <td><?php echo _t("Services Offered")?></td>
            <td><?php echo _t("Country of Origin")?></td>
            <td><?php echo _t("Contact Address")?></td>
            <td><?php echo _t("Contact Number")?></td>
            <td><?php echo _t("Mobile Number")?></td>
            <td><?php echo _t("Contact Email")?></td>
           
        </thead>
        <tbody>
<?php    
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
        $option_code=$res_sector->fields[0];
        $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main,sector where sector.opt_sector='{$option_code}' and sector.pgoc_uuid=org_main.o_uuid order by name";
        $res_org=$db->Execute($q);
	    if(!$res_org->EOF){
	    ?>
	    <tr>
		    <td>
	            <b><?php echo _t($res_sector->fields[1])?></b>
		    </td>
	    </tr>
	    <?php
        }
        while(!$res_org==NULL && !$res_org->EOF){
            $org_id=$res_org->fields[0];
            _shn_display_org($org_id,false);
            $res_org->MoveNext();
        }
        $res_sector->MoveNext();
    }
?>
   </tbody>
  </table>
</div>

<?php
}
