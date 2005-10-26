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

function shn_or_viewform_org(){
    global $global;
    $db=$global['db'];
    
?>
<div id ="result">
    <h1>"Organization Registry"</h1>
    <table>
        <thead>
            <td>Organization name</td>
            <td>Contact Address</td>
            <td>Contact Number</td>
            <td>Contact Email</td>
            <td>Country of Origin</td>
            <td>Man Power</td>
            <td>Facilities</td>
        </thead>
<?php    
    $q = "select o_uuid,name,man_power,resources from org_main";
    //$q = "select o_uuid,name,address_1,telephone,email,man_power,resources from org_main,,org_users,person_contact where org_main.id=org_users.org_id and users.user_id=person_contact.p_uuid";
    $res=$db->Execute($q);
    while(!res==NULL && !$res->EOF){
        
    $org_id=$res->fields[0];        
    $q = "select contact_value from contact where pgc_uuid='{$org_id}' and opt_contact_type='home'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);

    $q="select location_id from org_location where org_id='{$org_id}'";
    $res_temp=$db->Execute($q);
    $loc=$res_temp->fields[0][0];
    $q="select name from location where location_id='{$loc}'";
    $res_bsd_country=$db->Execute($q);
   // $q = "select name from location,org_location where org_id='{$org_id}' and location.location_id=org_location.location_id";
    //$q = "select name from location,org_location where org_id='{$org_id}' and opt_location_type='1' and location.location_id=org_location.location_id";
   // $res_bsd_country=$db->Execute($q);
?>

<tr>
    <td><a href="index.php?mod=or&act=org_view&id=<?php echo $res->fields[0] ?>"><?php echo $res->fields[1]?></a> 
    </td>
    <td><?php echo $res_addr->fields[0]?></td>
    <td><?php echo $res_phone->fields[0]?></td>
    <td><?php echo $res_email->fields[0]?></td>
    <td><?php echo $res_bsd_country->fields[0]?></td>
    <td><?php echo $res->fields[2]?></td>
    <td><?php echo $res->fields[3]?></td>
</tr>
<?php
        $res->MoveNext();
        
    }
?>
    </table>
</div>
<?php
}
?>
