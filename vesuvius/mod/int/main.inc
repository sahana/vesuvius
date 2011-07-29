<?
/**
 * @name         Internal
 * @version      1.0
 * @package      home
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0609
 */


// This is not a real Sahana module, but a module built for hosting internal NLM Project information


function shn_int_headerz() {
	echo '
		<ul>
		<li><a href="index.php?mod=int&act=servers">Internal Server List</a></li>
		<li><a href="index.php?mod=int&act=photos">Photos</a></li>
		<li><a href="index.php?mod=int&act=videos">Videos</a></li>
		<li><a href="index.php?mod=int&act=links">Links</a></li>
		<li><a href="index.php?mod=int&act=template">Sonya\'s Template</a></li>
		<li><a href="index.php?mod=int&act=unit">PLUS Web Service Unit Tests</a></li>
		<li><a href="index.php?mod=int&act=status">Tehseen\'s Status Report</a></li>
		<li><a href="index.php?mod=int&act=lan">Lan\'s Statistics Report</a></li>
		</ul>
		<hr style="color: #fff; background-color: #fff; border-bottom: 1px solid #ddd; height: 0px;">
		<br>
	';
}



function shn_int_default() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Internal Resources for the Lost Person Finder Project</h2>
	';
}



function shn_int_servers() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '34';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}


function shn_int_photos() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '35';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}



function shn_int_videos() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '36';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}




function shn_int_links() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '37';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}



function shn_int_template() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '38';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}



function shn_int_unit() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '39';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}



function shn_int_status() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '40';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}


function shn_int_lan() {
	global $global;
	shn_int_headerz();

	$q = "select * from rez_pages where rez_page_id = '41';";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}



