<?
/**
 * @name         Menu Library
 * @version      1.0
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


/**
 * shn_mainmenuitem
 *
 * @param mixed $action
 * @param mixed $desc
 * @param mixed $module
 * @access public
 * @return void
 */
function shn_mainmenuitem($action, $desc, $module = null) {
	global $global;
	require_once($global['approot'].'/mod/lpf/lib_lpf.inc');

	if ($module == null) {
		$module = $global['module'];
	}

	// hack to allow a menu item to go to a non-default action ~Greg
	$x = strpos($module, "&act=");
	if($x) {
		$action = substr($module, $x+5);
		$module = substr($module, 0, $x);
	}

	// if this menu item is the current module displayed, add a css class to allow proper styling
	if ($global['module'] == $module) {
		$class = ' class="currentMainMenuItem"';
	} else {
		$class = '';
	}


	// UGLY HACK TO NOT SHOW USER PREFERENCES AS CURRENT MODULE WHEN VIEWING "PEOPLE IM TRACKING" OR VICE VERSA ~~~ sorry!!! ~greg
	if(($desc == "My Settings") && ($global['action'] == "tracking")) {
		$class = '';
	}
	if(($desc == "People I'm Tracking") && ($global['action'] != "tracking")) {
		$class = '';
	}
	// HACK END


	// yet another hack to highlight the admin module when using either the snapshot or resource module in the administration module
	if(($desc == "Administration") && (isset($_GET['act']) && (($_GET['act'] == "adm_default") || ($_GET['act'] == "adm_configuration")))) {
		$class = ' class="currentMainMenuItem"';
	}
	if(($desc == "Resources") && (isset($_GET['act']) && (($_GET['act'] == "adm_default") || ($_GET['act'] == "adm_configuration")))) {
		$class = ' class=""';
	}

	// a 3rd hack to show the proper home linl (it doesn't have the shortname in the url)
	if($desc == "Home") {
		echo "<li ".$class."><a href=\"".makeBaseUrlMinusEvent()."\">".$desc."</a></li>";
	} else {
		echo "<li ".$class."><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";
	}

}



/**
 * shn_mainmenuopen
 *
 * @param mixed $desc
 * @access public
 * @return void
 */
function shn_mainmenuopen($desc) {
	echo "
		<div id=\"menuwrap\">
		<h2>Modules</h2>
		<ul id=\"menu\">
	";
}



/**
 * shn_mainmenuclose
 *
 * @access public
 * @return void
 */
function shn_mainmenuclose() {
	echo "
		</ul>
		</div> <!-- /modmenuwrap -->
	";
}



/**
 * shn_mod_menuitem
 *
 * @param mixed $action
 * @param mixed $desc
 * @param mixed $module
 * @access public
 * @return void
 */
function shn_mod_menuitem($action, $desc, $module = null) {
	global $global;
	if ( null == $module ) {
		$module = $global['module'];
	}
	// if this mod menu item is the current action, add a css class to allow proper styling
	if(($global['module'] == $module) && ($global['action'] == $action) && !isset($_REQUEST['page_id']) ) {
		echo "<li class=\"currentModMenuItem\"><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";

	// hack to accomodate links in mod_rez
	} else if($module == 'rez' && isset($_REQUEST['page_id']) && ($action == "default&page_id=".$_REQUEST['page_id'])) {
		echo "<li class=\"currentModMenuItem\"><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";

	// else display menu item normally
	} else {
		echo "<li><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";
	}
}



/**
 * shn_mod_menuopen
 *
 * @param mixed $desc
 * @access public
 * @return void
 */
function shn_mod_menuopen($desc)  {
	echo "
		<div id=\"modmenuwrap\">
		<h2>".$desc."</h2>
		<ul id=\"modmenu\">
	";
}



/**
 * shn_mod_menuclose
 *
 * @access public
 * @return void
 */
function shn_mod_menuclose() {
	echo "
		</ul>
		</div> <!-- /modmenuwrap -->
	";
}



/**
 * shn_sub_mod_menuitem
 *
 * @param mixed $action
 * @param mixed $desc
 * @param mixed $module
 * @access public
 * @return void
 */
function shn_sub_mod_menuitem($action, $desc, $module = null ) {
	global $global;
	if ( null == $module ) {
		$module = $global['module'];
	}
	echo "<li><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";
	global $sub_menu_id;
	$sub_menu_id=$action;
}



/**
 * shn_sub_mod_menuopen
 *
 * @param mixed $desc
 * @access public
 * @return void
 */
$sub_menu_id='sub';
function shn_sub_mod_menuopen($desc) {
	global $sub_menu_id;
	static $num = 0;
	$id = 'sub'.$sub_menu_id.$num;
	$num++;
	echo "<li><a href=\"#\" onclick=\"expand('".$id."',this);\" class=\"smopen\">".$desc."</a><ul id=\"".$id."\">";
}



/**
 * shn_sub_mod_menuclose
 *
 * @access public
 * @return void
 */
function shn_sub_mod_menuclose() {
	echo "
		</ul>
		</li> <!-- /modmenuwrap -->
	";
}



function shn_adm_menuopen($desc=null) {
	echo "
		<div id=\"submenu_v\">
	";
}



function shn_adm_menuclose() {
	echo "
		</div>
	";
}



function shn_adm_menuitem($action, $desc, $module = null ) {
	global $global;
	if( null == $module) {
		$module = $global['module'];
	}
	echo "<a ".($global['action'] == $action ? 'class="selected" ' : '')." href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a>";
}



/**
 * Open tab menu
 *
 * @access public
 * @return void
 */
function shn_tabmenu_open() {
	echo "
		<ul id=\"tabmenu\">
	";
}



/**
 * Close tab menu
 *
 * @access public
 * @return void
 */
function shn_tabmenu_close() {
	echo "
		</ul>
	";
}



/**
 * Add an tab menu item
 *
 * @param mixed $action
 * @param mixed $desc
 * @param mixed $module
 * @access public
 * @return void
 */
function shn_tabmenu_item($action, $desc, $module = null) {
	global $global;
	if(null == $module ) {
		$module = $global['module'];
	}
	static $count = 0;
	if(isset($_REQUEST['tabid'])) {
		$active = ($count == $_REQUEST['tabid']) ? "id='active'" : '';
	} else {
		$active = '';
	}
	$tabid = '&tabid='.$count++;
	echo "<li ".$active." ><a href=\"index.php?mod=".$module."&amp;act=".$action.$tabid."\"><span>".$desc."</span></a></li>";
}

