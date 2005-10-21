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
    $q = "select * from org_types";
    global $global;
    $db=$global['db'];
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
    

echo "<h2>" . _("Organization Registration") . "</h2>";
    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=or&act=reg_org_cr")
                    );
                    
    shn_show_form($header);
    
    // call OR name
    $or_main = array(
                        array('legend'=>''),
                        array('desc'=>_("Organization name : "),'type'=>"text",'size'=>20,'name'=>'org_name','br'=>0,'class'=>'test','id'=>'tid','br'=>'1'),    
                        array('desc'=>_("Organization Type:"),'type'=>"dropdown",'name'=>'org_type','options'=>$or_type_options
                        ),
                        array('desc'=>_("Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"or_sector[]",'option'=>
                        	array(
                                        array('drop_desc'=>_("Health"),'value'=>'health'),
                                        array('drop_desc'=>_("Finance"),'value'=>'finance','select'=>1),
                                        array('drop_desc'=>_("Medical"),'value'=>'medical'),
                                        array('drop_desc'=>_("Food"),'value'=>'food')
                             ), // end of list
                        'br'=>'1'
                        ), // end of list form
                        array('desc'=>_("Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>
                        	array(
                                	array('drop_desc'=>_("Sri Lanka"),'value'=>'lk'),
                                	array('drop_desc'=>_("New Zealand"),'value'=>'nz'),
                                	array('drop_desc'=>_("Australia"),'vale'=>'aus'),
                                	array('drop_desc'=>_("USA"),'value'=>'us')
                            ) // end of option
                       ),                         
                       array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1)
                     );
    shn_show_form($or_main);

    // base location
    $location_inf = array(
    					array('legend'=>_("Base Location Information :")),           
                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>array(
                                array('drop_desc'=>_("western"),'value'=>'lk'),
                                array('drop_desc'=>_("south"),'value'=>'nz'),
                                array('drop_desc'=>_("Australia"),'vale'=>'aus'),
                                array('drop_desc'=>_("east"),'value'=>'us')
                                            )
                        ),// end of option
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>array(
                                array('drop_desc'=>_("ampara"),'value'=>'lk'),
                                array('drop_desc'=>_("colombo"),'value'=>'nz'),
                               array('drop_desc'=>_("kalutara"),'value'=>'us')
                                            )
                            ),// end of option
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>array(
                                array('drop_desc'=>_("panaduara"),'value'=>'lk'),
                                array('drop_desc'=>_("bamba"),'value'=>'nz'),
                               array('drop_desc'=>_("maharagama"),'value'=>'us')
                                            )
                            )
                    );// end of option
                             
	shn_show_form($location_inf);
    // OR infomation
    
    $contact01 = array (
    					array('legend'=>_("Contact Person Information :")),          
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>45,'name'=>'contact01_name','br'=>1),
                        array('desc'=>_("Address : "),'type'=>"text",'size'=>40,'name'=>'contact01_add1','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact01_phone','br'=>0),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact01_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact01_mail','br'=>1),

                        ); // end of contact 01
    shn_show_form($contact01);
    
    echo "<br>";
    
    // get man power of the OR
    $man_power = array (
                        array('desc'=>_("Man Power : "),'type'=>"text",'size'=>4,'name'=>'manpower','br'=>1)
                        );
    shn_show_form($man_power);
     
    // for comments
    $comments = array(
					array('legend'=>_("Facilities Avaliable : ")),       				
                    array('type'=>"txtarea",'name'=>"some_comments",'rows'=>10,'cols'=>60)
    ); // end of comments

    shn_show_form($comments);

    // for get login info
    $login_info = array(
    				array('legend'=>_("Login information : ")),       	
                    array('desc'=>_("User name : "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_("Password : "),'type'=>"text",'size'=>12,'name'=>'password','br'=>1),
                    array('desc'=>_("Confirm Password: "),'type'=>"text",'size'=>12,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    shn_show_form($login_info); 	

    // make my contact info available
    $my_contact = array(
                    array('desc'=>_("   Make my contact information available  "),'type'=>'checkbox','name'=>'avail','value'=>'avail','algin'=>'right','select'=>1)
                    );
    shn_show_form($my_contact);


    // add location
    $sub_add = array(
                    array('desc'=>_(" Add branch information  "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1)
                    );
    shn_show_form($sub_add);
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
} 

function shn_or_branch_reg(){
echo "<h2>" . _("Organization Registration") . "</h2>";

    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"index.php?mod=or&act=reg_br_cr")
                    );
                    
    shn_show_form($header);
     // call OR name
    $or_name = array(
                        array('desc'=>_("Add a Branch under: "),'type'=>"text",'size'=>20,'name'=>'org_name','br'=>0)
                    );
    shn_show_form($or_name);

    //call OR sector
    $or_sec = array (
                        array('desc'=>_("Sector :"),'drop_desc'=>"Health",'type'=>"checkbox",'name'=>"chkhealth",'value'=>"health"),
                        array('drop_desc'=>_("Food"),'type'=>"checkbox",'name'=>"chkfokhealthd",'value'=>"food"),
                        array('drop_desc'=>_("Medicine"),'type'=>"checkbox",'name'=>"chkmedi",'value'=>"medicine"),
                        array('drop_desc'=>_("Child Care"),'type'=>"checkbox",'name'=>"chkchild",'value'=>"chld_care"),
                        array('drop_desc'=>_("Sanitation"),'type'=>"checkbox",'name'=>"chksani",'value'=>"sani"),
                        array('drop_desc'=>_("Finance"),'type'=>"checkbox",'name'=>"chkfinance",'value'=>"finance",'br'=>1),
                    );
    shn_show_form($or_sec);
    
    // base location
    echo "<br>";
    echo "<b>"._("Location Information :")."</b><br>";
	$country_inf = array (
                        
                        array('desc'=>_("Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country',
                            'options'=>array(
                                array('drop_desc'=>_("Sri Lanka"),'value'=>'lk'),
                                array('drop_desc'=>_("New Zealand"),'value'=>'nz'),
                                array('drop_desc'=>_("Australia"),'vale'=>'aus'),
                                array('drop_desc'=>_("USA"),'value'=>'us')
                                            ) // end of option
                          )
);                         
   shn_show_form($country_inf);
    $province_inf = array(           
                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>array(
                                array('drop_desc'=>_("western"),'value'=>'lk'),
                                array('drop_desc'=>_("south"),'value'=>'nz'),
                                array('drop_desc'=>_("Australia"),'vale'=>'aus'),
                                array('drop_desc'=>_("east"),'value'=>'us')
                                            )
                        )// end of option
                    );
                                                 
	shn_show_form($province_inf);
$district_inf = array(                      
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>array(
                                array('drop_desc'=>_("ampara"),'value'=>'lk'),
                                array('drop_desc'=>_("colombo"),'value'=>'nz'),
                               array('drop_desc'=>_("kalutara"),'value'=>'us')
                                            )
                            )// end of option
                    );
                             
	shn_show_form($district_inf);

$village_inf = array(
                        
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>array(
                                array('drop_desc'=>_("panaduara"),'value'=>'lk'),
                                array('drop_desc'=>_("bamba"),'value'=>'nz'),
                               array('drop_desc'=>_("maharagama"),'value'=>'us')
                                            )
                            )
                    );// end of option
                             
	shn_show_form($village_inf);
    // OR infomation
    echo "<br>";
    echo "<b>"._("Contact Person Information :")."</b><br>";
    
    $contact01 = array (
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>45,'name'=>'contact01_name','br'=>1),
                        array('desc'=>_("Address : "),'type'=>"text",'size'=>40,'name'=>'contact01_add1','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact01_phone','br'=>0),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact01_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact01_mail','br'=>1),

                        ); // end of contact 01
    shn_show_form($contact01);
    
    echo "<br>";
    
    // get man power of the OR
    $man_power = array (
                        array('desc'=>_("Man Power : "),'type'=>"text",'size'=>4,'name'=>'manpower','br'=>1)
                        );
    shn_show_form($man_power);
     
    // for comments
    echo _("Facilities Avaliable : <br>");
    $comments = array(
                    array('type'=>"txtarea",'name'=>"some_comments",'rows'=>10,'cols'=>60)
    ); // end of comments

    shn_show_form($comments);

    


    // add location
    $sub_add = array(
                    array('desc'=>_(" Add More branches  "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1)
                    );
    shn_show_form($sub_add);
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Next"))
                   );

    shn_show_form($tail);
} 

