<?php
/* $Id: edit_facility.inc,v 1.3 2009-08-27 22:26:48 pradeeper Exp $ */

/**
 * Edit the facility
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


/**
 * Generate Tabbs
 *
 * @param string $selected
 * @access public
 * @return void
 * @todo code this
 */
function shn_generate_tabs($selected='')
{
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

/* {{{ Load Informations

/**
* Load Informations on given person_uuid i.e. p_uuid
*
* @param mixed $p_uuid
* @access public
* @return void
*/
function shn_bsm_edit_load($facility_uuid)
{
	global $global;
        global $conf;

        //step 1: load details from bsm_person
    $sql =  "SELECT f.fclty_uuid AS facility_uuid, f.fclty_cate AS category, f.fclty_type AS type, f.fclty_status AS status, ";
    $sql .= "f.loc_uuid AS location_uuid, (SELECT loc_desc FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = f.loc_uuid) ";
    $sql .= "AS location_name, f.fclty_desc AS name FROM bsm_facility f INNER JOIN bsm_fclty_type ft ON ft.fclty_type = f.fclty_type ";
    $sql .= "INNER JOIN bsm_fclty_cate fc ON fc.fclty_cate = ft.fclty_cate WHERE f.deactivate_dt IS NULL AND f.fclty_uuid = '$facility_uuid'";
    
    $rs = $global['db']->Execute($sql);

    $_SESSION['bsm']['edit']['facility_uuid'] = $rs->fields['facility_uuid'];
    $_SESSION['bsm']['edit']['category'] = $rs->fields['category'];
    $_SESSION['bsm']['edit']['type'] = $rs->fields['type'];
    $_SESSION['bsm']['edit']['status'] = $rs->fields['status'];
    $_SESSION['bsm']['edit']['location_uuid'] = $rs->fields['location_uuid'];
    $_SESSION['bsm']['edit']['location_name'] = $rs->fields['location_name'];
    $_SESSION['bsm']['edit']['name'] = $rs->fields['name'];

}
/**
 * Edit Form
 *
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_bsm_edit_entry($errors=false)
{
    global $global;
    global $conf;
    
    shn_form_fopen("edit&entity=facility",null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Details for Facility UUID: '.$_SESSION['bsm']['edit']['facility_uuid']));

    shn_form_text(_('Name'),'name','size="30"',array('value'=>$_SESSION['bsm']['edit']['name'] ,'help' => _('Enter full or part of the last name also known as Surname or Family Name.'), 'req'=>true));
    
    $sql = "SELECT DISTINCT fclty_cate AS category FROM bsm_fclty_cate WHERE deactivate_dt IS NULL";
    $rsql = $global['db']->Execute($sql);
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        //$option .= " ".$rv[0];
        array_push($arropt,$rv[0]);
    }
    //$option = substr($option, 0, -1);
    //$arropt = explode(' ',$option);
    shn_form_select($arropt,_('Category'), 'category',null,array('value'=>$_SESSION['bsm']['edit']['category'] ,'help' => _('Select a person role.'), 'req'=>true));

    $sql = "SELECT DISTINCT fclty_type AS type FROM bsm_fclty_type WHERE deactivate_dt IS NULL ";
    $rsql = $global['db']->Execute($sql);
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    shn_form_select($arropt,_('Type'), 'type',null,array('value'=>$_SESSION['bsm']['edit']['type'] ,'help' => _('Select a person type.'), 'req'=>true));
    shn_form_opt_select('opt_fac_status',_('Status'), null,array('value'=>$_SESSION['bsm']['edit']['type'] ,'help' => _('Select a person type.'), 'req'=>true));
    echo $_SESSION['bsm']['edit']['location_name'] ?
        '<p align="center">'.'Location Name: '.$_SESSION['bsm']['edit']['location_name'].'<a title="'._('Edit').'" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lookup&id='.$_SESSION['bsm']['edit']['facility_uuid'].'">'." (click to change the location)".'</a></p>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lookup&id='.$_SESSION['bsm']['edit']['facility_uuid'].'">'."Click to Add a location".'</a></p>' ;

    shn_form_submit(_('Save'));
    shn_form_fsclose();

    shn_bsm_fclty_cont_vw();
    shn_bsm_fclty_addr_vw();
    shn_bsm_fclty_serv_vw();

}
function shn_bsm_fclty_cont_vw(){
    global $global;
    global $conf;
    $_SESSION['bsm']['edit']['facility_uuid'] = $_REQUEST['lukupid'];
    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
   /* $sql = "SELECT con.cont_uuid AS contact_uuid, con.cont_mode c_mode, con.cont_val c_value FROM bsm_contact con ";
    $sql .= "INNER JOIN bsm_fclty_cont fcon ON fcon.cont_uuid = con.cont_uuid INNER JOIN bsm_facility f ON f.fclty_uuid = fcon.fclty_uuid ";
    $sql .= "WHERE con.deactivate_dt IS NULL AND f.fclty_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";*/
		$sql = "SELECT con.*, pcon.* FROM bsm_contact con INNER JOIN bsm_prsn_cont pcon ON con.cont_uuid = pcon.cont_uuid WHERE con.deactivate_dt IS NULL AND pcon.p_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";
//print $sql;
//print($_REQUEST['lukupid']);
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Facility Contact Details (to edit or for further details clik on the record UUID)'));
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
        <TD> <?php   echo $detail['cont_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=contact&id='.$detail['cont_uuid'].'">'.
                        $detail['cont_uuid'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['cont_mode'] ? $detail['cont_mode'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['cont_val'] ? $detail['cont_val'].'<br>' : ''; ?> </TD>


    </TR><?php 
        }
    }
    ?></TABLE></div><?php
		$_SESSION['bsm']['edit']['p_uuid'] = $_REQUEST['lukupid'];
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=contact&seq=&id='.
        $_SESSION['bsm']['edit']['p_uuid'].'">'." click to ADD a new Contact".'</a><br>';
    shn_form_fsclose();
}
function shn_bsm_fclty_addr_vw(){
    global $global;
    global $conf;

    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
    $sql = "SELECT a.addr_uuid AS address_uuid, a.addr_type AS a_type, a.addr_status AS a_status, a.line_1 AS line1, ";
    $sql .= "a.line_2 AS line2, a.cty_twn_vil AS city_town_vill, a.post_code AS post_code, a.district AS district, ";
    $sql .= "a.state_prov AS state_province, a.country AS country FROM bsm_address a ";
    $sql .= "INNER JOIN bsm_fclty_addr fa ON fa.addr_uuid = a.addr_uuid INNER JOIN bsm_facility f ON f.fclty_uuid = fa.fclty_uuid ";
    $sql .= "WHERE fa.deactivate_dt IS NULL AND fa.fclty_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Facility Address Information (to edit or for further details clik on the record UUID)'));
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
                        $global['module'].'&act=edit&entity=address&id='.$detail['address_uuid'].'">'.
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
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=address&seq=&id='.
        $_SESSION['bsm']['edit']['p_uuid'].'">'." click to ADD a new Address".'</a><br>';
    shn_form_fsclose();
}
function shn_bsm_fclty_serv_vw(){
    global $global;
    global $conf;

    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
    /*$sql =  "SELECT s.serv_uuid AS service_uuid, s.serv_cate AS category, s.serv_type AS type, s.serv_status AS status, ";
    $sql .= "s.serv_status_dt AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, ";
    //$sql .= "s.serv_prov_prsn_id AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, ";
    $sql .= "s.serv_notes AS notes FROM bsm_service s INNER JOIN bsm_fclty_serv sf ON sf.serv_uuid = s.serv_uuid ";
    $sql .= "INNER JOIN bsm_facility f ON f.fclty_uuid = sf.fclty_uuid WHERE sf.deactivate_dt IS NULL ";
    $sql .= "AND sf.fclty_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";*/


	//	$sql = "SELECT s.serv_uuid AS service_uuid, s.serv_type AS type, s.serv_state AS status, s.serv_state_dt AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, s.serv_notes AS notes, fs.* FROM bsm_service s INNER JOIN bsm_fclty_serv fs ON  s.serv_uuid = fs.serv_uuid INNER JOIN bsm_facility f ON f.fclty_uuid = fs.fclty_uuid WHERE fs.deactivate_dt IS NULL AND fs.fclty_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";

	
		$sql = "SELECT cat.serv_cate as category, s.recp_p_uuid AS recepient, s.serv_uuid AS service_uuid, s.serv_type AS type, s.serv_state AS status, s.serv_state_dt AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, s.serv_notes AS notes, fs.* FROM bsm_serv_cate cat INNER JOIN bsm_serv_type AS type ON cat.serv_cate = type.serv_cate INNER JOIN bsm_service s ON type.serv_type = s.serv_type INNER JOIN bsm_fclty_serv fs ON  s.serv_uuid = fs.serv_uuid INNER JOIN bsm_facility f ON f.fclty_uuid = fs.fclty_uuid WHERE fs.deactivate_dt IS NULL AND fs.fclty_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";
//print $sql;

		//$sql1="SELECT cat.serv_cate as category FROM bsm_serv_cate cat INNER JOIN bsm_serv_type type ON cat.serv_cate = type.serv_cate INNER JOIN bsm_service s ON type.serv_type = s.serv_type WHERE s.deactivate"
    $details = $global['db']->Execute($sql);

		$recepient = $details->fields['recepient'];
		$sql = "SELECT last_name, first_name, mi_name FROM bsm_person WHERE p_uuid = '$recepient'";

		$res = $global['db']->Execute($sql);

    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Facility Service Information (to edit or for further details clik on the record UUID)'));
    ?>
    <div id="service_table">
    <TABLE>
    <THEAD>
        <TD><?= _('UUID');?></TD>
        <TD><?= _('Category, Type');?></TD>
        <TD><?= _('Status, date');?></TD>
        <TD><?= _('notes');?></TD>
        <TD><?= _('Recipient');?></TD>
        <TD><?= _('start date');?></TD>
        <TD><?= _('end date');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
		$_SESSION['bsm']['edit']['fclty_uuid'] = $_REQUEST['lukupid'];
    if($details!=null)
    {
        foreach($details as $detail)
        {
    ?><TR>
        <TD> <?php   echo $detail['service_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=service&id='.$detail['service_uuid'].'">'.
                        $detail['service_uuid'].'</a><br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['cateogry'] || $detail['type'] ? $detail['category'].', '.$detail['type'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['status'] || $detail['status_datetime'] ? $detail['status'].', '.$detail['status_datetime'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['notes'] ? $detail['notes'].'<br>' : ''; ?> </TD>
				<TD><?php echo($res->fields['first_name'].' '.$res->fields['mi_name'].' '.$res->fields['last_name'])?></TD>
        <TD> <?php   echo $detail['start_datetime'] ? $detail['start_datetime'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['end_datetime'] ? $detail['end_datetime'].'<br>' : ''; ?> </TD>
    </TR><?php
        }
    }
    ?></TABLE></div><?php
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=service&seq=&id='.
        $_SESSION['bsm']['edit']['fclty_uuid'].'">'." click to ADD a new Service".'</a><br>';
    shn_form_fsclose();
}
/* {{{ Edit Validation */
/**
 * Validation of the Edit Form
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_validate()
{
	global $global;
	global $conf;

	$error_flag=false;

	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

	$local_post['person_uuid'] = $_SESSION['bsm']['edit']['person_uuid'];
	//clean
	$_SESSION['bsm']['edit']=null;
	$_SESSION['bsm']['edit']=$local_post;

	if(!isset($local_post['last_name'])){
		add_error(_("Please enter the last name; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['role'])){
		add_error(_("Please select a person role; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['type'])){
		add_error(_("Please select a person type; null values not allowed"));
		$error_flag=true;
	}
        //$_SESSION['bsm']['edit']['person_uuid'] = $local_post['person_uuid'];
	if($error_flag)
	return false;
	else{return true;}
}
/* {{{ Edit Confirm */
/**
 * Confirmation page
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_confirm(){
    global $global;
    global $conf;

    $_SESSION['bsm']['edit']['last_name'] = isset($_POST['last_name']) ? trim($_POST['last_name']) : null;
    $_SESSION['bsm']['edit']['first_name'] = isset($_POST['first_name']) ? trim($_POST['first_name']) : null;
    $_SESSION['bsm']['edit']['middle_name'] = isset($_POST['middle_name']) ? trim($_POST['middle_name']) : null;
    $_SESSION['bsm']['edit']['alias'] = isset($_POST['alias']) ? trim($_POST['alias']) : null;
    $_SESSION['bsm']['edit']['role'] = isset($_POST['role']) ? trim($_POST['role']) : null;
    $_SESSION['bsm']['edit']['type'] = isset($_POST['type']) ? trim($_POST['type']) : null;
    $_SESSION['bsm']['edit']['state'] = isset($_POST['state']) ? trim($_POST['state']) : null;
    $_SESSION['bsm']['edit']['passport'] = isset($_POST['passport']) ? trim($_POST['passport']) : null;
    $_SESSION['bsm']['edit']['national_id'] = isset($_POST['national_id']) ? trim($_POST['national_id']) : null;
    $_SESSION['bsm']['edit']['driver_license'] = isset($_POST['driver_license']) ? trim($_POST['driver_license']) : null;
    $_SESSION['bsm']['edit']['gender'] = isset($_POST['gender']) ? trim($_POST['gender']) : null;    
    $_SESSION['bsm']['edit']['age'] = isset($_POST['age']) ? trim($_POST['age']) : null;
    $_SESSION['bsm']['edit']['age_group'] = isset($_POST['age_group']) ? trim($_POST['age_group']) : null;
    $_SESSION['bsm']['edit']['modify_datetime'] = getdate();
    $_SESSION['bsm']['edit']['modify_user'] = "user";
    $_SESSION['bsm']['edit']['modify_process'] = $conf['host'];

    shn_form_hidden(array('seq'=>'commit'));
}
/* {{{ Edit Commit */
/**
 * Commits the changes to the database
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_commit()
{
	// $update_array[<field_name>] = value
	global $global;
	global $conf;

	//$update_array['loc_id'] = $_SESSION['bsm']['edit']['location_uuid'];
        //if ($conf['debug']){print ('loc id = '.$_SESSION['bsm']['edit']['location_uuid'].'<hr><br>');}

	if(isset($_SESSION['bsm']['edit']['last_name']) && $_SESSION['bsm']['edit']['last_name']!=null)
            {$update_array['last_name'] = $_SESSION['bsm']['edit']['last_name'];}
	if(isset($_SESSION['bsm']['edit']['first_name']) && $_SESSION['bsm']['edit']['first_name']!=null)
            {$update_array['first_name'] = $_SESSION['bsm']['edit']['first_name'];}
	if(isset($_SESSION['bsm']['edit']['middle_name']) && $_SESSION['bsm']['edit']['middle_name']!=null)
            {$update_array['mi_name'] = $_SESSION['bsm']['edit']['middle_name'];}
	if(isset($_SESSION['bsm']['edit']['alias']) && $_SESSION['bsm']['edit']['alias']!=null)
            {$update_array['alias'] = $_SESSION['bsm']['edit']['alias'];}
//      if(isset($_SESSION['bsm']['edit']['role'])){$update_array['prsn_role'] = $_SESSION['bsm']['edit']['role'];}
//	if(isset($_SESSION['bsm']['edit']['type'])){$update_array['prsn_type'] = $_SESSION['bsm']['edit']['type'];}
//	if(isset($_SESSION['bsm']['edit']['state'])){$update_array['prsn_state'] = $_SESSION['bsm']['edit']['state'];}
	if(isset($_SESSION['bsm']['edit']['passport']) && $_SESSION['bsm']['edit']['passport']!=null)
            {$update_array['passport'] = $_SESSION['bsm']['edit']['passport'];}
	if(isset($_SESSION['bsm']['edit']['national_id']) && $_SESSION['bsm']['edit']['national_id']!=null)
            {$update_array['natl_id'] = $_SESSION['bsm']['edit']['national_id'];}
	if(isset($_SESSION['bsm']['edit']['driver_license']) && $_SESSION['bsm']['edit']['driver_license']!=null)
            {$update_array['dr_lic'] = $_SESSION['bsm']['edit']['driver_license'];}
	if(isset($_SESSION['bsm']['edit']['gender']) && $_SESSION['bsm']['edit']['gender']!=null)
            {$update_array['gender'] = $_SESSION['bsm']['edit']['gender'];}
	if(isset($_SESSION['bsm']['edit']['age']) && $_SESSION['bsm']['edit']['age']!=null)
            {$update_array['age'] = $_SESSION['bsm']['edit']['age'];}
	if(isset($_SESSION['bsm']['edit']['age_group']) && $_SESSION['bsm']['edit']['age_group']!=null)
            {$update_array['dr_lic'] = $_SESSION['bsm']['edit']['age_group'];}
	if(isset($_SESSION['bsm']['edit']['modify_datetime']) && $_SESSION['bsm']['edit']['modify_datetime']!=null){$update_array['modify_dt'] = $_SESSION['bsm']['edit']['modify_datetime'];}
	if(isset($_SESSION['bsm']['edit']['modify_user']) && $_SESSION['bsm']['edit']['modify_user']!=null){$update_array['modify_by'] = $_SESSION['bsm']['edit']['modify_user'];}
	if(isset($_SESSION['bsm']['edit']['modify_process']) && $_SESSION['bsm']['edit']['modify_process']!=null){$update_array['modify_proc'] = $_SESSION['bsm']['edit']['modify_process'];}

	shn_db_update($update_array,'bsm_person',' WHERE p_uuid = '.$_SESSION['bsm']['edit']['person_uuid']);
}

?>