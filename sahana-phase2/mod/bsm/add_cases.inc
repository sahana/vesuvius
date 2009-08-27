<?php
/**
 * Add Health cases
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
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/* {{{ Includes */
include_once($global['approot']."/inc/lib_uuid.inc");
/* {{{ Tools */
/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post 
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post){
    //trim them all
    foreach($_POST as $k => $v){
        $v = trim($v);
        if($v != '')
            $local_post[$k] = $v;
    }
}
/* {{{ Add Entry From */
/**
 * This is the Add Entry Form
 * @param mixed $errors 
 * @access public
 * @return void
 */
function shn_bsm_add_entry($errors=false){
    global $global;
    global $conf;

    $_SESSION['bsm']['main']['caseid']=shn_create_uuid();
    
    shn_form_fopen('edit&entity=cases&do=addcase&rtnid='.$_SESSION['bsm']['main']['caseid'].'',null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_hidden(array('entity'=>$_GET['entity']));
    shn_form_fsopen(_('Complete the ').$_REQUEST['entity']._(' details and save the record'));
	
    //Case UUID
    shn_form_text(_('Case UUID'),'case_uuid','size="8" disabled',array('value'=>$_SESSION['bsm']['main']['caseid'],'help' => _('Unique Identifier for Case')));
    $date=date("Y-m-d");
    shn_form_date(_('Case Report Date'),'case_rpt_date',array('req'=>true, 'value'=>$date));
    shn_form_textarea(_('Case Notes'),'case_notes');
   
    shn_form_submit(_('Save'));
    shn_form_fsclose();

 }
 
 function shn_bsm_add_entry_o($errors=false){
 	global $global;
    global $conf;

    //user cannot change the case_uuid or the case report date
    shn_form_fopen("add&entity=cases",null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_hidden(array('entity'=>$_GET['entity']));
	
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_hidden(array('entity'=>$_GET['entity']));
    
    shn_form_fsopen(_('Complete the Case')._(' details and save the record'));
	//Case UUID
    shn_form_text(_('Case UUID'),'case_uuid','size="4" disabled',array('value'=>2,'help' => _('Unique Identifier for Case')));
    shn_form_date(_('Case Date'),'case_date',array('req'=>true));
    shn_form_fsclose();
        
    //load disease diagnosis details
    
    shn_form_fsopen(_('Add Diagnosis details'));
    ?><TABLE>
    <THEAD>
        <TD><?= _('Disease');?></TD>
        <TD><?= _('Diagnose Date');?></TD>
        <TD><?= _('Carrier Agent');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <TD><?php
    
    echo $_SESSION['bsm']['add']['disease'] ?
        '<p align="center"><a title="'._('Edit').'" href="index.php?mod='.
        $global['module'].'&act=search&entity=disease&seq=lukup'.$_SESSION['bsm']['edit']['disease'].'">'.$_SESSION['bsm']['edit']['disease'].'</a><br>'._("     (Click to change)").'</p>'
        : '<p align="left"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=disease&seq=lukup&rtnfrm=cases&rtnid=">'._("Click to Add a disease").'</a></p>' ;
        
    /*
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=disease&seq=lukup&rtnfrm=cases">'."ADD".'</a><br>'; ?>
    */
    ?>
    </TD>
    <TD><CENTER><?php
    shn_form_date(null,'disease_diagnose_date');
    ?></CENTER></TD>
    <TD><CENTER><?php
    shn_form_text(null,'disease_carry_agent','size="20"',array('value'=>$_SESSION['bsm']['edit']['disease_carry_agent'], 'help' => _('Enter full or part of the facility name.'), 'req'=>false));
    ?></CENTER></TD>
    </TABLE><?php echo '<br>';

    //retieve disease symptoms
    $sql = "SELECT symptom FROM bsm_case_symp WHERE deactivate_dt IS NULL AND case_uuid = '".$_SESSION['bsm']['edit']['case_uuid']."'";
    $arrsymp = $global['db']->Execute($sql);

    //retieve disease signs
    $sql = "SELECT sign FROM bsm_case_sign WHERE deactivate_dt IS NULL AND case_uuid = '".$_SESSION['bsm']['edit']['case_uuid']."'";
    $arrsign = $global['db']->Execute($sql);

    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Add Symptoms and Signs'));
    ?>
    <TABLE>
    <div id = "symptom_table">
    <TD>
    <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=symptom&seq=lukup&rtnfrm=cases&rtnid='
                .$_SESSION['bsm']['edit']['case_uuid'].'">'."ADD".'</a><br>'; ?>
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
        <TD> <?php   echo $symp['symptom'] ? $symp['symptom'].'<br>' : ''; ?> </TD>
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
        <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=sign&seq=lukup&rtnfrm=cases&rtnid='
                .$_SESSION['bsm']['edit']['case_uuid'].'">'."ADD".'</a><br>'; ?>
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
            <TD> <?php echo $sign['sign'] ? $sign['sign'].'<br>' : ''; ?> </TD>
            <TD> <?php echo $sign['sign_code'] ? $sign['sign_code'].'<br>' : ''; ?> </TD>
        </TR><?php
        }
    }
    ?></TABLE>
    </TD></div>
    <TD><CENTER><?php
    shn_form_textarea(_('Case notes'),'notes',null,array('value'=>$_SESSION['bsm']['edit']['gender'], 'help' => _('Select the patient gender.'), 'req'=>false));
    ?></CENTER></TD>
    </TABLE><?php echo '<br>';

    //load case status history
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
        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'." (click to change)".'</a></p>'
        : '<p align="left"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['case_uuid'].'">'."Click to Add".'</a></p>' ;
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
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,null, 'patient_age_group',null,array('value'=>$_SESSION['bsm']['edit']['patient_age_group'],'help' => _('Select a disease type.'), 'req'=>false));
    ?></CENTER></TD>
    </TABLE></DIV><?php echo '<br>';
    shn_form_fsclose();

    shn_form_fsopen(_('Health worker, facility, location details'));
    echo $_SESSION['bsm']['edit']['hwork_full_name'] ?
        '<p align="center">'.'Health Worker full name: '.$_SESSION['bsm']['edit']['hwork_full_name'].'<a title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['hwork_person_uuid'].'">'." (click to change)".'</a></p>'
        : '<p align="center">'.'Health Worker full name: '.'<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['hwork_person_uuid'].'">'."Click to Add".'</a></p>' ;
    echo $_SESSION['bsm']['edit']['facility_name'] ?
        '<p align="center">'.'Facility name: '.$_SESSION['bsm']['edit']['facility_name'].'<a title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=facility&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['facility_uuid'].'">'." (click to change)".'</a></p>'
        : '<p align="center">'.'Facility name: '.'<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=facility&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['facility_uuid'].'">'."Click to Add".'</a></p>' ;
    echo $_SESSION['bsm']['edit']['location_name'] ?
        '<p align="center">'.'Location name: '.$_SESSION['bsm']['edit']['location_name'].'<a title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['location_uuid'].'">'." (click to change)".'</a></p>'
        : '<p align="center">'.'Location name: '.'<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=facility&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['location_uuid'].'">'."Click to Add".'</a></p>' ;
    shn_form_fsclose();

    shn_form_submit(_('Save'));
    shn_form_fsclose();
 }

