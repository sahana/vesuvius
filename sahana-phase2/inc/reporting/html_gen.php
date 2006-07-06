<?php
/**
 * Library for Generating xhtml
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
	var $output_code;
	var $background_color;

	/*
	* The constructor 
	*/
	function genhtml()
		{
		$this->output_code .="<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html>\n<head><title>Sahana Report</title></head>\n<body>\n";
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
		$this->file_name = "/".$name.".html";
		}
		
	function addTitle($title_in='')
		{
		$this->output_code .= "<h3 align='".$this->title_pos."'>".$title_in."</h3>\n<br>\n";
		}

	function setTitlePos($title_pos_in='')
		{
		$this->title_pos = $title_pos_in;
		}

	function addSummary($summary_in='',$alignment='center')
		{
		$this->output_code .= "<p align=".$alignment.">".$summary_in."</p>\n<br>\n";
		}

	function setImage($img_path='')
		{
		$this->output_code .= "<img src='".$img_path."' align='left'/>\n<br>\n";
		}

	function lineBrake()
		{
		$this->output_code .= "<br>\n";
		}
	
	function addTable($header_array='',$data_array='')
		{
		$this->output_code .= "<table border='1' align='center'>\n<tr>";
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

	function addLink($linkLocatoin='',$linkText='')
		{
		$this->output_code .= "<br><a href ='".$linkLocatoin."'>".$linkText."</a>";
		}


	function Output()
		{
		$this->output_code .= "</body>\n</html>\n";
		//echo $this->output_code;


		/**/

		$_sd_path = str_replace('\\', '/', dirname(__FILE__));
		$_sd_path = explode('/', dirname(__FILE__));
		array_pop($_sd_path);
		array_pop($_sd_path);
		$_sd_path = implode('/', $_sd_path);
		
		$_sd_path = $_sd_path."/www/tmp/";
		$data='';
		//echo $_sd_path;

			$f=fopen($_sd_path.$this->file_name,'wb');
			if(!$f)
			$this->Error('Unable to create output file: '.$name);
			fwrite($f,$this->output_code,strlen($this->output_code));
			fclose($f);
	
		
	
		echo "Your chart/Graph has been created in ".$_sd_path;
			/*
		$fp = fopen($_sd_path.$this->output_file, "rb");
			while(!feof($fp)) 
			{
			$data .= fread($fp, 1024); 
			}
			fclose($fp);
			$data = addslashes($data);
			$data = addcslashes($data, "\0");

		$today = getdate();
		$current_date = $today["year"]."-".$today["mon"]."-".$today["mday"];
		$current_time = $today["hours"].":".$today["minutes"].":".$today["seconds"]; 
		$file_size = filesize($_sd_path.$this->output_file)/1000; 
		$file_type = $this->file_format; 
		$title = $this->title_txt;
		$file_name = $this->output_file;
		$the_keyword = $this->keyword;
		$the_owner = $this->report_chart_owner;


		global $global;
    		$db=$global["db"];
		$q="insert into report_files(file_name,file_data,date_of_created,time_of_created,report_chart_owner,file_type,file_size_kb,keyword,title) values ('$file_name','$data','$current_date','$current_time','$the_owner','$file_type','$file_size','$the_keyword','$title')";
    		$res=$db->Execute($q);
	

	//-----------------------------------
		*/

		}


	}


?>