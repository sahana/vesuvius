<?php
/* $Id: edit_service.inc,v 1.1 2009-08-27 22:26:48 pradeeper Exp $ */

/**
 * Edit a service
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
function shn_bsm_edit_load($service_uuid)
{
	global $global;
        global $conf;

			$_SESSION['bsm']['edit']['facility_uuid'] = trim($_REQUEST['id']);
			//print($_SESSION['bsm']['edit']['facility_uuid']);

			$sql = "SELECT cat.serv_cate as category, s.recp_p_uuid AS recepient, s.serv_uuid AS service_uuid, s.serv_type AS type, s.serv_state AS state, s.serv_state_dt AS status_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, s.serv_notes AS notes, fs.* FROM bsm_serv_cate cat INNER JOIN bsm_serv_type AS type ON cat.serv_cate = type.serv_cate INNER JOIN bsm_service s ON type.serv_type = s.serv_type INNER JOIN bsm_fclty_serv fs ON  s.serv_uuid = fs.serv_uuid INNER JOIN bsm_facility f ON f.fclty_uuid = fs.fclty_uuid WHERE fs.deactivate_dt IS NULL AND s.serv_uuid = '".$_SESSION['bsm']['edit']['facility_uuid']."'";
//print $sql;
    $rs = $global['db']->Execute($sql);

	//@todo: check existance
/*        $sql =  "SELECT s.serv_uuid AS service_uuid, s.serv_cate AS category, s.serv_type AS type, ";
        $sql .= "s.serv_state AS state, s.serv_state_dt AS state_datetime, s.serv_start_dt AS start_datetime, s.serv_end_dt AS end_datetime, ";
        $sql .= "s.loc_uuid AS location_uuid, (SELECT loc_name FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = s.loc_uuid) AS location_name, ";
        $sql .= "s.serv_notes AS notes, s.prov_p_uuid AS provider_uuid, s.recp_p_uuid AS recipient_uuid, ";
        $sql .= "(SELECT last_name FROM bsm_person WHERE deactivate_dt IS NULL AND p_uuid = s.prov_p_uuid) AS provider_name, ";
        $sql .= "(SELECT last_name FROM bsm_person WHERE deactivate_dt IS NULL AND p_uuid = s.recp_p_uuid) AS recipient_name ";
        $sql .= "FROM bsm_service s WHERE s.deactivate_dt IS NULL AND s.serv_uuid = '$service_uuid' ";
	$rs = $global['db']->Execute($sql);
*/
	$_SESSION['bsm']['edit']['service_uuid'] = $rs->fields['service_uuid'];
        $_SESSION['bsm']['edit']['category'] = $rs->fields['category'];
        $_SESSION['bsm']['edit']['type'] = $rs->fields['type'];
	$_SESSION['bsm']['edit']['state'] = $rs->fields['state'];
	$_SESSION['bsm']['edit']['state_datetime'] = $rs->fields['status_datetime'];
	$_SESSION['bsm']['edit']['start_datetime'] = $rs->fields['start_datetime'];
	$_SESSION['bsm']['edit']['end_datetime'] = $rs->fields['end_datetime'];
	$_SESSION['bsm']['edit']['location_uuid'] = $rs->fields['location_uuid'];
	$_SESSION['bsm']['edit']['location_name'] = $rs->fields['location_name'];
	$_SESSION['bsm']['edit']['notes'] = $rs->fields['notes'];
	$_SESSION['bsm']['edit']['provider_uuid'] = $rs->fields['provider_uuid'];
	$_SESSION['bsm']['edit']['provider_name'] = $rs->fields['provider_name'];
	$_SESSION['bsm']['edit']['recipient_uuid'] = $rs->fields['recipient_uuid'];
	$_SESSION['bsm']['edit']['recipient_name'] = $rs->fields['recipient_name'];

	list($state_date, $state_time) =  split(" ", $_SESSION['bsm']['edit']['state_datetime']);
	$_SESSION['bsm']['edit']['state_date'] = $state_date;
	$_SESSION['bsm']['edit']['state_time'] = $state_time;

	list($start_date, $start_time) =  split(" ", $_SESSION['bsm']['edit']['start_datetime']);
	$_SESSION['bsm']['edit']['start_date'] = $start_date;
	$_SESSION['bsm']['edit']['start_time'] = $start_time;

	list($end_date, $end_time) =  split(" ", $_SESSION['bsm']['edit']['end_datetime']);
	$_SESSION['bsm']['edit']['end_date'] = $end_date;
	$_SESSION['bsm']['edit']['end_time'] = $end_time;
}
/**
 * @name    Service Edit Form
 * @tutorial    A service is a combination of the category and type; once a service has been set user cannot
 *              change the category or type; wanting to change the category or type means it is a new service;
 *              hence, user should delete the current service and create a new service
 * @param mixed $errors
 * @access public
 * @return void
 * @TODO    service state date should change to today when state is changed "onchange"
 */
