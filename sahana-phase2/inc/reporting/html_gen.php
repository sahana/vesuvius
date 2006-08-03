<?php
/**
 * Library for Generating xhtml Report
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
class genhtml
	{

	var $file_name;
	var $title_pos;
	var $title_txt;

	var $summary_pos;	
	var $table_pos;
	var $image_pos;	

	var $output_code;
	var $background_color;
	var $file_format;

	var $keyword;
	var $report_owner;
	var $extention;
	var $report_id;
	var $print_enable;
	/*
	* The constructor 
	*/
	function genhtml()
		{
		$this->output_code .="<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html>\n<head><title>Sahana Report</title></head>\n<body>\n";
		$this->file_format = "xhtml";
		$this->extention = ".html";
		}	

	/*
	*set file name
	*/
	function setFileName($name='')
		{
			if($name=='')
			{
			$name = "sahana_report";
			}
		$this->file_name = $name;
		}
		
	function setKeyword($keyword_in='')
		{
		$this->keyword = $keyword_in;
		}

	function setOwner($owner_in='')
		{
		$this->report_owner = $owner_in;
		}

	function setReportID($report_id_in = '')
		{
		$this->report_id = $report_id_in;
		}


	function addTitle($title_in='')
		{
		$this->output_code .= "<h3 align='".$this->title_pos."'>".$title_in."</h3>\n<br>\n";
		$this->title_txt = $title_in;
		}

	function setTitlePos($title_pos_in='')
		{
		$this->title_pos = $title_pos_in;
		}
	
	function addSummary($summary_in='')
		{
		$this->output_code .= "<p align='".$this->summary_pos."'>".$summary_in."</p>\n<br>\n";
		}

	function setSummaryPos($summary_pos_in="center")
		{
		$this->summary_pos = $summary_pos_in;
		} 

	function addImage($img_path='')
		{
		$this->output_code .= "<img src='".$img_path."/>\n<br>\n";
		}


	function lineBrake()
		{
		$this->output_code .= "<br>\n";
		}
	
	function addTable($header_array='',$data_array='')
		{
		$this->output_code .= "<table border='1' align='".$this->table_pos."'>\n<tr>";
		$header_keys = array_keys($header_array);
		for($i=0;$i<count($header_array);$i++)
			{
			$the_key = $header_keys[$i];
			$this->output_code .= "<th>".$header_array[$the_key]."</th>\n";
			}	
			$this->output_code .= "</tr>\n";
	
		foreach($data_array as $one_data_raw)
			{
				$data_raw_keys = array_keys($one_data_raw);
					$this->output_code .= "<tr>";
					for($i=0;$i<count($one_data_raw);$i++)
						{
							$the_data_key = $data_raw_keys[$i];
							$this->output_code .= "<td>".$one_data_raw[$the_data_key]."</td>\n";
						}	
					$this->output_code .= "</tr>\n";
			}
			$this->output_code .= "</table>\n<br>\n";
		}
	
	function setTablePos($table_pos_in='center')
		{
		$this->table_pos = $table_pos_in;	
		}

	function addLink($linkLocatoin='',$linkText='')
		{
		$this->output_code .= "<br><a href ='".$linkLocatoin."'>".$linkText."</a>";
		}

	function printInfoEnable($is_ok)
		{
		$this->print_enable = $is_ok;
		}

	function Output()
		{
		$this->output_code .= "</body>\n</html>\n";
		
		global $global;
    		$db=$global["db"];

		$temp = tmpfile();
		fwrite($temp,$this->output_code);
		fseek($temp, 0);
		while(!feof($temp)) 
		{
		$data .= fread($temp, 1024); 
		}
		$data = addslashes($data);
		$data = addcslashes($data, "\0");

		fclose($temp); // this removes the file
		
		$file_size = strlen($data)/1000;
		$file_type = $this->file_format; 
		$title = $this->title_txt;
		$file_name = $this->file_name.$this->extention;
		$the_owner = $this->report_owner;
		$the_report_ID = $this->report_id;

		$keyword_arr = $this->keyword;
		
		$query = "select rep_id from report_files where rep_id = '$the_report_ID' ";	
		$res_found = $db->Execute($query);

		
		if($res_found->fields['rep_id'] != null)
			{
		$query="update report_files set file_name = '$file_name' , file_data='$data' ,t_stamp=now(),report_chart_owner = '$the_owner' , file_size_kb = '$file_size' ,title = '$title' where rep_id='$the_report_ID' ";
			$res=$db->Execute($query);

			$num_of_keywords=count($keyword_arr);
			$keyword_arr_keys=array_keys($keyword_arr);

			$del_query="delete from report_keywords where rep_id='$the_report_ID' ";
			$del_res=$db->Execute($del_query);

				for($i=0;$i<$num_of_keywords;$i++)
				{
				$the_keyword_key = $keyword_arr_keys[$i];
				$the_keyword = $keyword_arr[$the_keyword_key];

				$query1="insert into report_keywords(rep_id,keyword_key,keyword) values ('$the_report_ID','$the_keyword_key','$the_keyword')";

				$res1=$db->Execute($query1);
				}

			}
		else
			{
			$query="insert into report_files(rep_id,file_name,file_data,report_chart_owner,file_type,file_size_kb,title) values ('$the_report_ID','$file_name','$data','$the_owner','$file_type','$file_size','$title')";
			$res=$db->Execute($query);
			
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

			$query_ts = "select t_stamp from report_files where rep_id = '$the_report_ID' ";	
			$timestamp_found = $db->Execute($query_ts);

			if($this->print_enable)
			{
				if($res == true)
				{
				print "<h1> Report - ".$title."</h1>";
				print "<b>Report ID : </b>".$the_report_ID." <br>";
				print "<b>Report File Name : </b>". $file_name."<br>";
				print "<b>Date/Time : </b>".$timestamp_found->fields['t_stamp']."<br>";
				print "<b>Report Owner :</b>".$the_owner."<br>";
				print "<b>File Type : </b>".$file_type."<br>";
				print "<b>File Size : </b>".$file_size." kb <br>";
				//print "<b>Keyword :</b>".$the_keyword."<br>";
				}
				else
				{
				print "<b>Report Creation Failed..</b>";
				}
			}
	
		}


	}//end of html_gen class


?>