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

echo "<h4>Organization Registration</h4>";

    // Start OR registration form
    $header = array (
                        array('method'=>"POST",'action'=>"somefile.php")
                    );
                    
    shn_show_form($header);

    // call OR name
    $or_name = array(
                        array('desc'=>"Organization name : ",'type'=>"text",'size'=>20,'name'=>'org_name','br'=>0)
                    );
    shn_show_form($or_name);

    // call OR type
    $or_type = array (
                        array('desc'=>"Organization Type:",'type'=>'dropdown','name'=>'org_type',
                            'options'=>array(
                                array('drop_desc'=>"Donor",'value'=>'donor'),
                                array('drop_desc'=>"Beneficiary",'value'=>'benifi'),
                                array('drop_desc'=>"Intermediary",'vale'=>'inter'),
                                array('drop_desc'=>"Service Provider",'value'=>'sp')
                                            ) // end of option
                          )
                  );

    shn_show_form($or_type);


    //call OR sector
    $or_sec = array (
                        array('desc'=>"Sector :",'drop_desc'=>"Health",'type'=>"checkbox",'name'=>"chkbox1",'value'=>"health"),
                        array('drop_desc'=>"Foos",'type'=>"checkbox",'name'=>"chkbox2",'value'=>"food"),
                        array('drop_desc'=>"Medicine",'type'=>"checkbox",'name'=>"chkbox3",'value'=>"medicine"),
                        array('drop_desc'=>"Child Care",'type'=>"checkbox",'name'=>"chkbox4",'value'=>"chld_care"),
                        array('drop_desc'=>"Sanitation",'type'=>"checkbox",'name'=>"chkbox5",'value'=>"sani"),
                        array('drop_desc'=>"Finance",'type'=>"checkbox",'name'=>"chkbox6",'value'=>"finance",'br'=>1),
                    );
    shn_show_form($or_sec);

    
    //Reg information
    echo "Registration Information :<br>";
    $reg_inf = array (
                        
                        array('desc'=>"Based Country:",'type'=>'dropdown','name'=>'bsd_country',
                            'options'=>array(
                                array('drop_desc'=>"Sri Lanka",'value'=>'lk'),
                                array('drop_desc'=>"New Zealand",'value'=>'nz'),
                                array('drop_desc'=>"Australia",'vale'=>'aus'),
                                array('drop_desc'=>"USA",'value'=>'us')
                                            ) // end of option
                          ),                          

                        array('desc'=>"Type :",'drop_desc'=>"NPO",'type'=>"checkbox",'name'=>"chkbox1",'value'=>"npo"),
                        array('drop_desc'=>"NGO",'type'=>"checkbox",'name'=>"chkbox2",'value'=>"ngo"),
                        array('drop_desc'=>"Multinational",'type'=>"checkbox",'name'=>"chkbox3",'value'=>"multin"),
                        array('drop_desc'=>"Bilateral",'type'=>"checkbox",'name'=>"chkbox4",'value'=>"bilateral",'br'=>1),


                        array('desc'=>"Registration Number : ",'type'=>"text",'size'=>20,'name'=>'reg_no','br'=>1)
                     );
    shn_show_form($reg_inf);


    // end of form
    $tail = array (
                        array('type'=>"submit",'value'=>"Enter")
                   );

    shn_show_form($tail);
                                                
?>
