<?php
/**Admin Module for GIS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @author   Sri Ganeshan <sri@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    admin
* @subpackage msg
* @version $id$
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
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
	<li><?php echo _("This section is to administer your Email server so that the messaging module can send emails");?> </li>
	<li><?php echo _("Enter the correct SMTP server details below to start using the email system");?></li>
    
	</ul>
<?php
	shn_form_fsclose();
	shn_form_fsopen(_("EMAIL SMTP SERVER SETTINGS"));
    shn_form_text(_("SMTP Host Name"),'host',null,array('req'=>true,'value'=>$conf['mod_msg_smtp_host']));
    shn_form_text(_("SMTP Host Port"),'port','size=4',array('req'=>true,'value'=>$conf['mod_msg_smtp_port']));
    shn_form_text(_("SMTP Username"),'username',null,array('value'=>$conf['mod_msg_smtp_user']));
    shn_form_password(_("SMTP Password"),'password');
    shn_form_text(_("Sender name"),'name',null,array('value'=>$conf['mod_msg_smtp_sender_name']));
    shn_form_text(_("Sender mail ID"),'mail_id',null,array('value'=>$conf['mod_msg_smtp_sender_email'],'help'=>_('Most mail servers require the sender to have' .
    		' an Email ID/Address. Most Email servers flag/reject mails without a valid sender, so it is advisable to have an email address here')));
    shn_form_fsclose();
    shn_form_submit(_('Save'));
    shn_form_fclose();
}
?>
