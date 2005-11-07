<?php
//validation
switch ($_POST['seq']) {

    case 'entry':
        if(shn_mpr_editmp_validate()){
            shn_mpr_editmp_upload();
        }else
            shn_mpr_editmp_entry(true);
    break;

    case 'upload_pic' :
        if(! shn_mpr_editmp_upload_pic())
            shn_mpr_editmp_upload(true);
        else
            shn_mpr_editmp_confirm();
    break;

    case 'commit' :
        shn_mpr_editmp_commit();
    break;

    default:
        //load details
        $_SESSION['mpr_entry'] = null;
        shn_mpr_editmp_load($_GET['id']);
        shn_mpr_editmp_entry();            
    break;

}

function shn_mpr_editmp_load($p_uuid)
{
    global $global;

    //@todo: check existance
    $_SESSION['mpr_entry']['p_uuid'] = $p_uuid;

    //Status
    $sql = "SELECT opt_status FROM person_status WHERE p_uuid = '$p_uuid'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['opt_status'] = $rs->fields[0];
   
    //identity_to_person
    //identity card
    $sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'nic'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['idcard'] = $rs->fields[0];
    //passport
    $sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'pas'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['passport'] = $rs->fields[0];
    //Driving License
    $sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'dln'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['drv_license'] = $rs->fields[0];

    //Basic Details, Physical Details, Other Details,  
    //person_uuid
    $sql = "SELECT 
                a.full_name, a.family_name, a.l10n_name,
                b.birth_date, b.opt_age_group, b.opt_race, b.opt_religion, 
                b.opt_marital_status,
                c.opt_blood_type, c.height, c.weight, c.opt_eye_color, c.opt_skin_color,
                c.opt_hair_color, c.comments as physical_comments, 
                d.last_seen, d.last_clothing, d.comments,
                e.name as rep_full_name, e.address as rep_address,
                e.relation as rep_relation, e.phone as rep_phone,
                e.email as rep_email, 
                f.address, f.postcode
            FROM person_uuid a
            LEFT OUTER JOIN person_details b USING (p_uuid)
            LEFT OUTER JOIN person_physical c USING (p_uuid)
            LEFT OUTER JOIN person_missing d USING (p_uuid)
            LEFT OUTER JOIN person_to_report e USING (p_uuid)
            LEFT OUTER JOIN location_details f ON (f.poc_uuid=a.p_uuid)
            WHERE a.p_uuid = '$p_uuid'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['full_name'] = $rs->fields['full_name'];
    $_SESSION['mpr_entry']['family_name'] = $rs->fields['family_name'];
    $_SESSION['mpr_entry']['local_name'] = $rs->fields['l10n_name'];
    $_SESSION['mpr_entry']['dob'] = $rs->fields['birth_date'];
    $_SESSION['mpr_entry']['opt_age_group'] = $rs->fields['opt_age_group'];
    $_SESSION['mpr_entry']['opt_race'] = $rs->fields['opt_race'];
    $_SESSION['mpr_entry']['opt_religion'] = $rs->fields['opt_religion'];
    $_SESSION['mpr_entry']['opt_marital_status'] = $rs->fields['opt_marital_status'];
    $_SESSION['mpr_entry']['opt_blood_type'] = $rs->fields['opt_blood_type'];
    $_SESSION['mpr_entry']['height'] = htmlspecialchars($rs->fields['height']);
    $_SESSION['mpr_entry']['weight'] = htmlspecialchars($rs->fields['weight']);
    $_SESSION['mpr_entry']['opt_eye_color'] = $rs->fields['opt_eye_color'];
    $_SESSION['mpr_entry']['opt_skin_color'] = $rs->fields['opt_skin_color'];
    $_SESSION['mpr_entry']['opt_hair_color'] = $rs->fields['opt_hair_color'];
    $_SESSION['mpr_entry']['physical_comments'] = $rs->fields['physical_comments'];
    $_SESSION['mpr_entry']['last_seen'] = $rs->fields['last_seen'];
    $_SESSION['mpr_entry']['last_clothing'] = $rs->fields['last_clothing'];
    $_SESSION['mpr_entry']['comments'] = $rs->fields['comments'];
    $_SESSION['mpr_entry']['rep_full_name'] = $rs->fields['rep_full_name'];
    $_SESSION['mpr_entry']['rep_address'] = $rs->fields['rep_address'];
    $_SESSION['mpr_entry']['rep_relation'] = $rs->fields['rep_relation'];
    $_SESSION['mpr_entry']['rep_phone'] = $rs->fields['rep_phone'];
    $_SESSION['mpr_entry']['rep_email'] = $rs->fields['rep_email'];
    $_SESSION['mpr_entry']['address'] = $rs->fields['address'];
    $_SESSION['mpr_entry']['zip'] = $rs->fields['postcode'];

    //Home phone
    $sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'curr'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['phone'] = $rs->fields[0];

    //Mobile phone
    $sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'cmob'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_entry']['mobile'] = $rs->fields[0];
}

