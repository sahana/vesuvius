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

function shn_or_report_org_sector(){
    global $global;
    $db=$global['db'];
    
?>
<div id ="result">
    <h2>Organization Report by Sector</h2>
    <table>
        <thead>
            <td>Organization Name</td>
            <td>Contact Address</td>
            <td>Contact Number</td>
            <td>Contact Email</td>
            <td>Country of Origin</td>
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
/**
function _shn_display_org($org_id){
    global $global;
    $db=$global["db"];
    $q = "select o_uuid,parent_id,name,man_power,resources from org_main where o_uuid=$org_id";
    //echo $q;
    $res_org=$db->Execute($q);
    $org_id=$res_org->fields[0];        
    $q = "select address from location_details where poc_uuid='{$org_id}'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);

    $q="select search_id from location_details,location where poc_uuid='{$org_id}' and location_details.location_id=location.location_id";
    $res_temp=$db->Execute($q);
    $loc=$res_temp->fields[0][0];
    $q="select name from location where location_id='{$loc}'";
    $res_bsd_country=$db->Execute($q);
   // $q = "select name from location,org_location where org_id='{$org_id}' and location.location_id=org_location.location_id";
    //$q = "select name from location,org_location where org_id='{$org_id}' and opt_location_type='1' and location.location_id=org_location.location_id";
   // $res_bsd_country=$db->Execute($q);
?>

<tr>
    <td>
     <?php
    $parent=$res_org->fields[1];
    if($parent>0){
    echo "<div id='parent'>";
    }
    ?>
    <a href="index.php?mod=or&act=view_org&id=<?php echo $res_org->fields[0] ?>"><?php echo $res_org->fields[2]?></a> 
    <?php
    if($parent>0){
    echo "</div>";
    }
    ?>
    </td>
    <td><?php echo $res_addr->fields[0]?></td>
    <td><?php echo $res_phone->fields[0]?></td>
    <td><?php echo $res_email->fields[0]?></td>
    <td><?php echo $res_bsd_country->fields[0]?></td>
    <td><?php echo $res_org->fields[2]?></td>
    <td><?php echo $res_org->fields[3]?></td>
</tr>
<?php
}
*/
