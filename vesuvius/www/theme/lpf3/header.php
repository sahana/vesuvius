<?
/**
 * @name         Lost Person Finder Theme
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

$date = "";

// get incident specific information for the header

$short = mysql_real_escape_string($_GET['shortname']);
$long = "";
$sql = "
	SELECT *
	FROM incident
	WHERE `shortname` = '".$short."'
	LIMIT 1;
";
$arr = $global['db']->GetAll($sql);
if (!empty($arr)) {
	foreach($arr as $row) {
		$long = $row['name'];
		$date = $row['date'];
	}
	// fix date
	$date = date("F j, Y", strtotime($row["date"]));
}


echo '
	<div id="header" class="clearfix">
		<a href="index.php"><img src="theme/lpf3/img/pl.png"></a>
';
if(isset($conf['enable_locale']) && $conf['enable_locale'] == true) {
	_shn_lc_lang_list();
}
echo '</div>';

echo '
	<div id="headerText">
		<h1><a href="index.php">'._t("People Locator").'</a></h1>
		<h2><a href="index.php"><span>'._t('for the ').'</span>'.$long.'</a></h1>
		<h3><a href="index.php">'._t("of").' '.$date.'</a></h2>
		<h4><a href="index.php">'._t("U.S. National Library of Medicine").'</a></h2>
		<h4><a href="index.php">'._t("Lister Hill National Center for Biomedical Communications").'</a></h2>
	</div>
';

// end theme header