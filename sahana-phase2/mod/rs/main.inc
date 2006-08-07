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
include_once $global['approot']."/inc/reporting/lib_chart.inc";

require_once 'lib_rs_js.inc';
include_once 'lib_rs_validate.inc';

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

	if(shn_rs_validate_search_reports())
	{
	display_errors();
	shn_rs_search_main_form();
	}
	else
	{
	shn_rs_search_main_form();
	shn_rs_search_submit_one_result();
	}

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

/**************************Download functions **************************************/
function shn_rs_download_report()
{
	global $global;
    	$db=$global["db"];
 	
	$rep_id = trim($_REQUEST['rep_id']);
	$query = "select file_name,file_data from report_files where rep_id = '$rep_id' ";	
	$res = $db->Execute($query);

	$file_name = $res->fields['file_name'];
	$data = $res->fields['file_data'];
       //header("Content-type: text/xml");
       header("Content-Disposition: attachment; filename=".$file_name);
       header("Cache-Control: no-cache, must-revalidate");
	print $data;
}

/************************* End of Download functions *********************************/

/*************************config functions *******************************************/
function shn_rs_config()
{
include_once('config.inc');
shn_rs_config_main_form();
}

function shn_rs_config_main_form_submit()
{
include_once('config.inc');
    if(shn_rs_validate_config_val())
    {
    display_errors();
    shn_rs_config_main_form();
    }
    else
    {
    shn_rs_config_main_form_submit_result();
    shn_rs_config_main_form();
    }
   
}
/*************************End of config functions*************************************/

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

$rs_test_ods_keyword_arr = array('mod'=>'rs','report'=>'ods','users'=>'amila','purpose'=>'test','towhom'=>'testing users');

shn_ods_report_fopen('mytestreport',$rs_test_ods_keyword_arr);
shn_ods_report_add_sheet('mysheetone');
shn_ods_report_add_title('Project of the Month');
shn_ods_report_add_table($headerarray,$datasR1);
shn_ods_report_add_summery( 'Sahana is a secure Web portal that provides applications for coordination and collaboration in the aftermath of disasters. Applications include finding missing people, connecting organizations, reporting on the distribution of aid and services, matching donations to requests, tracking temporary shelters, and, overall, providing transparency and visibility to groups working in a disaster. Key features include GIS, biometrics, PDA support, and availability in the form of a live CD.' );
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

$rs_test_pdf_keyword_arr = array('mod'=>'rs','report'=>'pdf','users'=>'jo priyanga','purpose'=>'test pdf reports');

shn_pdf_report_fopen("mypdfreport",$rs_test_pdf_keyword_arr);
shn_pdf_report_add_title($title);
shn_pdf_report_add_table($table_header,$table_data);
shn_pdf_report_add_summery($txt);
shn_pdf_report_add_image('tmp/Pictures/cartoon001.jpg');
shn_pdf_report_close();
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

$summary = "Ubuntu's first release was on October 20, 2004, which began by making a temporary fork of the Debian Linux project.[6] This was done so that a new version of Ubuntu could be released every six months, resulting in a more frequently updated system. Ubuntu releases always include the most recent GNOME release, and are scheduled to be released about a month after GNOME. In contrast with previous general-purpose forks of Debian—such as MEPIS, Xandros, Linspire, Progeny and Libranet, many of which relied on closed-source add-ons as part of their business model—Ubuntu has stayed closer to Debian's philosophy and uses free (libre) software most of the time";

$xhtml_key_arr = array('report'=>'for test','xhtml'=>'xhtml','mod'=>'rs','users'=>'ajith','purpose'=>'testing update');

shn_xhtml_report_fopen('testxhtmlfile',$xhtml_key_arr);
shn_xhtml_report_add_title("Ubuntu Linux distribution");
shn_xhtml_report_add_summary($summary);
shn_xhtml_report_add_table($headerarray,$datasR1);
shn_xhtml_report_add_image("ubuntu_logo.png");
shn_xhtml_report_close();
}


function shn_rs_chart()
{
shn_chart_test();
}

function shn_rs_piechart()
{
/*
$data = array(
    array("a", 2000,1500, 0, 100, 600,200),
    array("b", 2010,1000, 100, 150,200,300),
    array("c", 2015,500, 700, 179, 400,500),
    array("dd",2020,200,1000,979, 1000,600),
    array("e", 2025,100,1200,78,150,700),
    array("f", 2030,50, 1450,343, 1300,800)
);
*/
$data = array(
			array("sanjeewa",100,200,300,400)
			);

$keyword_arr = array('chart'=>'pie chart','mod'=>'inventory');
generate_piechart("Piechart","This is a testing pie chart","x axis","y axis",$data,$keyword_arr);
}
function shn_rs_barchart()
{
/*
$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);*/

$data = array(
			array("sanjeewa",100),
			array("mahesh",90),
			array("ajith",70),
			array("saranga",110)
			);

$keyword_arr = array('chart'=>'bar chart','mod'=>'catalogue');
generate_barchart("Barchart","This is a testing bar chart","x axis","y axis",$data,$keyword_arr);
}
?>