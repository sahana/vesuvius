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

chdir("..");
require_once("definitions.php");

echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"
   \"http://www.w3.org/TR/html4/loose.dtd\">
<html".ARABIC_HTML.">
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html;charset=".BD_CHARSET_HTML."\">
<link rel=\"stylesheet\" href=\"./../".PMBP_STYLESHEET_DIR.$CONF['stylesheet'].".css\" type=\"text/css\">
<title>phpMyBackupPro - ".F_HELP."</title>
</head>
<body>
<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\" width=\"100%\">\n
<tr><th colspan=\"2\" class=\"active\">";
echo PMBP_image_tag("../".PMBP_IMAGE_DIR."logo.png","phpMyBackupPro ".PMBP_WEBSITE,PMBP_WEBSITE);
echo "</th></tr>\n";

// choose help text
switch(preg_replace("'^.*/'","",$_GET['script'])) {
    case 'index.php': $filename=F_START;
    $html="On this page you can see system informations about the server where phpMyBackupPro is running on.<br><br>
    ".PMBP_I_SERVER.": Here you can see on what kind of server phpMyBackupPro is running on and the current server time.<br>
    "."PHP".": Here you can see the version of PHP and informations about different important PHP modules und functions.
    You can see if PHP safe mode is activated, the PHP memory limit value, wether gzip compression is possible,
    and wether you are able to send emails and transfer files via FTP on this server.<br>
    "."MySQL".": Here you can see your MySQL servers version and your MySQL clients version.<br>    
    ".F_BACKUP.": Here you cann see how much diskspace is allocated by stored backups,
    when the last backup was build and when the last backup was build by a schedule script.<br>
    ".LI_LOGIN.": Here you can see when you logged in to phpMyBackupPro the last time and from with which IP.";
    break;
    case 'config.php': $filename=F_CONFIG;
    $html="There are two levels of configuration: basic and extended configuration options. Editing the extended configuration variables is optional.
	The * indicates that this item may not be blank.<br><br>
	Basic configuration:<br>
	".C_SITENAME.": Give this system a name like e.g. 'production server'.<br>
	".C_LANG.": Change the language of phpMyBackupPro. Your can download several language packages on the phpMyBackupPro project site.<br>
	".C_SQL_HOST.": Enter your MySQL host e.g. 'localhost'.<br>
	".C_SQL_USER.": Enter your MySQL username.<br>
	".C_SQL_PASSWD.": Enter your MySQL password.<br>
	".C_SQL_DB.": If you want to only use one database on the server, you can enter the name of that database here.<br>
	".C_FTP_USE.": Check this if you want to use FTP functions to upload your backups automatically to an FTP server.<br>
	".C_FTP_BACKUP.": Check this if you want to enable the backup of directories to a FTP server.<br>
	".C_FTP_REC.": Check this if you want to backup directories including their sub directories.<br>
	".C_FTP_SERVER.": Enter the IP or URL of you FTP server.<br>
	".C_FTP_USER.": Enter your FTP loginname.<br>
	".C_FTP_PASSWD.": Enter your FTP password.<br>
	".C_FTP_PATH.": Enter a path to a directory on the FTP server where you want your backups stored.<br>
	".C_FTP_PASV.": Check this to use passive FTP.<br>
	".C_FTP_PORT.": Enter the port on which your FTP server is available. Default port is 21.<br>
	".C_FTP_DEL.": Check this to have the backup files on the FTP server automatically deleted when they are deleted locally.<br>
	".C_EMAIL_USE.": Check this to send your backups automatically via Email.<br>
	".C_EMAIL.": Enter the email address to which you want to send the backups.<br><br>
	Extended configuration:<br>
	".C_STYLESHEET.": Choose a stylesheet for phpMyBackupPro. You can download and upload stylesheets on the phpMyBackupPro project site.<br>
	".C_DATE.": Choose your favorite date format.<br>
	".C_LOGIN.": You can switch to HTTP authentication if you want to.<br>
	".C_DEL_TIME.": Specify a number of days after which the backup files are automatically deleted. Use 0 to disable this function.<br>
	".C_DEL_NUMBER.": Spezify a max number of backup files to be stored for each database.<br>
	".C_TIMELIMIT.": Increase the PHP time limit if there are problems with doing backups or imports. Will have no effect if PHP safe mode is on.<br>
	".C_CONFIRM.": Choose which actions on the import site need to be confirmed.<br>
	".C_IMPORT_ERROR.": Check this to receive a list of import errors if any occur.<br>
	".C_DIR_BACKUP.": Check this to enable directory backups. Valid FTP data must be entered to use this feature.<br>
	".C_DIR_REC.": Check this to backup directories recursively (with all subfolders).<br>
	".C_NO_LOGIN.": Check this to disable the login function. This is not recommended as everyone would get access to your database!<br><br>
	System variables:<br>
	Here you can change the values of the internal phpMyBackupPro system variables. Only change anything if you know what you are doing.
	You can find further help in the 'SYSTEM_VARIABLES.txt' documentation file.";
    break;
    case 'import.php': $filename=F_IMPORT;
    $html="Here you can see all currently stored local backup files.<br>
    You can get more information by clicking '".B_INFO."'.<br>
    By clicking '".B_VIEW."', you can read the backup file.<br>
    To download the backup file just click '".B_DOWNLOAD."'.<br>
    Click '".B_IMPORT."' to re-import the file in the database. Before you do this you can empty the database by clicking '".B_EMPTY_DB."'.<br>
    You can import big backups using the '".B_IMPORT_FRAG."' import. This will import the backup bit by bit.<br>
    To delete a backup file click '".B_DELETE."'. You can delete all backups of one database by clicking '".B_DELETE_ALL."'.<br><br>
    Click '".B_EMPTY_ALL."' to empty all available databases, click '".B_IMPORT_ALL."' to import the latest backup of each database,
    click '".B_DELETE_ALL_2."' to delete all available backup files.";
    break;
    case 'backup.php': $filename=F_BACKUP;
    $html="Here you can select which databases you want to backup.<br>
    A comment will be saved to each backup file.<br>
    You can choose if just the table structure, the data or both will be stored.<br>
    Add a 'drop table if exists ...' row to each table structure by clicking 'add drop table'<br>
    You can also choose the compression type for the backup files. On some systems, not all formats are available.<br><br>
	If you have activated the FTP backup function, you also can backup complete directories to your FTP server.<br>
	The selected directories and their files will be copied to the '".C_FTP_PATH."' configured on the '".F_CONFIG."' page.<br>
	It is not possible email the files but you can select '".EX_PACKED."' to pack all files and directories into one ZIP file.
	This will take more time than a normal transfer. The directory list is only generated once at the login. If you want to
	update the list, click on '".PMBP_EXS_UPDATE_DIRS."'.";
    break;
    case 'scheduled.php': $filename=F_SCHEDULE;
    $html="To automate the backup, you can generate some code to include in any existing PHP script.<br>
    When this script is loaded, the backup automatically starts. You can schedule when the backup will run.<br><br>
    Next, choose where the script will be located. The directory phpMyBackupPro must not be moved after this change!
	(If you have knowledge of coding PHP you can change the path later.)<br><br>
	A click on '".EXS_SHOW."' will show you a script that can be used for doing the scheduled backup. Copy the code and include it into an existing file,
	or use '".C_SAVE."' to save the script automatically with a given filename. This will overwrite an existing file with the same name!<br>
	Note: The file must be in the directory selected on the previous page in order to work correctly.<br>
    The backup will only run, when the script is opened or executed. You can include it into an existing PHP file or use a frame set with an invisible frame.<br><br>
    All configuration options will work in this script!<br> You can find more information about the backup options in the 'backup' help.<br><br>
    If you want to see a larger list of available directories go to the configuration page and change the system variable 'dir_lists' to 2!";
    break;
    case 'db_info.php': $filename=F_DB_INFO;
    $html="Here you can see a small summary of your databases.<br><br>
    In the column 'number of rows' you can find the sum of the number of rows from all tables.<br>
    If a database contains tables, you can click 'tables info' to get the names, number of cols, number of rows and size of all tables of the respective database.<br>
    The sizes may differ from the sizes of backup files because of additional data needed in the backup files.";
    break;
    case 'sql_query.php': $filename=F_SQL_QUERY;
    $html="This page is to send simple sql queries to the database.<br><br>
    You can select a database on which you want to run the queries.<br>
    You can insert one or more sql queries in the textbox.<br>
    Queries like 'select ...' will return a result table.<br>
    Some queries like 'delete ...' will only tell you '".SQ_SUCCESS."'<br><br>
    If you upload a file to be executed you will receive an error message for each error that has happened! (and this could be a lot!)<br>
    The last error message contains a list of all queries, which generated errors. An 'F' before a number of the query means this query was in the file.<br><br>
    These functions are not mature yet! There is no guarantee that all correct queries can be processed successfully!";
    break;
    default: $html="Sorry, no help available for this site.";
}

echo "<tr>\n<td>\n";
if ($filename) echo "<br><div class=\"bold_left\">Help for ".$filename.":</div><br>\n";
echo $html;
echo "</td>\n</tr>\n</table>\n</body>\n</html>";
?>
