<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

    global $global;
    
    include_once $global['approot']."/inc/lib_modules.inc";
    include_once $global['approot']."/inc/lib_menu.inc";
    include_once $global['approot']."/inc/lib_form.inc";
    include_once $global['approot']."/inc/lib_validate.inc";

?>   

<?php
    shn_form_fopen("new_req",null);
    shn_form_fsopen('New Request');
    shn_form_text('Tel','_n_date','size="30"');
    shn_form_text('Requester Name','name.r','size="30"');
    shn_form_text('Requester Email','email.e.r','size="30"');
    shn_form_text('Email','email','size="30"');
    shn_form_fsclose();
    shn_form_button('Submit','onClick="validate_form(this)"');
    shn_form_fclose();
?>