function shn_mpr_editmp_entry($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("editmp",null);

    shn_form_hidden(array('seq'=>'entry'));

    shn_form_fsopen('Status');
    shn_form_opt_select('opt_status','Change the status','',array('value'=>$_SESSION['mpr_entry']['opt_status']));
    shn_form_fsclose();

    shn_form_fsopen('Identity');
    shn_form_text('Identity Card Number','idcard','size="30"',array('value'=>$_SESSION['mpr_entry']['idcard']));
    shn_form_text('Passport Number','passport','size="30"',array('value'=>$_SESSION['mpr_entry']['passport']));
    shn_form_text('Driving License','drv_license','size="30"',array('value'=>$_SESSION['mpr_entry']['drv_license']));
    shn_form_fsclose();

    shn_form_fsopen("Basic Details");
?>
<p>Please enter any of the following details on the person:</p> 
<?php

    shn_form_text('Full Name','full_name','size="40"',array('value'=>$_SESSION['mpr_entry']['full_name']));
    shn_form_text('Family Name','family_name','size="40"',array('value'=>$_SESSION['mpr_entry']['family_name']));
    shn_form_text('Local Name','local_name','size="40"',array('value'=>$_SESSION['mpr_entry']['local_name']));
    shn_form_text('Date of Birth   (YYYY-MM-DD)','dob','size=8',array('value'=>$_SESSION['mpr_entry']['dob']));
    shn_form_opt_select("opt_age_group","Age Group",'',array('value'=>$_SESSION['mpr_entry']['opt_age_group']));
    shn_form_opt_select("opt_gender","Gender",'',array('value'=>$_SESSION['mpr_entry']['opt_gender']));
    shn_form_opt_select("opt_marital_status","Marital Status",'',array('value'=>$_SESSION['mpr_entry']['opt_marital_status']));
    shn_form_opt_select("opt_religion","Religion",'',array('value'=>$_SESSION['mpr_entry']['opt_religion']));
    shn_form_opt_select("opt_race","Race",'',array('value'=>$_SESSION['mpr_entry']['opt_race']));

    shn_form_fsclose();

    shn_form_fsopen("Contact Details");
    shn_form_textarea("Address","address",'',array('value'=>$_SESSION['mpr_entry']['address']));
    shn_form_text('Postal Code','zip','size="10"',array('value'=>$_SESSION['mpr_entry']['zip']));
    shn_form_text('Home Phone','phone','size="10"',array('value'=>$_SESSION['mpr_entry']['phone']));
    shn_form_text('Mobile','mobile','size="10"',array('value'=>$_SESSION['mpr_entry']['mobile']));
    shn_form_fsclose();

    shn_form_fsopen("Physical Details");
    shn_form_opt_select("opt_eye_color","Eye Colour",'',array('value'=>$_SESSION['mpr_entry']['opt_eye_color']));
    shn_form_opt_select("opt_skin_color","Skin Colour",'',array('value'=>$_SESSION['mpr_entry']['opt_skin_color']));
    shn_form_opt_select("opt_hair_color","Hair Colour",'',array('value'=>$_SESSION['mpr_entry']['opt_hair_color']));
    shn_form_text('Height','height','size="10"',array('value'=>$_SESSION['mpr_entry']['height']));
    shn_form_text('Weight','weight','size="10"',array('value'=>$_SESSION['mpr_entry']['weight']));
    shn_form_textarea('Comments','physical_comments','',array('value'=>$_SESSION['mpr_entry']['physical_comments']));
    shn_form_fsclose();

    shn_form_fsopen("Other Details");
    shn_form_opt_select("opt_blood_type","Blood Type",'',array('value'=>$_SESSION['mpr_entry']['opt_blood_type']));
    shn_form_textarea('Last Seen','last_seen','',array('value'=>$_SESSION['mpr_entry']['last_seen']));
    shn_form_textarea('Last Clothing','last_clothing','',array('value'=>$_SESSION['mpr_entry']['last_clothing']));
    shn_form_textarea('Comments','comments','',array('value'=>$_SESSION['mpr_entry']['comments']));
    shn_form_fsclose();

    shn_form_fsopen("Reporting Person");
    shn_form_text('Name','rep_full_name','size="40"',array('value'=>$_SESSION['mpr_entry']['rep_full_name']));
    shn_form_text('Relation','rep_relation','size="40"',array('value'=>$_SESSION['mpr_entry']['rep_relation']));
    shn_form_textarea('Address','rep_address','',array('value'=>$_SESSION['mpr_entry']['rep_address']));
    shn_form_text('Phone','rep_phone','size="40"',array('value'=>$_SESSION['mpr_entry']['rep_phone']));
    shn_form_text('Email','rep_email','size="40"',array('value'=>$_SESSION['mpr_entry']['rep_email']));
    shn_form_fsclose();
    
    shn_form_submit('Next');
    shn_form_fclose();
}

