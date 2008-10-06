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

global $global;
require_once $global['approot']."/inc/lib_locale/lib_locale.inc";
require_once('class_cap_alert.inc');
require_once('class_cap_info.inc');
require_once('class_cap_resource.inc');
require_once('class_cap_area.inc');
require_once('lib_cap_js.inc');

switch ($_REQUEST['seq'])
{
    case '' :
            $_SESSION['cap_msg'] = null;
            _shn_msg_cap_newmain();
            break;
    case 'new_cap_main':
                    _shn_msg_cap_addmain();
                    _shn_msg_cap_infonew();
                    break;
    case 'new_cap_info':
                    _shn_msg_cap_addinfo();
                    _shn_msg_cap_resourcenew();
                    break;
    case 'new_cap_res':
                    _shn_msg_cap_add_res();
                    _shn_msg_cap_resourcenew();
                    break;
    case 'del_cap_res':
                    _shn_msg_cap_del_res();
                    _shn_msg_cap_resourcenew();
                    break;
    case 'new_cap_area':
                    _shn_msg_cap_new_area();
                    break;
    case 'add_cap_area':
                    _shn_msg_cap_add_area();
                    _shn_msg_cap_new_area();
                    break;
    case 'del_cap_area':
                    _shn_msg_cap_del_area();
                    _shn_msg_cap_new_area();
                    break;
    case 'new_cap_finish':
                    _shn_msg_cap_finish();
                    break;
    case 'new_cap_save':
                    _shn_msg_cap_save();
                    break;
}

