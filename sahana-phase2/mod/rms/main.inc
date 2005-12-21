<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_location.inc";
require_once 'lib_rms.inc';


/**
 * RMS main menu
 */
function shn_rms_mainmenu() 
{
    global $global;
    $module = $global['module'];
    $user_id = $global['person_id'];
    
?>
    
   <div id="modmenuwrap"> 
        <h2><?php print _("RMS Module Actions"); ?></h2>
            <ul id="modmenu">
                <li>
                    <a href="index.php?mod=<?=$module?>">
                    <?php print _("Home"); ?></a>
                </li>
                <li><a href="#">Requests</a></li>
                <ul>                    
                    <li><a href="index.php?mod=<?=$module?>&amp;act=req_new">
                    <?php print _("New Request"); ?></a>
                    </li>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=req_vw">
                    <?php print _("View Request"); ?></a>
                    </li>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=req_list">
                    <?php print _("View All Requests"); ?></a>
                    </li>
                   
                   <li><a href="index.php?mod=<?=$module?>&amp;act=req_srch">
                   <?php print _("Search Requests"); ?></a>
                   </li>
                </ul>
                <li><a href="#">Pledges</a></li>       
                <ul>                    
                    <li><a href="index.php?mod=<?=$module?>&amp;act=plg_new">
                    <?php print _("Add Pledges"); ?></a>
                    </li>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=plg_vw">
                    <?php print _("View Pledges"); ?></a>
                    </li>
                </ul>          
            </ul>
    </div> <!-- /modmainwrap -->
    <?php
    include $global['approot']."/inc/handler_mainmenu.inc"; 
} 

/**
 * The Default RMS homepage
 */
function shn_rms_default()
{
    include_once ('handler_main.inc');
}

function shn_rms_req_new()
{
    include_once ('handler_req_new.inc');
}

function shn_rms_req_vw()
{
    include_once ('handler_req_vw.inc');
}

function shn_rms_req_list()
{
    include_once ('handler_req_list.inc');
}

function shn_rms_req_srch()
{
    include_once ('handler_req_srch.inc');
}

/**
 * Pledges
 */
function shn_rms_plg_new()
{
    include_once ('handler_plg_new.inc');
}

function shn_rms_plg_vw()
{
    include_once ('handler_plg_vw.inc');
}



?>

