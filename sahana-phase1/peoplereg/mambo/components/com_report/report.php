<?php

defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

//require_once( $mainframe->getPath( 'front_html' ) );

session_start();
include('forms.php');
include('db.php');

?>

<?php

function capture_data()
{
	capture_input_string('name');
	capture_input_string('other_names');
	capture_input_string('status');
	capture_input_string('gender');
	capture_input_string('dob');
	capture_input_string('age');
	capture_input_string('nic_no');
	capture_input_string('passport_no');
	capture_input_string('marital_status');
	capture_input_string('religion');
	capture_input_string('location');
	capture_input_string('location_details');
	capture_input_string('kin');
	capture_input_string('orphan');
	capture_input_string('kin_contact');
	capture_input_string('skin_colour');
	capture_input_string('hair_colour');
	capture_input_string('eye_colour');
	capture_input_string('height');
	capture_input_string('weight');
	capture_input_string('features');
	capture_input_string('clothing');
	capture_input_string('address');
	capture_input_string('city');
	capture_input_string('province');
	capture_input_string('district');
	capture_input_string('country');
	capture_input_string('email');
	capture_input_string('race');
	capture_input_string('phone_no');
	capture_input_string('mobile_no');
	capture_input_string('comments');
	capture_input_string('tracked_by');
	capture_input_string('tracking_comments');
	capture_input_image('picture');
}

function capture_reporter_data()
{
	capture_input_string('reporting_for');
	capture_input_string('reporter_name');
	capture_input_string('reporter_address');
	capture_input_string('reporter_city');
	capture_input_string('reporter_phone');
	capture_input_string('reporter_mobile');
	capture_input_string('reporter_email');
	capture_input_string('reporter_relationship');
	capture_input_string('reporter_org');
}

function validate_data()
{
	$_SESSION['form']['validated'] = true;
	return true;
}

function validate_reporter_data()
{
	$_SESSION['form']['reporter_validated'] = true;
	return true;
}

