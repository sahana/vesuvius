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

global $report_type;

function shn_report_fopen($rep_type,$file_name='',$keyword_in='',$dynamic_rep=false,$rep_id=null)
{
    global $report_type;
    $report_type = $rep_type;
    if(NULL==$rep_id){
    $backtrace = debug_backtrace();
    $rep_ID = $backtrace['1']["function"];
    }
    else
    {
    $rep_ID=$rep_id;	
    }
    switch($report_type)
    {
        case 'pdf':
			shn_pdf_report_fopen($rep_ID,$file_name,$keyword_in,$dynamic_rep);
        break;
        case 'ods':
			shn_ods_report_fopen($rep_ID,$file_name,$keyword_in,$dynamic_rep);
            shn_ods_report_add_sheet();
        break;
        case 'xhtml':
            shn_xhtml_report_fopen($rep_ID,$file_name,$keyword_in,$dynamic_rep);
        break;
        case 'xls':
			shn_excel_report_fopen($rep_ID,$file_name,$keyword_in,$dynamic_rep);
        break;
    }
        
}

function shn_report_add_title($title='')
{
    global $report_type;

    switch($report_type)
    {
        case 'pdf':
			shn_pdf_report_add_title($title);
        break;
        case 'ods':
			shn_ods_report_add_title($title);
        break;
        case 'xhtml':
            shn_xhtml_report_add_title($title);
        break;
        case 'xls':
			shn_excel_report_add_title($title);
        break;
    }

}

function shn_report_add_table($headerArray,$dataArray)
{   
    global $report_type;

    switch($report_type)
    {
        case 'pdf':
            shn_pdf_report_add_table($headerArray,$dataArray);
			#header("Content-type: application/pdf");
        break;
        case 'ods':
			shn_ods_report_add_table($headerArray,$dataArray);
        break;
        case 'xhtml':
            shn_xhtml_report_add_table($headerArray,$dataArray);
        break;
        case 'xls':
			shn_excel_report_add_table($headerArray,$dataArray);
        break;
    }

}

function shn_report_add_summary($summary='')
{
    global $report_type;

    switch($report_type)
    {
        case 'pdf':
			shn_pdf_report_add_summery($summary);
        break;
        case 'ods':
			shn_ods_report_add_summery($summary);
        break;
        case 'xhtml':
            shn_xhtml_report_add_summary($summary);
        break;
        case 'xls':
			shn_excel_report_add_summery($summary);
        break;
    }
}

function shn_report_add_sheet($sheet_name ='')
{
    global $report_type;

    switch($report_type)
    {
        case 'ods':
			shn_ods_report_add_sheet($sheet_name);
        break;
//             case 'xls':
// 		shn_excel_report_add_summery($summary);
//             break;
    }
}

function shn_report_add_page()
{
    global $report_type;

    switch($report_type)
    {
       	case 'pdf':
			shn_pdf_report_add_page();
        break;
    }
}


function shn_report_add_image($img_path='')
{
    global $report_type;
    //todo
}

function shn_report_close()
{
    global $report_type;

    switch($report_type)
    {
        case 'pdf':
			shn_pdf_report_close();
        break;
        case 'ods':
			shn_ods_report_close();
        break;
        case 'xhtml':
			shn_xhtml_report_close();
        break;
        case 'xls':
			shn_excel_report_close();
        break;
    }
}


global $calc;
global $sheet;
global $rep_title;
global $ods_keyword;
global $owner;
global $ods_row_counter;
global $ods_rep_ID;
global $ods_rep_gen_ok;
global $ods_file_name;
global $ods_dynamic_rep;

/**
 * This function will open the ods report
 *
 * @param string $file_name
 * @param mixed $keyword_in
 * @access public
 * @return void
 */
