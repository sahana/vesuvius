<?php
/* $Id: lib_stream_html.inc,v 1.1 2006-07-24 10:58:26 janakawicks Exp $ */

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

    // include the html head tags
    shn_include_page_section('html_head',$global['module']);  

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
