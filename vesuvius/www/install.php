<?php
/**
 * Sahana Agasti install.php, this file should be used only upon installation of Sahana Agasti
 * The purpose of the file is to automate the distro-like creation of the Agasti Application
 * The installer takes the input of users to customize the install of Agasti
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPLv3.0 license
 * that is available through the worldwideweb at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Charles Wisniewski, CUNY SPS
 *
 * Copyright of the Sahana Software Foundation, sahanafoundation.org
 */
$install_flag=true;
require_once(dirname(__FILE__).'/install/install.inc.php');


global $INS_CONFIG;

if (isset($_REQUEST['cancel']) || isset($_REQUEST['finish'])) {
  installer_unsetcookie('INS_CONFIG');
}

$INS_CONFIG = get_cookie('INS_CONFIG', null);
if (isset($INS_CONFIG)) {
  $INS_CONFIG = unserialize(stripcslashes($INS_CONFIG));
} else {
  $INS_CONFIG = array();
}
if (!isset($INS_CONFIG['step']))
  $INS_CONFIG['step'] = 0;
if (!isset($INS_CONFIG['agree']))
  $INS_CONFIG['agree'] = false;
if(!isset($INS_CONFIG['rootpath']))
    $INS_CONFIG['rootpath']=dirname(dirname(__FILE__));

$INS_CONFIG['allowed_db'] = array();

/*/* MYSQL */
if (installer_is_callable(array('mysql_pconnect', 'mysql_select_db', 'mysql_error', 'mysql_select_db', 'mysql_query', 'mysql_fetch_array', 'mysql_fetch_row', 'mysql_data_seek', 'mysql_insert_id'))) {
  $INS_CONFIG['allowed_db']['MYSQL'] = 'MySQL';
}

/* POSTGRESQL */
if (installer_is_callable(array('pg_pconnect', 'pg_fetch_array', 'pg_fetch_row', 'pg_exec', 'pg_getlastoid'))) {
  $INS_CONFIG['allowed_db']['POSTGRESQL'] = 'PostgreSQL';
}

/* ORACLE */
if (installer_is_callable(array('ocilogon', 'ocierror', 'ociparse', 'ociexecute', 'ocifetchinto'))) {
  $INS_CONFIG['allowed_db']['ORACLE'] = 'Oracle';
}

/* SQLITE3 */
if (installer_is_callable(array('sqlite3_open', 'sqlite3_close', 'sqlite3_query', 'sqlite3_error', 'sqlite3_fetch_array', 'sqlite3_query_close', 'sqlite3_exec'))) {
  $INS_CONFIG['allowed_db']['SQLITE3'] = 'SQLite3';
}

if (count($INS_CONFIG['allowed_db']) == 0) {
  $INS_CONFIG['allowed_db']['no'] = 'No';
}

global $APP_INSTALL;

$APP_INSTALL = new appInstall($INS_CONFIG);


installer_set_post_cookie('INS_CONFIG', serialize($INS_CONFIG));

installer_flush_post_cookies();

unset($_POST);
?>
<!--?xml version="1.0" encoding="utf-8"?-->
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>Sahana Agasti 2.0 Installer</title>
    <link rel="shortcut icon" href="install/images/favicon.ico" />
    <link rel="stylesheet" type="text/css" media="screen" href="install/css/main.css" />
  </head>
  <body>
    <div id="header">
      <h1>
        Vesuvius Installer
      </h1>
    </div>
    <div id="wrapper">
      <div id="columns">
        <h3><?php echo $APP_INSTALL->steps[$APP_INSTALL->getStep()]['title']; ?></h3>
        <div id="columnLeft">
<?php echo $APP_INSTALL->getList(); ?>
        </div>
        <div id="columnRight">
          <form action="install.php" method="post" class="configure" style="margin-right: 80px; float: left;">
          <?php echo $APP_INSTALL->getState(); ?>

            <ul>
              <li style="text-align: right">
                <input type="hidden" name="_enter_check" value="1" />
                <input type="hidden" name="_sql_check" value="<?php echo $install_flag; ?>" />

                <input id="back[<?php echo $APP_INSTALL->getStep(); ?>]" name="back[<?php echo $APP_INSTALL->getStep(); ?>]" type="submit" value="<< previous"<?php //echo $APP_INSTALL->; ?> class="linkButton" />
                <input type="submit" value="cancel" class="linkButton" id="cancel" name="cancel" />
<?php
          if (!isset($APP_INSTALL->steps[$APP_INSTALL->getStep() + 1])) {
            //checking to see if there is anything left in the ag_install stage
            $dolab = 'finish';
            $doval = 'finish';
          } else {
            $dolab = "next[" . $APP_INSTALL->getStep() . "]";
            $doval = "next >>";
          } ?>
                <input id="next[<?php echo $dolab; ?>]" name="<?php echo $dolab ?>" type="submit" value="<?php echo $doval ?>" class="linkButton" <?php if ($APP_INSTALL->DISABLE_NEXT)
                  echo " disabled=true"; ?> />
              </li>
            </ul>
          </form>
        </div>
      </div>
    </div>
    <div id="footer">
      <img src="install/images/nyc_logo.png" alt="NYC Office of Emergency Management Logo" />
    </div>
  </body>
</html>
