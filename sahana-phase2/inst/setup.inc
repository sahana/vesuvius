<?php

require_once ($global['approot']."inc/handler_html_head.inc");
require_once ($global['approot'].'inc/lib_modules.inc'); 
require_once ($global['approot'].'inc/lib_form.inc'); 
require_once ($global['approot'].'inc/lib_errors.inc'); 
require_once ($global['approot'].'3rd/adodb/adodb.inc.php');

shn_setup_main();

// main setup switchboard 
function shn_setup_main()
{
    $action = $_GET['act'];

    // display nice header
    shn_setup_header();
    switch ($action) {

    case 'dbsetup':
        if (shn_setup_database()) { // check if database writing is a success
            //shn_setup_write_timestamp();
            shn_setup_form2();
        } else {
            display_errors();
            shn_setup_form1();
        }
        break;

    default:
        // first database setup form
        shn_setup_form1();

    }
    shn_setup_footer();
}

function shn_setup_form2()
{
?>
    <h1>Sahaha Web Setup</h2>
    <p> Installation is complete. To start using Sahana click on the button below.</p>
<?php

    shn_form_fopen("default");
    shn_form_submit('Start Sahana');
    shn_form_fclose();

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
    shn_form_submit('Setup Database');
 
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


function shn_setup_write_timestamp()
{
    global $global;
    $fh = fopen($global['approot'].'inst/install-timestamp','w');
    fputs($fh,"This instance of Sahana was installed on ".strftime('%c'));
    fclose($fh);
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
