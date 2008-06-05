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

// get and print the informations about the $_GET['file'] backup file
if ($_GET['file']) {
    echo "<tr><td><div class=\"bold_left\"><br><br>".INF_DATE.":</div></td><td><br><br>".strftime($CONF['date'],PMBP_file_info("time","./".PMBP_EXPORT_DIR.$_GET['file']))."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".INF_DB.":</div></td><td>".PMBP_file_info("db","./".PMBP_EXPORT_DIR.$_GET['file'])."</td></tr>\n";
    $size=PMBP_size_type(PMBP_file_info("size","./".PMBP_EXPORT_DIR.$_GET['file']));
    echo "<tr><td><div class=\"bold_left\">".INF_SIZE.":</div></td><td>".$size['value']." ".$size['type']."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".INF_COMP.":</div></td><td>".PMBP_file_info("comp","./".PMBP_EXPORT_DIR.$_GET['file'])."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".INF_DROP.":</div></td><td>".PMBP_file_info("drop","./".PMBP_EXPORT_DIR.$_GET['file'])."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".INF_TABLES.":</div></td><td>".PMBP_file_info("tables","./".PMBP_EXPORT_DIR.$_GET['file'])."</td></tr>\n";
    echo "<tr><td><div class=\"bold_left\">".INF_DATA.":</div></td><td>".PMBP_file_info("data","./".PMBP_EXPORT_DIR.$_GET['file'])."</td></tr>\n";
    echo "<tr><td colspan=\"2\"><br><div class=\"bold_left\">".INF_COMMENT.":</div></td></tr>\n";
    echo "<tr><td colspan=\"2\">".PMBP_file_info("comment","./".PMBP_EXPORT_DIR.$_GET['file'])."</td></tr>\n";
} else{

// return error message if no file was selected
    echo "<tr><td><div class=\"bold\">".INF_NO_FILE."!</div></td></tr>\n";
}

echo "</table>\n</body>\n</html>";
?>
