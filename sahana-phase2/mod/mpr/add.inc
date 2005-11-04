<?php
//validation
switch ($_POST['seq']) {

    case 'entry':
        if(shn_mpr_addmp_validate()){
            shn_mpr_addmp_upload();
        }else
            shn_mpr_addmp_entry(true);
    break;

    case 'upload_pic' :
        if(! shn_mpr_addmp_upload_pic())
            shn_mpr_addmp_upload(true);
        else
            shn_mpr_addmp_confirm();
    break;

    case 'commit' :
        shn_mpr_addmp_commit();
    break;

    default:
        shn_mpr_addmp_entry();            

}


function shn_mpr_addmp_entry($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("addmp",null);

    shn_form_fsopen('WARNING');
?>
    <p>Please do a search and check whether the person you are looking for is already found or not</p>
<?php
    shn_form_fsclose();
    
    shn_form_hidden(array('seq'=>'entry'));

    shn_form_fsopen('Identity');
    shn_form_text('Identity Card Number','idcard','size="30"');
    shn_form_text('Passport Number','passport','size="30"');
    shn_form_text('Driving License','drv_license','size="30"');
    shn_form_fsclose();

    shn_form_fsopen("Basic Details");
?>
<p>Please enter any of the following details on the person:</p> 
<?php

    shn_form_text('Full Name','full_name','size="40"');
    shn_form_text('Family Name','family_name','size="40"');
    shn_form_text('Local Name','local_name','size="40"');
    shn_form_text('Date of Birth   (YYYY-MM-DD)','dob','size=8');
    shn_form_opt_select("opt_age_group","Age Group","" ,array('req'=>true));
    shn_form_opt_select("opt_gender","Gender");
    shn_form_opt_select("opt_marital_status","Marital Status");
    shn_form_opt_select("opt_religion","Religion");
    shn_form_opt_select("opt_race","Race");

    shn_form_fsclose();

    shn_form_fsopen("Contact Details");
    shn_form_textarea("Address","address");
    shn_form_text('Postal Code','zip','size="10"');
    shn_form_text('Home Phone','phone','size="10"');
    shn_form_text('Mobile','mobile','size="10"');
    shn_form_fsclose();

    shn_form_fsopen("Physical Details");
    shn_form_opt_select("opt_eye_color","Eye Colour");
    shn_form_opt_select("opt_skin_color","Skin Colour");
    shn_form_opt_select("opt_hair_color","Hair Colour");
    shn_form_text('Height','height','size="10"');
    shn_form_text('Weight','weight','size="10"');
    shn_form_fsclose();

    shn_form_fsopen("Other Details");
    shn_form_opt_select("opt_blood_type","Blood Type");
    shn_form_textarea('Last Seen','last_seen');
    shn_form_textarea('Last Clothing','last_clothing');
    shn_form_textarea('Comments','comments');
    shn_form_fsclose();

    shn_form_fsopen("Reporting Person");
    shn_form_text('Name','rep_full_name','size="40"');
    shn_form_text('Relation','rep_relation','size="40"');
    shn_form_textarea('Address','rep_address');
    shn_form_text('Phone','rep_phone','size="40"');
    shn_form_text('Email','rep_email','size="40"');
    shn_form_fsclose();
    
    shn_form_submit('Next');
    shn_form_fclose();
}

function shn_mpr_addmp_validate() 
{
    $error_flag=false;
    
    //trim them all
    foreach($_POST as $k => $v){
        $v = trim($v);
        if($v != '')
            $local_post[$k] = $v;
    }
   
    if(empty($local_post)){
        add_error(_("You have not completed the form"));
        return false;
    }
         
/*    if(isset($local_post['dob']) && ! shn_valid_date($local_post['dob'])){
        add_error(_("Invalid Date"));
        $error_flag=true;
    }

/*    if(shn_is_opt_field($opt_age_group)){
        add_error(_("Invalid Age Group"));
        $error_flag=true;
    }

    if(shn_is_opt_field($opt_gender)){
        add_error(_("Invalid Gender"));
        $error_flag=true;
    }

    if(shn_is_opt_field($opt_marital_status)){
        add_error(_("Invalid Marital Status"));
        $error_flag=true;
    }

    if(shn_is_opt_field($opt_religion)){
        add_error(_("Invalid Religion"));
        $error_flag=true;
    }

    if(shn_is_opt_field($opt_race)){
        add_error(_("Invalid Race"));
        $error_flag=true;
    }    
*/
    if($error_flag)
        return false;
    else{
        //set session
        $local_post['p_uuid'] = shn_create_uuid();
        $_SESSION['mpr_entry']=$local_post;
        return true;
    }
} 

