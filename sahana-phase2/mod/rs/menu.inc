<?php
/**
 * Main Menu of the Report System. 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * This is the main menu of reporting system.
 * @access public
 * @return void
 */
function _shn_rs_main_menu()
{
    global $global;
    global $conf;
    $module = $global['module'];
    $report_mods = _shn_get_mod_reports();
    // The  module menu
    shn_mod_menuopen(_t("Reporting System"));
    shn_mod_menuitem("default",_t("Home"),'rs');
    shn_sub_mod_menuopen(_t("Module Reports Aggregator"));
	foreach ($report_mods as $i) 
	{   
		if ($i == "vol") {
			//skip when the module is 'volenteer coordination', since it is under construction
			continue;
		} else {
	        shn_sub_mod_menuitem("rpt_default", $conf['mod_'.$i.'_name'], $i);
		}
	}
    shn_sub_mod_menuclose();
//     shn_mod_menuitem("sample",_t("Generate Sample Report"),'rs');
    shn_mod_menuitem("search",_t("Report/Chart Search"),'rs');
    shn_mod_menuitem("config",_t("Configuration"),'rs');
    //shn_mod_menuitem("table",_t("Dynamic Reports (Form)"),'rs');
    shn_mod_menuitem("dnd_table",_t("Reports from one table"),'rs');
    shn_mod_menuitem("dnd_multiple_table",_t("Reports from several tables"),'rs');
    shn_mod_menuclose();

    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
}

/**
 * This function returns an array of module names that are having report.inc
 * @access public
 * @return array
 */
function _shn_get_mod_reports()
{
    global $global;
    $module_list = array();

    $approot = $global['approot'];
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (file_exists($approot."mod/".$f."/report.inc")) {
          array_push($module_list, $f);
        }
    }
    return $module_list; 
}
