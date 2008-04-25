<?php
/**
*
* 
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mifan Careem <mifan@respere.com>
* @copyright  Respere - http://respere.com/
* @package	  Sahana - http://sahana.lk/
* @subpackage msg
* @version 	  $Id: adm_menu.inc,v 1.1 2008-04-25 11:36:44 pradeeper Exp $
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * Admin menu items to sit outside conventional modular admin
 */
function shn_msg_admin_menu()
{
 	global $global;
 	include_once $global['approot']."/mod/msg/adm_menu_actions.inc";
 	
 	shn_sub_mod_menuopen(_("Messaging/Alerting"));
    shn_sub_mod_menuitem("msg_general", _("General Messaging"), 'admin');
    shn_sub_mod_menuitem("msg_sms_plugin", _("Plugin Management"), 'admin');
    shn_sub_mod_menuitem("msg_email", _("Email Configuration"), 'admin');
    shn_sub_mod_menuclose();
}
?>
