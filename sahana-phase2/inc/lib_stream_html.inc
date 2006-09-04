<?php
/* $Id: lib_stream_html.inc,v 1.3 2006-09-04 10:32:47 chamindra Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    <package>
 * @subpackage <subpackage>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
function shn_stream_init()
{
    global $global;
    global $conf;

    $module = $global['module'];

    // include the html head tags
    shn_include_page_section('html_head',$module);  

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

    // hack for the admin section such that the mene and login come from 
    // the admin section
    if ($global['effective_module'] != null) {
        $module = $global['effective_module'];
    }

    // include the mainmenu and login provided there is not a module override
    shn_include_page_section('mainmenu',$module);
    shn_include_page_section('login',$module);

    // display the breadcrumbs: It is important that this happens after the menu definition
    shn_breadcrumb_push($global['shn_'.$global['module'].'_'.$global['action'].'_nicename']);

    shn_breadcrumb_display(); 
    // now include the main content of the page
?>  
    </div> <!-- Left hand side menus & login form -->
    <div id="content" class="clearfix">      
<?php

}

function shn_stream_close()
{
    global $global;
?>
    </div> <!-- /content -->
<?php

    // include the footer provided there is not a module override
    shn_include_page_section('footer',$global['module']);
?>
    </div> <!-- /wrapper -->
    </div> <!-- /container -->
    </body>
    </html>
<?php
}
?>