function _shn_msg_cap_newmain()
{
    require_once('lib_cap_help.inc');
    
    $id = time();
    $today = date("Y-m-d h:m:s");
    
    $status = array('Actual'=>'Actual', 'Exercise'=>'Exercise', 
                     'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');
    $msgType = array('Alert'=>'Alert', 'Update'=>'Update', 
                      'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
    $scope = array('Public'=>'Public', 'Restricted'=>'Restricted', 
                   'Private'=>'Private');
    
    print "<h2>" . _t("Creating New Cap Template") . "</h2>";
    
    shn_form_fopen("cap_new",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_hidden(array('seq'=>'new_cap_main'));
    shn_form_fsopen(_t("New Cap Template"));
    shn_form_hidden(array('time'=>$id,'stat'=>$status[_t("Actual")]));
    shn_form_text(_t("Message Identifier"),'identifier',null,array('value'=>$status[_t("Actual")] . "-$id",'help'=>$help_identifire));
    shn_form_text(_t("Date"),'sent',null,array('value'=>$today));
    shn_form_text(_t("Sender"),'sender','class=""',array('help'=>$help_sender));
    shn_form_select($status, _t("Status"), 'status', 'onChange="changeId(this);"', array('help'=>$help_status));
    shn_form_select($msgType, _t("Message Type"), 'msgType', 'onChange="showHideNote(this);"',array('help'=>$help_msgType));
    print '<div id="cap_note">';
    shn_form_textarea(_t("Note"),'note');
    print '</div>';
    shn_form_text(_t("Source"),'source',null, array('value'=>'Sahana',help=>$help_source));
    
    shn_form_select($scope, _t("Scope"), 'scope','onChange="changeScope(this);"',array('help'=>$help_scope));
    print '<div id="scope_rest">';
    shn_form_text(_t("Restriction [Restricted]"),'restriction');
    print '</div><div id="scope_addr">';
    shn_form_textarea(_t("Addresses [private]"),'addresses');
    print '</div>';

    shn_form_fsopen(_t("Optional"));    
    shn_form_text(_t("Code"),'code',null,array('br'=>false));
    print "<strong>Enter space separated set of codes</strong> <br />";

    
    shn_form_text(_t("References"),'references');
    shn_form_text(_t("incidents"),'incidents');
    shn_form_fsclose();
    
    shn_form_submit(_t("Next"), 'style="float: right"');
    
    shn_form_fsclose(); //Close capmessage form
    
    
    shn_form_fclose();
    
    _shn_msg_add_capjs();
}

function _shn_msg_cap_infonew()
{
    require_once('lib_cap_help.inc');
    
    $category = array('Geo'=>'Geo', 'Met'=>'Met', 'Safety'=>'Safety', 
                      'Security'=>'Security', 'Rescue'=>'Rescue', 
                      'Fire'=>'Fire', 'Health'=>'Health', 'Env'=>'Env', 
                      'Transport'=>'Transport', 'Infra'=>'Infra', 
                      'CBRNE'=>'CBRNE', 'Other'=>'Other');
    
    $session_lang = $_SESSION["locale"];
    switch ($session_lang)
    {
        case 'de_DE':
                $c_land = 'si_LK';
                break;
        default:
                $c_land = $session_lang;
    }
    
    $language = array('si_LK'=>_t("Sinhala"),'tm_LK'=>_t("Tamil"),'en_US'=>_t("English"));
    
    $cap_msg = unserialize($_SESSION['cap_msg']);
    $sender_name = $cap_msg->getSender();
    
    shn_form_fopen("cap_new",null,array('req_message'=>false,'name'=>'cap_new'));

    shn_form_hidden(array('seq'=>'new_cap_info'));
    
    shn_form_fsopen(_t("Cap Message Information"));
    shn_form_select($language, _t("Language"), 'info_language', null, array('value'=>$c_land,'help'=>$help_language));
    
    shn_form_select($category, _t("Category"),'info_category_list',null,array('br'=>false));
    shn_form_button("Add", 'onClick="addCategory(info_category_list.value);"',array('br'=>false));
    shn_form_text('','info_category',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_category)"');
    print '<br />';    
    shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event));
    shn_form_text(_t("Urgency"),'info_urgency',null,array('help'=>$help_urgency));
    shn_form_text(_t("Severity"),'info_severity');
    shn_form_text(_t("Certainty"),'info_certainty');
    
    
    shn_form_fsopen(_t("Optional"));
    shn_form_text(_t("Sender Name"),'info_senderName',null,array('value'=>$sender_name));
    shn_form_text(_t("Headline"),'info_headline');
    shn_form_text(_t("Description"),'info_description');
    
    shn_form_text(_t("Audience"),'info_audience');
    
    
    $responseType = array('Shelter'=>'Shelter', 'Evacuate'=>'Evacuate', 
                          'Prepare'=>'Prepare', 'Execute'=>'Execute', 
                          'Monitor'=>'Monitor', 'Assess'=>'Assess', 
                          'None'=>'None');
    
    shn_form_select($responseType, _t("Response Type"),'info_responseType_list',null,array('br'=>false));
    shn_form_button("Add", 'onClick="addResponseType(info_responseType_list.value);"',array('br'=>false));
    shn_form_text('','info_responseType',null,array('br'=>false,'value'=>_t("None")));
    shn_form_button("Clear", 'onClick="clearValue(info_responseType)"');

    print '<br />';    
    
    shn_form_text(_t("Effective"),'info_effective',null,array('br'=>false));
    print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
    shn_form_text(_t("Onset"),'info_onset',null,array('br'=>false));
    print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
    shn_form_text(_t("Expires"),'info_expires',null,array('br'=>false));
    print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
    
    print "<hr />";
    shn_form_textarea(_t("Instruction"),'info_instruction');
    shn_form_text(_t("Web"),'info_web');
    shn_form_text(_t("Contact"),'info_contact');
    
    shn_form_fsopen(_t("Cap Message Info - Event Code"));
    shn_form_text(_t("ValueName"),'valueName');
    shn_form_text(_t("Value"),'value_val',null, array('br'=>false));
    shn_form_button("Add", 'onClick="addEventCode(valueName.value,value_val.value);"');
    shn_form_text('','info_eventCode',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_eventCode)"');
    shn_form_fsclose();
    
    shn_form_fsopen(_t("Cap Message Info - Parameter"));
    shn_form_text(_t("ValueName"),'param_valueName');
    shn_form_text(_t("Value"),'param_value',null, array('br'=>false));
    shn_form_button("Add", 'onClick="addParameter(param_valueName.value,param_value.value);"');
    shn_form_text('','info_parameter',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_parameter)"');
    shn_form_fsclose();
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Next"), 'style="float: right"');
    
    shn_form_fclose();
    
    _shn_msg_add_capjs();
}

