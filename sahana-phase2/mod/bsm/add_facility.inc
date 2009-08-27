<?php
/**
 * Add a facility
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
    
    $_SESSION['bsm']['add_case']['facility'] = $_REQUEST['rtnid'];
	//print $_SESSION['bsm']['add_case']['facility'];    

    shn_form_fopen("add&entity=facility",null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_hidden(array('entity'=>$_GET['entity']));
    shn_form_fsopen(_('Complete the ').$_REQUEST['entity']._('details and save the record'));

    shn_form_text(_('Name'),'name','size="30"',array('help' => _('Enter full or part of the last name also known as Surname or Family Name.'), 'req'=>true));
    include('facility_type.inc');
    shn_form_opt_select('opt_fac_status',_('Status'), null,array('help' => _('Select a facility type.'), 'req'=>true));
    echo $_SESSION['bsm']['add']['location_name'] ?
        '<p align="center">'.'Location Name: '.$_SESSION['bsm']['add']['location_name'].'<a title="'._('Edit').'" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lookup&id='.$_SESSION['bsm']['add']['facility_uuid'].'">'." (click to change the location)".'</a></p>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lookup&id='.$_SESSION['bsm']['add']['facility_uuid'].'">'."Click to Add a location".'</a></p>' ;

        shn_form_hidden(array('case_uuid'=>$_SESSION['bsm']['add_case']['facility']));
    shn_form_submit(_('Save'));
    shn_form_fsclose();
    shn_form_fclose();

//    shn_bsm_cont_vw();
//    shn_bsm_addr_vw();
//    shn_bsm_serv_vw();
 }
/*
function shn_bsm_cont_vw(){
    global $global;
    global $conf;

//    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
//    $sql = "SELECT con.cont_uuid AS contact_uuid, con.cont_mode c_mode, con.cont_val c_value FROM bsm_contact con ";
//    $sql .= "INNER JOIN bsm_prsn_cont pcon ON pcon.cont_uuid = con.cont_uuid INNER JOIN bsm_person p ON p.p_uuid = pcon.p_uuid ";
//    $sql .= "WHERE con.deactivate_dt IS NULL AND p.p_uuid = '".$_SESSION['bsm']['add']['person_uuid']."'";
//    $details = $global['db']->Execute($sql);
//    if($_GET['act']!='add')
//        $select = true;
    shn_form_fsopen(_($_REQUEST['entity'])._(' Contact Details (to edit clink on the specific UUID)'));
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

function shn_bsm_addr_vw(){
    global $global;
    global $conf;

//    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
//    $sql = "SELECT a.addr_uuid AS address_uuid, a.addr_type AS a_type, a.addr_status AS a_status, a.line_1 AS line1, ";
//    $sql .= "a.line_2 AS line2, a.cty_twn_vil AS city_town_vill, a.post_code AS post_code, a.district AS district, ";
//    $sql .= "a.state_prov AS state_province, a.country AS country FROM bsm_address a ";
//    $sql .= "INNER JOIN bsm_prsn_addr pa ON pa.addr_uuid = a.addr_uuid INNER JOIN bsm_person p ON p.p_uuid = pa.p_uuid ";
//    $sql .= "WHERE pa.deactivate_dt IS NULL AND pa.p_uuid = '".$_SESSION['bsm']['add']['person_uuid']."'";
//    $details = $global['db']->Execute($sql);
//    if($_GET['act']!='add')
//        $select = true;
    shn_form_fsopen(_($_REQUEST['entity'])._(' Address Information (to edit clink on the specific UUID)'));
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
function shn_bsm_serv_vw(){
    global $global;
    global $conf;

//    //step 2: load details from bsm_prsn_cont, bsm_contact, & bsm_cont_mode
//    $sql =  "SELECT s.serv_uuid AS service_uuid, s.serv_cate AS category, s.serv_type AS type, s.serv_status AS status, ";
//    $sql .= "s.serv_status_dt AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, ";
//    //$sql .= "s.serv_prov_prsn_id AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, ";
//    $sql .= "s.serv_notes AS notes FROM bsm_service s INNER JOIN bsm_fclty_serv sf ON sf.serv_uuid = s.serv_uuid ";
//    $sql .= "INNER JOIN bsm_facility f ON f.fclty_uuid = sf.fclty_uuid WHERE sf.deactivate_dt IS NULL ";
//    $sql .= "AND sf.fclty_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";
//    $details = $global['db']->Execute($sql);
//
//    if($_GET['act']!='edit')
//        $select = true;
    shn_form_fsopen(_($_REQUEST['entity'])._(' Service Information (to edit or for further details clik on the record UUID)'));
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
        <TD> <?php   echo $detail['start_datetime'] ? $detail['start_datetime'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $detail['end_datetime'] ? $detail['end_datetime'].'<br>' : ''; ?> </TD>
    </TR><?php
        }
    }
    ?></TABLE></div><?php
    echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=service&seq=lookup&id='.
        $_SESSION['bsm']['edit']['fclty_uuid'].'">'." click to ADD a new Service".'</a><br>';
    shn_form_fsclose();
}
 */

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

	if(!isset($local_post['name'])){
		add_error(_("Please enter the facility name; null values not allowed"));
		$error_flag=true;
	}
	/*if(!isset($local_post['category'])){
		add_error(_("Please select a facility chategory; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['type'])){
		add_error(_("Please select a facility type; null values not allowed"));
		$error_flag=true;
	}*/
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

    $_SESSION['bsm']['add']['name'] = isset($_POST['name']) ? trim($_POST['name']) : null;
    $_SESSION['bsm']['add']['category'] = isset($_POST['category']) ? trim($_POST['category']) : null;
    $_SESSION['bsm']['add']['type'] = isset($_POST['type']) ? trim($_POST['type']) : null;
    $_SESSION['bsm']['add']['status'] = isset($_POST['opt_fac_status']) ? trim($_POST['opt_fac_status']) : null;
    $_SESSION['bsm']['add']['create_datetime'] =  date('Y-m-d H:i:s');
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

    $insert_array = null;
    $fclty_uuid = shn_create_uuid('facility');
    $case_uuid = $_SESSION['bsm']['add_case']['facility'];

    $insert_array['fclty_uuid'] = $fclty_uuid;

    if(isset($_SESSION['bsm']['add']['name']) && $_SESSION['bsm']['add']['name']!=null)
        {$insert_array['fclty_desc'] = $_SESSION['bsm']['add']['name'];}
