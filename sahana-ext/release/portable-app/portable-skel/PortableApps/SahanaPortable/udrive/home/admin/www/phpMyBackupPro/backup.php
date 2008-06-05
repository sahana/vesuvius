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

// login is not loaded, because of scheduled backups
// session_start() is needed for multi db mode
@session_start();

require_once("definitions.php");

// used variables
if (!isset($argv)) $argv=FALSE;
if (!isset($_POST['db'])) $_POST['db']=FALSE;
if (!isset($_POST['tables'])) $_POST['tables']=FALSE;
if (!isset($_POST['data'])) $_POST['data']=FALSE;
if (!isset($_POST['zip'])) $_POST['zip']=FALSE;
if (!isset($_POST['drop'])) $_POST['drop']=FALSE;
if (!isset($_POST['man_dirs'])) $_POST['man_dirs']=FALSE;
if (!isset($_POST['comments'])) $_POST['comments']=FALSE;
if (!isset($_POST['packed'])) $_POST['packed']=FALSE;

// session
if (!isset($_SESSION['LOGGED_IN'])) $_SESSION['LOGGED_IN']=FALSE;

// is shell mode or web-based mode or export-script mode used or is user not logged in?
if ($argv) {
	
    echo "+======>\n| phpMyBackupPro ".PMBP_VERSION." (c) 2004-2007 by Dirk Randhahn\n| ".PMBP_WEBSITE."\n+======>\n\n";
    if (!isset($argv[1])) {
        echo PMBP_EX_NO_ARGV;
        exit;
    }
    $mode="shell";
    $_POST['db']=$argv[1];
    if (isset($argv[2])) {
        if ($argv[2]) $_POST['tables']="on"; else $_POST['tables']="off";
    } else $_POST['tables']="off";
    if (isset($argv[3])) {
        if ($argv[3]) $_POST['data']="on"; else $_POST['data']="off";
    } else $_POST['data']="off";
    if (isset($argv[4])) {
        if ($argv[4]) $_POST['drop']="on"; else $_POST['drop']="off";
    } else $_POST['drop']="off";
    if (isset($argv[5])) {
        if ($argv[5]) $_POST['zip']="gzip"; else $_POST['zip']="off";
    } else $_POST['zip']="off";
    if (isset($argv[6])) $_POST['man_dirs']=$argv[6]; else $_POST['man_dirs']=FALSE;
    
// backups are only triggered if security key is set right
// older versions of the backup script witout security key should not cause error outputs, but will not trigger backups!
} elseif (isset($security_key)) {
    $mode="incl";
    include_once("definitions.php");
    if (!isset($_SESSION['wss'])) $_SESSION['wss']=-1;
    // is a databse or a directory selected?
    if ($_POST['db'] || isset($_POST['dirs']) || strlen($_POST['man_dirs'])) {
        // backups can only be triggered with the right security key!
        if ($security_key==$PMBP_SYS_VAR['security_key']) {
            // add new 'last_scheduled' system variables if it does not exist for the current account
            if ($_SESSION['wss']<0) {
                if (!isset($PMBP_SYS_VAR['last_scheduled'])) $PMBP_SYS_VAR['last_scheduled']=0;
            } else {
                if (!isset($PMBP_SYS_VAR['last_scheduled_'.$_SESSION['wss']])) $PMBP_SYS_VAR['last_scheduled_'.$_SESSION['wss']]=0;
            }
            // check if it is already time for a new backup
            if ($period!=0) {
	            if ( ($_SESSION['wss']<0 && $PMBP_SYS_VAR['last_scheduled']>(time()-$period) ) ||
	            ($_SESSION['wss']>=0 && $PMBP_SYS_VAR['last_scheduled_'.$_SESSION['wss']]>(time()-$period)) ) {
	                if($PMBP_SYS_VAR['scheduled_debug'])
	                    echo "It's not time for a new backups yet! Set period to 'At each call' for debugging.<br>\n";
	                return FALSE;
	            }
            }
        } else {
            if($PMBP_SYS_VAR['scheduled_debug'])
                echo "The security key is wrong. It must have the same value as in global_conf.php. Create a new script!<br>\n";
            return FALSE;
        }
    } else {
        if($PMBP_SYS_VAR['scheduled_debug'])
            echo "No database or directory was selected to backup.<br>\n";
        return FALSE;
    }
    if($PMBP_SYS_VAR['scheduled_debug'])
        echo "Start backing up the databases now:<br>\n";    
} else {
    $mode="web";
    include("login.php");
}

