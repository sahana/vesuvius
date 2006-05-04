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
$approot = $global['approot'];
$global['previous']=false;

// === include all base libraries ==
require_once ($global['approot'].'inc/lib_config.inc');
require_once ($global['approot'].'inc/lib_modules.inc'); 

// === filter the GET and POST ===
shn_main_filter_getpost();

// === Setup if not setup and load configuration === 

// if installed the sysconf.inc will exist in the conf directory
if (!file_exists($global['approot'].'conf/sysconf.inc')){

    // launch the web setup
    require_once ($global['approot'].'conf/sysconf.inc.tpl'); 
    require ($global['approot'].'inst/setup.inc');

} else {

    require_once ($global['approot'].'conf/conf-order.inc');
    require ($global['approot'].'conf/sysconf.inc'); 
    require_once ($global['approot'].'inc/handler_db.inc');
    require_once ($global['approot'].'inc/lib_session/handler_session.inc');
    require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    require_once ($global['approot'].'inc/lib_locale/handler_locale.inc'); 

    //include the user preferences
    include_once ($global['approot'].'inc/lib_user_pref.inc');
    shn_user_pref_populate();

    // give database the priority or the conf files
    if ('database' ==  $conf['sahana_conf_priority'] ) {
        // database overrides conf files
        shn_config_base_conf_fetch();
        shn_config_module_conf_fetch('all');
        shn_config_module_conf_fetch($global['module']);
        shn_config_database_fetch('base');
        shn_config_database_fetch($global['module']);
    } else {
        // conf files overrides database
        shn_config_database_fetch('base');
        shn_config_database_fetch($global['module']);
        shn_config_base_conf_fetch();
        shn_config_module_conf_fetch('all');
        shn_config_module_conf_fetch($global['module']);
    }

    shn_main_front_controller();
}

// === process the GET and POST ===
function shn_main_filter_getpost()
{
    global $global;

    if(!$global['previous']){
        $global['action'] = (NULL == $_REQUEST['act']) ? 
                                "default" : $_REQUEST['act'];
        $global['module'] = (NULL == $_REQUEST['mod']) ? 
                                "home" : $_REQUEST['mod'];
    }
}


// === front controller ===
function shn_main_front_controller() 
{
    global $global;
    global $conf;
    $approot = $global['approot'];
    $action = $global['action'];
    $module = $global['module'];

    // Redirect the module based on the action performed
    // redirect admin functions through the admin module
    if (preg_match('/^adm/',$action)) {
        $module = 'admin';
        $action = 'modadmin';
    } // the orignal module and action is stored in $global
  
    // check the users access permissions for this action
    $module_function = 'shn_'.$module.'_'.$action;
   
	$acl_enabled=shn_acl_get_state($module);

    // @TODO: test against admin function is wrong
    $allow = (!shn_acl_check_perms_action($_SESSION['user_id'], $module_function) || 
             !$acl_enabled)? true : false;

    // include the correct module file based on action and module
    $module_file = $approot.'mod/'.$module.'/main.inc';

    if (file_exists($module_file)) {
        include($module_file); 
    } else {
        include($approot.'mod/home/main.inc');
    }

    // include the html head tags
    shn_include_page_section('html_head', $module);

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
    <div id="wrapper_menu">
    <p id="skip">Jump to: <a href="#content"><?=_('Content')?></a> | <a href="#modulemenu"><?=_('Module Menu')?></a></p> 
<?php

    // include the mainmenu and login provided there is not a module override
    shn_include_page_section('mainmenu',$module);
    shn_include_page_section('login',$module);

    // now include the main content of the pageA
?>  
    </div> <!-- Left hand side menus & login form -->
    <div id="content" class="clearfix">      
<?php
    if($allow){
        // compose and call the relevant module function 
        if (!function_exists($module_function)) {
            $module_function='shn_'.$module.'_default';
        }
        $_SESSION['last_module']=$module;
        $_SESSION['last_action']=$action;
        $module_function(); 
    }else {
        shn_error_display_restricted_access();
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

