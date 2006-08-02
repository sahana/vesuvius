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

function _shn_rs_main_menu()
{
    global $global;
	global $conf;
    $module = $global['module'];

	$report_mods = _shn_get_mod_reports();
    // The  module menu
	shn_mod_menuopen(_("Reporting System"));
	shn_mod_menuitem("default",_("Home"),'rs');
	shn_sub_mod_menuopen(_("Module Reports Aggregator"));
	
		 foreach ($report_mods as $i) 
		{  
    		shn_sub_mod_menuitem("rpt_default", $conf['mod_'.$i.'_name'], $i);
 		}
	shn_sub_mod_menuclose();
	shn_mod_menuitem("sample",_("Generate Sample Reports"),'rs');
	shn_mod_menuitem("search",_("Report Search"),'rs');
	shn_mod_menuitem("download",_("Download Reports"),'rs');
	shn_sub_mod_menuopen(_("Test Reports & Charts"));
	shn_mod_menuitem("spreadsheet",_("SpreadSheet"),'rs');
	shn_mod_menuitem("pdf",_("PDF"),'rs');
	shn_mod_menuitem("xhtml",_("XHTML"),'rs');
	shn_mod_menuitem("chart",_("Chart"),'rs');
	shn_mod_menuitem("piechart",_("Pie Chart"),'rs');
	shn_mod_menuitem("barchart",_("Bar Chart"),'rs');
	shn_sub_mod_menuclose();
	shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
}

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


?>