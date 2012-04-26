<?
/**
 * @name         Menu Library
 * @version      15
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */


/** shn_mainmenuitem */
function shn_mainmenuitem($action, $desc, $module = null) {

	global $global;
	global $conf;

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

	// UGLY HACK TO NOT SHOW USER PREFERENCES AS CURRENT MODULE WHEN VIEWING "PEOPLE IM TRACKING" OR VICE VERSA
	if(($desc == "My Settings") && ($global['action'] == "tracking")) {
		$class = '';
	}
	if(($desc == "People I'm Tracking") && ($global['action'] != "tracking")) {
		$class = '';
	}


	// yet another hack to highlight the admin module when using the resource module in the administration module
	if(($desc == "Administration") && (isset($_GET['act']) && (($_GET['act'] == "adm_default") || ($_GET['act'] == "adm_configuration")))) {
		$class = ' class="currentMainMenuItem"';
	}
	if(($desc == "Resources") && (isset($_GET['act']) && (($_GET['act'] == "adm_default") || ($_GET['act'] == "adm_configuration")))) {
		$class = ' class=""';
	}

	// a 4th hack to show when the mpres cron daemon is dead!
	if($desc == "Inbound Email") {
		require_once($global['approot'].'/mod/mpres/main.inc');
		if(!shn_mpres_statusGood()) {
			$desc .= " <span style=\"color: red;\"><b>●</b></span>";
		} else {
			$desc .= " <span style=\"color: green;\"><b>●</b></span>";
		}
	}

	// a 5th hack to show when the pop email is erroring!
	if($desc == "Outbound Email") {
		require_once($global['approot'].'/mod/pop/main.inc');
		if(!shn_pop_statusGood()) {
			$desc .= " <span style=\"color: red;\"><b>●</b></span>";
		} else {
			$desc .= " <span style=\"color: green;\"><b>●</b></span>";
		}
	}

	// YAH (yet another hack) to show when the import/export sync is erroring!
	if($desc == "Import & Export") {
		require_once($global['approot'].'/mod/pfif/main.inc');
		if(shn_pfif_status_code() == RED) {
			$desc .= " <span style=\"color: red;\"><b>●</b></span>";
		} else if (shn_pfif_status_code() == ORANGE) {
			$desc .= " <span style=\"color: orange;\"><b>●</b></span>";
		} else {
			$desc .= " <span style=\"color: green;\"><b>●</b></span>";
		}
	}

	// prettify links :)
	switch($module) {
		case 'inw':
			$module = "search";
			break;
		case 'arrive':
			$module = "arrivals";
			break;
		case 'rez':
			$module = "resources";
			break;
		case 'tp':
			$module = "triagepic";
			break;
		case 'stat':
			$module = "statistics";
			break;
		case 'ha':
			$module = "hospitals";
			break;
		case 'pop':
			$module = "outbound";
			break;
		case 'mpres':
			$module = "inbound";
			break;
		case 'em':
			$module = "events";
			break;
		case 'sepl':
			$module = "searchplus";
			break;
	}
	if($module == "pref" && $action == "tracking") {
		$module = "tracking";
		$action = "default";
	}
/** >>>>>>> MERGE-SOURCE */

/** <<<<<<< TREE */
	// a 3rd hack to show the proper home linl (it doesn't have the shortname in the url)
/** ======= */
	// a 3rd hack to show the proper home link (it doesn't have the shortname in the url)
/** //>>>>>>> MERGE-SOURCE */
	if($desc == "Home") {
		echo "<li ".$class."><a href=\"".makeBaseUrlMinusEvent()."\">".$desc."</a></li>";
	} elseif($action != "default") {
		echo "<li ".$class."><a href=\"".$module."?act=".$action."\">".$desc."</a></li>";
	} else {
		echo "<li ".$class."><a href=\"".$module."\">".$desc."</a></li>";
	}
}



/** shn_mainmenuopen */
function shn_mainmenuopen($desc) {
	echo "
		<div id=\"menuwrap\">
		<ul id=\"menu\">
	";
}



/** shn_mainmenuclose */
function shn_mainmenuclose() {
	echo "
		</ul>
		</div> <!-- /menuwrap -->
	";
}



/** Open tab menu */
function shn_tabmenu_open() {
	echo "
		<ul id=\"tabmenu\">
	";
}



/** Close tab menu */
function shn_tabmenu_close() {
	echo "
		</ul>
	";
}



/** Add an tab menu item */
function shn_tabmenu_item($action, $desc, $module) {

	global $global;

	static $count = 0;
	if(isset($_GET['tabid'])) {
		$active = ($count == $_GET['tabid']) ? "id='active'" : '';
	} elseif($count == 0) {
		$active = "id='active'";
	} else {
		$active = '';
	}
	$tabid = '&tabid='.$count++;
	echo "<li ".$active." ><a href=\"".$module."?".$action.$tabid."\"><span>".$desc."</span></a></li>";
}


