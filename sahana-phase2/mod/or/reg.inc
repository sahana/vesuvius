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
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";

function shn_or_org_reg(){
    global $global;
    $db=$global['db'];
    
    $q = "select * from org_types";
    $res=$db->Execute($q);
    $or_type_options=array();
        
    while(!$res->EOF){
        array_push(
            $or_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
        
    }
    
    $q = "select * from org_sector_types";
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
    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='country'";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='province'";
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
    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='district'";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='village'";
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
echo "<h2><center>" . _("Organization Registration") . "</center></h2>";
    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=or&act=reg_org_cr")
                    );
                    
    shn_show_form($header);
    
    // call OR name
    $or_main = array(
                        array('legend'=>''),
                        array('desc'=>_("Organization name : "),'type'=>"text",'size'=>50,'name'=>'org_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("Organization Type:"),'type'=>"dropdown",'name'=>'org_type','options'=>$or_type_options
                        ),
                        array('desc'=>_("Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"org_sector[]",'option'=>$or_sector_type_options,
                        'br'=>'1'
                        ) // end of list form
                     );
    shn_show_form($or_main);

    // base location
    $location_inf = array(
    					array('legend'=>_("Base Location Information :")),           
                        array('desc'=>_("Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$or_countries
                             ),                         
                       array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1),
                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$or_provinces
                        ),// end of option
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$or_districts
                        ),// end of option
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$or_villages
                        )
                    );// end of option
                             
	shn_show_form($location_inf);
    // OR infomation
    
    $contact01 = array (
    					array('legend'=>_("Contact Person Information :")),          
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1),
                        array('desc'=>_("Address : "),'type'=>"txtarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1),

                        ); // end of contact 01
    shn_show_form($contact01);
    
     
    // for comments
    $facilities = array(
					array('legend'=>_("Facilities Avaliable : ")),       			// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'man_power','br'=>1),
                array('type'=>"txtarea",'desc'=>("Other relevant resources:"),'name'=>"resources",'rows'=>10,'cols'=>60)
    ); // end of comments

    shn_show_form($facilities);

    // for get login info
    $login_info = array(
    				array('legend'=>_("Login information : ")),       	
                    array('desc'=>_("User name : "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_("Password : "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    shn_show_form($login_info); 	

    // make my contact info available
    $extra = array(
                    array('desc'=>_("Make my contact information available  "),'type'=>'checkbox','name'=>'chk_avail','value'=>'avail','algin'=>'right','select'=>1,'br'=>1),
     // add location
                    array('desc'=>_(" Add branch information  "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1)
                    
            );
    shn_show_form($extra);


    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
} 

function shn_or_branch_reg(){
    global $global;
    $db=$global['db'];
    
    $q = "select * from org_sector_types";
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
    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='country'";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='province'";
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
    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='district'";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='village'";
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
echo "<h2><center>" . _("Branch Registration") . "</center></h2>";
    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=or&act=reg_branch_cr")
                    );
                    
    shn_show_form($header);
    
    echo "<h3>Add a Branch Under".$org."</h3><br>";
    // call OR name
    $or_main = array(
                        array('legend'=>''),
                        array('desc'=>_("Branch name : "),'type'=>"text",'size'=>50,'name'=>'org_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"or_sector[]",'option'=>$or_sector_type_options,
                        'br'=>'1'
                        ) // end of list form
                     );
    shn_show_form($or_main);

    // base location
    $location_inf = array(
    					array('legend'=>_("Base Location Information :")),           
                        array('desc'=>_("Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$or_countries
                             ),                         
                       array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1),
                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$or_provinces
                        ),// end of option
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$or_districts
                        ),// end of option
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$or_villages
                        )
                    );// end of option
                             
	shn_show_form($location_inf);
    // OR infomation
    
    $contact01 = array (
    					array('legend'=>_("Contact Person Information :")),          
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1),
                        array('desc'=>_("Address : "),'type'=>"txtarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1),

                        ); // end of contact 01
    shn_show_form($contact01);
    
     
    // for comments
    $facilities = array(
					array('legend'=>_("Facilities Avaliable : ")),       			// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'manpower','br'=>1),
                array('type'=>"txtarea",'desc'=>("Other relevant resources:"),'name'=>"some_comments",'rows'=>10,'cols'=>60)
    ); // end of comments

    shn_show_form($facilities);
    
    // make my contact info available
    $extra = array(
            // add location
                    array('desc'=>_(" Add more branches  "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1)
                    
            );
    shn_show_form($extra);


    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
} 

function shn_or_vol_reg(){

    global $global;
    $db=$global['db'];
   
$q = "select * from org_sector_types";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='country'";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='province'";
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
    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='district'";
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

    $q = "select location.name,location.location_id from location,location_type where location.location_type_id=location_type.location_type_id and location_type.name='village'";
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
echo "<h2><center>" . _("Volunteer Registration") . "</center></h2>";
    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=or&act=reg_vol_cr")
                    );
                    
    shn_show_form($header);
    
    // call OR name
       $perdetails = 	array (
                        				array('desc'=>_("Name in Full : "),'type'=>"text",'size'=>50,'name'=>'perdetails_name','br'=>1),
                       					array('desc'=>_("Age: "),'type'=>"text",'size'=>3,'name'=>'perdetails_age','br'=>1),
                        				array('desc'=>_("Sex :"),'type'=>'dropdown','name'=>'perdetails_sex',
                        								'options'=>array(
                                												array('drop_desc'=>_("Male"),'value'=>'male'),
                                												array('drop_desc'=>_("Female"),'value'=>'female')
                                											  )
                                				),							  
                        				
                        				array('desc'=>_("NID/Passport No: "),'type'=>"text",'size'=>15,'name'=>'perdetails_identity','br'=>1),
                        				array('desc'=>_("Occupation : "),'type'=>"text",'size'=>20,'name'=>'perdetails_occup','br'=>0)
           
                        ); // end of perdetails
                        
                        
      shn_show_form($perdetails);
    // base location
    $location_inf = array(
    					array('legend'=>_("Base Location Information :")),           
                        array('desc'=>_("Country of Residence:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$or_countries
                             ),                         
                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$or_provinces
                        ),// end of option
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$or_districts
                        ),// end of option
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$or_villages
                        )
                    );// end of option
                             
	shn_show_form($location_inf);
	$or_main = array(
                        array('legend'=>'Volunteerism'),
                        array('desc'=>_("select services you can offer : "),'type'=>"multiselect",'size'=>4,'name'=>"or_sector[]",'option'=>$or_sector_type_options,
                        'br'=>'1'
                        ) // end of list form
                     );
    shn_show_form($or_main);
    // OR infomation
    
    $contact01 = array (
    					array('legend'=>_("Contact  Information :")),          
                        array('desc'=>_("Address : "),'type'=>"txtarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1),

                        ); // end of contact 01
    shn_show_form($contact01);
    
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
}                                               
?>
