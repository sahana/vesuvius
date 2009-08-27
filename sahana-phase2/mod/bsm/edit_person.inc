<?php
/* $Id: edit_person.inc,v 1.1 2009-08-27 22:26:48 pradeeper Exp $ */

/**
 * Edit the location
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      Nuwan Waidyanatha <waidyanatha@lirne.net>
 * @copyright   Lanka Software Foundation - http://www.opensource.lk
 * @package     mod
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
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
* @name Load Informations on given person_uuid i.e. p_uuid
* @param mixed $p_uuid
* @access public
* @return void
*/
function shn_bsm_edit_load($p_uuid){

	global $global;
        global $conf;

        //step 1: load details from bsm_person
/*    $sql = "SELECT p.p_uuid AS person_uuid, p.prsn_role AS p_role, p.prsn_type AS p_type, p.prsn_state AS p_state, ";
    $sql .= "p.passport AS passport, p.natl_id AS national_id, p.dr_lic AS driver_license, p.last_name AS last_name, ";
    $sql .= "p.first_name AS first_name, p.mi_name AS middle_name, p.alias AS p_alias, p.gender AS gender, ";
    $sql .= "p.desig AS designation, p.dep_p_uuid AS dependent_p_uuid, ";
    $sql .= "(SELECT px.last_name FROM bsm_person px WHERE px.deactivate_dt IS NULL ";
    $sql .= "AND px.p_uuid = p.dep_p_uuid) AS dep_full_name, ";
    $sql .= "p.age AS age, p.age_grp AS age_group, p.dob AS dob ";
    $sql .= "FROM bsm_person p INNER JOIN bsm_prsn_type pt ON pt.prsn_type = p.prsn_type ";
    $sql .= "INNER JOIN bsm_prsn_role pr ON pr.prsn_role = pt.prsn_role ";
    $sql .= "INNER JOIN bsm_prsn_state ps ON ps.prsn_state = p.prsn_state ";
    $sql .= "WHERE p.deactivate_dt IS NULL AND p.p_uuid = '$p_uuid' ";*/

    $sql = "SELECT p.* ,l.prsn_state,l.prsn_type,pt.prsn_role FROM bsm_person AS p INNER JOIN bsm_prsn_link_type AS l ON l.p_uuid = p.p_uuid INNER JOIN bsm_prsn_type AS pt ON l.prsn_type = pt.prsn_type WHERE p.p_uuid='$p_uuid'";
    
    $rs = $global['db']->GetRow($sql);
/*
    $_SESSION['bsm']['edit']['person_uuid'] = $rs->fields['person_uuid'];
    $_SESSION['bsm']['edit']['role'] = $rs->fields['p_role'];
    $_SESSION['bsm']['edit']['type'] = $rs->fields['p_type'];
    $_SESSION['bsm']['edit']['state'] = $rs->fields['p_state'];
    $_SESSION['bsm']['edit']['passport'] = $rs->fields['passport'];
    $_SESSION['bsm']['edit']['national_id'] = $rs->fields['national_id'];
    $_SESSION['bsm']['edit']['driver_license'] = $rs->fields['driver_license'];
    $_SESSION['bsm']['edit']['last_name'] = $rs->fields['last_name'];
    $_SESSION['bsm']['edit']['first_name'] = $rs->fields['first_name'];
    $_SESSION['bsm']['edit']['middle_name'] = $rs->fields['middle_name'];
    $_SESSION['bsm']['edit']['p_alias'] = $rs->fields['p_alias'];
    $_SESSION['bsm']['edit']['gender'] = $rs->fields['gender'];
    $_SESSION['bsm']['edit']['designation'] = $rs->fields['designation'];
    $_SESSION['bsm']['edit']['dep_prsn_uuid'] = $rs->fields['dep_prsn_uuid'];
    $_SESSION['bsm']['edit']['dep_full_name'] = $rs->fields['dep_full_name'];
    $_SESSION['bsm']['edit']['dob'] = $rs->fields['dob'];
    $_SESSION['bsm']['edit']['age'] = $rs->fields['age'];
    $_SESSION['bsm']['edit']['age_group'] = $rs->fields['age_group'];
    $_SESSION['bsm']['edit']['dob'] = $rs->fields['dob'];*/
    $_SESSION['bsm']['edit'] = $rs;
}
/**
 * @name    Edit Form
 *
 * @param   bool $errors
 * @access  public
 * @return  void
 * @TODO    display type and state relative to selected category "onchange"
 * @TODO    if date of birth given then autocalculate the age
 */
