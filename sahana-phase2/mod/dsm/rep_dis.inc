<?php
include_once $global['approot'] . '/inc/lib_uuid.inc';
include_once $global['approot'] . '/inc/lib_image.inc';
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_location.inc');

function _shn_print_form_one()
{
    shn_form_fopen("rep_dis",null,array('req'=>false));
    shn_form_hidden(array('seq'=>'form2'));
    
    shn_form_fsopen(_('Diagnosis / Disease'));
    //shn_form_checkbox(_t('Identified the disease'), 'is_dis', null);
    $diseases = array();
    $diseases = _shn_dsm_diseases();//var_dump($diseases);
    shn_form_select($diseases,_t('Disease'),'dis_is');
    shn_form_fsclose();
    
    shn_form_fsopen(_('Details'));
    shn_form_text(_t('Name'),'pat_name','',array('req'=>true));
    shn_form_text(_t('Last Name'),'pat_lastname');
    shn_form_text(_t('Age'),'pat_age');
    shn_form_text(_t('Sex'),'pat_sex');
    
    shn_form_text(_t('Occupation'),'pat_occ');
    shn_form_fsclose();

    shn_form_fsopen(_('Symptoms'));
    $result = array();
    $result = _shn_dsm_get_stored_sym();//var_dump($result);
//while (!$result -> EOF) {
    $index = 0;
    foreach ($result as $id=>$desc) {
        //shn_form_checkbox($desc, 'sym'.$index, null, array('value'=>$id));//var_dump($res);
        shn_form_radio(array('Not a problem','Minor problem','Moderate problem','Serious problem'),$desc, 'sym'.$index, null, array('value'=>$id));
        $index++;
//shn_form_opt_checkbox('opt_age_group',$extra_opts=null);
//$result->MoveNext();
    }//shn_form_submit(_('Submit'));
    shn_form_fsclose();

    shn_form_fsopen(_('Diagnosis'));
    shn_form_checkbox(_t('Identified the disease'), 'is_dis', null);
    $diseases = array();
    $diseases = _shn_dsm_diseases();//var_dump($diseases);
    shn_form_select($diseases,_t('Disease'),'dis_is');
    shn_form_fsclose();
    
    _shn_patient_contact();
    
    //shn_form_fsopen(_(''));
    //shn_form_fsclose();

    shn_form_submit(_t('Next'));
    shn_form_fclose();
}

function _shn_patient_location()
{
    global $global;
    include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	
    shn_form_fopen("rep_dis",null,array('req'=>false));
	shn_form_hidden(array('seq'=>'finish'));
    
	shn_gis_add_marker_map_form("Area Map","",null,array('marker'=>'single'));
	//shn_form_multi_select('symptoms', array('ertet','ertet','dgdhgdh','dghedghd','gereyeyh'), _t('Symptoms'));
    
	shn_form_submit(_t('Next'));
	shn_form_fclose();
}

function _shn_dsm_set_patient()
{ 
	$_SESSION['rep']['dis'] = $_POST['dis_is']; //print $_POST['dis_is'];
	//if existing user then do coding for get id
	$_SESSION['dsm']['pat_uuid'] = shn_create_uuid();
	$_SESSION['dsm']['dia_id'] = shn_create_uuid('diagnosis');
	$_SESSION['dsm']['doc_id'] = '285ip-10'; 
	$_SESSION['dsm']['pat_name'] = $_POST['pat_name'];
	unset($_POST['pat_name']);
	$_SESSION['dsm']['pat_lastname'] = $_POST['pat_lastname'];
	unset($_POST['pat_lastname']);
	$_SESSION['dsm']['pat_age'] = $_POST['pat_age'];
	unset($_POST['pat_age']);
	$_SESSION['dsm']['pat_sex'] = $_POST['pat_sex'];
	unset($_POST['pat_sex']);
	$_SESSION['dsm']['pat_occ'] = $_POST['pat_occ'];
	unset($_POST['pat_occ']);
	
	//$_REQUEST['seq'] = null;
	
	$_SESSION[''] = $_POST['pat_'];
	
	_shn_set_contacts();
	
	$loc = shn_location_get_form_submit_loc();
	$_SESSION['dsm']['loc_id'] = $loc;
	
}