function shn_mpr_editmp_validate() 
{
    $error_flag=false;
    
    //trim them all
    foreach($_POST as $k => $v){
        $v = trim($v);
        if($v != '')
            $local_post[$k] = $v;
    }

    //anything entered?
    if(empty($local_post)){
        add_error(_("You have not completed the form"));
        return false;
    }
    
    //fullname is entered?
    if(! isset($local_post['full_name'])){
        add_error(_("Please enter the full name of the missing person"));
        $error_flag=true;
    }

    //Reporting person name
    if(! isset($local_post['rep_full_name'])){
        add_error(_("Please enter the full name of the reporting person"));
        $error_flag=true;
    }

    //Reporting person relation
    if(! isset($local_post['rep_relation'])){
        add_error(_("Please enter the relationship of the reporting person"));
        $error_flag=true;
    }

    //Reporting person contact
    if(! ( isset($local_post['rep_address']) || 
            isset($local_post['rep_phone']) || 
            isset($local_post['rep_email']) ) ){
        add_error(_("Please enter any contact method of the reporting person"));
        $error_flag=true;
    }
             
    if(isset($local_post['dob']) && ! shn_valid_date($local_post['dob'])){
        add_error(_("Invalid Date of Birth"));
        $error_flag=true;
    }

    //set session
    $local_post['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //clean
    session_unset($_SESSION['mpr_entry']);
    $_SESSION['mpr_entry']=$local_post;

    if($error_flag)
        return false;
    else{
        return true;
    }
} 

function shn_mpr_editmp_upload($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("editmp",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'upload_pic'));
    shn_form_fsopen('Replace Current Picture');
    shn_show_thumb($_SESSION['mpr_entry']['p_uuid']);
?>
    <br />
<?
    shn_form_upload("Upload Picture","picture");
    shn_form_submit('Next');
    shn_form_fsclose();
    shn_form_fclose();
}

function shn_mpr_editmp_upload_pic() 
{
    //No file was uploaded ignore
    if($_FILES['picture']['error']==UPLOAD_ERR_NO_FILE)
        return true;
    //Uploads 
    global $global;
    $info = getimagesize($_FILES['picture']['tmp_name']);
    //check the image type 
    if(! $info){
        add_error(_("Invalid Image Type Please try again"));
        return false;    
    }

    list($ignore,$ext) = split("\/",$info['mime']);
    //putting a dot ;-) 
    $ext = '.'.$ext;

    $upload_dir = $global['approot'].'www/tmp/';
    $uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_entry']['p_uuid'].$ext;
    move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
    $desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_entry']['p_uuid'].$ext; 
    //make thumb 100X100 or some thing like that ;-)
    shn_image_resize($uploadfile,$desc_path,100,100);
    return true;
}

