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

function shn_or_viewform_allorg(){
    global $global;
    $db=$global['db'];
    
?>
<div id ="result">
    <h2>Organization Registry</h2>
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
    $q = "select o_uuid,parent_id,name,man_power,resources from org_main where parent_id=0 order by name";
    $res_org=$db->Execute($q);
    while(!$res_org==NULL && !$res_org->EOF){
        $org_id=$res_org->fields[0];
        _shn_display_org($org_id);
        $q = "select o_uuid,parent_id,name,man_power,resources from org_main where parent_id=$org_id order by name";
        $res_operation=$db->Execute($q);
        while(!$res_operation==NULL && !$res_operation->EOF){
            $operation_id=$res_operation->fields[0];
            _shn_display_org($operation_id);
            $res_operation->MoveNext();
        }
        
        $res_org->MoveNext();
    }
?>
   </tbody>
  </table>
</div>

<?php
}


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

function shn_or_viewform_org($org_id)
{
    global $global;
    $db=$global['db'];
    $q = "select o_uuid,parent_id,name,reg_no,man_power,resources from org_main where o_uuid='{$org_id}'";
    
    $res_org=$db->Execute($q);
    if(!$res_org==NULL && !$res_org->EOF){
        
    $org_name=$res_org->fields[2];
    $reg_no=$res_org->fields[3]; 
    $man_power=$res_org->fields[4]; 
    $resources=$res_org->fields[5]; 
    $q = "select option_description from field_options,org_main where o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='opt_org_type'";

    $res_type=$db->Execute($q); 
    $org_type=$res_type->fields[0];

    $q = "select option_description from field_options,sector where pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
    $res_sector=$db->Execute($q);    
    $or_sector_type_options=array();
        
    while(!$res_sector->EOF){
        array_push(
            $or_sector_type_options,
            array(  'drop_desc'=>$res_sector->fields[0]
                    
            )       
        );
        
        $res_sector->MoveNext();
    }  

    $q = "select address from location_details where poc_uuid={$org_id}";
    $res_addr=$db->Execute($q); 
    $contact_address=$res_addr->fields[0];
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $contact_phone=$res_phone->fields[0];
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='name'";
    $res_name=$db->Execute($q);
    $contact_name=$res_name->fields[0];

    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='fax'";
    $res_fax=$db->Execute($q);
    $contact_fax=$res_fax->fields[0];

    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $contact_email=$res_email->fields[0];

    $q="select search_id,name from location_details,location where poc_uuid='{$org_id}' and location_details.location_id=location.location_id";
    $res_temp=$db->Execute($q);
    $bsd_village=$res_temp->fields[0];
    $loc=split("\.", $bsd_village);
    $bsd_village=$res_temp->fields[1];
    $bsd_country=$loc[0];
    $q="select name from location where search_id='$bsd_country'";
    $res_bsd_country=$db->Execute($q);
    $bsd_country=$res_bsd_country->fields[0];
    
    $bsd_province=$loc[0].".".$loc[1];
    $q="select name from location where search_id='$bsd_province'";
    $res_bsd_province=$db->Execute($q);
    $bsd_province=$res_bsd_province->fields[0];

    $bsd_district=$loc[0].".".$loc[1].".".$loc[1];
    $q="select name from location where search_id='$bsd_district'";
    $res_bsd_district=$db->Execute($q);
    $bsd_district=$res_bsd_district->fields[0];

    }
?>
<center><h2>Organization Registration Information of <h1> <?php echo $org_name?></h1></h2></center>
         
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=view_org','id'=>'formset');
	shn_form_open($header,false);
// call OR name
    $or_main = array(
                      
                        array('desc'=>_("Organization Type:"),'type'=>"text",'name'=>'org_type','size'=>50,'br'=>'1','value'=>$org_type
                        ),
                         array('multiple'=>'multiple','desc'=>_("Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$or_sector_type_options,
                        'br'=>'1'
                        )
                     );
    shn_form_add_component_list($or_main,$section=true,$legend='',$return=false,$default_val_req=true);
    // base location
    $location_inf = array(
                        array('desc'=>_("Country of Origin:"),'type'=>'text','name'=>'bsd_country','br'=>'1','value'=>$bsd_country                             ),                         
                       array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1,'value'=>$reg_no),
                        array('desc'=>_("Province :"),'type'=>'text','name'=>'bsd_province','br'=>'1','value'=>$bsd_province
                        ),// end of option
                        array('desc'=>_("District :"),'type'=>'text','name'=>'bsd_district','br'=>'1','value'=>$bsd_district
                        ),// end of option
                        array('desc'=>_("Village :"),'type'=>'text','name'=>'bsd_village',
                            'br'=>'1','value'=>$bsd_village
                        )
                    );// end of option
                             
    // OR infomation
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=true);
    $contact = array (
    					
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1,'value'=>$contact_name),
                        array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1,'value'=>$contact_address),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1,'value'=>$contact_phone),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1,'value'=>$contact_fax),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1,'value'=>$contact_email),

                        ); // end of contact 01
    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=true);
     
    // for comments
    $facilities = array(
		// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'man_power','br'=>1,'value'=>$man_power),
                array('type'=>"textarea",'desc'=>("Other relevant resources:"),'name'=>"resources",'rows'=>10,'cols'=>60,'br'=>1,'value'=>$resources)
    ); // end of comments
    shn_form_add_component_list($facilities,$section=true,$legend='Facilities Avaliable',$return=false,$default_val_req=true);
  
