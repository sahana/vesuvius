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
@ include ($global['approot']."conf/config.inc"); 
//TODO: when config is not there we have to setup

shn_front_controller();

// === front controller ===

function shn_front_controller() {
 
    global $global;
    global $conf;
    $approot = $global['approot'];
    $action = $global['action'];
    $module = $global['module'];

    // @todo: session authentication and authorization
    
    // Start a session
    session_start();
    
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
        #include($approot."mod/".$module."/admin.inc");
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

    // Start the body and the CSS container element
    echo '<body>';
    echo '<div id="container">';

    // include the page header provided there is not a module override
    $module_function = "shn_".$module."_header";
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($approot."inc/handler_header.inc");
    } 
    // Now include the wrapper for the main conent
    echo '<div id="wrapper" class="clearfix">';
    echo '<div id="navigation">';

    // include the mainmenu provided there is not a module override
    $module_function = "shn_".$module."_mainmenu";
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($approot."inc/handler_mainmenu.inc");
    }
    echo '</div> <!-- /navigation -->';

    // now include the main content of the page
    echo '<div id="content">';

    // compose and call the relevant module function 
    $module_function = "shn_".$module."_".$action;
    if (!function_exists($module_function)) {
        $module_function="shn_".$module."_default";
    }
    $module_function(); 
        
    include($approot."test/testconf.inc"); 

    echo '</div> <!-- /content -->';

    // include the footer provided there is not a module override
    $module_function = "shn_".$module."_footer";
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($approot."inc/handler_footer.inc");
    }
    ?>

    </div> <!-- /wrapper -->
    </div> <!-- /container -->
    </body>
    </html>
<?php 
}
?>
