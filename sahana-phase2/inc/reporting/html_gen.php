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
		$this->output_code .= "<h3 align='".$this->title_pos."'>".$title_in."</h3>\n<br />\n";
		$this->title_txt = $title_in;
		}

	function setTitlePos($title_pos_in='')
		{
		$this->title_pos = $title_pos_in;
		}
	
	function addSummary($summary_in='')
		{
		$this->output_code .= "<p align='".$this->summary_pos."'>".$summary_in."</p>\n<br />\n";
		}

	function setSummaryPos($summary_pos_in="center")
		{
		$this->summary_pos = $summary_pos_in;
		} 

	function addImage($img_path='')
		{
		$this->output_code .= "<img src='".$img_path."/>\n<br />\n";
		}


	function lineBrake()
		{
		$this->output_code .= "<br />\n";
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
			$this->output_code .= "</table>\n<br />\n";
		}
	
	function setTablePos($table_pos_in='center')
		{
		$this->table_pos = $table_pos_in;	
		}

	function addLink($linkLocatoin='',$linkText='')
		{
		$this->output_code .= "<br /><a href ='".$linkLocatoin."'>".$linkText."</a>";
		}

	function printInfoEnable($is_ok)
		{
		$this->print_enable = $is_ok;
		}

	function Output()
		{
		$this->output_code .= "</body>\n</html>\n";
		return $this->output_code;
		}//end of out put function
	}//end of html_gen class