/* {{{ Add Entry form Validation */

/**
 * This is the Add Entry Validation function
 * @access public
 * @return void
 */
function shn_bsm_add_validate(){
	global $global;
	global $conf;

	$error_flag=false;

	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

	//$local_post['facility_uuid'] = $_SESSION['bsm']['add']['facility_uuid'];
	//clean
	$_SESSION['bsm']['add']=null;
	$_SESSION['bsm']['add']=$local_post;

	if(!isset($local_post['case_rpt_date'])){
		add_error(_("Please enter the case reported date"));
		$error_flag=true;
	}


//	if(!isset($local_post['Status'])){
//		add_error(_("Please select a facility status; null values not allowed"));
//		$error_flag=true;
//	}
        //$_SESSION['bsm']['edit']['person_uuid'] = $local_post['person_uuid'];
	if($error_flag)
	return false;
	else{return true;}
}

function shn_bsm_add_confirm(){

    global $global;
    global $conf;
        
    //$_SESSION['bsm']['add']['uuid'] = isset($_POST['case_uuid']) ? trim($_POST['case_uuid']) : null;
    $_SESSION['bsm']['add']['uuid'] = $_SESSION['bsm']['main']['caseid'];
    $_SESSION['bsm']['add']['case_rpt_date'] = isset($_POST['case_rpt_date']) ? trim($_POST['case_rpt_date']) : null;
    $_SESSION['bsm']['add']['case_notes'] = isset($_POST['case_notes']) ? trim($_POST['case_notes']) : null;
    //$_SESSION['bsm']['add']['status'] = isset($_POST['status']) ? trim($_POST['status']) : null;
    //$_SESSION['bsm']['add']['create_datetime'] = getdate();
    $_SESSION['bsm']['add']['create_user'] = "user";
    $_SESSION['bsm']['add']['create_process'] = $conf['host'];

    shn_form_hidden(array('seq'=>'commit'));
}

