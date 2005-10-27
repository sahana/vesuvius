<?php
/* $Id: main.inc,v 1.5 2005-10-27 20:46:48 chamindra Exp $ */

/**Main home page of the Missing Person Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	  Chamindra de Silva <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";

function shn_mpr_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen("Missing Person Registry");

    shn_mod_menuitem("default","Home");
    shn_mod_menuitem("addmp","Report a Missing Person");
    shn_mod_menuitem("fndmp","Report a Found Person");
    shn_mod_menuitem("editmp","Edit a Missing Person");
    shn_mod_menuitem("search","Search for a Person");
    shn_mod_menuitem("stats","Statistics");

    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
	


function shn_mpr_default()
{
    global $global;
}

function shn_mpr_fndmp()
{
    global $global;

    $header=array('method'=>'POST','action'=>'index.php?mod=mpr&act=addmp','id'=>'formset');
    shn_form_open($header,false);

?>  <input type="text" value="hello"/>          <?php

    shn_form_close();
}

function shn_mpr_editmp()
{
    global $global;

    //validation
    if ($_POST['seq']=='submit') {
        if (!shn_valid_phone($_POST['phone'])) add_error("Invalid Phone Number"); 
        display_errors();
    } 

    shn_form_fopen("editmp");
    shn_form_fsopen("Identity");

    shn_form_hidden(array('seq'=>'submit'));

    shn_form_text('Full Name','name','size="60"',array('req'=>true));
    shn_form_text('Mobile Phone','phone','size="30"',array('req'=>true));
    shn_form_opt_select("opt_hair_color","Hair Color");
    shn_form_opt_select("opt_age_group","Age Group");
    shn_form_text('L10N name','l10name','size="60" disabled="disabled"');


    shn_form_fsclose();

    shn_form_fclose();
}

function shn_mpr_addmp()
{

}

function shn_mpr_search()
{
    global $global;
    echo "<h2>Search for a Missing Person</h2>";
}

?>

