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

/*basic data*/
define('BD_LANG_SHORTCUT',"en"); // used for the php function setlocale() (http://www.php.net/setlocale)
define('BD_DATE_FORMAT',"%x %X"); // used for the php function strftime() (http://www.php.net/strftime)
define('BD_CHARSET_HTML',"ISO-8859-1"); // the charset used in you language for html
define('BD_CHARSET_EMAIL',"ISO-8859-1"); // the charset used in your langauge for MIME-emails

/*functions.inc.php*/
define('F_START',"start");
define('F_CONFIG',"configuration");
define('F_IMPORT',"import");
define('F_BACKUP',"backup");
define('F_SCHEDULE',"schedule backup");
define('F_DB_INFO',"database info");
define('F_SQL_QUERY',"sql queries");
define('F_HELP',"help");
define('F_LOGOUT',"logout");
define('F_FOOTER',"Visit the %sphpMyBackupPro project site%s for new releases and news.");
define('F_NOW_AVAILABLE',"A new version of phpMyBackupPro is now available on %s".PMBP_WEBSITE."%s");
define('F_SELECT_DB',"Select databases to backup");
define('F_SELECT_ALL',"select all");
define('F_COMMENTS',"Comments");
define('F_EX_TABLES',"export tables");
define('F_EX_DATA',"export data");
define('F_EX_DROP',"add 'drop table'");
define('F_EX_COMP',"compression");
define('F_EX_OFF',"none");
define('F_EX_GZIP',"gzip");
define('F_EX_ZIP',"zip");
define('F_DEL_FAILED',"Failed to delete backup %s");
define('F_FTP_1',"FTP connection failed to server");
define('F_FTP_2',"Failed to login with user");
define('F_FTP_3',"FTP upload failed");
define('F_FTP_4',"File succesfully uploaded as");
define('F_FTP_5',"FTP delete of file '%s' failed");
define('F_FTP_6',"File '%s' succesfully deleted on FTP server");
define('F_FTP_7',"File '%s' not available on FTP server");
define('F_MAIL_1',"One receivers email is wrong");
define('F_MAIL_2',"This mail was sent by phpMyBackupPro ".PMBP_VERSION." ".PMBP_WEBSITE." running on");
define('F_MAIL_3',"coudn't be read");
define('F_MAIL_4',"MySQL backup from");
define('F_MAIL_5',"Mail coudn't be sent");
define('F_MAIL_6',"Files succesfully send by email to");
define('F_YES',"yes");
define('F_NO',"no");
define('F_DURATION',"Duration");
define('F_SECONDS',"seconds");

