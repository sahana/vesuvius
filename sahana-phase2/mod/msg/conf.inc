<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @author		Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	msg
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

$conf['mod_msg_name'] = _("Messaging/Alerting Module");
$conf['mod_msg_menuorder'] = 2;

$conf['input_file']="../mod/msg/kannel.conf";
$conf['output_file']="/tmp/kannel.conf";

/**
 * Internal Configuration for Messaging
 * Not required to be handled via the generic $conf handler in Sahana, 
 * so doesn't adhere to generic $conf namespace
 */
 
 $conf['mod_msg_plugin']='sms';
 
 //Counter for messaging module Media
 $conf['msg_supported_media']=2;
 
 //Medium: SMS
 $conf['msg_name'][0]='Short Messaging';
 $conf['msg_code'][0]='sms';
 
 //Medium: EMail
 $conf['msg_name'][1]='EMail';
 $conf['msg_code'][1]='email';
 
 /**
  * Email configuration
  * Use to configure SMTP server for email sending
  * Requires availability of local/remote SMTP server
  */
 $conf['mod_msg_smtp_host'] = 'localhost';
 $conf['mod_msg_smtp_user'] = '';
 $conf['mod_msg_smtp_pass'] = '';
 $conf['mod_msg_smtp_sender_name'] = '';
 $conf['mod_msg_smtp_sender_email'] = '';
 $conf['mod_msg_smtp_port'] = 25;
 $conf['mod_msg_smtp_mode'] = 'enabled';
 $conf['mod_msg_mail_subject_prefix'] = '[SAHANA-MSG]';

 // SMS receive console refresh rates in miliseconds
 $conf['msg_rc_refresh_rate']= 10000;
?>