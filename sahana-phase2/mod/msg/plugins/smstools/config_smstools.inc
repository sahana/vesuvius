<?php
/**
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	Mifan Careem <mifan@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: config_smstools.inc,v 1.1 2008-04-25 11:51:22 priyanga Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @plugin		SMSTools - http://smstools.meinemullemaus.de/
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_msg_st_conf_start($errors=false){
	if($errors)
		display_errors();
		
	global $global;
	global $conf;
	$db = $global['db'];
?>
<?php
	
	shn_form_fopen(astconf);

	shn_form_fsopen(_("Configuration File"));
	shn_form_text(_("SMSD configuration file path"),"sms_conf",'size="60"'
		,array('help'=>'Main SMSTools configuration file. Defaults to /etc/smsd.conf. Should be in a location writeable by the web server','req'=>true));
	shn_form_fsclose();
	
	shn_form_fsopen(_("Path to Log Files"));
	shn_form_text(_("Incoming Messages Folder"),"sms_incoming",'size="60"'
		,array('help'=>'Main SMSTools configuration file. Defaults to /etc/smsd.conf. Should be in a location writeable by the web server','req'=>true));
	shn_form_text(_("Outgoing Messages Folder"),"sms_outgoing",'size="60"'
		,array('help'=>'Main SMSTools configuration file. Defaults to /etc/smsd.conf. Should be in a location writeable by the web server','req'=>true));
	shn_form_text(_("Failed Messages Folder"),"sms_failed",'size="60"'
		,array('help'=>'Main SMSTools configuration file. Defaults to /etc/smsd.conf. Should be in a location writeable by the web server','req'=>true));
	shn_form_text(_("Sent Messages Folder"),"sms_sent",'size="60"'
		,array('help'=>'Main SMSTools configuration file. Defaults to /etc/smsd.conf. Should be in a location writeable by the web server','req'=>true));
	shn_form_fsclose();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

?>
