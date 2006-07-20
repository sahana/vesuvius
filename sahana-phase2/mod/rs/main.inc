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
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_uuid.inc";

include_once $global['approot']."/inc/reporting/lib_reporting.inc";

function shn_rs_mainmenu() 
{
	include_once ('menu.inc');
	_shn_rs_main_menu();

} 

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

function shn_rs_default()
{
	include_once ('home.inc');
}
/*******************Search functions**********************************************/
function shn_rs_search()
{
	include_once('search.inc');
	shn_rs_search_main_form();
}

function shn_rs_search_submit_one()
{
	include_once('search.inc');
	shn_rs_search_main_form();
	shn_rs_search_submit_one_result();
}

/*********************End of search functions*************************************/

/*********************Sample reports functions************************************/
function shn_rs_sample()
{
	include_once ('sample.inc');
	shn_rs_sample_report();
}
function shn_rs_sample_submit_one()
{
	include_once ('sample.inc');
	shn_rs_sample_submit_one_result();
}

function shn_rs_sample_submit_two()
{
	include_once ('sample.inc');
	_show_mod_select_form();
	shn_rs_sample_submit_two_result();
}

function shn_rs_sample_submit_three()
{
	include_once ('sample.inc');
	_show_mod_select_form();
	shn_rs_sample_submit_two_result();
	shn_rs_sample_submit_three_result();
}

function shn_rs_sample_submit_four()
{
	include_once ('sample.inc');
	_shn_rs_report_creator();
}


/**************************End of sample Report functions****************************/
function shn_rs_spreadsheet()
{
$datasR1 = array(
	array(
		'ingredient'	=> 'aaaa',
		'qte'			=> 150,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'bbbbb',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'ccccc',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'dddddddd',
		'qte'			=> 2,
		'unite'			=> 'kg'
	),
	array(
		'ingredient'	=> 'eeeeeee',
		'qte'			=> 1,
		'unite'			=> 'kg'
	),
);

	$headerarray=array( 'ss'	=> 'sssssssssss', 'dd' => 'dddddddddd', 'sd' => 'sdsdsdsdsd');

shn_ods_report_fopen('mytestreport','testodskey','pradeeper');
shn_ods_report_add_sheet('mysheetone');
shn_ods_report_add_title('Project of the Month');
shn_ods_report_add_table(5,5,$headerarray,$datasR1);
shn_ods_report_add_summery( 'Sahana is a secure Web portal that provides applications for coordination and collaboration in the aftermath of disasters. Applications include finding missing people, connecting organizations, reporting on the distribution of aid and services, matching donations to requests, tracking temporary shelters, and, overall, providing transparency and visibility to groups working in a disaster. Key features include GIS, biometrics, PDA support, and availability in the form of a live CD.' ,'5','15','5','0.75','middle','center');
shn_ods_report_add_image('cartoon001.jpg');
shn_ods_report_add_sheet('mysheettwo');
shn_ods_report_close();
}

function shn_rs_pdf()
{
$table_header=array('1' =>'aaaaaaaa', '2' => 'bbbbbbb' , '3' => 'cccccccccc');
$table_data = array(
	array(
		'ingredient'	=> 'aaaa',
		'qte'			=> 150,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'bbbbb',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'ccccc',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'dddddddd',
		'qte'			=> 2,
		'unite'			=> 'kg'
	),
	array(
		'ingredient'	=> 'eeeeeee',
		'qte'			=> 1,
		'unite'			=> 'kg'
	),
);

$title='Project of the Month';

$txt = 'Sahana is a secure Web portal that provides applications for coordination and collaboration in the aftermath of disasters. Applications include finding missing people, connecting organizations, reporting on the distribution of aid and services, matching donations to requests, tracking temporary shelters, and, overall, providing transparency and visibility to groups working in a disaster. Key features include GIS, biometrics, PDA support, and availability in the form of a live CD.';

shn_pdf_report_fopen("mypdfreport","sudeera","testkeyword");
shn_pdf_report_add_title($title);
//shn_pdf_report_add_page();
shn_pdf_report_add_table($table_header,$table_data);
//shn_pdf_report_add_page();
shn_pdf_report_add_summery($txt);
shn_pdf_report_add_page();
shn_pdf_report_add_image('tmp/Pictures/cartoon001.jpg');
shn_pdf_report_close();
}


function shn_rs_chart()
{
shn_chart_test();
}

function shn_rs_piechart()
{

$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);
generate_piechart("Piechart","This is a testing pie chart","x axis","y axis",$data,700,500,"sd keyword","sanjeewa jayasinghe");
}
function shn_rs_barchart()
{

$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);
generate_barchart("Barchart","This is a testing bar chart","x axis","y axis",$data,700,500,"bar chart keyword","mahesh kaluarachchi");
}

function shn_rs_xhtml()
{
$datasR1 = array(
	array(
		'ingredient'	=> 'aaaa',
		'qte'			=> 150,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'bbbbb',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'ccccc',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'dddddddd',
		'qte'			=> 2,
		'unite'			=> 'kg'
	),
	array(
		'ingredient'	=> 'eeeeeee',
		'qte'			=> 1,
		'unite'			=> 'kg'
	),
);

$headerarray=array( 'ss'	=> 'sssssssssssxxxx', 'dd' => 'dddddddddd', 'sd' => 'sdsdsdsdsd');
shn_xhtml_report_fopen('testxhtmlfile','testxhtml','xhtmlowner');
shn_xhtml_report_add_title('Sanjeewa Jayasinghe','left');
shn_xhtml_report_add_summary('ssssssssssssssssssssssssssssssssssssssdddddddddddddd','right');
shn_xhtml_report_add_table($headerarray,$datasR1,'center');
shn_xhtml_report_add_image("Pictures/cartoon001.jpg",'center');
shn_xhtml_report_close();
}


function shn_rs_xhtml_test()
{
shn_xhtml_test();
}


?>