function shn_mpr_addmp_upload($errors=false) 
{
    if($errors)
        display_errors();

    shn_form_fopen("addmp",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'upload_pic'));
    shn_form_fsopen('Upload Picture');
    shn_form_upload("Upload Picture","picture");
    shn_form_fsclose();
    shn_form_submit('Next');
    shn_form_fclose();
}
 
function shn_mpr_addmp_upload_pic() 
{
    //Uploads 
    global $global;
    $upload_dir = $global['approot'].'www/tmp/';
    $info = getimagesize($_FILES['picture']['tmp_name']);
    //check the image type 
    if(! $info){
        add_error(_("Invalid Image Type Please try again"));
        return false;    
    }

    list($ignore,$ext) = split("\/",$info['mime']);
    //putting a dot ;-) 
    $ext = '.'.$ext;

    $uploadfile = $upload_dir .'ori_'. $_SESSION['mpr_entry']['p_uuid'].$ext;
    move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
    $desc_path = $upload_dir . 'thumb_'.$_SESSION['mpr_entry']['p_uuid'].$ext; 
    //make thumb 150X150 or some thing like that ;-)
    shn_image_resize($uploadfile,$desc_path,150,150);
    return true;
}

function shn_create_uuid($type='p')
{
   return mktime().rand(0,1000); 
}

