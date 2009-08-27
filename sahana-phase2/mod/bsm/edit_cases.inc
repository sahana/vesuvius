<?php
/* $Id: edit_cases.inc,v 1.3 2009-08-27 22:26:48 pradeeper Exp $ */
/**
 * Edit Health cases
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      Nuwan Waidyanatha <waidyanatha@lirne.net>
 * @copyright   Lanka Software Foundation - http://www.opensource.lk
 * @package     module
 * @subpackage  dsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @tutorial    User can change the values of the attributes related to a case; however, cannot change the case ID
 *              or the case was reported, which is entered at the time of creating (or ADDing) the case. Symptoms,
 *              Signs, Persons, and Status are changed by navigating away from the page and using the resepcting
 *              search forms of the mentioned to include or exclude those values related to the case. While symptoms,
 *              signs, and case status are mutivalued records (i-to-many) the person information is a single detail 
 *              record (1-to-1).
 * @TODO    If the direct input values such as the dates and text are changed then process should prompt user to
 *          commit (or save) values to the database before navigating away from the page such as when looking up
 *          symptoms, signs, case status, or persons.
 * @TODO    Organize the entry fields and displays in a user friendly and accessible way; either by sqeezong all
 *          attributes in to one page or splitting the information in to several pages with page navigation controls.
 */
/**
 * @name    Generate Tabbs
 * @param string $selected
 * @access public
 * @return void
 * @todo code this
 */
