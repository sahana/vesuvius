<?php
/**
 * Main Controller of the Report System. 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @author	   Ishan Liyanage <ishan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $dieconf;

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_uuid.inc";
include_once $global['approot']."/inc/reporting/lib_reporting.inc";
include_once $global['approot']."/inc/reporting/lib_chart.inc";

require_once 'lib_rs_js.inc';
include_once 'lib_rs_validate.inc';
include_once 'rs_export.inc';
include_once 'lib_formats.inc';
include_once 'admin.inc';

_shn_die_fetch_formats(); //Load available formats


/**
 * This function includes the main menu of reporting module.
 * @access public
 * @return void
 */
function shn_rs_mainmenu() 
{
    include_once ('menu.inc');
    _shn_rs_main_menu();

} 

/**
 * This function finds modules that are having report.inc.
 * @access public
 * @return void
 */
function shn_rs_modreports()
{
    global $global;
    // include original module report section
    include $global['approot']."/mod/".$global['module']."/report.inc";
    // compose and call the relevant module function
    $module_function = "shn_".$global['module']."_".$global['action'];
    
    if (!function_exists($module_function)) {
        $module_function="shn_".$global['module']."_rpt_default";
    } 

    $module_function();
}

/**
 * Default function of the reporting module. Includes home.inc.
 * @access public
 * @return void
 */
function shn_rs_default()
{
    include_once ('home.inc');
}

/**
 * This function includes the search,inc, which will display the search form.
 * @access public
 * @return void
 */
function shn_rs_search()
{
    include_once('search.inc');
    shn_rs_search_type_select();
    shn_rs_search_main_form();
}

/**
 * Calls to validate functions for POST data from shn_rs_search_main_form() in search.inc and direct to the result function.
 * @access public
 * @return void
 */
function shn_rs_search_submit_one()
{
    include_once('search.inc');
    if(shn_rs_validate_search_reports())
    {
    display_errors();
    shn_rs_search_type_select();
    shn_rs_search_main_form();
    }
    else
    {
    shn_rs_search_type_select();
    shn_rs_search_main_form();
    shn_rs_search_submit_one_result();
    }
}

/**
 * Calls to sample report generate form by including sample.inc
 * @access public
 * @return void
 */
function shn_rs_sample()
{
    include_once ('sample.inc');
    shn_rs_sample_report();
}

/**
 * Calls to validate functions for POST data from shn_rs_sample_report() in sample.inc and direct to the result function.
 * @access public
 * @return void
 */
function shn_rs_sample_submit_one()
{
    include_once ('sample.inc');
    if(shn_rs_validate_sample_report())
    {
    display_errors();
    shn_rs_sample_report();
    }
    else
    {
    shn_rs_sample_submit_one_result();
    }
}

/**
 * displays the module select form to generate module specific reports.
 * @access public
 * @return void
 */
function shn_rs_sample_submit_two()
{
    include_once ('sample.inc');
    _show_mod_select_form();
    shn_rs_sample_submit_two_result();
}

/**
 * displays the result of the search
 * @access public
 * @return void
 */
function shn_rs_sample_submit_three()
{
    include_once ('sample.inc');
    _show_mod_select_form();
    shn_rs_sample_submit_two_result();
    shn_rs_sample_submit_three_result();
}

/**
 * Calls to the report creator function to create the sample report.
 * @access public
 * @return void
 */
function shn_rs_sample_submit_four()
{
    include_once ('sample.inc');
    _shn_rs_report_creator();
}

/**
 * Download report/chart..
 * @access public
 * @return void
 */
function shn_text_rs_download_report()
{
    include_once ('menu.inc');
    global $global;
    $db=$global["db"];

    $rep_id = trim($_REQUEST['rep_id']);
    $report_mods = _shn_get_mod_reports();

	/*
	foreach ($report_mods as $i) 
	{
    	include $global['approot']."/mod/".$i."/report.inc";
	$function_name = $rep_id;
		if(function_exists($function_name))
		{
		$function_name();
		break;
		}
 	}
*/

    $rep_mod = explode('_', $rep_id);
    include_once $global['approot']."mod/".$rep_mod[1]."/report.inc";// extract the module name from the report/chart.eg: shn_cs_chart; then this will return "cs"
    //$rep_id();

    $query = "select file_name,file_data,file_type from report_files where rep_id = '$rep_id' ";	
    $res = $db->Execute($query);
    $file_name = $res->fields['file_name'];
    $data = $res->fields['file_data'];
    $file_type = $res->fields['file_type'];

        switch($file_type)
	{
            case 'pdf':
		header("Content-type: application/pdf");
            break;
            case 'ods':
		header("Content-type: application/vnd.oasis.opendocument.spreadsheet");
            break;
            case 'xhtml':
		header("Content-type: text/html");
            break;
            case 'xls':
		header("Content-type: application/vnd.ms-excel");
            break;
            case 'png':
		header("Content-type: image/png");
            break;
	
        }

    header("Content-Disposition: attachment; filename=".$file_name);
    header("Cache-Control: no-cache, must-revalidate");
    print $data;
}

/**
 * Includes the config.inc and displays the main configuration form.
 * @access public
 * @return void
 */
function shn_rs_config()
{
    include_once('config.inc');
    shn_rs_config_main_form();
}

/**
 * Calls to the function that save the configuration values in the database..
 * @access public
 * @return void
 */
function shn_rs_config_main_form_submit()
{
    include_once('config.inc');
    shn_rs_config_main_form_submit_result();
    shn_rs_config_main_form();
}
//dynamic reports functions

function shn_rs_table()
{	
	global $global;
	include_once('table.inc');
}
function shn_rs_dnd_table()
{
	global $global;
	include_once('dnd_table.inc');
}
function shn_rs_dnd_multiple_table()
{
	global $global;
	include_once('dnd_multiple_table.inc');
}


//export functions

function shn_rs_export(){
    _shn_rs_export_form($_GET['title']);
}
function shn_text_rs_export(){
    global $global;
    //load the nessary format
    $format=$_POST['format'];
    $format=addslashes($format);
    $filename = $global['approot']."mod/rs/formats/$format/handler_export.inc";
    if (file_exists($filename)) {
        require_once($filename);
    } else {
        echo _("Error : The format you selected is unavailable")." $filename";
    }
}
