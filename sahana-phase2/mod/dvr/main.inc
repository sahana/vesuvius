<?php
/* $Id: main.inc,v 1.11 2005-10-13 10:39:55 chamindra Exp $ */

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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";


function shn_dvr_mainmenu() 
{
    global $global;
    $module = $global['module'];
?>
   <div id="modmenuwrap"> 
        <h2>DVR Module Actions</h2>
            <ul id="modmenu">
                <li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=add">Add Entry</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=search">Edit Entry</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=search">Search</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=stats">Statistics</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=help">Help/FAQ</a></li>
            </ul>
    </div> <!-- /modmenuwrap -->
    <?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
	
function shn_dvr_view()
{?>
    <p><b> DVR View Action </b></p> 
    <p> You made a call to the view action of the DVR module</p>
<?php
}

function shn_dvr_default()
{
    global $global;
    include $global['approot']."/mod/dvr/home.inc";
}

function shn_dvr_search()
{
    global $global;
    //include the dvr search function library
    include $global['approot']."/mod/dvr/search.inc";
}

//Main Add Controller
function shn_dvr_add()
{

    global $global;
    //include the dvr add function library
    include ($global['approot'].'/mod/dvr/add.inc');

    //Include the presentation layer
    //@todo : (may be not for this) check the presentation layer
    require_once ($global['approot'].'/inc/handler_form.inc');

    //check the add_sequence
    switch ($_REQUEST['add_sequence']){
    case 'start':
        _shn_dvr_add_show_form();
        break;
    default :
        _shn_dvr_add_default();
        break;
    }

}
?>