function shn_mpr_editmp_confirm()
{
    shn_form_fopen("editmp",null);
    shn_form_fsopen("Person");
    shn_form_hidden(array('seq'=>'commit'));
    shn_show_thumb($_SESSION['mpr_entry']['p_uuid']);
?>
    <br />
<?php
    //Status
    shn_form_label(shn_get_field_opt($_SESSION['mpr_entry']['opt_status'],'opt_status'),'');
    shn_form_fsclose();
    //Identity
    if(isset($_SESSION['mpr_entry']['idcard']) ||
            isset($_SESSION['mpr_entry']['passport']) ||
            isset($_SESSION['mpr_entry']['drv_license']) ) {
        shn_form_fsopen("Identity");
        $identity_section = true;
    }
    if(isset($_SESSION['mpr_entry']['idcard']))
        shn_form_label('Identity Card Number',$_SESSION['mpr_entry']['idcard']);
    if(isset($_SESSION['mpr_entry']['passport']))
        shn_form_label('Passport Number',$_SESSION['mpr_entry']['passport']);
    if(isset($_SESSION['mpr_entry']['drv_license']))
        shn_form_label('Driving License',$_SESSION['mpr_entry']['drv_license']);
    if($identity_section)
        shn_form_fsclose();

    //Basic Details
    if(isset($_SESSION['mpr_entry']['full_name']) ||
            isset($_SESSION['mpr_entry']['family_name']) ||
            isset($_SESSION['mpr_entry']['local_name']) ||
            isset($_SESSION['mpr_entry']['dob']) ||
            isset($_SESSION['mpr_entry']['opt_age_group']) ||
            isset($_SESSION['mpr_entry']['opt_gender']) ||
            isset($_SESSION['mpr_entry']['opt_marital_status']) ||
            isset($_SESSION['mpr_entry']['opt_religion']) ||
            isset($_SESSION['mpr_entry']['opt_race']) ) {
        shn_form_fsopen("Basic Details");
        $basic_section = true;
    }
    if(isset($_SESSION['mpr_entry']['full_name']))
        shn_form_label('Full Name',$_SESSION['mpr_entry']['full_name']);
    if(isset($_SESSION['mpr_entry']['family_name']))
        shn_form_label('Family Name',$_SESSION['mpr_entry']['family_name']);
    if(isset($_SESSION['mpr_entry']['local_name']))
        shn_form_label('Local Name',$_SESSION['mpr_entry']['local_name']);
    if(isset($_SESSION['mpr_entry']['dob']))
        shn_form_label('Date of Birth',$_SESSION['mpr_entry']['dob']);
    if(isset($_SESSION['mpr_entry']['opt_age_group']))
        shn_form_label('Age Group',shn_get_field_opt($_SESSION['mpr_entry']['opt_age_group'],'opt_age_group'));
    if(isset($_SESSION['mpr_entry']['opt_gender']))
        shn_form_label('Gender',shn_get_field_opt($_SESSION['mpr_entry']['opt_gender'],'opt_gender'));
    if(isset($_SESSION['mpr_entry']['opt_marital_status']))
        shn_form_label('Marital Status',shn_get_field_opt($_SESSION['mpr_entry']['opt_marital_status'],'opt_marital_status'));
    if(isset($_SESSION['mpr_entry']['opt_religion']))
        shn_form_label('Religion',shn_get_field_opt($_SESSION['mpr_entry']['opt_religion'],'opt_religion'));
    if(isset($_SESSION['mpr_entry']['opt_race']))
        shn_form_label('Race',shn_get_field_opt($_SESSION['mpr_entry']['opt_race'],'opt_race'));
    if($basic_section)
        shn_form_fsclose();

    //Physical Details
    if(isset($_SESSION['mpr_entry']['opt_eye_color']) ||
            isset($_SESSION['mpr_entry']['opt_skin_color']) ||
            isset($_SESSION['mpr_entry']['opt_hair_color']) ||
            isset($_SESSION['mpr_entry']['height']) ||
            isset($_SESSION['mpr_entry']['weight']) || 
            isset($_SESSION['mpr_entry']['physical_comments'])) {
        shn_form_fsopen("Physical Details");
        $physical_section = true;
    }
    if(isset($_SESSION['mpr_entry']['opt_eye_color']))
        shn_form_label('Eye Colour',shn_get_field_opt($_SESSION['mpr_entry']['opt_eye_color'],'opt_eye_color'));
    if(isset($_SESSION['mpr_entry']['opt_skin_color']))
        shn_form_label('Skin Colour',shn_get_field_opt($_SESSION['mpr_entry']['opt_skin_color'],'opt_skin_color'));
    if(isset($_SESSION['mpr_entry']['opt_hair_color']))
        shn_form_label('Hair Colour',shn_get_field_opt($_SESSION['mpr_entry']['opt_hair_color'],'opt_hair_color'));
    if(isset($_SESSION['mpr_entry']['height']))
        shn_form_label('Height',$_SESSION['mpr_entry']['height']);
    if(isset($_SESSION['mpr_entry']['weight']))
        shn_form_label('Weight',$_SESSION['mpr_entry']['weight']);
    if(isset($_SESSION['mpr_entry']['physical_comments']))
        shn_form_label('Comments',$_SESSION['mpr_entry']['physical_comments']);
    if($physical_section)
        shn_form_fsclose();

    //Contact Details
    if(isset($_SESSION['mpr_entry']['address']) || 
            isset($_SESSION['mpr_entry']['zip']) ||
            isset($_SESSION['mpr_entry']['phone']) ||
            isset($_SESSION['mpr_entry']['mobile']) ){
        shn_form_fsopen("Contact Details");
        $contact_section = true;
    }
    if(isset($_SESSION['mpr_entry']['address']))
        shn_form_label('Address',$_SESSION['mpr_entry']['address']);
    if(isset($_SESSION['mpr_entry']['zip']))
        shn_form_label('Postal Code',$_SESSION['mpr_entry']['zip']);
    if(isset($_SESSION['mpr_entry']['phone']))
        shn_form_label('Home Phone',$_SESSION['mpr_entry']['phone']);
    if(isset($_SESSION['mpr_entry']['mobile']))
        shn_form_label('Mobile',$_SESSION['mpr_entry']['mobile']);
    if($contact_section)
        shn_form_fsclose();

    if(isset($_SESSION['mpr_entry']['opt_blood_type']) ||
            isset($_SESSION['mpr_entry']['last_seen']) ||
            isset($_SESSION['mpr_entry']['last_clothing']) ||
            isset($_SESSION['mpr_entry']['comments']) ) {
        shn_form_fsopen("Other Details");
        $other_section = true;
    }
    //Other Details
    if(isset($_SESSION['mpr_entry']['opt_blood_type']))
        shn_form_label('Blood Type',shn_get_field_opt($_SESSION['mpr_entry']['opt_blood_type'],'opt_blood_type'));
    if(isset($_SESSION['mpr_entry']['last_seen']))
        shn_form_label('Last Seen',$_SESSION['mpr_entry']['last_seen']);
    if(isset($_SESSION['mpr_entry']['last_clothing']))
        shn_form_label('Last Clothing',$_SESSION['mpr_entry']['last_clothing']);
    if(isset($_SESSION['mpr_entry']['comments']))
        shn_form_label('Comments',$_SESSION['mpr_entry']['comments']);
    if($other_section)
        shn_form_fsclose();

    //Reporting Person
    shn_form_fsopen("Reporting Person");

    if(isset($_SESSION['mpr_entry']['rep_full_name']))
        shn_form_label('Name',$_SESSION['mpr_entry']['rep_full_name']);
    if(isset($_SESSION['mpr_entry']['rep_relation']))
        shn_form_label('Relation',$_SESSION['mpr_entry']['rep_relation']);
    if(isset($_SESSION['mpr_entry']['rep_address']))
        shn_form_label('Address',$_SESSION['mpr_entry']['rep_address']);
    if(isset($_SESSION['mpr_entry']['rep_phone']))
        shn_form_label('Phone',$_SESSION['mpr_entry']['rep_phone']);
    if(isset($_SESSION['mpr_entry']['rep_email']))
        shn_form_label('Email',$_SESSION['mpr_entry']['rep_email']);

    shn_form_fsclose();

 
    shn_form_fsopen("Confirm");
?>
    <p>Is the information that you've entered correct?</p>
<?php
    shn_form_submit('Next');
    shn_form_fsclose();
    shn_form_fclose();
}