function display_data()
{
	global $my;

?>

<div align="center">
<h1 style="color: #CF6A6A; font-family: Georgia, serif;"><? echo $my->id ? 'Enter People Information' : 'Report a Missing Person'; ?></h1>
</div>

<div align="left">

<form method="post" action="index.php?option=com_report&step=4">

<ul>
	
<? if (input_is_set('picture')) { ?>
	<img src="uploads/<?=$_SESSION['form']['picture']?>" align="right" />
<? } ?>
<? if (input_is_set('name')) { ?>
	<li>Name: <? display_input('name'); ?></li>
<? } ?>
<? if (input_is_set('other_names')) { ?>
	<li>Other names: <? display_input('other_names'); ?></li>
<? } ?>
<? if (input_is_set('status')) { ?>
	<li>Status: <? display_input_caption('status'); ?></li>
<? } ?>
<? if (input_is_set('gender')) { ?>
	<li>Gender: <? display_input_caption('gender'); ?></li>
<? } ?>
<? if (input_is_set('dob')) { ?>
	<li>Date of birth: <? display_input('dob'); ?></li>
<? } ?>
<? if (input_is_set('age')) { ?>
	<li>Age (years): <? display_input('age'); ?></li>
<? } ?>
<? if (input_is_set('nic_no')) { ?>
	<li>National ID number: <? display_input('nic_no'); ?></li>
<? } ?>
<? if (input_is_set('passport_no')) { ?>
	<li>Passport Number: <? display_input('passport_no'); ?></li>
<? } ?>
<? if (input_is_set('marital_status')) { ?>
	<li>Maritial status: <? display_input_caption('marital_status'); ?></li>
<? } ?>
<? if (input_is_set('religion')) { ?>
	<li>Religion: <? display_input_caption('religion'); ?></li>
<? } ?>
<? if (input_is_set('location')) { ?>
	<li>Last known location: <? display_input('location'); ?></li>
<? } ?>
<? if (input_is_set('location_details')) { ?>
	<li>Location contact details: <? display_input('location_details'); ?></li>
<? } ?>
<? if (input_is_set('kin')) { ?>
	<li>Next of kin: <? display_input('kin'); ?></li>
<? } ?>
<? if (input_is_set('orphan')) { ?>
	<li>Orphan: <? display_input('orphan'); ?></li>
<? } ?>
<? if (input_is_set('kin_contact')) { ?>
	<li>Next of kin contact details: <? display_input('kin_contact'); ?></li>
<? } ?>

<? if (input_is_set('skin_colour')) { ?>
	<li>Skin colour: <? display_input_caption('skin_colour'); ?></li>
<? } ?>
<? if (input_is_set('hair_colour')) { ?>
	<li>Hair colour: <? display_input_caption('hair_colour'); ?></li>
<? } ?>
<? if (input_is_set('eye_colour')) { ?>
	<li>Eye colour: <? display_input_caption('eye_colour'); ?></li>
<? } ?>
<? if (input_is_set('height')) { ?>
	<li>Height (inches): <? display_input('height'); ?></li>
<? } ?>
<? if (input_is_set('weight')) { ?>
	<li>Weight (kg): <? display_input('weight'); ?></li>
<? } ?>
<? if (input_is_set('features')) { ?>
	<li>Distinctive features: <? display_input('features'); ?></li>
<? } ?>
<? if (input_is_set('clothing')) { ?>
	<li>Last clothing: <? display_input('clothing'); ?></li>
<? } ?>

<? if (input_is_set('address')) { ?>
	<li>Street address: <? display_input('address'); ?></li>
<? } ?>
<? if (input_is_set('city')) { ?>
	<li>City/village: <? display_input('city'); ?></li>
<? } ?>
<? if (input_is_set('province')) { ?>
	<li>Province: <? display_input_caption('province'); ?></li>
<? } ?>
<? if (input_is_set('district')) { ?>
	<li>District: <? display_input_caption('district'); ?></li>
<? } ?>
<? if (input_is_set('country')) { ?>
	<li>Country: <? display_input('country'); ?></li>
<? } ?>
<? if (input_is_set('email')) { ?>
	<li>Email: <? display_input('email'); ?></li>
<? } ?>
<? if (input_is_set('race')) { ?>
	<li>Race: <? display_input_caption('race'); ?></li>
<? } ?>
<? if (input_is_set('phone_no')) { ?>
	<li>Home telephone no: <? display_input('phone_no'); ?></li>
<? } ?>
<? if (input_is_set('mobile_no')) { ?>
	<li>Mobile No: <? display_input('mobile_no'); ?></li>
<? } ?>
<? if (input_is_set('comments')) { ?>
	<li>Comments: <? display_input('comments'); ?></li>
<? } ?>
<? if (input_is_set('tracked_by')) { ?>
	<li>Being tracked by: <? display_input('tracked_by'); ?></li>
<? } ?>
<? if (input_is_set('tracking_comments')) { ?>
	<li>Tracking comments: <? display_input('tracking_comments'); ?></li>
<? } ?>
</ul>
<input type="submit" name="back" value="<<< Back" />
<input type="submit" name="confirm" value="Confirm >>>" />

</form>

</div>

<?

}

