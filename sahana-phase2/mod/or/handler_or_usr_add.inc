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
// Under OR the facility of adding new users
// - Chathra
// 10th October 2005
global $global;
include_once $global['approot']."/inc/handler_form.inc";

echo "<h2>" . _("Add User") . "</h2>";

    // Start Add Branch form
    $header = array (
                        array('method'=>"POST",'action'=>"somefile.php")
                    );
                        
    shn_show_form($header);

    echo "<br>";
    
    $or_usr_details = array(
    							array('desc'=>_("Select an Organization :"),'type'=>'dropdown','name'=>'usr_org',
                            			'options'=>array(
                                								array('drop_desc'=>_("Org1"),'value'=>'org1', 'select'=> 1),
                                								array('drop_desc'=>_("Org2"),'value'=>'org2'),
                                								array('drop_desc'=>_("Org3"),'vale'=>'org3')                               								
                                							                               								
                                            				) // end of option
                         			 ), 
                        array('desc'=>_("New User Log in Name : "),'type'=>"text",'size'=>20,'name'=>'usr_nname','br'=>1),
                        array('desc'=>_("New User Password : "),'type'=>"text",'size'=>20,'name'=>'usr_pswd','br'=>1),
                        array('desc'=>_("New User Role :"),'type'=>'dropdown','name'=>'usr_role',
                            			'options'=>array(
                                								array('drop_desc'=>_("Organization Administrator"),'value'=>'admin', 'select'=> 1),
                                								array('drop_desc'=>_("Data Entry"),'value'=>'ent'),
                                								array('drop_desc'=>_("Date Edit"),'vale'=>'edi'),
                                								array('drop_desc'=>_("Data Cleaning"),'value'=>'cln')
                                							                               								
                                            				) // end of option
                         			 ), 
                         			
                    ); 
    shn_show_form($or_usr_details);
    
    echo "<br>";
    echo "<b>"._("Personal Details :")."</b><br>";
    echo "<br>";

    $or_usr_info = array(
                        array('desc'=>_("User Name : "),'type'=>"text",'size'=>20,'name'=>'usr_name','br'=>1),
                        array('desc'=>_("Email : "),'type'=>"text",'size'=>20,'name'=>'usr_email','br'=>1),
                        array('desc'=>_("Telephone :"),'type'=>'text','name'=>'usr_tel','br'=> 1),
                        array('desc' =>_("Description :"),'type'=> 'text', name=> 'usr_des', br=> 1 )
                            			
                    ); 
    shn_show_form($or_usr_info);


     echo "<br>";
     echo "<b>"._("Access Control Information :")."</b><br>";
     echo "<br>";
     echo "<i>"._("To assign higher level Assign Access Rights to this user click on the Next> button.")."</i><br>";
     
     $nextacl = array (
     							array('type'=> "submit", 'value'=> ("Next >"))
     						);
     shn_show_form($nextacl);						
     							
     $tail = array (
                        array('type'=>"submit",'value'=>_("Submit"))
                   );

    shn_show_form($tail);
                          
     //echo "<ul><b>"._("Domain Victim Registry")."</b></ul>";
     /* $or_usr_acl_dvr = array (
     							array('drop_desc'=> ("Add Data"),'type'=>"checkbox",'name'=>"chkbox1",'value'=>"adddata", 'br'=> 1),
                        array('drop_desc'=>_("Edit Data "),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"editdata", 'br'=> 1),
                        array('drop_desc'=>_("View Statistics Reports Only"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"viewstat", 'br'=> 1),
                        array('drop_desc'=>_("Enable Search Facility"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"ensearch", 'br'=> 1),
                        array('drop_desc'=>_("Access Unclassified Information"),'type'=>"checkbox",'name'=>"chkbox5",'value'=>"unclassiinfo", 'br'=> 1),
                          array('drop_desc'=>_("Access Sensitive Informtion"),'type'=>"checkbox",'name'=>"chkbox6",'value'=>"sensinfo", 'br'=> 1)
                    );*/
                    
     // shn_show_form($or_usr_acl_dvr);
      
     // echo "<ul><b>"._("Organization Registry")."</b></ul>";
      /* $or_usr_acl_or = array (
    							//array('desc'=>_("OR :"),
                        array('drop_desc'=> ("Add Data"),'type'=>"checkbox",'name'=>"chkbox1",'value'=>"adddata", 'br'=> 1),
                        array('drop_desc'=>_("Edit Data "),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"editdata", 'br'=> 1),
                        array('drop_desc'=>_("View Statistics Reports Only"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"viewstat", 'br'=> 1),
                        array('drop_desc'=>_("Enable Search Facility"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"ensearch", 'br'=> 1),
                        array('drop_desc'=>_("Access Unclassified Information"),'type'=>"checkbox",'name'=>"chkbox5",'value'=>"unclassiinfo", 'br'=> 1),
                        array('drop_desc'=>_("Access Sensitive Informtion"),'type'=>"checkbox",'name'=>"chkbox6",'value'=>"sensinfo",'br'=>1) 
      				     );*/
      //shn_show_form($or_usr_acl_or);  	
      
       //echo "<ul><b>"._("Camp Registry")."</ul></b>";
      /* $or_usr_acl_cmp = array (
    							//array('desc'=>_("OR :"),
                        array('drop_desc'=> ("Add Data"),'type'=>"checkbox",'name'=>"chkbox1",'value'=>"adddata", 'br'=> 1),
                        array('drop_desc'=>_("Edit Data "),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"editdata", 'br'=> 1),
                        array('drop_desc'=>_("View Statistics Reports Only"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"viewstat", 'br'=> 1),
                        array('drop_desc'=>_("Enable Search Facility"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"ensearch", 'br'=> 1),
                        array('drop_desc'=>_("Access Unclassified Information"),'type'=>"checkbox",'name'=>"chkbox5",'value'=>"unclassiinfo", 'br'=> 1),
                        array('drop_desc'=>_("Access Sensitive Informtion"),'type'=>"checkbox",'name'=>"chkbox6",'value'=>"sensinfo",'br'=>1) 
      				     );*/
       //shn_show_form($or_usr_acl_cmp);
      
       //echo "<ul><b>"._("Request & Assistance Mgt System")."</ul></b>";
      /* $or_usr_acl_rms = array (
    							//array('desc'=>_("OR :"),
                        array('drop_desc'=> ("Add Data"),'type'=>"checkbox",'name'=>"chkbox1",'value'=>"adddata", 'br'=> 1),
                        array('drop_desc'=>_("Edit Data "),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"editdata", 'br'=> 1),
                        array('drop_desc'=>_("View Statistics Reports Only"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"viewstat", 'br'=> 1),
                        array('drop_desc'=>_("Enable Search Facility"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"ensearch", 'br'=> 1),
                        array('drop_desc'=>_("Access Unclassified Information"),'type'=>"checkbox",'name'=>"chkbox5",'value'=>"unclassiinfo", 'br'=> 1),
                        array('drop_desc'=>_("Access Sensitive Informtion"),'type'=>"checkbox",'name'=>"chkbox6",'value'=>"sensinfo",'br'=>1) 
      				     );*/
      //shn_show_form($or_usr_acl_rms);  	
  
                                                
?>
