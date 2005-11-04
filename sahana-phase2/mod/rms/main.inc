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
                <li><a href="index.php?mod=<?=$module?>">
                    <?php print _("Home"); ?></a>
                </li>
                <li><a href="index.php?mod=<?=$module?>&amp;act=new_req">
                    <?php print _("Make New Request"); ?></a>
                </li>
                <li><a href="index.php?mod=<?=$module?>&amp;act=vw_req&amp;user=all">
                    <?php print _("View All Requests"); ?></a>
                </li>
                <?php 
                    if(is_a_requester($user_id))
                    { 
                ?>
                <li><a href="index.php?mod=<?=$module?>&amp;act=vw_req&amp;user=user">
                    <?php print _("View My Requests"); ?></a>
                </li>  
               <?php } ?>              
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

/**
 * Add New request form
 */
function shn_rms_new_req()
{
    include_once ('handler_new_req.inc');
}

/**
 * Add New request form
 */
function shn_rms_vw_req()
{
    include_once ('handler_view_req.inc');
}


function shn_rms_mgt_req()
{
    include_once ('handler_mgt_req.inc');
}

/**
 * Enter Fulfilment information
 */
function shn_rms_fulfill_req()
{
    include_once ('handler_fulfill_req.inc');
}

function shn_rms_cstat_req()
{
    include_once ('handler_cstat_req.inc');
}

?>

