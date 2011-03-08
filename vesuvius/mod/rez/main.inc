<?
/**
 * @name         Resources
 * @version      1.2
 * @package      rez
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


include_once ($global['approot'].'/inc/lib_menu.inc');
include_once ($global['approot'].'/inc/lib_errors.inc');
require_once ($global['approot'].'/inc/handler_db.inc');


function shn_rez_header2() {
	global $global;

	// if we are display a positive number page, show the menu
	if($_GET['page_id'] > 0) {

		echo "<ul>";
		// get page titles/descriptions
		$q = "
			select *
			from rez_pages
			where rez_visibility = 'Public'
			order by rez_menu_order asc;
		";
		$res = $global['db']->Execute($q);
		if($res){
			// build page descriptions
			while($row = $res->FetchRow() ) {
				if($row['rez_page_id'] == $_GET['page_id']) {
					echo "
						<li><b>".$row['rez_page_title']."</b></li>
					";
				} else {
					echo "
						<li>
							<a style=\"font-size: 13px;\" class=\"rezLink\" href=\"index.php?mod=rez&act=default&page_id=".$row['rez_page_id']."\">".$row['rez_page_title']."</a>
						</li>
					";
				}
				// $row['rez_description'] removed
			}
		}
		echo "</ul>";
		echo "<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">";

	// if we are showing a negative number page, its an internal system page, so dont show the menu, instead show the page name
	} else {
		$q = "
			SELECT *
			FROM rez_pages
			WHERE rez_page_id = '".mysql_real_escape_string($_GET['page_id'])."'
			LIMIT 1;
		";
		$res = $global['db']->Execute($q);
		if($res) {
			while($row = $res->FetchRow() ) {
				echo "<h2>".$row['rez_page_title']."</h2>";
			}
		}
	}
}





/**
 * Displays the Resources pages' content on the front end of the site.
 * @access public
 * @return void
 */
function shn_rez_default() {
	global $global;

	// if page_id, then render that page from db
	if (isset($_GET['page_id'])) {
		// get page info
		$page_id = intval(mysql_real_escape_string($_GET['page_id']));
		$q = "select * from rez_pages where rez_page_id = '".$page_id."';";
		$res = $global['db']->Execute($q);

		if ($row = $res->FetchRow() ){
			//echo "<h2>".$row['rez_page_title']."</h2>";
			shn_rez_header2();
			echo $row['rez_content'];
		} else {
			// page doesn't exist
			echo "<h2>Error 404 ~ Page not found.</h2>";
		}

	// if no page_id, then render the Resources homepage
	} else {
		//echo "<h2>Resources : Main</h2><br>";
		echo "<ul id=\"rezMain\">";

			// get page titles/descriptions
			$q = "select * from rez_pages where rez_visibility = 'Public' order by rez_menu_order asc;";
			$res = $global['db']->Execute($q);
			if($res){
				// build page descriptions
				while($row = $res->FetchRow() ) {
					echo "
						<li>
							<a class=\"rezLink\" href=\"index.php?mod=rez&act=default&page_id=".$row['rez_page_id']."\">
							".$row['rez_page_title']."</a>
						</li>
					";
					// $row['rez_description'] removed
				}
			}
		echo "</ul>";
	}
}



/**
 * Displays a Landing Page
 * @access public
 * @return void
 */
function shn_rez_landing() {
	global $global;
	echo "<div id=\"home\">";

		/*
			TO DO ... CORRECT THIS!
			PAGE 15 is not always the landing page...
			so, fix mod rez to choose/set one
		*/
		$page_id = '15';
		$q = "select * from rez_pages where rez_page_id = '".$page_id."';";
		$res = $global['db']->Execute($q);

		if ($row = $res->FetchRow() ){
			echo "<h2>".$row['rez_page_title']."</h2>";
			echo $row['rez_content'];
		} else {
			// page doesn't exist
			echo "<h2>Error 404 ~ Page not found.</h2>";
		}
	echo "</div>";
}












