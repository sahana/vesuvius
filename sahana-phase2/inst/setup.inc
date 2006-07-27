<?php
/**
* Sahana web setup. Initially launched to setup the database and sahana configuration 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

session_start();

require_once ($global['approot'].'inc/handler_html_head.inc');
require_once ($global['approot'].'inc/lib_modules.inc'); 
require_once ($global['approot'].'inc/lib_form.inc'); 
require_once ($global['approot'].'inc/lib_errors.inc'); 
require_once ($global['approot'].'3rd/adodb/adodb.inc.php');
require_once ($global['approot'].'inc/lib_config.inc');
require_once ($global['approot'].'inc/lib_locale/handler_locale.inc');

shn_setup_main();

// main setup switchboard 
function shn_setup_main()
{
    $action = $_GET['act'];
    $modify = array();

    // display nice header
    shn_setup_header();
    switch ($action) {

    case 'dependancy':
        if (shn_setup_check_dependancy()) { // check if database writing is a success
            shn_setup_form1();
        } else {
            display_errors();
            shn_setup_form_dependancy(); 
        }
      
        break;

    case 'dbsetup': // second setup form
        if (shn_setup_database()) { // check if database writing is a success
            shn_setup_form2();
        } else {
            display_errors();
            shn_setup_form1();
        }
        break;
        
    case 'cfgsetup': // third setup form

        if (shn_setup_config_update($_POST['conffile'])) { 
            // check if writing the file was a success
            shn_setup_form_conffile();
        } else {
            display_errors();
            shn_setup_form2();
        }
        break;

    default: 
        // first database setup form
        shn_setup_form_dependancy();

    }
    shn_setup_footer();
}

function shn_setup_check_dependancy()
{
    global $global;

    $continue = true;

    if (!version_compare(phpversion(), '4.1', '>')) $continue = false;
    if (!extension_loaded('gd')) $continue = false;
    if (!extension_loaded('mysql')) $continue = false;
    if (!is_writable($global['approot'].'www/tmp')) $continue = false;

    return $continue;
}

function shn_setup_form_dependancy()
{
    global $global;
    $isOK = true;
    $tick_img = '<img align="top" src="theme/default/img/tic.png"/>';
    $cross_img = '<img align="top" src="theme/default/img/cross.png"/>';
    $oops_img = '<img align="bottom" src="theme/default/img/oops.png"/>';
?>
    <h1><?=_('Sahana Web Setup - Step 1')?></h1>

    <p><?=_('Welcome to Sahana. Please follow the following steps to setup the Sahana system')?></p>

    <p><?=_('First we need to check if all the relevant dependancies for the Sahana system to be install are available on your system')?></p>
<?php

    shn_form_fopen(_('dependancy'));

    shn_form_fsopen(_('PHP libraries'));
?>
    <p><?=_('The following checks if all the relevant Sahana libraries are installed')?></p>
<?php
    
    $value = (version_compare(phpversion(), '4.1', '>'));
    $isOK &= $value;

    //if ($isOK) echo "is OK"; 
    if ($value) {
        shn_form_label(_('PHP Version'), $tick_img.phpversion()." is installed");
    } else {
        shn_form_label(_('PHP Version'), $cross_img.phpversion()." is installed");
        echo "<p><br/>$oops_img Sahana needs PHP version 4.1 or higher. Please upgrate your version of PHP</p>";
    }
    
    $value = (extension_loaded('gd'));
    $isOK &= $value;

    if ($value) {
        shn_form_label(_('PHP-GD Library'), $tick_img."installed");
    } else {
        shn_form_label(_('PHP-GD Library'), $cross_img."is not installed");
        echo "<p><br/>$oops_img Sahana needs PHP-GD for image manipulations. Please install PHP-GD and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
    }
 
    $value = (extension_loaded('mysql'));
    $isOK &= $value;

    if ($value) {
        shn_form_label(_('MySQL library'), $tick_img."installed");
    } else {
        shn_form_label(_('MySQL library'), $cross_img."is not installed");
        echo "<p><br/>$oops_img Sahana needs PHP-MySQL library and MySQL for database operation. Please install PHP-MySQL library and MySQL and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
    }

    shn_form_fsclose();
    shn_form_fsopen(_('File and Directory Permissions'));
?>
    <p><?=_('The following checks if certain files and directories have write persmissions for Sahana to function')?></p>
<?php
    $value = is_writable($global['approot'].'www/tmp');
    $isOK &= $value;

    if ($value) {
        shn_form_label(_('www/tmp/ is writable?'), $tick_img."directory writable");
    } else {
        shn_form_label(_('www/tmp/ is writable?'), $cross_img."directory not writable");
        echo "<p><br/>$oops_img The directory ".$global['approot']."www/tmp needs to be writable by the web server at least. Please change the permissions of this directory and try again.</p>";
    }

/*   $value = (is_writable($global['approot'].'res/locale'))? 'checked':'';

    shn_form_checkbox('Sahana res/locale is writable?','write_locale',$value.' 
                        disabled="true"',array('value'=>'y','help'=>'hello')); 
*/
    $value = is_writable($global['approot'].'conf');

    if ($value) {
        shn_form_label(_('www/conf/ is writable?'), $tick_img."directory writable");
    } else {
        shn_form_label(_('www/conf/ is writable?'), "directory not writable");
        echo "<p><br/>$oops_img The directory ".$global['approot']."conf/ is not writable. However this you can still copy the configuration file to the conf/ directory later.</p>";
    }

    shn_form_fsclose();

    if ($isOK) {
        echo _('<p>All the dependancies are OK and you may move to
                the next step</p>')."\n";
        shn_form_submit(_('Next >>'));
    } else {
        echo _('<p>Please correct the required dependancies above and</p>')."\n";
        shn_form_submit(_('Try Again'));
    }
    shn_form_fclose();
}

