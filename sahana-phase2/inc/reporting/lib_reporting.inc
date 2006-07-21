<?php 
/**
 *
 * Sahana Reporting library
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

require_once('../3rd/odsgeneration/spreadsheet/OpenOfficeSpreadsheet.class.php');
/*global variables*/
global $calc;
global $sheet;
global $rep_title;
global $keyword;
global $owner;


function shn_ods_report_fopen($file_name='',$keyword_in='',$owner_in='')
{
    global $keyword;
    $keyword = $keyword_in;

    global $owner;
    $owner = $owner_in;
    
    if($file_name!='')
    {
    global $calc;
    $calc = new OpenOfficeSpreadsheet($file_name);
    }


}

function shn_ods_report_add_sheet($sheet_name='')
{	
	if($sheet_name!='')
	{
	global $calc;
	global $sheet;
	$sheet = $calc->addSheet($sheet_name);
	}
}


function shn_ods_report_add_title($title='',$col='5',$row='2',$width='5',$height='0.75',$v_align='middle',$t_align='center',$f_size='19pt')
{	global $sheet;
	global $rep_title;
	$rep_title = $title;
	$title_content = $sheet->getCell($col, $row);
	$title_content->setContent($title);
	$title_content->setWidth($width.'cm');
	$title_content->setHeight($height.'cm');
	$title_content->setVerticalAlign($v_aligns);
	$title_content->setTextAlign($t_align);
	$title_content->setFontWeight('bold');
	$title_content->setSpannedCols(3);
	$title_content->setFontSize($f_size);
}

function shn_ods_report_add_table($colBase,$rowBase,$headerArray,$dataArray)
{
	global $sheet;

	$col=$colBase;
	$row=$rowBase;

		$numOftabHeads=count($headerArray);
		$header_array_keys=array_keys($headerArray);

		for($i=0;$i<$numOftabHeads;$i++)
		{
		$col=$col+$i;
		$cell_i = $sheet->getCell($col, $row);
		$cell_i->setContent($headerArray[$header_array_keys[$i]].$col.$i);
		$cell_i->setBorder('', '0.005cm solid #555555');
		//$cell_i->setTextAlign('start');
		$cell_i->setBackgroundColor('#9491AD');
		$cell_i->setVerticalAlign('middle');
		$cell_i->setTextAlign('center');
		$cell_i->setFontWeight('bold');
		$col=$colBase;
		}
		
	$row++;
	$col=$colBase;

	foreach ($dataArray as $subdataArray) 
	{
		$numOfcols=count($subdataArray);
		$array_keys=array_keys($subdataArray);
		for($i=0;$i<$numOfcols;$i++)
		{
		$col=$col+$i;
		$cell_i = $sheet->getCell($col, $row);
		$cell_i->setContent($subdataArray[$array_keys[$i]]);
		$cell_i->setBorder('', '0.005cm solid #555555');
		$cell_i->setTextAlign('start');
		$cell_i->setBackgroundColor('#C0C0FF');
		$cell_i->setVerticalAlign('middle');
		$cell_i->setTextAlign('center');
		$col=$colBase;
		}
		$col=$colBase;
		$row++;
	}

}


function shn_ods_report_add_summery($summery='',$col='5',$row='2',$width='5',$height='0.75',$v_align='middle',$t_align='center')
{
	global $sheet;
	$summery_content = $sheet->getCell($col, $row);
	$summery_content->setContent($summery);
	$summery_content->setWidth($width.'cm');
	$summery_content->setHeight($height.'cm');
	$summery_content->setVerticalAlign($v_aligns);
	$summery_content->setTextAlign($t_align);
	$summery_content->setFontWeight('bold');
	$summery_content->setBackgroundColor('#C0E7FF');
	$summery_content->setSpannedCols(10);

}

function shn_ods_report_add_image($img_path='')
{
	global $sheet;
	$cellPict = $sheet->getCell(5, 18);
	$cellPict->setSpannedCols(4);
	$pict = $sheet->addPicture($img_path);
	$pict->setBottomRightCorner('10cm', '10cm', $cellPict);
	$pict->setSVG('0cm', '0cm');
	$pict->setSize('10cm', '10cm');
}

