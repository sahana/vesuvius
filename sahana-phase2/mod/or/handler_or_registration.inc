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
* @author     Pradeeper <pradeeper@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/
// OR registration form generator
// - Pradeeper
// 6th October 2005
global $global;
include_once $global['approot']."/inc/handler_form.inc";

echo "<h2>" . _("Organization Registration") . "</h2>";

    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"somefile.php")
                    );
                    
    shn_show_form($header);

    // call OR name
    $or_name = array(
                        array('desc'=>_("Organization name : "),'type'=>"text",'size'=>20,'name'=>'org_name','br'=>0)
                    );
    shn_show_form($or_name);

    // call OR type
    $or_type = array (
                        array('desc'=>_("Organization Type:"),'type'=>'dropdown','name'=>'org_type',
                            'options'=>array(
                                array('drop_desc'=>_("Donor"),'value'=>'donor'),
                                array('drop_desc'=>_("Beneficiary"),'value'=>'benifi'),
                                array('drop_desc'=>_("Intermediary"),'vale'=>'inter'),
                                array('drop_desc'=>_("Service Provider"),'value'=>'sp')
                                            ) // end of option
                          )
                  );

    shn_show_form($or_type);


    //call OR sector
    $or_sec = array (
                        array('desc'=>_("Sector :"),'drop_desc'=>"Health",'type'=>"checkbox",'name'=>"chkbox1",'value'=>"health"),
                        array('drop_desc'=>_("Foos"),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"food"),
                        array('drop_desc'=>_("Medicine"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"medicine"),
                        array('drop_desc'=>_("Child Care"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"chld_care"),
                        array('drop_desc'=>_("Sanitation"),'type'=>"checkbox",'name'=>"chkbox5",'value'=>"sani"),
                        array('drop_desc'=>_("Finance"),'type'=>"checkbox",'name'=>"chkbox6",'value'=>"finance",'br'=>1),
                    );
    shn_show_form($or_sec);

    
    //Reg information
    echo "<b>"._("Registration Information :")."</b><br>";
    $reg_inf = array (
                        
                        array('desc'=>_("Based Country:"),'type'=>'dropdown','name'=>'bsd_country',
                            'options'=>array(
                                array('drop_desc'=>_("Sri Lanka"),'value'=>'lk'),
                                array('drop_desc'=>_("New Zealand"),'value'=>'nz'),
                                array('drop_desc'=>_("Australia"),'vale'=>'aus'),
                                array('drop_desc'=>_("USA"),'value'=>'us')
                                            ) // end of option
                          ),                          

                        array('desc'=>_("Type :"),'drop_desc'=>"NPO",'type'=>"checkbox",'name'=>"chkbox1",'value'=>"npo"),
                        array('drop_desc'=>_("NGO"),'type'=>"checkbox",'name'=>"chkbox2",'value'=>"ngo"),
                        array('drop_desc'=>_("Multinational"),'type'=>"checkbox",'name'=>"chkbox3",'value'=>"multin"),
                        array('drop_desc'=>_("Bilateral"),'type'=>"checkbox",'name'=>"chkbox4",'value'=>"bilateral",'br'=>1),


                        array('desc'=>_("Registration Number : "),'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1)
                     );
    shn_show_form($reg_inf);


    // OR infomation
    echo "<br>";
    echo "<b>"._("Organization Information :")."</b><br>";
    echo _("First contact person's details : ");
    $contact01 = array (
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>45,'name'=>'contact01_name','br'=>1),
                        array('desc'=>_("Address 1: "),'type'=>"text",'size'=>40,'name'=>'contact01_add1','br'=>1),
                        array('desc'=>_("Address 2: "),'type'=>"text",'size'=>40,'name'=>'contact01_add1','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact01_phone','br'=>0),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact01_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact01_mail','br'=>1),
                        array('desc'=>_("NIC/Passport No : "),'type'=>"text",'size'=>35,'name'=>'contact01_id','br'=>1)

                        ); // end of contact 01
    shn_show_form($contact01);


    echo _("Second contact person's details : ");
    $contact02 = array (
                        array('desc'=>_("Name : "),'type'=>"text",'size'=>45,'name'=>'contact02_name','br'=>1),
                        array('desc'=>_("Address 1: "),'type'=>"text",'size'=>40,'name'=>'contact02_add1','br'=>1),
                        array('desc'=>_("Address 2: "),'type'=>"text",'size'=>40,'name'=>'contact02_add1','br'=>1),
                        array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact02_phone','br'=>0),
                        array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact02_fax','br'=>1),
                        array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact02_mail','br'=>1),
                        array('desc'=>_("NIC/Passport No : "),'type'=>"text",'size'=>35,'name'=>'contact02_id','br'=>1)

                        ); // end of contact 02
    shn_show_form($contact02);

    // get man power of the OR
    $man_power = array (
                        array('desc'=>_("Man Power : "),'type'=>"text",'size'=>4,'name'=>'manpower','br'=>1)
                        );
    shn_show_form($man_power);
    
    
    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>_("Submit"))
                   );

    shn_show_form($tail);
                                                
?>