function person_data()
{
	global $_SESSION;
	global $my;

	$_SESSION['form']['validated'] = false;

?>

<div align="center">
<h1 style="color: #CF6A6A; font-family: Georgia, serif;"><? echo $my->id ? 'Enter People Information' : 'Report a Missing Person'; ?></h1>
</div>

<? if (!isset($_SESSION['help']['report'])) { ?>

<ul style="line-height: 1.7em; list-style: square; color: #849663">
	<li>Please enter all available details of the person</li>
	<li>All fields below are optional</li>
	<li>If you need assistance please call this hotline xxx-xxxx-xxx</li>
</ul>

<? } ?>

<div id="entry-form">

<script language="JavaScript">

function validate_age()
{
	var age_regex = /[a-zA-Z]+/
	if( (document.reporting_form.age.value.search( age_regex ) != -1) ||
	    (document.reporting_form.age.value < 0) ) {
		alert( "Please enter only positive numbers for the Age field" );
	}
}

function validate_dob()
{
	if ( document.reporting_form.dob.value.search(/^\d+-\d\d-\d\d$/) != 0 ) {
		alert("Please enter the date in yyyy-mm-dd format");
	} else {
		var digits = document.reporting_form.dob.value.toString().split("-");
		// digits will have year, month, day
		// Anyone born before 1900 should be dead
		var mydate = new Date();
		if ( !( digits[0] >= 1900 && digits[0] <= mydate.getFullYear()) ) {
			alert("Please enter a valid year");
		} else if ( !( digits[1] >= 1 && digits[1] <= 12 ) ) {
			alert("Please enter a valid month");
		} else if ( !( digits[2] >= 1 && digits[2] <= 31 ) ) {
			alert("Please enter a valid date");
		}
	}
}

function validate_height() {
	if( document.reporting_form.height.value.search(/[a-zA-Z]+/) != -1 ) {
		alert("Height will be taken as Feet, please enter only the number");
	}
}

function validate_weight() {
	if( document.reporting_form.height.value.search(/[a-zA-Z]+/) != -1 ) {
		alert("Weight will be taken as KG, please enter only the number");
	}
}

function validate_email() {
	if( document.reporting_form.email.value.search(/@/) == -1 ) {
		alert("Please enter a valid email address");
	}
}

</script>

<form method="post" enctype="multipart/form-data" action="index.php?option=com_report&step=2" name="reporting_form">

<hr />

<table class="data_entry">
	<tr>
		<td class="row1">Name:</td>
		<td class="row2"><? show_input_text('name'); ?></td>
	</tr>
	<tr>
		<td>Other names:</td>
		<td><? show_input_text('other_names'); ?></td>
	</tr>
<? if ($my->id) { ?>
	<tr>
		<td>Status:</td>
		<td><? show_input_select('status'); ?></td>
	</tr>
<? } else { ?>
	<input type="hidden" name="status" value="missing" />
<? } ?>
	<tr> 
		<td>Gender:</td>
		<td><? show_input_select('gender'); ?></td>
	</tr>
	<tr>
		<td>Date of birth (yyyy-mm-dd):</td>
		<td><? show_input_text('dob', 0, "onblur=\"validate_dob();\""); ?></td>
	<tr>
		<td>Age:</td>
		<td><? show_input_text('age', 0, "onblur=\"validate_age();\""); ?></td>
	</tr>
	<tr>
		<td>Image:</td>
		<td><input type="file" name="picture" /></td>
	</tr>
</table>

<hr />

<table class="data_entry">
	<tr>
		<td class="row1">National ID number:</td>
		<td class="row2"><? show_input_text('nic_no'); ?></td>
	</tr>
	<tr>
		<td>Passport number:</td>
		<td><? show_input_text('passport_no'); ?></td>
	</tr>
	<tr>
		<td>Marital status:</td>
		<td><? show_input_select('marital_status'); ?></td>
	</tr>
	<tr>
		<td>Religion:</td>
		<td><? show_input_select('religion'); ?></td>
	</tr>
	<tr>
		<td>Race:</td>
		<td><? show_input_select('race'); ?></td>
	</tr>
</table>

<hr />

<table class="data_entry">
	<tr>
		<td class="row1">Last seen location:</td>
		<td class="row2"><? show_input_text('location'); ?></td>
	</tr>
	<tr>
		<td>Location contact details:</td>
		<td><? show_input_text('location_details'); ?></td>
	</tr>
	<tr>
		<td>Orphan?:</td>
		<td><? show_input_select('orphan'); ?></td>
	</tr>
	<tr>
		<td>Next of kin:</td>
		<td><? show_input_text('kin'); ?></td>
	</tr>
	<tr>
		<td>Next of kin contact details:</td>
		<td><? show_input_text('kin_contact'); ?></td>
	</tr>

</table>

<hr />

<table class="data_entry">

	<tr>
		<td class="row1">Skin colour:</td>
		<td class="row2"><? show_input_select('skin_colour'); ?></td>
	</tr>
	<tr>
		<td>Hair colour:</td>
		<td><? show_input_select('hair_colour'); ?></td>
	</tr>
	<tr>
		<td>Eye colour:</td>
		<td><? show_input_select('eye_colour'); ?></td>
	</tr>
	<tr>
		<td>Height: (inches)</td>
		<td><? show_input_text('height', 0, "onblur=\"validate_height(height);\""); ?></td>
	</tr>
	<tr>
		<td>Weight: (kg)</td>
		<td><? show_input_text('weight', 0, "onblur=\"validate_weight(weight);\""); ?></td>
	</tr>
	<tr>
		<td>Distinctive features:</td>
		<td><? show_input_textarea('features', 5, 35); ?></td>
	</tr>
	<tr>
		<td>Last clothing:</td>

		<td><input type="text" name="clothing" /></td>
	</tr>

</table>

<hr />

<table class="data_entry">
	<tr>
		<td class="row1">Street address:</td>
		<td class="row2"><? show_input_text('address'); ?></td>
	</tr>
	<tr>
		<td>City/village:</td>
		<td><? show_input_text('city'); ?></td>
	</tr>
	<tr>
		<td>Province:</td>
		<td><? show_input_select('province'); ?></td>
	</tr>
	<tr>
		<td>District:</td>
		<td><? show_input_select('district'); ?></td>
	</tr>
	<tr>
		<td>Country:</td>
		<td><? show_input_text('country'); ?></td>
	</tr>
	<tr>
		<td>Email:</td>
		<td><? show_input_text('email',0, "onblur=\"validate_email();\""); ?></td>
	</tr>
	<tr>
		<td>Home telephone no:</td>
		<td><? show_input_text('phone_no'); ?></td>
	</tr>
	<tr>
		<td>Mobile No:</td>
		<td><? show_input_text('mobile_no'); ?></td>
	</tr>
	<tr>
		<td>Comments:</td>
		<td><? show_input_textarea('comments', 5, 35); ?></td>
	</tr>

<? if ($my->id) { ?>

</table>

<hr />

<table class="data_entry">
	<tr>
		<td class="row1">Being tracked by:</td>
		<td class="row2"><? show_input_text('tracked_by'); ?></td>
	</tr>
	<tr>
		<td>Tracking comments:</td>
		<td><? show_input_textarea('tracking_comments', 5, 35); ?></td>
	</tr>

<? } ?>

	<tr>
		<td><input type="submit" value="Next >>>" /></td>
	</tr>

</table>

</form>

</div>

<?php

}

