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
 * @TODO       At some point this locations object or entity should be blended with the
 * original concept of locations used in MPR, GIS, VR etc based on a common acceptable standard set
 * of onthologies and taxinmoies
 */

/**
 * This function cleans the POST values
 * @name clean post
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
/**@name Add Entry Form
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
	$_SESSION['bsm']['add']['case_uuid'] = $_REQUEST['rtnid'];
	//print $_SESSION['bsm']['add']['case_uuid'];
    shn_form_fopen("add&entity=location",null,null);
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Complete the location details and save.'));
    shn_form_text(_('Name'),'name','size="30"',array('help' => _('Enter full or part of the location name.'), 'req'=>true));

    include('loc_type.inc');

    echo '<p align="center">'."Parent Location : ".'<a align="center" title="'._('add').
            '" href="index.php?mod='.$global['module'].'&act=search&entity=location&seq=lukup&flag=add&id=">Click to Add</a></p><br>';

    shn_form_text(_('Description'),'description','size="30"',array('help' => _('Type in the location ISO code.'), 'req'=>false));
	/*global $global;
	$sql = "SELECT * FROM field_options WHERE field_name = 'location_shape'";
	$res = $global['db']->Execute($sql);
	$loc_shape = array();
	while(!$res == NULL && !$res->EOF)
	{
		$loc_shape[$res->fields['option_code']] = $res->fields['option_description'];
		$res->MoveNext();
	}*/
	//var_dump($loc_shape);
    //shn_form_select($loc_shape, _('Shape'), 'opt_shape', 'size="1"', array('help' => _('Select a location shape.'), 'req'=>false));
	shn_form_opt_select('opt_shape', _('Shape'), null, $extra_opts = null);
    
    shn_form_text(_('X Vector'),'x_vector','size="30"',array('help' => _('Type in the vector seperate each element by a comma e.g. 100.6, 101.2, 102.5.'), 'req'=>false));
    shn_form_text(_('Y Vector'),'y_vector','size="30"',array('help' => _('Type in the vector seperate each element by a comma e.g. 0.6, 1.2, 2.5.'), 'req'=>false));
    shn_form_text(_('Z Vector'),'z_vector','size="30"',array('help' => _('Type in the vector seperate each element by a comma e.g. 10.6, 11.2, 12.5.'), 'req'=>false));
    shn_form_text(_('ISO Code'),'iso_code','size="30"',array('help' => _('Type in the location ISO code.'), 'req'=>false));

    $parent_id = $_REQUEST['lukupid'];
   // print $parent_id;
    shn_form_hidden(array('parent_id'=>$parent_id, 'case_uuid'=>$_SESSION['bsm']['add']['case_uuid']));
    shn_form_submit(_('Save'));
    shn_form_fsclose();
    shn_form_fclose();

 }
/**
 * @name Add Entry Validation
 * @access public
 * @return void
 */
function shn_bsm_add_validate()
{
	global $global;
	global $conf;
	//print $_POST['parent_id'];
	$error_flag=false;

	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

	//$local_post['location_uuid'] = $_SESSION['bsm']['add']['location_uuid'];
	//clean
	$_SESSION['bsm']['add']=null;
	$_SESSION['bsm']['add']=$local_post;

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

	if($error_flag)	{return false;}
        else {
            //ensure similar record with name, category, & type does not exisits
            $sql = "SELECT 1 FROM bsm_location WHERE deactivate_dt IS NULL AND loc_name = '".$local_post['name']."' ";
           // $sql .= " AND loc_cate = '".$local_post['category']."' AND loc_type = '".$local_post['type']."'";
            $sql .= " AND loc_type = '".$local_post['loc_type']."'";
            $rsql = $global['db']->Execute($sql);
//var_dump($rsql);
// $rsql->RecordCount();
/*$sql = "select * from ct_catalogue";
global $global;
$db = $global['db'];
$res = $db->Execute($sql);
//var_dump($res);
echo $res->fields['name'];*/
            if($rsql == true && $rsql->RecordCount() > 0){
                add_error(_('Recod with location name = ').$local_post['name']._(', category = ').$local_post['category'].
                    _(', and type = ').$local_post['loc_type']._(" existis. Search again to avoid duplication."));
                return false;
            }
            else {return true;}
        }
}
/*
 * @name confirm location value to add
 * @access public
 * @return void
 */
