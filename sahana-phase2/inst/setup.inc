<?php

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

    case 'dbsetup':
        if (shn_setup_database()) { // check if database writing is a success
            shn_setup_form2();
        } else {
            display_errors();
            shn_setup_form1();
        }
        break;
        
    case 'cfgsetup':

        if (shn_setup_config_update()) { // check if writing the file was a success
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

// the config file setup form
function shn_setup_form2()
{
 ?>
    <h1>Sahaha Web Setup - Step 2</h2>
    <p> Please follow the following steps to setup the Sahana configuration </p>
<?php
    shn_form_fopen("cfgsetup");
    
    // pass the previous post varibles into hidden for the configuration file
    shn_form_hidden( array(
        'dbhost' => $_POST['dbhost'] ,
        'dbname' => $_POST['dbname'] ,
        'dbuser' => $_POST['dbuser'] ,
        'dbpass' => $_POST['dbpass'] ));           

    shn_form_fsopen('Configuration');
    shn_form_select(
        array( 'default' => 'Default Theme', 'green_theme' => 'Green Theme'), 
                "Theme", "theme");
    shn_form_fsclose();

    shn_form_submit('Setup Configuration >>');
 
    shn_form_fclose();
}
function shn_setup_form3()
{
    global $global;
    if (copy('/tmp/sahana-config.inc', $global['approot'].'conf/config.inc')) {
?>
    <h1>Sahaha Web Setup</h2>
    <p> Installation is complete. To start using Sahana click on the button below.</p>
<?php
        shn_form_fopen("default");
        shn_form_submit('Start Sahana');
        shn_form_fclose();
    }

}

// the database setup form
function shn_setup_form1()
{
 ?>
    <h1>Sahaha Web Setup</h2>
    <p> Welcome to Sahana. Please follow the following steps to setup the Sahana system </p>
<?php

    shn_form_fopen("dbsetup");

    shn_form_fsopen('Database');
    shn_form_text('Database Host:Port','dbhost','size="30"',
                array('value'=>'localhost','req'=>true ));
    shn_form_text('Database Name','dbname','size="30"',
                array('value'=>'sahana', 'req'=>true));
    shn_form_text('Database User','dbuser','size="30"',
                array('value'=>'root', 'req'=>true));
    shn_form_text('Database Password','dbpass','size="30"', array('req'=>true));
    shn_form_fsclose();

    shn_form_fsopen('Schema\'s to Install');
    shn_form_checkbox('Create Main Database tables','dbcreate',"checked",
                        array('value'=>'y')); 
    shn_form_checkbox('Default Configuration','dbconfig',"checked",
                        array('value'=>'y')); 
    shn_form_checkbox('Sample Data','dbsample','',
                        array('value'=>'y')); 
    shn_form_fsclose();
    shn_form_submit('Setup Database >>');
 
    shn_form_fclose();
}

// connect to the database and run the scripts specified by the user
function shn_setup_database()
{
    $db = &NewADOConnection('mysql');
    if (! $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass']) ) {
        add_error("Could not connect to the database. Please check the setting and try again");
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


function shn_setup_config_update()
{
    global $global;

    $modify = array( 
        '/\'sahana_status\'/' => '$conf[\'sahana_status\'] = \'installed\';' ,
        '/\'theme\'/' => '$conf[\'theme\'] = \''.$_POST['theme'].'\';' ,
        '/\'db_host\'/' => '$conf[\'db_host\'] = \''.$_POST['dbhost'].'\';' ,
        '/\'db_name\'/' => '$conf[\'db_name\'] = \''.$_POST['dbname'].'\';' ,
        '/\'db_user\'/' => '$conf[\'db_user\'] = \''.$_POST['dbuser'].'\';' ,
        '/\'db_pass\'/' => '$conf[\'db_pass\'] = \''.$_POST['dbpass'].'\';' );           

    shn_config_update( $modify, $global['approot'].'conf/config.inc',
                            '/tmp/sahana-config.inc');

    return true;
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
