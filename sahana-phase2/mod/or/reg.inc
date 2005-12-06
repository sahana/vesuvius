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
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
include_once "lib_or.inc";

function shn_or_regform_org($error=false)
{
    global $global;
    $db=$global['db'];
?>
<h1 align="center">Organization Registration</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
    shn_form_open($header,false);
    $or_type=_shn_or_display_org_type($error);
    $or_main=array();
    $or_name=array('desc'=>_("* Organization Name : "),'type'=>"text",'size'=>50,'name'=>'org_name','br'=>0,'br'=>'1'); 
    $or_reg=array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>'1');
    $or_sector=_shn_or_display_sector($error);
    array_push(
            $or_main,
            $or_name
            );
    array_push(
            $or_main,
            $or_type
            );
    array_push(
            $or_main,
            $or_sector
            );
    array_push(
            $or_main,
            $or_reg
            );
    shn_form_add_component_list($or_main,$section=true,$legend='',$return=false,$default_val_req=$error);
  
   // base location
    $location_inf = shn_location_form('1','4'); 
                              
    // Contact infomation
    $contact=_shn_or_display_contact_person($error,true,null);

    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=$error);
     
    $facilities=_shn_or_display_org_facilities($error);
    shn_form_add_component_list($facilities,$section=true,$legend='Facilities Avaliable',$return=false,$default_val_req=$error);
  /*
  $login_info=_shn_or_display_logininfo($error);
    shn_form_add_component_list($login_info,$section=true,$legend='Create an Account for Login',$return=false,$default_val_req=false);
*/
    $extra=_shn_or_display_extra($error);
    shn_form_add_component_list($extra,$section=true,$legend='Extra',$return=false,$default_val_req=$error);
?>
<br />
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Next');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
    //close the form
    shn_form_close(false);
?>				     
</div>
<?php
    // end of form
} 


function shn_or_regform_vol($error=false)
{
  global $global;
    $db=$global['db'];
    $q = "select option_code,option_description from field_options where field_name='opt_gender'";
    $res=$db->Execute($q);
    $gender=array();
        
    while(!$res->EOF){
        array_push(
            $gender,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
     
 
?>
<h1 align="center">Volunteer Registration </h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_vol_cr','id'=>'formset');
	shn_form_open($header,false);

 $perdetails = 	array (
                        				array('desc'=>_("* Name in Full : "),'type'=>"text",'size'=>50,'name'=>'name','br'=>1),
                       					array('desc'=>_("Date of Birth: "),'type'=>"date",'size'=>10,'name'=>'dob','br'=>1),
                        			             				
                        				array('desc'=>_("Occupation : "),'type'=>"text",'size'=>20,'name'=>'job','br'=>1)
           
                        ); 
$gender=_shn_or_display_gender($error);
array_push(
            $perdetails,
            $gender
            );
// end of perdetails
shn_form_add_component_list($perdetails,$section=true,$legend='',$return=false,$default_val_req=$error);

$identity = 	    array (
                        				
                        				array('desc'=>_("National ID No: "),'type'=>"text",'size'=>15,'name'=>'nic','br'=>1),
                        				array('desc'=>_("Passport No: "),'type'=>"text",'size'=>15,'name'=>'pas','br'=>1),
                        				array('desc'=>_("Driving License No: "),'type'=>"text",'size'=>15,'name'=>'dln','br'=>1),
           
                        ); 
shn_form_add_component_list($identity,$section=true,$legend='Identity Information',$return=false,$default_val_req=$error);



    // base location
   $location_inf = shn_location_form('1','4'); 
// call OR name
   $services=array();
   $sectors=_shn_or_display_sector($error);
   array_push(
            $services,
            $sectors
            );    
shn_form_add_component_list($services,$section=true,$legend='Volunteerism',$return=false,$default_val_req=$error);    

   $contact=_shn_or_display_contact_person($error,false);

    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=$error);
 ?>
   
<br />
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
    // end of form

    
   
} 

function shn_or_regform_operation(){

  global $global;
    $db=$global['db'];
    
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type'";
    $res=$db->Execute($q);
    $or_sector_type_options=array();
        
    while(!$res->EOF){
        array_push(
            $or_sector_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='1'";
    $res=$db->Execute($q);
    $or_countries=array();
        
    while(!$res->EOF){
        array_push(
            $or_countries,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }

    $q = "select location.name,location.location_id from location where location.opt_location_type='2'";
    $res=$db->Execute($q);
    $or_provinces=array();
        
    while(!$res->EOF){
        array_push(
            $or_provinces,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='3'";
 
    $res=$db->Execute($q);
    $or_districts=array();
        
    while(!$res->EOF){
        array_push(
            $or_districts,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='4'";
 

    $res=$db->Execute($q);
    $or_villages=array();
        
    while(!$res->EOF){
        array_push(
            $or_villages,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
?>
<h2>Add an Operation/Branch under the Organization <?php echo $_SESSION["parent_name"]?> </h2>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_operation_cr','id'=>'formset');
	shn_form_open($header,false);



	$or_main=array();
	$or_name=array('desc'=>_("* Operation/Branch Name : "),'type'=>"text",'size'=>50,'name'=>'org_name','br'=>0,'br'=>'1'); 
              
                        
    	$or_sector=_shn_or_display_sector($error);

array_push(
            $or_main,
            $or_name
            );


array_push(
            $or_main,
            $or_sector
            );

    shn_form_add_component_list($or_main,$section=true,$legend='',$return=false,$default_val_req=$error);
    // base location
    $location_inf = array(
                        array('desc'=>_("Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$or_countries,'br'=>'1'                             ),                         
                       
                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$or_provinces,'br'=>'1'
                        ),// end of option
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$or_districts,'br'=>'1'
                        ),// end of option
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$or_villages,'br'=>'1'
                        )
                    );// end of option
                             
    // OR infomation
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=$error);

$contact=_shn_or_display_contact_person($error);

    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=$error);
     
    $facilities=_shn_or_display_org_facilities($error);
    shn_form_add_component_list($facilities,$section=true,$legend='Facilities Avaliable',$return=false,$default_val_req=$error);
 
  $extra=_shn_or_display_extra($error);
    shn_form_add_component_list($extra,$section=true,$legend='Extra',$return=false,$default_val_req=$error);
   
?>
<br />
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Next');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
    // end of form
  
}                                               
?>
