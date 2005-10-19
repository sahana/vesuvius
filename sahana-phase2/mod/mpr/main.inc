<?php
/* $Id: main.inc,v 1.1 2005-10-19 06:08:20 chamindra Exp $ */

/**Main home page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Mifan Careem <mifan@opensource.lk>
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @author	  Saumya Gunawardana <saumya@opensource.lk>
* @author	  Chamindra de Silva <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";


function shn_mpr_mainmenu() 
{
    global $global;
    $module = $global['module'];
?>
   <div id="modmenuwrap"> 
        <h2>Missing Person Registry</h2>
            <ul id="modmenu">
                <li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=addmp">Report a Missing Person</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=fndmp">Report a Found Person</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=search">Search for a Person</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=stats">Statistics</a></li>
            </ul>
    </div> <!-- /modmenuwrap -->
    <?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
	
function shn_mpr_default()
{
    global $global;
}

function shn_mpr_fndmp()
{
    global $global;
    echo "<h2>Find a Missing Person</h2>";
}

function shn_mpr_addmp()
{
    global $global;
    echo "<h2>Add a Missing Person</h2>";
}

function shn_mpr_search()
{
    global $global;
    echo "<h2>Search for a Missing Person</h2>";
}

?>