function reporter_data()
{
	global $my;

?>

<div align="center">
<h1 style="color: #CF6A6A; font-family: Georgia, serif;"><? echo $my->id ? 'Enter People Information' : 'Report a Missing Person'; ?></h1>
</div>

<div id="entry-form">

<form method="post" enctype="multipart/form-data" action="index.php?option=com_report&step=3">

<hr />

<table class="data_entry">
	<tr>
		<td colspan="2">Reporting on behalf of:
		<input type="radio" name="reporting" value="myself"> Myself
		<input type="radio" name="reporting" value="other"> Other
		</td>
	</tr>
	<tr>
		<td colspan="2">Please fill the following, if reporting on behalf of someone else, OR for the first time.</td>
	</tr>
	<tr>
		<td>Name:</td>
		<td><? show_input_text('reporter_name'); ?></td>
	</tr>
	<tr>
		<td>Address:</td>
		<td><? show_input_text('reporter_address'); ?></td>
	</tr>
	<tr>
		<td>City:</td>
		<td><? show_input_text('reporter_city'); ?></td>
	</tr>
	<tr>
		<td>Phone:</td>
		<td><? show_input_text('reporter_phone'); ?></td>
	</tr>
	<tr>
		<td>Mobile:</td>
		<td><? show_input_text('reporter_mobile'); ?></td>
	</tr>
	<tr>
		<td>Email:</td>
		<td><? show_input_text('reporter_email'); ?></td>
	</tr>
	<tr>
		<td>Relationship:</td>
		<td><? show_input_text('reporter_relationship'); ?></td>
	</tr>
	<tr>
		<td>Organization:</td>
		<td><? show_input_text('reporter_org'); ?></td>
	</tr>
	<tr>
		<td>
			<input type="submit" name="back" value="<<< Back" />
			<input type="submit" name="next" value="Next >>>" />
		</td>
	</tr>
</table>

</form>

</div>

<?php

}

