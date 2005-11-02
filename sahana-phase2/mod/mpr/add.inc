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
    shn_show_thumb($_SESSION['mpr_entry']['p_uuid']);
?>
    <hr>
<?php
    //Identity
    if(isset($_SESSION['mpr_entry']['idcard']))
        shn_form_label('Identity Card Number',$_SESSION['mpr_entry']['idcard']);
    if(isset($_SESSION['mpr_entry']['passport']))
        shn_form_label('Passport Number',$_SESSION['mpr_entry']['passport']);
    if(isset($_SESSION['mpr_entry']['drv_license']))
        shn_form_label('Driving License',$_SESSION['mpr_entry']['drv_license']);

    //Basic Details
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

    $ext = substr($filename,strlen($file),(strlen($filename)-strlen($file)));
?>
    <img src="tmp/<?='thumb_'.$p_uuid.'.'.$ext?>" />
<?php
}
?>
