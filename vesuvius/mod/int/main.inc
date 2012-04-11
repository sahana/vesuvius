<?
/**
 * @name         Internal
 * @version      13
 * @package      int
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */



function shn_int_headerz() {

	global $global;

	$count = 0;
	echo "<ul>";
	$q = "
		SELECT *
		FROM `rez_pages`
		WHERE rez_visibility = 'INTERNAL';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "int headerz"); }
	while($row = $result->FetchRow() ){
		$count++;
		$show = $row['rez_menu_title'];
		echo '<li><a href="index.php?mod=int&act=page&page_id='.$row['rez_page_id'].'">'.$show.'</a></li>';
	}
	if($count == 0) {
		echo '<li>no internal pages</li>';
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
}



function shn_int_page() {

	global $global;

	shn_int_headerz();
	$q = "
		select *
		from rez_pages
		where rez_page_id = '".$_GET['page_id']."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "int show page"); }
	if($row = $result->FetchRow() ){
		echo $row['rez_content'];
	} else {
		echo "page not found.";
	}
}




