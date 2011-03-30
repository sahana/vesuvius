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
	shn_breadcrumb_set_nicename($module, $action, $desc);

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
	shn_breadcrumb_set_nicename($module, $action, $desc);
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
	shn_breadcrumb_set_nicename($module, $action, $desc);
	echo "<a ".($global['action'] == $action ? 'class="selected" ' : '')." href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a>";
}



// BREAD CRUMB functions

// set a nicename
function shn_breadcrumb_set_nicename($module, $action, $desc) {
	global $global;
	$global['shn_q_mod='.$module.'&act='.$action.'_nicename'] = $desc;
}



function shn_breadcrumb_get_nicename($module, $action) {
	global $global;
	return $global['shn_q_mod='.$module.'&act='.$action.'_nicename'];
}



// pushes a link onto the breadcrumb stack
function shn_breadcrumb_push($nicename, $action = null, $module = null) {
	global $global;

	if ( null == $module ) $module = $global['module'];
	if ( null == $action ) $action = $global['action'];

	if ( !array_key_exists('shn_breadcrumb', $_SESSION ))
		$_SESSION['shn_breadcrumb'] = array();

	$last_crumb = end($_SESSION['shn_breadcrumb']);
	$last_module = $last_crumb[2];

	// create the query string. $action might have more appended
	$query_string = 'mod='.$module.'&amp;act='.$action;

	// only push the breadcrumb if it is not the home page and
	// if it is not the immidiately previous page in the history
	if ( $last_module == $module) {
		array_pop($_SESSION['shn_breadcrumb']);
	}
	array_push($_SESSION['shn_breadcrumb'], array($nicename, $query_string, $module));

	if (count($_SESSION['shn_breadcrumb']) > 3)
		array_shift($_SESSION['shn_breadcrumb']);
}



// pops a breadcrumb item off the top of the stack
function shn_breadcrumb_pop() {
    return array_pop($_SESSION['shn_breadcrumb']);
}



// displays the breadcrumb within the navigation section
function shn_breadcrumb_display() {
	global $conf;
	$current_mod = '';
	$breadcrumb = '';


	// create the breadcrumb array if it does not exist
	if ( !array_key_exists('shn_breadcrumb', $_SESSION )) {
		$_SESSION['shn_breadcrumb'] = array();
	}

	// clear the breadcrumb array if the user has logged out
	if ( $_SESSION['logged_in'] != true ) {
		$_SESSION['shn_breadcrumb'] = array();
	}

	//foreach ($_SESSION['shn_breadcrumb'] as $i ) {
	for ($j=0 ; $j < sizeof($_SESSION['shn_breadcrumb'])-1 ; $j++) {

		$i = $_SESSION['shn_breadcrumb'][$j];

		// check if this is an admin function, else report it under administration
		$pos = strpos($i[1], 'act=adm_');
		if ( false === $pos ) {
		$module_name = $conf['mod_'.$i[2].'_name'];
		} else {
		$module_name = $conf['mod_admin_name'];
		}

		// only prefix the module name if the next item is different
		if ($current_mod != $module_name) {
		$breadcrumb .= '<a href="?mod='.$i[2].'"><b>'.$module_name.'</b></a>: ';
		$current_mod = $module_name;
		}
		$breadcrumb .= '<a href="?'.$i[1].'">'.$i[0].'</a> > ';

	}

	// Display the breadcrumb
	if ( $breadcrumb != '' ) {
		// @TODO: Remove the space hack and make this a proper list for CSS
		echo '<div id="breadcrumbs">&nbsp;&nbsp;&nbsp;&nbsp;<b>';
		echo _t('Switch back to').' </b>'.$breadcrumb.'</div>';
	}
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
	shn_breadcrumb_set_nicename($module, $action, $desc);
	echo "<li ".$active." ><a href=\"index.php?mod=".$module."&amp;act=".$action.$tabid."\"><span>".$desc."</span></a></li>";
}

