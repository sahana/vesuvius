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
global $calc;
global $sheet;
global $rep_title;
global $keyword;
global $owner;
global $ods_row_counter;
global $ods_rep_ID;
global $ods_rep_gen_ok;
function shn_ods_report_fopen($file_name='',$owner_in='',$keyword_in='')
{
    global $global;
    $db=$global["db"];
    global $ods_rep_ID;
    global $keyword;
    global $ods_rep_gen_ok;

    $keyword = $keyword_in;

    global $owner;
    $owner = $owner_in;

		$backtrace = debug_backtrace();
		$ods_rep_ID = $backtrace['1']["function"];

		if($ods_rep_ID=='_shn_rs_report_creator')
		{
		$ods_rep_ID =  shn_create_uuid('report');
		}


//check the timestamp and set whether the update should be taken place or not

$query = "select t_stamp from report_files where rep_id = '$ods_rep_ID' ";	
$res_found = $db->Execute($query);
$ods_rep_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$ods_rep_gen_ok= (_shn_is_report_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}


    if($ods_rep_gen_ok)
    {
	if($file_name=='')
	{
	$file_name = "report";
	}
    global $calc;
    global $ods_row_counter;
    $calc = new OpenOfficeSpreadsheet($file_name);
    $ods_row_counter = 2;
    }


}

function shn_ods_report_add_sheet($sheet_name='')
{	
    global $ods_rep_gen_ok;

	if($ods_rep_gen_ok)
	{	
		if($sheet_name=='')
		{
		$sheet_name = "sheet1";
		}
	global $calc;
	global $sheet;
	$sheet = $calc->addSheet($sheet_name);
	}

}


function shn_ods_report_add_title($title='')
{	
	global $sheet;
	global $rep_title;
	global $ods_row_counter;
	global $ods_rep_gen_ok;

	$rep_title = $title;
	$span = strlen($title) / 5;
	if($ods_rep_gen_ok)
	{
	$title_content = $sheet->getCell(3, $ods_row_counter);
	$title_content->setContent($title);
	$title_content->setWidth('5cm');
	$title_content->setHeight('0.75cm');
	$title_content->setVerticalAlign('middle');
	$title_content->setTextAlign('center');
	$title_content->setFontWeight('bold');
	$title_content->setSpannedCols($span);
	$title_content->setFontSize('15pt');
	$title_content->setBackgroundColor('#C0E7FF');
	
	$ods_row_counter = $ods_row_counter + 2;
	}

}

function shn_ods_report_add_table($colBase,$rowBase,$headerArray,$dataArray)
{
	global $sheet;
	global $ods_row_counter;
	global $ods_rep_gen_ok;

	if($ods_rep_gen_ok)
	{
	$colBase = 3;
	$col=$colBase;
	//$row=$rowBase;
	$row = $ods_row_counter;

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

	$ods_row_counter = $row;

	$ods_row_counter = $ods_row_counter + 2;	
	}//end of $ods_rep_gen_ok 'if'
}


function shn_ods_report_add_summery($summery='')
{
	global $sheet;
	global $ods_row_counter;
	global $ods_rep_gen_ok;

	if($ods_rep_gen_ok)
	{
	$pieces = explode(" ", $summery);
	$temp = array();
	$desc_height = 0;
	for($i=0;$i<count($pieces);$i++)
	{
	array_push($temp, $pieces[$i]);
		if($i!=0 && $i%10 == 0)
		{
		$desc_height++;
		array_push($temp, "\n");
		}
	}
	$desc_height = $desc_height - 2.5;
	$new_description = implode(" ", $temp);
	
	$summery_content = $sheet->getCell('3', $ods_row_counter);
	$summery_content->setContent($new_description);
	$summery_content->setWidth('2cm');
	$summery_content->setHeight($desc_height.'cm');
	$summery_content->setVerticalAlign('middle');
	$summery_content->setTextAlign('center');
	$summery_content->setFontWeight('bold');
	$summery_content->setBackgroundColor('#C0E7FF');
	$summery_content->setSpannedCols(7);

	$ods_row_counter = $ods_row_counter + 2;	
	}//end of $ods_rep_gen_ok 'if'

}

