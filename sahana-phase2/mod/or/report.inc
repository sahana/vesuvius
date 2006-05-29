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
include_once("lib_or.inc");

function _shn_or_drill_org($parent=null)
{
    global $global;
    $db=$global['db'];
    if(($parent==null)){
    		$parent="NULL";
    		$lvl_child=1;
    }else{
    		$lvl_child=shn_get_level($parent);
    		$lvl_child=$lvl_child+1;
    }
    $q="select option_description from field_options where field_options.option_code ='{$lvl_child}' and field_name='opt_location_type'";
    
    $res=$db->Execute($q);
    $level=$res->fields["option_description"];
    ?>
	<h2><?=_("Organization Report By ". $level) ?></h2>
    <div id="note">
	<?=_("Each Row is a ".$level." ,Column is a  Service.")?><br />
	<?php 
    echo _("Intersection shows the number of organizations providng the service in the location and its sub locations.")."<br />";
    ?>
    </div>
    <?
  
?>
<!--</div>-->
<div id ="result">
    <table>
        <thead>
        <td><?=_("Location");?></td>
        
<?php
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
       echo "<td>".$res_sector->fields["option_description"]."</td>";
       $res_sector->MoveNext();
    }
       $res_sector->MoveFirst();
?>       
        </thead>
    <tbody>
<?php
	$q = "select loc_uuid,name from location where parent_id='{$parent}' order by name";
	$res_loc=$db->Execute($q);
	
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
<?php if(shn_location_is_leaf($res_loc->fields["loc_uuid"])){
        echo $res_loc->fields["name"];
      }else {
        echo "<a href='index.php?mod=or&act=drill_report_org_next&parent=".$res_loc->fields["loc_uuid"]."'>".$res_loc->fields["name"]."</a>";
      }
?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
        		$count=0;
        		_shn_is_covered_org($res_loc->fields["loc_uuid"],$res_sector->fields[0],$count);
        		if($count==0){
        			echo "<td><b><font color=#FF0000>".$count."</font></b></td>";
        		}else{
        			echo "<td><b><font color=#2E8B57>".$count."</font></b></td>";
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

function _shn_or_drill_loc($parent=null)
{
    global $global;
    $db=$global['db'];
    if(($parent==null)){
    		$parent="NULL";
    		$lvl_child=1;
    }else{
    		$lvl_child=shn_get_level($parent);
    		$lvl_child=$lvl_child+1;
    }
    $q="select option_description from field_options where field_options.option_code ='{$lvl_child}' and field_name='opt_location_type'";
    $res=$db->Execute($q);
    $level1=$res->fields["option_description"];
    $lvl_child=$lvl_child+1;
    $q="select option_description from field_options where field_options.option_code ='{$lvl_child}' and field_name='opt_location_type'";
    $res=$db->Execute($q);
    $child_type=$res->fields["option_description"];
    if($parent<0){
    	$parent=NULL;
    }
    $parent_type=$level1;
    
  /*
    $child=$child+1;
    $q="select option_description from field_options where field_options.option_code=$child and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    $grand_child_type=$res_label->fields[0];
    */
?>
	
 <? 
 	$tmp=shn_get_last_level();
 	if($tmp[0]==$lvl_child-1){
 	?>
 	<h2><?=_("Organization Report for $parent_type") ?></h2>
    <div id="note">
    <?
 	$tmp=shn_get_last_level();
 	$child_type=$tmp[1];
 	echo	_("Each Row is a ".$child_type." ,Column is a  Service.");
 	?>
 	</div><?
 }else{
 	?>
 	<h2><?=_("Organization Report by $child_type for $parent_type") ?></h2>
    <div id="note">
    <?
	echo	_("Each Row is a ".$parent_type." ,Column is a  Service.");?><br />

<?php
 	   	echo	_("Each Row is a ".$parent_type." ,Column is a  Service.");
        echo _("Intersection shows the precentage of ".$child_type." Covered per each service.")."<br />";
        echo _("e.g. For a country how many districts have at least one organization providing the service. <br /> ");
        echo _("If the country C has X no of district amd for the service S only Y no of districts have the presence of an organization the C/S intersection shows Y/X");
 ?></div><?
 }     

?>


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
		$q = "select loc_uuid,name from location where parent_id='{$parent}' order by name";
	
    $res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
<?php if(shn_location_is_leaf($res_loc->fields["loc_uuid"])){
        echo $res_loc->fields[1];
      }else {
        echo "<a href='index.php?mod=or&act=drill_report_loc_next&parent=".$res_loc->fields["loc_uuid"]."'>".$res_loc->fields["name"]."</a>";
      }
?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
            if(shn_location_is_leaf($res_loc->fields["loc_uuid"])){
//                echo ($res["active"]);
               if(_shn_is_covered($res_loc->fields[0],$res_sector->fields[0])){
                    $active=_("Covered");
		            echo "<td><b><font color=#2E8B57>".$active."</font></b></td>";
                }else {
                    $active=_("Not Covered");
		            echo "<td><b><font color=#FF0000>".$active."</font></b></td>";
                }
            }else {
                $res=_shn_coverage_loc($res_loc->fields["loc_uuid"],$res_sector->fields[0]);
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
    /*
    if(_shn_is_covered($loc,$sector)){    
            $result["active"]=$result["active"]+1;
    }*/
    $q="select loc_uuid,name from location where parent_id='{$loc}'";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $result["total"]=$result["total"]+1;
        $next_lvl=$res_tmp->fields[0];
        if(_shn_is_covered($res_tmp->fields["loc_uuid"],$sector)){    
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
    $q="select location_id from location_details,sector where location_details.location_id='{$loc}' and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector}'";
    $res_village=$db->Execute($q);
     if(!$res_village==NULL && !$res_village->EOF){
            return true;
    }
    $q="select loc_uuid,name from location where parent_id='{$loc}'";
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

function _shn_is_covered_org($loc,$sector,&$count)
{
    global $global;
    $db=$global["db"];
    $q="select location_id from location_details,sector where location_details.location_id='{$loc}' and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector}'";
    $res_village=$db->Execute($q);
    if(!$res_village==NULL && !$res_village->EOF){
            $count=$count+1;
    }
    $q="select loc_uuid,name from location where parent_id='{$loc}'";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $next_lvl=$res_tmp->fields["loc_uuid"];
      	_shn_is_covered_org($next_lvl,$sector,$count);
        $res_tmp->MoveNext();
    }
   return false; 
}

function _shn_or_report_org_sector()
{
    include_once("view_org.inc");
    global $global;
    $db=$global['db'];
    
?>
<h2><?=_("Organization Report by Sector")?></h2>
<div id ="result">
    <table>
        <thead>
        		<td><?=_("Service")?></td>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Services Offered")?></td>
            <td><?=_("Organization Type")?></td>
           
            <td><?=_("Address")?></td>
            <td><?=_("Contact Number")?></td>
            <td><?=_("Man Power")?></td>
            <td><?=_("Equipment")?></td>
            <td><?=_("Facilities")?></td>
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
	            <b><?=_($res_sector->fields[1])?></b>
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
