<?php
/*
 +--------------------------------------------------------------------------+
 | phpMyBackupPro                                                           |
 +--------------------------------------------------------------------------+
 | Copyright (c) 2004-2007 by Dirk Randhahn                                 |                               
 | http://www.phpMyBackupPro.net                                            |
 | version information can be found in definitions.php.                     |
 |                                                                          |
 | This program is free software; you can redistribute it and/or            |
 | modify it under the terms of the GNU General Public License              |
 | as published by the Free Software Foundation; either version 2           |
 | of the License, or (at your option) any later version.                   |
 |                                                                          |
 | This program is distributed in the hope that it will be useful,          |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of           |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            |
 | GNU General Public License for more details.                             |
 |                                                                          |
 | You should have received a copy of the GNU General Public License        |
 | along with this program; if not, write to the Free Software              |
 | Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,USA.|
 +--------------------------------------------------------------------------+
*/

require_once("login.php");

// forward to index.php in mu mode and if this page is disabled
if ($_SESSION['multi_user_mode'] && !$PMBP_MU_CONF['allow_sql_queries']) {
    header("Location: index.php");
}

PMBP_print_header(ereg_replace(".*/","",$_SERVER['SCRIPT_NAME']));

// used variables
$sql_print=FALSE;
if (!isset($_POST['sql_query'])) $_POST['sql_query']=FALSE;
if (!isset($_POST['sql_file'])) $_POST['sql_file']=FALSE;
if (!isset($_FILES['sql_file'])) $_FILES['sql_file']=FALSE;

