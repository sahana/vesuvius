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

// Specify the base location of the Sahana insallation
// The base should not be exposed to the web for security reasons
// only the www sub directory should be exposed to the web

$global['approot'] = realpath(dirname(__FILE__)).'/../';
// $global['approot'] = '/usr/local/bin/sahana/';
$global['previous']=false;
// === initialize configuration variables ===
require_once ($global['approot'].'conf/config.inc'); 

if ($conf['sahana_status'] == 'installed' ) {

    require_once ($global['approot'].'inc/lib_modules.inc'); 
    require_once ($global['approot'].'inc/handler_db.inc');
    require_once ($global['approot'].'inc/lib_session/handler_session.inc');
    require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    require_once ($global['approot'].'inc/lib_security/acl_api.inc');
    require_once ($global['approot'].'inc/lib_locale/handler_locale.inc'); 

    if(!$global['previous']){
        $global['action'] = (NULL == $_REQUEST['act']) ? 
                                "default" : $_REQUEST['act'];
        $global['module'] = (NULL == $_REQUEST['mod']) ? 
                                "home" : $_REQUEST['mod'];
    }
    shn_front_controller();

} else { // Launch the web setup
    
    require ($global['approot'].'inst/setup.inc');
}

// === front controller ===

function shn_front_controller() 
{
    global $global;
    global $conf;
    $approot = $global['approot'];
    $action = $global['action'];
    $module = $global['module'];
   
    // check the users access permissions for this action
    $req_act="shn_".$module."_".$action;
    $acl_enabled=shn_acl_get_state();
//    $module_enabled=shn_acl_is_enabled($module);
    $allow = (shn_acl_check_perms_action($_SESSION["user_id"],$req_act) || 
             !$acl_enabled)? true : false;
    // include the html head tags
    include($approot."inc/handler_html_head.inc");
    
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

    // include the mainmenu provided there is not a module override
    shn_include_page_section('login',$module);

    // now include the main content of the page
?>  
    <div id="content" class="clearfix">      
<?php
    if($allow){
        // compose and call the relevant module function 
        $module_function = "shn_".$module."_".$action;
        if (!function_exists($module_function)) {
            $module_function="shn_".$module."_default";
        }
        $_SESSION["last_module"]=$module;
        $_SESSION["last_action"]=$action;
        $module_function(); 
    }else {
         echo "<center><div><h1>you dont have permission to view this page</h1></div></center>";
    }
    #include($approot."test/testconf.inc"); 
?>
    </div> <!-- /content -->
<?php

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

