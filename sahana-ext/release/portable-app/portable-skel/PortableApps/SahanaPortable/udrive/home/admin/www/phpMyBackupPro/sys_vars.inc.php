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

// system variables are documented in documents/SYSTEM_VARIABLES.txt

// set general system variables 
$update=FALSE;
if (!isset($PMBP_SYS_VAR['last_scheduled'])) {
    $PMBP_SYS_VAR['last_scheduled']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['this_login'])) {
    $PMBP_SYS_VAR['this_login']="";
    $update=TRUE;
}

if (!isset($PMBP_SYS_VAR['last_login'])) {
    $PMBP_SYS_VAR['last_login']="";
    $update=TRUE;
}
if (isset($CONF['sql_passwd']) && isset($CONF['sql_user'])) {
    if (!isset($PMBP_SYS_VAR['security_key']) && $CONF['sql_passwd'] && $CONF['sql_user']) {
        $PMBP_SYS_VAR['security_key']=md5($_SERVER['PHP_SELF'].$CONF['sql_passwd'].$CONF['sql_user']);
        $update=TRUE;
    }
}
if (!isset($PMBP_SYS_VAR['dir_lists'])) {
    $PMBP_SYS_VAR['dir_lists']=1;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['memory_limit'])) {
    $PMBP_SYS_VAR['memory_limit']=9500000*4; // (less than) 4 mb
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['except_tables'])) {
    $PMBP_SYS_VAR['except_tables']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['scheduled_debug'])) {
    $PMBP_SYS_VAR['scheduled_debug']=0;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['schedule_all_dbs'])) {
    $PMBP_SYS_VAR['schedule_all_dbs']=0;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['ftp_timeout'])) {
    $PMBP_SYS_VAR['ftp_timeout']=10;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['dir_email_backup'])) {
    $PMBP_SYS_VAR['dir_email_backup']=0;
    $update=TRUE;
}

// update login sys vars
if (isset($_GET['login']) || isset($_POST['login'])) {
	$login_str=strftime($CONF['date'],time())." (IP: ".$_SERVER['REMOTE_ADDR'].")";
	if ($login_str!=$PMBP_SYS_VAR['this_login'])
	{
	    $PMBP_SYS_VAR['last_login']=$PMBP_SYS_VAR['this_login'];
	    $PMBP_SYS_VAR['this_login']=$login_str;
	    $update=TRUE;
	}
}

// functions.inc.php
if (!isset($PMBP_SYS_VAR['F_dbs'])) {
    $PMBP_SYS_VAR['F_dbs']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_comment'])) {
    $PMBP_SYS_VAR['F_comment']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_tables'])) {
    $PMBP_SYS_VAR['F_tables']=1;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_data'])) {
    $PMBP_SYS_VAR['F_data']=1;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_drop'])) {
    $PMBP_SYS_VAR['F_drop']=1;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_compression'])) {
    $PMBP_SYS_VAR['F_compression']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_ftp_dirs'])) {
    $PMBP_SYS_VAR['F_ftp_dirs']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_ftp_dirs_2'])) {
    $PMBP_SYS_VAR['F_ftp_dirs_2']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_packed'])) {
    $PMBP_SYS_VAR['F_packed']="";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_updates'])) {
    $PMBP_SYS_VAR['F_updates']=1;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['F_ffadd'])) {
    $PMBP_SYS_VAR['F_ffadd']=1;
    $update=TRUE;
}

// scheduled.php
if (!isset($PMBP_SYS_VAR['EXS_scheduled_file'])) {
    $PMBP_SYS_VAR['EXS_scheduled_file']="???.php";
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['EXS_scheduled_dir'])) {
    $PMBP_SYS_VAR['EXS_scheduled_dir']=0;
    $update=TRUE;
}
if (!isset($PMBP_SYS_VAR['EXS_period'])) {
    $PMBP_SYS_VAR['EXS_period']="";
    $update=TRUE;
}

// global_conf.php
if (!isset($CONF['sitename'])) {
    $CONF['sitename']="mySite";
    $update=TRUE;
}
if (!isset($CONF['lang'])) {
    $CONF['lang']="english";
    $update=TRUE;
}
if (!isset($CONF['import_error'])) {
    $CONF['import_error']="1";
    $update=TRUE;
}
if (!isset($CONF['no_login'])) {
    $CONF['no_login']="0";
    $update=TRUE;
}
if (!isset($CONF['login'])) {
    $CONF['login']="0";
    $update=TRUE;
}
if (!isset($CONF['dir_backup'])) {
    $CONF['dir_backup']="0";
    $update=TRUE;
}
if (!isset($CONF['dir_rec'])) {
    $CONF['dir_rec']="1";
    $update=TRUE;
}
if (!isset($CONF['email_use'])) {
    $CONF['email_use']="0";
    $update=TRUE;
}
if (!isset($CONF['email'])) {
    $CONF['email']="";
    $update=TRUE;
}
if (!isset($CONF['ftp_use'])) {
    $CONF['ftp_use']="0";
    $update=TRUE;
}
if (!isset($CONF['ftp_pasv'])) {
    $CONF['ftp_pasv']="1";
    $update=TRUE;
}
if (!isset($CONF['ftp_del'])) {
    $CONF['ftp_del']="1";
    $update=TRUE;
}
if (!isset($CONF['ftp_server'])) {
    $CONF['ftp_server']="";
    $update=TRUE;
}
if (!isset($CONF['ftp_user'])) {
    $CONF['ftp_user']="";
    $update=TRUE;
}
if (!isset($CONF['ftp_passwd'])) {
    $CONF['ftp_passwd']="";
    $update=TRUE;
}
if (!isset($CONF['ftp_path'])) {
    $CONF['ftp_path']="";
    $update=TRUE;
}
if (!isset($CONF['ftp_port'])) {
    $CONF['ftp_port']="21";
    $update=TRUE;
}
if (!$_SESSION['multi_user_mode']) {
    if (!isset($CONF['sql_passwd'])) {
        $CONF['sql_passwd']="";
        $update=TRUE;
    }
    if (!isset($CONF['sql_host'])) {
        $CONF['sql_host']="localhost";
        $update=TRUE;
    }
    if (!isset($CONF['sql_user'])) {
        $CONF['sql_user']="";
        $update=TRUE;
    }
    if (!isset($CONF['sql_db'])) {
        $CONF['sql_db']="";
        $update=TRUE;
    }
}
if (!isset($CONF['date'])) {
    $CONF['date']="%x %X";
    $update=TRUE;
}
if (!isset($CONF['del_time'])) {
    $CONF['del_time']="7";
    $update=TRUE;
}
if (!isset($CONF['del_number'])) {
    $CONF['del_number']="5";
    $update=TRUE;
}
if (!isset($CONF['timelimit'])) {
    $CONF['timelimit']="60";
    $update=TRUE;
}
if (!isset($CONF['confirm'])) {
    $CONF['confirm']="1";
    $update=TRUE;
}
if (!isset($CONF['stylesheet'])) {
    $CONF['stylesheet']="standard";
    $update=TRUE;
}

// save global_conf.php
if ($update) PMBP_save_global_conf();

?>