function store_data()
{
	global $_SESSION;
	global $my;

	if (!($my->id) && ($_SESSION['form']['status'] != 'missing'))
		return;
	if (!($my->id) && $_SESSION['form']['tracked_by'])
		return;
	if (!($my->id) && $_SESSION['form']['tracking_comments'])
		return;

	begin_transaction();
	$report_id = new_report();
	$entity_id = new_entity();

	store_string($report_id, $entity_id, 'name', 1);
	store_string($report_id, $entity_id, 'other_names', 1);
	store_selection($report_id, $entity_id, 'gender');
	store_string($report_id, $entity_id, 'dob');
	if (isset($_SESSION['form']['age'])) {
		$_SESSION['form']['age_str'] = $_SESSION['form']['age'];
		store_integer($report_id, $entity_id, 'age');
		store_string($report_id, $entity_id, 'age_str');
	}
	store_string($report_id, $entity_id, 'nic_no', 1);
	store_string($report_id, $entity_id, 'passport_no', 1);
	store_selection($report_id, $entity_id, 'marital_status', 1);
	store_selection($report_id, $entity_id, 'religion', 1);
	store_selection($report_id, $entity_id, 'status');
	store_string($report_id, $entity_id, 'location', 1);
	store_string($report_id, $entity_id, 'location_details', 1);
	store_string($report_id, $entity_id, 'kin');
	store_selection($report_id, $entity_id, 'orphan');
	store_string($report_id, $entity_id, 'kin_contact');
	store_selection($report_id, $entity_id, 'skin_colour');
	store_selection($report_id, $entity_id, 'hair_colour');
	store_selection($report_id, $entity_id, 'eye_colour');
	store_integer($report_id, $entity_id, 'height'); // FIXME: convert to inchecs
	store_integer($report_id, $entity_id, 'weight'); // FIXME: convert to kg
	store_string($report_id, $entity_id, 'features', 1);
	store_string($report_id, $entity_id, 'clothing', 1);
	store_string($report_id, $entity_id, 'address', 1);
	store_string($report_id, $entity_id, 'city', 1);
	store_selection($report_id, $entity_id, 'province', 1);
	store_selection($report_id, $entity_id, 'district', 1);
	store_selection($report_id, $entity_id, 'country', 1);
	store_selection($report_id, $entity_id, 'email', 1);
	store_selection($report_id, $entity_id, 'race', 1);
	store_string($report_id, $entity_id, 'phone_no');
	store_string($report_id, $entity_id, 'mobile_no');
	store_string($report_id, $entity_id, 'comments', 1);
	store_string($report_id, $entity_id, 'picture', 1);
	store_string($report_id, $entity_id, 'tracked_by', 1);
	store_string($report_id, $entity_id, 'tracking_comments', 1);

	// Reporter data
	store_string($report_id, $entity_id, 'reporting_for');
	store_string($report_id, $entity_id, 'reporter_name');
	store_string($report_id, $entity_id, 'reporter_address');
	store_string($report_id, $entity_id, 'reporter_city');
	store_string($report_id, $entity_id, 'reporter_phone');
	store_string($report_id, $entity_id, 'reporter_mobile');
	store_string($report_id, $entity_id, 'reporter_email');
	store_string($report_id, $entity_id, 'reporter_relationship');
	store_string($report_id, $entity_id, 'reporter_org');

	commit_transaction();
	clear_form();
	$_SESSION['help']['report'] = true;

	echo 'Thanks for the information!';
}