function shn_or_vol_reg(){

// OR volunteer registration form generator
// - Chathra
// 10th October 2005
// 20th october: ravindra

echo "<h2>" . _("Volunteer Registration") . "</h2>";

    // Start Volunteer Registration form
    $header = array (
                        array('method'=>"POST",'action'=>"somefile.php")
                    );
                    
    shn_show_form($header);

    echo "<br>";
    echo "<b>"._("Personal Details :")."</b><br>";
    
       $perdetails = 	array (
                        				array('desc'=>_("Name in Full : "),'type'=>"text",'size'=>45,'name'=>'perdetails_name','br'=>1),
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
      
      echo "<br>";
      echo "<b>"._("Contact Details :")."</b><br>";
      $contactdetails = 	array (
                        				array('desc'=>_("Address 1 : "),'type'=>"text",'size'=>20,'name'=>'contactdetails_add1','br'=>1),
                       					array('desc'=>_("Address 2: "),'type'=>"text",'size'=>20,'name'=>'contactdetails_add2','br'=>1),
                        				array('desc'=>_("Phone No:"),'type'=>"text",'size'=>15,'name'=>'contactdetails_phone','br'=>1),
                        				array('desc'=>_("Email : "),'type'=>"text",'size'=>20,'name'=>'contactdetails_email','br'=>0)
           
                        ); // end of perdetails
                        
                        
      shn_show_form($contactdetails);
    
    
      echo "<br>";
      echo "<b>"._("Locations Preferred :")."</b><br>";
      $locations = 	array (
                        		array('desc'=>_("Country:"),'type'=>'dropdown','name'=>'pre_country',
                            			'options'=>array(
                                								array('drop_desc'=>_("Sri Lanka"),'value'=>'lk'),
                                								array('drop_desc'=>_("New Zealand"),'value'=>'nz'),
                                								array('drop_desc'=>_("Australia"),'vale'=>'aus'),
                                								array('drop_desc'=>_("USA"),'value'=>'us'),
                                								array('drop_desc'=>_("Pakistan"),'value'=>'pak'),
                                								array('drop_desc'=>_("China"),'value'=>'chn'),
                                								
                                            				) // end of option
                         			 ), 
                         			
                         			array('desc'=>_("Locations:"),'type'=>'dropdown','name'=>'pre_location',
                            			'options'=>array(
                                								array('drop_desc'=>_("Colombo"),'value'=>'cmb'),
                                								array('drop_desc'=>_("Auckland"),'value'=>'auc'),
                                								array('drop_desc'=>_("Melbourne"),'vale'=>'mel'),
                                								array('drop_desc'=>_("Pittsburg"),'value'=>'ptt'),
                                								array('drop_desc'=>_("Islamabadh"),'value'=>'isl'),
                                								array('drop_desc'=>_("Beiging"),'value'=>'bei'),
                                								
                                            				) // end of option
                         			 ), 	   
                      	  ); // end of locations
                        
                        
      shn_show_form($locations);
      
      echo "<br>";
      $sectors = array (
      						array('desc'=>_("Volunterism Offered in :"),'drop_desc'=>"Health",'type'=>"checkbox",'name'=>"chkbox1",'value'=>"health"),
                        array('drop_desc'=>_("Food"),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"food"),
                        array('drop_desc'=>_("Medicine"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"medicine"),
                        array('drop_desc'=>_("Child Care"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"chld_care"),
                        array('drop_desc'=>_("Sanitation"),'type'=>"checkbox",'name'=>"chkbox5",'value'=>"sani"),
                        array('drop_desc'=>_("Finance"),'type'=>"checkbox",'name'=>"chkbox6",'value'=>"finance",'br'=>1)
                       ) ;
       shn_show_form($sectors);         
       
       $comments = array (
       							array('desc'=>_("Comments : "),'type'=>"text",'size'=>50,'name'=>'comments_cmt','br'=>1),        
       						  );
      shn_show_form($comments); 		
      
      				  	
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Submit")),
                        array('type'=>"submit",'value'=>_("Reset"))
                   );

    shn_show_form($tail);
}                                               
?>
