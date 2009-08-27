<?php
/* $Id: edit_location.inc,v 1.3 2009-08-27 22:26:48 pradeeper Exp $ */

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
 * @package     module
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @TODO       At some point this locations object or entity should be blended with the
 * original concept of locations used in MPR, GIS, VR etc based on a common acceptable standard set
 * of onthologies and taxinmoies
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
function shn_bsm_edit_load($location_uuid)
{
	global $global;
        global $conf;

	//@todo: check existance
        $sql = "SELECT loc_uuid AS location_uuid, loc_prnt_uuid AS parent_uuid, (SELECT loc_name FROM bsm_location ";
        $sql .= "WHERE deactivate_dt IS NULL AND loc_uuid IN (SELECT loc_prnt_uuid FROM bsm_location ";
        $sql .= "WHERE deactivate_dt IS NULL AND loc_uuid = '$location_uuid')) AS parent_name, ";
        $sql .= "loc_cate AS category, loc_type AS type, loc_name AS name, loc_desc AS description, loc_iso_code AS iso_code, ";
        $sql .= "loc_shape AS shape, loc_x_vect AS x_vector, loc_y_vect AS y_vector, loc_z_vect AS z_vector ";
        $sql .= "FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = '$location_uuid' ";

    $sql = "SELECT * FROM bsm_location WHERE loc_uuid='$location_uuid'";

//	$rs = $global['db']->Execute($sql);
    $rs = $global['db']->GetRow($sql);
    //print $sql;
    $_SESSION['bsm']['edit'] = $rs;

}
/* @name Edit location form
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_bsm_edit_entry($errors=false){
	//if($errors)
	// display_errors();
    global $global;
    global $conf;
    
    shn_form_fopen("edit&entity=location",null,null);
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Details for Location ID: '.$_SESSION['bsm']['edit']['loc_uuid']));
    shn_form_text(_('Name'),'name','size="30"',array('value'=>$_SESSION['bsm']['edit']['loc_name'], 'help' => _('Enter full or part of the location name.'), 'req'=>true));
    $loc_type = $_SESSION['bsm']['edit']['loc_type'];
    include_once('loc_type.inc');
	$parent = $_REQUEST['rtnid'];
    shn_form_hidden(array('parent_uuid'=>$_SESSION['bsm']['edit']['loc_prnt_uuid']));
	$sql = "SELECT loc_uuid, loc_name from bsm_location WHERE loc_uuid IN (select loc_prnt_uuid from bsm_location where loc_uuid = '$parent' )";
	$res = $global['db']->Execute($sql);
	//echo $res->fields['loc_name'];
    echo $_SESSION['bsm']['edit']['parent_name'] ?
        '<p align="center">'."Parent Location : ".'<b>'.$_SESSION['bsm']['edit']['parent_name']."  ".'</b><a align="center" title="'._('Edit').'" href="index.php?mod='.
        $global['module'].'&act=search&entity=location&seq=lukup&rtnfrm=location&rtnid='
        .$_SESSION['bsm']['edit']['loc_uuid'].'">'."click to change".'</a></p><br><br>'
        : '<p align="center"><a title="'._('Add').'" href="index.php?mod='
        .$global['module'].'&act=search&entity=location&seq=lukup&rtnfrm=location&rtnid='
        .$_SESSION['bsm']['edit']['loc_uuid'].'">'."Click to Add Parent Location - <b>".$res->fields['loc_name'].'</b></a></p><br><br>' ;
    
    shn_form_text(_('Description'),'description','size="30"',array('value'=>$_SESSION['bsm']['edit']['loc_desc'], 'help' => _('Type in the location ISO code.'), 'req'=>false));

    shn_form_opt_select('opt_shape', _('Shape'), "", array('help' => _('Select a location shape.'), 'req'=>false));

    shn_form_text(_('X Vector'),'x_vector','size="30"',array('value'=>$_SESSION['bsm']['edit']['x_vector'], 'help' => _('Type in the vector seperate each element by a comma e.g. 100.6, 101.2, 102.5.'), 'req'=>false));
    shn_form_text(_('Y Vector'),'y_vector','size="30"',array('value'=>$_SESSION['bsm']['edit']['y_vector'], 'help' => _('Type in the vector seperate each element by a comma e.g. 0.6, 1.2, 2.5.'), 'req'=>false));
    shn_form_text(_('Z Vector'),'z_vector','size="30"',array('value'=>$_SESSION['bsm']['edit']['z_vector'], 'help' => _('Type in the vector seperate each element by a comma e.g. 10.6, 11.2, 12.5.'), 'req'=>false));
    shn_form_text(_('ISO Code'),'iso_code','size="30"',array('value'=>$_SESSION['bsm']['edit']['loc_iso_code'], 'help' => _('Type in the location ISO code.'), 'req'=>false));
	if($_REQUEST['lukupid'] != null)
	{
		$parent_id = trim($_REQUEST['lukupid']);
		shn_form_hidden(array('parent_id' => $parent_id));
	}
    shn_form_submit(_('Save'));
    shn_form_fsclose();
    shn_form_fclose();
}
/* @name validation of input elements in Edit Form
 * @access public
 * @return boolean $erroflag
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

	$local_post['loc_uuid'] = $_SESSION['bsm']['edit']['loc_uuid'];
	//clean
	$_SESSION['bsm']['edit']=null;
	$_SESSION['bsm']['edit']=$local_post;

	if(!isset($local_post['name'])){
		add_error(_("Please enter the location name; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['loc_cate'])){
		add_error(_("Please select a location category; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['loc_type'])){
		add_error(_("Please select a location type; null values not allowed"));
		$error_flag=true;
	}
        $_SESSION['bsm']['edit']['location_id'] = $local_post['loc_uuid'];
	if($error_flag)	{return false;}
        else {
            //ensure similar record with name, category, & type does not exisits
            $sql = "SELECT 1 FROM bsm_location WHERE deactivate_dt IS NULL AND loc_name = '".$local_post['name']."' ";
            //$sql .= " AND loc_cate = '".$local_post['category']."' AND loc_type = '".$local_post['type']."' ";
            $sql .= " AND loc_type = '".$local_post['type']."' ";
            $sql .= " AND loc_uuid != '".$local_post['loc_uuid']."'";
            
            $rsql = $global['db']->Execute($sql);
            if($rsql->RecordCount() > 0){
                add_error(_('Recod with location name = ').$local_post['name']._(', category = ').$local_post['category'].
                    _(', and type = ').$local_post['type']._(" existis. Search again to avoid duplication."));
                return false;
            }
            else {return true;}
        }
}
/**
 * @name    Confirmation page
 * @access public
 * @return void
 */
