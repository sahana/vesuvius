<?

/* This code works well, but very dirty :-(  What do do? A million records
   are arriving tomorrow, and this UI is going to be used to enter data.
   -- Anuradha */

function get_caption($attribute, $option)
{
	$rows = mysql_query("select o.caption from sahana_attributes a, sahana_attribute_options o where a.name = '$attribute' and a.id = o.attribute_id and o.name='$option'");
	return ($row = mysql_fetch_array($rows)) ?  $row[0] : 'Unknown';
}

?>
