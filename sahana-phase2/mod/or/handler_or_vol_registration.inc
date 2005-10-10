<?php
/*
*
* Sahana HTML form handler
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/
// OR volunteer registration form generator
// - Chathra
// 10th October 2005
global $global;
include_once $global['approot']."/inc/handler_form.inc";

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
                                                
?>