// set the timelimit
@set_time_limit($CONF['timelimit']);
@ignore_user_abort(TRUE);

if ($mode=="incl") {    
    // save the new timestamp
    if ($_SESSION['wss']<0) {
        $PMBP_SYS_VAR['last_scheduled']=time();
    } else {
        $PMBP_SYS_VAR['last_scheduled_'.$_SESSION['wss']]=time();
    }
    // update global_conf.php
    PMBP_save_global_conf();
}


// print html if web mode
if ($mode=="web") {
    PMBP_print_header(ereg_replace(".*/","",$_SERVER['SCRIPT_NAME']));

    // if first use or no db-connection possible
    if (!@mysql_connect($CONF['sql_host'],$CONF['sql_user'],$CONF['sql_passwd'])) echo "<div class=\"red\">".I_SQL_ERROR."</div><br>\n";

    // check if ftp connection is possible
    if ($CONF['ftp_use'] || $CONF['dir_backup']) {
        if (!$CONF['ftp_server']) {
            echo "<div class=\"red\">".C_WRONG_FTP."</div>";
        } elseif (!$conn_id=@ftp_connect($CONF['ftp_server'],$CONF['ftp_port'],$PMBP_SYS_VAR['ftp_timeout'])) {
            echo "<div class=\"red\">".F_FTP_1." '".$CONF['ftp_server']."'!</div>";
        }
    }
}

