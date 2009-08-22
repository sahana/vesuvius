<?php
/**
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Respere - http://respere.com/
* @version      $Id: config_smstools.inc,v 1.4 2009-08-22 17:17:27 ravithb Exp $
* @package      Sahana - http://sahana.lk/
* @subpackage   messaging   
* @plugin       SMSTools - http://smstools.meinemullemaus.de/
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
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

    shn_form_fsopen(_t("Configuration File"));
    $sms_conf_help = _t("Main SMSTools configuration file. Defaults to /etc/smsd.conf. Should be in a location writable by the web server");
    shn_form_text(_t("SMSD configuration file path"),"sms_conf",'size="60"',array('help'=>$sms_conf_help,'req'=>true));
    shn_form_fsclose();

    shn_form_fsopen(_t("Path to Log Files"));
    shn_form_text(_t("Incoming Messages Folder"),"sms_incoming",'size="60"',array('req'=>true));
    shn_form_text(_t("Outgoing Messages Folder"),"sms_outgoing",'size="60"',array('req'=>true));
    shn_form_text(_t("Failed Messages Folder"),"sms_failed",'size="60"',array('req'=>true));
    shn_form_text(_t("Sent Messages Folder"),"sms_sent",'size="60"',array('req'=>true));
    shn_form_fsclose();
    shn_form_submit(_t("Next"));
    shn_form_fclose();
}


