<?

// This code works well, but very dirty :-(  What do do? A million records
// are arriving tomorrow, and this UI is going to be used to enter data.
// -- Anuradha

session_start();
require('forms.php');
require('db.php');
require('peoplesearch.php');

// Need to generate this dynamically
$num_members = 10; /* FIXME: get rid of the static value */

?>
<!--
<html>
<head>
	<title>Displaced Persons Data Entry</title>
	<link href="entry.css" rel="stylesheet" type="text/css" /> 
</head>
<body>
-->
	<form action="" method="post">
	<input type="hidden" name="num_members" value="10" />

<?

// Connect to DB running locally
//$dbh = mysql_connect('localhost', 'apache', 'abcd321')
//	or die('Could not connect: ' . mysql_error());
//mysql_select_db('mambo') or die('Could not select database');

// By default, we are in the data entry mode
$screen = 'entry';

// Do something extra for POST
if ($_POST) {
	if ($_POST['back']) {
		// Back button is pressed
		$screen = 'entry';
	}
	elseif ($_POST['submit']) {
		// Submit button pressed from the first screen
		// Capture form data into the session

		// Family ID if editing an existing record
		capture_input_string('family_id');

		// Common information
		capture_input_string('district');
		capture_input_string('division');
		capture_input_string('gs_division');
		capture_input_string('village');

		// General family information
		capture_input_int('family_serial_no');
		capture_input_string('address');
		capture_input_int('num_males');
		capture_input_int('num_females');
		capture_input_int('num_children');

		// Family members and income information
		capture_input_int('num_members');
		$num_members = $_SESSION['form']['num_members'];
		for ($i = 0; $i < $num_members; $i++) {
			capture_input_element_string('name', $i);
			capture_input_element_string('status', $i);
			capture_input_element_string('occupation', $i);
			capture_input_element_int('income', $i);
		}
		capture_input_int('other_income');
		capture_input_int('total_income');
		capture_input_string('property_owned');
		capture_input_int('property_value');

		// Present status and relief related information
		capture_input_string('current_location');
		capture_input_string('current_camp');
		capture_input_int('relief_adults');
		capture_input_int('relief_children');
		capture_input_string('relief_period');
		capture_input_string('remarks');

		// At this point, the input has to be validated
		// Confirmation screen is to be displayed ONLY if
		// validation goes through!

		// unset($_SESSION['form']['valid']);
		// Validate the form
		$_SESSION['form']['valid'] = 1;

		$screen = 'confirm';
	}
	elseif (($_POST['confirm'] || $_POST['finish'])
			&& isset($_SESSION['form']['valid'])) {
		if (isset($_SESSION['form']['family_id'])) {
			// Editing an existing record
			// Clear all the related data
			$family_id = $_SESSION['form']['family_id'];
		}
		else {
			// Create a new family entity
			$family_id = new_family();
		}

		// Each data entry is called a report
		$report_id = new_report();

		store_attribute_selection($report_id, $family_id, 'district');
		store_attribute_string($report_id, $family_id, 'division');
		store_attribute_string($report_id, $family_id, 'gs_division');
		store_attribute_string($report_id, $family_id, 'village');

		store_attribute_integer($report_id, $family_id, 'family_serial_no');
		store_attribute_string($report_id, $family_id, 'address');
		store_attribute_integer($report_id, $family_id, 'num_males');
		store_attribute_integer($report_id, $family_id, 'num_females');
		store_attribute_integer($report_id, $family_id, 'num_children');

		$num_members = $_SESSION['form']['num_members'];
		for ($i = 0; $i < $num_members; $i++) {
			if (member_info_available($i)) {
				$person_id = new_person();
				store_attribute_string($report_id, $person_id, 'name', 1, $i);
				store_attribute_selection($report_id, $person_id, 'status', $i);
				store_attribute_string($report_id, $person_id, 'occupation', 1, $i);
				store_attribute_integer($report_id, $person_id, 'income', $i);
				add_relation($person_id, $family_id, 'family member');
			}
		}

		store_attribute_integer($report_id, $family_id, 'other_income');
		store_attribute_integer($report_id, $family_id, 'total_income');
		store_attribute_string($report_id, $family_id, 'property_owned');
		store_attribute_integer($report_id, $family_id, 'property_value');

		store_attribute_selection($report_id, $family_id, 'current_location');
		store_attribute_string($report_id, $family_id, 'current_camp');
		store_attribute_integer($report_id, $family_id, 'relief_adults');
		store_attribute_integer($report_id, $family_id, 'relief_children');
		store_attribute_string($report_id, $family_id, 'relief_period');
		store_attribute_string($report_id, $family_id, 'remarks');

		// Preserve location info across families
		if ($_POST['confirm']) {
			backup_form_attribute('district');
			backup_form_attribute('division');
			backup_form_attribute('gs_division');
			backup_form_attribute('village');
		}

		clear_form();

		// Preserve location info across families (cont... ;-))
		if ($_POST['confirm']) {
			restore_form_attribute('district');
			restore_form_attribute('division');
			restore_form_attribute('gs_division');
			restore_form_attribute('village');
		}
	}
}