function shn_bsm_add_confirm(){

    global $global;
    global $conf;
//print ('hello');

    $_SESSION['bsm']['add']['parent_id'] = trim($_POST['parent_id']);
    $_SESSION['bsm']['add']['name'] = isset($_POST['name']) ? trim($_POST['name']) : null;
    $_SESSION['bsm']['add']['loc_cate'] = isset($_POST['loc_cate']) ? trim($_POST['loc_cate']) : null;
    $_SESSION['bsm']['add']['loc_type'] = isset($_POST['loc_type']) ? trim($_POST['loc_type']) : null;
    $_SESSION['bsm']['add']['description'] = isset($_POST['description']) ? trim($_POST['description']) : null;
    $_SESSION['bsm']['add']['parent_uuid'] = isset($_POST['parent_uuid']) ? trim($_POST['parent_uuid']) : null;
    $_SESSION['bsm']['add']['shape'] = isset($_POST['shape']) ? trim($_POST['shape']) : null;
    $_SESSION['bsm']['add']['x_vector'] = isset($_POST['x_vector']) ? trim($_POST['x_vector']) : null;
    $_SESSION['bsm']['add']['y_vector'] = isset($_POST['y_vector']) ? trim($_POST['y_vector']) : null;
    $_SESSION['bsm']['add']['z_vector'] = isset($_POST['z_vector']) ? trim($_POST['z_vector']) : null;
    $_SESSION['bsm']['add']['iso_code'] = isset($_POST['iso_code']) ? trim($_POST['iso_code']) : null;
    $_SESSION['bsm']['add']['create_datetime'] = date('Y-m-d H:i:s');
    $_SESSION['bsm']['add']['create_user'] = "user";
    $_SESSION['bsm']['add']['create_process'] = $conf['host'];

    shn_form_hidden(array('seq'=>'commit'));
}
/**
 * @name commit location to database.
 * @access public
 * @return void
 * @TODO inlude lib_uuid to insert sahana generated uuid's opposed to autoincrement interegers
 */