function shn_mpr_editmp_commit()
{
    // $update_array[<field_name>] = value
    global $global;

    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //phonetic flush and refill
    $global['db']->Execute("DELETE FROM phonetic_word WHERE pgl_uuid='{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_entry']['full_name'])){
        $update_array['full_name'] = $_SESSION['mpr_entry']['full_name'];
        shn_db_insert_phonetic($update_array['full_name'],$update_array['p_uuid']);
    }
    if(isset($_SESSION['mpr_entry']['family_name'])){
        $update_array['family_name'] = $_SESSION['mpr_entry']['family_name'];
        shn_db_insert_phonetic($update_array['family_name'],$update_array['p_uuid']);
    }
    if(isset($_SESSION['mpr_entry']['local_name'])){
        $update_array['l10n_name'] = $_SESSION['mpr_entry']['local_name'];
        shn_db_insert_phonetic($update_array['l10n_name'],$update_array['p_uuid']);
    }

    //update the person_uuid table
    shn_db_update($update_array,'person_uuid'," WHERE p_uuid = '{$update_array['p_uuid']}'");
    //reset $update_array 
    $update_array = null;

    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //Identity do a flush and refill
    $global['db']->Execute("DELETE FROM identity_to_person WHERE p_uuid = '{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_entry']['idcard'])) {
        $update_array['serial'] = $_SESSION['mpr_entry']['idcard'];
        $update_array['opt_id_type'] = 'nic';
        shn_db_insert($update_array,'identity_to_person');
    }
    if(isset($_SESSION['mpr_entry']['passport'])) {
        $update_array['serial'] = $_SESSION['mpr_entry']['passport'];
        $update_array['opt_id_type'] = 'pas';
        shn_db_insert($update_array,'identity_to_person');
    }
    if(isset($_SESSION['mpr_entry']['drv_license'])) {
        $update_array['serial'] = $_SESSION['mpr_entry']['drv_license'];
        $update_array['opt_id_type'] = 'dln';
        shn_db_insert($update_array,'identity_to_person');
    }
    //reset $update_array 
    $update_array = null;

    //Contacts
    $update_array['poc_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM location_details WHERE poc_uuid = '{$update_array['poc_uuid']}'");
    if(isset($_SESSION['mpr_entry']['address'])){
        $update_array['location_id'] = '0';
        $update_array['address'] = $_SESSION['mpr_entry']['address'];
        $update_array['opt_person_loc_type'] = 'hom';
    }
    if(isset($_SESSION['mpr_entry']['zip']))
        $update_array['postcode'] = $_SESSION['mpr_entry']['zip'];

    shn_db_insert($update_array,'location_details');
    //reset $update_array 
    $update_array = null;

    $update_array['pgoc_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM contact WHERE pgoc_uuid = '{$update_array['pgoc_uuid']}'");
    if(isset($_SESSION['mpr_entry']['phone'])){
        $update_array['contact_value'] = $_SESSION['mpr_entry']['phone'];
        $update_array['opt_contact_type'] = 'curr';
        
    }
    shn_db_insert($update_array,'contact');
    //reset $update_array 
    $update_array = null;

    $update_array['pgoc_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    if(isset($_SESSION['mpr_entry']['mobile'])){
        $update_array['contact_value'] = $_SESSION['mpr_entry']['mobile'];
        $update_array['opt_contact_type'] = 'cmob';
    }
    shn_db_insert($update_array,'contact');
    //reset $update_array 
    $update_array = null;

    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_physical WHERE p_uuid = '{$update_array['p_uuid']}'");
    //Physical Details : person_physical
    if(isset($_SESSION['mpr_entry']['opt_eye_color']))
        $update_array['opt_eye_color'] = $_SESSION['mpr_entry']['opt_eye_color'];
    if(isset($_SESSION['mpr_entry']['opt_skin_color']))
        $update_array['opt_skin_color'] = $_SESSION['mpr_entry']['opt_skin_color'];
    if(isset($_SESSION['mpr_entry']['opt_hair_color']))
        $update_array['opt_hair_color'] = $_SESSION['mpr_entry']['opt_hair_color'];
    if(isset($_SESSION['mpr_entry']['height']))
        $update_array['height'] = $_SESSION['mpr_entry']['height'];
    if(isset($_SESSION['mpr_entry']['weight']))
        $update_array['weight'] = $_SESSION['mpr_entry']['weight'];
    if(isset($_SESSION['mpr_entry']['opt_blood_type']))
        $update_array['opt_blood_type'] = $_SESSION['mpr_entry']['opt_blood_type'];
    if(isset($_SESSION['mpr_entry']['physical_comments']))
        $update_array['comments'] = $_SESSION['mpr_entry']['physical_comments'];

    shn_db_insert($update_array,'person_physical');
    //reset $update_array 
    $update_array = null;


    //Other Details
    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_missing WHERE p_uuid = '{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_entry']['last_seen']))
        $update_array['last_seen'] = $_SESSION['mpr_entry']['last_seen'];
    if(isset($_SESSION['mpr_entry']['last_clothing']))
        $update_array['last_clothing'] = $_SESSION['mpr_entry']['last_clothing'];
    if(isset($_SESSION['mpr_entry']['comments']))
        $update_array['comments'] = $_SESSION['mpr_entry']['comments'];

    shn_db_insert($update_array,'person_missing');
    //reset $update_array 
    $update_array = null;

    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //person_details        
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_details WHERE p_uuid = '{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_entry']['dob']))
        $update_array['birth_date'] = $_SESSION['mpr_entry']['dob'];
    if(isset($_SESSION['mpr_entry']['opt_age_group']))
        $update_array['opt_age_group'] = $_SESSION['mpr_entry']['opt_age_group'];
    if(isset($_SESSION['mpr_entry']['opt_gender']))
        $update_array['opt_gender'] = $_SESSION['mpr_entry']['opt_gender'];
    if(isset($_SESSION['mpr_entry']['opt_marital_status']))
        $update_array['opt_marital_status'] = $_SESSION['mpr_entry']['opt_marital_status'];
    if(isset($_SESSION['mpr_entry']['opt_religion']))
        $update_array['opt_religion'] = $_SESSION['mpr_entry']['opt_religion'];
    if(isset($_SESSION['mpr_entry']['opt_race']))
        $update_array['opt_race'] = $_SESSION['mpr_entry']['opt_race'];
    shn_db_insert($update_array,'person_details');
    //reset $update_array 
    $update_array = null;

    
    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_status WHERE p_uuid = '{$update_array['p_uuid']}'");
    //Insert Into person_status mis
    $update_array['opt_status'] = $_SESSION['mpr_entry']['opt_status'];
    shn_db_insert($update_array,'person_status');
    //reset $update_array 
    $update_array = null;

    //Reported person entry 
    $update_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_to_report WHERE p_uuid = '{$update_array['p_uuid']}'");
    //Reporting Person
    if(isset($_SESSION['mpr_entry']['rep_full_name']))
        $update_array['name'] = $_SESSION['mpr_entry']['rep_full_name'];
    if(isset($_SESSION['mpr_entry']['rep_relation']))
        $update_array['relation'] = $_SESSION['mpr_entry']['rep_relation'];
    if(isset($_SESSION['mpr_entry']['rep_address']))
        $update_array['address'] = $_SESSION['mpr_entry']['rep_address'];
    if(isset($_SESSION['mpr_entry']['rep_phone']))
        $update_array['phone'] = $_SESSION['mpr_entry']['rep_phone'];
    if(isset($_SESSION['mpr_entry']['rep_email']))
        $update_array['email'] = $_SESSION['mpr_entry']['rep_email'];

    shn_db_insert($update_array,'person_to_report');
    //reset $update_array 
    $update_array = null;
    
    //go back to the main menu
    shn_mpr_default();    
}

?>