function shn_ods_report_add_image($img_path='')
{
	global $sheet;
	global $ods_row_counter;
	global $ods_rep_gen_ok;

	if($ods_rep_gen_ok)
	{
	$cellPict = $sheet->getCell(3, $ods_row_counter);
	$pict = $sheet->addPicture($img_path);
	$pict->setBottomRightCorner('10cm', '10cm', $cellPict);
	$pict->setSVG('0cm', '0cm');
	$pict->setSize('10cm', '10cm');
	
	$ods_row_counter = $ods_row_counter + 2;	
	}//end of $ods_rep_gen_ok 'if'
}

function shn_ods_report_close()
{
	global $ods_rep_gen_ok;
	$backtrace = debug_backtrace();
	if($ods_rep_gen_ok)
	{
	// this is to check whether this function is calling by 'shn_rs_search_submit_one_result'. If it is, then printing report information is disabled
	$print_ok = $backtrace['3']["function"];
	if($print_ok == 'shn_rs_search_submit_one_result')	
	{
	$print_enable = false;	
	}
	else
	{
	$print_enable = true;
	}

	global $calc;
	global $rep_title;
	global $keyword;
	global $owner;
	global $ods_rep_ID;
	
	$calc->save(true,$rep_title,$keyword,$owner,$ods_rep_ID,$print_enable);	
	}//end of $ods_rep_gen_ok 'if'

}

