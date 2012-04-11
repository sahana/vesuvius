<?
/**
 * @name         TriagePic
 * @version      14
 * @package      tp
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


global $tabid;
$tabid = isset($_GET['tabid']) ? $_GET['tabid'] : 0;
$tabid = "&tabid=".$tabid;


function shn_tp_default() {

	global $global;

	$control = "";

	shn_tabmenu_open();
	shn_tabmenu_item("overview",  _t("Overview"),           "triagepic");
	shn_tabmenu_item("download",  _t("Download"),           "triagepic");
	shn_tabmenu_item("notes2011", _t("Release Notes 2011"), "triagepic");
	shn_tabmenu_item("notes2012", _t("Release Notes 2012"), "triagepic");
	shn_tabmenu_close();

	if(isset($_GET['overview'])) {
		$control = "shn_tp_page";
		$page = -50;

	} elseif(isset($_GET['download'])) {
		$control = "shn_tp_download";

	} elseif(isset($_GET['notes2011'])) {
		$control = "shn_tp_page";
		$page = -51;

	} elseif(isset($_GET['notes2012'])) {
		$control = "shn_tp_page";
		$page = -53;
	}
	if($control == "") {
		$control = "shn_tp_page";
		$page = -50;
	}

	$control($page);
}
/*
	// overview
	if(!isset($_GET['page_id']) || (isset($_GET['page_id']) && $_GET['page_id'] == "-50")) {
		shn_tp_page(-50);
	// download
	} else if($_GET['page_id'] == "-52") {
		shn_tp_download();
	// release notes 2012
	} else if($_GET['page_id'] == "-53") {
		shn_tp_page(-53);
	// release notes 2011
	} else if($_GET['page_id'] == "-51") {
		shn_tp_page(-51);
	// default to overview
	} else {
		shn_tp_page(-50);
	}
*/


/** Download Section */
function shn_tp_download() {

	global $global;

	//$intPath = getcwd()."/tmp/triagepic_cache/";
	//$intPathReal = realpath($intPath);

	$extPath = getcwd()."/tmp/triagepic_cache_ext/";
	$extPathReal = realpath($extPath);

	$border = "style=\"border: none;\"";
	$show = false;

/*
	if(file_exists($intPathReal)) {
		echo "<span style=\"color: red;\"><b>RED = Internal</b> /triagepic_cache</span> ";
		echo "
			<iframe src =\"tmp/triagepic_cache/publish.htm\" width=\"100%\" height=\"470\" style=\"border: 1px solid red;\">
			<p>Your browser does not support iframes.</p>
			</iframe>
		";
		$border = "style=\"border: 1px solid green;\"";
		echo "<br><br><span style=\"color: green;\"><b>GREEN = External</b> /triagepic_cache_ext</span>";
		$show = true;
	}
*/
	if(file_exists($extPathReal)) {
		echo "
			<br>
			<iframe src =\"tmp/triagepic_cache_ext/publish.htm\" width=\"100%\" height=\"470\" ".$border.">
			<p>Your browser does not support iframes.</p>
			</iframe>
		";
	} else {
		echo "
			<br>
			Please contact a site administrator as the tp_cache folder is missing.
		";
	}
}




/** Displays the proper tp page */
function shn_tp_page($page = -50) {

	global $global;

	// get page info
	$page = intval(mysql_real_escape_string($page));
	$q = "select * from rez_pages where rez_page_id = '".$page."';";
	$res = $global['db']->Execute($q);

	if ($row = $res->FetchRow() ){
		echo "<br>".$row['rez_content'];
	} else {
		// page doesn't exist
		echo "<br><h2>Error 404 ~ Page not found.</h2>";
	}
}