function shn_mpr_addmp_confirm()
{
    shn_form_fopen("addmp",null);
    shn_form_fsopen("Missing Person");
    shn_form_hidden(array('seq'=>'commit'));
    shn_show_thumb($_SESSION['mpr_entry']['p_uuid']);
?>
    <hr>
<?php
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
            isset($_SESSION['mpr_entry']['weight']) ) {
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
    if($physical_section)
        shn_form_fsclose();

    //Contact Details
    if(isset($_SESSION['mpr_entry']['address']) || 
            isset($_SESSION['mpr_entry']['']) ||
            isset($_SESSION['mpr_entry']['address']) ||
            isset($_SESSION['mpr_entry']['address']) ){
        shn_form_fsopen("Contact Details");
        $contact_section = true;
    }
    if(isset($_SESSION['mpr_entry']['address']))
        shn_form_label('Address',$_SESSION['mpr_entry']['address']);
    if(isset($_SESSION['mpr_entry']['']))
        shn_form_label('Postal Code',$_SESSION['mpr_entry']['zip']);
    if(isset($_SESSION['mpr_entry']['address']))
        shn_form_label('Home Phone',$_SESSION['mpr_entry']['phone']);
    if(isset($_SESSION['mpr_entry']['address']))
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

function shn_get_field_opt($value,$field_name)
{

    global $global;
    return $global['db']->GetOne("SELECT option_description FROM field_options WHERE option_code = '$value' AND field_name='$field_name'");
}

function shn_image_resize($src_path,$desc_path,$width,$height)
{
    $info = getimagesize($src_path);
    if(! $info)
        return false;

    $width_orig = $info[0];
    $height_orig = $info[1];

    if ($width && ($width_orig < $height_orig)) {
       $width = ($height / $height_orig) * $width_orig;
    } else {
       $height = ($width / $width_orig) * $height_orig;
    }
    
    $image_p = imagecreatetruecolor($width, $height);

    list($ignore,$mime) = split("\/",$info['mime']);
    $func = 'imagecreatefrom'.$mime;
    $image = $func($src_path);

    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
    $func2 = 'image'.$mime;
    $func2($image_p,$desc_path,100);
}

function shn_show_thumb($p_uuid)
{
    global $global;
    
    //Since we don't know the extension
    $file = $global['approot'].'www/tmp/thumb_'.$p_uuid.'*';
 
    //Need a better way
    $filename = `ls $file`;
    $filename = trim($filename);
    
    $ext = substr($filename,strlen($file),(strlen($filename)-strlen($file)));

    $info = getimagesize($global['approot']."www/tmp/ori_$p_uuid.$ext");
    $height = $info[1]+20;
    $width = $info[0]+20;
 
    $url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
    //remove the index.php
    $url = substr($url,0,strlen($url)-9);
    //add http://
    $url = 'http://'.$url."/tmp/ori_$p_uuid.$ext";
?>
    <a href="#" onclick="window.open('<?=$url?>','hello','width=<?=$width?>,height=<?=$height?>,scrollbars=no,status=no');return false;" >
    <img border="0" src="tmp/<?='thumb_'.$p_uuid.'.'.$ext?>" />
    </a>
<?php
}

function shn_mpr_addmp_commit()
{
/* LATER
    global $global;
    include_once($global['approot'].'inc/lib_dbentity/obj_person.inc');
    $missing_person = new shn_Person($_SESSION['mpr_entry']['p_uuid']);
    
    foreach($_SESSION['mpr_entry'] as $k => $v){
        if($k != 'seq')
            echo '$missing_person->set_'."$k($v)<br>";
    }
*/
    // $insert_array[<field_name>] = value
    global $global;

    $insert_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //Basic Details : person_uuid
    //@todo: soundex insert
    if(isset($_SESSION['mpr_entry']['full_name'])){
        $insert_array['full_name'] = $_SESSION['mpr_entry']['full_name'];
        shn_db_insert_phonetic($insert_array['full_name'],$insert_array['p_uuid']);
    }
    if(isset($_SESSION['mpr_entry']['family_name'])){
        $insert_array['family_name'] = $_SESSION['mpr_entry']['family_name'];
        shn_db_insert_phonetic($insert_array['family_name'],$insert_array['p_uuid']);
    }
    if(isset($_SESSION['mpr_entry']['local_name'])){
        $insert_array['l10n_name'] = $_SESSION['mpr_entry']['local_name'];
        shn_db_insert_phonetic($insert_array['l10n_name'],$insert_array['p_uuid']);
    }

    shn_db_insert($insert_array,'person_uuid');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //Identity
    if(isset($_SESSION['mpr_entry']['idcard'])) {
        $insert_array['serial'] = $_SESSION['mpr_entry']['idcard'];
        $insert_array['opt_id_type'] = 'nic';
        shn_db_insert($insert_array,'identity_to_person');
    }
    if(isset($_SESSION['mpr_entry']['passport'])) {
        $insert_array['serial'] = $_SESSION['mpr_entry']['passport'];
        $insert_array['opt_id_type'] = 'pas';
        shn_db_insert($insert_array,'identity_to_person');
    }
    if(isset($_SESSION['mpr_entry']['drv_license'])) {
        $insert_array['serial'] = $_SESSION['mpr_entry']['drv_license'];
        $insert_array['opt_id_type'] = 'dln';
        shn_db_insert($insert_array,'identity_to_person');
    }
    //reset $insert_array 
    $insert_array = null;

/*    $insert_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //Contacts
    if(isset($_SESSION['mpr_entry']['address']))
        shn_form_label('Address',$_SESSION['mpr_entry']['address']);
    if(isset($_SESSION['mpr_entry']['']))
        shn_form_label('Postal Code',$_SESSION['mpr_entry']['zip']);
    if(isset($_SESSION['mpr_entry']['address']))
        shn_form_label('Home Phone',$_SESSION['mpr_entry']['phone']);
    if(isset($_SESSION['mpr_entry']['address']))
        shn_form_label('Mobile',$_SESSION['mpr_entry']['mobile']);
    if($contact_section)
 */

    $insert_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //Physical Details : person_physical
    if(isset($_SESSION['mpr_entry']['opt_eye_color']))
        $insert_array['opt_eye_color'] = $_SESSION['mpr_entry']['opt_eye_color'];
    if(isset($_SESSION['mpr_entry']['opt_skin_color']))
        $insert_array['opt_skin_color'] = $_SESSION['mpr_entry']['opt_skin_color'];
    if(isset($_SESSION['mpr_entry']['opt_hair_color']))
        $insert_array['opt_hair_color'] = $_SESSION['mpr_entry']['opt_hair_color'];
    if(isset($_SESSION['mpr_entry']['height']))
        $insert_array['height'] = $_SESSION['mpr_entry']['height'];
    if(isset($_SESSION['mpr_entry']['weight']))
        $insert_array['weight'] = $_SESSION['mpr_entry']['weight'];
    if(isset($_SESSION['mpr_entry']['opt_blood_type']))
        $insert_array['opt_blood_type'] = $_SESSION['mpr_entry']['opt_blood_type'];

    shn_db_insert($insert_array,'person_physical');
    //reset $insert_array 
    $insert_array = null;
    $insert_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];


    //Other Details
    if(isset($_SESSION['mpr_entry']['last_seen']))
        $insert_array['last_seen'] = $_SESSION['mpr_entry']['last_seen'];
    if(isset($_SESSION['mpr_entry']['last_clothing']))
        $insert_array['last_clothing'] = $_SESSION['mpr_entry']['last_clothing'];
    if(isset($_SESSION['mpr_entry']['comments']))
        $insert_array['comments'] = $_SESSION['mpr_entry']['comments'];

    shn_db_insert($insert_array,'person_missing');
    //reset $insert_array 
    $insert_array = null;

    $rep_p_uuid = shn_create_uuid('p');
    $insert_array['p_uuid'] = $rep_p_uuid;
    //Reporting Person
    if(isset($_SESSION['mpr_entry']['rep_full_name']))
        $insert_array['full_name'] = $_SESSION['mpr_entry']['rep_full_name'];

    shn_db_insert($insert_array,'person_uuid');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['pgoc_uuid'] = $rep_p_uuid;
    if(isset($_SESSION['mpr_entry']['rep_address'])){
        $insert_array['contact_value'] = $_SESSION['mpr_entry']['rep_address'];
        $insert_array['opt_contact_type'] = 'home';
    }

    shn_db_insert($insert_array,'contact');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['pgoc_uuid'] = $rep_p_uuid;
    if(isset($_SESSION['mpr_entry']['rep_phone'])){
        $insert_array['contact_value'] = $_SESSION['mpr_entry']['rep_phone'];
        $insert_array['opt_contact_type'] = 'curr';
        
    }
    shn_db_insert($insert_array,'contact');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['pgoc_uuid'] = $rep_p_uuid;
    if(isset($_SESSION['mpr_entry']['rep_email'])){
        $insert_array['contact_value'] = $_SESSION['mpr_entry']['rep_email'];
        $insert_array['opt_contact_type'] = 'emai';
    }
    shn_db_insert($insert_array,'contact');
    //reset $insert_array 
    $insert_array = null;

    $insert_array['p_uuid'] = $_SESSION['mpr_entry']['p_uuid'];
    //person_details        
    if(isset($_SESSION['mpr_entry']['dob']))
        $insert_array['birth_date'] = $_SESSION['mpr_entry']['dob'];
    if(isset($_SESSION['mpr_entry']['opt_age_group']))
        $insert_array['opt_age_group'] = $_SESSION['mpr_entry']['opt_age_group'];
    if(isset($_SESSION['mpr_entry']['opt_gender']))
        $insert_array['opt_gender'] = $_SESSION['mpr_entry']['opt_gender'];
    if(isset($_SESSION['mpr_entry']['opt_marital_status']))
        $insert_array['opt_marital_status'] = $_SESSION['mpr_entry']['opt_marital_status'];
    if(isset($_SESSION['mpr_entry']['opt_religion']))
        $insert_array['opt_religion'] = $_SESSION['mpr_entry']['opt_religion'];
    if(isset($_SESSION['mpr_entry']['opt_race']))
        $insert_array['opt_race'] = $_SESSION['mpr_entry']['opt_race'];
    if(isset($_SESSION['mpr_entry']['rep_relation'])){
        $insert_array['next_kin_uuid'] = $rep_p_uuid;
        $insert_array['relation'] = $_SESSION['mpr_entry']['rep_relation'];    
    }
    shn_db_insert($insert_array,'person_details');
    
    //go back to the main menu
    shn_mpr_default();    
}
?>
