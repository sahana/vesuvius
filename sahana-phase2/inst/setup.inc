<?php

    require_once ($global['approot']."inc/handler_html_head.inc");
    require_once ($global['approot'].'inc/lib_modules.inc'); 
    require_once ($global['approot'].'inc/lib_form.inc'); 

    shn_setup_main();

function shn_setup_main()
{
    $action = $_GET['act'];

    shn_setup_header();
    switch ($action) {

    case 'setup':
        shn_setup_write_timestamp();
        shn_setup_form2();
        break;

    default:
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

function shn_setup_form1()
{
 ?>
    <h1>Sahaha Web Setup</h2>
    <p> Welcome to Sahana. Please follow the following steps to setup the Sahana system </p>
<?php

    shn_form_fopen("setup");

    shn_form_fsopen('Database');
    shn_form_text('Database Host','dbhost','size="30"');
    shn_form_text('Database Name','dbname','size="30"');
    shn_form_text('Database User','dbuser','size="30"');
    shn_form_text('Database Password','dbpass','size="30"');
    shn_form_fsclose();

    shn_form_submit('Setup');
 
    shn_form_fclose();
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