function display_entity_info($entity)
{
	global $my;

	echo '<table width="100%"><tr><td width="100%" valign="top">';

	$name = get_string_attribute_by_entity($entity, 'name');
	echo '<li> Name: ' . $name;
	$other_names = get_string_attribute_by_entity($entity, 'other_names');
	if ($other_names != 'Unknown') echo '<li> Other Names: ' . $other_names;
	$status = get_option_attribute_by_entity($entity, 'status');
	echo '<li> Status: ' . $status;
	$gender = get_option_attribute_by_entity($entity, 'gender');
	echo '<li> Gender: ' . $gender;
	//$dob = get_string_attribute_by_entity($entity, 'dob');
	//if ($dob != 'Unknown') echo '<li> Date of birth: ' . $dob;
	$age = get_integer_attribute_by_entity($entity, 'age');
	echo '<li> Age: ' . $age;
	//$nic_no = get_string_attribute_by_entity($entity, 'nic_no');
	//if ($nic_no != 'Unknown') echo '<li> NIC no: ' . $nic_no;
	//$passport_no = get_string_attribute_by_entity($entity, 'passport_no');
	//if ($passport_no != 'Unknown') echo '<li> Passport no: ' . $passport_no;
	$marital_status = get_option_attribute_by_entity($entity, 'marital_status');
	if ($marital_status != 'Unknown') echo '<li> Marital status: ' . $marital_status;
	$religion = get_option_attribute_by_entity($entity, 'religion');
	if ($religion != 'Unknown') echo '<li> Religion: ' . $religion;
	//$race = get_option_attribute_by_entity($entity, 'race');
	//if ($race != 'Unknown') echo '<li> Race: ' . $race;
	$location = get_string_attribute_by_entity($entity, 'location');
	if ($location != 'Unknown') echo '<li> Location: ' . $location;
	$location_details = get_string_attribute_by_entity($entity, 'location_details');
	if ($location_details != 'Unknown') echo '<li> Location details: ' . $location_details;
	//$kin = get_string_attribute_by_entity($entity, 'kin');
	//if ($kin != 'Unknown') echo '<li> Kin: ' . $kin;
	//$kin_contact = get_string_attribute_by_entity($entity, 'kin_contact');
	//if ($kin_contact != 'Unknown') echo '<li> Kin contact: ' . $kin_contact;
	$skin_colour = get_option_attribute_by_entity($entity, 'skin_colour');
	if ($skin_colour != 'Unknown') echo '<li> Skin colour: ' . $skin_colour;
	$hair_colour = get_option_attribute_by_entity($entity, 'hair_colour');
	if ($hair_colour != 'Unknown') echo '<li> Hair colour: ' . $hair_colour;
	$eye_colour = get_option_attribute_by_entity($entity, 'eye_colour');
	if ($eye_colour != 'Unknown') echo '<li> Eye colour: ' . $eye_colour;
	$height = get_integer_attribute_by_entity($entity, 'height');
	if ($height != 'Unknown') echo '<li> Height: ' . $height;
	$weight = get_integer_attribute_by_entity($entity, 'weight');
	if ($weight != 'Unknown') echo '<li> Weight: ' . $weight;
	$features = get_string_attribute_by_entity($entity, 'features');
	if ($features != 'Unknown') echo '<li> Features: ' . $features;
	$clothing = get_string_attribute_by_entity($entity, 'clothing');
	if ($clothing != 'Unknown') echo '<li> Clothing: ' . $clothing;
	//$address = get_string_attribute_by_entity($entity, 'address');
	//if ($address != 'Unknown') echo '<li> Address: ' . $address;
	$city = get_string_attribute_by_entity($entity, 'city');
	if ($city != 'Unknown') echo '<li> City: ' . $city;
	$province = get_option_attribute_by_entity($entity, 'province');
	if ($province != 'Unknown') echo '<li> Province: ' . $province;
	$district = get_option_attribute_by_entity($entity, 'district');
	if ($district != 'Unknown') echo '<li> District: ' . $district;
	$country = get_string_attribute_by_entity($entity, 'country');
	if ($country != 'Unknown') echo '<li> Country: ' . $country;
	if ($my->id) {
		$email = get_string_attribute_by_entity($entity, 'email');
		if ($email != 'Unknown') echo '<li> Email: ' . $email;
	}
	$phone_no = get_string_attribute_by_entity($entity, 'phone_no');
	if ($phone_no != 'Unknown') echo '<li> Phone no: ' . $phone_no;
	//$mobile_no = get_string_attribute_by_entity($entity, 'mobile_no');
	//if ($mobile_no != 'Unknown') echo '<li> Mobile no: ' . $mobile_no;
	$comments = get_string_attribute_by_entity($entity, 'comments');
	if ($comments != 'Unknown') echo '<li> Comments: ' . $comments;
	$tracked_by = get_string_attribute_by_entity($entity, 'tracked_by');
	if ($tracked_by != 'Unknown') echo '<li> Being tracked by: ' . $tracked_by;
	$tracking_comments = get_string_attribute_by_entity($entity, 'tracking_comments');
	if ($tracking_comments != 'Unknown') echo '<li> Tracking comments: ' . $tracking_comments;

	echo '</td>';

	$picture = get_string_attribute_by_entity($entity, 'picture');
	if ($picture != 'Unknown') {
		echo '<td valign="top"><img src="uploads/' . $picture. '" align="right" /></td>';
	}
	echo '</tr></table>';
}

