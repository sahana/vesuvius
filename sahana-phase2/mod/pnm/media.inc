<?php
/**Media Organization Management Functionality of the Press and Media Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravith Botejue, Miyuru Daminda, Reka Sandaruwan, Chamara Caldera, Nishantha Pradeep
* @copyright Respective Authors
* @package    sahana
* @subpackage pnm
* 
* Developed during Sahana 2009 as a tribute.
*/

switch($_POST['seq']){
        case '':            
            _shn_pnm_media_reg_form();
            break;
        case 'add':
            if(_shn_pnm_validate_add()){
                _shn_pnm_media_add();
            }
            else{
                _shn_pnm_media_reg_form();
            }
        default :
            break;        
    }
    
function _shn_pnm_media_reg_form(){
    echo '<h3>Add New Media Organization</h3>';
    shn_form_fopen('mediareg',null, array('req_message'=>false));
    shn_form_fsopen(_t('Add Media Organization'));
    shn_form_hidden(array('seq'=>'add'));
    shn_form_text(_t('Name : '),'name','', array('req'=>true));
    shn_form_fsopen(_t("Contact Details"));
    shn_form_text(_t("Contact Person"), 'contact_person', '', null);
    shn_form_textarea(_t('Contact Address : '),'address','', null);
    shn_form_text(_t("Tel No :"), 'tel_no', '', null);
    shn_form_text(_t('Email :'), 'email', '', null);
    shn_form_fsclose();
    shn_form_submit(_t('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_pnm_validate_add(){
    if($_POST['name'] == null){
        add_error("Name can not be null");
        return false;
    }
    return true;
}

function _shn_pnm_add_person($name){
    global $global;
    $uuid = shn_create_uuid('p');
    $sql = "INSERT INTO person_uuid(p_uuid, full_name) VALUES('$uuid', '$name')";
    $res = $global['db']->Execute($sql);
    
    return $uuid;
}

function _shn_pre_add_contact($puuid, $type, $contact){
    global $global;
    $sql = "INSERT INTO contact VALUES('$puuid', '$type', '$contact')";
    $res = $global['db']->Execute($sql);
    return $res;
}

function _shn_pnm_media_add(){
    global $global;
    $person = _shn_pnm_add_person($_POST['contact_person']);
    
    if($_POST['address'] != null){
        _shn_pre_add_contact($person, 'address', $_POST['address']);
    }
    if($_POST[''] != null){
        _shn_pre_add_contact($person, 'tel_no', $_POST['tel_no']);
    }
    if($_POST[''] != null){
        _shn_pre_add_contact($person, 'email', $_POST['email']);
    }
    $name = $_POST['name'];
    $uuid = shn_create_uuid('o');
    $sql = "INSERT INTO pnm_media_org VALUES('$uuid', '$name', '$person')";
    $res = $global['db']->Execute($sql);
    echo $global['db']->ErrorMsg();
    if($res != false){
        add_confirmation("Media Organization added");
    }
    
}

function _shn_pnm_get_person_name($person_uuid){
    global $global;
    $sql = "SELECT full_name FROM person_uuid WHERE p_uuid = '$person_uuid'";
    $res = $global['db']->Execute($sql);
    if($res->RecordCount() > 0){
        return $res->fields['full_name'];
    }
    else{
        return false;
    }
}