// the database setup form
function shn_setup_form1()
{
 ?>
    <h1><?=_('Sahana Database Setup - Step 2')?></h2>
<?php

    shn_form_fopen('dbsetup');

    shn_form_fsopen(_('Database'));
    shn_form_select(
        array( 'mysql' => 'MySQL 4.1 or above'), 
                'Database Types', 'dbtype');
    shn_form_text(_('Database Host:Port'),'dbhost','size="30"',
                array('value'=>'localhost','req'=>true ));
    shn_form_text(_('Database Name'),'dbname','size="30"',
                array('value'=>'sahana', 'req'=>true));
    shn_form_text(_('Database User'),'dbuser','size="30"',
                array('value'=>'root', 'req'=>true));
    shn_form_password(_('Database Password'),'dbpass','size="30"', array('req'=>true));
    shn_form_fsclose();

    shn_form_fsopen(_('Schema\'s to Install'));
    shn_form_checkbox(_('Default Item Categories'),'dbsample','checked',
                        array('value'=>'y', 'help'=>'Check this to 
                        create the default categories for aid goods, units')); 
    shn_form_fsclose();
    shn_form_submit(_('Setup Database >>'));
 
    shn_form_fclose();
}


// the config file setup form
function shn_setup_form2()
{
 ?>
    <h1>Sahaha Web Setup - Step 3</h2>
    <p> Please follow the following steps to setup the Sahana configuration </p>
<?php
    global $global;

    shn_form_fopen('cfgsetup');
    
    // pass the previous post varibles into hidden for the configuration file
    shn_form_hidden( array(
        'dbhost' => $_POST['dbhost'] ,
        'dbname' => $_POST['dbname'] ,
        'dbuser' => $_POST['dbuser'] ,
        'dbpass' => $_POST['dbpass'] ));           

    shn_form_fsopen(_('Settings'));
    shn_form_password(_('root (admin) Password'),'rootpwd','size="30"', 
        array('req'=>true, 'help'=>'The root user is the administrator
                of the system and has the greatest privilages'));
    shn_form_select(
        array( 'disable' => _('Disable'),'enable' =>_('Enable')), 
                _('Access Control'),'acl');
    shn_form_select(
        array( 'default' => _('Default Theme')), 
                _('Theme'), 'theme');
    shn_form_fsclose();

    shn_form_fsopen(_('Configuration File'));

    if (is_writeable($global['approot'].'conf')) {
    
        echo '<p>The next step is to write the configuration file sysconf.inc in the Sahana /conf directory.';

        shn_form_hidden(array('conffile' => 
            $global['approot'].'conf/sysconf.inc'));

    } else {

        echo '<p>The PHP/Web Server should normally not have access to write 
    or modify the configuration file located in Sahana application <b>/conf</b> 
    directory, as this is a security risk. Please specify where to write the temporary file (e.g. /tmp). Subsequently you need to move this file to 
    the Sahana <b>/conf</b> directory.</p>';

        $tmp_filename = tempnam('/tmp','sysconf.inc');
        // Need the temporary directory rather than the filename
        $tmp_filename = preg_replace('/sysconf.inc.*$/','sysconf.inc',
                        $tmp_filename); 

        shn_form_text(_('Location To Write Config File (sysconf.inc)'),
                'conffile','size="50"', array('value'=>"$tmp_filename",
                'req'=>true ));

    }
    shn_form_fsclose();

    shn_form_submit(_('Write Configuration File >>'));
 
    shn_form_fclose();
}


function shn_setup_form_conffile()
{
?>
    <h1><?=_('Sahaha Web Setup - Step 3')?></h2>
    <p><?=_('Configuration file ')?><?=$_POST['conffile']?> <?=_(' has been successfully written.')?></p>

<?php
    global $global;
    $oops_img = '<img align="bottom" src="theme/default/img/oops.png"/>';

    shn_form_fopen('default','admin',array('req_message' => false));
    shn_form_fsopen(_('Starting Sahana'));
    
    shn_form_hidden( array(
        'conffile' => $_POST['conffile'] )); 
    $sahana_url = 'http://'.$_SERVER['HTTP_HOST'].preg_replace('/index.php\?.*$/','',$_SERVER['REQUEST_URI']);

    if (is_writeable($global['approot'].'conf')) {
?>
    <p><b><u><?php echo $oops_img._('WARNING: Security')?></u></b></p>
    <p><?php echo _('To secure the configuration you have to remove write 
             permissions from the configuration file sysconf.inc located in 
             the Sahana directory conf/')?></p>

    <p><?=_('Click the button below to start Sahana')?>

<?php
    } else {
?>

    <p><?=_('To finish the configuration follow the steps below')?></p>
    <p> <b>1.</b><?=_(' Copy the temporary config file created from: ')?><br/>
        <u><?=$_POST['conffile']?></u> to: <br/>
     <u><?=$global['approot']."conf/sysconf.inc"?></u></p>
    <p> <b>2.</b><?=_(' For security reasons delete the temporary configuration file at ')?><u><?=$_POST['conffile']?></u></p>
    <p> <b>3.</b><?=_(' Once done click the button below to start Sahana or access it anytime using the url: ')?><a href="<?=$sahana_url?>"><?=$sahana_url?></a></p>

<?php        
    }
    shn_form_fsclose();
    shn_form_submit(_('Start Sahana'));    
    shn_form_fclose();
}

// connect to the database and run the scripts specified by the user
function shn_setup_database()
{
    global $global;

    $db = &NewADOConnection('mysql');
    if (! $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass']) ) {
        add_error(_('Could not connect to the database. Please check the setting and try again'));
        return false;
    }

    // create the main database
    $db->Execute("CREATE DATABASE IF NOT EXISTS ".$_POST['dbname']);
    $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass'],$_POST['dbname']);
    $global['db'] = $db;

    // setup the choosen sql scripts
    shn_setup_run_sqlscript($db,'inst/mysql-dbcreate.sql');
    shn_setup_run_sqlscript($db,'inst/mysql-acl.sql');
    shn_setup_run_sqlscript($db,'mod/rms/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/gis/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/cs/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/ims/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'inst/mysql-config.sql');

    if ($_POST['dbsample']=='y') {
        include_once($global['approot'].'inc/lib_uuid.inc');
        shn_setup_run_sqlscript($db,'inst/mysql-sampledata.sql');
        include($global['approot'].'mod/cs/ins/setup.inc');
        shn_cs_datacreate();
    }

    return true;
}

// runs the script file relative to the approot
function shn_setup_run_sqlscript($db, $relative_script_path)
{
    global $global;

    $script = $global['approot'].$relative_script_path;

    if ($fh = fopen($script,'r')) {
        $sql='';
        
        while (! feof($fh) ) { // a fix as Execute gets confused over carriage returns 
            $t = fgets($fh,1024);
            $sql=$sql.$t;
            if(preg_match('/;/',$t)) {
                $db->Execute($sql);
                $sql='';
            }
        }
        //$sql = fread($fh,filesize($script));
        fclose($fh);
    }
    // @todo error handler if file does not exist
}


function shn_setup_config_update($tmp_configfile)
{
    global $global;

    $modify = array( 
        '/\'theme\'/' => '$conf[\'theme\'] = \''.$_POST['theme'].'\';' ,
        '/\'db_host\'/' => '$conf[\'db_host\'] = \''.$_POST['dbhost'].'\';' ,
        '/\'db_name\'/' => '$conf[\'db_name\'] = \''.$_POST['dbname'].'\';' ,
        '/\'root_pwd\'/' => '$conf[\'root_pwd\'] = \''.$_POST['rootpwd'].'\';' ,
        '/\'db_user\'/' => '$conf[\'db_user\'] = \''.$_POST['dbuser'].'\';' ,
        '/\'db_pass\'/' => '$conf[\'db_pass\'] = \''.$_POST['dbpass'].'\';' );           

    if ( @shn_config_file_update( $modify, $global['approot'].'conf/sysconf.inc.tpl',
                            $tmp_configfile) ) {
        return true;
    } else {
        add_error(_('Could not write to file $tmp_configfile. Try another location'));
        return false;
    }
}

function shn_setup_header() 
{
?>
    <body>
    <div id="container">
<?php 
    shn_include_page_section('header',$module);
?>
    <div id="wrapper" class="clearfix">
    <div id="content" class="clearfix">      
<?php
}

function shn_setup_footer()
{
?>
    </div> <!-- /content -->
<?php
    shn_include_page_section('footer',$module);
?>
    </div> <!-- /wrapper -->
    </div> <!-- /container -->
    </body>
    </html>
<?php
}