function shn_bsm_edit_entry($errors=false){

    global $global;
    global $conf;
    shn_form_fopen("edit&entity=person",null,null);
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Details for Person UUID: '.$_SESSION['bsm']['edit']['p_uuid']));
    shn_form_fsopen(_('Names :'));
    shn_form_text(_('Last Name'),'last_name','size="30"',array('value'=>$_SESSION['bsm']['edit']['last_name'] ,'help' => _('Enter full or part of the last name also known as Surname or Family Name.'), 'req'=>true));
    shn_form_text(_('First Name'),'first_name','size="30"',array('value'=>$_SESSION['bsm']['edit']['first_name'] ,'help' => _('Enter full or part of the first name.'), 'req'=>true));
    shn_form_text(_('Middle Name'),'mi_name','size="30"',array('value'=>$_SESSION['bsm']['edit']['mi_name'] ,'help' => _('Enter full or part of the middle name or second name.'), 'req'=>false));
    shn_form_text(_('Alias'),'alias','size="30"',array('value'=>$_SESSION['bsm']['edit']['alias'] ,'help' => _('Enter full or part of the alias name.'), 'req'=>false));
    shn_form_fsclose();
    shn_form_fsopen(_('Characteristics :'));

    $prsn_type = $_SESSION['bsm']['edit']['prsn_type'];
    $prsn_state = $_SESSION['bsm']['edit']['prsn_state'];
    include('person_type.inc');

    shn_form_fsclose();
    shn_form_fsopen(_('Indentifications :'));
    shn_form_text(_('Passport'),'passport','size="30"',array('value'=>$_SESSION['bsm']['edit']['passport'] ,'help' => _('Enter full or part of the passport number.'), 'req'=>false));
    shn_form_text(_('National Identification'),'natl_id','size="30"',array('value'=>$_SESSION['bsm']['edit']['natl_id'] ,'help' => _('Enter full or part of the national identification number.'), 'req'=>false));
    shn_form_text(_('Driver License'),'dr_lic','size="30"',array('value'=>$_SESSION['bsm']['edit']['dr_lic'] ,'help' => _('Enter full or part of the drivers license number.'), 'req'=>false));

    shn_form_opt_select('opt_gender', 'Gender', null, array('help' => _('Select the person sex or gender, if in doubt select unknown.'), 'req'=>false));
    shn_form_date(_('Date of Birth'),'dob',array('value'=>$_SESSION['bsm']['edit']['dob'], 'help'=> _('Set date of birth'), 'req'=>false));
    shn_form_text(_('Age'),'age','size="30"',array('value'=>$_SESSION['bsm']['edit']['age'] ,'help' => _('Enter full or part of the drivers license number.'), 'req'=>false));
    shn_form_opt_select('opt_age_group', 'Age Group', null, array('value'=>$_SESSION['bsm']['edit']['age_grp'] ,'help' => _('Select an age group.'), 'req'=>false));
    shn_form_fsclose();
    echo $_SESSION['bsm']['edit']['dep_full_name'] ?
        '<p align="center">'.'Dependent Full Name: '.$_SESSION['bsm']['edit']['dep_full_name'].'<a title="'._('Edit').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['p_uuid'].'">'." (click to change dependent)".'</a></p>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lookup&rtnid='.$_SESSION['bsm']['edit']['p_uuid'].'">'."Click to Add dependent".'</a></p>' ;

    shn_form_submit(_('Save'));
    shn_form_fsclose();

    shn_bsm_prsn_cont_vw();
    shn_bsm_prsn_addr_vw();
}

