<?php

/* {{{ Load Informations 

/**
 * shn_mpr_editmp_load 
 * 
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_mpr_editmp_load($p_uuid)
{
    global $global;

    //@todo: check existance
    $_SESSION['mpr_edit']['entry']['p_uuid'] = $p_uuid;

    //Status
    $sql = "SELECT opt_status FROM person_status WHERE p_uuid = '$p_uuid'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['opt_status'] = $rs->fields[0];
   
    //identity_to_person
    //identity card
    $sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'nic'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['idcard'] = $rs->fields[0];
    //passport
    $sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'pas'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['passport'] = $rs->fields[0];
    //Driving License
    $sql = "SELECT serial FROM identity_to_person WHERE p_uuid = '$p_uuid' AND opt_id_type = 'dln'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['drv_license'] = $rs->fields[0];

    //Basic Details, Physical Details, Other Details,  
    //person_uuid
    $sql = "SELECT 
                a.full_name, a.family_name, a.l10n_name,
                b.birth_date, b.opt_age_group, b.opt_race, b.opt_religion, 
                b.opt_marital_status, b.opt_gender,
                c.opt_blood_type, c.height, c.weight, c.opt_eye_color, c.opt_skin_color,
                c.opt_hair_color, c.comments as physical_comments, 
                d.last_seen, d.last_clothing, d.comments,
                e.address, e.postcode, e.location_id
            FROM person_uuid a
            LEFT OUTER JOIN person_details b USING (p_uuid)
            LEFT OUTER JOIN person_physical c USING (p_uuid)
            LEFT OUTER JOIN person_missing d USING (p_uuid)
            LEFT OUTER JOIN location_details e ON (e.poc_uuid=a.p_uuid)
            WHERE a.p_uuid = '$p_uuid'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['full_name'] = $rs->fields['full_name'];
    $_SESSION['mpr_edit']['entry']['family_name'] = $rs->fields['family_name'];
    $_SESSION['mpr_edit']['entry']['local_name'] = $rs->fields['l10n_name'];
    $_SESSION['mpr_edit']['entry']['dob'] = $rs->fields['birth_date'];
    $_SESSION['mpr_edit']['entry']['opt_age_group'] = $rs->fields['opt_age_group'];
    $_SESSION['mpr_edit']['entry']['opt_race'] = $rs->fields['opt_race'];
    $_SESSION['mpr_edit']['entry']['opt_religion'] = $rs->fields['opt_religion'];
    $_SESSION['mpr_edit']['entry']['opt_marital_status'] = $rs->fields['opt_marital_status'];
    $_SESSION['mpr_edit']['entry']['opt_blood_type'] = $rs->fields['opt_blood_type'];
    $_SESSION['mpr_edit']['entry']['height'] = htmlspecialchars($rs->fields['height']);
    $_SESSION['mpr_edit']['entry']['weight'] = htmlspecialchars($rs->fields['weight']);
    $_SESSION['mpr_edit']['entry']['opt_eye_color'] = $rs->fields['opt_eye_color'];
    $_SESSION['mpr_edit']['entry']['opt_skin_color'] = $rs->fields['opt_skin_color'];
    $_SESSION['mpr_edit']['entry']['opt_hair_color'] = $rs->fields['opt_hair_color'];
    $_SESSION['mpr_edit']['entry']['physical_comments'] = $rs->fields['physical_comments'];
    $_SESSION['mpr_edit']['entry']['last_seen'] = $rs->fields['last_seen'];
    $_SESSION['mpr_edit']['entry']['last_clothing'] = $rs->fields['last_clothing'];
    $_SESSION['mpr_edit']['entry']['comments'] = $rs->fields['comments'];
    $_SESSION['mpr_edit']['entry']['address'] = $rs->fields['address'];
    $_SESSION['mpr_edit']['entry']['location_id'] = $rs->fields['location_id'];
    $_SESSION['mpr_edit']['entry']['zip'] = $rs->fields['postcode'];
    $_SESSION['mpr_edit']['entry']['opt_gender'] = $rs->fields['opt_gender'];

    //Home phone
    $sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'curr'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['phone'] = $rs->fields[0];

    //Mobile phone
    $sql = "SELECT contact_value FROM contact WHERE pgoc_uuid = '$p_uuid' AND opt_contact_type = 'cmob'";
    $rs = $global['db']->Execute($sql);
    $_SESSION['mpr_edit']['entry']['mobile'] = $rs->fields[0];
}
/* }}} */

