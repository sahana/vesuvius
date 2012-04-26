<?
/**
 * @name         Main Menu Handler
 * @version      1.0
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



global $conf;
global $global;
require_once($global['approot'].'/inc/lib_modules.inc');
require_once($global['approot'].'/inc/lib_menu.inc');

shn_mainmenuopen(_t('Main Menu'));

// display the list of modules on the menu bar
$module_list = shn_get_enabled_module_names();

$module_names = array();
$module_menuorder = array();
$module_directory = array();

foreach ($module_list as $i) {
	if(isset($conf['mod_'.$i.'_hide_in_menu']) == false) {
		$tmp = isset($conf['mod_'.$i.'_name']) ? $conf['mod_'.$i.'_name'] : null;
		array_push($module_names, (null == $tmp) ? $i : $tmp);

		$tmp = isset($conf['mod_'.$i.'_menuorder']) ? $conf['mod_'.$i.'_menuorder'] : null;
		array_push($module_menuorder, (null == $tmp) ? 10 : $tmp);

		$tmp = isset($conf['mod_'.$i.'_directory']) ? $conf['mod_'.$i.'_directory'] : null;
		array_push($module_directory, $i);
	}
}

// HACK TO SHOW "People I'm Tracking" menu link ~ Greg
// if Edit A Person Module and Preferences Tracker installed and logged in, show a menu link to this resource
if($_SESSION['logged_in'] == true) {
	array_push($module_names, "People I'm Tracking");
	array_push($module_menuorder,15);
	array_push($module_directory, "pref&act=tracking");
}

array_multisort($module_menuorder, $module_names, $module_directory);

for ($i = 0; $i < count($module_menuorder); $i++) {
	shn_mainmenuitem('default', $module_names[$i], $module_directory[$i]);
}

shn_mainmenuclose();


