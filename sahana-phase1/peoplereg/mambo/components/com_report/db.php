<?

function begin_transaction()
{
	global $database;
	$database->setQuery('begin work');
	$database->query();
}

function basic_search_by_term($term)
{
	global $database;
	$term = strtolower($term);
	$database->setQuery("select e.entity_id as entity_id from sahana_search_terms t, sahana_search_entities e where t.term = '$term' and t.id = e.term_id limit 50");
	return $database->loadResultArray();
}

function get_caption($attribute, $option)
{
	global $database;
	$database->setQuery("select o.caption from sahana_attributes a, sahana_attribute_options o where a.name = '$attribute' and a.id = o.attribute_id and o.name='$option'");
	return $database->loadResult() ? $database->loadResult() : 'Unknown';
}

function get_string_attribute_by_entity($entity, $attribute)
{
	global $database;
	$database->setQuery("select v.value_string from sahana_attribute_values v, sahana_attributes a where a.name = '$attribute' and v.entity = $entity and a.id = v.attribute_id limit 1");
	return $database->loadResult() ? $database->loadResult() : 'Unknown';
}

function get_integer_attribute_by_entity($entity, $attribute)
{
	global $database;
	$database->setQuery("select v.value_int from sahana_attribute_values v, sahana_attributes a where a.name = '$attribute' and v.entity = $entity and a.id = v.attribute_id limit 1");
	return $database->loadResult() ? $database->loadResult() : 'Unknown';
}

function get_option_attribute_by_entity($entity, $attribute)
{
	global $database;
	$database->setQuery("select o.caption from sahana_attribute_values v, sahana_attributes a, sahana_attribute_options o where a.name = '$attribute' and v.entity = $entity and a.id = v.attribute_id and v.value_int = o.id limit 1");
	return $database->loadResult() ? $database->loadResult() : 'Unknown';
}

function get_names_by_entity($entity)
{
	$name = get_string_attribute_by_entity($entity, 'name');
	if (!$name) $name = 'Name unknown';
	$other_names = get_string_attribute_by_entity($entity, 'other_names');
	return $other_names ? "$name ($other_names)" : $name;
}

function new_report()
{
	global $database;
	global $my;
	$validity = $my->id ? 1 : 0;
	$date = date('Y-m-d H:i:s');
	$database->setQuery('insert into sahana_reports (user_id, dtime, validity) values (' . $my->id . ", '" . $date . "', " . $validity . ')');
	$database->query();
	$database->setQuery('select last_insert_id()');
	return $database->loadResult();
}

function new_entity()
{
	global $database;
	$database->setQuery('insert into sahana_entities values ()');
	$database->query();
	$database->setQuery('select last_insert_id()');
	return $database->loadResult();
}

function index_string($entity, $string)
{
	global $database;

	$terms = explode(' ', strtolower(trim($string)));
	foreach ($terms as $term) {
		if (trim($term) == '') continue;
		$database->setQuery("select id from sahana_search_terms where term='$term'");
		$term_id = $database->loadResult();
		if ($term_id <= 0) {
			$database->setQuery("insert into sahana_search_terms (term) values ('$term')");
			$database->query();
			$database->setQuery("select id from sahana_search_terms where term='$term'");
			$term_id = $database->loadResult();
		}
		$database->setQuery("insert into sahana_search_entities (term_id, entity_id) values ($term_id, $entity)");
		$database->query();
	}

}

function store_string($report, $entity, $attribute, $index = 0)
{
	global $_SESSION;
	global $database;

	if (isset($_SESSION['form'][$attribute])
			&& ($_SESSION['form'][$attribute] != 'unknown')
			&& ($_SESSION['form'][$attribute] != '')) {
		$value = trim($_SESSION['form'][$attribute]); // FIXME: escape special characters
		$database->setQuery("insert into sahana_attribute_values (report_id, entity, attribute_id, value_string) select $report, $entity, id, '$value' from sahana_attributes where name='$attribute'");
		$database->query();
	}
	if ($index) index_string($entity, $value);
}

function store_integer($report, $entity, $attribute)
{
	global $_SESSION;
	global $database;

	if (isset($_SESSION['form'][$attribute])
			&& ($_SESSION['form'][$attribute] != 'unknown')
			&& ($_SESSION['form'][$attribute] != '')) {
		$value = intval(trim($_SESSION['form'][$attribute]));
		$database->setQuery("insert into sahana_attribute_values (report_id, entity, attribute_id, value_int) select $report, $entity, id, $value from sahana_attributes where name='$attribute'");
		$database->query();
	}
}

function store_selection($report, $entity, $attribute)
{
	global $_SESSION;
	global $database;

	if (isset($_SESSION['form'][$attribute])
			&& ($_SESSION['form'][$attribute] != 'unknown')
			&& ($_SESSION['form'][$attribute] != '')) {
		$value = trim($_SESSION['form'][$attribute]); // FIXME: escape special characters
		$database->setQuery("insert into sahana_attribute_values (report_id, entity, attribute_id, value_int) select $report, $entity, a.id, o.id from sahana_attributes a, sahana_attribute_options o where a.name = '$attribute' and a.id = o.attribute_id and o.name = '$value'");
		$database->query();
	}
	if ($index) index_string($entity, $value);
}

function commit_transaction()
{
	global $database;
	$database->setQuery('commit');
	$database->query();
}

?>