/* {{{ Add Commit */
/**
 * This function commits the given Missing person's data to the databsae.
 * @access public
 * @return void
 */
function shn_bsm_add_commit(){
    // $insert_array[<field_name>] = value
    global $global;
    global $conf;
    $db = $global['db'];

    //if(isset($_SESSION['bsm']['add']['name']) && $_SESSION['bsm']['add']['name']!=null)
    //    {$insert_array['fclty_desc'] = $_SESSION['bsm']['add']['name'];}
//      if(isset($_SESSION['bsm']['add']['category'])){$insert_array['category'] = $_SESSION['bsm']['add']['category'];}
//	if(isset($_SESSION['bsm']['add']['type'])){$insert_array['prsn_type'] = $_SESSION['bsm']['add']['type'];}
//	if(isset($_SESSION['bsm']['add']['status'])){$insert_array['fclty_status'] = $_SESSION['bsm']['add']['status'];}
    if(isset($_SESSION['bsm']['add']['create_datetime']) && $_SESSION['bsm']['add']['create_datetime']!=null){$insert_array['create_dt'] = $_SESSION['bsm']['add']['create_datetime'];}
    if(isset($_SESSION['bsm']['add']['create_user']) && $_SESSION['bsm']['add']['create_user']!=null){$insert_array['create_by'] = $_SESSION['bsm']['add']['create_user'];}
    if(isset($_SESSION['bsm']['add']['create_process']) && $_SESSION['bsm']['add']['create_process']!=null){$insert_array['create_proc'] = $_SESSION['bsm']['add']['create_process'];}
	
    $sql = " insert into bsm_cases (case_uuid,case_dt,notes,create_dt,create_by,create_proc) values ('{$_SESSION['bsm']['add']['uuid']}','{$_SESSION['bsm']['add']['case_rpt_date']}','{$_SESSION['bsm']['add']['case_notes']}','{$_SESSION['bsm']['add']['create_datetime']}','{$_SESSION['bsm']['add']['create_user']}','{$_SESSION['bsm']['add']['create_process']}')";
    //echo  $sql;
    //print $sql;
    $res = $db->Execute($sql);
		if($res) {
			add_confirmation(_('Case added Successfully'));
			} else {
			add_error(_('Error occured while adding case'));
		}
    //shn_db_insert($insert_array,'bsm_facility',true, null);
    
?>
	<p> <a href="index.php?mod=bsm&act=edit&entity=cases&rtnid=<?php echo $_SESSION['bsm']['add']['uuid']?>">Add more details to case</a>.
	</p>
<?php
    
    
    
}



/**
 * This is a buch of javascript helps for the collapse and expanind of a
 * given division.
 * @todo Move to somewhere 
 * @access public
 * @return void
 */
function shn_js_toggle_layer(){
?>
<script language="javascript">
function toggleLayer(whichLayer,whichLayer1)
{
    if (document.getElementById) {
		// this is the way the standards work
		var style1 = document.getElementById(whichLayer).style;
		var style2 = document.getElementById(whichLayer1).style;
		if(style1.display == 'none')
			style1.display = 'block';
		else
			style1.display = 'none';
		if(style2.display == 'none')
			style2.display = 'block';
		else
			style2.display = 'none';
		//style2.display = style2.display? "none":"block";
    } else if (document.all) {
		// this is the way old msie versions work
		var style2 = document.all[whichLayer].style;
		style2.display = style2.display? "none":"block";
    } else if (document.layers) {
		// this is the way nn4 works
		var style2 = document.layers[whichLayer].style;
		style2.display = style2.display? "none":"block";
	}
}
</script>
<?
}
?>