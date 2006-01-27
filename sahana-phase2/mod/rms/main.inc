<?php
/**
* Sahana Request Management System main page
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package
* @subpackage
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_form.inc";
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
	                <li><a href="index.php?mod=<?=$module?>&amp;act=new_req">
	                <?php print _("New Request"); ?></a>
	                </li>
	                <li><a href="index.php?mod=<?=$module?>&amp;act=vw_req&amp;user=all">
	                <?php print _("List All Requests"); ?></a>
	                </li>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=sc_req">
                    <?php print _("Search Requests"); ?></a>
                    </li>
                </ul>
                <li><a href="#">Pledges</a></li>
                <ul>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=new_plg">
                    <?php print _("Add Pledges"); ?></a>
                    </li>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=vw_plg">
                    <?php print _("View Pledge"); ?></a>
                    </li>
                    <li><a href="index.php?mod=<?=$module?>&amp;act=vw_plgs">
                    <?php print _("List Pledges"); ?></a>
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

/**
 * Add New request form
 */
function shn_rms_new_req()
{
    include_once ('handler_new_req.inc');
}

/**
 * List Requests
 */
function shn_rms_vw_req()
{
    include_once ('handler_view_req.inc');
}

function shn_rms_v_req()
{
    include_once ('handler_vw_req.inc');
}

/**
 * Search Requests
 */
function shn_rms_sc_req()
{
    include_once ('handler_sc_req.inc');
}

function shn_rms_mgt_req()
{
    include_once ('handler_mgt_req.inc');
}

/**
 * Pledges
 */
function shn_rms_new_plg()
{
    include_once ('handler_plg_new.inc');
}

function shn_rms_vw_plg()
{
    include_once ('handler_plg_vw.inc');
}

function shn_rms_vw_plgs()
{
    include_once ('handler_plg_ls.inc');
}

function shn_rms_del_plg()
{
    include_once ('handler_plg_del.inc');
}

function shn_rms_stat_plgs()
{
    include_once ('handler_plg_stat.inc');
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

