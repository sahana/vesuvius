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
* @version 	  $Id: adm_menu_actions.inc,v 1.3 2009-08-22 17:17:22 ravithb Exp $
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * Front controller function to handle plugin architecture
 */
function shn_admin_msg_sms_plugin()
{
	global $global;
	include_once $global['approot']."/mod/msg/admin_fns.inc";
	global $conf;
	//echo "PLUGIN:".$conf['mod_msg_plugin'];
	shn_msg_adm_default();
}


function shn_admin_msg_plugin_commit()
{
	global $global;
	include_once $global['approot']."/mod/msg/admin_fns.inc";
	_shn_msg_adm_store_plugin($_REQUEST['mod_msg']);
}

function shn_admin_msg_email()
{
	global $global;
	global $conf;
	//include_once $global['approot']."/mod/msg/admin_fns.inc";
	echo "<h2>"._lc($conf['mod_msg_name'])." "._("Email Server Administration")."</h2>";
	//_shn_msg_adm_email_conf();
	include_once ($global['approot'].'/mod/msg/handler_admin.inc');
	shn_msg_adm_email_configuration();	
}

function shn_admin_msg_email_commit()
{
	global $global;
	global $conf;
	include_once $global['approot']."/mod/msg/admin_fns.inc";
	_shn_msg_adm_email_conf();
;	
}



function shn_admin_msg_general()
{
	global $global;
	include_once $global['approot']."/mod/msg/admin_fns.inc";
}
