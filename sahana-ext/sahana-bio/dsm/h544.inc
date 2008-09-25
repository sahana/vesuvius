<?php
function _shn_dsm_h544_input_form()
{
    display_submit_message();
    display_errors();
    echo '<center><h1>H544</h1></center>';
    //var_dump($_POST);
    shn_form_fopen('h544',null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'validate'));
    shn_form_fsopen(_t('H544'));

    shn_form_text(_t('Institute'),'institute','size="30"');
    shn_form_text(_t('Name of Patient'),'name_patient','size="30"');
    shn_form_text(_t('Name of the Guardian'),'name_guardian','size="30"');

    $opt = array('a'=>'A','b'=>'B');
    shn_form_select($opt,_t('Disease Type'),'dis_type');
    $opt=null;

    $opt = array('11'=>'Dis1','12'=>'Dis2');
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
    shn_form_text(_t('Status of Doctor'),'doc_status','size="30"');
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
NULL , '{$_POST['institute']}', '{$_POST['name_patient']}', '{$_POST['name_guardian']}', '{$_POST['dis_id']}', '{$_POST['date_onset']}', '{$_POST['date_admission']}', '{$_POST['bht']}', '{$_POST['ward']}', '{$_POST['age']}', '{$_POST['sex']}', '{$_POST['laboratory_results']}', '{$_POST['home_address']}', '{$_POST['telephone']}', NULL, '{$_POST['doc_name']}', '{$_POST['doc_status']}', '{$_POST['date']}'
) ";

$db->Execute($sql);
add_confirmation('Notification added');
unset($_POST);

_shn_dsm_h544_input_form();
}


?>