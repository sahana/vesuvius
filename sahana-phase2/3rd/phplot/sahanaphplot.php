<?php

include_once("phplot.php");

Class SahanaPHPlot extends PHPlot{
	//my
	var $safe_margin = 5;
	var $legend_x_pos = '100';
    var $legend_y_pos = '100';
	
	var $keyword;
	var $chart_id;
	//var $print_enable;
	
	function SahanaPHPlot($which_width=600, $which_height=800, $which_output_file=NULL, $which_input_file=NULL){
    	PHPlot::PHPlot($which_width,$which_height,$which_output_file,$which_input_file);
	}
	
	function Setkeyword($keyword_arr_in)
	{
		$this->keyword = $keyword_arr_in;
		return TRUE;
	}

	function Setchartid($id_in)
	{
		$this->chart_id = $id_in;
		return TRUE;
	}

	function SetprintEnable($enable_in)
	{
		$this->print_enable = $enable_in;
		return TRUE;
	}

	function PrintImage(){

		global $global;
		$db=$global["db"];

		$_sd_path = str_replace('\\', '/', dirname(__FILE__));
		$_sd_path = explode('/', $_sd_path);
		array_pop($_sd_path);
		array_pop($_sd_path);
		$_sd_path = implode('/', $_sd_path);
		$_sd_path = $_sd_path."/www/tmp/";
		$data='';

		ImagePng($this->img, $_sd_path.$this->output_file);

		$fp = fopen($_sd_path.$this->output_file, "rb");
		while(!feof($fp)) {
			$data .= fread($fp, 1024);
		}
			
		fclose($fp);
		$data = addslashes($data);
		$data = addcslashes($data, "\0");

		$file_size = filesize($_sd_path.$this->output_file)/1024;
		$file_type = $this->file_format;
		$title = $this->title_txt;
		$file_name = $this->output_file;
		$keyword_arr = $this->keyword;
		$the_chart_ID = $this->chart_id;

		unlink($_sd_path.$this->output_file);//delete the file

		$query = "select rep_id from report_files where rep_id = '$the_chart_ID' ";
		$res_found = $db->Execute($query);

		if($res_found->fields['rep_id'] != null)
		{
			$query="update report_files set file_name = '$file_name' , file_data='$data' , t_stamp=now(), file_size_kb = '$file_size', title = '$title' where rep_id='$the_chart_ID' ";
			$res=$db->Execute($query);

			$num_of_keywords=count($keyword_arr);
			$keyword_arr_keys=array_keys($keyword_arr);

			$del_query="delete from report_keywords where rep_id='$the_chart_ID' ";
			$del_res=$db->Execute($del_query);

			for($i=0;$i<$num_of_keywords;$i++)
			{
				$the_keyword_key = $keyword_arr_keys[$i];
				$the_keyword = $keyword_arr[$the_keyword_key];
				$query1="insert into report_keywords(rep_id,keyword_key,keyword) values ('$the_chart_ID','$the_keyword_key','$the_keyword')";
				$res1=$db->Execute($query1);
			}
		}
		else
		{
			$query="insert into report_files(rep_id,file_name,file_data,file_type,file_size_kb,title) values ('$the_chart_ID','$file_name','$data','$file_type','$file_size','$title')";
			$res=$db->Execute($query);

			$num_of_keywords=count($keyword_arr);
			$keyword_arr_keys=array_keys($keyword_arr);

			for($i=0;$i<$num_of_keywords;$i++)
			{
				$the_keyword_key = $keyword_arr_keys[$i];
				$the_keyword = $keyword_arr[$the_keyword_key];
				$query1="insert into report_keywords(rep_id,keyword_key,keyword) values ('$the_chart_ID','$the_keyword_key','$the_keyword')";
				$res1=$db->Execute($query1);
			}
		}

		unset($data);

		$query_ts = "select t_stamp from report_files where rep_id = '$the_chart_ID' ";
		$timestamp_found = $db->Execute($query_ts);

		if($this->print_enable)
		{
			print "<h1> Chart - ".$title."</h1>";
			print "<b>Chart ID : </b>".$the_chart_ID." <br>";
			print "<b>Chart File Name : </b>". $file_name."<br>";
			print "<b>Date/Time : </b>".$timestamp_found->fields['t_stamp']."<br>";
			print "<b>File Type : </b>".$file_type."<br>";
			print "<b>File Size : </b>".$file_size." kb <br>";
		}
		return TRUE;
	}

}