// if first use or no db-connection is possible
if (!$con=@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd'])) echo "<div class=\"red_left\">".I_SQL_ERROR."</div><br>";
    
// if sql_query was send to db
if (($_POST['sql_query'] || $_FILES['sql_file']) && $_POST['db']) {

    // get start time to calculate duration
    if (function_exists("microtime")) {
        $microtime=explode(" ",microtime());
        $starttime=($microtime[0]+$microtime[1]);
    } else {
        $starttime=time();
    }

    // set php timelimit
    @set_time_limit($CONF['timelimit']);
    @ignore_user_abort(TRUE);

    // get the submited file
    if (is_uploaded_file($_FILES['sql_file']['tmp_name'])) {
            
        // run big_import.php
        if (isset($_POST['fragmented'])) {
            $filename=PMBP_EXPORT_DIR.$_FILES['sql_file']['name'];
            // rename to make it consistent
            @rename($_FILES['sql_file']['tmp_name'],$filename);
            if (file_exists($filename)) {
                echo "<script type=\"text/javascript\">\n";
                // set delete to 1 to delete the renamed file afterwards
                echo "window.onload=popUp(\"big_import.php?fn=".$filename."&delete=1&dbn=".$_POST['db']."\",\"".B_IMPORT."\",\"".$CONF['confirm']."\",\"".B_CONF_IMP."\");\n";
                echo "\n</script>";
            }

        // standard import
        } else {        

	        // trim lines and remove comments
	        $sql_file="";
	
			// remove comments and store sql queries in $sql_file		
	        while($line=PMBP_getln($_FILES['sql_file']['tmp_name'],false,$_FILES['sql_file']['name'])) {
	        	if (trim($line) && substr(trim($line),0,1)!="#" && substr(trim($line),0,2)!="--") $sql_file.=trim($line)."\n";	
	        }
	        PMBP_getln($_FILES['sql_file']['tmp_name'],true,$_FILES['sql_file']['name']);
	        
	        // do everything below once for the POST-data and once for the file
	        $file_and_post=array($_POST['sql_query'],$sql_file);

/*
// alternative code instead of the paragraph before:
// it uses exec_sql for executing the sql queries but does not output any query results!!!

		    // extract zip file
		    if (PMBP_file_info("comp",$_FILES['sql_file']['name'])=="zip") {
				include_once("pclzip.lib.php");
				$pclzip = new PclZip($_FILES['sql_file']['tmp_name']);
				$extracted_file=$pclzip->extractByIndex(0,"./".PMBP_EXPORT_DIR,"");
				if ($pclzip->error_code!=0) $error="plczip: ".$pclzip->error_string."<br>".BI_BROKEN_ZIP."!";
				$filename="./".PMBP_EXPORT_DIR.$extracted_file[0]["stored_filename"];
				unset($pclzip);	
		    }

			$resultArray=PMBP_exec_sql($filehandler=gzopen($filename,"r"),$con);
			@gzclose($filehandler);
			@unlink($filename);
			print_r($resultArray);
*/
        }
    }

    if(!isset($file_and_post)) {
        $file_and_post=array($_POST['sql_query']);
    }

	// for standard imports
	if (!isset($_POST['fragmented'])) {

	    // $key > 0 when the source was a file
	    foreach($file_and_post as $key=>$sql_queries) {
	        // select the db
	        if (!$key) mysql_select_db($_POST['db']);
	
	        // replace these strings in the sql query. Do you know any more or a better way?
	        if (!$key) {
	            $str_find=array("\\'",'\\"',"\\\\");  //"
	            $str_repl=array("'",'"',"\\");        //"
	            $sql_queries=str_replace($str_find,$str_repl,$sql_queries);
	            $sql_print=$sql_queries;
	        }
	
	        // separate sql queries and remove empty queries
	        $all_queries=str_replace(";\n",";|:-:--:-:|",$sql_queries);
	        $all_queries=str_replace(";\r\n",";|:-:--:-:|",$all_queries);
	        $queries=explode("|:-:--:-:|",$all_queries);
	
	        // to remove empty rows
	        $all_queries="";
	        foreach($queries as $number=>$query)
	            if (strlen($query)>1) $all_queries[$number]=$query;
	
	        // execute sql queries
	        $i=0;
	        $sql_error=FALSE;
	

            if (is_array($all_queries)) {
                foreach($all_queries as $query) {            
                    $i++;
                    if (!$key) echo "<div class=\"bold_left\">".SQ_RESULT." ".$i.":</div>\n";
    
                    // error if: no result AND error is not 'empty result' OR: error is empty result and its the first error
                    if ((!$res=mysql_query($query) AND mysql_errno()!=1065) OR (mysql_errno()==1065 AND !$sql_error)){
                        echo $query."\n<div class=\"red_left\">".mysql_error()."</div><br>\n";
                        if ($key) $sql_error.="F".$i.", "; else $sql_error.=$i.", ";
                    } elseif (mysql_errno()!=1065) {
    
                        // print result table
                        if (!$key) {
                            echo "<table>\n";
    
                            // print field names
                            echo "<tr>\n";
                            for($j=0,$field_names="";$field_names[]=@mysql_field_name($res,$j);$j++)
                                echo "<th class=\"active\">".$field_names[$j]."</th>";
                            echo "</tr>\n";
    
                            // print query results
                            $result_exists=FALSE;
                            while($result=@mysql_fetch_array($res,MYSQL_NUM)) {
                                $result_exists=TRUE;
                                if (!$key) echo "<tr ".PMBP_change_color("#FFFFFF","#000000").">";
                                foreach($result as $field)
                                    if ($field!="" && !$key) echo "<td class=\"list\">".htmlentities($field)."</td>"; else echo "<td class=\"list\">&nbsp;</td>";
                                if (!$key) echo "</tr>\n";
                            }
                            
                            // print number of rows or if empty mysql result print number of affected rows
                            if (!$result_exists) {
                                if (!$key) echo "<tr>\n<td>".SQ_SUCCESS."</td>\n</tr>\n";
                                if (!$affected=@mysql_affected_rows()) $affected=0;
                            } else {
                                if (!$affected=@mysql_num_rows($res)) $affected=0;
                            }
                            
                            echo "<tr>\n<td colspan=\"".$j."\">".SQ_AFFECTED.": ".$affected."</td>\n</tr>\n";
                            echo "</table><br>\n";
                        }
                    }
                }
            }

	        if (!$key && isset($_FILES['sql_file']['filename'])) echo "======== ".$_FILES['sql_file']['name']." ========<br>\n";
	    }
	}
    
    // print errors and final message if the import was not fragmented
    if (!isset($_POST['fragmented'])) {
        // print errors or message of success
        if ($sql_error) echo "<div class=\"red_left\">".SQ_ERROR." ".$sql_error."</div>\n";
            else echo "<div class=\"green_left\">".SQ_SUCCESS."</div>\n";
    
        // print execution duration
        if (function_exists("microtime")) {
            $microtime=explode(" ",microtime());
            $endtime=($microtime[0]+$microtime[1]);
        } else {
            $endtime=time();
        }
        echo "<div class=\"bold_left\">".F_DURATION.": ".number_format($endtime-$starttime,3)." ".F_SECONDS."</div><br><br>\n";
    }
}

// print html form and show last selected database and last queries
echo "<form action=\"sql_query.php\" method=\"post\" name=\"sql\" enctype=\"multipart/form-data\">\n<div>\n";
echo "<div class=\"bold_left\">".SQ_WARNING."</div>\n";

// print database select
echo SQ_SELECT_DB.":<br><select name=\"db\">";
    if (count(PMBP_get_db_list())>0) foreach(PMBP_get_db_list() as $db) {
    	$selected="";
        if (isset($_POST['db']))
        	if ($_POST['db']==$db) $selected=" selected";

        echo "<option value='".$db."'".$selected.">".$db."</option>\n";
    } else {
        echo "<option></option>\n";
    }
echo "</select>\n<br>";

// print sql textarea and submit button
echo "<br>".SQ_INSERT.":<br>\n<textarea name=\"sql_query\" rows=\"10\" cols=\"80\">".$sql_print."</textarea>";
echo "<input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"3000000\">";
echo "<br><br>".SQ_FILE.":<br>\n<input type=\"file\" name=\"sql_file\">".$_POST['sql_file'];
echo "<br><br>\n<input type=\"submit\" value=\"".SQ_SEND."\" class=\"button\">\n";
echo "\n&nbsp;&nbsp;&nbsp;&nbsp;(<input name=\"fragmented\" type=\"checkbox\" class=\"button\"> ".B_IMPORT_FRAG.")<br>\n";
echo "</div>\n</form>\n";
PMBP_print_footer();
?>
