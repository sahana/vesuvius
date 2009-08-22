<?php
/**Admin Module for GIS
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* 
* @author   	Mifan Careem <mifan@opensource.lk>
* @author   	Sri Ganeshan <sri@opensource.lk>
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @package    	Sahana - http://sahana.sourceforge.net
* @subpackage 	msg
* @version 		$Id: handler_admin.inc,v 1.3 2009-08-22 17:17:22 ravithb Exp $
* @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Configuration form for SMTP 
 */
function shn_msg_adm_email_configuration()
{
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_form.inc');
	include_once($global['approot'].'/inc/lib_validate.inc');
	include_once($global['approot'].'/inc/lib_errors.inc');
	
	shn_form_fopen("msg_email_commit");
	shn_form_fsopen("Sending Emails Administration");
?>
	<ul>
	<li><?php echo _t("This section is to administer your Email server so that the messaging module can send emails");?> </li>
	<li><?php echo _t("Enter the correct SMTP server details below to start using the email system");?></li>
    
	</ul>
<?php
	shn_form_fsclose();
	shn_form_fsopen(_t("EMAIL SMTP SERVER SETTINGS"));
    shn_form_text(_t("SMTP Host Name"),'host',null,array('req'=>true,'value'=>$conf['mod_msg_smtp_host']));
    shn_form_text(_t("SMTP Host Port"),'port','size=4',array('req'=>true,'value'=>$conf['mod_msg_smtp_port']));
    shn_form_text(_t("SMTP Username"),'username',null,array('value'=>$conf['mod_msg_smtp_user']));
    shn_form_password(_t("SMTP Password"),'password');
    shn_form_text(_t("Sender name"),'name',null,array('value'=>$conf['mod_msg_smtp_sender_name']));
    shn_form_text(_t("Sender mail ID"),'mail_id',null,array('value'=>$conf['mod_msg_smtp_sender_email'],'help'=>_t('Most mail servers require the sender to have' .
    		' an Email ID/Address. Most Email servers flag/reject mails without a valid sender, so it is advisable to have an email address here')));
    shn_form_fsclose();
    shn_form_submit(_t('Save'));
    shn_form_fclose();
}