function _shn_msg_cap_resourcenew()
{
    shn_form_fopen("cap_new",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_fsopen(_t("Cap Message Info - Resource"));

    shn_form_hidden(array('seq'=>'new_cap_res'));
    shn_form_text(_t("Resource Description"),'info_resDesc');
    shn_form_text(_t("mime Type"),'info_mimeType');
    shn_form_text(_t("Size"),'info_size');
    shn_form_text(_t("URI"),'info_uri','class=""');
    shn_form_text(_t("Attach File"),'info_derefUri', 'disabled="true" value="null"');
    shn_form_text(_t("Digest"),'info_digest');
    shn_form_submit(_t("Add Resource"));

    shn_form_fsclose();
    shn_form_fclose();
    
    shn_form_fopen("cap_new",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_hidden(array('seq'=>'new_cap_area'));
    print '<br />';
    shn_form_submit(_t("Next"));
    shn_form_fclose();

    _shn_msg_add_capjs();
    
}

function _shn_msg_cap_new_area()
{
    shn_form_fopen("cap_new",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_fsopen(_t("Cap Message Info - Area"));

    shn_form_hidden(array('seq'=>'add_cap_area'));
    shn_form_text(_t("Area Description"),'area_areaDesc',null,array('value'=>''));
        
    shn_form_fsopen(_t("Polygon"));
    shn_form_text(_t("X "),'area_pX');
    shn_form_text(_t("Y "),'area_pY',null,array('br'=>false));
    shn_form_button("Add Point", 'onClick="addCoordinates(area_pX.value, area_pY.value);"',array('br'=>false));
    shn_form_text('','area_poly_list',null,array('value'=>''));
    shn_form_fsclose();
  
    shn_form_fsopen(_t("Circle"));
    shn_form_text(_t("X "),'area_cX');
    shn_form_text(_t("Y "),'area_cY');
    shn_form_text(_t("Radius "),'area_r',null,array('br'=>false));
    shn_form_button("Add Circle", 'onClick="addCircle(area_cX.value, area_cY.value, area_r.value);"',array('br'=>false));
    shn_form_text('','area_crl_list',null,array('value'=>''));
    shn_form_fsclose();
    
    shn_form_fsopen(_t("Geocode"));
    shn_form_text(_t("Value Name"),'gc_vn');
    shn_form_text(_t("Value"),'gc_v',null,array('br'=>false));
    shn_form_button("Add Geocode", 'onClick="addGeocode(gc_vn.value, gc_v.value);"',array('br'=>false));
    shn_form_text('','gc_list',null,array('value'=>''));
    shn_form_fsclose();
    
    shn_form_fsopen(_t("Other"));
    shn_form_text(_t("Altitude"),'area_altitude',null,array('value'=>''));
    shn_form_text(_t("Ceiling"),'area_ceiling',null,array('value'=>''));
    shn_form_fsclose();
    
    print "<br />";
    shn_form_submit(_t("Add Area"));

    shn_form_fsclose();
    shn_form_fclose();
    
    shn_form_fopen("cap_new",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_hidden(array('seq'=>'new_cap_finish'));
    print '<br />';
    shn_form_submit(_t("Finish"));
    shn_form_fclose();

    _shn_msg_add_capjs();
}

function _shn_msg_cap_add_area()
{
    $alert = unserialize($_SESSION['cap_msg']);
    $info   = $alert->getInfo();
    
    $ar = new Msg_CapArea();
        
    $ar->setAreaDesc($_POST['area_areaDesc']);
    
    $poly = split('-', $_POST['area_poly_list']);
    $ar->addPolygon($poly);
    
    $circles = split('-', $_POST['area_crl_list']);
    foreach ($circles as $circle)
    {
        $circle = split(',', $circle);
        $ar->addCircle($circle[0],$circle[1],$circle[2]);
    }
    
    $geoCodes = split('-', $_POST['gc_list']);
    foreach ($geoCodes as $geoCode)
    {
        $geoCode = split(',', $geoCode);
        $ar->addGeocode($geoCode[0],$geoCode[1]);
    }
    
    $ar->setAltitude($_POST['area_altitude']);
    $ar->setCeiling($_POST['area_ceiling']);
    
    $info->addArea($ar);
    
    $alert->setInfo($info,0);
    $alert->printAreas(true);
    $_SESSION['cap_msg'] = serialize($alert);
}

function _shn_msg_cap_del_area()
{
    $index = $_REQUEST['area_id'];
    $alert = unserialize($_SESSION['cap_msg']);
    $info   = $alert->getInfo();
    $info->delArea($index);
    $alert->setInfo($info,0);
    $alert->printAreas(true);
    $_SESSION['cap_msg'] = serialize($alert);
}


function _shn_msg_cap_addmain()
{
    $alert  = new Msg_CapAlert();
    
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
    
    $_SESSION['cap_msg'] = serialize($alert);
    
}

function _shn_msg_cap_addinfo()
{
    //print_r();
    $alert = unserialize($_SESSION['cap_msg']);
    $info   = new Msg_CapInfo();
    
    $info->setLanguage($_POST['info_language']);
    
    $category = split(' ', $_POST['info_category']);
    foreach($category as $cat)
    {
        if(trim($cat) != '')
            $info->addCategory($cat);
    }
    
    $info->setEvent($_POST['info_event']);
    
    $responseType = split(' ', $_POST['info_responseType']);
    foreach($responseType as $res)
    {
        if(trim($res) != '')
            $info->addResponseType($res);
    }
    
    $info->setUrgency($_POST['info_urgency']);
    $info->setSeverity($_POST['info_severity']);
    $info->setCertainty($_POST['info_certainty']);
    $info->setAudience($_POST['info_audience']);
    
    $eventCodes = split(' ', $_POST['info_eventCode']);
    foreach($eventCodes as $eventCode)
    {
        $eventCode = split(':', $eventCode);
        if(trim($eventCode[0]) != '' && trim($eventCode[1]) != '' )
            $info->addEventCode($eventCode[0],$eventCode[1]);
    }
    
    $info->setEffective($_POST['info_effective']);
    $info->setOnset($_POST['info_onSet']);
    $info->setExpires($_POST['info_expires']);
    $info->setSendername($_POST['info_senderName']);
    $info->setHeadline($_POST['info_headline']);
    $info->setDescription($_POST['info_description']);
    $info->setInstruction($_POST['info_instruction']);
    $info->setWeb($_POST['web']);
    $info->setContact($_POST['contact']);
    
    $parameters = split(' ', $_POST['info_parameter']);
    foreach($parameters as $parameter)
    {
        $parameter = split(':', $parameter);
        if(trim($parameter[0]) != '' && trim($parameter[1]) != '' )
            $info->addParameter($parameter[0],$parameter[1]);
    }
    
    $alert->addInfo($info);
    $_SESSION['cap_msg'] = serialize($alert);
//    $alert->printCapXML();
}

function _shn_msg_cap_add_res()
{
    $alert = unserialize($_SESSION['cap_msg']);
    $info   = $alert->getInfo();
    
    $res = new Msg_CapResource();
    $res->setResourceDesc($_POST['info_resDesc']);
    $res->setMimeType($_POST['info_mimeType']);
    $res->setSize($_POST['info_size']);
    $res->setUri($_POST['info_uri']);
    $res->setDerefUri($_POST['info_derefUri']);
    $res->setDigest($_POST['info_digest']);
    
    $info->addResource($res);
    $alert->setInfo($info,0);
    $alert->printResource(true);
    $_SESSION['cap_msg'] = serialize($alert);
//    $alert->printCapXML();
}

function _shn_msg_cap_del_res()
{
    $index = $_REQUEST['res_id'];
    $alert = unserialize($_SESSION['cap_msg']);
    $info   = $alert->getInfo();
    $info->delResource($index);
    $alert->setInfo($info,0);
    $alert->printResource(true);
    $_SESSION['cap_msg'] = serialize($alert);
}

function _shn_msg_cap_finish()
{
    $index = $_REQUEST['res_id'];
    $alert = unserialize($_SESSION['cap_msg']);
?>
    <div class="center"><h3>Save CAP AS:</h3></div>
    <table class="layout">
        <tr>
        <td align="right">
<?php
    shn_form_fopen("cap_new",null,array('req_message'=>false,'style'=>'form_blank'));
    shn_form_hidden(array('seq'=>'new_cap_save','type'=>'template'));
    print '<br />';
    shn_form_submit(_t("Template"));
    shn_form_fclose();
?>
        </td>
        <td>
<?php
    shn_form_fopen("cap_new",null,array('req_message'=>false,'style'=>'form_blank'));
    shn_form_hidden(array('seq'=>'new_cap_save','type'=>'message'));
    print '<br />';
    shn_form_submit(_t("Message"));
    shn_form_fclose();
?>
        </td>
        </tr>
    </table>
<?php
    $alert->printFormattedMsg();
}

function _shn_msg_cap_save()
{
    $type = $_POST['type'];
    $alert = unserialize($_SESSION['cap_msg']);
    
    $MSG_DIR = '../res/msg';
    $tpl_path = "$MSG_DIR/" . "cap/templates/";
    $msg_path = "$MSG_DIR/" . "cap/messages/";
        
    switch($type)
    {
        case 'template':
                    $fileName = $alert->getIdentifier() . '.xml';
                    $alert->saveXML($tpl_path, $fileName);
                    print "<h3>" . _t("CAP saved as a Template") . "</h3>";
                    print _t("File Name") . 
                          "<strong>" . $tpl_path.$fileName . "</strong>";
                    break;
        case 'message':
                    $fileName = $alert->getIdentifier() . '.xml';
                    $alert->saveXML($msg_path, $fileName);
                    print "<h3>" . _t("CAP saved as a Message") . "</h3>";
                    print _t("File Name") . 
                          ":<strong>" . $msg_path.$fileName . "</strong>";
                    break;
    }
    
    $alert->printFormattedMsg();
}
?>


        