function shn_bsm_add_commit(){
    
    global $global;
    global $conf;

    include_once($global['approot']."/inc/lib_uuid.inc");
    $loc_uuid = shn_create_uuid('loc');
    
    $case_uuid = $_POST['case_uuid'];
    //print $loc_uuid;
    $insert_array = null;
    $insert_array['loc_uuid'] = $loc_uuid;

	if(isset($_SESSION['bsm']['add']['parent_id']) && !empty($_SESSION['bsm']['add']['parent_id']))
        {$insert_array['loc_prnt_uuid'] = $_SESSION['bsm']['add']['parent_id'];}
    if(isset($_SESSION['bsm']['add']['name']) && !empty($_SESSION['bsm']['add']['name']))
        {$insert_array['loc_name'] = $_SESSION['bsm']['add']['name'];}
//    if(isset($_SESSION['bsm']['add']['category'])){$insert_array['loc_cate'] = $_SESSION['bsm']['add']['category'];}
    if(isset($_SESSION['bsm']['add']['loc_type'])){$insert_array['loc_type'] = $_SESSION['bsm']['add']['loc_type'];}
    if(isset($_SESSION['bsm']['add']['parent_uuid']) && !empty($_SESSION['bsm']['add']['parent_uuid']))
        {$insert_array['loc_prnt_id'] = $_SESSION['bsm']['add']['parent_uuid'];}
    if(isset($_SESSION['bsm']['add']['description']) && !empty($_SESSION['bsm']['add']['description']))
        {$insert_array['loc_desc'] = $_SESSION['bsm']['add']['description'];}
    if(isset($_SESSION['bsm']['add']['shape'])){$insert_array['loc_shape'] = $_SESSION['bsm']['add']['shape'];}
    if(isset($_SESSION['bsm']['add']['x_vector']) && !empty($_SESSION['bsm']['add']['x_vector']))
        {$insert_array['loc_x_vect'] = $_SESSION['bsm']['add']['x_vector'];}
    if(isset($_SESSION['bsm']['add']['y_vector']) && !empty($_SESSION['bsm']['add']['y_vector']))
        {$insert_array['loc_y_vect'] = $_SESSION['bsm']['add']['y_vector'];}
    if(isset($_SESSION['bsm']['add']['z_vector']) && !empty($_SESSION['bsm']['add']['z_vector']))
        {$insert_array['loc_z_vect'] = $_SESSION['bsm']['add']['z_vector'];}
    if(isset($_SESSION['bsm']['add']['iso_code']) && !empty($_SESSION['bsm']['add']['iso_code']))
        {$insert_array['loc_iso_code'] = $_SESSION['bsm']['add']['iso_code'];}
 //   if(isset($_SESSION['bsm']['add']['create_datetime'])){$insert_array['create_dt'] = $_SESSION['bsm']['add']['create_datetime'];}
 //   if(isset($_SESSION['bsm']['add']['create_user'])){$insert_array['create_by'] = $_SESSION['bsm']['add']['create_user'];}
 //   if(isset($_SESSION['bsm']['add']['create_process'])){$insert_array['create_proc'] = $_SESSION['bsm']['add']['create_process'];}

    //shn_db_insert($insert_array,'bsm_location',true, null);
//var_dump($insert_array);
    global $global;
    $db = $global['db'];
	
		//$insert_array_cat = array();
		//$insert_array_cat['loc_cate'] = 

		/*$insert_array = array();
		$insert_array['loc_uuid'] = $loc_uuid;
		$insert_array['loc_prnt_uuid'] =  $_SESSION['bsm']['add']['parent_uuid'];
		$insert_array['loc_name'] = $_SESSION['bsm']['add']['name'];
		$insert_array['loc_type'] = $_SESSION['bsm']['add']['type'];
		$insert_array['loc_desc'] = $_SESSION['bsm']['add']['description'];
		$insert_array['loc_iso_code'] = $_SESSION['bsm']['add']['iso_code'];
		$insert_array['create_dt'] = $_SESSION['bsm']['add']['create_datetime'];
		$insert_array['create_by'] = $_SESSION['bsm']['add']['create_user'];
		$insert_array['create_proc'] = $_SESSION['bsm']['add']['create_process'];*/
		//var_dump($insert_array);
		$res = $db->AutoExecute('bsm_location', $insert_array, 'INSERT');
		
		if($case_uuid!=NULL || $case_uuid!='')
		{
			$sql = "UPDATE bsm_cases SET loc_uuid='{$loc_uuid}', loc_name='{$insert_array['loc_name']}' WHERE case_uuid='$case_uuid'";
			$res1 = $db->Execute($sql);
		}
		//print $sql;
    //print $insert_array['loc_uuid'];
//    $sql = "INSERT INTO bsm_location (loc_uuid, loc_prnt_uuid, loc_name, loc_type, loc_desc, loc_iso_code, create_dt, create_by, create_proc ) VALUES('{$loc_uuid}', '{$_SESSION['bsm']['add']['parent_uuid']}', '{$_SESSION['bsm']['add']['name']}',  '{$_SESSION['bsm']['add']['type']}', '{$_SESSION['bsm']['add']['description']}', '{$_SESSION['bsm']['add']['iso_code']}', '{$_SESSION['bsm']['add']['create_datetime']}', '{$_SESSION['bsm']['add']['create_user']}', '{$_SESSION['bsm']['add']['create_process']}');";
    //print $sql;
 //   $res = $db->Execute($sql);
    
    
    global $conf;
    if ($conf['gis']) {
        require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
        $class = 'bsm_location';
        $coords = shn_gis_coord_encode(array(array($_SESSION['bsm']['add']['x_vector'],$_SESSION['bsm']['add']['y_vector'],$_SESSION['bsm']['add']['z_vector'])), 'point');
        $keys = array(  
            'f_class'         => $class,
            'f_type'          => 'point',
            'f_coords'        => $coords,
            'f_module_item'   => $uid,
            'f_name'          => $_SESSION['bsm']['add']['name'],
            'f_url'           => ('mod=bsm'),
            'f_address'       => $_SESSION['bsm']['add']['loc_type']
        );
        shn_gis_create_feature($keys);
    }
    
    if($res)
        add_confirmation($_SESSION['bsm']['add']['name']._t(" Added Successfully"));
    else{
        add_error(_('Error while saving location.'));
    }
    //shn_bsm_add();
//print_r($insert_array);
}
/**
 * This is a buch of javascript helps for the collapse and expanind of a
 * given division.
 * @todo Move to somewhere make it work
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
