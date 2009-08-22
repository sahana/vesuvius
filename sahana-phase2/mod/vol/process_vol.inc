<?php
/**Processing functions(add ,edit,delete,ect) for Volunteers of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/


function _shn_vol_reg_cr()
{
    global $global;
    include_once $global['approot']."inc/lib_security/auth_form.inc";
    include_once "reg_vol.inc";
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
   
    $parents=array();
    shn_get_parents($_SESSION['vol']['loc'],$parents);
    $loc=$_SESSION['vol']['loc'];
    $bsd_country=array_pop($parents);
    $name=$_SESSION['vol']['name'];
    $dob=$_SESSION['vol']['dob'];
    $male=$_SESSION['vol']['gender'];
    $job=$_SESSION['vol']['job'];
    $nic=$_SESSION['vol']['nic'];
    $pas=$_SESSION['vol']['pas'];
    $dln=$_SESSION['vol']['dln'];
    $sector=$_SESSION['vol']['sector'];
    $skills=$_SESSION['vol']['skills'];
    $contact_address=$_SESSION['vol']['contact_address'];
    $contact_phone=$_SESSION['vol']['contact_phone'];
    $contact_mobile=$_SESSION['vol']['contact_mobile'];
    $contact_fax=$_SESSION['vol']['contact_fax'];
    $contact_mail=$_SESSION['vol']['contact_mail'];
    $contact_web=$_SESSION['vol']['contact_web'];
    $db=$global['db'];
    $pid = $db->GenID('person_seq',1);
    $q="select p_uuid from person_uuid where p_uuid='{$pid}'";
    $res=$db->Execute($q);
    if(!$res->EOF){
        $error=true;
        add_error(SHN_ERR_vol_PERSON_EXISTS);
    }
    if(!$error){
        $q="insert into person_uuid(p_uuid,full_name) values($pid,'{$name}')";
        $res=$db->Execute($q);
	$q="insert into person_details(p_uuid,birth_date,opt_country,opt_gender,occupation) values($pid,'{$dob}','{$bsd_country}','{$male}','{$job}')";
    $res=$db->Execute($q);
    $q="insert into person_status(p_uuid,isReliefWorker) values($pid,1)";
    $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$nic}','nic')";
   $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$pas}','pas')";
    $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$dln}','dln')";
    $res=$db->Execute($q);
   	$q="insert into resource_to_incident(incident_id,x_uuid) values('{$_SESSION['user_pref_ims_incident_id']}',$pid)";
    $res=$db->Execute($q);
       
    
    $i=0;
    while($i<count($sector)){
            $q="insert into sector(pgoc_uuid,opt_sector) values($pid,'{$sector[$i]}')";
           $res=$db->Execute($q);
           $i=$i+1;
        }
        
        $i=0;
    foreach ($skills as $i){
            $q="insert into vol_skills(p_uuid,opt_skill_code) values('{$pid}','{$i}')";
           $res=$db->Execute($q);
         //  $i=$i+1;
        }
        
    }
    

    
    
    $q="insert into location_details(poc_uuid,location_id,opt_person_loc_type,address) values($pid,'{$loc}','hom','{$contact_address}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'curr','{$contact_phone}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'pmob','{$contact_mobile}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'fax','{$contact_fax}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'email','{$contact_mail}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'web','{$contact_web}')";
    $res=$db->Execute($q);
    if($error!=true){
		$msg=$name." was succesfully registered as a volunteer";
		add_confirmation($msg);
    }
    _shn_vol_regform($error);
}

function _shn_vol_edit()
{
    global $global;
    include_once "errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    $incidents=$_POST["incidents"];
    $VARCHAR=100;
    $error=false;
    $pid=$_POST{"pid"};
	list($error,$name)=(shn_validate_field($_POST{"name"},"Full Name",$VARCHAR,true))?array($error,$_POST{"name"}):array(true,NULL);
    if (!shn_valid_date($_POST{"dob"})){
        $error=true;
        add_error(SHN_ERR_DOB_INCORRECT);
    }else {    
        $dob=$_POST{"dob"};
    }
    
    list($error,$male)=(shn_validate_opt_field('opt_gender',$_POST{"opt_gender"},"Gender",$VARCHAR,false))?array($error,$_POST{"opt_gender"}):array(true,NULL);
    $job=$_POST{"job"};
    $nic=trim($_POST{"nic"});
    $pas=trim($_POST{"pas"});
    $dln=trim($_POST{"dln"});
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Volunteer Service",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    list($error,$skills)=(shn_validate_opt_field('opt_skill_type',$_POST{"opt_skill_type"},"Volunteer Skills",$VARCHAR,true))?array($error,$_POST{"opt_skill_type"}):array(true,NULL);
    $loc=shn_location_get_form_submit_loc();
    if ($loc==-1){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }
    $parents=array();
    shn_get_parents($loc,$parents);
    $bsd_country=array_pop($parents);
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_mobile=$_POST{"contact_mobile"};
    $contact_fax=$_POST{"contact_fax"};
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_vol_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }
    }
    $contact_web=$_POST{"contact_web"};
    if(!$error){
    $db=$global['db'];
    $q="update person_uuid set full_name='{$name}' where p_uuid=$pid";
    $res=$db->Execute($q);
	$q="update person_details set birth_date='{$dob}',opt_country='{$bsd_country}',opt_gender='{$male}',occupation='{$job}' where p_uuid=$pid";
    $res=$db->Execute($q);
	$q="update identity_to_person set serial='{$nic}' where p_uuid=$pid and opt_id_type='nic'";
    $res=$db->Execute($q);
	$q="update identity_to_person set serial='{$pas}' where p_uuid=$pid and opt_id_type='pas'";
    $res=$db->Execute($q);
    $q="update identity_to_person set serial='{$dln}' where p_uuid=$pid and opt_id_type='dln'";
    $res=$db->Execute($q);
    $q="delete from sector where pgoc_uuid=$pid";
    $res=$db->Execute($q);
    $i=0;
    while($i<count($sector)){
        $q="insert into sector(pgoc_uuid,opt_sector) values($pid,'{$sector[$i]}')";
        $res=$db->Execute($q);
        $i=$i+1;
    }
    
    $q="delete from vol_skills where p_uuid='{$pid}'";
    $res=$db->Execute($q);
    $i=0;
    while($i<count($skills)){
            $q="insert into vol_skills(p_uuid,opt_skill_code) values('{$pid}','{$skills[$i]}')";
           $res=$db->Execute($q);
           $i=$i+1;
    }
 
    $q="update location_details set location_id='{$loc}',address='{$contact_address}' where poc_uuid=$pid";
    $res=$db->Execute($q);
    $q="update contact set contact_name='{$contact_name}' where pgoc_uuid=$pid and opt_contact_type='name'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_phone}' where pgoc_uuid=$pid and opt_contact_type='curr'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_mobile}' where pgoc_uuid=$pid and opt_contact_type='pmob'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_fax}' where pgoc_uuid=$pid and opt_contact_type='fax'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_mail}' where pgoc_uuid=$pid and opt_contact_type='email'";
    $res=$db->Execute($q);
    $q="update contact set contact_value='{$contact_web}' where pgoc_uuid=$pid and opt_contact_type='web'";
    $res=$db->Execute($q);
    
    
?>
    <div id="result_msg">
       <?php echo $name?> was succesfully Updated
    </div>
    <br />
<h2> Volunteer Registry</h2>
<?php
    }
    if($error==true){
		_shn_vol_viewform($pid,$error);
        return false;
	}
        _shn_vol_viewform_all();    
}


function _shn_vol_del()
{ 
    global $global;
    $db=$global['db'];
    $pid=$_POST{"pid"};
    $q="select full_name from person_uuid where p_uuid=$pid";
    $res=$db->Execute($q);
    $name=$res->fields[0];
    $q="update person_status set isReliefWorker=0 where p_uuid=$pid";
    $res=$db->Execute($q);
     ?>
    <div id="result_msg">
       <?php echo $name?> Volunteer was succesfully Deleted
    </div>
    <br />
<h2> Volunteer Registry</h2>
<?php
        _shn_vol_viewform_all();   
}

/**
 * This checks for the uploaded picture and make the thumbnail.
 * @access public
 * @return void
 */
