<?
/**
 * @name         Lost Person Finder Theme
 * @version      3.5
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1005
 */


global $global;
global $conf;
require_once($global['approot'].'mod/lpf/lib_lpf.inc');
$full = false; // true when we show the full header...

// show image
echo '<div id="header" class="clearfix"><div id="leftHeaderLogo"><a href="'.makeBaseUrlMinusEvent().'"><img id="leftHeaderLogoImg" src="theme/lpf3/img/pl.png" alt="People Locator Logo"></a><sup id="suplogo" style="font-size: 120%; color: #34689A;">™</sup></div><div id="rightHeaderLogo"><a href="http://www.nlm.nih.gov/"><img src="theme/lpf3/img/NLMlogoSmall.gif" alt="United States National Library of Medicine Logo"></a></div>';

// show language selection if necessary...
if(isset($conf['enable_locale']) && $conf['enable_locale'] == true) {
	_shn_lc_lang_list();
}
echo '</div>';


// check if we have a shortname...
if(isset($_GET['shortname'])) {

	$date = "";
	$short = mysql_real_escape_string($_GET['shortname']);
	$long = "";
	$q = "
		SELECT *
		FROM incident
		WHERE `shortname` = '".$short."'
		LIMIT 1;
	";
	$arr = $global['db']->GetAll($q);

	// if the event shortname is valid....
	if(!empty($arr)) {

		foreach($arr as $row) {

			$long = $row['description'];
			$date = $row['date'];
		}
		// fix date
		$date = date("F j, Y", strtotime($row["date"]));

		// show the full event specific header...
		echo '
			<div id="headerText">
				<h1>'._t($conf['site_name']).' '.$long.'</h1>
				<h3>'._t("of").' '.$date.'</h3>
				<h4>'._t("U.S. National Library of Medicine").'</h4>
				<h4>'._t("Lister Hill National Center for Biomedical Communications").'</h4>
			</div>
		';
		$full = true;
	}
}

// ok, show the short header
if(!$full) {

	echo '
		<div id="headerText">
			<h1>'._t($conf['site_name']).'<sup>™</sup></h1>
			<h3>&nbsp;</h3>
			<h4>'._t("U.S. National Library of Medicine").'</h4>
			<h4>'._t("Lister Hill National Center for Biomedical Communications").'</h4>
		</div>
	';
}

/*
function isChrome() {
	return(stristr($_SERVER['HTTP_USER_AGENT'], "chrome"));
}

if(isChrome()) {
	echo "
		<div id=\"install-button\" style=\"z-index: 99999;\">
			<center><a href=\"#\" onclick=\"chrome.webstore.install(); console.log('clicked');\">Install the People Locator app to Chrome</a></center>
			<script>if(chrome.app.isInstalled) { document.getElementById('install-button').style.display = 'none'; }</script>
		</div>
	";
}
*/



