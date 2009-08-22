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
 * @package    moduleAPI
 * @subpackage reporting
 * @author     Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * This function is a internal one which uses by other functions
 *
 * @param string $chart_ID
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */

global $graph;
global $chat_type_flag;

global $d_arr;
$d_arr = array();
global $d_arr_index;
$d_arr_index = 0;

function add_data($x_val,$y_val)
{
global $d_arr;
global $d_arr_index;
$d_arr[$d_arr_index] = array($x_val,$y_val);
$d_arr_index++;
}

 
function base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr_in,$dataArray, $legend='')
{
    include_once( "../3rd/phplot/sahanaphplot.php");
    global $graph;
    global $chat_type_flag;
   
	if($chat_type_flag == 'pie') {	
		$num_arrs = count($dataArray);
		//print_r($num_arrs);
		$final_arr_count = 0;
		$arr_count = 1;
		$final_data_arr = array();
		
		foreach($dataArray as $arr) {	
			$temp = array();
			
			for($i = 0 ; $i < $num_arrs ; $i++) {
			$temp[$i] = 0;
			}
			
			$temp[0] = $arr[0];
			$temp[$arr_count] = $arr[1];
			$arr_count++;

			$final_data_arr[$final_arr_count] = $temp;
			$final_arr_count++;
		}
	} else {
		$num_arrs=count($dataArray);	
		$final_arr_count = 0;
		$final_data_arr = array();
		//print $num_arrs;	
		
		for($i=0;$i<$num_arrs;$i++) {
		$temp_x1 = $dataArray[$i][0];
		$temp_y1 = $dataArray[$i][1];

		$temp = array($temp_x1,$temp_y1);
		
			for($j=$i+1;$j<$num_arrs;$j++) {	
				//print $num_arrs;
				$temp_x2 = $dataArray[$j][0];
				
				if($temp_x1 == $temp_x2) {
				//print $dataArray[$j][1];
				array_push($temp,$dataArray[$j][1]);
				$i++;
				}

			}

		$final_data_arr[$final_arr_count] = $temp;
		$final_arr_count++;
		}
	}
//edit chart size here
    $graph = new SahanaPHPlot(800,275);
    $graph->Setchartid($chart_ID);
    $graph->SetDataType("text-data");  
    $graph->SetDataValues($final_data_arr);
    $graph->SetFileFormat("png"); 
    $graph->SetImageArea(800,275);
    $graph->SetTitleFontSize("5");
    $graph->SetTitle( $title);
    $graph->Setkeyword($keyword_arr_in);
	$legend_arr = array();
	if($chat_type_flag == 'pie') {
	    foreach($final_data_arr as $xval) {
	        array_push($legend_arr,$xval[0]);
	    }
	    $graph->SetLegend($legend_arr); 
	}
	else{
		 if($legend != '')
		     $graph->SetLegend($legend);
	}
	$graph->setLegendPixels(50,10);
    $graph->SetPlotBgColor("red");
    $graph->SetPlotBorderType( "left");
    $graph->SetBackgroundColor('white');
    $graph->SetXTitle($xtitle, "plotdown"); // para = ($title, $position); $postion= plotup or plotdown or both or none
    $graph->SetYTitle($ytitle,"plotleft"); // plotright or plotleft or both or both

	$xval_counter=0;
	$temp_arr = array();
	
	foreach($final_data_arr as $xval) {
	$xval_counter++;
	sort($xval,SORT_NUMERIC);
	array_push($temp_arr,$xval[count($xval)-1]);
	}
	
	sort($temp_arr,SORT_NUMERIC);
	$max_val_y = $temp_arr[count($temp_arr)-1];
	$xval_counter = $xval_counter+1;
	$y_unit = (round($max_val_y, (-(strlen($max_val_y)) + 1)))/10;

    $graph->SetHorizTickIncrement( "1"); 
    $graph->SetVertTickIncrement($y_unit);
    //$graph->SetPrecisionX("0");
    $graph->SetPrecisionY( "0"); 
    $graph->SetYGridLabelType( "data");
    $graph->SetLightGridColor( "blue");
    $graph->SetPlotAreaWorld(0,0,$xval_counter,$max_val_y);
    $graph->SetOutputFile($chart_file_name.".png");
}