function shn_generate_tabs($selected=''){
	global $conf;
	$tabs = $conf['mod_bsm']['edit']['tabs'];
	?>
<div id="form_tabs">
<ul>
<?php
foreach($tabs as $tab){
	?>
	<li><a href="#"><?= $tab; ?></a></li>
	<?php
}
?>
</ul>
</div>
<?php
}
/**
* @name Load Informations on cases
* @param mixed $p_uuid
* @access public
* @return void
*/
function shn_bsm_edit_load($case_id){

    global $global;
    global $conf;

    $sql =  "SELECT case_uuid AS case_uuid, case_dt AS case_datetime, pat_p_uuid AS patient_person_uuid, ";
    $sql .= "pat_full_name AS patient_full_name, gender AS patient_gender, age_grp AS patient_age_group, age AS patient_age, ";
    $sql .= "disease AS disease, dis_dia_dt AS disease_diagnose_date, agent AS disease_carry_agent,  ";
    $sql .= "hwork_p_uuid AS hwork_person_uuid, hwork_full_name AS hwork_full_name, ";
    $sql .= "fclty_uuid AS facility_uuid, fclty_name AS facility_name, loc_uuid AS location_uuid, loc_name AS location_name, notes AS notes ";
    $sql .= "FROM bsm_cases WHERE deactivate_dt IS NULL AND case_uuid = '{$case_id}'";

    //echo $sql;
    $rs = $global['db']->Execute($sql);
    //echo $sql;

    $_SESSION['bsm']['edit']['case_uuid'] = $rs->fields['case_uuid'];
    $_SESSION['bsm']['edit']['case_datetime'] = $rs->fields['case_datetime'];
    $_SESSION['bsm']['edit']['patient_person_uuid'] = $rs->fields['patient_person_uuid'];
    $_SESSION['bsm']['edit']['patient_full_name'] = $rs->fields['patient_full_name'];
    $_SESSION['bsm']['edit']['patient_gender'] = $rs->fields['patient_gender'];
    $_SESSION['bsm']['edit']['patient_age_group'] = $rs->fields['patient_age_group'];
    $_SESSION['bsm']['edit']['patient_age'] = $rs->fields['patient_age'];
    $_SESSION['bsm']['edit']['disease'] = $rs->fields['disease'];
    $_SESSION['bsm']['edit']['disease_diagnose_date'] = $rs->fields['disease_diagnose_date'];
    $_SESSION['bsm']['edit']['disease_carry_agent'] = $rs->fields['disease_carry_agent'];
    $_SESSION['bsm']['edit']['previous_diagnose_disease'] = $rs->fields['previous_diagnose_disease'];
    $_SESSION['bsm']['edit']['previous_diagnose_date'] = $rs->fields['previous_diagnose_date'];
    $_SESSION['bsm']['edit']['hwork_person_uuid'] = $rs->fields['hwork_person_uuid'];
    $_SESSION['bsm']['edit']['hwork_full_name'] = $rs->fields['hwork_full_name'];
    $_SESSION['bsm']['edit']['facility_uuid'] = $rs->fields['facility_uuid'];
    $_SESSION['bsm']['edit']['facility_name'] = $rs->fields['facility_name'];
    $_SESSION['bsm']['edit']['location_uuid'] = $rs->fields['location_uuid'];
    $_SESSION['bsm']['edit']['location_name'] = $rs->fields['location_name'];
    $_SESSION['bsm']['edit']['notes'] = $rs->fields['notes'];
    
    //echo "whereis".$_SESSION['bsm']['edit']['disease'];
}
/**
 * @name    Edit Form
 *
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_bsm_edit_entry($errors=false){
    global $global;
    global $conf;
    
    $_SESSION['bsm']['edit']['service_uuid']=$_SESSION['bsm']['edit']['case_uuid'] = $_GET['rtnid'];
	
    //user cannot change the case_uuid or the case report date
    shn_form_fopen("edit&entity=cases&rtnid=".$_SESSION['bsm']['edit']['case_uuid']."",null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Details for Case ID: ').$_SESSION['bsm']['edit']['case_uuid']._(' reported on date: ').$_SESSION['bsm']['edit']['case_datetime']);

    //load disease diagnosis details
    shn_form_fsopen(_('Diagnosis details'));
    ?><TABLE>
    <THEAD>
        <TD><?= _('Disease');?></TD>
        <TD><?= _('Diagnose Date');?></TD>
        <TD><?= _('Carrier Agent');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <TD><?php
    /*
    echo $_SESSION['bsm']['edit']['disease'] ?
        '<p align="center"><a title="'._('Edit').'" href="index.php?mod='.
        $global['module'].'&act=search&entity=disease&seq=lukup'.$_SESSION['bsm']['edit']['disease'].'">'.$_SESSION['bsm']['edit']['disease'].'</a><br>'._("     (Click to change)").'</p>'
        : '<p align="left"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=disease&seq=lukup&rtnfrm=cases&rtnfk=disease&rtnid='.$_SESSION['bsm']['edit']['service_uuid'].'">'._("Click to Add a disease").'</a></p>' ;
    */
    echo $_SESSION['bsm']['edit']['disease'] ?
        '<p align="center"><a title="'._('Edit').'" href="index.php?mod='.
        $global['module'].'&act=search&entity=disease&seq=lukup&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'&current_value='.$_SESSION['bsm']['edit']['disease'].'">'.$_SESSION['bsm']['edit']['disease'].'</a><br>'._("     (Click to change)").'</p>'
        : '<p align="left"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=disease&seq=lukup&rtnfrm=cases&rtnfk=disease&rtnid='.$_SESSION['bsm']['edit']['service_uuid'].'">'._("Click to Add a disease").'</a></p>' ;
    ?></TD>
    <TD><CENTER><?php
    shn_form_date(null,'disease_diagnose_date',array('value'=>$_SESSION['bsm']['edit']['disease_diagnose_date']));
    ?></CENTER></TD>
    <TD><CENTER><?php
    shn_form_text(null,'disease_carry_agent','size="20"',array('value'=>$_SESSION['bsm']['edit']['disease_carry_agent'], 'help' => _('Enter full or part of the facility name.'), 'req'=>false));
    ?></CENTER></TD>
    </TABLE><?php echo '<br>';

    //retieve disease symptoms
    $dis = $_SESSION['bsm']['edit']['disease'];
    //print $dis;
    $sql = "SELECT symptom FROM bsm_dis_symp WHERE disease='$dis'";
    //$sql = "SELECT s.symptom AS symptom, s.symp_code as symp_code FROM bsm_case_symp bs INNER JOIN bsm_symptom s ON bs.symptom=s.symptom WHERE bs.deactivate_dt IS NULL AND bs.case_uuid = '".$_SESSION['bsm']['edit']['case_uuid']."'";
    $arrsymp = $global['db']->Execute($sql);
