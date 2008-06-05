<?php
/*

Use this file to configure the phpMyBackupPro multi user mode.
Don't touch this file if you only want to use phpMyBackupPro for one MySQL user.

*/

// specify the MySQL root account data or set to "" to disable the multi user mode
$PMBP_MU_CONF['sql_host_admin']="locahost";
$PMBP_MU_CONF['sql_user_admin']="";
$PMBP_MU_CONF['sql_passwd_admin']="";

// set the home directory for each users backup files (eg. a subdirectory of his home directory)
// use $_SESSION['sql_user'] as placeholder for the user name
// sample:  $PMBP_MU_CONF['user_export_dir' ="../../user_directories/".$PMBP_MU_CONF['user_export_dir']."/mysql_backups/";
$PMBP_MU_CONF['user_export_dir']="./export_mu/".$_SESSION['sql_user']."/";

// set the path for each users config file
// use $_SESSION['sql_user'] as placeholder for the user name
// sample: $PMBP_MU_CONF['user_conf_file']="../../home/".$PMBP_MU_CONF['user_export_dir']."/phpMyBackupPro_conf.txt";
$PMBP_MU_CONF['user_conf_file']="./export_mu/".$_SESSION['sql_user']."/phpMyBackupPro_conf.php";

// set a path for each user where he can place a scheduled backup script (eg. his home directory)
// use $_SESSION['sql_user'] as placeholder for the user name
// sample: $PMBP_MU_CONF['user_conf_file']="../../home/".$PMBP_MU_CONF['user_export_dir']."/www/";
$PMBP_MU_CONF['user_scheduled_dir']="./export_mu/";


// set the rights for the users

// set to false to hide the 'sql queries' page (recommended)
// otherwise set to true
$PMBP_MU_CONF['allow_sql_queries']=true;

// set to true to allow sending of emails (recommended)
// otherwise set to false
$PMBP_MU_CONF['allow_email']=true;

// set to true to allow FTP transfers to remote servers (recommended) 
// otherwise set to false
// (if true, each user can choose his own FTP server)
$PMBP_MU_CONF['allow_ftp']=true;

// set to true to allow file directory backups
// otherwise set to false
// (if true, each user can choose his own FTP server)
$PMBP_MU_CONF['allow_dir_backup']=true;

// set server name
// leave it blank to let the users set it by their own
$PMBP_MU_CONF['sitename']="Uniform Server";

?>
