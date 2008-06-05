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

// This code is derived from BigDump ver. 0.21b from 2005-02-08
// Author: Alexey Ozerov (alexey at ozerov dot de) 
// More Infos: http://www.ozerov.de/bigdump
// License: GNU General Public License 2

require_once("login.php");
@session_start();

// print html header
echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"
   \"http://www.w3.org/TR/html4/loose.dtd\">
<html".ARABIC_HTML.">
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html;charset=".BD_CHARSET_HTML."\">
<link rel=\"stylesheet\" href=\"".PMBP_STYLESHEET_DIR.$CONF['stylesheet'].".css\" type=\"text/css\">
<title>phpMyBackupPro - ".INF_INFO."</title>
</head>
<body>
<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\" width=\"100%\">\n
<tr><th colspan=\"2\" class=\"active\">\n";
echo PMBP_image_tag("logo.png","phpMyBackupPro PMBP_WEBSITE",PMBP_WEBSITE);
echo "\n</th></tr>\n";

@set_time_limit($CONF['timelimit']);

// set parameters
$linespersession=10000;    

// set some basic values on start up
$error=false;
if (!isset($_GET['sn'])) $_GET['sn']=0; else $_GET['sn']++;
if (!isset($_GET['totalqueries'])) $_GET['totalqueries']=0;
if (!isset($_GET['dbn'])) $_GET['dbn']=" ";
if (!isset($_GET['delete'])) $_GET['delete']=false;
if (!isset($_GET['start']) || !isset($_GET['foffset'])) {
    $_GET['start']=$_GET['foffset']=0;
    $firstSession=TRUE;
    $linenumber=0;
    $foffset=0;
    $totalqueries=0;    
}

// connect to the database
if (!isset($firstSession)) {
    $con=@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd']); 
    if (!$con) $error=C_WRONG_SQL;
    if (!$error) $db=@mysql_select_db($_GET['dbn']);
    if (!$db) $error=C_WRONG_DB." (".$_GET['dbn'].")";
}

// open the file
if (!$error && !isset($firstSession)) {
// gzopen can be used for plain text too!
    
    // extract zip file
    if (PMBP_file_info("comp",$_GET["fn"])=="zip") {
		include_once("pclzip.lib.php");
		$pclzip = new PclZip($_GET["fn"]);
		$extracted_file=$pclzip->extractByIndex(0,"./".PMBP_EXPORT_DIR,"");
		if ($pclzip->error_code!=0) $error="plczip: ".$pclzip->error_string."<br>".BI_BROKEN_ZIP."!";
		$_GET["fn"]=substr($_GET["fn"],0,strlen($_GET["fn"])-4);
		unset($pclzip);	
    }

    if(!$error && !$file=@gzopen($_GET["fn"],"r")) $error=C_OPEN." ".$_GET["fn"];    
}