//      if(isset($_SESSION['bsm']['add']['category'])){$insert_array['category'] = $_SESSION['bsm']['add']['category'];}
	if(isset($_SESSION['bsm']['add']['type'])){$insert_array['fclty_type'] = $_SESSION['bsm']['add']['type'];}
	if(isset($_SESSION['bsm']['add']['status'])){$insert_array['fclty_status'] = $_SESSION['bsm']['add']['status'];}
    if(isset($_SESSION['bsm']['add']['create_datetime']) && $_SESSION['bsm']['add']['create_datetime']!=null){$insert_array['create_dt'] = $_SESSION['bsm']['add']['create_datetime'];}
    if(isset($_SESSION['bsm']['add']['create_user']) && $_SESSION['bsm']['add']['create_user']!=null){$insert_array['create_by'] = $_SESSION['bsm']['add']['create_user'];}
    if(isset($_SESSION['bsm']['add']['create_process']) && $_SESSION['bsm']['add']['create_process']!=null){$insert_array['create_proc'] = $_SESSION['bsm']['add']['create_process'];}

    $db = $global['db'];
    $res = $db->AutoExecute('bsm_facility', $insert_array, 'INSERT');
    
    //$res1 = $db->AutoExecute('bsm_cases', 'UPDATE', 'case_uuid')
    if($case_uuid!=NULL || $case_uuid !='')
    {
    $sql = "UPDATE bsm_cases SET fclty_uuid='{$fclty_uuid}', fclty_name='{$insert_array['fclty_type']}' WHERE case_uuid='$case_uuid'";
    $res1 = $db->Execute($sql);
   // print $sql;
    }
    if($res)
        add_confirmation(_t("Facility Added successfully"));
    else{
        add_error(_('Error while saving facility.'));
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
