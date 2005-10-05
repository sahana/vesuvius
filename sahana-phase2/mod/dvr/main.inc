<?php
/**Main home page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author			
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";

function shn_dvr_mainmenu() 
{
    global $global;
    $module = $global['module'];
    include $global['approot']."/inc/handler_mainmenu.inc";
?>
    
        <h2>DVR Module Actions</h2>
        <dl>
       <dt><a href="index.php?mod="></a></dt>
        <dd>
            <ul>
                <li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=add">Add Entry</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=search&adv=1">Edit Entry</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=search&adv=1">Search</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=stats">Statistics</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=help">Help/FAQ</a></li>
            </ul>
        </dd>
       </dt>
    <?php 
} 
	
function shn_dvr_view()
{?>
    <p><b> DVR View Action </b></p> 
    <p> You made a call to the view action of the DVR module</p>
<?php
}

function shn_dvr_default()
{
?>
    <p><b> Welcome to the DVR home </b></p>
    <p> This is the default view</p>


<?php
}
?>