function shn_bsm_prsn_cont_vw(){
/*
    global $global;
    global $conf;
    
    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
    $sql = "SELECT con.cont_uuid AS contact_uuid, con.cont_mode c_mode, con.cont_val c_value FROM bsm_contact con ";
    $sql .= "INNER JOIN bsm_prsn_cont pcon ON pcon.cont_uuid = con.cont_uuid INNER JOIN bsm_person p ON p.p_uuid = pcon.p_uuid ";
    $sql .= "WHERE con.deactivate_dt IS NULL AND p.p_uuid = '".$_SESSION['bsm']['edit']['person_uuid']."'";
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='edit')
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
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=contact&seq=lookup&rtnid='.
        $_SESSION['bsm']['edit']['p_uuid'].'">'." click to ADD a new Contact".'</a><br>';
    shn_form_fsclose();
*/
}
function shn_bsm_prsn_addr_vw(){

    global $global;
    global $conf;

    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
    $sql = "SELECT a.addr_uuid AS address_uuid, a.addr_type AS a_type, a.addr_status AS a_status, a.line_1 AS line1, ";
    $sql .= "a.line_2 AS line2, a.cty_twn_vil AS city_town_vill, a.post_code AS post_code, a.district AS district, ";
    $sql .= "a.state_prov AS state_province, a.country AS country FROM bsm_address a ";
    $sql .= "INNER JOIN bsm_prsn_addr pa ON pa.addr_uuid = a.addr_uuid INNER JOIN bsm_person p ON p.p_uuid = pa.p_uuid ";
    $sql .= "WHERE pa.deactivate_dt IS NULL AND pa.p_uuid = '".$_SESSION['bsm']['edit']['p_uuid']."'";
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='edit')
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
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=address&seq=lookup&rtnid='.
        $_SESSION['bsm']['edit']['p_uuid'].'">'." click to ADD a new Address".'</a><br>';
    shn_form_fsclose();
}
/**
 * @name    Validate changed values in Edit Form
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

	$local_post['p_uuid'] = $_SESSION['bsm']['edit']['p_uuid'];
	//clean
	$_SESSION['bsm']['edit']=null;
	$_SESSION['bsm']['edit']=$local_post;

	if(!isset($local_post['last_name'])){
		add_error(_("Please enter the last name; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['prsn_role'])){
		add_error(_("Please select a person role; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['prsn_type'])){
		add_error(_("Please select a person type; null values not allowed"));
		$error_flag=true;
	}
    $_SESSION['bsm']['edit']['p_uuid'] = $local_post['p_uuid'];
	if($error_flag)
	return false;
	else{return true;}
}
/**
 * @name    Confirmation page
 * @access  public
 * @return  void
 */
function shn_bsm_edit_confirm(){
    global $global;
    global $conf;

    $_SESSION['bsm']['edit']['last_name'] = isset($_POST['last_name']) ? trim($_POST['last_name']) : null;
    $_SESSION['bsm']['edit']['first_name'] = isset($_POST['first_name']) ? trim($_POST['first_name']) : null;
    $_SESSION['bsm']['edit']['mi_name'] = isset($_POST['mi_name']) ? trim($_POST['mi_name']) : null;
    $_SESSION['bsm']['edit']['alias'] = isset($_POST['alias']) ? trim($_POST['alias']) : null;
    $_SESSION['bsm']['edit']['prsn_role'] = isset($_POST['prsn_role']) ? trim($_POST['prsn_role']) : null;
    $_SESSION['bsm']['edit']['prsn_type'] = isset($_POST['prsn_type']) ? trim($_POST['prsn_type']) : null;
    $_SESSION['bsm']['edit']['prsn_state'] = isset($_POST['prsn_state']) ? trim($_POST['prsn_state']) : null;
    $_SESSION['bsm']['edit']['passport'] = isset($_POST['passport']) ? trim($_POST['passport']) : null;
    $_SESSION['bsm']['edit']['natl_id'] = isset($_POST['natl_id']) ? trim($_POST['natl_id']) : null;
    $_SESSION['bsm']['edit']['dr_lic'] = isset($_POST['drr_lic']) ? trim($_POST['dr_lic']) : null;
    $_SESSION['bsm']['edit']['gender'] = isset($_POST['gender']) ? trim($_POST['gender']) : null;    
    $_SESSION['bsm']['edit']['dob'] = isset($_POST['dob']) ? trim($_POST['dob']) : null;
    $_SESSION['bsm']['edit']['age'] = isset($_POST['age']) ? trim($_POST['age']) : null;
    $_SESSION['bsm']['edit']['age_grp'] = isset($_POST['age_grp']) ? trim($_POST['age_grp']) : null;
    $_SESSION['bsm']['edit']['modify_datetime'] = getdate();
    $_SESSION['bsm']['edit']['modify_user'] = "user";
    $_SESSION['bsm']['edit']['modify_process'] = $conf['host'];

    shn_form_hidden(array('seq'=>'commit'));
}
/**
 * @name    Commits changes to the database
 * @access public
 * @return void
 */