function shn_bsm_edit_confirm(){
    global $global;
    global $conf;
	$_SESSION['bsm']['edit']['parent_id'] = isset($_POST['parent_id']) ? trim($_POST['parent_id']) : null;
    $_SESSION['bsm']['edit']['loc_cate'] = isset($_POST['loc_cate']) ? trim($_POST['loc_cate']) : null;
    $_SESSION['bsm']['edit']['loc_type'] = isset($_POST['loc_type']) ? trim($_POST['loc_type']) : null;
    $_SESSION['bsm']['edit']['loc_name'] = isset($_POST['name']) ? trim($_POST['name']) : null;
    $_SESSION['bsm']['edit']['loc_prnt_uuid'] = isset($_POST['parent_uuid']) ? trim($_POST['parent_uuid']) : null;
    $_SESSION['bsm']['edit']['loc_desc'] = isset($_POST['description']) ? trim($_POST['description']) : null;
    $_SESSION['bsm']['edit']['loc_shape'] = isset($_POST['shape']) ? trim($_POST['shape']) : null;
    $_SESSION['bsm']['edit']['x_vector'] = isset($_POST['x_vector']) ? trim($_POST['x_vector']) : null;
    $_SESSION['bsm']['edit']['y_vector'] = isset($_POST['y_vector']) ? trim($_POST['y_vector']) : null;
    $_SESSION['bsm']['edit']['z_vector'] = isset($_POST['z_vector']) ? trim($_POST['z_vector']) : null;
    $_SESSION['bsm']['edit']['loc_iso_code'] = isset($_POST['iso_code']) ? trim($_POST['iso_code']) : null;
    $_SESSION['bsm']['edit']['modify_datetime'] = date('Y-m-d H:i:s');
    $_SESSION['bsm']['edit']['modify_user'] = "user";
    $_SESSION['bsm']['edit']['modify_process'] = $conf['host'];

    shn_form_hidden(array('seq'=>'commit'));
}
/**
 * Commits the changes to the database
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_commit(){
	// $update_array[<field_name>] = value
	global $global;
	global $conf;

	
if(isset($_SESSION['bsm']['edit']['parent_id']) && $_SESSION['bsm']['edit']['parent_id']!=null)
            {$update_array['loc_prnt_uuid'] = $_SESSION['bsm']['edit']['parent_id'];}
	
	if(isset($_SESSION['bsm']['edit']['loc_name']) && $_SESSION['bsm']['edit']['loc_name']!=null)
            {$update_array['loc_name'] = $_SESSION['bsm']['edit']['loc_name'];}
	if(isset($_SESSION['bsm']['edit']['loc_type'])){$update_array['loc_type'] = $_SESSION['bsm']['edit']['loc_type'];}
	if(isset($_SESSION['bsm']['edit']['loc_prnt_uuid']) && $_SESSION['bsm']['edit']['loc_prnt_uuid']!=null)
            {$update_array['loc_prnt_uuid'] = $_SESSION['bsm']['edit']['loc_prnt_uuid'];}
	if(isset($_SESSION['bsm']['edit']['loc_desc']) && $_SESSION['bsm']['edit']['loc_desc']!=null)
            {$update_array['loc_desc'] = $_SESSION['bsm']['edit']['loc_desc'];}
	if(isset($_SESSION['bsm']['edit']['loc_shape']) && $_SESSION['bsm']['edit']['loc_shape']!=null)
            {$update_array['loc_shape'] = $_SESSION['bsm']['edit']['loc_shape'];}
	if(isset($_SESSION['bsm']['edit']['x_vector']) && $_SESSION['bsm']['edit']['x_vector']!=null)
            {$update_array['loc_x_vect'] = $_SESSION['bsm']['edit']['x_vector'];}
	if(isset($_SESSION['bsm']['edit']['y_vector']) && $_SESSION['bsm']['edit']['y_vector']!=null)
            {$update_array['loc_y_vect'] = $_SESSION['bsm']['edit']['y_vector'];}
	if(isset($_SESSION['bsm']['edit']['z_vector']) && $_SESSION['bsm']['edit']['z_vector']!=null)
            {$update_array['loc_z_vect'] = $_SESSION['bsm']['edit']['z_vector'];}
        if(isset($_SESSION['bsm']['edit']['iso_code']) && $_SESSION['bsm']['edit']['iso_code']!=null)
            {$update_array['loc_iso_code'] = $_SESSION['bsm']['edit']['loc_iso_code'];}
	if(isset($_SESSION['bsm']['edit']['modify_datetime']) && $_SESSION['bsm']['edit']['modify_datetime']!=null){$update_array['modify_dt'] = $_SESSION['bsm']['edit']['modify_datetime'];}
	if(isset($_SESSION['bsm']['edit']['modify_user']) && $_SESSION['bsm']['edit']['modify_user']!=null){$update_array['modify_by'] = $_SESSION['bsm']['edit']['modify_user'];}
	if(isset($_SESSION['bsm']['edit']['modify_process']) && $_SESSION['bsm']['edit']['modify_process']!=null){$update_array['modify_proc'] = $_SESSION['bsm']['edit']['modify_process'];}
//var_dump($update_array);
	//shn_db_update($update_array,'bsm_location',' WHERE loc_uuid = '.$_SESSION['bsm']['edit']['loc_uuid']);
    $res = $global['db']->AutoExecute('bsm_location', $update_array, 'UPDATE',"loc_uuid = '{$_SESSION['bsm']['edit']['loc_uuid']}'");
    if(!$res)
        add_error('Location update failed');
    else
        add_confirmation('Location updated');
}
/**
 * @name    Commits loouk up value of parent location
 * @access public
 * @return void
 */
function shn_bsm_edit_commit_lukup($location_uuid=null,$location_parent_uuid=null, $attr_name=null){
    global $global;
    global $conf;

    if ($location_parent_uuid==null || $location_uuid==null){add_error(_("Your selection is invalid"));}
    else{
        $update_array['loc_prnt_uuid'] = $location_parent_uuid;
        shn_db_update($update_array,'bsm_location',' WHERE loc_uuid = '.$location_uuid);

    }
}
?>
