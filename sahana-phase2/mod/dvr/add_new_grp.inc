<?php


/**
 * 
 * Functions to add group in DVR
 * 
 *
 *  PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera  
 * @author     Sheran Corera
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ('lib.inc');
include_once ('add_new_indv.inc');
include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');
include_once ($global['approot'] . '/inc/lib_errors.inc');

//add group type and group head details
function shn_dvr_grouptype_and_head_details_start() {
	_shn_dvr_print_header(_("Add New Group"));
	shn_dvr_grouptype_and_head_details();
}

//error handling
function _shn_dvr_validate_error() {
	clean_errors();
	$error_flag = false;

	$cc = $_POST['typ_of_grp'];
	if (trim($cc) == null | trim($cc) == '0') {
		add_error(_("Please  select the group type"));
		$error_flag = true;
	}
	return $error_flag;
}

//group type and head details
function shn_dvr_grouptype_and_head_details($errors = false) {
	if ($errors)
		display_errors();

	shn_form_fopen("add_new_grp", null, array (
		'req_message' => true
	));
?>
    <?php


	shn_form_hidden(array (
		'seq' => 'chk'
	));
	//select the group type
	shn_form_fsopen(_("Select Group Type"));
	print '<div class="info">';
	print _("Please select a Group that describes you well");
	print '<br />';

	print '<br />';
	print '</div>';
	print '<br />';

	$typ_of_grp = array ();
	//to be removed using field options
	array_push($typ_of_grp, '-- Select Category --');
	array_reverse($typ_of_grp);
	$typ_of_grp[1] = "Families";
	$typ_of_grp[2] = "Passengers";
	$typ_of_grp[3] = "Tourists";
	$typ_of_grp[4] = "Other";

	$extra_opts['value'] = $typ_of_grp;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	$extra_opts['req'] = true;

	shn_form_select($typ_of_grp, _("Type of Group"), 'typ_of_grp', "onChange='makeRequest(\"stream.php?mod=rms&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", $extra_opts);
	shn_form_fsclose();
	//group head information
	shn_form_fsopen(_("Head Of Group"));

	print '<br />';

	$extra_opts['value'] = $name;
	$extra_opts['help'] = _("Enter the Full Name.(Required)");
	$extra_opts['req'] = true;

	$extra_opts['value'] = $nic;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	$extra_opts['req'] = false;
	shn_form_text(_("NIC No"), 'nic', null, $extra_opts);

	shn_form_upload(_('Upload Photograph'), "picture");

	$extra_opts['value'] = $mobile;
	$extra_opts['help'] = _("Enter the Mobile number if available. (Optional)");
	shn_form_text(_("Mobile"), 'mobile', null, $extra_opts);

	$extra_opts['value'] = $telephone;
	$extra_opts['help'] = _("Enter a Land Phone number if available. (Optional)");
	shn_form_text(_("Telephone"), 'telephone', null, $extra_opts);

	$extra_opts['value'] = $email;
	$extra_opts['help'] = _("Enter a Email Address if available. (Optional)");
	shn_form_text(_("Email"), 'email', null, $extra_opts);

	$extra_opts['value'] = $address;
	$extra_opts['help'] = _("Enter a Address if available. (Optional)");
	shn_form_textarea(_("Address"), 'address', null, $extra_opts);
?>
   
<?php


	shn_form_fsclose();

	print '<br />';
	//head count
	shn_form_fsopen(_("No Of Members In Group"));
	print '<br />';

	$extra_opts['value'] = $adlt_mls;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Adult Males"), 'adlt_mls', null, $extra_opts);

	$extra_opts['value'] = $adlt_fmls;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Adult Females"), 'adlt_fmls', null, $extra_opts);

	$extra_opts['value'] = $chldrn;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Children"), 'chldrn', null, $extra_opts);
	shn_form_fsclose();
	print '<br />';
	//member status
	shn_form_fsopen(_("Status Of Members In Group"));
	print '<br />';

	$extra_opts['value'] = $dsplcd;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Displaced"), 'dsplcd', null, $extra_opts);

	$extra_opts['value'] = $misng;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Missing"), 'misng', null, $extra_opts);

	$extra_opts['value'] = $dead;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Dead"), 'dead', null, $extra_opts);

	$extra_opts['value'] = $rehbd;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Rehabilitated"), 'rehbd', null, $extra_opts);

	shn_form_fsclose();

	shn_form_submit(_("Add Location Check Details"), "name=location_button");
	shn_form_submit(_("Finish"));
	shn_form_fclose();
	print '<br />';
}

//dvr member details
function shn_dvr_mbr_dtls() {
	_shn_dvr_print_header(_("Add New Group"));
	shn_dvr_tab_lst_grp();
	//  shn_dvr_no_of_ppl();

	shn_form_fopen("loc_of_grp", null, array (
		'req_message' => false
	));
	shn_form_hidden(array (
		'seq' => 'add_reqstr'
	));
	shn_form_fsopen(_("No Of Members In Group"));

	print '<br />';

	$extra_opts['value'] = $adlt_mls;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Adult Males"), 'adlt_mls', null, $extra_opts);

	$extra_opts['value'] = $adlt_fmls;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Adult Females"), 'adlt_fmls', null, $extra_opts);

	$extra_opts['value'] = $chldrn;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Children"), 'chldrn', null, $extra_opts);

	shn_form_fsclose();
	//  shn_form_fclose();
	print '<br />';

	shn_form_hidden(array (
		'seq' => 'add_reqstr'
	));
	shn_form_fsopen(_("Status Of Members In Group"));

	print '<br />';

	$extra_opts['value'] = $dsplcd;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Displaced"), 'dsplcd', null, $extra_opts);

	$extra_opts['value'] = $misng;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Missing"), 'misng', null, $extra_opts);

	$extra_opts['value'] = $dead;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Dead"), 'dead', null, $extra_opts);

	$extra_opts['value'] = $rehbd;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_text(_("Rehabilitated"), 'rehbd', null, $extra_opts);

	shn_form_fsclose();

	shn_form_submit(_("Add Location Check Details"), "name=location_button");
	shn_form_submit(_("Finish"));
	shn_form_fclose();
	print '<br />';
}

//location details
function shn_dvr_loc_dtls() {

	global $global;
	global $conf;
	_shn_dvr_print_header(_("Add New Group"));

	shn_form_fopen("add_new_grp", null, array (
		'req_message' => false
	));
	shn_form_hidden(array (
		'seq' => 'add_reqstr'
	));
	shn_form_fsopen(_("Displaced Location"));

	$parent = _shn_dvr_get_start_loc();
	$range = shn_dvr_get_loc_range();
	//to be changed
	$extra_opts['camps'] = 'false';
	//shn_location($range, $_POST[$range["end"]], $parents);
	shn_form_checkbox("Location Unknown", "loc_unknown");
	shn_form_text("Location Name", "dis_loc_name");
	shn_form_text("Address Line1", "dis_add_line1");
	shn_form_text("Address Line2", "dis_add_line2");

	shn_form_fsclose();

	shn_form_fsopen(_("Current Location"));
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

	shn_form_submit(_("Check List"), "name=checklist_button");
	shn_form_submit(_("Finish"));
	shn_form_fclose();
	print '<br />';

}

function shn_dvr_cklst_and_desc() {
	_shn_dvr_print_header(_("Add New Group"));
	//shn_dvr_tab_lst_grp();
	//shn_dvr_chk_lst();

	shn_form_fopen("req_new", null, array (
		'req_message' => false
	));
	shn_form_hidden(array (
		'seq' => 'add_reqstr'
	));
	shn_form_fsopen(_("Checklist"));

	print '<br />';

	$extra_opts['value'] = $dry_rtns;
	$extra_opts['help'] = _("If you recieved the necessary Dry Rations please " .
	"tick the Check Box (Optional)");
	shn_form_checkbox(_("Dry Rations"), 'dry_rtns', 'null', $extra_opts);

	$extra_opts['value'] = $wtr;
	$extra_opts['help'] = _("If you recieved the necessary Drinking Water supplies please " .
	"tick the Check Box (Optional)");
	shn_form_checkbox(_("Drinking Water"), 'wtr', 'null', $extra_opts);

	$extra_opts['value'] = $clths;
	$extra_opts['help'] = _("If you recieved the necessary Clothes please " .
	"tick the Check Box (Optional)");
	shn_form_checkbox(_("Clothes"), 'clths', 'null', $extra_opts);

	$extra_opts['value'] = $sntry_spls;
	$extra_opts['help'] = _("If you recieved the necessary Sanitary Supplies please " .
	"tick the Check Box (Optional)");
	shn_form_checkbox(_("Sanitary Supplies"), 'sntry_spls', 'null', $extra_opts);

	$extra_opts['value'] = $emgcy_blnkt;
	$extra_opts['help'] = _("If you recieved the necessary Emergency Blankets please " .
	"tick the Check Box (Optional)");
	shn_form_checkbox(_("Emergency Blankets"), 'emgncy_blnkt', 'null', $extra_opts);

	$extra_opts['value'] = $fst_aid;
	$extra_opts['help'] = _("If you recieved the necessary First Aid Items please " .
	"tick the Check Box (Optional)");
	shn_form_checkbox(_("First Aid Items"), 'fst_aid', 'null', $extra_opts);
	shn_form_fsclose();

	print '<br />';

	shn_form_hidden(array (
		'seq' => 'add_reqstr'
	));
	shn_form_fsopen(_("Group Description"));

	print '<br />';

	$extra_opts['value'] = $desc;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	shn_form_textarea(_("Description"), 'desc', null, $extra_opts);
	shn_form_submit(_("Finish"));
	shn_form_fsclose();

	shn_form_fclose();
	print '<br />';

}

function shn_dvr_hd_of_grp() {
	//head
	shn_form_fopen("hd_of_grp", null, array (
		'req_message' => false
	));
	shn_form_hidden(array (
		'seq' => 'add_reqstr'
	));
	shn_form_fsopen(_("Head Of Group"));
	print '<div class="info">';
	print _("If you are a registered requester, Please enter your request ID ");
	print '<br />';
	print _("You can also use your 'id' if you have registered on the sahana system as a user, administrator, volunteer etc...");
	print '<br />';
	print '</div>';
	print '<br />';

	$extra_opts['value'] = $name;
	$extra_opts['help'] = _("Enter the Full Name.(Required)");
	$extra_opts['req'] = true;
	shn_form_text(_("Full Name"), 'name', null, $extra_opts);

	$extra_opts['value'] = $nic;
	$extra_opts['help'] = _("Enter the National Identity Card Number if available. (Optional)");
	$extra_opts['req'] = false;
	shn_form_text(_("NIC No"), 'nic', null, $extra_opts);

	$extra_opts['value'] = $mobile;
	$extra_opts['help'] = _("Enter the Mobile number if available. (Optional)");
	shn_form_text(_("Mobile"), 'mobile', null, $extra_opts);

	$extra_opts['value'] = $telephone;
	$extra_opts['help'] = _("Enter a Land Phone number if available. (Optional)");
	shn_form_text(_("Telephone"), 'telephone', null, $extra_opts);

	$extra_opts['value'] = $email;
	$extra_opts['help'] = _("Enter a Email Address if available. (Optional)");
	shn_form_text(_("Email"), 'email', null, $extra_opts);

	$extra_opts['value'] = $address;
	$extra_opts['help'] = _("Enter a Address if available. (Optional)");
	shn_form_textarea(_("Address"), 'address', null, $extra_opts);

	shn_form_submit(_("Add More Details"));
	shn_form_fsclose();
	shn_form_fclose();
	print '<br />';
}
?>
