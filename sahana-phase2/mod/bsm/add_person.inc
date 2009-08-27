<?php
/**
 * Add a location
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
    //if($errors)
    //display_errors();

    global $global;
    global $conf;
	$_SESSION['bsm']['add']['case_p_uuid'] = $_REQUEST['rtnid'];
	$_SESSION['bsm']['add']['case_person'] = $_REQUEST['person'];
	
	$case_uuid = $_SESSION['bsm']['add']['case_p_uuid'];
	//print $_SESSION['bsm']['add']['case_p_uuid'];
		
    shn_form_fopen("add&entity=person",null,null);
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Complete the details and save to add a new person'));

    shn_form_text(_('Last Name'),'last_name','size="30"',array('help' => _('Enter full or part of the last name also known as Surname or Family Name.'), 'req'=>true));
    shn_form_text(_('First Name'),'first_name','size="30"',array('help' => _('Enter full or part of the first name.'), 'req'=>true));
    shn_form_text(_('Middle Name'),'mi_name','size="30"',array('help' => _('Enter full or part of the middle name or second name.'), 'req'=>false));
    shn_form_text(_('Alias'),'alias','size="30"',array('help' => _('Enter full or part of the alias name.'), 'req'=>false));

    include('person_type.inc');

    shn_form_text(_('Passport'),'passport','size="30"',array('help' => _('Enter full or part of the passport number.'), 'req'=>false));
    shn_form_text(_('National Identification'),'natl_id','size="30"',array('help' => _('Enter full or part of the national identification number.'), 'req'=>false));
    shn_form_text(_('Driver License'),'dr_lic','size="30"',array('help' => _('Enter full or part of the drivers license number.'), 'req'=>false));
    shn_form_opt_select('opt_gender', 'Gender', null, array('help' => _('Select the person sex or gender, if in doubt select unknown.'), 'req'=>false));
    shn_form_text(_('Age'),'age','size="30"',array('help' => _('Enter full or part of the drivers license number.'), 'req'=>false));
    shn_form_date(_('Date of Birth'),'dob',array( 'help'=> _('Set date of birth'), 'req'=>false));
    shn_form_opt_select('opt_age_group', 'Age Group', null, array('help' => _('Select an age group.'), 'req'=>false));
    echo $_SESSION['bsm']['add']['dep_full_name'] ?
        '<p align="center">'.'Dependent Full Name: '.$_SESSION['bsm']['add']['dep_full_name'].'<a title="'._('Edit').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&id='.
        $_SESSION['bsm']['add']['dep_prsn_uuid'].'">'." (click to change dependent)".'</a></p><br><br>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=person&seq=lookup&id='.$_SESSION['bsm']['add']['p_uuid'].'">'."Click to Add dependent".'</a></p><br><br>' ;
	shn_form_hidden(array('case_uuid'=>$_SESSION['bsm']['add']['case_p_uuid'], 'case_person'=>$_SESSION['bsm']['add']['case_person']));        
    shn_form_submit(_('Save'));
    shn_form_fsclose();
    shn_form_fclose();

//    shn_bsm_prsn_cont_vw();
//    shn_bsm_prsn_addr_vw();


 }
/*
function shn_bsm_prsn_cont_vw(){
    global $global;
    global $conf;

    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
    $sql = "SELECT con.cont_uuid AS contact_uuid, con.cont_mode c_mode, con.cont_val c_value FROM bsm_contact con ";
    $sql .= "INNER JOIN bsm_prsn_cont pcon ON pcon.cont_uuid = con.cont_uuid INNER JOIN bsm_person p ON p.p_uuid = pcon.p_uuid ";
    $sql .= "WHERE con.deactivate_dt IS NULL AND p.p_uuid = '".$_SESSION['bsm']['add']['person_uuid']."'";
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='add')
        $select = true;
    shn_form_fsopen(_('Person Contact Details (to edit clink on the specific UUID)'));
    ?>
    <div id = "contact_table">
    <TABLE>
    <THEAD>
        <TD><?= _('UUID');?></TD>
        <TD><?= _('Contact Mode');?></TD>
        <TD><?= _('Details');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($details!=null)
    {
        foreach($details as $detail)
        {
    ?><TR>
        <TD> <?php   echo $detail['contact_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=contact&id='.$detail['contact_uuid'].'">'.
                        $detail['contact_uuid'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['c_mode'] ? $detail['c_mode'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['c_value'] ? $detail['c_value'].'<br>' : ''; ?> </TD>


    </TR><?php
        }
    }
    ?></TABLE></div><?php
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=contact&seq=lookup&id='.
        $_SESSION['bsm']['add']['p_uuid'].'">'." click to ADD a new Contact".'</a><br>';
    shn_form_fsclose();
}
function shn_bsm_prsn_addr_vw(){
    global $global;
    global $conf;

    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
    $sql = "SELECT a.addr_uuid AS address_uuid, a.addr_type AS a_type, a.addr_status AS a_status, a.line_1 AS line1, ";
    $sql .= "a.line_2 AS line2, a.cty_twn_vil AS city_town_vill, a.post_code AS post_code, a.district AS district, ";
    $sql .= "a.state_prov AS state_province, a.country AS country FROM bsm_address a ";
    $sql .= "INNER JOIN bsm_prsn_addr pa ON pa.addr_uuid = a.addr_uuid INNER JOIN bsm_person p ON p.p_uuid = pa.p_uuid ";
    $sql .= "WHERE pa.deactivate_dt IS NULL AND pa.p_uuid = '".$_SESSION['bsm']['add']['person_uuid']."'";
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='add')
        $select = true;
    shn_form_fsopen(_('Person Address Information (to edit clink on the specific UUID)'));
    ?>
    <div id="address_table">
    <TABLE>
    <THEAD>
        <TD><?= _('UUID');?></TD>
        <TD><?= _('Type, Status');?></TD>
        <TD><?= _('Address line');?></TD>
        <TD><?= _('City/Town/Village');?></TD>
        <TD><?= _('District, State/Province');?></TD>
        <TD><?= _('Country, Postal Code');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($details!=null)
    {
        foreach($details as $detail)
        {
    ?><TR>
        <TD> <?php   echo $detail['address_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=contact&id='.$detail['address_uuid'].'">'.
                        $detail['address_uuid'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['a_type'] || $detail['a_status'] ? $detail['a_type'].', '.$detail['a_status'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['line1'] || $detail['line2'] ? $detail['line1'].', '.$detail['line2'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['city_town_vill'] ? $detail['city_town_vill'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['district'] || $detail['state_province'] ? $detail['district'].', '.$detail['state_province'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['country'] || $detail['post_code'] ? $detail['country'].', '.$detail['post_code'].'<br>' : ''; ?> </TD>



    </TR><?php
        }
    }
    ?></TABLE></div><?php
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=address&seq=lookup&id='.
        $_SESSION['bsm']['add']['p_uuid'].'">'." click to ADD a new Address".'</a><br>';
    shn_form_fsclose();
}
 *
 */
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

	$local_post['person_uuid'] = $_SESSION['bsm']['add']['person_uuid'];
	//clean
	$_SESSION['bsm']['add']=null;
	$_SESSION['bsm']['add']=$local_post;

	if(!isset($local_post['last_name'])){
		add_error(_("Please enter the last name; null values not allowed"));
		$error_flag=true;
	}
	/*if(!isset($local_post['role'])){
		add_error(_("Please select a person role; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['type'])){
		add_error(_("Please select a person type; null values not allowed"));
		$error_flag=true;
	}*/
        //$_SESSION['bsm']['edit']['person_uuid'] = $local_post['person_uuid'];
	if($error_flag)
	return false;
	else{return true;}
}