function shn_bsm_edit_entry($errors=false)
{
	//if($errors)
	// display_errors();
    global $global;
    global $conf;
    
    shn_form_fopen("edit&entity=service",null,null);
    shn_form_hidden(array('seq'=>'entry'));

    shn_form_fsopen(_('Details for Service ID: ').$_SESSION['bsm']['edit']['service_uuid']);

    echo '<br /><center><b>'._('Category : ').'</b> '.$_SESSION['bsm']['edit']['category'].' '.'</center><br />';
    echo '<center><b>'._('Type     : ').'</b> '.$_SESSION['bsm']['edit']['type'].' '.'</center><br />';

    $sql = "SELECT DISTINCT serv_state AS state FROM bsm_serv_state WHERE deactivate_dt IS NULL ";
    //if (isset($_POST['location_category'])){$location_category = trim($_POST['location_category']); $sql .= "AND lt.loc_cate = '$location_category'";}
    $rsql = $global['db']->Execute($sql);
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,_('Service State'), 'state',null,array('value'=>$_SESSION['bsm']['edit']['state'], 'help' => _('Select a location type.'), 'req'=>true));
    shn_form_date(_('State Date'),'state_datetime',array('value'=>$_SESSION['bsm']['edit']['state_date'], 'help'=> _('Set the date the state was changed'), 'req'=>true));

    echo $_SESSION['bsm']['edit']['location_name'] ?
        '<p align="center">'."Location Name : ".'<b>'.$_SESSION['bsm']['edit']['location_name']."  ".'</b><a align="center" title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lukup&rtnfrm=service&rtnfk=location&rtnid='
        .$_SESSION['bsm']['edit']['service_uuid'].'">'."click to change".'</a></p><br>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lukup&rtnfrm=service&rtnfk=location&rtnid='
        .$_SESSION['bsm']['edit']['service_uuid'].'">'."Click to Add Location".'</a></p><br>' ;

    shn_form_textarea(_('Notes'),'notes',null,array('value'=>$_SESSION['bsm']['edit']['notes'], 'help' => _('Enter any description about the service or notes in relation to the tasks.'),'req'=>false));
    shn_form_date(_('Start Date'),'start_datetime',array('value'=>$_SESSION['bsm']['edit']['start_date'], 'help'=> _('Set the date the service should begin, which can be in the future or past of the record entry date.'), 'req'=>true));
    shn_form_date(_('End Date'),'end_datetime',array('value'=>$_SESSION['bsm']['edit']['end_date'], 'help'=> _('Set the date when the service should be or is complete or closed'), 'req'=>true));

    echo $_SESSION['bsm']['edit']['provider_name'] ?
        '<p align="center">'."Provider Name : ".'<b>'.$_SESSION['bsm']['edit']['provider_name']."  ".'</b><a align="center" title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=provider&rtnid='
        .$_SESSION['bsm']['edit']['service_uuid'].'">'."click to change".'</a></p><br>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=provider&rtnid='
        .$_SESSION['bsm']['edit']['service_uuid'].'">'."Click to Add Service Provider".'</a></p><br>' ;
    echo $_SESSION['bsm']['edit']['recipient_name'] ?
        '<p align="center">'."Recipient Name : ".'<b>'.$_SESSION['bsm']['edit']['recipient_name']."  ".'</b><a align="center" title="'._('Edit').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=recipient&rtnid='
        .$_SESSION['bsm']['edit']['service_uuid'].'">'."click to change".'</a></p><br>'
        : '<p align="center"><a title="'._('Add').
        '" href="index.php?mod='.$global['module'].'&act=search&entity=person&seq=lukup&rtnfrm=service&rtnfk=recipient&rtnid='
        .$_SESSION['bsm']['edit']['service_uuid'].'">'."Click to Add Service Recipient".'</a></p><br>' ;

    //service item detail
    $sql = "SELECT si.item_name AS item_name, si.item_state AS item_state, si.serv_cate AS service_category, si.item_desc AS item_description, i.serv_uuid AS service_uuid FROM bsm_serv_type_item si INNER JOIN bsm_serv_item i ON si.item_name = i.item_name WHERE i.deactivate_dt IS NULL ";
    $sql .= "AND i.serv_uuid = '".$_SESSION['bsm']['edit']['service_uuid']."'";
