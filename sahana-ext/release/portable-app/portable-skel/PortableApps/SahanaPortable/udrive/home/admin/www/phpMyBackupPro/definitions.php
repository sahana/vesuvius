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

// ---- adjust these two lines to your file system. The pathes must be relative to this file! ----- //

$_PMBP_GLOBAL_CONF="global_conf.php";       // example: $_PMBP_GLOBAL_CONF="../../files/global_conf.php";
$_PMBP_EXPORT_DIR="export/";                // example: $_PMBP_EXPORT_DIR="../../files/export/";

// ---- adjust this line only if you are going to backup from several database servers or if you have to use different accounts ---- //

define('PMBP_GLOBAL_CONF_SQL',"global_conf_sql.php");    // example: define('PMBP_GLOBAL_CONF',"../../files/global_conf_sql.php");

// ---- adjust this line only if you want to use one installation for several different users with different MySQL accounts ---- //

define('PMBP_GLOBAL_CONF_MU',"global_conf_mu.php");    // example: define('PMBP_GLOBAL_CONF',"../../files/global_conf_mu.php");

// ---- No need to modify anything more! ---- //

// definitions
define('PMBP_VERSION',"v.2.1");  // this is the version of this phpMyBackupPro release

define('PMBP_MAIN_INC',"./functions.inc.php");
define('PMBP_JAVASCRIPTS',"javascripts.js");
define('PMBP_STYLESHEET_DIR',"stylesheets/");
define('PMBP_LANGUAGE_DIR',"language/");
define('PMBP_IMAGE_DIR',"images/");
define('PMBP_WEBSITE',"http://www.phpMyBackupPro.net");

// check for MySQL module
if (!function_exists("mysql_connect")) {
    echo "The MySQL module for PHP seems not to be installed correctly.<br>
    You can configure the MySQL module in php.ini. Read the HTTP servers (eg. Apache) log files for more infomation.";
    exit;    
}

// must be set always
$CONF['sql_host_s']=array();
$CONF['sql_user_s']=array();
$CONF['sql_passwd_s']=array();
$CONF['sql_db_s']=array();

// change path when in shell mode
if(isset($argv) && basename($GLOBALS['_SERVER']['SCRIPT_FILENAME'])=="backup.php") {
	$prepath=dirname($GLOBALS['_SERVER']['SCRIPT_FILENAME'])."/";
	//return;	
} else {
	$prepath="";
}

// include functions.inc
require_once($prepath.PMBP_MAIN_INC);

// set up multi user mode
if (@include_once($prepath.PMBP_GLOBAL_CONF_MU)) {
    if ($PMBP_MU_CONF['sql_user_admin'] && $PMBP_MU_CONF['sql_passwd_admin']) {
        // test MySQL admin data
        if (!$con=@mysql_connect($CONF['sql_host'],$PMBP_MU_CONF['sql_user_admin'],$PMBP_MU_CONF['sql_passwd_admin'])) {        
            echo "MySQL admin data are incorrect in global_conf_mu.php. Please correct them in order to use the multi user mode.";
            exit;
        }
        // if connection issn't closed the user could get access to all data
        if(!mysql_close($con)) {
            echo "phpMyBackupPro stoped loading due to security reasons: The MySQL connection could not be shut down! (".__FILE__.", Line ".__LINE__.")";
            exit;
        }

        // discover if we are in mu mode
        if (isset($_SESSION['sql_user']) && isset($_SESSION['sql_passwd'])) {
            // admin has logged on
            if ($_SESSION['sql_user']==$PMBP_MU_CONF['sql_user_admin'] && $_SESSION['sql_passwd']==$PMBP_MU_CONF['sql_passwd_admin'])
                $_SESSION['multi_user_mode']=FALSE;
            else 
                $_SESSION['multi_user_mode']=TRUE;
            if (isset($_SESSION['LOGGED_IN']))
                $override_user_date=TRUE;
        } else {
            $_SESSION['multi_user_mode']=TRUE;
        }
    } else {
        $_SESSION['multi_user_mode']=FALSE;
    }
}

// include global-conf file
if ($_SESSION['multi_user_mode'] && isset($_SESSION['sql_user'])) {
    define('PMBP_GLOBAL_CONF',$PMBP_MU_CONF['user_conf_file']);
} else {
    define('PMBP_GLOBAL_CONF',$_PMBP_GLOBAL_CONF);
}

// try to include global conf file
if (!@include_once($prepath.PMBP_GLOBAL_CONF)) {
    // show warning in schedlued mode only if scheduled_debug is on
    if ((!isset($security_key) || $PMBP_SYS_VAR['scheduled_debug'])) {
        // try to create global_conf.php
        if(!@touch($prepath.PMBP_GLOBAL_CONF)) { 
            echo PMBP_GLOBAL_CONF." is missing.<br>Please read INSTALL.txt and specify the global_conf.php path in definitions.php.";
            exit;
        }
    }
}