function _shn_vol_upload_pic() 
{
    //No file was uploaded ignore
    if($_FILES['picture']['error']==UPLOAD_ERR_NO_FILE)
        return true;
    //Uploads 
    global $global;
    global $conf;
    $info = getimagesize($_FILES['picture']['tmp_name']);
    //check the image type 
    if(! $info){
        add_error(_t("Invalid Image Type Please try again"));
        return false;    
    }

    list($ignore,$ext) = split("\/",$info['mime']);

    //check for save handler
    if($conf['mod_vol']['upload_picture']['savehandler'] == 'database'){
        $size = filesize($_FILES['picture']['tmp_name']);
        $pic = fread(fopen($_FILES['picture']['tmp_name'],"r"),$size);
        $_SESSION['vol']['entry']['image'] = $pic;
        $_SESSION['vol']['entry']['image_type'] = $ext;
        $_SESSION['vol']['entry']['image_height'] = $info[1];
        $_SESSION['vol']['entry']['image_width'] = $info[0];
        
        return true;
    }

    //putting a dot ;-) 
    $ext = '.'.$ext;
    $upload_dir = $global['approot'].'www/tmp/';
    $uploadfile = $upload_dir .'ori_'. $_SESSION['vol_add']['entry']['p_uuid'].$ext;
    move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
    $desc_path = $upload_dir . 'thumb_'.$_SESSION['vol_add']['entry']['p_uuid'].$ext; 
    //make thumb 100X100 or some thing like that ;-)
    shn_image_resize($uploadfile,$desc_path,100,100);
    
    if (isset($_POST["chk_login"])){
       			$header=array('method'=>'POST','action'=>'index.php?mod=vol&act=add_user_cr','id'=>'formset');
       			shn_auth_form_user_add("Create an Account for Login",$header,false);
    }
    return true;
}

