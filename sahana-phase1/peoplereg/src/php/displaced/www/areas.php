<script language="javascript">

function load_gs_division_list()
{
	var iframeObj = parent.document.getElementById('gs_division_frame');
	var division = parent.document.getElementById('division');
	var select_box = document.getElementById('division0')
	var division0 = select_box.options[select_box.selectedIndex].value;

	if (iframeObj.contentDocument) {
		// For NS6
		iframedoc = iframeObj.contentDocument;
	} else if (iframeObj.contentWindow) {
		// For IE5.5 and IE6
		iframedoc = iframeObj.contentWindow.document;
	} else if (iframeObj.document) {
		// For IE5
		iframedoc = iframeObj.document;
	} else {
		return;
	}
    iframedoc.location.replace('/peoplereg/displaced/areas.php?t=g&d=' + division0);
	division.value = division0;
}

function set_gs_division()
{
	var gs_division = parent.document.getElementById('gs_division');
	var select_box = document.getElementById('gs_division0');
	gs_division.value = select_box.options[select_box.selectedIndex].value;
}

</script>
<?
$dbh = mysql_connect('localhost', 'apache', 'abcd321')
	or die('Could not connect: ' . mysql_error());
mysql_select_db('mambo') or die('Could not select database');

if ($_GET['t'] == 'd') {
	$type = 'District';
	if ($_GET['d'] == 'nuwaraeliya')
		$parent = 'Nuwara Eliya';
	else
		$parent = ucfirst($_GET['d']);
	echo '<select id="division0" name="division0" onLoad="load_gs_division_list();" onChange="load_gs_division_list();">' . "\n";
}
elseif ($_GET['t'] == 'g') {
	$type = 'Division';
	$parent = $_GET['d'];
	echo '<select id="gs_division0" name="gs_division0" onChange="set_gs_division();">' . "\n";
}

$default = isset($_GET['s']) ? $_GET['s'] : '';

$rows = mysql_query("select l.name from sahana_locations l, sahana_locations lp, sahana_location_types lt where lt.name = '$type' and lt.id = lp.location_type and lp.name = '$parent' and l.parent = lp.id order by l.name");
while ($row = mysql_fetch_array($rows)) {
	echo '<option value="' . $row[0] . '"';
	if ($row[0] == $default) echo ' selected';
	echo '> ' . $row[0] . "\n";
}

echo '</select>' . "\n";

?>
