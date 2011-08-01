<?
/**
 * @name         Internal
 * @version      1.1
 * @package      home
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
 */


// This is not a real Sahana module, but a module built for hosting internal NLM Project information


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
		<h2>Internal Resources Pages (only viewable by Admins)</h2>
	';
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




