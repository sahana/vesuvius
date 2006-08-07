<?php
/**
 *
 * Sahana Chart library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage presentation
 * @author     Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/lib_uuid.inc";
global $graph;

function base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr_in)
{
include ( "../3rd/phplot/phplot.php");
global $graph;

$graph = new PHPlot(700,500);

$rep_id =  shn_create_uuid('report');
$graph->Setchartid($rep_id);

$graph->SetDataType("text-data");  
$graph->SetDataValues($dataArray);
$graph->SetFileFormat("png"); 
$graph->SetImageArea(700,500);
$graph->SetTitleFontSize( "5");
$graph->SetTitle( $title);

$graph->Setkeyword($keyword_arr_in);

$legend_arr = array();
foreach($dataArray as $xval)
{
array_push($legend_arr,$xval[0]);
}

$graph->SetLegend($legend_arr); 
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange");

$graph->SetXTitle($xtitle, "plotdown"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle($ytitle,"plotleft"); // plotright or plotleft or both or both

$graph->SetHorizTickIncrement( "5"); //this should be set according to the data
$graph->SetVertTickIncrement( "500"); //this should be set according to the data

$graph->SetPrecisionX("1");
$graph->SetPrecisionY( "0"); 

$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetPlotAreaWorld(0,0,7,2000);//this should be modified

$graph->SetOutputFile($chart_file_name.".png");

}

function generate_piechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "pie");
$graph->DrawGraph();
}

function generate_barchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "bars");
$graph->DrawGraph();
}

function generate_areachart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "area");
$graph->DrawGraph();
}

function generate_linechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "lines");
$graph->DrawGraph();
}

function generate_linepointchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "linepoints");
$graph->DrawGraph();
}

function generate_pointschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "points");
$graph->DrawGraph();
}

function generate_thinbarlinechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "thinbarline");
$graph->DrawGraph();
}

function generate_squaredchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "squared");
$graph->DrawGraph();
}

function generate_stackedbarschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
$graph->SetPlotType( "stackedbars");
$graph->DrawGraph();
}



function shn_chart_test()
{
include ( "../3rd/phplot/phplot.php");
$graph = new PHPlot(700,500);

//$graph->SetDataType( "linear-linear"); //text-data
$graph->SetDataType("text-data");  //Must be called before SetDataValues

// Specify some data
$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);
$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); // parameters = "png" or "jpg" or "gif"

//Specify plotting area details
$graph->SetImageArea(700,500);
/*commented types are ok with the data*/
$graph->SetPlotType( "lines");
//$graph->SetPlotType( "linepoints");
//$graph->SetPlotType( "points");
//$graph->SetPlotType( "area");
//$graph->SetPlotType( "thinbarline");
//$graph->SetPlotType( "squared");
//$graph->SetPlotType( "pie");
//$graph->SetPlotType( "bars");
//$graph->SetPlotType( "stackedbars");

$graph->SetTitleFontSize( "5"); // the max value of font size is 5
$graph->SetTitle( "This is SD test chart");

$graph->SetLegend(array("2000","2001","2002","2003", "2004", "2005", "2006", "2007"));
//$graph->SetPlotAreaWorld(2000,0,2050,2500); // parameters = ($starting_val_of_x_axis, $s_val_of_y, $ending_val_of_x, $e_val_of_y)
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange"); // set the chart background

//you can set the x title by one line or as commented three lines
$graph->SetXTitle("SD X title", "both"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle('SD Y title',"both"); // plotright or plotleft or both or both

//Define the X axis
/*$graph->SetXLabel( "Year");
$graph->SetHorizTickIncrement( "5");
$graph->SetXGridLabelType( "title");*/

//Define the Y axis
$graph->SetVertTickIncrement( "500"); //the gap between two values in the Y axis
$graph->SetPrecisionY( "0"); // determine how many decimal points should be there in Y axis values
$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetOutputFile("sdtestpieChart.png");


//$graph->SetNewPlotAreaPixels(70,120,375,220);
$graph->SetPlotAreaWorld(0,0,7,2000);
$graph->DrawGraph();
}

?>