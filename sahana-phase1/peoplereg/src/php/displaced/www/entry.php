<?

/* This code works well, but very dirty :-(  What do do? A million records
   are arriving tomorrow, and this UI is going to be used to enter data.
   -- Anuradha */

session_start();
require('forms.php');
require('db.php');
?>
<html>
<head>
<title>Enter displaced persons</title>
<link href="entry.css" rel="stylesheet" type="text/css" /> 
</head>

<body>

<form action="entry.php" method="post">

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

		capture_input_int('family_no');
		capture_input_int('num_males');
		capture_input_int('num_females');
		capture_input_int('num_children');

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
<td>Serial number of family:</td>
<td><? display_input('family_no'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Males:</td>
<td><? display_input('num_males'); ?></td>
<td>Females:</td>
<td><? display_input('num_females'); ?></td>
<td>Children:</td>
<td><? display_input('num_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">

<tr>
<td>Name</td>
<td>Status</td>
<td>Occupation</td>
<td>Income</td>
</tr>

<tr>
<td><? display_input('name[0]'); ?></td>
<td><? display_input_caption('status[0]'); ?></td>
<td><? display_input('occupation[0]'); ?></td>
<td><? display_input('income[0]'); ?></td>
</tr>

<tr>
<td><? display_input('name[1]'); ?></td>
<td><? display_input_caption('status[1]'); ?></td>
<td><? display_input('occupation[1]'); ?></td>
<td><? display_input('income[1]'); ?></td>
</tr>

<tr>
<td><? display_input('name[2]'); ?></td>
<td><? display_input_caption('status[2]'); ?></td>
<td><? display_input('occupation[2]'); ?></td>
<td><? display_input('income[2]'); ?></td>
</tr>

<tr>
<td><? display_input('name[3]'); ?></td>
<td><? display_input_caption('status[3]'); ?></td>
<td><? display_input('occupation[3]'); ?></td>
<td><? display_input('income[3]'); ?></td>
</tr>

<tr>
<td><? display_input('name[4]'); ?></td>
<td><? display_input_caption('status[4]'); ?></td>
<td><? display_input('occupation[4]'); ?></td>
<td><? display_input('income[4]'); ?></td>
</tr>

<tr>
<td><? display_input('name[5]'); ?></td>
<td><? display_input_caption('status[5]'); ?></td>
<td><? display_input('occupation[5]'); ?></td>
<td><? display_input('income[5]'); ?></td>
</tr>

<tr>
<td><? display_input('name[6]'); ?></td>
<td><? display_input_caption('status[6]'); ?></td>
<td><? display_input('occupation[6]'); ?></td>
<td><? display_input('income[6]'); ?></td>
</tr>

<tr>
<td><? display_input('name[7]'); ?></td>
<td><? display_input_caption('status[7]'); ?></td>
<td><? display_input('occupation[7]'); ?></td>
<td><? display_input('income[7]'); ?></td>
</tr>

<tr>
<td><? display_input('name[8]'); ?></td>
<td><? display_input_caption('status[8]'); ?></td>
<td><? display_input('occupation[8]'); ?></td>
<td><? display_input('income[8]'); ?></td>
</tr>

<tr>
<td><? display_input('name[9]'); ?></td>
<td><? display_input_caption('status[9]'); ?></td>
<td><? display_input('occupation[9]'); ?></td>
<td><? display_input('income[9]'); ?></td>
</tr>

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

<form action="entry.php" method="post">

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
<td>Serial number of family:</td>
<td><? show_input_text('family_no'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Males:</td>
<td><? show_input_text('num_males'); ?></td>
<td>Females:</td>
<td><? show_input_text('num_females'); ?></td>
<td>Children:</td>
<td><? show_input_text('num_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">

<tr>
<td>Name</td>
<td>Status</td>
<td>Occupation</td>
<td>Income</td>
</tr>

<tr>
<td><? show_input_text('name[0]'); ?></td>
<td><? show_input_select($dbh, 'status[0]'); ?></td>
<td><? show_input_text('occupation[0]'); ?></td>
<td><? show_input_text('income[0]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[1]'); ?></td>
<td><? show_input_select($dbh, 'status[1]'); ?></td>
<td><? show_input_text('occupation[1]'); ?></td>
<td><? show_input_text('income[1]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[2]'); ?></td>
<td><? show_input_select($dbh, 'status[2]'); ?></td>
<td><? show_input_text('occupation[2]'); ?></td>
<td><? show_input_text('income[2]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[3]'); ?></td>
<td><? show_input_select($dbh, 'status[3]'); ?></td>
<td><? show_input_text('occupation[3]'); ?></td>
<td><? show_input_text('income[3]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[4]'); ?></td>
<td><? show_input_select($dbh, 'status[4]'); ?></td>
<td><? show_input_text('occupation[4]'); ?></td>
<td><? show_input_text('income[4]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[5]'); ?></td>
<td><? show_input_select($dbh, 'status[5]'); ?></td>
<td><? show_input_text('occupation[5]'); ?></td>
<td><? show_input_text('income[5]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[6]'); ?></td>
<td><? show_input_select($dbh, 'status[6]'); ?></td>
<td><? show_input_text('occupation[6]'); ?></td>
<td><? show_input_text('income[6]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[7]'); ?></td>
<td><? show_input_select($dbh, 'status[7]'); ?></td>
<td><? show_input_text('occupation[7]'); ?></td>
<td><? show_input_text('income[7]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[8]'); ?></td>
<td><? show_input_select($dbh, 'status[8]'); ?></td>
<td><? show_input_text('occupation[8]'); ?></td>
<td><? show_input_text('income[8]'); ?></td>
</tr>

<tr>
<td><? show_input_text('name[9]'); ?></td>
<td><? show_input_select($dbh, 'status[9]'); ?></td>
<td><? show_input_text('occupation[9]'); ?></td>
<td><? show_input_text('income[9]'); ?></td>
</tr>

<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>Other income</td>
<td><? show_input_text('other_income'); ?></td>
</tr>

<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>Total income</td>
<td><? show_input_text('total_income'); ?></td>
</tr>

</table>
</div>

<hr />

<div align="center">
<table class="entry">
<tr>
<td>Current location:</td>
<td><? show_input_text('location'); ?></td>
<td>Camp (if applicable):</td>
<td><? show_input_text('camp'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>No of people eligible for relief:</td>
<td>Adults:</td>
<td><? show_input_text('relief_adults'); ?></td>
<td>Children:</td>
<td><? show_input_text('relief_children'); ?></td>
</tr>
</table>
</div>

<div align="center">
<table class="entry">
<tr>
<td>Probable period for which relief is necessary:</td>
<td><? show_input_text('relief_period'); ?></td>
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

