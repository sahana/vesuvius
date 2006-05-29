<?php

function shn_lr_default()
{
?>
<div id="home">
<h2><?php echo _("Landmark Location  Registry");?></h2>
<ul>
	<li><?php echo _('The Landmark Location Registry helps you keep track of landmarks');?></li>
</ul>
</div>
<?php
}

function shn_lr_aloc ($errors=false)
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
	shn_form_fsopen('Landmark\'s Location');
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

function shn_lr_amap()
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
	shn_form_fsopen(_("Plot Location on Map"));
	shn_form_hidden(array('loc_x'=>''));
	shn_form_hidden(array('loc_y'=>''));
	global $global;
	$db=$global['db'];
	global $conf;
	include $global['approot']."/mod/gis/gis_fns.inc";
	
	//shn_gis_add_marker_map();
	shn_gis_init_plugin();
	shn_form_fsclose();
	shn_form_fsopen(_("GPS Coordinates"));
	shn_form_text(_("Northing / Latitude"),"gps_x",'size="60"');
	shn_form_text(_("Easting / Longitude"),"gps_y",'size="60"');
	shn_form_fsclose();	
	shn_form_submit("Next");
	shn_form_fclose();
	include_once $global['approot']."/mod/gis/plugins/google_maps/handler_google_maps.inc";
	add_footer();
	load_map();
	add_marker($_POST['location_name']);
	end_page();
}

function shn_lr_com ()
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
