<?php
/* $Id: add_service.inc,v 1.1 2009-08-27 22:26:49 pradeeper Exp $ */

/**
 * Add a service
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

include_once($global['approot']."/inc/lib_uuid.inc");

/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post 
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post)
{
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
function shn_bsm_add_entry($errors=false)
{
    //if($errors)
    //display_errors();

    global $global;
    global $conf;
    shn_js_toggle_layer();
    shn_form_fopen("add&entity=service",null,null);
    shn_form_hidden(array('seq'=>'entry'));

    shn_form_fsopen(_('Complete the service information and save.'));

    include('service_type.inc');

    shn_form_date(_('State Date'),'state_datetime',array('help'=> _('Set the date the state was changed'), 'req'=>true));
    shn_form_textarea(_('Notes'),'notes',null,array('help' => _('Enter any description about the service or notes in relation to the tasks.'),'req'=>false));
    shn_form_date(_('Start Date'),'start_datetime',array('help'=> _('Set the date the service should begin, which can be in the future or past of the record entry date.'), 'req'=>true));
    shn_form_date(_('End Date'),'end_datetime',array('help'=> _('Set the date when the service should be or is complete or closed'), 'req'=>true));

// may be remove and let user add provider and recipient in edit mode
//    echo $_SESSION['bsm']['add']['provider_name'] ?
//        '<p align="center">'."Provider Name : ".'<b>'.$_SESSION['bsm']['add']['provider_name']."  ".'</b><a align="center" title="'._('Edit').
//        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=provider&rtnid='
//        .$_SESSION['bsm']['add']['service_uuid'].'">'."click to change".'</a></p><br>'
//        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=provider&rtnid='
//        .$_SESSION['bsm']['add']['service_uuid'].'">'."Click to Add Service Provider".'</a></p><br>' ;
//    echo $_SESSION['bsm']['add']['recipient_name'] ?
//        '<p align="center">'."Recipient Name : ".'<b>'.$_SESSION['bsm']['add']['recipient_name']."  ".'</b><a align="center" title="'._('Edit').
//        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=recipient&rtnid='
//        .$_SESSION['bsm']['add']['service_uuid'].'">'."click to change".'</a></p><br>'
//        : '<p align="center"><a title="'._('Add').
//        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=recipient&rtnid='
//        .$_SESSION['bsm']['add']['service_uuid'].'">'."Click to Add Service Recipient".'</a></p><br>';
    shn_form_fsclose();
    shn_form_submit(_('Save'));
    shn_form_fclose();

 }
/* }}} */

/* {{{ Add Entry form Validation */

/**
 * This is the Add Entry Validation function
 * @access public
 * @return void
 */
function shn_bsm_add_validate()
{
    global $global;
    global $conf;

    $error_flag=false;
   
    //clean the post
    shn_tools_clean_post(&$local_post);
    
    $_SESSION['bsm_add']['add']=$local_post;
//    if(! isset($_SESSION['bsm']['add']['service_uuid'])){
//        $_SESSION['bsm']['add']['serv_uuid'] = shn_create_uuid();
//    }
    $state_datetime=$_POST['state_datetime'];
    $start_datetime=$_POST['start_datetime'];
    $end_datetime=$_POST['end_datetime'];
	
//    if(!shn_valid_date($dob,false,'/^\d{4}-\d{2}-\d{2}$/','state_datetime') ||
//        !shn_valid_date($start_datetime,false,'/^\d{4}-\d{2}-\d{2}$/','start_datetime') ||
//        !shn_valid_date($end_datetime,false,'/^\d{4}-\d{2}-\d{2}$/','end_datetime'))
//        {$error_flag = true;}
//    if(isset($_POST['notes']) && $_POST['notes']!=null){$notes = $_POST['notes'];}

    if(empty($local_post)){add_error(_("You have not completed the form"));
        return false;}
   
    if($error_flag){return false;}
    else{return true;}
} 


