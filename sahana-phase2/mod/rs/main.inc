<?php


/**
 * Main Controller of the Catalogue System. 
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
 * @subpackage cs
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
    global $global;
    $module = $global['module'];

    // The  module menu
	shn_mod_menuopen(_("Reporting System"));
	shn_mod_menuitem("default",_("Home"));
	shn_sub_mod_menuopen(_("Reports"));
	shn_sub_mod_menuclose();
	shn_sub_mod_menuopen(_("Test Reports & Charts"));
	shn_mod_menuitem("spreadsheet",_("SpreadSheet"));
	shn_mod_menuitem("pdf",_("PDF"));
	shn_mod_menuitem("chart",_("Chart"));
	shn_mod_menuitem("piechart",_("Pie Chart"));
	shn_mod_menuitem("barchart",_("Bar Chart"));
	shn_sub_mod_menuopen(_("Sample Reports"));
	shn_sub_mod_menuclose();
	shn_sub_mod_menuclose();

	shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 


function shn_rs_default()
{
	include_once ('home.inc');
}

function shn_rs_spreadsheet()
{
echo "Hi ....";

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

shn_ods_report_fopen('mytestreport');
shn_ods_report_add_sheet('mysheetone');
shn_ods_report_add_title('Project of the Month');
shn_ods_report_add_table(5,5,$headerarray,$datasR1);
shn_ods_report_add_summery( 'Sahana is a secure Web portal that provides applications for coordination and collaboration in the aftermath of disasters. Applications include finding missing people, connecting organizations, reporting on the distribution of aid and services, matching donations to requests, tracking temporary shelters, and, overall, providing transparency and visibility to groups working in a disaster. Key features include GIS, biometrics, PDA support, and availability in the form of a live CD.' ,'5','15','5','0.75','middle','center');
shn_ods_report_add_graph('cartoon001.jpg');
shn_ods_report_add_sheet('mysheettwo');
shn_ods_report_add_title('SD well done');
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

shn_pdf_report_fopen("mypdfreport");
shn_pdf_report_add_title($title);
//shn_pdf_report_add_page();
shn_pdf_report_add_table($table_header,$table_data);
//shn_pdf_report_add_page();
shn_pdf_report_add_summery($txt);
shn_pdf_report_add_page();
shn_pdf_report_add_graph();
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
//generate_piechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='')
generate_piechart("Piechart","This is a testing pie chart","x axis","y axis",$data,700,500);
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
//generate_piechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='')
generate_barchart("Barchart","This is a testing bar chart","x axis","y axis",$data,700,500);
}



?>

