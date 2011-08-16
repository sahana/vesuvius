<?
/**
 * @name         Internal
 * @version      1.1
 * @package      int
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
 */


function shn_int_headerz() {
	global $global;

	echo "<ul>";

	$q = "
		SELECT *
		FROM `rez_pages`
		WHERE rez_visibility = 'INTERNAL';
	";
	$res = $global['db']->Execute($q);
	while($row = $res->FetchRow() ){
		if($row['rez_page_title'] == $row['rez_description']) {
			$show = $row['rez_page_title'];
		} else {
			$show = $row['rez_page_title'] ." --- ".$row['rez_description'];
		}

		echo '<li><a href="index.php?mod=int&act=page&page_id='.$row['rez_page_id'].'">'.$show.'</a></li>';
	}

	echo '
		</ul>
		<br>
		<hr style="height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; ">
		<br>
	';
}



function shn_int_default() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Internal Resources (only viewable by Admins)</h2>
	';
	// show build & version

	global $global;
	$revision_file = $global['approot']."/www/theme/lpf3/version";
	$time_file     = $global['approot']."/www/theme/lpf3/time";

	// only show the rev/build info on stage/production ~ not dev as version/time dont exist there or in svn
	if(file_exists($revision_file) && file_exists($time_file)) {
		// open file with the revision number in the first line
		$handle = fopen($revision_file, "r");

		// read first line. TODO: check if it's not empty, etc.
		$version = fgets($handle);

		// open file to read timestamp
		$handle2 = fopen($time_file, "r");

		// extract time
		$time = fgets($handle2);

		// print generated link
		echo "version: <b>r".$version."</b> &nbsp; Build Time: <b>".$time."</b>";
	}
}



function shn_int_page() {
	global $global;
	shn_int_headerz();

	$q = "
		select *
		from rez_pages
		where rez_page_id = '".$_GET['page_id']."';
	";
	$res = $global['db']->Execute($q);
	if($row = $res->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}