//print $sql;
    //retieve disease signs
    //$sql = "SELECT s.sign AS sign, s.sign_code AS sign_code  FROM bsm_case_sign bs INNER JOIN bsm_sign s ON bs.sign=s.sign WHERE bs.deactivate_dt IS NULL AND bs.case_uuid = '".$_SESSION['bsm']['edit']['case_uuid']."'";
    $sql = "SELECT sign FROM bsm_dis_sign WHERE disease='$dis'";
    $arrsign = $global['db']->Execute($sql);

    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Symptoms and Signs'));
    ?>
    <TABLE>
    <div id = "symptom_table">
    <TD>
    <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=symptom&seq=lukup&rtnfrm=cases&rtnid='
                .$dis.'&caseid='.$_SESSION['bsm']['edit']['case_uuid'].'">'."Add".'</a><br>'; ?>
    <TABLE>
    <THEAD>
        <TD><?= _('Symptom');?></TD>
        <TD><?= _('Code');?></TD>
				<TD><?php echo _('Action'); ?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
		$delete = _('Delete');
    if($arrsymp!=null)
    {
        foreach($arrsymp as $symp)
        {
    ?><TR>
        <TD> <?php   echo '<a title="'._('Edit').'" href="index.php?mod='.$global['module'].
                '&act=edit&entity=symptom&seq=lukup&rtnfrm=cases&rtnid='
                .$symp['symptom'].'">'.$symp['symptom'].'</a><br>'; ?> </TD>
        <TD> <?php   echo $symp['symp_code'] ? $symp['symp_code'].'<br>' : ''; ?> </TD>
				<TD> <?php   echo '<a title="'._('Delete').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=cases&sympid='.$symp['symptom'].'&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'.$delete.'</a><br>'  ; ?> </TD>
    </TR><?php
        }
    }
    ?></TABLE>
    </TD>
    </div>

    <TD>
    <?php echo "     "; ?>
    </TD>
    <div id = "sign_table">
    <TD>
        <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=sign&seq=lukup&rtnfrm=cases&rtnid='
                .$dis.'&caseid='.$_SESSION['bsm']['edit']['case_uuid'].'">'."Add".'</a><br>'; ?>
    <TABLE>
    <THEAD>
        <TD><?= _('Sign');?></TD>
        <TD><?= _('Code');?></TD>
				<TD><?php echo _('Action'); ?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrsign!=null)
    {
        foreach($arrsign as $sign)
        {
        ?><TR>
            <TD> <?php echo '<a title="'._('Edit').'" href="index.php?mod='.$global['module'].
                '&act=edit&entity=sign&seq=lukup&rtnfrm=cases&rtnid='
                .$sign['sign'].'">'.$sign['sign'].'</a><br>';//echo $sign['sign'] ? $sign['sign'].'<br>' : ''; ?> </TD>
            <TD> <?php echo $sign['sign_code'] ? $sign['sign_code'].'<br>' : ''; ?> </TD>
						<TD> <?php   echo '<a title="'._('Delete').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=cases&signid='.$sign['sign'].'&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'.$delete.'</a><br>'  ; ?> </TD>
        </TR><?php
        }
    }
    ?></TABLE>
    </TD></div>
    <TD><CENTER><?php
    shn_form_textarea(_('Case notes'),'notes',null,array('value'=>$_SESSION['bsm']['edit']['notes'], 'help' => _('Additional comments about the Symptoms and Signs can be stored here.'), 'req'=>false));
    ?></CENTER></TD>
    </TABLE><?php echo '<br>';

    
    //load case status history
    
    /*
    $sql = "SELECT csl.case_status AS case_status, csl.case_status_dt AS status_datetime, csl.auth_p_uuid AS authorize_person_uuid, ";
    $sql .= "(SELECT p.last_name FROM bsm_person p WHERE deactivate_dt IS NULL AND p_uuid = csl.auth_p_uuid) AS authorize_person, ";
    $sql .= "csl.notes AS status_notes FROM bsm_case_status cs INNER JOIN bsm_case_status_log csl ON csl.case_status = cs.case_status ";
    $sql .= "INNER JOIN bsm_cases c ON c.case_uuid = csl.case_uuid WHERE csl.deactivate_dt IS NULL ";
    $sql .= "AND csl.case_uuid = '".$_SESSION['bsm']['edit']['case_uuid']."'";
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='edit')
        $select = true;
    ?>
    <div id = "case_status_table" align="center">
    <TABLE>
    <THEAD>
        <TD><?= _('Status');?></TD>
        <TD><?= _('Status Date');?></TD>
        <TD><?= _('Authorized By');?></TD>
        <TD><?= _('Status Notes');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($details!=null)
    {
        foreach($details as $detail)
        {
    ?><TR>
        <TD> <?php   echo $detail['case_status'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=casestatus&rtnid='.$detail['case_uuid'].'">'.
                        $detail['case_uuid'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['Status Date'] ? $detail['status_datetime'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['Authorized by'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=person&rtnid='.$detail['authorize_person_uuid'].'">'.
                        $detail['authorize_person'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['statu_notes'] ? $detail['status_notes'].'<br>' : ''; ?> </TD>
    </TR><?php
        }
    }
    ?></TABLE></div><?php
    echo '<p align="center">'._("To change the status ").'<a title="'._('Edit').'" href="index.php?mod='.
          $global['module'].'&act=add&entity=casestatus&rtnid='.$detail['authorize_person_uuid'].'">'._("Click").'</a></p><br>';
    */
    
    shn_form_fsclose();

    shn_form_fsopen(_('Patient details'));
    ?><DIV id = "patient_details" align="center"><TABLE>
    <THEAD>
        <TD><?= _('Name');?></TD>
        <TD><?= _('Gender');?></TD>
        <TD><?= _('Age');?></TD>
        <TD><?= _('Age Group');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <TD><CENTER><?php
    echo $_SESSION['bsm']['edit']['patient_full_name'] ?
        '<p align="left">'.$_SESSION['bsm']['edit']['patient_full_name'].'<a title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&person=patient&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'."<br> (update)".'</a></p>'
        : '<p align="left"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=cases&person=patient&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'."Click to Add".'</a></p>' ;
    ?></CENTER></TD>
    <TD><CENTER><?php
    $sql = "SELECT DISTINCT option_description AS gender FROM field_options WHERE field_name = 'opt_gender'";
    $rsql = $global['db']->Execute($sql);
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,null, 'patient_gender',null,array('value'=>$_SESSION['bsm']['edit']['patient_gender'],'help' => _('Select a disease type.'), 'req'=>false));
    ?></CENTER></TD>
    <TD><CENTER><?php
    shn_form_text(null,'patient_age','size="5"',array('value'=>$_SESSION['bsm']['edit']['patient_age'], 'help' => _('Enter full or part of the facility name.'), 'req'=>false));
    ?></CENTER></TD>
    <TD><CENTER><?php
    $sql = "SELECT DISTINCT option_description AS age_group FROM field_options WHERE field_name = 'opt_age_group'";
    $rsql = $global['db']->Execute($sql);
    //print $sql;
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
		$_SESSION['bsm']['edit']['rtnid'] = $_REQUEST['rtnid'];
		
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,null, 'patient_age_group',null,array('value'=>$_SESSION['bsm']['edit']['patient_age_group'],'help' => _('Select a disease type.'), 'req'=>false));
    ?></CENTER></TD>
    </TABLE></DIV><?php echo '<br>';
    shn_form_fsclose();
		//var_dump($_SESSION['bsm']['edit']);
    shn_form_fsopen(_('Health worker, facility, location details'));

    	// Health worker
    	echo $_SESSION['bsm']['edit']['hwork_full_name'] ?
    	'<center>Health Worker full name : <strong><a href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&person=healthworker&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['rtnid']/*$_SESSION['bsm']['edit']['hwork_person_uuid']*/.'">'.$_SESSION['bsm']['edit']['hwork_full_name']."</a></strong></center>"
    	: '<center>Health Worker full name : <strong><a href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&person=healthworker&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'.$_SESSION['bsm']['edit']['hwork_full_name']."Add</a></strong></center>";
    	
  		 // Facility Name
  		 echo $_SESSION['bsm']['edit']['facility_name'] ?
		 '<center>Facility name : <strong><a href="index.php?mod='.$global['module'].'&act=search&entity=facility&seq=lukup&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['rtnid'].'">'.$_SESSION['bsm']['edit']['facility_name'].'</a></strong></center>'
  		 :'<center>Facility name : <strong><a href="index.php?mod='.$global['module'].'&act=search&entity=facility&seq=lukup&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">Add</a></strong></center>';
  		 
  		 // Location Name
  		 echo $_SESSION['bsm']['edit']['location_name'] ?
		 '<center>Location Name : <strong><a href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lukup&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['rtnid'].'">'.$_SESSION['bsm']['edit']['location_name'].'</a></strong></center>'
  		 :'<center>Location Name : <strong><a href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lukup&rtnfrm=cases&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">Add</a></strong></center>';
  		 
  		 
    
    shn_form_fsclose();

    shn_form_submit(_('Save'));
    shn_form_fsclose();
}
/**
 * @name    view case symptoms
 * @deprecated remove this function when sure
 * @global <type> $global
 * @global <type> $conf @d
 */
