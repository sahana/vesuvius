<?php 
/**
 * modRez xajax library
 *
 * @package	module
 * @subpackage	rez
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

include_once ($global['approot'].'/inc/lib_menu.inc');
include_once ($global['approot'].'/inc/lib_errors.inc');
include_once ($global['approot'].'/inc/lib_log.inc');
require_once ($global['approot'].'/inc/handler_db.inc');


/**
 * Generate the module's own specific menu structure.
 * @access public
 * @return void
 */
function shn_rez_mainmenu() {
	global $conf;
	global $global;
	$module = $global['module'];

	// include the main menu before mod menu?
	if ($conf['mod_rez_mainmenu_before_modmenu']) {
		include $global['approot'].'/inc/handler_mainmenu.inc';
	}

	// open menu
	shn_mod_menuopen(_t('Resources'));

	// show "Home" menu item
	shn_mod_menuitem("default",_t("Main"));

	// get pages info
	$q = "select * from rez_pages where rez_visibility = 'Public' order by rez_menu_order asc;";
	$res = $global['db']->Execute($q);

	$pages = array();
	$count = 0;

	// build menu, if resources exist
	if($res){
		while($row = $res->FetchRow() ){
			shn_mod_menuitem("default&page_id=".$row['rez_page_id'],_t($row['rez_menu_title']));
		}
	}

	shn_mod_menuclose();

	// include the main menu after mod menu?
	if (!$conf['mod_rez_mainmenu_before_modmenu']) {
		include $global['approot'].'/inc/handler_mainmenu.inc';
	}
}


/**
 * Displays the Resources pages' content on the front end of the site.
 * @access public
 * @return void
 */
function shn_rez_default() {
	global $global;
	?><div id="home"><?
	// if page_id, then render that page from db
	if (isset($_GET['page_id'])) {
		// get page info
		$q = "select * from rez_pages where rez_page_id = '".$_GET['page_id']."';";
		$res = $global['db']->Execute($q);

		if ($row = $res->FetchRow() ){
			echo "<h2>".$row['rez_page_title']."</h2>";
			echo $row['rez_content'];
		}

	// if no page_id, then render the Resources homepage
	} else {
		echo "<h2>Resources : Main</h2>";
			echo "<br><h3>Additional Resources</h3>";
			echo "<ul>";

			// get page titles/descriptions
			$q = "select * from rez_pages where rez_visibility = 'Public' order by rez_menu_order asc;";
			$res = $global['db']->Execute($q);
			if($res){
				// build page descriptions
				while($row = $res->FetchRow() ) {
					echo "<li><a href=\"index.php?mod=rez&act=default&page_id=".$row['rez_page_id']."\">".$row['rez_page_title']."</a> : ".$row['rez_description']."</li>";
			}
		echo "</ul>";
		}
	}
	?></div><?
}