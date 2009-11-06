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


print "<h1>" . _t("Sahana Messaging Module") . "</h1>";
print "<h3>" . _t("CAP Message Viewer") . "</h3>";

switch ($_REQUEST['seq'])
{
    case '' :
        //_shn_msg_cap_url_selector();
        _shn_msg_cap_file_selector();
        break;

    case 'view_msg':
               //_shn_msg_cap_url_selector();
               _shn_msg_cap_file_selector();
               _shn_msg_view_cap_message();
                   break;
    case 'view_tpl':
                _shn_msg_cap_file_selector();
                _shn_msg_view_cap_template();
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

function _shn_msg_get_cap_msglist()
{
    $MSG_DIR = '../res/msg';
    $messages = scandir($MSG_DIR.'/cap/messages');
    
    foreach ($messages as $message)
    {
        if(strstr($message,'.xml') || strstr($message,'.XML'))
            $list_msg[$message]=$message;
    }

    return $list_msg;
}

function _shn_msg_cap_file_selector()
{
    print '<table class="layout">';
    print '<tr>';
    print '<td>';
    shn_form_fopen("cap_view",null,array('req_message'=>false,'style'=>'form_blank'));
    shn_form_hidden(array('seq'=>'view_tpl'));
    shn_form_fsopen(_t("Select Template"));
    shn_form_select(_shn_msg_get_cap_tpllist(),"","file",'onChange=submit(this);',array('br'=>false));
    shn_form_submit(_t("View"));
    shn_form_fsclose();
    shn_form_fclose();
    print '</td>';
    print '<td>';
    shn_form_fopen("cap_view",null,array('req_message'=>false,'style'=>'form_blank'));
    shn_form_hidden(array('seq'=>'view_msg'));
    shn_form_fsopen(_t("Select Message"));
    shn_form_select(_shn_msg_get_cap_msglist(),"","file",'onChange=submit(this);',array('br'=>false));
    shn_form_submit(_t("View"));
    shn_form_fsclose();
    shn_form_fclose();
    print '</td>';
    print '</tr>';
    print '</table>';
}

function _shn_msg_cap_url_selector()
{

    shn_form_fopen("cap_view",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'view_msg'));


    shn_form_text(_t("Enter a URL <br/>(http://example.org/cap.xml)"),'file',null,array('br'=>false));

    shn_form_submit(_t("View"));
    shn_form_fclose();
}

function _shn_msg_view_cap_message()
{
    $file = $_POST['file'];
    $MSG_DIR = '../res/msg';
    $msg = new Msg_CapAlert($MSG_DIR.'/cap/messages/' . $file);
    
    print "<form method='POST' action='index.php?stream=text&amp;mod=msg&amp;act=cap_download' id='formset' name=''>";
    print "Download : $file_name";
    shn_form_hidden(array('seq'=>'','file'=>$file,'type'=>'messages'));
    shn_form_submit(_t("Dowload"));
    print "</form>";
    
    print $msg->printFormattedMsg();
}

function _shn_msg_view_cap_template()
{
    $file = $_POST['file'];
    $MSG_DIR = '../res/msg';
    $msg = new Msg_CapAlert($MSG_DIR.'/cap/templates/' . $file);

    print "<form method='POST' action='index.php?stream=text&amp;mod=msg&amp;act=cap_download' id='formset' name=''>";
    shn_form_hidden(array('seq'=>'','file'=> $file ,'type'=>'templates'));
    print "Download : ";
    shn_form_submit(_t("Dowload"));
    print "</form>";
    
    print $msg->printFormattedMsg();
}

?>