//print $sql;
    $details = $global['db']->Execute($sql);
    if($_GET['act']!='edit')
        $select = true;
    ?>
    <div id = "service_itme_table" align="center">
    <TABLE>
    <THEAD>
        <TD><?= _('Item Name');?></TD>
        <TD><?= _('Select');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($details!=null)
    {
        foreach($details as $detail)
        {
    ?><TR>
        <TD> <?php   echo $detail['item_name'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=serviceitem&rtnid='.$detail['service_uuid'].'">'.
                        $detail['item_name'].'</a><br>' : ''; ?> </TD>
    </TR><?php
        }
    }
    ?></TABLE></div><?php
    echo '<p align="center">'._("To Add an item ").'<a title="'._('Edit').'" href="index.php?mod='.
          $global['module'].'&act=add&entity=serviceitem&id='.$_SESSION['bsm']['edit']['service_uuid'].'&rtnid='.$detail['service_item'].'">'._("Click").'</a></p><br>';

    shn_form_submit(_('Save'));
    shn_form_fsclose();
}
/**
 * @name Validation entries in the service Edit Form
 * @access public
 * @return void
 */
function shn_bsm_edit_validate(){
	global $global;
	global $conf;

	$error_flag=false;

	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

	$local_post['service_uuid'] = $_SESSION['bsm']['edit']['service_uuid'];
	//clean
	$_SESSION['bsm']['edit']=null;
	$_SESSION['bsm']['edit']=$local_post;
	
	if(!isset($local_post['start_datetime'])){
		add_error(_("Please set the start date."));
		$error_flag=true;
	}
	if(!isset($local_post['state_datetime'])){
		add_error(_("Please set the state date"));
		$error_flag=true;
	}

	if($error_flag)	return false;
	else{return true;}
}
/**
 * @name Confirmation page values
 * @access public
 * @return void
 */
function shn_bsm_edit_confirm(){
    global $global;
    global $conf;

    $_SESSION['bsm']['edit']['category'] = isset($_POST['category']) ? trim($_POST['category']) : null;
    $_SESSION['bsm']['edit']['type'] = isset($_POST['type']) ? trim($_POST['type']) : null;
    $_SESSION['bsm']['edit']['state'] = isset($_POST['state']) ? trim($_POST['state']) : null;
    $_SESSION['bsm']['edit']['state_datetime'] = isset($_POST['state_datetime']) ? trim($_POST['state_datetime']) : null;
    //@deprecate redundant
    //$_SESSION['bsm']['edit']['provider_uuid'] = $_SESSION['bsm']['edit']['provider_uuid']!=null ? $_SESSION['bsm']['edit']['provider_uuid'] : null;
    //$_SESSION['bsm']['edit']['recipient_uuid'] = $_SESSION['bsm']['edit']['recipient_uuid']!=null ? $_SESSION['bsm']['edit']['recipient_uuid'] : null;
    $_SESSION['bsm']['edit']['notes'] = isset($_POST['notes']) ? trim($_POST['notes']) : null;
    $_SESSION['bsm']['edit']['start_datetime'] = isset($_POST['start_datetime']) ? trim($_POST['start_datetime']) : null;
    $_SESSION['bsm']['edit']['end_datetime'] = isset($_POST['end_datetime']) ? trim($_POST['end_datetime']) : null;
    $_SESSION['bsm']['edit']['modify_datetime'] = getdate();
    $_SESSION['bsm']['edit']['modify_user'] = "user";
    $_SESSION['bsm']['edit']['modify_process'] = $conf['host'].'_'.$global['module'];

    shn_form_hidden(array('seq'=>'commit'));

}
/**
 * @name Commits the changes to the database
 * @access public
 * @return void
 */