/**
 * This function is used to generate pie charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_piechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='')
{
    global $chat_type_flag;
    $chat_type_flag = 'pie';
    global $d_arr;
    global $graph;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr);
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType("pie");
	$graph->DrawGraph();

	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate bar charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_barchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='', $legend='')
{
    global $chat_type_flag;
    $chat_type_flag = 'bar';

    global $d_arr;
    global $graph;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr, $legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "bars");
	$graph->DrawGraph();
	unset($d_arr);
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate area charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_areachart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='')
{
    global $chat_type_flag;
    $chat_type_flag = 'area';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];
    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "area");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate line charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_linechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='', $legend='')
{
    global $chat_type_flag;
    $chat_type_flag = 'line';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr, $legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "lines");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate Line point charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_linepointchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='', $legend='')
{
    global $chat_type_flag;
    $chat_type_flag = 'line_point';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr, $legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "linepoints");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate point charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_pointschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='',$legend='')
{
    global $chat_type_flag;
    $chat_type_flag = 'points';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr,$legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "points");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate thin bar line charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_thinbarlinechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='',$legend='')
{
    global $chat_type_flag;
    $chat_type_flag = 'thin_bar';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr,$legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "thinbarline");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate squared charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_squaredchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='',$legend='')
{
    global $chat_type_flag;
    $chat_type_flag = 'squred';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr,$legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "squared");
	$graph->DrawGraph();	
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function is used to generate stack bar charts
 *
 * @param string $chart_file_name
 * @param string $title
 * @param string $xtitle
 * @param string $ytitle
 * @param mixed $dataArray
 * @param mixed $keyword_arr_in
 * @access public
 * @return void
 */
function generate_stackedbarschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$keyword_arr='',$legend)
{
    global $chat_type_flag;
    $chat_type_flag = 'stacked';
    global $d_arr;
    $backtrace = debug_backtrace();
    $chart_ID = $backtrace['1']["function"];

    global $graph;
    global $global;
    $db=$global["db"];
    //check the timestamp and set whether the update should be taken place or not
    $query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
    $res_found = $db->Execute($query);
    $chart_gen_ok = true;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	global $d_arr_index;
	$d_arr_index = 0;
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$keyword_arr,$d_arr,$legend);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "stackedbars");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br />";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br />";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br />";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br />";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br />";
		}
	}
}

/**
 * This function will return the url to download the chart
 *
 * @param string $chart_id
 * @return string
 */
function shn_chart_download_link($chart_id)
{
    return "index.php?mod=rs&act=download_report&stream=text&rep_id=".$chart_id;
    #return "stream.php?mod=rs&act=download_report&rep_id=".$chart_id;
}

/**
 * This function will return the url to display the chart
 *
 * @param string $chart_id
 * @return string
 */
function shn_chart_display_link($chart_id)
{
    return "index.php?mod=rs&act=download_report&stream=text&rep_id=".$chart_id;
}

/**
 * This function will prompt user to download the chart
 *
 * @param string $chart_id
 * @return string
 */
function shn_chart_download($chart_id,$string)
{
    $link = "index.php?mod=rs&act=download_report&stream=text&rep_id=".$chart_id;
    print "<a href= ".$link."> ".$string." </a>";
}

/**
 * This function will display the chart
 *
 * @param string $chart_id
 * @return string
 */
function shn_chart_display($chart_id)
{
    $link = "index.php?mod=rs&act=download_report&stream=text&rep_id=".$chart_id;
    print "<img src = '".$link."' /> ";
}

/**
 * This function return boolean value of whether the chart generation ok or not.
 *
 * @param string $last_updated_time_stamp
 * @access private
 * @return boolean
 */
function _shn_is_chart_update_OK($last_updated_time_stamp)
{
    global $global;
    $db=$global["db"];
    $today = getdate();	
    $cur_unix_ts = mktime($today["hours"], $today["minutes"],$today["seconds"], $today["mon"], $today["mday"] , $today["year"]);
    $rep_unix_ts = mktime(substr($last_updated_time_stamp, 10, 3),substr($last_updated_time_stamp, 14, 2),substr($last_updated_time_stamp, 17, 2), substr($last_updated_time_stamp, 5, 2),substr($last_updated_time_stamp, 8, 2) , substr($last_updated_time_stamp, 0, 4));

    $time_diff = ($cur_unix_ts-$rep_unix_ts)/60;
    //$query="select option_code from field_options where field_name='opt_rs_cht_freq'";
    //$res=$db->Execute($query);
    //$frequency=$res->fields["option_code"];
    $frequency = $conf['mod_rs_chart_update_interval'] ;
 	if($time_diff>$frequency)
	{
	return true;
	}
	else
	{
	return false;
	}	
}

/**
 * This function return boolean value of whether the chart infomation print ok or not..
 *
 * @param string $last_updated_time_stamp
 * @access private
 * @return boolean
 */
function _shn_is_print_ok()
{
    if(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='search_submit_one')
    {
    return false;
    }
    elseif(trim($_REQUEST['mod'])=='rs' && trim($_REQUEST['act']) =='download_report')
    {
    return false;
    }
    else
    {
    return true;
    }
}