?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Close');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
    // end of form

    
} 



function shn_or_viewform_allvol(){
    global $global;
    $db=$global['db'];
    
?>
<div id ="result">
    <h2>Volunteer Registry</h2>
    <table>
        <thead>
            <td>Name</td>
            <td>Contact Address</td>
            <td>Contact Number</td>
            <td>Contact Email</td>
            <td>Country of Origin</td>
            <td>Occupation</td>
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
    $q = "select contact_value from contact where pgoc_uuid='{$pid}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $country=$res_pers->fields[2];
    $q="select name from location where location_id=$country";
    $res_country=$db->Execute($q);
    $country=$res_country->fields[0];
    

?>

<tr>
    <td>
    
    <a href="index.php?mod=or&act=view_vol&id=<?php echo $res_pers->fields[0] ?>"><?php echo $res_pers->fields[1]?></a> 
   
    </td>
    <td><?php echo $res_addr->fields[0]?></td>
    <td><?php echo $res_phone->fields[0]?></td>
    <td><?php echo $res_email->fields[0]?></td>
    <td><?php echo $country?></td>
    <td><?php echo $res_pers->fields[3]?></td>
   
</tr>
<?php
        $res_pers->MoveNext();
        
    }
?>
    </table>
</div>
<?php
}

function shn_or_viewform_vol($pid){
    global $global;
    $db=$global["db"];
    $q = "select person_uuid.p_uuid,full_name,birth_date,opt_country,opt_gender,occupation from person_details,person_uuid where person_details.p_uuid=person_uuid.p_uuid and person_uuid.p_uuid=$pid";
    $res_pers=$db->Execute($q);
    if(!$res_pers==NULL && !$res_pers->EOF){
        $name=$res_pers->fields[1];
        $dob=$res_pers->fields[2];
        $bsd_country=$res_pers->fields[3];
        $sex=$res_pers->fields[4];
        $q="select option_description from field_options where field_name='opt_gender' and option_code='{$sex}'";
        $res_sex=$db->Execute($q);
        $sex=$res_sex->fields[0];
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

        $q = "select address from location_details where poc_uuid='{$pid}'";
        $res_addr=$db->Execute($q);
        $contact_address=$res_addr->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$pid}' and opt_contact_type='curr'";
        $res_phone=$db->Execute($q);
        $contact_phone=$res_phone->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$pid}' and opt_contact_type='email'";
        $res_email=$db->Execute($q);
        $contact_email=$res_email->fields[0];
        $q="select search_id,name from location_details,location where poc_uuid='{$pid}' and location_details.location_id=location.location_id";
        $res_temp=$db->Execute($q);
         $bsd_village=$res_temp->fields[0];
        $loc=split("\.", $bsd_village);
        $bsd_village=$res_temp->fields[1];
        $bsd_country=$loc[0];
        $q="select name from location where search_id='$bsd_country'";
        $res_bsd_country=$db->Execute($q);
        $bsd_country=$res_bsd_country->fields[0];
    
        $bsd_province=$loc[0].".".$loc[1];
        $q="select name from location where search_id='$bsd_province'";
        $res_bsd_province=$db->Execute($q);
        $bsd_province=$res_bsd_province->fields[0];

        $bsd_district=$loc[0].".".$loc[1].".".$loc[1];
        $q="select name from location where search_id='$bsd_district'";
        $res_bsd_district=$db->Execute($q);
        $bsd_district=$res_bsd_district->fields[0];


       
        $q = "select option_description from field_options,sector where pgoc_uuid='{$pid}' and field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
        $res_sector=$db->Execute($q);    
        $person_sector_type_options=array();
        
        while(!$res_sector->EOF){
            array_push(
            $person_sector_type_options,
                array(  'drop_desc'=>$res_sector->fields[0]
                )       
            );
        $res_sector->MoveNext();
        }  
    }