/**********************************End of spread sheet functions************************************************************/
/********************************** Starting of pdf functions ****************************************************************/
global $pdf;
global $pdfreportname;
global $pdf_rep_gen_ok;
function shn_pdf_report_fopen($reportname='',$creator='',$keywords='')
{

require('../3rd/fpdf/fpdf.php');
global $pdf;
global $pdfreportname;
global $pdf_rep_gen_ok;

global $global;
$db=$global["db"];

$pdfreportname = $reportname;
$pdf=new FPDF();
$backtrace = debug_backtrace();
$rep_id = $backtrace['1']["function"];

//check the timestamp and set whether the update should be taken place or not
$query = "select t_stamp from report_files where rep_id = '$rep_id' ";	
$res_found = $db->Execute($query);
$pdf_rep_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$pdf_rep_gen_ok= (_shn_is_report_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($rep_id=='_shn_rs_report_creator')
	{
	$rep_id =  shn_create_uuid('report');
	}

// this is to check whether this function is calling by 'shn_rs_search_submit_one_result'. If it is, then printing report information is disabled
	$print_ok = $backtrace['3']["function"];
	if($print_ok == 'shn_rs_search_submit_one_result')	
	{
	$pdf->printInfoEnable(false);
	}
	else
	{
	$pdf->printInfoEnable(true);
	}

	//if report gen is OK it will start generation
	if($pdf_rep_gen_ok)
	{
	$pdf->AddPage();
	$pdf->SetCreator($creator);
	$pdf->SetKeywords($keywords);
	$pdf->SetReportID($rep_id);
	
	//$pdf->SetFont('Arial','B',16);
	}


}

function shn_pdf_report_add_page()
{
global $pdf_rep_gen_ok;
global $pdf;
	if($pdf_rep_gen_ok)
	{
	$pdf->AddPage();
	$pdf->SetFont('Arial','B',16);
	}

}

function shn_pdf_report_add_title($title='')
{
    global $pdf_rep_gen_ok;
    global $pdf;
	if($pdf_rep_gen_ok)
	{
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


}

function shn_pdf_report_add_table($header,$data)
{
    global $pdf_rep_gen_ok;
    global $pdf;

	if($pdf_rep_gen_ok)
	{
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

}

function shn_pdf_report_add_summery($txt='')
{
	global $pdf_rep_gen_ok;
	global $pdf;
	if($pdf_rep_gen_ok)
	{
	$pdf->SetFont('Arial','B',12);
	$pdf->SetTextColor(0);
    	$pdf->MultiCell(175,5,$txt);
    	$pdf->Ln(10);	
	}

}

function shn_pdf_report_add_image($img_path='')
{	global $pdf_rep_gen_ok;
	global $pdf;
	if($pdf_rep_gen_ok)
	{
	$pdf->AddPage();
	$pdf->SetFont('Arial','B',16);
	$pdf->Image($img_path,10,10,150);	
	}

}

function shn_pdf_report_close()
{
	global $pdf_rep_gen_ok;
	global $pdf;
	global $pdfreportname;
	if($pdf_rep_gen_ok)
	{
	//$pdf->Output('','S');
	$pdf->Output($pdfreportname.".pdf");
	}

}
/**********************************End of pdf functions************************************************************/

/******************************** Start of XHTML Report Generation Functions **************************************/

include("html_gen.php");
global $xhtml;
global $html_rep_gen_ok;
function shn_xhtml_report_fopen($file_name='',$owner='',$keyword='')
{
global $xhtml;
global $html_rep_gen_ok;
global $global;
$db=$global["db"];

$backtrace = debug_backtrace();
$rep_id = $backtrace['1']["function"];

//check the timestamp and set whether the update should be taken place or not
$query = "select t_stamp from report_files where rep_id = '$rep_id' ";	
$res_found = $db->Execute($query);
$html_rep_gen_ok = true;


	if($res_found->fields['t_stamp'] != null)
	{
	$html_rep_gen_ok= (_shn_is_report_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($rep_id=='_shn_rs_report_creator')
	{
	$rep_id =  shn_create_uuid('report');
	}

// this is to check whether this function is calling by 'shn_rs_search_submit_one_result'. If it is, then printing report information is disabled
	$print_ok = $backtrace['3']["function"];

		if($html_rep_gen_ok)
		{	$xhtml = new genhtml();

			if($print_ok == 'shn_rs_search_submit_one_result')	
			{
			$xhtml->printInfoEnable(false);
			}
			else
			{
			$xhtml->printInfoEnable(true);
			}	

		$xhtml->setFileName($file_name);
		$xhtml->setKeyword($keyword);
		$xhtml->setOwner($owner);
		$xhtml->setReportID($rep_id);	
		}

}

function shn_xhtml_report_add_title($Title='',$position='center')
{
global $html_rep_gen_ok;
global $xhtml;
	if($html_rep_gen_ok)
	{
	$xhtml->setTitlePos('center');
	$xhtml->addTitle($Title);
	}

}

function shn_xhtml_report_add_summary($summary='',$summary_pos_in='center')
{
global $html_rep_gen_ok;
global $xhtml;
	if($html_rep_gen_ok)
	{
	$xhtml->setSummaryPos('center');
	$xhtml->addSummary($summary);
	}

}

function shn_xhtml_report_add_table($tab_header='',$tab_data='')
{
global $html_rep_gen_ok;
global $xhtml;
	if($html_rep_gen_ok)
	{
	$xhtml->setTablePos('center');
	$xhtml->addTable($tab_header,$tab_data);
	}

}

function shn_xhtml_report_add_image($img_path_in='')
{
global $html_rep_gen_ok;
global $xhtml;
	if($html_rep_gen_ok)
	{
	$xhtml->addImage('Pictures/'.$img_path_in);
	}

}

function shn_xhtml_report_close()
{
global $html_rep_gen_ok;
global $xhtml;
	if($html_rep_gen_ok)
	{
	$xhtml->Output();
	}

}

/******************************** End of XHTML Report Generation Functions **************************************/

/*********************************private Functions *************************************************************/
function _shn_is_report_update_OK($last_updated_time_stamp)
{
	$today = getdate();	
	$cur_unix_ts = mktime($today["hours"], $today["minutes"],$today["seconds"], $today["mon"], $today["mday"] , $today["year"]);
	$rep_unix_ts = mktime(substr($last_updated_time_stamp, 10, 3),substr($last_updated_time_stamp, 14, 2),substr($last_updated_time_stamp, 17, 2), substr($last_updated_time_stamp, 5, 2),substr($last_updated_time_stamp, 8, 2) , substr($last_updated_time_stamp, 0, 4));

	$time_diff = ($cur_unix_ts-$rep_unix_ts)/60;
	if($time_diff>1)
	{
	return true;
	}
	else
	{
	return false;
	}	
}
/*********************************End of private functions *****************************************************/
?>