function shn_ods_report_close()
	{
		global $calc;
		global $rep_title;
		global $keyword;
		global $owner;
		$calc->save(true,$rep_title,$keyword,$owner);

print "<br>";
$backtrace = debug_backtrace();
//var_dump($backtrace);
print $backtrace['1']["function"];
print "<br>";
	}

/**********************************End of spread sheet functions************************************************************/
/********************************** Starting of pdf functions ****************************************************************/
global $pdf;
global $pdfreportname;
function shn_pdf_report_fopen($reportname='',$creator='',$keywords='')
{

require('../3rd/fpdf/fpdf.php');
global $pdf;
global $pdfreportname;
$pdfreportname = $reportname;
$pdf=new FPDF();
$pdf->AddPage();
$pdf->SetCreator($creator);
$pdf->SetKeywords($keywords);
//$pdf->SetFont('Arial','B',16);

}

function shn_pdf_report_add_page()
{
global $pdf;
$pdf->AddPage();
$pdf->SetFont('Arial','B',16);

}

function shn_pdf_report_add_title($title='')
{
global $pdf;
    $pdf->SetTitle($title);
    $pdf->SetFont('Arial','B',15);
    $w=$pdf->GetStringWidth($title)+6;
    $pdf->SetX((210-$w)/2);
    $pdf->SetDrawColor(0,80,180);
    $pdf->SetFillColor(200,230,0);
    $pdf->SetTextColor(220,50,50);
    $pdf->SetLineWidth(0);
    $pdf->Cell($w,9,$title,1,1,'C',1);
    $pdf->Ln(10);

}

function shn_pdf_report_add_table($header,$data)
{
global $pdf;

    $pdf->SetFillColor(255,0,0);
    $pdf->SetTextColor(255);
    $pdf->SetDrawColor(128,0,0);
    $pdf->SetLineWidth(.3);
    $pdf->SetFont('','B');
    //Header
	foreach($header as $col)
        $pdf->Cell(40,7,$col,1,0,'C',1);
    	$pdf->Ln();
	

    $pdf->SetFillColor(224,235,255);
    $pdf->SetTextColor(0);
    $pdf->SetDrawColor(128,0,0);
    $pdf->SetLineWidth(.3);
    $pdf->SetFont('','');
	
	//data
	foreach($data as $row)
	{
		foreach($row as $col)
		{
        	$pdf->Cell(40,7,$col,1,0,'C',1);
		}
		$pdf->Ln();
	}
$pdf->Ln(10);
}

function shn_pdf_report_add_summery($txt='')
{
	global $pdf;
	$pdf->SetFont('Arial','B',12);
	$pdf->SetTextColor(0);
    	$pdf->MultiCell(175,5,$txt);
    	$pdf->Ln(10);
}

function shn_pdf_report_add_image($img_path='')
{	
	global $pdf;
	$pdf->Image($img_path,10,8,33);
}

function shn_pdf_report_close()
{
global $pdf;
global $pdfreportname;
//$pdf->Output('','S');
$pdf->Output($pdfreportname.".pdf");
print "<br>The PDF report created<br>";


print "<br>";
$backtrace = debug_backtrace();
//var_dump($backtrace);
print $backtrace['1']["function"];
print "<br>";
}
/**********************************End of pdf functions************************************************************/

/********************************* Starting of graph generation Functions *******************************************/

global $graph;

