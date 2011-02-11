<?php
/**
 * TP Module
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module tp
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */



/**
 * Default Admin function 
 * 
 * @access public
 * @return void
 */
function shn_tp_default() {
	global $global;

	shn_tp_header2();

	// overview
	if(!isset($_GET['page_id']) || (isset($_GET['page_id']) && $_GET['page_id'] == "-50")) {
		shn_tp_page(-50);

	// download
	} else if($_GET['page_id'] == "-52") {
		shn_tp_download();

	// release notes
	} else if($_GET['page_id'] == "-51") {
		shn_tp_page(-51);

	// default to overview
	} else {
		shn_tp_page(-50);
	}
}



/**
 * Default Admin function 
 * 
 * @access public
 * @return void
 */
function shn_tp_download() {
	global $global;
	$intPath = getcwd()."/tmp/triagepic_cache/";
	$extPath = getcwd()."/tmp/triagepic_cache_ext/";
	$intPathReal = realpath($intPath);
	$extPathReal = realpath($extPath);
	$border = "style=\"border: none;\"";
	$show = false;
	
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
	if(file_exists($extPathReal)) {
		echo "
			<iframe src =\"tmp/triagepic_cache_ext/publish.htm\" width=\"100%\" height=\"470\" ".$border.">
			<p>Your browser does not support iframes.</p>
			</iframe>
		";
	}
}



// generate the TP module header
function shn_tp_header2() {
	global $global;

	echo "
		<ul>
	";

	// OVERVIEW PAGE
	if(!isset($_GET['page_id']) || (isset($_GET['page_id']) && $_GET['page_id'] == "-50")) {
		echo "
			<li><b>Overview</b></li>
		";
	} else {
		echo "
			<li><a style=\"font-size: 13px;\" class=\"rezLink\" href=\"index.php?mod=tp&act=default&page_id=-50\">Overview</a></li>
		";
	}

	// DOWNLOAD PAGE
	if(!isset($_GET['page_id']) || (isset($_GET['page_id']) && $_GET['page_id'] != "-52")) {
		echo "
			<li><a style=\"font-size: 13px;\" class=\"rezLink\" href=\"index.php?mod=tp&act=default&page_id=-52\">Download</a></li>
		";
	} else {
		echo "
			<li><b>Download</b></li>
		";
	}

	// RELEASE NOTES PAGE
	if(!isset($_GET['page_id']) || (isset($_GET['page_id']) && $_GET['page_id'] != "-51")) {
		echo "
			<li><a style=\"font-size: 13px;\" class=\"rezLink\" href=\"index.php?mod=tp&act=default&page_id=-51\">Release Notes</a></li>
		";
	} else {
		echo "
			<li><b>Release Notes</b></li>
		";
	}

	echo "
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
	";
}



/**
 * Displays the proper tp page
 * @access public
 * @return void
 */
function shn_tp_page($page_id = -50) {
	global $global;

	// get page info
	$page_id = intval(mysql_real_escape_string($page_id));
	$q = "select * from rez_pages where rez_page_id = '".$page_id."';";
	$res = $global['db']->Execute($q);

	if ($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		// page doesn't exist
		echo "<h2>Error 404 ~ Page not found.</h2>";
	}
}



