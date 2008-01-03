<?php
/* $Id: api.inc,v 1.3 2008-01-03 04:43:06 isurunishan Exp $ */

/**
 * Main Controller of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function shn_mpr_api_addmp($arrmpr){
    global $global;

    $insert_array['p_uuid'] = $arrmpr['p_uuid'];

    //Basic Details : Table person_uuid and Phonetic Table
    if(isset($arrmpr['full_name'])){
        $insert_array['full_name'] = $arrmpr['full_name'];
        shn_db_insert_phonetic($insert_array['full_name'],$insert_array['p_uuid']);
    }
    if(isset($arrmpr['family_name'])){
        $insert_array['family_name'] = $arrmpr['family_name'];
        shn_db_insert_phonetic($insert_array['family_name'],$insert_array['p_uuid']);
    }
    if(isset($arrmpr['local_name'])){
        $insert_array['l10n_name'] = $arrmpr['local_name'];
        shn_db_insert_phonetic($insert_array['l10n_name'],$insert_array['p_uuid']);
    }

    shn_db_insert($insert_array,'person_uuid',true, 'p_uuid');
    $insert_array = null;


    $insert_array['p_uuid'] = $arrmpr['p_uuid'];
    //Identity
    if(isset($arrmpr['idcard'])) {
        $insert_array['serial'] = $arrmpr['idcard'];
        $insert_array['opt_id_type'] = 'nic';
        shn_db_insert($insert_array,'identity_to_person',true,'p_uuid');
    }
    if(isset($arrmpr['passport'])) {
        $insert_array['serial'] = $arrmpr['passport'];
        $insert_array['opt_id_type'] = 'pas';
        shn_db_insert($insert_array,'identity_to_person',true,'p_uuid');
    }
    if(isset($arrmpr['drv_license'])) {
        $insert_array['serial'] = $arrmpr['drv_license'];
        $insert_array['opt_id_type'] = 'dln';
        shn_db_insert($insert_array,'identity_to_person', true, 'p_uuid');
    }
    $insert_array = null;

    //Contacts
    $insert_array['poc_uuid'] = $arrmpr['p_uuid'];
    $insert_array['opt_person_loc_type'] = 'hom';
    if(isset($arrmpr['address'])){
        $insert_array['address'] = $arrmpr['address'];
    }
    /* This hack should be integrated with 
        the lib_location
    */
    //Starts
        $i = $conf['mod_mpr_location_lower_limit'];
        while((! isset($arrmpr[$i])) && 
                $i > $conf['mod_mpr_location_upper_limit'] ) 
            $i--;
    //Ends
    if(isset($arrmpr[$i]))
        $insert_array['location_id'] = $arrmpr[$i];

    if(isset($arrmpr['zip']))
        $insert_array['postcode'] = $arrmpr['zip'];
    shn_db_insert($insert_array,'location_details', true, 'poc_uuid');
    $insert_array = null;

    //Contact : Phone
    $insert_array['pgoc_uuid'] = $arrmpr['p_uuid'];
    if(isset($arrmpr['phone'])){
        $insert_array['contact_value'] = $arrmpr['phone'];
        $insert_array['opt_contact_type'] = 'curr';
        
    }
    shn_db_insert($insert_array,'contact', true, 'pgoc_uuid');
    $insert_array = null;

    //Contact : Mobile
    $insert_array['pgoc_uuid'] = $arrmpr['p_uuid'];
    if(isset($arrmpr['mobile'])){
        $insert_array['contact_value'] = $arrmpr['mobile'];
        $insert_array['opt_contact_type'] = 'cmob';
    }
    shn_db_insert($insert_array,'contact',true,'pgoc_uuid');
    $insert_array = null;
   
    //Physical Details : person_physical
    $insert_array['p_uuid'] = $arrmpr['p_uuid'];
    if(isset($arrmpr['opt_eye_color']))
        $insert_array['opt_eye_color'] = $arrmpr['opt_eye_color'];
    if(isset($arrmpr['opt_skin_color']))
        $insert_array['opt_skin_color'] = $arrmpr['opt_skin_color'];
    if(isset($arrmpr['opt_hair_color']))
        $insert_array['opt_hair_color'] = $arrmpr['opt_hair_color'];
    if(isset($arrmpr['height']))
        $insert_array['height'] = $arrmpr['height'];
    if(isset($arrmpr['weight']))
        $insert_array['weight'] = $arrmpr['weight'];
    if(isset($arrmpr['opt_blood_type']))
        $insert_array['opt_blood_type'] = $arrmpr['opt_blood_type'];
    if(isset($arrmpr['physical_comments']))
        $insert_array['comments'] = $arrmpr['physical_comments'];
    shn_db_insert($insert_array,'person_physical',true,'p_uuid');
    $insert_array = null;

    $insert_array['p_uuid'] = $arrmpr['p_uuid'];


    //Other Details
    if(isset($arrmpr['last_seen']))
        $insert_array['last_seen'] = $arrmpr['last_seen'];
    if(isset($arrmpr['last_clothing']))
        $insert_array['last_clothing'] = $arrmpr['last_clothing'];
    if(isset($arrmpr['comments']))
        $insert_array['comments'] = $arrmpr['comments'];

    shn_db_insert($insert_array,'person_missing',true,'p_uuid');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['p_uuid'] = $arrmpr['p_uuid'];
    //person_details        
    if(isset($arrmpr['dob']))
        $insert_array['birth_date'] = $arrmpr['dob'];
    if(isset($arrmpr['opt_age_group']))
        $insert_array['opt_age_group'] = $arrmpr['opt_age_group'];
    if(isset($arrmpr['opt_gender']))
        $insert_array['opt_gender'] = $arrmpr['opt_gender'];
    if(isset($arrmpr['opt_marital_status']))
        $insert_array['opt_marital_status'] = $arrmpr['opt_marital_status'];
    if(isset($arrmpr['opt_religion']))
        $insert_array['opt_religion'] = $arrmpr['opt_religion'];
    if(isset($arrmpr['opt_race']))
        $insert_array['opt_race'] = $arrmpr['opt_race'];
    shn_db_insert($insert_array,'person_details',true,'p_uuid');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['p_uuid'] = $arrmpr['p_uuid'];
    //Insert Into person_status mis
    $insert_array['opt_status'] = $arrmpr['opt_status'];
    $insert_array['isvictim'] = 'TRUE';
    shn_db_insert($insert_array,'person_status',true,'p_uuid');
    //reset $insert_array 
    $insert_array = null;

    //insert into mutiple incidents 
    $insert_array['x_uuid'] = $arrmpr['p_uuid'];
    $insert_array['incident_id'] = $_SESSION['user_pref_ims_incident_id'];
    shn_db_insert($insert_array,'resource_to_incident',true,'x_uuid');
    //reset $insert_array 
    $insert_array = null;

    /** 
     * todo: Later for now using the person_to_report to group
    //Insert into pgroup
    /*
     * For Tracking purpose create a group around missing person
     * /
    $insert_array['p_uuid'] = $arrmpr['p_uuid'];
    $insert_array['opt_group_type'] = 'mpr_trk';
    shn_db_insert($insert_array,'pgroup');
    //reset $insert_array 
    $insert_array = null;
    */

    //reset $insert_array 

    if($arrmpr['tracker_id']){
        shn_add_person_to_report ($arrmpr['p_uuid'],
                $arrmpr['tracker_id'],
                $_SESSION['mpr_add']['report_person']['rep_relation']);
    }else
        shn_mpr_addmp_insert_reporter($arrmpr['p_uuid']);

    //Insert Image if image save handler is set to database
    if($conf['mod_mpr_upload_picture_savehandler'] == 'database'){
        shn_image_to_db_ex($arrmpr['p_uuid'],
                            $_SESSION['mpr']['entry']['image'],
                            $_SESSION['mpr']['entry']['image_type'],
                            $_SESSION['mpr']['entry']['image_height'],
                            $_SESSION['mpr']['entry']['image_width']);
    }
}
?>
