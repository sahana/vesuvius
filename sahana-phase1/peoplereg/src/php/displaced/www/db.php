<?

/* This code works well, but very dirty :-(  What do do? A million records
   are arriving tomorrow, and this UI is going to be used to enter data.
   -- Anuradha */

function get_caption($attribute, $option)
{
	$rows = mysql_query("select o.caption from sahana_attributes a, sahana_attribute_options o where a.name = '$attribute' and a.id = o.attribute_id and o.name='$option'");
	return ($row = mysql_fetch_array($rows)) ?  $row[0] : 'Unknown';
}

function new_family()
{
	return new_entity('family');
}

function new_person()
{
	return new_entity('person');
}

function new_entity($type)
{
	mysql_query("insert into sahana_entities (entity_type) select id from sahana_entity_types where name = '$type'")
		or die('Database error');
	$rows = mysql_query('select last_insert_id()')
		or die('Database error');
	if ($row = mysql_fetch_array($rows)) return $row[0];
	die('Database error');
}

function new_report()
{
	// FIXME: get validity by looking at the UID
	//$validity = $my->id ? 1 : 0;
	$validity = 0;
	$date = date('Y-m-d H:i:s');
	$uid = 0;
	mysql_query("insert into sahana_reports (user_id, dtime, validity) values ($uid, '$date', $validity)")
		or die('Database error');
	$rows = mysql_query('select last_insert_id()')
		or die('Database error');
	if ($row = mysql_fetch_array($rows)) return $row[0];
	die('Database error');
}

function store_attribute_string($report, $entity, $attribute, $index = 0, $n = -1)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$attribute])
			&& ($_SESSION['form'][$attribute] != 'unknown')
			&& ($_SESSION['form'][$attribute] != '')) {
		$value = trim(($n < 0) ? $_SESSION['form'][$attribute] : $_SESSION['form'][$attribute][$n]); // FIXME: escape special characters
		mysql_query("insert into sahana_attribute_values (report_id, entity, attribute_id, value_string) select $report, $entity, id, '$value' from sahana_attributes where name='$attribute'");
	}
	// Do indexing if $index is set
	_indexAttribute($value, $entity, get_attribute_id($attribute));
}

function store_attribute_integer($report, $entity, $attribute, $n = -1)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$attribute])) {
		$value = intval(trim(($n < 0) ? $_SESSION['form'][$attribute] : $_SESSION['form'][$attribute][$n]));
		mysql_query("insert into sahana_attribute_values (report_id, entity, attribute_id, value_int) select $report, $entity, id, $value from sahana_attributes where name='$attribute'");
	}
}

function store_attribute_selection($report, $entity, $attribute, $n = -1)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$attribute])
			&& ($_SESSION['form'][$attribute] != 'unknown')
			&& ($_SESSION['form'][$attribute] != '')) {
		$value = trim(($n < 0) ? $_SESSION['form'][$attribute] : $_SESSION['form'][$attribute][$n]); // FIXME: escape special characters
		mysql_query("insert into sahana_attribute_values (report_id, entity, attribute_id, value_int) select $report, $entity, a.id, o.id from sahana_attributes a, sahana_attribute_options o where a.name = '$attribute' and a.id = o.attribute_id and o.name = '$value'");
	}
}

function add_relation($entity, $related, $relation)
{
	mysql_query("insert into sahana_entity_relationships (entity_id, related_id, relation_type) select $entity, $related, id from sahana_entity_relationship_types where name = '$relation'");
}

function get_attribute_id($attribute)
{
	$rows = mysql_query("select id from sahana_attributes where name='$attribute'");
	return ($row = mysql_fetch_array($rows)) ?  $row[0] : 0;
}

function get_string_attribute_by_entity($entity_id, $attribute)
{
	$rows = mysql_query("select v.value_string from sahana_attribute_values v, sahana_attributes a where a.name = '$attribute' and v.entity = $entity_id and a.id = v.attribute_id limit 1");
	return ($row = mysql_fetch_array($rows)) ?  $row[0] : 0;
}

function get_integer_attribute_by_entity($entity_id, $attribute)
{
	$rows = mysql_query("select v.value_int from sahana_attribute_values v, sahana_attributes a where a.name = '$attribute' and v.entity = $entity_id and a.id = v.attribute_id limit 1");
	return ($row = mysql_fetch_array($rows)) ?  $row[0] : 0;
}

?>
