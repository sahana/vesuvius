<?

/* This code works well, but very dirty :-(  What do do? A million records
   are arriving tomorrow, and this UI is going to be used to enter data.
   -- Anuradha */

function clear_form()
{
	global $_SESSION;
	unset($_SESSION['form']);
}

function show_input_text($name, $size = 0, $js ="")
{
	global $_SESSION;

	echo '<input type="text" name="' . $name . '"';
	if (isset($_SESSION['form'][$name]))
		echo ' value="' . $_SESSION['form'][$name] . '"';
	if ($size)
		echo ' size="' . $size . '"';
	if ($js)
		echo " $js";	
	echo ' />';
}

function show_input_textarea($name, $rows, $cols)
{
	global $_SESSION;

	echo '<textarea name="' . $name . '" rows="' . $rows . '" cols="' . $cols . '">';
	if (isset($_SESSION['form'][$name]))
		echo $_SESSION['form'][$name];
	echo '</textarea>';
}

function show_input_select($dbh, $name)
{
	global $_SESSION;
	$value = '';

	echo '<select name="' . $name . '">';
	$value = isset($_SESSION['form'][$name]) ? $_SESSION['form'][$name] : '';
	$name_sql = ereg_replace('\[.*\]', '', $name);

	$rows = mysql_query("select o.id as id, o.name as name, o.caption as caption from sahana_attribute_options o, sahana_attributes a where a.name='$name_sql' and a.id = o.attribute_id order by id");

	while ($row = mysql_fetch_array($rows)) {
		echo '<option value="' . $row[1] . '"';
		if ($row[1] == $value) echo ' selected';
		echo '>' . $row[2] . '</option>';
	}
	echo '</select>';
}

function capture_input_string($name)
{
	global $_POST;
	global $_SESSION;

	if (!isset($_SESSION['form'])) $_SESSION['form'] = array();

	if (isset($_POST[$name]))
		$_SESSION['form'][$name] = trim($_POST[$name]);
	else
		unset($_SESSION['form'][$name]);
}

function capture_input_element_string($name, $n)
{
	global $_POST;
	global $_SESSION;

	if (!isset($_SESSION['form'])) $_SESSION['form'] = array();

	if (isset($_POST[$name][$n]))
		$_SESSION['form'][$name][$n] = trim($_POST[$name][$n]);
	else
		unset($_SESSION['form'][$name][$n]);
}

function capture_input_image($name)
{
	global $_FILES;
	global $_SESSION;

	if (!isset($_SESSION['form'])) $_SESSION['form'] = array();
	if (!isset($_FILES[$name])) {
		unset($_SESSION['form'][$name]);
		return;
	}
	if ($_FILES[$name]['error'] != 0) {
		unset($_SESSION['form'][$name]);
		return;
	}

	// Right now, file type has to JPG, GIF, PNG or BMP

	$type = strtolower($_FILES[$name]['type']);

	if ($type != 'image/jpeg')
		$ext = 'jpg';
	elseif ($type != 'image/png')
		$ext = 'png';
	elseif ($type != 'image/gif')
		$ext = 'gif';
	elseif ($type != 'image/bmp')
		$ext = 'bmp';
	else {
		unset($_SESSION['form'][$name]);
		return;
	}

	$tmp = tempnam('/var/www/mambo/uploads', 'img');
	move_uploaded_file($_FILES[$name]['tmp_name'], $tmp);

	$full_name = "$tmp.$ext";
	link($tmp, $full_name);

	$filename = substr(strrchr($full_name, '/'), 1);
	$_SESSION['form'][$name] = $filename;
}

function capture_input_int($name)
{
	global $_POST;
	global $_SESSION;

	if (!isset($_SESSION['form'])) $_SESSION['form'] = array();

	if (isset($_POST[$name]))
		$_SESSION['form'][$name] = intval(trim($_POST[$name]));
	else
		unset($_SESSION['form'][$name]);
}

function capture_input_element_int($name, $n)
{
	global $_POST;
	global $_SESSION;

	if (!isset($_SESSION['form'])) $_SESSION['form'] = array();

	if (isset($_POST[$name][$n]))
		$_SESSION['form'][$name][$n] = intval(trim($_POST[$name][$n]));
	else
		unset($_SESSION['form'][$name][$n]);
}

function input_is_set($name)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$name]))
		return ($_SESSION['form'][$name] == 'unknown') || ($_SESSION['form'][$name] == '') ? false : true;
	return false;
}

function display_input($name)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$name]))
		echo $_SESSION['form'][$name];
}

function display_input_element($name, $n)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$name][$n]))
		echo $_SESSION['form'][$name][$n];
}

function display_input_caption($name)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$name]))
		echo get_caption($name, $_SESSION['form'][$name]);
}

function display_input_element_caption($name, $n)
{
	global $_SESSION;

	if (isset($_SESSION['form'][$name][$n]))
		echo get_caption($name, $_SESSION['form'][$name][$n]);
}

?>