function base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword_in,$owner)
{
include ( "../3rd/phplot/phplot.php");
global $graph;
$graph = new PHPlot($hight,$width);
$graph->SetDataType("text-data");  
$graph->SetDataValues($dataArray);
$graph->SetFileFormat("png"); 
$graph->SetImageArea(700,500);
$graph->SetTitleFontSize( "5");
$graph->SetTitle( $title);

$graph->Setkeyword($keyword_in);
$graph->SetreportOwner($owner);

$graph->SetLegend(array("2000","2001","2002","2003", "2004", "2005", "2006")); // this values should be extracted from the data array 
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange");

$graph->SetXTitle($xtitle, "plotdown"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle($ytitle,"plotleft"); // plotright or plotleft or both or both

$graph->SetHorizTickIncrement( "5");
$graph->SetVertTickIncrement( "500"); 

$graph->SetPrecisionX("1");
$graph->SetPrecisionY( "0"); 

$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetPlotAreaWorld(0,0,7,2000);

$graph->SetOutputFile($chart_file_name.".png");

}


function generate_piechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "pie");
$graph->DrawGraph();
}

function generate_barchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "bars");
$graph->DrawGraph();
}

function generate_areachart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "area");
$graph->DrawGraph();
}

function generate_linechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "lines");
$graph->DrawGraph();
}

function generate_linepointchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "linepoints");
$graph->DrawGraph();
}

function generate_pointschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "points");
$graph->DrawGraph();
}

function generate_thinbarlinechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "thinbarline");
$graph->DrawGraph();
}

function generate_squaredchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
$graph->SetPlotType( "squared");
$graph->DrawGraph();
}

function generate_stackedbarschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$hight='',$width='',$keyword='',$owner='')
{
global $graph;
base_elements_of_chart($chart_file_name,$title,$xtitle,$ytitle,$dataArray,$hight,$width,$keyword,$owner);
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
/********************************* End of Graph generation Functions **********************************************/

/******************************** Start of XHTML Report Generation Functions **************************************/

include("html_gen.php");
global $xhtml;
function shn_xhtml_report_fopen($file_name='',$keyword='',$owner='')
{
//print "<br>";
$backtrace = debug_backtrace();
//var_dump($backtrace);
//print $backtrace['1']["function"];
//print "<br>";
$rep_id = $backtrace['1']["function"];

global $xhtml;
$xhtml = new genhtml();
$xhtml->setFileName($file_name);
$xhtml->setKeyword($keyword);
$xhtml->setOwner($owner);
$xhtml->setReportID($rep_id);
}

function shn_xhtml_report_add_title($Title='',$position='center')
{
global $xhtml;
$xhtml->setTitlePos($position);
$xhtml->addTitle($Title);
}

function shn_xhtml_report_add_summary($summary='',$summary_pos_in='center')
{
global $xhtml;
$xhtml->setSummaryPos($summary_pos_in);
$xhtml->addSummary($summary);
}

function shn_xhtml_report_add_table($tab_header='',$tab_data='',$tab_pos='center')
{
global $xhtml;
$xhtml->setTablePos($tab_pos);
$xhtml->addTable($tab_header,$tab_data);
}

function shn_xhtml_report_add_image($img_path_in='',$image_pos_in='center')
{
global $xhtml;
$xhtml->setImagePos($image_pos_in);
$xhtml->addImage('Pictures/'.$img_path_in);
}

function shn_xhtml_report_close()
{
global $xhtml;
$xhtml->Output();
}

function shn_xhtml_test()
{
//include("html_gen.php");
$testobj = new genhtml();
$testobj->setFileName('sdtest_xhtml_report');
$testobj->setKeyword("xhtml_key");
$testobj->setOwner("html_rep_owner");
$testobj->setTitlePos("left");
$testobj->addTitle("Sahana Disaster Management");

$testobj->setSummaryPos("left");
$testobj->addSummary("Sahana is a Free and Open Source Disaster Management system. It is a web based collaboration tool that addresses the common coordination problems during a disaster from finding missing people, managing aid, managing volunteers, tracking camps effectively between Government groups, the civil society (NGOs) and the victims themselves.");


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
$testobj->setTablePos("left");
$testobj->addTable($headerarray,$datasR1);
$testobj->addLink("http://www.sahana.lk/","SAHANA");
$testobj->setImagePos("left");
$testobj->addImage("cartoon001.jpg");

$testobj->Output();
}

/******************************** End of XHTML Report Generation Functions **************************************/

?>
