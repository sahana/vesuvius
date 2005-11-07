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


function shn_or_regform_org($error=false)
{
    global $global;
    $db=$global['db'];
    
    $q = "select option_code,option_description from field_options where field_name='opt_org_type'";
    $res=$db->Execute($q);
    $or_type_options=array();
        
    while(!$res==NULL && !$res->EOF){
        array_push(
            $or_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
    
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
<h2>Organization Registration</h2>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=reg_org_cr','id'=>'formset');
	shn_form_open($header,false);
// call OR name
    $or_main = array(
                        array('desc'=>_("* Organization name : "),'type'=>"text",'size'=>50,'name'=>'org_name','br'=>0,'br'=>'1'),    
                        array('desc'=>_("* Organization Type:"),'type'=>"dropdown",'name'=>'org_type','options'=>$or_type_options,'br'=>'1'
                        ),
                        array('desc'=>_("* Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$or_sector_type_options,
                        'br'=>'1'
                        ) // end of list form
                     );
    shn_form_add_component_list($or_main,$section=true,$legend='',$return=false,$default_val_req=true);
    // base location
    $location_inf = array(
                        array('desc'=>_("* Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$or_countries,'br'=>'1'                             ),                         
                       array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1),
                        array('desc'=>_("* Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$or_provinces,'br'=>'1'
                        ),// end of option
                        array('desc'=>_("* District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$or_districts,'br'=>'1'
                        ),// end of option
                        array('desc'=>_("* Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$or_villages,'br'=>'1'
                        )
                    );// end of option
                             
    // OR infomation
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=true);
    $contact = array (
    					
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1),
                        array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1),

                        ); // end of contact 01
    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=true);
     
    // for comments
    $facilities = array(
		// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'man_power','br'=>1),
                array('type'=>"textarea",'desc'=>("Other relevant resources:"),'name'=>"resources",'rows'=>10,'cols'=>60,'br'=>1)
    ); // end of comments
    shn_form_add_component_list($facilities,$section=true,$legend='Facilities Avaliable',$return=false,$default_val_req=true);
  /*
  // for get login info
    $login_info = array(
    		       	array('desc'=>_("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1),
                    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    shn_form_add_component_list($login_info,$section=true,$legend='Create an Account for Login',$return=false,$default_val_req=false);
*/
  $extra = array(
  /**
                    array('desc'=>_("Make my contact information available  "),'type'=>'checkbox','name'=>'chk_avail','value'=>'avail','algin'=>'right','select'=>1,'br'=>1),
     **/
     // add location
                    array('desc'=>_("Add Operation<br> (Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is usefull.) "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1,'br'=>4)
                    
            );
    shn_form_add_component_list($extra,$section=true,$legend='Extra',$return=false,$default_val_req=true);
?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Next');
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
     
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type'";
    $res=$db->Execute($q);
    $person_sector_type_options=array();
        
    while(!$res->EOF){
        array_push(
            $person_sector_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='1'";
    $res=$db->Execute($q);
    $person_countries=array();
        
    while(!$res->EOF){
        array_push(
            $person_countries,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }

    $q = "select location.name,location.location_id from location where location.opt_location_type='2'";
    $res=$db->Execute($q);
    $person_provinces=array();
        
    while(!$res->EOF){
        array_push(
            $person_provinces,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='3'";
 
    $res=$db->Execute($q);
    $person_districts=array();
        
    while(!$res->EOF){
        array_push(
            $person_districts,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='4'";
 

    $res=$db->Execute($q);
    $person_villages=array();
        
    while(!$res->EOF){
        array_push(
            $person_villages,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
?>
<h2>Volunteer Registration </h2>
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
                        				array('desc'=>_("Gender :"),'type'=>'dropdown','name'=>'sex','br'=>1,'options'=>$gender),							  
                        				
                        				array('desc'=>_("Occupation : "),'type'=>"text",'size'=>20,'name'=>'job','br'=>1)
           
                        ); // end of perdetails
shn_form_add_component_list($perdetails,$section=true,$legend='',$return=false,$default_val_req=true);

$identity = 	    array (
                        				
                        				array('desc'=>_("National ID No: "),'type'=>"text",'size'=>15,'name'=>'nic','br'=>1),
                        				array('desc'=>_("Passport No: "),'type'=>"text",'size'=>15,'name'=>'pas','br'=>1),
                        				array('desc'=>_("Driving License No: "),'type'=>"text",'size'=>15,'name'=>'dln','br'=>1),
           
                        ); 
shn_form_add_component_list($identity,$section=true,$legend='Identity Information',$return=false,$default_val_req=true);



    // base location
    $location_inf = array(
                        array('desc'=>_("* Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$person_countries,'br'=>'1'                             ),                         
                       
                        array('desc'=>_("* Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$person_provinces,'br'=>'1'
                        ),// end of option
                        array('desc'=>_("* District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$person_districts,'br'=>'1'
                        ),// end of option
                        array('desc'=>_("* Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$person_villages,'br'=>'1'
                        )
                    );// end of option
                             
    // OR infomation
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=false);

// call OR name
    $services =    array(                     
                        array('multiple'=>"true",'desc'=>_("* select services you can offer  : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$person_sector_type_options,
                        'br'=>'1'
)
                         );
shn_form_add_component_list($services,$section=true,$legend='Volunteerism',$return=false,$default_val_req=false);    

    $contact = array (
    					
                        
                        array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1),

                        ); // end of contact 01
    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=false);
 ?>
   
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
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

// call OR name
    $or_main = array(
                        array('desc'=>_("Operation/Branch name : "),'type'=>"text",'size'=>50,'name'=>'opr_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        
                        array('multiple'=>"true",'desc'=>_("Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$or_sector_type_options,
                        'br'=>'1'
                        ) // end of list form
                     );
    shn_form_add_component_list($or_main,$section=true,$legend='',$return=false,$default_val_req=true);
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
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=false);
    $contact = array (
    					
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1,'value'=>$_SESSION["contact_name"]),
                        array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1,'value'=>$_SESSION["contact_address"]),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1,'value'=>$_SESSION["contact_phone"]),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1,'value'=>$_SESSION["contact_fax"]),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1,'value'=>$_SESSION["contact_email"]),

                        ); // end of contact 01
    shn_form_add_component_list($contact,$section=true,$legend='Contact Information',$return=false,$default_val_req=false);
     
    // for comments
    $facilities = array(
		// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'man_power','br'=>1,'value'=>$_SESSION["man_power"]),
                array('type'=>"textarea",'desc'=>("Other relevant resources:"),'name'=>"resources",'rows'=>10,'cols'=>60,'br'=>1,'value'=>$_SESSION["resources"])
    ); // end of comments
    shn_form_add_component_list($facilities,$section=true,$legend='Facilities Avaliable',$return=false,$default_val_req=false);
    

  $extra = array(
                    
                    array('desc'=>_("Add More Operations "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1,'br'=>1)
                    
            );
    shn_form_add_component_list($extra,$section=true,$legend='Extra',$return=false,$default_val_req=false);
?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Next');
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
