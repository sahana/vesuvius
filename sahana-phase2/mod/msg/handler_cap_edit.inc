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
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

require_once('class_cap_alert.inc');
require_once('class_cap_info.inc');
require_once('class_cap_resource.inc');
require_once('class_cap_area.inc');
require_once('lib_cap_js.inc');

switch ($_REQUEST['seq'])
{
    case '' :
        _shn_msg_cap_editmain();
        break;

    case 'edit_tpl':
                _shn_msg_cap_edit_tpl();
                break;
    case 'save_cap_main':
                _shn_msg_cap_save_tpl();
                break;
}

function _shn_msg_cap_editmain()
{
    print "<h1>" . _("Sahana Messaging Module") . "</h1>";
    print "<h3>" . _("CAP Template Editor") . "</h3>";
    _shn_msg_cap_file_selector();
}

function _shn_msg_cap_file_selector()
{
    shn_form_fopen("cap_edit",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'edit_tpl'));
    shn_form_fsopen(_("Select Template"));
    shn_form_select(_shn_msg_get_cap_tpllist(),"","file",'onChange=submit(this);',array('br'=>false));
    shn_form_submit(_("Edit"));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_msg_get_cap_tpllist()
{
    $MSG_DIR = '../res/msg';
    $templates = scandir($MSG_DIR.'/cap/templates');
    
    foreach ($templates as $template)
    {
        if(strstr($template,'.xml') || strstr($template,'.XML'))
            $list_tpl[$template]=$template;
    }

    return $list_tpl;
}

function _shn_msg_cap_edit_tpl()
{
    $file = $_POST['file'];
    $MSG_DIR = '../res/msg';
    $tpl_file = $MSG_DIR.'/cap/templates/' . $file;
    $tpl = new Msg_CapAlert($tpl_file);
    
    _shn_msg_cap_edit_capmain($tpl, $tpl_file);
}

function _shn_msg_cap_edit_capmain($alert, $file_name)
{
    require_once('lib_cap_help.inc');
    
    $id = $alert->getIdentifier();
    $date = $alert->getSent();
    $sender = $alert->getSender();
    $status_sel= $alert->getStatus();
    $messageType_sel = $alert->getMsgType();
    $note= $alert->getNote();
    $source = $alert->getSource();
    $scope = $alert->getScope();
    $restriction = $alert->getRestriction();
    $address = $alert->getAddress();
    $code = $alert->getCode();
    $references = $alert->getReferences();
    $incidents = $alert->getIncidents(); 
    
    $status = array('Actual'=>'Actual', 'Exercise'=>'Exercise', 
                     'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');
    $msgType = array('Alert'=>'Alert', 'Update'=>'Update', 
                      'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
    $scope = array('Public'=>'Public', 'Restricted'=>'Restricted', 
                   'Private'=>'Private');
    
    print "<h2>" . _("Edit Cap Template Information") . "</h2>";
    
    shn_form_fopen("cap_edit",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'save_cap_main', 'file_name'=>$file_name));
    shn_form_fsopen(_("Edit Cap Message"));
    shn_form_text(_("Message Identifier"),'identifier',null,array('value'=>$id,'help'=>$help_identifire));
    shn_form_text(_("Date"),'sent',null,array('value'=>$date));
    shn_form_text(_("Sender"),'sender','class=""',array('value'=>$sender,'help'=>$help_sender));
    shn_form_select($status, _("Status"), 'status', null, array('value'=>$status_sel,'help'=>$help_status));
    shn_form_select($msgType, _("Message Type"), 'msgType', 'onChange="showHideNote(this);"',array('value'=>$messageType_sel,'help'=>$help_msgType));
    print '<div id="cap_note">';
    shn_form_textarea(_("Note"),'note',null,array('value'=>$note));
    print '</div>';
    shn_form_text(_("Source"),'source',null, array('value'=>$source,help=>$help_source));
    
    shn_form_select($scope, _("Scope"), 'scope','onChange="changeScope(this);"',array('value'=>$scope,'help'=>$help_scope));
    print '<div id="scope_rest">';
    shn_form_text(_("Restriction [Restricted]"),'restriction',null,array('value'=>$restriction));
    print '</div><div id="scope_addr">';
    shn_form_textarea(_("Addresses [private]"),'addresses',null,array('value'=>$address));
    print '</div>';

    shn_form_fsopen(_("Optional"));    
    shn_form_text(_("Code"),'code',null,array('value'=>$code,'br'=>false));
    print "<strong>Enter space separated set of codes</strong> <br />";

    
    shn_form_text(_("References"),'references',null,array('value'=>$references));
    shn_form_text(_("incidents"),'incidents',null,array('value'=>$incidents));
    shn_form_fsclose();
    
    shn_form_fsopen(_("Save as"));
    shn_form_checkbox(_("Message"), 'type', 'checked="true"', array('value'=>'msg'));
    shn_form_checkbox(_("Template"), 'type', null, array('value'=>'tpl'));
    shn_form_submit(_("Save"), 'style="float: right"');
    shn_form_fsclose();
    
    shn_form_fsclose(); //Close capmessage form
    shn_form_fclose();
    
    _shn_msg_add_capjs();
}

function _shn_msg_cap_save_tpl()
{
    $tpl_file = $_POST['file_name'];
    $alert = new Msg_CapAlert($tpl_file);
    
    $alert->setIdentifier($_POST['identifier']);
    $alert->setSender($_POST['sender']);
    $alert->setSent($_POST['sent']);
    $alert->setStatus($_POST['status']);
    $alert->setMsgType($_POST['msgType']);
    $alert->setSource($_POST['source']);
    $alert->setScope($_POST['scope']);
    $alert->setRestriction($_POST['restriction']);
    $alert->setAddress($_POST['address']);
    
    $codes = split(' ', $_POST['code']);
    foreach($codes as $code)
    {
        if(trim($code) != '')
            $alert->addCode($code);
    }
    
    $alert->setNote($_POST['note']);
    $alert->setReferences($_POST['references']);
    $alert->setIncidents($_POST['incidents']);
    
    $alert->printFormattedMsg();
    
    /**
     * Saving the CAP Alert
     */
    $type = $_POST['type'];
    $MSG_DIR = '../res/msg';
    $tpl_path = "$MSG_DIR/" . "cap/templates/";
    $msg_path = "$MSG_DIR/" . "cap/messages/";
    switch ($type)
    {
        case 'tpl':
                $fileName = $alert->getIdentifier() . '.xml';
                $alert->saveXML($tpl_path, $fileName);
                print "<h3>" . _("CAP saved as a Template") . "</h3>";
                print _("File Name") . 
                      "<strong>" . $tpl_path.$fileName . "</strong><br />";
        case 'msg':
                $fileName = $alert->getIdentifier() . '.xml';
                $alert->saveXML($msg_path, $fileName);
                print "<h3>" . _("CAP saved as a Message") . "</h3>";
                print _("File Name") . 
                      ":<strong>" . $msg_path.$fileName . "</strong>";
                break;
        
         
    }
}
?>
