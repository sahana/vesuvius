<?
/**
 * @name         Vesuvius Theme
 * @version      3.0
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


global $global;
global $conf;

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

?>
<div id="header" class="clearfix">
	<a href="index.php"><img src="theme/vesuvius/img/pl.png"></a>
	<h1><a href="index.php"><?php
		echo _t(getLongName()." &lt;Family Reunification System&gt;");?>
	</a></h1>
	<h2>&lt;enter some text here&gt;<br>
	&lt;enter some more text here&gt;</h2>
	<?php
	if(isset($conf['enable_locale']) && $conf['enable_locale'] == true) {
		_shn_lc_lang_list();
	}
	?>
</div>
<?