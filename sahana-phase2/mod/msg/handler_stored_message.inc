<?php
/**
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the wcrld-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* 
* Handler for stored messages
*
* @author     	Mifan Careem <mifan@respere.com>
* @copyright  	Respere - http://respere.com/
* @package		Sahana - http://sahana.lk/
* @subpackage	msg
* @version	  	$Id: handler_stored_message.inc,v 1.2 2008-04-30 05:58:01 mifanc Exp $ 	  
* @license	  	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

/**
 * Form to input stored message and message media
 * @todo move message media to multi-select
 * @todo provide usage information
 */
function shn_msg_create_stored_message_form($errors=false)
{
	if($errors)
		display_errors();
		
	global $global;
	global $conf;
?>
<h2><?php echo _t("Create New Stored Message")?></h2>
<?php
	
	$supported_media = array();
	for($i=0;$i<$conf['msg_supported_media'];$i++){
		$supported_media[$conf['msg_code'][$i]] = $conf['msg_name'][$i];
	}
	
	shn_form_fopen(create_store);
	shn_form_fsopen(_t('Information'));
?>
<div id="info">
  <ul>
    <li>Create and store pre-defined messages in the system<br/>
    </li>
    <li>These messages can be used in the messaging system to quickly send pre-defined messages<br/>
    </li>
  </ul>
 </div>
  
<?php
	shn_form_fsclose();

	shn_form_fsopen(_t("Stored Message"));
	shn_form_text(_t("Message Heading/Summary"),"msg_head",'size="70"',
		array('req'=>true,'help'=>_t('Enter a summary/header for the message. This section wouldn\'t be displayed in the actual sent message, and is only used to identify the message')));
	shn_form_textarea(_t("Message"),"message",null,array('cols'=>70,'rows'=>8));
	shn_form_multi_select('media_type',$supported_media,_t("Medium/Media Selection"),'size="6" width="20" multiple="true"',
		array('help'=>_t('Select the message medium that the message should be sent over. Hold down the Ctrl key for selecting more than one medium')));
	shn_form_fsclose();
	
	shn_form_submit(_t("Save Message"));
	shn_form_fclose();
}

?>

