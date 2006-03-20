<?php
/** View ,Edit forms for Organizations of the Organization Registry 
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
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_location.inc";

function _shn_or_viewform_allorg($no=NULL)
{
    global $global;
    $db=$global['db'];
?>
<div id ="result">
	<table>
        <thead>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Services Provided")?></td>
            <td><?=_("Organization Type")?></td>
            <td><?=_("Country of Origin")?></td>
            <td><?=_("Address")?></td>
            <td><?=_("Contact Numbers")?></td>
            <td><?=_("Man Power")?></td>
            <td><?=_("Equipment")?></td>
            <td><?=_("Other <br /> Facilities")?></td>
        </thead>
        <tbody>
<?php
    if($no==NULL){
        $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where parent_id=0 order by name";
        $res_org=$db->Execute($q);
    }else {
        $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where parent_id=0 order by o_uuid desc";
        $res_org=$db->SelectLimit($q,$no);
    }
    while(!$res_org==NULL && !$res_org->EOF){
        $org_id=$res_org->fields[0];
        if($org_id!=0){
        _shn_display_org($org_id);
        $q = "select o_uuid from org_main where parent_id=$org_id order by name";
        $res_operation=$db->Execute($q);
        while(!$res_operation==NULL && !$res_operation->EOF){
            $operation_id=$res_operation->fields[0];
            _shn_display_org($operation_id);
            $res_operation->MoveNext();
        }
        }
        $res_org->MoveNext();
    }
?>
   </tbody>
  </table>
</div>
<?php
}

function _shn_display_org($org_id,$indent=true,$edit=false)
{
    global $global;
    $db=$global["db"];
    $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where o_uuid=$org_id";
    $res_org=$db->Execute($q);
    $org_id=$res_org->fields[0];        
    $q = "select address from location_details where poc_uuid='{$org_id}'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
    $res_mobile=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $q="select search_id from location_details,location where poc_uuid='{$org_id}' and location_details.location_id=location.location_id";
    $res_temp=$db->Execute($q);
    $loc=$res_temp->fields[0][0];
    $q="select name from location where location_id='{$loc}'";
    $res_bsd_country=$db->Execute($q);
    $q = "select option_description from field_options,org_main where o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='opt_org_type'";
    $res_type=$db->Execute($q); 
    $org_type=$res_type->fields[0];
    $q = "select option_description from field_options,sector where pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
    $res_sector=$db->Execute($q);    
?>
<tr>
    <td>
     <?php
    $parent=$res_org->fields[1];
    if($parent>0 && $indent){
        echo "<div id='parent'>";
    }
    ?>
    <a href="index.php?mod=or&act=view_org&id=<?php echo $res_org->fields[0] ?>"><?php echo $res_org->fields[2]?></a> 
    <?php
    if($parent>0 && $indent){
        echo "</div>";
    }
    ?>
    </td>
    <td>
<?php
    while(!$res_sector->EOF){
        echo $res_sector->fields[0]."<br />";
        $res_sector->MoveNext();
    }
?>
    </td>
    <td><?php echo $org_type?></td>
    <td><?php echo $res_bsd_country->fields[0]?></td>
    <td><?php echo $res_addr->fields[0]?><br /><a href="mailto:<?php echo $res_email->fields[0]?>"/><?php echo $res_email->fields[0]?></a></td>
    <td><?php echo $res_phone->fields[0]?><br /><?php echo $res_mobile->fields[0]?></td>
    <td><?php echo $res_org->fields[3]?></td>
    <td><?php echo $res_org->fields[4]?></td>
    <td><?php echo $res_org->fields[5]?></td>
</tr>
<?php
}

function _shn_or_viewform_org($org_id,$error=false)
{
    include_once "lib_or.inc";
    global $global;
    $db=$global['db'];
    $q = "select o_uuid,parent_id,name,reg_no,man_power,resources from org_main where o_uuid='{$org_id}'";
    $res_org=$db->Execute($q);
    if(!$res_org==NULL && !$res_org->EOF){
        $parent=($res_org->fields[1]=='0')?true:false;    
        $org_name=$res_org->fields[2];
        $reg_no=$res_org->fields[3]; 
        $q = "select option_code from field_options,org_main where o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='opt_org_type'";
        $res_type=$db->Execute($q); 
        $org_type=$res_type->fields[0];
        $q = "select option_code from field_options,sector where pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
        $res_sector=$db->Execute($q);    
        $or_sector_arr=array();
        
        while(!$res_sector->EOF){
            array_push(
                $or_sector_arr,
                $res_sector->fields[0]
            );       
            $res_sector->MoveNext();
        } 
    $q = "select location_id from location_details where poc_uuid='{$org_id}'";
    $res_loc=$db->Execute($q);
    $bsd_village=$res_loc->fields[0];
   // $loc=_shn_or_get_org_loc_parents($org_id);
    //$bsd_village=$loc[5][2];
    }
?>
<h2><?=_("Organization Registration Information of <em>").$org_name?></em></h2>
<?php
 if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $form_opts['name']='view';
    $form_opts['req_message']=false;
    shn_form_fopen("view_org_submit",null,$form_opts);
    shn_form_fsopen(_('Primary Details'));
    $extra_opts['req']=true;
    $extra_opts['value']=$org_name;
    shn_form_text(_("Organization Name : "),'org_name','size="50"', $extra_opts); 
    if($parent){
        shn_form_text(_("Registration Number : "),'reg_no','size="50"',array('value'=>$reg_no)); 
    }
    shn_form_fsclose();
    shn_form_fsopen(_("Organization Type *(req)"));
    _shn_or_display_org_type($error,false,$org_type);
    shn_form_fsclose();
    shn_form_fsopen(_("Organization Sector *(req)"));
    _shn_or_display_sector($error,$or_sector_arr);
    shn_form_fsclose();
    shn_form_fsopen("Base Location");
    $range= shn_or_get_loc_range();
    shn_location_form_org($range,$bsd_village);
    shn_form_fsclose();
    shn_form_fsopen(_("Contact Information"));
    _shn_or_display_contact_person($error,true,$org_id);
    shn_form_fsclose();
    shn_form_fsopen(_("Facilities Avaliable"));
    _shn_or_display_org_facilities($error,$org_id);
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
    shn_form_button(_("Close"),"onClick='change_action(\"close\")'");
	shn_form_button(_("Save"),"onClick='change_action(\"edit\")'");
    shn_form_button(_("Delete"),"onClick='change_action(\"del\")'");
    shn_form_hidden(array('action'=>'0'));
     shn_form_hidden(array('org_id'=>$org_id));
    _shn_or_action_change_javascript("action");
?>
</center>
<br />
<?php
        //close the form
    shn_form_close(false);
?>				     
</div>
<?php
} 
?>
