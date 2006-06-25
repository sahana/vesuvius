<?php
/**
* Sahana Messaging Module
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana
* @subpackage   Messaging
* @tutorial
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";
require_once $global['approot']."/inc/lib_misc.inc";


/**
 * Messaging main menu
 */
function shn_msg_mainmenu()
{
    global $global;
    $module = $global['module'];

    shn_mod_menuopen("Messaging");
    shn_mod_menuitem("default", "Home", $module) ;
    shn_sub_mod_menuopen("XMMP");
//    shn_sub_mod_menuitem("jab_new", "New Message", $module  );
//    shn_sub_mod_menuitem("jab_view", "View Messages", $module);
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen("CAP");
    shn_sub_mod_menuitem("cap_new", _("New Alert"), $module);
    shn_sub_mod_menuitem("cap_view", _("View Alert"), $module);
    shn_sub_mod_menuitem("cap_edit", _("Edit Alert"), $module);
    shn_sub_mod_menuitem("cap_upload", _("Upload CAP File"), $module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose() ;

    include $global['approot']."/inc/handler_mainmenu.inc";
}

/**
 * The Default Messaging homepage
 */
function shn_msg_default()
{
    include_once ('handler_main.inc');
}

function shn_msg_cap_new()
{
    include_once ('handler_cap_new.inc');
}

function shn_msg_cap_view()
{
    include_once ('handler_cap_view.inc');
}

function shn_msg_cap_edit()
{
    include_once ('handler_cap_edit.inc');
}

function shn_msg_cap_upload()
{
    include_once ('handler_cap_upload.inc');
}

function shn_msg_cap_download()
{
    $file = $_GET['filename'];
    header("Content-type: text/xml");
    header("Content-Disposition: attachment; filename=$file");
    $file_str = file_get_contents($file);
    print $file_str;
}

?>