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

    // @todo: session authentication and authorization
    
    // include the html head tags
    include($approot."inc/handler_html_head.inc");
    
    // include the page header provided there is not a module override
    $module_function = "shn_".$global['module']."_header";
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($approot."inc/handler_header.inc");
    }

    include($approot."test/testconf.inc");
    ?>
   <?php


    // include the correct module file based on action and module
    $module_file = $approot."mod/".$global['module']."/main.inc";

    if (file_exists($module_file)) {
        @ include($module_file); 
    } else {
        @ include($approot."mod/home/main.inc");
    }

    // compose and call the relevant module function 
    $module_function = "shn_".$global['module']."_".$global['action'];
    if (!function_exists($module_function)) {
        $module_function="shn_".$global['module']."_default";
    }
    $module_function(); ?>
        

       <div id="page_content_footer"></div>
      </div>
    <?php 

    // include the mainmenu provided there is not a module override
    $module_function = "shn_".$global['module']."_mainmenu";
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($approot."inc/handler_mainmenu.inc");
    }

    // include the footer provided there is not a module override
    $module_function = "shn_".$global['module']."_footer";
    if (function_exists($module_function)) {
        $module_function();
    } else {
        include($approot."inc/handler_footer.inc");
    }
    ?>
 
    </div>
   </body>
  </html>
<?php 
}
?>
