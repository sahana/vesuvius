<?php
/**
* Sahana Messaging Module
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana
* @subpackage
* @tutorial
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


require_once('class_cap_alert.inc');
require_once('class_cap_info.inc');
require_once('class_cap_resource.inc');
require_once('class_cap_area.inc');
require_once('lib_cap_js.inc');

?>

<h1>Sahana Messaging Module</h1>
<h3>CAP Message Viewer</h3>

<?php

function _shn_msg_get_cap_filelist()
{
    $list = array();
    $files = scandir('../res/msg');
    foreach ($files as $file)
    {
        if(strstr($file,'.xml') || strstr($file,'.XML'))
            $list[$file]=$file;
    }

    return $list;
}

function _shn_msg_cap_file_selector()
{

    shn_form_fopen("cap_view",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'view_msg'));

    //shn_form_fsopen(_("Select Message"));
    shn_form_select(_shn_msg_get_cap_filelist(),"","file",'onChange=submit(this);',array('br'=>false));
    shn_form_submit(_("View"));
    //shn_form_fsclose();
    
    shn_form_fclose();
}

function _shn_msg_cap_url_selector()
{

    shn_form_fopen("cap_view",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'view_msg'));


    shn_form_text(_("Enter a URL <br/>(http://example.org/cap.xml)"),'file',null,array('br'=>false));

    shn_form_submit(_("View"));
    shn_form_fclose();
}

function _shn_msg_view_cap_message()
{
    $file = $_POST['file'];
    $msg = new Msg_CapAlert('../res/msg/' . $file);
    print $msg->printFormattedMsg();
    
//    shn_form_fopen("cap_xml_view",null,array('req_message'=>false));
//    shn_form_textarea('','name','rows=20 cols=150',array('value'=>$msg->getXML()));
//    shn_form_fclose();

}

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
}
?>