?>

<?php

$type = mosGetParam($_GET, 'type');


if ($type == 'search') {
	$q = trim(mosGetParam($_GET, 'q'));
	$entities = basic_search_by_term($q);
	if (sizeof($entities)) {
		//echo '<table border=0 width="100%" cellpadding="10" cellpadding="1">';
		echo '<table border=1>';
		echo '<tr>';
		echo '<th>Name(s)</th>';
		echo '<th>Gender</th>';
		echo '<th>Age</th>';
		echo '<th>Status</th>';
		echo '</tr>';
		foreach($entities as $entity) {
                        echo '<tr class="results-';
			echo ($i % 2) ? 'odd' : 'even';
			echo '">';
			echo '<td><a href="index.php?option=com_report&amp;type=entity&amp;entity=' . $entity . '">' . get_names_by_entity($entity) . '</a></td>';
			echo '<td>' . get_option_attribute_by_entity($entity, 'gender') . '</td>';
			echo '<td>' . get_integer_attribute_by_entity($entity, 'age') . '</td>';
			echo '<td>' . get_option_attribute_by_entity($entity, 'status') . '</td>';
			echo '</tr>';
		}
		echo '</table>';
	}
	else {
		echo "No results found for $q.";
	}
}
elseif ($type == 'entity') {
	$entity = intval(mosGetParam($_GET, 'entity'));
	if ($entity) {
		display_entity_info($entity);
	}
	else {
		echo "No information for this entity.";
	}
}
else {
	$step = intval($_GET['step']);
	if ($step == 0) clear_form();
	if ($_POST['back']) $step -= 2;
	switch ($step) {
		case 2:
			capture_data();
			if (validate_data())
				reporter_data();
			else
				person_data();
			break;
		case 3:
			capture_reporter_data();
			if (validate_reporter_data())
				display_data();
			else
				reporter_data();
			break;
		case 4:
			store_data();
			break;
		default:
			person_data();
	}
}

