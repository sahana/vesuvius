<?php

/* $Id: main_fns.inc,v 1.20 2008-01-03 04:41:59 isurunishan Exp $ */

/**
* Functions page of the GIS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package module
* @subpackage gis
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/



function shn_gis_default()
{
        global $conf;
?>
<div id="home">
<h2><?php echo _('Situation Mapping')?></h2>
<p>
<?= _("The Situation Mapping module provides a mechanism to collaboratively provide an overview of the developing disaster, using online mapping (GIS). You can add markers and pictures to pin point incidents on the map.");?>
        
</p>

<br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
<br></br>
<ul>
        <li><?php echo _('Provides a map based view of the disaster situtation') ?></li>
        <li><?php echo _('Allows users to collaboratively add markers of the developing disaster sitation');?></li>
</ul>

<strong><?php echo _('Description of Actions:')?></strong><br/>
    <ul>
        <li><a href="index.php?mod=gis&act=swik"><b><?= _('View Situation Map'); ?></b></a><br/><?= _('Map of the developing situation with markers of incidentss, locations and objects displayed on the map'); ?></li>
        <li><a href="index.php?mod=gis&act=awik"><b><?= _('Add Situation Markers'); ?> </b> </a><br/><?= _('Add markers on the map of incidents and objects with pictures'); ?></li>
        <li><a href="index.php?mod=gis&act=mapc"><b><?= _('General Map'); ?> </b></a><br/><?= _('Free form map of the location without markers'); ?></li>
        
        
</ul>
<br/>

</div>
<?php
}

//not being used any more
//replaced by sha_gis_mapc()
function shn_gis_show()
{
  //echo "showing";
  global $global;
  include_once $global['approot']."/mod/gis/gis_fns.inc";
  
  $options=array();
  if((isset($_POST['mapa_x'])) && isset($_POST['mapa_y'])){
  	//echo $_POST['mapa_x'];
  }
  //var_dump($_POST);
  shn_gis_map();
}

						



function shn_gis_aloc ($errors=false)
{
	global $global;
	include_once($global['approot'].'/inc/lib_form.inc');
	include_once($global['approot'].'/inc/lib_validate.inc');
	include_once($global['approot'].'/inc/lib_errors.inc');
	include $global['approot'].'/inc/lib_location.inc';
	if($errors)
		display_errors();
		
	shn_form_fopen(amap);
	shn_form_fsopen(_("Landmark Specific Details"));
	shn_form_text(_("Landmark Name"),"location_name",'size="60"');
	shn_form_opt_select("opt_landmark_type",_("Landmark Type"));
	shn_form_fsclose();
	shn_form_fsopen(_('Landmark\'s Location'));
	$range = shn_get_range();
	shn_location($range);
	shn_form_fsclose();

	shn_form_fsopen(_('Main Contact Details'));
	shn_form_text(_("Contact Person  Name"),"person_name",'size="60"');
	shn_form_opt_select("opt_landmark_contact_type",_("Contact Type"));
	shn_form_text(_("Contact Person  Address"),"person_address",'size="60"');
	shn_form_text(_("Contact Person  Phone"),"person_phone",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen(_('Other Details'));
	shn_form_textarea(_("Directions to Landmark"),"direction",'size="60"');
	shn_form_textarea(_("Significance of  Landmark"),"comment",'size="60"');
	shn_form_fsclose();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

function shn_gis_amap()
{
	global $global;
	include_once($global['approot'].'/inc/lib_form.inc');
	include $global['approot'].'/inc/lib_location.inc';
	$location_val = shn_get_range();
	$location = $location_val['end'];
	$_SESSION['location_name'] = $_POST['location_name'];
	$_SESSION['opt_landmark_type'] = $_POST['opt_landmark_type'];
	$_SESSION['person_name'] = $_POST['person_name'];
	$_SESSION['opt_landmark_contact_type'] = $_POST['opt_landmark_contact_type'];
	$_SESSION['person_address'] = $_POST['person_address'];
	$_SESSION['person_phone'] = $_POST['person_phone'];
	$_SESSION['direction'] = $_POST['direction'];
	$_SESSION['comment'] = $_POST['comment'];
	$_SESSION[$location] = $_POST[$location];

	shn_form_fopen(com);
	shn_form_fsopen(_("Location Information"));
	echo _("Plot the Location OR Enter its GPS coordinates ");
	shn_form_fsclose();
	shn_form_hidden(array('loc_x'=>''));
	shn_form_hidden(array('loc_y'=>''));
	global $global;
	$db=$global['db'];
	global $conf;
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_add_marker_map_form("Area Map",$_POST['location_name']);
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

function shn_gis_com ()
{
	global $global;
	global $conf;
	$db = $global['db'];
	include_once($global['approot'].'/inc/lib_location.inc');
	include_once ($global['approot'].'/mod/gis/gis_fns.inc');
	$db = $global['db'];
	if((null==$_POST['gps_x']) && null==$_POST['gps_y']){
			$_SESSION['gis_loc_x']=$_POST['loc_x'];
			$_SESSION['gis_loc_y']=$_POST['loc_y'];
		}
		else{
			$_POST['loc_x'] = $_POST['gps_x'];
			$_POST['loc_y'] = $_POST['gps_y'];
			$_SESSION['gis_loc_x']=$_POST['loc_x'];
			$_SESSION['gis_loc_y']=$_POST['loc_y'];
		}
	$location_val = shn_get_range();
	$location = $location_val['end'];
	include_once($global['approot'].'/inc/lib_uuid.inc');
	$landmark_id = shn_create_uuid('l');
	$gis_id = shn_create_uuid('g');
	$land_query = "insert into landmark_location (landmark_uuid,name,opt_landmark_type,description,comments,gis_uid) values ('{$landmark_id}','{$_SESSION['location_name']}','{$_SESSION['opt_landmark_type']}','{$_SESSION['direction']}','{$_SESSION['comment']}','{$gis_id}') ";
	$res = $db->Execute($land_query);	
	if($conf['gis']){
		shn_gis_dbinsert(0,0,null,$_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'],null,$gis_id);
	}
?>
	<h2><?=_('Your Landmark has been succesfully added. ')?></h2>
<?php

	
}
?>
