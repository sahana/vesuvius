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
 * @package    moduleAPI
 * @subpackage reporting
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

/**
 * This function will open the ods report
 *
 * @param string $file_name
 * @param mixed $keyword_in
 * @access public
 * @return void
 */
function shn_ods_report_fopen($file_name='',$keyword_in='')
{
    global $global;
    $db=$global["db"];
    global $ods_rep_ID;
    global $keyword;
    global $ods_rep_gen_ok;
    global $owner;
    $keyword = $keyword_in;

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

/**
 * This function will add a new sheet to the ods report
 *
 * @param string $sheet_name
 * @access public
 * @return void
 */
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

/**
 * This function will add a title to the ods report
 *
 * @param string $title
 * @access public
 * @return void
 */
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

/**
 * This function will add a table to the ods report
 *
 * @param mixed $headerArray
 * @param mixed $dataArray
 * @access public
 * @return void
 */
function shn_ods_report_add_table($headerArray,$dataArray)
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
	$cell_i->setContent($headerArray[$header_array_keys[$i]]);
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

/**
 * This function will add a paragraph to the ods report
 *
 * @param string $summery
 * @access public
 * @return void
 */
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

/**
 * This function will add an image to the ods report
 *
 * @param string $img_path
 * @access public
 * @return void
 */
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

/**
 * This function will close the ods report
 *
 * @param string $img_path
 * @access public
 * @return void
 */
function shn_ods_report_close()
{
    global $ods_rep_gen_ok;

    if(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='search_submit_one')
    {
    $print_enable = false;	
    }
    elseif(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='download_report')
    {
    $print_enable = false;
    }
    else
    {
    $print_enable = true;
    }

    if($ods_rep_gen_ok)
    {	
    global $calc;
    global $rep_title;
    global $keyword;
    global $owner;
    global $ods_rep_ID;
    $calc->save(true,$rep_title,$keyword,$owner,$ods_rep_ID,$print_enable);	
    }//end of $ods_rep_gen_ok 'if'
    else if(!$ods_rep_gen_ok && $print_enable)
    {
    global $global;
    $db=$global["db"];
    global $ods_rep_ID;
    $query = "select * from report_files where rep_id = '$ods_rep_ID' ";	
    $res = $db->Execute($query);

    print "<h1> Report - ".$res->fields['title']."</h1>";
    print "<b>Report ID : </b>".$res->fields['rep_id']." <br>";
    print "<b>Report File Name : </b>". $res->fields['file_name']."<br>";
    print "<b>Date/Time : </b>".$res->fields['t_stamp']."<br>";
    print "<b>File Type : </b>".$res->fields['file_type']."<br>";
    print "<b>File Size : </b>".$res->fields['file_size_kb']." kb <br>";
    }
}

global $pdf;
global $pdfreportname;
global $pdf_rep_gen_ok;
global $pdf_print_enable;
global $pdf_rep_ID;

/**
 * This function will open the pdf report
 *
 * @param string $reportname
 * @param mixed $keywords
 * @access public
 * @return void
 */
function shn_pdf_report_fopen($reportname='',$keywords='')
{
    require('../3rd/fpdf/fpdf.php');
    global $pdf;
    global $pdfreportname;
    global $pdf_rep_gen_ok;
    global $pdf_print_enable;
    global $pdf_rep_ID;
    global $global;
    $db=$global["db"];

    $pdfreportname = $reportname;
    $pdf=new FPDF();
    $backtrace = debug_backtrace();
    $rep_id = $backtrace['1']["function"];
    $pdf_rep_ID = $rep_id;
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

    if(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='search_submit_one')
    {
    $pdf->printInfoEnable(false);
    $pdf_print_enable = false;
    }
    elseif(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='download_report')
    {
    $pdf->printInfoEnable(false);
    $pdf_print_enable = false;
    }
    else
    {
    $pdf->printInfoEnable(true);
    $pdf_print_enable = true;
    }

    //if report gen is OK it will start generation
    if($pdf_rep_gen_ok)
    {
    $pdf->AddPage();
    $pdf->SetKeywords($keywords);
    $pdf->SetReportID($rep_id);	
    //$pdf->SetFont('Arial','B',16);
    }
}

/**
 * This function will add a new page to the pdf report
 *
 * @param string $title
 * @access public
 * @return void
 */
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

/**
 * This function will add a title to the pdf report
 *
 * @param string $title
 * @access public
 * @return void
 */
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

/**
 * This function will add a table to the pdf report
 *
 * @param mixed $header
 * @param mixed $data
 * @access public
 * @return void
 */
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

/**
 * This function will add a paragraph to the pdf report
 *
 * @param string $txt
 * @access public
 * @return void
 */
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

/**
 * This function will add an image to the pdf report
 *
 * @param string $img_path
 * @access public
 * @return void
 */
function shn_pdf_report_add_image($img_path='')
{	
    global $pdf_rep_gen_ok;
    global $pdf;
    if($pdf_rep_gen_ok)
    {
    $pdf->AddPage();
    $pdf->SetFont('Arial','B',16);
    $pdf->Image("tmp/Pictures/".$img_path,10,10,150);	
    }
}

/**
 * This function will close the pdf report
 *
 * @access public
 * @return void
 */
function shn_pdf_report_close()
{
    global $global;
    $db=$global["db"];
    global $pdf_rep_gen_ok;
    global $pdf;
    global $pdfreportname;
    global $pdf_print_enable;
    global $pdf_rep_ID;

    if($pdf_rep_gen_ok)
    {
    //$pdf->Output('','S');
    $pdf->Output($pdfreportname.".pdf");
    }
    else if(!$pdf_rep_gen_ok && $pdf_print_enable)
    {
    $query = "select * from report_files where rep_id = '$pdf_rep_ID' ";	
    $res = $db->Execute($query);

    print "<h1> Report - ".$res->fields['title']."</h1>";
    print "<b>Report ID : </b>".$res->fields['rep_id']." <br>";
    print "<b>Report File Name : </b>". $res->fields['file_name']."<br>";
    print "<b>Date/Time : </b>".$res->fields['t_stamp']."<br>";
    print "<b>File Type : </b>".$res->fields['file_type']."<br>";
    print "<b>File Size : </b>".$res->fields['file_size_kb']." kb <br>";
    }
}

include("html_gen.php");
global $xhtml;
global $html_rep_gen_ok;
global $html_print_enable;
global $html_rep_ID;

/**
 * This function will open the xhtml report
 *
 * @param string $file_name
 * @param mixed $keyword
 * @access public
 * @return void
 */
function shn_xhtml_report_fopen($file_name='',$keyword='')
{
    global $xhtml;
    global $html_rep_gen_ok;
    global $html_print_enable;
    global $html_rep_ID;
    global $global;
    $db=$global["db"];

    $backtrace = debug_backtrace();
    $rep_id = $backtrace['1']["function"];
    $html_rep_ID = $rep_id;
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
    $xhtml = new genhtml();

    if(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='search_submit_one')
    {
    $xhtml->printInfoEnable(false);
    $html_print_enable = false;
    }
    elseif(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='download_report')
    {
    $xhtml->printInfoEnable(false);
    $html_print_enable = false;
    }
    else
    {
    $xhtml->printInfoEnable(true);
    $html_print_enable = true;
    }

    if($html_rep_gen_ok)
    {	
    $xhtml->setFileName($file_name);
    $xhtml->setKeyword($keyword);
    $xhtml->setReportID($rep_id);	
    }
}

/**
 * This function will add a title to the xhtml report
 *
 * @param string $file_name
 * @param mixed $keyword
 * @access public
 * @return void
 */
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

/**
 * This function will add a paragraph to the xhtml report
 *
 * @param string $summary
 * @access public
 * @return void
 */
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

/**
 * This function will add a table to the xhtml report
 *
 * @param mixed $tab_header
 * @param mixed $tab_data
 * @access public
 * @return void
 */
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

/**
 * This function will add a image to the xhtml report
 *
 * @param string $img_path_in
 * @access public
 * @return void
 */
function shn_xhtml_report_add_image($img_path_in='')
{
    global $html_rep_gen_ok;
    global $xhtml;
    if($html_rep_gen_ok)
    {
    $xhtml->addImage('Pictures/'.$img_path_in);
    }
}

/**
 * This function will close the xhtml report
 *
 * @param string $img_path_in
 * @access public
 * @return void
 */
function shn_xhtml_report_close()
{
    global $global;
    $db=$global["db"];
    global $html_rep_gen_ok;
    global $html_print_enable;
    global $html_rep_ID;
    global $xhtml;
    if($html_rep_gen_ok)
    {
    $xhtml->Output();
    }
    else if(!$html_rep_gen_ok && $html_print_enable)
    {
    $query = "select * from report_files where rep_id = '$html_rep_ID' ";	
    $res = $db->Execute($query);

    print "<h1> Report - ".$res->fields['title']."</h1>";
    print "<b>Report ID : </b>".$res->fields['rep_id']." <br>";
    print "<b>Report File Name : </b>". $res->fields['file_name']."<br>";
    print "<b>Date/Time : </b>".$res->fields['t_stamp']."<br>";
    print "<b>File Type : </b>".$res->fields['file_type']."<br>";
    print "<b>File Size : </b>".$res->fields['file_size_kb']." kb <br>";
    }
}

/**
 * This function will return the download url for the purticular report/chart ID.
 *
 * @param string $report_id
 * @access public
 * @return string
 */
function report_download_link($report_id)
{
    return "stream.php?mod=rs&act=download_report&rep_id=".$report_id;
}

/**
 * This function return boolean value of whether the report generation ok or not.
 *
 * @param string $last_updated_time_stamp
 * @access private
 * @return boolean
 */
function _shn_is_report_update_OK($last_updated_time_stamp)
{
    global $global;
    $db=$global["db"];
    $today = getdate();	
    $cur_unix_ts = mktime($today["hours"], $today["minutes"],$today["seconds"], $today["mon"], $today["mday"] , $today["year"]);
    $rep_unix_ts = mktime(substr($last_updated_time_stamp, 10, 3),substr($last_updated_time_stamp, 14, 2),substr($last_updated_time_stamp, 17, 2), substr($last_updated_time_stamp, 5, 2),substr($last_updated_time_stamp, 8, 2) , substr($last_updated_time_stamp, 0, 4));

    $time_diff = ($cur_unix_ts-$rep_unix_ts)/60;
    $query="select option_code from field_options where field_name='opt_rs_rep_freq'";
    $res=$db->Execute($query);
    $frequency=$res->fields["option_code"];
 	if($time_diff>$frequency)
	{
	return true;
	}
	else
	{
	return false;
	}	
}
?>
