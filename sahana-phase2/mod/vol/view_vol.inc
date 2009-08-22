<?php
/** View ,Edit forms for Volunteers of the Organization Registry 
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
include_once ("lib_vol.inc");


function _shn_vol_viewform_all()
{
    global $global;
    $db=$global['db'];
?>
<div id ="result">
    <table>
        <thead>
            <td><?php echo _t("Name")?></td>
	        <td><?php echo _t("Services Offered")?></td>
            <td><?php echo _t("Skills")?></td>
           <!-- <td><?php echo _t("Country of Origin")?></td>-->
            <td><?php echo _t("Contact Address")?></td>
            <td><?php echo _t("Contact Number")?></td>
            <td><?php echo _t("Contact Mobile")?></td>
            <td><?php echo _t("Contact Email")?></td>
        </thead>
<?php    
    $q = "select person_uuid.p_uuid,full_name,opt_country,occupation from person_details,person_status,person_uuid where person_status.isReliefWorker=1 and  person_status.p_uuid=person_uuid.p_uuid and person_details.p_uuid=person_uuid.p_uuid order by full_name";
	$res_pers=$db->Execute($q);
    while(!$res_pers==NULL && !$res_pers->EOF){
    $pid=$res_pers->fields[0];        
    $q = "select address from location_details where poc_uuid='{$pid}'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$pid}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$pid}' and opt_contact_type='pmob'";
    $res_mobile=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$pid}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $country=$res_pers->fields["opt_country"];
    $q="select name from location where loc_uuid='{$country}'";
    $res_country=$db->Execute($q);
    $country=$res_country->fields["name"];
    $q = "select option_description from field_options,sector where pgoc_uuid='{$pid}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
    $res_sector=$db->Execute($q);    
    $q = "select distinct(option_description) from field_options,vol_skills where p_uuid='{$pid}' and
field_options.option_code=vol_skills.opt_skill_code and field_options.field_name='opt_skill_type'";
    $res_skills=$db->Execute($q);
?>
<tr>
    <td>
    <a href="index.php?mod=vol&act=view&id=<?php echo $res_pers->fields[0] ?>"><?php echo $res_pers->fields[1]?></a> 
    </td>
    <td>
<?php
    while(!$res_sector->EOF){
        echo $res_sector->fields[0]."<br />";
        $res_sector->MoveNext();
    }
?>
    </td>
    <td>
<?php
    while((!$res_skills->NULL)&&(!$res_skills->EOF)){
        echo $res_skills->fields[0]."<br />";
        $res_skills->MoveNext();
    }
?>
    </td>
    <!--<td><?php echo $country?></td>-->
    <td><?php echo $res_addr->fields[0]?></td>
    <td><?php echo $res_phone->fields[0]?></td>
    <td><?php echo $res_mobile->fields[0]?></td>
    <td><?php echo $res_email->fields[0]?></td>
</tr>
<?php
        $res_pers->MoveNext();
    }
?>
    </table>
</div>
<?php
}

function _shn_vol_viewform($pid,$error=false)
{
    global $global;
    $db=$global["db"];
    $q = "select person_uuid.p_uuid,full_name,birth_date,opt_country,opt_gender,occupation from person_details,person_uuid where person_details.p_uuid=person_uuid.p_uuid and person_uuid.p_uuid=$pid";
    $res_pers=$db->Execute($q);
    if(!$res_pers==NULL && !$res_pers->EOF){
        $name=$res_pers->fields[1];
        $dob=$res_pers->fields[2];
        $bsd_country=$res_pers->fields[3];
        $sex=$res_pers->fields[4];
        $job=$res_pers->fields[5];
        $q="Select serial from identity_to_person where p_uuid=$pid and opt_id_type='nic'";
        $res_nic=$db->Execute($q);
        $nic=$res_nic->fields[0];
        $q="Select serial from identity_to_person where p_uuid=$pid and opt_id_type='pas'";
        $res_pas=$db->Execute($q);
        $pas=$res_pas->fields[0];
        $q="Select serial from identity_to_person where p_uuid=$pid and opt_id_type='dln'";
        $res_dln=$db->Execute($q);
        $dln=$res_dln->fields[0];
       // $loc=_shn_vol_get_org_loc_parents($pid);
       // $bsd_village=$loc[3][2];
        $q = "select location_id from location_details where poc_uuid='{$pid}'";
    	$res_loc=$db->Execute($q);
    	$bsd_village=$res_loc->fields[0];
        $q = "select option_code from field_options,sector where pgoc_uuid='{$pid}' and field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
        $res_sector=$db->Execute($q);    
        $sector_arr=array();
        while(!$res_sector->EOF){
            array_push(
                $sector_arr,
                $res_sector->fields[0]
            );       
            $res_sector->MoveNext();
        } 
        
        $q = "select option_code from field_options,vol_skills where p_uuid='{$pid}' and field_options.option_code=vol_skills.opt_skill_code and field_options.field_name='opt_skill_type'";
        $res_skill=$db->Execute($q);    
        $skill_arr=array();
        while(!$res_skill->EOF){
            array_push(
                $skill_arr,
                $res_skill->fields[0]
            );       
            $res_skill->MoveNext();
        } 
 
    }
?>
<h2><?php echo _t("Volunteer Registration information of ")?><em> <?php echo $name ?></em> </h2>
<?php
 if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $form_opts['name']='view';
    $form_opts['req_message']=false;
    shn_form_fopen("view_submit",null,$form_opts);
   // shn_form_fsopen(_t("Picture"));
   // shn_show_thumb($pid);
   // shn_form_fsclose();
   	shn_form_fsopen(_t('Primary Details'));
   	?><div class="info"><?php echo  _t("These are the basic details of a Volunteer. Name is required ,but others optional")."</div><br />";
    $extra_opts['value']=$name;
    $extra_opts['req']=true;
    shn_form_text(_t("Name in Full : "),'name','size="50"',$extra_opts); 
    $extra_opts['req']=false;
    $extra_opts['value']=$dob;
    shn_form_text(_t("Date of Birth : "),'dob','size="10"',$extra_opts); 
    //shn_form_date(_t("Date of Birth: "),'dob', null ) ;
    $extra_opts['value']=$job;
    shn_form_text(_t("Occupation : "),'job','size="50"',$extra_opts); 
    _shn_vol_display_gender($error,$sex);
    shn_form_fsclose();
    shn_form_fsopen(_t('Identity Information'));
    ?><div class="info"><?php echo  _t("Please enter all the identity information you have. e.g Passport No ")."</div><br />";
    $extra_opts['value']=$nic;
    shn_form_text(_t("National ID No : "),'nic','size="50"',$extra_opts); 
    $extra_opts['value']=$pas;
    shn_form_text(_t("Passport No : "),'pas','size="50"',$extra_opts); 
    $extra_opts['value']=$dln;
    shn_form_text(_t("Driving License No : "),'dln','size="50"',$extra_opts); 
    shn_form_fsclose();

    $range= shn_vol_get_loc_range();
     // base location
    shn_form_fsopen("Base Location");
	shn_location($range,$bsd_village);
    shn_form_fsclose();
	shn_form_fsopen(_t("Services Offered"));
    _shn_vol_display_sector($error,$sector_arr);
    shn_form_fsclose();
    shn_form_fsopen(_t("Skills"));
    _shn_vol_display_skills($error,$skill_arr);
    shn_form_fsclose();
    shn_form_fsopen(_t("Contact Information"));
     _shn_vol_display_contact_person(false,false,$pid);
    shn_form_fsclose();
?>
<br />
<center>
<?php
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    shn_form_button(_t("Close"),"onClick='change_action(\"close\")'",$extra_opts);
    shn_form_button(_t("Save"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick='change_action(\"del\")'",$extra_opts);
    //$change= array('type'=>'hidden', 'name'=>'action');
	shn_form_hidden(array('action'=>'0'));
	//shn_form_add_component($change,false,false);
    //$p_id= array('type'=>'hidden', 'name'=>'pid','value'=>$pid);
	shn_form_hidden(array('pid'=>$pid));
	//shn_form_add_component($p_id,false,false);
    _shn_vol_action_change_javascript("view","action");
?>
</center>
<br />
<?php
    shn_form_fclose();
?>				     
</div>
<?php
}

