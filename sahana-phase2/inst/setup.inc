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


require_once ($global['approot']."inc/handler_html_head.inc");
require_once ($global['approot'].'inc/lib_modules.inc'); 
require_once ($global['approot'].'inc/lib_form.inc'); 
require_once ($global['approot'].'inc/lib_errors.inc'); 
require_once ($global['approot'].'3rd/adodb/adodb.inc.php');
require_once ($global['approot'].'inc/lib_config.inc');

shn_setup_main();

// main setup switchboard 
function shn_setup_main()
{
    $action = $_GET['act'];
    $modify = array();

    // display nice header
    shn_setup_header();
    switch ($action) {

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
            shn_setup_form3();
        } else {
            display_errors();
            shn_setup_form2();
        }
        break;

    default: 
        // first database setup form
        shn_setup_form1();

    }
    shn_setup_footer();
}

// the database setup form
function shn_setup_form1()
{
 ?>
    <h1><?=_('Sahaha Web Setup')?></h2>
    <p><?=_('Welcome to Sahana. Please follow the following steps to setup the Sahana system ')?></p>
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
    shn_form_checkbox(_('Create Main Database tables'),'dbcreate',"checked",
                        array('value'=>'y')); 
    shn_form_checkbox(_('Default Configuration'),'dbconfig',"checked",
                        array('value'=>'y')); 
    shn_form_checkbox(_('Sample Data'),'dbsample','',
                        array('value'=>'y')); 
    shn_form_fsclose();
    shn_form_submit(_('Setup Database >>'));
 
    shn_form_fclose();
}


// the config file setup form
function shn_setup_form2()
{
 ?>
    <h1>Sahaha Web Setup - Step 2</h2>
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
    shn_form_select(
        array( 'default' => _('Default Theme')), 
                _('Theme'), 'theme');
    shn_form_select(
        array( 'disable' => _('Disable'),'enable' =>_('Enable')), 
                _('Access Control'),'acl');
    shn_form_fsclose();

    shn_form_fsopen(_('Configuration File'));
?>
    <p><?=_('The PHP/Web Server should normally not have access to write 
    or modify the configuration file located in Sahana application <b>/conf</b> 
    directory, as this is a security risk. Please specify where to
    write the temporary file (e.g. /tmp). Subsequently you need to move this file to 
    the Sahana <b>/conf</b> directory.</p>')?>
<?php
    $tmp_filename = tempnam('/tmp','sysconf.inc');
    // Need the temporary directory rather than the filename
    $tmp_filename = preg_replace('/sysconf.inc.*$/','sysconf.inc',$tmp_filename); 

    shn_form_text(_('Location To Write Config File (sysconf.inc)'),'conffile','size="50"',
                array('value'=>"$tmp_filename",'req'=>true ));
    shn_form_fsclose();

    shn_form_submit(_('Write Configuration File >>'));
 
    shn_form_fclose();
}


function shn_setup_form3()
{
?>
    <h1><?=_('Sahaha Web Setup - Step 3')?></h2>
    <p><?=_('Configuration file ')?><?=$_POST['conffile']?> <?=_(' has been successfully written.')?></p>

<?php
    global $global;
    shn_form_fopen('default','home');
    shn_form_fsopen(_('Configuration File'));
    shn_form_hidden( array(
        'conffile' => $_POST['conffile'] )); 
    $sahana_url = 'http://'.$_SERVER['HTTP_HOST'].preg_replace('/index.php\?.*$/','',$_SERVER['REQUEST_URI']);
?>

    <p><?=_('To finish the configuration follow the steps below')?></p>
    <p> <b>1.</b><?=_(' Copy the temporary config file created from: ')?><br/>
        <u><?=$_POST['conffile']?></u> to: <br/>
     <u><?=$global['approot']."conf/sysconf.inc"?></u></p>
    <p> <b>2.</b><?=_(' For security reasons delete the temporary configuration file at ')?><u><?=$_POST['conffile']?></u></p>
    <p> <b>3.</b><?=_(' Once done click the button below to start Sahana or access it anytime using the url: ')?><a href="<?=$sahana_url?>"><?=$sahana_url?></a></p>

<?php        
    shn_form_fsclose();
    shn_form_submit(_('Start Sahana'));    
    shn_form_fclose();
}

// connect to the database and run the scripts specified by the user
function shn_setup_database()
{
    $db = &NewADOConnection('mysql');
    if (! $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass']) ) {
        add_error(_('Could not connect to the database. Please check the setting and try again'));
        return false;
    }

    // create the main database
    $db->Execute("CREATE DATABASE IF NOT EXISTS ".$_POST['dbname']);
    $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass'],$_POST['dbname']);


    // setup the choosen sql scripts
    if ($_POST['dbcreate']=='y') {
        shn_setup_run_sqlscript($db,'inst/mysql-dbcreate.sql');
        shn_setup_run_sqlscript($db,'inst/mysql-acl.sql');
        shn_setup_run_sqlscript($db,'mod/rms/ins/rms.sql');
        shn_setup_run_sqlscript($db,'mod/gis/dbcreate.sql');
        shn_setup_run_sqlscript($db,'mod/lr/dbcreate.sql');
        shn_setup_run_sqlscript($db,'mod/ims/ins/dbcreate.sql');
    }
    if ($_POST['dbconfig']=='y') 
        shn_setup_run_sqlscript($db,'inst/mysql-config.sql');
    if ($_POST['dbsample']=='y') 
        shn_setup_run_sqlscript($db,'inst/mysql-sampledata.sql');

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
