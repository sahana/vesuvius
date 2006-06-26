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

//$cap = new Msg_CapMessage('../res/msg/SampleAlerts.xml');

//$cap->printCapXML();

require_once('class_cap_alert.inc');
require_once('class_cap_info.inc');
require_once('class_cap_resource.inc');
require_once('class_cap_area.inc');
require_once('lib_cap_js.inc');

function _shn_msg_cap_newform()
{
    shn_form_fopen("cap_new",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'new_cap'));
    
    	
	$id = time();
	$today = date("Y-m-d h:m:s");
	$status = array('Actual'=>'Actual', 'Exercise'=>'Exercise', 'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');
	$msgType = array('Alert'=>'Alert', 'Update'=>'Update', 'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
	$scope = array('Public'=>'Public', 'Restricted'=>'Restricted', 'Private'=>'Private');
    
    $category = array('Geo'=>'Geo', 'Met'=>'Met', 'Safety'=>'Safety', 
                      'Security'=>'Security', 'Rescue'=>'Rescue', 
                      'Fire'=>'Fire', 'Health'=>'Health', 'Env'=>'Env', 
                      'Transport'=>'Transport', 'Infra'=>'Infra', 
                      'CBRNE'=>'CBRNE', 'Other'=>'Other');
	
    print '<div id="tab1">'; // tab1 - start
    shn_form_fsopen(_("New Cap Message"));
    shn_form_text(_("Message Identifier"),'identifier',null,array('value'=>$status[0] . "-$id"));
    shn_form_text(_("Date"),'sent',null,array('value'=>$today));
    shn_form_text(_("Sender"),'sender','class=""');
    shn_form_select($status, _("Status"), 'status');
    shn_form_select($msgType, _("Message Type"), 'msgType', 'onChange="showHideNote(this);"');
    print '<div id="cap_note">';
    shn_form_textarea(_("Note"),'note');
    print '</div>';
    shn_form_text(_("Source"),'source',null, array('value'=>'Sahana'));
	
    
	shn_form_fsopen(_("Scope"));
	shn_form_select($scope, _("Scope"), 'scope','onChange="changeScope(this);"');
	print '<div id="scope_rest">';
    shn_form_text(_("Restriction [Restricted]"),'restriction');
    print '</div><div id="scope_addr">';
    shn_form_textarea(_("Addresses [private]"),'addresses');
    print '</div>';
    shn_form_fsclose();
    
    shn_form_text(_("Code"),'code',null,array('br'=>false));
    print "<strong>Enter space separated set of codes</strong> <br />";

    
    shn_form_text(_("References"),'references');
    shn_form_text(_("incidents"),'incidents');

    shn_form_button('Next', 'onClick=load_tab("tab2") style="float: right"');
    print '</div>'; // tab1 - end
    
    print '<div id="tab2">'; // tab2 - start
    shn_form_button('Back', 'onClick=load_tab("tab1")');
    
    shn_form_fsopen(_("Cap Message Info"));
    
    shn_form_text(_("Sender Name"),'info_senderName');
    shn_form_text(_("Headline"),'info_headline');
    shn_form_text(_("Description"),'info_description');
    shn_form_text(_("Language"),'info_language');
    shn_form_text(_("Event"),'info_event');
    shn_form_text(_("Audience"),'info_audience');
    
    
    $responseType = array('Shelter'=>'Shelter', 'Evacuate'=>'Evacuate', 
                          'Prepare'=>'Prepare', 'Execute'=>'Execute', 
                          'Monitor'=>'Monitor', 'Assess'=>'Assess', 
                          'None'=>'None');
    shn_form_fsopen(_("Response Type"));
    shn_form_select($responseType, _("Response Type"),'info_responseType_list',null,array('br'=>false));
    shn_form_button("Add", 'onClick="addResponseType(info_responseType_list.value);"');
    shn_form_text('','info_responseType',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_responseType)"');
    shn_form_fsclose();
    
    shn_form_fsopen(_("Category"));
    shn_form_select($category, _("Category"),'info_category_list',null,array('br'=>false));
    shn_form_button("Add", 'onClick="addCategory(info_category_list.value);"');
    shn_form_text('','info_category',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_category)"');
    
    
    
    shn_form_text(_("Urgency"),'info_urgency');
    shn_form_text(_("Severity"),'info_severity');
    shn_form_text(_("Certainty"),'info_certainty');
    
    shn_form_text(_("Effective"),'info_effective',null,array('br'=>false));
    print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
    shn_form_text(_("Onset"),'info_onset',null,array('br'=>false));
    print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
    shn_form_text(_("Expires"),'info_expires',null,array('br'=>false));
    print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
    
    shn_form_button('Next', 'onClick=load_tab("tab3") style="float: right"');
    print '</div>'; // tab2 - end
    
    print '<div id="tab3">'; // tab3 - start
    
    shn_form_textarea(_("Instruction"),'info_instruction');
    shn_form_text(_("Web"),'info_web');
    shn_form_text(_("Contact"),'info_contact');
    
    shn_form_fsopen(_("Cap Message Info - Event Code"));
    shn_form_text(_("ValueName"),'valueName');
    shn_form_text(_("Value"),'value_val',null, array('br'=>false));
    shn_form_button("Add", 'onClick="addEventCode(valueName.value,value_val.value);"');
    shn_form_text('','info_eventCode',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_eventCode)"');
    shn_form_fsclose();
    
    shn_form_fsopen(_("Cap Message Info - Parameter"));
    shn_form_text(_("ValueName"),'param_valueName');
    shn_form_text(_("Value"),'param_value',null, array('br'=>false));
    shn_form_button("Add", 'onClick="addParameter(param_valueName.value,param_value.value);"');
    shn_form_text('','info_parameter',null,array('br'=>false));
    shn_form_button("Clear", 'onClick="clearValue(info_parameter)"');
    shn_form_fsclose();
    
    shn_form_fsopen(_("Cap Message Info - Resource"));
    shn_form_text(_("Resource Description"),'info_resDesc');
    shn_form_text(_("mime Type"),'info_mimeType');
    shn_form_text(_("Size"),'info_size');
    shn_form_text(_("URI"),'info_uri','class=""');
    shn_form_text(_("Attach File"),'info_derefUri', 'disabled="true" value="null"');
    shn_form_text(_("Digest"),'info_digest');
    shn_form_button("Add Resource", 'onClick="addResource(info_resDesc.value, info_mimeType.value, info_size.value, info_uri.value, info_derefUri.value, info_digest.value);"');
    print "<br />";
    shn_form_textarea(_("Resources"),'info_resource');
    shn_form_fsclose();
    
    shn_form_fsopen(_("Cap Message Info - Area"));
    shn_form_text(_("Area Description"),'area_areaDesc');
        
    shn_form_fsopen(_("Polygon"));
    shn_form_text(_("X "),'area_pX');
    shn_form_text(_("Y "),'area_pY',null,array('br'=>false));
    shn_form_button("Add Point", 'onClick="addCoordinates(area_pX.value, area_pY.value);"');
    shn_form_text('','area_poly_list');
    shn_form_fsclose();
  
    shn_form_fsopen(_("Circle"));
    shn_form_text(_("X "),'area_cX');
    shn_form_text(_("Y "),'area_cY');
    shn_form_text(_("Radius "),'area_r',null,array('br'=>false));
    shn_form_button("Add Circle", 'onClick="addCircle(area_cX.value, area_cY.value, area_r.value);"');
    shn_form_text('','area_crl_list');
    shn_form_fsclose();
    
    shn_form_fsopen(_("Geocode"));
    shn_form_text(_("Value Name"),'gc_vn');
    shn_form_text(_("Value"),'gc_v',null,array('br'=>false));
    shn_form_button("Add Geocode", 'onClick="addGeocode(gc_vn.value, gc_v.value);"');
    shn_form_text('','gc_list');
    shn_form_fsclose();
    
    shn_form_text(_("Altitude"),'area_altitude');
    shn_form_text(_("Ceiling"),'area_ceiling');
    
    print "<br />";
    shn_form_button("Add Area", 'onClick="addArea();"');
    print "<br />";
    shn_form_textarea('','info_area');    
    
    shn_form_fsclose();
    
    shn_form_fsclose();
    print '</div>'; // tab3 - end
    shn_form_submit(_("New CAP Message"));
    
    
	shn_form_fsclose(); //Close capmessage form
	
    
    shn_form_fclose();
    
    _shn_msg_add_capjs(); // the javascript has to be added after the form
    
}