// if pressed 'backup' backup the db
if ($_POST['db'] || isset($_POST['dirs']) || strlen($_POST['man_dirs'])) {
    $out="";

    // get start time to calculate duration
    if (function_exists("microtime")) {
        $microtime=explode(" ",microtime());
        $starttime=($microtime[0]+$microtime[1]);
    } else {
        $starttime=time();
    }    

    // delete old backup files
    PMBP_get_backup_files();

    // save PMBP_SYS_VARS
    if ($mode=="web") PMBP_save_export_settings();

    // in shell mode the dbs must be seperated with commas
    if ($mode=="shell") $db_list=explode(",",$_POST['db']);
        elseif(!isset($_POST['db'][0])) $db_list=FALSE;
            else $db_list=$_POST['db'];                 

    // get all available databases
    $available_dbs=PMBP_get_db_list();

    // always backup all dbs in scheduled mode, if the system variable is set
    if ($mode=="incl" && $PMBP_SYS_VAR["schedule_all_dbs"]) {
        $db_list=$available_dbs;
    }         

    // is a database selected?
    if ($db_list) {
            
        foreach($db_list as $export_db) {
        
            // check if $export_db is available
            if (in_array($export_db,$available_dbs)) {

                // generate db dump
                $backupfile=PMBP_dump($export_db,($_POST['tables']=="on"),($_POST['data']=="on"),($_POST['drop']=="on"),$_POST['zip'],$_POST['comments']);

                // is there no db connection or a db missing?
                if ($backupfile && $backupfile!=="DB_ERROR") {
                    // change mode to 0777                    
                    @chmod("./".$backupfile,0777);

                    // remind filenames if backup by ftp or email is selected
                    if (($CONF['email_use'] && function_exists("mail")) || ($CONF['ftp_use'] && function_exists("ftp_connect"))) {
                    	$store_files[]=PMBP_EXPORT_DIR.$backupfile;
                    }

                    if ($mode=="web") echo "<div class=\"green\">".EX_SAVED." ".$backupfile."</div>\n";
                        elseif ($mode=="shell") echo EX_SAVED." ".$backupfile."\n";
                            elseif($mode=="incl") $out.=EX_SAVED." ".$backupfile."<br>\n";
                    
                } elseif($backupfile==="DB_ERROR") {
                    if ($mode=="web") echo "<div class=\"red\">".C_WRONG_SQL."</div>\n";
                        elseif ($mode=="shell") echo C_WRONG_SQL."\n";
                            elseif($mode=="incl") $out.=C_WRONG_SQL."<br>\n";
                } else {
                    if ($mode=="web") printf("<div class=\"red\">".EX_NOT_SAVED."</div>\n",$export_db,PMBP_EXPORT_DIR);
                        elseif ($mode=="shell") printf(EX_NOT_SAVED."\n",$export_db,PMBP_EXPORT_DIR);
                            elseif($mode=="incl") $out.=sprintf(EX_NOT_SAVED."<br>\n",$export_db,PMBP_EXPORT_DIR);
                }
                
            } else {
                if ($mode=="web") printf("<div class=\"red\">".PMBP_EX_NO_AVAILABLE."</div>\n",$export_db);
                    elseif ($mode=="shell") printf(PMBP_EX_NO_AVAILABLE."\n",$export_db);
                        elseif($mode=="incl") $out.=sprintf(PMBP_EX_NO_AVAILABLE."<br>\n",$export_db);
            }
        }
    } else {
        if ($mode=="web") echo "<div class=\"red\">".EX_NO_DB."</div><br>\n";
            elseif ($mode=="shell") echo EX_NO_DB."\n";
                elseif ($mode=="incl") $out.=EX_NO_DB."<br>\n";
            
    }

    // start backup using ftp or email
    $backup_info=array("comments"=>$_POST['comments'],"tables"=>($_POST['tables']=="on"),"data"=>($_POST['data']=="on"),"drop"=>($_POST['drop']=="on"),"comp"=>$_POST['zip']);
    if ($CONF['ftp_use'] && isset($store_files)) $out=PMBP_ftp_store($store_files)."\n";
    if ($CONF['email_use'] && isset($store_files)) $out.=PMBP_email_store($store_files,$backup_info);
    
    // file backup per FTP
    if ($CONF['dir_backup'] && (isset($_POST['dirs']) || strlen($_POST['man_dirs']))) {
        $_POST['man_dirs']= str_replace("\n",",",$_POST['man_dirs']);
        $files=array();
        if (isset($_POST['dirs'])) {
            $_POST['dirs']=array_merge(explode(",",$_POST['man_dirs']),$_POST['dirs']);
            foreach($_POST['dirs'] as $dir) $files=array_merge($files,PMBP_get_files($dir));
        } else {
            foreach(explode("|",$_POST['man_dirs']) as $dir) $files=array_merge($files,PMBP_get_files($dir));
        }
        
        // backup files by emails
        if($PMBP_SYS_VAR['dir_email_backup']) {
        	$out.=PMBP_email_store($files,$_POST['comments']);
        }
        // backup files by FTP
        $out.=PMBP_save_FTP($files,$_POST['packed']);
    }
    
    // show execution duration
    if (function_exists("microtime")) {
        $microtime=explode(" ",microtime());
        $endtime=($microtime[0]+$microtime[1]);
    } else {
        $endtime=time();
    }

    if ($mode=="web") {
        echo $out."\n";
        echo "<div class=\"bold\">".F_DURATION.": ".number_format($endtime-$starttime,3)." ".F_SECONDS."</div>\n";
        	echo "<br>";
    } elseif ($mode=="shell") {
        echo $out;
        echo F_DURATION.": ".number_format($endtime-$starttime,3)." ".F_SECONDS;
    } elseif($mode=="incl") {
         if ($PMBP_SYS_VAR['scheduled_debug']) {
            echo $out;
            echo F_DURATION.": ".number_format($endtime-$starttime,3)." ".F_SECONDS;
         }         
    }
}

// show the form for selecting a db to backup
if ($mode=="web") {
    echo "<form action=\"backup.php\" method=\"post\" name=\"backup\">\n<div>\n";
    PMBP_print_export_form();
    echo "\n<input type=\"submit\" value=\"".EX_EXPORT."\" class=\"button\">\n</div>\n</form>\n";
}

// update file list (deletes new generated files if $CONS[del_numer]=0)
PMBP_get_backup_files();

// print html if web mode
if ($mode=="web") {
    PMBP_print_footer();
} elseif ($mode=="incl") {
        return TRUE;
}
?>
