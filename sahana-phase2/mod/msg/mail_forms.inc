<?
/**Contains methods to create froms to compose mail,ect
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sri Ganeshan <sri@opensource.lk>
* @author     Ravindra De Silva <ravindra@opensource.lk><ravi@computer.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage msg
*/

function _shn_msg_compose_mail_form($error=false){
global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc"
?>
<h2><?= _('Compose Mail')?></h2>
<?php
    if($error)
    display_errors();
?>
    <div id="formcontainer">
<?
    shn_form_fopen("send_mail&stream=text");
    shn_form_fsopen("individual mails");
    shn_form_textarea(_("Message : "),'message','size="30"',array('req'=>true,'value'=>$val,'help'=>_('Enter Your<br/> message here<br/>')));

shn_form_textarea(_("Phone Number : "),'phone','size="30"',array('req'=>true, 'help'=>_('Enter multiple Phone Numbers here,comma seperatedly')));
    
    shn_form_textarea(_("e-mail : "),'email','size="30"',array('req'=>true, 'help'=>_('Enter multiple mail addresses here,comma seperatedly')));
    
    
    shn_form_fsclose();
    shn_form_fclose();
?>
</div>
<?
}			     
?>