// Display data entry screen
if ($screen == 'entry') {
	// Newly enterred data - not valid
	unset($_SESSION['form']['valid']);

?>
	<h2>Family Details Entry Form</h2>
	<div align="center">
		<hr />
		<table class="entry">
			<tr>
				<td>District:</td>
				<td><? show_input_select('district'); ?></td>
				<td>Divisional secretariat:</td>
				<td><? show_input_text('division'); ?></td>
			</tr>
			<tr>
				<td>Grama Niladhari's Division:</td>
				<td><? show_input_text('gs_division'); ?></td>
				<td>Village:</td>
				<td><? show_input_text('village'); ?></td>
			</tr>
		</table>
		<hr />
		<table class="entry">
			<tr>
				<td>Serial number of the family:</td>
				<td><? show_input_text('family_serial_no'); ?></td>
			</tr>
			<tr>
				<td>Address:</td>
				<td><? show_input_textarea('address', 3, 50); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Males: <? show_input_text('num_males'); ?></td>
				<td>Females: <? show_input_text('num_females'); ?></td>
				<td>Children: <? show_input_text('num_children'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td align="center">Name</td>
				<td align="center">Status</td>
				<td align="center">Occupation</td>
				<td align="center">Income</td>
			</tr>
<?

// Inputs for individual family members
for ($i = 0; $i < $num_members; $i++) {

?>
			<tr>
				<td align="center"><? show_input_element_text('name', $i, 50); ?></td>
				<td align="center"><? show_input_element_select('status', $i); ?></td>
				<td align="center"><? show_input_element_text('occupation', $i); ?></td>
				<td align="center"><? show_input_element_text('income', $i); ?></td>
			</tr>
<?

} // end for

?>
			<tr>
				<td colspan="3" align="right">Other income:</td>
				<td align="center"><? show_input_text('other_income'); ?></td>
			</tr>
			<tr>
				<td colspan="3" align="right">Total income:</td>
				<td align="center"><? show_input_text('total_income'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td valign="middle">Property owned:</td>
				<td><? show_input_textarea('property_owned', 3, 50); ?></td>
				<td valign="middle">Value (Rs): <? show_input_text('property_value'); ?></td>
			</tr>
		</table>
		<hr />
		<table class="entry">
			<tr>
				<td>Current location: <? show_input_select('current_location'); ?></td>
				<td>Camp (if applicable): <? show_input_text('current_camp'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>No of people eligible for relief:</td>
				<td>Adults: <? show_input_text('relief_adults'); ?></td>
				<td>Children: <? show_input_text('relief_children'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Probable period for which relief is necessary: <? show_input_text('relief_period'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Remarks:</td>
				<td><? show_input_textarea('remarks', 3, 50); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td align="right"><input type="submit" name="submit" value=" Submit " /></td>
			</tr>
		</table>
	</div>
<?

} // if ($screen == 'entry')

// Done with the data entry screen
// Now to the confirmation screen

elseif ($screen == 'confirm') {

?>
	<h2>Confirmation Form</h2>
	<div align="center">
		<hr />
		<table class="entry">
			<tr>
				<td>District:</td>
				<td><? display_input_caption('district'); ?></td>
				<td>Divisional secretariat:</td>
				<td><? display_input('division'); ?></td>
			</tr>
			<tr>
				<td>Grama Niladhari's Division:</td>
				<td><? display_input('gs_division'); ?></td>
				<td>Village:</td>
				<td><? display_input('village'); ?></td>
			</tr>
		</table>
		<hr />
		<table class="entry">
			<tr>
				<td>Serial number of the family:</td>
				<td><? display_input('family_serial_no'); ?></td>
			</tr>
			<tr>
				<td>Address:</td>
				<td><? display_input('address'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Males: <? display_input('num_males'); ?>, Females: <? display_input('num_females'); ?>, Children: <? display_input('num_children'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td align="center">Name</td>
				<td align="center">Status</td>
				<td align="center">Occupation</td>
				<td align="center">Income</td>
			</tr>
<?
 
for ($i = 0; $i < $num_members; $i++) {
	if (member_info_available($i)) {
		print "\t\t\t<tr>\n";
		print "\t\t\t\t<td>";
		display_input_element('name', $i);
		print "</td>\n";
		print "\t\t\t\t<td>";
		display_input_element_caption('status', $i);
		print "</td>\n";
		print "\t\t\t\t<td>";
		display_input_element('occupation', $i);
		print "</td>\n";
		print "\t\t\t\t<td>";
		display_input_element_money('income', $i);
		print "</td>\n";
		print "\t\t\t<tr>\n";
	}
}

?>
			<tr>
				<td colspan="3" align="right">Other income</td>
				<td align="right"><? display_input_money('other_income'); ?></td>
			</tr>
			<tr>
				<td colspan="3" align="right">Total income</td>
				<td align="right"><? display_input_money('total_income'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Property owned:</td>
				<td><? display_input('property_owned'); ?></td>
				<td>Property value:</td>
				<td><? display_input_money('property_value'); ?></td>
			</tr>
		</table>
		<hr />
		<table class="entry">
			<tr>
				<td>Current location:</td>
				<td><? display_input_caption('current_location'); ?></td>
				<td>Camp (if applicable):</td>
				<td><? display_input('current_camp'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>No of people eligible for relief:</td>
				<td>Adults:</td>
				<td><? display_input('relief_adults'); ?></td>
				<td>Children:</td>
				<td><? display_input('relief_children'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Probable period for which relief is necessary: <? display_input('relief_period'); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td>Remarks:</td>
				<td><? display_input('remarks', 3, 50); ?></td>
			</tr>
		</table>
		<table class="entry">
			<tr>
				<td align="right"><input type="submit" name="back" value=" Back " />
				<input type="submit" name="confirm" value=" Confirm " /></td>
			</tr>
		</table>
	</div>
<?

} // elseif ($screen == 'confirm')

?>
	</form>
<!--
<body>
</html>
-->

<?

function member_info_available($n)
{
	global $_SESSION;
	return ($_SESSION['form']['status'][$n] != 'unknown')
		|| ($_SESSION['form']['name'][$n] != '')
		|| ($_SESSION['form']['occupation'][$n] != '');
}

?>