/*index.php*/
define('I_SQL_ERROR',"ERROR: Please insert your correct MySQL data in the 'configuration'!");
define('I_NAME',"This is phpMyBackupPro");
define('I_WELCOME',"phpMyBackupPro is free software licensed under the GNU GPL.<br>
For help try the online help or visit %s.<br><br>
Choose in the top menu what you want to do next! If this is your first time using phpMyBackupPro you should start with the configuration!
The rights of the directory 'export' and the file 'global_conf.php' must be set to 0777.");
define('I_CONF_ERROR',"The file ".PMBP_GLOBAL_CONF." is not writeable!");
define('I_DIR_ERROR',"The directory ".PMBP_EXPORT_DIR." is not writeable!");
define('PMBP_I_INFO',"System information");
define('PMBP_I_SERVER',"Server");
define('PMBP_I_TIME',"Time");
define('PMBP_I_PHP_VERS',"PHP Version");
define('PMBP_I_MEM_LIMIT',"PHP Memory Limit");
define('PMBP_I_SAFE_MODE',"Safe Mode activated");
define('PMBP_I_FTP',"FTP transfer possible");
define('PMBP_I_MAIL',"Emails sendable");
define('PMBP_I_GZIP',"gzip compression possible");
define('PMBP_I_SQL_SERVER',"MySQL Server");
define('PMBP_I_SQL_CLIENT',"MySQL Client");
define('PMBP_I_NO_RES',"*Can not be retrieved*");
define('PMBP_I_LAST_SCHEDULED',"Last scheduled backup");
define('PMBP_I_LAST_LOGIN',"Last login");
define('PMBP_I_LAST_LOGIN_ERROR',"Last incorrect login");

/*config.php*/
define('C_SITENAME',"site name");
define('C_LANG',"language");
define('C_SQL_HOST',"MySQL hostname");
define('C_SQL_USER',"MySQL username");
define('C_SQL_PASSWD',"MySQL password");
define('C_SQL_DB',"only this database");
define('C_FTP_USE',"save backups per FTP?");
define('C_FTP_BACKUP',"use directory backup?");
define('C_FTP_REC',"backup directories recursively?");
define('C_FTP_SERVER',"FTP server (url or IP)");
define('C_FTP_USER',"FTP username");
define('C_FTP_PASSWD',"FTP password");
define('C_FTP_PATH',"FTP path");
define('C_FTP_PASV',"use passive ftp?");
define('C_FTP_PORT',"FTP port");
define('C_FTP_DEL',"delete files on FTP server");
define('C_EMAIL_USE',"use email?");
define('C_EMAIL',"email address");
define('C_STYLESHEET',"skin");
define('C_DATE',"date style");
define('C_DEL_TIME',"delete local backups after x days");
define('C_DEL_NUMBER',"store max x files per database");
define('C_TIMELIMIT',"php timelimit");
define('C_IMPORT_ERROR',"show import errors?");
define('C_NO_LOGIN',"disable login function?");
define('C_LOGIN',"HTTP authentication?");
define('C_DIR_BACKUP',"enable directory backups?");
define('C_DIR_REC',"directory backup with subdirectories?");
define('C_CONFIRM',"confirmation level");
define('C_CONFIRM_1',"empty, delete, import");
define('C_CONFIRM_2',"... all");
define('C_CONFIRM_3',"... ALL");
define('C_CONFIRM_4',"don't confirm anything");

define('C_BASIC_VAL',"Basic configuration");
define('C_EXT_VAL',"Extended configuration");
define('PMBP_C_SYSTEM_VAL',"System variables");
define('PMBP_C_SYS_WARNING',"These system variables are managed by phpMyBackupPro. Don't edit them unless you know what you are doing!");
define('C_TITLE_SQL',"SQL data");
define('C_TITLE_FTP',"FTP settings");
define('C_TITLE_EMAIL',"Backup per email");
define('C_TITLE_STYLE',"Style of phpMyBackupPro");
define('C_TITLE_DELETE',"Automatic deletion of backup files");
define('C_TITLE_CONFIG',"Further configuration items");
define('C_WRONG_TYPE',"is not correct!");
define('C_WRONG_SQL',"MySQL data is not correct!");
define('C_WRONG_DB',"MySQL database name is not correct!");
define('C_WRONG_FTP',"FTP data is not correct!");
define('C_OPEN',"Can't open");
define('C_WRITE',"Can't write to");
define('C_SAVED',"Data successfully saved");
define('C_WRITEABLE',"is not writeable");
define('C_SAVE',"Save data");

/*import.php*/
define('IM_ERROR',"%d error(s) occured. You can use 'empty database' to be sure the database does not contain any tables.");
define('IM_SUCCESS',"Successfully imported");
define('IM_TABLES',"tables and");
define('IM_ROWS',"rows");

define('B_EMPTIED_ALL',"All databases were succesfully emptied");
define('B_EMPTIED',"The database was succesfully emptied");
define('B_DELETED',"The file was succesfully deleted");
define('B_DELETED_ALL',"All files were succesfully deleted");
define('B_NO_FILES',"There are currently no backup files");
define('B_DELETE_ALL_2',"delete ALL backups");
define('B_IMPORT_ALL',"import ALL backups");
define('B_EMPTY_ALL',"empty ALL databases");
define('B_EMPTY_DB',"empty database");
define('B_DELETE_ALL',"delete all backups");
define('B_INFO',"info");
define('B_VIEW',"view");
define('B_DOWNLOAD',"download");
define('B_IMPORT',"import");
define('B_IMPORT_FRAG',"fragmented");
define('B_DELETE',"delete");
define('B_CONF_EMPTY_DB',"Do you really want to empty the database?");
define('B_CONF_DEL_ALL',"Do you really want to delete all backups of this database?");
define('B_CONF_IMP',"Do you really want to import this backup?");
define('B_CONF_DEL',"Do you really want to delete this backup?");
define('B_CONF_EMPT_ALL',"Do you really want to empty ALL databases?");
define('B_CONF_IMP_ALL',"Do you really want to import ALL last backups?");
define('B_CONF_DEL_ALL_2',"Do you really want to delete ALL backups?");
define('B_LAST_BACKUP',"Last backup built on");
define('B_SIZE_SUM',"Total size of all backups");

/*backup.php*/
define('EX_SAVED',"File successfully saved as");
define('EX_NO_DB',"No database selected");
define('EX_EXPORT',"Backup");
define('EX_NOT_SAVED',"Could not save backup of database %s in '%s'");
define('EX_DIRS',"Select directories to backup to FTP server");
define('EX_DIRS_MAN',"Enter more directory paths relative to the phpMyBackupPro directory.<br>Separate with '|'");
define('EX_PACKED',"Pack all in one ZIP file");
define('PMBP_EX_NO_AVAILABLE',"Database %s is not available");
define('PMBP_EXS_UPDATE_DIRS',"Update directory list");
define('PMBP_EX_NO_ARGV',"Usage example:\n$ php backup.php db1,db2,db3
For more functions please read 'SHELL_MODE.txt' in the 'documentation' directory");

/*scheduled.php*/
define('EXS_PERIOD',"Select backup period");
define('EXS_PATH',"Select directory where the PHP file will be placed");
define('EXS_BACK',"back");
define('PMBP_EXS_ALWAYS',"At each call");
define('EXS_HOUR',"hour");
define('EXS_HOURS',"hours");
define('EXS_DAY',"day");
define('EXS_DAYS',"days");
define('EXS_WEEK',"week");
define('EXS_WEEKS',"weeks");
define('EXS_MONTH',"month");
define('EXS_SHOW',"Show script");
define('PMBP_EXS_INCL',"Include this script in the PHP file (%s) you want to do the backup job");
define('PMBP_EXS_SAVE',"or save this script to a new file (will overwrite an existing file!)");

/*file_info.php*/
define('INF_INFO',"info");
define('INF_DATE',"Date");
define('INF_DB',"Database");
define('INF_SIZE',"Backup size");
define('INF_COMP',"Is compressed");
define('INF_DROP',"Contains 'drop table'");
define('INF_TABLES',"Contains tables");
define('INF_DATA',"Contains data");
define('INF_COMMENT',"Comments");
define('INF_NO_FILE',"No file selected");

/*db_status.php*/
define('DB_NAME',"name of database");
define('DB_NUM_TABLES',"number of tables");
define('DB_NUM_ROWS',"number of rows");
define('DB_SIZE',"size");
define('DB_DIFF',"Sizes can differ from sizes of backup files!");
define('DB_NO_DB',"No databases available");
define('DB_TABLES',"tables info");
define('DB_TAB_TITLE',"tables of database ");
define('DB_TAB_NAME',"name of table");
define('DB_TAB_COLS',"number of fields");

/*sql_query.php*/
define('SQ_ERROR',"Errors occured in line number");
define('SQ_SUCCESS',"Successfully executed");
define('SQ_RESULT',"Query result");
define('SQ_AFFECTED',"Number of affected rows");
define('SQ_WARNING',"Attention: This page is only built to send simple sql queries to the databases. Being careless can destroy your databases!");
define('SQ_SELECT_DB',"Select database");
define('SQ_INSERT',"Insert your sql query here");
define('SQ_FILE',"Upload sql file");
define('SQ_SEND',"Run");

/*login.php*/
define('LI_MSG',"Please login (use your MySQL username and password)");
define('LI_USER',"username");
define('LI_PASSWD',"password");
define('LI_LOGIN',"Login");
define('LI_LOGED_OUT',"Safely loged out!");
define('LI_NOT_LOGED_OUT',"Not safely logged out!<br>To safely logout enter a WRONG password");

/*big_import.php*/
define('BI_IMPORTING_FILE',"Importing file");
define('BI_INTO_DB',"Into database");
define('BI_SESSION_NO',"Session number");
define('BI_STARTING_LINE',"Starting at line");
define('BI_STOPPING_LINE',"Stopping at line");
define('BI_QUERY_NO',"Number of queries performed");
define('BI_BYTE_NO',"Number of bytes processed yet");
define('BI_DURATION',"Duration of last session");
define('BI_THIS_LAST',"this session/total");
define('BI_END',"End of file reached, import seems to be OK");
define('BI_RESTART',"Restart import of file ");
define('BI_SCRIPT_RUNNING',"This script is still running!<br>Please wait until the end of the file is reached");
define('BI_CONTINUE',"Continue from the line");
define('BI_ENABLE_JS',"Enable JavaScript to continue automatically");
define('BI_BROKEN_ZIP',"The ZIP file seems to be broken");
define('BI_WRONG_FILE',"Stopped at line %s.<br>The current query includes more than %s dump lines. That happens if your backup file was created
by some tool which didn't place a semicolon followed by a linebreak at the end of each query, or if your backup file contains extended inserts.");
?>
