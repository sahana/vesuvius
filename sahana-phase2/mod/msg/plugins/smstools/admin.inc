<?php
/**
* 
* Admin module for SMSTools
* 
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	Mifan Careem <mifan@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: admin.inc,v 1.3 2009-08-22 17:17:27 ravithb Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @plugin		SMSTools - http://smstools.meinemullemaus.de/
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_form.inc');


function shn_plugin_default(){
?>
<h2><?php echo _t("SMSTools Administration")?></h2>	
<?php
	global $global;
    global $conf;
    $module = $global['module'];
 	include_once ($global['approot'].'/mod/msg/plugins/smstools/config_smstools.inc');
    _shn_msg_st_conf_start();
}

