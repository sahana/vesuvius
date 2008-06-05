<?php
/*
 +--------------------------------------------------------------------------+
 | phpMyBackupPro                                                           |
 +--------------------------------------------------------------------------+
 | Copyright (c) 2004-2007 by Dirk Randhahn                                 |                               
 | http://www.phpMyBackupPro.net                                                                                                                                                                                |
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
PMBP_print_header(ereg_replace(".*/","",$_SERVER['SCRIPT_NAME']));

// if PMBP_GLOBAL_CONF.php is not writeable
if (!is_writeable(PMBP_GLOBAL_CONF)) echo "<div class=\"red_left\">".I_CONF_ERROR."</div>\n";

// if export directory is not writeable
if (!is_writeable("./".PMBP_EXPORT_DIR)) echo "<div class=\"red_left\">".I_DIR_ERROR."</div>\n";

// if first use or no db-connection possible
if (!@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd']))  echo "<div class=\"red_left\">".C_WRONG_SQL."</div>\n";
if ($CONF['sql_db']) if (!@mysql_select_db($CONF['sql_db'])) echo "<div class=\"red_left\">".C_WRONG_DB."</div>\n";

echo "<br><div class=\"bold_left\">".I_NAME." ".PMBP_VERSION."</div>";
printf(I_WELCOME,"<a href=\"".PMBP_WEBSITE."\">".PMBP_WEBSITE."</a>");

// get all system informations
if (!($server=$_SERVER["SERVER_SOFTWARE"])) $server=PMBP_I_NO_RES;
if (function_exists("phpversion")) {
    $tmp=phpversion();
    $phpvers=$tmp[0].$tmp[1].$tmp[2];
    if ($phpvers>=4.3) $php=$tmp; else $php="<span class=\"red_left\">".$tmp."</span>";
} else {
    $php=PMBP_I_NO_RES;
}
if (!($memory_limit=@ini_get("memory_limit"))) $memory_limit=PMBP_I_NO_RES;
if (@ini_get("safe_mode")=="1") $safe_mode=F_YES; else $safe_mode="<span class=\"red_left\">".F_NO."</span>";
if (function_exists("ftp_connect")) $ftp=F_YES; else $ftp="<span class=\"red_left\">".F_NO."</span>";
if (function_exists("mail")) $mail=F_YES; else $mail="<span class=\"red_left\">".F_NO."</span>";
if (function_exists("gzopen")) $gzip=F_YES; else $gzip=F_NO;
if (!function_exists("mysql_get_server_info")) $mysql_s=PMBP_I_NO_RES; else $mysql_s=@mysql_get_server_info();
if (!function_exists("mysql_get_client_info")) $mysql_c=PMBP_I_NO_RES; else $mysql_c=@mysql_get_client_info();

// calculate size of all backups and last backup date
$all_files=PMBP_get_backup_files();
if (is_array($all_files)) {
    $last_backup=0;
    $size_sum=0;
    foreach($all_files as $filename) {
        $file="./".PMBP_EXPORT_DIR.$filename;
        $size_sum+=PMBP_file_info("size",$file);
        if (($time=PMBP_file_info("time",$file))>$last_backup) $last_backup=$time;
    }
    $size_sum=PMBP_size_type($size_sum);
    $size=$size_sum['value']." ".$size_sum['type'];
    $time=strftime($CONF['date'],$last_backup);
} else {
    $size="0 kb";
    $time="?";
}
$scheduled_time=$PMBP_SYS_VAR['last_scheduled'];
foreach($PMBP_SYS_VAR as $key=>$value) {
    if (substr($key,0,15)=="last_scheduled_" && $value>$scheduled_time) $scheduled_time=$value;
}
if ($scheduled_time) $scheduled_time=strftime($CONF['date'],$scheduled_time); else $scheduled_time="-";

// print system informations
echo "<br><br><div class=\"bold_left\">".PMBP_I_INFO."</div>\n";
echo "<table>\n<tr>\n";
echo "<th colspan=\"5\" class=\"active\">".PMBP_I_SERVER."</th>";
echo "</tr><tr>\n";
echo "<td class=\"list\" colspan=\"3\">".$server."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_TIME.": ".strftime($CONF['date'],time())."</td>\n";
echo "</tr><tr>\n";
echo "<th colspan=\"5\" class=\"active\">PHP</th>";
echo "</tr><tr>\n";
echo "<td class=\"list\">".PMBP_I_PHP_VERS.": ".$php."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_SAFE_MODE.": ".$safe_mode."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_MEM_LIMIT.": ".$memory_limit."</td>\n";
echo "</tr><tr>\n";
echo "<td class=\"list\">".PMBP_I_GZIP.": ".$gzip."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_MAIL.": ".$mail."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_FTP.": ".$ftp."</td>\n";
echo "</tr><tr>\n";
echo "<th colspan=\"5\" class=\"active\">MySQL</th>";
echo "</tr><tr>\n";
echo "<td class=\"list\" colspan=\"3\">".PMBP_I_SQL_SERVER.": ".$mysql_s."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_SQL_CLIENT.": ".$mysql_c."</td>\n";
echo "</tr><tr>\n";
echo "<th colspan=\"5\" class=\"active\">".F_BACKUP."</th>";
echo "</tr><tr>\n";
echo "<td class=\"list\">".B_SIZE_SUM.": ".$size."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".B_LAST_BACKUP.": ".$time."</td>\n";
echo "<td>&nbsp;</td>";
echo "<td class=\"list\">".PMBP_I_LAST_SCHEDULED.": ".$scheduled_time."</td>\n";
echo "</tr><tr>\n";
echo "<th colspan=\"5\" class=\"active\">".LI_LOGIN."</th>";
echo "</tr><tr>\n";
echo "<td colspan=\"5\" class=\"list\">".PMBP_I_LAST_LOGIN.": ".$PMBP_SYS_VAR['last_login']."</td>\n";
echo "</tr></table>";

PMBP_print_footer();
?>
