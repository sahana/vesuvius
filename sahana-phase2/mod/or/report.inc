<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";

function shn_or_province(){
    global $global;
    $db=$global['db'];
    
?>

<h2>Organization Report by Province</h2>
<div id="note">
Rows are Provinces ,Columns are Services ,Intersection shows how many
villages are covered as a ratio: <br>If atleast one organization is there in the village providing the service then that village is considered as covered for that service
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
?>       
    </thead>
     <tbody>
<?php    
    $q = "select location_id,name from location where opt_location_type='2' order by name";
    $res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
        <a href="index.php?mod=or&act=report_district&id=<?php echo $res_loc->fields[0]?>"><?php echo $res_loc->fields[1]?></a>
        </td>
<?php
        _shn_district_coverage_province($res_loc->fields[0]);
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


function shn_or_district($province){
    global $global;
    $db=$global['db'];
    
?>

<h2>Organization Report by District</h2>
<div id="note">
Rows are Districts ,Columns are Services ,Intersection shows how many
villages are covered as a ratio: <br>If atleast one organization is there in the village providing the service then that village is considered as covered for that service
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
    $q = "select location_id,name from location where parent_id={$province} order by name";
    $res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
        <a href="index.php?mod=or&act=report_village&id=<?php echo $res_loc->fields[0]?>"><?php echo $res_loc->fields[1]?></a>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
            $res=_shn_coverage_district($res_loc->fields[0],$res_sector->fields[0]);
            echo "<td>".$res["active"]."/".$res["total"]."</td>";
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

function shn_or_village($district){
    global $global;
    $db=$global['db'];
    
?>

<h2>Organization Report by Villages</h2>
<div id="note">
Rows are Villages ,Columns are Services ,Intersection shows how many
villages are covered as a ratio: <br>If atleast one organization is there in the village providing the service then that village is considered as covered for that service
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
    $q = "select location_id,name from location where parent_id={$district} order by name";
    $res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
        <?php echo $res_loc->fields[1]?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
            $q="select location_id from location_details,sector where location_details.location_id={$res_loc->fields[0]} and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$res_sector->fields[0]}'";
            $res_village=$db->Execute($q);
            if(!$res_village==NULL && !$res_village->EOF)
                $active="T";
            else
                $active="F";
            
            echo "<td>".$active."</td>";
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



function _shn_district_coverage_province($loc){
     global $global;
     $db=$global["db"];
     $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
     while(!$res_sector==NULL && !$res_sector->EOF){
        $active=0;
        $q="select location_id,name from location where parent_id={$loc}";
        $res_tmp=$db->Execute($q);
        $total=0;
        while(!$res_tmp==NULL && !$res_tmp->EOF){
            $res=_shn_coverage_district($res_tmp->fields[0],$res_sector->fields[0]);
            $total=$total+$res["total"];
            $active=$active+$res["active"];
            $res_tmp->MoveNext();
        }

        echo "<td>".$active."/".$total."</td>";
        $res_sector->MoveNext();
    }
 
}

function _shn_coverage_district($loc,$sector){
    global $global;
    $db=$global["db"];

    $result=array();
    $result["total"]=0;
    $result["active"]=0;
    $q="select location_id,name from location where parent_id={$loc}";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $result["total"]=$result["total"]+1;
        $village=$res_tmp->fields[0];
        $q="select location_id from location_details,sector where location_details.location_id={$village} and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector}'";
        $res_village=$db->Execute($q);
        if(!$res_village==NULL && !$res_village->EOF){
            $result["active"]=$result["active"]+1;
        }
        $res_tmp->MoveNext();
    }
   return $result; 
}

function shn_or_report_org_sector(){
    global $global;
    $db=$global['db'];
    
?>
<div id ="result">
    <h2>Organization Report by Sector</h2>
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
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
        $option_code=$res_sector->fields[0];
        $q = "select o_uuid,parent_id,name,man_power,resources from org_main,sector where sector.opt_sector='{$option_code}' and sector.pgoc_uuid=org_main.o_uuid order by name";
        $res_org=$db->Execute($q);
	    if(!$res_org->EOF){
	    ?>
	    <tr>
		    <td>
	            <b><?php echo $res_sector->fields[1]?></b>
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

