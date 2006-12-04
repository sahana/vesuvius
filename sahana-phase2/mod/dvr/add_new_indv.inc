<?php


/**
 *Major functions for add a new disaster victim
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ('lib.inc');
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_errors.inc');

function shn_dvr_add_new_individual() {
	_shn_dvr_print_header(_("Add New Individual"));

	shn_form_fopen("add_new_indv", null, array (
		'req_message' => true
	));
	shn_form_hidden(array (
		'seq' => 'add_new_individual'
	));
	shn_form_fsopen(_("Select Group Type"));
	print '<div class="info">';
	print _("Please select a Group that describes you well");
	print '<br />';

	print '</div>';
	print '<br />';

	$typ_of_grp = array ();

	//to be removed using field_option
	array_push($typ_of_grp, '-- Select Category --');
	array_reverse($typ_of_grp);

	$typ_of_grp[1] = "Families";

	$typ_of_grp[2] = "Passengers";

	$typ_of_grp[3] = "Tourists";

	$typ_of_grp[4] = "Other";

	$extra_opts['value'] = $typ_of_grp;

	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");

	$extra_opts['req'] = true;

	shn_form_select($typ_of_grp, _("Type Of Group"), 'typ_of_grp', "onChange='makeRequest(\"stream.php?mod=rms&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", $extra_opts);

	shn_form_fsclose();

	print '<br />';

	shn_form_fsopen(_('Basic Details'));
	print '<br />';
	shn_form_text(_('Full Name'), 'full_name', 'size="30"', array (
		'req' => true,
		'help' => 'You are required to specify the full name in order to identify the entry'
	));
	shn_form_text(_('Family Name'), 'family_name', 'size="30"', array (
		'help' => _('Family name, or the surname could be specified for matching of people with similar Family names'
	)));
	shn_form_text(_('Local Name'), 'local_name', 'size="30"', array (
		'help' => _('You may also specify the local name, even in different script than English'
	)));
	shn_form_text(_('Date of Birth   (YYYY-MM-DD)'), 'dob', 'size=8');
	shn_form_opt_select("opt_age_group", _('Age Group'));
	shn_form_opt_select("opt_gender", _('Gender'));
	shn_form_opt_select("opt_marital_status", _('Marital Status'));
	shn_form_opt_select("opt_religion", _('Religion'), null);
	shn_form_opt_select("opt_race", _('Race'));
	shn_form_fsclose();
	print '<br />';

	shn_form_fsopen(_('Identity'));
	print '<br />';
	shn_form_text(_('Identity Card Number'), 'idcard', 'size="30"', array (
		'help' => _('Specify the Identity card Number, Although this is not required this will be useful in searching for the person'
	)));
	shn_form_text(_('Passport Number'), 'passport', 'size="30"', array (
		'help' => _('Please Specify the passport number, Although this is not required this will be useful in searching for the person'
	)));
	shn_form_text(_('Driving License'), 'drv_license', 'size="30"', array (
		'help' => _('Please Specify the driving License number, Although this is not required this will be useful in searching for the person'
	)));
	shn_form_fsclose();

	print '<br />';
	shn_form_fsopen(_('Upload Picture'));
	print '<br />';
	shn_form_upload(_('Upload Picture'), "picture");
	shn_form_fsclose();

	shn_form_fsopen(_('Contact Information Of The Disaster Victim'));
	print '<div class="info">';
	print '<br />';
	shn_form_textarea(_('Address'), "address", null, array (
		'help' => _('Your address can be specified to contact you'
	)));
	shn_form_text(_('Postal Code'), 'zip', 'size="15"', array (
		'help' => _('Specify a postal code, if it is available'
	)));
	shn_form_text(_('Home Phone'), 'phone', 'size="15"');
	shn_form_text(_('Mobile'), 'mobile', 'size="15"');
	shn_form_fsclose();

	shn_form_submit("Next", "name=location_individual");
	shn_form_fclose();
	print '<br />';

}

//add location dettails

function shn_dvr_disp_and_crnt_loc() {
	_shn_dvr_print_header(_("Add New Individual"));
	global $global;
	global $conf;
	shn_form_fopen("add_new_indv", null, array (
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'entry'
	));
	shn_form_fsopen(_('Displaced Location Of The Victim'));
	print '<br />';
	$typ_of_grp = array ();
	array_push($typ_of_grp, '-- Select Option --');
	array_reverse($typ_of_grp);
	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	shn_form_select($typ_of_grp, _("Displaced Location"), 'typ_of_grp', "onChange='makeRequest(\"stream.php?mod=dvr&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", array (
		'value' => $category
	));

	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();
	$extra_opts['camps'] = 'true';
	//shn_location($range, $_POST[$range["end"]], $parents);
	shn_form_checkbox("Location Unknown", "loc_unknown");
	shn_form_text("Location Name", "dis_loc_name");
	shn_form_text("Address Line1", "dis_add_line1");
	shn_form_text("Address Line2", "dis_add_line2");
	shn_form_fsclose();
	shn_form_fsopen(_('Current Location Of The Victim'));

	print '<br />';
	$typ_of_grp = array ();
	array_push($typ_of_grp, '-- Select Option --');
	array_reverse($typ_of_grp);
	$typ_of_grp[1] = "Same As Group";
	$typ_of_grp[2] = "Other";
	shn_form_select($typ_of_grp, _("Current Location"), 'typ_of_grp', "onChange='makeRequest(\"stream.php?mod=dvr&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", array (
		'value' => $category
	));
	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();
	shn_location($range, $_POST[$range["end"]], $parent, 'camp');
	shn_form_fsclose();

	shn_form_fsopen(_("Location Information"));
	echo _("Plot the Camp/Shelter Location or Coordinates below");
	shn_form_hidden(array (
		'seq' => 'chk'
	));
	shn_form_fsclose();

	//call gis api from gis module
	include $global['approot'] . "/mod/gis/gis_fns.inc";
	shn_gis_add_marker_map_form("GIS Map", "Disaster Victims Registry");

	shn_form_fsclose();
	shn_form_submit("Next", "name=physical_button");
	shn_form_fclose();
	print '<br />';

	//shn_dvr_crnt_loc_vic();
}

function shn_dvr_physical_information() {
	shn_form_fopen("add_new_indv", null, array (
		'enctype' => 'enctype="multipart/form-data"'
	));
	shn_form_hidden(array (
		'seq' => 'entry'
	));

	shn_form_fsopen(_('Upload FingerPrint'));
	print '<br />';
	shn_form_upload(_('Upload Picture'), "picture");
	shn_form_fsclose();
	print '<br />';

	shn_form_fsopen(_('Physical Details'));
	print '<br />';
	shn_form_opt_select("opt_eye_color", _('Eye Colour'));
	shn_form_opt_select("opt_skin_color", _('Skin Colour'));
	shn_form_opt_select("opt_hair_color", _('Hair Colour'));
	shn_form_text(_('Height'), 'height', 'size="10"');
	shn_form_text(_('Weight'), 'weight', 'size="10"');
	shn_form_opt_select("opt_blood_type", _('Blood Type'));
	//shn_form_textarea(_('Other Distinctive Features'), 'physical_comments');
	shn_form_fsclose();
	shn_form_fsopen(_('Other Details'));
	print '<br />';

	shn_form_textarea(_('Description Of Clothing And Appearance'), 'last_clothing');
	shn_form_textarea(_('Other Relevant Information'), 'comments');
	shn_form_fsclose();
	shn_form_submit(_('Finish'));
	shn_form_fclose();
	print '<br />';

}
?>
