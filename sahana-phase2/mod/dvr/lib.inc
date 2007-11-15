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

function _shn_dvr_print_header($string = null) {
	print '<h2>' . $string . '</h2>';
}




function _shn_dvr_getchecklist()
{
	global $global;
	global $conf;
	$db = $global['db'];
	$loc = array ();
	$q = "select option_description from field_options where field_name='opt_dvr_service'";
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


function _shn_dvr_getoptiondescription($opt_code)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$loc = array ();
	$q = "select distinct option_description from field_options where option_code='$opt_code'";
	$res = $db->Execute($q);
	$desc=$res->fields['option_description'];
	return $desc;
}


function _shn_dvr_getgroupheadspertype($grp_type)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$head_names= array ();
	$i=0;
	$q = "select p.full_name,pg.g_uuid as groupid from person_uuid p,pgroup pg,group_details gd where p.p_uuid=gd.head_uuid and pg.g_uuid=gd.g_uuid and pg.opt_group_type='{$grp_type}'";
	$res = $db->Execute($q);
	while(!$res->EOF)
	{
	$head_names[$res->fields['groupid']]=$res->fields['full_name'];
	$res->MoveNext();
	}
	return $head_names;
}

function _shn_dvr_get_group_id($head_name)
{
	
global $global;

	$db = $global['db'];
	$sql="select pg.g_uuid as group from pgroup pg,person_uuid pu where pg.head_uuid=pu.p_uuid and pu.full_name='{$head_name}' ";
$res = $db->Execute($sql);
$group=$res->fields['group'];
return $group;
}

function _shn_dvr_get_person_full_name($person_uuid)
{
	
		
global $global;

$db = $global['db'];
$sql="select full_name from person_uuid where p_uuid ='{$person_uuid}'";
$res = $db->Execute($sql);
$group=$res->fields['full_name'];
return $group;
	
}

function _shn_dvr_get_groupdisplaced_location($groupid)
{
	global $global;

$db = $global['db'];
$sql="select location_id from location_details where poc_uuid ='{$groupid}-disp'";
$res = $db->Execute($sql);
$loc=$res->fields['location_id'];
return $loc;
}

function _shn_dvr_get_groupcurrent_location($groupid)
{
	global $global;

$db = $global['db'];
$sql="SELECT location_id FROM location_details WHERE poc_uuid ='{$groupid}-curr'";
$res = $db->Execute($sql);
$loc=$res->fields['location_id'];
return $loc;
}


function _shn_dvr_get_groupcurrent_shelter($groupid)
{
	global $global;

$db = $global['db'];
$sql="select full_name from person_uuid where p_uuid ='{$person_uuid}'";
$res = $db->Execute($sql);
$group=$res->fields['full_name'];
return $group;
}




function _shn_dvr_get_image_id($groupid,$category)
{
	global $global;

$db = $global['db'];
$sql="select i.image_id as imid from image i,pgroup p where p.head_uuid=i.x_uuid and p.g_uuid ='{$groupid} and p.category='{$category}'";
$res = $db->Execute($sql);
$imageid=$res->fields['imid'];
return $imageid;
}



function _shn_dvr_search_show_verticle($details)
{
    global $global;
    global $conf;
?>
<DIV ID="result">
<TABLE>
<?
    for($i=0; $i<count($details); $i+=2){
        if($details[$i]){
?>
    <TR>
        <TD>
<?php
	        if(shn_show_thumb_url($details[$i]['p_uuid'],$conf['mod_mpr']['upload_picture']['savehandler'],'mpr','addmp_img'))
	            echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	        else{
	            echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	            echo ($details[$i]['height']?_('Height : ').$details[$i]['height'].'<br>':'');
	            echo ($details[$i]['weight']?_('Weight : ').$details[$i]['weight'].'<br>':'');
	            echo ($details[$i]['opt_eye_color']?_('Eye Colour : ').shn_get_field_opt($details[$i]['opt_eye_color'],'opt_eye_color').'<br>':'');
	            echo ($details[$i]['opt_skin_color']?_('Skin Colour : ').shn_get_field_opt($details[$i]['opt_skin_color'],'opt_skin_color').'<br>':'');
	            echo ($details[$i]['opt_hair_color']?_('Hair Colour : ').shn_get_field_opt($details[$i]['opt_hair_color'],'opt_hair_color').'<br>':'');
	            echo ($details[$i]['last_seen']?_('Last Seen : ').$details[$i]['last_seen'].'<br>':'');
	            echo ($details[$i]['last_clothing']?_('Last Clothing : ').$details[$i]['last_clothing'].'<br>':'');
	            echo ($details[$i]['comments']?_('Comments : ').$details[$i]['comments']:'');
	        } 
            echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'" class="hideprint">'._('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
                if(shn_show_thumb_url($details[$i+1]['p_uuid'],$conf['mod_mpr']['upload_picture']['savehandler'],'mpr','addmp_img'))
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		        else{
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		            echo ($details[$i+1]['height']?_('Height : ').$details[$i+1]['height'].'<br>':'');
		            echo ($details[$i+1]['weight']?_('Weight : ').$details[$i+1]['weight'].'<br>':'');
	                echo ($details[$i+1]['opt_eye_color']?_('Eye Colour : ').shn_get_field_opt($details[$i+1]['opt_eye_color'],'opt_eye_color').'<br>':'');
	                echo ($details[$i+1]['opt_skin_color']?_('Skin Colour : ').shn_get_field_opt($details[$i+1]['opt_skin_color'],'opt_skin_color').'<br>':'');
	                echo ($details[$i+1]['opt_hair_color']?_('Hair Colour : ').shn_get_field_opt($details[$i+1]['opt_hair_color'],'opt_hair_color').'<br>':'');
	                echo ($details[$i+1]['last_seen']?_('Last Seen : ').$details[$i+1]['last_seen'].'<br>':'');
	                echo ($details[$i+1]['last_clothing']?_('Last Clothing : ').$details[$i+1]['last_clothing'].'<br>':'');
	                echo ($details[$i+1]['comments']?_('Comments : ').$details[$i+1]['comments']:'');
		        } 
                echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'" class="hideprint">'._('Assign to more incidents').'</a>';
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
	$q = "select value from config where module_id='or' and confkey='loc_range_start'";
	$res = $db->Execute($q);
	if ($res->fields[0] == NULL) {
		$loc["start"] = $conf['mod_or_loc_level_start'];
	} else {
		$loc["start"] = $res->fields[0];
	}
	$q = "select value from config where module_id='dvr' and confkey='loc_range_end'";
	$res = $db->Execute($q);
	if ($res->fields[0] == NULL) {
		$loc["end"] = $conf['mod_or_loc_level_end'];
	} else {
		$loc["end"] = $res->fields[0];
	}
	return $loc;
}

function _shn_dvr_get_start_loc() {
	global $global;
	global $conf;
	$db = $global['db'];
	$q = "select value from config where module_id='dvr' and confkey='loc_start'";
	$res = $db->Execute($q);
	//   if($res->fields[0]==NULL){
	//    	return $conf['mod_or_start_loc'];
	//}else {
	if ($res == NULL) {
		return NULL;
	} else {
		return $res->fields["value"];
	}
}
?>
