<?
/**
 * @name         Resources
 * @version      16
 * @package      rez
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0729
 */


require_once($global['approot'].'/inc/lib_menu.inc');
require_once($global['approot'].'/inc/lib_errors.inc');
require_once($global['approot'].'/inc/handler_db.inc');
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');
require_once($global['approot'].'/mod/rez/handler_locale.inc');


function shn_rez_header2() {

	global $global;

	// if we are display a positive number page, show the menu
	if($_GET['page'] > 0) {
		//get the locale
		$locale = shn_rez_getlocale();
		//array to hold loaded rez ids for locale
		$locale_ids = array();
		echo "<ul>";
		// get page info
		$q = "
		select *
		from rez_pages
		where rez_visibility = 'Public'
		and rez_locale = '".mysql_real_escape_string($locale)."'
		order by rez_menu_order asc;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez pages header");
		}
		if($result){
			// build page info
			while($row = $result->FetchRow() ) {
				$locale_ids[] = $row['rez_page_id'];
				if( $row['rez_page_id'] == $_GET['page'] && $row['rez_locale'] == $_GET['l'] ) {
					echo "
					<li><b>".$row['rez_menu_title']."</b></li>
					";
				} else {
					echo "
					<li>
					<a style=\"font-size: 13px;\" class=\"rezLink\" href=\"resources?page=".$row['rez_page_id']."&l=".$row['rez_locale']."\">".$row['rez_menu_title']."</a>
					</li>
					";
				}
			}
		}
		$q = "
		select *
		from rez_pages
		where rez_visibility = 'Public'
		order by rez_menu_order asc;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez pages header");
		}
		if($result){
			// build page info
			while($row = $result->FetchRow() ) {
				if( $row['rez_page_id'] == $_GET['page'] && $row['rez_locale'] == $_GET['l'] && 
						array_search($row['rez_page_id'], $locale_ids) === false ) {
					echo "
					<li><b>".$row['rez_menu_title']."</b></li>
					";
				} else if ( array_search($row['rez_page_id'], $locale_ids) === false ) {
					echo "
					<li>
					<a style=\"font-size: 13px;\" class=\"rezLink\" href=\"resources?page=".$row['rez_page_id']."&l=".$row['rez_locale']."\">".$row['rez_menu_title']."</a>
					</li>
					";
						
				}
			}
		}
		echo "</ul>";
		echo "<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">";

		// if we are showing a negative number page, its an internal system page, so dont show the menu, instead show the page name
	} else {
		$q = "
		SELECT *
		FROM rez_pages
		WHERE rez_page_id = '".mysql_real_escape_string($_GET['page'])."'
		AND rez_locale = '".mysql_real_escape_string($_GET['l'])."'
		LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez pages header");
		}
		if($result) {
			while($row = $result->FetchRow() ) {
				echo "<h2>".$row['rez_menu_title']."</h2>";
			}
		}
	}
}





/** Displays the Resources pages' content on the front end of the site. */
function shn_rez_default() {

	global $global;
	//get the locale
	$locale = shn_rez_getlocale();
	//array to hold loaded rez ids for locale
	$locale_ids = array();

	// if page, then render that page from db
	if(isset($_GET['page'])) {

		// get page info
		$page = intval(mysql_real_escape_string($_GET['page']));
		$locale = $_GET['l'];
		$q = "
		select *
		from rez_pages
		where rez_page_id = '".$page."'
		and rez_locale = '".$locale."'
		and rez_visibility <> 'INTERNAL';
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez pages default");
		}

		if($row = $result->FetchRow() ){
			shn_rez_header2();
			echo $row['rez_content'];
		} else {
			// page doesn't exist
			echo "<h2>Error 404 ~ Page not found.</h2>";
		}

		// if no page, then render the Resources homepage
	} else {
		echo "<ul id=\"rezMain\">";

		// get page info
		$q = "
		select *
		from rez_pages
		where rez_visibility = 'Public'
		and rez_locale = '".mysql_real_escape_string($locale)."'
		order by rez_menu_order asc;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez pages default");
		}
		if($result){
			// build page links
			while($row = $result->FetchRow() ) {
				$locale_ids[] = $row['rez_page_id'];
				echo "
				<li>
				<a class=\"rezLink\" href=\"resources?page=".$row['rez_page_id']."&l=".$row['rez_locale']."\">
				".$row['rez_menu_title']."</a>
				</li>
				";
			}
		}
		// get page info
		$q = "
		select *
		from rez_pages
		where rez_visibility = 'Public'
		order by rez_menu_order asc;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez pages default");
		}
		if($result){
			// build page links
			while($row = $result->FetchRow() ) {
				if ( array_search($row['rez_page_id'], $locale_ids) === false ) {
					echo "
					<li>
					<a class=\"rezLink\" href=\"resources?page=".$row['rez_page_id']."&l=".$row['rez_locale']."\">
					".$row['rez_menu_title']."</a>
					</li>
					";
				}
			}
		}
		echo "</ul>";
	}
}
