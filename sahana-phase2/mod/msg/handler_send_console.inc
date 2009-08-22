<?php
/**
* The Sahana Messaging Module Send Console
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	J P Fonseka <jo@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: handler_send_console.inc,v 1.3 2009-08-22 17:17:22 ravithb Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once ('lib_receive_console.inc');

echo "<h2>"._t('Send Console')."</h2>";

//send console form
shn_form_fopen('send_message',null,array('req'=>false));
shn_form_fsopen(_t('Send Message'));

//display the contact drop down
_shn_msg_contact_dropdown('to');
?>
<br />
<?php

shn_form_textarea('To','to');


//fetch the stored message list
$sql="select m_uuid , message_header from msg_stored_messages;";
$res=$global['db']->Execute($sql);
$stmsg['']="";
foreach($res as $message)
    $stmsg[$message[0]]=$message[1];

shn_form_select($stmsg,'Stored Messages','stmsg','onchange="msg_set_message(this)"');

$sql="select m_uuid , message_header from msg_tpl_messages;";
$res=$global['db']->Execute($sql);
$temsg['']="";
foreach($res as $message)
    $temsg[$message[0]]=$message[1];

shn_form_select($temsg,'Template Messages','temsg','onchange="msg_set_message(this)"');

_shn_msg_message_ui();
$global['xajax']->printJavascript("res/js"); 
shn_form_fsclose();
shn_form_submit('Send Message');
shn_form_fclose();
