<?

// This code works well, but very dirty :-(  What do do? A million records
// are arriving tomorrow, and this UI is going to be used to enter data.
// -- Anuradha

session_start();
require('forms.php');
require('db.php');

// Change this to the data entry URI
// It NEEDS at least one (even dummy) get parameter
$entry_url = 'http://127.0.0.1/mambo/?d=1';

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

// Show 25 results per page by default
$page_size = isset($_GET['s']) ?  intval($_GET['s']) : 25;

// We are on the first page by default
$page = isset($_GET['p']) ?  intval($_GET['p']) : 1;

$skip = ($page - 1) * $page_size;

// Generic query
$query = "sahana_entities e join sahana_entity_types et on (e.entity_type = et.id) left join sahana_entity_relationships er on (e.id = er.entity_id) left join sahana_entity_relationship_types ert on (er.relation_type = ert.id) where et.name = 'person' and (ert.name is NULL or ert.name = 'family member')";

echo '<div align="center">';
// First count the list
$query_count = "select count(*) from $query";
$rows = mysql_query($query_count);
$row = mysql_fetch_array($rows) or die('Database error!');
$num_results = $row[0];
print $num_results . ' matches found.<br>';

$bar = page_bar($page_size, $page, 'list.php', $num_results);
print $bar;

$query_real = "select e.id as id, er.related_id as relation from $query order by e.id $order limit $skip, $page_size";
$rows = mysql_query($query_real);
print '<table width="95%" cellpadding="3" cellspacing="1" border="0">';
print '<tr>';
print '<th bgcolor="#336699"><font color="#ffffff">Name</font></th>';
print '<th bgcolor="#336699"><font color="#ffffff">Age</font></th>';
print '<th bgcolor="#336699"><font color="#ffffff">Gender</font></th>';
print '<th bgcolor="#336699"><font color="#ffffff">Status</font></th>';
print '<th bgcolor="#336699"><font color="#ffffff">Family</font></th>';
print '</tr>';
while ($row = mysql_fetch_array($rows)) {
	print '<tr>';

	print '<td bgcolor="#dddddd">';
	$person = get_person_info($row[0]);
	print '<a href="/mambo/index.php?option=com_report&type=entity&entity=' . $row[0] . '">' . ($person['name'] ? $person['name'] : 'Unknown') . '</a>';
	print '</td>';

	print '<td bgcolor="#dddddd">';
	print $person['age'];
	print '</td>';

	print '<td bgcolor="#dddddd">';
	print $person['gender'];
	print '</td>';

	print '<td bgcolor="#dddddd">';
	print $person['status'];
	print '</td>';

	print '<td bgcolor="#dddddd">';
	print $row[1] ? '<a href="' . $entry_url . '&amp;edit=1&amp;f=' .
		$row[1] . '">Edit</a>' : '&nbsp;';
	print '</td>';
	print '</tr>';
}
print "</table>\n";

print $bar;

echo '</div>';

?>

<body>
</html>

<?
function get_person_info($entity_id)
{
	$person = array();
	$person['name'] = get_string_attribute_by_entity($entity_id, 'name');
	$person['age'] = get_integer_attribute_by_entity($entity_id, 'name');
	$person['gender'] = get_option_attribute_caption_by_entity($entity_id, 'gender');
	$person['status'] = get_option_attribute_caption_by_entity($entity_id, 'status');
	return $person;
}

function page_bar($page_size, $page_id, $url, $num_results,
	$num_pages = 5, $target = '', $show_range = 0)
{
   	if ($target) {
		$target = " target=\"$target\"";
	}
   	$pgbit = ereg("\?", $url) > 0 ? '&p':'?p';
   	$page_start = $page_size * ($page_id - 1);
	$page_end = $page_start + $page_size;

	if ($page_start > $num_results - 1) {
	   	return '';
   	}
	if ($page_end >= $num_results) $page_end = $num_results;

	$page_str = '';
	$num_showpages = ceil($num_results / $page_size);
	$start_page = $page_id > $num_pages ? $page_id - $num_pages : 1;
	for ($i = $start_page; $i <= $num_showpages; $i++) {
		if ($i > $page_id + $num_pages) break;
	   	if ($show_range) {
		   	$st = ($i - 1) * $page_size;
			$en = $st + $page_size;
			$st++;
			if ($page_id == $i)
				$page_str .= "$st - $en | ";
			else
				$page_str .= "<a href=\"$url$pgbit=$i\"$target>$st - $en</a> |";
		}
		else{
			if ($page_id == $i)
				$page_str.="<font color=#BB0000>$i</font> | ";
			
			else $page_str.="<a href=\"$url$pgbit=$i\"$target>$i</a> | ";
		}#if($show_range)
	}
	//Build next and previous links
	if ($page_id < $num_showpages)
		$page_str.="<a href=\"$url$pgbit=".($page_id+1)."\"$target>next &gt;</a> | ";
	if ($page_id > 1)
		$page_str = "<a href=\"$url$pgbit=".($page_id-1)."\"$target>&lt; prev</a> | " . $page_str;
	$page_str = substr($page_str, 0, strlen($page_str) - 2);
	#Apply css style
	$page_str = "<font class='small'>$page_str</font>";
	return $page_str;
}

?>

