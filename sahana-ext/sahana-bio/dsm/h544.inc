<?php
function _shn_dsm_h544_input_form()
{
    global $global;
    $db = $global['db'];
    
    display_submit_message();
    display_errors();
    echo '<center><h1>H544</h1></center>';
    //var_dump($_POST);
    shn_form_fopen('h544',null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'validate'));
    shn_form_fsopen(_t('H544'));

    shn_form_text(_t('Institute'),'institute','size="30"');
    shn_form_text(_t('Name of Patient'),'name_patient','size="30"',array('req'=>true));
    shn_form_text(_t('Name of the Guardian'),'name_guardian','size="30"');

//    $opt = array('a'=>'A','b'=>'B');
//    shn_form_select($opt,_t('Disease Type'),'dis_type');
//    $opt=null;

    $sql = "SELECT * FROM rtbs_disease WHERE disease_type='A'";
    $res = $db->Execute($sql);
    $opt = array();
    $opt[0]='';
    $opt[-1]='----A----';
    while(!$res->EOF){
        $opt[$res->fields['disease_id']]=$res->fields['disease_name'];
        $res->MoveNext();
    }
    $opt[-2]='----B----';
    $sql = "SELECT * FROM rtbs_disease WHERE disease_type='B'";
    $res = $db->Execute($sql);
    while(!$res->EOF){
        $opt[$res->fields['disease_id']]=$res->fields['disease_name'];
        $res->MoveNext();
    }
    
    shn_form_select($opt,_t('Disease Name'),'dis_id');
    $opt = null;

    shn_form_date(_t('Date of Onset'),'date_onset',array('value'=>date('Y-m-d',time())));
    shn_form_date(_t('Date of Admission'),'date_admission',array('value'=>date('Y-m-d',time())));
    shn_form_text(_t('BHT number'),'bht','size="30"');
    shn_form_text(_t('Ward'),'ward','size="30"');
    shn_form_text(_t('Age'),'age','size="30"');

    $opt = array('m'=>'Male','f'=>'Female');
    shn_form_select($opt,_t('Sex'),'sex');
    $opt = null;

    shn_form_textarea(_t('Laboratory results'),'laboratory_results');
    shn_form_textarea(_t('Home address'),'home_address');
    shn_form_text(_t('Telephone number'),'telephone','size="30"');
    shn_form_text(_t('Name of Doctor'),'doc_name','size="30"');
    
    $opt = array('MBBS'=>'MBBS','FRCS'=>'FRCS');
    shn_form_select($opt,_t('Status of Doctor'),'doc_status');
    $opt = null;
    
    shn_form_date(_t('Date'),'date',array('value'=>date('Y-m-d',time())));
    shn_form_submit(_t("Save"));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_dsm_h544_validate()
{
    if($_POST['name_patient']==''){
        add_error('Name required');
        return false;
    }

    return true;
}

function _shn_dsm_h544_commit()
{
    global $global;
    $db = $global['db'];
    $sql = " INSERT INTO `rtbs_h544` (
`notify_id` ,
`institute` ,
`name_of_patient` ,
`name_of_the_guardian` ,
`disease_id` ,
`date_of_onset` ,
`date_of_admission` ,
`bht_no` ,
`ward` ,
`age` ,
`sex` ,
`laboratory_results` ,
`home_address` ,
`telephone_number` ,
`notified_by` ,
`name_of_doctor` ,
`status_of_doctor` ,
`date`
)
VALUES (
NULL , '{$_SESSION['dsm']['h544']['institute']}', '{$_SESSION['dsm']['h544']['name_patient']}', '{$_SESSION['dsm']['h544']['name_guardian']}', '{$_SESSION['dsm']['h544']['dis_id']}', '{$_SESSION['dsm']['h544']['date_onset']}', '{$_SESSION['dsm']['h544']['date_admission']}', '{$_SESSION['dsm']['h544']['bht']}', '{$_SESSION['dsm']['h544']['ward']}', '{$_SESSION['dsm']['h544']['age']}', '{$_SESSION['dsm']['h544']['sex']}', '{$_SESSION['dsm']['h544']['laboratory_results']}', '{$_SESSION['dsm']['h544']['home_address']}', '{$_SESSION['dsm']['h544']['telephone']}', NULL, '{$_SESSION['dsm']['h544']['doc_name']}', '{$_SESSION['dsm']['h544']['doc_status']}', '{$_SESSION['dsm']['h544']['date']}'
) ";

$db->Execute($sql);
add_confirmation('Notification added');


_shn_dsm_h544_notify_to($_POST['dis_id']);
unset($_POST);
}

function _shn_dsm_h544_notify_to($id)
{
    global $global;
    $db = $global['db'];
    
    $sql = "SELECT * FROM rtbs_disease_notify_to WHERE disease_id={$id}";
    echo '<h2>Notify this disease to</h2>';
    echo '<ul>';
    $res = $db->Execute($sql);
    while(!$res->EOF){
        echo '<li>';
        echo $res->fields['notify_to'];
        $res->MoveNext();
        echo '</li>';
    }
    echo "</ul>";
    shn_form_fopen('h544',null,array('req_message'=>false));
    shn_form_submit(_t('OK'));
    shn_form_fclose();
    
}

function _shn_dsm_h544_to_session()
{
    $_SESSION['dsm']['h544']['institute'] = $_POST['institute'];
    $_SESSION['dsm']['h544']['name_patient'] = $_POST['name_patient'];
    $_SESSION['dsm']['h544']['name_guardian'] = $_POST['name_guardian'];
    $_SESSION['dsm']['h544']['dis_id'] = $_POST['dis_id'];
    $_SESSION['dsm']['h544']['date_onset'] = $_POST['date_onset'];
    $_SESSION['dsm']['h544']['date_admission'] = $_POST['date_admission'];
    $_SESSION['dsm']['h544']['bht'] = $_POST['bht'];
    $_SESSION['dsm']['h544']['ward'] = $_POST['ward'];
    $_SESSION['dsm']['h544']['age'] = $_POST['age'];
    $_SESSION['dsm']['h544']['sex'] = $_POST['sex'];
    $_SESSION['dsm']['h544']['laboratory_results'] = $_POST['laboratory_results'];
    $_SESSION['dsm']['h544']['home_address'] = $_POST['home_address'];
    $_SESSION['dsm']['h544']['telephone'] = $_POST['telephone'];
    $_SESSION['dsm']['h544']['doc_name'] = $_POST['doc_name'];
    $_SESSION['dsm']['h544']['doc_status'] = $_POST['doc_status'];
    $_SESSION['dsm']['h544']['date'] = $_POST['date'];
    
}
?>