/* {{{ Edit Form */ 

/**
 * shn_mpr_editmp_entry 
 * 
 * @param mixed $errors 
 * @access public
 * @return void
 */
function shn_mpr_editmp_entry($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("editmp",null);

    shn_form_hidden(array('seq'=>'entry'));

    shn_form_fsopen('Status');
    shn_form_opt_select('opt_status','Change the status','',array('value'=>$_SESSION['mpr_edit']['entry']['opt_status']));
    shn_form_fsclose();

    shn_form_fsopen('Identity');
    shn_form_text('Identity Card Number','idcard','size="30"',array('value'=>$_SESSION['mpr_edit']['entry']['idcard']));
    shn_form_text('Passport Number','passport','size="30"',array('value'=>$_SESSION['mpr_edit']['entry']['passport']));
    shn_form_text('Driving License','drv_license','size="30"',array('value'=>$_SESSION['mpr_edit']['entry']['drv_license']));
    shn_form_fsclose();

    shn_form_fsopen("Basic Details");
?>
<p>Please enter any of the following details on the person:</p> 
<?php

    shn_form_text('Full Name','full_name','size="40"',array('value'=>$_SESSION['mpr_edit']['entry']['full_name']));
    shn_form_text('Family Name','family_name','size="40"',array('value'=>$_SESSION['mpr_edit']['entry']['family_name']));
    shn_form_text('Local Name','local_name','size="40"',array('value'=>$_SESSION['mpr_edit']['entry']['local_name']));
    shn_form_text('Date of Birth   (YYYY-MM-DD)','dob','size=8',array('value'=>$_SESSION['mpr_edit']['entry']['dob']));
    shn_form_opt_select("opt_age_group","Age Group",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_age_group']));
    shn_form_opt_select("opt_gender","Gender",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_gender']));
    shn_form_opt_select("opt_marital_status","Marital Status",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_marital_status']));
    shn_form_opt_select("opt_religion","Religion",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_religion']));
    shn_form_opt_select("opt_race","Race",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_race']));

    shn_form_fsclose();

    shn_form_fsopen("Contact Details");
    shn_form_textarea("Address","address",'',array('value'=>$_SESSION['mpr_edit']['entry']['address']));
    shn_form_text('Postal Code','zip','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['zip']));
    shn_form_text('Home Phone','phone','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['phone']));
    shn_form_text('Mobile','mobile','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['mobile']));
    shn_form_fsclose();
    
    global $global;
    global $conf;


    include_once($global['approot']."/inc/lib_location.inc");
    /* This hack should be integrated with 
        the lib_location
    */
    //Starts
        $i = $conf['mod_mpr']['location']['lower_limit'];
        while((! isset($_POST[$i])) &&
                $i > $conf['mod_mpr']['location']['upper_limit'] )
            $i--;
    //Ends
    $selected_loc_id = (isset($_POST[$i]) ? $_POST[$i] : $_SESSION['mpr_edit']['entry']['location_id']);
    shn_location_form($conf['mod_mpr']['location']['upper_limit'],
                        $conf['mod_mpr']['location']['lower_limit'],
                        $selected_loc_id); 

    shn_form_fsopen("Physical Details");
    shn_form_opt_select("opt_eye_color","Eye Colour",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_eye_color']));
    shn_form_opt_select("opt_skin_color","Skin Colour",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_skin_color']));
    shn_form_opt_select("opt_hair_color","Hair Colour",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_hair_color']));
    shn_form_text('Height','height','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['height']));
    shn_form_text('Weight','weight','size="10"',array('value'=>$_SESSION['mpr_edit']['entry']['weight']));
    shn_form_textarea('Comments','physical_comments','',array('value'=>$_SESSION['mpr_edit']['entry']['physical_comments']));
    shn_form_fsclose();

    shn_form_fsopen("Other Details");
    shn_form_opt_select("opt_blood_type","Blood Type",'',array('value'=>$_SESSION['mpr_edit']['entry']['opt_blood_type']));
    shn_form_textarea('Last Seen','last_seen','',array('value'=>$_SESSION['mpr_edit']['entry']['last_seen']));
    shn_form_textarea('Last Clothing','last_clothing','',array('value'=>$_SESSION['mpr_edit']['entry']['last_clothing']));
    shn_form_textarea('Comments','comments','',array('value'=>$_SESSION['mpr_edit']['entry']['comments']));
    shn_form_fsclose();

    shn_form_submit('Next');
    shn_form_fclose();
}
/* }}} */

/* {{{ Edit Validation */
/**
 * shn_mpr_editmp_validate 
 * 
 * @access public
 * @return void
 */
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

    if(isset($local_post['dob']) && ! shn_valid_date($local_post['dob'])){
        add_error(_("Invalid Date of Birth"));
        $error_flag=true;
    }

    //set session
    $local_post['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //clean
    session_unset($_SESSION['mpr_edit']['entry']);
    $_SESSION['mpr_edit']['entry']=$local_post;

    if($error_flag)
        return false;
    else{
        return true;
    }
} 
/* }}} */

/* {{{ Edit Upload Form */
/**
 * shn_mpr_editmp_upload 
 * 
 * @param mixed $errors 
 * @access public
 * @return void
 */
function shn_mpr_editmp_upload($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("editmp",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'upload_pic'));
    shn_form_fsopen('Replace Current Picture');
    shn_show_thumb($_SESSION['mpr_edit']['entry']['p_uuid']);
?>
    <br />
<?
    shn_form_upload("Upload Picture","picture");
    shn_form_submit('Next');
    shn_form_fsclose();
    shn_form_fclose();
}
/* }}} */

/* {{{ Edit Upload */
/**
 * shn_mpr_editmp_upload_pic 
 * 
 * @access public
 * @return void
 */
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
    $uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_edit']['entry']['p_uuid'].$ext;
    move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
    $desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_edit']['entry']['p_uuid'].$ext; 
    //make thumb 100X100 or some thing like that ;-)
    shn_image_resize($uploadfile,$desc_path,100,100);
    return true;
}
/* }}} */

/* {{{ Edit Confirm */
/**
 * shn_mpr_editmp_confirm 
 * 
 * @access public
 * @return void
 */
function shn_mpr_editmp_confirm()
{
    var_dump($_SESSION['mpr_edit']['entry']);
    global $global;
    global $conf;

    shn_form_fopen("editmp",null);
    shn_form_fsopen("Person");
    shn_form_hidden(array('seq'=>'commit'));
    shn_show_thumb($_SESSION['mpr_edit']['entry']['p_uuid']);
?>
    <br />
<?php
    //Status
    shn_form_label(shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_status'],'opt_status'),'');
    shn_form_fsclose();
    //Identity
    if(isset($_SESSION['mpr_edit']['entry']['idcard']) ||
            isset($_SESSION['mpr_edit']['entry']['passport']) ||
            isset($_SESSION['mpr_edit']['entry']['drv_license']) ) {
        shn_form_fsopen("Identity");
        $identity_section = true;
    }
    if(isset($_SESSION['mpr_edit']['entry']['idcard']))
        shn_form_label('Identity Card Number',$_SESSION['mpr_edit']['entry']['idcard']);
    if(isset($_SESSION['mpr_edit']['entry']['passport']))
        shn_form_label('Passport Number',$_SESSION['mpr_edit']['entry']['passport']);
    if(isset($_SESSION['mpr_edit']['entry']['drv_license']))
        shn_form_label('Driving License',$_SESSION['mpr_edit']['entry']['drv_license']);
    if($identity_section)
        shn_form_fsclose();

    //Basic Details
    if(isset($_SESSION['mpr_edit']['entry']['full_name']) ||
            isset($_SESSION['mpr_edit']['entry']['family_name']) ||
            isset($_SESSION['mpr_edit']['entry']['local_name']) ||
            isset($_SESSION['mpr_edit']['entry']['dob']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_age_group']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_gender']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_marital_status']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_religion']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_race']) ) {
        shn_form_fsopen("Basic Details");
        $basic_section = true;
    }
    if(isset($_SESSION['mpr_edit']['entry']['full_name']))
        shn_form_label('Full Name',$_SESSION['mpr_edit']['entry']['full_name']);
    if(isset($_SESSION['mpr_edit']['entry']['family_name']))
        shn_form_label('Family Name',$_SESSION['mpr_edit']['entry']['family_name']);
    if(isset($_SESSION['mpr_edit']['entry']['local_name']))
        shn_form_label('Local Name',$_SESSION['mpr_edit']['entry']['local_name']);
    if(isset($_SESSION['mpr_edit']['entry']['dob']))
        shn_form_label('Date of Birth',$_SESSION['mpr_edit']['entry']['dob']);
    if(isset($_SESSION['mpr_edit']['entry']['opt_age_group']))
        shn_form_label('Age Group',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_age_group'],'opt_age_group'));
    if(isset($_SESSION['mpr_edit']['entry']['opt_gender']))
        shn_form_label('Gender',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_gender'],'opt_gender'));
    if(isset($_SESSION['mpr_edit']['entry']['opt_marital_status']))
        shn_form_label('Marital Status',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_marital_status'],'opt_marital_status'));
    if(isset($_SESSION['mpr_edit']['entry']['opt_religion']))
        shn_form_label('Religion',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_religion'],'opt_religion'));
    if(isset($_SESSION['mpr_edit']['entry']['opt_race']))
        shn_form_label('Race',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_race'],'opt_race'));
    if($basic_section)
        shn_form_fsclose();

    //Physical Details
    if(isset($_SESSION['mpr_edit']['entry']['opt_eye_color']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_skin_color']) ||
            isset($_SESSION['mpr_edit']['entry']['opt_hair_color']) ||
            isset($_SESSION['mpr_edit']['entry']['height']) ||
            isset($_SESSION['mpr_edit']['entry']['weight']) || 
            isset($_SESSION['mpr_edit']['entry']['physical_comments'])) {
        shn_form_fsopen("Physical Details");
        $physical_section = true;
    }
    if(isset($_SESSION['mpr_edit']['entry']['opt_eye_color']))
        shn_form_label('Eye Colour',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_eye_color'],'opt_eye_color'));
    if(isset($_SESSION['mpr_edit']['entry']['opt_skin_color']))
        shn_form_label('Skin Colour',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_skin_color'],'opt_skin_color'));
    if(isset($_SESSION['mpr_edit']['entry']['opt_hair_color']))
        shn_form_label('Hair Colour',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_hair_color'],'opt_hair_color'));
    if(isset($_SESSION['mpr_edit']['entry']['height']))
        shn_form_label('Height',$_SESSION['mpr_edit']['entry']['height']);
    if(isset($_SESSION['mpr_edit']['entry']['weight']))
        shn_form_label('Weight',$_SESSION['mpr_edit']['entry']['weight']);
    if(isset($_SESSION['mpr_edit']['entry']['physical_comments']))
        shn_form_label('Comments',$_SESSION['mpr_edit']['entry']['physical_comments']);
    if($physical_section)
        shn_form_fsclose();

    //Contact Details
#    if(isset($_SESSION['mpr_edit']['entry']['address']) || 
#            isset($_SESSION['mpr_edit']['entry']['zip']) ||
#            isset($_SESSION['mpr_edit']['entry']['phone']) ||
#            isset($_SESSION['mpr_edit']['entry']['mobile']) ){
#        shn_form_fsopen("Contact Details");
#        $contact_section = true;
#    }
    shn_form_fsopen("Contact Details");
    $contact_section = true;

    if(isset($_SESSION['mpr_edit']['entry']['address']))
        shn_form_label('Address',$_SESSION['mpr_edit']['entry']['address']);

    /* This hack should also include in the
        lib_location
    */
    //Starts
        $i = $conf['mod_mpr']['location']['upper_limit'] - 1;
        while( $i < $conf['mod_mpr']['location']['lower_limit'] ) {
            $i++;
            if(isset($_SESSION['mpr_edit']['entry'][$i])){
                $sql = " SELECT location.name , field_options.option_description FROM location ".
                    " INNER JOIN field_options ON field_options.option_code = location.opt_location_type " .
                    " WHERE location.opt_location_type = '$i' AND " .
                    " location.location_id = '{$_SESSION['mpr_edit']['entry'][$i]}' ";
                $result = $global['db']->GetRow($sql);
                shn_form_label($result['option_description'] , $result['name']);
            }

        }
    //Ends

    if(isset($_SESSION['mpr_edit']['entry']['zip']))
        shn_form_label('Postal Code',$_SESSION['mpr_edit']['entry']['zip']);
    if(isset($_SESSION['mpr_edit']['entry']['phone']))
        shn_form_label('Home Phone',$_SESSION['mpr_edit']['entry']['phone']);
    if(isset($_SESSION['mpr_edit']['entry']['mobile']))
        shn_form_label('Mobile',$_SESSION['mpr_edit']['entry']['mobile']);
    if($contact_section)
        shn_form_fsclose();

    if(isset($_SESSION['mpr_edit']['entry']['opt_blood_type']) ||
            isset($_SESSION['mpr_edit']['entry']['last_seen']) ||
            isset($_SESSION['mpr_edit']['entry']['last_clothing']) ||
            isset($_SESSION['mpr_edit']['entry']['comments']) ) {
        shn_form_fsopen("Other Details");
        $other_section = true;
    }
    //Other Details
    if(isset($_SESSION['mpr_edit']['entry']['opt_blood_type']))
        shn_form_label('Blood Type',shn_get_field_opt($_SESSION['mpr_edit']['entry']['opt_blood_type'],'opt_blood_type'));
    if(isset($_SESSION['mpr_edit']['entry']['last_seen']))
        shn_form_label('Last Seen',$_SESSION['mpr_edit']['entry']['last_seen']);
    if(isset($_SESSION['mpr_edit']['entry']['last_clothing']))
        shn_form_label('Last Clothing',$_SESSION['mpr_edit']['entry']['last_clothing']);
    if(isset($_SESSION['mpr_edit']['entry']['comments']))
        shn_form_label('Comments',$_SESSION['mpr_edit']['entry']['comments']);
    if($other_section)
        shn_form_fsclose();

    //Reporting Person
    shn_form_fsopen("Reporting People");
    global $global;
    require_once($global['approot'].'mod/mpr/search.inc');
    $arr =
        shn_mpr_search_get_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
?>
<DIV ID="result">
<TABLE>
<THEAD>
    <TD>Picture</TD><TD>Name</TD><TD>Relationship</TD>
</THEAD>
<?php
    foreach($arr as $tracker){
?>
<TR>
    <TD><?php shn_show_thumb($tracker['p_uuid']); ?></TD>
    <TD><?= $tracker['full_name']; ?>
    </TD>
    <TD><?= $tracker['relation']; ?>
    </TD>
</TR>
<?php
    }
?>
</TABLE>
</DIV>
<?php
    shn_form_fsclose();

 
    shn_form_fsopen("Confirm");
?>
    <p>Is the information that you've entered correct?</p>
<?php
    shn_form_submit('Next');
    shn_form_fsclose();
    shn_form_fclose();
}
/* }}} */

/* {{{ Edit Commit */
/**
 * shn_mpr_editmp_commit 
 * 
 * @access public
 * @return void
 */
function shn_mpr_editmp_commit()
{
    // $update_array[<field_name>] = value
    global $global;
    global $conf;

    $update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //phonetic flush and refill
    $global['db']->Execute("DELETE FROM phonetic_word WHERE pgl_uuid='{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_edit']['entry']['full_name'])){
        $update_array['full_name'] = $_SESSION['mpr_edit']['entry']['full_name'];
        shn_db_insert_phonetic($update_array['full_name'],$update_array['p_uuid']);
    }
    if(isset($_SESSION['mpr_edit']['entry']['family_name'])){
        $update_array['family_name'] = $_SESSION['mpr_edit']['entry']['family_name'];
        shn_db_insert_phonetic($update_array['family_name'],$update_array['p_uuid']);
    }
    if(isset($_SESSION['mpr_edit']['entry']['local_name'])){
        $update_array['l10n_name'] = $_SESSION['mpr_edit']['entry']['local_name'];
        shn_db_insert_phonetic($update_array['l10n_name'],$update_array['p_uuid']);
    }

    //update the person_uuid table
    shn_db_update($update_array,'person_uuid'," WHERE p_uuid = '{$update_array['p_uuid']}'");
    //reset $update_array 
    $update_array = null;

    $update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //Identity do a flush and refill
    $global['db']->Execute("DELETE FROM identity_to_person WHERE p_uuid = '{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_edit']['entry']['idcard'])) {
        $update_array['serial'] = $_SESSION['mpr_edit']['entry']['idcard'];
        $update_array['opt_id_type'] = 'nic';
        shn_db_insert($update_array,'identity_to_person');
    }
    if(isset($_SESSION['mpr_edit']['entry']['passport'])) {
        $update_array['serial'] = $_SESSION['mpr_edit']['entry']['passport'];
        $update_array['opt_id_type'] = 'pas';
        shn_db_insert($update_array,'identity_to_person');
    }
    if(isset($_SESSION['mpr_edit']['entry']['drv_license'])) {
        $update_array['serial'] = $_SESSION['mpr_edit']['entry']['drv_license'];
        $update_array['opt_id_type'] = 'dln';
        shn_db_insert($update_array,'identity_to_person');
    }
    //reset $update_array 
    $update_array = null;

    //Contacts
    $update_array['poc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM location_details WHERE poc_uuid = '{$update_array['poc_uuid']}'");

    
    $update_array['opt_person_loc_type'] = 'hom';
    if(isset($_SESSION['mpr_edit']['entry']['address']))
        $update_array['address'] = $_SESSION['mpr_edit']['entry']['address'];

    /* This hack should be integrated with 
        the lib_location
    */
    //Starts
        $i = $conf['mod_mpr']['location']['lower_limit'];
        while((! isset($_SESSION['mpr_edit']['entry'][$i])) &&
                $i > $conf['mod_mpr']['location']['upper_limit'] )
            $i--;
    //Ends
    if(isset($_SESSION['mpr_edit']['entry'][$i]))
        $update_array['location_id'] = $_SESSION['mpr_edit']['entry'][$i];
 
    if(isset($_SESSION['mpr_edit']['entry']['zip']))
        $update_array['postcode'] = $_SESSION['mpr_edit']['entry']['zip'];

    shn_db_insert($update_array,'location_details');
    //reset $update_array 
    $update_array = null;

    $update_array['pgoc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM contact WHERE pgoc_uuid = '{$update_array['pgoc_uuid']}'");
    if(isset($_SESSION['mpr_edit']['entry']['phone'])){
        $update_array['contact_value'] = $_SESSION['mpr_edit']['entry']['phone'];
        $update_array['opt_contact_type'] = 'curr';
        
    }
    shn_db_insert($update_array,'contact');
    //reset $update_array 
    $update_array = null;

    $update_array['pgoc_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    if(isset($_SESSION['mpr_edit']['entry']['mobile'])){
        $update_array['contact_value'] = $_SESSION['mpr_edit']['entry']['mobile'];
        $update_array['opt_contact_type'] = 'cmob';
    }
    shn_db_insert($update_array,'contact');
    //reset $update_array 
    $update_array = null;

    $update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_physical WHERE p_uuid = '{$update_array['p_uuid']}'");
    //Physical Details : person_physical
    if(isset($_SESSION['mpr_edit']['entry']['opt_eye_color']))
        $update_array['opt_eye_color'] = $_SESSION['mpr_edit']['entry']['opt_eye_color'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_skin_color']))
        $update_array['opt_skin_color'] = $_SESSION['mpr_edit']['entry']['opt_skin_color'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_hair_color']))
        $update_array['opt_hair_color'] = $_SESSION['mpr_edit']['entry']['opt_hair_color'];
    if(isset($_SESSION['mpr_edit']['entry']['height']))
        $update_array['height'] = $_SESSION['mpr_edit']['entry']['height'];
    if(isset($_SESSION['mpr_edit']['entry']['weight']))
        $update_array['weight'] = $_SESSION['mpr_edit']['entry']['weight'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_blood_type']))
        $update_array['opt_blood_type'] = $_SESSION['mpr_edit']['entry']['opt_blood_type'];
    if(isset($_SESSION['mpr_edit']['entry']['physical_comments']))
        $update_array['comments'] = $_SESSION['mpr_edit']['entry']['physical_comments'];

    shn_db_insert($update_array,'person_physical');
    //reset $update_array 
    $update_array = null;


    //Other Details
    $update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_missing WHERE p_uuid = '{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_edit']['entry']['last_seen']))
        $update_array['last_seen'] = $_SESSION['mpr_edit']['entry']['last_seen'];
    if(isset($_SESSION['mpr_edit']['entry']['last_clothing']))
        $update_array['last_clothing'] = $_SESSION['mpr_edit']['entry']['last_clothing'];
    if(isset($_SESSION['mpr_edit']['entry']['comments']))
        $update_array['comments'] = $_SESSION['mpr_edit']['entry']['comments'];

    shn_db_insert($update_array,'person_missing');
    //reset $update_array 
    $update_array = null;

    $update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //person_details        
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_details WHERE p_uuid = '{$update_array['p_uuid']}'");
    if(isset($_SESSION['mpr_edit']['entry']['dob']))
        $update_array['birth_date'] = $_SESSION['mpr_edit']['entry']['dob'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_age_group']))
        $update_array['opt_age_group'] = $_SESSION['mpr_edit']['entry']['opt_age_group'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_gender']))
        $update_array['opt_gender'] = $_SESSION['mpr_edit']['entry']['opt_gender'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_marital_status']))
        $update_array['opt_marital_status'] = $_SESSION['mpr_edit']['entry']['opt_marital_status'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_religion']))
        $update_array['opt_religion'] = $_SESSION['mpr_edit']['entry']['opt_religion'];
    if(isset($_SESSION['mpr_edit']['entry']['opt_race']))
        $update_array['opt_race'] = $_SESSION['mpr_edit']['entry']['opt_race'];
    shn_db_insert($update_array,'person_details');
    //reset $update_array 
    $update_array = null;

    
    $update_array['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
    //flush and refill baby
    $global['db']->Execute("DELETE FROM person_status WHERE p_uuid = '{$update_array['p_uuid']}'");
    //Insert Into person_status mis
    $update_array['opt_status'] = $_SESSION['mpr_edit']['entry']['opt_status'];
    shn_db_insert($update_array,'person_status');
    //reset $update_array 
    $update_array = null;

}
/* }}} */

/* {{{ Edit Tracker */
/**
 * shn_edit_show_trackers 
 * 
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_edit_show_trackers($p_uuid)
{
    global $global;
    require_once($global['approot'].'mod/mpr/search.inc');
    
    $arr = shn_mpr_search_get_trackers($p_uuid);

    shn_form_fopen("editmp",null);

    shn_form_hidden(array('seq'=>'trackers'));
    
    shn_form_fsopen('Current Trackers');
?>
<DIV ID="result">
<TABLE>
<THEAD>
    <TD>Picture</TD><TD>Name</TD><TD>Relationship</TD><TD>Remove</TD>
</THEAD>
<?php
    foreach($arr as $tracker){
?>
<TR>
    <TD><?php shn_show_thumb($tracker['p_uuid']); ?></TD>
    <TD>
<?php echo '<a title="View" '. 
           'href="index.php?mod='.$global['module'].'&act=viewmp&id='.
            $tracker['p_uuid'].'">'.
            $tracker['full_name'].'</a><br />';
?>
    </TD>
    <TD><?= $tracker['relation']; ?>
    </TD>
    <TD><a title="Remove"
href="<?='index.php?mod='.$global['module'].
    '&act=editmp&tracker_id='.$tracker['p_uuid'].'&seq=del_tracker';
?>" 
>Click to remove the tracker</a>
    </TD>
</TR>
<?php
    }
?>
<TR>
    <TD colspan="4">
<?php
    echo '<a title="Add Tracker" '.
        'href="index.php?mod='.$global['module'].'&act=editmp&seq=add_tracker&id='.
        $p_uuid . '">'. 'Add a tracker' . '</a>';
?>
    </TD>
</TR>
</TABLE>
</DIV>
<?php
    shn_form_submit('Next');
    shn_form_fclose();
    
    
}
/* }}} */

/* {{{ Edit: Delete Tracker */
/**
 * shn_edit_del_tracker 
 * 
 * @param mixed $p_uuid 
 * @param mixed $rep_uuid 
 * @access public
 * @return void
 */
function shn_edit_del_tracker($p_uuid, $rep_uuid)
{
    global $global;
    
    $sql = "DELETE FROM person_to_report WHERE p_uuid = '$p_uuid' ".
            " AND rep_uuid = '$rep_uuid'";
    $global['db']->Execute($sql);

}
/* }}} */

?>