function shn_bsm_add_confirm(){
    global $global;
    global $conf;

    $_SESSION['bsm']['add']['category'] = isset($_POST['service_category']) ? trim($_POST['service_category']) : null;
    $_SESSION['bsm']['add']['type'] = isset($_POST['service_type']) ? trim($_POST['service_type']) : null;
    $_SESSION['bsm']['add']['state_datetime'] = isset($_POST['state_datetime']) ? trim($_POST['state_datetime']) : null;
    //$_SESSION['bsm']['add']['provider_uuid'] = isset(shn_form_hidden['recipient_uuid']) ? trim(shn_form_hidden['recipient_uuid'] : null;
    //$_SESSION['bsm']['add']['provider'] = isset($_POST['provider']) ? trim($_POST['provider']) : null;
    //$_SESSION['bsm']['add']['provider_uuid'] = isset(shn_form_hidden['recipient_uuid']) ? trim(shn_form_hidden['recipient_uuid'] : null;
    //$_SESSION['bsm']['add']['recipient'] = isset($_POST['recipient']) ? trim($_POST['recipient']) : null;
    $_SESSION['bsm']['add']['notes'] = isset($_POST['notes']) ? trim($_POST['notes']) : null;
    $_SESSION['bsm']['add']['start_datetime'] = isset($_POST['start_datetime']) ? trim($_POST['start_datetime']) : null;
    $_SESSION['bsm']['add']['end_datetime'] = isset($_POST['end_datetime']) ? trim($_POST['end_datetime']) : null;
    $_SESSION['bsm']['add']['create_datetime'] = date('Y-m-d H:i:s');
    $_SESSION['bsm']['add']['create_user'] = "user";
    $_SESSION['bsm']['add']['create_process'] = $conf['host'];
    shn_form_hidden(array('seq'=>'commit'));

}

/* {{{ Add Commit */
/**
 * This function commits the given Missing person's data to the databsae.
 * @access public
 * @return void
 * @TODO    return the service_uuid to main.inc and call the shn_bsm_edit function with the same
 */
function shn_bsm_add_commit()
{
    //require_once($global['approot']."/inc/db_handler.inc");
    // $insert_array[<field_name>] = value
    global $global;
    global $conf;
    include_once($global['approot']."/inc/lib_uuid.inc");
    $service_uuid = shn_create_uuid('service');
//print $service_uuid;
    
    $insert_array = null;
		$insert_array['fclty_uuid'] = $_SESSION['bsm']['edit']['fclty_uuid'];
    $insert_array['serv_uuid'] = $service_uuid;
    if(isset($_SESSION['bsm']['add']['category'])){$insert_array['serv_cate'] = $_SESSION['bsm']['add']['category'];}
    if(isset($_SESSION['bsm']['add']['type'])){$insert_array['serv_type'] = $_SESSION['bsm']['add']['type'];}
    if(isset($_SESSION['bsm']['add']['service_state'])){$insert_array['serv_state'] = $_SESSION['bsm']['add']['service_state'];}
    if(isset($_SESSION['bsm']['add']['state_datetime'])){$insert_array['serv_state_dt'] = $_SESSION['bsm']['add']['state_datetime'];}
    if(isset($_SESSION['bsm']['add']['provider_uuid'])){$insert_array['serv_prov_prsn_id'] = $_SESSION['bsm']['add']['provider_uuid'];}
    if(isset($_SESSION['bsm']['add']['recipient_uuid'])){$insert_array['serv_recp_prsn_id'] = $_SESSION['bsm']['add']['recipient_uuid'];}
    if(isset($_SESSION['bsm']['add']['start_datetime'])){$insert_array['serv_start_dt'] = $_SESSION['bsm']['add']['start_datetime'];}
    if(isset($_SESSION['bsm']['add']['end_datetime'])){$insert_array['serv_end_dt'] = $_SESSION['bsm']['add']['end_datetime'];}
    if(isset($_SESSION['bsm']['add']['notes'])){$insert_array['serv_notes'] = $_SESSION['bsm']['add']['notes'];}
    $insert_array['create_dt'] = $_SESSION['bsm_add']['add']['create_datetime'];
    $insert_array['create_by'] = $_SESSION['bsm_add']['add']['create_user'];
    $insert_array['modify_proc'] = $_SESSION['bsm_add']['add']['create_process'];

    $db = $global['db'];
    //hack to remove null values
    $insert_array['create_dt']=' ';
    $insert_array['create_by']=' ';
    $res = $db->AutoExecute('bsm_service', $insert_array, 'INSERT');
		$res = $db->AutoExecute('bsm_fclty_serv', $insert_array, 'INSERT');
    
    if($res)
        add_confirmation(_t("Service Added successfully"));
    else{
        add_error(_('Error while saving service.'));
    }
}
/**
 * This is a buch of javascript helps for the collapse and expanind of a
 * given division.
 * @todo Move to somewhere 
 * @access public
 * @return void
 */
function shn_js_toggle_layer()
{
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
