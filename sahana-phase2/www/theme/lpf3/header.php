<?php
/**
 * Lost Person Finder v3 Theme HTML header
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 */
?>
<div id="header" class="clearfix">
	<h1><?php 
		echo _t(getLongName()." Person Locator");?>
	</h1>
	<h2>A beta project of the U.S. National Library of Medicine<br>
	Lister Hill National Center for Biomedical Communications</h2>
	<?php 
	if(file_exists($global['approot'].'conf/sysconf.inc.php')) {
		_shn_lc_lang_list(); 
	}
	?>
</div>
<?

// Get the Long Name of the incident
function getLongName() {
	global $global;
	global $conf;

	$short = mysql_real_escape_string($_GET['shortname']);

	$long = "";
	$sql = "SELECT name FROM incident WHERE `shortname` = '".$short."' LIMIT 1;";  
	$arr = $global['db']->GetAll($sql);
	if (!empty($arr)) {
		foreach($arr as $row) {
			$long = $row['name'];
		}
	}
	return $long;
}