function shn_ods_report_fopen($rep_id,$file_name='',$keyword_in='',$dynamic_rep=false)
{
    global $global;
    require_once $global['approot']."3rd/odsgeneration/spreadsheet/OpenOfficeSpreadsheet.class.php";
    $db=$global["db"];
    global $ods_rep_ID;
    global $ods_keyword;
    global $ods_rep_gen_ok;
    global $owner;
    global $ods_file_name;
    global $ods_dynamic_rep;
    $ods_dynamic_rep = false;
    $ods_file_name = $file_name;
    $ods_keyword = $keyword_in;

    #$backtrace = debug_backtrace();
    #$ods_rep_ID = $backtrace['1']["function"];

    $ods_rep_ID = $rep_id;

	if($ods_rep_ID=='_shn_rs_report_creator')
	{
	   $ods_rep_ID =  shn_create_uuid('report');
	}

	if($dynamic_rep)
	{
            $ods_rep_ID = "dynamic_".shn_create_uuid('report');
            $ods_dynamic_rep = true;
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
        $header_array_keys = array();
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
    global $calc;
    global $rep_title;
    global $ods_keyword;
    global $owner;
    global $ods_rep_ID;
    global $ods_file_name;
    global $ods_rep_gen_ok;
    global $rep_title;
    global $ods_dynamic_rep;
    global $global;
    $db=$global["db"];

    if($ods_dynamic_rep == true)
    {
        $print_enable = false;
    }
    else
    {
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
    }

   if($ods_rep_gen_ok)
    {	
        $calc_file_data = $calc->save(true,$rep_title,$ods_keyword,$owner,$ods_rep_ID,$print_enable);	
    
        unset($data);
        $data='';
        $temp = tmpfile();
    
        if ($ods_file_name != '')
        {
            fwrite($temp,$calc_file_data);
            fseek($temp, 0);
                    while(!feof($temp)) 
                    {
                        $data .= fread($temp, 1024); 
                    }
        }
        $data = addslashes($data);
        $data = addcslashes($data, "\0");
        fclose($temp); // this removes the file
    
        $file_size = strlen($data)/1024;
        $file_type = "ods"; 
        $title = $rep_title;
        $file_name = $ods_file_name.".ods";
        $the_owner = $owner;
        $the_report_ID = $ods_rep_ID;
        $keyword_arr = $ods_keyword;
    
        $query = "select rep_id from report_files where rep_id = '$the_report_ID' ";	
        $res_found = $db->Execute($query);
    
        if($res_found->fields['rep_id'] != null)
        {
            $updated = _shn_update_report_file_table($file_name,$data,$file_size,$title,$the_report_ID);
            _shn_delete_report_keywords($the_report_ID);
            _shn_insert_report_keywords($the_report_ID,$keyword_arr);
        }
        else
        {
            $updated = _shn_insert_report_file_table($the_report_ID,$file_name,$data,$file_type,$file_size,$title);
            _shn_insert_report_keywords($the_report_ID,$keyword_arr);
        }
                            
        unset($data);    
        $query_ts = "select t_stamp from report_files where rep_id = '$the_report_ID' ";	
        $timestamp_found = $db->Execute($query_ts);
    
        if($print_enable)
        {
            if($updated)
            {
                _shn_print_report_info($title,$the_report_ID,$file_name,$timestamp_found->fields['t_stamp'],$file_type,$file_size);
            }
            else
            {
                print "<b>Report Creation Failed..</b>";
            }
        }	
    } // end of if($ods_rep_gen_ok) 

    else if(!$ods_rep_gen_ok && $print_enable)
    {
        $query = "select * from report_files where rep_id = '$ods_rep_ID' ";	
        $res = $db->Execute($query);

        _shn_print_report_info($res->fields['title'],$res->fields['rep_id'],$res->fields['file_name'],$res->fields['t_stamp'],$res->fields['file_type'],$res->fields['file_size_kb']);
    }

    if($ods_dynamic_rep)
    {
        print "<b>Download : </b>"; shn_report_download($ods_rep_ID,$ods_file_name.".ods"); print "<br />";
    }
}


global $pdf;
global $pdfreportname;
global $pdf_rep_gen_ok;
global $pdf_print_enable;
global $pdf_rep_ID;
global $pdf_keyword_arr;
global $rep_title;
global $pdf_dynamic_rep;
/**
 * This function will open the pdf report
 *
 * @param string $reportname
 * @param mixed $keywords
 * @access public
 * @return void
 */
function shn_pdf_report_fopen($rep_id,$reportname='',$keywords='',$dynamic_rep=false)
{
    global $global;
    require $global['approot']."3rd/fpdf/fpdf.php";
    global $pdf;
    global $pdfreportname;
    global $pdf_rep_gen_ok;
    global $pdf_print_enable;
    global $pdf_rep_ID;
    global $pdf_keyword_arr;
    global $pdf_dynamic_rep;
    $db=$global["db"];
    $pdfreportname = $reportname;
    $pdf_keyword_arr = $keywords;

    $pdf=new FPDF();
    #$backtrace = debug_backtrace();
    #$rep_id = $backtrace['1']["function"];

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

    if($dynamic_rep)
    {
        $pdf_rep_ID = "dynamic_".shn_create_uuid('report');
        $pdf_dynamic_rep = true;
        $pdf_print_enable = false;
    }
    else
    {
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
    }

    //if report gen is OK it will start generation
    if($pdf_rep_gen_ok)
    {
        $pdf->AddPage();
        #$pdf->SetKeywords($keywords);
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
    global $rep_title;
    $rep_title = $title;

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
 * @param mixed $data    #global $global;
 * @access public
 * @return void
 */
function shn_pdf_report_add_table($header,$data)
{
    global $pdf_rep_gen_ok;
    global $pdf;

    if($pdf_rep_gen_ok)
    {
        #this code will check all the rows of the table, verify whether they have all colomns which are specified in the table header.
        #And this will replace empty colomn values to 20 underscores.
        #if there are colomns, which has only the key but not the value, then it also will replace with 20 underscores.
        $row_arr_keys = array_keys($header);
        $new_data = array();
        foreach($data as $row)
        {	
            $current_row = $row;//array_pop($data);
            for($y=0;$y<count($row_arr_keys);$y++)
            {
                if(!(array_key_exists($row_arr_keys[$y], $current_row)))
                {
                    $current_row[$row_arr_keys[$y]]="____________________";
                }
                if((array_key_exists($row_arr_keys[$y], $current_row)) && !isset($current_row[$row_arr_keys[$y]]))
                {
                    $current_row[$row_arr_keys[$y]]="____________________";
                }	
            }
            array_push($new_data,$current_row);
        }
    
        $data = $new_data;
        #end of replacement
    
        #this code will check for the maximum colomn width of each colomn data
        $size_col_arr = array();
        foreach($data as $row)
        {	
            $row_arr_keys = array_keys($row);
            for($i=0;$i<count($row_arr_keys);$i++)
            {	
                if(!isset($size_col_arr[$row_arr_keys[$i]]))
                {
                    $size_col_arr[$row_arr_keys[$i]] = strlen($row[$row_arr_keys[$i]]);
                }	
                else
                {
                    if($size_col_arr[$row_arr_keys[$i]] < strlen($row[$row_arr_keys[$i]]))
                    {
                        $size_col_arr[$row_arr_keys[$i]] = strlen($row[$row_arr_keys[$i]]);
                    }
                }		
            }
        }# end of checking max value
    
        # this will reduce the size of each colomn by one at each time, until the total of colomn widths are compatible with the page size
        $size_col_arr_keys = array_keys($size_col_arr);
        while((array_sum(array_values($size_col_arr)))> 190 )
        {
            for($x=0;$x<count($size_col_arr_keys);$x++)
            {
                $size_col_arr[$size_col_arr_keys[$x]] = $size_col_arr[$size_col_arr_keys[$x]] - 1;
            }
        }
    
        $pdf->SetFont('Arial','B',6);
        #$pdf->SetWidths(array(30,50,30,40));
        $pdf->SetWidths(array_values($size_col_arr));
    
        //Table Header
        #$pdf->SetFillColor(255,0,0);
        $pdf->SetTextColor(0);
        $pdf->SetDrawColor(128,0,0);
        #$pdf->SetLineWidth(.7);
        $pdf->Row(array_values($header));
    
        //Table body
        $pdf->SetFont('Arial','',6);
        $pdf->SetTextColor(0);
        $pdf->SetDrawColor(128,0,0);
        #$pdf->SetLineWidth(.3);
        foreach($data as $row)
        {
            $pdf->Row(array_values($row));
        }
    }#end of if($pdf_rep_gen_ok)
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
        $pdf->SetFont('Arial','',6);
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
    global $rep_title;
    global $pdf_keyword_arr;
    global $pdf_dynamic_rep;
	
    $keyword_arr = array();
    if($pdf_rep_gen_ok)
    {
        $buffer = $pdf->Output($pdfreportname.".pdf");
        unset($data);
        $data='';
        $temp = tmpfile();
        fwrite($temp,$buffer);
        fseek($temp, 0);

        while(!feof($temp)) 
        {
            $data .= fread($temp, 1024); 
        }
        $data = addslashes($data);
        $data = addcslashes($data, "\0");
        fclose($temp); // this removes the file

        $file_size = strlen($data)/1024;
        $file_type = "pdf"; 
        $title = $rep_title;
        $file_name =$pdfreportname.".pdf";
        $the_report_ID = $pdf_rep_ID;
        $keyword_arr = $pdf_keyword_arr;
			
        $query = "select rep_id from report_files where rep_id = '$the_report_ID' ";	
        $res_found = $db->Execute($query);

            if($res_found->fields['rep_id'] != null)
            {
                $updated = _shn_update_report_file_table($file_name,$data,$file_size,$title,$the_report_ID);    
                _shn_delete_report_keywords($the_report_ID);
                _shn_insert_report_keywords($the_report_ID,$keyword_arr);
            }
            else
            {
                $updated = _shn_insert_report_file_table($the_report_ID,$file_name,$data,$file_type,$file_size,$title);
                _shn_insert_report_keywords($the_report_ID,$keyword_arr);
            }

            unset($data);			

            $query_ts = "select t_stamp from report_files where rep_id = '$the_report_ID' ";	
            $timestamp_found = $db->Execute($query_ts);

            if($pdf_print_enable)
            {
                if($updated)
                {
                    _shn_print_report_info($title,$the_report_ID,$file_name,$timestamp_found->fields['t_stamp'],$file_type,$file_size);
                }
                else
                {
                    print "<b>Report Creation Failed..</b>";
                }
            }

    }
    else if(!$pdf_rep_gen_ok && $pdf_print_enable)
    {
        $query = "select * from report_files where rep_id = '$pdf_rep_ID' ";	
        $res = $db->Execute($query);

        _shn_print_report_info($res->fields['title'],$res->fields['rep_id'],$res->fields['file_name'],$res->fields['t_stamp'],$res->fields['file_type'],$res->fields['file_size_kb']);
    }

        if($pdf_dynamic_rep)
        {
            print "<b>Download : </b>"; shn_report_download($pdf_rep_ID,$pdfreportname.".pdf"); 
            print "<br />";
        }
}

global $xhtml;
global $html_rep_gen_ok;
global $html_print_enable;
global $html_rep_ID;
global $html_file_name;
global $html_keyword_arr;
global $html_title;
global $html_dynamic_rep;
/**
 * This function will open the xhtml report
 *
 * @param string $file_name
 * @param mixed $keyword
 * @access public
 * @return void
 */
function shn_xhtml_report_fopen($rep_id,$file_name='',$keyword='',$dynamic_rep=false)
{
    global $global;
    require_once $global['approot']."inc/reporting/html_gen.php";
    global $xhtml;
    global $html_rep_gen_ok;
    global $html_print_enable;
    global $html_rep_ID;
    global $html_file_name;
    global $html_keyword_arr;
    global $html_dynamic_rep;
    $html_keyword_arr = $keyword;
    $html_file_name = $file_name;
    $db=$global["db"];

    #$backtrace = debug_backtrace();
    #$rep_id = $backtrace['1']["function"];

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

    if($dynamic_rep)
    {
        $html_rep_ID = "dynamic_".shn_create_uuid('report');
        $html_dynamic_rep = true;
        $html_print_enable = false;
    }
    else
    {
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
function shn_xhtml_report_add_title($title='',$position='center')
{
    global $html_rep_gen_ok;
    global $xhtml;
    global $html_title;
    $html_title = $title;

    if($html_rep_gen_ok)
    {
        $xhtml->setTitlePos('center');
        $xhtml->addTitle($title);
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
 * @param string $img_path_in    #global $global;
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
    global $html_file_name;
    global $html_keyword_arr;
    global $html_title;
    global $html_dynamic_rep;

    if($html_rep_gen_ok)
    {
        $output_code = $xhtml->Output();

        $data='';
        $temp = tmpfile();
        fwrite($temp,$output_code);
        fseek($temp, 0);

            while(!feof($temp)) 
            {
                $data .= fread($temp, 1024); 
            }

        $data = addslashes($data);
        $data = addcslashes($data, "\0");
        fclose($temp); // this removes the file
		
        $file_size = strlen($data)/1024;
        $file_type = "xhtml"; 
        $title = $html_title;
        $file_name = $html_file_name.".html";
        #$the_owner = $this->report_owner;
        $the_report_ID = $html_rep_ID;
        $keyword_arr = $html_keyword_arr;
		
        $query = "select rep_id from report_files where rep_id = '$the_report_ID' ";	
        $res_found = $db->Execute($query);

            if($res_found->fields['rep_id'] != null)
            {
                $updated = _shn_update_report_file_table($file_name,$data,$file_size,$title,$the_report_ID);
                _shn_delete_report_keywords($the_report_ID);
                _shn_insert_report_keywords($the_report_ID,$keyword_arr);
            }
            else
            {
                $updated = _shn_insert_report_file_table($the_report_ID,$file_name,$data,$file_type,$file_size,$title);
                _shn_insert_report_keywords($the_report_ID,$keyword_arr);
            }

        $query_ts = "select t_stamp from report_files where rep_id = '$the_report_ID' ";	
        $timestamp_found = $db->Execute($query_ts);

            if($html_print_enable)
            {
                if($updated)
                {
                    _shn_print_report_info($title,$the_report_ID,$file_name,$timestamp_found->fields['t_stamp'],$file_type,$file_size);
                }
                else
                {
                    print "<b>Report Creation Failed..</b>";
                }
            }
    }
    else if(!$html_rep_gen_ok && $html_print_enable)
    {
        $query = "select * from report_files where rep_id = '$html_rep_ID' ";	
        $res = $db->Execute($query);

        _shn_print_report_info($res->fields['title'],$res->fields['rep_id'],$res->fields['file_name'],$res->fields['t_stamp'],$res->fields['file_type'],$res->fields['file_size_kb']);
    }

        if($html_dynamic_rep)
        {
            print "<b>Download : </b>"; shn_report_download($html_rep_ID,$html_file_name.".html"); 
            print "<br />";
        }
}


global $excel;
global $excelreportname;
global $excel_rep_gen_ok;
global $excel_print_enable;
global $excel_rep_ID;
global $excel_keyword_arr;
global $excel_title;
global $excel_dynamic_rep;
/**
 * This function will open the excel report
 *
 * @param string $reportname
 * @param mixed $keywords
 * @access public
 * @return void
 */
function shn_excel_report_fopen($rep_id,$reportname='',$keywords='',$dynamic_rep=false)
{
    global $global;
    require $global['approot']."3rd/excelwriter/excelwriter.inc.php";
    global $excel;
    global $excelreportname;
    global $excel_rep_gen_ok;
    global $excel_print_enable;
    global $excel_rep_ID;
    global $excel_keyword_arr;
    global $excel_dynamic_rep;
    $db=$global["db"];

    $excel_keyword_arr = $keywords;
    $excelreportname = $reportname;
    $excel=new ExcelWriter($excelreportname);

    #$backtrace = debug_backtrace();
    #$rep_id = $backtrace['1']["function"];

    $excel_rep_ID = $rep_id;

    //check the timestamp and set whether the update should be taken place or not
    $query = "select t_stamp from report_files where rep_id = '$rep_id' ";	
    $res_found = $db->Execute($query);
    $excel_rep_gen_ok = true;

    if($res_found->fields['t_stamp'] != null)
    {
        $excel_rep_gen_ok= (_shn_is_report_update_OK($res_found->fields['t_stamp'])) ? true : false;
    } 

    if($rep_id=='_shn_rs_report_creator')
    {
        $rep_id =  shn_create_uuid('report');
    }

    if($dynamic_rep)
    {
        $excel_rep_ID = "dynamic_".shn_create_uuid('report');
        $excel_dynamic_rep = true;
        $excel_print_enable = false;
    }
    else
    {
        if(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='search_submit_one')
        {
            $excel->printInfoEnable(false);
            $excel_print_enable = false;
        }
        elseif(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='download_report')
        {
            $excel->printInfoEnable(false);
            $excel_print_enable = false;
        }
        else
        {
            $excel->printInfoEnable(true);
            $excel_print_enable = true;
        }
    }

    //if report gen is OK it will start generation
    if($excel_rep_gen_ok)
    {
        $excel->SetKeywords($keywords);
        $excel->SetReportID($rep_id);	
        $excel->SetFileName($excelreportname);
    }
}


/**
 * This function will add a title to the excel report
 *
 * @param string $title
 * @access public
 * @return void
 */
function shn_excel_report_add_title($title='')
{
    global $excel_rep_gen_ok;
    global $excel;
    global $excel_title;

    $excel_title = $title;

    if($excel_rep_gen_ok)
    {
        $excel->SetReportTitle($title);
	$tile_arr = array();
	array_push($tile_arr,$title);
	$excel->writeLine($tile_arr);
    }
}

/**
 * This function will add a table to the excel report
 *
 * @param mixed $header
 * @param mixed $data
 * @access public
 * @return void
 */
function shn_excel_report_add_table($header,$data)
{
    global $excel_rep_gen_ok;
    global $excel;

    if($excel_rep_gen_ok)
    {
        #write the table header
        $excel->writeLine($header);
        
        foreach ($data as $row)
        {
            $excel->writeRow();
            foreach ($row as $col)
            {
                $excel->writeCol($col);
            }
        }	 
    }#end of if($excel_rep_gen_ok)
}

/**
 * This function will add a paragraph to the excel report
 *
 * @param string $txt
 * @access public
 * @return void
 */
function shn_excel_report_add_summery($txt='')
{
    global $excel_rep_gen_ok;
    global $excel;
    if($excel_rep_gen_ok)
    {
	# todo	
    }
}

/**
 * This function will add an image to the excel report
 *
 * @param string $img_path
 * @access public
 * @return void
 */
function shn_excel_report_add_image($img_path='')
{	
    global $excel_rep_gen_ok;
    global $excel;
    if($excel_rep_gen_ok)
    {
	#todo
    }
}

/**
 * This function will close the pdf report
 *
 * @access public
 * @return void
 */
function shn_excel_report_close()
{
    global $global;
    $db=$global["db"];
    global $excel;
    global $excelreportname;
    global $excel_rep_gen_ok;
    global $excel_print_enable;
    global $excel_rep_ID;
    global $excel_keyword_arr;
    global $excel_title;
    global $excel_dynamic_rep;

    if($excel_rep_gen_ok)
    {
        $file_data = $excel->close();

        unset($data);
        $data='';
        $temp = tmpfile();
        fwrite($temp,$file_data);
        fseek($temp, 0);

            while(!feof($temp)) 
            {
            $data .= fread($temp, 1024); 
            }

        $data = addslashes($data);
        $data = addcslashes($data, "\0");
        fclose($temp); // this removes the file

        $file_size = strlen($data)/1024;
        $file_type = "xls"; 
        $title = $excel_title;
        $file_name =$excelreportname.".xls";
        $the_report_ID = $excel_rep_ID;
        $keyword_arr = $excel_keyword_arr;
			
        $query = "select rep_id from report_files where rep_id = '$the_report_ID' ";	
        $res_found = $db->Execute($query);

            if($res_found->fields['rep_id'] != null)
            {
                $updated = _shn_update_report_file_table($file_name,$data,$file_size,$title,$the_report_ID);
                _shn_delete_report_keywords($the_report_ID);
                _shn_insert_report_keywords($the_report_ID,$keyword_arr);
            }
            else
            {
                $updated = _shn_insert_report_file_table($the_report_ID,$file_name,$data,$file_type,$file_size,$title);
                _shn_insert_report_keywords($the_report_ID,$keyword_arr);
            }
				
        unset($data);			

        $query_ts = "select t_stamp from report_files where rep_id = '$the_report_ID' ";	
        $timestamp_found = $db->Execute($query_ts);
			
        if($excel_print_enable)
        {
            if($updated)
            {
                _shn_print_report_info($title,$the_report_ID,$file_name,$timestamp_found->fields['t_stamp'],$file_type,$file_size);
            }
            else
            {
                print "<b>Report Creation Failed..</b>";
            }
        }

    }
    else if(!$excel_rep_gen_ok && $excel_print_enable)
    {
        $query = "select * from report_files where rep_id = '$excel_rep_ID' ";	
        $res = $db->Execute($query);
    
        _shn_print_report_info($res->fields['title'],$res->fields['rep_id'],$res->fields['file_name'],$res->fields['t_stamp'],$res->fields['file_type'],$res->fields['file_size_kb']);
    }

        if($excel_dynamic_rep)
        {
        print "<b>Download : </b>"; shn_report_download($excel_rep_ID,$excelreportname.".xls"); 
        print "<br />";
        }
}


/**
 * This function will return the download url for the particular report/chart ID.
 *
 * @param string $report_id
 * @access public
 * @return string
 */
function report_download_link($report_id)
{
    return "index.php?mod=rs&act=download_report&stream=text&rep_id=".$report_id;
}

function shn_report_download($report_id,$string)
{
    $link = "index.php?mod=rs&act=download_report&stream=text&rep_id=".$report_id;
    print "<a href= ".$link."> ".$string." </a>";
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

function _shn_update_report_file_table($file_name,$data,$file_size,$title,$the_report_ID)
{
    global $global;
    $db=$global["db"];

    $query="update report_files set file_name = '$file_name' , file_data='$data' , t_stamp=now(), file_size_kb = '$file_size', title = '$title' where rep_id='$the_report_ID' ";
    $res=$db->Execute($query);

    return true;
}

function _shn_insert_report_file_table($the_report_ID,$file_name,$data,$file_type,$file_size,$title)
{
    global $global;
    $db=$global["db"];

    $query="insert into report_files(rep_id,file_name,file_data,file_type,file_size_kb,title) values ('$the_report_ID','$file_name','$data','$file_type','$file_size','$title')";
    $res=$db->Execute($query);

    return true;
}

function _shn_delete_report_keywords($the_report_ID)
{
    global $global;
    $db=$global["db"];

    $del_query="delete from report_keywords where rep_id='$the_report_ID' ";
    $del_res=$db->Execute($del_query);
}

function _shn_insert_report_keywords($the_report_ID,$keyword_arr)
{
    global $global;
    $db=$global["db"];
    $keyword_arr = array();
    $num_of_keywords=count($keyword_arr);
    $keyword_arr_keys=array_keys($keyword_arr);
        for($i=0;$i<$num_of_keywords;$i++)
        {
            $the_keyword_key = $keyword_arr_keys[$i];
            $the_keyword = $keyword_arr[$the_keyword_key];
            $query1="insert into report_keywords(rep_id,keyword_key,keyword) values ('$the_report_ID','$the_keyword_key','$the_keyword')";
            $res1=$db->Execute($query1);
        }
}

/**
 * This function will print information about a report.
 *
 * @param string $title
 * @param string $the_report_ID
 * @param string $file_name
 * @param string $timestamp
 * @param string $file_type
 * @param string $file_size
 * @access private
 * @return void
 */

function _shn_print_report_info($title,$the_report_ID,$file_name,$timestamp,$file_type,$file_size)
{
    print "<h1> Report - ".$title."</h1>";
    print "<b>Download : </b>"; shn_report_download($the_report_ID,$file_name); print "<br />";
    print "<b>Report ID : </b>".$the_report_ID." <br />";
    print "<b>Report File Name : </b>". $file_name."<br />";
    print "<b>Date/Time : </b>".$timestamp."<br />";
    print "<b>File Type : </b>".$file_type."<br />";
    print "<b>File Size : </b>".$file_size." kb <br />";
}

