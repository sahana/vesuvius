<?php
	
     /*
     ###############################################
     ####                                       ####
     ####    Author : Harish Chauhan            ####
     ####    Date   : 31 Dec,2004               ####
     ####    Updated:                           ####
     ####                                       ####
     ###############################################

     */

	 
	 /*
	 * Class is used for save the data into microsoft excel format.
	 * It takes data into array or you can write data column vise.
	 */


	Class ExcelWriter
	{
			
		var $fp=null;
		var $error;
		var $state="CLOSED";
		var $newRow=false;

		var $file_data;
		var $report_id;
		var $print_enable;
		var $file_name;
		var $keywords;


		/*
		* @Params : $file  : file name of excel file to be created.
		* @Return : On Success Valid File Pointer to file
		* 			On Failure return false	 
		*/
		 
		function ExcelWriter($file="")
		{
			return $this->open($file);
		}
		
		/*
		* @Params : $file  : file name of excel file to be created.
		* 			if you are using file name with directory i.e. test/myFile.xls
		* 			then the directory must be existed on the system and have permissioned properly
		* 			to write the file.
		* @Return : On Success Valid File Pointer to file
		* 			On Failure return false	 
		*/
		function open($file)
		{ 
			if($this->state!="CLOSED")
			{
				$this->error="Error : Another file is opend .Close it to save the file";
				return false;
			}	
		
			if(!empty($file))
			{	# edited by sd
				#$this->fp=@fopen($file,"w+");
				#$this->fp=fopen($file,"w+");
				
			}
			else
			{
				$this->error="Usage : New ExcelWriter('fileName')";
				return false;
			}	
			/*if($this->fp==false)
			{
				$this->error="Error: Unable to open/create File.You may not have permmsion to write the file.";
				return false;
			}*/
			$this->state="OPENED";
			#fwrite($this->fp,$this->GetHeader());
			#return $this->fp;
		
			$this->file_data .= $this->GetHeader();
		}


#==============================================================================================

		function SetReportID($rep_id_in = '')
		{
			$this->report_id = $rep_id_in; 
		}
		
		function printInfoEnable($is_ok)
		{
			$this->print_enable = $is_ok;
		}

		function SetReportTitle($title_in)
		{
			$this->title = $title_in;
		}

		function SetFileName($file_name_in)
		{
			$this->file_name = $file_name_in;
		}

		function SetKeywords($keyword_arr_in)
		{
			$this->keywords = $keyword_arr_in;
		}



#==============================================================================================
		
		function close()
		{
			if($this->state!="OPENED")
			{
				$this->error="Error : Please open the file.";
				return false;
			}	
			if($this->newRow)
			{
				$this->file_data .= "</tr>";
				#fwrite($this->fp,"</tr>");
				$this->newRow=false;
			}
			
			#fwrite($this->fp,$this->GetFooter());
			$this->file_data .= $this->GetFooter();
			#fclose($this->fp);


#############################################################################################################

		global $global;
    		$db=$global["db"];

		unset($data);
		$data='';
		$temp = tmpfile();
		fwrite($temp,$this->file_data);
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
			$title = $this->title;
			$file_name =$this->file_name.".xls";
			$the_report_ID = $this->report_id;
			$keyword_arr = $this->keywords;
			
			$query = "select rep_id from report_files where rep_id = '$the_report_ID' ";	
			$res_found = $db->Execute($query);

			if($res_found->fields['rep_id'] != null)
			{
			$query="update report_files set file_name = '$file_name' , file_data='$data' , t_stamp=now(), file_size_kb = '$file_size', title = '$title' where rep_id='$the_report_ID' ";
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
			$query="insert into report_files(rep_id,file_name,file_data,file_type,file_size_kb,title) values ('$the_report_ID','$file_name','$data','$file_type','$file_size','$title')";
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
			
    			
			unset($data);			

			$query_ts = "select t_stamp from report_files where rep_id = '$the_report_ID' ";	
			$timestamp_found = $db->Execute($query_ts);
			/**/
			if($this->print_enable)
			{
				if($res == true)
				{
				print "<h1> Report - ".$title."</h1>";
				print "<b>Report ID : </b>".$the_report_ID." <br />";
				print "<b>Report File Name : </b>". $file_name."<br />";
				print "<b>Date/Time : </b>".$timestamp_found->fields['t_stamp']."<br />";
				//print "<b>Report Owner :</b>".$the_owner."<br />";
				print "<b>File Type : </b>".$file_type."<br />";
				print "<b>File Size : </b>".$file_size." kb <br />";
				//print "<b>Keyword :</b>".$the_keyword."<br>";
				}
				else
				{
				print "<b>Report Creation Failed..</b>";
				}
			}


#############################################################################################################






			$this->state="CLOSED";
			return ;
		}
		/* @Params : Void
		*  @return : Void
		* This function write the header of Excel file.
		*/
		 							
		function GetHeader()
		{
			$header = <<<EOH
				<html xmlns:o="urn:schemas-microsoft-com:office:office"
				xmlns:x="urn:schemas-microsoft-com:office:excel"
				xmlns="http://www.w3.org/TR/REC-html40">

				<head>
				<meta http-equiv=Content-Type content="text/html; charset=us-ascii">
				<meta name=ProgId content=Excel.Sheet>
				<!--[if gte mso 9]><xml>
				 <o:DocumentProperties>
				  <o:LastAuthor>Sahana</o:LastAuthor>
				  <o:LastSaved>2005-01-02T07:46:23Z</o:LastSaved>
				  <o:Version>10.2625</o:Version>
				 </o:DocumentProperties>
				 <o:OfficeDocumentSettings>
				  <o:DownloadComponents/>
				 </o:OfficeDocumentSettings>
				</xml><![endif]-->
				<style>
				<!--table
					{mso-displayed-decimal-separator:"\.";
					mso-displayed-thousand-separator:"\,";}
				@page
					{margin:1.0in .75in 1.0in .75in;
					mso-header-margin:.5in;
					mso-footer-margin:.5in;}
				tr
					{mso-height-source:auto;}
				col
					{mso-width-source:auto;}
				br
					{mso-data-placement:same-cell;}
				.style0
					{mso-number-format:General;
					text-align:general;
					vertical-align:bottom;
					white-space:nowrap;
					mso-rotate:0;
					mso-background-source:auto;
					mso-pattern:auto;
					color:windowtext;
					font-size:10.0pt;
					font-weight:400;
					font-style:normal;
					text-decoration:none;
					font-family:Arial;
					mso-generic-font-family:auto;
					mso-font-charset:0;
					border:none;
					mso-protection:locked visible;
					mso-style-name:Normal;
					mso-style-id:0;}
				td
					{mso-style-parent:style0;
					padding-top:1px;
					padding-right:1px;
					padding-left:1px;
					mso-ignore:padding;
					color:windowtext;
					font-size:10.0pt;
					font-weight:400;
					font-style:normal;
					text-decoration:none;
					font-family:Arial;
					mso-generic-font-family:auto;
					mso-font-charset:0;
					mso-number-format:General;
					text-align:general;
					vertical-align:bottom;
					border:none;
					mso-background-source:auto;
					mso-pattern:auto;
					mso-protection:locked visible;
					white-space:nowrap;
					mso-rotate:0;}
				.xl24
					{mso-style-parent:style0;
					white-space:normal;}
				-->
				</style>
				<!--[if gte mso 9]><xml>
				 <x:ExcelWorkbook>
				  <x:ExcelWorksheets>
				   <x:ExcelWorksheet>
					<x:Name>sheet1</x:Name>
					<x:WorksheetOptions>
					 <x:Selected/>
					 <x:ProtectContents>False</x:ProtectContents>
					 <x:ProtectObjects>False</x:ProtectObjects>
					 <x:ProtectScenarios>False</x:ProtectScenarios>
					</x:WorksheetOptions>
				   </x:ExcelWorksheet>
				  </x:ExcelWorksheets>
				  <x:WindowHeight>10005</x:WindowHeight>
				  <x:WindowWidth>10005</x:WindowWidth>
				  <x:WindowTopX>120</x:WindowTopX>
				  <x:WindowTopY>135</x:WindowTopY>
				  <x:ProtectStructure>False</x:ProtectStructure>
				  <x:ProtectWindows>False</x:ProtectWindows>
				 </x:ExcelWorkbook>
				</xml><![endif]-->
				</head>

				<body link=blue vlink=purple>
				<table x:str border=0 cellpadding=0 cellspacing=0 style='border-collapse: collapse;table-layout:fixed;'>
EOH;
			return $header;
		}

		function GetFooter()
		{
			return "</table></body></html>";
		}
		
		/*
		* @Params : $line_arr: An valid array 
		* @Return : Void
		*/
		 
		function writeLine($line_arr)
		{
			if($this->state!="OPENED")
			{
				$this->error="Error : Please open the file.";
				return false;
			}	
			if(!is_array($line_arr))
			{
				$this->error="Error : Argument is not valid. Supply an valid Array.";
				return false;
			}
			#fwrite($this->fp,"<tr>");
			$this->file_data .= "<tr>";
			foreach($line_arr as $col)
				$this->file_data .= "<td class=xl24 width=64 >$col</td>";
				#fwrite($this->fp,"<td class=xl24 width=64 >$col</td>");
			$this->file_data .= "</tr>";
			#fwrite($this->fp,"</tr>");
		}

		/*
		* @Params : Void
		* @Return : Void
		*/
		function writeRow()
		{
			if($this->state!="OPENED")
			{
				$this->error="Error : Please open the file.";
				return false;
			}	
			if($this->newRow==false)
				$this->file_data .= "<tr>"; 
				#fwrite($this->fp,"<tr>");
			else
				$this->file_data .= "</tr><tr>";
				#fwrite($this->fp,"</tr><tr>");
			$this->newRow=true;	
		}

		/*
		* @Params : $value : Coloumn Value
		* @Return : Void
		*/
		function writeCol($value)
		{
			if($this->state!="OPENED")
			{
				$this->error="Error : Please open the file.";
				return false;
			}
			$this->file_data .= "<td class=xl24 width=64 >$value</td>";	
			#fwrite($this->fp,"<td class=xl24 width=64 >$value</td>");
		}
	}
?>