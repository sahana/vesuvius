<?php
/**
 * Add a diagnosis - disease + symptoms + signs + causality factors
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

    shn_form_fopen("add&entity=disease",null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_hidden(array('entity'=>$_GET['entity']));
    shn_form_fsopen(_('Complete the ').$_REQUEST['entity']._(' details and save the record'));

    shn_form_text(_('Name of Disease'),'name','size="30"',array('help' => _('Enter name of disease.'), 'req'=>true));

    $sql = "SELECT DISTINCT dis_type AS d_type FROM bsm_dis_type WHERE deactivate_dt IS NULL ";
    $rsql = $global['db']->Execute($sql);
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,_('Type'), 'type',null,array('help' => _('Select a disease type.'), 'req'=>false));
    shn_form_opt_select('opt_dis_priority',_('Priority'), null, array('help' => _('Select the disease priority.'), 'req'=>false));
    shn_form_text(_('ICD 10 Code'),'icd_code','size="30"',array('help' => _('Enter full or part of the ICD 10 code.'), 'req'=>false));
    shn_form_textarea(_('ICD 10 descritpion'),'icd_desc',null,array('help' => _('Enter full or part of the ICD 10 description.'), 'req'=>false));
    shn_form_textarea(_('Other Notes'),'notes',null,array('help' => _('Enter full or part of the ICD 10 description.'), 'req'=>false));
	$case_id = $_REQUEST['rtnid'];
	shn_form_hidden(array('case_id'=>$case_id));
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
	$_SESSION['bsm']['add']['case_id'] = $_POST['case_id'];

	if(!isset($local_post['name'])){
		add_error(_("Please enter the Name of Disease."));
		$error_flag=true;
	}
	/*
	if(!isset($local_post['opt_dis_priority'])){
		add_error(_("Please select a facility chategory; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['type'])){
		add_error(_("Please select a facility type; null values not allowed"));
		$error_flag=true;
	}
	*/
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
    //$_SESSION['bsm']['add']['category'] = isset($_POST['category']) ? trim($_POST['category']) : null;
    $_SESSION['bsm']['add']['type'] = isset($_POST['type']) ? trim($_POST['type']) : null;
    $_SESSION['bsm']['add']['priority'] = isset($_POST['opt_dis_priority']) ? trim($_POST['opt_dis_priority']) : null;
    $_SESSION['bsm']['add']['icd_code'] = isset($_POST['icd_code']) ? trim($_POST['icd_code']) : null;
    $_SESSION['bsm']['add']['icd_desc'] = isset($_POST['icd_desc']) ? trim($_POST['icd_desc']) : null;
    $_SESSION['bsm']['add']['notes'] = isset($_POST['notes']) ? trim($_POST['notes']) : null;
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

    $insert_array = array();
    if(isset($_SESSION['bsm']['add']['name']) && $_SESSION['bsm']['add']['name']!=null)
        {$insert_array['disease'] = $_SESSION['bsm']['add']['name'];}
	
    if(isset($_SESSION['bsm']['add']['type']) && $_SESSION['bsm']['add']['type']!=null)
        {$insert_array['type'] = $_SESSION['bsm']['add']['type'];}

	if(isset($_SESSION['bsm']['add']['priority']) && $_SESSION['bsm']['add']['priority']!=null)
        {$insert_array['priority'] = $_SESSION['bsm']['add']['priority'];}

    if(isset($_SESSION['bsm']['add']['icd_code']) && $_SESSION['bsm']['add']['icd_code']!=null)
        {$insert_array['icd_code'] = $_SESSION['bsm']['add']['icd_code'];}

    if(isset($_SESSION['bsm']['add']['icd_desc']) && $_SESSION['bsm']['add']['icd_desc']!=null)
        {$insert_array['icd_desc'] = $_SESSION['bsm']['add']['icd_desc'];}
    
    if(isset($_SESSION['bsm']['add']['notes']) && $_SESSION['bsm']['add']['notes']!=null)
        {$insert_array['notes'] = $_SESSION['bsm']['add']['notes'];}
	
    //if(isset($_SESSION['bsm']['add']['deactivate_dt']) && $_SESSION['bsm']['add']['deactivate_dt']!=null)
    if ($_SESSION['bsm']['add']['deactivate_dt']!=NULL && $_SESSION['bsm']['add']['deactivate_dt']!="0000-00-00 00:00:00") {
    	$insert_array['deactivate_dt'] = $_SESSION['bsm']['add']['deactivate_dt'];
    	print "Deactivate date is ".$_SESSION['bsm']['add']['deactivate_dt'];
    }
    
            
/*	if(isset($_SESSION['bsm']['add']['category'])){$insert_array['category'] = $_SESSION['bsm']['add']['category'];}
	if(isset($_SESSION['bsm']['add']['type'])){$insert_array['prsn_type'] = $_SESSION['bsm']['add']['type'];}
	if(isset($_SESSION['bsm']['add']['status'])){$insert_array['fclty_status'] = $_SESSION['bsm']['add']['status'];}
    
    if(isset($_SESSION['bsm']['add']['create_datetime']) && $_SESSION['bsm']['add']['create_datetime']!=null)
    	{$insert_array['create_dt'] = $_SESSION['bsm']['add']['create_datetime'];}
    if(isset($_SESSION['bsm']['add']['create_user']) && $_SESSION['bsm']['add']['create_user']!=null)
    	{$insert_array['create_by'] = $_SESSION['bsm']['add']['create_user'];}
    if(isset($_SESSION['bsm']['add']['create_process']) && $_SESSION['bsm']['add']['create_process']!=null)
    	{$insert_array['create_proc'] = $_SESSION['bsm']['add']['create_process'];}
*/    	
	/*if($conf['debug']){
    	print "<hr>";
		print_r($insert_array);
		print "<hr>";
	}*/	
    //shn_db_insert($insert_array,'bsm_facility',true, null);
    //shn_db_insert($insert_array,'bsm_disease',true, null);
    //$sql = "insert into bsm_disease values ('{$insert_array['disease']}','1','{$insert_array['type']}','{$insert_array['priority']}','{$insert_array['icd_code']}','{$insert_array['icd_desc']}','{$insert_array['notes']}','{$insert_array['deactivate_dt']}');";
   $sql = "insert into bsm_disease 
    		(disease,dis_enum,dis_type,dis_priority,icd_code,icd_desc,notes) 
    		values ('{$insert_array['disease']}','1','{$insert_array['type']}','{$insert_array['priority']}','{$insert_array['icd_code']}','{$insert_array['icd_desc']}','{$insert_array['notes']}');";
	//echo $sql;
	$_GET['rtnid'] = $insert_array['disease'];
	/*if($conf['debug']){
    	print "<hr>".$sql."<hr>";
	}*/
	$db = $global['db'];
	$db->Execute($sql);
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