?>

<center><h2>Volunteer Registration information of<h1><?php echo $name ?></h1> </h2></center>

<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=view_vol','id'=>'formset');
	shn_form_open($header,false);

 $perdetails = 	array (
                        			//	array('desc'=>_("Name in Full : "),'type'=>"text",'size'=>50,'name'=>'name','br'=>1,'value'=>$name),
                       					array('desc'=>_("Date of Birth: "),'type'=>"text",'size'=>10,'name'=>'dob','br'=>1,'value'=>$dob),
                        				array('desc'=>_("Sex :"),'type'=>'text','name'=>'sex','br'=>1,'size'=>10,'value'=>$sex	),							  
                        				
                        				array('desc'=>_("Occupation : "),'type'=>"text",'size'=>20,'name'=>'job','br'=>1,'value'=>$job)
           
                        ); // end of perdetails
shn_form_add_component_list($perdetails,$section=true,$legend='',$return=false,$default_val_req=true);

$identity = 	    array (
                        				
                        				array('desc'=>_("National ID No: "),'type'=>"text",'size'=>15,'name'=>'nic','br'=>1,'value'=>$nic),
                        				array('desc'=>_("Passport No: "),'type'=>"text",'size'=>15,'name'=>'pas','br'=>1,'value'=>$pas),
                        				array('desc'=>_("Driving License No: "),'type'=>"text",'size'=>15,'name'=>'dln','br'=>1,'value'=>$dln),
           
                        ); 
shn_form_add_component_list($identity,$section=true,$legend='Identity Information',$return=false,$default_val_req=true);



    // base location
    $location_inf = array(
                        array('desc'=>_("Country of Origin:"),'type'=>'text','name'=>'bsd_country','br'=>'1','value'=>$bsd_country),                         
                       
                        array('desc'=>_("Province :"),'type'=>'text','name'=>'bsd_province','br'=>'1','value'=>$bsd_province ),// end of option
                        array('desc'=>_("District :"),'type'=>'text','name'=>'bsd_district','br'=>'1','value'=>$bsd_district
                        ),// end of option
                        array('desc'=>_("Village :"),'type'=>'text','name'=>'bsd_village','br'=>'1','value'=>$bsd_village
                        )
                    );// end of option
                             
    // OR infomation
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=false);

// call OR name
    $services =    array(                     
                        array('multiple'=>"true",'desc'=>_("Services offered  : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$person_sector_type_options,
                        'br'=>'1'
)
                         );
shn_form_add_component_list($services,$section=true,$legend='Volunteerism',$return=false,$default_val_req=false);    

    $contact = array (
    					
                        
                        array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1,'value'=>$contact_address),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1,'value'=>$contact_phone),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1,'value'=>$contact_fax),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1,'value'=>$contact_email),

                        ); // end of contact 01
    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=false);
 ?>
   
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Close');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
    // end of form

}

?>