if (!$error) {
    // get start time to calculate duration
    if (function_exists("microtime")) {
        $microtime=explode(" ",microtime());
        $starttime=($microtime[0]+$microtime[1]);
    } else {
        $starttime=time();
    }    

	if (file_exists($_GET["fn"].".zip")) echo "<tr><td><div class=\"bold_left\">".BI_IMPORTING_FILE.":</div></td><td>".basename($_GET["fn"]).".zip</td></tr>\n";
        else echo "<tr><td><div class=\"bold_left\">".BI_IMPORTING_FILE.":</div></td><td>".basename($_GET["fn"])."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".BI_INTO_DB.":</div></td><td>".$_GET["dbn"]."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".BI_SESSION_NO.":</div></td><td>".$_GET["sn"]."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".BI_STARTING_LINE.":</div></td><td>".$_GET["start"]."</td></tr>\n";

    // start or continue the import process
    if (!isset($firstSession)) {
        if (gzseek($file, $_GET["foffset"])!=0) $error="UNEXPECTED ERROR: Can't set gzip file pointer to offset: ".$_GET["foffset"];

		// execute sql queries
        if (!$error) {
			extract(PMBP_exec_sql($file,$con,$linespersession ),EXTR_OVERWRITE);
    	}

        // get the current file position
        if (!$error) {
            $foffset=gztell($file);
            if ($foffset===false) $error="UNEXPECTED ERROR: Can't read the file pointer offset";
        }
    }

    // clean up
    if (!isset($firstSession)) {
        if ($con) @mysql_close();
        @gzclose($file);
    }
    
    if (!$error || isset($firstSession)) {
        // calculate execution duration of this session
        if (function_exists("microtime")) {
            $microtime=explode(" ",microtime());
            $endtime=($microtime[0]+$microtime[1]);
        } else {
            $endtime=time();
        }

        if (!isset($firstSession)) {
        	// print information table
            echo "<tr><td><div class=\"bold_left\">".BI_STOPPING_LINE.":</div></td><td>".($linenumber-1)."</td></tr>\n";
            echo "<tr><td><div class=\"bold_left\">".BI_QUERY_NO."<br>(".BI_THIS_LAST."):</div></td><td>".$queries."/".$totalqueries."</td></tr>\n";
            echo "<tr><td><div class=\"bold_left\">".BI_BYTE_NO.":</div></td><td>".round($foffset/1024)." KB</td></tr>\n";        
            echo "<tr><td><div class=\"bold_left\">".BI_DURATION.":</div></td><td>".number_format($endtime-$starttime,3)." ".F_SECONDS."</td></tr>\n";
        }
        
        if ($linenumber<$_GET["start"]+$linespersession && !isset($firstSession)) {
        	// delete extracted zip file
        	if (file_exists($_GET["fn"].".zip")) @unlink($_GET["fn"]);
            // all sql queries executed
            echo "<tr><td colspan=\"2\">&nbsp;</td></tr>\n";
            echo "<tr><td colspan=\"2\" class=\"active\"><div class=\"green_left\">".BI_END.".\n";
			// delete the temporary created file
            if (!$_GET['delete']) {
            	if (file_exists($_GET["fn"].".zip")) echo "<br>(<a href=\"".$_SERVER["PHP_SELF"]."?fn=".$_GET["fn"].".zip&dbn=".$_GET['dbn']."\">".BI_RESTART."".basename($_GET['fn']).".zip</a>)</td></tr>\n";
            		else echo "<br>(<a href=\"".$_SERVER["PHP_SELF"]."?fn=".$_GET["fn"]."&dbn=".$_GET['dbn']."\">".BI_RESTART."".basename($_GET['fn'])."</a>)</td></tr>\n";
            }
            echo "</table>\n";
        } else {
            // restart script to execute next queries
            echo "<tr><td colspan=\"2\">&nbsp;</td></tr>\n";
            echo "<tr><td colspan=\"2\" class=\"active\"><div class=\"red_left\">".BI_SCRIPT_RUNNING.".</div></td></tr>\n";
            echo "</table>\n";
            echo "<script language=\"JavaScript\" type=\"text/javascript\">window.setTimeout('location.href=\"".$_SERVER["PHP_SELF"]."?fn=".$_GET["fn"];
            echo "&dbn=".$_GET['dbn']."&delete=".$_GET['delete']."&start=".$linenumber."&foffset=".$foffset."&totalqueries=".$totalqueries."&sn=".$_GET['sn']."\";',500);</script>\n";
            echo "<noscript>\n";
            echo "<div class=\"red_left\"><a href=\"".$_SERVER["PHP_SELF"]."?delete=".$_GET['delete']."&start=".$linenumber."&fn=".$_GET["fn"]."&foffset=".$foffset."&dbn=".$_GET['dbn'];
            echo "&totalqueries=".$totalqueries."&sn=".$_GET['sn']."\">".BI_CONTINUE." ".$linenumber."</a> (".BI_ENABLE_JS."!)</div>\n";
            echo "</noscript>\n";
        }
    }    
}

if ($error) echo "<tr><td colspan=\"2\"><div class=\"red_left\">".$error."</td></tr>";
echo "</table></body>\n</html>";
?>