function _shn_dsm_set_symptoms()
{
	$_SESSION['symptoms'] = array();
	
	for ($i = 0; $i<10; $i++) {
		//if ($val != null | $key != 'seq')
		array_push($_SESSION['symptoms'],$_POST['sym'.$i]);//print $_POST['sym'.$i];
		
		//$_POST -> MoveNext();
	}
	
	//$_SESSION['dsm']['pat_address'] = $_POST['pat_address'];
	//$_SESSION['dsm']['pat_email'] = $_POST['pat_email'];
	//$_SESSION['dsm']['pat_phone'] = $_POST['pat_phone'];
	//$_SESSION['dsm']['pat_mobile'] = $_POST['pat_mobile'];
	
}

function _shn_patient_contact()
{
    //shn_form_fopen("rep_dis",null,array('req'=>false));
	//shn_form_hidden(array('seq'=>'finish'));
    
	shn_form_fsopen(_t('Contact Details'));
	shn_form_textarea(_t('Address'),'pat_address');
    shn_form_text(_t('Phone'),'pat_phone','size="30"');
    shn_form_text(_t('Modile'),'pat_mobile','size="30"');
    shn_form_text(_t('Email'),'pat_email','size="30"');
	shn_form_fsclose();
    
	//shn_form_fclose();
}

function _shn_set_contacts()
{
	$_SESSION['dsm']['pat_address'] = $_POST['pat_address'];
	$_SESSION['dsm']['pat_email'] = $_POST['pat_email'];
	$_SESSION['dsm']['pat_phone'] = $_POST['pat_phone'];
	$_SESSION['dsm']['pat_mobile'] = $_POST['pat_mobile'];
}

function _shn_dsm_commit_patient()
{
	$sql = "INSERT INTO person_uuid (p_uuid,full_name,family_name,l10n_name,custom_name) VALUES ('{$_SESSION['dsm']['pat_uuid']}','{$_SESSION['dsm']['pat_name']}.{$_SESSION['dsm']['pat_lastname']}','{$_SESSION['dsm']['pat_lastname']}','{$_SESSION['dvr']['person']['local_name']}','')";
	_shn_dsm_execute($sql);
	
	$sql = "INSERT INTO diagnosis (pat_id,doc_id,dia_id,gender,age_group,disease,location) VALUES ('{$_SESSION['dsm']['pat_uuid']}','not assigned','{$_SESSION['dsm']['dia_id']}','{$_SESSION['dsm']['pat_sex']}','{$_SESSION['dsm']['pat_agegroup']}','{$_SESSION['rep']['dis']}','{$_SESSION['dsm']['loc_id']}')";
	_shn_dsm_execute($sql);
	
	if($_SESSION['dsm']['pat_email'])
	_dsm_add_contact($_SESSION['dsm']['pat_uuid'],'email',$_SESSION['dsm']['pat_email']);
	if($_SESSION['dsm']['pat_mobile'])
	_dsm_add_contact($_SESSION['dsm']['pat_uuid'],'mobile',$_SESSION['dsm']['pat_mobile']);
	if($_SESSION['dsm']['pat_telephone'])
	_dsm_add_contact($_SESSION['dsm']['pat_uuid'],'telephone',$_SESSION['dsm']['pat_telephone']);
	if($_SESSION['dsm']['pat_address'])
	_dsm_add_contact($_SESSION['dsm']['pat_uuid'],'address',$_SESSION['dsm']['pat_address']);
	
	//$sql = "INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES ('{$_SESSION['dsm']['pat_uuid']}','address','{$_SESSION['dsm']['pat_address']}')";
    //_shn_dsm_execute($sql);
}

function _shn_confirm_patient_todb()
{
	shn_form_fopen("rep_dis",null,array('req'=>false));
	//shn_form_fsopen();
	add_confirmation(_t('Patient details are added to the system.'));
	 print '<br />'. '<center>' .
                  '[ <a href="index.php?mod=dsm">DSM Home</a> ] :: ' .
                  '[ <a href="index.php?mod=dsm&amp;act=rep_dis">Report a patient</a> ]' . '</center>';
    //shn_form_fsclose();
    shn_form_fclose();
}