// now override sql data and restricted settings in $CONF
if (isset($override_user_date)) {
    $CONF['sql_user']=$_SESSION['sql_user'];
    $CONF['sql_passwd']=$_SESSION['sql_passwd'];
    $CONF['sql_host']=$PMBP_MU_CONF['sql_host_admin'];
    $CONF['sql_db']="";
    
    // disable the following functions if they were disabled in global_mu_conf.php
    if ($PMBP_MU_CONF['sitename']) $CONF['sitename']=$PMBP_MU_CONF['sitename'];
    if (!$PMBP_MU_CONF['allow_ftp']) $CONF['ftp_use']="0";
    if (!$PMBP_MU_CONF['allow_dir_backup']) $CONF['allow_dir_backup']="0";
    if (!$PMBP_MU_CONF['allow_email']) $CONF['email_use']="0";
}

// reset missing system variables and configurations but not before login
if ($_SESSION['multi_user_mode'] && $_PMBP_GLOBAL_CONF!=PMBP_GLOBAL_CONF || !$_SESSION['multi_user_mode'])
    include($prepath."sys_vars.inc.php");

// multi server mode only if not in multi user mode
if(!$_SESSION['multi_user_mode']) 
    @include_once($prepath.PMBP_GLOBAL_CONF_SQL);

// set working sql server
if (count($CONF['sql_host_s'])) {
    // set working server and register session vars
    if (!isset($_SESSION['sql_host_org'])) $_SESSION['sql_host_org']=$CONF['sql_host'];
    if (!isset($_SESSION['sql_user_org'])) $_SESSION['sql_user_org']=$CONF['sql_user'];
    if (!isset($_SESSION['sql_passwd_org'])) $_SESSION['sql_passwd_org']=$CONF['sql_passwd'];
    if (!isset($_SESSION['sql_db_org'])) $_SESSION['sql_db_org']=$CONF['sql_db'];    
    if (!isset($_SESSION['wss'])) $_SESSION['wss']=-1;
    if(isset($_POST['mysql_host'])) $_SESSION['wss']=$_POST['mysql_host'];

    // load setting from $_SESSION['wss'] as long we are not on the config page and if the host data are still in global_conf_sql.php
    // otherwise set to original host
    if ($_SESSION['wss']<0 || basename($_SERVER['SCRIPT_NAME'])=="config.php" || !isset($CONF['sql_host_s'][$_SESSION['wss']]) ) {
        $CONF['sql_host']=$_SESSION['sql_host_org'];
        $CONF['sql_user']=$_SESSION['sql_user_org'];
        $CONF['sql_passwd']=$_SESSION['sql_passwd_org'];
        $CONF['sql_db']=$_SESSION['sql_db_org'];
    } else {
        $CONF['sql_host']=$CONF['sql_host_s'][$_SESSION['wss']];
        $CONF['sql_user']=$CONF['sql_user_s'][$_SESSION['wss']];
        $CONF['sql_passwd']=$CONF['sql_passwd_s'][$_SESSION['wss']];
        $CONF['sql_db']=$CONF['sql_db_s'][$_SESSION['wss']];        
    }
}

// set export directory and global-conf file based on multi user mode
if (!$_SESSION['multi_user_mode']) {
    // choose the right export directory in multi db mode
    if (count($CONF['sql_host_s']) && basename($_SERVER['SCRIPT_NAME'])!=="config.php") {
        // multi db mode
        if ($_SESSION['wss']<0) {
            // main account from global_conf.php
            define('PMBP_EXPORT_DIR',$_PMBP_EXPORT_DIR);
        } else {
            // other accounts        
            define('PMBP_EXPORT_DIR',$_PMBP_EXPORT_DIR.$CONF['sql_host']."_".$CONF['sql_user']."/");            
        }
    } else {
        // single db mode
        define('PMBP_EXPORT_DIR',$_PMBP_EXPORT_DIR);
    }
} else {
    // multi user mode
    define('PMBP_EXPORT_DIR',$PMBP_MU_CONF['user_export_dir']);
}

// try to create export directories
@umask(0000);
@mkdir(PMBP_EXPORT_DIR,0777);

// check if language was just changed in config.php
if (isset($_POST['lang']) && ereg_replace(".*/","",$_SERVER['PHP_SELF'])=="config.php") $CONF['lang']=$_POST['lang'];

// include language.inc.php
if (!isset($CONF['lang'])) $CONF['lang']="english";
if (!file_exists($prepath.PMBP_LANGUAGE_DIR.$CONF['lang'].".inc.php")) include_once($prepath.PMBP_LANGUAGE_DIR."english.inc.php"); else include($prepath.PMBP_LANGUAGE_DIR.$CONF['lang'].".inc.php");

// set local time to defined or environment variable value
if (function_exists("phpversion")) {
    $tmp=@phpversion();
    $phpvers=$tmp[0].$tmp[1].$tmp[2];
} else {
    $phpvers="0";
}

if (defined("BD_LANG_SHORTCUT") AND $phpvers>=4.3) setlocale(LC_TIME,BD_LANG_SHORTCUT,BD_LANG_SHORTCUT."_".strtoupper('BD_LANG_SHORTCUT')); else setlocale(LC_TIME,"");

// special part for arabic language
if ($CONF['lang']=="arabic") define('ARABIC_HTML'," dir=\"rtl\""); else define('ARABIC_HTML',"");

// update the system variables but not before login
if ($_SESSION['multi_user_mode'] && $_PMBP_GLOBAL_CONF!=PMBP_GLOBAL_CONF || !$_SESSION['multi_user_mode'])
    include("sys_vars.inc.php");
?>