function shn_bsm_symp_vw(){
    global $global;
    global $conf;
    
    //retieve disease symptoms
    $sql = "SELECT s.symptom, s.symp_code FROM bsm_symptom s INNER JOIN bsm_dis_symp ds ON ds.symptom = s.symptom ";
    $sql .= "INNER JOIN bsm_disease d ON d.disease = ds.disease WHERE ds.deactivate_dt IS NULL AND ds.disease = '".$_SESSION['bsm']['edit']['disease']."'";
    $arrsymp = $global['db']->Execute($sql);
    
    //retieve disease signs
    $sql = "SELECT s.sign, s.sign_code FROM bsm_sign s INNER JOIN bsm_dis_sign ds ON ds.sign = s.sign ";
    $sql .= "INNER JOIN bsm_disease d ON d.disease = ds.disease WHERE ds.deactivate_dt IS NULL AND ds.disease = '".$_SESSION['bsm']['edit']['disease']."'";
    $arrsign = $global['db']->Execute($sql);

    //retieve disease causality factors
    $sql = "SELECT cf.caus_fact, cf.caus_fact_code FROM bsm_caus_fact cf INNER JOIN bsm_dis_caus_fact dsf ON dsf.caus_fact = dsf.caus_fact ";
    $sql .= "INNER JOIN bsm_disease d ON d.disease = dsf.disease WHERE dsf.deactivate_dt IS NULL AND dsf.disease = '".$_SESSION['bsm']['edit']['disease']."'";
    $arrcf = $global['db']->Execute($sql);

    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Symptoms, Signs, and Causality Factors (to edit or further details clik on the record)'));
    ?>
    <TABLE>
    <div id = "symptom_table">
    <TD>
    <TABLE>
    <THEAD>
        <TD><?= _('Symptom');?></TD>
        <TD><?= _('Code');?></TD>
				<?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrsymp!=null)
    {
        foreach($arrsymp as $symp)
        {
    ?><TR>
        <TD> <?php   echo $symp['symptom'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=symptom&rtnid='.$symp['symptom'].'">'.
                        $symp['symptom'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $symp['symp_code'] ? $symp['symp_code'].'<br>' : ''; ?> </TD>
				
    </TR><?php
        }
    }
    ?></TABLE>
    </TD>
    </div>

    <TD>
    <?php echo "     "; ?>
    </TD>

    <div id = "sign_table">
    <TD>
    <TABLE>
    <THEAD>
        <TD><?= _('Sign');?></TD>
        <TD><?= _('Code');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrsign!=null)
    {
        foreach($arrsign as $sign)
        {
        ?><TR>
            <TD> <?php echo $sign['sign'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=symptom&rtnid='.$sign['sign'].'">'.
                        $sign['sign'].'</a><br>' : ''; ?> </TD>
            <TD> <?php echo $sign['sign_code'] ? $sign['sign_code'].'<br>' : ''; ?> </TD>
        </TR><?php
        }
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=symptom&seq=lookup&rtnid='.
        $_SESSION['bsm']['edit']['disease'].'">'." click to ADD a new Sign".'</a><br>';
    }
    ?></TABLE>
    </TD></div>

    <div id = "causality_factor_table">
    <TD>
    <TABLE>
    <THEAD>
        <TD><?= _('Causality');?></TD>
        <TD><?= _('Code');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrcf!=null)
    {
        foreach($arrcf as $causfact)
        {
        ?><TR>
            <TD> <?php echo $causfact['caus_fact'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=symptom&rtnid='.$causfact['caus_fact'].'">'.
                        $causfact['caus_fact'].'</a><br>' : ''; ?> </TD>
            <TD> <?php echo $causfact['caus_fact_code'] ? $causfact['caus_fact_code'].'<br>' : ''; ?> </TD>
        </TR><?php
        }
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=symptom&seq=lookup&rtnid='.
        $_SESSION['bsm']['edit']['disease'].'">'." click to ADD a new Sign".'</a><br>';
    }
    ?></TABLE>
    </TD></div>

    </TABLE><?php

    shn_form_fsclose();
}
/**
 * Validation of the Edit Form
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_validate(){

	global $global;
	global $conf;

	$error_flag=false;

	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

	$local_post['case_uuid'] = $_SESSION['bsm']['edit']['case_uuid'];
	//clean
	$_SESSION['bsm']['edit']=null;
	$_SESSION['bsm']['edit']=$local_post;

//	if(!isset($local_post['patient_person_uuid'])){
//		add_error(_("Please add patient name or add anonymous from the list of patients; null values not allowed"));
//		$error_flag=true;
//	}
	if(!isset($local_post['patient_gender'])){
		//add_error(_("Please select the patient gender; null values not allowed"));
		$error_flag=true;
	}
//	if(!isset($local_post['location_uuid'])){
//		add_error(_("Please identify the location; null values not allowed"));
//		$error_flag=true;
//	}
        //$_SESSION['bsm']['edit']['person_uuid'] = $local_post['person_uuid'];
	if($error_flag)
	return false;
	else{return true;}
}
/**
 * Confirmation page
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_confirm(){

    global $global;
    global $conf;

    $_SESSION['bsm']['edit']['patient_person_uuid'] = isset($_POST['patient_person_uuid']) ? trim($_POST['patient_person_uuid']) : null;
    $_SESSION['bsm']['edit']['patient_full_name'] = isset($_POST['patient_full_name']) ? trim($_POST['patient_full_name']) : null;
    $_SESSION['bsm']['edit']['patient_gender'] = isset($_POST['patient_gender']) ? trim($_POST['patient_gender']) : null;
    $_SESSION['bsm']['edit']['patient_age_group'] = isset($_POST['patient_age_group']) ? trim($_POST['patient_age_group']) : null;
    $_SESSION['bsm']['edit']['patient_age'] = isset($_POST['patient_age']) ? trim($_POST['patient_age']) : null;
    $_SESSION['bsm']['edit']['disease'] = isset($_POST['disease']) ? trim($_POST['disease']) : null;
    $_SESSION['bsm']['edit']['disease_diagnose_date'] = isset($_POST['disease_diagnose_date']) ? trim($_POST['disease_diagnose_date']) : null;
    $_SESSION['bsm']['edit']['disease_carry_agent'] = isset($_POST['disease_carry_agent']) ? trim($_POST['disease_carry_agent']) : null;
    $_SESSION['bsm']['edit']['hwork_person_uuid'] = isset($_POST['hwork_person_uuid']) ? trim($_POST['hwork_person_uuid']) : null;
    $_SESSION['bsm']['edit']['hwork_full_name'] = isset($_POST['hwork_full_name']) ? trim($_POST['hwork_full_name']) : null;
    $_SESSION['bsm']['edit']['facility_uuid'] = isset($_POST['facility_uuid']) ? trim($_POST['facility_uuid']) : null;
    $_SESSION['bsm']['edit']['facility_name'] = isset($_POST['facility_name']) ? trim($_POST['facility_name']) : null;
    $_SESSION['bsm']['edit']['location_uuid'] = isset($_POST['location_uuid']) ? trim($_POST['location_uuid']) : null;
    $_SESSION['bsm']['edit']['location_name'] = isset($_POST['location_name']) ? trim($_POST['location_name']) : null;
    $_SESSION['bsm']['edit']['notes'] = isset($_POST['notes']) ? trim($_POST['notes']) : null;
    $_SESSION['bsm']['edit']['modify_datetime'] = getdate();
    $_SESSION['bsm']['edit']['modify_user'] = "user";
    $_SESSION['bsm']['edit']['modify_process'] = $conf['host'];

    shn_form_hidden(array('seq'=>'commit'));
}
/* {{{ Edit Commit */
/**
 * @name    Commits changes to the database
 * @tutorial    all filled attributes releveant the the bsm_cases and only those values are written to the database.
 * @access public
 * @return void
 */
function shn_bsm_edit_commit(){
	
	global $global;
	global $conf;

	if(isset($_SESSION['bsm']['edit']['patient_person_uuid']))
		{$update_array['pat_p_uuid'] = $_SESSION['bsm']['edit']['patient_person_uuid'];}
	if(isset($_SESSION['bsm']['edit']['patient_full_name']))
		{$update_array['pat_full_name'] = $_SESSION['bsm']['edit']['patient_full_name'];}
	if(isset($_SESSION['bsm']['edit']['patient_gender']))
		{$update_array['gender'] = $_SESSION['bsm']['edit']['patient_gender'];}
	if(isset($_SESSION['bsm']['edit']['patient_age_group']))
		{$update_array['age_grp'] = $_SESSION['bsm']['edit']['patient_age_group'];}
	if(isset($_SESSION['bsm']['edit']['patient_age']))
		{$update_array['age'] = $_SESSION['bsm']['edit']['patient_age'];}
	if(isset($_SESSION['bsm']['edit']['disease']))
		{$update_array['disease'] = $_SESSION['bsm']['edit']['disease'];}
	if(isset($_SESSION['bsm']['edit']['disease_diagnose_date']))
		{$update_array['dis_dia_dt'] = $_SESSION['bsm']['edit']['disease_diagnose_date'];}
	if(isset($_SESSION['bsm']['edit']['disease_carry_agent']))
		{$update_array['agent'] = $_SESSION['bsm']['edit']['disease_carry_agent'];}
	if(isset($_SESSION['bsm']['edit']['hwork_person_uuid']))
		{$update_array['hwork_p_uuid'] = $_SESSION['bsm']['edit']['hwork_person_uuid'];}
	if(isset($_SESSION['bsm']['edit']['hwork_full_name']))
		{$update_array['hwork_full_name'] = $_SESSION['bsm']['edit']['hwork_full_name'];}
	if(isset($_SESSION['bsm']['edit']['facility_uuid']))
		{$update_array['fclty_uuid'] = $_SESSION['bsm']['edit']['facility_uuid'];}
	if(isset($_SESSION['bsm']['edit']['facility_name']))
		{$update_array['fclty_name'] = $_SESSION['bsm']['edit']['facility_name'];}
	if(isset($_SESSION['bsm']['edit']['location_uuid']))
		{$update_array['loc_uuid'] = $_SESSION['bsm']['edit']['location_uuid'];}
	if(isset($_SESSION['bsm']['edit']['location_name']))
		{$update_array['loc_name'] = $_SESSION['bsm']['edit']['location_name'];}
	if(isset($_SESSION['bsm']['edit']['notes']))
		{$update_array['notes'] = $_SESSION['bsm']['edit']['notes'];}
	if(isset($_SESSION['bsm']['edit']['modify_datetime']))
		{$update_array['modify_dt'] = $_SESSION['bsm']['edit']['modify_datetime'];}
	if(isset($_SESSION['bsm']['edit']['modify_user']))
		{$update_array['modify_by'] = $_SESSION['bsm']['edit']['modify_user'];}
	if(isset($_SESSION['bsm']['edit']['modify_process']))
		{$update_array['modify_proc'] = $_SESSION['bsm']['edit']['modify_process'];}
	
	$case_uuid = $_SESSION['bsm']['edit']['case_uuid'];
	
	//shn_db_update($update_array,'bsm_cases',' WHERE case_uuid = '.$_SESSION['bsm']['edit']['case_uuid']);
	$sql = "UPDATE bsm_cases SET ";

    foreach($update_array as $k => $v){
        if($v == '')
            $sql .= "$k = NULL, ";
        else
            $sql .= "$k = ".shn_db_clean($v).", ";
    }
	$sql = substr($sql,0,strlen($sql)-2);
    
    $sql .= " WHERE case_uuid = '$case_uuid'";
    //print "<br>Case ID is ".$_SESSION['bsm']['edit']['case_uuid'];
    
	if($conf['debug']) {
        echo "<hr>".$sql.' '.$key."<hr>";
    }
    
	global $global, $conf;
	$res=$global['db']->Execute($sql);
	if($res) {
		add_confirmation("Case was saved successfully!");
	} else {
		add_error("Case can not be saved!");
	}
	
}
/**
 * @name    Commits loouk up value
 * @tutorial    case by case if the symptoms, signs, patient details, and health worker details are not
 *              in the database then the referred values are commited to the database relevant tables.
 *              Programer must pass the case_uuid ($pk_uuid), symptom, sign, or p_uuid (fk_uuid) and the
 *              name of the fk attribute to the function.
 * @access  public
 * @return  void
 * @param   mixed $pk_uuid
 * @param   mixed $fk_uuid
 * @param   string $fk_name
 */
function shn_bsm_edit_commit_lukup($pk_uuid=null,$fk_uuid=null,$fk_name=null, $disease=null){

    global $global;
    global $conf;
    $db = $global['db'];
//print "<br>pk_uuid=".$pk_uuid." fk_uuid=".$fk_uuid." fk_name=".$fk_name."<br>";
    if ($pk_uuid==null || $fk_uuid==null){
    	add_error(_("Your lookup selection is invalid, failed to return the values!"));
    } else {
        switch ($_GET['entity'])
        {
            case 'symptom':
                //$sql = "SELECT 1 FROM bsm_case_symp WHERE deactivate_dt IS NULL AND case_uuid = '".$pk_uuid."' AND symptom = '".$fk_uuid."'";
                $sql = "SELECT 1 FROM bsm_dis_symp WHERE deactivate_dt IS NULL AND disease ='".$disease."' AND symptom = '".$fk_uuid."'";
            	//print $sql;
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("This symptom: ").$fk_uuid._(" already recorded to this case: ").$pk_uuid);}
                else{
                    //$insert_array['case_uuid'] = $pk_uuid;
                    //$insert_array['symptom'] = $fk_uuid;
                    //shn_db_insert($insert_array,'bsm_case_symp',null,$pk_uuid);
                   $insert_array['disease'] = $disease;
                   $insert_array['symptom'] = $fk_uuid;
                   shn_db_insert($insert_array,'bsm_dis_symp',null,$disease);
                   //shn_bsm_edit();
                }
                break;
            case 'sign':
                //$sql = "SELECT 1 FROM bsm_case_sign WHERE deactivate_dt IS NULL AND case_uuid = '".$pk_uuid."' AND sign = '".$fk_uuid."'";
                $sql = "SELECT 1 FROM bsm_dis_sign WHERE deactivate_dt IS NULL AND disease ='".$disease."' AND sign = '".$fk_uuid."'";
            	$rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("This sign: ").$fk_uuid._(" already recorded to this case: ").$pk_uuid);}
                else{
                   // $insert_array['case_uuid'] = $pk_uuid;
                    //$insert_array['sign'] = $fk_uuid;
                   // shn_db_insert($insert_array,'bsm_case_sign',null,$pk_uuid);
                   $insert_array['disease'] = $disease;
                   $insert_array['sign'] = $fk_uuid;
                   shn_db_insert($insert_array,'bsm_dis_sign',null,$disease);
                }
                break;
            case 'disease':
                //$sql = "SELECT 1 FROM bsm_cases WHERE deactivate_dt IS NULL AND case_uuid = '".$pk_uuid."' AND disease = '".$fk_uuid."'";
                $sql = "SELECT 1 FROM bsm_cases WHERE deactivate_dt IS NULL AND case_uuid = '".$pk_uuid."'";
                
                //print $sql;
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>1){add_error(_("This disease: ").$fk_uuid._(" already recorded to this case: ").$pk_uuid);}
                else{
                    $insert_array['case_uuid'] = $pk_uuid;
                    $insert_array['disease'] = $fk_uuid;
                    $sql = "update bsm_cases set disease='{$insert_array['disease']}' where case_uuid='{$insert_array['case_uuid']}'";
                    //shn_db_insert($insert_array,'bsm_case_symp',null,$pk_uuid);
                    //shn_db_update($insert_array, 'bsm_cases',null);
                    $global['db']->Execute($sql);
                }
                break;
            
        	case 'facility':
        		/*
				 $sql = "SELECT 1 FROM bsm_dis_caus_fact WHERE deactivate_dt IS NULL AND disease = '".$pk_uuid."' AND caus_fact = '".$fk_uuid."'";
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("A record with same disease and causality factor exisits"));}
                else{
                    //$insert_array['disease'] = $pk_uuid;
                    //$insert_array['caus_fact'] = $fk_uuid;
                    
                    
                    
             }
             */
        		
        		
                    
        			$insert_array['case_uuid'] = $pk_uuid;
                    $insert_array['fclty_uuid'] = $fk_uuid;
                    $sql = "select fclty_type from bsm_facility where fclty_uuid='{$insert_array['fclty_uuid']}'";
                    $result = $db->Execute($sql);
                    $name = $result->fields['fclty_type'];
                    $sql="update bsm_cases set fclty_uuid='{$insert_array['fclty_uuid']}',fclty_name='{$name}' where case_uuid='{$insert_array['case_uuid']}';
                    ";
                    $db->Execute($sql);
                break;
        		
            case 'person':
            	/*
                $sql = "SELECT 1 FROM bsm_dis_caus_fact WHERE deactivate_dt IS NULL AND disease = '".$pk_uuid."' AND caus_fact = '".$fk_uuid."'";
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("A record with same disease and causality factor exisits"));}
                else{
                    $insert_array['disease'] = $pk_uuid;
                    $insert_array['caus_fact'] = $fk_uuid;
                    shn_db_insert($insert_array,'bsm_dis_caus_fact',null,$pk_uuid);
                }
                */
            	//if health worker handle differently
            	
            	
                	$insert_array['case_uuid'] = $pk_uuid;
                    $insert_array['person_uuid'] = $fk_uuid;
                    
                    //Based on the p_uuid, figure out whether person is Patient or Health Worker
                    $sql = "select prsn_role from bsm_prsn_type where prsn_type=(select prsn_type from bsm_prsn_link_type where p_uuid='{$insert_array['person_uuid']}')";
                    //echo "role".$sql;
                    $result = $db->Execute($sql);
                    $person_type = $result->fields['prsn_role'];
                    
                    $sql = "select * from bsm_person where p_uuid='{$insert_array['person_uuid']}'";
            		//echo $sql."===";
                    $result = $db->Execute($sql);
                    $name=$result->fields['first_name'];
                    $name .= " ".$result->fields['last_name'];
                    //echo "Person type is |".$person_type."|";
                    switch ($person_type){
            		case 'Patient':
            			$sql="update bsm_cases set pat_p_uuid='{$insert_array['person_uuid']}',pat_full_name='{$name}' where case_uuid='{$insert_array['case_uuid']}';
                    ";
                    	//echo "Person-".$sql;
                    	$db->Execute($sql);
            			break;
            		case	'Health Care Worker':
            			$sql="update bsm_cases set hwork_p_uuid='{$insert_array['person_uuid']}',hwork_full_name='{$name}' where case_uuid='{$insert_array['case_uuid']}'";
                    	//echo "Health Worker-".$sql;
                    	$db->Execute($sql);
            			break;
            		default:
            			$sql="update bsm_cases set pat_p_uuid='{$insert_array['person_uuid']}',pat_full_name='{$name}' where case_uuid='{$insert_array['case_uuid']}'";
                    	//echo "None-".$sql;
                    	$db->Execute($sql);
            			break;
                    }
                
                break;
			case 'location':
				/*
				 $sql = "SELECT 1 FROM bsm_dis_caus_fact WHERE deactivate_dt IS NULL AND disease = '".$pk_uuid."' AND caus_fact = '".$fk_uuid."'";
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("A record with same disease and causality factor exisits"));}
                else{
                    //$insert_array['disease'] = $pk_uuid;
                    //$insert_array['caus_fact'] = $fk_uuid;
                    
             }
             	*/
					//do above duplicate check
					
             		$insert_array['case_uuid'] = $pk_uuid;
                    $insert_array['location_uuid'] = $fk_uuid;
                    $sql = "select loc_name from bsm_location where loc_uuid='{$insert_array['location_uuid']}'";
                    $result = $db->Execute($sql);
                    $name=$result->fields['loc_name'];
                    $sql="update bsm_cases set loc_uuid='{$insert_array['location_uuid']}',loc_name='{$name}' where case_uuid='{$insert_array['case_uuid']}';
                    ";
//print $sql;
                    $db->Execute($sql);
                break;

            default:
                break;
        }
    }
}


?>