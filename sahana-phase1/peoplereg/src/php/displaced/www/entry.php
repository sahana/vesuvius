<?

/* This code works well, but very dirty :-(  What do do? A million records
   are arriving tomorrow, and this UI is going to be used to enter data.
   -- Anuradha */

session_start();
require('forms.php');
require('db.php');

$num_members = 10; /* FIXME: get rid of the static value */

?>
<html>
<head>
<title>Enter displaced persons</title>
<link href="entry.css" rel="stylesheet" type="text/css" /> 
</head>

<body>

<form action="entry.php" method="post">

<input type="hidden" name="num_members" value="10" />

<?

$dbh = mysql_connect('localhost', 'apache', 'abcd321')
   or die('Could not connect: ' . mysql_error());

mysql_select_db('mambo') or die('Could not select database');

$screen = 'entry';

if ($_POST) {
	if ($_POST['back']) {
		$screen = 'entry';
	}
	elseif ($_POST['submit']) {
		capture_input_string('district');
		capture_input_string('division');
		capture_input_string('grama');
		capture_input_string('village');

		capture_input_int('family_serial_no');
		capture_input_int('num_males');
		capture_input_int('num_females');
		capture_input_int('num_children');

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

		capture_input_int('relief_adults');
		capture_input_int('relief_children');

		capture_input_string('relief_period');
		capture_input_string('remarks');

		$screen = 'confirm';
	}
}

if ($screen == 'confirm') {

?>

<h2>Confirmation Form</h2>

<hr />

<div align="center">
<table class="entry">
<tr>
  <td>District:</td>
  <td><? display_input_caption('district'); ?></td>
  <td>Divisional secretariat:</td>
  <td><? display_input('division'); ?></td>
</tr>
<tr>
  <td>Grama Niladhari's Division:</td>
  <td><? display_input('grama'); ?></td>
  <td>Village:</td>
  <td><? display_input('village'); ?></td>
</tr>

</table>
</div>

<hr />

<div align="center">
<table class="entry">
<tr>
<td>Serial number of the family: <? display_input('family_serial_no'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Males: <? display_input('num_males'); ?>, Females: <? display_input('num_females'); ?>, Children: <? display_input('num_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
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
		print '<tr><td>';
		display_input_element('name', $i);
		print '</td><td>';
		display_input_element_caption('status', $i);
		print '</td><td>';
		display_input_element('occupation', $i);
		print '</td><td align="right">';
		display_input_element('income', $i);
		print '</td></tr>';
	}
}
?>

<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>Other income</td>
<td><? display_input('other_income'); ?></td>
</tr>

<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>Total income</td>
<td><? display_input('total_income'); ?></td>
</tr>

</table>
</div>

<hr />

<div align="center">
<table class="entry">
<tr>
<td>Current location:</td>
<td><? display_input('location'); ?></td>
<td>Camp (if applicable):</td>
<td><? display_input('camp'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>No of people eligible for relief:</td>
<td>Adults:</td>
<td><? display_input('relief_adults'); ?></td>
<td>Children:</td>
<td><? display_input('relief_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Probable period for which relief is necessary:</td>
<td><? display_input('relief_period'); ?></td>
</tr>
</table>
</div>


<div align="center">
<table class="entry">
<tr>
<td>Remarks:</td>
<td><? display_input('remarks', 3, 50); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td align="right"><input type="submit" name="back" value=" Back " />
<input type="submit" name="confirm" value=" Confirm " /></td>
</tr>
</table>
</div>


<?

}
else {

?>

<h2>Family Details Entry Form</h2>

<hr />

<div align="center">
<table class="entry">
<tr>
  <td>District:</td>
  <td><? show_input_select($dbh, 'district'); ?></td>
  <td>Divisional secretariat:</td>
  <td><? show_input_text('division'); ?></td>
</tr>
<tr>
  <td>Grama Niladhari's Division:</td>
  <td><? show_input_text('grama'); ?></td>
  <td>Village:</td>
  <td><? show_input_text('village'); ?></td>
</tr>

</table>
</div>

<hr />

<div align="center">
<table class="entry">
<tr>
<td>Serial number of the family: <? show_input_text('family_serial_no'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Males: <? show_input_text('num_males'); ?></td>
<td>Females: <? show_input_text('num_females'); ?></td>
<td>Children: <? show_input_text('num_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">

<tr>
<td align="center">Name</td>
<td align="center">Status</td>
<td align="center">Occupation</td>
<td align="center">Income</td>
</tr>

<?
for ($i = 0; $i < $num_members; $i++) {
?>

<tr>
<td align="center"><? show_input_text('name[]', 50); ?></td>
<td align="center"><? show_input_select($dbh, 'status[]'); ?></td>
<td align="center"><? show_input_text('occupation[]'); ?></td>
<td align="center"><? show_input_text('income[]'); ?></td>
</tr>

<?
}
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
</div>

<div align="center">
<table class="entry">
<tr>
<td valign="middle">Property owned:</td><td><? show_input_textarea('property_owned', 3, 50); ?></td>
<td valign="middle">Value (Rs): <? show_input_text('property_value'); ?></td>
</tr>
</table>
</div>

<hr />

<div align="center">
<table class="entry">
<tr>
<td>Current location: <? show_input_text('location'); ?></td>
<td>Camp (if applicable): <? show_input_text('camp'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>No of people eligible for relief:</td>
<td>Adults: <? show_input_text('relief_adults'); ?></td>
<td>Children: <? show_input_text('relief_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Probable period for which relief is necessary: <? show_input_text('relief_period'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Remarks:</td>
<td><? show_input_textarea('remarks', 3, 50); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td align="right"><input type="submit" name="submit" value=" Submit " /></td>
</tr>
</table>
</div>

<?
}
?>

</form>

<body>
</html>

<?
function member_info_available($n)
{
	global $_SESSION;
	return ($_SESSION['form']['status'][$n] != 'unknown')
		|| ($_SESSION['form']['name'][$n] != '')
		|| ($_SESSION['form']['occupation'][$n] != '');
}

?>