function shn_bsm_edit_commit(){
    
    global $global;
		$db = $global['db'];
    global $conf;

    //$update_array['serv_uuid'] = $_SESSION['bsm']['edit']['service_uuid'];
    if(isset($_SESSION['bsm']['edit']['category']) && $_SESSION['bsm']['edit']['category']!=null)
        {$update_array['serv_cate'] = $_SESSION['bsm']['edit']['category'];
}
    if(isset($_SESSION['bsm']['edit']['type']) && $_SESSION['bsm']['edit']['type']!=null)
        {$update_array['serv_type'] = $_SESSION['bsm']['edit']['type'];
}
    if(isset($_SESSION['bsm']['edit']['state']) && $_SESSION['bsm']['edit']['state']!=null)
        {$update_array['serv_state'] = $_SESSION['bsm']['edit']['state'];}
    if(isset($_SESSION['bsm']['edit']['state_datetime']) && $_SESSION['bsm']['edit']['state_datetime']!=null)
        {$update_array['serv_start_dt'] = $_SESSION['bsm']['edit']['state_datetime'];}
    if(isset($_SESSION['bsm']['edit']['provider_uuid']) && $_SESSION['bsm']['edit']['provider_uuid']!=null)
        {$update_array['prov_p_id'] = $_SESSION['bsm']['edit']['provider_uuid'];}
    if(isset($_SESSION['bsm']['edit']['recipient_uuid']) && $_SESSION['bsm']['edit']['recipient_uuid']!=null)
        {$update_array['recp_p_id'] = $_SESSION['bsm']['edit']['recipient_uuid'];}
    if(isset($_SESSION['bsm']['edit']['start_datetime']) && $_SESSION['bsm']['edit']['start_datetime']!=null)
        {$update_array['serv_start_dt'] = $_SESSION['bsm']['edit']['start_datetime'];}
    if(isset($_SESSION['bsm']['edit']['end_datetime']) && $_SESSION['bsm']['edit']['end_datetime']!=null)
        {$update_array['serv_end_dt'] = $_SESSION['bsm']['edit']['end_datetime'];}
    if(isset($_SESSION['bsm']['edit']['notes']) && $_SESSION['bsm']['edit']['notes']!=null)
        {$update_array['serv_notes'] = $_SESSION['bsm']['edit']['notes'];}
    $update_array['modify_dt'] = $_SESSION['bsm']['edit']['modify_datetime'];
    $update_array['modify_by'] = $_SESSION['bsm']['edit']['modify_user'];
    $update_array['modify_proc'] = $_SESSION['bsm']['edit']['modify_process'];

		$service_uuid = $_SESSION['bsm']['edit']['service_uuid'];
		$serv_type = $update_array['serv_type'];
		$serv_cate = $update_array['serv_cate'];
		$serv_state = $update_array['serv_state'];
		$serv_start_dt = $update_array['serv_start_dt'];
		$provider_uuid = $update_array['prov_p_id'];
		$recipient_uuid = $update_array['recp_p_id'];
		$start_dt = $update_array['serv_start_dt'];
		$end_dt = $update_array['serv_end_dt'];
		$serv_notes = $update_array['serv_notes'];
		$modify_dt = $update_array['modify_dt'];
		$modify_by = $update_array['modify_by'];
		$modify_proc = $update_array['modify_proc'];		
		
		
//print $_SESSION['bsm']['edit']['service_uuid'];
//var_dump($update_array);
		$sql = "UPDATE bsm_service SET serv_state_dt='$serv_state_dt', prov_p_uuid='$provider_uuid', recp_p_uuid='$recipient_uuid', serv_start_dt='$serv_start_dt', serv_notes='$serv_notes', modify_dt='$modify_dt', modify_by='$modify_by', modify_proc='$modify_proc' WHERE serv_uuid='$service_uuid'";
		$res=$db->Execute($sql);
		if($res){
			add_confirmation(_('Service Updated Successfully'));
		} else {
			add_error(_('Error While updating Service'));
		}
//print $sql;
    //shn_db_update($update_array,'bsm_service',' WHERE serv_uuid =  '.$_SESSION['bsm']['edit']['service_uuid']);
}
/**
 * @name    Commits loouk up value of parent location
 * @access public
 * @return void
 */
function shn_bsm_edit_commit_lukup($pk_uuid=null,$fk_uuid=null,$fk_name=null){

    global $global;
    global $conf;
    echo "pk = ".$pk_uuid." fk = ".$fk_uuid." fkname = ".$fk_name;
    if ($pk_uuid==null || $fk_uuid==null){add_error(_("Your lookup selection is invalid, failed to return the values!"));}
    else{
        switch ($fk_name)
        {
            case 'provider':
                $update_array['prov_p_uuid'] = $fk_uuid;
                shn_db_update($update_array,'bsm_service',' WHERE serv_uuid = '.$pk_uuid);
                break;
            case 'recipient':
                $update_array['recp_p_uuid'] = $fk_uuid;
                shn_db_update($update_array,'bsm_service',' WHERE serv_uuid = '.$pk_uuid);
                break;
            case 'location':

                $update_array['loc_uuid'] = $fk_uuid;
                shn_db_update($update_array,'bsm_service',' WHERE serv_uuid = '.$pk_uuid);
                break;
            default:
                break;
        }
    }
}
?>
