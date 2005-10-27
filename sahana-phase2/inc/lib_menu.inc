<?php  
/**
* Template helpers for generating menus
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

function shn_mod_menuitem($action, $desc, $module = null ) 
{ 
    global $global;
    if ( null == $module ) $module = $global['module'];
?>
    <li><a href="index.php?mod=<?=$module?>&act=<?=$action?>"><?=$desc?></a></li>
<?php
}


function shn_mod_menuopen($desc ) 
{   
?>
    <div id="modmenuwrap"> 
    <h2><?=$desc?></h2>
    <ul id="modmenu">
<?php
}

function shn_mod_menuclose() 
{   
?>
    </ul>
    </div> <!-- /modmenuwrap -->
<?php
}
?>