function _shn_msg_cap_newmsg()
{
    $alert  = new Msg_CapAlert();
    $info   = new Msg_CapInfo();
    
    
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
    
    /***
     * Building the info Object
     */
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
    
    $resources = split('\n\r', $_POST['info_resource']);
    foreach($resources as $resource)
    {
        $res = new Msg_CapResource();
    
        $resource = split(',', $resource);
        $res->setResourceDesc($resource[0]);
        $res->setMimeType($resource[1]);
        $res->setSize($resource[2]);
        $res->setUri($resource[3]);
        $res->setDerefUri($resource[4]);
        $res->setDigest($resource[5]);
        
        $info->addResource($res);        
    }
    
    $areas = split('\n', $_POST['info_area']);
    foreach($areas as $area)
    {
        $ar = new Msg_CapArea();
        
        $area = split('//', $area);
        $ar->setAreaDesc($area[0]);
        
        $poly = split('-', $area[1]);
        $ar->addPolygon($poly);
        
        $circles = split('-', $area[2]);
        foreach ($circles as $circle)
        {
            $circle = split(',', $circle);
            $ar->addCircle($circle[0],$circle[1],$circle[2]);
        }
        
        $geoCodes = split('-', $area[3]);
        foreach ($geoCodes as $geoCode)
        {
            $geoCode = split(',', $geoCode);
            $ar->addGeocode($geoCode[0],$geoCode[1]);
        }
        
        $ar->setAltitude($area[4]);
        $ar->setCeiling($area[5]);
        
        $info->addArea($ar);        
    }
    
    $alert->addInfo($info);   
    
    $alert->printFormattedMsg();

    $fileName = $_POST['identifier'] . '.xml';
    $alert->saveXML($fileName);

//    shn_form_fopen("cap_new",null);
//
//    shn_form_hidden(array('seq'=>'save_cap'));
//    shn_form_text(_("File Name"),'file_name',null);
//    shn_form_submit(_("Save CAP Message"));
//    shn_form_fclose();

}

function _shn_msg_cap_savexml()
{


    unset($_POST['file_name']);

    print ">>>>>>>>>>. $fileName";
    $msg = new Msg_CapMessage();

    foreach($_POST as $post_key=>$post_val)
    {
        $msg->$post_key = $post_val;
    }

    $msg->printFormattedMsg();
}

switch ($_REQUEST['seq'])
{
    case '' :
            _shn_msg_cap_newform();
            break;

    case 'new_cap':
                   _shn_msg_cap_newmsg();
                   break;
    case 'save_cap':
                   _shn_msg_cap_savexml();
                   break;
}


?>