function shn_bsm_add_confirm(){

    global $global;
    global $conf;

    $_SESSION['bsm']['add']['last_name'] = isset($_POST['last_name']) ? trim($_POST['last_name']) : null;
    $_SESSION['bsm']['add']['first_name'] = isset($_POST['first_name']) ? trim($_POST['first_name']) : null;
    $_SESSION['bsm']['add']['mi_name'] = isset($_POST['mi_name']) ? trim($_POST['mi_name']) : null;
    $_SESSION['bsm']['add']['alias'] = isset($_POST['alias']) ? trim($_POST['alias']) : null;
    $_SESSION['bsm']['add']['prsn_role'] = isset($_POST['prsn_role']) ? trim($_POST['prsn_role']) : null;
    $_SESSION['bsm']['add']['prsn_type'] = isset($_POST['prsn_type']) ? trim($_POST['prsn_type']) : null;
    $_SESSION['bsm']['add']['prsn_state'] = isset($_POST['prsn_state']) ? trim($_POST['prsn_state']) : null;
    $_SESSION['bsm']['add']['passport'] = isset($_POST['passport']) ? trim($_POST['passport']) : null;
    $_SESSION['bsm']['add']['natl_id'] = isset($_POST['natl_id']) ? trim($_POST['natl_id']) : null;
    $_SESSION['bsm']['add']['dr_lic'] = isset($_POST['dr_lic']) ? trim($_POST['dr_lic']) : null;
    $_SESSION['bsm']['add']['gender'] = isset($_POST['gender']) ? trim($_POST['gender']) : null;
    $_SESSION['bsm']['add']['dob'] = isset($_POST['dob']) ? trim($_POST['dob']) : null;
    $_SESSION['bsm']['add']['age'] = isset($_POST['age']) ? trim($_POST['age']) : null;
    $_SESSION['bsm']['add']['age_grp'] = isset($_POST['age_grp']) ? trim($_POST['age_grp']) : null;
    $_SESSION['bsm']['add']['create_datetime'] = getdate();
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
    include_once $global['approot'].'/inc/lib_uuid.inc';
    //print 'hello';
    $case_uuid =  $_POST['case_uuid'];
    $case_person = $_POST['case_person'];
	//$case_uuid = $_SESSION['bsm']['add']['case_p_uuid'];
	//print $case_uuid;
    $insert_array = array();
    $insert_array = null;
    $p_uuid = shn_create_uuid('per');
//print $p_uuid;
    $insert_array['p_uuid'] = $p_uuid;

    if(isset($_SESSION['bsm']['add']['last_name']) && $_SESSION['bsm']['add']['last_name']!=null)
        {$insert_array['last_name'] = $_SESSION['bsm']['add']['last_name'];}
    if(isset($_SESSION['bsm']['add']['first_name']) && $_SESSION['bsm']['add']['first_name']!=null)
        {$insert_array['first_name'] = $_SESSION['bsm']['add']['first_name'];}
    if(isset($_SESSION['bsm']['add']['mi_name']) && $_SESSION['bsm']['add']['mi_name']!=null)
        {$insert_array['mi_name'] = $_SESSION['bsm']['add']['mi_name'];}
    if(isset($_SESSION['bsm']['add']['alias']) && $_SESSION['bsm']['add']['alias']!=null)
        {$insert_array['alias'] = $_SESSION['bsm']['add']['alias'];}
      if(isset($_SESSION['bsm']['add']['prsn_role'])){$insert_array['prsn_role'] = $_SESSION['bsm']['add']['prsn_role'];}
	if(isset($_SESSION['bsm']['add']['prsn_type'])){$insert_array['prsn_type'] = $_SESSION['bsm']['add']['prsn_type'];}
	if(isset($_SESSION['bsm']['add']['prsn_state'])){$insert_array['prsn_state'] = $_SESSION['bsm']['add']['prsn_state'];}
    if(isset($_SESSION['bsm']['add']['passport']) && $_SESSION['bsm']['add']['passport']!=null)
        {$insert_array['passport'] = $_SESSION['bsm']['add']['passport'];}
    if(isset($_SESSION['bsm']['add']['natl_id']) && $_SESSION['bsm']['add']['natl_id']!=null)
        {$insert_array['natl_id'] = $_SESSION['bsm']['add']['natl_id'];}
    if(isset($_SESSION['bsm']['add']['dr_lic']) && $_SESSION['bsm']['add']['dr_lic']!=null)
        {$insert_array['dr_lic'] = $_SESSION['bsm']['add']['dr_lic'];}
    if(isset($_SESSION['bsm']['add']['gender']) && $_SESSION['bsm']['add']['gender']!=null)
        {$insert_array['gender'] = $_SESSION['bsm']['add']['gender'];}
    if(isset($_SESSION['bsm']['add']['age']) && $_SESSION['bsm']['add']['age']!=null)
        {$insert_array['age'] = $_SESSION['bsm']['add']['age'];}
    if(isset($_SESSION['bsm']['add']['dob']) && $_SESSION['bsm']['add']['dob']!=null)
        {$insert_array['dob'] = $_SESSION['bsm']['add']['dob'];}
    if(isset($_SESSION['bsm']['add']['age_grp']) && $_SESSION['bsm']['add']['age_grp']!=null)
        {$insert_array['age_grp'] = $_SESSION['bsm']['add']['age_grp'];}
    if(isset($_SESSION['bsm']['add']['create_datetime']) && $_SESSION['bsm']['add']['create_datetime']!=null){$insert_array['create_dt'] = $_SESSION['bsm']['add']['create_datetime'];}
    if(isset($_SESSION['bsm']['add']['create_user']) && $_SESSION['bsm']['add']['create_user']!=null){$insert_array['create_by'] = $_SESSION['bsm']['add']['create_user'];}
    if(isset($_SESSION['bsm']['add']['create_process']) && $_SESSION['bsm']['add']['create_process']!=null){$insert_array['create_proc'] = $_SESSION['bsm']['add']['create_process'];}

    //shn_db_insert($insert_array,'bsm_person',true, null);
    //var_dump($insert_array);

    global $global;
    $db = $global['db'];
//    $sql = "INSERT INTO bsm_person (p_uuid, passport, natl_id, dr_lic, last_name, first_name, mi_name, alias, gender, age, age_grp) VALUES ('{$p_uuid}', '{$_SESSION['bsm']['add']['passport']}', '{$_SESSION['bsm']['add']['national_id']}', '{$_SESSION['bsm']['add']['driver_license']}', '{$_SESSION['bsm']['add']['last_name']}', '{$_SESSION['bsm']['add']['first_name']}', '{$_SESSION['bsm']['add']['middle_name']}', '{$_SESSION['bsm']['add']['alias']}', '{$_SESSION['bsm']['add']['gender']}', '{$_SESSION['bsm']['add']['age']}', '{$_SESSION['bsm']['add']['age_group']}');";
  //  $db->Execute($sql);
    $res = $db->AutoExecute('bsm_person', $insert_array, 'INSERT');
    $res = $db->AutoExecute('bsm_prsn_link_type', $insert_array, 'INSERT');
		//$res = $db->AutoExecute('bsm_prsn_type', $insert_array, 'INSERT');
		$cases_array = array();
		$cases_array['pat_p_uuid'] = $p_uuid;
		$cases_array['pat_full_name'] = $insert_array['first_name'].' '.$insert_array['mi_name'].' '.$insert_array['last_name'];
		$pat_full_name = $insert_array['first_name'].' '.$insert_array['mi_name'].' '.$insert_array['last_name'];
		//$res1 = $db->AutoExecute('bsm_cases', $cases_array, 'UPDATE', "case_uuid=$case_uuid");
		// print $res1;
		 //print 'test';
		// var_dump($cases_array);
		if($case_uuid!=NULL || $case_uuid!='')
		{
		if($case_person=='patient') 
		{
			//print $case_person;
			$sql = "UPDATE bsm_cases SET pat_p_uuid = '{$p_uuid}', pat_full_name = '{$pat_full_name}' WHERE case_uuid = '$case_uuid'";
			$res1 = $db->Execute($sql);
		}
		if($case_person=='healthworker')
		{
			//print $case_person;
			$sql = "UPDATE bsm_cases SET hwork_p_uuid = '{$p_uuid}', hwork_full_name = '{$pat_full_name}' WHERE case_uuid = '$case_uuid'";
			$res1 = $db->Execute($sql);
			//print $sql;
		}
		}
		
		//print $sql;
    
    if($res)
        add_confirmation($_SESSION['bsm']['add']['first_name'].' '.$_SESSION['bsm']['add']['last_name']._t(" added successfully"));
    else{
        add_error(_('Error while saving person.'));
    }

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
