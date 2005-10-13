<?php 
/**
* Sahana front controller, through which all actions are dispatched
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

// === initialize global variables ===

// Find the base location of the Sahana installation
$global['approot']=realpath(dirname(__FILE__)).'/../';

// Initilize action and module global variables
$global['action'] = (NULL == $_REQUEST['act']) ? 
                            "default" : $_REQUEST['act'];
$global['module'] = (NULL == $_REQUEST['mod']) ? 
                            "home" : $_REQUEST['mod'];

// === initialize configuration variables ===
include_once ($global['approot']."conf/config.inc"); 
//TODO: when config is not there we have to setup

include_once ($global['approot']."inc/lib_modules.inc"); 
include ($global['approot']."inc/lib_session/session.inc");
include ($global['approot']."inc/lib_security/authenticate.inc");

shn_front_controller();

// === front controller ===

function shn_front_controller() {
 
    global $global;
    global $conf;
    $approot = $global['approot'];
    $action = $global['action'];
    $module = $global['module'];

    // Start a session and authenticate user
	shn_session_start();
	$user_data = shn_authenticate_user();

 	if($user_data["user_id"]>0){
		shn_session_change($user_data);
    }
    
    // if (shn_authorized("shn_".$module."_".$action", $user)..
    //    change session
    // error
    //    call the error handler
    // shn_modulename_err
    
    // include the html head tags
    include($approot."inc/handler_html_head.inc");
    
    // error handler

    // Redirect the module based on the action performed
    // redirect admin functions through the admin module
    if (preg_match('/^adm/',$action)) {
        $module = 'admin';   
        $action = 'modadmin';
    }

    // include the correct module file based on action and module
    $module_file = $approot."mod/".$module."/main.inc";

    if (file_exists($module_file)) {
        include($module_file); 
    } else {
        include($approot."mod/home/main.inc");
    }

    // include the module configuration files 
    $d = dir($approot."mod/");
    while (false !== ($f = $d->read())) {
        if (file_exists($approot."mod/".$f."/conf.inc")) {
          include ($approot."mod/".$f."/conf.inc");
        }
    } 

    // Start the body and the CSS container element
    ?>
    <body>
        <div id="container">
    <?php
    
    // include the page header provided there is not a module override
    shn_include_page_section('header',$module);
    
    // Now include the wrapper for the main content
    ?>     
            <div id="wrapper" class="clearfix"> 
                <p id="skip">Jump to: <a href="#content">Content</a> | <a href="#modulemenu">Module Menu</a></p> 
    <?php

    // include the mainmenu provided there is not a module override
    shn_include_page_section('mainmenu',$module);

    // now include the main content of the page
    ?>          <div id="content">                      <?php

    // compose and call the relevant module function 
    $module_function = "shn_".$module."_".$action;
    if (!function_exists($module_function)) {
        $module_function="shn_".$module."_default";
    }
    $module_function(); 
        
    #include($approot."test/testconf.inc"); 

    ?>          </div> <!-- /content -->                <?php

    // include the footer provided there is not a module override
    shn_include_page_section('footer',$module);
    ?>

                </div> <!-- /wrapper -->
        </div> <!-- /container -->
    </body>
    </html>
<?php 
}
?>

