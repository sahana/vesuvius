<?

// This code works well, but very dirty :-(  What do do? A million records
// are arriving tomorrow, and this UI is going to be used to enter data.
// -- Anuradha

session_start();
require('forms.php');
require('db.php');

?>
<html>
<head>
	<title>Displaced Persons Data Entry</title>
</head>
<body bgcolor="#ffffff">

<?
// Connect to DB running locally
$dbh = mysql_connect('localhost', 'apache', 'abcd321')
	or die('Could not connect: ' . mysql_error());
mysql_select_db('mambo') or die('Could not select database');

// Descending order by default
$order = isset($_GET['o']) && $_GET['o'] == 'a' ? 'asc' : 'desc';

// Show first page by default
$skip = isset($_GET['s']) ?  intval($_GET['s']) : 0;

// Skip 25 pages by default
$page = isset($_GET['p']) ?  intval($_GET['p']) : 25;

// Generic query
$query = "sahana_entities e join sahana_entity_types et on (e.entity_type = et.id) left join sahana_entity_relationships er on (e.id = er.entity_id) left join sahana_entity_relationship_types ert on (er.relation_type = ert.id) where et.name = 'person' and (ert.name is NULL or ert.name = 'family member')";

// First count the list
$query_count = "select count(*) from $query";
$rows = mysql_query($query_count);
$row = mysql_fetch_array($rows) or die('Database error!');
print $row[0] . ' matches found.';

$query_real = "select e.id as id, ert.name as relation from $query order by e.id $order limit $skip, $page";
$rows = mysql_query($query_real);
print '<table cellpadding="3" cellspacing="1" border="0">';
print '<tr>';
print '<th bgcolor="#336699"><font color="#ffffff">Name</font></th>';
print '<th bgcolor="#336699"><font color="#ffffff">Family</font></th>';
print '</tr>';
while ($row = mysql_fetch_array($rows)) {
	print '<tr>';
	print '<td bgcolor="#dddddd">';
	$person = get_person_info($row[0]);
	print '<a href="/mambo/index.php?option=com_report&type=entity&entity=' . $row[0] . '">' . $person['name'] . '</a>';
	print '</td>';
	print '<td bgcolor="#dddddd">';
	print $row[1] ? 'have family' : '&nbsp;';
	print '</td>';
	print '</tr>';
}
print "</table>\n";

?>

<body>
</html>

<?
function get_person_info($entity_id)
{
	$person = array();
	$person['name'] = get_string_attribute_by_entity($entity_id, 'name');
	return $person;
}

?>

