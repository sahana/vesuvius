<?php


/**
 * All the commonly used functionalities in the  DVR are stored in this file
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera (isuru@opensource.lk)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once ($global['approot'] . '/mod/dvr/data_access.inc');
function _shn_dvr_print_header($string = null) {
	print '<h2>' . $string . '</h2>';
}

function _shn_dvr_populate_individual_detail() 
{
	$p_uuid = $_GET['p_uuid'];
	$_SESSION['dvr']['person']['p_uuid'] = $p_uuid;
	$results = get_person_major_details($p_uuid);
	$group_type = $results->fields['group_type'];
	$head_id = $results->fields['head_id'];
	$group_id = $results->fields['groupid'];
    
	$grcurr_loc = _shn_dvr_get_current_location($group_id);
    $grdis_loc = _shn_dvr_get_displaced_location($group_id);
    $_SESSION['dvr']['person']['current_loc'] = _shn_dvr_get_current_location($p_uuid);
    $_SESSION['dvr']['person']['displaced_loc'] = _shn_dvr_get_displaced_location($p_uuid);
    //var_dump('loc'.$_SESSION['dvr']['person']['current_loc'].$_SESSION['dvr']['person']['displaced_loc']);
    if($_SESSION['dvr']['person']['displaced_loc']!=$grdis_loc)
    $_SESSION['dvr']['person']['displacedlocationtypeof_group']=2;
    else
    $_SESSION['dvr']['person']['displacedlocationtypeof_group']=1;
    
    if($_SESSION['dvr']['person']['current_loc']!=$grcurr_loc)
    $_SESSION['dvr']['person']['currentlocationtypeof_group']=2;
    else
    $_SESSION['dvr']['person']['currentlocationtypeof_group']=1;
	
    $personal = get_person_full_name($p_uuid);

	$p_full_name = $personal->fields['full_name'];
	$p_family_name = $personal->fields['family_name'];
	$p_local_name = $personal->fields['l10n_name'];

	$head_details = get_person_full_name($head_id);
	$head_full_name = $head_details->fields['full_name'];

	$_SESSION['dvr']['person']['typ_of_grp'] = $group_type;
//	print 'head name is' . $_POST['head_name'];
	$_SESSION['dvr']['person']['head_name'] = $head_full_name;
	//$group=_shn_dvr_get_group_id($_POST['head_name']);

	$_SESSION['dvr']['person']['group_id'] = $group_id;
	$_SESSION['dvr']['person']['full_name'] = $p_full_name;
	$_SESSION['dvr']['person']['family_name'] = $p_family_name;
	$_SESSION['dvr']['person']['local_name'] = $p_local_name;

	$personal_results = get_personal_details($p_uuid);
	
	$dob = $personal_results->fields['birth_date'];
	$age_group = $personal_results->fields['opt_age_group'];
	$gender = $personal_results->fields['opt_gender'];
	$marital = $personal_results->fields['opt_marital_status'];
	$religion = $personal_results->fields['opt_religion'];

	$race = $personal_results->fields['opt_race'];

	$id_results = get_identity_to_person($p_uuid);

	while (!$id_results->EOF) {
		$id = $id_results->fields['serial'];
		$val = $id_results->fields['opt_id_type'];
		if ($val == 'idcard') {
			$_SESSION['dvr']['person']['idcard'] = $id;
		} else
			if ($val == 'pas') {
				$_SESSION['dvr']['person']['passport'] = $id;
			} else
				if ($val == 'dln') {
					$_SESSION['dvr']['person']['drv_licence'] = $id;
				}
		$id_results->MoveNext();
	}
	
	$physical_result = get_person_physical_details($p_uuid);
	
	$_SESSION['dvr']['person']['opt_eye_color'] = $physical_result->fields['opt_eye_color'];
	$_SESSION['dvr']['person']['opt_skin_color'] = $physical_result->fields['opt_skin_color'];
	$_SESSION['dvr']['person']['opt_hair_color'] = $physical_result->fields['opt_hair_color'];
	$_SESSION['dvr']['person']['height'] = $physical_result->fields['height'];
	$_SESSION['dvr']['person']['weight'] = $physical_result->fields['weight'];
	$_SESSION['dvr']['person']['opt_blood_type'] = $physical_result->fields['opt_blood_type'];
	//$_SESSION['dvr']['person']['last_clothing'];
	$comments = $physical_result->fields['comments'];
	$chars = preg_split('/,/', $comments);
	$_SESSION['dvr']['person']['last_clothing'] = $chars[0];
	$_SESSION['dvr']['person']['comments'] = $chars[1];
		
	$_SESSION['dvr']['person']['dob'] = $dob;
	$_SESSION['dvr']['person']['opt_age_group'] = $age_group;
	$_SESSION['dvr']['person']['opt_gender'] = $gender;
	$_SESSION['dvr']['person']['opt_marital_status'] = $marital;
	$_SESSION['dvr']['person']['opt_religion'] = $religion;
	$_SESSION['dvr']['person']['opt_race'] = $race;

	$contact_results = get_contacts($p_uuid);

	while (!$contact_results->EOF) {
		$ctct_type = $contact_results->fields['opt_contact_type'];
		$ctct_value = $contact_results->fields['contact_value'];

		if ($ctct_type == "mobile") {
			$_SESSION['dvr']['person']['mobile'] = $ctct_value;
		} else
			if ($ctct_type == "telephone") {
				$_SESSION['dvr']['person']['telephone'] = $ctct_value;
			} else
				if ($ctct_type == "address") {
					$_SESSION['dvr']['person']['address'] = $ctct_value;
				}
		$contact_results->MoveNext();

	}
	
}

function _shn_dvr_regconfirm_individuals() 
{
	global $global;
	global $conf;
	$db = $global['db'];
?>
<h2><center><?php echo  _t('Details of ') . $_SESSION['dvr']['person']['full_name'] ?></center></h2>
<div id="formcontainer">
<?php


	shn_form_fopen("edit_individual", null,false);

	shn_form_fsopen(_t('Group Type and Personal details'));

	shn_form_label(_t("Group type: "), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['typ_of_grp']));

	shn_form_label(_t("Full name"), $_SESSION['dvr']['person']['full_name']);

	shn_form_label(_t("Family name"), $_SESSION['dvr']['person']['family_name']);

	shn_form_label(_t("Local name"), $_SESSION['dvr']['person']['local_name']);

	shn_form_label(_t("Current Photograph"), $_SESSION['dvr']['person']['picture']);
?>
	<p align='center'>
	<?php
//shn_show_thumb_url($x_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null)
	shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], 'database', 'dvr', 'addvictim_img', false);
	
?>
	
	</p>
	<?php


	shn_form_label(_t("Date Of birth"), $_SESSION['dvr']['person']['dob']);

	shn_form_label(_t("Age group"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_age_group']));

	shn_form_label(_t("Gender"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_gender']));

	shn_form_label(_t("Marital Status"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_marital_status']));

	shn_form_label(_t("Religion"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_religion']));

	shn_form_label(_t("Race"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_race']));

	shn_form_fsclose();

	shn_form_fsopen(_t("Identity"));
	shn_form_label(_t("Identity Card Number"), $_SESSION['dvr']['person']['idcard']);
	shn_form_label(_t("Passport Number"), $_SESSION['dvr']['person']['passport']);
	shn_form_label(_t("Driving License"), $_SESSION['dvr']['person']['drv_licence']);

	shn_form_fsclose();

	shn_form_fsopen(_t("Contact Information"));
	shn_form_label(_t("Address"), $_SESSION['dvr']['person']['address']);
	//shn_form_label(_t("Postal Code"), $_SESSION['dvr']['person']['postal_code']);
	shn_form_label(_t("Home Phone"), $_SESSION['dvr']['person']['telephone']);
	shn_form_label(_t("Mobile"), $_SESSION['dvr']['person']['mobile']);
	shn_form_fsclose();

	shn_form_fsopen(_t("Displaced/Current Location"));
	$location = shn_location_string($_SESSION['dvr']['person']['displaced_loc']);

	shn_form_label(_t("Displaced Location"), $location);
	
	$location = shn_location_string($_SESSION['dvr']['person']['current_loc']);
	$map_location = "Latitude= " . $_SESSION['dvr']['person']['gis_loc_y'] . " Longitude= " . $_SESSION['dvr']['person']['gis_loc_x'];
	shn_form_label(_t("Current Location"), $location);
	//shn_form_label(_t("Map Location"), $map_location);
	shn_form_fsclose();

	// Contact infomation
	shn_form_fsopen(_t("Physical Information"));

	shn_form_label(_t("Current Fingerprint"), $_SESSION['dvr']['person']['finger_picture']);
?>
	<p align='center'>
	<?php
//shn_show_thumb_url($x_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null)
	shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'], 'database', 'dvr', 'addfingerprint_img', false, "finger");
?>
	
	</p>
	<?php


	shn_form_label(_t("Eye Color"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_eye_color'],'opt_eye_color'));
	shn_form_label(_t("Skin Color"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_skin_color'],'opt_skin_color'));
	shn_form_label(_t("Hair Color"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_hair_color'],'opt_hair_color'));
	shn_form_label(_t("Height"), $_SESSION['dvr']['person']['height']);
	shn_form_label(_t("Weight"), $_SESSION['dvr']['person']['weight']);
	shn_form_label(_t("Blood Type"), _shn_dvr_getoptiondescription($_SESSION['dvr']['person']['opt_blood_type']));
	shn_form_label(_t("Clothing and appearance"), $_SESSION['dvr']['person']['last_clothing']);
	shn_form_label(_t("Other Details"), $_SESSION['dvr']['person']['comments']);

	shn_form_fsclose();
?>
<br />
<center>
<?php


	//create the submit button
	$extra_opts['br'] = false;

	
	shn_form_hidden(array (
		'action' => '0'
	));
	// _shn_dvr_action_change_javascript("confirm_reg","action");
?>
</center>
<br />
<?php


	//close the form
	shn_form_fclose();
?>				     
</div>
<?php


}


function _shn_dvr_getchecklist()
{
	global $global;
	global $conf;
	$db = $global['db'];
	$loc = array ();
	$q = "SELECT option_description FROM field_options WHERE field_name='opt_dvr_service'";
	$res = $db->Execute($q);
	$i=0;
	while(!$res->EOF)
	{
	$elements[$i]=$res->fields['option_description'];
	$i++;
	$res->MoveNext();
	}
	//bad
	$_SESSION['elementcount']=$i;
	return $elements;
}


function _shn_dvr_getoptiondescription($opt_code,$field_name=null)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$loc = array ();
	if(isset($field_name))
	$q = "SELECT distinct option_description FROM field_options WHERE option_code='$opt_code' AND field_name='$field_name'";
	else
	$q = "SELECT distinct option_description FROM field_options WHERE option_code='$opt_code'";
	$res = $db->Execute($q);
	$desc=$res->fields['option_description'];
	return $desc;
}


function _shn_dvr_getgroupheadspertype($grp_type=null)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$head_names= array ();
	$i=0;
	if(isset($grp_type)){
	$q = "SELECT p.full_name,pg.g_uuid AS groupid FROM person_uuid p,pgroup pg,group_details gd WHERE p.p_uuid=gd.head_uuid AND pg.g_uuid=gd.g_uuid AND pg.opt_group_type='{$grp_type}'";
	}else{
	$q = "SELECT p.full_name,pg.g_uuid AS groupid FROM person_uuid p,pgroup pg,group_details gd WHERE p.p_uuid=gd.head_uuid AND pg.g_uuid=gd.g_uuid";
	}
	$res = $db->Execute($q);
	
	while(!$res->EOF)
	{
	$head_names[$res->fields['groupid']]=$res->fields['full_name'];
	$res->MoveNext();
	}
	return $head_names;
}

function _shn_dvr_getgrouptype($g_uuid)
{
	global $global;
	$db = $global['db'];
	$sql="SELECT opt_group_type FROM pgroup WHERE g_uuid = '$g_uuid'";
    $res = $db->Execute($sql);
    $grouptype=$res->fields['opt_group_type'];
    
    return $grouptype;
}

function _shn_dvr_get_group_id($head_name)
{
	
    global $global;

	$db = $global['db'];
	$sql="SELECT pg.g_uuid AS group FROM pgroup pg,person_uuid pu WHERE pg.head_uuid=pu.p_uuid AND pu.full_name='{$head_name}' ";
    $res = $db->Execute($sql);
    $group=$res->fields['group'];
    return $group;
}

function _shn_dvr_get_person_full_name($person_uuid)
{	
    global $global;

    $db = $global['db'];
    $sql="SELECT full_name FROM person_uuid WHERE p_uuid ='{$person_uuid}'";
$res = $db->Execute($sql);
$group=$res->fields['full_name'];
return $group;
	
}

function _shn_dvr_get_groupdisplaced_location($poc_uuid)
{
	global $global;

    $db = $global['db'];
    $sql="SELECT location_id FROM location_details WHERE poc_uuid ='{$poc_uuid}-disp'";
    $res = $db->Execute($sql);
    $loc=$res->fields['location_id'];
    return $loc;
}

function _shn_dvr_get_displaced_location($poc_uuid)
{
	global $global;

    $db = $global['db'];
    $sql="SELECT location_id FROM location_details WHERE poc_uuid ='{$poc_uuid}-disp'";
    $res = $db->Execute($sql);
    $loc=$res->fields['location_id'];
    return $loc;
}

function _shn_dvr_get_groupcurrent_location($poc_uuid)
{
	global $global;

    $db = $global['db'];
    $sql="SELECT location_id FROM location_details WHERE poc_uuid ='{$poc_uuid}-curr'";
    $res = $db->Execute($sql);
    $loc=$res->fields['location_id'];
    return $loc;
}

function _shn_dvr_get_current_location($poc_uuid)
{
	global $global;

    $db = $global['db'];
    $sql="SELECT location_id FROM location_details WHERE poc_uuid ='{$poc_uuid}-curr'";
    $res = $db->Execute($sql);
    $loc=$res->fields['location_id'];
    return $loc;
}


function _shn_dvr_get_groupcurrent_shelter($groupid)
{
	global $global;

    $db = $global['db'];
    $sql="SELECT full_name FROM person_uuid WHERE p_uuid ='{$person_uuid}'";
    $res = $db->Execute($sql);
    $group=$res->fields['full_name'];
    return $group;
}




function _shn_dvr_get_image_id($groupid,$category)
{
	global $global;

    $db = $global['db'];
    //$sql="SELECT i.image_id AS imid FROM image i,pgroup p WHERE p.head_uuid=i.x_uuid AND p.g_uuid ='{$groupid} AND p.category='{$category}'";
    $sql = "SELECT image_id FROM image WHERE x_uuid ='$groupid' AND category='$category'";
    $res = $db->Execute($sql);
    $imageid=$res->fields['image_id'];
    return $imageid;
}



function _shn_libdvr_search_show_verticle($details)
{
    global $global;
    global $conf;
?>
<DIV ID="result">
<TABLE>
<?php
    for($i=0; $i<count($details); $i+=2){
        if($details[$i]){
?>
    <TR>
        <TD>
<?php
	        if(shn_show_thumb_url($details[$i]['p_uuid'],$conf['mod_mpr_upload_picture_savehandler'],'mpr','addmp_img'))
	            echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	        else{
	            echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	            echo ($details[$i]['height']?_t('Height : ').$details[$i]['height'].'<br>':'');
	            echo ($details[$i]['weight']?_t('Weight : ').$details[$i]['weight'].'<br>':'');
	            echo ($details[$i]['opt_eye_color']?_t('Eye Colour : ').shn_get_field_opt($details[$i]['opt_eye_color'],'opt_eye_color').'<br>':'');
	            echo ($details[$i]['opt_skin_color']?_t('Skin Colour : ').shn_get_field_opt($details[$i]['opt_skin_color'],'opt_skin_color').'<br>':'');
	            echo ($details[$i]['opt_hair_color']?_t('Hair Colour : ').shn_get_field_opt($details[$i]['opt_hair_color'],'opt_hair_color').'<br>':'');
	            echo ($details[$i]['last_seen']?_t('Last Seen : ').$details[$i]['last_seen'].'<br>':'');
	            echo ($details[$i]['last_clothing']?_t('Last Clothing : ').$details[$i]['last_clothing'].'<br>':'');
	            echo ($details[$i]['comments']?_t('Comments : ').$details[$i]['comments']:'');
	        } 
            echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'" class="hideprint">'._t('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
                if(shn_show_thumb_url($details[$i+1]['p_uuid'],$conf['mod_mpr_upload_picture_savehandler'],'mpr','addmp_img'))
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		        else{
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		            echo ($details[$i+1]['height']?_t('Height : ').$details[$i+1]['height'].'<br>':'');
		            echo ($details[$i+1]['weight']?_t('Weight : ').$details[$i+1]['weight'].'<br>':'');
	                echo ($details[$i+1]['opt_eye_color']?_t('Eye Colour : ').shn_get_field_opt($details[$i+1]['opt_eye_color'],'opt_eye_color').'<br>':'');
	                echo ($details[$i+1]['opt_skin_color']?_t('Skin Colour : ').shn_get_field_opt($details[$i+1]['opt_skin_color'],'opt_skin_color').'<br>':'');
	                echo ($details[$i+1]['opt_hair_color']?_t('Hair Colour : ').shn_get_field_opt($details[$i+1]['opt_hair_color'],'opt_hair_color').'<br>':'');
	                echo ($details[$i+1]['last_seen']?_t('Last Seen : ').$details[$i+1]['last_seen'].'<br>':'');
	                echo ($details[$i+1]['last_clothing']?_t('Last Clothing : ').$details[$i+1]['last_clothing'].'<br>':'');
	                echo ($details[$i+1]['comments']?_t('Comments : ').$details[$i+1]['comments']:'');
		        } 
                echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'" class="hideprint">'._t('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            }
?>
    </TR>
<?php
        }
    }
?>
</TABLE>
</DIV>
<?php
}





function shn_dvr_get_loc_range() {
	global $global;
	global $conf;
	$db = $global['db'];
	$loc = array ();
	$q = "SELECT value FROM config WHERE module_id='dvr' AND confkey='loc_range_start'";
	$res = $db->Execute($q);
	if ($res->fields[0] == NULL) {
		$loc["start"] = $conf['mod_dvr_loc_level_start'];
	} else {
		$loc["start"] = $res->fields[0];
	}
	$q = "SELECT value FROM config WHERE module_id='dvr' AND confkey='loc_range_end'";
	$res = $db->Execute($q);
	if ($res->fields[0] == NULL) {
		$loc["end"] = $conf['mod_dvr_loc_level_end'];
	}
	else {
		$loc["end"] = $res->fields[0];
	}
	
	return $loc;
}

function _shn_dvr_get_start_loc() {
	global $global;
	global $conf;
	$db = $global['db'];
	$q = "SELECT value FROM config WHERE module_id='dvr' AND confkey='loc_start'";
	$res = $db->Execute($q);
	
	if($res->fields["value"] == NULL){
		$loc_start = $conf['mod_dvr_loc_start'];
	}
	else {
		$loc_start = $res->fields["value"];
	}
		
	return $loc_start;
}