function shn_bsm_edit_commit(){
	
	global $global;
	global $conf;

	//$update_array['loc_id'] = $_SESSION['bsm']['edit']['location_uuid'];
        //if ($conf['debug']){print ('loc id = '.$_SESSION['bsm']['edit']['location_uuid'].'<hr><br>');}
/*
	if(isset($_SESSION['bsm']['edit']['last_name']) && $_SESSION['bsm']['edit']['last_name']!=null)
            {$update_array['last_name'] = $_SESSION['bsm']['edit']['last_name'];}
	if(isset($_SESSION['bsm']['edit']['first_name']) && $_SESSION['bsm']['edit']['first_name']!=null)
            {$update_array['first_name'] = $_SESSION['bsm']['edit']['first_name'];}
	if(isset($_SESSION['bsm']['edit']['middle_name']) && $_SESSION['bsm']['edit']['middle_name']!=null)
            {$update_array['mi_name'] = $_SESSION['bsm']['edit']['mi_name'];}
	if(isset($_SESSION['bsm']['edit']['alias']) && $_SESSION['bsm']['edit']['alias']!=null)
            {$update_array['alias'] = $_SESSION['bsm']['edit']['alias'];}
        if(isset($_SESSION['bsm']['edit']['role'])){$update_array['prsn_role'] = $_SESSION['bsm']['edit']['prsn_role'];}
	if(isset($_SESSION['bsm']['edit']['type'])){$update_array['prsn_type'] = $_SESSION['bsm']['edit']['type'];}
	if(isset($_SESSION['bsm']['edit']['state'])){$update_array['prsn_state'] = $_SESSION['bsm']['edit']['state'];}
	if(isset($_SESSION['bsm']['edit']['passport']) && $_SESSION['bsm']['edit']['passport']!=null)
            {$update_array['passport'] = $_SESSION['bsm']['edit']['passport'];}
	if(isset($_SESSION['bsm']['edit']['national_id']) && $_SESSION['bsm']['edit']['national_id']!=null)
            {$update_array['natl_id'] = $_SESSION['bsm']['edit']['national_id'];}
	if(isset($_SESSION['bsm']['edit']['driver_license']) && $_SESSION['bsm']['edit']['driver_license']!=null)
            {$update_array['dr_lic'] = $_SESSION['bsm']['edit']['driver_license'];}
	if(isset($_SESSION['bsm']['edit']['gender']))
            {$update_array['gender'] = $_SESSION['bsm']['edit']['gender'];}
	if(isset($_SESSION['bsm']['edit']['dob'])){$update_array['dob'] = $_SESSION['bsm']['edit']['dob'];}
	if(isset($_SESSION['bsm']['edit']['age']) && $_SESSION['bsm']['edit']['age']!=null)
            {$update_array['age'] = $_SESSION['bsm']['edit']['age'];}
	if(isset($_SESSION['bsm']['edit']['age_group']) && $_SESSION['bsm']['edit']['age_group']!=null)
            {$update_array['dr_lic'] = $_SESSION['bsm']['edit']['age_group'];}*/
    $update_array = $_SESSION['bsm']['edit'];
	if(isset($_SESSION['bsm']['edit']['modify_datetime']) && $_SESSION['bsm']['edit']['modify_datetime']!=null){$update_array['modify_dt'] = $_SESSION['bsm']['edit']['modify_datetime'];}
	if(isset($_SESSION['bsm']['edit']['modify_user']) && $_SESSION['bsm']['edit']['modify_user']!=null){$update_array['modify_by'] = $_SESSION['bsm']['edit']['modify_user'];}
	if(isset($_SESSION['bsm']['edit']['modify_process']) && $_SESSION['bsm']['edit']['modify_process']!=null){$update_array['modify_proc'] = $_SESSION['bsm']['edit']['modify_process'];}

    $res = $global['db']->AutoExecute('bsm_person', $update_array, 'UPDATE',"p_uuid = '{$_SESSION['bsm']['edit']['p_uuid']}'");
    $res = $global['db']->AutoExecute('bsm_prsn_link_type', $update_array, 'UPDATE',"p_uuid = '{$_SESSION['bsm']['edit']['p_uuid']}'");
    if(!$res)
        add_error('Person update failed');
    else
        add_confirmation('Person updated');
}

?>
