<?php

function shn_lr_default()
{
?>
<div id="home">
<h2><?php echo _("Location  Registry");?></h2>
<?php
}

function shn_lr_aloc ()
{
	
	//echo "Locations";
	global $global;
	include_once($global['approot'].'/inc/lib_form.inc');
	include_once($global['approot'].'/inc/lib_validate.inc');
	include_once($global['approot'].'/inc/lib_errors.inc');
	
	shn_form_fopen(amap);
	shn_form_fsopen(_("Add Location"));
	shn_form_text(_("Location Name"),"location_name",'size="60"');
	shn_form_opt_select("opt_camp_type",_("Location Type"));
	shn_form_text(_("Contact Person  Name"),"person_name",'size="60"');
	shn_form_opt_select("opt_camp_type",_("Contact Type"));
	shn_form_text(_("Contact Person  Address"),"person_address",'size="60"');
	shn_form_text(_("Contact Person  Phone"),"person_phone",'size="60"');
	shn_form_textarea(_("Directions to Location"),"direction",'size="60"');
	shn_form_textarea(_("Comments on Location"),"comment",'size="60"');
	shn_form_fsclose();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

function shn_lr_amap()
{
	global $global;
	include_once($global['approot'].'/inc/lib_form.inc');
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
	echo "Done";
}
?>
