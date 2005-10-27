<?php
/* $Id: main.inc,v 1.4 2005-10-27 12:09:33 chamindra Exp $ */

/**Main home page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Mifan Careem <mifan@opensource.lk>
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @author	  Saumya Gunawardana <saumya@opensource.lk>
* @author	  Chamindra de Silva <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";

function shn_mpr_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen("Missing Person Registry");

    shn_mod_menuitem("default","Home");
    shn_mod_menuitem("addmp","Report a Missing Person");
    shn_mod_menuitem("fndmp","Report a Found Person");
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
    //include the mpr add function library
    include ($global['approot'].'/mod/mpr/add.inc');

    //Include the presentation layer
    //@todo : (may be not for this) check the presentation layer
    require_once ($global['approot'].'/inc/handler_form.inc');
    _shn_mpr_add_new();

}

function shn_mpr_addmp()
{
    global $global;
    //include the mpr add function library
    include ($global['approot'].'/mod/mpr/add.inc');

    //Include the presentation layer
    //@todo : (may be not for this) check the presentation layer
    require_once ($global['approot'].'/inc/handler_form.inc');

    //check the add_sequence
    switch ($_REQUEST['add_sequence']){
    case 'commit':
        _shn_mpr_add_commit();
        break;
    default :
        _shn_mpr_add_default();
        break;
    }


}

function shn_mpr_search()
{
    global $global;
    echo "<h2>Search for a Missing Person</h2>";
}

?>

