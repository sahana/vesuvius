<?php
/*
 * Sahana CAP alert aggregator Module
 * PHP version 5
 * LICENSE: This source file is subject to LGPL license 
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 * @author     Shree Kant Bohra <skbohra123@gmail.com> 
 * @package    Sahana - http://sahana.lk/
 * @module     CAP
 * @copyright  Lanka Software Foundation - http://www.opensource.lk 
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 */
global $global;
include_once $global['approot'].'/mod/msg/lib_msg.inc'; 
print "<h2>"._t("CAP Aggregator")."</h2>";

switch($_REQUEST['filled'])
{
	
	case '':
	shn_form_fopen('cap_msg','');
	shn_form_fsopen();
	shn_form_text(_('To:'),'to','size="10"',array('req'=>'true', 'has_error'=>'true'));
	shn_form_textarea(_('Messge'),'messge',array('req'=>'true', 'has_error'=>'true'),array('value'=>$_REQUEST[title]));
	shn_form_hidden(array('filled'=>'true'));
	shn_form_submit(_('Send'));
	shn_form_fsclose();
	shn_form_fclose();
	break;
	
	case 'true':
	shn_msg_send_short_message($_REQUEST['to'],$_REQUEST['message']);
	break;
}


 

