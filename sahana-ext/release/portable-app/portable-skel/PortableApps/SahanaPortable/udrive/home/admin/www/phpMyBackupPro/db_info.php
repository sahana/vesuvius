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

// used variables
if (!isset($_GET['table'])) $_GET['table']=FALSE;

// connect to mySQL
$con=@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd']);

    // get start time to calculate duration
    if (function_exists("microtime")) {
        $microtime=explode(" ",microtime());
        $starttime=($microtime[0]+$microtime[1]);
    } else {
        $starttime=time();
    }

// tables info popUp
if ($_GET['table']) {

    // select the db
    mysql_select_db($_GET['table']);

    $stati=mysql_query("show table status");
    while($status=mysql_fetch_array($stati)) {
        $table_names[]=$status['Name'];
        $table_rows[]=$status['Rows'];
        $size=PMBP_size_type($status['Data_length']+$status['Index_length']);
        $table_size[]=$size['value']." ".$size['type'];
    }
    
    // get number of fields
    if (is_array($table_names))
    foreach($table_names as $table) {
        mysql_query("show columns from `".$table."`");
        $table_fields[]=mysql_affected_rows();
    }

    echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"
   \"http://www.w3.org/TR/html4/loose.dtd\">
<html".ARABIC_HTML.">
<head>
<title>phpMyBackupPro - ".F_DB_INFO."</title>
<meta http-equiv=\"Content-Type\" content=\"text/html;charset=".BD_CHARSET_HTML."\">
<link rel=\"stylesheet\" href=\"./".PMBP_STYLESHEET_DIR.$CONF['stylesheet'].".css\" type=\"text/css\">\n";
readfile(PMBP_JAVASCRIPTS);
echo "</head>
<body class=\"white\">
<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\" width=\"100%\">\n
<tr><th colspan=\"4\" class=\"active\">\n";
echo PMBP_image_tag("logo.png","phpMyBackupPro PMBP_WEBSITE",PMBP_WEBSITE);
echo " ".PMBP_VERSION."</th></tr>\n";

    echo "<tr>\n<td colspan=\"4\"><br><div class=\"bold_left\">".DB_TAB_TITLE.$_GET['table'].":</div><br></td>\n</tr>\n";
    echo "<tr>\n<th class=\"active\">".DB_TAB_NAME."</th>\n<th class=\"active\">".DB_TAB_COLS."</th>\n<th class=\"active\">".DB_NUM_ROWS."</th>\n<th class=\"active\">".DB_SIZE."</th>\n</tr>\n";
    for($i=0;$i<count($table_names);$i++) {
        echo "<tr ".PMBP_change_color("#FFFFFF","#000000").">\n<th class=\"active\">".$table_names[$i]."</th>\n<td class=\"list\">".$table_fields[$i]."</td>";
        echo "\n<td class=\"list\">".$table_rows[$i]."</td>\n<td class=\"list\">".$table_size[$i]."</td>\n</tr>\n";
    }
    
    // show execution duration
    if (function_exists("microtime")) {
        $microtime=explode(" ",microtime());
        $endtime=($microtime[0]+$microtime[1]);
    } else {
        $endtime=time();
    }
    echo "<tr>\n<td colspan=\"4\">\n<br><div class=\"bold_left\">".F_DURATION.": ".number_format($endtime-$starttime,3)." ".F_SECONDS."</div>\n</td>\n</tr>\n";
    echo "</table>\n</body>\n</html>";
    exit;
}

PMBP_print_header(ereg_replace(".*/","",$_SERVER['SCRIPT_NAME']));

// if first use or no db-connection possible
if (!$con) {
	echo "<div class=\"red\">".I_SQL_ERROR."</div>";
}
//else
{

	echo "<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\" width=\"100%\">\n";
	
	// list all databases
	$all_dbs=PMBP_get_db_list();
	
	if (count($all_dbs)) {
	    natsort($all_dbs);
	
	    echo "<tr>\n<th class=\"active\">".DB_NAME."</th>\n<th class=\"active\">".DB_NUM_TABLES."</th>\n<th class=\"active\">".DB_NUM_ROWS."</th>\n<th class=\"active\">".DB_SIZE."</th>\n</tr>\n";
	
	    // print html table
	    foreach($all_dbs as $db_name) {
	
	        // select the db
	        mysql_select_db($db_name,$con);
	        
	        $num_tables=$num_rows=$data_size=0;
	        
	        // get number of rows and size of tables
	        $stati=mysql_query("show table status",$con);
	        while ($status=@mysql_fetch_array($stati)) {
	            $data_size+=($status['Data_length']+$status['Index_length']);
	            $num_rows+=$status['Rows'];
	        }
	        $size=PMBP_size_type($data_size);
	
	        // get number of tables
	        $num_tables=mysql_affected_rows($con);
	    
	        // first field for the db name
	        echo "<tr ".PMBP_change_color("#FFFFFF","#000000").">";
	        echo "\n<th class=\"active\">\n".$db_name;
	        if ($num_tables>0) echo "<span class=\"standard\">".PMBP_pop_up("db_info.php?table=".$db_name," [".DB_TABLES."]","view")."</span>";
	            elseif ($num_tables<0) $num_tables="<span class=\"red\">".C_WRONG_DB."</span>";
	        echo "\n</th>\n";
	        echo "<td class=\"list\">".$num_tables."</td>\n";
	        echo "<td class=\"list\">".$num_rows."</td>\n";
	        echo "<td class=\"list\">".$size['value']." ".$size['type']."</td>\n";
	    }
	
	    // show execution duration
	    if (function_exists("microtime")) {
	        $microtime=explode(" ",microtime());
	        $endtime=($microtime[0]+$microtime[1]);
	    } else {
	        $endtime=time();
	    }
	    echo "<tr>\n<td colspan=\"4\">\n<br><div class=\"bold_left\">".F_DURATION.": ".number_format($endtime-$starttime,3)." ".F_SECONDS."</div>\n".DB_DIFF."\n</td>\n</tr>\n";
	} else {
	
	    // if there are no databases
	    echo "<tr>\n<td><div class=\"bold\">".DB_NO_DB.".</div>\n</td>\n</tr>\n";
	}
	
	echo "</table>\n";
}
PMBP_print_footer();
?>
