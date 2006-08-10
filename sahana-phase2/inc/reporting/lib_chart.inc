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

function base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr_in)
{
include_once( "../3rd/phplot/phplot.php");
global $graph;

$graph = new PHPlot(350,200);

$graph->Setchartid($chart_ID);

$graph->SetDataType("text-data");  
$graph->SetDataValues($dataArray);
$graph->SetFileFormat("png"); 
$graph->SetImageArea(350,200);
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

//$graph->SetHorizTickIncrement( "5"); //this should be set according to the data
$graph->SetVertTickIncrement( "500"); //this should be set according to the data

//$graph->SetPrecisionX("1");
$graph->SetPrecisionY( "0"); 

$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetPlotAreaWorld(0,0,7,2030);//this should be modified

$graph->SetOutputFile($chart_file_name.".png");

}

function generate_piechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "pie");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_barchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "bars");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_areachart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "area");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_linechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "lines");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_linepointchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "linepoints");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_pointschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
$backtrace = debug_backtrace();
$chart_ID = $backtrace['1']["function"];

global $graph;
global $global;
$db=$global["db"];
//check the timestamp and set whether the update should be taken place or not
$query = "select rep_id,file_name,file_type,file_size_kb,title,t_stamp from report_files where rep_id = '$chart_ID' ";	
$res_found = $db->Execute($query);
$chart_gen_ok = true;
;

	if($res_found->fields['t_stamp'] != null)
	{
	$chart_gen_ok= (_shn_is_chart_update_OK($res_found->fields['t_stamp'])) ? true : false;
	}

	if($chart_gen_ok)
	{
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "points");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_thinbarlinechart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "thinbarline");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_squaredchart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "squared");
	$graph->DrawGraph();	
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

}

function generate_stackedbarschart($chart_file_name='',$title='',$xtitle='',$ytitle='',$dataArray='',$keyword_arr='')
{
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
	base_elements_of_chart($chart_ID,$chart_file_name,$title,$xtitle,$ytitle,$dataArray,$keyword_arr);
	$graph->SetprintEnable(_shn_is_print_ok());
	$graph->SetPlotType( "stackedbars");
	$graph->DrawGraph();
	}
	else
	{
		if(_shn_is_print_ok())
		{
		print "<h1> Chart - ".$res_found->fields['title']."</h1>";
		print "<b>Chart ID : </b>".$res_found->fields['rep_id']." <br>";
		print "<b>Chart File Name : </b>". $res_found->fields['file_name']."<br>";
		print "<b>Date/Time : </b>".$res_found->fields['t_stamp']."<br>";
		print "<b>File Type : </b>".$res_found->fields['file_type']."<br>";
		print "<b>File Size : </b>".$res_found->fields['file_size_kb']." kb <br>";
		}

	}

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


function chart_download_link($chart_id)
{
return "stream.php?mod=rs&act=download_report&rep_id=".$chart_id;
}

/*********************************private Functions *************************************************************/
function _shn_is_chart_update_OK($last_updated_time_stamp)
{
    global $global;
    $db=$global["db"];
    $today = getdate();	
    $cur_unix_ts = mktime($today["hours"], $today["minutes"],$today["seconds"], $today["mon"], $today["mday"] , $today["year"]);
    $rep_unix_ts = mktime(substr($last_updated_time_stamp, 10, 3),substr($last_updated_time_stamp, 14, 2),substr($last_updated_time_stamp, 17, 2), substr($last_updated_time_stamp, 5, 2),substr($last_updated_time_stamp, 8, 2) , substr($last_updated_time_stamp, 0, 4));

    $time_diff = ($cur_unix_ts-$rep_unix_ts)/60;
    $query="select option_code from field_options where field_name='opt_rs_freq'";
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
/*********************************End of private functions *****************************************************/

?>